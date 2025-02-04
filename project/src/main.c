#include "game.h"
#include <stdio.h>

int main(void)
{
    Game game;
    int num_players;

    puts("🎮 Welcome to UNO!");
    printf("Enter the number of players (2-10): ");
    scanf("%d", &num_players);
    
    if (num_players < 2 || num_players > 10)
    {
        puts("Invalid number of players. Defaulting to 3 players.");
        num_players = 3;
    }

    game_init(&game, num_players);
    game_start(&game);

    return 0;
}
