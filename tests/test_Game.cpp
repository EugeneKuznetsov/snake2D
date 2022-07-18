#include <gtest/gtest.h>

#include <Snake2D/Game.hpp>

class game : public testing::Test {
public:
    auto SetUp() -> void {}
};

TEST_F(game, dummy_test)
{
    ASSERT_TRUE(true);
}
