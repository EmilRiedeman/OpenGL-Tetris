#include "Game.hpp"

#include <algorithm>

using tetris::Game;

void Game::tick() {
    if (mGameOver) return;

    if (check_if_scheduled(mController.rotate, ROT_SPEED)) {
        mTetromino.next_rotation();
        if (!check_direction(ZERO)) mTetromino.prev_rotation();
    }

    if (check_if_scheduled(mController.left, MOVE_SPEED))
        if (check_direction(LEFT)) --mTetromino.mPosition.x;

    if (check_if_scheduled(mController.right, MOVE_SPEED))
        if (check_direction(RIGHT)) ++mTetromino.mPosition.x;

    if (mController.hardDrop == mTick) {
        while (check_direction(DOWN)) --mTetromino.mPosition.y;
        next_tetromino();
    } else if (check_if_scheduled(mController.softDrop, SOFT_DROP_SPEED) || (!mController.softDrop &&
            check_if_scheduled(mGravityTick, GRAVITY_SPEED))) {
        if (check_direction(DOWN)) --mTetromino.mPosition.y;
        else next_tetromino();
    }

    mTick++;
}

Game::Game(Controller& controller, std::mt19937& gen): mTetromino(START_POS, gen), mNextTetromino(START_POS, gen), mController(controller), mRand(gen) {
    for (uint32_t i = 0; i < HEIGHT; ++i) {
        mRows[i] = mData + i * WIDTH;
    }
}

void Game::clear_row(uint32_t row) {
    std::fill(mRows[row], mRows[row] + WIDTH, 0);
    auto holder = mRows[row];
    for (uint32_t i = row; i < HEIGHT-1; ++i) {
        mRows[i] = mRows[i + 1];
    }
    mRows[HEIGHT-1] = holder;
}

bool Game::check_row(uint32_t row) const {
    return std::all_of(mRows[row], mRows[row] + WIDTH, [=] (auto color) {
        return color != Color::NONE;
    });
}

bool Game::check_direction(tetris::Vec2 dir) const {
    return std::all_of(std::begin(mTetromino.mSquares), std::end(mTetromino.mSquares), [=] (auto offset) {
        Vec2 next = offset + (mTetromino.mPosition + dir);
        return (!in_range(next) && mRows[next.y][next.x] == Color::NONE);
    });
}

bool Game::check_if_scheduled(uint32_t startTick, uint32_t interval) const {
    return !(startTick && (mTick - startTick) % interval);
}

bool Game::in_range(tetris::Vec2 pos) {
    return pos.x < WIDTH && pos.y < HEIGHT;
}

void Game::next_tetromino() {
    mGravityTick = mTick;

    uint32_t length = 0;
    for (const auto& offset : mNextTetromino.mSquares) {
        if (-offset.y > length) length = -offset.y;
        auto loc = mNextTetromino.mPosition + offset;
        mRows[loc.y][loc.x] = mNextTetromino.mColor;
    }

    uint32_t row = mTetromino.mPosition.y - length;
    for (uint32_t i = 0; i <= length; ++i) {
        if (check_row(row)) clear_row(row);
        else ++row;
    }

    mTetromino = std::move(mNextTetromino);
    mNextTetromino = Tetromino(START_POS, mRand);

    if (!check_direction(ZERO)) mGameOver = true;
}
