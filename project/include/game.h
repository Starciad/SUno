#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "deck.h"
#include <stdint.h>

#define MAX_PLAYERS 4

typedef struct Game {
    Deck game_deck;
    Player players[MAX_PLAYERS];
    uint8_t num_players;
    uint8_t current_player;
    Card discard_pile;
    int8_t game_direction;
} Game;

// Function prototypes
void game_init(Game* game, uint8_t num_players);
void game_start(Game* game);
void game_next_turn(Game* game);
void game_print_state(const Game* game);

#endif // GAME_H
