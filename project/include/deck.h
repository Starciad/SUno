#ifndef DECK_H
#define DECK_H

#include "card.h"
#include <stdint.h>

#define DECK_SIZE 108

typedef struct Deck {
    Card cards[DECK_SIZE];
    uint8_t top_index; // Tracks the next card to be drawn.
} Deck;

// Function prototypes.
void deck_init(Deck* deck);
void deck_shuffle(Deck* deck);
Card deck_draw(Deck* deck);

#endif // DECK_H
