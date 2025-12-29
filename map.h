#ifndef MAP_H
#define MAP_H
#include<raylib.h>

#define CELL_SIZE 64
#define BORDER_WIDTH CELL_SIZE*8
#define BORDER_HEIGHT CELL_SIZE*14
#define BORDER_OX 20  //top left x position
#define BORDER_OY 20  //top left y position

extern char map[14][8];

extern void draw_borders(void);
#endif
