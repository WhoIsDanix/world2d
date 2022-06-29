#ifndef WORLD2D_LUA_IMGUI_WIDGETS_WINDOW_SCROLLING_WIDGET_H
#define WORLD2D_LUA_IMGUI_WIDGETS_WINDOW_SCROLLING_WIDGET_H


#include "world2d/lua/imgui/Widget.h"

namespace world2d {
    namespace ImGui {
        class WindowScrollingWidget : public Widget {
        private:
            WindowScrollingWidget();

        public:
            WindowScrollingWidget(const WindowScrollingWidget& widget) = delete;
            void SetLuaEnvironment(sol::table& luaImGuiNamespace) override;
            static WindowScrollingWidget* Get();
        };
    }
}

#endif