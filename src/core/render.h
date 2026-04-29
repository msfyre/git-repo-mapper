#include "runtime.h"
#include <SDL3/SDL_render.h>
#include <functional>
#include <vector>

#ifndef PROGRAM_RENDER
#define PROGRAM_RENDER

using RenderEventCallbackFn = std::function<void(SDL_Renderer* renderer, float deltatime)>;

class Renderer {
	float frameTimerMax;
	float frameTimerCurrent;

	std::vector<RenderEventCallbackFn> events;

	bool isDebugMode;

	void callrender(float deltatime);

	public:
		float DeltaTime;

		SDL_Renderer* SDLRenderer;

		Renderer(Runtime* runtime, const char *window_name, int w, int h, float fps_cap);
		void SubscribeFunction(RenderEventCallbackFn callbackfn);
};

#endif
