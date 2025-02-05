#include "ai.h"
#include "game.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Predefined names for bots
const char* bot_names[] =
{
    "James", "Mary", "John", "Jennifer", "Robert", "Linda", 
    "Michael", "Elizabeth", "David", "Susan", "William", "Jessica", 
    "Joseph", "Sarah", "Charles", "Karen", "Thomas", "Nancy", 
    "Christopher", "Betty"
};

// Returns the index of the next player considering the game direction
uint8_t game_get_next_player_index(const Game* game)
{
    int8_t next_index = game->current_player_index + game->direction;

    // Handle wrap-around logic
    if (next_index >= game->num_players)
    {
        return 0; // Wrap back to the first player
    }
    else if (next_index < 0)
    {
        return game->num_players - 1; // Wrap back to the last player
    }

    return (uint8_t)next_index;
}

// Switches to the next player using game_get_next_player_index
void game_next_turn(Game* game)
{
    game->current_player_index = game_get_next_player_index(game);
}

// Asks the player to call UNO
void check_uno_call(Game* game, Player* player)
{
    if (player->hand_size != 1)
    {
        return;
    }

    if (player->is_ai)
    {
        printf("🤖 %s calls UNO!\n", player->name);
        return;;
    }

    char response[4];
    printf("⚠️ You have one card left! Type 'UNO' to call it: ");
    scanf("%3s", response);

    if (strcmp(response, "UNO") != 0)
    {
        printf("🚨 You forgot to call UNO! Drawing 2 penalty cards.\n");
        player_add_card(player, deck_draw(&game->deck));
        player_add_card(player, deck_draw(&game->deck));
    }
}

// Applies the effects of special cards
void apply_card_effect(Game* game, const Card* played_card)
{
    // Select the next player index based on the current context.
    uint8_t next_player_index = game_get_next_player_index(game);

    // ================================ //

    switch (played_card->type)
    {
        case CARD_SKIP_TYPE:
            puts("Next player is skipped!");
            game_next_turn(game);
            break;

        case CARD_REVERSE_TYPE:
            puts("Changing direction!");
            game->direction *= -1;
            break;

        case CARD_DRAW_TWO_TYPE:
            puts("Next player draws 2 cards!");
            game_next_turn(game);

            for (uint8_t i = 0; i < 2; i++)
            {
                player_add_card(&game->players[next_player_index], deck_draw(&game->deck));
            }
            break;

        case CARD_WILD_TYPE:
            puts("Choosing a new color...");

            if (game->players[game->current_player_index].is_ai)
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
            puts("Choosing a new color, next player draws 4 cards!");

            if (game->players[game->current_player_index].is_ai)
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
                player_add_card(&game->players[next_player_index], deck_draw(&game->deck));
            }
            break;

        default:
            break;
    }
}

// =============================================================================== //
// Prints the player list.
void game_print_players(const Game* game)
{
    puts("\n\n===== Player List =====\n");

    for (uint8_t i = 0; i < game->num_players; i++)
    {
        const Player* player = &game->players[i];

        // Indicate the current player
        if (i == game->current_player_index)
        {
            printf(">  ");
        }
        else
        {
            printf("   ");
        }

        printf("[%d] %s - %d card(s)\n", i + 1, player->name, player->hand_size);
    }

    printf("\n=======================");
}


// Print the current game state
void game_print_state(const Game* game)
{
    // Print the current player
    puts("\n");
    printf("- Current Player: %s\n", game->players[game->current_player_index].name);
    printf("- Current Card on the Table: ");
    card_print(&game->discard_pile);
    puts("\n");
}

// Print the main user's HUD
void game_print_hud_state(const Game* game)
{
    // Prints the user hand of cards
    printf("Your hand:\n");
    for (int i = 0; i < game->players[game->current_player_index].hand_size; i++) {
        printf("%d. ", i + 1);
        card_print(&game->players[game->current_player_index].hand[i]);
        printf("\n");
    }

    printf("\n");
}

