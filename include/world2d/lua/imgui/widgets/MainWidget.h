#ifndef WORLD2D_LUA_IMGUI_WIDGETS_MAIN_WIDGET_H
#define WORLD2D_LUA_IMGUI_WIDGETS_MAIN_WIDGET_H

#include "world2d/lua/imgui/Widget.h"

namespace world2d {
    namespace ImGui {
        class MainWidget : public Widget {
        private:
            MainWidget();

        public:
            MainWidget(const MainWidget& widget) = delete;
            void SetLuaEnvironment(sol::table& luaImGuiNamespace) override;
            static MainWidget* Get();
        };
    }
}

#endif