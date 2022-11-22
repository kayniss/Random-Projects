#include "rogue.h"

Player * playerSetUp() {
    Player * newPlayer;
    newPlayer = malloc(sizeof(Player));
    newPlayer->position = malloc(sizeof(Position)); 

    newPlayer->position->x = 14;
    newPlayer->position->y = 14;
    newPlayer->health = 20;
    newPlayer->attack = 1;

    mvprintw(newPlayer->position->y, newPlayer->position->x, "@");
    move(newPlayer->position->y, newPlayer->position->x);

    return newPlayer;
}

Position * handleInput(int input, Player * user) {
    
    Position * newPosition;
    newPosition = malloc(sizeof(Position));

    switch (input) {
        // move up
        case 'w':
        case 'W':
            newPosition->y = user->position->y - 1;
            newPosition->x = user->position->x;
            break;

        // move down
        case 's':
        case 'S':
            newPosition->y = user->position->y + 1;
            newPosition->x = user->position->x;
            break;

        // move left
        case 'a':
        case 'A':
            newPosition->y = user->position->y;
            newPosition->x = user->position->x - 1;
            break;

        // move right
        case 'd':
        case 'D':
            newPosition->y = user->position->y;
            newPosition->x = user->position->x + 1;
            break;

        default:
            break;

    }

    return newPosition;
}

// check what is at the next position
int checkPosition(Position * newPosition, Level * level) {

    Player * user;
    user = level->user;
    int space;

    switch (mvinch(newPosition->y, newPosition->x)) {
        case '.':
        case '#':
        case '+':
            playerMove(newPosition, user, level->tiles);
            break;
        case 'X':
            combat(user, getMonsterAt(newPosition, level->monsters), PLAYER_ORDER);
        case 'G':
            combat(user, getMonsterAt(newPosition, level->monsters), PLAYER_ORDER);
        case 'T':
            combat(user, getMonsterAt(newPosition, level->monsters), PLAYER_ORDER);
        default:
            move(user->position->y, user->position->x);
            break;
    }
}

int playerMove(Position * newPosition, Player * user, char ** level) {
    
    char buffer[BUFFER_LENGTH];

    sprintf(buffer, "%c", level[user->position->y][user->position->x]);

    mvprintw(user->position->y, user->position->x, buffer);

    user->position->y = newPosition->y;
    user->position->x = newPosition->x;

    mvprintw(user->position->y, user->position->x, "@");
    move(user->position->y, user->position->x);
}