#pragma once

#include <cstdint>
#include <random>

namespace tetris {

enum class Color: uint32_t {
    NONE = 0,
    RED,
    GREEN,
    BLUE
};

static Color GetRandomColor(std::mt19937& gen) {
    std::uniform_int_distribution<> dist(1, (uint32_t)Color::BLUE);
    return static_cast<Color>(dist(gen));
}
}
