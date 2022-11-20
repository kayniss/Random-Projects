#include "rogue.h"

int main () {

    Player * user;
    int ch;
    
    screenSetUp();   

    mapSetUp();

    user = playerSetUp();

    while ((ch = getch()) != 'q') {
        handleInput(ch, user);
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

Room ** mapSetUp() {

    Room ** rooms;
    rooms = malloc(sizeof(Room)* 6);
    
    rooms[0] = createRoom(13, 13, 6, 8);
    drawRoom(rooms[0]);

    rooms[1] = createRoom(2, 40, 6, 8);
    drawRoom(rooms[1]);

    rooms[2] = createRoom(10, 40, 6, 12); 
    drawRoom(rooms[2]);

    connectDoors(rooms[0]->doors[3], rooms[2]->doors[1]);
    connectDoors(rooms[1]->doors[2], rooms[0]->doors[0]);

    return rooms;
}