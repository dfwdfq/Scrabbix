#include<raylib.h>
#include<stdlib.h>
#include<stdbool.h>
#include"constants.h"
#include"gb_palette.h"
#include"game.h"

void run(void);
int main()
{

  qsort(google_words, google_words_len, sizeof(char*), str_cmp);

  SetConfigFlags(FLAG_VSYNC_HINT);
  InitWindow(WINDOW_WIDTH,WINDOW_HEIGHT,"Scrabrix");
  SetExitKey(KEY_NULL);
  SetTargetFPS(60);
  
  init_map();
  init_game();
  load_fonts();
  while(!WindowShouldClose())
    {
      run();

#if PRINT_FPS== 1     
      static double last_time = 0;
      double now = GetTime();
      double dt = now - last_time;
      if (dt > 0.0)
	{
	  printf("FPS: %.1f\n", 1.0 / dt);
	}
      last_time = now;
#endif

      WaitTime(0);
    }
  free_game();
  unload_fonts();
  UnloadTexture(vignette_tex);
  UnloadTexture(scanlines_tex);
  CloseWindow();
  return 0;
}
void run()
{  
  if(IsKeyReleased(KEY_ESCAPE))
    _pause = !_pause;
  
  if(!_pause && !victory && !game_over)
    run_game();

  if(game_over  && IS_GAME_OVER_TIMER_DONE)
    {
      if(IsKeyReleased(KEY_R))
	{
	  reset_game();
	}
    }
  if(victory && victory_timer >= VICTORY_PROMPT_START)
    {
      if(IsKeyReleased(KEY_R))
	{
	  reset_game();
	}
    }
  
  BeginDrawing();
  ClearBackground(GB_DMG_DARKEST);
  draw_game();
  if(game_over)
    draw_game_over();
  if(victory)
    draw_victory();
  EndDrawing();

}
