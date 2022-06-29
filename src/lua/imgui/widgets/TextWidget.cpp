#include "world2d/lua/imgui/widgets/TextWidget.h"
#include "imgui/imgui.h"

world2d::ImGui::TextWidget::TextWidget() {

}

void world2d::ImGui::TextWidget::SetLuaEnvironment(sol::table& luaImGuiNamespace) {
    luaImGuiNamespace.set_function("Text", [&](const char* text) {
        ::ImGui::Text(text);
    });

    luaImGuiNamespace.set_function("TextColored", [&](const ImVec4& col, const char* text) {
        ::ImGui::TextColored(col, text);
    });

    luaImGuiNamespace.set_function("TextDisabled", [&](const char* text) {
        ::ImGui::TextDisabled(text);
    });

    luaImGuiNamespace.set_function("TextWrapped", [&](const char* text) {
        ::ImGui::TextWrapped(text);
    });

    luaImGuiNamespace.set_function("LabelText", [&](const char* label, const char* text) {
        ::ImGui::LabelText(label, text);
    });

    luaImGuiNamespace.set_function("BulletText", [&](const char* text) {
        ::ImGui::BulletText(text);
    });
}

world2d::ImGui::TextWidget* world2d::ImGui::TextWidget::Get() {
    static world2d::ImGui::TextWidget currentWidget;
    return &currentWidget;
}