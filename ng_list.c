#include "ng_list.h"

struct ng_list *
ng_list_new () {
  struct ng_list *list = malloc (sizeof (struct ng_list));
  list->count = 0;
  list->head = list->tail = NULL;
  return list;
}

int
ng_list_count (struct ng_list *list) {
  return list->count;
}

void
ng_list_free (struct ng_list *list) {
  struct ng_list_node *current;
  while (list->head != NULL) {
    current = list->head;
    list->head = current->next;
    free (current);
  }
}

void
ng_list_append (struct ng_list *list, void (*func) (void *)) {
  struct ng_list_node *node = malloc (sizeof (struct ng_list_node));
  node->func = func;
  node->next = NULL;
  if (list->count == 0)
    list->head = list->tail = node;
  else {
    list->tail->next = node;
    list->tail = node;
  }
  list->count++;
}

void
ng_list_foreach (struct ng_list *list, void (*func) (struct ng_list_node *)) {
  struct ng_list_node *current = list->head;
  while (current != NULL) {
    func (current);
    current = current->next;
  }
}
