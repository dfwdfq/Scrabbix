#include"word_searcher.h"
bool get_next_substring(const char* str, int reset, int* start_index, char* out_buf, size_t buf_size)
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
            len = (int)strlen(str);
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
            return false;
        }
    }
    
    if (saved_str == NULL || len < 3)
    {
        if (start_index) *start_index = -1;
        return false;
    }
    
    while (sub_len <= 13 && sub_len <= len)
    {
        if (start <= len - sub_len)
        {
            size_t to_copy = (sub_len < (int)buf_size - 1) ? sub_len : buf_size - 1;
            strncpy(out_buf, saved_str + start, to_copy);
            out_buf[to_copy] = '\0';
            
            if (start_index) 
                *start_index = start;
            
            start++;
            return true;
        }
        
        sub_len++;
        start = 0;
    }
    
    if (start_index) *start_index = -1;
    return false;
}
