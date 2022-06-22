#ifndef WORLD2D_IMGUIMODULE_H
#define WORLD2D_IMGUIMODULE_H

#include "world2d/Module.h"
#include "imgui/imgui.h"

namespace world2d {
    class ImGuiModule : public world2d::Module {
    private:
        bool mImGuiInitialized = false;

    public:
        ImGuiModule();
        ImGuiModule(const ImGuiModule&) = delete;
        ~ImGuiModule();

        bool Initialize() override;
        void OnEvent(SDL_Event& event) override;
        void Update(double deltaTime) override;
        void Render() override;

        void InitializeImGui();

        static ImGuiModule* Get();
    };
}

#endif