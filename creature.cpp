#include "creature.hpp"

Creature::Creature(WINDOW* win, int y, int x, int hp, char c){
    currwin = win;
    yLoc = y;
    xLoc = x;
    getmaxyx(currwin, yMax, xMax);
    total_hp = current_hp = hp;
    character = c;
    is_landed = true;
    bool face_right = true;
}

//TODO: check for platforms
void Creature::mvup(){
    mvwaddch(currwin, yLoc, xLoc, ' ');
    yLoc--;
    if (yLoc < 1){ 
        yLoc = 1;
        is_landed = true;
    }
}

//TODO: check for platforms
void Creature::mvdown(){
    mvwaddch(currwin, yLoc, xLoc, ' ');
    yLoc++;
    if (yLoc > yMax - 2){
        yLoc = yMax - 2;
        is_landed = true;
    }
}

//TODO: check for platforms
void Creature::mvright(){
    mvwaddch(currwin, yLoc, xLoc, ' ');
    xLoc++;
    if(xLoc > xMax - 2) xLoc = xMax - 2;
}

//TODO: check for platforms
void Creature::mvleft(){
    mvwaddch(currwin, yLoc, xLoc, ' ');
    xLoc--;
    if(xLoc < 1) xLoc = 1;
}

//prints the creature onto the window
void Creature::display(){
    mvwaddch(currwin, yLoc, xLoc, character);
}

int Creature::get_current_hp(){
    return current_hp;
}

int Creature::get_total_hp(){
    return total_hp;
}

void Creature::decrement_hp(){
    current_hp--;
    //TODO: implement death (overload for player in order to game over)
}

bool Creature::facing_right(){
    return face_right;
}

void Creature::set_face_left(){
    face_right = false;
}

void Creature::set_face_right(){
    face_right = true;
}