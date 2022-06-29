#ifndef WORLD2D_LUA_IMGUI_WIDGETS_STYLE_WIDGET_H
#define WORLD2D_LUA_IMGUI_WIDGETS_STYLE_WIDGET_H

#include "world2d/lua/imgui/Widget.h"

namespace world2d {
    namespace ImGui {
        class StyleWidget : public Widget {
        private:
            StyleWidget();

        public:
            StyleWidget(const StyleWidget& widget) = delete;
            void SetLuaEnvironment(sol::table& luaImGuiNamespace) override;
            static StyleWidget* Get();
        };
    }
}

#endif