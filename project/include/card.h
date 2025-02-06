#ifndef CARD_H
#define CARD_H

#include <stdbool.h>

typedef enum CardColor {
    CARD_COLOR_RED = 0,
    CARD_COLOR_BLUE = 1,
    CARD_COLOR_GREEN = 2,
    CARD_COLOR_YELLOW = 3,
    CARD_COLOR_BLACK = 4 // Wild cards.
} CardColor;

typedef enum CardValue {
    CARD_VALUE_NONE = -1,
    CARD_VALUE_0 = 0,
    CARD_VALUE_1 = 1,
    CARD_VALUE_2 = 2,
    CARD_VALUE_3 = 3,
    CARD_VALUE_4 = 4,
    CARD_VALUE_5 = 5,
    CARD_VALUE_6 = 6,
    CARD_VALUE_7 = 7,
    CARD_VALUE_8 = 8,
    CARD_VALUE_9 = 9,
    CARD_VALUE_SKIP = 10,
    CARD_VALUE_REVERSE = 11,
    CARD_VALUE_DRAW_TWO = 12,
    CARD_VALUE_WILD = 13,
    CARD_VALUE_WILD_DRAW_FOUR = 14
} CardValue;

typedef enum CardType {
    CARD_NUMBER_TYPE = 0,
    CARD_SKIP_TYPE = 1,
    CARD_REVERSE_TYPE = 2,
    CARD_DRAW_TWO_TYPE = 3,
    CARD_WILD_TYPE = 4,
    CARD_WILD_DRAW_FOUR_TYPE = 5
} CardType;

typedef struct Card {
    CardColor color;
    CardType type;
    CardValue value;
} Card;

// Function prototypes.
void card_print(const Card* card);
bool card_is_playable(const Card* card, const Card* top_card);

#endif // CARD_H
