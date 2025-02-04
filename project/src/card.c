#include "card.h"
#include <stdio.h>

const char* color_names[] =
{
    "Red",
    "Blue",
    "Green",
    "Yellow",
    "Black"
};

const char* value_names[] =
{ 
    "0",
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9", 
    "Skip",
    "Reverse",
    "Draw Two",
    "Wild",
    "Wild Draw Four"
};

// Prints a card
extern void card_print(const Card* card)
{
    printf("[%s %s]", color_names[card->color], value_names[card->value]);
}

// Checks if a card is playable
extern bool card_is_playable(const Card* card, const Card* top_card)
{
    return (card->color == top_card->color || card->value == top_card->value || card->color == CARD_COLOR_BLACK);
}
