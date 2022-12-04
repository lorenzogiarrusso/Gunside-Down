#ifndef _CREATURE_H
#define _CREATURE_H

#include <ncurses.h>
using namespace std;

//superclass for enemies and player
class Creature{
    protected:
        int xLoc, yLoc, xMax, yMax;     //hold current position and the window's max x and y
        char character;                 //character used to represent the creature
        bool is_landed;
        bool face_right;
        int total_hp, current_hp;
        WINDOW* currwin;
    public:
        Creature(WINDOW* win, int y, int x, int hp, char c);
        void mvup();
        void mvdown();
        void mvright();
        void mvleft();
        void display();                 //prints the creature onto the window

        int get_current_hp();
        int get_total_hp();
        void decrement_hp();
        
        bool facing_right();
        void set_face_left();
        void set_face_right();
};

#endif
