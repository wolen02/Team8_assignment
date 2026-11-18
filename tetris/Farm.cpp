#include "Farm.h"
#include <iostream>
using namespace std;

void Farm::showFarmer() const {
    cout << "\nTHE YOUNG FARMER\n";
    cout << R"(     .--------.
    /__________\
      | o  o |
      |  __  |
       \____/
      --|  |--
        |__|
        /  \
       /    \
)";
}
void Farm::showStorage() const {
    cout << "\nHARVEST STORAGE\n";
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 5; col++) cout << "[###] ";
        cout << '\n';
    }
}
void Farm::showFarm(int stage) const {
    cout << "\nFARM FIELD - STAGE " << stage << endl;

    if (stage == 1) {
        cout << R"(
 \|/     \|/     \|/     \|/     \|/
  |       |       |       |       |
 / \     / \     / \     / \     / \
 \|/     \|/     \|/     \|/     \|/
  |       |       |       |       |
 / \     / \     / \     / \     / \
 \|/     \|/     \|/     \|/     \|/
  |       |       |       |       |
 / \     / \     / \     / \     / \
)";
    }
    else if (stage == 2) {
        cout << R"(
 \|/     \|/     \|/     \|/     \|/
  P       P       P       P       P
 / \     / \     / \     / \     / \
 \|/     \|/     \|/     \|/     \|/
  P       P       P       P       P
 / \     / \     / \     / \     / \
 \|/     \|/     \|/     \|/     \|/
  P       P       P       P       P
 / \     / \     / \     / \     / \
)";
    }
    else if (stage == 3) {
        cout << R"(
  *       *       *       *       *
  |       |       |       |       |
 / \     / \     / \     / \     / \
  *       *       *       *       *
  |       |       |       |       |
 / \     / \     / \     / \     / \
  *       *       *       *       *
  |       |       |       |       |
 / \     / \     / \     / \     / \
)";
    }
}