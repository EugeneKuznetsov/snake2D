#pragma once

#include <tuple>

struct Playfield {
    Playfield(unsigned short rows, unsigned short cols)
        : rows{rows}
        , cols{cols}
    {
    }

    unsigned short rows{0};
    unsigned short cols{0};
};

constexpr auto operator==(const Playfield& left, const Playfield& right) -> bool
{
    return std::tie(left.rows, left.cols) == std::tie(right.rows, right.cols);
}
