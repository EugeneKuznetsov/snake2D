#pragma once

#include <tuple>

struct Playfield {
    Playfield(short rows, short cols)
        : rows{rows}
        , cols{cols}
    {
    }

    short rows{0};
    short cols{0};
};

constexpr auto operator==(const Playfield& left, const Playfield& right) -> bool
{
    return std::tie(left.rows, left.cols) == std::tie(right.rows, right.cols);
}
