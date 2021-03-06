#pragma once

#include <cstdint>

#include "Tetromino.hpp"

namespace tetris {

static constexpr const uint32_t WIDTH = 10, HEIGHT = 20;
static constexpr const uint32_t TPS = 20;
static constexpr const uint32_t MOVE_SPEED = TPS/5;
static constexpr const uint32_t ROT_SPEED = TPS/4;
static constexpr const uint32_t GRAVITY_SPEED = TPS;
static constexpr const uint32_t SOFT_DROP_SPEED = 1;
static constexpr const Vec2 START_POS = {WIDTH/2-1, HEIGHT-1};

struct Controller {
    uint32_t
        left        = 0,
        right       = 0,
        softDrop    = 0,
        hardDrop    = 0,
        rotate      = 0;
};

class Game {
public:
    Game(Controller& controller, std::mt19937& gen);
    ~Game() = default;

    void tick();
    [[nodiscard]] uint32_t get_time() const { return mTick; }
private:
    [[nodiscard]] bool check_direction(Vec2 dir) const;
    [[nodiscard]] bool check_if_scheduled(uint32_t startTick, uint32_t interval) const;
    [[nodiscard]] bool check_row(uint32_t row) const;
    void clear_row(uint32_t row);
    void next_tetromino();
    [[nodiscard]] static bool in_range(Vec2 pos);

    bool mGameOver = false;
    uint32_t mTick = 1;
    uint32_t mGravityTick = 1;
    std::array<Color, HEIGHT * WIDTH> mData{};
    std::array<Color *, HEIGHT> mRows{};
    Tetromino mTetromino, mNextTetromino;

    Controller& mController;

    std::mt19937& mRand;
};
}
