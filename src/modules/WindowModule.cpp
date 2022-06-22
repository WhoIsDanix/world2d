#include "world2d/modules/WindowModule.h"
#include <tuple>

world2d::WindowModule::WindowModule() : world2d::Module() {

}

bool world2d::WindowModule::Initialize() {
    sol::state& lua = mEngine->GetLua();

    sol::table luaWorld2dNamespace { lua.get<sol::table>("world2d") };
    sol::table luaWindowNamespace { lua.create_table() };

    // ===== Enums =====
    luaWindowNamespace.new_enum("MessageBoxType",
        "Error", SDL_MESSAGEBOX_ERROR,
        "Warning", SDL_MESSAGEBOX_WARNING,
        "Information", SDL_MESSAGEBOX_INFORMATION
    );

    luaWindowNamespace.new_enum("FlashOperation",
        "Cancel", SDL_FLASH_CANCEL,
        "Briefly", SDL_FLASH_BRIEFLY,
        "UntilFocused", SDL_FLASH_UNTIL_FOCUSED
    );
    // =================

    // ===== Main functions =====
    luaWindowNamespace.set_function("SetPosition", [&](int x, int y) {
        SDL_SetWindowPosition(mEngine->GetSDLWindow(), x, y);
    });

    luaWindowNamespace.set_function("SetSize", [&](int w, int h) {
        SDL_SetWindowSize(mEngine->GetSDLWindow(), w, h);
    });

    luaWindowNamespace.set_function("GetSize", [&]() {
        int w, h;
        SDL_GetWindowSize(mEngine->GetSDLWindow(), &w, &h);
        return std::make_tuple(w, h);
    });

    luaWindowNamespace.set_function("SetTitle", [&](const char* title) {
        SDL_SetWindowTitle(mEngine->GetSDLWindow(), title);
    });

    luaWindowNamespace.set_function("SetResizable", [&](SDL_bool resizable) {
        SDL_SetWindowResizable(mEngine->GetSDLWindow(), resizable);
    });

    luaWindowNamespace.set_function("ShowSimpleMessageBox", [&](SDL_MessageBoxFlags flags, const char* title, const char* message) {
        if (SDL_ShowSimpleMessageBox(flags, title, message, mEngine->GetSDLWindow()) != 0) {
            luaL_error(lua.lua_state(), SDL_GetError());
        }
    });

    luaWindowNamespace.set_function("GetTitle", [&]() {
        if (SDL_GetWindowTitle(mEngine->GetSDLWindow()) != 0) {
            luaL_error(lua.lua_state(), SDL_GetError());
        }
    });

    luaWindowNamespace.set_function("Flash", [&](SDL_FlashOperation operation) {
        return static_cast<bool>(SDL_FlashWindow(mEngine->GetSDLWindow(), operation));
    });

    luaWindowNamespace.set_function("SetVSync", [&](bool vsync) {
        if (SDL_RenderSetVSync(mEngine->GetSDLRenderer(), vsync) != 0) {
            luaL_error(lua.lua_state(), SDL_GetError());
        }
    });

    luaWindowNamespace.set_function("GetDisplaySize", [&]() {
        SDL_DisplayMode mode;
        SDL_GetCurrentDisplayMode(0, &mode);
        return std::make_tuple(mode.w, mode.h);
    });
    // ==========================

    luaWorld2dNamespace["Window"] = luaWindowNamespace;
    return true;
}

world2d::WindowModule* world2d::WindowModule::Get() {
    static world2d::WindowModule currentModule;
    return &currentModule;
}