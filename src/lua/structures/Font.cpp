#include "world2d/lua/structures/Font.h"
#include "world2d/Engine.h"

world2d::Font::Font(const char* pathToFont, int fontSize) {
    mFont = FC_CreateFont();
    FC_LoadFont(mFont, world2d::Engine::Get()->GetSDLRenderer(), pathToFont, fontSize, FC_MakeColor(255, 255, 255, 255), TTF_STYLE_NORMAL);

    if (mFont == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load TTF font: %s", TTF_GetError());
    }
}

world2d::Font::~Font() {
    FC_FreeFont(mFont);
    mFont = nullptr;
}

void world2d::Font::Draw(const char* text, int x, int y) {
    Draw(text, x, y, FC_GetWidth(mFont, text), FC_GetHeight(mFont, text));
}

void world2d::Font::Draw(const char* text, int x, int y, int w, int h) {
    FC_DrawBox(mFont, world2d::Engine::Get()->GetSDLRenderer(), FC_MakeRect(x, y, w, h), text);
}

std::tuple<int, int> world2d::Font::GetTextSize(const char* text) {
    return std::make_tuple(
        FC_GetWidth(mFont, text),
        FC_GetHeight(mFont, text)
    );
}