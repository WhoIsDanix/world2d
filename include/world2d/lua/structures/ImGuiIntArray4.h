#ifndef WORLD2D_LUA_STRUCTURES_IMGUIINTARRAY4_H
#define WORLD2D_LUA_STRUCTURES_IMGUIINTARRAY4_H

#include <cstddef>

namespace world2d {
    class ImGuiIntArray4 {
    private:
        int arr[4];

    public:
        ImGuiIntArray4();
        ImGuiIntArray4(int v1, int v2, int v3, int v4);

        int* data();

        int LuaIndexOperator(size_t idx);
        void LuaNewIndexOperator(size_t idx, int value);
    };
}

#endif