#ifndef VERTEX_LIST_H
#define VERTEX_LIST_H
#include<stddef.h>
#include<stdlib.h>
#include<stdio.h>

typedef struct VertexListNode
{
  int x,y;
  struct VertexListNode* next;
} VertexListNode;

extern VertexListNode* create_node(int x, int y);
extern void push_node(VertexListNode** head,int x,int y);
extern void clear_VertexList(VertexListNode* head);
extern void print_list(VertexListNode* head);

#endif
