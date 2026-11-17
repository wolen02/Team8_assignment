#pragma once
#include "Block.h"

class CropBlock : public Block {
public:
    explicit CropBlock(int shapeIndex);                   
    std::string name() const override;
    int color() const override;
    int shapeIndex() const { return shapeIndex_; }
private:
    int shapeIndex_;
};
