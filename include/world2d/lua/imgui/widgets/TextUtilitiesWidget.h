#ifndef WORLD2D_LUA_IMGUI_WIDGETS_TEXT_UTILITIES_WIDGET_H
#define WORLD2D_LUA_IMGUI_WIDGETS_TEXT_UTILITIES_WIDGET_H

#include "world2d/lua/imgui/Widget.h"

namespace world2d {
    namespace ImGui {
        class TextUtilitiesWidget : public Widget {
        private:
            TextUtilitiesWidget();

        public:
            TextUtilitiesWidget(const TextUtilitiesWidget& widget) = delete;
            void SetLuaEnvironment(sol::table& luaImGuiNamespace) override;
            static TextUtilitiesWidget* Get();
        };
    }
}

#endif