#include"game.h"

VertexListNode* letters_head;
int score = 0;
bool _pause = false;
bool victory = false, game_over=false;
int combo = 0;
int max_combo = 0;

int lock_flash_x = -1;
int lock_flash_y = -1;
int lock_flash_timer = 0;

char found_words_labels[MAX_FOUND_WORDS_SIZE][FOUND_WORD_LEN];
int found_words_labels_counter = 0;
Color fading_w_color = (Color){255,255,255,255};

Font font;

void load_fonts(void)
{
  font = LoadFontFromMemory(".otf",Hardpixel_OTF,Hardpixel_OTF_len,48,NULL,0);
}
void unload_fonts(void)
{
  UnloadFont(font);
}

void free_game(void)
{
  clear_VertexList(letters_head);
}
void hard_drop(void)
{
    if (block_y == -1) return;

    int drop_distance = 0;

    while (block_y < MAP_HEIGHT - 1 &&
           map[block_y + 1][block_x] == '\0')
    {
        char val = map[block_y][block_x];
        map[block_y][block_x] = '\0';
        map[++block_y][block_x] = val;
        drop_distance++;
    }

    score += drop_distance * 2;
    RESET_MOV_TIMER;
}
int get_ghost_y(void)
{
  if (block_y == -1) return -1;
  
  int y = block_y;
  
  while (y < MAP_HEIGHT - 1 &&
	 map[y + 1][block_x] == '\0')
    {
      y++;
    }
  
  return y;
}
void draw_ghost_block(Font *font)
{
    if (block_y == -1) return;

    int ghost_y = get_ghost_y();
    if (ghost_y == block_y) return;

    char letter = map[block_y][block_x];

    Color ghost_color = (Color){255, 255, 255, 80};

    Vector2 text_size = MeasureTextEx(*font, TextFormat("%c", letter), 44, 0);
    
      
    Vector2 pos = {
      GPX(block_x) + (CELL_SIZE - text_size.x) / 2,
      GPY(ghost_y)
    };

    DrawTextEx(*font,
               TextFormat("%c", letter),
               pos,
               CELL_SIZE,
               0.0f,
               ghost_color);
}

void handle_keys(void)
{
    static float move_cooldown = 0.0f;
    const float initial_delay = 0.25f;
    const float repeat_delay = 0.08f;
    static bool key_was_down = false;

    if (block_y == -1) return;

    float dt = GetFrameTime();
    if(IsKeyPressed(KEY_SPACE))
      {
	hard_drop();
	return;
      }
    bool key_down = 
        IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT) ||
        IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT) ||
        IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN) ||
      IsKeyDown(KEY_SPACE);

    if (!key_down)
      {
        move_cooldown = 0.0f;
        key_was_down = false;
        return;
      }

    if (!key_was_down)
      {
        move_cooldown = initial_delay;
        key_was_down = true;
        try_move();
        return;
      }

    move_cooldown -= dt;
    if (move_cooldown <= 0.0f)
      {
        move_cooldown = repeat_delay;
        try_move();
      }
}

void try_move(void)
{
    if ((IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) && 
        block_x > 0 && map[block_y][block_x-1] == '\0')
      {
        char val = map[block_y][block_x];
        map[block_y][block_x] = '\0';
        map[block_y][--block_x] = val;
        return;
      }

    if ((IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) && 
        block_x < MAP_WIDTH-1 && map[block_y][block_x+1] == '\0')
      {
        char val = map[block_y][block_x];
        map[block_y][block_x] = '\0';
        map[block_y][++block_x] = val;
        return;
      }

    if ((IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) && 
        block_y < MAP_HEIGHT-1 && map[block_y+1][block_x] == '\0')
      {
        char val = map[block_y][block_x];
        map[block_y][block_x] = '\0';
        map[++block_y][block_x] = val;
        return;
      }
}

