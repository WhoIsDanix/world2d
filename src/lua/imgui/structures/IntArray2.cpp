#include "world2d/lua/imgui/structures/IntArray2.h"

world2d::ImGui::IntArray2::IntArray2() {
    arr[0] = 0;
    arr[1] = 0;
}

world2d::ImGui::IntArray2::IntArray2(int v1, int v2) {
    arr[0] = v1;
    arr[1] = v2;
}

int* world2d::ImGui::IntArray2::data() {
    return arr;
}

int world2d::ImGui::IntArray2::LuaIndexOperator(size_t idx) {
    return arr[idx - 1];
}

void world2d::ImGui::IntArray2::LuaNewIndexOperator(size_t idx, int value) {
    arr[idx - 1] = value;
}