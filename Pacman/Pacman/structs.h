#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct maze
{
	int** passable;
	int** dots;
	int** powerups;
	int speed;
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
	ghost* ghosts;
	int score; int lives; int game_end;
} game;

game* gen_game(int lvl, int width, int height);
void print_game(game* g);
void end_game(game* g);

#endif // !STRUCTS_H