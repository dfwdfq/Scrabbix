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
void print_list(VertexListNode* head)
{
  VertexListNode* current = head;
  while(current != NULL)
    {
      printf("%d %d\n",current->x,current->y);
      current = current->next;
    }
  printf("end!\n");
}
