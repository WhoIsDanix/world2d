#ifndef WORLD2D_LUA_IMGUI_STRUCTURES_INTARRAY3_H
#define WORLD2D_LUA_IMGUI_STRUCTURES_INTARRAY3_H

#include <cstddef>

namespace world2d {
    namespace ImGui {
        class IntArray3 {
        private:
            int arr[3];

        public:
            IntArray3();
            IntArray3(int v1, int v2, int v3);

            int* data();

            int LuaIndexOperator(size_t idx);
            void LuaNewIndexOperator(size_t idx, int value);
        };
    }
}

#endif