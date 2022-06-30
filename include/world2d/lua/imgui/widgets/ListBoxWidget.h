#ifndef WORLD2D_LUA_IMGUI_WIDGETS_LIST_BOX_WIDGET_H
#define WORLD2D_LUA_IMGUI_WIDGETS_LIST_BOX_WIDGET_H

#include "world2d/lua/imgui/Widget.h"

namespace world2d {
    namespace ImGui {
        class ListBoxWidget : public Widget {
        private:
            ListBoxWidget();
        
        public:
            ListBoxWidget(const ListBoxWidget& widget) = delete;
            void SetLuaEnvironment(sol::table& luaImGuiNamespace) override;
            static ListBoxWidget* Get();
        };
    }
}

#endif