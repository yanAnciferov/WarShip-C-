#include <iostream>
#include <time.h>
#include <conio.h>
#include <Windows.h>
#include <Wincon.h>
#include <iomanip>

using namespace std;

HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_CURSOR_INFO cci = CONSOLE_CURSOR_INFO();
void MoveCursor(short int x, short int y)
{

	SetConsoleCursorPosition(handle, COORD{ x, y });
}



void setFontSize()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx = new CONSOLE_FONT_INFOEX();
	lpConsoleCurrentFontEx->cbSize = sizeof(CONSOLE_FONT_INFOEX);
	GetCurrentConsoleFontEx(hConsole, 0, lpConsoleCurrentFontEx);
	lpConsoleCurrentFontEx->dwFontSize.X = 16;
	lpConsoleCurrentFontEx->dwFontSize.Y = 12;
	SetCurrentConsoleFontEx(hConsole, 0, lpConsoleCurrentFontEx);
}


void SetColor(int text, int background) {
	SetConsoleTextAttribute(handle, (WORD)((background << 4) | text));
}
enum ConsoleColor {
	Black,
	Blue, //
	Green, //
	Cyan,
	Red, //
	Magenta, //
	Brown,
	LightGray,
	DarkGray,
	LightBlue,
	LightGreen,
	LightCyan,
	LightRed,
	LightMagenta,
	Yellow, //
	White,

};


struct scores
{
	char name[10];
	int score;
};





void table_score_show(scores score[8])
{

	SetColor(3, White);
	for (int i = 0; i < 24; i++)
	{
		for (int j = 0; j < 29; j++)
		{
			MoveCursor(18 + i, 7 + j);
			cout << ' ';

		}
		cout << endl;
	}
	SetColor(DarkGray, 3);
	MoveCursor(18, 36);
	for (int i = 0; i < 24; i++)
	{
		cout << char(223);
	}
	for (int i = 0; i < 29; i++)
	{
		MoveCursor(41, 7 + i);
		SetColor(DarkGray, White);
		cout << char(222);
	}
	SetColor(3, White);
	MoveCursor(20, 9);
	cout << "Name          Score";
	int j = 0;
	for (int i = 12; i < 35; i += 3)
	{

		MoveCursor(20, i);
		if (score[j].score)
		{
			cout << setw(14) << left << score[j].name << score[j].score;

		}
		else if (score[j].score == 0)
		{
			cout << "_______       ___";

		}
		j++;
	}

}

void table_score_add(scores score[8], int all)
{
	system("cls");
	system("color 30");
	int num_str = 0;
	if (score[7].score != 0 && score[7].score > all)
	{
		_getch();
		return;
	}
	for (int i = 0; i < 8; i++)
	{

		if (score[i].score == 0)
		{
			num_str = i;
			break;
		}
		else if (score[i].score < all && score[i - 1].score >= all)
		{

			for (int i = 0; i < 7 - i; i++)
			{
				score[6 - i + 1].score = score[6 - i].score;
			}
			num_str = i;
			break;
		}
	}
	table_score_show(score);
	int x = 12 + (num_str * 3);
	MoveCursor(20, x);
	for (int i = 0; i < 18; i++)
	{
		cout << ' ';
	}
	MoveCursor(34, x);
	cout << all;
	MoveCursor(20, x);
	cin.getline(score[num_str].name, 10);
	score[num_str].score = all;

	_getch();
}

void table_score_sort(scores score[8])
{
	int colvo = 0;
	for (int i = 0; i < 8; i++)
	{
		if (score[i].score != 0)
		{
			colvo++;
		}
		else break;
	}
	if (colvo == 0 || colvo == 1)
	{
		return;
	}

	for (int i = 0; i < colvo - 1; i++) {

		for (int j = 0; j < colvo - i - 1; j++) {
			if (score[j].score < score[j + 1].score) {

				int b = score[j].score;
				score[j].score = score[j + 1].score;
				score[j + 1].score = b;
				char nams[10];

				strcpy_s(nams, score[j].name);
				strcpy_s(score[j].name, score[j + 1].name);
				strcpy_s(score[j + 1].name, nams);

			}
		}
	}

}

void set_cursor_visible(bool visible) {
	GetConsoleCursorInfo(handle, &cci);
	cci.bVisible = visible;
	SetConsoleCursorInfo(handle, &cci);
}

int courd_x = 5;
int courd_y = 30;



int dest[2][8] = {
	{ -1, 0, 1, 1, 1, 0, -1, -1 },
	{ -1,-1,-1, 0, 1, 1,  1,  0 }
};

