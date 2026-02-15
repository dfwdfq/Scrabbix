#include"map.h"

char map[MAP_HEIGHT][MAP_WIDTH];
int block_x, block_y;

void init_map(void)
{
  for(int i = 0;i<MAP_HEIGHT;++i)
    {
      memset(map[i],'\0',sizeof(char)*8);
    }

  block_x = -1, block_y = -1;
}

void draw_map(Font* font)
{
  bool marked[MAP_HEIGHT][MAP_WIDTH] = {false};

  if (er_counter > 0 && found_words_counter > 0)
      {
        for (int idx = 0; idx < found_words_counter; idx++)
	  {
            FWord *fw = &found_words_data[idx];
            int len = strlen(found_words[idx]);
            int x = fw->x;
            int y = fw->y;
            int dir = fw->dir;

            switch (dir)
	      {
                case LEFT:
                    for (int i = 0; i < len; i++)
		      {
                        int cx = x - i;
                        if (cx >= 0) marked[y][cx] = true;
                    }
                    break;
                case RIGHT:
                    for (int i = 0; i < len; i++)
		      {
                        int cx = x + i;
                        if (cx < MAP_WIDTH) marked[y][cx] = true;
                    }
                    break;
                case UP:
                    for (int i = 0; i < len; i++)
		      {
                        int cy = y - i;
                        if (cy >= 0) marked[cy][x] = true;
                    }
                    break;
                case DOWN:
                    for (int i = 0; i < len; i++)
		      {
                        int cy = y + i;
                        if (cy < MAP_HEIGHT) marked[cy][x] = true;
                    }
                    break;
                case LEFT_DOWN:
                    if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT)
                        marked[y][x] = true;
                    if (y + 1 < MAP_HEIGHT)
		      {
                        marked[y + 1][x] = true;
                        for (int i = 1; i < len - 1; i++)
			  {
                            int cx = x - i;
                            if (cx >= 0) marked[y + 1][cx] = true;
                        }
                    }
                    break;
                case RIGHT_DOWN:
                    if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT)
                        marked[y][x] = true;
		    
                    if (y + 1 < MAP_HEIGHT)
		      {
                        marked[y + 1][x] = true;
                        for (int i = 1; i < len - 1; i++)
			  {
                            int cx = x + i;
                            if (cx < MAP_WIDTH) marked[y + 1][cx] = true;
                        }
                    }
                    break;
                case LEFT_UP:
                    if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT)
                        marked[y][x] = true;
		    
                    if (y - 1 >= 0)
		      {
                        marked[y - 1][x] = true;
                        for (int i = 1; i < len - 1; i++)
			  {
                            int cx = x - i;
                            if (cx >= 0) marked[y - 1][cx] = true;
                        }
                    }
                    break;
                case RIGHT_UP:
                    if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT)
                        marked[y][x] = true;
                    if (y - 1 >= 0)
		      {
                        marked[y - 1][x] = true;
                        for (int i = 1; i < len - 1; i++)
			  {
                            int cx = x + i;
                            if (cx < MAP_WIDTH) marked[y - 1][cx] = true;
                        }
                    }
                    break;
            }
        }
    }

    for (int y = 0; y < MAP_HEIGHT; y++)
      {
        for (int x = 0; x < MAP_WIDTH; x++)
	  {
            if (map[y][x] != '\0')
	      {
		draw_gb_block(x, y, map[y][x], font, 1);

                if (marked[y][x] && (er_counter % 2 == 0))
		  {
                    Color highlight = {255, 255, 255, 128};
                    DrawRectangle(GPX(x), GPY(y), CELL_SIZE, CELL_SIZE, highlight);
                }
            }
        }
    }
}
void update_map(void)
{
  if(block_x == -1 ||
     block_y == -1)
    return;

  if (block_y == MAP_HEIGHT - 1)
    return;
  
  char val = map[block_y][block_x];
  if(map[block_y+1][block_x] == '\0')
    {
      map[block_y][block_x] = '\0';
      map[++block_y][block_x] = val;
    }

}
void generate_random_start_pos(void)
{
  block_y = 0;
  block_x = GetRandomValue(0,7);
}
