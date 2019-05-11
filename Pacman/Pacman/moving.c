
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include "structs.h"
#include "key_press.h"

void move_paccy(game* g) //1 - dole; 2-desno; 3-gore; 4-levo
{
	if (g->p->moving_direction == 1)
	{
		int pom = (g->p->x + 1) % (g->m->height);
		if (g->m->passable[pom][g->p->y] == 1)
		{
			g->p->x = pom;
		}
	}
	else if (g->p->moving_direction == 2)
	{
		int pom = (g->p->y + 1) % (g->m->width);
		if (g->m->passable[g->p->x][pom] == 1)
		{
			g->p->y = pom;
		}
	}
	else if (g->p->moving_direction == 3)
	{
		int pom = g->p->x - 1;
		if (pom < 0) pom += g->m->height;
		if (g->m->passable[pom][g->p->y] == 1)
		{
			g->p->x = pom;
		}
	}
	else if (g->p->moving_direction == 4)
	{
		int pom = g->p->y - 1;
		if (pom < 0) pom += g->m->width;
		if (g->m->passable[g->p->x][pom] == 1)
		{
			g->p->y = pom;
		}
	}
}

void change_paccy_direction(game* g, char c) //1 - dole; 2-desno; 3-gore; 4-levo
{
	if (g->p->moving_direction == 0)
	{
		if (c == 'w') g->p->moving_direction = 3;
		else if (c == 's') g->p->moving_direction = 1;
		else if (c == 'd') g->p->moving_direction = 2;
		else if (c == 'a') g->p->moving_direction = 4;
	}
	else if (g->p->moving_direction == 1 || g->p->moving_direction==3)
	{
		if (c == 'd') g->p->moving_direction = 2;
		else if (c == 'a') g->p->moving_direction = 4;
	}
	else if (g->p->moving_direction == 2 || g->p->moving_direction == 4)
	{
		if (c == 'w') g->p->moving_direction = 3;
		if (c == 's') g->p->moving_direction = 1;
	}
}

void paccy_dots(game* g)
{
	if (g->m->dots[g->p->x][g->p->y] == 1)
	{
		g->m->dots[g->p->x][g->p->y] = 0;
		g->score += 1;
	}
}

void paccy_power_ups(game* g)
{
	if (g->m->powerups[g->p->x][g->p->y] == 1)
	{
		g->m->powerups[g->p->x][g->p->y] = 0;
		g->p->powered_up = 1;
		g->score += 5;
	}
}

void paccy_ghost(game* g)
{
	int k = -1;
	for (int i = 0; i < 4; i++)
	{
		if (g->p->x == g->ghosts[i].x && g->p->y == g->ghosts[i].y)
		{
			k = i;
		}
	}
	if (k != -1)
	{
		if (g->p->powered_up == 1)
		{
			g->score += 5;
			g->ghosts[k].dead = 10;
		}
		else
		{
			g->lives -= 1;
			if (g->lives == 0) end_game(g);
		}
	}
}