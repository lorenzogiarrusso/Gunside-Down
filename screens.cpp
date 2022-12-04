#include "screens.hpp"
#define PLAYER_HEALTH 5

//prints title art and main menu
int print_title(WINDOW* win){
    wclear(win);
    int highlight = 0;                                         //index of currently highlighted option
    string menu_options[] = {"  GAME START  ", " LEVEL SELECT ", 
                             "   CONTROLS   ", "     QUIT     "};
    keypad(win, true);
    int choice = 0;                                            //holds the input arrow
    int yMax, xMax;
    getmaxyx(win, yMax, xMax);

    //print title art
    wattron(win, A_REVERSE);
    mvwprintw(win, 4, 0, "\n\t     _____                                                             \n\t  __|___  |__  __   _  ____   _  ______  ____  _____   ______          \n\t |   ___|    ||  | | ||    \\ | ||   ___||    ||     \\ |   ___|         \n\t |   |  |    ||  |_| ||     \\| | `-.`-. |    ||      \\|   ___|         \n\t |______|  __||______||__/\\____||______||____||______/|______|         \n\t    |_____|  _____   _____  __  __  __  ____   _                       \n\t            |     \\ /     \\|  \\/  \\|  ||    \\ | |                      \n\t            |      \\|     ||     /\\   ||     \\| |                      \n\t            |______/\\_____/|____/  \\__||__/\\____|                      \n                                                                               \n");
    wattroff(win, A_REVERSE);
    
    mvwprintw(win, yMax/2 + 8, xMax/2 - 7, "PRESS ");
    wattron(win, A_REVERSE);
    mvwprintw(win, yMax/2 + 8, xMax/2 - 1, " Z ");
    wattroff(win, A_REVERSE);
    mvwprintw(win, yMax/2 + 8, xMax/2 + 2, " TO SELECT");
    do{                                                        //prints menu and highlights the currently
                                                               //selected option; repeats until an option
                                                               //is selected with the z button
        for(int i = 0; i < 4; i++){                            
            if(highlight == i) wattron(win, A_REVERSE);
            mvwprintw(win, yMax/2 + i+10, xMax/2 - 5, "%s", menu_options[i].c_str());
            wattroff(win, A_REVERSE);
        }
        choice = wgetch(win);
        if(choice == KEY_UP){
            highlight--;
            if (highlight < 0) highlight = 3;
        }
        else if(choice == KEY_DOWN){
            highlight++;
            if(highlight > 3) highlight = 0;
        }
    }while(choice != 'z' && choice != 'Z');
    return highlight;
}

//executes the game screen
//TODO: separate unrelated things into a game_loop function?
void game_play(WINDOW* win, WINDOW* header){
    wclear(win);

    int pause_input = 0;        //holds input received while the pause screen is displayed
    int yMax_scr, xMax_scr;
    int yMax_win, xMax_win;
    int yBeg_win, xBeg_win;

    getmaxyx(stdscr, yMax_scr, xMax_scr);
    getmaxyx(win, yMax_win, xMax_win);
    getbegyx(win, yBeg_win, yBeg_win);

    box(win, 0, 0);
    wrefresh(win);
    wrefresh(header);
    wtimeout(win, 7);
        
    Player* p = new Player(win, yMax_win, 1, PLAYER_HEALTH, '}');

    do{
            if(clock()%100 < 20) p->fall();
            p->display();
            wrefresh(win);
            mvwprintw(header, 0, 0, "LIFE: ");
            for(int i = 0; i < p -> get_total_hp(); i++){
                if(i < p->get_current_hp()) mvwprintw(header, 0, 7 + i, "O");
                else mvwprintw(header, 0, 7 + i, "-");
            }
            wrefresh(header);

            if(p->getMov() == 10)   //10 = Enter
                pause_input = print_pause(win);
            wrefresh(win);
            wtimeout(win, 7);
            p->getMov();
    }while(pause_input != 'q');
    wtimeout(win, -1);
    werase(header);
    wrefresh(header);
}

//prints level select screen
void print_lvl_select(WINDOW* win){
    wclear(win);
    getch();
}

//prints controls screen
void print_controls(WINDOW* win){
    wclear(win);
    box(win, 0, 0);
    wrefresh(win);
    int xMax, yMax;
    getmaxyx(win, yMax, xMax);
    int y_button = yMax / 4 - 3;
    int x_button = xMax / 8 + 8;

    //Z
    wattron(win, A_REVERSE);
    mvwprintw(win, y_button, x_button, "   Z   ");
    wattroff(win, A_REVERSE);
    mvwprintw(win, y_button, x_button + 15, "SWITCH GRAVITY");
    
    //X
    wattron(win, A_REVERSE);
    mvwprintw(win, y_button + 4, x_button, "   X   ");
    wattroff(win, A_REVERSE);
    mvwprintw(win, y_button + 4, x_button + 15, "SHOOT");

    //←→
    wattron(win, A_REVERSE);
    mvwprintw(win, y_button + 8, x_button, " <- -> ");
    wattroff(win, A_REVERSE);
    mvwprintw(win, y_button + 8, x_button + 15, "MOVE");

    //P
    wattron(win, A_REVERSE);
    mvwprintw(win, y_button + 12, x_button, " ENTER ");
    wattroff(win, A_REVERSE);
    mvwprintw(win, y_button + 12, x_button + 15, "PAUSE");

    mvwprintw(win, y_button + 20, x_button + 8, "PRESS ANY BUTTON TO RETURN TO TITLE");

    wrefresh(win);
    wgetch(win);
}

//prints pause window, return input received while the puase window is displayed
//TODO: actually print stuff in the pause window
int print_pause(WINDOW* win){
    int xMax, yMax;
    int input = 0;
    getmaxyx(stdscr, yMax, xMax);
    wtimeout(win, -1);
    WINDOW* pause= newwin(10, 20, yMax/2 - 5, xMax/2 - 10);
    box(pause, 0, 0);
    mvwprintw(pause, 2, 7, "PAUSED");
    mvwprintw(pause, 4, 4, "Z  -  RESUME");
    mvwprintw(pause, 6, 4, "Q  -  QUIT");
    wrefresh(pause);
    while(input != 'q' && input != 'Q' && input != 'z' && input != 'Z') input = wgetch(pause);
    werase(pause);
    wrefresh(pause);
    wrefresh(win);
    wtimeout(win, 7);
    return input;
}