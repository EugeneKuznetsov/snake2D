#pragma once

#include <list>

#include <Snake2D/Position.hpp>
#include <Snake2D/Direction.hpp>

struct Playfield;

class Snake {
public:
    explicit Snake(const Position& position);

public:
    auto direction(const Direction& direction) -> void;

public:
    inline auto position() const -> const std::list<Position>& { return position_; }

public:
    auto move(const Playfield& playfield) -> void;

private:
    std::list<Position> position_;
    Direction direction_;
};
