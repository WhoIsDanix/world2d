#ifndef WORLD2D_MODULE_H
#define WORLD2D_MODULE_H

#include "SDL/SDL.h"
#include "Engine.h"

namespace world2d {
    class Engine;

    class Module {
    protected:
        world2d::Engine* mEngine = nullptr;

    public:
        Module();

        virtual bool Initialize();
        virtual void BeforeRun();
        virtual void OnEvent(SDL_Event& event);
        virtual void Update(double deltaTime);
        virtual void Render();
    };
}

#endif