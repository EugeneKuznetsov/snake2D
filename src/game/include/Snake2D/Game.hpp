#pragma once

#include <memory>

#include <GDK/AbstractGame.hpp>

namespace gamedevkit::input::keyboard {
enum class Key;
enum class Action;
enum class Modifier;
}  // namespace gamedevkit::input::keyboard

struct Playfield;
class PositionGenerator;
class Snake;

class Game : public gamedevkit::AbstractGame {
public:
    explicit Game();
    explicit Game(std::shared_ptr<PositionGenerator> position_generator);
    ~Game() override;

public:
    inline auto playfield() const -> const std::unique_ptr<Playfield>& { return playfield_; }
    inline auto snake() const -> const std::unique_ptr<Snake>& { return snake_; }

private:
    auto setup() -> void override;
    auto update() -> void override;
    auto input(const gamedevkit::input::keyboard::Key& key,
               const gamedevkit::input::keyboard::Action& action,
               const std::set<gamedevkit::input::keyboard::Modifier>& modifiers) -> void override;

private:
    std::shared_ptr<PositionGenerator> position_generator_;
    std::unique_ptr<Playfield> playfield_;
    std::unique_ptr<Snake> snake_;
};
