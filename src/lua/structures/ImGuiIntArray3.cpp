#include "world2d/lua/structures/ImGuiIntArray3.h"

world2d::ImGuiIntArray3::ImGuiIntArray3() {
    arr[0] = 0;
    arr[1] = 0;
    arr[2] = 0;
}

world2d::ImGuiIntArray3::ImGuiIntArray3(int v1, int v2, int v3) {
    arr[0] = v1;
    arr[1] = v2;
    arr[2] = v3;
}

int* world2d::ImGuiIntArray3::data() {
    return arr;
}

int world2d::ImGuiIntArray3::LuaIndexOperator(size_t idx) {
    return arr[idx - 1];
}

void world2d::ImGuiIntArray3::LuaNewIndexOperator(size_t idx, int value) {
    arr[idx - 1] = value;
}