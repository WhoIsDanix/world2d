#ifndef WORLD2D_LUA_STRUCTURES_IMGUIFLOATARRAY4_H
#define WORLD2D_LUA_STRUCTURES_IMGUIFLOATARRAY4_H

#include <cstddef>

namespace world2d {
    class ImGuiFloatArray4 {
    private:
        float arr[4];

    public:
        ImGuiFloatArray4();
        ImGuiFloatArray4(float v1, float v2, float v3, float v4);

        float* data();

        float LuaIndexOperator(size_t idx);
        void LuaNewIndexOperator(size_t idx, float value);
    };
}

#endif