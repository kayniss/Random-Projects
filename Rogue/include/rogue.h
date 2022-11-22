#ifndef ROGUE_H
#define ROGUE_H

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

typedef struct Position {
    int y;
    int x;
    // TILE_TYPE tile;
} Position;

typedef struct Room {
    Position position;
    int height;
    int width;

    Position ** doors;
    // Pointer of an array of monsters and items 
    // Monster ** monsters;
    // Item ** items;
} Room;

typedef struct Player {
    Position position;
    int health;
    // Room * room;
} Player;

int screenSetUp();

// level/map functions 
Room ** mapSetUp();
char ** saveLevelPositions();

// player functions 
Player * playerSetUp();
Position * handleInput(int input, Player * user);
int checkPosition(Position * newPosition, Player * unit, char ** level);
int playerMove(Position * newPosition, Player * user, char ** level);

/* room functions */
Room * createRoom(int y, int x, int height, int width);
int drawRoom(Room * room);
int connectDoors(Position * doorOne, Position * doorTwo);

#endif