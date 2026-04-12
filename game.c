#include"game.h"

#if PRINT_DEBUG_MAP == 0
bool dump_map = false;
#endif


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

int reupdate_delay = 0;

int death_flash_timer = 4;

char found_words_labels[MAX_FOUND_WORDS_SIZE][FOUND_WORD_LEN];
int found_words_labels_counter = 0;
Color fading_w_color = (Color){255,255,255,255};

Font font;

Sound move_sound,
  hard_drop_sound,
  soft_land_sound,
  word_found_sound,
  word_erase_sound,
  perfect_sound,
  combo_sound,
  pause_sound,
  victory_sound,
  game_over_sound;

void load_fonts(void)
{
  font = LoadFontFromMemory(".otf",Hardpixel_OTF,Hardpixel_OTF_len,48,NULL,0);

  move_sound = create_move_sound();
  SetSoundVolume(move_sound, 0.5f);

  hard_drop_sound = create_hard_drop_sound();
  SetSoundVolume(hard_drop_sound, 1.0f);

  soft_land_sound = create_soft_land_sound();
  SetSoundVolume(soft_land_sound, 1.0f);

  word_found_sound = create_word_found_sound();
  SetSoundVolume(word_found_sound, 0.4f);

  word_erase_sound = create_word_erase_sound();
  SetSoundVolume(word_erase_sound, 0.4f);

  perfect_sound = create_perfect_clear_sound();
  SetSoundVolume(perfect_sound, 0.6f);

  combo_sound = create_combo_sound();
  SetSoundVolume(combo_sound, 0.8f);

  pause_sound = create_pause_sound();
  SetSoundVolume(pause_sound, 0.5f);

  victory_sound = create_victory_sound();
  SetSoundVolume(victory_sound, 0.7f);

  game_over_sound = create_game_over_sound();
  SetSoundVolume(game_over_sound,0.6f);
}
void unload_fonts(void)
{
  UnloadFont(font);
  UnloadSound(move_sound);
  UnloadSound(hard_drop_sound);
  UnloadSound(soft_land_sound);
  UnloadSound(word_found_sound);
  UnloadSound(word_erase_sound);
  UnloadSound(perfect_sound);
  UnloadSound(combo_sound);
  UnloadSound(victory_sound);
  UnloadSound(game_over_sound);
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

    score += drop_distance * 0.2;
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
    if(found_words_counter > 0) return;

    float dt = GetFrameTime();
    if(IsKeyPressed(KEY_SPACE))
      {
	PlaySound(hard_drop_sound);
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
	SetSoundPan(move_sound,0.0f);
	PlaySound(move_sound);
        return;
      }

    if ((IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) && 
        block_x < MAP_WIDTH-1 && map[block_y][block_x+1] == '\0')
      {
        char val = map[block_y][block_x];
        map[block_y][block_x] = '\0';
        map[block_y][++block_x] = val;

	SetSoundPan(move_sound,1.0f);
	PlaySound(move_sound);
        return;
      }
}

void increase_complexity(void)
{
  //yeah, kinda tricky
  int level = floor(sqrt(score / 100.0));
  mov_timer = fmax(30 - level * 4, 14);
  
#if TEST == 0      
  if (found_words_counter == 0)
    {
      if (score >= 2000)
	min_word_len = 5;
      else if (score >= 500)
	min_word_len = 4;
      else
	min_word_len = 3;
    }
#endif  
}

