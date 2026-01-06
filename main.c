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
  while(1)
    {
      if(WindowShouldClose())break;
      
      if(IsKeyReleased(KEY_ESCAPE))
	_pause = !_pause;
      
      if(!_pause)
	run_game();
      
      BeginDrawing();
      ClearBackground(BLACK);
      draw_game();
      EndDrawing();
      
    }
  free_game();
  CloseWindow();
  return 0;
}