void add_ships(int mas[10][10], int shp1[2][4], int shp4[2][4], int shp2_1[2][2], int shp2_2[2][2], int shp2_3[2][2], int shp3_1[2][3], int shp3_2[2][3])
{

	//четырехпалубные
	for (int i = 0; i < 1; )
	{
		int h = rand();
		int x = rand() % 6;
		int y = rand() % 6;
		if (h % 2 == 0)
		{
			for (int j = 0; j < 4; j++)
			{
				if (mas[x][y + j] == 0)
				{

					h = 1;
				}
				else
				{
					h = 0;
					break;
				}
			}
			if (h == 1)
			{
				for (int l = 0; l < 4; l++)
				{
					shp4[0][l] = x;
					shp4[1][l] = y + l;

				}
				i++;
			}
		}
		else
		{
			for (int j = 0; j < 4; j++)
			{
				if (mas[x + j][y] == 0)
				{
					h = 1;
				}
				else
				{
					h = 0;
					break;
				}
			}
			if (h == 1)
			{
				for (int l = 0; l < 4; l++)
				{
					shp4[0][l] = x + l;
					shp4[1][l] = y;

				}
				i++;
			}
		}
	}
	for (int j = 0; j < 4; j++)
	{
		int x = shp4[0][j];
		int y = shp4[1][j];
		for (int i = 0; i < 8; i++)
		{
			if (x + dest[0][i] < 10 && y + dest[1][i] < 10 && x + dest[0][i] >= 0 && y + dest[1][i] >= 0 && mas[x + dest[0][i]][y + dest[1][i]] >= 0)
			{
				mas[x + dest[0][i]][y + dest[1][i]] = -1;
			}

		}
		for (int i = 0; i < 4; i++)
		{
			mas[x][y] = 4;
		}
	}
	for (int j = 0; j < 4; j++)
	{
		int x = shp4[0][j];
		int y = shp4[1][j];
		mas[x][y] = 4;
	}




	//Однопалубные
	for (int i = 0; i < 4;)
	{
		int x = rand() % 10;
		int y = rand() % 10;
		if (mas[x][y] == 0)
		{
			mas[x][y] = 1;
			for (int i = 0; i < 8; i++)
			{
				if (x + dest[0][i] < 10 && y + dest[1][i] < 10 && x + dest[0][i] >= 0 && y + dest[1][i] >= 0)
				{
					mas[x + dest[0][i]][y + dest[1][i]] = -1;
				}
			}
			i++;
		}
	}

	//двухпалубные
	for (int i = 0; i < 1; )
	{
		int type = 2;
		int h = rand();
		int x = rand() % 8;
		int y = rand() % 8;
		if (h % 2 == 0)
		{
			for (int j = 0; j < 2; j++)
			{
				if (mas[x][y + j] == 0)
				{

					h = 1;
				}
				else
				{
					h = 0;
					break;
				}
			}
			if (h == 1)
			{
				for (int l = 0; l < 2; l++)
				{
					shp2_1[0][l] = x;
					shp2_1[1][l] = y + l;

				}
				i++;
			}
		}
		else
		{
			for (int j = 0; j < 2; j++)
			{
				if (mas[x + j][y] == 0)
				{
					h = 1;
				}
				else
				{
					h = 0;
					break;
				}
			}
			if (h == 1)
			{
				for (int l = 0; l < 2; l++)
				{
					shp2_1[0][l] = x + l;
					shp2_1[1][l] = y;

				}
				i++;
			}
		}
	}
	for (int j = 0; j < 2; j++)
	{
		int x = shp2_1[0][j];
		int y = shp2_1[1][j];
		for (int i = 0; i < 8; i++)
		{
			if (x + dest[0][i] < 10 && y + dest[1][i] < 10 && x + dest[0][i] >= 0 && y + dest[1][i] >= 0 && mas[x + dest[0][i]][y + dest[1][i]] >= 0)
			{
				mas[x + dest[0][i]][y + dest[1][i]] = -1;
			}

		}
		for (int i = 0; i < 2; i++)
		{
			mas[x][y] = 2;
		}
	}
	for (int j = 0; j < 2; j++)
	{
		int x = shp2_1[0][j];
		int y = shp2_1[1][j];
		mas[x][y] = 2;
	}


	for (int i = 0; i < 1; )
	{
		int type = 2;
		int h = rand();
		int x = rand() % 8;
		int y = rand() % 8;
		if (h % 2 == 0)
		{
			for (int j = 0; j < 2; j++)
			{
				if (mas[x][y + j] == 0)
				{

					h = 1;
				}
				else
				{
					h = 0;
					break;
				}
			}
			if (h == 1)
			{
				for (int l = 0; l < 2; l++)
				{
					shp2_2[0][l] = x;
					shp2_2[1][l] = y + l;

				}
				i++;
			}
		}
		else
		{
			for (int j = 0; j < 2; j++)
			{
				if (mas[x + j][y] == 0)
				{
					h = 1;
				}
				else
				{
					h = 0;
					break;
				}
			}
			if (h == 1)
			{
				for (int l = 0; l < 2; l++)
				{
					shp2_2[0][l] = x + l;
					shp2_2[1][l] = y;

				}
				i++;
			}
		}
	}
	for (int j = 0; j < 2; j++)
	{
		int x = shp2_2[0][j];
		int y = shp2_2[1][j];
		for (int i = 0; i < 8; i++)
		{
			if (x + dest[0][i] < 10 && y + dest[1][i] < 10 && x + dest[0][i] >= 0 && y + dest[1][i] >= 0 && mas[x + dest[0][i]][y + dest[1][i]] >= 0)
			{
				mas[x + dest[0][i]][y + dest[1][i]] = -1;
			}

		}
		for (int i = 0; i < 2; i++)
		{
			mas[x][y] = 2;
		}
	}
	for (int j = 0; j < 2; j++)
	{
		int x = shp2_2[0][j];
		int y = shp2_2[1][j];
		mas[x][y] = 12;
	}


	for (int i = 0; i < 1; )
	{
		int type = 2;
		int h = rand();
		int x = rand() % 8;
		int y = rand() % 8;
		if (h % 2 == 0)
		{
			for (int j = 0; j < 2; j++)
			{
				if (mas[x][y + j] == 0)
				{

					h = 1;
				}
				else
				{
					h = 0;
					break;
				}
			}
			if (h == 1)
			{
				for (int l = 0; l < 2; l++)
				{
					shp2_3[0][l] = x;
					shp2_3[1][l] = y + l;

				}
				i++;
			}
		}
		else
		{
			for (int j = 0; j < 2; j++)
			{
				if (mas[x + j][y] == 0)
				{
					h = 1;
				}
				else
				{
					h = 0;
					break;
				}
			}
			if (h == 1)
			{
				for (int l = 0; l < 2; l++)
				{
					shp2_3[0][l] = x + l;
					shp2_3[1][l] = y;

				}
				i++;
			}
		}
	}
	for (int j = 0; j < 2; j++)
	{
		int x = shp2_3[0][j];
		int y = shp2_3[1][j];
		for (int i = 0; i < 8; i++)
		{
			if (x + dest[0][i] < 10 && y + dest[1][i] < 10 && x + dest[0][i] >= 0 && y + dest[1][i] >= 0 && mas[x + dest[0][i]][y + dest[1][i]] >= 0)
			{
				mas[x + dest[0][i]][y + dest[1][i]] = -1;
			}

		}
		for (int i = 0; i < 2; i++)
		{
			mas[x][y] = 2;
		}
	}
	for (int j = 0; j < 2; j++)
	{
		int x = shp2_3[0][j];
		int y = shp2_3[1][j];
		mas[x][y] = 22;
	}

	//Трехпалубные
	for (int i = 0; i < 1; )
	{

		int h = rand();
		int x = rand() % 8;
		int y = rand() % 8;
		if (h % 2 == 0)
		{
			for (int j = 0; j < 3; j++)
			{
				if (mas[x][y + j] == 0)
				{

					h = 1;
				}
				else
				{
					h = 0;
					break;
				}
			}
			if (h == 1)
			{
				for (int l = 0; l < 3; l++)
				{
					shp3_1[0][l] = x;
					shp3_1[1][l] = y + l;

				}
				i++;
			}
		}
		else
		{
			for (int j = 0; j < 3; j++)
			{
				if (mas[x + j][y] == 0)
				{
					h = 1;
				}
				else
				{
					h = 0;
					break;
				}
			}
			if (h == 1)
			{
				for (int l = 0; l < 3; l++)
				{
					shp3_1[0][l] = x + l;
					shp3_1[1][l] = y;

				}
				i++;
			}
		}
	}
	for (int j = 0; j < 3; j++)
	{
		int x = shp3_1[0][j];
		int y = shp3_1[1][j];
		for (int i = 0; i < 8; i++)
		{
			if (x + dest[0][i] < 10 && y + dest[1][i] < 10 && x + dest[0][i] >= 0 && y + dest[1][i] >= 0 && mas[x + dest[0][i]][y + dest[1][i]] >= 0)
			{
				mas[x + dest[0][i]][y + dest[1][i]] = -1;
			}

		}
		for (int i = 0; i < 3; i++)
		{
			mas[x][y] = 3;
		}
	}
	for (int j = 0; j < 2; j++)
	{
		int x = shp3_1[0][j];
		int y = shp3_1[1][j];
		mas[x][y] = 3;
	}



	for (int i = 0; i < 1; )
	{

		int h = rand();
		int x = rand() % 8;
		int y = rand() % 8;
		if (h % 2 == 0)
		{
			for (int j = 0; j < 3; j++)
			{
				if (mas[x][y + j] == 0)
				{

					h = 1;
				}
				else
				{
					h = 0;
					break;
				}
			}
			if (h == 1)
			{
				for (int l = 0; l < 3; l++)
				{
					shp3_2[0][l] = x;
					shp3_2[1][l] = y + l;

				}
				i++;
			}
		}
		else
		{
			for (int j = 0; j < 3; j++)
			{
				if (mas[x + j][y] == 0)
				{
					h = 1;
				}
				else
				{
					h = 0;
					break;
				}
			}
			if (h == 1)
			{
				for (int l = 0; l < 3; l++)
				{
					shp3_2[0][l] = x + l;
					shp3_2[1][l] = y;

				}
				i++;
			}
		}
	}
	for (int j = 0; j < 3; j++)
	{
		int x = shp3_2[0][j];
		int y = shp3_2[1][j];
		for (int i = 0; i < 8; i++)
		{
			if (x + dest[0][i] < 10 && y + dest[1][i] < 10 && x + dest[0][i] >= 0 && y + dest[1][i] >= 0 && mas[x + dest[0][i]][y + dest[1][i]] >= 0)
			{
				mas[x + dest[0][i]][y + dest[1][i]] = -1;
			}

		}
		for (int i = 0; i < 3; i++)
		{
			mas[x][y] = 13;
		}
	}
	for (int j = 0; j < 2; j++)
	{
		int x = shp3_2[0][j];
		int y = shp3_2[1][j];
		mas[x][y] = 13;
	}



	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (mas[i][j] == -1)
				mas[i][j] = 0;
		}
	}
}

