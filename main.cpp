#include "world2d/Engine.h"

int main(int argc, char* args[]) {
    world2d::Engine* engine = world2d::Engine::Get();
    engine->LoadModules();

    bool compiled = engine->CompileAndRun((argc >= 2) ? args[1] : "./nogame.lua");

    if (!compiled) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to compile");
        return -1;
    }

    return 0;
}
