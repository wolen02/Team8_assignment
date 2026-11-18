#pragma once  
class Farm { 
public: 
    void showFarmer() const;  // 농부의 모습을 화면에 보여 줘요
    void showStorage() const;  // 수확물을 보관하는 창고를 보여 줘요
    void showFarm(int stage) const;  // 스테이지에 따라 농장의 모습을 다르게 보여 줘요
};
