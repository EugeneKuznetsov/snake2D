#include "Snake2D/Snake.hpp"

#include <unordered_map>

#include "Snake2D/Playfield.hpp"

Snake::Snake(const Position& position, const Velocity& velocity /*= {2}*/)
    : position_{position}
    , direction_{Direction::invalid}
    , velocity_{velocity}
    , accept_direction_change_{true}
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

    if (accept_direction_change_ && direction != direction_ && direction != bad_directions[direction_]) {
        direction_ = direction;
        accept_direction_change_ = false;
    }
}

auto Snake::move_on(const Playfield& playfield, const std::function<bool(const Position&)> snake_can_grow_predicate /*= nullptr*/) -> void
{
    if (Direction::invalid == direction_)
        return;

    auto head = calculate_head_next_position(playfield);

    if (nullptr != snake_can_grow_predicate && true == snake_can_grow_predicate(head)) {
        position_.insert(position_.begin(), head);
    }
    else {
        auto previous_body_part_iter = position_.rbegin();
        for (auto next_body_part_iter = ++position_.rbegin(); next_body_part_iter != position_.rend(); ++next_body_part_iter) {
            *previous_body_part_iter = *next_body_part_iter;
            previous_body_part_iter = next_body_part_iter;
        }
        position_.front() = head;
    }

    accept_direction_change_ = true;
}

auto Snake::increase_velocity() -> void
{
    velocity_.positions_per_second++;
}

auto Snake::calculate_head_next_position(const Playfield& playfield) -> Position
{
    auto head = position_.front();

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

    return head;
}
