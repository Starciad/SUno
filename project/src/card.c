#include "ansicolor.h"
#include "card.h"
#include <stdio.h>

const char* color_names[] =
{
    ANSI_COLOR_RED "Red" ANSI_COLOR_RESET,
    ANSI_COLOR_BLUE "Blue" ANSI_COLOR_RESET,
    ANSI_COLOR_GREEN "Green" ANSI_COLOR_RESET,
    ANSI_COLOR_YELLOW "Yellow" ANSI_COLOR_RESET,
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

// Returns the ANSI color string corresponding to the card color
const char* get_ansi_color(CardColor color)
{
    switch (color)
    {
        case CARD_COLOR_RED: return ANSI_COLOR_RED;
        case CARD_COLOR_BLUE: return ANSI_COLOR_BLUE;
        case CARD_COLOR_GREEN: return ANSI_COLOR_GREEN;
        case CARD_COLOR_YELLOW: return ANSI_COLOR_YELLOW;
        default: return ANSI_COLOR_RESET;
    }
}

// Prints a card with ANSI colors
extern void card_print(const Card* card)
{
    const char* color_code = get_ansi_color(card->color);

    switch (card->type)
    {
        case CARD_NUMBER_TYPE:
            printf("[%s%s%s (%s%s%s)]", color_code, value_names[card->value], ANSI_COLOR_RESET, color_code, color_names[card->color], ANSI_COLOR_RESET);
            break;

        case CARD_SKIP_TYPE:
        case CARD_REVERSE_TYPE:
        case CARD_DRAW_TWO_TYPE:
            printf("[%s%s%s (%s%s%s)]", color_code, type_names[card->type], ANSI_COLOR_RESET, color_code, color_names[card->color], ANSI_COLOR_RESET);
            break;

        case CARD_WILD_TYPE:
        case CARD_WILD_DRAW_FOUR_TYPE:
            if (card->color == CARD_COLOR_BLACK)
            {
                printf("[%s%s%s]", ANSI_COLOR_MAGENTA, type_names[card->type], ANSI_COLOR_RESET);
            }
            else
            {
                printf("[%s%s%s (%s%s%s)]", color_code, type_names[card->type], ANSI_COLOR_RESET, color_code, color_names[card->color], ANSI_COLOR_RESET);
            }
            break;

        default:
            break;
    }
}

// Checks if a card is playable
extern bool card_is_playable(const Card* card, const Card* top_card)
{
    // A card is playable if:
    // 1. It has the same color as the top card.
    // 2. It has the same value as the top card (only if both have a defined value).
    // 3. It is a wild card (black cards are always playable).
    return (card->color == top_card->color) ||
           (card->value != CARD_VALUE_NONE && top_card->value != CARD_VALUE_NONE && card->value == top_card->value) ||
           (card->color == CARD_COLOR_BLACK);
}
