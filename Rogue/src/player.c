#include "rogue.h"

Player * playerSetUp() {
    Player * newPlayer;
    newPlayer = malloc(sizeof(Player)); 

    newPlayer->position.x = 14;
    newPlayer->position.y = 14;
    newPlayer->health = 20;

    playerMove(14, 14, newPlayer);

    return newPlayer;
}

int handleInput(int input, Player * user) {
    
    int new_y;
    int new_x;
    switch (input) {
        // move up
        case 'w':
        case 'W':
            new_y = user->position.y - 1;
            new_x = user->position.x;
            break;

        // move down
        case 's':
        case 'S':
            new_y = user->position.y + 1;
            new_x = user->position.x;
            break;

        // move left
        case 'a':
        case 'A':
            new_y = user->position.y;
            new_x = user->position.x - 1;
            break;

        // move right
        case 'd':
        case 'D':
            new_y = user->position.y;
            new_x = user->position.x + 1;
            break;

        default:
            break;

    }

    checkPosition(new_y, new_x, user);
}

// check what is at the next position
int checkPosition(int new_y, int new_x, Player * user) {

    int space;
    switch (mvinch(new_y, new_x)) {
        case '.':
            playerMove(new_y, new_x, user);
            break;
        default:
            move(user->position.y, user->position.x);
            break;
    }
}

int playerMove(int y, int x, Player * user) {
    
    mvprintw(user->position.y, user->position.x, ".");

    user->position.y = y;
    user->position.x = x;

    mvprintw(user->position.y, user->position.x, "@");
    move(user->position.y, user->position.x);
}