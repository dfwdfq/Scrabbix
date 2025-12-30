#include"game.h"

void handle_keys(void)
{
  if(IsKeyReleased(KEY_A) && block_y != -1)
    {
      if(block_x > 0)
	{
	  char val = map[block_y][block_x];
	  map[block_y][block_x] = '\0';
	  map[block_y][--block_x] = val;
	}
    }
  if(IsKeyReleased(KEY_D) && block_y != -1)
    {
      if(block_x < 7)
	{
	  char val = map[block_y][block_x];
	  map[block_y][block_x] = '\0';
	  map[block_y][++block_x] = val;
	}
    }
  if(IsKeyReleased(KEY_S))
    {
      if(block_y < 13)
	{
	  char val = map[block_y][block_x];
	  map[block_y][block_x] = '\0';
	  map[++block_y][block_x] = val;
	}
    }
}
void run_game(void)
{
  handle_keys();

  printf("%d %d\n",block_x,block_y);
  UPDATE_TIMER;
  if(IS_DONE)
    {
      RESET_TIMER;
      update_map();
    }
}
void draw_game(void)
{
  draw_borders();
  draw_map();
}
