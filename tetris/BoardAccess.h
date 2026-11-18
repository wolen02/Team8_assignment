#pragma once
#include "CellType.h"

class BoardAccess {
public:
    virtual ~BoardAccess() = default;

    virtual int width()  const = 0;                      
    virtual int height() const = 0;                   
    virtual CellType getCell(int x, int y) const = 0;
    virtual void     setCell(int x, int y, CellType t) = 0;

    bool isInside(int x, int y) const {
        return x >= 0 && x < width() && y >= 0 && y < height();
    }
};
