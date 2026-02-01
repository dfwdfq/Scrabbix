#ifndef GAME_H
#define GAME_H
#include<stddef.h>
#include<stdio.h>
#include<stdbool.h>
#include"map.h"
#include"timer.h"
#include"bag.h"
#include"vertex_list.h"
#include"word_searcher.h"
#include"font.h"
#include"gb_palette.h"

extern VertexListNode* letters_head;
extern int score;
extern bool _pause;
extern bool victory,game_over;

extern Font font32,font48,font56;

extern char found_words_labels[MAX_FOUND_WORDS_SIZE][FOUND_WORD_LEN];
extern int found_words_labels_counter;
extern Color fading_w_color; //fading word color

extern void handle_keys(void);

extern void init_game(void);  //init_game.c
extern void free_game(void);

//init_game is too big, so for fonts I use particular proc
extern void load_fonts(void);
extern void unload_fonts(void);

extern void run_game(void);
extern void draw_game(void);
extern void draw_labels(void);
extern void draw_found_words(void);

extern void erase_blocks(void);    //erase_blocks.c
extern void reupdate_blocks(void); //reupdate_blocks.c

// Helper function to handle movement logic (avoids duplication)
extern void try_move(void);
#endif
