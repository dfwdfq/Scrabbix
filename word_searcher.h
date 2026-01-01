#ifndef WORD_SEARCHER_H
#define WORD_SEARCHER_H
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>
#include"vertex_list.h"
#include"map.h"
#include"google_words.h"

extern void search(VertexListNode* head);
extern bool does_match(char* word);
extern int str_cmp(const void* str1, const void* str2);

extern void search_along_ox(int dx,
			    int x,
			    int y,
			    char* word,
			    int* start_x,
			    int* start_y);
extern void search_along_oy(int dy,
			    int x,
			    int y,
			    char* word,
			    int* start_x,
			    int* start_y);


#endif
