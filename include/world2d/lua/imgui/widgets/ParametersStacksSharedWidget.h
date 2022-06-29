#ifndef WORLD2D_LUA_IMGUI_WIDGETS_PARAMETERS_STACKS_SHARED_WIDGET_H
#define WORLD2D_LUA_IMGUI_WIDGETS_PARAMETERS_STACKS_SHARED_WIDGET_H

#include "world2d/lua/imgui/Widget.h"

namespace world2d {
    namespace ImGui {
        class ParametersStacksSharedWidget : public Widget {
        private:
            ParametersStacksSharedWidget();

        public:
            ParametersStacksSharedWidget(const ParametersStacksSharedWidget& widget) = delete;
            void SetLuaEnvironment(sol::table& luaImGuiNamespace) override;
            static ParametersStacksSharedWidget* Get();
        };
    }
}

#endif