#include "ai.h"
#include <stdbool.h>

// AI selects the best playable card.
extern bool ai_try_select_card(const Player* player, const Card* top_card, Card* selected_card)
{
    uint8_t best_index = 255;

    // Prioritize action cards.
    for (uint8_t i = 0; i < player->hand_size; i++)
    {
        if (card_is_playable(&player->hand[i], top_card))
        {
            // Immediately play an action card.
            if (player->hand[i].value == CARD_VALUE_SKIP ||
                player->hand[i].value == CARD_VALUE_REVERSE ||
                player->hand[i].value == CARD_VALUE_DRAW_TWO)
            {
                *selected_card = player->hand[i];
                return true;
            }

            // Store first valid card.
            if (best_index == 255)
            {
                best_index = i;
            }
        }
    }

    // Play regular number cards first, save Wild cards.
    if (best_index != 255)
    {
        *selected_card = player->hand[best_index];
        return true;
    }

    // Last resort: play Wild cards.
    for (uint8_t i = 0; i < player->hand_size; i++)
    {
        if (player->hand[i].value == CARD_VALUE_WILD || player->hand[i].value == CARD_VALUE_WILD_DRAW_FOUR)
        {
            *selected_card = player->hand[i];
            return true;
        }
    }

    return false;
}
