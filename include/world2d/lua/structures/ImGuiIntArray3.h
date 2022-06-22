#ifndef WORLD2D_LUA_STRUCTURES_IMGUIINTARRAY3_H
#define WORLD2D_LUA_STRUCTURES_IMGUIINTARRAY3_H

#include <cstddef>

namespace world2d {
    class ImGuiIntArray3 {
    private:
        int arr[3];

    public:
        ImGuiIntArray3();
        ImGuiIntArray3(int v1, int v2, int v3);

        int* data();

        int LuaIndexOperator(size_t idx);
        void LuaNewIndexOperator(size_t idx, int value);
    };
}

#endif