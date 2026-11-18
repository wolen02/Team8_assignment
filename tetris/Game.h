#pragma once  
class Game { 
private: 
    int score = 0;  
    int stage = 1;  
public:
    void setStage(int value); 
    void addClearedLines(int lines);  // 지운 줄의 수에 따라 점수를 추가합니다.
    void showHold(const char shapes[7][4][4][4], int type, int rotation) const;  // HOLD에 저장된 블록을 보여 줍니다.
    void showNext(const char shapes[7][4][4][4], int type, int rotation) const;  // 다음에 나올 블록을 보여 줍니다.
    void showEvent() const;  // 현재 이벤트 정보를 보여 줍니다.
    void showScore() const;  // 현재 점수를 보여 줍니다.
    void showStage() const;  // 현재 스테이지와 목표 점수를 보여 줍니다.
    void showTime() const;  // 게임 시간을 보여 줍니다.
};
