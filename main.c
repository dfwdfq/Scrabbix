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


  InitWindow(WINDOW_WIDTH,WINDOW_HEIGHT,"Scrabrix");
  SetExitKey(KEY_NULL);
  SetTargetFPS(60);
  
  init_map();
  init_game();
  load_fonts();
  while(!WindowShouldClose())
    {
      run();
    }
  free_game();
  unload_fonts();
  CloseWindow();
  return 0;
}
void run()
{  
  if(IsKeyReleased(KEY_ESCAPE))
    _pause = !_pause;
  
  if(!_pause && !victory && !game_over)
    run_game();
  
  BeginDrawing();
  ClearBackground(GB_DMG_DARKEST);
  draw_game();
  EndDrawing();

}
