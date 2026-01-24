#ifndef GB_PALETTE_H
#define GB_PALETTE_H
#include<raylib.h>
#include"constants.h"

#define GB_DMG_DARKEST   (Color){ 15,  56,  15, 255 }  //#0F380F
#define GB_DMG_DARK      (Color){ 48,  98,  48, 255 }  //#306230
#define GB_DMG_LIGHT     (Color){139, 172,  15, 255 }  //#8BAC0F
#define GB_DMG_LIGHTEST  (Color){155, 188,  15, 255 }  //#9BBC0F

extern void draw_vignette(void);
extern void draw_scanlines(int scanline_height);

#endif /* GB_PALETTE_H */
