#include "world2d/lua/imgui/structures/StyleColors.h"
#include <cassert>

world2d::ImGui::StyleColors::StyleColors(ImVec4* colors) : mColors(colors) {

}

ImVec4 world2d::ImGui::StyleColors::LuaIndexOperator(size_t idx) {
    assert((idx + 1) >= 0 && (idx + 1) < ImGuiCol_COUNT);
    return mColors[idx + 1];
}

void world2d::ImGui::StyleColors::LuaNewIndexOperator(size_t idx, ImVec4 value) {
    assert((idx + 1) >= 0 && (idx + 1) < ImGuiCol_COUNT);
    mColors[idx + 1] = value;
}