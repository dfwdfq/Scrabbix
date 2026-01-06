#ifndef CONSTANTS_H
#define CONSTANTS_H

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 930

#define CELL_SIZE 62
#define BORDER_WIDTH CELL_SIZE*8
#define BORDER_HEIGHT CELL_SIZE*14
#define BORDER_OX 20  //top left x position
#define BORDER_OY 20  //top left y position

#define MAP_HEIGHT 14
#define MAP_WIDTH  8

#define LEFT  0
#define RIGHT 1
#define UP    2
#define DOWN  3
#define LEFT_DOWN  4
#define RIGHT_DOWN 5
#define LEFT_UP    6
#define RIGHT_UP   7

#define DEBUG 1 //if 1, use pre-defined test bag
#define TEST  12
#define PRINT_DEBUG 1

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
