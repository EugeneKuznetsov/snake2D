#include "Snake2D/Game.hpp"

#include <unordered_map>

#include <GDK/Keyboard.hpp>

#include "Snake2D/Playfield.hpp"
#include "Snake2D/PositionGenerator.hpp"
#include "Snake2D/Snake.hpp"

constexpr auto playfield_max_rows = 60;
constexpr auto playfield_max_cols = 60;

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

auto Game::update() -> void
{
    snake_->move_on(*playfield_);
}

auto Game::input(const gamedevkit::input::keyboard::Key& key,
                 const gamedevkit::input::keyboard::Action& action,
                 const std::set<gamedevkit::input::keyboard::Modifier>& /*modifiers*/) -> void
{
    namespace keyboard = gamedevkit::input::keyboard;
    if (keyboard::Action::press != action)
        return;

    static std::unordered_map<keyboard::Key, Direction> directions{{keyboard::Key::key_left, Direction::left},
                                                                   {keyboard::Key::key_up, Direction::up},
                                                                   {keyboard::Key::key_right, Direction::right},
                                                                   {keyboard::Key::key_down, Direction::down}};
    if (directions.find(key) != directions.cend())
        snake_->direction(directions[key]);
}
