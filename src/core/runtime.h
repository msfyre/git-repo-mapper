#ifndef PROGRAM_RUNTIME
#define PROGRAM_RUNTIME

#include <array>
#include <functional>
#include <vector>

using RuntimeEventCallbackFn = std::function<void(float)>;

class Runtime {
	bool isRunning;
	
	// parameter of the func is deltatime
	std::vector<RuntimeEventCallbackFn> events; 

	public:
		float DeltaTime;

		Runtime();

		void Execute();
		void SubscribeToRuntime(RuntimeEventCallbackFn callbackfn);
};

#endif
