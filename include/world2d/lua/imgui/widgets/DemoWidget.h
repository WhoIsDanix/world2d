#ifndef WORLD2D_LUA_IMGUI_WIDGETS_DEMO_WIDGET_H
#define WORLD2D_LUA_IMGUI_WIDGETS_DEMO_WIDGET_H

#include "world2d/lua/imgui/Widget.h"

namespace world2d {
    namespace ImGui {
        class DemoWidget : public Widget {
        private:
            DemoWidget();

        public:
            DemoWidget(const DemoWidget& widget) = delete;
            void SetLuaEnvironment(sol::table& luaImGuiNamespace) override;
            static DemoWidget* Get();
        };
    }
}

#endif