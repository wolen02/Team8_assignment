#include "Story.h"
#include <iostream>
using namespace std;

void Story::showStory(int stage) const {
    cout << "\n+---------------- STORY ----------------+\n";

    if (stage == 1) {
        cout << "STAGE 1: Start your farm!\n";
        cout << "작물을 키우고 수확물을 모으세요!\n";
    }
    else if (stage == 2) {
        cout << "STAGE 2: Protect the farm!\n";
        cout << "해충이 몰려오고 있습니다! 농작물을 지키세요!\n";
    }
    else {
        cout << "STAGE 3: Winter is coming!\n";
        cout << "눈으로부터 농작물을 안전하게 보호하세요!\n";
    }

    cout << "+---------------------------------------+\n";
}