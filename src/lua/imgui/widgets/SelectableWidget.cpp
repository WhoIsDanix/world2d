#include "world2d/lua/imgui/widgets/SelectableWidget.h"
#include "imgui/imgui.h"

#include "world2d/lua/imgui/structures/Bool.h"

world2d::ImGui::SelectableWidget::SelectableWidget() {

}

void world2d::ImGui::SelectableWidget::SetLuaEnvironment(sol::table& luaImGuiNamespace) {
    luaImGuiNamespace.set_function("Selectable", sol::overload(
        [&](const char* label) {
            return ::ImGui::Selectable(label);
        },

        [&](const char* label, bool selected) {
            return ::ImGui::Selectable(label, selected);
        },

        [&](const char* label, bool selected, ImGuiSelectableFlags flags) {
            return ::ImGui::Selectable(label, selected, flags);
        },

        [&](const char* label, bool selected, ImGuiSelectableFlags flags, const ImVec2& size) {
            return ::ImGui::Selectable(label, selected, flags, size);
        },

        [&](const char* label, world2d::ImGui::Bool* pSelected) {
            return ::ImGui::Selectable(label, &(pSelected->value));
        },

        [&](const char* label, world2d::ImGui::Bool* pSelected, ImGuiSelectableFlags flags) {
            return ::ImGui::Selectable(label, &(pSelected->value), flags);
        },

        [&](const char* label, world2d::ImGui::Bool* pSelected, ImGuiSelectableFlags flags, const ImVec2& size) {
            return ::ImGui::Selectable(label, &(pSelected->value), flags, size);
        }
    ));
}

world2d::ImGui::SelectableWidget* world2d::ImGui::SelectableWidget::Get() {
    static world2d::ImGui::SelectableWidget currentWidget;
    return &currentWidget;
}