#include "world2d/lua/imgui/structures/IntArray3.h"

world2d::ImGui::IntArray3::IntArray3() {
    arr[0] = 0;
    arr[1] = 0;
    arr[2] = 0;
}

world2d::ImGui::IntArray3::IntArray3(int v1, int v2, int v3) {
    arr[0] = v1;
    arr[1] = v2;
    arr[2] = v3;
}

int* world2d::ImGui::IntArray3::data() {
    return arr;
}

int world2d::ImGui::IntArray3::LuaIndexOperator(size_t idx) {
    return arr[idx - 1];
}

void world2d::ImGui::IntArray3::LuaNewIndexOperator(size_t idx, int value) {
    arr[idx - 1] = value;
}