#ifndef _PLAYER_H
#define _PLAYER_H

#include <ncurses.h>
#include "creature.hpp"
using namespace std;

class Player : public Creature{
    protected:
        bool gravity;   //if true, gravity is downwards, otherwise upwards
        int coins;
        int score;
    
    public:
        Player(WINDOW* win, int y, int x, int hp, char c);
        int getMov();   //gets input and updates player's position
        void fall();    //makes player "fall" (upwards or downwards) while in the air
};

#endif
