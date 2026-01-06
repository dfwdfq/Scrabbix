#ifndef GAME_H
#define GAME_H
#include<stddef.h>
#include<stdio.h>
#include"map.h"
#include"timer.h"
#include"bag.h"
#include"vertex_list.h"
#include"word_searcher.h"

extern VertexListNode* letters_head;
extern int score;

extern char found_words_labels[MAX_FOUND_WORDS_SIZE][FOUND_WORD_LEN];
extern int found_words_labels_counter;
extern Color fading_w_color; //fading word color

extern void handle_keys(void);

extern void init_game(void);  //init_game.c
extern void free_game(void);

extern void run_game(void);
extern void draw_game(void);
extern void draw_labels(void);
extern void draw_found_words(void);

extern void erase_blocks(void);    //erase_blocks.c
extern void reupdate_blocks(void);
#endif
