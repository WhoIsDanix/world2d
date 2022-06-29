#ifndef WORLD2D_LUA_IMGUI_WIDGETS_MENU_WIDGET_H
#define WORLD2D_LUA_IMGUI_WIDGETS_MENU_WIDGET_H

#include "world2d/lua/imgui/Widget.h"

namespace world2d {
    namespace ImGui {
        class MenuWidget : public Widget {
        private:
            MenuWidget();

        public:
            MenuWidget(const MenuWidget& widget) = delete;
            void SetLuaEnvironment(sol::table& luaImGuiNamespace) override;
            static MenuWidget* Get();
        };
    }
}

#endif