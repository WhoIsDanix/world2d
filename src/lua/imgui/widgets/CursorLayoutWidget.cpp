#include "world2d/lua/imgui/widgets/CursorLayoutWidget.h"
#include "imgui/imgui.h"

world2d::ImGui::CursorLayoutWidget::CursorLayoutWidget() {

}

void world2d::ImGui::CursorLayoutWidget::SetLuaEnvironment(sol::table& luaImGuiNamespace) {
    luaImGuiNamespace.set_function("Separator", &::ImGui::Separator);
    luaImGuiNamespace.set_function("NewLine", &::ImGui::SameLine);
    luaImGuiNamespace.set_function("Spacing", &::ImGui::Spacing);
    luaImGuiNamespace.set_function("Dummy", &::ImGui::Dummy);

    luaImGuiNamespace.set_function("Indent", sol::overload(
        [&]() {
            ::ImGui::Indent();
        },

        [&](float indentW) {
            ::ImGui::Indent(indentW);
        }
    ));

    luaImGuiNamespace.set_function("Unindent", sol::overload(
        [&]() {
            ::ImGui::Unindent();
        },

        [&](float indentW) {
            ::ImGui::Unindent(indentW);
        }
    ));

    luaImGuiNamespace.set_function("BeginGroup", &::ImGui::BeginGroup);
    luaImGuiNamespace.set_function("EndGroup", &::ImGui::EndGroup);
    luaImGuiNamespace.set_function("GetCursorPos", &::ImGui::GetCursorPos);
    luaImGuiNamespace.set_function("GetCursorPosX", &::ImGui::GetCursorPosX);
    luaImGuiNamespace.set_function("GetCursorPosY", &::ImGui::GetCursorPosY);
    luaImGuiNamespace.set_function("SetCursorPos", &::ImGui::SetCursorPos);
    luaImGuiNamespace.set_function("SetCursorPosX", &::ImGui::SetCursorPosX);
    luaImGuiNamespace.set_function("SetCursorPosY", &::ImGui::SetCursorPosY);
    luaImGuiNamespace.set_function("GetCursorStartPos", &::ImGui::GetCursorStartPos);
    luaImGuiNamespace.set_function("GetCursorScreenPos", &::ImGui::GetCursorScreenPos);
    luaImGuiNamespace.set_function("SetCursorScreenPos", &::ImGui::SetCursorScreenPos);
    luaImGuiNamespace.set_function("AlignTextToFramePadding", &::ImGui::AlignTextToFramePadding);
    luaImGuiNamespace.set_function("GetTextLineHeight", &::ImGui::GetTextLineHeight);
    luaImGuiNamespace.set_function("GetTextLineHeightWithSpacing", &::ImGui::GetTextLineHeightWithSpacing);
    luaImGuiNamespace.set_function("GetFrameHeight", &::ImGui::GetFrameHeight);
    luaImGuiNamespace.set_function("GetFrameHeightWithSpacing", &::ImGui::GetFrameHeightWithSpacing);
}

world2d::ImGui::CursorLayoutWidget* world2d::ImGui::CursorLayoutWidget::Get() {
    static world2d::ImGui::CursorLayoutWidget currentWidget;
    return &currentWidget;
}