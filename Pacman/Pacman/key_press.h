#ifndef KEY_PRESS_H
#define KEY_PRESS_H
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include<stdio.h>

void cls(HANDLE hConsole);
void write_symbol_in_color(HANDLE h, SHORT x, SHORT y, const char* symbol, WORD color);

#endif
