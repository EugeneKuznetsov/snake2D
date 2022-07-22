#pragma once

#include <Snake2D/Position.hpp>

class PositionGenerator {
public:
    auto boundaries(const Position& minimum, const Position& maximum) -> void;

public:
    virtual auto generate() const -> Position;

private:
    auto generate_random_number(const short minimum, const short maximum) const -> short;

private:
    Position minimum_{0, 0};
    Position maximum_{0, 0};
};
