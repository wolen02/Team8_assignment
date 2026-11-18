#include "GameManager.h"
#include<iostream>
#include <windows.h>
// 콘솔에서 키보드가 눌린 상태인지 확인하는 _kbhit()함수 포함하는 헤더
#include<conio.h>
#include"Stage.h"

#define EXT_KEY			0xffffffe0	//확장키 인식값 
#define KEY_LEFT		0x4b
#define KEY_RIGHT		0x4d
#define KEY_UP			0x48
#define KEY_DOWN		0x50
using namespace std;

GameManager::GameManager()
	:level(0), lines(0), ab_x(5), ab_y(1),is_gameover(0), block_angle(0), score(0)
{
	// 난수 설정
	srand((unsigned)time(NULL));

	// 여기부터
	int i, j;

	for (i = 0;i < 20;i++)
	{
		for (j = 0;j < 14;j++)
		{
			if ((j == 0) || (j == 13))
			{
				total_block[i][j] = 1;
			}
			else {
				total_block[i][j] = 0;
			}
		}
	}

	for (j = 0;j < 14;j++)			//화면의 제일 밑의 줄은 1로 채운다.
		total_block[20][j] = 1;

	// 여기까지는 board에서 초기화 해야할 부분 나중에 지우자.

	// Stage 정보 저장.
	for (int i = 0; i < size(stage_data); i++) {
		stage_data[i] = Stage((40-10*i), (20 - 3 * i), 20);
	}

}

GameManager::~GameManager()
{
}

int GameManager::init()
{
	// 시작하면 start 화면이 보여야함.
	show_logo();

	// 무한 반복 실행
	while (1)
	{
		// input_data() 기능은 잘 모르겠음
		input_data();
		// 비어있는 보드 보여주기
		show_total_block();

		// 현재 블록과 다음에 올 블록 미리 생성하기
		block_shape = make_new_block();
		next_block_shape = make_new_block();
		// 오른쪽 위에 다음에 올 블록 표시
		show_next_block(next_block_shape);
		
		// 블록 내려오기
		block_start(block_shape, &block_angle, &block_x, &block_y);

		// 현재 게임 상태를 불러오는 것 같은데, 왜 이렇게 구현했는 지 이해가 안 됨.
		show_gamestat();


		// 게임 시작
		int i;
		for (i = 1;1;i++)
		{
			// 키보드 입력이 감지되면
			if (_kbhit())
			{
				// 입력된 키 확인하고
				char keytemp = _getche();

				// 확장키로 읽되
				if (keytemp == EXT_KEY)
				{
					keytemp = _getche();
					
					// 방향키면 주어진 대로 움직이고
					switch (keytemp)
					{
					case KEY_UP:		//회전하기

						if (strike_check(block_shape, (block_angle + 1) % 4, block_x, block_y) == 0)
						{
							erase_cur_block(block_shape, block_angle, block_x, block_y);
							block_angle = (block_angle + 1) % 4;
							show_cur_block(block_shape, block_angle, block_x, block_y);
						}
						break;
					case KEY_LEFT:		//왼쪽으로 이동
						if (block_x > 1)
						{
							erase_cur_block(block_shape, block_angle, block_x, block_y);
							block_x--;
							if (strike_check(block_shape, block_angle, block_x, block_y) == 1)
								block_x++;

							show_cur_block(block_shape, block_angle, block_x, block_y);
						}
						break;
					case KEY_RIGHT:		//오른쪽으로 이동

						if (block_x < 14)
						{
							erase_cur_block(block_shape, block_angle, block_x, block_y);
							block_x++;
							if (strike_check(block_shape, block_angle, block_x, block_y) == 1)
								block_x--;
							show_cur_block(block_shape, block_angle, block_x, block_y);
						}
						break;
					case KEY_DOWN:		//아래로 이동
						is_gameover = move_block(&block_shape, &block_angle, &block_x, &block_y, &next_block_shape);
						show_cur_block(block_shape, block_angle, block_x, block_y);
						break;
					}
				}
				
				// 입력 키가 스페이스 바면
				if (keytemp == 32)
				{
					// game over될 때까지 블록을 밑으로 옮김
					while (is_gameover == 0)
					{
						// move_block은 충돌이 일어났을 때 game over면 return 1
						// 충돌이 일어났지만 문제없다면 return 2
						// 충돌이 일어나지 않았다면 return 0
						is_gameover = move_block(&block_shape, &block_angle, &block_x, &block_y, &next_block_shape);
					}
					show_cur_block(block_shape, block_angle, block_x, block_y);
				}
			}

			// 방향키를 누르지 않았을 때, 블록이 밑으로 내려옴
			if (i % stage_data[level].getSpeed() == 0)
			{
				is_gameover = move_block(&block_shape, &block_angle, &block_x, &block_y, &next_block_shape);

				show_cur_block(block_shape, block_angle, block_x, block_y);
			}

			if (stage_data[level].getClear_line() == lines)	//클리어 스테이지
			{
				level++;
				lines = 0;
			}
			if (is_gameover == 1)
			{
				show_gameover();
				SetColor(GRAY);
				break;
			}

			gotoxy(77, 23);
			Sleep(15);
			gotoxy(77, 23);
		}
		init();
	}
	return 0;
}

