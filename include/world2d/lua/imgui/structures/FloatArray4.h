#ifndef WORLD2D_LUA_IMGUI_STRUCTURES_FLOATARRAY4_H
#define WORLD2D_LUA_IMGUI_STRUCTURES_FLOATARRAY4_H

#include <cstddef>

namespace world2d {
    namespace ImGui {
        class FloatArray4 {
        private:
            float arr[4];

        public:
            FloatArray4();
            FloatArray4(float v1, float v2, float v3, float v4);

            float* data();

            float LuaIndexOperator(size_t idx);
            void LuaNewIndexOperator(size_t idx, float value);
        };
    }
}

#endif