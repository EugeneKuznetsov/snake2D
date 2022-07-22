#pragma once

#include <chrono>

class Stopwatch {
public:
    inline auto running() const -> const bool& { return running_; };
    auto elapsed() const -> std::chrono::milliseconds;

public:
    auto start() -> void;
    auto lap(const std::chrono::milliseconds& lag) -> void;

private:
    bool running_{false};
    std::chrono::milliseconds lap_start_{std::chrono::milliseconds::zero()};
};
