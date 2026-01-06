#include"game.h"

VertexListNode* letters_head;
int score = 0;

char found_words_labels[10][14];
int found_words_labels_counter;


#if TEST == 0 || TEST == 13 //13 is sandboxing
void init_game(void)
{
  init_bag();
  letters_head = NULL;

  generate_random_start_pos();
  map[block_y][block_x] = get_next_letter();

}
#endif
#if TEST == 1
void init_game(void)
{
  init_bag();
  letters_head = NULL;

  map[13][2] = 'C';
  map[13][3] = 'A'; 
  map[13][4] = 'T';
  
  push_node(&letters_head, 2, 13);
  push_node(&letters_head, 3, 13);
  push_node(&letters_head, 4, 13);
  

  
  search(letters_head);
}
#endif
#if TEST == 2
//vertical word "BAG"
void init_game(void)
{
  init_bag();
  letters_head = NULL;
  
  map[10][3] = 'B';
  map[11][3] = 'A';
  map[12][3] = 'G';
  
  push_node(&letters_head, 3, 10);
  push_node(&letters_head, 3, 11);
  push_node(&letters_head, 3, 12);
  
  search(letters_head);
}
#endif

#if TEST == 3
//L-shaped word "GREAT" (G at turn)
void init_game(void)
{
  init_bag();
  letters_head = NULL;
  
  // L shape: G at (3,12), then REAT to the right at row 13
  map[12][3] = 'G';
  map[13][3] = 'R';
  map[13][4] = 'E';
  map[13][5] = 'A';
  map[13][6] = 'T';
  
  push_node(&letters_head, 3, 12);
  push_node(&letters_head, 3, 13);
  push_node(&letters_head, 4, 13);
  push_node(&letters_head, 5, 13);
  push_node(&letters_head, 6, 13);
  
  search(letters_head);
}
#endif

#if TEST == 4
// Test 4: Multiple words simultaneously
void init_game(void)
{
  init_bag();
  letters_head = NULL;
  
  // Create "CAT" horizontally and "AT" vertically
  // C A T
  //   A
  //   T
  map[10][2] = 'C';
  map[10][3] = 'A';
  map[10][4] = 'T';
  map[11][3] = 'A';
  map[12][3] = 'T';
  
  push_node(&letters_head, 2, 10);
  push_node(&letters_head, 3, 10);
  push_node(&letters_head, 4, 10);
  push_node(&letters_head, 3, 11);
  push_node(&letters_head, 3, 12);
  
  search(letters_head);
}
#endif

#if TEST == 5
// Test 5: Word at grid edges
void init_game(void)
{
  init_bag();
  letters_head = NULL;
  
  // Left edge vertical word "DOG"
  map[11][0] = 'D';
  map[12][0] = 'O';
  map[13][0] = 'G';
  
  // Right edge horizontal word "CAT"
  map[13][5] = 'C';
  map[13][6] = 'A';
  map[13][7] = 'T';
  
  push_node(&letters_head, 0, 11);
  push_node(&letters_head, 0, 12);
  push_node(&letters_head, 0, 13);
  push_node(&letters_head, 5, 13);
  push_node(&letters_head, 6, 13);
  push_node(&letters_head, 7, 13);
  
  search(letters_head);
}
#endif

#if TEST == 6
// Test 6: Stacked blocks with word at bottom
void init_game(void)
{
  init_bag();
  letters_head = NULL;
  
  // Stack some random blocks
  map[10][3] = 'X';
  map[11][3] = 'Y';
  map[12][3] = 'Z';
  
  // Create "CAT" at bottom
  map[13][2] = 'C';
  map[13][3] = 'A';
  map[13][4] = 'T';
  
  push_node(&letters_head, 3, 10);
  push_node(&letters_head, 3, 11);
  push_node(&letters_head, 3, 12);
  push_node(&letters_head, 2, 13);
  push_node(&letters_head, 3, 13);
  push_node(&letters_head, 4, 13);
  
  search(letters_head);
}
#endif

#if TEST == 7
// Test 7: Chain reaction - removing word causes new word
void init_game(void)
{
  init_bag();
  letters_head = NULL;
  
  // Create "CAT" horizontally
  map[13][2] = 'C';
  map[13][3] = 'A';
  map[13][4] = 'T';
  
  // Above 'A' put 'R' and 'T' to form "RAT" when blocks fall
  map[11][3] = 'R';
  map[12][3] = 'T';
  
  push_node(&letters_head, 2, 13);
  push_node(&letters_head, 3, 13);
  push_node(&letters_head, 4, 13);
  push_node(&letters_head, 3, 11);
  push_node(&letters_head, 3, 12);
  
  search(letters_head);
}
#endif

#if TEST == 8
// Test 8: Non-dictionary words (should NOT be removed)
void init_game(void)
{
  init_bag();
  letters_head = NULL;
  
  // Create "XYZ" - not in dictionary
  map[13][2] = 'X';
  map[13][3] = 'Y';
  map[13][4] = 'Z';
  
  // Create "CAT" - should be removed
  map[12][2] = 'C';
  map[12][3] = 'A';
  map[12][4] = 'T';
  
  push_node(&letters_head, 2, 13);
  push_node(&letters_head, 3, 13);
  push_node(&letters_head, 4, 13);
  push_node(&letters_head, 2, 12);
  push_node(&letters_head, 3, 12);
  push_node(&letters_head, 4, 12);
  
  search(letters_head);
}
#endif

