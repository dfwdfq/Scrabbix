#ifndef MAP_H
#define MAP_H
#include<raylib.h>
#include<stdio.h> //sprintf
#include<string.h>

#define CELL_SIZE 62
#define BORDER_WIDTH CELL_SIZE*8
#define BORDER_HEIGHT CELL_SIZE*14
#define BORDER_OX 20  //top left x position
#define BORDER_OY 20  //top left y position

//get drawable position
#define GPX(x) (4+ BORDER_OX+(x*CELL_SIZE) ) 
#define GPY(y) (4+ BORDER_OY+(y*CELL_SIZE) )

extern char map[14][8];
extern char spawn_line[8];

void init_map(void);

extern void draw_borders(void);
extern void draw_block(int x, int y,char* str);
extern void draw_map(void);
#endif
