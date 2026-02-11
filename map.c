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
  for(int y =0;y<MAP_HEIGHT;++y)
    for(int x =0;x<MAP_WIDTH;++x)
      {
	if(map[y][x] != '\0')
	  {
	    draw_gb_block(x,y,map[y][x],font,1);
	  }
      }
}
void update_map(void)
{
  if(block_x == -1 &&
     block_y == -1)
    return;
  
  if(block_y == MAP_HEIGHT-1)
    {
      block_x = -1;
      block_y = -1;
    }
  else
    {
      char val = map[block_y][block_x];
      if(map[block_y+1][block_x] == '\0')
	{
	  map[block_y][block_x] = '\0';
	  map[++block_y][block_x] = val;
	}
    }
}
void generate_random_start_pos(void)
{
  block_y = 0;
  block_x = GetRandomValue(0,7);
}
