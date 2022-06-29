#ifndef WORLD2D_LUA_IMGUI_WIDGETS_TOOLTIP_WIDGET_H
#define WORLD2D_LUA_IMGUI_WIDGETS_TOOLTIP_WIDGET_H

#include "world2d/lua/imgui/Widget.h"

namespace world2d {
    namespace ImGui {
        class TooltipWidget : public Widget {
        private:
            TooltipWidget();

        public:
            TooltipWidget(const TooltipWidget& widget) = delete;
            void SetLuaEnvironment(sol::table& luaImGuiNamespace) override;
            static TooltipWidget* Get();
        };
    }
}

#endif