#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<conio.h>

#include "structs.h"
#include "key_press.h"
#include "zapisi_interface.h"

maze* gen_maze(int lvl, int width, int height)
{
	FILE *fp = NULL, *in = NULL;
	fp = fopen("maze.txt", "r");
	in = fopen("paths.txt", "r");
	if (!fp || !in)
	{
		perror("There was an error! Please restart the game.");
	}
	else
	{
		maze* m = malloc(sizeof(maze));
		m->height = height;
		m->width = width;
		m->passable = malloc(m->height * sizeof(int*));
		m->paths = malloc(m->height * m->height * m->width * sizeof(int*));
		m->dots = malloc(m->height * sizeof(int*));
		m->powerups = malloc(m->height * sizeof(int*));
		for (int i = 0; i < m->height; i++)
		{
			m->passable[i] = malloc(m->width * sizeof(int));
			m->dots[i] = malloc(m->width * sizeof(int));
			m->powerups[i] = malloc(m->width * sizeof(int));
		}
		for (int i = 0; i < m->height * m->height * m->width; i++) {
			m->paths[i] = malloc(m->width * sizeof(int));
			for (int j = 0; j < m->width; j++)
				fscanf(in, "%d", &m->paths[i][j]);
		}
		fclose(in);
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

void print_with_spaces(char* c, int x, int y, HANDLE h, int t, WORD color)
{
	if (!t)
	{
		write_symbol(h, x, y, " ");
		write_symbol(h, x + 1, y, c);
		write_symbol(h, x + 2, y, " ");
	}
	else
	{
		write_symbol(h, x, y, " ");
		write_symbol_in_color(h, x+1, y, c, color);
		write_symbol(h, x + 2, y, " ");
	}
}
//1 - dole; 2-desno; 3-gore; 4-levo
void print_paccy(int x, int y, int d, int time, HANDLE hStdOut) // d kao direction
{
    if (!d) print_with_spaces("{", x, y, hStdOut, 1, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    else
    if (d==3)
    {
        if (time%2==0) print_with_spaces("V", x, y, hStdOut, 1, FOREGROUND_RED | FOREGROUND_GREEN |  FOREGROUND_INTENSITY);
        if (time%2==1) print_with_spaces("|", x, y, hStdOut, 1, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    }
    else
    if (d==2)
    {
        if (time%6==0 || time%6==4) print_with_spaces("{", x, y, hStdOut, 1, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        if (time%6==1 || time%6==3)print_with_spaces("<", x, y, hStdOut, 1, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        if (time%6==2) print_with_spaces("-", x, y, hStdOut, 1, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        if (time%6==5) print_with_spaces("(", x, y, hStdOut, 1, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    }
    else
    if (d==1)
    {
        if (time%2==0) print_with_spaces("^", x, y, hStdOut, 1, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        if (time%2==1) print_with_spaces("|", x, y, hStdOut, 1, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    }
    else
    if (d==4)
    {
        if (time%6==0 || time%6==4) print_with_spaces("}", x, y, hStdOut, 1, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        if (time%6==1 || time%6==3)print_with_spaces(">", x, y, hStdOut, 1, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        if (time%6==2) print_with_spaces("-", x, y, hStdOut, 1, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        if (time%6==5) print_with_spaces(")", x, y, hStdOut, 1, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    }

}

void print_game(game* g, HANDLE hStdOut)
{
	int x = 28;
	int y = 8;
	for (int i = 0; i < g->m->height; i++)
	{
		for (int j = 0; j < g->m->width; j++)
		{
			int t = 0;
			for (int k = 0; k < g->num_ghost; k++)
			{
				if (g->ghosts[k].x == i && g->ghosts[k].y == j && g->ghosts[k].dead == 0) t = k + 1;
			}
			if (g->m->passable[i][j] == 0) print_with_spaces("x", x, y, hStdOut, 1, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			else if (g->p->x == i && g->p->y == j) print_paccy(x, y ,g->p->moving_direction, g->time, hStdOut); ///print_with_spaces("c", x, y, hStdOut);
			else if (t) {
				if (g->p->powered_up)
				{
					if (g->p->powered_up<10 && g->time%2==0) print_with_spaces("g", x, y, hStdOut, 1, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
					else if (g->p->powered_up<10 && g->time%2==1) print_with_spaces("g", x, y, hStdOut, 1, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
					else print_with_spaces("g", x, y, hStdOut, 1, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				}
				else {
					switch (t) {
					case 1: print_with_spaces("g", x, y, hStdOut, 1, FOREGROUND_RED | FOREGROUND_INTENSITY);
						break;
					case 2: print_with_spaces("g", x, y, hStdOut, 1, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
						break;
					case 3: print_with_spaces("g", x, y, hStdOut, 1, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
						break;
					case 4: print_with_spaces("g", x, y, hStdOut, 1, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
						break;
					default:
						break;
					}
				}
			}
			else if (g->m->powerups[i][j] == 1) print_with_spaces("*", x, y, hStdOut, 1, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			else if (g->m->dots[i][j] == 1) print_with_spaces(".", x, y, hStdOut, 1, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			else print_with_spaces(" ", x, y, hStdOut, 0, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			x += 3;
		}
		//printf("\n");
		x = 28;
		y++;
	}
	ispis_string("Lives:", 50, 5, hStdOut);
	ispis_string(broj_to_string(g->lives), 57, 5, hStdOut);
	ispis_string("Level:", 50, 6, hStdOut);
	ispis_string(broj_to_string(g->lvl), 57, 6, hStdOut);
	ispis_string("Score:", 50, 4, hStdOut);
	ispis_string(broj_to_string(g->score), 56, 4, hStdOut);
	//if (!(g->time % 10)) printf("%d ", g->score);
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

ghost* gen_ghosts(int num_ghosts,int *xs,int *ys)
{	
	
	ghost* gs = malloc(num_ghosts * sizeof(ghost));
	for (int i = 0; i < num_ghosts; i++)
	{
		gs[i] = *gen_ghost(xs[i], ys[i], i);
	}
	return gs;
}

game* gen_game(int lvl, int width, int height, int num_ghosts, int speed, int lives)
{
	game* g = malloc(sizeof(game));
	g->lvl = 1;
	g->m = gen_maze(lvl, width, height);
	g->p = gen_paccy(20, 13);
	int xs[] = { 16,16,16,16 };
	int ys[] = { 12,13,14,15 };
	g->ghosts = gen_ghosts(num_ghosts, xs, ys);
	g->score = 0;
	g->game_end = 0;
	g->lives = lives; 
	g->time = 0;
	g->speed = 100 - 25 * (speed-1);
	g->num_ghost = num_ghosts;
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
		//Sleep(1000);
		g->m = gen_maze(g->lvl, g->m->width, g->m->height);
		g->p = gen_paccy(20, 13);
		int xs[] = { 16,16,16,16 };
		int ys[] = { 12,13,14,15 };
		g->ghosts = gen_ghosts(g->num_ghost, xs, ys);
	}
}

score* get_scores()
{
	FILE *fs;
	fs = fopen("scores.cep", "rb");
	if (fs == NULL)
	{
		perror("There was an error! Please restart the game.");
	}
	else
	{
		score* scores = malloc(10 * sizeof(score));
		int br = 0;
		while ((fread(scores + br, sizeof(score), 1, fs)) == 1)
		{
			br++;
		}
		for (; br < 10; br++)
		{
			for (int i = 0; i < 30; i++)
			{
				scores[br].ime[i] = '\0';
			}
			scores[br].score = 0;
		}
		fclose(fs);
		return scores;
	}
}

void kill_game(game* g)
{
	for (int i = 0; i < g->m->height; i++)
	{
		free(g->m->passable[i]);
		free(g->m->powerups[i]);
		free(g->m->dots[i]);
	}
	for (int i = 0; i < g->m->height * g->m->height * g->m->width; i++) free(g->m->paths[i]);
	free(g->m->paths);
	free(g->m->passable);
	free(g->m->powerups);
	free(g->m->dots);
	free(g->p);
	free(g);
}

void finish_game(game* g)
{
	score *scores = NULL;
	scores = get_scores();
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE)
	{
		printf("Invalid handle");
		return;
	}
	cls(hStdOut);
	int t = 0;
	for (int i = 0; i < 10; i++)
	{
		if (g->score > scores[i].score) t = 1;
	}
	if (t)
	{
		printf("Enter name here:\n");
		scanf("%s", scores[9].ime);
		scores[9].score = g->score;
		for (int i = 0; i < 10; i++)
		{
			for (int j = i; j < 10; j++)
			{
				if (scores[i].score < scores[j].score)
				{
					score t = scores[i];
					scores[i] = scores[j];
					scores[j] = t;
				}
			}
		}
	}
	FILE *fs;
	fs = fopen("scores.cep", "wb");
	for (int i = 0; i < 10; i++)
	{
		fwrite(scores + i, sizeof(score), 1, fs);
	}
	fclose(fs);
	kill_game(g);
}

void write_game(game* g)
{
	FILE *fs;
	fs = fopen("cur_state.txt", "w");
	fprintf(fs, "1\n");
	fprintf(fs, "%d %d\n", g->m->height, g->m->width);
	for (int i = 0; i < g->m->height; i++)
	{
		for (int j = 0; j < g->m->width; j++)
		{
			fprintf(fs, "%d ", g->m->passable[i][j]);
		}
		fprintf(fs, "\n");
	}
	for (int i = 0; i < g->m->height; i++)
	{
		for (int j = 0; j < g->m->width; j++)
		{
			fprintf(fs, "%d ", g->m->dots[i][j]);
		}
		fprintf(fs, "\n");
	}
	for (int i = 0; i < g->m->height; i++)
	{
		for (int j = 0; j < g->m->width; j++)
		{
			fprintf(fs, "%d ", g->m->powerups[i][j]);
		}
		fprintf(fs, "\n");
	}
	fprintf(fs, "%d %d %d\n", g->p->x, g->p->y, g->p->powered_up);
	fprintf(fs, "%d\n", g->num_ghost);
	for (int i = 0; i < g->num_ghost; i++)
	{
		fprintf(fs, "%d %d\n", g->ghosts[i].x, g->ghosts[i].y);
	}
	fprintf(fs, "%d\n", g->score);
	fprintf(fs, "%d\n", g->speed);
	fprintf(fs, "%d\n", g->lvl);
	fprintf(fs, "%d\n", g->game_end);
	fprintf(fs, "%d\n", g->lives);
	fprintf(fs, "%d\n", g->time);
	fclose(fs);
}

int if_save(game *g, char c)
{
	if (c == 27)
	{
		write_game(g);
		kill_game(g);
		return 1;
	}
	return 0;
}

game* load_game()
{
	FILE *fs = fopen("cur_state.txt", "r");
	int state;
	fscanf(fs, "%d", &state);
	if (state)
	{
		game * g = malloc(sizeof(game));
		g->m = malloc(sizeof(maze));
		fscanf(fs, "%d %d", &g->m->height, &g->m->width);
		g->m->passable = malloc(g->m->height * sizeof(int*));
		for (int i = 0; i < g->m->height; i++)
		{
			g->m->passable[i] = malloc(g->m->width * sizeof(int));
			for (int j = 0; j < g->m->width; j++) 
			{
				fscanf(fs,"%d", &g->m->passable[i][j]);
			}
		}

		FILE *in = fopen("paths.txt", "r");
		g->m->paths = malloc(g->m->height * g->m->height * g->m->width * sizeof(int*));
		for (int i = 0; i < g->m->height * g->m->height * g->m->width; i++) {
			g->m->paths[i] = malloc(g->m->width * sizeof(int));
			for (int j = 0; j < g->m->width; j++)
				fscanf(in, "%d", &g->m->paths[i][j]);
		}
		fclose(in);

		g->m->dots = malloc(g->m->height * sizeof(int*));
		for (int i = 0; i < g->m->height; i++)
		{
			g->m->dots[i] = malloc(g->m->width * sizeof(int));
			for (int j = 0; j < g->m->width; j++)
			{
				fscanf(fs,"%d", &g->m->dots[i][j]);
			}
		}

		g->m->powerups = malloc(g->m->height * sizeof(int*));
		for (int i = 0; i < g->m->height; i++)
		{
			g->m->powerups[i] = malloc(g->m->width * sizeof(int));
			for (int j = 0; j < g->m->width; j++)
			{
				fscanf(fs,"%d", &g->m->powerups[i][j]);
			}
		}

		int px; int py; int p_pow;
		fscanf(fs,"%d %d %d", &px, &py, &p_pow);
		g->p = gen_paccy(px, py);
		g->p->powered_up = p_pow;
		int num_g;
		fscanf(fs,"%d", &num_g);
		g->num_ghost = num_g;
		int *xs = malloc(num_g * sizeof(int));
		int *ys = malloc(num_g * sizeof(int));
		for (int i = 0; i < num_g; i++)
		{
			fscanf(fs, "%d %d", xs + i, ys + i);
		}
		g->ghosts = gen_ghosts(num_g, xs, ys);
		fscanf(fs, "%d", &g->score);
		fscanf(fs, "%d", &g->speed);
		fscanf(fs, "%d", &g->lvl);
		fscanf(fs, "%d", &g->game_end);
		fscanf(fs, "%d", &g->lives);
		fscanf(fs, "%d", &g->time);
		fclose(fs);
		return g;
	}
	else
	{
		fclose(fs);
		return NULL;
	}
}
