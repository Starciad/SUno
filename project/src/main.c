#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    srand(time(NULL));

    Game game;
    int num_players;

    printf("\n");
    puts("+-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-+");
    puts("|                                                       |");
    puts("|    _____ __  ______  __________     __  ___   ______  |");
    puts("|   / ___// / / / __ \\/ ____/ __ \\   / / / / | / / __ \\ |");
    puts("|   \\__ \\/ / / / /_/ / __/ / /_/ /  / / / /  |/ / / / / |");
    puts("|  ___/ / /_/ / ____/ /___/ _, _/  / /_/ / /|  / /_/ /  |");
    puts("| /____/\\____/_/   /_____/_/ |_|   \\____/_/ |_/\\____/   |");
    puts("|                                                       |");
    puts("+-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-+");
    puts("\nMIT License (c) 2025 - Davi \"Starciad\" Fernandes.\n");

    do
    {
        printf("> Enter the number of players (2-10): ");
        scanf("%d", &num_players);
    } while (num_players < 2 || num_players > 10);

    game_init(&game, num_players);
    game_start(&game);

    return 0;
}
