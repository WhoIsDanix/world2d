#ifndef WORLD2D_LUA_IMGUI_WIDGET_H
#define WORLD2D_LUA_IMGUI_WIDGET_H

#include "sol/sol.hpp"

namespace world2d {
    namespace ImGui {
        class Widget {
        public:
            virtual void SetLuaEnvironment(sol::table& luaImGuiNamespace) = 0;
        };
    }
}

#endif