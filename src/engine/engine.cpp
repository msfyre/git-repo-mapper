#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>

#include <engine/engine.h>
#include <engine/renderer.h>
#include <engine/runtime.h>

#include <string>

using namespace engine;

bool Engine::IsDebug = false;

Runtime *Engine::ProgramRuntime = nullptr;
Renderer *Engine::ProgramRenderer = nullptr;

// so far this only renders the fps counter
// lols
void render_debug_information(SDL_Renderer *renderer, float runtime_dt,
                              float render_dt) {
    std::string fps_string = std::to_string(1.0 / runtime_dt);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDebugText(
        renderer, 5, 5,
        ((std::string) "DEBUG MODE: " + (Engine::IsDebug ? "TRUE" : "FALSE"))
            .c_str());
    SDL_RenderDebugText(renderer, 5, 15,
                        ((std::string) "FPS: " + fps_string).c_str());
}

void Engine::Run(const char *program_name, size_t max_fps) {
    Engine::ProgramRuntime = new Runtime(max_fps);
    Engine::ProgramRenderer =
        new Renderer(Engine::ProgramRuntime, program_name, 640, 480);

    Engine::ProgramRenderer->SubscribeFunction(
        [](SDL_Renderer *renderer, float runtime_dt, float render_dt) {
            if (Engine::IsDebug) {
                render_debug_information(renderer, runtime_dt, render_dt);
            }
        });

    ProgramRuntime->Execute();
}
