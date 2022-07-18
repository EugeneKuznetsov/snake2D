#pragma once

#include <GDK/AbstractGame.hpp>

namespace gamedevkit::inputkeyboard {
enum class Key;
enum class Action;
enum class Modifier;
}  // namespace gamedevkit::inputkeyboard

class Game : public gamedevkit::AbstractGame {
public:
    auto setup() -> void override;
    auto update() -> void override;
    auto input(const gamedevkit::input::keyboard::Key& key,
               const gamedevkit::input::keyboard::Action& action,
               const std::set<gamedevkit::input::keyboard::Modifier>& modifiers) -> void override;
};
