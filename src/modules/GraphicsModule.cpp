#include "world2d/modules/GraphicsModule.h"

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

#include "world2d/lua/enums/DrawMode.h"

#include "world2d/lua/structures/Texture.h"
#include "world2d/lua/structures/Sprite.h"
#include "world2d/lua/structures/Font.h"

#include <cmath>
#include <tuple>

world2d::GraphicsModule::GraphicsModule() : world2d::Module() {

}

world2d::GraphicsModule::~GraphicsModule() {
    IMG_Quit();
    TTF_Quit();
}

bool world2d::GraphicsModule::Initialize() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize SDL (video subsystem): %s", SDL_GetError());
        return false;
    }

    int flags = IMG_INIT_PNG;
    if ((IMG_Init(flags) & flags) != flags) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize SDL image: %s", IMG_GetError());
        return false;
    }

    if (TTF_Init() != 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize SDL TTF: %s", TTF_GetError());
        return false;
    }

    sol::state& luaState = mEngine->GetLua();
    sol::table luaWorld2dNamespace = luaState.get<sol::table>("world2d");

    // ===== Main callbacks =====
    luaWorld2dNamespace.set_function("Init", []() {});
    luaWorld2dNamespace.set_function("Update", []() {});
    luaWorld2dNamespace.set_function("Render", []() {});
    // ==========================

    sol::table luaGraphicsNamespace { luaState.create_table() };

    // ===== Structures =====
    luaGraphicsNamespace.new_usertype<world2d::Texture>("Texture",
        sol::constructors<world2d::Texture(const char*)>(),

        "w",
        sol::property([&](world2d::Texture self) {
            return self.GetWidth();
        }),

        "h",
        sol::property([&](world2d::Texture self) {
            return self.GetHeight();
        })
    );

    luaGraphicsNamespace.new_usertype<world2d::Sprite>("Sprite",
        sol::constructors<
            world2d::Sprite(const char*),
            world2d::Sprite(const char*, int),
            world2d::Sprite(const char*, int, int),
            world2d::Sprite(const char*, int, int, int),
            world2d::Sprite(const char*, int, int, int, int),

            world2d::Sprite(world2d::Texture&),
            world2d::Sprite(world2d::Texture&, int),
            world2d::Sprite(world2d::Texture&, int, int),
            world2d::Sprite(world2d::Texture&, int, int, int),
            world2d::Sprite(world2d::Texture&, int, int, int, int)
        >(),

        "x",
        &world2d::Sprite::x,

        "y",
        &world2d::Sprite::y,

        "w",
        &world2d::Sprite::w,

        "h",
        &world2d::Sprite::h,

        "IsCollidingWith",
        &world2d::Sprite::IsCollidingWith
    );

    luaGraphicsNamespace.new_usertype<world2d::Font>("Font",
        sol::constructors<world2d::Font(const char*, int)>(),
        "GetTextSize", &world2d::Font::GetTextSize
    );
    // ======================

    // ===== Enums =====
    luaGraphicsNamespace.new_enum("DrawMode",
        "Fill", DrawMode_Fill,
        "Line", DrawMode_Line
    );
    // =================

    // ===== Functions =====
    luaGraphicsNamespace.set_function("SetDrawColor", [&](int r, int g, int b, int a) {
        SDL_SetRenderDrawColor(mEngine->GetSDLRenderer(), r, g, b, a);
    });

    luaGraphicsNamespace.set_function("GetDrawColor", [&]() {
        Uint8 r, g, b, a;
        SDL_GetRenderDrawColor(mEngine->GetSDLRenderer(), &r, &g, &b, &a);
        return std::make_tuple(r, g, b, a);
    });

    luaGraphicsNamespace.set_function("Clear", [&]() {
        SDL_RenderClear(mEngine->GetSDLRenderer());
    });

    luaGraphicsNamespace.set_function("DrawLine", [&](int x1, int y1, int x2, int y2) {
        SDL_RenderDrawLine(mEngine->GetSDLRenderer(), x1, y1, x2, y2);
    });

    luaGraphicsNamespace.set_function("DrawPoint", [&](int x, int y) {
        SDL_RenderDrawPoint(mEngine->GetSDLRenderer(), x, y);
    });

    luaGraphicsNamespace.set_function("DrawRect", [&](DrawMode drawMode, int x, int y, int w, int h) {
        SDL_Rect rect { x, y, w, h };

        if (drawMode == DrawMode_Fill) {
            SDL_RenderFillRect(mEngine->GetSDLRenderer(), &rect);
        } else {
            SDL_RenderDrawRect(mEngine->GetSDLRenderer(), &rect);
        }
    });

    luaGraphicsNamespace.set_function("DrawCircle", [&](DrawMode drawMode, int x0, int y0, int radius) {
        // Credits to: https://gist.github.com/derofim/912cfc9161269336f722
        SDL_Renderer* renderer = mEngine->GetSDLRenderer();

        if (drawMode == DrawMode_Fill) {
            static const int BPP = 4;

            for (double dy = 1; dy <= radius; dy += 1.0) {
                double dx = std::floor(std::sqrt((2.0 * radius * dy) - (dy * dy)));
                int x = x0 - dx;

                SDL_RenderDrawLine(renderer, x0 - dx, y0 + dy - radius, x0 + dx, y0 + dy - radius);
                SDL_RenderDrawLine(renderer, x0 - dx, y0 - dy + radius, x0 + dx, y0 - dy + radius);
            }
        } else {
            double error = (double)-radius;
            double x = (double)radius - 0.5;
            double y = (double)0.5;
            double cx = x0 - 0.5;
            double cy = y0 - 0.5;

            while (x >= y) {
                SDL_RenderDrawPoint(renderer, cx + x, cy + y);
                SDL_RenderDrawPoint(renderer, cx + y, cy + x);

                if (x != 0) {
                    SDL_RenderDrawPoint(renderer, cx - x, cy + y);
                    SDL_RenderDrawPoint(renderer, cx + y, cy - x);
                }

                if (y != 0) {
                    SDL_RenderDrawPoint(renderer, cx + x, cy - y);
                    SDL_RenderDrawPoint(renderer, cx - y, cy + x);
                }

                if (x != 0 && y != 0) {
                    SDL_RenderDrawPoint(renderer, cx - x, cy - y);
                    SDL_RenderDrawPoint(renderer, cx - y, cy - x);
                }

                error += y;
                ++y;
                error += y;

                if (error >= 0) {
                    --x;
                    error -= x;
                    error -= x;
                }
            }
        }
    });

    luaGraphicsNamespace.set_function("Draw", sol::overload(
        [&](world2d::Texture& texture) {
            texture.Draw();
        },

        [&](world2d::Texture& texture, int x, int y) {
            texture.Draw(x, y);
        },

        [&](world2d::Texture& texture, int x, int y, int w, int h) {
            texture.Draw(x, y, w, h);
        },

        [&](world2d::Sprite& sprite) {
            sprite.Draw();
        },

        [&](world2d::Font& font, const char* text, int x, int y) {
            font.Draw(text, x, y);
        },

        [&](world2d::Font& font, const char* text, int x, int y, int w, int h) {
            font.Draw(text, x, y, w, h);
        }
    ));
    // =====================

    luaWorld2dNamespace["Graphics"] = luaGraphicsNamespace;

    return true;
}

void world2d::GraphicsModule::BeforeRun() {
    mEngine->GetLua().get<sol::table>("world2d").get<sol::function>("Init")();
}

void world2d::GraphicsModule::Update(double deltaTime) {
    mEngine->GetLua().get<sol::table>("world2d").get<sol::function>("Update")(deltaTime);
}

void world2d::GraphicsModule::Render() {
    SDL_SetRenderDrawColor(mEngine->GetSDLRenderer(), 255, 255, 255, 255);
    mEngine->GetLua().get<sol::table>("world2d").get<sol::function>("Render")();
}

world2d::GraphicsModule* world2d::GraphicsModule::Get() {
    static world2d::GraphicsModule currentModule;
    return &currentModule;
}