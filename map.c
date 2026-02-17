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
            int x = fw->x;
            int y = fw->y;
            marked[y][x] = true;                     //mark start
            for (int i = 0; i < fw->tail_len; i++)   //mark tail cells
            {
                int tx = fw->tail[i].x;
                int ty = fw->tail[i].y;
                if (tx >= 0 && tx < MAP_WIDTH && ty >= 0 && ty < MAP_HEIGHT)
                    marked[ty][tx] = true;
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
