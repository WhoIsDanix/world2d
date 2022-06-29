#include "world2d/lua/imgui/widgets/NextWindowUtilitiesWidget.h"
#include "imgui/imgui.h"

world2d::ImGui::NextWindowUtilitiesWidget::NextWindowUtilitiesWidget() {

}

void world2d::ImGui::NextWindowUtilitiesWidget::SetLuaEnvironment(sol::table& luaImGuiNamespace) {
    luaImGuiNamespace.set_function("SetNextWindowPos", sol::overload(
        [&](const ImVec2& pos) {
            ::ImGui::SetNextWindowPos(pos);
        },

        [&](const ImVec2& pos, ImGuiCond cond) {
            ::ImGui::SetNextWindowPos(pos, cond);
        },

        [&](const ImVec2& pos, ImGuiCond cond, const ImVec2& pivot) {
            ::ImGui::SetNextWindowPos(pos, cond, pivot);
        }
    ));

    luaImGuiNamespace.set_function("SetNextWindowSize", sol::overload(
        [&](const ImVec2& size) {
            ::ImGui::SetNextWindowSize(size);
        },

        [&](const ImVec2& size, ImGuiCond cond) {
            ::ImGui::SetNextWindowSize(size, cond);
        }
    ));
}

world2d::ImGui::NextWindowUtilitiesWidget* world2d::ImGui::NextWindowUtilitiesWidget::Get() {
    static world2d::ImGui::NextWindowUtilitiesWidget currentWidget;
    return &currentWidget;
}