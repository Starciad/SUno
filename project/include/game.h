#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "deck.h"
#include <stdint.h>

#define MIN_PLAYERS_SHIFTING_COUNT 10
#define MAX_PLAYERS_SHIFTING_COUNT 1000

#define MIN_DECK_SHIFTING_COUNT 10
#define MAX_DECK_SHIFTING_COUNT 1000

#define MAX_PLAYERS 10

typedef enum GameDirection {
    GAME_DIRECTION_NONE = 0,
    GAME_DIRECTION_LEFT = -1,
    GAME_DIRECTION_RIGHT = 1
} GameDirection;

typedef struct Game {
    Deck deck;
    Player players[MAX_PLAYERS];
    uint8_t num_players;
    int8_t current_player_index;
    Card discard_pile;
    GameDirection direction;
} Game;

// Function prototypes.
void game_init(Game* game, uint8_t num_players);
void game_start(Game* game);

#endif // GAME_H
