#include "world2d/lua/imgui/widgets/DataPlottingWidget.h"
#include "imgui/imgui.h"

world2d::ImGui::DataPlottingWidget::DataPlottingWidget() {

}

void world2d::ImGui::DataPlottingWidget::SetLuaEnvironment(sol::table& luaImGuiNamespace) {
    luaImGuiNamespace.set_function("PlotLines", [&](const char* label, sol::table values) {
        std::vector<float> newvalues;
        newvalues.reserve(values.size());

        for (auto pair : values) {
            if (pair.first.get_type() != sol::type::number) continue;

            if (pair.second.get_type() == sol::type::number) {
                newvalues.push_back(pair.second.as<float>());
            } else {
                // luaL_error(lua.lua_state(), "Invalid value for PlotLines");
            }
        }

        ::ImGui::PlotLines(label, newvalues.data(), newvalues.size());
    });

    // TODO: add PlotHistogram
}

world2d::ImGui::DataPlottingWidget* world2d::ImGui::DataPlottingWidget::Get() {
    static world2d::ImGui::DataPlottingWidget currentWidget;
    return &currentWidget;
}