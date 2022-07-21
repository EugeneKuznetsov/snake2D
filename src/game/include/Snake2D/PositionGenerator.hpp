#pragma once

#include <Snake2D/Position.hpp>

class PositionGenerator {
public:
    auto boundaries(const Position minimum, const Position maximum) -> void;

public:
    virtual auto generate() const -> Position;

private:
    auto generate_random_number(const unsigned short minimum, const unsigned short maximum) const -> unsigned short;

private:
    Position minimum_{0u, 0u};
    Position maximum_{0u, 0u};
};
