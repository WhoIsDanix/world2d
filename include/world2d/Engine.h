#ifndef WORLD2D_ENGINE_H
#define WORLD2D_ENGINE_H

#include "SDL/SDL.h"

#include "world2d/Module.h"
#include <vector>

extern "C" {
    #include "lua/lua.h"
    #include "lua/lauxlib.h"
    #include "lua/lualib.h"
}

#include <sol/sol.hpp>

namespace world2d {
    class Module;

    class Engine {
    private:
        SDL_Window* mSDLWindow = nullptr;
        SDL_Renderer* mSDLRenderer = nullptr;

        SDL_Event mSDLEvent;
        bool mIsRunning = true;

        sol::state mLuaState;
        std::vector<world2d::Module*> mModules;

        Uint64 mNow, mLast;
        double mDeltaTime;

    public:
        Engine();
        ~Engine();

        void LoadModules();
        bool CompileAndRun(const char* filename);

        SDL_Window* GetSDLWindow();
        SDL_Renderer* GetSDLRenderer();
        sol::state& GetLua();

        static Engine* Get();
    };
}

#endif