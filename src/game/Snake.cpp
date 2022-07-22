#include "Snake2D/Snake.hpp"

Snake::Snake(const Position& position)
    : position_{position}
{
    position_.emplace_back(Position{position.row, static_cast<unsigned short>(position.col + 1u)});
    position_.emplace_back(Position{position.row, static_cast<unsigned short>(position.col + 2u)});
}
