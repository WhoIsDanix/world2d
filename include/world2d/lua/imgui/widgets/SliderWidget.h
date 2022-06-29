#ifndef WORLD2D_LUA_IMGUI_WIDGETS_SLIDER_WIDGET_H
#define WORLD2D_LUA_IMGUI_WIDGETS_SLIDER_WIDGET_H

#include "world2d/lua/imgui/Widget.h"

namespace world2d {
    namespace ImGui {
        class SliderWidget : public Widget {
        private:
            SliderWidget();

        public:
            SliderWidget(const SliderWidget& widget) = delete;
            void SetLuaEnvironment(sol::table& luaImGuiNamespace) override;
            static SliderWidget* Get();
        };
    }
}

#endif