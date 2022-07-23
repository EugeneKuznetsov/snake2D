#include <gtest/gtest.h>

#include <Snake2D/PositionGenerator.hpp>

struct position_generator_params {
    struct generator_boundaries {
        Position minimum;
        Position maximum;
    } boundaries;
    std::list<Position> actual_excluded;
    Position expected_generated;
};

class position_generator : public testing::TestWithParam<position_generator_params> {
public:
    auto SetUp() -> void
    {
        const auto& test_case_params = GetParam();
        generator.boundaries(test_case_params.boundaries.minimum, test_case_params.boundaries.maximum);
    }

    PositionGenerator generator;
};

const auto single_left_position_params = testing::Values(position_generator_params{{{1, 1}, {2, 2}}, {{1, 2}, {2, 1}, {2, 2}}, {1, 1}},
                                                         position_generator_params{{{1, 1}, {2, 2}}, {{1, 1}, {2, 1}, {2, 2}}, {1, 2}},
                                                         position_generator_params{{{1, 1}, {2, 2}}, {{1, 1}, {1, 2}, {2, 2}}, {2, 1}},
                                                         position_generator_params{{{1, 1}, {2, 2}}, {{1, 1}, {1, 2}, {2, 1}}, {2, 2}});
INSTANTIATE_TEST_SUITE_P(, position_generator, single_left_position_params);
TEST_P(position_generator, generates_single_left_position_when_everything_else_is_excluded)
{
    const auto& test_case_params = GetParam();
    EXPECT_EQ(generator.generate(test_case_params.actual_excluded), test_case_params.expected_generated);
}

TEST(position_generator_exceptions, throws_runtime_error_when_all_possible_positions_should_be_excluded)
{
    PositionGenerator generator;
    generator.boundaries({1, 1}, {2, 2});

    const std::list<Position> exclude{{1, 1}, {1, 2}, {2, 1}, {2, 2}};
    EXPECT_THROW(generator.generate(exclude), std::runtime_error);
}
