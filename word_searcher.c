#include"word_searcher.h"


char found_words[MAX_FOUND_WORDS_SIZE][FOUND_WORD_LEN];
FWord found_words_data[MAX_FOUND_WORDS_SIZE];
int found_words_counter = 0;
int min_word_len = 3;

int str_cmp(const void* a, const void* b)
{
  return strcmp(*(const char**)a, *(const char**)b);
}

bool does_match(char* word)
{
  //if it's too short, then it doesn't match
  if(strlen(word) != min_word_len)
    {
      return false;
    }
  
  char *key = word;
  char** found = bsearch(&key,
			 google_words,
			 google_words_len, 
			 sizeof(char*), str_cmp);
  return found != NULL;   
}
void save_found_word(char* word, int x, int y,short dir)
{
  //check is word already added
  //linear search is not ok, but good enough since little amount
  for(int i = 0;i<found_words_counter;++i)
    {
      if(strcmp(word,found_words[i]) == 0)
	{
	  DEBUG_PRINT(ANSI_GREEN,"%s is already added!\n",word);
	  return;
	}
    }
  
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
  if(dir == LEFT)
    {
      x=-1;
      y= 0;
    }
  else
  if(dir == RIGHT)
    {
      x=1;
      y=0;
    }
  else
  if(dir == UP)
    {
      x=0;
      y=-1;
    }
  else
  if(dir == DOWN)
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
	  DEBUG_PRINT(ANSI_RED,
		      "##@@@@@@%s substr found! start pos:%d\n",
		      substr,
		      substr_start);
	  
	  save_found_word(substr,
			  x_pos+(substr_start*x),
			  y_pos+(substr_start*y),
			  dir);
	}
      
      free(substr);	      
      substr = get_next_substring(NULL, 0,&substr_start);
    }
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
  
  while(y < MAP_HEIGHT && map[y][start_x] != '\0')
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
void search_L_left_down(int start_x, int start_y, char* word)
{
  //can't search
  if(start_y+1 == MAP_HEIGHT)return;
  
  int y = start_y;
  int x = start_x;  
  int i = 0;
  
  word[i++] = map[y][x];  
  ++y;
  while(x >= 0 && map[y][x] != '\0')
    {
      word[i++] = map[y][x];
      x--;
    }
  word[i] = '\0';  
}
void search_L_right_down(int start_x, int start_y, char* word)
{
  //can't search
  if(start_y+1 == MAP_HEIGHT)return;
  
  int y = start_y;
  int x = start_x;  
  int i = 0;
  
  word[i++] = map[y][x];  
  ++y;
  while(x < 8 && map[y][x] != '\0')
    {
      word[i++] = map[y][x];
      x++;
    }
  word[i] = '\0';  
}
void search_L_left_up(int start_x,int start_y, char* word)
{
  if(start_y-1 == -1)return;

    int y = start_y;
    int x = start_x;  
    int i = 0;
    
    word[i++] = map[y][x];
    --y;
    while(x >= 0 && map[y][x] != '\0')
      {
	word[i++] = map[y][x];
	x--;
      }
    word[i] = '\0';  
}
void search_L_right_up(int start_x, int start_y,char* word)
{
  //can't search
  if(start_y-1 == -1)return;
  
  int y = start_y;
  int x = start_x;  
  int i = 0;
  
  word[i++] = map[y][x];  
  --y;
  while(x < 8 && map[y][x] != '\0')
    {
      word[i++] = map[y][x];
      x++;
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
void reverse_string(char* in, char* out)
{
  size_t size = strlen(in);
  for (size_t i = 0; i < size; i++)
    {
      out[i] = in[size - 1 - i];
    }
    
  out[size] = '\0';  
}
