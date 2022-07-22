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
    const Position head_position_{1u, 1u};
    const Position torso_position_{head_position_.row, head_position_.col + 1u};
    const Position tail_position_{torso_position_.row, torso_position_.col + 1u};
};

TEST_F(the_snake, initializes_horizontally_positions_for_head_torso_and_tail)
{
    EXPECT_POSITION({head_position_, torso_position_, tail_position_});
}
