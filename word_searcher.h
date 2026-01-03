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


extern char found_words[10][14];
extern int found_words_counter;
extern FWord found_words_data[10];

extern void search(VertexListNode* head);
extern void save_found_word(char* word, int x, int y,short dir);

extern char* get_next_substring(const char* str, int reset,int* start_index);
extern bool does_match(char* word);
extern int str_cmp(const void* str1, const void* str2);

extern void search_rightward(int start_x, int start_y, char* word);
extern void search_leftward(int start_x, int start_y, char* word);
extern void search_upward(int start_x, int start_y, char* word);
extern void search_downward(int start_x,int start_y,char* word);
extern void conv_to_lower(char*word);

#endif
