#include <string>
#include <ncurses.h>
#include <unistd.h>
#include "game.h"

WINDOW* wnd;

struct {
    vec2i pos;
    char disp_char;
} player;

int init() {
    wnd = initscr();
    cbreak();
    noecho();
    clear();
    refresh();

    keypad(wnd, true); // interpret action keys
    nodelay(wnd, true); // disable blocking when using wgetch()
    curs_set(0); // make the cursor invisble

    // check if the terminal supports colors
    if(!has_colors()) {
        endwin();
        printf("Unfortunately, your terminal does not support colors\n");
        exit(1);
    }
    start_color();

    attron(A_BOLD);
    box(wnd, 0, 0);
    attroff(A_BOLD);

    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    wbkgd(wnd, COLOR_PAIR(1));

    return 0;
}


void run() {
    player.disp_char = '0';
    player.pos = {10, 5};
    mvaddch(player.pos.y, player.pos.x, player.disp_char);
    refresh();

    // game loop
    int in_char;
 bool exit_requested = false;

    while(1) {
        in_char = wgetch(wnd);
        mvaddch(player.pos.y, player.pos.x, ' ');
        
        switch(in_char) {
            case 'q':
                exit_requested = true;
                break;
            case KEY_UP:
            case 'w':
                player.pos.y -= 1;
                break;
            case KEY_DOWN:
            case 's':
                player.pos.y += 1;
                break;
            case KEY_LEFT:
            case 'a':
                player.pos.x -= 1;
                break;
            case KEY_RIGHT:
            case 'd':
                player.pos.x += 1;
                break;
            default:
                break;
        }

        mvaddch(player.pos.y, player.pos.x, player.disp_char);
        refresh();

        if(exit_requested) break;
        usleep(10000); // 10 ms
        refresh();
    }
}


void close() {
    endwin();
}