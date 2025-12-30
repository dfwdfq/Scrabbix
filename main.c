#include<raylib.h>
#include"game.h"

int main()
{
  InitWindow(800,930,"Scrabrix");
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

  CloseWindow();
  return 0;
}
