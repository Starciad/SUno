#ifndef AI_H
#define AI_H

#include "player.h"
#include "card.h"

// Function prototypes.
bool ai_try_select_card(const Player* player, const Card* top_card, Card* selected_card);

#endif // AI_H
