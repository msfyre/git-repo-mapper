#include <engine/runtime.hpp>

#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>

#include <glm/ext/vector_int2.hpp>
#include <sys/types.h>

#include <cstddef>
#include <functional>
#include <vector>

#ifndef PROGRAM_RENDER
#define PROGRAM_RENDER

namespace engine {
namespace renderer {

using namespace engine::runtime;

using RenderEventCallbackFn =
    std::function<void(float runtime_dt, float render_dt)>;

struct RenderEvent {
    size_t uid;
    RenderEventCallbackFn callback;
};

class Renderer {
    std::vector<RenderEvent> events;

    size_t nextCallbackUID;

    bool isDebugMode;

    void callRender(float deltatime);

  public:
    float DeltaTime;

    SDL_Window *SDLWindow;
    SDL_GLContext SDLContext;

    glm::ivec2 ViewportSize;

    Renderer(Runtime *runtime, const char *window_name, uint w, uint h);
    void RenderText(char *text, char *font);

    RenderEvent SubscribeFunction(RenderEventCallbackFn callbackfn);
    void UnsubscribeEvent(RenderEvent event);
};

} // namespace renderer
} // namespace engine

#endif
