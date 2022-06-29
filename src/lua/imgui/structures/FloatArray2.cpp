#include "world2d/lua/imgui/structures/FloatArray2.h"

world2d::ImGui::FloatArray2::FloatArray2() {
    arr[0] = 0.0f;
    arr[1] = 0.0f;
}

world2d::ImGui::FloatArray2::FloatArray2(float v1, float v2) {
    arr[0] = v1;
    arr[1] = v2;
}

float* world2d::ImGui::FloatArray2::data() {
    return arr;
}

float world2d::ImGui::FloatArray2::LuaIndexOperator(size_t idx) {
    return arr[idx - 1];
}

void world2d::ImGui::FloatArray2::LuaNewIndexOperator(size_t idx, float value) {
    arr[idx - 1] = value;
}