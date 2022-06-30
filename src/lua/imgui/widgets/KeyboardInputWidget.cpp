#include "world2d/lua/imgui/widgets/KeyboardInputWidget.h"

#include "imgui/imgui.h"
#include "imgui/imgui_stdlib.h"

#include "world2d/lua/imgui/structures/String.h"

#include "world2d/lua/imgui/structures/Float.h"
#include "world2d/lua/imgui/structures/FloatArray2.h"
#include "world2d/lua/imgui/structures/FloatArray3.h"
#include "world2d/lua/imgui/structures/FloatArray4.h"

#include "world2d/lua/imgui/structures/Int.h"
#include "world2d/lua/imgui/structures/IntArray2.h"
#include "world2d/lua/imgui/structures/IntArray3.h"
#include "world2d/lua/imgui/structures/IntArray4.h"

world2d::ImGui::KeyboardInputWidget::KeyboardInputWidget() {

}

void world2d::ImGui::KeyboardInputWidget::SetLuaEnvironment(sol::table& luaImGuiNamespace) {
    luaImGuiNamespace.set_function("InputText", sol::overload(
        [&](const char* label, ::world2d::ImGui::String* str) {
            return ::ImGui::InputText(label, &(str->value));
        },

        [&](const char* label, ::world2d::ImGui::String* str, ImGuiInputTextFlags flags) {
            return ::ImGui::InputText(label, &(str->value), flags);
        }
    ));

    luaImGuiNamespace.set_function("InputTextMultiline", sol::overload(
        [&](const char* label, ::world2d::ImGui::String* str) {
            return ::ImGui::InputTextMultiline(label, &(str->value));
        },

        [&](const char* label, ::world2d::ImGui::String* str, const ImVec2& size) {
            return ::ImGui::InputTextMultiline(label, &(str->value), size);
        },

        [&](const char* label, ::world2d::ImGui::String* str, const ImVec2& size, ImGuiInputTextFlags flags) {
            return ::ImGui::InputTextMultiline(label, &(str->value), size, flags);
        }
    ));

    luaImGuiNamespace.set_function("InputTextWithHint", sol::overload(
        [&](const char* label, const char* hint, ::world2d::ImGui::String* str) {
            return ::ImGui::InputTextWithHint(label, hint, &(str->value));
        },

        [&](const char* label, const char* hint, ::world2d::ImGui::String* str, ImGuiInputTextFlags flags) {
            return ::ImGui::InputTextWithHint(label, hint, &(str->value), flags);
        }
    ));

    luaImGuiNamespace.set_function("InputFloat", sol::overload(
        [&](const char* label, world2d::ImGui::Float* v) {
            return ::ImGui::InputFloat(label, &(v->value));
        },

        [&](const char* label, world2d::ImGui::Float* v, float step) {
            return ::ImGui::InputFloat(label, &(v->value), step);
        },

        [&](const char* label, world2d::ImGui::Float* v, float step, float step_fast) {
            return ::ImGui::InputFloat(label, &(v->value), step, step_fast);
        },

        [&](const char* label, world2d::ImGui::Float* v, float step, float step_fast, const char* format) {
            return ::ImGui::InputFloat(label, &(v->value), step, step_fast, format);
        },

        [&](const char* label, world2d::ImGui::Float* v, float step, float step_fast, const char* format, ImGuiInputTextFlags flags) {
            return ::ImGui::InputFloat(label, &(v->value), step, step_fast, format, flags);
        }
    ));

    luaImGuiNamespace.set_function("InputFloat2", sol::overload(
        [&](const char* label, world2d::ImGui::FloatArray2* v) {
            return ::ImGui::InputFloat2(label, v->data());
        },

        [&](const char* label, world2d::ImGui::FloatArray2* v, const char* format) {
            return ::ImGui::InputFloat2(label, v->data(), format);
        },

        [&](const char* label, world2d::ImGui::FloatArray2* v, const char* format, ImGuiInputTextFlags flags) {
            return ::ImGui::InputFloat2(label, v->data(), format, flags);
        }
    ));

    luaImGuiNamespace.set_function("InputFloat3", sol::overload(
        [&](const char* label, world2d::ImGui::FloatArray3* v) {
            return ::ImGui::InputFloat3(label, v->data());
        },

        [&](const char* label, world2d::ImGui::FloatArray3* v, const char* format) {
            return ::ImGui::InputFloat3(label, v->data(), format);
        },

        [&](const char* label, world2d::ImGui::FloatArray3* v, const char* format, ImGuiInputTextFlags flags) {
            return ::ImGui::InputFloat3(label, v->data(), format, flags);
        }
    ));

    luaImGuiNamespace.set_function("InputFloat4", sol::overload(
        [&](const char* label, world2d::ImGui::FloatArray4* v) {
            return ::ImGui::InputFloat4(label, v->data());
        },

        [&](const char* label, world2d::ImGui::FloatArray4* v, const char* format) {
            return ::ImGui::InputFloat4(label, v->data(), format);
        },

        [&](const char* label, world2d::ImGui::FloatArray4* v, const char* format, ImGuiInputTextFlags flags) {
            return ::ImGui::InputFloat4(label, v->data(), format, flags);
        }
    ));

    luaImGuiNamespace.set_function("InputInt", sol::overload(
        [&](const char* label, world2d::ImGui::Int* v) {
            return ::ImGui::InputInt(label, &(v->value));
        },

        [&](const char* label, world2d::ImGui::Int* v, int step) {
            return ::ImGui::InputInt(label, &(v->value), step);
        },

        [&](const char* label, world2d::ImGui::Int* v, int step, int step_fast) {
            return ::ImGui::InputInt(label, &(v->value), step, step_fast);
        },

        [&](const char* label, world2d::ImGui::Int* v, int step, int step_fast, ImGuiInputTextFlags flags) {
            return ::ImGui::InputInt(label, &(v->value), step, step_fast, flags);
        }
    ));

    luaImGuiNamespace.set_function("InputInt2", sol::overload(
        [&](const char* label, world2d::ImGui::IntArray2* v) {
            return ::ImGui::InputInt2(label, v->data());
        },

        [&](const char* label, world2d::ImGui::IntArray2* v, ImGuiInputTextFlags flags) {
            return ::ImGui::InputInt2(label, v->data(), flags);
        }
    ));

    luaImGuiNamespace.set_function("InputInt3", sol::overload(
        [&](const char* label, world2d::ImGui::IntArray3* v) {
            return ::ImGui::InputInt3(label, v->data());
        },

        [&](const char* label, world2d::ImGui::IntArray3* v, ImGuiInputTextFlags flags) {
            return ::ImGui::InputInt3(label, v->data(), flags);
        }
    ));

    luaImGuiNamespace.set_function("InputInt4", sol::overload(
        [&](const char* label, world2d::ImGui::IntArray4* v) {
            return ::ImGui::InputInt4(label, v->data());
        },

        [&](const char* label, world2d::ImGui::IntArray4* v, ImGuiInputTextFlags flags) {
            return ::ImGui::InputInt4(label, v->data(), flags);
        }
    ));
}

world2d::ImGui::KeyboardInputWidget* world2d::ImGui::KeyboardInputWidget::Get() {
    static world2d::ImGui::KeyboardInputWidget currentWidget;
    return &currentWidget;
}