int type = 0;
int ee_x = 0, ee_y = 0;

int ee_hp[6]{ 2,2,2,3,3,4 };
int ee_goriz;
int x_c = 0, y_c = 0;
int ee_ships;


void ee_enter(int x, int y, int mas[10][10])
{
	if (mas[x][y] == -2)
	{
		SetColor(Red, Red);
		MoveCursor(courd_y + y * 2, courd_x + x * 2);
		cout << ' ';
		MoveCursor(courd_y + y * 2 + 1, courd_x + x * 2 + 1);
		cout << ' ';
		MoveCursor(courd_y + y * 2 + 1, courd_x + x * 2);
		cout << ' ';
		MoveCursor(courd_y + y * 2, courd_x + x * 2 + 1);
		cout << ' ';
		MoveCursor(0, 0);
	}
	else if (mas[x][y] == -1)
	{
		SetColor(Black, Blue);
		MoveCursor(courd_y + y * 2, courd_x + x * 2);
		cout << (char)176;
		MoveCursor(courd_y + y * 2 + 1, courd_x + x * 2 + 1);
		cout << (char)176;
		MoveCursor(courd_y + y * 2 + 1, courd_x + x * 2);
		cout << (char)176;
		MoveCursor(courd_y + y * 2, courd_x + x * 2 + 1);
		cout << (char)176;
		MoveCursor(0, 0);
	}
	else if (mas[x][y] == 0)
	{
		SetColor(Blue, Blue);
		MoveCursor(courd_y + y * 2, courd_x + x * 2);
		cout << ' ';
		MoveCursor(courd_y + y * 2 + 1, courd_x + x * 2 + 1);
		cout << ' ';
		MoveCursor(courd_y + y * 2 + 1, courd_x + x * 2);
		cout << ' ';
		MoveCursor(courd_y + y * 2, courd_x + x * 2 + 1);
		cout << ' ';
		MoveCursor(0, 0);
	}
	else if (mas[x][y] > 0)
	{
		SetColor(White, White);
		MoveCursor(courd_y + y * 2, courd_x + x * 2);
		cout << ' ';
		MoveCursor(courd_y + y * 2 + 1, courd_x + x * 2 + 1);
		cout << ' ';
		MoveCursor(courd_y + y * 2 + 1, courd_x + x * 2);
		cout << ' ';
		MoveCursor(courd_y + y * 2, courd_x + x * 2 + 1);
		cout << ' ';
		MoveCursor(0, 0);
	}

}

