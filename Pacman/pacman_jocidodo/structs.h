#ifndef STRUCTS_H
#define STRUCTS_H
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <string.h>

typedef struct maze
{
	int** passable;
	int **paths;
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
ghost* gen_ghosts(int num_ghosts,int* xs,int* ys);

typedef struct game
{
	maze* m;
	paccy* p;
	ghost* ghosts; int lvl;
	int score; int lives; int game_end; int time; int num_ghost; int speed;
} game;


game* gen_game(int lvl, int width, int height, int num_ghosts, int speed, int lives);
void print_game(game* g, HANDLE hStdOut);
void end_game(game* g);
void print_with_spaces(char* c, int x, int y, HANDLE h, int t, WORD color);
void next_lvl(game* g);
void finish_game(game* g);
void kill_game(game* g);
void write_game(game* g);
int if_save(game *g, char c);
game* load_game();

typedef struct score
{
	char ime[30];
	int score;
} score;

score* get_scores();

#endif // !STRUCTS_H