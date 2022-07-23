#include "Snake2D/PositionGenerator.hpp"

#include <random>
#include <set>
#include <stdexcept>
#include <vector>

auto PositionGenerator::boundaries(const Position& minimum, const Position& maximum) -> void
{
    minimum_ = minimum;
    maximum_ = maximum;
}

auto PositionGenerator::generate(const std::list<Position>& exclude /*= {}*/) const -> Position
{
    std::set<std::size_t> exclude_indicies;
    for (const auto& exclude_position : exclude)
        exclude_indicies.insert(index(exclude_position));

    const auto max_rows = (maximum_.row - minimum_.row) + 1;
    const auto max_cols = (maximum_.col - minimum_.col) + 1;
    std::vector<Position> available_positions{};
    available_positions.reserve((max_rows * max_cols) - exclude_indicies.size());

    if (0u == available_positions.capacity())
        throw std::runtime_error("Cannot generate Position when every available position was excluded");

    for (auto row = minimum_.row; row <= maximum_.row; ++row) {
        for (auto col = minimum_.col; col <= maximum_.col; ++col) {
            const Position available_position{row, col};
            const auto available_position_index = index(available_position);
            if (exclude_indicies.find(available_position_index) == exclude_indicies.cend())
                available_positions.push_back(available_position);
        }
    }

    return available_positions[generate_random_number(0, available_positions.size() - 1)];
}

auto PositionGenerator::generate_random_number(const std::size_t& minimum, const std::size_t& maximum) const -> std::size_t
{
    std::random_device seed;
    std::mt19937 generator{seed()};
    std::uniform_int_distribution<std::size_t> number{minimum, maximum};

    return number(generator);
}

auto PositionGenerator::index(const Position& position) const -> std::size_t
{
    const auto max_cols = (maximum_.col - minimum_.col) + 1;
    const auto adjusted_col = position.col - minimum_.col;
    const auto adjusted_row = position.row - minimum_.row;
    if (adjusted_col < 0 || adjusted_row < 0)
        throw std::runtime_error("Adjusted column and row cannot be negative");

    return (adjusted_row * max_cols) + adjusted_col;
}
