#include "player.hpp"
#include "creature.hpp"
#include "screens.hpp"
#include <iostream>
#include <ctime>
using namespace std;

int main(){
    initscr();
    noecho();
    cbreak();
    curs_set(0);

    int menu_select;        //holds index of what is selected in the title screen
                            // 0 -> Game start 
                            // 1 -> Level select 
                            // 2 -> Controls 
                            // 3 -> Quit

    int yMax_scr, xMax_scr;
    getmaxyx(stdscr, yMax_scr, xMax_scr);

    WINDOW* header = newwin(1, 40, yMax_scr/2 - 16, xMax_scr/2 - 40);
    WINDOW* win = newwin(30, 80, yMax_scr/2 - 15, xMax_scr/2 - 40);

    do{
        menu_select = print_title(win);     

        switch(menu_select){
            case 0:
                game_play(win, header);
                break;
            case 1:
                print_lvl_select(win);
                break;
            case 2:
                print_controls(win);
                break;
            default:
                break;
        }
    }while(menu_select != 3);
    wrefresh(win);
    endwin();
    return 0;
}
