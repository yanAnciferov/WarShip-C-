#pragma once
#include <iostream>
#include <time.h>
#include <conio.h>
#include <Windows.h>
#include <Wincon.h>
#include <iomanip>

using namespace std;


extern HANDLE handle;
extern CONSOLE_CURSOR_INFO cci;

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

void MoveCursor(short int x, short int y);
void setFontSize();
void SetColor(int text, int background);
struct scores
{
	char name[10];
	int score;
};
void table_score_show(scores score[8]);
void table_score_add(scores score[8], int all);
void table_score_sort(scores score[8]);
void set_cursor_visible(bool visible);
void add_ships(int mas[10][10], int shp1[2][4], int shp4[2][4], int shp2_1[2][2], int shp2_2[2][2], int shp2_3[2][2], int shp3_1[2][3], int shp3_2[2][3]);
void ee_enter(int x, int y, int mas[10][10]);
int ee_hod(int mas[10][10], int shp1[2][4], int shp4[2][4], int shp2_1[2][2], int shp2_2[2][2], int shp2_3[2][2], int shp3_1[2][3], int shp3_2[2][3]);
void enter(int x, int y, int ee_mas[10][10]);
void shoy_cours(int mas[10][10], int x, int y);
void shoy(int player[10][10], int ee_player[10][10]);
void show_lose(int lx, int ly, int i);
void shoy_score();
void war_ship(scores scorh[8]);