void run_game(void)
{  
    if (hitstop_counter > 0)
    {
        hitstop_counter--;
        return;//freeze game briefly after word detection
    }

    if (perfect_display)
        return;//freeze game while "PERFECT!" is shown

    handle_keys();

    //---Block placement (when current block can no longer move) ---
    if (block_y != -1)//only if a block exists
    {
        if (map[block_y + 1][block_x] != '\0' || block_y == MAP_HEIGHT - 1)
        {

#if PRINT_DEBUG	== 1
#if PRINT_DEBUG_MAP == 1	  
	  dump_map = true;
#endif
#endif
	  PlaySound(soft_land_sound);
	  //fix block in place
	  push_node(&letters_head, block_x, block_y);

	  block_x = -1;
	  block_y = -1;

	  //prevent problem, when word is not erased
	  if(found_words_counter == 0)
	    {
	      search(letters_head);//look for words
	    }
	  
	  generate_random_start_pos();

	  if(map[block_y][block_x] == '\0')
	    {
	      map[block_y][block_x] = get_next_letter();
	    }
	  else
	    {
	      game_over = true;
	      PlaySound(game_over_sound);
	    }
        }
    }

    //--- Automatic downward movement (gravity) ---
    UPDATE_MOV_TIMER;
    if (IS_MOV_TIMER_DONE)
    {
        RESET_MOV_TIMER;
        update_map();
    }

    //--- word discovery -> start erase timer and copy words for display ---
    if (found_words_counter > 0)
    {
        UPDATE_ER_TIMER;
        fading_w_color = (Color){255, 255, 255, 255};
        found_words_labels_counter = found_words_counter;

        for (int i = 0; i < found_words_labels_counter; ++i)
            strcpy(found_words_labels[i], found_words[i]);

        hitstop_counter = 3;//brief freeze for visual feedback
	PlaySound(word_found_sound);
    }

    // --- Erase words when erase timer expires ---
    if (IS_ER_TIMER_DONE)
    {
      if (found_words_counter > 0)
        {
	  combo = found_words_counter;//number of words in this batch
	  if (combo > max_combo)
	    max_combo = combo;
	  
	  if (combo >= 2)
	    {
	      sprintf(combo_message, "combo %dx!", combo);
	      PlaySound(combo_sound);
	      combo_timer = 60;//show combo for 1 second (60 frames)
	    }
        }

      PlaySound(word_erase_sound);
        RESET_ER_TIMER;

#if PRINT_DEBUG == 1
	DEBUG_PRINT(ANSI_RESET, "letters list before erasing:\n");
        print_list(letters_head,map);
	DEBUG_PRINT(ANSI_RESET,"end of list.\n");
#endif
        erase_blocks();//remove the found words

#if PRINT_DEBUG == 1	
	DEBUG_PRINT(ANSI_RESET,"letters list before erasing:\n");
	print_list(letters_head,map);
	DEBUG_PRINT(ANSI_RESET,"end of list.\n");
#endif
	
        //Start the delay before blocks re‑fall
        reupdate_delay = 10;//10 frames ~ 0.17 seconds at 60 FPS

        if (IS_FOUND_TIMER_DONE)
        {
            found_words_counter = 0;
            RESET_FOUND_TIMER;
        }
    }

    //---Reupdate delay: wait a moment, then let blocks fall ---
    if (reupdate_delay > 0)
    {
        reupdate_delay--;
        if (reupdate_delay == 0)
        {
            reupdate_blocks();//blocks drop to fill gaps
            letters_head = clear_list(letters_head);//clean up empty nodes

            if (letters_head == NULL && !perfect_display)
            {
	      PlaySound(perfect_sound);
	      perfect_display = true;
	      perfect_timer = 60;//show "PERFECT!" for 1 second
            }
        }
    }

    increase_complexity();//adjust speed and min word length
#if PRINT_DEBUG == 1    
#if PRINT_DEBUG_MAP == 1
    if(dump_map)
      {
	DEBUG_PRINT(ANSI_RESET,"map dump start:\n\n");
	for(int y = 0;y<MAP_HEIGHT;++y)
	  {
	    for(int x = 0;x<MAP_WIDTH;++x)
	      {
		char el = map[y][x];
		if(el != '\0')
		  printf("%c",map[y][x]);
		else
		  printf("_");
	      }
	    printf("\n");
	  }
	dump_map = false;
	DEBUG_PRINT(ANSI_RESET,"map dump end.\n\n");
      }    
      
#endif
#endif
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
    draw_scanlines();
    draw_pixel_grid();
}
void draw_labels(void)
{
  //prevent one tricky problem
  char next_letter = '?';
  if (current_letter < 98)
    next_letter = bag[current_letter];
  
  DrawTextEx(font,"next:",(Vector2){520,260},44,0.0f,WHITE);    
  draw_gb_block_next(620,255,next_letter,&font,1);


  DrawTextEx(font,"Scrabbix",(Vector2){480,20},64,0.0f,WHITE);

  char score_line[7] = {'0','0','0','0','0','0','\0'};
  char score_str[6];
  if(score >= SCORE_CAP && !victory)
    {
      victory = true;
      victory_timer = 0;
      printf("VICTORY!!!!!!!!!\n");
      PlaySound(victory_sound);
    }
  else
    {
      sprintf(score_str,"%d",score);
      int j = 0;
      int i = 6-strlen(score_str);
      for(i;i<6;++i)
	{
	  score_line[i] = score_str[j++];     
	}
      char _score[30];
      sprintf(_score,"score: %s",score_line);
      //DrawText(_score,550,200,32,WHITE);
      DrawTextEx(font,_score,(Vector2){500,200},44,0.0f,WHITE);
    }

  DrawTextEx(font,TextFormat("min: %d",min_word_len),(Vector2){535,330},44,0.0f,WHITE);
  
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
      if(!_pause)
	UPDATE_FOUND_TIMER;
      
      int start_x = 500;
      int start_y = 390;
      for(int i = 0;i<(found_words_labels_counter>3?3:found_words_labels_counter);++i)
	{
	  sprintf(str,"%s found!\n",found_words_labels[i]);	 
	  DrawTextEx(font,str,(Vector2){start_x,start_y+(i*50)},48,0.0f,fading_w_color);	  
	}

      if(!_pause)
	{
	  if (fading_w_color.a > 2)
	    fading_w_color.a -= 2;
	  else
	    fading_w_color.a = 0;
	}
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

      if(!_pause)
	combo_timer--;
      if (combo_timer <= 0) combo_phase = 0.0f;
    }
}
void draw_victory(void)
{
  UPDATE_VICTORY_TIMER;

  //phase 1
  if (victory_timer <= VICTORY_FLASH_FRAMES)
    {
      int alpha = 200 - (victory_timer * (200 / VICTORY_FLASH_FRAMES));
      DrawRectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
		    (Color){GB_DMG_LIGHTEST.r, GB_DMG_LIGHTEST.g, GB_DMG_LIGHTEST.b, alpha});
    }
    else if (victory_timer <= VICTORY_GLOW_END)//phase 2
    {
        float t = (victory_timer - VICTORY_GLOW_START) * 0.3f;//speed factor
        int alpha = 40 + (int)(sinf(t) * 10);
        DrawRectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
                      (Color){GB_DMG_LIGHTEST.r, GB_DMG_LIGHTEST.g, GB_DMG_LIGHTEST.b, alpha});
    }


    //phase 3
  if (victory_timer >= VICTORY_TEXT_START)
    {
      const char* msg = "VICTORY";
      float base_size = 64.0f;
      float scale;
      if (victory_timer <= VICTORY_TEXT_END)
        {
	  
	  float progress = (float)(victory_timer - VICTORY_TEXT_START) / (VICTORY_TEXT_END - VICTORY_TEXT_START);
	  scale = 1.2f - (0.2f * progress);
        }
      else
        {
	  scale = 1.0f;
        }
      float current_size = base_size * scale;
      Vector2 text_size = MeasureTextEx(font, msg, current_size, 0);
      int centerX = WINDOW_WIDTH / 2;
      int y = WINDOW_HEIGHT / 2 - 80;
      DrawTextEx(font, msg,
		 (Vector2){centerX - text_size.x/2, y},
		 current_size, 0, WHITE);
    }

  //phase 4
  if (victory_timer >= VICTORY_STATS_START)
    {
      int stats_alpha;
      if (victory_timer <= VICTORY_STATS_END)
        {
	  float progress = (float)(victory_timer - VICTORY_STATS_START) / (VICTORY_STATS_END - VICTORY_STATS_START);
	  stats_alpha = (int)(255 * progress);
        }
      else
        {
	  stats_alpha = 255;
        }
      char score_str[64];
      sprintf(score_str, "SCORE: %d", score);
      char combo_str[64];
      sprintf(combo_str, "MAX COMBO: %d", max_combo);
      
      int fontSize = 32;
      Vector2 score_size = MeasureTextEx(font, score_str, fontSize, 0);
      Vector2 combo_size = MeasureTextEx(font, combo_str, fontSize, 0);
      int centerX = WINDOW_WIDTH / 2;
      int y = WINDOW_HEIGHT / 2 + 20;

      DrawTextEx(font, score_str,
		 (Vector2){centerX - score_size.x/2, y},
		 fontSize, 0, (Color){255,255,255, stats_alpha});
      DrawTextEx(font, combo_str,
		 (Vector2){centerX - combo_size.x/2, y + 40},
		 fontSize, 0, (Color){255,255,255, stats_alpha});
    }

  
  if (victory_timer >= VICTORY_PROMPT_START)
    {
      const char* prefix = "press ";
      const char* blink_char = "R";
      const char* suffix = " to restart";
      
      Vector2 prefix_size = MeasureTextEx(font, prefix, 36, 0);
      Vector2 blink_size = MeasureTextEx(font, blink_char, 36, 0);
      Vector2 suffix_size = MeasureTextEx(font, suffix, 36, 0);

      int centerX = WINDOW_WIDTH / 2;
      float total_width = prefix_size.x + blink_size.x + suffix_size.x;
      float start_x = centerX - total_width / 2;
      int y_pos = WINDOW_HEIGHT - 60;
      
      DrawTextEx(font, prefix, (Vector2){start_x, y_pos}, 36, 0, WHITE);
      
      static int blink_frame = 0;
      blink_frame = (blink_frame + 1) % 20;
      Color blink_color = (blink_frame < 10) ? WHITE : (Color){255, 255, 255, 100};	  
      DrawTextEx(font, blink_char, (Vector2){start_x + prefix_size.x, y_pos}, 36, 0, blink_color);
      DrawTextEx(font, suffix, (Vector2){start_x + prefix_size.x + blink_size.x, y_pos}, 36, 0, WHITE);
    }
}
void draw_game_over(void)
{
  if (death_flash_timer > 0)
    {
      float t = (float)death_flash_timer / 4;
      unsigned char alpha = (unsigned char)(255 * t);
      
      Color flash;

      if (death_flash_timer > 2)
        flash = GB_DMG_LIGHTEST;
      else
        flash = GB_DMG_DARK;

      flash.a = alpha;
      DrawRectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, flash);
    
      death_flash_timer--;
    }
  if(!IS_GAME_OVER_TIMER_DONE)
    UPDATE_GAME_OVER_TIMER;

  float alpha_factor = (float)game_over_timer / 50;
  alpha_factor = 1.0f - (1.0f - alpha_factor) * (1.0f - alpha_factor); 
  if (alpha_factor > 1.0f) alpha_factor = 1.0f;
  unsigned char overlay_alpha = (unsigned char)(230 * alpha_factor);
  
  DrawRectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
		(Color){0, 0, 0, overlay_alpha});
      
  static const char* msg1 = "OUT OF SPACE";
  char* msg2 = TextFormat("SCORE: %d", score);

      
  Vector2 size1 = MeasureTextEx(font, msg1, 48, 0);
  Vector2 size2 = MeasureTextEx(font, msg2, 48, 0);

  int centerX = WINDOW_WIDTH / 2;
  int startY = WINDOW_HEIGHT / 2 - 80;

  DrawTextEx(font, msg1,
	     (Vector2){centerX - size1.x/2, startY},
	     48, 0, WHITE);
  
  DrawTextEx(font, msg2,
	     (Vector2){centerX - size2.x/2, startY + 60},
	     48, 0, WHITE);
      //}

  if (IS_GAME_OVER_TIMER_DONE)
    {
      const char* prefix = "press ";
      const char* blink_char = "R";
      const char* suffix = " to restart";
      
      Vector2 prefix_size = MeasureTextEx(font, prefix, 36, 0);
      Vector2 blink_size = MeasureTextEx(font, blink_char, 36, 0);
      Vector2 suffix_size = MeasureTextEx(font, suffix, 36, 0);
      
      float total_width = prefix_size.x + blink_size.x + suffix_size.x;
      float start_x = centerX - total_width / 2;
      float y_pos = startY + 140;
      
      DrawTextEx(font, prefix, (Vector2){start_x, y_pos}, 36, 0, WHITE);
      
      static int blink_frame = 0;
      blink_frame = (blink_frame + 1) % 20;
      Color blink_color = (blink_frame < 10) ? WHITE : (Color){255, 255, 255, 100};	  
      DrawTextEx(font, blink_char, (Vector2){start_x + prefix_size.x, y_pos}, 36, 0, blink_color);
      DrawTextEx(font, suffix, (Vector2){start_x + prefix_size.x + blink_size.x, y_pos}, 36, 0, WHITE);
    }
}
void reset_game(void)
{
  free_game();
  init_map();
  init_game();
  
  score = 0;
  _pause = false;
  victory = false;
  game_over = false;
  combo = 0;
  max_combo = 0;
  combo_timer = 0;
  //TODO: combo_message
  //update on TODO
  /*
    combo_message is simply overwritten,
    so no need to nullify it
  */  
  combo_phase = 0.0f;
  hitstop_counter = 0;
  last_drop_x = -1;
  last_drop_y = -1;
  hard_drop_glow = 0.0f;
  perfect_display = false;
  perfect_timer = 0;
  perfect_phase = 0.0f;
  reupdate_delay = 0;
  death_flash_timer = 4;
  found_words_labels_counter = 0;
  //TODO: found_words_labels
  //update on TODO
  /*
    i think there is no need to reset this array, because
    new values are overwritten, so need to nullify them manually
  */
  fading_w_color.r = 255;
  fading_w_color.g = 255;
  fading_w_color.b = 255;
  fading_w_color.a = 255; 
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
