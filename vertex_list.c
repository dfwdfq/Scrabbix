#include"vertex_list.h"

VertexListNode* create_node(int x, int y)
{
  VertexListNode* node = malloc(sizeof(VertexListNode));
  if(!node) return NULL;

  node->x = x;
  node->y = y;
  node->next = NULL;
  return node;
}
void push_node(VertexListNode** head,int x,int y)
{
  VertexListNode* node = create_node(x,y);
  node->next = *head;
  *head = node;
}
void clear_VertexList(VertexListNode* head)
{
  VertexListNode* tmp;
  while(head != NULL)
    {
      tmp = head;
      head = head->next;
      free(tmp);
    }
}
void print_list(VertexListNode* head,
		char map[MAP_HEIGHT][MAP_WIDTH])
{
  VertexListNode* current = head;
  while(current != NULL)
    {
      printf("%d %d %c\n",current->x,current->y,map[current->y][current->x]);
      current = current->next;
    }
}
VertexListNode* remove_by_value(VertexListNode* head,
				int x,
				int y)
{
  VertexListNode *current = head;
  VertexListNode *prev    = NULL;

  while(current != NULL &&
	!(current->x == x &&
	  current->y == y))
    {
      prev = current;
      current = current->next;
    }

  if(current == NULL)
    {
      return head;
    }

  if(prev == NULL)
    {
      head = current->next;
    }
  else
    {
      prev->next = current->next;
    }
  free(current);
  return head;  
}
