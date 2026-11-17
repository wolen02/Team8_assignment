#pragma once
// ============================================================================
// BoardAccess.h
//  Block 이 게임판을 "읽고 쓰기" 위해 필요한 최소한의 인터페이스.
//
//  왜 Board 클래스를 직접 쓰지 않나?
//   - Board 는 다른 팀원이 만든다. Block 이 Board 의 세부 구현에 의존하면
//     Board 가 바뀔 때마다 Block 도 고쳐야 한다.
//   - 그래서 Block 은 이 추상 인터페이스만 알고, Board 가 이것을 상속(구현)한다.
//     -> class Board : public BoardAccess { ... };
//  좌표: x = 열(0~13, 0과 13은 벽), y = 행(0~20, 20은 바닥). 원본과 같다.
// ============================================================================
#include "CellType.h"

class BoardAccess {
public:
    virtual ~BoardAccess() = default;

    virtual int width()  const = 0;                       // 14
    virtual int height() const = 0;                       // 21
    virtual CellType getCell(int x, int y) const = 0;
    virtual void     setCell(int x, int y, CellType t) = 0;

    bool isInside(int x, int y) const {
        return x >= 0 && x < width() && y >= 0 && y < height();
    }
};
