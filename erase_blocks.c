#include"game.h"
void erase_blocks(void)
{
  for(int n = 0;n<found_words_counter;++n)
    {	
      short dir = found_words_data[n].dir;
      int x     = found_words_data[n].x;
      int y     = found_words_data[n].y;
      int len   = strlen(found_words[n]);
      score     += len*10;
      
      if(dir == RIGHT)
	{
	  for(int i = x;i<x+len;i++)
	    {
	      map[y][i] = '\0';
	      letters_head = remove_by_value(letters_head,i,y);
	    }
	}
      
      if(dir == LEFT)
	{
	  for(int i = 0;i<len;++i)
	    {
	      map[y][x-i] = '\0';
	      letters_head = remove_by_value(letters_head,x-i,y);
	    }
	}
      
      if(dir == UP)
	{
	  printf("%s %d y=%d\n",found_words[n],len,y);	  
	  for(int i =0;i<len;++i)
	    {
	      map[y-i][x] = '\0';
	      letters_head = remove_by_value(letters_head,x,y-i);
	    }
	}

      if(dir == DOWN)
	{
	  for(int i =y;i<y+len;++i)
	    {
	      map[i][x] = '\0';
	      letters_head = remove_by_value(letters_head,x,i);
	      }
	}
      if(dir == LEFT_DOWN)
	{
	  map[y][x] = '\0';
	  letters_head = remove_by_value(letters_head,x,y);
	  
	  ++y;
	  for(int i = 0;i<len-1;++i)
	    {
	      map[y][x-i] = '\0';
	      letters_head = remove_by_value(letters_head,x-i,y);
	    }
	}
      if(dir == RIGHT_DOWN)
	{
	  map[y][x] = '\0';
	  letters_head = remove_by_value(letters_head,x,y);
	  
	  ++y;
	  for(int i = 0;i<len-1;++i)
	    {
	      map[y][x+i] = '\0';
	      letters_head = remove_by_value(letters_head,x+i,y);
	    }
	}
      if(dir == LEFT_UP)
	{
	  map[y][x] = '\0';
	  letters_head = remove_by_value(letters_head,x,y);
	  
	  --y;
	  for(int i = 0;i<len-1;++i)
	    {
	      map[y][x-i] = '\0';
	      letters_head = remove_by_value(letters_head,x-i,y);
	    }
	}
      if(dir == RIGHT_UP)
	{
	  map[y][x] = '\0';
	  letters_head = remove_by_value(letters_head,x,y);
	  
	  --y;
	  for(int i = 0;i<len-1;++i)
	    {
	      map[y][x+i] = '\0';
	      letters_head = remove_by_value(letters_head,x+i,y);
	    }
	}


    }
  found_words_counter = 0;
}
