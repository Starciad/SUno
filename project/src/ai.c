#include "ai.h"
#include <stdbool.h>

// AI selects the best playable card
extern int8_t ai_select_card(const Player* player, const Card* top_card)
{
    int8_t best_index = -1;

    // Prioritize action cards
    for (uint8_t i = 0; i < player->hand_size; i++)
    {
        if (card_is_playable(&player->hand[i], top_card))
        {
            if (player->hand[i].value == CARD_VALUE_SKIP ||
                player->hand[i].value == CARD_VALUE_REVERSE ||
                player->hand[i].value == CARD_VALUE_DRAW_TWO)
            {
                return i;  // Immediately play an action card
            }

            if (best_index == -1)
            {
                best_index = i; // Store first valid card
            }
        }
    }

    // Play regular number cards first, save Wild cards
    if (best_index != -1)
    {
        return best_index;
    }

    // Last resort: play Wild cards
    for (uint8_t i = 0; i < player->hand_size; i++)
    {
        if (player->hand[i].value == CARD_VALUE_WILD || player->hand[i].value == CARD_VALUE_WILD_DRAW_FOUR)
        {
            return i;
        }
    }

    return -1; // No valid card, must draw
}
