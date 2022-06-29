#ifndef WORLD2D_LUA_IMGUI_WIDGETS_TEXT_WIDGET_H
#define WORLD2D_LUA_IMGUI_WIDGETS_TEXT_WIDGET_H

#include "world2d/lua/imgui/Widget.h"

namespace world2d {
    namespace ImGui {
        class TextWidget : public Widget {
        private:
            TextWidget();

        public:
            TextWidget(const TextWidget& widget) = delete;
            void SetLuaEnvironment(sol::table& luaImGuiNamespace) override;
            static TextWidget* Get();
        };
    }
}

#endif