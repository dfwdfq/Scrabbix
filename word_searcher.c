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
void save_found_word(char* word, int x, int y,short dir)
{
  strcpy(found_words[found_words_counter],word);
  found_words_data[found_words_counter].x = x;
  found_words_data[found_words_counter].y = y;
  found_words_data[found_words_counter].dir = dir;
  found_words_counter++;
}
void search_word(char* word,short dir,int x_pos, int y_pos)
{
  char* substr = NULL;
  int substr_start = -1;

  int x,y;
  if(dir == 0)//left
    {
      x=-1;
      y= 0;
    }
  else
  if(dir == 1)
    {
      x=1;
      y=0;
    }
  else
  if(dir == 2)
    {
      x=0;
      y=-1;
    }
  else
  if(dir == 3)
    {
      x=0;
      y=1;
    }
  
  substr = get_next_substring(word,1,&substr_start);
  while (substr != NULL)
    {
      //check word
      if(does_match(substr))
	{
	  printf("##@@@@@@%s substr found! start pos:%d\n",substr,substr_start);
	  save_found_word(substr,
			  x_pos+(substr_start*x),
			  y_pos+(substr_start*y),
			  dir);
	}
      
      free(substr);	      
      substr = get_next_substring(NULL, 0,&substr_start);
    }

}
void search(VertexListNode* head)
{
  VertexListNode* current = head;

  char word[14];
  int i = 0;
  
  while(current != NULL)
    {
#if PRINT_DEBUG == 1      
      printf("%d# letter:%c\n",
	     i,
	     map[current->y][current->x]);
#endif      
	     
      search_leftward(current->x,current->y,word);
      conv_to_lower(word);
      search_word(word,LEFT,current->x,current->y);
#if PRINT_DEBUG == 1       
      printf("word found in left direction:%s %ld\n",word,strlen(word));
#endif      
      

      search_rightward(current->x,current->y,word);
      conv_to_lower(word);
#if PRINT_DEBUG == 1      
      printf("word found right direction:%s %ld\n",word,strlen(word));
#endif      
      search_word(word,RIGHT,current->x,current->y);

      search_upward(current->x,current->y,word);
      conv_to_lower(word);
#if PRINT_DEBUG == 1      
      printf("word found upward:%s %ld\n",word,strlen(word));
#endif      
      search_word(word,UP,current->x,current->y);
      
      search_downward(current->x,current->y,word);
      conv_to_lower(word);
#if PRINT_DEBUG == 1      
      printf("word found downward:%s %ld\n",word,strlen(word));
#endif      
      search_word(word,DOWN,current->x,current->y);
      
      current = current->next;
      i++;

      get_next_substring(NULL,1,NULL); //reset generator
    }
#if PRINT_DEBUG == 1  
  printf("\n\n");
#endif  
}
char* get_next_substring(const char* str, int reset, int* start_index)
{
  static const char* saved_str = NULL;
  static int len = 0;
  static int sub_len = 3;
  static int start = 0;
  
  if (reset || str != NULL)
    {
      if (str != NULL)
        {
	  saved_str = str;
	  len = strlen(str);
        }
      else
        {
	  saved_str = NULL;
	  len = 0;
        }
        sub_len = 3;
        start = 0;
        
        if (str == NULL && reset)
	  {
            if (start_index) *start_index = -1;
            return NULL;
	  }
    }
  
  if (saved_str == NULL || len < 3)
    {
      if (start_index) *start_index = -1;
      return NULL;
    }
  
  while (sub_len <= 13 && sub_len <= len)
    {
      if (start <= len - sub_len)
        {
	  char* substr = (char*)malloc(sub_len + 1);
	  if (!substr) 
            {
	      if (start_index) *start_index = -1;
	      return NULL;
            }
	  
	  strncpy(substr, saved_str + start, sub_len);
	  substr[sub_len] = '\0';
          
	  if (start_index) 
	    *start_index = start;
	  
	  start++;            
	  return substr;
        }
      
      sub_len++;
      start = 0;
    }
  
  if (start_index) *start_index = -1;
  return NULL;
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
