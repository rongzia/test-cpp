//
// Created by rrzhang on 2019/9/10.
//

#ifndef TEST_SOCKET_PROFILER_H
#define TEST_SOCKET_PROFILER_H

#include <chrono>

class Profiler {
public:
    //! Starts the timer
    void Start() {
        finished = false;
        start = Tick();
    }
    //! Finishes timing
    void End() {
        end = Tick();
        finished = true;
    }

    //! Returns the elapsed time in seconds. If End() has been called, returns
    //! the total elapsed time. Otherwise returns how far along the timer is
    //! right now.
    double Elapsed() const {
        auto _end = finished ? end : Tick();
        return std::chrono::duration_cast<std::chrono::duration<double>>(_end - start).count();
    }

private:
    std::chrono::time_point<std::chrono::system_clock> Tick() const {
        return std::chrono::system_clock::now();
    }
    std::chrono::time_point<std::chrono::system_clock> start;
    std::chrono::time_point<std::chrono::system_clock> end;
    bool finished = false;
};

#endif //TEST_SOCKET_PROFILER_H
