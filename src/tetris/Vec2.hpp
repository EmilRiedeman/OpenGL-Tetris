#pragma once

#include <cstdint>

namespace tetris {

struct Vec2 {
    uint32_t x, y;

    Vec2 operator+(const Vec2& o) const {
        return {x + o.x, y + o.y};
    }
};

static constexpr Vec2 UP{0u, 1u}, DOWN{0u, -1u}, LEFT{-1u, 0u}, RIGHT{1u, 0u}, ZERO{0, 0};
}
