#include "rogue.h"

int combat(Player * player, Monster * monster, int order) {

    // player attacking 
    if (order == PLAYER_ORDER) {
        monster->health -= player->attack; 
        if (monster->health > 0) {
            player->health -= monster->attack;
        } else {
            killMonster(monster);
        }
    }

    // monster attacking
    else {
        player->health -= monster->attack;
        if (player->health > 0) {
            monster->health -= player->attack;
        } 
    }

    return 1;
}