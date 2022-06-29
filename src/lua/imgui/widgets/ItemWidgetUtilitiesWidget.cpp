#include "world2d/lua/imgui/widgets/ItemWidgetUtilitiesWidget.h"
#include "imgui/imgui.h"

world2d::ImGui::ItemWidgetUtilitiesWidget::ItemWidgetUtilitiesWidget() {

}

void world2d::ImGui::ItemWidgetUtilitiesWidget::SetLuaEnvironment(sol::table& luaImGuiNamespace) {
    luaImGuiNamespace.set_function("IsItemHovered", sol::overload(
        [&]() {
            return ::ImGui::IsItemHovered();
        },

        [&](ImGuiHoveredFlags flags) {
            return ::ImGui::IsItemHovered(flags);
        }
    ));

    luaImGuiNamespace.set_function("IsItemActive", &::ImGui::IsItemActive);
    luaImGuiNamespace.set_function("IsItemFocused", &::ImGui::IsItemFocused);

    luaImGuiNamespace.set_function("IsItemClicked", sol::overload(
        [&]() {
            return ::ImGui::IsItemClicked();
        },

        [&](ImGuiMouseButton mouseButton) {
            return ::ImGui::IsItemClicked(mouseButton);
        }
    ));

    luaImGuiNamespace.set_function("IsItemVisible", &::ImGui::IsItemVisible);
    luaImGuiNamespace.set_function("IsItemEdited", &::ImGui::IsItemEdited);
    luaImGuiNamespace.set_function("IsItemActivated", &::ImGui::IsItemActivated);
    luaImGuiNamespace.set_function("IsItemDeactivated", &::ImGui::IsItemDeactivated);
    luaImGuiNamespace.set_function("IsItemDeactivatedAfterEdit", &::ImGui::IsItemDeactivatedAfterEdit);
    luaImGuiNamespace.set_function("IsItemToggledOpen", &::ImGui::IsItemToggledOpen);
    luaImGuiNamespace.set_function("IsAnyItemHovered", &::ImGui::IsAnyItemHovered);
    luaImGuiNamespace.set_function("IsAnyItemActive", &::ImGui::IsAnyItemActive);
    luaImGuiNamespace.set_function("IsAnyItemFocused", &::ImGui::IsAnyItemFocused);
    luaImGuiNamespace.set_function("GetItemRectMin", &::ImGui::GetItemRectMin);
    luaImGuiNamespace.set_function("GetItemRectMax", &::ImGui::GetItemRectMax);
    luaImGuiNamespace.set_function("GetItemRectSize", &::ImGui::GetItemRectSize);
    luaImGuiNamespace.set_function("SetItemAllowOverlap", &::ImGui::SetItemAllowOverlap);
}

world2d::ImGui::ItemWidgetUtilitiesWidget* world2d::ImGui::ItemWidgetUtilitiesWidget::Get() {
    static world2d::ImGui::ItemWidgetUtilitiesWidget currentWidget;
    return &currentWidget;
}