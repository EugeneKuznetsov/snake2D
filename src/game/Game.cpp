#include "Snake2D/Game.hpp"

#include <GDK/Keyboard.hpp>

auto Game::setup() -> void {}

auto Game::update() -> void {}

auto Game::input(const gamedevkit::input::keyboard::Key& /*key*/,
                 const gamedevkit::input::keyboard::Action& /*action*/,
                 const std::set<gamedevkit::input::keyboard::Modifier>& /*modifiers*/) -> void
{
}
