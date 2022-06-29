#include "world2d/lua/imgui/widgets/TabWidget.h"
#include "imgui/imgui.h"

#include "world2d/lua/imgui/structures/Bool.h"

world2d::ImGui::TabWidget::TabWidget() {

}

void world2d::ImGui::TabWidget::SetLuaEnvironment(sol::table& luaImGuiNamespace) {
    luaImGuiNamespace.set_function("BeginTabBar", sol::overload(
        [&](const char* strId) {
            return ::ImGui::BeginTabBar(strId);
        },

        [&](const char* strId, ImGuiTabBarFlags flags) {
            return ::ImGui::BeginTabBar(strId, flags);
        }
    ));

    luaImGuiNamespace.set_function("EndTabBar", &::ImGui::EndTabBar);

    luaImGuiNamespace.set_function("BeginTabItem", sol::overload(
        [&](const char* label) {
            return ::ImGui::BeginTabItem(label);
        },

        [&](const char* label, world2d::ImGui::Bool* pOpen) {
            return ::ImGui::BeginTabItem(label, &(pOpen->value));
        },

        [&](const char* label, world2d::ImGui::Bool* pOpen, ImGuiTabItemFlags flags) {
            return ::ImGui::BeginTabItem(label, &(pOpen->value), flags);
        }
    ));

    luaImGuiNamespace.set_function("EndTabItem", &::ImGui::EndTabItem);
    luaImGuiNamespace.set_function("SetTabItemClosed", &::ImGui::SetTabItemClosed);
}

world2d::ImGui::TabWidget* world2d::ImGui::TabWidget::Get() {
    static world2d::ImGui::TabWidget currentWidget;
    return &currentWidget;
}