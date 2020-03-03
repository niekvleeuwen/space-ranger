#include <ncurses.h>
#include <string>
using namespace std;

int main(int argv, char** argc) {
    initscr();
    cbreak();
    noecho();
    clear();
    refresh();

    move(5, 5);
    string text = "Hello world!";
    for(int i = 0; i < text.size(); i++) {
        addch(text[i]);
        addch(' ');
    }
    refresh();

    while(1);
    return 0;
}