#ifndef WORLD2D_LUA_IMGUI_STRUCTURES_STRING_H
#define WORLD2D_LUA_IMGUI_STRUCTURES_STRING_H

#include <string>

namespace world2d {
    namespace ImGui {
        class String {
        public:
            std::string value = "";

            String();
            String(std::string newvalue);
        };
    }
}

#endif