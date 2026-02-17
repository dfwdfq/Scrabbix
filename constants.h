#ifndef CONSTANTS_H
#define CONSTANTS_H

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 680

#define MAP_HEIGHT 13
#define MAP_WIDTH  8

#define CELL_SIZE 50
#define BORDER_WIDTH CELL_SIZE*MAP_WIDTH
#define BORDER_HEIGHT CELL_SIZE*MAP_HEIGHT
#define BORDER_OX 20  //top left x position
#define BORDER_OY 20  //top left y position


#define MAX_FOUND_WORDS_SIZE 100
#define FOUND_WORD_LEN       14

//directions
#define LEFT  0
#define RIGHT 1
#define UP    2
#define DOWN  3
#define LEFT_DOWN  4
#define RIGHT_DOWN 5
#define LEFT_UP    6
#define RIGHT_UP   7

#define DEBUG 0 //if 1, use pre-defined test bag
#define PRINT_DEBUG 0

#define TEST 0 //0 - standard game, 1 and more - test bags
#define PRINT_DEBUG_MAP 1

#if PRINT_DEBUG == 1
    #define ANSI_RESET   "\033[0m"
    #define ANSI_RED     "\033[31m"
    #define ANSI_GREEN   "\033[32m"
    #define ANSI_YELLOW  "\033[33m"
    #define ANSI_BLUE    "\033[34m"
    #define ANSI_MAGENTA "\033[35m"
    #define ANSI_CYAN    "\033[36m"
    
    #define DEBUG_PRINT(color, format, ...) printf(color "[DEBUG]" ANSI_RESET " " format, ##__VA_ARGS__)
    #define DEBUG_PRINT_SEPARATOR printf("\n\n\n")

#endif
#endif
