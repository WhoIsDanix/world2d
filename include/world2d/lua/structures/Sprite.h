#ifndef WORLD2D_LUA_STRUCTURES_SPRITE_H
#define WORLD2D_LUA_STRUCTURES_SPRITE_H

#include "world2d/lua/structures/Texture.h"
#include <memory>

namespace world2d {
    class Sprite {
    public:
        std::shared_ptr<world2d::Texture> mTexture;
        int x = 0, y = 0, w = 0, h = 0;

        Sprite(const char* pathtotexture);
        Sprite(const char* pathtotexture, int x);
        Sprite(const char* pathtotexture, int x, int y);
        Sprite(const char* pathtotexture, int x, int y, int w);
        Sprite(const char* pathtotexture, int x, int y, int w, int h);

        Sprite(world2d::Texture& texture);
        Sprite(world2d::Texture& texture, int x);
        Sprite(world2d::Texture& texture, int x, int y);
        Sprite(world2d::Texture& texture, int x, int y, int w);
        Sprite(world2d::Texture& texture, int x, int y, int w, int h);

        void Draw();
        bool IsCollidingWith(world2d::Sprite& target);
    };
}

#endif