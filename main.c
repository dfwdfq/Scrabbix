#include<raylib.h>
#include"constants.h"
#include"game.h"

int main()
{
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
