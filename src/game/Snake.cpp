#include "Snake2D/Snake.hpp"

#include "Snake2D/Playfield.hpp"

Snake::Snake(const Position& position)
    : position_{position}
    , direction_{Direction::invalid}
{
    position_.emplace_back(Position{position.row, static_cast<unsigned short>(position.col + 1u)});
    position_.emplace_back(Position{position.row, static_cast<unsigned short>(position.col + 2u)});
}

auto Snake::direction(const Direction& direction) -> void
{
    direction_ = direction;
}

auto Snake::move(const Playfield& /*playfield*/) -> void {}