int ee_hod(int mas[10][10], int shp1[2][4], int shp4[2][4], int shp2_1[2][2], int shp2_2[2][2], int shp2_3[2][2], int shp3_1[2][3], int shp3_2[2][3])
{
	srand(time(0));
	if (type == 0)
	{
		for (int i = 0; i < 1;)
		{
			ee_x = rand() % 10;
			ee_y = rand() % 10;
			if (mas[ee_x][ee_y] >= 0)
			{
				i++;
			}
		}
	}
	else if (type == 2)
	{
		int rad;
		for (int i = 0; i < 1;)
		{
			rad = rand() % 4;
			if (rad == 0 && mas[ee_x + 1][ee_y] == 0 && ee_x + 1 < 10)
			{
				mas[ee_x + 1][ee_y] = -1;
				ee_enter(ee_x + 1, ee_y, mas);
				i++;
				return 0;
			}
			else if (rad == 0 && mas[ee_x + 1][ee_y] > 0 && ee_x + 1 < 10)
			{
				ee_x += 1;
				i++;
			}
			else if (rad == 1 && mas[ee_x][ee_y + 1] == 0 && ee_y + 1 < 10)
			{
				mas[ee_x][ee_y + 1] = -1;
				ee_enter(ee_x, ee_y + 1, mas);
				i++;
				return 0;
			}
			else if (rad == 1 && mas[ee_x][ee_y + 1] > 0 && ee_y + 1 < 10)
			{
				ee_y += 1;
				i++;
			}
			else if (rad == 2 && mas[ee_x - 1][ee_y] == 0 && ee_x - 1 >= 0)
			{
				mas[ee_x - 1][ee_y] = -1;
				ee_enter(ee_x - 1, ee_y, mas);
				i++;
				return 0;
			}
			else if (rad == 2 && mas[ee_x - 1][ee_y] > 0 && ee_x - 1 >= 0)
			{
				ee_x -= 1;
				i++;
			}
			else if (rad == 3 && mas[ee_x][ee_y - 1] == 0 && ee_y - 1 >= 0)
			{
				mas[ee_x][ee_y - 1] = -1;
				ee_enter(ee_x, ee_y - 1, mas);
				i++;
				return 0;
			}
			else if (rad == 3 && mas[ee_x][ee_y - 1] > 0 && ee_y - 1 >= 0)
			{
				ee_y -= 1;
				i++;
			}
		}

	}
	else if (type == 3)
	{
		int rad;
		if (ee_goriz == 0)
		{
			x_c = ee_x;
			y_c = ee_y;
			for (int i = 0; i < 1;)
			{
				rad = rand() % 4;
				if (rad == 0 && mas[ee_x + 1][ee_y] == 0 && ee_x + 1 < 10)
				{
					mas[ee_x + 1][ee_y] = -1;
					ee_enter(ee_x + 1, ee_y, mas);
					i++;
					return 0;
				}
				else if (rad == 0 && mas[ee_x + 1][ee_y] > 0 && ee_x + 1 < 10)
				{
					ee_x += 1;
					i++;
					ee_goriz = 1;
				}
				else if (rad == 1 && mas[ee_x][ee_y + 1] == 0 && ee_y + 1 < 10)
				{
					mas[ee_x][ee_y + 1] = -1;
					ee_enter(ee_x, ee_y + 1, mas);
					i++;
					return 0;
				}
				else if (rad == 1 && mas[ee_x][ee_y + 1] > 0 && ee_y + 1 < 10)
				{
					ee_y += 1;
					i++;
					ee_goriz = 2;
				}
				else if (rad == 2 && mas[ee_x - 1][ee_y] == 0 && ee_x - 1 >= 0)
				{
					mas[ee_x - 1][ee_y] = -1;
					ee_enter(ee_x - 1, ee_y, mas);
					i++;
					return 0;
				}
				else if (rad == 2 && mas[ee_x - 1][ee_y] > 0 && ee_x - 1 >= 0)
				{
					ee_x -= 1;
					i++;
					ee_goriz = 1;
				}
				else if (rad == 3 && mas[ee_x][ee_y - 1] == 0 && ee_y - 1 >= 0)
				{
					mas[ee_x][ee_y - 1] = -1;
					ee_enter(ee_x, ee_y - 1, mas);
					i++;
					return 0;
				}
				else if (rad == 3 && mas[ee_x][ee_y - 1] > 0 && ee_y - 1 >= 0)
				{
					ee_y -= 1;
					i++;
					ee_goriz = 2;
				}
			}
		}
		else if (ee_goriz == 1)
		{

			for (int i = 0; i < 1;)
			{
				rad = rand() % 2;
				if (rad == 0 && mas[ee_x + 1][ee_y] == 0 && ee_x + 1 < 10)
				{
					mas[ee_x + 1][ee_y] = -1;
					ee_enter(ee_x + 1, ee_y, mas);
					i++;
					return 0;
				}
				else if (rad == 0 && mas[ee_x + 1][ee_y] > 0 && ee_x + 1 < 10)
				{
					ee_x += 1;
					i++;
					continue;
				}
				else if (rad == 1 && mas[ee_x - 1][ee_y] == 0 && ee_x - 1 >= 0)
				{
					mas[ee_x - 1][ee_y] = -1;
					ee_enter(ee_x - 1, ee_y, mas);
					i++;
					return 0;

				}
				else if (rad == 1 && mas[ee_x - 1][ee_y] > 0 && ee_x - 1 >= 0)
				{
					ee_x -= 1;
					i++;
					continue;

				}
				if ((ee_x + 1 > 9 || mas[ee_x + 1][ee_y] == -1) && (ee_x - 1 < 0 || mas[ee_x - 1][ee_y] == -2))
				{
					ee_x -= 1;
				}
				else if ((ee_x + 1 > 9 || mas[ee_x + 1][ee_y] == -2) && (ee_x - 1 < 0 || mas[ee_x - 1][ee_y] == -1))
				{
					ee_x += 1;
				}
				else if (mas[ee_x - 1][ee_y] == -2 && mas[ee_x + 1][ee_y] == -2)
				{
					ee_x = x_c;
					ee_y = y_c;
				}
			}
		}
		else if (ee_goriz == 2)
		{

			for (int i = 0; i < 1;)
			{
				rad = rand() % 2;
				if (rad == 0 && mas[ee_x][ee_y + 1] == 0 && ee_y + 1 < 10)
				{
					mas[ee_x][ee_y + 1] = -1;
					ee_enter(ee_x, ee_y + 1, mas);
					i++;
					return 0;
				}
				else if (rad == 0 && mas[ee_x][ee_y + 1] > 0 && ee_y + 1 < 10)
				{
					ee_y += 1;
					i++;
					continue;
				}
				else if (rad == 1 && mas[ee_x][ee_y - 1] == 0 && ee_y - 1 >= 0)
				{
					mas[ee_x][ee_y - 1] = -1;
					ee_enter(ee_x, ee_y - 1, mas);
					i++;
					return 0;
				}
				else if (rad == 1 && mas[ee_x][ee_y - 1] > 0 && ee_y - 1 >= 0)
				{
					ee_y -= 1;
					i++;
					continue;
				}
				if ((ee_y + 1 > 9 || mas[ee_x][ee_y + 1] == -1) && (ee_y - 1 < 0 || mas[ee_x][ee_y - 1] == -2))
				{
					ee_y -= 1;
				}
				else if ((ee_y + 1 > 9 || mas[ee_x][ee_y + 1] == -2) && (ee_y - 1 < 0 || mas[ee_x][ee_y - 1] == -1))
				{
					ee_y += 1;
				}
				else if (mas[ee_x][ee_y - 1] == -2 && mas[ee_x][ee_y + 1] == -2)
				{
					ee_x = x_c;
					ee_y = y_c;
				}
			}
		}

	}

	if (mas[ee_x][ee_y] == 0)
	{
		mas[ee_x][ee_y] = -1;
		ee_enter(ee_x, ee_y, mas);
		return 0;
	}
	else if (mas[ee_x][ee_y] == 1)
	{
		ee_ships--;

		for (int i = 0; i < 8; i++)
		{
			if (ee_x + dest[0][i] < 10 && ee_y + dest[1][i] < 10 && ee_x + dest[0][i] >= 0 && ee_y + dest[1][i] >= 0 && mas[ee_x + dest[0][i]][ee_y + dest[1][i]] >= 0)
			{
				mas[ee_x + dest[0][i]][ee_y + dest[1][i]] = -1;
				ee_enter(ee_x + dest[0][i], ee_y + dest[1][i], mas);
			}

		}
		mas[ee_x][ee_y] = -2;
		ee_enter(ee_x, ee_y, mas);
	}
	else if (mas[ee_x][ee_y] == 2)
	{
		type = 2;
		ee_hp[0]--;
		if (ee_hp[0] == 0)
		{
			type = 0;
			ee_ships--;

			for (int j = 0; j < 2; j++)
			{
				for (int i = 0; i < 8; i++)
				{
					if (shp2_1[0][j] + dest[0][i] < 10 && shp2_1[1][j] + dest[1][i] < 10 && shp2_1[0][j] + dest[0][i] >= 0 && shp2_1[1][j] + dest[1][i] >= 0 && mas[shp2_1[0][j] + dest[0][i]][shp2_1[1][j] + dest[1][i]] >= 0)
					{
						mas[shp2_1[0][j] + dest[0][i]][shp2_1[1][j] + dest[1][i]] = -1;
						ee_enter(shp2_1[0][j] + dest[0][i], shp2_1[1][j] + dest[1][i], mas);
					}

				}
			}
			mas[ee_x][ee_y] = -2;
			ee_enter(ee_x, ee_y, mas);
		}
		else {

			mas[ee_x][ee_y] = -2;
			ee_enter(ee_x, ee_y, mas);
		}
	}
	else if (mas[ee_x][ee_y] == 12)
	{
		type = 2;
		ee_hp[1]--;
		if (ee_hp[1] == 0)
		{
			type = 0;
			ee_ships--;

			for (int j = 0; j < 2; j++)
			{
				for (int i = 0; i < 8; i++)
				{
					if (shp2_2[0][j] + dest[0][i] < 10 && shp2_2[1][j] + dest[1][i] < 10 && shp2_2[0][j] + dest[0][i] >= 0 && shp2_2[1][j] + dest[1][i] >= 0 && mas[shp2_2[0][j] + dest[0][i]][shp2_2[1][j] + dest[1][i]] >= 0)
					{
						mas[shp2_2[0][j] + dest[0][i]][shp2_2[1][j] + dest[1][i]] = -1;
						ee_enter(shp2_2[0][j] + dest[0][i], shp2_2[1][j] + dest[1][i], mas);
					}

				}
			}
			mas[ee_x][ee_y] = -2;
			ee_enter(ee_x, ee_y, mas);
		}
		else {

			mas[ee_x][ee_y] = -2;
			ee_enter(ee_x, ee_y, mas);
		}
	}
	else if (mas[ee_x][ee_y] == 22)
	{
		type = 2;
		ee_hp[2]--;
		if (ee_hp[2] == 0)
		{
			type = 0;
			ee_ships--;

			for (int j = 0; j < 2; j++)
			{
				for (int i = 0; i < 8; i++)
				{
					if (shp2_3[0][j] + dest[0][i] < 10 && shp2_3[1][j] + dest[1][i] < 10 && shp2_3[0][j] + dest[0][i] >= 0 && shp2_3[1][j] + dest[1][i] >= 0 && mas[shp2_3[0][j] + dest[0][i]][shp2_3[1][j] + dest[1][i]] >= 0)
					{
						mas[shp2_3[0][j] + dest[0][i]][shp2_3[1][j] + dest[1][i]] = -1;
						ee_enter(shp2_3[0][j] + dest[0][i], shp2_3[1][j] + dest[1][i], mas);
					}

				}
			}
			mas[ee_x][ee_y] = -2;
			ee_enter(ee_x, ee_y, mas);
		}
		else {

			mas[ee_x][ee_y] = -2;
			ee_enter(ee_x, ee_y, mas);
		}
	}
	else if (mas[ee_x][ee_y] == 3)
	{

		type = 3;
		ee_hp[3]--;
		if (ee_hp[3] == 0)
		{
			ee_goriz = 0;
			type = 0;
			ee_ships--;

			for (int j = 0; j < 3; j++)
			{
				for (int i = 0; i < 8; i++)
				{
					if (shp3_1[0][j] + dest[0][i] < 10 && shp3_1[1][j] + dest[1][i] < 10 && shp3_1[0][j] + dest[0][i] >= 0 && shp3_1[1][j] + dest[1][i] >= 0 && mas[shp3_1[0][j] + dest[0][i]][shp3_1[1][j] + dest[1][i]] >= 0)
					{
						mas[shp3_1[0][j] + dest[0][i]][shp3_1[1][j] + dest[1][i]] = -1;
						ee_enter(shp3_1[0][j] + dest[0][i], shp3_1[1][j] + dest[1][i], mas);
					}

				}
			}
			mas[ee_x][ee_y] = -2;
			ee_enter(ee_x, ee_y, mas);
		}
		else {

			mas[ee_x][ee_y] = -2;
			ee_enter(ee_x, ee_y, mas);
		}
	}
	else if (mas[ee_x][ee_y] == 13)
	{
		type = 3;
		ee_hp[4]--;
		if (ee_hp[4] == 0)
		{
			ee_goriz = 0;
			type = 0;
			ee_ships--;

			for (int j = 0; j < 3; j++)
			{
				for (int i = 0; i < 8; i++)
				{
					if (shp3_2[0][j] + dest[0][i] < 10 && shp3_2[1][j] + dest[1][i] < 10 && shp3_2[0][j] + dest[0][i] >= 0 && shp3_2[1][j] + dest[1][i] >= 0 && mas[shp3_2[0][j] + dest[0][i]][shp3_2[1][j] + dest[1][i]] >= 0)
					{
						mas[shp3_2[0][j] + dest[0][i]][shp3_2[1][j] + dest[1][i]] = -1;
						ee_enter(shp3_2[0][j] + dest[0][i], shp3_2[1][j] + dest[1][i], mas);
					}

				}
			}
			mas[ee_x][ee_y] = -2;
			ee_enter(ee_x, ee_y, mas);
		}
		else {

			mas[ee_x][ee_y] = -2;
			ee_enter(ee_x, ee_y, mas);
		}
	}
	else if (mas[ee_x][ee_y] == 4)
	{
		type = 3;
		ee_hp[5]--;
		if (ee_hp[5] == 0)
		{
			type = 0;
			ee_goriz = 0;
			ee_ships--;
			for (int j = 0; j < 4; j++)
			{
				for (int i = 0; i < 8; i++)
				{
					if (shp4[0][j] + dest[0][i] < 10 && shp4[1][j] + dest[1][i] < 10 && shp4[0][j] + dest[0][i] >= 0 && shp4[1][j] + dest[1][i] >= 0 && mas[shp4[0][j] + dest[0][i]][shp4[1][j] + dest[1][i]] >= 0)
					{
						mas[shp4[0][j] + dest[0][i]][shp4[1][j] + dest[1][i]] = -1;
						ee_enter(shp4[0][j] + dest[0][i], shp4[1][j] + dest[1][i], mas);
					}

				}
			}
			mas[ee_x][ee_y] = -2;
			ee_enter(ee_x, ee_y, mas);
		}
		else {

			mas[ee_x][ee_y] = -2;
			ee_enter(ee_x, ee_y, mas);
		}
	}
	else mas[ee_x][ee_y] = -2;



}



