#ifndef WORLD2D_LUA_IMGUI_STRUCTURES_FLOAT_H
#define WORLD2D_LUA_IMGUI_STRUCTURES_FLOAT_H

namespace world2d {
    namespace ImGui {
        struct Float {
        public:
            float value = 0.0f;

            Float();
            Float(float _value);
        };
    }
}

#endif