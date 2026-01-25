#ifndef GB_PALETTE_H
#define GB_PALETTE_H
#include<raylib.h>
#include"constants.h"

#define GB_DMG_DARKEST   (Color){ 15,  56,  15, 255 }  //#0F380F
#define GB_DMG_DARK      (Color){ 48,  98,  48, 255 }  //#306230
#define GB_DMG_LIGHT     (Color){139, 172,  15, 255 }  //#8BAC0F
#define GB_DMG_LIGHTEST  (Color){155, 188,  15, 255 }  //#9BBC0F

#define GPX(x) (4+ BORDER_OX+(x*CELL_SIZE) ) 
#define GPY(y) (4+ BORDER_OY+(y*CELL_SIZE) )

extern Color get_dithered_color(int x, int y, Color a, Color b);
extern void draw_vignette(void);
extern void draw_scanlines(int scanline_height);
extern void draw_pixel_grid(void);
extern void draw_gb_borders(void);
extern void draw_gb_block(int x, int y, char letter, Font* font, bool is_falling);
extern void draw_gb_block_next(int x, int y, char letter, Font* font, bool is_falling);

#endif /* GB_PALETTE_H */
