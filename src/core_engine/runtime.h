#include <SDL3/SDL_events.h>
#include <array>
#include <cstddef>
#include <functional>
#include <unordered_set>
#include <vector>

#ifndef PROGRAM_RUNTIME
#define PROGRAM_RUNTIME

using RuntimeEventCallbackFn = std::function<void(float runtime_dt, SDL_Event event)>;

struct RuntimeEvent
{
    size_t uid;
    RuntimeEventCallbackFn callback;
};

class Runtime
{
    size_t nextCallbackFnUID;
    bool isRunning;
    float frameDelayMS;

    std::vector<RuntimeEvent> events;

  public:
    float DeltaTime;

    Runtime(size_t fps_cap);

    void Execute();
    RuntimeEvent SubscribeFunction(RuntimeEventCallbackFn callbackfn);
    void UnsubscribeFunction(RuntimeEvent event);
};

#endif
