#include "Snake2D/Game.hpp"

#include <unordered_map>

#include <GDK/Keyboard.hpp>

#include "Snake2D/Playfield.hpp"
#include "Snake2D/PositionGenerator.hpp"
#include "Snake2D/Snake.hpp"
#include "Snake2D/Stopwatch.hpp"

Game::Game()
    : Game{std::make_shared<PositionGenerator>()}
{
}

Game::Game(std::shared_ptr<PositionGenerator> position_generator)
    : gamedevkit::AbstractGame()
    , food_expires_in_{15000}
    , playfield_max_rows_{60}
    , playfield_max_cols_{60}
    , position_generator_{std::move(position_generator)}
    , snake_movement_stopwatch_{std::make_unique<Stopwatch>()}
    , food_generator_stopwatch_{std::make_unique<Stopwatch>()}
    , playfield_{std::make_unique<Playfield>(playfield_max_rows_, playfield_max_cols_)}
    , snake_{nullptr}
    , food_{nullptr}
    , food_eaten_{0u}
{
    position_generator_->boundaries({1, 1}, {playfield_->rows, playfield_->cols});
}

Game::~Game() = default;

auto Game::setup() -> void
{
    snake_ = std::make_unique<Snake>(position_generator_->generate());
    generate_food();
}

auto Game::update() -> void
{
    if (false == snake_movement_stopwatch_->running())
        return;

    if (food_generator_stopwatch_->elapsed() >= food_expires_in_)
        generate_food();

    const auto ms_per_move = snake_->velocity().ms_per_position();
    if (const auto elapsed = snake_movement_stopwatch_->elapsed(); elapsed >= ms_per_move) {
        snake_->move_on(*playfield_, std::bind(&Game::snake_can_eat_food, this, std::placeholders::_1));

        if (snake_->dead()) {
            reset();
            return;
        }

        if (snake_can_eat_food(snake_->position().front())) {
            food_eaten_++;
            if (food_eaten_ % 2 == 0)
                snake_->increase_velocity();
            generate_food();
        }

        snake_movement_stopwatch_->lap(elapsed - ms_per_move);
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

        if (false == snake_movement_stopwatch_->running()) {
            snake_movement_stopwatch_->start();
            food_generator_stopwatch_->start();
            snake_->move_on(*playfield_, std::bind(&Game::snake_can_eat_food, this, std::placeholders::_1));
        }
    }
}

auto Game::reset() -> void
{
    snake_movement_stopwatch_ = std::make_unique<Stopwatch>();
    food_generator_stopwatch_ = std::make_unique<Stopwatch>();
    snake_ = std::make_unique<Snake>(position_generator_->generate());
    generate_food();
    food_eaten_ = 0u;
}

auto Game::generate_food() -> void
{
    food_ = std::make_unique<Position>(position_generator_->generate(snake_->position()));
    if (true == food_generator_stopwatch_->running())
        food_generator_stopwatch_->lap();
}

auto Game::snake_can_eat_food(const Position& snake_head) -> bool
{
    return snake_head == *food_;
}
