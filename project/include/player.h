#ifndef PLAYER_H
#define PLAYER_H

#include "card.h"
#include <stdbool.h>
#include <stdint.h>

#define MAX_CARDS 108 // Max hand size.
#define MAX_NAME_LEN 20

typedef struct Player {
    char name[MAX_NAME_LEN];
    Card hand[MAX_CARDS];
    uint8_t hand_size;
    bool is_ai;
} Player;

// Function prototypes.
void player_init(Player* player, const char* name, bool is_ai);
void players_shuffle(Player players[], uint8_t num_players);
void player_add_card(Player* player, Card new_card);
void player_remove_card(Player* player, uint8_t index);
void player_print_hand(const Player* player);

#endif // PLAYER_H
