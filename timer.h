/*
This is bad(!), yet primitive and working
implementation of ticking timer. It's used
to move down blocks automatically.
*/  
#ifndef TIMER
#define TIMER
extern int counter;

#define UPDATE_TIMER --counter;
#define IS_DONE      (counter == 0)
#define RESET_TIMER  counter=60;

#endif
