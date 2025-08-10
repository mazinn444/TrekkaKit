#pragma once
#include <chrono>
#include <functional>
#include <algorithm>

namespace Trekka {

using namespace std::chrono;

class Timer {
private:
    steady_clock::time_point start;
    int durationMs = 0;
    bool running = false;
    bool looping = false;
    std::function<void()> callback = nullptr;

public:
    void startTimer(int ms, std::function<void()> cb = nullptr, bool repeat = false) {
        durationMs = ms;
        start = steady_clock::now();
        running = true;
        looping = repeat;
        callback = cb;
    }

    bool isDone() {
        if (!running) return false;

        auto now = steady_clock::now();
        int elapsed = duration_cast<milliseconds>(now - start).count();

        if (elapsed >= durationMs) {
            if (callback) callback();
            if (looping) start = steady_clock::now();
            else running = false;
            return true;
        }
        return false;
    }

    void reset() {
        running = false;
        callback = nullptr;
    }

    bool isRunning() const { return running; }
    bool isLooping() const { return looping; }
    int getDurationMs() const { return durationMs; }

    int getRemainingMs() const {
        if (!running) return 0;

        auto now = steady_clock::now();
        int elapsed = duration_cast<milliseconds>(now - start).count();
        return std::max(0, durationMs - elapsed);
    }
};

} // namespace Trekka
