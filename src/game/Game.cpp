#include "Snake2D/Game.hpp"

#include <unordered_map>

#include <GDK/Keyboard.hpp>

#include "Snake2D/Playfield.hpp"
#include "Snake2D/PositionGenerator.hpp"
#include "Snake2D/Snake.hpp"
#include "Snake2D/Stopwatch.hpp"

constexpr auto playfield_max_rows = 60;
constexpr auto playfield_max_cols = 60;

Game::Game()
    : Game{std::make_shared<PositionGenerator>()}
{
}

Game::Game(std::shared_ptr<PositionGenerator> position_generator)
    : gamedevkit::AbstractGame()
    , position_generator_{std::move(position_generator)}
    , stopwatch_{std::make_unique<Stopwatch>()}
    , playfield_{std::make_unique<Playfield>(playfield_max_rows, playfield_max_cols)}
    , snake_{nullptr}
{
    position_generator_->boundaries({1, 1}, {playfield_->rows, playfield_->cols});
}

Game::~Game() = default;

auto Game::setup() -> void
{
    snake_ = std::make_unique<Snake>(position_generator_->generate());
}

auto Game::update() -> void
{
    if (false == stopwatch_->running())
        return;

    const auto ms_per_move = snake_->velocity().ms_per_position();
    if (const auto elapsed = stopwatch_->elapsed(); elapsed >= ms_per_move) {
        snake_->move_on(*playfield_);
        stopwatch_->lap(elapsed - ms_per_move);
    }
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
    if (directions.find(key) != directions.cend()) {
        snake_->direction(directions[key]);

        if (false == stopwatch_->running()) {
            stopwatch_->start();
            snake_->move_on(*playfield_);
        }
    }
}
