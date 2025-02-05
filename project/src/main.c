#include "game.h"
#include <stdio.h>

int main(void)
{
    Game game;
    int num_players;

    puts("\n[ Welcome to SUNO! ]\n");

    do
    {
        printf("Enter the number of players (2-10): ");
        scanf("%d", &num_players);
    } while (num_players < 2 || num_players > 10);

    game_init(&game, num_players);
    game_start(&game);

    return 0;
}
