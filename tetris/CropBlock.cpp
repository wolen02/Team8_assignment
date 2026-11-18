#include "CropBlock.h"

CropBlock::CropBlock(int shapeIndex)
    : Block(tetromino(shapeIndex), CellType::Crop), shapeIndex_(shapeIndex) {}

std::string CropBlock::name() const
{
    static const char* names[7] = { "대파", "감자", "고추", "옥수수", "당근", "배추", "토마토" };
    return names[shapeIndex_ % 7];
}

int CropBlock::color() const
{
    // 원본 show_cur_block 의 모양별 색과 같다
    static const int colors[7] = { ConsoleColor::RED, ConsoleColor::BLUE, ConsoleColor::SKY_BLUE,
                                   ConsoleColor::WHITE, ConsoleColor::YELLOW, ConsoleColor::VIOLET,
                                   ConsoleColor::GREEN };
    return colors[shapeIndex_ % 7];
}
