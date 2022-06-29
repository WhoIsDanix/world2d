#include "world2d/lua/imgui/widgets/MenuWidget.h"
#include "imgui/imgui.h"

#include "world2d/lua/imgui/structures/Bool.h"

world2d::ImGui::MenuWidget::MenuWidget() {

}

void world2d::ImGui::MenuWidget::SetLuaEnvironment(sol::table& luaImGuiNamespace) {
    luaImGuiNamespace.set_function("BeginMenuBar", &::ImGui::BeginMenuBar);
    luaImGuiNamespace.set_function("EndMenuBar", &::ImGui::EndMenuBar);
    luaImGuiNamespace.set_function("BeginMainMenuBar", &::ImGui::BeginMainMenuBar);
    luaImGuiNamespace.set_function("EndMainMenuBar", &::ImGui::EndMainMenuBar);

    luaImGuiNamespace.set_function("BeginMenu", sol::overload(
        [&](const char* label) {
            return ::ImGui::BeginMenu(label);
        },

        [&](const char* label, bool enabled) {
            return ::ImGui::BeginMenu(label, enabled);
        }
    ));

    luaImGuiNamespace.set_function("EndMenu", &::ImGui::EndMenu);

    luaImGuiNamespace.set_function("MenuItem", sol::overload(
        [&](const char* label) {
            return ::ImGui::MenuItem(label);
        },

        [&](const char* label, const char* shortcut) {
            return ::ImGui::MenuItem(label, shortcut);
        },

        [&](const char* label, const char* shortcut, bool selected) {
            return ::ImGui::MenuItem(label, shortcut, selected);
        },

        [&](const char* label, const char* shortcut, bool selected, bool enabled) {
            return ::ImGui::MenuItem(label, shortcut, selected, enabled);
        },

        [&](const char* label, const char* shortcut, world2d::ImGui::Bool* pSelected) {
            return ::ImGui::MenuItem(label, shortcut, &(pSelected->value));
        },

        [&](const char* label, const char* shortcut, world2d::ImGui::Bool* pSelected, bool enabled) {
            return ::ImGui::MenuItem(label, shortcut, &(pSelected->value), enabled);
        }
    ));
}

world2d::ImGui::MenuWidget* world2d::ImGui::MenuWidget::Get() {
    static world2d::ImGui::MenuWidget currentWidget;
    return &currentWidget;
}