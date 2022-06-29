#include "world2d/lua/imgui/widgets/ParametersStacksSharedWidget.h"
#include "imgui/imgui.h"

world2d::ImGui::ParametersStacksSharedWidget::ParametersStacksSharedWidget() {

}

void world2d::ImGui::ParametersStacksSharedWidget::SetLuaEnvironment(sol::table& luaImGuiNamespace) {
    luaImGuiNamespace.set_function("PushFont", &::ImGui::PushFont);
    luaImGuiNamespace.set_function("PopFont", &::ImGui::PopFont);

    luaImGuiNamespace.set_function("PushStyleColor", sol::overload(
        [&](ImGuiCol idx, ImU32 col) {
            ::ImGui::PushStyleColor(idx, col);
        },

        [&](ImGuiCol idx, const ImVec4& col) {
            ::ImGui::PushStyleColor(idx, col);
        }
    ));

    luaImGuiNamespace.set_function("PopStyleColor", sol::overload(
        [&]() {
            ::ImGui::PopStyleColor();
        },

        [&](int count) {
            ::ImGui::PopStyleColor(count);
        }
    ));

    luaImGuiNamespace.set_function("PushStyleVar", sol::overload(
        [&](ImGuiStyleVar idx, float val) {
            ::ImGui::PushStyleVar(idx, val);
        },

        [&](ImGuiStyleVar idx, const ImVec2& val) {
            ::ImGui::PushStyleVar(idx, val);
        }
    ));

    luaImGuiNamespace.set_function("PopStyleVar", sol::overload(
        [&]() {
            ::ImGui::PopStyleVar();
        },

        [&](int count) {
            ::ImGui::PopStyleVar(count);
        }
    ));

    luaImGuiNamespace.set_function("GetFont", &::ImGui::GetFont);

    luaImGuiNamespace.set_function("GetFontSize", &::ImGui::GetFontSize);
    luaImGuiNamespace.set_function("GetFontTexUvWhitePixel", &::ImGui::GetFontTexUvWhitePixel);
    
    luaImGuiNamespace.set_function("GetColorU32", sol::overload(
        [&](ImGuiCol idx) {
            return ::ImGui::GetColorU32(idx);
        },

        [&](ImGuiCol idx, float alphaMul) {
            return ::ImGui::GetColorU32(idx, alphaMul);
        },

        [&](const ImVec4& col) {
            return ::ImGui::GetColorU32(col);
        },

        [&](ImU32 col) {
            return ::ImGui::GetColorU32(col);
        }
    ));
}

world2d::ImGui::ParametersStacksSharedWidget* world2d::ImGui::ParametersStacksSharedWidget::Get() {
    static world2d::ImGui::ParametersStacksSharedWidget currentWidget;
    return &currentWidget;
}