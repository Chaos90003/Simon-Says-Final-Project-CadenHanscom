#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simon.h"

#define MAX_INPUT 100


int main() {
    SimonGame *game = create_game();
    char input[MAX_INPUT];
    int round = 1;
    int hard_mode;
    int score = 0;

    do {
        printf("Choose difficulty:\n 1 = Nomral:\n 2 = Hard:\n >");
        if (scanf("%d", &hard_mode) != 1 || (hard_mode != 1 && hard_mode != 2)){
            printf("Invalid input, enter 1 or 2\n");
            while(getchar() != '\n');
            hard_mode = 0;
        } else {
            while (getchar() != '\n');
        }
    } while (hard_mode != 1 && hard_mode != 2);

    hard_mode = (hard_mode == 2);



    printf("The game is about to start\n");
    if (hard_mode == 1){
        printf("You picked Hard!\n");
    } else {
        printf("You picked Normal!\n");
        hard_mode = 0;
    }
//simon says game loop
while (1) {
    char move = move_picker(hard_mode);
    add_move(game, move);
    printf("\nRound %d - Memorize the sequence:\n", round);
    print_moves(game);

    printf("Enter the sequence: ");
    fgets(input, MAX_INPUT, stdin);
    input[strcspn(input, "\n")] = '\0';

    if (!check_moves(game, input)) {
        printf("That's wrong! You lose.\n");
        score_tracker(score, hard_mode);
        break;
    }

    round++;
    score++;
}

free_game(game);
return 0;
}