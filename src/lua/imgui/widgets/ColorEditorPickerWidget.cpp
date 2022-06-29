#include "world2d/lua/imgui/widgets/ColorEditorPickerWidget.h"
#include "imgui/imgui.h"

#include "world2d/lua/imgui/structures/Float.h"
#include "world2d/lua/imgui/structures/FloatArray3.h"
#include "world2d/lua/imgui/structures/FloatArray4.h"

world2d::ImGui::ColorEditorPickerWidget::ColorEditorPickerWidget() {

}

void world2d::ImGui::ColorEditorPickerWidget::SetLuaEnvironment(sol::table& luaImGuiNamespace) {
    luaImGuiNamespace.set_function("ColorEdit3", sol::overload(
        [&](const char* label, world2d::ImGui::FloatArray3* col) {
            return ::ImGui::ColorEdit3(label, col->data());
        },

        [&](const char* label, world2d::ImGui::FloatArray3* col, ImGuiColorEditFlags flags) {
            return ::ImGui::ColorEdit3(label, col->data(), flags);
        }
    ));

    luaImGuiNamespace.set_function("ColorEdit4", sol::overload(
        [&](const char* label, world2d::ImGui::FloatArray4* col) {
            return ::ImGui::ColorEdit4(label, col->data());
        },

        [&](const char* label, world2d::ImGui::FloatArray4* col, ImGuiColorEditFlags flags) {
            return ::ImGui::ColorEdit4(label, col->data(), flags);
        }
    ));

    luaImGuiNamespace.set_function("ColorPicker3", sol::overload(
        [&](const char* label, world2d::ImGui::FloatArray3* col) {
            return ::ImGui::ColorPicker3(label, col->data());
        },

        [&](const char* label, world2d::ImGui::FloatArray3* col, ImGuiColorEditFlags flags) {
            return ::ImGui::ColorPicker3(label, col->data(), flags);
        }
    ));

    luaImGuiNamespace.set_function("ColorPicker4", sol::overload(
        [&](const char* label, world2d::ImGui::FloatArray4* col) {
            return ::ImGui::ColorPicker4(label, col->data());
        },

        [&](const char* label, world2d::ImGui::FloatArray4* col, ImGuiColorEditFlags flags) {
            return ::ImGui::ColorPicker4(label, col->data(), flags);
        },

        [&](const char* label, world2d::ImGui::FloatArray4* col, ImGuiColorEditFlags flags, const world2d::ImGui::Float* refCol) {
            return ::ImGui::ColorPicker4(label, col->data(), flags, &(refCol->value));
        }
    ));

    luaImGuiNamespace.set_function("ColorButton", sol::overload(
        [&](const char* descId, const ImVec4& col) {
            return ::ImGui::ColorButton(descId, col);
        },

        [&](const char* descId, const ImVec4& col, ImGuiColorEditFlags flags) {
            return ::ImGui::ColorButton(descId, col, flags);
        },

        [&](const char* descId, const ImVec4& col, ImGuiColorEditFlags flags, ImVec2 size) {
            return ::ImGui::ColorButton(descId, col, flags, size);
        }
    ));

    luaImGuiNamespace.set_function("SetColorEditOptions", &::ImGui::SetColorEditOptions);
}

world2d::ImGui::ColorEditorPickerWidget* world2d::ImGui::ColorEditorPickerWidget::Get() {
    static world2d::ImGui::ColorEditorPickerWidget currentWidget;
    return &currentWidget;
}