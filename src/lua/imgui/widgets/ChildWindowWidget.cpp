#include "world2d/lua/imgui/widgets/ChildWindowWidget.h"
#include "imgui/imgui.h"

world2d::ImGui::ChildWindowWidget::ChildWindowWidget() {

}

void world2d::ImGui::ChildWindowWidget::SetLuaEnvironment(sol::table& luaImGuiNamespace) {
    luaImGuiNamespace.set_function("BeginChild", sol::overload(
        [&](const char* strId) {
            return ::ImGui::BeginChild(strId);
        },

        [&](const char* strId, const ImVec2& size) {
            return ::ImGui::BeginChild(strId, size);
        },

        [&](const char* strId, const ImVec2& size, bool border) {
            return ::ImGui::BeginChild(strId, size, border);
        },

        [&](const char* strId, const ImVec2& size, bool border, ImGuiWindowFlags flags) {
            return ::ImGui::BeginChild(strId, size, border, flags);
        },

        [&](ImGuiID id) {
            return ::ImGui::BeginChild(id);
        },

        [&](ImGuiID id, const ImVec2& size) {
            return ::ImGui::BeginChild(id, size);
        },

        [&](ImGuiID id, const ImVec2& size, bool border) {
            return ::ImGui::BeginChild(id, size, border);
        },

        [&](ImGuiID id, const ImVec2& size, bool border, ImGuiWindowFlags flags) {
            return ::ImGui::BeginChild(id, size, border, flags);
        }
    ));

    luaImGuiNamespace.set_function("EndChild", &::ImGui::EndChild);
}

world2d::ImGui::ChildWindowWidget* world2d::ImGui::ChildWindowWidget::Get() {
    static world2d::ImGui::ChildWindowWidget currentWidget;
    return &currentWidget;
}