#ifndef WORLD2D_MODULES_TIMERMODULE_H
#define WORLD2D_MODULES_TIMERMODULE_H

#include "world2d/Module.h"

namespace world2d {
    class TimerModule : public world2d::Module {
    public:
        TimerModule();
        bool Initialize();

        static TimerModule* Get();
    };
}

#endif