#include"game.h"

VertexListNode* letters_head;
int score = 0;

void init_game(void)
{
  init_bag();
  letters_head = NULL;

  generate_random_start_pos();
  map[block_y][block_x] = get_next_test_letter();

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
      if(block_x > 0 &&
	 map[block_y][block_x-1] == '\0')
	{
	  char val = map[block_y][block_x];
	  map[block_y][block_x] = '\0';
	  map[block_y][--block_x] = val;
	}
    }
  if(IsKeyReleased(KEY_D) &&
     block_y != -1)
    {
      if(block_x < 7 &&
	 map[block_y][block_x+1] == '\0')
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
  handle_keys();
  
  //this fancy-pancy hack prevents block from being moved when it get stucked
  if(map[block_y+1][block_x] != '\0' ||
     block_y == 13)
    {
      push_node(&letters_head,block_x,block_y); //add new block to list of existing blocks

      //nullify block
      block_x = -1;
      block_y = -1;
      search(letters_head);

      generate_random_start_pos();
      map[block_y][block_x] = get_next_test_letter();
    }

  //move blocks down every 60 tick
  UPDATE_MOV_TIMER;
  if(IS_MOV_TIMER_DONE)
    {
      RESET_MOV_TIMER;
      update_map();
    }


  //if there are words to erase, start counting down the timer to erase them
  if(found_words_counter > 0)
    {
      UPDATE_ER_TIMER;
    }

  if(IS_ER_TIMER_DONE)
  {
    RESET_ER_TIMER;
    for(int i = 0;i<found_words_counter;++i)
      {	
	short dir = found_words_data[i].dir;
	int x     = found_words_data[i].x;
	int y     = found_words_data[i].y;
	int len   = strlen(found_words[i]);
	
	//right(1)
	if(dir == 1)
	  {
	    for(int i = x;i<x+len;i++)
	      {
		map[y][i] = '\0';
		letters_head = remove_by_value(letters_head,i,y);
	      }
	  }
	
	//left(0)
	if(dir == 0)
	  {
	    for(int i = 0;i<len;++i)
	      {
		map[y][x-i] = '\0';
		letters_head = remove_by_value(letters_head,x-i,y);
	      }
	  }

	//up(2)
	if(dir == 2)
	  {
	    for(int i =0;i<len;++i)
	      {
		map[y-i][x] = '\0';
		letters_head = remove_by_value(letters_head,x,y-i);
	      }
	  }
	
      }
    printf("\n");
    found_words_counter = 0;
  }

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
