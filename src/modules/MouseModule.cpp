#include "world2d/modules/MouseModule.h"

#include <string>
#include <tuple>

world2d::MouseModule::MouseModule() : world2d::Module() {

}

bool world2d::MouseModule::Initialize() {
    sol::state& lua = mEngine->GetLua();

    sol::table luaWorld2dNamespace { lua.get<sol::table>("world2d") };
    sol::table luaMouseNamespace { lua.create_table() };

    luaWorld2dNamespace.set_function("MousePressed", [&]() {});
    luaWorld2dNamespace.set_function("MouseReleased", [&]() {});

    luaMouseNamespace.set_function("GetCoordinates", [&]() {
        int x = 0, y = 0;
        SDL_GetMouseState(&x, &y);
        return std::make_tuple(x, y);
    });

    luaWorld2dNamespace["Mouse"] = luaMouseNamespace;
    return true;
}

void world2d::MouseModule::OnEvent(SDL_Event& event) {
    if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
        const char* funcName = (event.type == SDL_MOUSEBUTTONDOWN) ? "MousePressed" : "MouseReleased";
        std::string buttonName;

        switch (event.button.button) {
            case SDL_BUTTON_LEFT:
                buttonName = "Left";
                break;

            case SDL_BUTTON_MIDDLE:
                buttonName = "Middle";
                break;

            case SDL_BUTTON_RIGHT:
                buttonName = "Right";
                break;
        }

        mEngine->GetLua().get<sol::table>("world2d").get<sol::function>(funcName)(event.button.x, event.button.y, buttonName.c_str());
    }
}

world2d::MouseModule* world2d::MouseModule::Get() {
    static world2d::MouseModule currentModule;
    return &currentModule;
}