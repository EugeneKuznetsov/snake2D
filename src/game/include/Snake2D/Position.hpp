#pragma once

#include <tuple>

struct Position {
    unsigned short row{0u};
    unsigned short col{0u};
};

constexpr auto operator==(const Position& left, const Position& right) -> bool
{
    return std::tie(left.row, left.col) == std::tie(right.row, right.col);
}