// 커서를 이동시키는 거임
int GameManager::gotoxy(int x, int y)
{
	// #include windows.h를 통해 표준 입출력, 표준 에러의 handle을 가져올 수 있음
	// handle은 os의 handle table의 값을 가져옴
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.Y = y;
	pos.X = x;
	SetConsoleCursorPosition(hConsole, pos);
	return 0;
}

int GameManager::show_logo()
{
	int i, j;
	gotoxy(13, 3);
	printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
	Sleep(100);
	gotoxy(13, 4);
	printf("┃◆◆◆  ◆◆◆  ◆◆◆   ◆◆     ◆   ◆◆◆ ┃");
	Sleep(100);
	gotoxy(13, 5);
	printf("┃  ◆    ◆        ◆     ◆ ◆    ◆   ◆     ┃");
	Sleep(100);
	gotoxy(13, 6);
	printf("┃  ◆    ◆◆◆    ◆     ◆◆     ◆     ◆   ┃");
	Sleep(100);
	gotoxy(13, 7);
	printf("┃  ◆    ◆        ◆     ◆ ◆    ◆       ◆ ┃");
	Sleep(100);
	gotoxy(13, 8);
	printf("┃  ◆    ◆◆◆    ◆     ◆  ◆   ◆   ◆◆◆ ┃");
	Sleep(100);
	gotoxy(13, 9);
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");

	gotoxy(28, 20);
	printf("Please Press Any Key~!");

	for (i = 0;i >= 0;i++) {
		if (i % 40 == 0)
		{
			for (j = 0;j < 5;j++)
			{
				gotoxy(18, 14 + j);
				printf("                                                          ");
			}
			show_cur_block(rand() % 7, rand() % 4, 6, 14);
			show_cur_block(rand() % 7, rand() % 4, 12, 14);
			show_cur_block(rand() % 7, rand() % 4, 19, 14);
			show_cur_block(rand() % 7, rand() % 4, 24, 14);
		}
		if (_kbhit())
			break;
		Sleep(30);
	}
	// 키보드로부터 문자를 즉시 입력받는 함수(아무키나 눌렀던 걸 비우는 거구나)
	_getche();
	system("cls");

	return 0;
}

int GameManager::show_cur_block(int shape, int angle, int x, int y)
{
	int i, j;

	switch (shape)
	{
	case 0:
		SetColor(RED);
		break;
	case 1:
		SetColor(BLUE);
		break;
	case 2:
		SetColor(SKY_BLUE);
		break;
	case 3:
		SetColor(WHITE);
		break;
	case 4:
		SetColor(YELLOW);
		break;
	case 5:
		SetColor(VOILET);
		break;
	case 6:
		SetColor(GREEN);
		break;
	}

	for (i = 0;i < 4;i++)
	{
		for (j = 0;j < 4;j++)
		{
			if ((j + y) < 0)
				continue;
			if (block[shape][angle][j][i] == 1)
			{
				gotoxy((i + x) * 2 + ab_x, j + y + ab_y);
				printf("■");
			}
		}
	}
	SetColor(BLACK);
	gotoxy(77, 23);
	return 0;
}

int GameManager::erase_cur_block(int shape, int angle, int x, int y)
{
	int i, j;
	for (i = 0;i < 4;i++)
	{
		for (j = 0;j < 4;j++)
		{
			if (block[shape][angle][j][i] == 1)
			{
				gotoxy((i + x) * 2 + ab_x, j + y + ab_y);
				printf("  ");
				//break;

			}
		}
	}
	return 0;
}

int GameManager::show_total_block()
{
	int i, j;
	SetColor(DARK_GRAY);
	for (i = 0;i < 21;i++)
	{
		for (j = 0;j < 14;j++)
		{
			if (j == 0 || j == 13 || i == 20)		//레벨에 따라 외벽 색이 변함
			{
				SetColor((level % 6) + 1);

			}
			else {
				SetColor(DARK_GRAY);
			}
			gotoxy((j * 2) + ab_x, i + ab_y);
			if (total_block[i][j] == 1)
			{
				printf("■");
			}
			else {
				printf("  ");
			}

		}
	}
	SetColor(BLACK);
	gotoxy(77, 23);
	return 0;
}

// 오른쪽 위에 다음에 올 블록 표시
int GameManager::show_next_block(int shape)
{
	int i, j;
	SetColor((level + 1) % 6 + 1);
	for (i = 1;i < 7;i++)
	{
		gotoxy(33, i);
		for (j = 0;j < 6;j++)
		{
			if (i == 1 || i == 6 || j == 0 || j == 5)
			{
				printf("■");
			}
			else {
				printf("  ");
			}
		}
	}
	show_cur_block(shape, 0, 15, 1);
	return 0;
}

int GameManager::make_new_block()
{
	int shape;
	int i;
	i = rand() % 100;
	if (i <= stage_data[level].getStick_rate())		//막대기 나올확률 계산
		return 0;							//막대기 모양으로 리턴

	shape = (rand() % 6) + 1;		//shape에는 1~6의 값이 들어감
	show_next_block(shape);
	return shape;
}

