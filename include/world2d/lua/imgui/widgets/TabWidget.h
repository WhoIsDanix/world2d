#ifndef WORLD2D_LUA_IMGUI_WIDGETS_TAB_WIDGET_H
#define WORLD2D_LUA_IMGUI_WIDGETS_TAB_WIDGET_H

#include "world2d/lua/imgui/Widget.h"

namespace world2d {
    namespace ImGui {
        class TabWidget : public Widget {
        private:
            TabWidget();

        public:
            TabWidget(const TabWidget& widget) = delete;
            void SetLuaEnvironment(sol::table& luaImGuiNamespace) override;
            static TabWidget* Get();
        };
    }
}

#endif