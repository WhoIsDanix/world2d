#include "world2d/lua/imgui/widgets/WindowWidget.h"

#include "imgui/imgui.h"
#include "world2d/lua/imgui/structures/Bool.h"

world2d::ImGui::WindowWidget::WindowWidget() {

}

void world2d::ImGui::WindowWidget::SetLuaEnvironment(sol::table& luaImGuiNamespace) {
    luaImGuiNamespace.set_function("Begin", sol::overload(
        [&](const char* name) {
            return ::ImGui::Begin(name);
        },

        [&](const char* name, world2d::ImGui::Bool* pOpen) {
            return ::ImGui::Begin(name, &(pOpen->value));
        },

        [&](const char* name, world2d::ImGui::Bool* pOpen, ImGuiWindowFlags flags) {
            return ::ImGui::Begin(name, &(pOpen->value), flags);
        }
    ));

    luaImGuiNamespace.set_function("End", &::ImGui::End);
}

world2d::ImGui::WindowWidget* world2d::ImGui::WindowWidget::Get() {
    static world2d::ImGui::WindowWidget currentWidget;
    return &currentWidget;
}