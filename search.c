#include"word_searcher.h"
void search(VertexListNode* head)
{
  VertexListNode* current = head;

  char word[14];
  int i = 0;
  while(current != NULL)
    {
      DEBUG_PRINT(ANSI_RESET,
		  "%d# letter:%c\n",
		  i,
		  map[current->y][current->x]);


      //LEFT DIRECTION
      search_leftward(current->x,current->y,word);
      conv_to_lower(word);     
      search_word(word,LEFT,current->x,current->y);
      
      /*DEBUG_PRINT(ANSI_RESET,
		  "word found in left direction:%s %ld\n",
		  word,
		  strlen(word));
      */

      //RIGHT DIRECTION
      search_rightward(current->x,current->y,word);
      conv_to_lower(word);      
      search_word(word,RIGHT,current->x,current->y);

      
      /*DEBUG_PRINT(ANSI_RESET,
		  "word found right direction:%s %ld\n",
		  word,
		  strlen(word));
      */
		  
      //UP DIRECTION
      search_upward(current->x,current->y,word);
      conv_to_lower(word);      
      search_word(word,UP,current->x,current->y);

      
      /*DEBUG_PRINT(ANSI_RESET,
		  "word found upward:%s %ld\n",
		  word,
		  strlen(word));
      */
		  
      //DOWN DIRECTION
      search_downward(current->x,current->y,word);
      conv_to_lower(word);      
      search_word(word,DOWN,current->x,current->y);

      
      /*DEBUG_PRINT(ANSI_RESET,
		  "word found downward:%s %ld\n",
		  word,
		  strlen(word));
      */
		  
      current = current->next;
      i++;
      get_next_substring(NULL,1,NULL); //reset generator
    }

  DEBUG_PRINT_SEPARATOR;
}
