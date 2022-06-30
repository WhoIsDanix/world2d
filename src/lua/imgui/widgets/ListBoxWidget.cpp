#include "world2d/lua/imgui/widgets/ListBoxWidget.h"
#include "imgui/imgui.h"

world2d::ImGui::ListBoxWidget::ListBoxWidget() {

}

void world2d::ImGui::ListBoxWidget::SetLuaEnvironment(sol::table& luaImGuiNamespace) {
    luaImGuiNamespace.set_function("BeginListBox", sol::overload(
        [&](const char* label) {
            return ::ImGui::BeginListBox(label);
        },

        [&](const char* label, const ImVec2& size) {
            return ::ImGui::BeginListBox(label, size);
        }
    ));

    luaImGuiNamespace.set_function("EndListBox", &::ImGui::EndListBox);
}

world2d::ImGui::ListBoxWidget* world2d::ImGui::ListBoxWidget::Get() {
    static world2d::ImGui::ListBoxWidget currentWidget;
    return &currentWidget;
}