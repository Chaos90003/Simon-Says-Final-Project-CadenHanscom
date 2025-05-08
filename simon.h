#ifndef SIMON_H
#define SIMON_H

typedef struct {
    char *sequence;
    int length;
    int capacity;
} SimonGame;

SimonGame* create_game();
void add_move(SimonGame *game, char move);
void print_moves(SimonGame *game);
char move_picker(int hard_mode);
int check_moves(SimonGame *game, char *input);
void free_game(SimonGame *game);
void score_tracker(int score, int hard_mode);


#endif