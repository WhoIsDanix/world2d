#ifndef WORLD2D_LUA_IMGUI_WIDGETS_WINDOW_UTILITIES_WIDGET_H
#define WORLD2D_LUA_IMGUI_WIDGETS_WINDOW_UTILITIES_WIDGET_H

#include "world2d/lua/imgui/Widget.h"

namespace world2d {
    namespace ImGui {
        class WindowUtilitiesWidget : public Widget {
        private:
            WindowUtilitiesWidget();

        public:
            WindowUtilitiesWidget(const WindowUtilitiesWidget& widget) = delete;
            void SetLuaEnvironment(sol::table& luaImGuiNamespace) override;
            static WindowUtilitiesWidget* Get();
        };
    }
}

#endif