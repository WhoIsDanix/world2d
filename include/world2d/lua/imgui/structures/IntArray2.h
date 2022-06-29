#ifndef WORLD2D_LUA_IMGUI_STRUCTURES_INTARRAY2_H
#define WORLD2D_LUA_IMGUI_STRUCTURES_INTARRAY2_H

#include <cstddef>

namespace world2d {
    namespace ImGui {
        class IntArray2 {
        private:
            int arr[2];

        public:
            IntArray2();
            IntArray2(int v1, int v2);

            int* data();

            int LuaIndexOperator(size_t idx);
            void LuaNewIndexOperator(size_t idx, int value);
        };
    }
}

#endif