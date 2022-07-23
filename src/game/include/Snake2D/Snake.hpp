#pragma once

#include <functional>
#include <list>

#include <Snake2D/Position.hpp>
#include <Snake2D/Velocity.hpp>
#include <Snake2D/Direction.hpp>

struct Playfield;

class Snake {
public:
    explicit Snake(const Position& position, const Velocity& velocity = {2});

public:
    auto direction(const Direction& direction) -> void;

public:
    inline auto position() const -> const std::list<Position>& { return position_; }
    inline auto velocity() const -> const Velocity& { return velocity_; }

public:
    auto move_on(const Playfield& playfield, const std::function<bool(const Position&)> grow_predicate = nullptr) -> void;

private:
    std::list<Position> position_;
    Direction direction_;
    Velocity velocity_;
    bool accept_direction_change_;
};
