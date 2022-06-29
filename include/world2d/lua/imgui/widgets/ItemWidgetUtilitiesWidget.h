#ifndef WORLD2D_LUA_IMGUI_WIDGETS_ITEM_WIDGET_UTILITIES_WIDGET_H
#define WORLD2D_LUA_IMGUI_WIDGETS_ITEM_WIDGET_UTILITIES_WIDGET_H

#include "world2d/lua/imgui/Widget.h"

namespace world2d {
    namespace ImGui {
        class ItemWidgetUtilitiesWidget : public Widget {
        private:
            ItemWidgetUtilitiesWidget();

        public:
            ItemWidgetUtilitiesWidget(const ItemWidgetUtilitiesWidget& widget) = delete;
            void SetLuaEnvironment(sol::table& luaImGuiNamespace) override;
            static ItemWidgetUtilitiesWidget* Get();
        };
    }
}

#endif