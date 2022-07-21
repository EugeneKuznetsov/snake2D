#include "Snake2D/Game.hpp"

#include <GDK/Keyboard.hpp>

#include "Snake2D/Playfield.hpp"
#include "Snake2D/Snake.hpp"

Game::Game()
    : gamedevkit::AbstractGame()
    , playfield_{nullptr}
    , snake_{nullptr}
{
}

Game::~Game() = default;

auto Game::setup() -> void {}

auto Game::update() -> void {}

auto Game::input(const gamedevkit::input::keyboard::Key& /*key*/,
                 const gamedevkit::input::keyboard::Action& /*action*/,
                 const std::set<gamedevkit::input::keyboard::Modifier>& /*modifiers*/) -> void
{
}

auto Game::playfield() const -> const std::unique_ptr<Playfield>&
{
    return playfield_;
}

auto Game::snake() const -> const std::unique_ptr<Snake>&
{
    return snake_;
}
