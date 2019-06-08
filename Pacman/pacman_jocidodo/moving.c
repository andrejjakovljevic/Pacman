#include <stdio.h>
#include "structs.h"
#include "key_press.h"
#define CHUNK_2 4
#define CHUNK_3 2
#define BOUND 8

void move_paccy(game* g) //1 - dole; 2-desno; 3-gore; 4-levo
{
	if (g->p->moving_direction == 1)
	{
		int pom = (g->p->x + 1) % (g->m->height);
		if (g->m->passable[pom][g->p->y] == 1) {
			int k = 1;
			for (int i = 0; i < 4; i++)
				if (g->ghosts[i].x == pom && g->ghosts[i].y == g->p->y && !(g->p->powered_up)) k = 0;
			if (k) g->p->x = pom;
		}
	}
	else if (g->p->moving_direction == 2)
	{
		int pom = (g->p->y + 1) % (g->m->width);
		if (g->m->passable[g->p->x][pom] == 1) {
			int k = 1;
			for (int i = 0; i < 4; i++)
				if (g->ghosts[i].x == g->p->x && g->ghosts[i].y == pom && !(g->p->powered_up)) k = 0;
			if (k) g->p->y = pom;
		}
	}
	else if (g->p->moving_direction == 3)
	{
		int pom = g->p->x - 1;
		if (pom < 0) pom += g->m->height;
		if (g->m->passable[pom][g->p->y] == 1) {
			int k = 1;
			for (int i = 0; i < 4; i++)
				if (g->ghosts[i].x == pom && g->ghosts[i].y == g->p->y && !(g->p->powered_up)) k = 0;
			if (k) g->p->x = pom;
		}
	}
	else if (g->p->moving_direction == 4)
	{
		int pom = g->p->y - 1;
		if (pom < 0) pom += g->m->width;
		if (g->m->passable[g->p->x][pom] == 1) {
			int k = 1;
			for (int i = 0; i < 4; i++)
				if (g->ghosts[i].x == g->p->x && g->ghosts[i].y == pom && !(g->p->powered_up)) k = 0;
			if (k) g->p->y = pom;
		}
	}
}

void change_paccy_direction(game* g, char c) //1 - dole; 2-desno; 3-gore; 4-levo
{
	int pom1 = (g->p->x + 1) % (g->m->height);
	int pom2 = (g->p->y + 1) % (g->m->width);
	int pom3 = g->p->x - 1;
	if (pom3 < 0) pom3 += g->m->height;
	int pom4 = g->p->y - 1;
	if (pom4 < 0) pom4 += g->m->width;
	if (c == 'w' && g->m->passable[pom3][g->p->y] == 1) g->p->moving_direction = 3;
	else if (c == 's' && g->m->passable[pom1][g->p->y] == 1) g->p->moving_direction = 1;
	else if (c == 'd' && g->m->passable[g->p->x][pom2] == 1) g->p->moving_direction = 2;
	else if (c == 'a' && g->m->passable[g->p->x][pom4] == 1) g->p->moving_direction = 4;
}

