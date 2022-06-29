#include "world2d/lua/imgui/structures/IntArray4.h"

world2d::ImGui::IntArray4::IntArray4() {
    arr[0] = 0;
    arr[1] = 0;
    arr[2] = 0;
    arr[3] = 0;
}

world2d::ImGui::IntArray4::IntArray4(int v1, int v2, int v3, int v4) {
    arr[0] = v1;
    arr[1] = v2;
    arr[2] = v3;
    arr[3] = v4;
}

int* world2d::ImGui::IntArray4::data() {
    return arr;
}

int world2d::ImGui::IntArray4::LuaIndexOperator(size_t idx) {
    return arr[idx - 1];
}

void world2d::ImGui::IntArray4::LuaNewIndexOperator(size_t idx, int value) {
    arr[idx - 1] = value;
}