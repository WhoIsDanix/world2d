#ifndef WORLD2D_LUA_IMGUI_STRUCTURES_INTARRAY4_H
#define WORLD2D_LUA_IMGUI_STRUCTURES_INTARRAY4_H

#include <cstddef>

namespace world2d {
    namespace ImGui {
    class IntArray4 {
        private:
            int arr[4];

        public:
            IntArray4();
            IntArray4(int v1, int v2, int v3, int v4);

            int* data();

            int LuaIndexOperator(size_t idx);
            void LuaNewIndexOperator(size_t idx, int value);
        };
    }
}

#endif