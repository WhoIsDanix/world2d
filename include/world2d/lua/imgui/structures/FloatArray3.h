#ifndef WORLD2D_LUA_IMGUI_STRUCTURES_FLOATARRAY3_H
#define WORLD2D_LUA_IMGUI_STRUCTURES_FLOATARRAY3_H

#include <cstddef>

namespace world2d {
    namespace ImGui {
        class FloatArray3 {
        private:
            float arr[3];

        public:
            FloatArray3();
            FloatArray3(float v1, float v2, float v3);

            float* data();

            float LuaIndexOperator(size_t idx);
            void LuaNewIndexOperator(size_t idx, float value);
        };
    }
}

#endif