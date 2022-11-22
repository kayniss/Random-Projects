#include "rogue.h"

int main () {

    Player * user;
    int ch;
    Position * newPosition;

    Level * level;

    screenSetUp();

    level = createLevel(1);

    user = playerSetUp();

    // main game loop
    while ((ch = getch()) != 'q') {
        newPosition = handleInput(ch, user);
        checkPosition(newPosition, user, level->tiles);
    }
    endwin();

    return 0;
}

int screenSetUp() {
    initscr();
    printw("Hello world!");
    noecho(); // whatever you type shows on screen, disabled with this
    refresh();

    srand(time(NULL));

    return 1;
}

