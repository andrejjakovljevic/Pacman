#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

#include "zapisi_interface.h"
#include "key_press.h"

void options()
{
	int p = 1;
	FILE* f = fopen("parameters.txt", "r");
	int num_ghost; int lives; int dif;
	fscanf(f, "%d %d %d", &num_ghost, &lives, &dif);
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	cls(hStdOut);
	ispis_options(p, num_ghost, lives, dif,hStdOut);
	fclose(f);
	while (1) // menu_loop
	{
		if (_kbhit())
		{
			int c = _getch();

			if (c == 0 || c == 224)
			{
				c = _getch();
				if (c == 72) // key up
				{
					if (p > 1) p--;
				}
				if (c == 80) // key down
				{
					if (p < 3) p++;
				}
				if (c == 75) //left key
				{
					if (p == 1)
					{
						if (num_ghost > 1) num_ghost--;
					}
					if (p == 2)
					{
						if (lives > 1) lives--;
					}
					if (p == 3)
					{
						if (dif > 1) dif--;
					}
				}
				if (c == 77) //right key
				{
					if (p == 1)
					{
						if (num_ghost < 4) num_ghost++;
					}
					if (p == 2)
					{
						if (lives < 4) lives++;
					}
					if (p == 3)
					{
						if (dif < 3) dif++;
					}
				}
			}
			else if (c == 27)
			{
				FILE *f = NULL;
				f = fopen("parameters.txt", "w");
				fprintf(f, "%d\n", num_ghost);
				fprintf(f, "%d\n", lives);
				fprintf(f, "%d\n", dif);
				fclose(f);
				return;
			}
			ispis_options(p, num_ghost, lives, dif, hStdOut);
		}
	}
}