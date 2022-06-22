#ifndef WORLD2D_MODULES_KEYBOARDMODULE_H
#define WORLD2D_MODULES_KEYBOARDMODULE_H

#include "world2d/Module.h"

namespace world2d {
    class KeyboardModule : public world2d::Module {
    public:
        KeyboardModule();

        bool Initialize();
        void OnEvent(SDL_Event& event);

        static KeyboardModule* Get();
    };
}

#endif