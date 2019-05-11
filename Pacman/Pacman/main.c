#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include "key_press.h"
#include "structs.h"
#include "moving.h"


int main()
{
	/*HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE)
	{
		printf("Invalid handle");
		return 1;
	}

	write_symbol_in_color(hStdOut, 0, 0, "R", FOREGROUND_RED | FOREGROUND_INTENSITY);
	write_symbol_in_color(hStdOut, 1, 0, "G", FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	write_symbol_in_color(hStdOut, 2, 0, "B", FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	write_symbol_in_color(hStdOut, 3, 0, "C", FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	write_symbol_in_color(hStdOut, 4, 0, "M", FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	write_symbol_in_color(hStdOut, 5, 0, "Y", FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);*/
	game* g =gen_game(1, 28, 36);//28,36
	while (1)
	{
		HANDLE hStdout;

		hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

		cls(hStdout);
		if (_kbhit())
		{
			change_paccy_direction(g, _getch());
			continue;
		}
		//change_paccy_direction(g, c);
		paccy_dots(g);
		paccy_power_ups(g);
		paccy_ghost(g); //ovo je komentar
		move_paccy(g);
		print_game(g);
		Sleep(100);
	}
	system("PAUSE");
}