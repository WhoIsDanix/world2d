#ifndef WORLD2D_GRAPHICSMODULE_H
#define WORLD2D_GRAPHICSMODULE_H

#include "world2d/Engine.h"
#include "world2d/Module.h"

namespace world2d {
    class GraphicsModule : public world2d::Module {
    public:
        GraphicsModule();
        GraphicsModule(const GraphicsModule&) = delete;
        ~GraphicsModule();

        bool Initialize() override;
        void BeforeRun() override;
        void Update(double deltaTime) override;
        void Render() override;

        static GraphicsModule* Get();
    };
}

#endif