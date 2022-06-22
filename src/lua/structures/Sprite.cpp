#include "world2d/lua/structures/Sprite.h"
#include "world2d/Engine.h"

world2d::Sprite::Sprite(const char* pathtotexture) : world2d::Sprite(pathtotexture, 0, 0, -1, -1) {

}

world2d::Sprite::Sprite(const char* pathtotexture, int x) : world2d::Sprite(pathtotexture, x, 0, -1, -1) {

}

world2d::Sprite::Sprite(const char* pathtotexture, int x, int y) : world2d::Sprite(pathtotexture, x, y, -1, -1) {

}

world2d::Sprite::Sprite(const char* pathtotexture, int x, int y, int w) : world2d::Sprite(pathtotexture, x, y, w, -1) {

}

world2d::Sprite::Sprite(const char* pathtotexture, int x, int y, int w, int h) {
    mTexture = std::make_shared<world2d::Texture>(pathtotexture);

    this->x = x;
    this->y = y;

    this->w = (w < 0) ? mTexture->GetWidth() : w;
    this->h = (h < 0) ? mTexture->GetHeight() : h;
}

world2d::Sprite::Sprite(world2d::Texture& texture) : world2d::Sprite(texture, 0, 0, -1, -1) {

}

world2d::Sprite::Sprite(world2d::Texture& texture, int x) : world2d::Sprite(texture, x, 0, -1, -1) {

}

world2d::Sprite::Sprite(world2d::Texture& texture, int x, int y) : world2d::Sprite(texture, x, y, -1, -1) {

}

world2d::Sprite::Sprite(world2d::Texture& texture, int x, int y, int w) : world2d::Sprite(texture, x, y, w, -1) {

}

world2d::Sprite::Sprite(world2d::Texture& texture, int x, int y, int w, int h) {
    mTexture = std::make_shared<world2d::Texture>(texture);

    this->x = x;
    this->y = y;

    this->w = (w < 0) ? mTexture->GetWidth() : w;
    this->h = (h < 0) ? mTexture->GetHeight() : h;
}

void world2d::Sprite::Draw() {
    mTexture->Draw(this->x, this->y, this->w, this->h);
}

bool world2d::Sprite::IsCollidingWith(world2d::Sprite& target) {
    return (this->x < (target.x + target.w) &&
            (this->x + this->w) > target.x &&
            this->y < (target.y + target.h) &&
            (this->h + this->y) > target.y);
}