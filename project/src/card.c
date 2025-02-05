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
    "Zero",
    "One",
    "Two",
    "Three",
    "Four",
    "Five",
    "Six",
    "Seven",
    "Eight",
    "Nine",
    "Skip",
    "Reverse",
    "Draw Two",
    "Wild",
    "Wild Draw Four"
};

const char* type_names[] =
{
    "Number",
    "Skip",
    "Reverse",
    "Draw Two",
    "Wild",
    "Wild Draw Four"
};

// Prints a card
extern void card_print(const Card* card)
{
    switch (card->type)
    {
        case CARD_NUMBER_TYPE:
            printf("[%s (%s)]", value_names[card->value], color_names[card->color]);
            break;

        case CARD_SKIP_TYPE:
        case CARD_REVERSE_TYPE:
        case CARD_DRAW_TWO_TYPE:
            printf("[%s (%s)]", type_names[card->type], color_names[card->color]);
            break;

        case CARD_WILD_TYPE:
        case CARD_WILD_DRAW_FOUR_TYPE:
        printf("[%s]", type_names[card->type]);
            break;

        default:
            break;
    }
}

// Checks if a card is playable
extern bool card_is_playable(const Card* card, const Card* top_card)
{
    return (card->color == top_card->color || card->value == top_card->value || card->color == CARD_COLOR_BLACK);
}
