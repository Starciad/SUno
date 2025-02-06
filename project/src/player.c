#include "player.h"
#include "random.h"
#include <stdio.h>
#include <string.h>

// Initializes a player.
extern void player_init(Player* player, const char* name, bool is_ai)
{
    strncpy(player->name, name, MAX_NAME_LEN - 1);
    
    player->name[MAX_NAME_LEN - 1] = '\0'; // Ensure null-termination.
    player->hand_size = 0;
    player->is_ai = is_ai;
}

// Swaps two players in the array.
static void swap_players(Player* a, Player* b)
{
    Player temp = *a;
    *a = *b;
    *b = temp;
}

// Fisher-Yates Shuffle algorithm using random_int().
void players_shuffle(Player players[], uint8_t num_players)
{
    for (uint8_t i = num_players - 1; i > 0; i--)
    {
        uint8_t j = (uint8_t)random_int(0, i);
        swap_players(&players[i], &players[j]);
    }
}

// Adds a card to the player's hand.
extern void player_add_card(Player* player, Card new_card)
{
    if (player->hand_size < MAX_CARDS)
    {
        player->hand[player->hand_size++] = new_card;
    }
}

// Removes a card from the player's hand.
extern void player_remove_card(Player* player, uint8_t index)
{
    if (index >= 0 && index < player->hand_size)
    {
        for (int i = index; i < player->hand_size - 1; i++)
        {
            player->hand[i] = player->hand[i + 1];
        }

        player->hand_size--;
    }
}

// Prints the player's hand.
extern void player_print_hand(const Player* player)
{
    printf("%s's hand:\n", player->name);
    for (uint8_t i = 0; i < player->hand_size; i++)
    {
        printf("  %d: ", i + 1);
        card_print(&player->hand[i]);
        printf("\n");
    }
}
