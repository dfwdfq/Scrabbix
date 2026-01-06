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

  map[13][2] = 'C';
  map[13][3] = 'A'; 
  map[13][4] = 'T';
  
  push_node(&letters_head, 2, 13);
  push_node(&letters_head, 3, 13);
  push_node(&letters_head, 4, 13);
  

  
  search(letters_head);
}
#endif
#if TEST == 2
//vertical word "BAG"
void init_game(void)
{
  init_bag();
  letters_head = NULL;
  
  map[10][3] = 'B';
  map[11][3] = 'A';
  map[12][3] = 'G';
  
  push_node(&letters_head, 3, 10);
  push_node(&letters_head, 3, 11);
  push_node(&letters_head, 3, 12);
  
  search(letters_head);
}
#endif

#if TEST == 3
//L-shaped word "GREAT" (G at turn)
void init_game(void)
{
  init_bag();
  letters_head = NULL;
  
  // L shape: G at (3,12), then REAT to the right at row 13
  map[12][3] = 'G';
  map[13][3] = 'R';
  map[13][4] = 'E';
  map[13][5] = 'A';
  map[13][6] = 'T';
  
  push_node(&letters_head, 3, 12);
  push_node(&letters_head, 3, 13);
  push_node(&letters_head, 4, 13);
  push_node(&letters_head, 5, 13);
  push_node(&letters_head, 6, 13);
  
  search(letters_head);
}
#endif

#if TEST == 4
// Test 4: Multiple words simultaneously
void init_game(void)
{
  init_bag();
  letters_head = NULL;
  
  // Create "CAT" horizontally and "AT" vertically
  // C A T
  //   A
  //   T
  map[10][2] = 'C';
  map[10][3] = 'A';
  map[10][4] = 'T';
  map[11][3] = 'A';
  map[12][3] = 'T';
  
  push_node(&letters_head, 2, 10);
  push_node(&letters_head, 3, 10);
  push_node(&letters_head, 4, 10);
  push_node(&letters_head, 3, 11);
  push_node(&letters_head, 3, 12);
  
  search(letters_head);
}
#endif

#if TEST == 5
// Test 5: Word at grid edges
void init_game(void)
{
  init_bag();
  letters_head = NULL;
  
  // Left edge vertical word "DOG"
  map[11][0] = 'D';
  map[12][0] = 'O';
  map[13][0] = 'G';
  
  // Right edge horizontal word "CAT"
  map[13][5] = 'C';
  map[13][6] = 'A';
  map[13][7] = 'T';
  
  push_node(&letters_head, 0, 11);
  push_node(&letters_head, 0, 12);
  push_node(&letters_head, 0, 13);
  push_node(&letters_head, 5, 13);
  push_node(&letters_head, 6, 13);
  push_node(&letters_head, 7, 13);
  
  search(letters_head);
}
#endif

#if TEST == 6
// Test 6: Stacked blocks with word at bottom
void init_game(void)
{
  init_bag();
  letters_head = NULL;
  
  // Stack some random blocks
  map[10][3] = 'X';
  map[11][3] = 'Y';
  map[12][3] = 'Z';
  
  // Create "CAT" at bottom
  map[13][2] = 'C';
  map[13][3] = 'A';
  map[13][4] = 'T';
  
  push_node(&letters_head, 3, 10);
  push_node(&letters_head, 3, 11);
  push_node(&letters_head, 3, 12);
  push_node(&letters_head, 2, 13);
  push_node(&letters_head, 3, 13);
  push_node(&letters_head, 4, 13);
  
  search(letters_head);
}
#endif

