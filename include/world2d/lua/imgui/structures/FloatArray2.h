#ifndef WORLD2D_LUA_IMGUI_STRUCTURES_FLOATARRAY2_H
#define WORLD2D_LUA_IMGUI_STRUCTURES_FLOATARRAY2_H

#include <cstddef>

namespace world2d {
    namespace ImGui {
        class FloatArray2 {
        private:
            float arr[2];

        public:
            FloatArray2();
            FloatArray2(float v1, float v2);

            float* data();

            float LuaIndexOperator(size_t idx);
            void LuaNewIndexOperator(size_t idx, float value);
        };
    }
}

#endif