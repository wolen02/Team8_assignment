#pragma once
//  게임판(Board)의 한 칸에 무엇이 들어 있는지 나타내는 열거형.
//  Board 는 char 대신 CellType 을 저장
enum class CellType {
    Empty,       // 빈 칸           
    Wall,        // 벽/바닥         
    Crop,        // 일반 작물    
    Stone        // 큰 돌        
};

// 칸이 차 있는지
inline bool isSolid(CellType t) { return t != CellType::Empty; }

inline bool isHarvestable(CellType t) {
    return t == CellType::Crop;
}