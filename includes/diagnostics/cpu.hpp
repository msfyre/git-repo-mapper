#ifndef PROGRAM_DIAGNOSTICS_CPU
#define PROGRAM_DIAGNOSTICS_CPU

#include <chrono>
#ifdef _WIN32
#include <windows.h>
#endif

namespace diagnostics {
namespace cpu {

struct CPUTimes {
#ifdef __linux__
    unsigned long long user, nice, system, idle, iowait, irq, softirq;
#endif
};

CPUTimes readCPUTimes();
unsigned long long total(const CPUTimes &times);
unsigned long long idle(const CPUTimes &times);
unsigned long long getProcessTimeFromPID(int pid);

#ifdef __linux__
class ProcessMonitor {
    double updateTimer;

  public:
    int pid;
    unsigned long long lastProcTime = 0;
    std::chrono::steady_clock::time_point lastTime;

    ProcessMonitor(int p);

    double GetUsagePercentage();
};
#endif

} // namespace cpu
} // namespace diagnostics

#endif
