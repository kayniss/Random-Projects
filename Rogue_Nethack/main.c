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
Room ** mapSetUp();
Player * playerSetUp();
int handleInput(int input, Player * user);
int checkPosition(int new_y, int new_x, Player * unit);
int playerMove(int y, int x, Player * user);

/* room functions */
Room * createRoom(int y, int x, int height, int width);
int drawRoom(Room * room);
int connectDoors(Position * doorOne, Position * doorTwo);

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

    // mvprintw(13, 13, "--------");
    // mvprintw(14, 13, "|......|");
    // mvprintw(15, 13, "|......|");
    // mvprintw(16, 13, "|......|");
    // mvprintw(17, 13, "|......|");
    // mvprintw(18, 13, "--------");
    
    rooms[0] = createRoom(13, 13, 6, 8);
    drawRoom(rooms[0]);

    // mvprintw(2, 40, "--------");
    // mvprintw(3, 40, "|......|");
    // mvprintw(4, 40, "|......|");
    // mvprintw(5, 40, "|......|");
    // mvprintw(6, 40, "|......|");
    // mvprintw(7, 40, "--------");

    rooms[1] = createRoom(2, 40, 6, 8);
    drawRoom(rooms[1]);

    // mvprintw(10, 40, "------------");
    // mvprintw(11, 40, "|..........|");
    // mvprintw(12, 40, "|..........|");
    // mvprintw(13, 40, "|..........|");
    // mvprintw(14, 40, "|..........|");
    // mvprintw(15, 40, "------------");   

    rooms[2] = createRoom(10, 40, 6, 12); 
    drawRoom(rooms[2]);

    connectDoors(rooms[0]->doors[3], rooms[2]->doors[1]);

    return rooms;
}

Room * createRoom(int y, int x, int height, int width) {
    Room * newRoom;
    newRoom = malloc(sizeof(Room));

    // not dynamical made therefore . not ->
    newRoom->position.y = y;
    newRoom->position.x = x;
    newRoom->height = height;
    newRoom->width = width;
    newRoom->doors = malloc(sizeof(Position) * 4);

    // top door
    newRoom->doors[0] = malloc(sizeof(Position));
    newRoom->doors[0]->x = rand() % (width - 2) + newRoom->position.x + 1;
    newRoom->doors[0]->y = newRoom->position.y;

    // bottom door
    newRoom->doors[1] = malloc(sizeof(Position));
    newRoom->doors[1]->y = rand() % (height - 2) + newRoom->position.y + 1;
    newRoom->doors[1]->x = newRoom->position.x;

    // left door
    newRoom->doors[2] = malloc(sizeof(Position));
    newRoom->doors[2]->x = rand() % (width - 2) + newRoom->position.x + 1;
    newRoom->doors[2]->y = newRoom->position.y + newRoom->height - 1;

    // right door
    newRoom->doors[3] = malloc(sizeof(Position));
    newRoom->doors[3]->y = rand() % (height - 2) + newRoom->position.y + 1;
    newRoom->doors[3]->x = newRoom->position.x + width - 1;

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
    mvprintw(room->doors[0]->y, room->doors[0]->x, "+");
    mvprintw(room->doors[1]->y, room->doors[1]->x, "+");
    mvprintw(room->doors[2]->y, room->doors[2]->x, "+");
    mvprintw(room->doors[3]->y, room->doors[3]->x, "+");

    return 1;
}

int connectDoors(Position * doorOne, Position * doorTwo) {

    Position temp;

    temp.x = doorOne->x;
    temp.y = doorOne->y;

    while (1) {
        // step left
        if ((abs((temp.x - 1) - doorTwo->x) < abs(temp.x - doorTwo->x)) && mvinch(temp.y, temp.x - 1) == ' ') {
            mvprintw(temp.y, temp.x - 1, "#");
            temp.x = temp.x - 1;
        }
        // step right
        else if ((abs((temp.x + 1) - doorTwo->x) < abs(temp.x - doorTwo->x)) && mvinch(temp.y, temp.x + 1) == ' ') {
            mvprintw(temp.y, temp.x + 1, "#");
            temp.x = temp.x + 1;
        }
        // step down
        else if ((abs((temp.y + 1) - doorTwo->y) < abs(temp.y - doorTwo->y)) && mvinch(temp.y + 1, temp.x) == ' ') {
            mvprintw(temp.y + 1, temp.x, "#");
            temp.y = temp.y + 1;
        }
        // step up
        else if ((abs((temp.y - 1) - doorTwo->y) < abs(temp.y - doorTwo->y)) && mvinch(temp.y - 1, temp.x) == ' ') {
            mvprintw(temp.y - 1, temp.x, "#");
            temp.y = temp.y - 1;
        }
        else {
            return 0;
        }

        getch();
    }


    return 1;
}

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