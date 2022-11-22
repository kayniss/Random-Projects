#include "rogue.h"

Room * createRoom(int grid, int numberOfDoors) {
    int i;
    Room * newRoom;
    newRoom = malloc(sizeof(Room));
    newRoom->numberOfDoors = numberOfDoors;

    switch (grid) {
        case 0:
            newRoom->position.x = 0;
            newRoom->position.y = 0;
            break;
        case 1:
            newRoom->position.x = 33;
            newRoom->position.y = 0;
            break;
        case 2:
            newRoom->position.x = 66;
            newRoom->position.y = 0;
            break;
        case 3:
            newRoom->position.x = 0;
            newRoom->position.y = 14;
            break;
        case 4:
            newRoom->position.x = 33;
            newRoom->position.y = 14;
            break;
        case 5:
            newRoom->position.x = 66;
            newRoom->position.y = 14;
            break;
    }

    newRoom->width = rand() % 14 + 4; // max size 17
    newRoom->height = rand() % 6 + 4; // max size 9

    // offset
    newRoom->position.x += rand() % (30 - newRoom->width) + 1;
    newRoom->position.y += rand() % (10 - newRoom->height) + 1;

    // not dynamical made therefore . not ->
    newRoom->doors = malloc(sizeof(Door *) * numberOfDoors);
    for (i = 0; i < numberOfDoors; i++) {
        newRoom->doors[i] = malloc(sizeof(Door));
        newRoom->doors[i]->connected = 0;
    }

    // top door
    newRoom->doors[0]->position.x = rand() % (newRoom->width - 2) + newRoom->position.x + 1;
    newRoom->doors[0]->position.y = newRoom->position.y;

    // bottom door
    newRoom->doors[1]->position.y = rand() % (newRoom->height - 2) + newRoom->position.y + 1;
    newRoom->doors[1]->position.x = newRoom->position.x;

    // left door
    newRoom->doors[2]->position.x = rand() % (newRoom->width - 2) + newRoom->position.x + 1;
    newRoom->doors[2]->position.y = newRoom->position.y + newRoom->height - 1;

    // right door
    newRoom->doors[3]->position.y = rand() % (newRoom->height - 2) + newRoom->position.y + 1;
    newRoom->doors[3]->position.x = newRoom->position.x + newRoom->width - 1;

    return newRoom;
}

int drawRoom(Room * room) {
    
    int y;
    int x;

    // Draw top and bottom
    for (x = room->position.x; x < room->position.x + room->width; x++) {
        mvprintw(room->position.y, x, "-"); // top
        mvprintw(room->position.y + room->height - 1, x, "-"); // bottom
    }

    // draw floors and side walls
    for (y = room->position.y + 1; y < room->position.y + room->height - 1; y++) {
        
        // draw side walls
        mvprintw(y, room->position.x, "|");
        mvprintw(y, room->position.x + room->width - 1, "|");
        
        // draw florrs
        for (x = room->position.x + 1; x < room->position.x + room->width - 1; x++) {
            mvprintw(y, x, ".");
        }
    }

    // draw doors
    mvprintw(room->doors[0]->position.y, room->doors[0]->position.x, "+");
    mvprintw(room->doors[1]->position.y, room->doors[1]->position.x, "+");
    mvprintw(room->doors[2]->position.y, room->doors[2]->position.x, "+");
    mvprintw(room->doors[3]->position.y, room->doors[3]->position.x, "+");

    return 1;
}