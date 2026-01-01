#include"word_searcher.h"

bool does_match(char* word)
{
  //just for now
  //sure it's not good, because it's O(n), but I tried bsearch and it didn't work  
  for(size_t n = 0;n<google_words_len;++n)
    {
      if(strcmp(word,google_words[n]) == 0)
	return true;
    }
  return false;
}
void search(VertexListNode* head)
{
  VertexListNode* current = head;

  int start_x, start_y;
  char word[8];
  while(current != NULL)
    {
      //look in 4 direction, check word, if it matches, then destroy
      
      //search leftward
      search_along_ox(-1,
		      current->x,
		      current->y,
		      word,
		      &start_x,
		      &start_y);
      if(does_match(word))
	{

	}
      else
	{
	  printf("%s is not word!\n",word);
	}
      
      //search rightward
      search_along_ox(1,
		      current->x,
		      current->y,
		      word,
		      &start_x,
		      &start_y);
      if(does_match(word))
	{

	}
      else
	{
	  printf("%s is not word!\n",word);
	}

      //search downward
      search_along_oy(1,
		      current->x,
		      current->y,
		      word,
		      &start_x,
		      &start_y);          
      if(does_match(word))
	{

	}
      else
	{
	  printf("%s is not word!\n",word);
	}

      //search upward
      search_along_oy(-1,
		      current->x,
		      current->y,
		      word,
		      &start_x,
		      &start_y);
      if(does_match(word))
	{

	}
      else
	{
	  printf("%s is not word!\n",word);
	}

      printf("found string:%s,len %d\n",word,strlen(word));
      
      current = current->next;
    }

}
void search_along_ox(int dx,
		     int x,
		     int y,
		     char *word,
		     int* start_x,
		     int* start_y)
{
  *start_y = y;
  int cur = x;
  int i = 0;
  while(map[y][cur] != '\0')
    {      
      word[i++] = map[y][cur];
      cur+=dx;
      if(cur == 0 || cur == 7)break;
    }
  word[i] = '\0';
  *start_x = cur;
}
void search_along_oy(int dy,
		     int x,
		     int y,
		     char *word,
		     int* start_x,
		     int* start_y)
{
  *start_x = x;
  int cur = y;
  int i = 0;
  while(map[cur][x] != '\0')
    {      
      word[i++] = map[cur][x];
      cur+=dy;
      if(cur == 0 || cur == 7)break;
    }
  word[i] = '\0';
  *start_y =  cur;
}
