#include "gb_palette.h"

void draw_vignette(void)
{
  int margin = 100;
  
  DrawRectangleGradientV(0, 0, WINDOW_WIDTH, margin,
			 (Color){0, 0, 0, 120},
			 (Color){0, 0, 0, 0});
  
  DrawRectangleGradientV(0, WINDOW_HEIGHT - margin, WINDOW_WIDTH, margin,
			 (Color){0, 0, 0, 0},
			 (Color){0, 0, 0, 120});
  
  DrawRectangleGradientH(0, 0, margin, WINDOW_HEIGHT,
			 (Color){0, 0, 0, 120},
			 (Color){0, 0, 0, 0});
    
  DrawRectangleGradientH(WINDOW_WIDTH - margin, 0, margin, WINDOW_HEIGHT,
			 (Color){0, 0, 0, 0},
			 (Color){0, 0, 0, 120});
}
