#ifndef WORLD2D_LUA_IMGUI_WIDGETS_NEXT_WINDOW_UTILITIES_WIDGET_H
#define WORLD2D_LUA_IMGUI_WIDGETS_NEXT_WINDOW_UTILITIES_WIDGET_H

#include "world2d/lua/imgui/Widget.h"

namespace world2d {
    namespace ImGui {
        class NextWindowUtilitiesWidget : public Widget {
        private:
            NextWindowUtilitiesWidget();

        public:
            NextWindowUtilitiesWidget(const NextWindowUtilitiesWidget& widget) = delete;
            void SetLuaEnvironment(sol::table& luaImGuiNamespace) override;
            static NextWindowUtilitiesWidget* Get();
        };
    }
}

#endif