#include"game.h"

void reupdate_blocks(void)
{
  bool moved;
  
  do {
    moved = false;
    VertexListNode* current = letters_head;
    while(current != NULL)
    {
      if(current->y < 13)
      {
        int new_y = current->y;
        
        while(new_y < 13 && map[new_y + 1][current->x] == '\0')
        {
          new_y++;
        }
        
        if(new_y > current->y)
        {
          char letter = map[current->y][current->x];
          
          map[current->y][current->x] = '\0';
          
          current->y = new_y;        
          map[current->y][current->x] = letter;
          
          moved = true;
        }
      }
      current = current->next;
    }
  } while(moved);
}

