#ifndef WORLD2D_LUA_IMGUI_WIDGETS_CURSOR_LAYOUT_WIDGET_H
#define WORLD2D_LUA_IMGUI_WIDGETS_CURSOR_LAYOUT_WIDGET_H

#include "world2d/lua/imgui/Widget.h"

namespace world2d {
    namespace ImGui {
        class CursorLayoutWidget : public Widget {
        private:
            CursorLayoutWidget();

        public:
            CursorLayoutWidget(const CursorLayoutWidget& widget) = delete;
            void SetLuaEnvironment(sol::table& luaImGuiNamespace) override;
            static CursorLayoutWidget* Get();
        };
    }
}

#endif