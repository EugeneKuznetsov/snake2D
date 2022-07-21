#pragma once

#include <Snake2D/Position.hpp>

class Snake {
public:
    inline auto position() const -> const Position& { return position_; }

private:
    Position position_;
};