void increase_complexity(void)
{
  //yeah, kinda tricky
  int level = floor(sqrt(score / 150.0));
  mov_timer = fmax(60 - level * 4, 18);

  if (found_words_counter == 0)
    {
      if (score >= 2000)
	min_word_len = 5;
      else if (score >= 500)
	min_word_len = 4;
      else
	min_word_len = 3;
    }  
}
void draw_lock_flash(void)
{
  if (lock_flash_timer <= 0) return;
  
  char letter = map[lock_flash_y][lock_flash_x];  
  Color flash_color = (Color){255, 255, 255, 255};
  Vector2 text_size = MeasureTextEx(font, TextFormat("%c", letter), 44, 0);

    Vector2 pos = {
      GPX(lock_flash_x) + (CELL_SIZE - text_size.x) / 2,
      GPY(lock_flash_y)      
    };

    DrawTextEx(font,
               TextFormat("%c", letter),
               pos,
               CELL_SIZE,
               0.0f,
               flash_color);

    lock_flash_timer--;
}

void run_game(void)
{  
  handle_keys();
  
  //this fancy-pancy hack prevents block from being moved when it get stucked
  if(map[block_y+1][block_x] != '\0' ||
     block_y == MAP_HEIGHT-1)
    {
      lock_flash_x = block_x;
      lock_flash_y = block_y;
      lock_flash_timer = 4;
    
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
    if (found_words_counter > 0)
      {
	combo++;
	if (combo > max_combo)
	  max_combo = combo;
      }

    
    RESET_ER_TIMER;
    printf("before:\n");
    print_list(letters_head);
    printf("\n\n");

    erase_blocks();
    reupdate_blocks();
    printf("after!:\n");
    print_list(letters_head);
    printf("\n\n");
    if(IS_FOUND_TIMER_DONE)
      {
	found_words_counter = 0;
	RESET_FOUND_TIMER;
      }
  }

  increase_complexity();
}
void draw_game(void)
{
  //draw_borders();
  draw_gb_borders();
  draw_map(&font);
  draw_lock_flash();
  draw_ghost_block(&font);  
  draw_labels();
  draw_found_words();
  draw_vignette();
  draw_scanlines(10000);
  draw_pixel_grid();
}
void draw_labels(void)
{
  //DrawText("next:",570,250,32,WHITE);
  DrawTextEx(font,"next:",(Vector2){520,260},44,0.0f,WHITE);    
  draw_gb_block_next(620,255,bag[current_letter],&font,1);


  DrawTextEx(font,"Scrabbix",(Vector2){480,20},64,0.0f,WHITE);

  char score_line[7] = {'0','0','0','0','0','0','\0'};
  char score_str[6];
  sprintf(score_str,"%d",score);
  int j = 0;
  for(int i = 6-strlen(score_str);i<6;++i)
    {
     score_line[i] = score_str[j++];     
    }
  char _score[30];
  sprintf(_score,"score: %s",score_line);
  //DrawText(_score,550,200,32,WHITE);
  DrawTextEx(font,_score,(Vector2){500,200},44,0.0f,WHITE);

  DrawTextEx(font,TextFormat("min: %d+",min_word_len),(Vector2){535,330},44,0.0f,WHITE);
  
  if(_pause)
    {
      //DrawText("paused!",550,840,48,WHITE);
      DrawTextEx(font,"paused!",(Vector2){500,600},48,0.0f,WHITE);
    }
}

void draw_found_words(void)
{
  char str[40];
  if(found_words_labels_counter == 0)return;
  if(!(IS_FOUND_TIMER_DONE))
    {
      UPDATE_FOUND_TIMER;
      int start_x = 500;
      int start_y = 390;
      for(int i = 0;i<found_words_labels_counter;++i)
	{
	  sprintf(str,"%s found!\n",found_words_labels[i]);
	  DrawTextEx(font,str,(Vector2){start_x,start_y+(i*50)},48,0.0f,fading_w_color);	  
	}
      
      fading_w_color.a-=1;
    }
}
