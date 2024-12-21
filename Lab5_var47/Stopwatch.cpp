
#include <chrono>

class Stopwatch {
public:
    void Start() {
        m_startTime = std::chrono::high_resolution_clock::now();
    }

    void Stop() {
        m_endTime = std::chrono::high_resolution_clock::now();
    }

    double Time() {
        std::chrono::duration<double> duration = m_endTime - m_startTime;
        m_elapsedTime += duration.count();
        return m_elapsedTime;
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_startTime, m_endTime;
    double m_elapsedTime;
};