#include"word_searcher.h"


char found_words[10][14];
FWord found_words_data[10];
int found_words_counter = 0;

bool does_match(char* word)
{  
  //just for now
  //sure it's not good, because it's O(n), but I tried bsearch and it didn't work  
  for(size_t n = 0;n<google_words_len;++n)
      {
	if(strcmp(word,google_words[n]) == 0)
	  {
	    printf("%s matches %s\n",word,google_words[n]);
	    return true;
	  }
      }

    return false;
  //    char** found = (char**) bsearch(&word,google_words,google_words_len,sizeof(char*),str_cmp);
  //    return found != NULL;
  
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
      printf("word found in left direction:%s %ld\n",word,strlen(word));
      if(does_match(word))
	{
	  printf("@@@@@@@@%s matched! len:%ld\n",word,strlen(word));
	  strcpy(found_words[found_words_counter],word);
	  found_words_data[found_words_counter].x = current->x;
	  found_words_data[found_words_counter].y = current->y;
	  found_words_data[found_words_counter].dir = 0;
	  found_words_counter++;
	}

      search_rightward(current->x,current->y,word);
      conv_to_lower(word);
      printf("word found right direction:%s %ld\n",word,strlen(word));
      if(does_match(word))
	{
	  printf("@@@@@@@@%s matched! len:%ld\n",word,strlen(word));
	  strcpy(found_words[found_words_counter],word);
	  found_words_data[found_words_counter].x = current->x;
	  found_words_data[found_words_counter].y = current->y;
	  found_words_data[found_words_counter].dir = 1;
	  found_words_counter++;
	}

      search_upward(current->x,current->y,word);
      conv_to_lower(word);
      printf("word found upward:%s %ld\n",word,strlen(word));
      if(does_match(word))
	{
	  printf("@@@@@@@%s matched! len:%ld\n",word,strlen(word));
	  strcpy(found_words[found_words_counter],word);
	  found_words_data[found_words_counter].x = current->x;
	  found_words_data[found_words_counter].y = current->y;
	  found_words_data[found_words_counter].dir = 2;
	  found_words_counter++;
	}

      search_downward(current->x,current->y,word);
      conv_to_lower(word);
      printf("word found downward:%s %ld\n",word,strlen(word));
      if(does_match(word))
	{
	  printf("@@@@@@@@%s matched! len:%ld\n",word,strlen(word));
	  strcpy(found_words[found_words_counter],word);
	  found_words_data[found_words_counter].x = current->x;
	  found_words_data[found_words_counter].y = current->y;
	  found_words_data[found_words_counter].dir = 3;
	  found_words_counter++;

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
  
  while(x < 8 && map[start_y][x] != '\0')
  {
    word[i++] = map[start_y][x];
    x++;
  }
  word[i] = '\0';
}

void search_leftward(int start_x, int start_y, char* word)
{
  int x = start_x;
  int i = 0;
  
  while(x >= 0 && map[start_y][x] != '\0')
  {
    word[i++] = map[start_y][x];
    x--;
  }
  word[i] = '\0';  
}

void search_downward(int start_x, int start_y, char* word)
{
  int y = start_y;
  int i = 0;
  
  while(y < 14 && map[y][start_x] != '\0')
  {
    word[i++] = map[y][start_x];
    y++;
  }
  word[i] = '\0';
}

void search_upward(int start_x, int start_y, char* word)
{
  int y = start_y;
  int i = 0;
  
  while(y >= 0 && map[y][start_x] != '\0')
  {
    word[i++] = map[y][start_x];
    y--;
  }
  word[i] = '\0';  
}
void conv_to_lower(char* word)
{
  for (int i = 0; word[i] != '\0'; i++)
    {
      word[i] = tolower(word[i]);
    }
}
int str_cmp(const void* str1, const void* str2)
{
  const char *key = (const char*)str1;
  const char *element = *(const char**)str2;
  
  return strcmp(key, element);
}
