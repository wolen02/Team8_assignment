#pragma once

#include <array>
#include <string>
#include "CellType.h"
#include "BoardAccess.h"

namespace ConsoleColor {
    constexpr int DARK_GRAY = 8, BLUE = 9, GREEN = 10, SKY_BLUE = 11,
                  RED = 12, VIOLET = 13, YELLOW = 14, WHITE = 15,
                  DARK_YELLOW = 6, GRAY = 7, DARK_GREEN = 2;
}

class Block {
public:
    static constexpr int SIZE = 4;                       
    using Grid      = std::array<std::array<bool, SIZE>, SIZE>;   // [행][열]
    using Rotations = std::array<Grid, 4>;                // 회전 4방향

    static constexpr int START_X = 5;                    
    static constexpr int START_Y = -3;

    virtual ~Block() = default;

 
    // 현재 회전 상태에서 (row, col) 칸이 차 있는지
    bool isFilled(int row, int col) const { return rotations_[angle_][row][col]; }

    // ---------- 위치 / 회전 ----------
    int x() const { return x_; }
    int y() const { return y_; }
    int angle() const { return angle_; }

    void moveLeft()   { --x_; }
    void moveRight()  { ++x_; }
    void moveDown()   { ++y_; }
    void moveUp()     { --y_; }                          
    void rotateCW()   { angle_ = (angle_ + 1) % 4; }
    void rotateCCW()  { angle_ = (angle_ + 3) % 4; }      
    void resetPosition();                                 // 시작 위치로

    // 지금 위치에서 벽이나 쌓인 칸과 겹치는지 
    bool collides(const BoardAccess& board) const;
    // 블록을 판에 새긴다 
    void stampOnto(BoardAccess& board) const;
    // 블록 칸 중 하나라도 화면 위(y < 0)에 걸쳐 있는지 -> 게임오버 판정용
    bool isAboveTop() const;

    // ---------- 종류별로 달라지는 부분 (가상 함수) ----------
    virtual std::string name() const = 0;                 // "옥수수", "큰 돌" 등
    virtual int color() const = 0;                       
    virtual const char* symbol() const { return "■"; }   // 화면에 찍을 문자
    CellType cellType() const { return cellType_; }       // 판에 새겨질 칸 종류

    
    virtual std::string onLanded(BoardAccess& board) { (void)board; return ""; }

protected:
   
    Block(const Rotations& rotations, CellType type);

    // 블록 모양
    static const Rotations& tetromino(int shapeIndex);

    static Rotations sameForAllAngles(const Grid& g) { return { g, g, g, g }; }

private:
    Rotations rotations_;
    CellType  cellType_;
    int angle_ = 0;
    int x_ = START_X;
    int y_ = START_Y;
};
