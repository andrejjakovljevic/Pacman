#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<conio.h>

#include "structs.h"
#include "key_press.h"

maze* gen_maze(int lvl, int width, int height)
{
	FILE *fp;
	fp = fopen("maze.txt", "r");
	if (fp == NULL)
	{
		perror("There was an error! Please restart the game.");
	}
	else
	{
		maze* m = malloc(sizeof(maze));
		m->height = height;
		m->width = width;
		m->passable = malloc(m->height * sizeof(int*));
		m->dots = malloc(m->height * sizeof(int*));
		m->powerups = malloc(m->height * sizeof(int*));
		for (int i = 0; i < m->height; i++)
		{
			m->passable[i] = malloc(m->width * sizeof(int));
			m->dots[i] = malloc(m->width * sizeof(int));
			m->powerups[i] = malloc(m->width * sizeof(int));
		}
		int i = 0;
		char* str = malloc(m->width * sizeof(char));
		for (int i = 0; i < m->height; i++)
		{
			fscanf(fp, "%s", str);
			for (int j = 0; j < m->width; j++)
			{
				if (str[j] == '0')
				{
					m->passable[i][j] = 0;
					m->dots[i][j] = 0;
					m->powerups[i][j] = 0;
				}
				else if (str[j] == '1')
				{
					m->passable[i][j] = 1;
					m->dots[i][j] = 0;
					m->powerups[i][j] = 0;
				}
				else if (str[j] == 'p')
				{
					m->passable[i][j] = 1;
					m->dots[i][j] = 0;
					m->powerups[i][j] = 1;
				}
				else
				{
					m->passable[i][j] = 1;
					m->dots[i][j] = 1;
					m->powerups[i][j] = 0;
				}
			}
		}
		fclose(fp);
		//free(str);
		return m;
	}
}

void print_with_spaces(char* c, int x, int y, HANDLE h)
{
	write_symbol(h, x, y, " ");
	write_symbol(h, x + 1, y, c);
	write_symbol(h, x + 2, y, " ");
}

void print_game(game* g)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE)
	{
		printf("Invalid handle");
		return;
	}
	int x = 0;
	int y = 0;
	for (int i = 0; i < g->m->height; i++)
	{
		for (int j = 0; j < g->m->width; j++)
		{
			int t = 0;
			for (int k = 0; k < 4; k++)
			{
				if (g->ghosts[k].x == i && g->ghosts[k].y == j && g->ghosts[k].dead==0) t = 1;
			}
			if (g->m->passable[i][j] == 0) print_with_spaces("x", x, y, hStdOut);
			else if (g->p->x == i && g->p->y == j) print_with_spaces("c", x, y, hStdOut);
			else if (t) print_with_spaces("g", x, y, hStdOut);
			else if (g->m->powerups[i][j] == 1) print_with_spaces("p", x, y, hStdOut);
			else if (g->m->dots[i][j] == 1) print_with_spaces(".", x, y, hStdOut);
			else print_with_spaces(" ", x, y, hStdOut);
			x += 3;
		}
		//printf("\n");
		x = 0;
		y++;
	}
}

paccy* gen_paccy(int x, int y)
{
	paccy* p = malloc(sizeof(paccy));
	p->x = x;
	p->y = y;
	p->powered_up = 0;
	p->moving_direction = 0;
	return p;
}

ghost* gen_ghost(int x, int y, int iden)
{
	ghost* g = malloc(sizeof(ghost));
	g->x = x;
	g->y = y;
	g->identificator = iden;
	g->dead = 0;
	return g;
}

ghost* gen_ghosts(int* xs, int* ys)
{
	ghost* gs = malloc(4 * sizeof(ghost));
	for (int i = 0; i < 4; i++)
	{
		gs[i] = *gen_ghost(xs[i], ys[i], i);
	}
	return gs;
}

game* gen_game(int lvl, int width, int height)
{
	game* g = malloc(sizeof(g));
	g->lvl = 1;
	g->m = gen_maze(lvl, width, height);
	g->p = gen_paccy(20, 13);
	int xs[] = { 16,16,16,16 };
	int ys[] = { 12,13,14,15 };
	g->ghosts = gen_ghosts(xs, ys);
	g->score = 0;
	g->game_end = 0;
	return g;
}

void end_game(game* g)
{
	g->game_end = 1;
}

void next_lvl(game* g)
{
	int t = 0;
	for (int i = 0; i < g->m->height; i++)
	{
		for (int j = 0; j < g->m->width; j++)
		{
			if (g->m->dots[i][j] == 1) t = 1;
		}
	}
	if (t == 0)
	{
		g->lvl++;
		if (g->lvl == 10) end_game(g);
		Sleep(1000);
		g->m = gen_maze(g->lvl, g->m->width, g->m->height);
		g->p = gen_paccy(20, 13);
	}
}

void finish_game(game* g)
{
	//UPISATI HIGHSCORE ITD!
}