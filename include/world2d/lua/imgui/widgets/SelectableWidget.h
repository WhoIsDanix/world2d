#ifndef WORLD2D_LUA_IMGUI_WIDGETS_SELECTABLE_WIDGET_H
#define WORLD2D_LUA_IMGUI_WIDGETS_SELECTABLE_WIDGET_H

#include "world2d/lua/imgui/Widget.h"

namespace world2d {
    namespace ImGui {
        class SelectableWidget : public Widget {
        private:
            SelectableWidget();

        public:
            SelectableWidget(const SelectableWidget& widget) = delete;
            void SetLuaEnvironment(sol::table& luaImGuiNamespace) override;
            static SelectableWidget* Get();
        };
    }
}

#endif