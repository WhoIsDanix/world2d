#include "world2d/lua/structures/Texture.h"
#include "world2d/Engine.h"

#include "SDL/SDL_image.h"

world2d::Texture::Texture() {
    // mSDLTexture is nullptr
}

world2d::Texture::Texture(const char* filename) {
    mSDLTexture = IMG_LoadTexture(world2d::Engine::Get()->GetSDLRenderer(), filename);

    if (mSDLTexture == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load texture: %s", IMG_GetError());
    }
}

world2d::Texture::~Texture() {
    SDL_DestroyTexture(mSDLTexture);
}

void world2d::Texture::Draw() {
    SDL_RenderCopy(world2d::Engine::Get()->GetSDLRenderer(), mSDLTexture, nullptr, nullptr);
}

void world2d::Texture::Draw(int x, int y) {
    SDL_Rect rect { x, y, GetWidth(), GetHeight() };
    SDL_RenderCopy(world2d::Engine::Get()->GetSDLRenderer(), mSDLTexture, nullptr, &rect);
}

void world2d::Texture::Draw(int x, int y, int w, int h) {
    SDL_Rect rect { x, y, w, h };
    SDL_RenderCopy(world2d::Engine::Get()->GetSDLRenderer(), mSDLTexture, nullptr, &rect);
}

SDL_Texture* world2d::Texture::GetSDLTexture() const {
    return mSDLTexture;
}

int world2d::Texture::GetWidth() const {
    int width = 0;
    SDL_QueryTexture(mSDLTexture, nullptr, nullptr, &width, nullptr);
    return width;
}

int world2d::Texture::GetHeight() const {
    int height = 0;
    SDL_QueryTexture(mSDLTexture, nullptr, nullptr, nullptr, &height);
    return height;
}