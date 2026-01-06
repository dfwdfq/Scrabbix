#include<raylib.h>
#include<stdlib.h>
#include"constants.h"
#include"game.h"

int main()
{
#if USE_BINARY_SEARCH == 1
    qsort(google_words, google_words_len, sizeof(char*), str_cmp);
#endif
  
  InitWindow(WINDOW_WIDTH,WINDOW_HEIGHT,"Scrabrix");
  SetTargetFPS(60);

  init_map();
  init_game();
  while(!WindowShouldClose())
    {
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
