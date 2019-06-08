#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include "key_press.h"
#include "structs.h"
#include "moving.h"
#include "zapisi_interface.h"
#define SPEED 100


void continue_game()
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
	game* g = load_game();//28,36
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	print_game(g,hStdOut);
	Sleep(1000);
	while (1)
	{
		if (_kbhit())
		{
			char c = _getch();
			if (if_save(g, c)) return;
			change_paccy_direction(g, c);
			continue;
		}
		//change_paccy_direction(g, c);
		paccy_dots(g);
		paccy_power_ups(g);
		paccy_ghost(g);
		if (g->game_end == 1)
		{
			finish_game(g);
			break;
		}
		move_paccy(g);
		move_ghosts(g);
		next_lvl(g);
		print_game(g,hStdOut);
		pass_time(g);
		//Sleep(g->speed - (g->lvl) * 10);
		//Sleep(5);
	}
	//finish_game(g);
	//printf("NESTO");
	//system("PAUSE");
}