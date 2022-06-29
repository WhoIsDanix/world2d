#ifndef WORLD2D_LUA_IMGUI_STRUCTURES_STYLECOLORS_H
#define WORLD2D_LUA_IMGUI_STRUCTURES_STYLECOLORS_H

#include "imgui/imgui.h"

namespace world2d {
    namespace ImGui {
        class StyleColors {
        private:
            ImVec4* mColors;
        
        public:
            StyleColors(ImVec4* colors);

            ImVec4 LuaIndexOperator(size_t idx);
            void LuaNewIndexOperator(size_t idx, ImVec4 value);
        };
    }
}

#endif