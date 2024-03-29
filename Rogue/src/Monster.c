#include "rogue.h"

int addMonsters(Level * level) {

    int x;
    level->monsters = malloc(sizeof(Monster *)* 6);
    level->number_of_monsters = 0;

    for (x = 0; x < level->numberOfRooms; x++) {
        if ((rand() % 2) == 0) {
            level->monsters[level->number_of_monsters] = selectMonster(level->level);
            setStartingPosition(level->monsters[level->number_of_monsters], level->rooms[x]);
            level->number_of_monsters++;
        }
    }

}

Monster * selectMonster(int level) {
    
    int monster;

    switch (level) {
        case 1:
        case 2:
        case 3:
            monster = (rand() % 2) + 1; 
            break;
        case 4:
        case 5:
            monster = (rand() % 2) + 2;
            break;
        case 6:
            monster = 3;
            break;
    }

    switch (monster) {
        // spider
        case SPIDER: 
            return createMonster('X', 2, 1, 1, 1, PATHFINDING_RANDOM);
        // goblin
        case GOBLIN:
            return createMonster('G', 5, 3, 1, 1, PATHFINDING_SEEKING);
        // troll
        case TROLL:
                return createMonster('T', 15, 5, 1, 1, PATHFINDING_RANDOM);
        }
}

Monster * createMonster(char symbol, int health, int attack, int speed, int defence, int pathfinding) {

    Monster * newMonster;
    newMonster = malloc(sizeof(Monster));

    newMonster->symbol = symbol;
    newMonster->health = health;
    newMonster->attack = attack;
    newMonster->speed = speed;
    newMonster->defence = defence;
    newMonster->pathfinding = pathfinding;
    newMonster->alive = MONSTER_ALIVE;

    sprintf(newMonster->string, "%c", symbol);

    return newMonster;
}

int killMonster(Monster * monster) {

    mvprintw(monster->position->y, monster->position->x, ".");
    monster->alive = MONSTER_DEAD;

    return 1;
}


int setStartingPosition(Monster * monster, Room * room) {

    monster->position = malloc(sizeof(Position));

    monster->position->x = (rand() % (room->width - 2)) + room->position.x + 1;
    monster->position->y = (rand() % (room->height - 2)) + room->position.y + 1;

    mvprintw(monster->position->y, monster->position->x, monster->string);
}

int moveMonsters(Level * level) {

    int x;

    for (x = 0; x < level->number_of_monsters; x++) {

        if (level->monsters[x]->alive == MONSTER_DEAD)
            continue;

        mvprintw(level->monsters[x]->position->y, level->monsters[x]->position->x, ".");

        if (level->monsters[x]->pathfinding == PATHFINDING_RANDOM) {
            // random
            pathfindingRandom(level->monsters[x]->position);
        } else if (level->monsters[x]->pathfinding == PATHFINDING_SEEKING) {
            // seeking
            pathfindingSeek(level->monsters[x]->position, level->user->position);
        }
        mvprintw(level->monsters[x]->position->y, level->monsters[x]->position->x, level->monsters[x]->string);
    }
}

int pathfindingRandom(Position * position) {
    
    int random;

    random = rand() % 5;

    switch (random) {
        // step up (mvinch() returns the character at the coord)
        case 0:
            if (mvinch(position->y - 1, position->x) == '.') {
                position->y = position->y - 1;
            }
            break;

        // step down
        case 1:
            if (mvinch(position->y + 1, position->x) == '.') {
                position->y = position->y + 1;
            }
            break;

        // step left
        case 2:
            if (mvinch(position->y, position->x - 1) == '.') {
                position->x = position->x - 1;
            }
            break;

        // step right
        case 3:
            if (mvinch(position->y , position->x + 1) == '.') {
                position->x = position->x + 1;
            }
            break;

        // do nothing
        case 4:
            break;
    }

    return 1;
}

int pathfindingSeek(Position * start, Position * destination) {

    // step left
    if ((abs((start->x - 1) - destination->x) < abs(start->x - destination->x)) && mvinch(start->y, start->x - 1) == '.') {
        start->x = start->x - 1;
    }
    // step right
    else if ((abs((start->x + 1) - destination->x) < abs(start->x - destination->x)) && mvinch(start->y, start->x + 1) == '.') {
        start->x = start->x + 1;
    }
    // step down
    else if ((abs((start->y + 1) - destination->y) < abs(start->y - destination->y)) && mvinch(start->y + 1, start->x) == '.') {
        start->y = start->y + 1;
    }
    // step up
    else if ((abs((start->y - 1) - destination->y) < abs(start->y - destination->y)) && mvinch(start->y - 1, start->x) == '.') {
        start->y = start->y - 1;
    } else {
        // do nothing
    }
   
    return 1;
}

Monster * getMonsterAt(Position * position, Monster ** monsters) {

    int x;
    for (x = 0; x < 6; x++) {
        if ((position->y == monsters[x]->position->y) && (position->x == monsters[x]->position->x)) {
            return monsters[x];
        }
    }

    return NULL;
}

/*

1 Spider
    symbol: X
    levels: 1-3
    health: 2
    attack: 1
    speed: 1
    defence: 1
    pathfinding: 1 (random)

2 Goblin
    symbol: G
    levels: 1-5
    health: 5
    attack: 3
    speed: 1
    defence: 1
    pathfinding: 2 (seeking)

3 Troll
    symbol: T
    levels: 4-6
    health: 15
    attack: 5
    speed: 1
    defence: 1
    pathfinding: 1 (random)
*/;