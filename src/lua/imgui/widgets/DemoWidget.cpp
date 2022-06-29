#include "world2d/lua/imgui/widgets/DemoWidget.h"

#include "imgui/imgui.h"
#include "world2d/lua/imgui/structures/Bool.h"

world2d::ImGui::DemoWidget::DemoWidget() {

}

void world2d::ImGui::DemoWidget::SetLuaEnvironment(sol::table& luaImGuiNamespace) {
    luaImGuiNamespace.set_function("ShowDemoWindow", sol::overload(
        [&]() {
            ::ImGui::ShowDemoWindow();
        },

        [&](world2d::ImGui::Bool* pOpen) {
            ::ImGui::ShowDemoWindow(&(pOpen->value));
        }
    ));

    luaImGuiNamespace.set_function("ShowAboutWindow", sol::overload(
        [&]() {
            ::ImGui::ShowAboutWindow();
        },

        [&](world2d::ImGui::Bool* pOpen) {
            ::ImGui::ShowAboutWindow(&(pOpen->value));
        }
    ));

    luaImGuiNamespace.set_function("ShowMetricsWindow", [&](world2d::ImGui::Bool* pOpen) {
        ::ImGui::ShowMetricsWindow(&(pOpen->value));
    });

    luaImGuiNamespace.set_function("ShowStyleSelector", &::ImGui::ShowStyleSelector);
    luaImGuiNamespace.set_function("ShowFontSelector", &::ImGui::ShowFontSelector);
    luaImGuiNamespace.set_function("ShowUserGuide", &::ImGui::ShowUserGuide);
}

world2d::ImGui::DemoWidget* world2d::ImGui::DemoWidget::Get() {
    static world2d::ImGui::DemoWidget currentWidget;
    return &currentWidget;
}