#include "Snake2D/Snake.hpp"

#include <unordered_map>

#include "Snake2D/Playfield.hpp"

Snake::Snake(const Position& position)
    : position_{position}
    , direction_{Direction::invalid}
{
    position_.emplace_back(Position{position.row, static_cast<short>(position.col + 1)});
    position_.emplace_back(Position{position.row, static_cast<short>(position.col + 2)});
}

auto Snake::direction(const Direction& direction) -> void
{
    static std::unordered_map<Direction, Direction> bad_directions = {{Direction::left, Direction::right},
                                                                      {Direction::up, Direction::down},
                                                                      {Direction::right, Direction::left},
                                                                      {Direction::down, Direction::up}};
    if (Direction::invalid == direction_) {
        const auto& head = *position_.cbegin();
        const auto& torso = *++position_.cbegin();

        const auto head_torso_diff_x = head.col - torso.col;
        const auto head_torso_diff_y = head.row - torso.row;
        if (head_torso_diff_x > 0 && direction == bad_directions[Direction::right])
            return;
        else if (head_torso_diff_x < 0 && direction == bad_directions[Direction::left])
            return;
        else if (head_torso_diff_y > 0 && direction == bad_directions[Direction::down])
            return;
        else if (head_torso_diff_y < 0 && direction == bad_directions[Direction::up])
            return;
    }

    if (direction != direction_ && direction != bad_directions[direction_])
        direction_ = direction;
}

auto Snake::move_on(const Playfield& playfield) -> void
{
    if (Direction::invalid == direction_)
        return;

    auto previous_iter = position_.rbegin();
    for (auto iter = ++position_.rbegin(); iter != position_.rend(); ++iter) {
        *previous_iter = *iter;
        previous_iter = iter;
    }

    auto& head = position_.front();
    switch (direction_) {
        case Direction::left:
            --head.col;
            if (0 == head.col)
                head.col = playfield.cols;
            break;
        case Direction::up:
            --head.row;
            if (0 == head.row)
                head.row = playfield.rows;
            break;
        case Direction::right:
            ++head.col;
            if (playfield.cols < head.col)
                head.col = 1;
            break;
        case Direction::down:
            ++head.row;
            if (playfield.rows < head.row)
                head.row = 1;
            break;
        default:
            break;
    }
}
