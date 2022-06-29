#include "world2d/lua/imgui/structures/FloatArray3.h"

world2d::ImGui::FloatArray3::FloatArray3() {
    arr[0] = 0.0f;
    arr[1] = 0.0f;
    arr[2] = 0.0f;
}

world2d::ImGui::FloatArray3::FloatArray3(float v1, float v2, float v3) {
    arr[0] = v1;
    arr[1] = v2;
    arr[2] = v3;
}

float* world2d::ImGui::FloatArray3::data() {
    return arr;
}

float world2d::ImGui::FloatArray3::LuaIndexOperator(size_t idx) {
    return arr[idx - 1];
}

void world2d::ImGui::FloatArray3::LuaNewIndexOperator(size_t idx, float value) {
    arr[idx - 1] = value;
}