#include "world2d/Module.h"

world2d::Module::Module() {
    mEngine = world2d::Engine::Get();
}

bool world2d::Module::Initialize() {
    return true;
}

void world2d::Module::BeforeRun() {

}

void world2d::Module::OnEvent(SDL_Event& event) {

}

void world2d::Module::Update(double deltaTime) {

}

void world2d::Module::Render() {

}