#include "Block.h"

const Block::Rotations& Block::tetromino(int shapeIndex)
{
    static const char raw[7][4][4][4] = {
        // 막대
        1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,  1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,  1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,  1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,
        // 네모
        1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,  1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,  1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,  1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,
        // 'ㅓ'
        0,1,0,0,1,1,0,0,0,1,0,0,0,0,0,0,  1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,  1,0,0,0,1,1,0,0,1,0,0,0,0,0,0,0,  0,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,
        // 'ㄱ'
        1,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,  1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,  1,0,0,0,1,0,0,0,1,1,0,0,0,0,0,0,  0,0,1,0,1,1,1,0,0,0,0,0,0,0,0,0,
        // 'ㄴ'
        1,1,0,0,1,0,0,0,1,0,0,0,0,0,0,0,  1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,  0,1,0,0,0,1,0,0,1,1,0,0,0,0,0,0,  1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,
        // 'Z'
        1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,  0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0,  1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,  0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0,
        // 'S'
        0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,  1,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0,  0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,  1,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0,
    };

    static const std::array<Rotations, 7> table = [] {
        std::array<Rotations, 7> t{};
        for (int s = 0; s < 7; ++s)
            for (int a = 0; a < 4; ++a)
                for (int r = 0; r < SIZE; ++r)
                    for (int c = 0; c < SIZE; ++c)
                        t[s][a][r][c] = (raw[s][a][r][c] == 1);
        return t;
    }();

    if (shapeIndex < 0 || shapeIndex >= 7) shapeIndex = 0;   
    return table[shapeIndex];
}

Block::Block(const Rotations& rotations, CellType type)
    : rotations_(rotations), cellType_(type) {}

void Block::resetPosition()
{
    x_ = START_X;
    y_ = START_Y;
    angle_ = 0;
}

bool Block::collides(const BoardAccess& board) const
{
    for (int r = 0; r < SIZE; ++r) {
        for (int c = 0; c < SIZE; ++c) {
            if (!isFilled(r, c)) continue;
            const int bx = x_ + c;
            const int by = y_ + r;

            // 좌우 벽 밖이거나 바닥 아래면 충돌
            if (bx < 0 || bx >= board.width() || by >= board.height()) return true;

            if (by < 0) {
                if (board.getCell(bx, 0) == CellType::Wall) return true;   
                continue;
            }

            if (isSolid(board.getCell(bx, by))) return true;
        }
    }
    return false;
}

void Block::stampOnto(BoardAccess& board) const
{
    for (int r = 0; r < SIZE; ++r)
        for (int c = 0; c < SIZE; ++c)
            if (isFilled(r, c) && board.isInside(x_ + c, y_ + r))
                board.setCell(x_ + c, y_ + r, cellType_);
}

bool Block::isAboveTop() const
{
    for (int r = 0; r < SIZE; ++r)
        for (int c = 0; c < SIZE; ++c)
            if (isFilled(r, c) && y_ + r < 0) return true;
    return false;
}
