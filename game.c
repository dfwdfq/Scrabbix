#include"game.h"

VertexListNode* letters_head;
int score = 0;
bool _pause = false;
bool victory = false, game_over=false;

char found_words_labels[MAX_FOUND_WORDS_SIZE][FOUND_WORD_LEN];
int found_words_labels_counter;
Color fading_w_color = (Color){255,255,255,255};


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
      if(block_x < MAP_WIDTH-1 &&
	 map[block_y][block_x+1] == '\0')
	{
	  char val = map[block_y][block_x];
	  map[block_y][block_x] = '\0';
	  map[block_y][++block_x] = val;
	}
    }
  if(IsKeyReleased(KEY_S))
    {
      if(block_y < MAP_HEIGHT-1 && map[block_y+1][block_x] == '\0')
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
     block_y == MAP_HEIGHT-1)
    {
      push_node(&letters_head,block_x,block_y); //add new block to list of existing blocks

      //nullify block
      block_x = -1;
      block_y = -1;
      search(letters_head);

      generate_random_start_pos();
      map[block_y][block_x] = get_next_letter();
    }

  //move blocks down every 60 tick
  UPDATE_MOV_TIMER;
  if(IS_MOV_TIMER_DONE)
    {
      RESET_MOV_TIMER;
      update_map();
    }


  //if there are words to erase, start counting down the timer to erase them
  //also copy them to draw
  if(found_words_counter > 0)
    {
      UPDATE_ER_TIMER;
      fading_w_color = (Color){255,255,255,255};
      found_words_labels_counter = found_words_counter;
      for(int i = 0;i<found_words_labels_counter;++i)
	{
	  strcpy(found_words_labels[i],found_words[i]);
	}
    }

  //erase words
  if(IS_ER_TIMER_DONE)
  {
    RESET_ER_TIMER;
    erase_blocks();
    reupdate_blocks();
    if(IS_FOUND_TIMER_DONE)
      {
	found_words_counter = 0;
	RESET_FOUND_TIMER;
      }
  }

}
void draw_game(void)
{
  draw_borders();
  draw_map();
  draw_labels();
  draw_found_words();
}
void draw_labels(void)
{
  DrawText("next:",570,250,32,WHITE);
  DrawRectangle(655,250,CELL_SIZE/2,CELL_SIZE/2,WHITE);
  
  char str[2];
  sprintf(str,"%c\n",bag[current_letter]);
  DrawText(str,660,250,32,BLACK);

  DrawText("Scrabbix",540,20,56,WHITE);

  char score_line[7] = {'0','0','0','0','0','0','\0'};
  char score_str[6];
  sprintf(score_str,"%d",score);
  int j = 0;
  for(int i = 6-strlen(score_str);i<6;++i)
    {
     score_line[i] = score_str[j++];     
    }
  char _score[30];
  sprintf(_score,"score:%s",score_line);
  DrawText(_score,550,200,32,WHITE);

  if(_pause)
    {
      DrawText("paused!",550,840,48,WHITE);
    }
}

void draw_found_words(void)
{
  char str[40];
  if(found_words_labels_counter == 0)return;
  if(!(IS_FOUND_TIMER_DONE))
    {
      UPDATE_FOUND_TIMER;
      int start_x = 570;
      int start_y = 330;
      for(int i = 0;i<found_words_labels_counter;++i)
	{
	  sprintf(str,"%s found!\n",found_words_labels[i]);
	  DrawText(str,start_x,start_y+(i*50),32,fading_w_color);	  
	}
      fading_w_color.a-=1;
    }
}
