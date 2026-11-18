#include "Game.h"
#include <iostream>
using namespace std;

namespace {
void showPreview(const char shapes[7][4][4][4], int type, int rotation) {
    if (type < 0 || type >= 7 || rotation < 0 || rotation >= 4) return;
    for (int i = 0; i < 4; i++) {
        cout << "|    ";
        for (int j = 0; j < 4; j++)
            cout << (shapes[type][rotation][i][j] ? " ■" : "  ");
        cout << "    |\n";
    }
}
}

void Game::setStage(int value) {
    if (value >= 1 && value <= 3) stage = value;
}
void Game::addClearedLines(int lines) {
    if (lines > 0) score += lines * 50;
}
void Game::showHold(const char shapes[7][4][4][4], int type, int rotation) const {
    cout << "\n+----------------+\n|      HOLD      |\n";
    showPreview(shapes, type, rotation);
    cout << "+----------------+\n";
}
void Game::showNext(const char shapes[7][4][4][4], int type, int rotation) const {
    cout << "\n+----------------+\n|      NEXT      |\n";
    showPreview(shapes, type, rotation);
    cout << "+----------------+\n";
}
void Game::showEvent() const {
    cout << "\n+----------------+\n|     EVENT      |\n|  PEST ATTACK!  |\n+----------------+\n";
}
void Game::showScore() const {
    cout << "\n+----------------+\n| SCORE : " << score << "\n+----------------+\n";
}
void Game::showStage() const {
    int target = stage * 1000; // score의 목적 점수 
    cout << "\n+----------------+\n| STAGE : " << stage << " / 3\n";
    cout << "| TARGET: " << target << "\n| " << score << " / " << target << "\n+----------------+\n";
}
void Game::showTime() const {
    cout << "\n+----------------+\n| TIME : 00:00\n+----------------+\n";
}
