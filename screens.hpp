#ifndef _SCREENS_H
#define _SCREENS_H

#include <ncurses.h>
#include <string>
#include "player.hpp"
#include <ctime>
using namespace std;

//prints title art and main menu
int print_title(WINDOW*);

//executes the game screen
void game_play(WINDOW*, WINDOW*);

//prints level select screen
void print_lvl_select(WINDOW*);

//prints controls screen
void print_controls(WINDOW*);

//prints pause window, return input received while the puase window is displayed
int print_pause(WINDOW*);

#endif
