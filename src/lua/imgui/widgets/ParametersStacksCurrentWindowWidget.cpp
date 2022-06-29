#include "world2d/lua/imgui/widgets/ParametersStacksCurrentWindowWidget.h"
#include "imgui/imgui.h"

world2d::ImGui::ParametersStacksCurrentWindowWidget::ParametersStacksCurrentWindowWidget() {

}

void world2d::ImGui::ParametersStacksCurrentWindowWidget::SetLuaEnvironment(sol::table& luaImGuiNamespace) {
    luaImGuiNamespace.set_function("PushItemWidth", &::ImGui::PushItemWidth);
    luaImGuiNamespace.set_function("PopItemWidth", &::ImGui::PopItemWidth);
    luaImGuiNamespace.set_function("SetNextItemWidth", &::ImGui::SetNextItemWidth);
    luaImGuiNamespace.set_function("CalcItemWidth", &::ImGui::CalcItemWidth);

    luaImGuiNamespace.set_function("PushTextWrapPos", sol::overload(
        [&]() {
            ::ImGui::PushTextWrapPos();
        },

        [&](float wrapLocalPosX) {
            ::ImGui::PushTextWrapPos(wrapLocalPosX);
        }
    ));

    luaImGuiNamespace.set_function("PopTextWrapPos", &::ImGui::PopTextWrapPos);
    luaImGuiNamespace.set_function("PushAllowKeyboardFocus", &::ImGui::PushAllowKeyboardFocus);
    luaImGuiNamespace.set_function("PopAllowKeyboardFocus", &::ImGui::PopAllowKeyboardFocus);
    luaImGuiNamespace.set_function("PushButtonRepeat", &::ImGui::PushButtonRepeat);
    luaImGuiNamespace.set_function("PopButtonRepeat", &::ImGui::PopButtonRepeat);
}

world2d::ImGui::ParametersStacksCurrentWindowWidget* world2d::ImGui::ParametersStacksCurrentWindowWidget::Get() {
    static world2d::ImGui::ParametersStacksCurrentWindowWidget currentWidget;
    return &currentWidget;
}