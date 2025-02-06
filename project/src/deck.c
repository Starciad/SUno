#include "deck.h"
#include "random.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to initialize the UNO deck.
extern void deck_init(Deck* deck)
{
    uint8_t index = 0;

    // Populate deck with standard cards.

    /* 
     * Creates the same cards in the four existing color groupings:
     *
     * - CARD_COLOR_RED = 0;
     * - CARD_COLOR_BLUE = 1;
     * - CARD_COLOR_GREEN = 2;
     * - CARD_COLOR_YELLOW = 3.
     * 
     */
    for (int i = 0; i < 4; i++)
    {
        // This loop creates the numeric cards (from 1 to 9) for the current color group.
        for (int j = 0; j <= 9; j++)
        {
            deck->cards[index++] = (Card)
            {
                .color = (CardColor)i,
                .type = CARD_NUMBER_TYPE,
                .value = (uint8_t)j
            };

            // This conditional exists to ensure that the number 0 card only appears once per color, while the numbers 1 through 9 appear twice per color in the deck.
            if (j != 0)
            {
                deck->cards[index++] = (Card)
                {
                    .color = (CardColor)i,
                    .type = CARD_NUMBER_TYPE,
                    .value = (uint8_t)j
                };
            }
        }
        
        // This loop is responsible for creating the special cards of the respective color group. He creates the same cards twice.
        for (int j = 0; j < 2; j++)
        {
            deck->cards[index++] = (Card)
            {
                .color = (CardColor)i,
                .type = CARD_SKIP_TYPE,
                .value = CARD_VALUE_NONE
            };
            
            deck->cards[index++] = (Card)
            {
                .color = (CardColor)i,
                .type = CARD_REVERSE_TYPE,
                .value = CARD_VALUE_NONE
            };

            deck->cards[index++] = (Card)
            {
                .color = (CardColor)i,
                .type = CARD_DRAW_TWO_TYPE,
                .value = CARD_VALUE_NONE
            };
        }
    }

    // Creates wild and wild cards draw four cards.
    for (int i = 0; i < 4; i++)
    {
        deck->cards[index++] = (Card)
        {
            .color = CARD_COLOR_BLACK,
            .type = CARD_WILD_TYPE,
            .value = CARD_VALUE_NONE
        };
        
        deck->cards[index++] = (Card)
        {
            .color = CARD_COLOR_BLACK,
            .type = CARD_WILD_DRAW_FOUR_TYPE,
            .value = CARD_VALUE_NONE
        };
    }

    deck->top_index = 0; // Start from the beginning.
}

// Function to shuffle the deck.
extern void deck_shuffle(Deck* deck)
{
    for (int i = DECK_SIZE - 1; i > 0; i--)
    {
        int j = random_int(0, i); // Utility function for random numbers.

        Card temp = deck->cards[i];
        deck->cards[i] = deck->cards[j];
        deck->cards[j] = temp;
    }
}

// Function to draw a card from the deck.
extern Card deck_draw(Deck* deck)
{
    if (deck->top_index >= DECK_SIZE)
    {
        deck->top_index = 0;
        deck_shuffle(deck);
    }
    
    return deck->cards[deck->top_index++];
}
