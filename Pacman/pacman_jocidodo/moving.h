#ifndef MOVING_H
#define MOVING_H

#include <stdio.h>

void move_paccy(game* g); //1 - dole; 2-desno; 3-gore; 4-levo
void change_paccy_direction(game* g, char c);
void move_ghosts(game *g);
void paccy_dots(game* g);
void paccy_power_ups(game* g);
void paccy_ghost(game* g);
void pass_time(game* g);
#endif // !MOVING_H