void move_ghosts(game *g) {

	int targetx[4] = { g->p->x };
	int targety[4] = { g->p->y };

	switch (g->p->moving_direction)
	{
	case 1: {
		targetx[1] = min(g->p->x + CHUNK_2, g->m->height - 1);
		targety[1] = g->p->y;
		int pom1 = min(g->p->x + CHUNK_3, g->m->height - 1);
		int pom2 = g->p->y;
		targetx[2] = max(min(g->m->height - 1, 2 * pom1 - g->ghosts[0].x), 0);
		targety[2] = max(min(g->m->width - 1, 2 * pom2 - g->ghosts[0].y), 0);
	}
			break;
	case 0: case 2: {
		targetx[1] = g->p->x;
		targety[1] = min(g->p->y + CHUNK_2, g->m->width - 1);
		int pom1 = g->p->x;
		int pom2 = min(g->p->y + CHUNK_3, g->m->width - 1);
		targetx[2] = max(min(g->m->height - 1, 2 * pom1 - g->ghosts[0].x), 0);
		targety[2] = max(min(g->m->width - 1, 2 * pom2 - g->ghosts[0].y), 0);
	}
			break;
	case 3: {
		targetx[1] = max(g->p->x - CHUNK_2, 0);
		targety[1] = g->p->y;
		int pom1 = max(g->p->x - CHUNK_3, 0);
		int pom2 = g->p->y;
		targetx[2] = max(min(g->m->height - 1, 2 * pom1 - g->ghosts[0].x), 0);
		targety[2] = max(min(g->m->width - 1, 2 * pom2 - g->ghosts[0].y), 0);
	}
			break;
	case 4: {
		targetx[1] = g->p->x;
		targety[1] = max(g->p->y - CHUNK_2, 0);
		int pom1 = g->p->x;
		int pom2 = max(g->p->y - CHUNK_3, 0);
		targetx[2] = max(min(g->m->height - 1, 2 * pom1 - g->ghosts[0].x), 0);
		targety[2] = max(min(g->m->width - 1, 2 * pom2 - g->ghosts[0].y), 0);
	}
			break;
	default:
		break;
	}

	if (g->num_ghost > 3)
	{
		int dc = g->m->paths[g->m->height * (g->m->width * g->ghosts[3].x + g->ghosts[3].y) + targetx[0]][targety[0]];
		if (dc > BOUND) {
			targetx[3] = targetx[0];
			targety[3] = targety[0];
		}
		else {
			targetx[3] = 32;
			targety[3] = 1;
		}
	}
	for (int i = 0; i < g->num_ghost; i++) {
		int mind = -2, d;
		int minx = g->ghosts[i].x;
		int miny = g->ghosts[i].y;

		int occupied = 0;
		for (int c = 0; c < g->num_ghost; c++) {
			if (g->ghosts[i].x - 1 == g->ghosts[c].x && g->ghosts[i].y == g->ghosts[c].y) occupied = 1;
		}
		if (occupied) d = -1;
		else {
			d = g->m->paths[g->m->height * (g->m->width * (g->ghosts[i].x - 1) + g->ghosts[i].y) + targetx[i]][targety[i]];
			if ((mind > d || mind == -2) && d != -1) {
				mind = d;
				minx = g->ghosts[i].x - 1;
				miny = g->ghosts[i].y;
			}
		}

		occupied = 0;
		for (int c = 0; c < g->num_ghost; c++) {
			if (g->ghosts[i].x + 1 == g->ghosts[c].x && g->ghosts[i].y == g->ghosts[c].y) occupied = 1;
		}
		if (occupied) d = -1;
		else {
			d = g->m->paths[g->m->height * (g->m->width * (g->ghosts[i].x + 1) + g->ghosts[i].y) + targetx[i]][targety[i]];
			if ((mind > d || mind == -2) && d != -1) {
				mind = d;
				minx = g->ghosts[i].x + 1;
				miny = g->ghosts[i].y;
			}
		}
		occupied = 0;

		for (int c = 0; c < g->num_ghost; c++) {
			if (g->ghosts[i].x == g->ghosts[c].x && g->ghosts[i].y - 1 == g->ghosts[c].y) occupied = 1;
		}
		if (occupied) d = -1;
		else {
			d = g->m->paths[g->m->height * (g->m->width * g->ghosts[i].x + g->ghosts[i].y - 1) + targetx[i]][targety[i]];
			if ((mind > d || mind == -2) && d != -1) {
				mind = d;
				minx = g->ghosts[i].x;
				miny = g->ghosts[i].y - 1;
			}
		}

		occupied = 0;
		for (int c = 0; c < g->num_ghost; c++) {
			if (g->ghosts[i].x == g->ghosts[c].x && g->ghosts[i].y + 1 == g->ghosts[c].y) occupied = 1;
		}
		if (occupied) d = -1;
		else {
			d = g->m->paths[g->m->height * (g->m->width * g->ghosts[i].x + g->ghosts[i].y + 1) + targetx[i]][targety[i]];
			if ((mind > d || mind == -2) && d != -1) {
				mind = d;
				minx = g->ghosts[i].x;
				miny = g->ghosts[i].y + 1;
			}
		}
		if (g->m->passable[minx][miny] && ((g->p->powered_up && g->time % 2) || !(g->p->powered_up))) {
			g->ghosts[i].x = minx;
			g->ghosts[i].y = miny;
		}
	}
}

void paccy_dots(game* g)
{
	if (g->m->dots[g->p->x][g->p->y] == 1)
	{
		g->m->dots[g->p->x][g->p->y] = 0;
		g->score += 5;
	}
}

void paccy_power_ups(game* g)
{
	if (g->m->powerups[g->p->x][g->p->y])
	{
		g->m->powerups[g->p->x][g->p->y] = 0;
		g->p->powered_up = 25;
		g->score += 100;
	}
}

void paccy_ghost(game* g)
{
	int k = -1;
	for (int i = 0; i < g->num_ghost; i++)
	{
		if (g->p->x == g->ghosts[i].x && g->p->y == g->ghosts[i].y && g->ghosts[i].dead == 0)
		{
			k = i;
		}
	}
	if (k != -1)
	{
		if (g->p->powered_up)
		{
			g->score += 100;
			g->ghosts[k].dead = 10;
		}
		else
		{
			g->lives -= 1;
			Sleep(500);

			free(g->p);
			g->p = gen_paccy(20, 13);
			int xs[] = { 16,16,16,16 };
			int ys[] = { 12,13,14,15 };
			g->ghosts = gen_ghosts(g->num_ghost, xs, ys);
			if (g->lives == 0) end_game(g);
		}
	}
}

void pass_time(game* g)
{
	int xs[] = { 16,16,16,16 };
	int ys[] = { 12,13,14,15 };

	for (int i = 0; i < g->num_ghost; i++)
	{
		if (g->ghosts[i].dead == 1) {
			g->ghosts[i].x = xs[i];
			g->ghosts[i].y = ys[i];
		}
		if (g->ghosts[i].dead) g->ghosts[i].dead--;
	}
	if (g->p->powered_up) g->p->powered_up--;

	g->time++;
}
