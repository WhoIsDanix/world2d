#include "world2d/lua/imgui/widgets/SliderWidget.h"
#include "imgui/imgui.h"

#include "world2d/lua/imgui/structures/Float.h"
#include "world2d/lua/imgui/structures/FloatArray2.h"
#include "world2d/lua/imgui/structures/FloatArray3.h"
#include "world2d/lua/imgui/structures/FloatArray4.h"

#include "world2d/lua/imgui/structures/Int.h"
#include "world2d/lua/imgui/structures/IntArray2.h"
#include "world2d/lua/imgui/structures/IntArray3.h"
#include "world2d/lua/imgui/structures/IntArray4.h"

world2d::ImGui::SliderWidget::SliderWidget() {

}

void world2d::ImGui::SliderWidget::SetLuaEnvironment(sol::table& luaImGuiNamespace) {
    luaImGuiNamespace.set_function("SliderFloat", sol::overload(
        [&](const char* label, world2d::ImGui::Float* v, float vMin, float vMax) {
            return ::ImGui::SliderFloat(label, &(v->value), vMin, vMax);
        },

        [&](const char* label, world2d::ImGui::Float* v, float vMin, float vMax, const char* format) {
            return ::ImGui::SliderFloat(label, &(v->value), vMin, vMax, format);
        },

        [&](const char* label, world2d::ImGui::Float* v, float vMin, float vMax, const char* format, float power) {
            return ::ImGui::SliderFloat(label, &(v->value), vMin, vMax, format, power);
        }
    ));

    luaImGuiNamespace.set_function("SliderFloat2", sol::overload(
        [&](const char* label, world2d::ImGui::FloatArray2* v, float vMin, float vMax) {
            return ::ImGui::SliderFloat2(label, v->data(), vMin, vMax);
        },

        [&](const char* label, world2d::ImGui::FloatArray2* v, float vMin, float vMax, const char* format) {
            return ::ImGui::SliderFloat2(label, v->data(), vMin, vMax, format);
        },

        [&](const char* label, world2d::ImGui::FloatArray2* v, float vMin, float vMax, const char* format, float power) {
            return ::ImGui::SliderFloat2(label, v->data(), vMin, vMax, format, power);
        }
    ));

    luaImGuiNamespace.set_function("SliderFloat3", sol::overload(
        [&](const char* label, world2d::ImGui::FloatArray3* v, float vMin, float vMax) {
            return ::ImGui::SliderFloat3(label, v->data(), vMin, vMax);
        },

        [&](const char* label, world2d::ImGui::FloatArray3* v, float vMin, float vMax, const char* format) {
            return ::ImGui::SliderFloat3(label, v->data(), vMin, vMax, format);
        },

        [&](const char* label, world2d::ImGui::FloatArray3* v, float vMin, float vMax, const char* format, float power) {
            return ::ImGui::SliderFloat3(label, v->data(), vMin, vMax, format, power);
        }
    ));

    luaImGuiNamespace.set_function("SliderFloat4", sol::overload(
        [&](const char* label, world2d::ImGui::FloatArray4* v, float vMin, float vMax) {
            return ::ImGui::SliderFloat4(label, v->data(), vMin, vMax);
        },

        [&](const char* label, world2d::ImGui::FloatArray4* v, float vMin, float vMax, const char* format) {
            return ::ImGui::SliderFloat4(label, v->data(), vMin, vMax, format);
        },

        [&](const char* label, world2d::ImGui::FloatArray4* v, float vMin, float vMax, const char* format, float power) {
            return ::ImGui::SliderFloat4(label, v->data(), vMin, vMax, format, power);
        }
    ));

    luaImGuiNamespace.set_function("SliderAngle", sol::overload(
        [&](const char* label, world2d::ImGui::Float* vRad) {
            return ::ImGui::SliderAngle(label, &(vRad->value));
        },

        [&](const char* label, world2d::ImGui::Float* vRad, float vDegreesMin) {
            return ::ImGui::SliderAngle(label, &(vRad->value), vDegreesMin);
        },

        [&](const char* label, world2d::ImGui::Float* vRad, float vDegreesMin, float vDegreesMax) {
            return ::ImGui::SliderAngle(label, &(vRad->value), vDegreesMin, vDegreesMax);
        },

        [&](const char* label, world2d::ImGui::Float* vRad, float vDegreesMin, float vDegreesMax, const char* format) {
            return ::ImGui::SliderAngle(label, &(vRad->value), vDegreesMin, vDegreesMax, format);
        }
    ));

    luaImGuiNamespace.set_function("SliderInt", sol::overload(
        [&](const char* label, world2d::ImGui::Int* v, int vMin, int vMax) {
            return ::ImGui::SliderInt(label, &(v->value), vMin, vMax);
        },

        [&](const char* label, world2d::ImGui::Int* v, int vMin, int vMax, const char* format) {
            return ::ImGui::SliderInt(label, &(v->value), vMin, vMax, format);
        }
    ));

    luaImGuiNamespace.set_function("SliderInt2", sol::overload(
        [&](const char* label, world2d::ImGui::IntArray2* v, int vMin, int vMax) {
            return ::ImGui::SliderInt2(label, v->data(), vMin, vMax);
        },

        [&](const char* label, world2d::ImGui::IntArray2* v, int vMin, int vMax, const char* format) {
            return ::ImGui::SliderInt2(label, v->data(), vMin, vMax, format);
        }
    ));

    luaImGuiNamespace.set_function("SliderInt3", sol::overload(
        [&](const char* label, world2d::ImGui::IntArray3* v, int vMin, int vMax) {
            return ::ImGui::SliderInt3(label, v->data(), vMin, vMax);
        },

        [&](const char* label, world2d::ImGui::IntArray3* v, int vMin, int vMax, const char* format) {
            return ::ImGui::SliderInt3(label, v->data(), vMin, vMax, format);
        }
    ));

    luaImGuiNamespace.set_function("SliderInt4", sol::overload(
        [&](const char* label, world2d::ImGui::IntArray4* v, int vMin, int vMax) {
            return ::ImGui::SliderInt4(label, v->data(), vMin, vMax);
        },

        [&](const char* label, world2d::ImGui::IntArray4* v, int vMin, int vMax, const char* format) {
            return ::ImGui::SliderInt4(label, v->data(), vMin, vMax, format);
        }
    ));
}

world2d::ImGui::SliderWidget* world2d::ImGui::SliderWidget::Get() {
    static world2d::ImGui::SliderWidget currentWidget;
    return &currentWidget;
}