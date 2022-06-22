#ifndef WORLD2D_LUA_STRUCTURES_IMGUIFLOATARRAY2_H
#define WORLD2D_LUA_STRUCTURES_IMGUIFLOATARRAY2_H

#include <cstddef>

namespace world2d {
    class ImGuiFloatArray2 {
    private:
        float arr[2];

    public:
        ImGuiFloatArray2();
        ImGuiFloatArray2(float v1, float v2);

        float* data();

        float LuaIndexOperator(size_t idx);
        void LuaNewIndexOperator(size_t idx, float value);
    };
}

#endif