#ifndef ng_list_h
#define ng_list_h

#ifndef ng_forward_h
#include <stdio.h>
#include <stdlib.h>
#include "ng_log.h"
#endif // ng_forward_h

// List node
struct ng_list_node {
  void (*func) ();
  struct ng_list_node *next;
};

// List
struct ng_list {
  int count;
  struct ng_list_node *head;
  struct ng_list_node *tail;
};

struct ng_list *
ng_list_new ();

int
ng_list_count (struct ng_list *);

void
ng_list_free (struct ng_list *);

void
ng_list_append (struct ng_list *, void (*) ());

void
ng_list_foreach (struct ng_list *, void (*) (struct ng_list_node *));

#endif // ng_list_h
