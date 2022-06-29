#ifndef WORLD2D_LUA_IMGUI_WIDGETS_WINDOW_WIDGET_H
#define WORLD2D_LUA_IMGUI_WIDGETS_WINDOW_WIDGET_H

#include "world2d/lua/imgui/Widget.h"

namespace world2d {
    namespace ImGui {
        class WindowWidget : public Widget {
        private:
            WindowWidget();

        public:
            WindowWidget(const WindowWidget& widget) = delete;
            void SetLuaEnvironment(sol::table& luaImGuiNamespace) override;
            static WindowWidget* Get();
        };
    }
}

#endif