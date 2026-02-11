#include"game.h"
//implementations of init_game

#if TEST == 0 || TEST == 13 //13 is sandboxing
void init_game(void)
{
  init_bag();
  letters_head = NULL;

  generate_random_start_pos();
  map[block_y][block_x] = get_next_letter();

}
#endif
#if TEST == 1
void init_game(void)
{
  init_bag();
  letters_head = NULL;

  map[12][2] = 'C';
  map[12][3] = 'A'; 
  map[12][4] = 'T';
  
  push_node(&letters_head, 2, 12);
  push_node(&letters_head, 3, 12);
  push_node(&letters_head, 4, 12);
  

  
  search(letters_head);
}
#endif
