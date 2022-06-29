#ifndef WORLD2D_LUA_IMGUI_WIDGETS_CLIPPING_WIDGET_H
#define WORLD2D_LUA_IMGUI_WIDGETS_CLIPPING_WIDGET_H

#include "world2d/lua/imgui/Widget.h"

namespace world2d {
    namespace ImGui {
        class ClippingWidget : public Widget {
        private:
            ClippingWidget();

        public:
            ClippingWidget(const ClippingWidget& widget) = delete;
            void SetLuaEnvironment(sol::table& luaImGuiNamespace) override;
            static ClippingWidget* Get();
        };
    }
}

#endif