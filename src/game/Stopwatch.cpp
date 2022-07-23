#include "Snake2D/Stopwatch.hpp"

auto Stopwatch::elapsed() const -> std::chrono::milliseconds
{
    const auto current = std::chrono::high_resolution_clock::now().time_since_epoch();
    return std::chrono::duration_cast<std::chrono::milliseconds>(current - lap_start_);
}

auto Stopwatch::start() -> void
{
    lap(std::chrono::milliseconds::zero());
    running_ = true;
}

auto Stopwatch::lap(const std::chrono::milliseconds& lag /*= std::chrono::milliseconds::zero()*/) -> void
{
    const auto current = std::chrono::high_resolution_clock::now().time_since_epoch();
    lap_start_ = std::chrono::duration_cast<std::chrono::milliseconds>(current - lag);
}
