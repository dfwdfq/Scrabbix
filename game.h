#ifndef GAME_H
#define GAME_H
#include<stddef.h>
#include<stdio.h>
#include"map.h"
#include"timer.h"
#include"bag.h"

extern void handle_keys(void);

extern void init_game(void);
extern void run_game(void);
extern void draw_game(void);


#endif
