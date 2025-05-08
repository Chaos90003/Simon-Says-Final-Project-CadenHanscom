#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "simon.h"
#include <unistd.h>

//creates the game, will be called in main
SimonGame* create_game(){
    SimonGame *game = (SimonGame *)malloc(sizeof(SimonGame));
    game->length = 0;
    game->capacity = 4; //for each color - remember to consider making a hard difficulty later
    game->sequence = (char*)malloc(game->capacity * sizeof(char));
    srand(time(NULL)); //ensures originality
    return game;

}
//checks for space/creates more space and adds the move
void add_move(SimonGame *game, char move){
    if (game->length == game->capacity){
        game->capacity *= 2;
        char *temp = realloc(game->sequence, game->capacity * sizeof(char));
        if (temp == NULL){
            printf("realloc failed");
        }
        game->sequence = temp;
    }

    *(game->sequence + game->length) = move;
    game->length++;

}
//prints the sequence of moves
void print_moves(SimonGame *game) {
    for (char *ptr = game->sequence; ptr < game->sequence + game-> length; ptr++){
        printf("%c ", *ptr);
        fflush(stdout);
        sleep(1);
    }
    
    printf("\n");

    sleep(0.5);
    system("clear"); //clears simons sequence from terminal
}

//uses switch and rand() to determine the next move, 
char move_picker(int hard_mode){
    int range = hard_mode ? 6 : 4; //looks for if hard mode or not and determines which range to use
    switch (rand() % range){
        case 0: 
            return 'R';
        case 1:
            return 'G';
        case 2:
            return 'B';
        case 3:
            return 'Y';
        case 4:
            return 'O'; //hard mode only
        case 5:
            return 'P'; // hard mode only
    }
}

//compares to see if matches
int check_moves(SimonGame *game, char *input){
   if (memcmp(game->sequence, input, game->length) == 0){
        return 1; //match
   }
   return 0; //don't match
}

//writes scores to scores.txt
void score_tracker(int score, int hard_mode){
    FILE *file = fopen("scores.txt", "a");


    fprintf(file, "\nScore: %d\nDifficulty: %s\n", score, (hard_mode == 2) ? "Hard": "Normal");
    fclose(file);
}



void free_game(SimonGame *game){
    free(game->sequence);
    free(game);
}
