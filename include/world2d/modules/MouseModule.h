#ifndef WORLD2D_MODULES_MOUSEMODULE_H
#define WORLD2D_MODULES_MOUSEMODULE_H

#include "world2d/Module.h"

namespace world2d {
    class MouseModule : public world2d::Module {
    public:
        MouseModule();

        bool Initialize();
        void OnEvent(SDL_Event& event);

        static MouseModule* Get();
    };
}

#endif