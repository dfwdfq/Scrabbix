#include"map.h"

char map[14][8];
int block_x, block_y;

void init_map(void)
{
  for(int i = 0;i<14;++i)
    {
      memset(map[i],'\0',sizeof(char)*8);
    }

  block_x = -1, block_y = -1;
}

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
	if(map[y][x] != '\0')
	  {
	    sprintf(str,"%c\n",map[y][x]);
	    draw_block(x,y,str);
	  }
      }
}
void update_map(void)
{
  if(block_x == -1 &&
     block_y == -1)
    return;
  
  if(block_y == 13)
    {
      block_x = -1;
      block_y = -1;
    }
  else
    {
      char val = map[block_y][block_x];
      if(map[block_y+1][block_x] == '\0')
	{
	  map[block_y][block_x] = '\0';
	  map[++block_y][block_x] = val;
	}
    }
}
void generate_random_start_pos(void)
{
  block_y = 0;
  block_x = GetRandomValue(0,7);
}
