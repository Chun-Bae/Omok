#include <stdio.h>
#include <Windows.h>

#include "board.h"

#define SPACE_BAR 32

typedef struct cursor {
	int x;
	int y;
}Cursor;

int stone_color = 1;
int proceed = 1;

Cursor cursor;
INPUT_RECORD rec;
DWORD dw;
COORD pos = { 0,0 };

void DrawBoard();
void MouseClick();
void RemoveConsole();
void SwapColor();
void InputStone();
void Check_5Stone();
void CheckWidth(int check_x, int check_y);
void CheckHeight(int check_x, int check_y);
void CheckLeftUpCross(int check_x, int check_y);
void CheckRightUpCross(int check_x, int check_y);
void Manual();
void WhoWin();
void GameOver();
void gotoxy(int x, int y);

int main() {
	while (proceed) {
		DrawBoard();
		Manual();
		MouseClick();
		InputStone();
		Check_5Stone();
		RemoveConsole();
	}
	DrawBoard();
	WhoWin();
}

void MouseClick() {	
	int click_bool = 0;
	int temp_x;
	int temp_y;

	while (1) {
		SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);
		// �ܼ� �Է� ������  ��¸�� ����
		ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &rec, 1, &dw);
		// �ܼ� ���� �о����
		if (rec.EventType == MOUSE_EVENT) {
			if (rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) {
				temp_x = rec.Event.MouseEvent.dwMousePosition.X;
				temp_y = rec.Event.MouseEvent.dwMousePosition.Y;
				if (Board[temp_y - 1][temp_x / 2 - 1] == 1 || Board[temp_y - 1][temp_x / 2 - 1] == 2)
					continue;
					// �ߺ���ġ �Ұ�
				if (temp_x / 2 <= 15 && temp_x >= 2 && temp_y <= 15 && temp_y >= 1) {
					// �ٵ��� �ȿ��� ��ġ�� �� �ֵ���.					
					cursor.x = temp_x / 2;
					cursor.y = temp_y;
					// ���콺 ��ġ ��			
					gotoxy(cursor.x, cursor.y);
					puts("��");
					SwapColor();
					click_bool = 1;

				}
			}
		}
		if (click_bool == 1)
			break;
	}
	
}

void InputStone() {
	switch (_getch()) {
	case SPACE_BAR:
		Board[cursor.y - 1][cursor.x - 1] = stone_color;
		break;
	default:
		SwapColor(); 
		// ����ϴ� ��� �ٽ� �ٲ���
		break;
	}
}

void SwapColor() {
	switch (stone_color) {
	case 1:
		stone_color = 2;
		break;
	case 2:
		stone_color = 1;
		break;
	}
}

void WhoWin() {	
	gotoxy(18, 0);
	switch (stone_color) {
	case 1:
		puts("�� ��!");
		break;
	case 2:
		puts("������ ��!");
		break;
	}
	gotoxy(0, 20);
}

void GameOver() {
	proceed = 0;
}

void Check_5Stone() {
	int check_x = cursor.x - 1;
	int check_y = cursor.y - 1;

	for (int check_line = 1; check_line <= 4; check_line++) {
		switch (check_line) {
		case 1:
			// ������ üũ
			CheckWidth(check_x, check_y);
			break;
		case 2:
			// ������ üũ
			CheckHeight(check_x, check_y);
			break;
		case 3:
			// ������ �밢�� üũ
			CheckLeftUpCross(check_x, check_y);
			break;
		case 4:
			// �������� �밢�� üũ
			CheckRightUpCross(check_x, check_y);
			break;
		}
	}
}

void CheckWidth(int check_x, int check_y) {
	if (Board[check_y][check_x] == stone_color) {
		if (Board[check_y][check_x - 1] == stone_color) {
			if (Board[check_y][check_x - 2] == stone_color) {
				if (Board[check_y][check_x - 3] == stone_color) {
					if (Board[check_y][check_x - 4] == stone_color) {
						GameOver();
					}
					else if (Board[check_y][check_x + 1] == stone_color) {
						GameOver();
					}
				}
				else if (Board[check_y][check_x + 1] == stone_color) {
					if (Board[check_y][check_x + 2] == stone_color) {
						GameOver();
					}
				}
			}
			else if (Board[check_y][check_x + 1] == stone_color) {
				if (Board[check_y][check_x + 2] == stone_color) {
					if (Board[check_y][check_x + 3] == stone_color) {
						GameOver();
					}
				}
			}
		}
		else  if (Board[check_y][check_x + 1] == stone_color) {
			if (Board[check_y][check_x + 2] == stone_color) {
				if (Board[check_y][check_x + 3] == stone_color) {
					if (Board[check_y][check_x + 4] == stone_color) {
						GameOver();
					}
				}
			}
		}
	}
}

