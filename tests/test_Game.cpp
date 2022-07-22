#include <gtest/gtest.h>

#include <GDK/Keyboard.hpp>

#include <Snake2D/Game.hpp>
#include <Snake2D/Playfield.hpp>
#include <Snake2D/PositionGenerator.hpp>
#include <Snake2D/Snake.hpp>

class PositionPseudoGenerator : public PositionGenerator {
public:
    auto generate() const -> Position override { return next_position_; }

public:
    auto next_position(const Position& position) -> void { next_position_ = position; }

private:
    Position next_position_{0, 0};
};

class game_config {
public:
    auto setup_game() -> void
    {
        position_generator_->next_position(initial_pseudo_generated_position_);
        game_ = std::make_shared<Game>(position_generator_);
        as_abstract_game()->setup();
    }

    auto as_abstract_game() const -> std::shared_ptr<gamedevkit::AbstractGame>
    {
        return std::static_pointer_cast<gamedevkit::AbstractGame>(game_);
    }

    const Position initial_pseudo_generated_position_{1, 1};
    std::shared_ptr<Game> game_{nullptr};
    std::shared_ptr<PositionPseudoGenerator> position_generator_{std::make_shared<PositionPseudoGenerator>()};
};

class the_game : public game_config, public testing::Test {
    auto SetUp() -> void { setup_game(); }
};

struct game_input_params {
    gamedevkit::input::keyboard::Key actual_key;
    gamedevkit::input::keyboard::Action actual_action;
    Position expected_snake_head_position_diff;
};

class the_game_input : public game_config, public testing::TestWithParam<game_input_params> {
public:
    auto SetUp() -> void { setup_game(); }
};

TEST_F(the_game, initializes_playfield_size_60x60_before_setup)
{
    Game game;
    ASSERT_TRUE(nullptr != game.playfield());

    const auto expected_playfield = Playfield{60, 60};
    EXPECT_TRUE(expected_playfield == *game.playfield());
}

TEST_F(the_game, should_have_uninitialized_snake_before_setup)
{
    Game game;
    EXPECT_TRUE(nullptr == game.snake());
}

TEST_F(the_game, should_initialize_snake_in_pseudo_random_position_after_setup)
{
    ASSERT_TRUE(nullptr != game_->snake());

    const auto expected_position = initial_pseudo_generated_position_;
    EXPECT_TRUE(expected_position == game_->snake()->position().front());
}

namespace keyboard = gamedevkit::input::keyboard;
const auto snake_movement_params = testing::Values(game_input_params{keyboard::Key::key_left, keyboard::Action::press, {0, -1}},
                                                   game_input_params{keyboard::Key::key_left, keyboard::Action::release, {0, 0}},
                                                   game_input_params{keyboard::Key::key_up, keyboard::Action::press, {-1, 0}},
                                                   game_input_params{keyboard::Key::key_down, keyboard::Action::press, {1, 0}},
                                                   game_input_params{keyboard::Key::key_right, keyboard::Action::press, {0, 0}});
INSTANTIATE_TEST_SUITE_P(, the_game_input, snake_movement_params);
TEST_P(the_game_input, should_update_snake_position_when_possible)
{
    const auto test_case_param = GetParam();
    const auto& playfield = *game_->playfield();
    const auto& snake_head_position = game_->snake()->position().front();

    auto expected_position = Position{static_cast<short>(test_case_param.expected_snake_head_position_diff.row + snake_head_position.row),
                                      static_cast<short>(test_case_param.expected_snake_head_position_diff.col + snake_head_position.col)};
    if (expected_position.col == 0)
        expected_position.col = playfield.cols;
    else if (expected_position.col > playfield.cols)
        expected_position.col = 1;

    if (expected_position.row == 0)
        expected_position.row = playfield.rows;
    else if (expected_position.row > playfield.rows)
        expected_position.row = 1;

    as_abstract_game()->input(test_case_param.actual_key, test_case_param.actual_action, {});
    as_abstract_game()->update();

    EXPECT_EQ(snake_head_position, expected_position);
}
