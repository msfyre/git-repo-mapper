#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_video.h>

#include <engine/renderer.hpp>
#include <engine/runtime.hpp>

#include <chrono>

#include <GL/gl.h>
#include <sys/types.h>

using namespace engine::runtime;
using namespace engine::renderer;

Renderer::Renderer(Runtime *runtime, const char *window_name, uint w, uint h) {
    DeltaTime = 0;

    ViewportSize.x = w;
    ViewportSize.y = h;

    SDLWindow = SDL_CreateWindow(window_name, w, h, SDL_WINDOW_OPENGL);
    SDLContext = SDL_GL_CreateContext(SDLWindow);

    SDL_GL_MakeCurrent(SDLWindow, SDLContext);

    RuntimeEventCallbackFn call_render_lambda = [this](float runtime_dt,
                                                       SDL_Event sdl_event) {
        this->callRender(runtime_dt);
    };

    runtime->SubscribeFunction(call_render_lambda);
}

void Renderer::callRender(float runtime_dt) {
    auto prevtime = std::chrono::high_resolution_clock::now();

    glViewport(0, 0, this->ViewportSize.x, this->ViewportSize.y);
    glClear(GL_COLOR_BUFFER_BIT);

    for (RenderEvent event : events) {
        event.callback(runtime_dt, DeltaTime);
    }

    SDL_GL_SwapWindow(SDLWindow);

    auto currtime = std::chrono::high_resolution_clock::now();

    DeltaTime = std::chrono::duration<float>(currtime - prevtime).count();
}

RenderEvent Renderer::SubscribeFunction(RenderEventCallbackFn callbackfn) {
    RenderEvent event = {
        .uid = nextCallbackUID++,
        .callback = callbackfn,
    };

    events.push_back(event);

    return event;
}

void Renderer::UnsubscribeEvent(RenderEvent event) {
    events.erase(events.begin() + event.uid);
}
