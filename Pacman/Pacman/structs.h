#ifndef STRUCTS_H
#define STRUCTS_H
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <string.h>

typedef struct main_menu
{
	int indentifier;
} main_menu;

void arrow_down(main_menu* m);
void arrow_up(main_menu* m);
char* get_str(main_menu* m);
void print_mm(main_menu* m);
void do_things(main_menu* m);

typedef struct maze
{
	int** passable;
	int** dots;
	int** powerups;
	int height; int width;
} maze;

maze* gen_maze(int lvl, int width, int height);


typedef struct paccy
{
	int x; int y;
	int powered_up;
	int moving_direction;
} paccy;

paccy* gen_paccy(int x, int y);

typedef struct ghost
{
	int x; int y;
	int identificator;
	int dead;
} ghost;

ghost* gen_ghost(int x, int y, int iden);
ghost* gen_ghosts(int* xs, int* ys);

typedef struct game
{
	maze* m;
	paccy* p;
	ghost* ghosts; int lvl;
	int score; int lives; int game_end; int time;
} game;


game* gen_game(int lvl, int width, int height);
void print_game(game* g);
void end_game(game* g);
void print_with_spaces(char* c, int x, int y, HANDLE h);
void next_lvl(game* g);
void finish_game(game* g);
void kill_game(game* g);

typedef struct score
{
	char* ime;
	int score;
} score;

score* get_scores();

#endif // !STRUCTS_H