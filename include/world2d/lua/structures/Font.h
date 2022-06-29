#ifndef WORLD2D_LUA_STRUCTURES_FONT_H
#define WORLD2D_LUA_STRUCTURES_FONT_H

#include "SDL/SDL_FontCache.h"
#include <tuple>

namespace world2d {
    class Font {
    private:
        FC_Font* mFont = nullptr;

    public:
        Font(const char* pathToFont, int fontSize);
        ~Font();

        void Draw(const char* text, int x, int y);
        void Draw(const char* text, int x, int y, int w, int h);

        std::tuple<int, int> GetTextSize(const char* text);
    };
}

#endif