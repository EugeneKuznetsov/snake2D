#pragma once

#include <tuple>

struct Position {
    short row{0};
    short col{0};
};

constexpr auto operator==(const Position& left, const Position& right) -> bool
{
    return std::tie(left.row, left.col) == std::tie(right.row, right.col);
}
