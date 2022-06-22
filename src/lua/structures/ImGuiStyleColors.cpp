#include "world2d/lua/structures/ImGuiStyleColors.h"
#include <cassert>

world2d::ImGuiStyleColors::ImGuiStyleColors(ImVec4* colors) : mColors(colors) {

}

ImVec4 world2d::ImGuiStyleColors::LuaIndexOperator(size_t idx) {
    assert((idx + 1) >= 0 && (idx + 1) < ImGuiCol_COUNT);
    return mColors[idx + 1];
}

void world2d::ImGuiStyleColors::LuaNewIndexOperator(size_t idx, ImVec4 value) {
    assert((idx + 1) >= 0 && (idx + 1) < ImGuiCol_COUNT);
    mColors[idx + 1] = value;
}