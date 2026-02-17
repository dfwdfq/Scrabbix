#include"word_searcher.h"


char found_words[MAX_FOUND_WORDS_SIZE][FOUND_WORD_LEN];
FWord found_words_data[MAX_FOUND_WORDS_SIZE];
int found_words_counter = 0;
size_t min_word_len = 3;

int str_cmp(const void* a, const void* b)
{
  return strcmp(*(const char**)a, *(const char**)b);
}

bool does_match(char* word)
{
  //if it's too short, then it doesn't match
  if(strlen(word) < min_word_len)
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
#if PRINT_DEBUG == 1	  
	  DEBUG_PRINT(ANSI_GREEN,"%s is already added!\n",word);
#endif	  
	  return;
	}
    }
  
  strcpy(found_words[found_words_counter],word);
  found_words_data[found_words_counter].x = x;
  found_words_data[found_words_counter].y = y;
  found_words_data[found_words_counter].dir = dir;

  int _x,_y;
  size_t size;
  switch(dir)
    {
    case LEFT:
       _x = x-1;
       _y = y;
       size = strlen(word)-1;
      for(size_t i = 0;i<size;++i)
	{
	  found_words_data[found_words_counter].tail[i].x = _x-i;
	  found_words_data[found_words_counter].tail[i].y = _y;
	}
      found_words_data[found_words_counter].tail_len = strlen(word)-1;
      break;
    case RIGHT:
       _x = x+1;
       _y = y;
       size = strlen(word)-1;
      for(size_t i = 0;i<size;++i)
	{
	  found_words_data[found_words_counter].tail[i].x = _x+i;
	  found_words_data[found_words_counter].tail[i].y = _y;
	}
      found_words_data[found_words_counter].tail_len = strlen(word)-1;
      break;
    case UP:
       _x = x;
       _y = y-1;
       size = strlen(word)-1;
      for(size_t i = 0;i<size;++i)
	{
	  found_words_data[found_words_counter].tail[i].x = _x;
	  found_words_data[found_words_counter].tail[i].y = _y-i;
	}
      found_words_data[found_words_counter].tail_len = strlen(word)-1;
      break;
    case DOWN:
       _x = x;
       _y = y+1;
       size = strlen(word)-1;
      for(size_t i = 0;i<size;++i)
	{
	  found_words_data[found_words_counter].tail[i].x = _x;
	  found_words_data[found_words_counter].tail[i].y = _y+i;
	}
      found_words_data[found_words_counter].tail_len = strlen(word)-1;

      break;
    }
  found_words_counter++;
}
void search_word(char* word,short dir,int x_pos, int y_pos)
{
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

  char substr_buf[14];
  int substr_start = -1;
  if (get_next_substring(word, 1, &substr_start, substr_buf, sizeof(substr_buf)))
    {
      do {
        if (does_match(substr_buf))
	  {
            save_found_word(substr_buf,
                            x_pos + (substr_start * x),
                            y_pos + (substr_start * y),
                            dir);
	  }
      } while (get_next_substring(NULL, 0, &substr_start, substr_buf, sizeof(substr_buf)));
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

void save_found_word_path(char* word, Vector2* cells, int num_cells)
{
    // Avoid duplicates (linear search, ok for small lists)
    for (int i = 0; i < found_words_counter; i++)
    {
        if (strcmp(word, found_words[i]) == 0)
        {
#if PRINT_DEBUG == 1	  
            DEBUG_PRINT(ANSI_GREEN, "%s is already added!\n", word);
#endif	    
            return;
        }
    }

    strcpy(found_words[found_words_counter], word);
    found_words_data[found_words_counter].x = cells[0].x;
    found_words_data[found_words_counter].y = cells[0].y;
    found_words_data[found_words_counter].tail_len = num_cells - 1;

    for (int i = 1; i < num_cells; i++)
        found_words_data[found_words_counter].tail[i-1] = cells[i];

    found_words_data[found_words_counter].dir = 0; // unused now
    found_words_counter++;
}
void search_L_shaped(int start_x, int start_y)
{
    char path_str[21];
    Vector2 path_pos[21];
    int dx[4] = {-1, 1, 0, 0}; 
    int dy[4] = {0, 0, -1, 1};

    for (int d = 0; d < 4; d++)
    {
        int steps = 0;
        int cx = start_x, cy = start_y;

        path_pos[0].x = start_x;
        path_pos[0].y = start_y;
        path_str[0] = tolower(map[start_y][start_x]);

        while (1)
        {
            int nx = cx + dx[d];
            int ny = cy + dy[d];
            if (nx < 0 || nx >= MAP_WIDTH || ny < 0 || ny >= MAP_HEIGHT) break;
            if (map[ny][nx] == '\0') break;

            steps++;
            cx = nx; cy = ny;
            path_pos[steps].x = cx;
            path_pos[steps].y = cy;
            path_str[steps] = tolower(map[cy][cx]);

            if (steps >= 1)
            {
                int perp1, perp2;
                if (d == LEFT || d == RIGHT)
                {
                    perp1 = UP;
                    perp2 = DOWN;
                }
                else
                {
                    perp1 = LEFT;
                    perp2 = RIGHT;
                }

                for (int p = 0; p < 2; p++)
                {
                    int perp = (p == 0) ? perp1 : perp2;

                    int bx = cx, by = cy;
                    int b = 0;

                    while (1)
                    {
                        int nx2 = bx + dx[perp];
                        int ny2 = by + dy[perp];
                        if (nx2 < 0 || nx2 >= MAP_WIDTH || ny2 < 0 || ny2 >= MAP_HEIGHT) break;
                        if (map[ny2][nx2] == '\0') break;

                        b++;
                        bx = nx2; by = ny2;
                        int idx = steps + b;
                        if (idx >= 20) break; //prevent buffer overflow

                        path_pos[idx].x = bx;
                        path_pos[idx].y = by;
                        path_str[idx] = tolower(map[by][bx]);
                        path_str[idx + 1] = '\0';

			char substr_buf[14];
			int substr_start;
			if (get_next_substring(path_str, 1, &substr_start, substr_buf, sizeof(substr_buf)))
			  {
			    do {
			      if (does_match(substr_buf))
				{
				  int word_len = strlen(substr_buf);
				  Vector2 word_cells[13];
				  for (int i = 0; i < word_len; i++)
				    word_cells[i] = path_pos[substr_start + i];
				  save_found_word_path(substr_buf, word_cells, word_len);
				}
			    } while (get_next_substring(NULL,
							0,
							&substr_start,
							substr_buf,
							sizeof(substr_buf)));
			  }
		    }
		}
	    }
	}
    }
}
void conv_to_lower(char* word)
{
  for (int i = 0; word[i] != '\0'; i++)
    {
      word[i] = tolower(word[i]);
    }
}