void enter(int x, int y, int ee_mas[10][10])
{
	if (ee_mas[x][y] == -2)
	{
		SetColor(Red, Red);
		MoveCursor(courd_y + y * 2 - 25, courd_x + x * 2);
		cout << ' ';
		MoveCursor(courd_y + y * 2 + 1 - 25, courd_x + x * 2 + 1);
		cout << ' ';
		MoveCursor(courd_y + y * 2 + 1 - 25, courd_x + x * 2);
		cout << ' ';
		MoveCursor(courd_y + y * 2 - 25, courd_x + x * 2 + 1);
		cout << ' ';
		MoveCursor(0, 0);
	}
	else if (ee_mas[x][y] == -1)
	{
		SetColor(Black, Blue);
		MoveCursor(courd_y + y * 2 - 25, courd_x + x * 2);
		cout << char(176);
		MoveCursor(courd_y + y * 2 + 1 - 25, courd_x + x * 2 + 1);
		cout << char(176);
		MoveCursor(courd_y + y * 2 + 1 - 25, courd_x + x * 2);
		cout << char(176);
		MoveCursor(courd_y + y * 2 - 25, courd_x + x * 2 + 1);
		cout << char(176);
		MoveCursor(0, 0);
	}
	else
	{
		SetColor(Blue, Blue);
		MoveCursor(courd_y + y * 2 - 25, courd_x + x * 2);
		cout << ' ';
		MoveCursor(courd_y + y * 2 + 1 - 25, courd_x + x * 2 + 1);
		cout << ' ';
		MoveCursor(courd_y + y * 2 + 1 - 25, courd_x + x * 2);
		cout << ' ';
		MoveCursor(courd_y + y * 2 - 25, courd_x + x * 2 + 1);
		cout << ' ';
		MoveCursor(0, 0);
	}

}



void shoy_cours(int mas[10][10], int x, int y)
{
	if (mas[x][y] == -1)
	{
		MoveCursor(courd_y + y * 2 - 25, courd_x + x * 2);
		SetColor(Blue, Black);
		MoveCursor(courd_y + y * 2 - 25, courd_x + x * 2);
		cout << char(176);
		MoveCursor(courd_y + y * 2 + 1 - 25, courd_x + x * 2 + 1);
		cout << char(176);;
		MoveCursor(courd_y + y * 2 + 1 - 25, courd_x + x * 2);
		cout << char(176);;
		MoveCursor(courd_y + y * 2 - 25, courd_x + x * 2 + 1);
		cout << char(176);;
		MoveCursor(0, 0);
	}
	else if (mas[x][y] == -2)
	{
		MoveCursor(courd_y + y * 2 - 25, courd_x + x * 2);
		SetColor(LightRed, LightRed);
		MoveCursor(courd_y + y * 2 - 25, courd_x + x * 2);
		cout << ' ';
		MoveCursor(courd_y + y * 2 + 1 - 25, courd_x + x * 2 + 1);
		cout << ' ';
		MoveCursor(courd_y + y * 2 + 1 - 25, courd_x + x * 2);
		cout << ' ';
		MoveCursor(courd_y + y * 2 - 25, courd_x + x * 2 + 1);
		cout << ' ';
		MoveCursor(0, 0);
	}
	else
	{
		MoveCursor(courd_y + y * 2 - 25, courd_x + x * 2);
		SetColor(LightBlue, LightBlue);
		MoveCursor(courd_y + y * 2 - 25, courd_x + x * 2);
		cout << ' ';
		MoveCursor(courd_y + y * 2 + 1 - 25, courd_x + x * 2 + 1);
		cout << ' ';
		MoveCursor(courd_y + y * 2 + 1 - 25, courd_x + x * 2);
		cout << ' ';
		MoveCursor(courd_y + y * 2 - 25, courd_x + x * 2 + 1);
		cout << ' ';
		MoveCursor(0, 0);
	}

}

