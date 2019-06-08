#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include <windows.h>
#include "zapisi_interface.h"
#include "key_press.h"
int main()
{
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);
    int p=1;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    print_menu(p, hStdOut);
    while (1) // menu_loop
    {
        if (_kbhit())
        {
            int c=_getch();

            if (c==0 || c==224)
            {
                c=_getch();
                if (c==72) // key up
                {
                    if (p>1) p--;
                }
                else
                if (c==80) // key down
                {
                    if (p<6) p++;
                }
            }
            else
            if (c==0xD)  //enter key
            {
				if (p == 1)
				{
					cls(hStdOut);
					continue_game();
				}
                if (p==2)
                {
                    cls(hStdOut);
                    new_game();
                }
                if (p==3) highscores();
				if (p == 4) options();
                if (p==6)
                {
                    cls(hStdOut);
                    exit(0);   // KAKO ODMAH IZACI?
                }

                print_menu(p,hStdOut);
            }

            print_menu(p,hStdOut);
        }
    }
    return 0;
}