#if TEST == 9
// Test 9: Complex L-shape combinations
void init_game(void)
{
  init_bag();
  letters_head = NULL;
  
  // Create multiple L-shapes
  // L1: G-R-E-A-T
  map[10][2] = 'G';
  map[11][2] = 'R';
  map[11][3] = 'E';
  map[11][4] = 'A';
  map[11][5] = 'T';
  
  // L2: C-O-A-T
  map[12][5] = 'C';
  map[13][5] = 'O';
  map[13][6] = 'A';
  map[13][7] = 'T';
  
  push_node(&letters_head, 2, 10);
  push_node(&letters_head, 2, 11);
  push_node(&letters_head, 3, 11);
  push_node(&letters_head, 4, 11);
  push_node(&letters_head, 5, 11);
  push_node(&letters_head, 5, 12);
  push_node(&letters_head, 5, 13);
  push_node(&letters_head, 6, 13);
  push_node(&letters_head, 7, 13);
  
  search(letters_head);
}
#endif

#if TEST == 10
// Test 10: Full column test for block falling mechanics
void init_game(void)
{
  init_bag();
  letters_head = NULL;
  
  // Fill column 3 completely
  for(int y = 6; y < MAP_HEIGHT; y++) {
    map[y][3] = 'A' + (y % 26);
    push_node(&letters_head, 3, y);
  }
  
  // Put "CAT" at the bottom of column 4
  map[13][4] = 'C';
  map[13][5] = 'A';
  map[13][6] = 'T';
  push_node(&letters_head, 4, 13);
  push_node(&letters_head, 5, 13);
  push_node(&letters_head, 6, 13);
  
  search(letters_head);
}
#endif

#if TEST == 11
// Test 11: Moving block mechanics
void init_game(void)
{
  init_bag();
  letters_head = NULL;
  
  // Create obstacles
  map[13][2] = 'X';
  map[13][6] = 'Y';
  
  // Place a movable block above
  block_y = 12;
  block_x = 4;
  map[block_y][block_x] = 'C';
  
  push_node(&letters_head, 2, 13);
  push_node(&letters_head, 6, 13);
  
  // Don't call search initially - let player move the block
}
#endif

#if TEST == 12
// Test 12: Timer and automatic falling
void init_game(void)
{
  init_bag();
  letters_head = NULL;
  
  // Set timer to almost done
  mov_counter = 1; // Will trigger on next frame
  
  // Place a falling block
  block_y = 0;
  block_x = 3;
  map[block_y][block_x] = 'C';
  
  // Place obstacles below
  map[13][3] = 'X';
  map[13][4] = 'Y';
  push_node(&letters_head, 3, 13);
  push_node(&letters_head, 4, 13);
}
#endif

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
}
void erase_blocks(void)
{
  for(int n = 0;n<found_words_counter;++n)
    {	
      short dir = found_words_data[n].dir;
      int x     = found_words_data[n].x;
      int y     = found_words_data[n].y;
      int len   = strlen(found_words[n]);
      score     += len*10;
      
      if(dir == RIGHT)
	{
	  for(int i = x;i<x+len;i++)
	    {
	      map[y][i] = '\0';
	      letters_head = remove_by_value(letters_head,i,y);
	    }
	}
      
      if(dir == LEFT)
	{
	  for(int i = 0;i<len;++i)
	    {
	      map[y][x-i] = '\0';
	      letters_head = remove_by_value(letters_head,x-i,y);
	    }
	}
      
      if(dir == UP)
	{
	  printf("%s %d y=%d\n",found_words[n],len,y);	  
	  for(int i =0;i<len;++i)
	    {
	      map[y-i][x] = '\0';
	      letters_head = remove_by_value(letters_head,x,y-i);
	    }
	}

      if(dir == DOWN)
	{
	  for(int i =y;i<y+len;++i)
	    {
	      map[i][x] = '\0';
	      letters_head = remove_by_value(letters_head,x,i);
	      }
	}
      if(dir == LEFT_DOWN)
	{
	  map[y][x] = '\0';
	  ++y;
	  for(int i = 0;i<len-1;++i)
	    {
	      map[y][x-i] = '\0';
	      letters_head = remove_by_value(letters_head,x-i,y);
	    }
	}
      if(dir == RIGHT_DOWN)
	{
	  map[y][x] = '\0';
	  ++y;
	  for(int i = 0;i<len-1;++i)
	    {
	      map[y][x+i] = '\0';
	      letters_head = remove_by_value(letters_head,x+i,y);
	    }
	}
      if(dir == LEFT_UP)
	{
	  map[y][x] = '\0';
	  --y;
	  for(int i = 0;i<len-1;++i)
	    {
	      map[y][x-i] = '\0';
	      letters_head = remove_by_value(letters_head,x-i,y);
	    }
	}
      if(dir == RIGHT_UP)
	{
	  map[y][x] = '\0';
	  --y;
	  for(int i = 0;i<len-1;++i)
	    {
	      map[y][x+i] = '\0';
	      letters_head = remove_by_value(letters_head,x+i,y);
	    }
	}


    }
  found_words_counter = 0;
}
void reupdate_blocks(void)
{
  bool moved;
  
  do {
    moved = false;
    VertexListNode* current = letters_head;
    while(current != NULL)
    {
      if(current->y < 13)
      {
        int new_y = current->y;
        
        while(new_y < 13 && map[new_y + 1][current->x] == '\0')
        {
          new_y++;
        }
        
        if(new_y > current->y)
        {
          char letter = map[current->y][current->x];
          
          map[current->y][current->x] = '\0';
          
          current->y = new_y;        
          map[current->y][current->x] = letter;
          
          moved = true;
        }
      }
      current = current->next;
    }
  } while(moved);
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
	  DrawText(str,start_x,start_y+(i*50),32,WHITE);	  
	}
    }
}
