#include "world2d/lua/imgui/widgets/FocusActivationWidget.h"
#include "imgui/imgui.h"

world2d::ImGui::FocusActivationWidget::FocusActivationWidget() {

}

void world2d::ImGui::FocusActivationWidget::SetLuaEnvironment(sol::table& luaImGuiNamespace) {
    luaImGuiNamespace.set_function("SetItemDefaultFocus", &::ImGui::SetItemDefaultFocus);

    luaImGuiNamespace.set_function("SetKeyboardFocusHere", sol::overload(
        [&]() {
            ::ImGui::SetKeyboardFocusHere();
        },

        [&](int offset) {
            ::ImGui::SetKeyboardFocusHere(offset);
        }
    ));
}

world2d::ImGui::FocusActivationWidget* world2d::ImGui::FocusActivationWidget::Get() {
    static world2d::ImGui::FocusActivationWidget currentWidget;
    return &currentWidget;
}