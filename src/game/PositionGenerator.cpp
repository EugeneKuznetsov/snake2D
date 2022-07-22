#include "Snake2D/PositionGenerator.hpp"

#include <random>

auto PositionGenerator::boundaries(const Position& minimum, const Position& maximum) -> void
{
    minimum_ = minimum;
    maximum_ = maximum;
}

auto PositionGenerator::generate() const -> Position
{
    return {generate_random_number(minimum_.row, maximum_.row), generate_random_number(minimum_.col, maximum_.col)};
}

auto PositionGenerator::generate_random_number(const short minimum, const short maximum) const -> short
{
    std::random_device seed;
    std::mt19937 generator{seed()};
    std::uniform_int_distribution<short> number{minimum, maximum};

    return number(generator);
}
