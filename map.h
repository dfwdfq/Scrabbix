#ifndef MAP_H
#define MAP_H
#include<raylib.h>
#include<stdio.h> //sprintf
#include<string.h>
#include"constants.h"
#include"font.h"
#include"gb_palette.h"
#include"timer.h"
#include"word_searcher.h"

//get drawable position
#define GPX(x) (4+ BORDER_OX+(x*CELL_SIZE) ) 
#define GPY(y) (4+ BORDER_OY+(y*CELL_SIZE) )

extern char map[MAP_HEIGHT][MAP_WIDTH];
extern int block_x, block_y;


void init_map(void);

extern void draw_map(Font* font);
extern void update_map(void);

extern void generate_random_start_pos(void);
#endif
