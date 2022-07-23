#include <gtest/gtest.h>

#include <Snake2D/Snake.hpp>
#include <Snake2D/Playfield.hpp>

class the_snake : public testing::Test {
public:
    auto SetUp() -> void { snake_ = std::make_unique<Snake>(head_position_); }

    auto EXPECT_POSITION(const std::list<Position>& expected_position) -> void
    {
        ASSERT_EQ(expected_position.size(), snake_->position().size());
        auto real = snake_->position().cbegin();
        auto expected = expected_position.cbegin();
        for (; expected != expected_position.cend(); ++expected, ++real)
            EXPECT_EQ((*expected), (*real));
    }

public:
    std::unique_ptr<Snake> snake_{nullptr};
    Position head_position_{1, 1};
    Position torso_position_{head_position_.row, static_cast<short>(head_position_.col + 1)};
    Position tail_position_{torso_position_.row, static_cast<short>(torso_position_.col + 1)};
    const Playfield playfield_{3, 3};
};

TEST_F(the_snake, initializes_horizontally_positions_for_head_torso_and_tail)
{
    EXPECT_POSITION({head_position_, torso_position_, tail_position_});
}

TEST_F(the_snake, does_not_move_without_setting_direction_for_the_first_time)
{
    snake_->move_on(playfield_);
    EXPECT_POSITION({head_position_, torso_position_, tail_position_});
}

TEST_F(the_snake, head_moves_to_opposite_side_of_playfield_horizontally)
{
    snake_->direction(Direction::left);
    snake_->move_on(playfield_);
    head_position_.col = playfield_.cols;
    torso_position_.col--;
    tail_position_.col--;
    EXPECT_POSITION({head_position_, torso_position_, tail_position_});
}

TEST_F(the_snake, head_moves_to_opposite_side_of_playfield_vertically)
{
    snake_->direction(Direction::up);
    snake_->move_on(playfield_);
    head_position_.row = playfield_.rows;
    torso_position_.col--;
    tail_position_.col--;
    EXPECT_POSITION({head_position_, torso_position_, tail_position_});
}

TEST_F(the_snake, head_moves_down_when_changing_direction_down)
{
    snake_->direction(Direction::down);
    snake_->move_on(playfield_);
    head_position_.row++;
    torso_position_.col--;
    tail_position_.col--;
    EXPECT_POSITION({head_position_, torso_position_, tail_position_});
}

TEST_F(the_snake, head_will_not_move_towards_torso_when_changing_direction_towards_torso)
{
    snake_->direction(Direction::right);
    snake_->move_on(playfield_);
    EXPECT_POSITION({head_position_, torso_position_, tail_position_});
}

TEST_F(the_snake, head_will_not_move_towards_torso_when_changing_direction_towards_torso_but_continues_moving_further)
{
    snake_->direction(Direction::left);
    snake_->direction(Direction::right);
    snake_->move_on(playfield_);
    head_position_.col = playfield_.cols;
    torso_position_.col--;
    tail_position_.col--;
    EXPECT_POSITION({head_position_, torso_position_, tail_position_});
}

TEST_F(the_snake, tail_remains_on_the_same_position_when_requested_to_grow_during_movement)
{
    snake_->direction(Direction::left);
    snake_->move_on(playfield_, [](const auto&) -> bool { return true; });
    EXPECT_POSITION({{head_position_.row, playfield_.cols}, head_position_, torso_position_, tail_position_});
}

TEST_F(the_snake, dead_returns_true_when_snake_hits_itself)
{
    snake_->direction(Direction::left);
    snake_->move_on(playfield_, [](const auto&) -> bool { return true; });
    EXPECT_TRUE(snake_->dead());
    EXPECT_POSITION({{head_position_.row, playfield_.cols}, head_position_, torso_position_, tail_position_});
}

TEST_F(the_snake, dead_returns_false_when_snake_does_not_hit_itself)
{
    snake_->direction(Direction::left);
    snake_->move_on(playfield_);
    EXPECT_FALSE(snake_->dead());
    head_position_.col = playfield_.cols;
    torso_position_.col--;
    tail_position_.col--;
    EXPECT_POSITION({{head_position_.row, playfield_.cols}, torso_position_, tail_position_});
}
