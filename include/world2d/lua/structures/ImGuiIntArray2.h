#ifndef WORLD2D_LUA_STRUCTURES_IMGUIINTARRAY2_H
#define WORLD2D_LUA_STRUCTURES_IMGUIINTARRAY2_H

#include <cstddef>

namespace world2d {
    class ImGuiIntArray2 {
    private:
        int arr[2];

    public:
        ImGuiIntArray2();
        ImGuiIntArray2(int v1, int v2);

        int* data();

        int LuaIndexOperator(size_t idx);
        void LuaNewIndexOperator(size_t idx, int value);
    };
}

#endif