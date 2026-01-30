#include "gb_palette.h"

Color get_dithered_color(int x, int y, Color a, Color b)
{
  if (((x + y) & 1) == 0)
    {
      return a;
    }
  else
    {
      return b;
    }
}
void draw_vignette(void)
{
  int margin = 30;
  
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
void draw_scanlines(int scanline_height)
{
  for (int y = 0; y < WINDOW_HEIGHT; y += scanline_height * 2)
    {
      DrawRectangle(0, y + scanline_height, WINDOW_WIDTH, scanline_height, 
		    (Color){0, 0, 0, 80});
    }  
}
void draw_pixel_grid(void)
{
  int pixel_size = 2;
  for (int y = 0; y < WINDOW_HEIGHT; y += pixel_size)
    {
      for (int x = 0; x < WINDOW_WIDTH; x += pixel_size)
	{
	  DrawRectangleLines(x, y, pixel_size, pixel_size, 
			     (Color){0, 0, 0, 20});
	}
    }
}
void draw_gb_borders(void)
{
  int border_thickness = 8;
    
  DrawRectangle(BORDER_OX - border_thickness,
  		BORDER_OY - border_thickness,
  		BORDER_WIDTH + border_thickness * 2,
  		BORDER_HEIGHT + border_thickness * 2,
  		GB_DMG_DARK);
    
  DrawRectangleLinesEx((Rectangle){BORDER_OX - border_thickness + 2,
  				   BORDER_OY - border_thickness + 2,
  				   BORDER_WIDTH + border_thickness * 2 - 4,
  				   BORDER_HEIGHT + border_thickness * 2 - 4},
  2, GB_DMG_LIGHT);
    
}
void draw_gb_block(int x, int y, char letter, Font* font, bool is_falling)
{
  int screen_x = GPX(x);
  int screen_y = GPY(y);
    
  for (int dy = 0; dy < CELL_SIZE; dy += 4)
    {
      for (int dx = 0; dx < CELL_SIZE; dx += 4)
	{
	  Color fill_color;
            
	  if (is_falling)
	    {
	      fill_color = get_dithered_color(screen_x + dx, screen_y + dy,
					      GB_DMG_LIGHTEST, 
					      GB_DMG_LIGHT);
            }
	  else
	    {	     
	      fill_color = get_dithered_color(screen_x + dx, screen_y + dy,
					      GB_DMG_LIGHT,
					      GB_DMG_DARK);
            }
            
            DrawRectangle(screen_x + dx, screen_y + dy, 4, 4, fill_color);
        }
    }
    
  DrawRectangle(screen_x, screen_y, CELL_SIZE, 2, GB_DMG_LIGHTEST);
  DrawRectangle(screen_x, screen_y, 2, CELL_SIZE, GB_DMG_LIGHTEST);
    

  DrawRectangle(screen_x, screen_y + CELL_SIZE - 2, CELL_SIZE, 2, GB_DMG_DARKEST);
  DrawRectangle(screen_x + CELL_SIZE - 2, screen_y, 2, CELL_SIZE, GB_DMG_DARKEST);
    
  char letter_str[2] = {letter, '\0'};
  Vector2 text_size = MeasureTextEx(*font, letter_str, 44, 0);
    
  DrawTextEx(*font, letter_str,
	     (Vector2){screen_x + (CELL_SIZE - text_size.x) / 2,
		       screen_y + (CELL_SIZE - text_size.y) / 2 - 4},
	     44, 0, GB_DMG_DARKEST);
}
void draw_gb_block_next(int x, int y, char letter, Font* font, bool is_falling)
{
  int screen_x = x;
  int screen_y = y;
    
  for (int dy = 0; dy < CELL_SIZE; dy += 4)
    {
      for (int dx = 0; dx < CELL_SIZE; dx += 4)
	{
	  Color fill_color;
            
	  if (is_falling)
	    {
	      fill_color = get_dithered_color(screen_x + dx, screen_y + dy,
					      GB_DMG_LIGHTEST, 
					      GB_DMG_LIGHT);
            }
	  else
	    {	     
	      fill_color = get_dithered_color(screen_x + dx, screen_y + dy,
					      GB_DMG_LIGHT,
					      GB_DMG_DARK);
            }
            
            DrawRectangle(screen_x + dx, screen_y + dy, 4, 4, fill_color);
        }
    }
    
  DrawRectangle(screen_x, screen_y, CELL_SIZE, 2, GB_DMG_LIGHTEST);
  DrawRectangle(screen_x, screen_y, 2, CELL_SIZE, GB_DMG_LIGHTEST);
    

  DrawRectangle(screen_x, screen_y + CELL_SIZE - 2, CELL_SIZE, 2, GB_DMG_DARKEST);
  DrawRectangle(screen_x + CELL_SIZE - 2, screen_y, 2, CELL_SIZE, GB_DMG_DARKEST);
    
  char letter_str[2] = {letter, '\0'};
  Vector2 text_size = MeasureTextEx(*font, letter_str, 44, 0);
    
  DrawTextEx(*font, letter_str,
	     (Vector2){screen_x + (CELL_SIZE - text_size.x) / 2,
		       screen_y + (CELL_SIZE - text_size.y) / 2 - 4},
	     44, 0, GB_DMG_DARKEST);
}

