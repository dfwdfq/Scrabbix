#include"game.h"

VertexListNode* letters_head;

void init_game(void)
{
  init_bag();
  letters_head = NULL;
}
void free_game(void)
{
  clear_VertexList(letters_head);
}
void handle_keys(void)
{
  if(IsKeyReleased(KEY_A) &&
     block_y != -1)
    {
      if(block_x > 0)
	{
	  char val = map[block_y][block_x];
	  map[block_y][block_x] = '\0';
	  map[block_y][--block_x] = val;
	}
    }
  if(IsKeyReleased(KEY_D) &&
     block_y != -1)
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
      if(block_y < 13 && map[block_y+1][block_x] == '\0')
	{
	  char val = map[block_y][block_x];
	  map[block_y][block_x] = '\0';
	  map[++block_y][block_x] = val;
	}
    }
}
void run_game(void)
{
  if(block_x == -1 &&
     block_y == -1)
    {
      generate_random_start_pos();
      map[block_y][block_x] = get_next_letter();
    }
  
  handle_keys();
  //this fancy-pancy hack prevents block from being moved when it get stucked
  if(map[block_y+1][block_x] != '\0' ||
     block_y == 13)
    {
      push_node(&letters_head,block_x,block_y);
      block_x = -1;
      block_y = -1;
      search(letters_head);
      //print_list(letters_head);
    }
  
  UPDATE_TIMER;
  if(IS_DONE)
    {
      RESET_TIMER;
      update_map();
    }

  //printf(" current block position: %d %d\n",block_x,block_y);
}
void draw_game(void)
{
  draw_borders();
  draw_map();
  draw_labels();
}
void draw_labels(void)
{
  DrawText("next:",535,300,32,WHITE);
  DrawRectangle(620,300,CELL_SIZE/2,CELL_SIZE/2,WHITE);
  
  char str[2];
  sprintf(str,"%c\n",bag[current_letter]);
  DrawText(str,625,300,32,BLACK);
}
