#ifndef WORLD2D_LUA_STRUCTURES_IMGUIFLOATARRAY3_H
#define WORLD2D_LUA_STRUCTURES_IMGUIFLOATARRAY3_H

#include <cstddef>

namespace world2d {
    class ImGuiFloatArray3 {
    private:
        float arr[3];

    public:
        ImGuiFloatArray3();
        ImGuiFloatArray3(float v1, float v2, float v3);

        float* data();

        float LuaIndexOperator(size_t idx);
        void LuaNewIndexOperator(size_t idx, float value);
    };
}

#endif