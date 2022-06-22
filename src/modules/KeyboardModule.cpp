#include "world2d/modules/KeyboardModule.h"

world2d::KeyboardModule::KeyboardModule() : world2d::Module() {

}

bool world2d::KeyboardModule::Initialize() {
    sol::state& lua = mEngine->GetLua();

    sol::table luaWorld2dNamespace { lua.get<sol::table>("world2d") };
    sol::table luaKeyboardNamespace { lua.create_table() };

    luaKeyboardNamespace.set_function("IsKeyPressed", [&](const char* key) {
        // TODO: make this safe (we don't check if key is valid)

        const Uint8 *state = SDL_GetKeyboardState(nullptr);
        return (bool)state[SDL_GetScancodeFromName(key)];
    });

    luaWorld2dNamespace["Keyboard"] = luaKeyboardNamespace;
    return true;
}

void world2d::KeyboardModule::OnEvent(SDL_Event& event) {
    sol::table luaWorld2dNamespace = mEngine->GetLua().get<sol::table>("world2d");

    switch (event.type) {
        case SDL_KEYUP:
            luaWorld2dNamespace.get<sol::function>("KeyUp")(SDL_GetKeyName(event.key.keysym.sym), event.key.repeat);
            break;

        case SDL_KEYDOWN:
            luaWorld2dNamespace.get<sol::function>("KeyDown")(SDL_GetKeyName(event.key.keysym.sym), event.key.repeat);
            break;
    }
}

world2d::KeyboardModule* world2d::KeyboardModule::Get() {
    static world2d::KeyboardModule currentModule;
    return &currentModule;
}