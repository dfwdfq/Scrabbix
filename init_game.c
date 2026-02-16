#include"game.h"
//implementations of init_game

void init_game(void)
{
  init_bag();
  letters_head = NULL;

  generate_random_start_pos();
  map[block_y][block_x] = get_next_letter();
}
