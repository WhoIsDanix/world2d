#include "world2d/lua/imgui/widgets/ColorUtilitiesWidget.h"
#include "imgui/imgui.h"

#include <tuple>

world2d::ImGui::ColorUtilitiesWidget::ColorUtilitiesWidget() {

}

void world2d::ImGui::ColorUtilitiesWidget::SetLuaEnvironment(sol::table& luaImGuiNamespace) {
    luaImGuiNamespace.set_function("ColorConvertU32ToFloat4", &::ImGui::ColorConvertU32ToFloat4);
    luaImGuiNamespace.set_function("ColorConvertFloat4ToU32", &::ImGui::ColorConvertFloat4ToU32);

    luaImGuiNamespace.set_function("ColorConvertRGBtoHSV", [&](float r, float g, float b) {
        float outH, outS, outV;
        ::ImGui::ColorConvertRGBtoHSV(r, g, b, outH, outS, outV);
        return std::make_tuple(outH, outS, outV);
    });

    luaImGuiNamespace.set_function("ColorConvertHSVtoRGB", [&](float h, float s, float v) {
        float outR, outG, outB;
        ::ImGui::ColorConvertHSVtoRGB(h, s, v, outR, outG, outB);
        return std::make_tuple(outR, outG, outB);
    });
}

world2d::ImGui::ColorUtilitiesWidget* world2d::ImGui::ColorUtilitiesWidget::Get() {
    static world2d::ImGui::ColorUtilitiesWidget currentWidget;
    return &currentWidget;
}