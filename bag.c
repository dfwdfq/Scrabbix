#include"bag.h"

char bag[100];

void init_bag(void)
{
  srand(time(0));
  memcpy(bag,
	 "AAAAAAAAABBCCDDDDEEEEEEEEEEEEFFGGGHHIIIIIIIIIJKLLLLMMNNNNNNOOOOOOOOPPQRRRRRRSSSSTTTTTTUUUUVVWWXYYZ",
	 99);

    shuffle(bag,100);
}
void shuffle(char* array, size_t n)
{
  if (n > 1) 
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
}
