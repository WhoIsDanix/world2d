#ifndef WORLD2D_LUA_IMGUI_WIDGETS_COLOR_UTILITIES_WIDGET_H
#define WORLD2D_LUA_IMGUI_WIDGETS_COLOR_UTILITIES_WIDGET_H

#include "world2d/lua/imgui/Widget.h"

namespace world2d {
    namespace ImGui {
        class ColorUtilitiesWidget : public Widget {
        private:
            ColorUtilitiesWidget();

        public:
            ColorUtilitiesWidget(const ColorUtilitiesWidget& widget) = delete;
            void SetLuaEnvironment(sol::table& luaImGuiNamespace) override;
            static ColorUtilitiesWidget* Get();
        };
    }
}

#endif