#ifndef WORLD2D_MODULES_WINDOWMODULE_H
#define WORLD2D_MODULES_WINDOWMODULE_H

#include "world2d/Engine.h"

namespace world2d {
    class WindowModule : public world2d::Module {
    public:
        WindowModule();
        WindowModule(const WindowModule&) = delete;
        bool Initialize() override;

        static WindowModule* Get();
    };
}

#endif