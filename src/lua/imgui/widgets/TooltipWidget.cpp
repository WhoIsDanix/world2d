#include "world2d/lua/imgui/widgets/TooltipWidget.h"
#include "imgui/imgui.h"

world2d::ImGui::TooltipWidget::TooltipWidget() {

}

void world2d::ImGui::TooltipWidget::SetLuaEnvironment(sol::table& luaImGuiNamespace) {
    luaImGuiNamespace.set_function("BeginTooltip", &::ImGui::BeginTooltip);
    luaImGuiNamespace.set_function("EndTooltip", &::ImGui::EndTooltip);

    luaImGuiNamespace.set_function("SetTooltip", [&](const char* text) {
        return ::ImGui::SetTooltip(text);
    });
}

world2d::ImGui::TooltipWidget* world2d::ImGui::TooltipWidget::Get() {
    static world2d::ImGui::TooltipWidget currentWidget;
    return &currentWidget;
}