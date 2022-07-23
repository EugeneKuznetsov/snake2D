#pragma once

#include <list>

#include <Snake2D/Position.hpp>

class PositionGenerator {
public:
    auto boundaries(const Position& minimum, const Position& maximum) -> void;

public:
    virtual auto generate(const std::list<Position>& exclude = {}) const -> Position;

private:
    auto generate_random_number(const std::size_t& minimum, const std::size_t& maximum) const -> std::size_t;
    auto index(const Position& position) const -> std::size_t;

private:
    Position minimum_{0, 0};
    Position maximum_{0, 0};
    const Position invalid_position_{-1, -1};
};