void shoy(int player[10][10], int ee_player[10][10])
{
	/*SetColor(0, 15);
	for (int i = 4; i < 26; i++)
	{
	for (int j = 4; j < 26; j++)
	{
	MoveCursor(j, i);
	cout << char(178);
	MoveCursor(j + 25, i);
	cout << char(178);
	}
	}*/
	SetColor(White, 3);
	MoveCursor(courd_x + 6, courd_y - 28);
	cout << "Computer";
	MoveCursor(courd_x + 32, courd_y - 28);
	cout << "Player";

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			enter(i, j, ee_player);
			ee_enter(i, j, player);
		}
	}

}

void show_lose(int lx, int ly, int i)
{

	SetColor(DarkGray, DarkGray);
	MoveCursor(courd_y + ly * 2 - 25 + dest[0][i], courd_x + lx * 2 + dest[1][i]);
	cout << ' ';
	MoveCursor(courd_y + ly * 2 + 1 - 25 + dest[0][i], courd_x + lx * 2 + 1 + dest[1][i]);
	cout << ' ';
	MoveCursor(courd_y + ly * 2 + 1 - 25 + dest[0][i], courd_x + lx * 2 + dest[1][i]);
	cout << ' ';
	MoveCursor(courd_y + ly * 2 - 25 + dest[0][i], courd_x + lx * 2 + 1 + 1);
	cout << ' ';
	MoveCursor(0, 0);
}

void shoy_score()
{
	SetColor(3, LightGray);

	for (int i = 28; i < 37; i++)
	{
		SetColor(3, LightGray);
		for (int j = 5; j < 49; j++)
		{
			MoveCursor(j, i);
			cout << ' ';
		}
		SetColor(DarkGray, LightGray);
		cout << (char)222 << endl;

	}
	SetColor(DarkGray, 3);
	for (int i = 5; i < 50; i++)
	{

		MoveCursor(i, 37);
		cout << (char)223;
	}
	SetColor(3, LightGray);
	MoveCursor(7, 30);
	cout << "Ships: \t\t      Ships:";
	MoveCursor(7, 33);
	cout << "Score: ";

}


