#ifndef WORLD2D_LUA_IMGUI_WIDGETS_MISCELLANEOUS_UTILITIES_WIDGET_H
#define WORLD2D_LUA_IMGUI_WIDGETS_MISCELLANEOUS_UTILITIES_WIDGET_H

#include "world2d/lua/imgui/Widget.h"

namespace world2d {
    namespace ImGui {
        class MiscellaneousUtilitiesWidget : public Widget {
        private:
            MiscellaneousUtilitiesWidget();

        public:
            MiscellaneousUtilitiesWidget(const MiscellaneousUtilitiesWidget& widget) = delete;
            void SetLuaEnvironment(sol::table& luaImGuiNamespace) override;
            static MiscellaneousUtilitiesWidget* Get();
        };
    }
}

#endif