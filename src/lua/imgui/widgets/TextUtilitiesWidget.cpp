#include "world2d/lua/imgui/widgets/TextUtilitiesWidget.h"
#include "imgui/imgui.h"

world2d::ImGui::TextUtilitiesWidget::TextUtilitiesWidget() {

}

void world2d::ImGui::TextUtilitiesWidget::SetLuaEnvironment(sol::table& luaImGuiNamespace) {
    luaImGuiNamespace.set_function("CalcTextSize", sol::overload(
        [&](const char* text) {
            return ::ImGui::CalcTextSize(text);
        },

        [&](const char* text, const char* textEnd) {
            return ::ImGui::CalcTextSize(text, textEnd);
        },

        [&](const char* text, const char* textEnd, bool hideTextAfterDoubleHash) {
            return ::ImGui::CalcTextSize(text, textEnd, hideTextAfterDoubleHash);
        },

        [&](const char* text, const char* textEnd, bool hideTextAfterDoubleHash, float wrapWidth) {
            return ::ImGui::CalcTextSize(text, textEnd, hideTextAfterDoubleHash, wrapWidth);
        }
    ));
}

world2d::ImGui::TextUtilitiesWidget* world2d::ImGui::TextUtilitiesWidget::Get() {
    static world2d::ImGui::TextUtilitiesWidget currentWidget;
    return &currentWidget;
}