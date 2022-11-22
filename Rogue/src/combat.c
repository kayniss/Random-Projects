#include "rogue.h"

int combat(Player * player, Monster * monster, int order) {

    // player attacking 
    if (order == PLAYER_ORDER) {
        monster->health -= player->attack; 
        if (monster->health > 0) {
            player->health -= monster->attack;
            // if (monster->health <= 0) {
            //     player->exp =+ 1;
            // }
        } else {
            killMonster(monster);
            player->exp =+ 1;
        }
    }

    // monster attacking
    else {
        player->health -= monster->attack;
        if (player->health > 0) {
            monster->health -= player->attack;
            if (monster->health <= 0) {
                killMonster(monster);
                player->exp += 1;
            }
        } 
    }

    return 1;
}