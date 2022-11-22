#include "rogue.h"

int main () {

    int ch;
    Position * newPosition;

    Level * level;

    screenSetUp();

    level = createLevel(1);

    // main game loop
    while ((ch = getch()) != 'q') {
        newPosition = handleInput(ch, level->user);
        checkPosition(newPosition, level);
        moveMonsters(level);
        move(level->user->position->y, level->user->position->x);
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

