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

  
  char word[8];
  int i = 0;
  while(current != NULL)
    {
      printf("%d# letter:%c\n",
	     i,
	     map[current->y][current->x]);
      
      search_leftward(current->x,current->y,word);
      conv_to_lower(word);
      printf("word found in left direction:%s %d\n",word,strlen(word));
      if(does_match(word))
	{
	  printf("%s matched!\n",word);	  
	}

      search_rightward(current->x,current->y,word);
      conv_to_lower(word);
      printf("word found right direction:%s %d\n",word,strlen(word));
      if(does_match(word))
	{
	  printf("%s matched!\n",word);
	}
      
      current = current->next;
      i++;
    }
  printf("\n\n");

}
void search_rightward(int start_x, int start_y, char* word)
{
  int x = start_x;
  int i = 0;
  word[i++] = map[start_y][x++];
  while(1)
    {
      if(i == 8) break;
      if(map[start_y][x] == '\0')break;
      if(x == 8)break;
      word[i++] = map[start_y][x++];
    }
  word[i] = '\0';
}
void search_leftward(int start_x, int start_y, char* word)
{
  int x = start_x;
  int i = 0;
  word[i++] = map[start_y][x--];
  while(1)
    {
      if(i == -1) break;
      if(map[start_y][x] == '\0')break;
      if(x == -1)break;
      word[i++] = map[start_y][x--];
    }
  word[i] = '\0';  
}
void conv_to_lower(char* word)
{
  int i =0;
  while(1)
    {
      if(i == 8)break;
      word[i++] = tolower(word[i]);
    }
}
