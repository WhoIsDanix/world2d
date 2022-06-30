/*
    * sol::stack::call and its variants will, if no templated boolean is specified, check all of the arguments for a function call
    * All calls from Lua will have their arguments checked
*/
#define SOL_SAFE_FUNCTION_CALLS 1

/*
    * All uses of sol::function and sol::stack_function will default to sol::protected_function and sol::stack_protected_function, respectively, rather than sol::unsafe_function and sol::stack_unsafe_function
    * Note this does not apply to sol::stack_aligned_function: this variant must always be unprotected due to stack positioning requirements, especially in use with sol::stack_count
    * Will make any sol::state_view::script calls default to their safe variants if there is no supplied environment or error handler function
*/
#define SOL_SAFE_FUNCTION 1

#define WORLD2D_VERSION "0.01 WIP"

#include "world2d/Engine.h"

#include "world2d/modules/GraphicsModule.h"
#include "world2d/modules/ImGuiModule.h"

#include "world2d/modules/WindowModule.h"
#include "world2d/modules/KeyboardModule.h"
#include "world2d/modules/MouseModule.h"
#include "world2d/modules/ClipboardModule.h"
#include "world2d/modules/TimerModule.h"

#include <cxxabi.h> // abi::__cxa_demangle
#include <iostream>

int engine_exception_handler(lua_State* L, sol::optional<const std::exception&> maybe_exception, sol::string_view description) {
    std::cout << "Error occured: ";

    if (maybe_exception) {
        const std::exception& ex = *maybe_exception;
        std::cout << ex.what();
    } else {
        std::cout.write(description.data(), description.size());
    }

    std::cout << "\n";
    return sol::stack::push(L, description);
}

inline void engine_at_panic(sol::optional<std::string> maybe_msg) {
    if (maybe_msg) {
        const std::string& msg = maybe_msg.value();
        std::cerr << "Lua Error: " << msg << "\n";
    }
}

world2d::Engine::Engine() {

}

world2d::Engine::~Engine() {
    SDL_DestroyRenderer(mSDLRenderer);
    SDL_DestroyWindow(mSDLWindow);

    mSDLRenderer = nullptr;
    mSDLWindow = nullptr;

    SDL_Quit();
}

void world2d::Engine::LoadModules() {
    if (mModules.size() > 0) {
        return;
    }

    mModules.push_back(world2d::GraphicsModule::Get());
    mModules.push_back(world2d::ImGuiModule::Get());

    mModules.push_back(world2d::WindowModule::Get());
    mModules.push_back(world2d::KeyboardModule::Get());
    mModules.push_back(world2d::MouseModule::Get());
    mModules.push_back(world2d::ClipboardModule::Get());
    mModules.push_back(world2d::TimerModule::Get());
}

bool world2d::Engine::CompileAndRun(const char* filename) {
    mSDLWindow = SDL_CreateWindow("world2d Application", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_RESIZABLE);

    if (mSDLWindow == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to create SDL window: %s", SDL_GetError());
        return false;
    }

    mSDLRenderer = SDL_CreateRenderer(mSDLWindow, -1, SDL_RENDERER_ACCELERATED);

    if (mSDLRenderer == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to create SDL renderer: %s", SDL_GetError());
        return false;
    }

    mLuaState.open_libraries();

    mLuaState.set_exception_handler(&engine_exception_handler);
    mLuaState.set_panic(sol::c_call<decltype(&engine_at_panic), &engine_at_panic>);

    sol::table luaWorld2dNamespace { mLuaState.create_named_table("world2d") };

    luaWorld2dNamespace["Version"] = WORLD2D_VERSION;
    luaWorld2dNamespace.set_function("GetPlatform", &SDL_GetPlatform);

    for (world2d::Module* module : mModules) {
        if (!module->Initialize()) {
            int status;
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize module %s", abi::__cxa_demangle(typeid(*module).name(), 0, 0, &status));
        }
    }

    auto result = mLuaState.safe_script_file(filename, sol::script_pass_on_error);

    if (!result.valid()) {
        sol::error err = result;
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to compile Lua: %s", err.what());

        return false;
    }

    for (world2d::Module* module : mModules) {
        module->BeforeRun();
    }

    mNow = SDL_GetPerformanceCounter();
    mLast = 0;
    mDeltaTime = 0;

    while (mIsRunning) {
        mLast = mNow;
        mNow = SDL_GetPerformanceCounter();

        mDeltaTime = ((mNow - mLast) * 1000 / (double)SDL_GetPerformanceFrequency());

        while (SDL_PollEvent(&mSDLEvent)) {
            if (mSDLEvent.type == SDL_QUIT) {
                mIsRunning = false;
            }

            for (Module* module : mModules) {
                module->OnEvent(mSDLEvent);
            }
        }

        for (world2d::Module* module : mModules) {
            module->Update(mDeltaTime);
        }

        SDL_SetRenderDrawColor(mSDLRenderer, 0, 0, 0, 255);
        SDL_RenderClear(mSDLRenderer);

        for (world2d::Module* module : mModules) {
            module->Render();
        }

        SDL_RenderPresent(mSDLRenderer);
    }

    return true;
}

SDL_Window* world2d::Engine::GetSDLWindow() {
    return mSDLWindow;
}

SDL_Renderer* world2d::Engine::GetSDLRenderer() {
    return mSDLRenderer;
}

sol::state& world2d::Engine::GetLua() {
    return mLuaState;
}

world2d::Engine* world2d::Engine::Get() {
    static world2d::Engine currentEngine;
    return &currentEngine;
}