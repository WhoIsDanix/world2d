#include "world2d/lua/imgui/widgets/ComboBoxWidget.h"
#include "imgui/imgui.h"

#include "world2d/lua/imgui/structures/Float.h"
#include "world2d/lua/imgui/structures/FloatArray2.h"
#include "world2d/lua/imgui/structures/FloatArray3.h"
#include "world2d/lua/imgui/structures/FloatArray4.h"

#include "world2d/lua/imgui/structures/Int.h"
#include "world2d/lua/imgui/structures/IntArray2.h"
#include "world2d/lua/imgui/structures/IntArray3.h"
#include "world2d/lua/imgui/structures/IntArray4.h"

world2d::ImGui::ComboBoxWidget::ComboBoxWidget() {

}

void world2d::ImGui::ComboBoxWidget::SetLuaEnvironment(sol::table& luaImGuiNamespace) {
    luaImGuiNamespace.set_function("BeginCombo", sol::overload(
        [&](const char* label, const char* previewValue) {
            return ::ImGui::BeginCombo(label, previewValue);
        },

        [&](const char* label, const char* previewValue, ImGuiComboFlags flags) {
            return ::ImGui::BeginCombo(label, previewValue, flags);
        }
    ));

    luaImGuiNamespace.set_function("EndCombo", &::ImGui::EndCombo);

    luaImGuiNamespace.set_function("DragFloat", sol::overload(
        [&](const char* label, world2d::ImGui::Float* v) {
            return ::ImGui::DragFloat(label, &(v->value));
        },

        [&](const char* label, world2d::ImGui::Float* v, float vSpeed) {
            return ::ImGui::DragFloat(label, &(v->value), vSpeed);
        },

        [&](const char* label, world2d::ImGui::Float* v, float vSpeed, float vMin) {
            return ::ImGui::DragFloat(label, &(v->value), vSpeed, vMin);
        },

        [&](const char* label, world2d::ImGui::Float* v, float vSpeed, float vMin, float vMax) {
            return ::ImGui::DragFloat(label, &(v->value), vSpeed, vMin, vMax);
        },

        [&](const char* label, world2d::ImGui::Float* v, float vSpeed, float vMin, float vMax, const char* format) {
            return ::ImGui::DragFloat(label, &(v->value), vSpeed, vMin, vMax, format);
        },

        [&](const char* label, world2d::ImGui::Float* v, float vSpeed, float vMin, float vMax, const char* format, float power) {
            return ::ImGui::DragFloat(label, &(v->value), vSpeed, vMin, vMax, format, power);
        }
    ));

    luaImGuiNamespace.set_function("DragFloat2", sol::overload(
        [&](const char* label, world2d::ImGui::FloatArray2* v) {
            return ::ImGui::DragFloat2(label, v->data());
        },

        [&](const char* label, world2d::ImGui::FloatArray2* v, float vSpeed) {
            return ::ImGui::DragFloat2(label, v->data(), vSpeed);
        },

        [&](const char* label, world2d::ImGui::FloatArray2* v, float vSpeed, float vMin) {
            return ::ImGui::DragFloat2(label, v->data(), vSpeed, vMin);
        },

        [&](const char* label, world2d::ImGui::FloatArray2* v, float vSpeed, float vMin, float vMax) {
            return ::ImGui::DragFloat2(label, v->data(), vSpeed, vMin, vMax);
        },

        [&](const char* label, world2d::ImGui::FloatArray2* v, float vSpeed, float vMin, float vMax, const char* format) {
            return ::ImGui::DragFloat2(label, v->data(), vSpeed, vMin, vMax, format);
        },

        [&](const char* label, world2d::ImGui::FloatArray2* v, float vSpeed, float vMin, float vMax, const char* format, float power) {
            return ::ImGui::DragFloat2(label, v->data(), vSpeed, vMin, vMax, format, power);
        }
    ));

    luaImGuiNamespace.set_function("DragFloat3", sol::overload(
        [&](const char* label, world2d::ImGui::FloatArray3* v) {
            return ::ImGui::DragFloat3(label, v->data());
        },

        [&](const char* label, world2d::ImGui::FloatArray3* v, float vSpeed) {
            return ::ImGui::DragFloat3(label, v->data(), vSpeed);
        },

        [&](const char* label, world2d::ImGui::FloatArray3* v, float vSpeed, float vMin) {
            return ::ImGui::DragFloat3(label, v->data(), vSpeed, vMin);
        },

        [&](const char* label, world2d::ImGui::FloatArray3* v, float vSpeed, float vMin, float vMax) {
            return ::ImGui::DragFloat3(label, v->data(), vSpeed, vMin, vMax);
        },

        [&](const char* label, world2d::ImGui::FloatArray3* v, float vSpeed, float vMin, float vMax, const char* format) {
            return ::ImGui::DragFloat3(label, v->data(), vSpeed, vMin, vMax, format);
        },

        [&](const char* label, world2d::ImGui::FloatArray3* v, float vSpeed, float vMin, float vMax, const char* format, float power) {
            return ::ImGui::DragFloat3(label, v->data(), vSpeed, vMin, vMax, format, power);
        }
    ));

    luaImGuiNamespace.set_function("DragFloat4", sol::overload(
        [&](const char* label, world2d::ImGui::FloatArray4* v) {
            return ::ImGui::DragFloat4(label, v->data());
        },

        [&](const char* label, world2d::ImGui::FloatArray4* v, float vSpeed) {
            return ::ImGui::DragFloat4(label, v->data(), vSpeed);
        },

        [&](const char* label, world2d::ImGui::FloatArray4* v, float vSpeed, float vMin) {
            return ::ImGui::DragFloat4(label, v->data(), vSpeed, vMin);
        },

        [&](const char* label, world2d::ImGui::FloatArray4* v, float vSpeed, float vMin, float vMax) {
            return ::ImGui::DragFloat4(label, v->data(), vSpeed, vMin, vMax);
        },

        [&](const char* label, world2d::ImGui::FloatArray4* v, float vSpeed, float vMin, float vMax, const char* format) {
            return ::ImGui::DragFloat4(label, v->data(), vSpeed, vMin, vMax, format);
        },

        [&](const char* label, world2d::ImGui::FloatArray4* v, float vSpeed, float vMin, float vMax, const char* format, float power) {
            return ::ImGui::DragFloat4(label, v->data(), vSpeed, vMin, vMax, format, power);
        }
    ));

    luaImGuiNamespace.set_function("DragFloatRange2", sol::overload(
        [&](const char* label, world2d::ImGui::Float* vCurrentMin, world2d::ImGui::Float* vCurrentMax) {
            return ::ImGui::DragFloatRange2(label, &(vCurrentMin->value), &(vCurrentMax->value));
        },

        [&](const char* label, world2d::ImGui::Float* vCurrentMin, world2d::ImGui::Float* vCurrentMax, float vSpeed) {
            return ::ImGui::DragFloatRange2(label, &(vCurrentMin->value), &(vCurrentMax->value), vSpeed);
        },

        [&](const char* label, world2d::ImGui::Float* vCurrentMin, world2d::ImGui::Float* vCurrentMax, float vSpeed, float vMin) {
            return ::ImGui::DragFloatRange2(label, &(vCurrentMin->value), &(vCurrentMax->value), vSpeed, vMin);
        },

        [&](const char* label, world2d::ImGui::Float* vCurrentMin, world2d::ImGui::Float* vCurrentMax, float vSpeed, float vMin, float vMax) {
            return ::ImGui::DragFloatRange2(label, &(vCurrentMin->value), &(vCurrentMax->value), vSpeed, vMin, vMax);
        },

        [&](const char* label, world2d::ImGui::Float* vCurrentMin, world2d::ImGui::Float* vCurrentMax, float vSpeed, float vMin, float vMax, const char* format) {
            return ::ImGui::DragFloatRange2(label, &(vCurrentMin->value), &(vCurrentMax->value), vSpeed, vMin, vMax, format);
        },

        [&](const char* label, world2d::ImGui::Float* vCurrentMin, world2d::ImGui::Float* vCurrentMax, float vSpeed, float vMin, float vMax, const char* format, const char* formatMax) {
            return ::ImGui::DragFloatRange2(label, &(vCurrentMin->value), &(vCurrentMax->value), vSpeed, vMin, vMax, format, formatMax);
        },

        [&](const char* label, world2d::ImGui::Float* vCurrentMin, world2d::ImGui::Float* vCurrentMax, float vSpeed, float vMin, float vMax, const char* format, const char* formatMax, float power) {
            return ::ImGui::DragFloatRange2(label, &(vCurrentMin->value), &(vCurrentMax->value), vSpeed, vMin, vMax, format, formatMax, power);
        }
    ));

    luaImGuiNamespace.set_function("DragInt", sol::overload(
        [&](const char* label, world2d::ImGui::Int* v) {
            return ::ImGui::DragInt(label, &(v->value));
        },

        [&](const char* label, world2d::ImGui::Int* v, float vSpeed) {
            return ::ImGui::DragInt(label, &(v->value), vSpeed);
        },

        [&](const char* label, world2d::ImGui::Int* v, float vSpeed, int vMin) {
            return ::ImGui::DragInt(label, &(v->value), vSpeed, vMin);
        },

        [&](const char* label, world2d::ImGui::Int* v, float vSpeed, int vMin, int vMax) {
            return ::ImGui::DragInt(label, &(v->value), vSpeed, vMin, vMax);
        },

        [&](const char* label, world2d::ImGui::Int* v, float vSpeed, int vMin, int vMax, const char* format) {
            return ::ImGui::DragInt(label, &(v->value), vSpeed, vMin, vMax, format);
        }

        // TODO: add DragInt2, DragInt3, DragInt4, DragIntRange2, DragScalar, DragScalarN
    ));
}

world2d::ImGui::ComboBoxWidget* world2d::ImGui::ComboBoxWidget::Get() {
    static world2d::ImGui::ComboBoxWidget currentWidget;
    return &currentWidget;
}