#include "Board.h"
#include "Farm.h"
#include "Story.h"
#include "Game.h"
#include <iostream>
using namespace std;

int main() {
    Board board;
    Farm farm;
    Story story;
    Game game;

    // 블록이 예시 
    char demoShapes[7][4][4][4] = {};
    demoShapes[1][0][0][0] = 1;
    demoShapes[1][0][0][1] = 1;
    demoShapes[1][0][1][0] = 1;
    demoShapes[1][0][1][1] = 1;
    demoShapes[5][0][0][1] = 1;
    demoShapes[5][0][0][2] = 1;
    demoShapes[5][0][1][0] = 1;
    demoShapes[5][0][1][1] = 1;

    int stage = 1;
    game.setStage(stage);

    
    board.showBoard();
    game.showHold(demoShapes, 1, 0);
    game.showNext(demoShapes, 5, 0);
    game.showEvent();
    game.showScore();
    game.showStage();
    game.showTime();
    story.showStory(stage);
    farm.showFarmer();
    farm.showStorage();
    farm.showFarm(stage);
    
    return 0;
}
