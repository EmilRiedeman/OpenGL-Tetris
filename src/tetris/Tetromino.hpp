#pragma once

#include "Vec2.hpp"
#include "Color.hpp"

#include <cstdint>
#include <random>

namespace tetris {

struct Game;

class Tetromino {
    friend Game;
public:
    enum class Type {
        l, O, T, L, J, S, Z
    };

    Tetromino(tetris::Vec2 pos, Type t, Color color);
    Tetromino(tetris::Vec2 pos, std::mt19937& gen);
    Tetromino(Tetromino&&) = default;
    Tetromino& operator=(Tetromino&&) = default;

    void next_rotation();
    void prev_rotation();

    volatile Type mType;
    volatile Color mColor;
private:
    constexpr void change_rotation();
    constexpr static uint32_t get_total_rotations(Type type);
    static Type get_random_type(std::mt19937& gen);

    Vec2 mPosition;
    uint32_t mCurrentRotation = 0;
    Vec2 mSquares[4]{};
};
}
