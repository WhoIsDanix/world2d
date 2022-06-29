#ifndef WORLD2D_LUA_IMGUI_WIDGETS_PARAMETERS_STACKS_CURRENT_WINDOW_WIDGET_H
#define WORLD2D_LUA_IMGUI_WIDGETS_PARAMETERS_STACKS_CURRENT_WINDOW_WIDGET_H

#include "world2d/lua/imgui/Widget.h"

namespace world2d {
    namespace ImGui {
        class ParametersStacksCurrentWindowWidget : public Widget {
        private:
            ParametersStacksCurrentWindowWidget();

        public:
            ParametersStacksCurrentWindowWidget(const ParametersStacksCurrentWindowWidget& widget) = delete;
            void SetLuaEnvironment(sol::table& luaImGuiNamespace) override;
            static ParametersStacksCurrentWindowWidget* Get();
        };
    }
}

#endif