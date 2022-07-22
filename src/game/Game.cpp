#include "Snake2D/Game.hpp"

#include <GDK/Keyboard.hpp>

#include "Snake2D/Playfield.hpp"
#include "Snake2D/PositionGenerator.hpp"
#include "Snake2D/Snake.hpp"

constexpr auto playfield_max_rows = 60u;
constexpr auto playfield_max_cols = 60u;

Game::Game()
    : Game{std::make_shared<PositionGenerator>()}
{
}

Game::Game(std::shared_ptr<PositionGenerator> position_generator)
    : gamedevkit::AbstractGame()
    , position_generator_{std::move(position_generator)}
    , playfield_{std::make_unique<Playfield>(playfield_max_rows, playfield_max_cols)}
    , snake_{nullptr}
{
    position_generator_->boundaries({0, 0}, {playfield_->rows, playfield_->cols});
}

Game::~Game() = default;

auto Game::setup() -> void
{
    snake_ = std::make_unique<Snake>(position_generator_->generate());
}

auto Game::update() -> void {}

auto Game::input(const gamedevkit::input::keyboard::Key& /*key*/,
                 const gamedevkit::input::keyboard::Action& /*action*/,
                 const std::set<gamedevkit::input::keyboard::Modifier>& /*modifiers*/) -> void
{
}
