#ifndef WORLD2D_LUA_STRUCTURES_IMGUISTYLECOLORS_H
#define WORLD2D_LUA_STRUCTURES_IMGUISTYLECOLORS_H

#include "imgui/imgui.h"

namespace world2d {
    class ImGuiStyleColors {
    private:
        ImVec4* mColors;
    
    public:
        ImGuiStyleColors(ImVec4* colors);

        ImVec4 LuaIndexOperator(size_t idx);
        void LuaNewIndexOperator(size_t idx, ImVec4 value);
    };
}

#endif