#ifndef WORLD2D_LUA_STRUCTURES_IMGUIBOOL_H
#define WORLD2D_LUA_STRUCTURES_IMGUIBOOL_H

namespace world2d {
    struct ImGuiBool {
    public:
        bool value = false;

        ImGuiBool();
        ImGuiBool(bool _value);
    };
}

#endif