#pragma once
#include"Board.h"
#include"Stage.h"

class GameManager
{
private:
	// 우리는 4단계로 나눌거니까, 각 단계의 stage 정보를 저장할 공간 마련
	Stage stage_data[4];
	// 보드는 불러오면 알아서 초기화 되게 보드에서 만들기. 나는 그냥 사용만.
	Board board;
	int score;
	int level;
	int is_gameover;
	int block_angle;
	int block_x;
	int block_y;
	// 현재 지운 라인 수?
	int lines;
	int ab_x;
	int ab_y;
	char total_block[21][14];// 화면에 표시되는 블록들
	int block_shape; // 현재 블록 모양
	int next_block_shape; // 다음 블록 모양
	char block[7][4][4][4] = {
		//막대모양
		1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,	1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,	1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,

		//네모모양
		1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,

		//'ㅓ' 모양
		0,1,0,0,1,1,0,0,0,1,0,0,0,0,0,0,	1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,1,0,0,1,0,0,0,0,0,0,0,	0,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,

		//'ㄱ'모양
		1,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,	1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,0,0,0,1,1,0,0,0,0,0,0,	0,0,1,0,1,1,1,0,0,0,0,0,0,0,0,0,

		//'ㄴ' 모양
		1,1,0,0,1,0,0,0,1,0,0,0,0,0,0,0,	1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,	0,1,0,0,0,1,0,0,1,1,0,0,0,0,0,0,	1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,

		//'Z' 모양
		1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,	0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0,	1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,	0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0,

		//'S' 모양
		0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0,	0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0

	};
	enum {
		BLACK,      /*  0 : 까망 */
		DARK_BLUE,    /*  1 : 어두운 파랑 */
		DARK_GREEN,    /*  2 : 어두운 초록 */
		DARK_SKY_BLUE,  /*  3 : 어두운 하늘 */
		DARK_RED,    /*  4 : 어두운 빨강 */
		DARK_VOILET,  /*  5 : 어두운 보라 */
		DARK_YELLOW,  /*  6 : 어두운 노랑 */
		GRAY,      /*  7 : 회색 */
		DARK_GRAY,    /*  8 : 어두운 회색 */
		BLUE,      /*  9 : 파랑 */
		GREEN,      /* 10 : 초록 */
		SKY_BLUE,    /* 11 : 하늘 */
		RED,      /* 12 : 빨강 */
		VOILET,      /* 13 : 보라 */
		YELLOW,      /* 14 : 노랑 */
		WHITE,      /* 15 : 하양 */
	};
public:
	GameManager();
	~GameManager();
	
	// 게임 시작시 실행화면 출력
	int init(); // 변수 초기화 => 생성자로 하면 될 듯
	int gotoxy(int x, int y);
	int show_logo();
	int show_cur_block(int shape, int angle, int x, int y); //진행중인 블럭을 화면에 표시한다
	void SetColor(int color);

	int erase_cur_block(int shape, int angle, int x, int y);	//블럭 진행의 잔상을 지우기 위한 함수
	int show_total_block();	//쌓여져있는 블럭을 화면에 표시한다.
	int show_next_block(int shape);
	int make_new_block();	//return값으로 block의 모양번호를 알려줌
	int strike_check(int shape, int angle, int x, int y);	//블럭이 화면 맨 아래에 부닥쳤는지 검사 부닥치면 1을리턴 아니면 0리턴
	int merge_block(int shape, int angle, int x, int y);	//블럭이 바닥에 닿았을때 진행중인 블럭과 쌓아진 블럭을 합침
	int block_start(int shape, int* angle, int* x, int* y);	//블럭이 처음 나올때 위치와 모양을 알려줌
	int move_block(int* shape, int* angle, int* x, int* y, int* next_shape);	//게임오버는 1을리턴 바닥에 블럭이 닿으면 2를 리턴
	int rotate_block(int shape, int* angle, int* x, int* y);
	int show_gameover();
	int show_gamestat();
	int input_data();
	int check_full_line();
};