void CheckHeight(int check_x, int check_y) {
	if (Board[check_y][check_x] == stone_color) {
		if (Board[check_y - 1][check_x] == stone_color) {
			if (Board[check_y - 2][check_x] == stone_color) {
				if (Board[check_y - 3][check_x] == stone_color) {
					if (Board[check_y - 4][check_x] == stone_color) {
						GameOver();
					}
					else if (Board[check_y + 1][check_x] == stone_color) {
						GameOver();
					}
				}
				else if (Board[check_y + 1][check_x] == stone_color) {
					if (Board[check_y + 2][check_x] == stone_color) {
						GameOver();
					}
				}
			}
			else if (Board[check_y + 1][check_x] == stone_color) {
				if (Board[check_y + 2][check_x] == stone_color) {
					if (Board[check_y + 3][check_x] == stone_color) {
						GameOver();
					}
				}
			}
		}
		else  if (Board[check_y + 1][check_x] == stone_color) {
			if (Board[check_y + 2][check_x] == stone_color) {
				if (Board[check_y + 3][check_x] == stone_color) {
					if (Board[check_y + 4][check_x] == stone_color) {
						GameOver();
					}
				}
			}
		}
	}
}

void CheckLeftUpCross(int check_x, int check_y) {
	if (Board[check_y][check_x] == stone_color) {
		if (Board[check_y + 1][check_x + 1] == stone_color) {
			if (Board[check_y + 2][check_x + 2] == stone_color) {
				if (Board[check_y + 3][check_x + 3] == stone_color) {
					if (Board[check_y + 4][check_x + 4] == stone_color) {
						GameOver();
					}
					else if (Board[check_y - 1][check_x - 1] == stone_color) {
						GameOver();
					}
				}
				else if (Board[check_y - 1][check_x - 1] == stone_color) {
					if (Board[check_y - 2][check_x - 2] == stone_color) {
						GameOver();
					}
				}
			}
			else if (Board[check_y - 1][check_x - 1] == stone_color) {
				if (Board[check_y - 2][check_x - 2] == stone_color) {
					if (Board[check_y - 3][check_x - 3] == stone_color) {
						GameOver();
					}
				}
			}
		}
		else  if (Board[check_y - 1][check_x - 1] == stone_color) {
			if (Board[check_y - 2][check_x - 2] == stone_color) {
				if (Board[check_y - 3][check_x - 3] == stone_color) {
					if (Board[check_y - 4][check_x - 4] == stone_color) {
						GameOver();
					}
				}
			}
		}
	}
}

void CheckRightUpCross(int check_x, int check_y) {
	if (Board[check_y][check_x] == stone_color) {
		if (Board[check_y + 1][check_x - 1] == stone_color) {
			if (Board[check_y + 2][check_x - 2] == stone_color) {
				if (Board[check_y + 3][check_x - 3] == stone_color) {
					if (Board[check_y + 4][check_x - 4] == stone_color) {
						GameOver();
					}
					else if (Board[check_y - 1][check_x + 1] == stone_color) {
						GameOver();
					}
				}
				else if (Board[check_y - 1][check_x + 1] == stone_color) {
					if (Board[check_y - 2][check_x + 2] == stone_color) {
						GameOver();
					}
				}
			}
			else if (Board[check_y - 1][check_x + 1] == stone_color) {
				if (Board[check_y - 2][check_x + 2] == stone_color) {
					if (Board[check_y - 3][check_x + 3] == stone_color) {
						GameOver();
					}
				}
			}
		}
		else  if (Board[check_y - 1][check_x + 1] == stone_color) {
			if (Board[check_y - 2][check_x + 2] == stone_color) {
				if (Board[check_y - 3][check_x + 3] == stone_color) {
					if (Board[check_y - 4][check_x + 4] == stone_color) {
						GameOver();
					}
				}
			}
		}
	}
}



void RemoveConsole() {
	FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ', 100* 100, pos, &dw);
	// 0,0���� 100*100��ŭ ȭ�� �����
}

void Manual() {
	gotoxy(1, 18);
	printf("���� �� : ");
	switch (stone_color) {
	case 1:
		puts("��");
		break;
	case 2:
		puts("��");
		break;
	}
	printf("\n  Ŭ�� �� Space Bar�� ��������!");	
}

void DrawBoard() {
	for (int x = 0; x < Board_X; x++) {
		for (int y = 0; y < Board_Y; y++) {
			switch (Board[y][x]) {
			case 0:
				gotoxy(x + 1, y + 1);
				puts("��");
				break;
			case 1:
				gotoxy(x + 1, y + 1);
				puts("��");
				break;
			case 2:
				gotoxy(x + 1, y + 1);
				puts("��");
				break;			
			case 10:
				gotoxy(x + 1, y + 1);
				puts("��");
				break;
			case 20:
				gotoxy(x + 1, y + 1);
				puts("��");
				break;
			case 30:
				gotoxy(x + 1, y + 1);
				puts("��");
				break;
			case 40:
				gotoxy(x + 1, y + 1);
				puts("��");
				break;
			case 11:
				gotoxy(x + 1, y + 1);
				puts("��");
				break;
			case 22:
				gotoxy(x + 1, y + 1);
				puts("��");
				break;
			case 33:
				gotoxy(x + 1, y + 1);
				puts("��");
				break;
			case 44:
				gotoxy(x + 1, y + 1);
				puts("��");
				break;
			}
		}
	}
}

void gotoxy(int x, int y) {
	COORD pos = { x*2 ,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}