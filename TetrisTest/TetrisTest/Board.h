#pragma once 
class Board {  
private:  
    static const int height = 21;  
    static const int width = 14;  
    char total_block[height][width];  
public:  
    Board();  
    void initBoard();  // 보드를 처음 상태로 만들어
    void showBoard() const;  // 현재 보드를 화면에 보여준디.
    bool canPlaceBlock(const char shape[4][4], int x, int y) const;  // 블록을 이 위치에 놓을 수 있는지 확인한디
    void setBlock(const char shape[4][4], int x, int y);  // 블록을 보드에서 저장해요
    int checkFullLine();  // 가득 찬 줄을 지우고, 지운 줄의 수를 돌려준다
    int getCell(int x, int y) const;  // 해당 위치의 값을 가져온다.
    void setCell(int x, int y, int value);  // 해당 위치의 값을 바꿔요
};
