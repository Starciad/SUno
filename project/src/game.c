#include "game.h"
#include "ai.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Predefined names for bots
const char* bot_names[] = {
    "James", "Mary", "John", "Jennifer", "Robert", "Linda", 
    "Michael", "Elizabeth", "David", "Susan", "William", "Jessica", 
    "Joseph", "Sarah", "Charles", "Karen", "Thomas", "Nancy", 
    "Christopher", "Betty"
};

// Asks the player to call UNO
void check_uno_call(Game* game, Player* player)
{
    if (player->hand_size == 1)
    {
        if (player->is_ai)
        {
            printf("🤖 %s calls UNO!\n", player->name);
        }
        else
        {
            char response[4];
            printf("⚠️  You have one card left! Type 'UNO' to call it: ");
            scanf("%3s", response);

            if (strcmp(response, "UNO") != 0)
            {
                printf("🚨 You forgot to call UNO! Drawing 2 penalty cards.\n");
                player_add_card(player, deck_draw(&game->game_deck));
                player_add_card(player, deck_draw(&game->game_deck));
            }
        }
    }
}

// Applies the effects of special cards
void apply_card_effect(Game* game, const Card *played_card) {
    switch (played_card->type)
    {
        case CARD_SKIP_TYPE:
            printf("⏩ %s played Skip! Next player is skipped!\n", game->players[game->current_player].name);
            game_next_turn(game);
            break;

        case CARD_REVERSE_TYPE:
            printf("🔄 %s played Reverse! Changing direction!\n", game->players[game->current_player].name);
            game->game_direction *= -1;
            break;

        case CARD_DRAW_TWO_TYPE:
            printf("🚨 %s played Draw Two! Next player draws 2 cards!\n", game->players[game->current_player].name);
            game_next_turn(game);
            player_add_card(&game->players[game->current_player], deck_draw(&game->game_deck));
            player_add_card(&game->players[game->current_player], deck_draw(&game->game_deck));
            break;

        case CARD_WILD_TYPE:
            printf("🎨 %s played Wild! Choosing a new color...\n", game->players[game->current_player].name);
            if (game->players[game->current_player].is_ai)
            {
                game->discard_pile.color = rand() % 4; // AI chooses a random color
            }
            else
            {
                int chosen_color;
                printf("Choose a color (0: Red, 1: Blue, 2: Green, 3: Yellow): ");
                scanf("%d", &chosen_color);
                game->discard_pile.color = (CardColor)chosen_color;
            }
            break;

        case CARD_WILD_DRAW_FOUR_TYPE:
            printf("🔥 %s played Wild Draw Four! Choosing a new color, next player draws 4 cards!\n", game->players[game->current_player].name);

            if (game->players[game->current_player].is_ai)
            {
                game->discard_pile.color = rand() % 4;
            }
            else
            {
                int chosen_color;
                printf("Choose a color (0: Red, 1: Blue, 2: Green, 3: Yellow): ");
                scanf("%d", &chosen_color);
                game->discard_pile.color = (CardColor)chosen_color;
            }

            game_next_turn(game);

            for (int i = 0; i < 4; i++)
            {
                player_add_card(&game->players[game->current_player], deck_draw(&game->game_deck));
            }
            break;

        default:
            break;
    }
}

// Switches to the next player taking into account the direction
extern void game_next_turn(Game* game) {
    game->current_player += game->game_direction;

    // If the next player exceeds the number of players, we go back to the beginning
    if (game->current_player >= game->num_players)
    {
        game->current_player = 0;
    }
    else if (game->current_player < 0)
    {
        game->current_player = game->num_players - 1;
    }
}

// Print the current game state
extern void game_print_state(const Game* game) {
    // Imprime o jogador atual
    printf("\n- Current Player: %s\n", game->players[game->current_player].name);
    printf("- Current card: ");
    card_print(&game->discard_pile);
    puts("\n");

    // Prints the current player's hand of cards
    printf("Your hand:\n");
    for (int i = 0; i < game->players[game->current_player].hand_size; i++) {
        printf("%d. ", i + 1);
        card_print(&game->players[game->current_player].hand[i]);
        printf("\n");
    }
}

// Initializes the game, dealing the cards and setting up the players
extern void game_init(Game* game, uint8_t num_players) {
    game->num_players = num_players;
    game->current_player = 0;
    game->game_direction = 1; // 1 for clockwise, -1 for counterclockwise

    deck_init(&game->game_deck); // Create the deck of cards
    deck_shuffle(&game->game_deck); // Shuffle the deck

    // Allows the player to choose their name
    char player_name[50];
    printf("Enter your name: ");
    scanf("%49s", player_name); // Limit input to prevent overflow
    player_init(&game->players[0], player_name, false); // The first player is the human

    // Deals cards to the player
    for (uint8_t j = 0; j < 7; j++)
    {
        player_add_card(&game->players[0], deck_draw(&game->game_deck));
    }

    // Assigns names and distributes cards to bots
    uint8_t bot_index = 1;
    for (uint8_t i = 1; i < num_players; i++)
    {
        player_init(&game->players[i], bot_names[bot_index - 1], true); // Name the bot

        for (uint8_t j = 0; j < 7; j++)
        {
            player_add_card(&game->players[i], deck_draw(&game->game_deck)); // Deals cards to bots
        }

        bot_index++;
    }

    // Put a card in the discard pile
    game->discard_pile = deck_draw(&game->game_deck);
    
    // Ensures the starting card is playable
    while (!card_is_playable(&game->discard_pile, &game->discard_pile))
    {
        game->discard_pile = deck_draw(&game->game_deck);
    }

    printf("The game has started! Good luck!\n");
}

// Updates the game loop to include UNO call
extern void game_start(Game* game)
{
    while (true)
    {
        puts("\n=============================\n");

        game_print_state(game);
        Player* player = &game->players[game->current_player];

        int selected_card = -1;

        if (player->is_ai)
        {
            selected_card = ai_select_card(player, &game->discard_pile);
            if (selected_card == -1)
            {
                printf("🤖 %s draws a card.\n", player->name);
                player_add_card(player, deck_draw(&game->game_deck));
            }
            else
            {
                printf("🤖 %s plays ", player->name);
                card_print(&player->hand[selected_card]);
                printf("\n");

                game->discard_pile = player->hand[selected_card];
                apply_card_effect(game, &game->discard_pile);
                player_remove_card(player, selected_card);
                check_uno_call(game, player);
            }
        }
        else
        {
            printf("Your turn! Select a card (1-%d) or enter 0 to draw: ", player->hand_size);
            scanf("%d", &selected_card);
            selected_card--;

            if (selected_card < 0 || selected_card >= player->hand_size ||  !card_is_playable(&player->hand[selected_card], &game->discard_pile))
            {
                printf("Invalid move! Drawing a card.\n");
                player_add_card(player, deck_draw(&game->game_deck));
            }
            else
            {
                game->discard_pile = player->hand[selected_card];
                apply_card_effect(game, &game->discard_pile);
                player_remove_card(player, selected_card);
                check_uno_call(game, player);
            }
        }

        if (player->hand_size == 0)
        {
            printf("🎉 %s WINS! 🎉\n", player->name);
            break;
        }

        game_next_turn(game);
    }
}
