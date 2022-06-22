#include "world2d/modules/ClipboardModule.h"
#include <cstring>

world2d::ClipboardModule::ClipboardModule() : world2d::Module() {

}

bool world2d::ClipboardModule::Initialize() {
    sol::state& lua { mEngine->GetLua() };

    sol::table luaWorld2dNamespace { lua.get<sol::table>("world2d") };
    sol::table luaClipboardNamespace { lua.create_table() };

    luaClipboardNamespace.set_function("GetText", [&]() {
        return SDL_GetClipboardText();
    });

    luaClipboardNamespace.set_function("HasText", [&]() {
        return static_cast<bool>(SDL_HasClipboardText());
    });

    luaClipboardNamespace.set_function("SetText", [&](const char* text) {
        int success = SDL_SetClipboardText(text);
        // TODO: throw an error when success != 0
    });

    luaWorld2dNamespace["Clipboard"] = luaClipboardNamespace;
    return true;
}

world2d::ClipboardModule* world2d::ClipboardModule::Get() {
    static world2d::ClipboardModule currentModule;
    return &currentModule;
}