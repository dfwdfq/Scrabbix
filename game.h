#ifndef GAME_H
#define GAME_H
#include<stddef.h>
#include<stdio.h>
#include<stdbool.h>
#include<math.h>
#include"map.h"
#include"timer.h"
#include"bag.h"
#include"vertex_list.h"
#include"word_searcher.h"
#include"font.h"
#include"gb_palette.h"

#if PRINT_DEBUG_MAP == 1
extern bool dump_map;
#endif


extern VertexListNode* letters_head;
extern int score;
extern bool _pause;
extern bool victory,game_over;
extern int combo;
extern int max_combo;
extern int reupdate_delay;

extern Font font;

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

extern void increase_complexity(void);
extern int get_ghost_y(void);
extern void draw_ghost_block(Font *font);
extern void hard_drop(void);


extern void erase_blocks(void);    //erase_blocks.c
extern void reupdate_blocks(void); //reupdate_blocks.c

extern VertexListNode* clear_list(VertexListNode* lst);

extern void try_move(void);
#endif
