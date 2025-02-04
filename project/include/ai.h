#ifndef AI_H
#define AI_H

#include "player.h"
#include "card.h"

int8_t ai_select_card(const Player* player, const Card* top_card);

#endif // AI_H
