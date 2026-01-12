#include<raylib.h>
#include<stdlib.h>
#include<stdbool.h>
#include"constants.h"
#include"game.h"

int main()
{
#if USE_BINARY_SEARCH == 1
    qsort(google_words, google_words_len, sizeof(char*), str_cmp);
#endif

  InitWindow(WINDOW_WIDTH,WINDOW_HEIGHT,"Scrabrix");
  SetExitKey(KEY_NULL);
  SetTargetFPS(60);
  
  init_map();
  init_game();
  load_fonts();
  while(1)
    {
      if(WindowShouldClose())break;
      
      if(IsKeyReleased(KEY_ESCAPE))
	_pause = !_pause;
      
      if(!_pause && !victory && !game_over)
	run_game();
      
      BeginDrawing();
      ClearBackground(BLACK);
      draw_game();
      EndDrawing();
      
    }
  free_game();
  unload_fonts();
  CloseWindow();
  return 0;
}
