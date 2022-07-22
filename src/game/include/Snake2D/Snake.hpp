#pragma once

#include <list>

#include <Snake2D/Position.hpp>

class Snake {
public:
    explicit Snake(const Position& position);

public:
    inline auto position() const -> const std::list<Position>& { return position_; }

private:
    std::list<Position> position_;
};
