#include <gtest/gtest.h>

#include <Snake2D/Game.hpp>
#include <Snake2D/Playfield.hpp>
#include <Snake2D/Snake.hpp>

class the_game : public testing::Test {
public:
    auto SetUp() -> void {}

    Game game_;
};

TEST_F(the_game, initializes_playfield_size_60x60_before_setup)
{
    ASSERT_TRUE(nullptr != game_.playfield());

    const auto expected_playfield = Playfield{60u, 60u};
    EXPECT_TRUE(expected_playfield == *game_.playfield());
}

TEST_F(the_game, should_have_uninitialized_snake_before_setup)
{
    EXPECT_TRUE(nullptr == game_.snake());
}

TEST_F(the_game, should_initialize_snake_in_pseudorandom_position_after_setup)
{
    ASSERT_TRUE(nullptr != game_.snake());

    const auto expected_position = Position{10u, 20u};
    EXPECT_TRUE(expected_position == game_.snake()->position());
}