void war_ship(scores scorh[8])
{

	int player[10][10]{};
	int ships = 10;
	int shp1[2][4];
	int ship2_1[2][2];
	int ship2_2[2][2];
	int ship2_3[2][2];
	int ship3_1[2][3];
	int ship3_2[2][3];
	int ship4[2][4];

	int tochn = 100;
	int score = 0;
	int hp[6]{ 2,2,2,3,3,4 };
	int x = 0, y = 0;

	//////////////////////////////////////////////////////////////////////////////
	int ee_player[10][10]{};

	int ee_shp1[2][4];
	int ee_ship2_1[2][2];
	int ee_ship2_2[2][2];
	int ee_ship2_3[2][2];
	int ee_ship3_1[2][3];
	int ee_ship3_2[2][3];
	int ee_ship4[2][4];

	ee_ships = 10;
	type = 0;
	ee_x = 0, ee_y = 0;

	ee_hp[0] = 2;
	ee_hp[1] = 2;
	ee_hp[2] = 2;
	ee_hp[3] = 3;
	ee_hp[4] = 3;
	ee_hp[5] = 4;

	x_c = 0, y_c = 0;

	srand(time(0));
	add_ships(ee_player, ee_shp1, ee_ship4, ee_ship2_1, ee_ship2_2, ee_ship2_3, ee_ship3_1, ee_ship3_2);
	add_ships(player, shp1, ship4, ship2_1, ship2_2, ship2_3, ship3_1, ship3_2);
	/////////////////////////////////////////////////////////////////////////////
	char prov;
	SetColor(0, 0);

	shoy(ee_player, player);
	shoy_cours(player, x, y);
	shoy_score();


	while (1)
	{
		SetColor(3, LightGray);
		MoveCursor(14, 30);
		cout << "  ";
		MoveCursor(14, 30);
		cout << ships;
		MoveCursor(37, 30);
		cout << "  ";
		MoveCursor(37, 30);
		cout << ee_ships;
		MoveCursor(14, 33);
		cout << score;
		setlocale(0, " ");
		prov = _getch();
		if ((prov == 'w' || prov == 'ц' || prov == 72) && x - 1 >= 0)
		{
			if (player[x][y] == -1)
			{
				MoveCursor(courd_y + y * 2 - 25, courd_x + x * 2);
				SetColor(Black, Blue);
				MoveCursor(courd_y + y * 2 - 25, courd_x + x * 2);
				cout << char(176);
				MoveCursor(courd_y + y * 2 + 1 - 25, courd_x + x * 2 + 1);
				cout << char(176);
				MoveCursor(courd_y + y * 2 + 1 - 25, courd_x + x * 2);
				cout << char(176);
				MoveCursor(courd_y + y * 2 - 25, courd_x + x * 2 + 1);
				cout << char(176);
				MoveCursor(0, 0);
			}
			else if (player[x][y] == -2)
			{
				MoveCursor(courd_y + y * 2 - 25, courd_x + x * 2);
				SetColor(Red, Red);
				MoveCursor(courd_y + y * 2 - 25, courd_x + x * 2);
				cout << ' ';
				MoveCursor(courd_y + y * 2 + 1 - 25, courd_x + x * 2 + 1);
				cout << ' ';
				MoveCursor(courd_y + y * 2 + 1 - 25, courd_x + x * 2);
				cout << ' ';
				MoveCursor(courd_y + y * 2 - 25, courd_x + x * 2 + 1);
				cout << ' ';
				MoveCursor(0, 0);
			}
			else
			{
				MoveCursor(courd_y + y * 2 - 25, courd_x + x * 2);
				SetColor(Blue, Blue);
				MoveCursor(courd_y + y * 2 - 25, courd_x + x * 2);
				cout << ' ';
				MoveCursor(courd_y + y * 2 + 1 - 25, courd_x + x * 2 + 1);
				cout << ' ';
				MoveCursor(courd_y + y * 2 + 1 - 25, courd_x + x * 2);
				cout << ' ';
				MoveCursor(courd_y + y * 2 - 25, courd_x + x * 2 + 1);
				cout << ' ';
				MoveCursor(0, 0);
			}
			x--;

		}
		else if ((prov == 's' || prov == 'ы' || prov == 80) && x + 1 < 10)
		{
			if (player[x][y] == -1)
			{
				MoveCursor(courd_y + y * 2 - 25, courd_x + x * 2);
				SetColor(Black, Blue);
				MoveCursor(courd_y + y * 2 - 25, courd_x + x * 2);
				cout << char(176);
				MoveCursor(courd_y + y * 2 + 1 - 25, courd_x + x * 2 + 1);
				cout << char(176);
				MoveCursor(courd_y + y * 2 + 1 - 25, courd_x + x * 2);
				cout << char(176);
				MoveCursor(courd_y + y * 2 - 25, courd_x + x * 2 + 1);
				cout << char(176);
				MoveCursor(0, 0);
			}
			else if (player[x][y] == -2)
			{
				MoveCursor(courd_y + y * 2 - 25, courd_x + x * 2);
				SetColor(Red, Red);
				MoveCursor(courd_y + y * 2 - 25, courd_x + x * 2);
				cout << ' ';
				MoveCursor(courd_y + y * 2 + 1 - 25, courd_x + x * 2 + 1);
				cout << ' ';
				MoveCursor(courd_y + y * 2 + 1 - 25, courd_x + x * 2);
				cout << ' ';
				MoveCursor(courd_y + y * 2 - 25, courd_x + x * 2 + 1);
				cout << ' ';
				MoveCursor(0, 0);
			}
			else
			{
				MoveCursor(courd_y + y * 2 - 25, courd_x + x * 2);
				SetColor(Blue, Blue);
				MoveCursor(courd_y + y * 2 - 25, courd_x + x * 2);
				cout << ' ';
				MoveCursor(courd_y + y * 2 + 1 - 25, courd_x + x * 2 + 1);
				cout << ' ';
				MoveCursor(courd_y + y * 2 + 1 - 25, courd_x + x * 2);
				cout << ' ';
				MoveCursor(courd_y + y * 2 - 25, courd_x + x * 2 + 1);
				cout << ' ';
				MoveCursor(0, 0);
			}
			x++;

		}
		else if ((prov == 'a' || prov == 'ф' || prov == 75) && y - 1 >= 0)
		{
			if (player[x][y] == -1)
			{
				MoveCursor(courd_y + y * 2 - 25, courd_x + x * 2);
				SetColor(Black, Blue);
				MoveCursor(courd_y + y * 2 - 25, courd_x + x * 2);
				cout << char(176);
				MoveCursor(courd_y + y * 2 + 1 - 25, courd_x + x * 2 + 1);
				cout << char(176);
				MoveCursor(courd_y + y * 2 + 1 - 25, courd_x + x * 2);
				cout << char(176);
				MoveCursor(courd_y + y * 2 - 25, courd_x + x * 2 + 1);
				cout << char(176);
				MoveCursor(0, 0);
			}
			else if (player[x][y] == -2)
			{
				MoveCursor(courd_y + y * 2 - 25, courd_x + x * 2);
				SetColor(Red, Red);
				MoveCursor(courd_y + y * 2 - 25, courd_x + x * 2);
				cout << ' ';
				MoveCursor(courd_y + y * 2 + 1 - 25, courd_x + x * 2 + 1);
				cout << ' ';
				MoveCursor(courd_y + y * 2 + 1 - 25, courd_x + x * 2);
				cout << ' ';
				MoveCursor(courd_y + y * 2 - 25, courd_x + x * 2 + 1);
				cout << ' ';
				MoveCursor(0, 0);
			}
			else
			{
				MoveCursor(courd_y + y * 2 - 25, courd_x + x * 2);
				SetColor(Blue, Blue);
				MoveCursor(courd_y + y * 2 - 25, courd_x + x * 2);
				cout << ' ';
				MoveCursor(courd_y + y * 2 + 1 - 25, courd_x + x * 2 + 1);
				cout << ' ';
				MoveCursor(courd_y + y * 2 + 1 - 25, courd_x + x * 2);
				cout << ' ';
				MoveCursor(courd_y + y * 2 - 25, courd_x + x * 2 + 1);
				cout << ' ';
				MoveCursor(0, 0);
			}
			y--;

		}
		else if ((prov == 'd' || prov == 'в' || prov == 77) && y + 1 < 10)
		{
			if (player[x][y] == -1)
			{
				MoveCursor(courd_y + y * 2 - 25, courd_x + x * 2);
				SetColor(Black, Blue);
				MoveCursor(courd_y + y * 2 - 25, courd_x + x * 2);
				cout << char(176);
				MoveCursor(courd_y + y * 2 + 1 - 25, courd_x + x * 2 + 1);
				cout << char(176);
				MoveCursor(courd_y + y * 2 + 1 - 25, courd_x + x * 2);
				cout << char(176);
				MoveCursor(courd_y + y * 2 - 25, courd_x + x * 2 + 1);
				cout << char(176);
				MoveCursor(0, 0);
			}
			else if (player[x][y] == -2)
			{
				MoveCursor(courd_y + y * 2 - 25, courd_x + x * 2);
				SetColor(Red, Red);
				MoveCursor(courd_y + y * 2 - 25, courd_x + x * 2);
				cout << ' ';
				MoveCursor(courd_y + y * 2 + 1 - 25, courd_x + x * 2 + 1);
				cout << ' ';
				MoveCursor(courd_y + y * 2 + 1 - 25, courd_x + x * 2);
				cout << ' ';
				MoveCursor(courd_y + y * 2 - 25, courd_x + x * 2 + 1);
				cout << ' ';
				MoveCursor(0, 0);
			}
			else
			{
				MoveCursor(courd_y + y * 2 - 25, courd_x + x * 2);
				SetColor(Blue, Blue);
				MoveCursor(courd_y + y * 2 - 25, courd_x + x * 2);
				cout << ' ';
				MoveCursor(courd_y + y * 2 + 1 - 25, courd_x + x * 2 + 1);
				cout << ' ';
				MoveCursor(courd_y + y * 2 + 1 - 25, courd_x + x * 2);
				cout << ' ';
				MoveCursor(courd_y + y * 2 - 25, courd_x + x * 2 + 1);
				cout << ' ';
				MoveCursor(0, 0);
			}
			y++;

		}
		else if (prov == 13 || prov == ' ')
		{
			if (player[x][y] == 0)
			{
				tochn--;
				player[x][y] = -1;
				enter(x, y, player);
				while (1) {
					Sleep(500);
					if (!ee_hod(ee_player, ee_shp1, ee_ship4, ee_ship2_1, ee_ship2_2, ee_ship2_3, ee_ship3_1, ee_ship3_2))
					{
						if (!ee_ships) {
							system("cls");
							system("color 30");
							for (int i = 20; i < 23; i++)
							{
								for (int j = 19; j < 31; j++)
								{

									SetColor(LightGray, LightGray);

									MoveCursor(j, i);
									cout << ' ';
								}

								SetColor(DarkGray, LightGray);
								cout << char(222);
							}
							for (int i = 19; i < 32; i++)
							{
								MoveCursor(i, 23);
								SetColor(DarkGray, 3);
								cout << char(223);
							}
							MoveCursor(21, 21);


							SetColor(3, LightGray);
							cout << "You Lose";
							Sleep(1000);
							while (1)
							{
								if (char a = _getch() == 13)
								{
									return;
								}
							}

						}
						break;
					}
					else
					{
						if (!ee_ships) {
							Sleep(500);
							system("cls");
							system("color 30");
							for (int i = 20; i < 23; i++)
							{
								for (int j = 19; j < 31; j++)
								{

									SetColor(LightGray, LightGray);

									MoveCursor(j, i);
									cout << ' ';
								}

								SetColor(DarkGray, LightGray);
								cout << char(222);
							}
							for (int i = 19; i < 32; i++)
							{
								MoveCursor(i, 23);
								SetColor(DarkGray, 3);
								cout << char(223);
							}
							MoveCursor(21, 21);


							SetColor(3, LightGray);
							cout << "You Lose";
							Sleep(1000);
							while (1)
							{
								if (char a = _getch() == 13)
								{
									return;
								}
							}
						}
					}



					shoy_cours(player, x, y);
				}

			}
			else if (player[x][y] == 1)
			{
				if (ships > 6)
					score += 100;
				else score += 80;
				ships--;
				for (int i = 0; i < 8; i++)
				{
					if (x + dest[0][i] < 10 && y + dest[1][i] < 10 && x + dest[0][i] >= 0 && y + dest[1][i] >= 0 && player[x + dest[0][i]][y + dest[1][i]] >= 0)
					{
						player[x + dest[0][i]][y + dest[1][i]] = -1;
						enter(x + dest[0][i], y + dest[1][i], player);
					}

				}
				player[x][y] = -2;
				enter(x, y, player);
			}
			else if (player[x][y] == 4)
			{
				hp[5]--;
				if (hp[5] == 0)
				{
					if (ships >= 9)
						score += 100;
					else
						score += 25;
					ships--;
					for (int j = 0; j < 4; j++)
					{
						for (int i = 0; i < 8; i++)
						{
							if (ship4[0][j] + dest[0][i] < 10 && ship4[1][j] + dest[1][i] < 10 && ship4[0][j] + dest[0][i] >= 0 && ship4[1][j] + dest[1][i] >= 0 && player[ship4[0][j] + dest[0][i]][ship4[1][j] + dest[1][i]] >= 0)
							{
								player[ship4[0][j] + dest[0][i]][ship4[1][j] + dest[1][i]] = -1;
								enter(ship4[0][j] + dest[0][i], ship4[1][j] + dest[1][i], player);
							}

						}
					}
					player[x][y] = -2;
					enter(x, y, player);
				}
				else {

					player[x][y] = -2;
					enter(x, y, player);
				}
			}
			else if (player[x][y] == 2)
			{
				hp[0]--;
				if (hp[0] == 0)
				{
					score += 75;
					ships--;
					for (int j = 0; j < 2; j++)
					{
						for (int i = 0; i < 8; i++)
						{
							if (ship2_1[0][j] + dest[0][i] < 10 && ship2_1[1][j] + dest[1][i] < 10 && ship2_1[0][j] + dest[0][i] >= 0 && ship2_1[1][j] + dest[1][i] >= 0 && player[ship2_1[0][j] + dest[0][i]][ship2_1[1][j] + dest[1][i]] >= 0)
							{
								player[ship2_1[0][j] + dest[0][i]][ship2_1[1][j] + dest[1][i]] = -1;
								enter(ship2_1[0][j] + dest[0][i], ship2_1[1][j] + dest[1][i], player);
							}

						}
					}
					player[x][y] = -2;
					enter(x, y, player);
				}
				else {

					player[x][y] = -2;
					enter(x, y, player);
				}
			}
			else if (player[x][y] == 12)
			{
				hp[1]--;
				if (hp[1] == 0)
				{
					score += 75;
					ships--;
					for (int j = 0; j < 2; j++)
					{
						for (int i = 0; i < 8; i++)
						{
							if (ship2_2[0][j] + dest[0][i] < 10 && ship2_2[1][j] + dest[1][i] < 10 && ship2_2[0][j] + dest[0][i] >= 0 && ship2_2[1][j] + dest[1][i] >= 0 && player[ship2_2[0][j] + dest[0][i]][ship2_2[1][j] + dest[1][i]] >= 0)
							{
								player[ship2_2[0][j] + dest[0][i]][ship2_2[1][j] + dest[1][i]] = -1;
								enter(ship2_2[0][j] + dest[0][i], ship2_2[1][j] + dest[1][i], player);
							}

						}
					}
					player[x][y] = -2;
					enter(x, y, player);
				}
				else {

					player[x][y] = -2;
					enter(x, y, player);
				}
			}
			else if (player[x][y] == 22)
			{
				hp[2]--;
				if (hp[2] == 0)
				{
					score += 75;
					ships--;
					for (int j = 0; j < 2; j++)
					{
						for (int i = 0; i < 8; i++)
						{
							if (ship2_3[0][j] + dest[0][i] < 10 && ship2_3[1][j] + dest[1][i] < 10 && ship2_3[0][j] + dest[0][i] >= 0 && ship2_3[1][j] + dest[1][i] >= 0 && player[ship2_3[0][j] + dest[0][i]][ship2_3[1][j] + dest[1][i]] >= 0)
							{
								player[ship2_3[0][j] + dest[0][i]][ship2_3[1][j] + dest[1][i]] = -1;
								enter(ship2_3[0][j] + dest[0][i], ship2_3[1][j] + dest[1][i], player);
							}

						}
					}
					player[x][y] = -2;
					enter(x, y, player);
				}
				else {

					player[x][y] = -2;
					enter(x, y, player);
				}
			}
			else if (player[x][y] == 3)
			{
				hp[3]--;
				if (hp[3] == 0)
				{
					score += 50;
					ships--;
					for (int j = 0; j < 3; j++)
					{
						for (int i = 0; i < 8; i++)
						{
							if (ship3_1[0][j] + dest[0][i] < 10 && ship3_1[1][j] + dest[1][i] < 10 && ship3_1[0][j] + dest[0][i] >= 0 && ship3_1[1][j] + dest[1][i] >= 0 && player[ship3_1[0][j] + dest[0][i]][ship3_1[1][j] + dest[1][i]] >= 0)
							{
								player[ship3_1[0][j] + dest[0][i]][ship3_1[1][j] + dest[1][i]] = -1;
								enter(ship3_1[0][j] + dest[0][i], ship3_1[1][j] + dest[1][i], player);
							}

						}
					}
					player[x][y] = -2;
					enter(x, y, player);
				}
				else {

					player[x][y] = -2;
					enter(x, y, player);
				}
			}
			else if (player[x][y] == 13)
			{
				hp[4]--;
				if (hp[4] == 0)
				{
					score += 50;
					ships--;
					for (int j = 0; j < 3; j++)
					{
						for (int i = 0; i < 8; i++)
						{
							if (ship3_2[0][j] + dest[0][i] < 10 && ship3_2[1][j] + dest[1][i] < 10 && ship3_2[0][j] + dest[0][i] >= 0 && ship3_2[1][j] + dest[1][i] >= 0 && player[ship3_2[0][j] + dest[0][i]][ship3_2[1][j] + dest[1][i]] >= 0)
							{
								player[ship3_2[0][j] + dest[0][i]][ship3_2[1][j] + dest[1][i]] = -1;
								enter(ship3_2[0][j] + dest[0][i], ship3_2[1][j] + dest[1][i], player);
							}

						}
					}
					player[x][y] = -2;
					enter(x, y, player);
				}
				else {

					player[x][y] = -2;
					enter(x, y, player);
				}
			}

		}
		else if (prov == 27)
		{
			return;
		}

		if (ships == 0)
		{
			Sleep(500);
			system("cls");
			system("color 30");
			for (int i = 12; i < 37; i++)
			{
				for (int j = 12; j < 42; j++)
				{

					SetColor(White, White);

					MoveCursor(j, i);
					cout << ' ';
				}

				SetColor(DarkGray, White);
				cout << char(222);
			}
			for (int i = 12; i < 43; i++)
			{
				MoveCursor(i, 37);
				SetColor(DarkGray, 3);
				cout << char(223);
			}
			MoveCursor(23, 13);


			SetColor(3, White);
			cout << "You Win  ";
			MoveCursor(15, 17);
			Sleep(500);
			cout << "Score................";
			for (int i = 1; i <= score; i++)
			{
				MoveCursor(36, 17);
				cout << i;
				Sleep(1);
			}
			MoveCursor(15, 22);
			Sleep(600);
			cout << "Ships................";
			for (int i = 1; i <= ee_ships; i++)
			{
				MoveCursor(36, 22);
				cout << i;
				Sleep(90);
			}
			MoveCursor(15, 27);
			Sleep(600);
			cout << "Precision............";
			for (int i = 1; i <= tochn; i++)
			{
				MoveCursor(36, 27);
				cout << i;
				Sleep(10);
			}
			MoveCursor(15, 32);
			Sleep(600);
			cout << "All..................";
			int all = score + (ee_ships * tochn);
			for (int i = 1; i <= all; i++)
			{
				MoveCursor(36, 32);
				cout << i;
				Sleep(1);
			}

			while (1)
			{
				if (char a = _getch() == 13)
				{
					table_score_add(scorh, all);
					table_score_sort(scorh);

					return;
				}
			}
		}
		shoy_cours(player, x, y);

	}

}
