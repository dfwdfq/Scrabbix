#ifndef WORD_SEARCHER_H
#define WORD_SEARCHER_H
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>
#include<ctype.h>
#include<unistd.h>
#include"vertex_list.h"
#include"map.h"
#include"google_words.h"

typedef struct
{
  int x,y; //start position
  short dir;
} FWord;


extern char found_words[MAX_FOUND_WORDS_SIZE][FOUND_WORD_LEN];
extern int found_words_counter;
extern FWord found_words_data[MAX_FOUND_WORDS_SIZE];

extern void search(VertexListNode* head); //search.c
extern void search_word(char* word,short dir,int x_pos,int y_pos);

extern void save_found_word(char* word, int x, int y,short dir);
extern bool does_match(char* word);

//horizontal
extern void search_rightward(int start_x, int start_y, char* word);
extern void search_leftward(int start_x, int start_y, char* word);

//vertical
extern void search_upward(int start_x, int start_y, char* word);
extern void search_downward(int start_x,int start_y,char* word);

//L-shaped words
extern void search_L_left_down(int start_x, int start_y, char* word);
extern void search_L_right_down(int start_x, int start_y, char* word);
extern void search_L_left_up(int start_x,int start_y, char* word);
extern void search_L_right_up(int start_x,int start_y, char* word);

//some util functions
extern void conv_to_lower(char*word);
extern void reverse_string(char* in, char* out);
extern char* get_next_substring(const char* str, int reset,int* start_index); //get_next_substring.c

#if USE_BINARY_SEARCH == 1
//define this function if you are going to use binary search
int str_cmp(const void* a, const void* b);
#endif

#endif
