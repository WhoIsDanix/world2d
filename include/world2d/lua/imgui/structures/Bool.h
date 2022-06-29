#ifndef WORLD2D_LUA_IMGUI_STRUCTURES_BOOL_H
#define WORLD2D_LUA_IMGUI_STRUCTURES_BOOL_H

namespace world2d {
    namespace ImGui {
        struct Bool {
        public:
            bool value = false;

            Bool();
            Bool(bool _value);
        };
    }
}

#endif