#ifndef WORLD2D_LUA_IMGUI_WIDGETS_COMBO_BOX_WIDGET_H
#define WORLD2D_LUA_IMGUI_WIDGETS_COMBO_BOX_WIDGET_H

#include "world2d/lua/imgui/Widget.h"

namespace world2d {
    namespace ImGui {
        class ComboBoxWidget : public Widget {
        private:
            ComboBoxWidget();

        public:
            ComboBoxWidget(const ComboBoxWidget& widget) = delete;
            void SetLuaEnvironment(sol::table& luaImGuiNamespace) override;
            static ComboBoxWidget* Get();
        };
    }
}

#endif