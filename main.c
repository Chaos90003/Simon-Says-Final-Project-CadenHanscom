
/*
Name: Caden Hanscom
Date: 5/8/2025
*/


/*
This file manages the game flow and 
incoroporates the functions defined in simon.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "simon.h"

#define MAX_INPUT 100


//controls the game flow, has all the prints, and takes the user input and determines
//if it matches or not either ending the game, or moving to the next round
int main() {
    SimonGame *game = create_game();
    char input[MAX_INPUT];
    int round = 1;
    int hard_mode;
    int score = 0;

    //provid a warning when something other than 1 or 2 is inputted
    do {
        printf("Choose difficulty:\n 1 = Nomral:\n 2 = Hard:\n >");
        if (scanf("%d", &hard_mode) != 1 || (hard_mode != 1 && hard_mode != 2)){
            printf("Invalid input, enter 1 or 2\n");
            while(getchar() != '\n'); //prevents the input being incorrectly read
            hard_mode = 0;
        } else {
            while (getchar() != '\n'); //prevents the input being incorrectly read
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

    //allows for lower case input
    for (int i = 0; input[i] != '\0'; i++){
        input[i] = toupper(input[i]);
    }

    //checks if input matches simon and takes the players score if game ends
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