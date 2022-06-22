#ifndef WORLD2D_LUA_STRUCTURES_IMGUIFLOAT_H
#define WORLD2D_LUA_STRUCTURES_IMGUIFLOAT_H

namespace world2d {
    struct ImGuiFloat {
    public:
        float value = 0.0f;

        ImGuiFloat();
        ImGuiFloat(float _value);
    };
}

#endif