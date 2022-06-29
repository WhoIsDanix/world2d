#include "world2d/lua/imgui/widgets/MiscellaneousUtilitiesWidget.h"
#include "imgui/imgui.h"

world2d::ImGui::MiscellaneousUtilitiesWidget::MiscellaneousUtilitiesWidget() {

}

void world2d::ImGui::MiscellaneousUtilitiesWidget::SetLuaEnvironment(sol::table& luaImGuiNamespace) {
    luaImGuiNamespace.set_function("IsRectVisible", sol::overload(
        [&](const ImVec2& size) {
            return ::ImGui::IsRectVisible(size);
        },

        [&](const ImVec2& rectMin, const ImVec2& rectMax) {
            return ::ImGui::IsRectVisible(rectMin, rectMax);
        }
    ));

    luaImGuiNamespace.set_function("GetTime", &::ImGui::GetTime);
    luaImGuiNamespace.set_function("GetFrameCount", &::ImGui::GetFrameCount);

    // TODO: add draw lists
    // luaImGuiNamespace.set_function("GetBackgroundDrawList", &::ImGui::GetBackgroundDrawList);
    // luaImGuiNamespace.set_function("GetForegroundDrawList", &::ImGui::GetForegroundDrawList);
    // luaImGuiNamespace.set_function("GetDrawListSharedData", &::ImGui::GetDrawListSharedData);

    // TODO: add ImGuiStorage
    // luaImGuiNamespace.set_function("SetStateStorage", &::ImGui::SetStateStorage);
    // luaImGuiNamespace.set_function("GetStateStorage", &::ImGui::GetStateStorage);

    luaImGuiNamespace.set_function("BeginChildFrame", sol::overload(
        [&](ImGuiID id, const ImVec2& size) {
            return ::ImGui::BeginChildFrame(id, size);
        },

        [&](ImGuiID id, const ImVec2& size, ImGuiWindowFlags flags) {
            return ::ImGui::BeginChildFrame(id, size, flags);
        }
    ));

    luaImGuiNamespace.set_function("EndChildFrame", &::ImGui::EndChildFrame);
}

world2d::ImGui::MiscellaneousUtilitiesWidget* world2d::ImGui::MiscellaneousUtilitiesWidget::Get() {
    static world2d::ImGui::MiscellaneousUtilitiesWidget currentWidget;
    return &currentWidget;
}