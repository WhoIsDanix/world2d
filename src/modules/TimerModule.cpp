#include "world2d/modules/TimerModule.h"

world2d::TimerModule::TimerModule() : world2d::Module() {

}

bool world2d::TimerModule::Initialize() {
    sol::state& lua = mEngine->GetLua();

    sol::table luaWorld2dNamespace { lua.get<sol::table>("world2d") };
    sol::table luaTimerNamespace { lua.create_table() };

    luaTimerNamespace.set_function("Delay", SDL_Delay);

    luaWorld2dNamespace["Timer"] = luaTimerNamespace;
    return true;
}

world2d::TimerModule* world2d::TimerModule::Get() {
    static world2d::TimerModule currentModule;
    return &currentModule;
}