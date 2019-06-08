#include<stdio.h>
#include "zapisi_interface.h"
#include "key_press.h"
#include "structs.h"
void highscores()
{
    FILE *f=fopen("scores.cep","rb");

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    cls(hStdOut);
    char c;
	printf("HIGHSCORES\n");
	printf("\n");
	int n = 0; score s;
	while (fread(&s,sizeof(score),1,f)==1)
	{
		if (s.score != 0)
		{
			printf("%d. %s %d\n", (n + 1), s.ime, s.score);
		}
		else
		{
			printf("%d.\n", n + 1);
		}
		n++;
	}
    fclose(f);
    printf("\n\n*** PRESS ENTER TO RETURN TO MAIN MENU ***");
    while (1)
    {
        if (_kbhit())
        {
            int c=_getch();
            if (c==0xD) return;
        }
    }
}
