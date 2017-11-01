#include "game.h"


using namespace std;


void main()
{

	set_cursor_visible(0);
	system("color 30");
	HWND hwnd = GetConsoleWindow();
	if (hwnd != NULL) { MoveWindow(hwnd, 360, 50, 1000, 620, TRUE); }
	setFontSize();
	int lvl = 0;
	char chek;
	
	scores score[8];
	
	for (int i = 0; i < 8; i++)
	{
		score[i].score = 0;
	}
	
	

	while (1)
	{
		for (int i = 20; i < 23; i++)
		{
			for (int j = 19; j < 31; j++)
			{
				if (lvl == 0 || lvl == 2)
					SetColor(LightGray, LightGray);
				else
					SetColor(White, White);
				MoveCursor(j, i);
				cout << ' ';
			}
			if (lvl == 0 || lvl == 2)
				SetColor(DarkGray, LightGray);
			else
				SetColor(DarkGray, White);
			cout << char(222);
		}
		for (int i = 19; i < 32; i++)
		{
			MoveCursor(i, 23);
			SetColor(DarkGray, 3);
			cout << char(223);
		}
		MoveCursor(22, 21);
		if (lvl == 0 || lvl == 2)
			SetColor(3, LightGray);
		else
			SetColor(3, White);
		cout << "Scores";


		for (int i = 15; i < 18; i++)
		{
			for (int j = 19; j < 31; j++)
			{
				if (lvl == 1 || lvl == 2)
					SetColor(LightGray, LightGray);
				else
					SetColor(White, White);
				MoveCursor(j, i);
				cout << ' ';
			}
			if (lvl == 1 || lvl == 2)
				SetColor(DarkGray, LightGray);
			else
				SetColor(DarkGray, White);
			cout << char(222);
		}
		for (int i = 19; i < 32; i++)
		{
			MoveCursor(i, 18);
			SetColor(DarkGray, 3);
			cout << char(223);
		}
		MoveCursor(21, 16);
		if (lvl == 1 || lvl == 2)
			SetColor(3, LightGray);
		else
			SetColor(3, White);
		cout << "New Game";

		for (int i = 25; i < 28; i++)
		{
			for (int j = 19; j < 31; j++)
			{
				if (lvl == 0 || lvl == 1)
					SetColor(LightGray, LightGray);
				else
					SetColor(White, White);
				MoveCursor(j, i);
				cout << ' ';
			}
			if (lvl == 0 || lvl == 1)
				SetColor(DarkGray, LightGray);
			else
				SetColor(DarkGray, White);
			cout << char(222);
		}
		for (int i = 19; i < 32; i++)
		{
			MoveCursor(i, 28);
			SetColor(DarkGray, 3);
			cout << char(223);
		}
		MoveCursor(23, 26);
		if (lvl == 0 || lvl == 1)
			SetColor(3, LightGray);
		else
			SetColor(3, White);
		cout << "Exit";

		chek = _getch();
		if (chek == 'w')
		{
			if(lvl != 0)
			lvl -= 1;
		}
		else if (chek == 's')
		{
			if(lvl < 2)
			lvl += 1;
		}
		else if (chek == 13)
		{
			if (lvl == 0)
			{
				system("cls");
				system("color 30");
				war_ship(score);
				system("cls");
				system("color 30");
			}
			else if(lvl == 1)
			{
				system("cls");
				system("color 30");
				table_score_show(score);
				_getch();
				system("cls");
				system("color 30");
			}
			else if (lvl == 2)
			{
				system("cls");
				system("color 30");
				exit(0);
				system("cls");
				system("color 30");
			}
		}
	}

	
	
	
}
