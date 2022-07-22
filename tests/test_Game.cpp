#include <gtest/gtest.h>

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
    Position next_position_{0u, 0u};
};

class the_game : public testing::Test {
public:
    auto SetUp() -> void
    {
        position_generator_ = std::make_shared<PositionPseudoGenerator>();
        position_generator_->next_position(initial_pseudo_generated_position_);

        game_ = std::make_unique<Game>(position_generator_);
        game_->setup();
    }

    const Position initial_pseudo_generated_position_{1u, 1u};
    std::unique_ptr<Game> game_{nullptr};
    std::shared_ptr<PositionPseudoGenerator> position_generator_{nullptr};
};

TEST_F(the_game, initializes_playfield_size_60x60_before_setup)
{
    Game game;
    ASSERT_TRUE(nullptr != game.playfield());

    const auto expected_playfield = Playfield{60u, 60u};
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
