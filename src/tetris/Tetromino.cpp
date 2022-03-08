#include <initializer_list>
#include <algorithm>
#include "Tetromino.hpp"

using tetris::Tetromino;

Tetromino::Tetromino(tetris::Vec2 pos, Type t, Color color): mPosition(pos), mType(t), mColor(color) {
    change_rotation();
}

Tetromino::Tetromino(tetris::Vec2 pos, std::mt19937& gen): Tetromino(pos, get_random_type(gen), GetRandomColor(gen)) {
}

constexpr void Tetromino::change_rotation() {
    std::initializer_list<Vec2> n;
    switch (mType) {
        case Type::l:
            switch (mCurrentRotation) {
                case 0: n = {{0, 2}, {1, 2}, {2, 2}, {3, 2}}; break;
                case 1: n = {{1, 0}, {1, 1}, {1, 2}, {1, 3}}; break;
            }
            break;
        case Type::O:
            n = {{1, 1}, {1, 2}, {2, 1}, {2, 2}};
            break;
        case Type::T:
            switch (mCurrentRotation) {
                case 0: n = {{0, 1}, {1, 1}, {2, 1}, {1, 2}}; break;
                case 1: n = {{1, 0}, {0, 1}, {1, 1}, {1, 2}}; break;
                case 2: n = {{0, 1}, {1, 1}, {2, 1}, {1, 0}}; break;
                case 3: n = {{1, 0}, {2, 1}, {1, 1}, {1, 2}}; break;
            }
            break;
        case Type::L:
            switch (mCurrentRotation) {
                case 0: n = {{0, 1}, {1, 1}, {2, 1}, {2, 2}}; break;
                case 1: n = {{1, 0}, {0, 0}, {1, 1}, {1, 2}}; break;
                case 2: n = {{0, 1}, {1, 1}, {2, 1}, {2, 0}}; break;
                case 3: n = {{1, 0}, {2, 2}, {1, 1}, {1, 2}}; break;
            }
            break;
        case Type::J:
            switch (mCurrentRotation) {
                case 0: n = {{0, 1}, {1, 1}, {2, 1}, {0, 2}}; break;
                case 1: n = {{1, 0}, {0, 2}, {1, 1}, {1, 2}}; break;
                case 2: n = {{0, 1}, {1, 1}, {2, 1}, {0, 0}}; break;
                case 3: n = {{1, 0}, {2, 0}, {1, 1}, {1, 2}}; break;
            }
            break;
        case Type::S:
            switch (mCurrentRotation) {
                case 0: n = {{0, 2}, {1, 1}, {2, 1}, {1, 2}}; break;
                case 1: n = {{0, 0}, {0, 1}, {1, 1}, {1, 2}}; break;
            }
            break;
        case Type::Z:
            switch (mCurrentRotation) {
                case 0: n = {{0, 1}, {1, 1}, {2, 2}, {1, 2}}; break;
                case 1: n = {{1, 0}, {0, 1}, {1, 1}, {0, 2}}; break;
            }
            break;
    }
    std::copy(n.begin(), n.end(), mSquares);
}

constexpr uint32_t Tetromino::get_total_rotations(Tetromino::Type type) {
    switch (type) {
        case Type::S:
        case Type::Z:
        case Type::l:return 2;
        case Type::O:return 1;
        case Type::T:
        case Type::L:
        case Type::J:return 4;
    }
    return 0;
}

Tetromino::Type Tetromino::get_random_type(std::mt19937& gen) {
    std::uniform_int_distribution<> dist(0, (uint32_t)Type::L);
    return static_cast<Type>(dist(gen));
}

void tetris::Tetromino::next_rotation() {
    (++mCurrentRotation) %= get_total_rotations(mType);
}


void tetris::Tetromino::prev_rotation() {
    if (mCurrentRotation) --mCurrentRotation;
    else mCurrentRotation = get_total_rotations(mType) - 1;
}
