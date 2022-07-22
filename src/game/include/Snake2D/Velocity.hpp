#pragma once

#include <chrono>

struct Velocity {
    std::size_t positions_per_second{0};

    auto ms_per_position() const -> auto { return std::chrono::milliseconds{1000} / positions_per_second; }
};
