#pragma once

#include <chrono>
#include <memory>

#include <GDK/AbstractGame.hpp>

namespace gamedevkit::input::keyboard {
enum class Key;
enum class Action;
enum class Modifier;
}  // namespace gamedevkit::input::keyboard

struct Playfield;
struct Position;
class PositionGenerator;
class Snake;
class Stopwatch;

class Game : public gamedevkit::AbstractGame {
public:
    explicit Game();
    explicit Game(std::shared_ptr<PositionGenerator> position_generator);
    ~Game() override;

public:
    inline auto playfield() const -> const std::unique_ptr<Playfield>& { return playfield_; }
    inline auto snake() const -> const std::unique_ptr<Snake>& { return snake_; }
    inline auto food() const -> const std::unique_ptr<Position>& { return food_; }

private:
    auto setup() -> void override;
    auto update() -> void override;
    auto input(const gamedevkit::input::keyboard::Key& key,
               const gamedevkit::input::keyboard::Action& action,
               const std::set<gamedevkit::input::keyboard::Modifier>& modifiers) -> void override;

private:
    auto generate_food() -> void;
    auto snake_can_eat_food(const Position& snake_head) -> bool;

private:
    const std::chrono::milliseconds food_expires_in_;
    const short playfield_max_rows_;
    const short playfield_max_cols_;

    std::shared_ptr<PositionGenerator> position_generator_;
    std::unique_ptr<Stopwatch> snake_movement_stopwatch_;
    std::unique_ptr<Stopwatch> food_generator_stopwatch_;
    std::unique_ptr<Playfield> playfield_;
    std::unique_ptr<Snake> snake_;
    std::unique_ptr<Position> food_;
};
