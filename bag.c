#include"bag.h"

char bag[100];
int current_letter = 0;


void init_bag(void)
{

  srand(time(0));
#ifndef DEBUG 
  memcpy(bag,
	 "AAAAAAAAABBCCDDDDEEEEEEEEEEEEFFGGGHHIIIIIIIIIJKLLLLMMNNNNNNOOOOOOOOPPQRRRRRRSSSSTTTTTTUUUUVVWWXYYZ",
	 98);

    shuffle(bag,98);
#endif
#ifdef DEBUG 
    memcpy(bag,
	   "CATBAGWORDHELLOBINBITDOGBOTBONEWELLHELLDEATHWORLDWISDOMLOVEHATEVAGINASEXGOBLINUNOMAMATINFOILFFF",
	   98);
#endif
    
}
void shuffle(char* array, size_t n)
{
  size_t i;
  for (i = 0; i < n - 1; i++) 
    {
      size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
      char t = array[j];
      array[j] = array[i];
      array[i] = t;
    }
}
char get_next_letter(void)
{
  if(current_letter == 99)
    {
      shuffle(bag,100);
      current_letter = 0;
    }
  return bag[current_letter++];
}

