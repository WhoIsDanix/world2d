#ifndef WORLD2D_LUA_IMGUI_WIDGETS_FOCUS_ACTIVATION_WIDGET_H
#define WORLD2D_LUA_IMGUI_WIDGETS_FOCUS_ACTIVATION_WIDGET_H

#include "world2d/lua/imgui/Widget.h"

namespace world2d {
    namespace ImGui {
        class FocusActivationWidget : public Widget {
        private:
            FocusActivationWidget();

        public:
            FocusActivationWidget(const FocusActivationWidget& widget) = delete;
            void SetLuaEnvironment(sol::table& luaImGuiNamespace) override;
            static FocusActivationWidget* Get();
        };
    }
}

#endif