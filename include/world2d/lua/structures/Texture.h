#ifndef WORLD2D_LUA_STRUCTURES_TEXTURE_H
#define WORLD2D_LUA_STRUCTURES_TEXTURE_H

#include "SDL/SDL.h"

namespace world2d {
    class Texture {
    private:
        SDL_Texture* mSDLTexture = nullptr;

    public:
        Texture();
        Texture(const char* filename);

        ~Texture();

        void Draw();
        void Draw(int x, int y);
        void Draw(int x, int y, int w, int h);

        SDL_Texture* GetSDLTexture() const;
        int GetWidth() const;
        int GetHeight() const;
    };
}

#endif