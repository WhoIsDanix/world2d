#ifndef WORLD2D_LUA_IMGUI_WIDGETS_DATA_PLOTTING_WIDGET_H
#define WORLD2D_LUA_IMGUI_WIDGETS_DATA_PLOTTING_WIDGET_H

#include "world2d/lua/imgui/Widget.h"

namespace world2d {
    namespace ImGui {
        class DataPlottingWidget : public Widget {
        private:
            DataPlottingWidget();

        public:
            DataPlottingWidget(const DataPlottingWidget& widget) = delete;
            void SetLuaEnvironment(sol::table& luaImGuiNamespace) override;
            static DataPlottingWidget* Get();
        };
    }
}

#endif