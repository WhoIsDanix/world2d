#ifndef WORLD2D_LUA_IMGUI_WIDGETS_CHILD_WINDOW_WIDGET_H
#define WORLD2D_LUA_IMGUI_WIDGETS_CHILD_WINDOW_WIDGET_H

#include "world2d/lua/imgui/Widget.h"

namespace world2d {
    namespace ImGui {
        class ChildWindowWidget : public Widget {
        private:
            ChildWindowWidget();

        public:
            ChildWindowWidget(const ChildWindowWidget& widget) = delete;
            void SetLuaEnvironment(sol::table& luaImGuiNamespace) override;
            static ChildWindowWidget* Get();
        };
    }
}

#endif