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
    Position head_position_{1u, 1u};
    Position torso_position_{head_position_.row, static_cast<unsigned short>(head_position_.col + 1u)};
    Position tail_position_{torso_position_.row, static_cast<unsigned short>(torso_position_.col + 1u)};
    const Playfield playfield_{4u, 4u};
};

TEST_F(the_snake, initializes_horizontally_positions_for_head_torso_and_tail)
{
    EXPECT_POSITION({head_position_, torso_position_, tail_position_});
}

TEST_F(the_snake, does_not_move_without_setting_direction_for_the_first_time)
{
    snake_->move(playfield_);
    EXPECT_POSITION({head_position_, torso_position_, tail_position_});
}

TEST_F(the_snake, head_moves_to_opposite_side_of_playfield_horizontally)
{
    snake_->direction(Direction::left);
    snake_->move(playfield_);
    head_position_.col = playfield_.cols;
    torso_position_.col--;
    tail_position_.col--;
    EXPECT_POSITION({head_position_, torso_position_, tail_position_});
}

TEST_F(the_snake, head_moves_to_opposite_side_of_playfield_vertically)
{
    snake_->direction(Direction::up);
    snake_->move(playfield_);
    head_position_.row = playfield_.rows;
    torso_position_.col--;
    tail_position_.col--;
    EXPECT_POSITION({head_position_, torso_position_, tail_position_});
}

TEST_F(the_snake, head_moves_down_when_changing_direction_down)
{
    snake_->direction(Direction::down);
    snake_->move(playfield_);
    head_position_.row++;
    torso_position_.col--;
    tail_position_.col--;
    EXPECT_POSITION({head_position_, torso_position_, tail_position_});
}

TEST_F(the_snake, head_will_not_move_towards_torso_when_changing_direction_towards_torso)
{
    snake_->direction(Direction::right);
    snake_->move(playfield_);
    head_position_.col = playfield_.cols;
    torso_position_.col--;
    tail_position_.col--;
    EXPECT_POSITION({head_position_, torso_position_, tail_position_});
}
