#pragma once

#include <memory>

#include <GDK/AbstractGame.hpp>

namespace gamedevkit::inputkeyboard {
enum class Key;
enum class Action;
enum class Modifier;
}  // namespace gamedevkit::inputkeyboard

struct Playfield;
class Snake;

class Game : public gamedevkit::AbstractGame {
public:
    explicit Game();
    ~Game() override;

public:
    auto setup() -> void override;
    auto update() -> void override;
    auto input(const gamedevkit::input::keyboard::Key& key,
               const gamedevkit::input::keyboard::Action& action,
               const std::set<gamedevkit::input::keyboard::Modifier>& modifiers) -> void override;

public:
    auto playfield() const -> const std::unique_ptr<Playfield>&;
    auto snake() const -> const std::unique_ptr<Snake>&;

private:
    std::unique_ptr<Playfield> playfield_;
    std::unique_ptr<Snake> snake_;
};
