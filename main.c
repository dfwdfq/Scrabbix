#include<raylib.h>
#include"game.h"

int main()
{
  InitWindow(800,640,"Scrabble");
  SetTargetFPS(60);


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
