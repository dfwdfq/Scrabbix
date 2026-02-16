#include"game.h"

VertexListNode* letters_head;
int score = 0;
bool _pause = false;
bool victory = false, game_over=false;
int combo = 0;
int max_combo = 0;

char combo_message[40] = "";
int combo_timer = 0;
float combo_phase = 0.0f;

int hitstop_counter = 0;

int last_drop_x = -1, last_drop_y = -1;
float hard_drop_glow = 0.0f;

bool perfect_display = false;
int perfect_timer = 0;
float perfect_phase = 0.0f;

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

    last_drop_x = block_x;
    last_drop_y = block_y;
    hard_drop_glow = 0.2f;  
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
}

void increase_complexity(void)
{
  //yeah, kinda tricky
  int level = floor(sqrt(score / 100.0));
  mov_timer = fmax(30 - level * 4, 14);
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

void run_game(void)
{
  if (hitstop_counter > 0)
    {
      hitstop_counter--;
      return;//skip logic for a moment
    }
  if(perfect_display)
    return;
  
  handle_keys();
  
  
  if(block_y != -1) //this is another hack and .... well, it fixes some obscure shit
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
      hitstop_counter = 3;
    }

  //erase words
  if(IS_ER_TIMER_DONE)
  {
    if (found_words_counter > 0)
      {
	printf("here! %d\n",found_words_counter);
	combo = found_words_counter;
	if (combo > max_combo)
	  max_combo = combo;

	if(combo >= 2)
	  {
	    printf("combo!!!!\n");
	    sprintf(combo_message, "combo %dx!", combo);
	    combo_timer = 60;   
	  }
      }

    
    RESET_ER_TIMER;
    printf("before:\n");
    print_list(letters_head);
    printf("\n\n");

    erase_blocks();
    reupdate_blocks();
    letters_head = clear_list(letters_head);
    if (letters_head == NULL && !perfect_display)
      {
	perfect_display = true;
	perfect_timer = 60;  
    }
    
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
  draw_gb_borders();
  draw_map(&font);
  draw_ghost_block(&font);
  if (hard_drop_glow > 0.0f && last_drop_x >= 0 && last_drop_y >= 0)
    {
      float t = hard_drop_glow * 30.0f;        
      float intensity = sinf(t) * 0.5f + 0.5f;

      Color glow_color = {255, 255, 255, (unsigned char)(intensity * 200)};
      DrawRectangle(GPX(last_drop_x), GPY(last_drop_y), CELL_SIZE, CELL_SIZE, glow_color);
      
      hard_drop_glow -= GetFrameTime(); 
      if (hard_drop_glow <= 0.0f)
	last_drop_x = last_drop_y = -1;
    }

  if (perfect_display)
    {
      const char* msg = "PERFECT!";
      perfect_phase += GetFrameTime() * 10.0f;
      
      float pulse = sinf(perfect_phase);      
      float scale = 1.0f + pulse * 0.1f;      
      float alpha = 200 + pulse * 55;         
      
      Color glow_color = GOLD;
      glow_color.a = (unsigned char)alpha;

      float base_size = 72.0f;
      float current_size = base_size * scale;
      Vector2 text_size = MeasureTextEx(font, msg, current_size, 0);
      Vector2 pos = { (WINDOW_WIDTH - text_size.x) / 2, (WINDOW_HEIGHT - text_size.y) / 2 };
      

      Vector2 shadow_pos = { pos.x + 4, pos.y + 4 };
      DrawTextEx(font, msg, shadow_pos, current_size, 0, (Color){0,0,0,(unsigned char)(alpha/2)});

      DrawTextEx(font, msg, pos, current_size, 0, glow_color);
      
      perfect_timer--;
      if (perfect_timer <= 0) perfect_display = false;
    }
  
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
 if (found_words_labels_counter == 0 && combo_timer == 0) return;
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
      
      fading_w_color.a-=2;
    }


  if (combo_timer > 0)
    {
      combo_phase += GetFrameTime() * 6.0f;          

      float base_size = 56.0f;
      float pulse = sinf(combo_phase) * 3.0f;        
      float current_size = base_size + pulse;

      float alpha_factor = (float)combo_timer / 100.0f;
      Color combo_color = GOLD;
      combo_color.a = (unsigned char)(255 * alpha_factor);

      Vector2 pos = { 500, 360 + (found_words_labels_counter + 1) * 50 };

      Color shadow_color = {0, 0, 0, combo_color.a / 2};
      Vector2 shadow_pos = { pos.x + 4, pos.y + 4 };
      DrawTextEx(font, combo_message, shadow_pos, current_size, 0, shadow_color);

      DrawTextEx(font, combo_message, pos, current_size, 0, combo_color);

      combo_timer--;
      if (combo_timer <= 0) combo_phase = 0.0f;
    }
}
VertexListNode* clear_list(VertexListNode* head)
{
  VertexListNode* current = head;
  VertexListNode* prev = NULL;

  while (current != NULL)
    {
      VertexListNode* next = current->next;
      
      if (map[current->y][current->x] == '\0')
        {
	  if (prev == NULL)
	    {
	      head = next;
            }
	  else
	    {
	      prev->next = next;
            }
	  free(current);
        }
      else
        {
	  prev = current;
        }
      
      current = next;
    }
  
  return head;
}