int GameManager::strike_check(int shape, int angle, int x, int y)
{
	int i, j;
	int block_dat;

	for (i = 0;i < 4;i++)
	{
		for (j = 0;j < 4;j++)
		{
			if (((x + j) == 0) || ((x + j) == 13))
				block_dat = 1;
			else
				block_dat = total_block[y + i][x + j];


			if ((block_dat == 1) && (block[shape][angle][i][j] == 1))	//좌측벽의 좌표를 빼기위함
			{
				return 1;
			}
		}
	}
	return 0;
}

int GameManager::merge_block(int shape, int angle, int x, int y)
{
	int i, j;
	for (i = 0;i < 4;i++)
	{
		for (j = 0;j < 4;j++)
		{
			total_block[y + i][x + j] |= block[shape][angle][i][j];
		}
	}
	check_full_line();
	show_total_block();

	return 0;
}

int GameManager::block_start(int shape, int* angle, int* x, int* y)
{
	*x = 5;
	*y = -3;
	*angle = 0;
	return 0;
}

int GameManager::move_block(int* shape, int* angle, int* x, int* y, int* next_shape)
{
	erase_cur_block(*shape, *angle, *x, *y);

	(*y)++;	//블럭을 한칸 아래로 내림
	if (strike_check(*shape, *angle, *x, *y) == 1)
	{
		if (*y < 0)	//게임오버
		{

			return 1;
		}
		(*y)--;
		merge_block(*shape, *angle, *x, *y);
		*shape = *next_shape;
		*next_shape = make_new_block();

		block_start(*shape, angle, x, y);	//angle,x,y는 포인터임
		show_next_block(*next_shape);
		return 2;
	}
	return 0;
}

int GameManager::rotate_block(int shape, int* angle, int* x, int* y)
{
	return 0;
}

int GameManager::show_gameover()
{
	SetColor(RED);
	gotoxy(15, 8);
	printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
	gotoxy(15, 9);
	printf("┃**************************┃");
	gotoxy(15, 10);
	printf("┃*        GAME OVER       *┃");
	gotoxy(15, 11);
	printf("┃**************************┃");
	gotoxy(15, 12);
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
	fflush(stdin);
	Sleep(1000);

	_getche();
	system("cls");

	return 0;
}

int GameManager::show_gamestat()
{
	static int printed_text = 0;
	SetColor(GRAY);
	if (printed_text == 0)
	{
		gotoxy(35, 7);
		printf("STAGE");

		gotoxy(35, 9);
		printf("SCORE");

		gotoxy(35, 12);
		printf("LINES");

	}
	gotoxy(41, 7);
	printf("%d", level + 1);
	gotoxy(35, 10);
	printf("%10d", score);
	gotoxy(35, 13);
	printf("%10d", stage_data[level].getClear_line() - lines);
	return 0;
}

int GameManager::input_data()
{
	int i = 0;
	SetColor(GRAY);
	gotoxy(10, 7);
	printf("┏━━━━━━━━━<GAME KEY>━━━━━━━━━┓");
	Sleep(10);
	gotoxy(10, 8);
	printf("┃ UP   : Rotate Block        ┃");
	Sleep(10);
	gotoxy(10, 9);
	printf("┃ DOWN : Move One-Step Down  ┃");
	Sleep(10);
	gotoxy(10, 10);
	printf("┃ SPACE: Move Bottom Down    ┃");
	Sleep(10);
	gotoxy(10, 11);
	printf("┃ LEFT : Move Left           ┃");
	Sleep(10);
	gotoxy(10, 12);
	printf("┃ RIGHT: Move Right          ┃");
	Sleep(10);
	gotoxy(10, 13);
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");


	while (i < 1 || i>8)
	{
		gotoxy(10, 3);
		printf("Select Start level[1-4]:       \b\b\b\b\b\b\b");
		scanf_s("%d", &i);
	}


	level = i - 1;
	system("cls");
	return 0;
}

int GameManager::check_full_line()
{
	int i, j, k;
	for (i = 0;i < 20;i++)
	{
		for (j = 1;j < 13;j++)
		{
			if (total_block[i][j] == 0)
				break;
		}
		if (j == 13)	//한줄이 다 채워졌음
		{
			lines++;
			show_total_block();
			SetColor(BLUE);
			gotoxy(1 * 2 + ab_x, i + ab_y);
			for (j = 1;j < 13;j++)
			{
				printf("□");
				Sleep(10);
			}
			gotoxy(1 * 2 + ab_x, i + ab_y);
			for (j = 1;j < 13;j++)
			{
				printf("  ");
				Sleep(10);
			}

			for (k = i;k > 0;k--)
			{
				for (j = 1;j < 13;j++)
					total_block[k][j] = total_block[k - 1][j];
			}
			for (j = 1;j < 13;j++)
				total_block[0][j] = 0;
			score += 100 + (level * 10) + (rand() % 10);
			show_gamestat();
		}
	}
	return 0;
}

void GameManager::SetColor(int color)
{
	static HANDLE std_output_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(std_output_handle, color);
}
