#include "world2d/lua/structures/ImGuiIntArray2.h"

world2d::ImGuiIntArray2::ImGuiIntArray2() {
    arr[0] = 0;
    arr[1] = 0;
}

world2d::ImGuiIntArray2::ImGuiIntArray2(int v1, int v2) {
    arr[0] = v1;
    arr[1] = v2;
}

int* world2d::ImGuiIntArray2::data() {
    return arr;
}

int world2d::ImGuiIntArray2::LuaIndexOperator(size_t idx) {
    return arr[idx - 1];
}

void world2d::ImGuiIntArray2::LuaNewIndexOperator(size_t idx, int value) {
    arr[idx - 1] = value;
}