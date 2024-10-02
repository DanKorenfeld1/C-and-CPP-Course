#include "linked_list.h"
#include <stdio.h>

void red () {
  printf("\033[1;31m");
}

void yellow() {
  printf("\033[1;33m");
}

void reset () {
  printf("\033[0m");
}
void green() {
  printf("\033[0;32m");
}
void blue() {
  printf("\033[0;34m");
}
void cyan() {
  printf("\033[1;36m");
}
void purple() {
  printf("\033[1;35m");
}



int add(LinkedList *link_list, void *data)
{
    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL)
    {
        return 1;
    }
    *new_node = (Node) {data, NULL};

    if (link_list->first == NULL)
    {
        link_list->first = new_node;
        link_list->last = new_node;
    }
    else
    {
        link_list->last->next = new_node;
        link_list->last = new_node;
    }

    link_list->size++;
    return 0;
}