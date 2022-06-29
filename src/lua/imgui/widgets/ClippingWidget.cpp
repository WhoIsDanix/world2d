#include "world2d/lua/imgui/widgets/ClippingWidget.h"
#include "imgui/imgui.h"

world2d::ImGui::ClippingWidget::ClippingWidget() {

}

void world2d::ImGui::ClippingWidget::SetLuaEnvironment(sol::table& luaImGuiNamespace) {
    luaImGuiNamespace.set_function("PushClipRect", &::ImGui::PushClipRect);
    luaImGuiNamespace.set_function("PopClipRect", &::ImGui::PopClipRect);
}

world2d::ImGui::ClippingWidget* world2d::ImGui::ClippingWidget::Get() {
    static world2d::ImGui::ClippingWidget currentWidget;
    return &currentWidget;
}