#include "world2d/lua/imgui/widgets/MainWidget.h"
#include "imgui/imgui.h"

#include "world2d/lua/imgui/structures/Bool.h"
#include "world2d/lua/imgui/structures/Int.h"

world2d::ImGui::MainWidget::MainWidget() {

}

void world2d::ImGui::MainWidget::SetLuaEnvironment(sol::table& luaImGuiNamespace) {
    luaImGuiNamespace.set_function("GetIO", &::ImGui::GetIO);
    luaImGuiNamespace.set_function("GetStyle", &::ImGui::GetStyle);

    luaImGuiNamespace.set_function("Button", sol::overload(
        [&](const char* label) {
            return ::ImGui::Button(label);
        },

        [&](const char* label, const ImVec2& size) {
            return ::ImGui::Button(label, size);
        }
    ));

    luaImGuiNamespace.set_function("SmallButton", &::ImGui::SmallButton);
    luaImGuiNamespace.set_function("InvisibleButton", &::ImGui::InvisibleButton);
    luaImGuiNamespace.set_function("ArrowButton", &::ImGui::ArrowButton);

    luaImGuiNamespace.set_function("Checkbox", [&](const char* label, world2d::ImGui::Bool* imGuiBool) {
        return ::ImGui::Checkbox(label, &(imGuiBool->value));
    });

    luaImGuiNamespace.set_function("RadioButton", sol::overload(
        [&](const char* label, bool active) {
            return ::ImGui::RadioButton(label, active);
        },

        [&](const char* label, world2d::ImGui::Int* v, int vButton) {
            return ::ImGui::RadioButton(label, &(v->value), vButton);
        }
    ));

    luaImGuiNamespace.set_function("ProgressBar", sol::overload(
        [&](float fraction) {
            ::ImGui::ProgressBar(fraction);
        },

        [&](float fraction, const ImVec2& sizeArg) {
            ::ImGui::ProgressBar(fraction, sizeArg);
        },

        [&](float fraction, const ImVec2& sizeArg, const char* overlay) {
            ::ImGui::ProgressBar(fraction, sizeArg, overlay);
        }
    ));

    luaImGuiNamespace.set_function("Bullet", &::ImGui::Bullet);
}

world2d::ImGui::MainWidget* world2d::ImGui::MainWidget::Get() {
    static world2d::ImGui::MainWidget currentWidget;
    return &currentWidget;
}