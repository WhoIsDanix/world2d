#ifndef WORLD2D_LUA_IMGUI_WIDGETS_COLOR_EDITOR_PICKER_WIDGET_H
#define WORLD2D_LUA_IMGUI_WIDGETS_COLOR_EDITOR_PICKER_WIDGET_H

#include "world2d/lua/imgui/Widget.h"

namespace world2d {
    namespace ImGui {
        class ColorEditorPickerWidget : public Widget {
        private:
            ColorEditorPickerWidget();

        public:
            ColorEditorPickerWidget(const ColorEditorPickerWidget& widget) = delete;
            void SetLuaEnvironment(sol::table& luaImGuiNamespace) override;
            static ColorEditorPickerWidget* Get();
        };
    }
}

#endif