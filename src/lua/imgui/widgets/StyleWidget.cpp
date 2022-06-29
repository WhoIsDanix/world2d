#include "world2d/lua/imgui/widgets/StyleWidget.h"
#include "imgui/imgui.h"

world2d::ImGui::StyleWidget::StyleWidget() {

}

void world2d::ImGui::StyleWidget::SetLuaEnvironment(sol::table& luaImGuiNamespace) {
    luaImGuiNamespace.set_function("StyleColorsDark", &::ImGui::StyleColorsDark);
    luaImGuiNamespace.set_function("StyleColorsClassic", &::ImGui::StyleColorsClassic);
    luaImGuiNamespace.set_function("StyleColorsLight", &::ImGui::StyleColorsLight);
}

world2d::ImGui::StyleWidget* world2d::ImGui::StyleWidget::Get() {
    static world2d::ImGui::StyleWidget currentWidget;
    return &currentWidget;
}