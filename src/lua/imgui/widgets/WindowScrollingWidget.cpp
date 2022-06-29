#include "world2d/lua/imgui/widgets/WindowScrollingWidget.h"
#include "imgui/imgui.h"

world2d::ImGui::WindowScrollingWidget::WindowScrollingWidget() {

}

void world2d::ImGui::WindowScrollingWidget::SetLuaEnvironment(sol::table& luaImGuiNamespace) {
    luaImGuiNamespace.set_function("GetScrollX", &::ImGui::GetScrollX);
    luaImGuiNamespace.set_function("GetScrollY", &::ImGui::GetScrollY);
    luaImGuiNamespace.set_function("GetScrollMaxX", &::ImGui::GetScrollMaxX);
    luaImGuiNamespace.set_function("GetScrollMaxY", &::ImGui::GetScrollMaxY);
    luaImGuiNamespace.set_function("SetScrollX", &::ImGui::SetScrollX);
    luaImGuiNamespace.set_function("SetScrollY", &::ImGui::SetScrollY);

    luaImGuiNamespace.set_function("SetScrollHereX", sol::overload(
        [&]() {
            ::ImGui::SetScrollHereX();
        },

        [&](float centerXRatio) {
            ::ImGui::SetScrollHereX(centerXRatio);
        }
    ));

    luaImGuiNamespace.set_function("SetScrollHereY", sol::overload(
        [&]() {
            ::ImGui::SetScrollHereY();
        },

        [&](float centerYRatio) {
            ::ImGui::SetScrollHereY(centerYRatio);
        }
    ));

    luaImGuiNamespace.set_function("SetScrollFromPosX", sol::overload(
        [&](float localX) {
            ::ImGui::SetScrollFromPosX(localX);
        },

        [&](float localX, float centerXRatio) {
            ::ImGui::SetScrollFromPosX(localX, centerXRatio);
        }
    ));

    luaImGuiNamespace.set_function("SetScrollFromPosY", sol::overload(
        [&](float localY) {
            ::ImGui::SetScrollFromPosY(localY);
        },

        [&](float localY, float centerYRatio) {
            ::ImGui::SetScrollFromPosY(localY, centerYRatio);
        }
    ));
}

world2d::ImGui::WindowScrollingWidget* world2d::ImGui::WindowScrollingWidget::Get() {
    static world2d::ImGui::WindowScrollingWidget currentWidget;
    return &currentWidget;
}