/*
This is bad(!), yet primitive and working
implementation of ticking timer. It's used
to move down blocks automatically.
*/  
#ifndef TIMER
#define TIMER
extern int mov_counter, mov_timer;
extern int er_counter;
extern int found_counter;

#define UPDATE_MOV_TIMER    --mov_counter;
#define IS_MOV_TIMER_DONE   (mov_counter == 0)
#define RESET_MOV_TIMER     mov_counter=mov_timer;

#define UPDATE_ER_TIMER    --er_counter;
#define IS_ER_TIMER_DONE   (er_counter == 0)
#define RESET_ER_TIMER     er_counter=8;

#define UPDATE_FOUND_TIMER    --found_counter;
#define IS_FOUND_TIMER_DONE   (found_counter == 0)
#define RESET_FOUND_TIMER     found_counter=60;


#endif
