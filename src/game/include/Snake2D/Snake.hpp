#pragma once

#include <Snake2D/Position.hpp>

class Snake {
public:
    explicit Snake(const Position& position);

public:
    inline auto position() const -> const Position& { return position_; }

private:
    Position position_;
};
