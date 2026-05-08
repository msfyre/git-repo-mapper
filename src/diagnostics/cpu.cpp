#include <chrono>
#include <fstream>
#include <string>

#include <diagnostics/cpu.hpp>
#include <unistd.h>

using namespace diagnostics;

cpu::CPUTimes cpu::readCPUTimes() {
    std::ifstream file("/proc/stat");
    std::string cpu;

    CPUTimes times{};

    file >> cpu >> times.user >> times.nice >> times.system >> times.idle >>
        times.iowait >> times.irq >> times.softirq;

    return times;
}

unsigned long long cpu::total(const CPUTimes &times) {
    return times.user + times.nice + times.system + times.idle + times.iowait +
           times.irq + times.softirq;
}

unsigned long long cpu::idle(const CPUTimes &times) {
    return times.idle + times.iowait;
}

unsigned long long cpu::getProcessTimeFromPID(int pid) {
    std::ifstream file("/proc/" + std::to_string(pid) + "/stat");
    std::string ignore;

    unsigned long long utime, stime;

    for (int i = 0; i < 13; i++) {
        file >> ignore;
    }

    file >> utime >> stime;

    return utime + stime;
}

cpu::ProcessMonitor::ProcessMonitor(int pid) : pid(pid) {
    lastProcTime = getProcessTimeFromPID(pid);
    lastTime = std::chrono::steady_clock::now();
}

double cpu::ProcessMonitor::GetUsagePercentage() {
    auto now = std::chrono::steady_clock::now();

    unsigned long long procNow = getProcessTimeFromPID(pid);

    double elapsedSec = std::chrono::duration<double>(now - lastTime).count();

    unsigned long long procDelta = procNow - lastProcTime;

    lastProcTime = procNow;
    lastTime = now;

    double tickPerSecond = sysconf(_SC_CLK_TCK);
    double procSec = procDelta / tickPerSecond;

    int cores = sysconf(_SC_NPROCESSORS_ONLN);

    if (elapsedSec <= 0.0)
        return 0.0;

    return (procSec / elapsedSec) * 100.0 / cores;
}
