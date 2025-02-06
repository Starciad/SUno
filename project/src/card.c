#include "ansicolor.h"
#include "card.h"
#include <stdio.h>

const char* color_names[] =
{
    /* [0] */ ANSI_COLOR_RED "Red" ANSI_COLOR_RESET,
    /* [1] */ ANSI_COLOR_BLUE "Blue" ANSI_COLOR_RESET,
    /* [2] */ ANSI_COLOR_GREEN "Green" ANSI_COLOR_RESET,
    /* [3] */ ANSI_COLOR_YELLOW "Yellow" ANSI_COLOR_RESET,
    /* [4] */ "Black"
};

const char* value_names[] =
{ 
    /* [0] */ "Zero",
    /* [1] */ "One",
    /* [2] */ "Two",
    /* [3] */ "Three",
    /* [4] */ "Four",
    /* [5] */ "Five",
    /* [6] */ "Six",
    /* [7] */ "Seven",
    /* [8] */ "Eight",
    /* [9] */ "Nine",
    /* [10] */ "Skip",
    /* [11] */ "Reverse",
    /* [12] */ "Draw Two",
    /* [13] */ "Wild",
    /* [14] */ "Wild Draw Four"
};

const char* type_names[] =
{
    /* [0] */ "Number",
    /* [1] */ "Skip",
    /* [2] */ "Reverse",
    /* [3] */ "Draw Two",
    /* [4] */ "Wild",
    /* [5] */ "Wild Draw Four"
};

// Returns the ANSI color string corresponding to the card color.
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

// Prints a card with ANSI colors.
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

// Checks if a card is playable.
extern bool card_is_playable(const Card* card, const Card* top_card)
{
    /*
     * A card is playable if:
     * 1. It has the same color.
     * 2. It has the same value (for numbered cards).
     * 3. It has the same type (for special action cards).
     * 4. It is a Wild card.
     */
    
    // If the current card is the same color as the top card (or the top card is black), then play it.
    if (card->color == top_card->color || card->color == CARD_COLOR_BLACK)
    {
        return true;
    }

    // Ensure value comparison is only for non-special cards
    if (card->value != CARD_VALUE_NONE && top_card->value != CARD_VALUE_NONE && card->value == top_card->value)
    {
        return true;
    }

    // Ensure type comparison is only for action cards.
    if (card->type != CARD_NUMBER_TYPE && card->type == top_card->type)
    {
        return true;
    }

    // If none of the above conditions are true, then this card cannot be played.
    return false;
}
