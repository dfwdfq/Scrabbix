#include"game.h"
void erase_blocks(void)
{
  for(int n = 0;n<found_words_counter;++n)
    {	
      int x     = found_words_data[n].x;
      int y     = found_words_data[n].y;
      int len   = strlen(found_words[n]);
      score     += len*10;

      map[y][x] = '\0';
      letters_head = remove_by_value(letters_head,x,y);
      for(int i = 0;i<found_words_data[n].tail_len;++i)
	{
	  int _x = found_words_data[n].tail[i].x;
	  int _y = found_words_data[n].tail[i].y;
	  map[_y][_x] = '\0';
	  letters_head = remove_by_value(letters_head,_x,_y);
	}
    }
  found_words_counter = 0;
}
