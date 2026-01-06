#include"word_searcher.h"
char* get_next_substring(const char* str, int reset, int* start_index)
{
  static const char* saved_str = NULL;
  static int len = 0;
  static int sub_len = 3;
  static int start = 0;
  
  if (reset || str != NULL)
    {
      if (str != NULL)
        {
	  saved_str = str;
	  len = strlen(str);
        }
      else
        {
	  saved_str = NULL;
	  len = 0;
        }
        sub_len = 3;
        start = 0;
        
        if (str == NULL && reset)
	  {
            if (start_index) *start_index = -1;
            return NULL;
	  }
    }
  
  if (saved_str == NULL || len < 3)
    {
      if (start_index) *start_index = -1;
      return NULL;
    }
  
  while (sub_len <= 13 && sub_len <= len)
    {
      if (start <= len - sub_len)
        {
	  char* substr = (char*)malloc(sub_len + 1);
	  if (!substr) 
            {
	      if (start_index) *start_index = -1;
	      return NULL;
            }
	  
	  strncpy(substr, saved_str + start, sub_len);
	  substr[sub_len] = '\0';
          
	  if (start_index) 
	    *start_index = start;
	  
	  start++;            
	  return substr;
        }
      
      sub_len++;
      start = 0;
    }
  
  if (start_index) *start_index = -1;
  return NULL;
}
