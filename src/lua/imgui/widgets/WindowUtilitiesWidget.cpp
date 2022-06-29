#include "world2d/lua/imgui/widgets/WindowUtilitiesWidget.h"

#include "imgui/imgui.h"
#include "world2d/lua/imgui/structures/Bool.h"

world2d::ImGui::WindowUtilitiesWidget::WindowUtilitiesWidget() {

}

void world2d::ImGui::WindowUtilitiesWidget::SetLuaEnvironment(sol::table& luaImGuiNamespace) {
    luaImGuiNamespace.set_function("IsWindowAppearing", &::ImGui::IsWindowAppearing);
    luaImGuiNamespace.set_function("IsWindowCollapsed", &::ImGui::IsWindowCollapsed);

    luaImGuiNamespace.set_function("IsWindowFocused", sol::overload(
        [&]() {
            return ::ImGui::IsWindowFocused();
        },

        [&](ImGuiFocusedFlags flags) {
            return ::ImGui::IsWindowFocused(flags);
        }
    ));

    luaImGuiNamespace.set_function("IsWindowHovered", sol::overload(
        [&]() {
            return ::ImGui::IsWindowHovered();
        },

        [&](ImGuiHoveredFlags flags) {
            return ::ImGui::IsWindowHovered(flags);
        }
    ));

    luaImGuiNamespace.set_function("GetWindowDrawList", &::ImGui::GetWindowDrawList);

    luaImGuiNamespace.set_function("GetWindowPos", &::ImGui::GetWindowPos);
    luaImGuiNamespace.set_function("GetWindowSize", &::ImGui::GetWindowSize);
    luaImGuiNamespace.set_function("GetWindowWidth", &::ImGui::GetWindowWidth);
    luaImGuiNamespace.set_function("GetWindowHeight", &::ImGui::GetWindowHeight);
}

world2d::ImGui::WindowUtilitiesWidget* world2d::ImGui::WindowUtilitiesWidget::Get() {
    static world2d::ImGui::WindowUtilitiesWidget currentWidget;
    return &currentWidget;
}