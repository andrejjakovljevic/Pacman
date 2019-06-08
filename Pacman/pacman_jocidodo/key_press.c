// #define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include<conio.h>
#include "key_press.h"


void cls(HANDLE hConsole)
{
	COORD coordScreen = { 0, 0 };    // home for the cursor
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;

	// Get the number of character cells in the current buffer.

	if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
	{
		return;
	}

	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

	// Fill the entire screen with blanks.

	if (!FillConsoleOutputCharacter(hConsole,        // Handle to console screen buffer
		(TCHAR) ' ',     // Character to write to the buffer
		dwConSize,       // Number of cells to write
		coordScreen,     // Coordinates of first cell
		&cCharsWritten))// Receive number of characters written
	{
		return;
	}

	// Get the current text attribute.

	if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
	{
		return;
	}

	// Set the buffer's attributes accordingly.

	if (!FillConsoleOutputAttribute(hConsole,         // Handle to console screen buffer
		csbi.wAttributes, // Character attributes to use
		dwConSize,        // Number of cells to set attribute
		coordScreen,      // Coordinates of first cell
		&cCharsWritten)) // Receive number of characters written
	{
		return;
	}

	// Put the cursor at its home coordinates.

	SetConsoleCursorPosition(hConsole, coordScreen);
}
void write_symbol_in_color(HANDLE h, SHORT x, SHORT y, const char* symbol, WORD color)
{
	COORD here;
	here.X = x;
	here.Y = y;

	WORD attribute = color;
	DWORD written;
	WriteConsoleOutputAttribute(h, &attribute, 1, here, &written);
	WriteConsoleOutputCharacterA(h, symbol, 1, here, &written);
}

void write_symbol(HANDLE h, SHORT x, SHORT y, const char* symbol)
{
	COORD here;
	here.X = x;
	here.Y = y;
	DWORD written;
	WORD attribute = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
	WriteConsoleOutputAttribute(h, &attribute, 1, here, &written);
	WriteConsoleOutputCharacter(h, symbol, 1, here, &written);
}

void ispis_string(char* str, int x, int y, HANDLE h)
{
	COORD here;
	here.X = x;
	here.Y = y;
	DWORD written;
	WORD attribute = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
	for (int i = 0; i < strlen(str); i++)
	{
		here.X++;
		WriteConsoleOutputAttribute(h, &attribute, 1, here, &written);
		WriteConsoleOutputCharacter(h, str+i, 1, here, &written);
	}
}

char* broj_to_string(int num)
{
	int br = 0; int pom = num;
	while (pom)
	{
		pom /= 10;
		br++;
	}
	pom = num;
	char* s = malloc(6 * sizeof(char));
	for (int i = 0; i < br; i++)
	{
		s[br - 1 - i] = (pom % 10) + '0';
		pom /= 10;
	}
	s[br] = '\0';
	return s;
}


