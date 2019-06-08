#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

#include <windows.h>

#include "key_press.h"

const int WIDTH_MAX=200;

void print_menu (int i, HANDLE hStdOut)
{
    FILE *f;

    if (i==1)
        f=fopen("mainmenu1.txt","r");
    else
    if (i==2)
        f=fopen("mainmenu2.txt","r");
    else
    if (i==3)
        f=fopen("mainmenu3.txt","r");
    else
    if (i==4)
        f=fopen("mainmenu4.txt","r");
    else
    if (i==5)
        f=fopen("mainmenu5.txt","r");
    else
        f=fopen("mainmenu6.txt","r");
    char c;
    int x=0, y=0;
    while ((c=fgetc(f))!=EOF)
    {
        if (c=='\n')
        {
            for (;x<=WIDTH_MAX;x++)
                write_symbol(hStdOut, x, y, " ");
            x=0;
            y++;
        }
        else
            write_symbol(hStdOut, x++, y, &c);
    }
    for (;x<=WIDTH_MAX;x++)
                write_symbol(hStdOut, x, y, " "); // poslednji red obrisi
    /*while ((fscanf(f,"%c",&c)!=EOF))
        printf("%c",c);*/
    fclose(f);
}

void ispis_options(int i, int num_ghost, int lives, int dif, HANDLE hStdOut)
{
	FILE *f = NULL;
	FILE *f1 = NULL;
	FILE *f2 = NULL;
	FILE *f3 = NULL;
	char* s1 = "1.txt";
	char* s2 = "2.txt";
	char* s3 = "3.txt";
	char* s4 = "4.txt";
	char *sn1=NULL; char* sn2=NULL; char* sn3=NULL;
	if (num_ghost == 1)
	{
		sn1 = s1;
	}
	if (num_ghost == 2)
	{
		sn1 = s2;
	}
	if (num_ghost == 3)
	{
		sn1 = s3;
	}
	if (num_ghost == 4)
	{
		sn1 = s4;
	}
	if (lives == 1)
	{
		sn2 = s1;
	}
	if (lives == 2)
	{
		sn2 = s2;
	}
	if (lives == 3)
	{
		sn2 = s3;
	}
	if (lives == 4)
	{
		sn2 = s4;
	}
	if (dif == 1)
	{
		sn3 = s1;
	}
	if (dif == 2)
	{
		sn3 = s2;
	}
	if (dif == 3)
	{
		sn3 = s3;
	}
	if (dif == 4)
	{
		sn3 = s4;
	}
	f1 = fopen(sn1, "r");
	f2 = fopen(sn2, "r");
	f3 = fopen(sn3, "r");
	if (i==1)
        f=fopen("options1.txt","r");
    else
    if (i==2)
        f=fopen("options2.txt","r");
    else
    if (i==3)
        f=fopen("options3.txt","r");
	char c;
	if (f == NULL) return;
	char **mat = malloc(150 * sizeof(char*));
	char **mat1 = malloc(6 * sizeof(char*));
	char **mat2 = malloc(6 * sizeof(char*));
	char **mat3 = malloc(6 * sizeof(char*));
	for (int i = 0; i < 6; i++)
	{
		mat1[i] = malloc(20 * sizeof(char));
		mat2[i] = malloc(20 * sizeof(char));
		mat3[i] = malloc(20 * sizeof(char));
		for (int j = 0; j < 20; j++)
		{
			mat1[i][j] = ' ';
			mat2[i][j] = ' ';
			mat3[i][j] = ' ';
		}
	}
	for (int i = 0; i < 150; i++)
	{
		mat[i] = malloc(150 * sizeof(char));
		for (int j = 0; j < 150; j++)
		{
			mat[i][j] = ' ';
		}
	}
	int x = 0; int y = 0;

	while ((c = fgetc(f)) != EOF)
	{
		if (c == '\n')
		{
			x++; y = 0;
		}
		else mat[x][y] = c;
		y++;
	}
	x = 0; y = 0;
	while ((c = fgetc(f2)) != EOF)
	{
		if (c == '\n')
		{
			x++; y = 0;
		}
		else mat2[x][y] = c;
		y++;
	}
	x = 0; y = 0;
	while ((c = fgetc(f3)) != EOF)
	{
		if (c == '\n')
		{
			x++; y = 0;
		}
		else mat3[x][y] = c;
		y++;
	}
	x = 0; y = 0;
	while ((c = fgetc(f1)) != EOF)
	{
		if (c == '\n')
		{
			x++; y = 0;
		}
		else mat1[x][y] = c;
		y++;
	}
	fclose(f);
	fclose(f1);
	fclose(f2);
	fclose(f3);
	for (int i = 0; i < 150; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			write_symbol(hStdOut, j, i, &mat[i][j]);
		}
	}
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			write_symbol(hStdOut, j + 50, i + 8, &mat1[i][j]);
			write_symbol(hStdOut, j + 50, i + 14, &mat2[i][j]);
			write_symbol(hStdOut, j + 50, i + 20, &mat3[i][j]);
		}
	}
	for (int i = 0; i < 150; i++)
	{
		free(mat[i]);
	}
	for (int i = 0; i < 6; i++)
	{
		if (mat1[i]) free(mat1[i]);
		if (mat2[i]) free(mat2[i]);
		if (mat3[i]) free(mat3[i]);
	}
	free(mat1);
	free(mat2);
	free(mat3);
	free(mat);
	fclose(f);
}
