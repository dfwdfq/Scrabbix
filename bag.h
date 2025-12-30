#ifndef BAG_H
#define BAG_H
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

extern char bag[100];

extern void init_bag(void);
extern void shuffle(char* array, size_t n);

#endif
