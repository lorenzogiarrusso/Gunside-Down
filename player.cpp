#include "player.hpp"

Player::Player(WINDOW* win, int y, int x, int hp, char c) : Creature(win, y, x, hp, c){
    gravity = true;                         //default gravity is downwards
    coins = 0;
    score = 0;
    keypad(currwin, true);
}

//gets input and updates player's position
int Player::getMov(){ 
    int choice = wgetch(currwin);
    if((choice == 'z' || choice == 'Z') && is_landed){
        gravity = !gravity;   //invert gravity if z is pressed
        is_landed = false;
    }

    if(choice == KEY_RIGHT){                                 //if right arrow is pressed, makes the player face right and move right
        character = '}';
        set_face_right();
        mvright();
    }
    else if(choice == KEY_LEFT){                             //if left arrow is pressed, makes the player face left and move left
        character = '{';
        set_face_left();
        mvleft();
    }

    return choice;
}

//makes player "fall" (upwards or downwards) while in the air
void Player::fall(){
    if(gravity) mvdown();
    else mvup();
}

//TODO: overloaded mv_up and mv_down to implement platform check with gravity
