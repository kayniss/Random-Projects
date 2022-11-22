#ifndef ROGUE_H
#define ROGUE_H

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

/**************** Struct Definitions ****************/
typedef struct Level {
    char ** tiles;
    int level;
    int number_of_rooms;
    struct Room ** rooms;
    struct Monster ** monsters;
    int number_of_monsters;
    struct Player * user;
} Level;

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

//  Just use the address-of operator "&", i.e. &(player->position) to turn a position into a pointer!
typedef struct Player {
    Position * position;
    int health;
    int attack;
    int gold;
    int maxHealth;
    int exp;
    // Room * room;
} Player;

typedef struct Monster {
    char string[2];
    char symbol;
    int health;
    int attack;
    int speed;
    int defence;
    int pathfinding;
    int alive;
    Position * position;

} Monster;

/***************** Global Variables *****************/
int MAX_HEIGHT;
int MAX_WIDTH;
#define BUFFER_LENGTH 8
#define SPIDER 1
#define GOBLIN 2
#define TROLL 3
#define PATHFINDING_SEEKING 2
#define PATHFINDING_RANDOM 1
#define PLAYER_ORDER 1 
#define MONSTER_ORDER 0
#define MONSTER_ALIVE 1
#define MONSTER_DEAD 0


// screen functions
int screenSetUp();
int printGameHub(Level * level);

// level/map functions 
Room ** roomsSetUp();
char ** saveLevelPositions();
Level * createLevel(int level);

// player functions 
Player * playerSetUp();
Position * handleInput(int input, Player * user);
int checkPosition(Position * newPosition, Level * level);
int playerMove(Position * newPosition, Player * user, char ** level);
int placePlayer(Room ** rooms, Player * user);

/* room functions */
Room * createRoom(int grid);
int drawRoom(Room * room);
int connectDoors(Position * doorOne, Position * doorTwo);

/* monster functions */
int addMonsters(Level * level);
Monster * selectMonster(int level);
Monster * createMonster(char symbol, int health, int attack, int speed, int defence, int pathfinding);
int setStartingPosition(Monster * monster, Room * room);
int moveMonsters(Level * level);
int pathfindingSeek(Position * start, Position * destination);
int pathfindingRandom(Position * position);
Monster * getMonsterAt(Position * position, Monster ** monsters);
int killMonster(Monster * monster);

int combat(Player * player, Monster * monster, int order);

#endif