#if TEST == 7
// Test 7: Chain reaction - removing word causes new word
void init_game(void)
{
  init_bag();
  letters_head = NULL;
  
  // Create "CAT" horizontally
  map[13][2] = 'C';
  map[13][3] = 'A';
  map[13][4] = 'T';
  
  // Above 'A' put 'R' and 'T' to form "RAT" when blocks fall
  map[11][3] = 'R';
  map[12][3] = 'T';
  
  push_node(&letters_head, 2, 13);
  push_node(&letters_head, 3, 13);
  push_node(&letters_head, 4, 13);
  push_node(&letters_head, 3, 11);
  push_node(&letters_head, 3, 12);
  
  search(letters_head);
}
#endif

#if TEST == 8
// Test 8: Non-dictionary words (should NOT be removed)
void init_game(void)
{
  init_bag();
  letters_head = NULL;
  
  // Create "XYZ" - not in dictionary
  map[13][2] = 'X';
  map[13][3] = 'Y';
  map[13][4] = 'Z';
  
  // Create "CAT" - should be removed
  map[12][2] = 'C';
  map[12][3] = 'A';
  map[12][4] = 'T';
  
  push_node(&letters_head, 2, 13);
  push_node(&letters_head, 3, 13);
  push_node(&letters_head, 4, 13);
  push_node(&letters_head, 2, 12);
  push_node(&letters_head, 3, 12);
  push_node(&letters_head, 4, 12);
  
  search(letters_head);
}
#endif

#if TEST == 9
// Test 9: Complex L-shape combinations
void init_game(void)
{
  init_bag();
  letters_head = NULL;
  
  // Create multiple L-shapes
  // L1: G-R-E-A-T
  map[10][2] = 'G';
  map[11][2] = 'R';
  map[11][3] = 'E';
  map[11][4] = 'A';
  map[11][5] = 'T';
  
  // L2: C-O-A-T
  map[12][5] = 'C';
  map[13][5] = 'O';
  map[13][6] = 'A';
  map[13][7] = 'T';
  
  push_node(&letters_head, 2, 10);
  push_node(&letters_head, 2, 11);
  push_node(&letters_head, 3, 11);
  push_node(&letters_head, 4, 11);
  push_node(&letters_head, 5, 11);
  push_node(&letters_head, 5, 12);
  push_node(&letters_head, 5, 13);
  push_node(&letters_head, 6, 13);
  push_node(&letters_head, 7, 13);
  
  search(letters_head);
}
#endif

#if TEST == 10
// Test 10: Full column test for block falling mechanics
void init_game(void)
{
  init_bag();
  letters_head = NULL;
  
  // Fill column 3 completely
  for(int y = 6; y < MAP_HEIGHT; y++) {
    map[y][3] = 'A' + (y % 26);
    push_node(&letters_head, 3, y);
  }
  
  // Put "CAT" at the bottom of column 4
  map[13][4] = 'C';
  map[13][5] = 'A';
  map[13][6] = 'T';
  push_node(&letters_head, 4, 13);
  push_node(&letters_head, 5, 13);
  push_node(&letters_head, 6, 13);
  
  search(letters_head);
}
#endif

#if TEST == 11
// Test 11: Moving block mechanics
void init_game(void)
{
  init_bag();
  letters_head = NULL;
  
  // Create obstacles
  map[13][2] = 'X';
  map[13][6] = 'Y';
  
  // Place a movable block above
  block_y = 12;
  block_x = 4;
  map[block_y][block_x] = 'C';
  
  push_node(&letters_head, 2, 13);
  push_node(&letters_head, 6, 13);
  
  // Don't call search initially - let player move the block
}
#endif

#if TEST == 12
// Test 12: Timer and automatic falling
void init_game(void)
{
  init_bag();
  letters_head = NULL;
  
  // Set timer to almost done
  mov_counter = 1; // Will trigger on next frame
  
  // Place a falling block
  block_y = 0;
  block_x = 3;
  map[block_y][block_x] = 'C';
  
  // Place obstacles below
  map[13][3] = 'X';
  map[13][4] = 'Y';
  push_node(&letters_head, 3, 13);
  push_node(&letters_head, 4, 13);
}
#endif
