#include"map.h"

char map[14][8];
char spawn_line[8];

void draw_borders(void)
{
  //top border
  for(int i = 0;i<4;++i)
    {
      DrawLine(BORDER_OX+i,BORDER_OY+i,
	       BORDER_OX+BORDER_WIDTH+i,BORDER_OY+i,
	       WHITE);
    }

  //bottom border
  for(int i = 0;i<4;++i)
    {
      DrawLine(BORDER_OX+i,BORDER_HEIGHT+BORDER_OY+i,
	       BORDER_OX+BORDER_WIDTH+i,BORDER_HEIGHT+BORDER_OY+i,
	       WHITE);
    }

  //left border
  for(int i = 0;i<4;++i)
    {
      DrawLine(BORDER_OX+i,BORDER_OY+i,
	       BORDER_OX+i,BORDER_HEIGHT+BORDER_OY+i,
	       WHITE);
    }

  //right border
  for(int i = 0;i<4;++i)
    {
      DrawLine(BORDER_OX+BORDER_WIDTH+i,BORDER_OY+i,
	       BORDER_OX+BORDER_WIDTH+i,BORDER_HEIGHT+BORDER_OY+i,
	       WHITE);
    }

}
void draw_block(int x, int y,char* str)
{
  DrawRectangle(GPX(x),GPX(y),CELL_SIZE,CELL_SIZE,WHITE);
  DrawText(str,GPX(x)+20,GPY(y)+16,32,BLACK);
}
void draw_map(void)
{
  char str[2];
  for(int y =0;y<14;++y)
    for(int x =0;x<8;++x)
      {
	sprintf(str,"%c\n",map[y][x]);
	draw_block(x,y,str);
      }
}
