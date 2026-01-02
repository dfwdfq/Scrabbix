#ifndef BAG_H
#define BAG_H
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

extern char bag[100];
extern char test_bag[3];
extern int current_letter;

extern void init_bag(void);
extern void shuffle(char* array, size_t n);
extern char get_next_letter(void);
extern char get_next_test_letter(void);
#endif
