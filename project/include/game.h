#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "deck.h"
#include <stdint.h>

#define MAX_PLAYERS 10

typedef struct Game {
    Deck deck;
    Player players[MAX_PLAYERS];
    uint8_t num_players;
    uint8_t current_player_index;
    Card discard_pile;
    int8_t direction;
} Game;

// Function prototypes
void game_init(Game* game, uint8_t num_players);
void game_start(Game* game);

#endif // GAME_H