// =============================================================================== //
// Method responsible for handling player turn protocols
void game_execute_user_turn(Game* game, Player* player)
{
    int selected_card = 0;

    game_print_hud_state(game);

    try_again_action_label:
    printf("Your turn! Select a card (1-%d) or enter 0 to draw: ", player->hand_size);
    scanf("%d", &selected_card);
    
    if (selected_card == 0)
    {
        puts("You drawn a card...");
        Card drawn_card = deck_draw(&game->deck);
        player_add_card(player, drawn_card);
        return;
    }

    selected_card--;

    if (selected_card < 0 || selected_card >= player->hand_size || !card_is_playable(&player->hand[selected_card], &game->discard_pile))
    {
        puts("Invalid move! Try again.");
        goto try_again_action_label;
    }

    game->discard_pile = player->hand[selected_card];
    apply_card_effect(game, &game->discard_pile);
    player_remove_card(player, selected_card);
    check_uno_call(game, player);
}

// Method responsible for handling AI shift routines
void game_execute_ai_turn(Game* game, Player* player)
{
    Card selected_card;

    if (!ai_try_select_card(player, &game->discard_pile, &selected_card))
    {
        printf("🤖 %s draws a card.\n", player->name);
        Card drawn_card = deck_draw(&game->deck);
        player_add_card(player, drawn_card);
        return;
    }

    // Find the index of the selected card in your hand
    int selected_index = -1;
    for (int i = 0; i < player->hand_size; i++)
    {
        if (player->hand[i].color == selected_card.color &&
            player->hand[i].value == selected_card.value)
        {
            selected_index = i;
            break;
        }
    }

    if (selected_index == -1)
    {
        fprintf(stderr, "Error: AI selected a card that does not exist in hand.\n");
        return;
    }

    printf("🤖 %s plays ", player->name);
    card_print(&selected_card);
    printf("\n");

    game->discard_pile = selected_card;
    apply_card_effect(game, &game->discard_pile);
    player_remove_card(player, selected_index);
    check_uno_call(game, player);
}

// =============================================================================== //

// Initializes the game, dealing the cards and setting up the players
extern void game_init(Game* game, uint8_t num_players)
{
    game->num_players = num_players;
    game->current_player_index = 0;
    game->direction = 1; // 1 for clockwise, -1 for counterclockwise

    deck_init(&game->deck); // Create the deck of cards

    // Shuffle the deck
    for (uint8_t i = 0; i < DECK_SHIFTING_COUNT; i++)
    {
        deck_shuffle(&game->deck); 
    }

    // Allows the player to choose their name
    char player_name[50];
    printf("Enter your name: ");
    scanf("%49s", player_name); // Limit input to prevent overflow
    player_init(&game->players[0], player_name, false); // The first player is the human

    // Deals cards to the player
    for (uint8_t j = 0; j < 7; j++)
    {
        player_add_card(&game->players[0], deck_draw(&game->deck));
    }

    // Assigns names and distributes cards to bots
    uint8_t bot_index = 1;
    for (uint8_t i = 1; i < num_players; i++)
    {
        player_init(&game->players[i], bot_names[bot_index - 1], true); // Name the bot

        for (uint8_t j = 0; j < 7; j++)
        {
            player_add_card(&game->players[i], deck_draw(&game->deck)); // Deals cards to bots
        }

        bot_index++;
    }

    // Put a card in the discard pile
    game->discard_pile = deck_draw(&game->deck);
    
    // Ensures the starting card is playable
    while (!card_is_playable(&game->discard_pile, &game->discard_pile))
    {
        game->discard_pile = deck_draw(&game->deck);
    }

    puts("\n=============================\n");
    puts("Your competitors are:\n");
    for (uint8_t i = 0; i < num_players; i++)
    {
        printf("%i. %s\n", i + 1, game->players[i].name);
        usleep(500 * 1000);
    }
    printf("\n");
    puts("The game has started! Good luck!");
    sleep(3);
}

// Updates the game loop to include UNO call
extern void game_start(Game* game)
{
    while (true)
    {
        printf("\n_______________________");

        game_print_players(game);
        game_print_state(game);

        Player* player = &game->players[game->current_player_index];

        if (player->is_ai)
        {
            game_execute_ai_turn(game, player);
        }
        else
        {
            game_execute_user_turn(game, player);
        }

        if (player->hand_size == 0)
        {
            printf("🎉 %s WINS! 🎉\n", player->name);
            break;
        }

        sleep(2);
        game_next_turn(game);
    }
}
