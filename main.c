#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simon.h"

#define MAX_INPUT 100


int main() {
    SimonGame *game = create_game();
    char input[MAX_INPUT];
    int round = 1;



printf("The game is about to start");

while (1) {
    char move = move_picker();
    add_move(game, move);
    printf("\nRound %d - Memorize the sequence:\n", round);
    print_moves(game);

    printf("Enter the sequence: ");
    fgets(input, MAX_INPUT, stdin);
    input[strcspn(input, "\n")] = '\0';

    if (!check_moves(game, input)) {
        printf("That's wrong! You lose.\n");
        break;
    }

    round++;
}

free_game(game);
return 0;
}