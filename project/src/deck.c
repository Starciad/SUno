#include "Card.h"
#include "deck.h"
#include "random.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to initialize the UNO deck
extern void deck_init(Deck* deck)
{
    uint8_t index = 0;

    // Populate deck with standard cards
    for (int color = CARD_COLOR_RED; color <= CARD_COLOR_YELLOW; color++)
    {
        for (int num = 0; num <= 9; num++)
        {
            deck->cards[index++] = (Card) { color, CARD_NUMBER_TYPE, (uint8_t)num };

            if (num != 0)
            {
                deck->cards[index++] = (Card) { color, CARD_NUMBER_TYPE, (uint8_t)num };
            }
        }
        
        for (int i = 0; i < 2; i++)
        {
            deck->cards[index++] = (Card) { color, CARD_SKIP_TYPE, 0 };
            deck->cards[index++] = (Card) { color, CARD_REVERSE_TYPE, 0 };
            deck->cards[index++] = (Card) { color, CARD_DRAW_TWO_TYPE, 0 };
        }
    }

    // Add wild and wild draw four cards
    for (int i = 0; i < 4; i++)
    {
        deck->cards[index++] = (Card) { CARD_COLOR_BLACK, CARD_WILD_TYPE, 0 };
        deck->cards[index++] = (Card) { CARD_COLOR_BLACK, CARD_WILD_DRAW_FOUR_TYPE, 0 };
    }

    deck->top_index = 0; // Start from the beginning
}

// Function to shuffle the deck
extern void deck_shuffle(Deck* deck)
{
    for (int i = DECK_SIZE - 1; i > 0; i--)
    {
        int j = random_int(0, i); // Utility function for random numbers

        Card temp = deck->cards[i];
        deck->cards[i] = deck->cards[j];
        deck->cards[j] = temp;
    }
}

// Function to draw a card from the deck
extern Card deck_draw(Deck* deck)
{
    if (deck->top_index >= DECK_SIZE)
    {
        printf("Deck is empty! Reshuffling not implemented yet.\n");
        exit(1);
    }
    
    return deck->cards[deck->top_index++];
}
