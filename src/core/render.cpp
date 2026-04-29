#include "render.h"
#include "runtime.h"
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <chrono>

Renderer::Renderer(Runtime* runtime, const char *window_name, int w, int h, float fps_cap) {
	DeltaTime = 0;
	frameTimerMax = 1 / fps_cap;

	SDL_Window* window = SDL_CreateWindow(window_name, w, h, 0);
	SDLRenderer = SDL_CreateRenderer(window, nullptr);

	RuntimeEventCallbackFn call_render_lambda = [this](float runtime_dt) {
		this -> callrender(runtime_dt);
	};

	runtime -> SubscribeToRuntime(call_render_lambda);
}


void Renderer::callrender(float runtime_dt) {
	if (frameTimerCurrent > 0) {
		frameTimerCurrent -= runtime_dt;
		return;
	}

	auto prevtime = std::chrono::high_resolution_clock::now();

	for (RenderEventCallbackFn& callback : events) {
		callback(this->SDLRenderer, DeltaTime);
	}

	SDL_RenderPresent(SDLRenderer);

	auto currtime = std::chrono::high_resolution_clock::now();

	std::chrono::duration<float> duration_delta = currtime - prevtime;

	DeltaTime = duration_delta.count();

	frameTimerCurrent = frameTimerMax;
}

void Renderer::SubscribeFunction(RenderEventCallbackFn callbackfn) {
	events.insert(events.begin(), callbackfn);
}
