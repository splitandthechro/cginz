#ifndef ng_list_h
#define ng_list_h

#ifndef ng_forward_h
#include <stdio.h>
#include <stdlib.h>
#include "ng_log.h"
#include "ng_types.h"
#endif // ng_forward_h

typedef void ng_list_iterator (GameTime *time);

// List node
struct ng_list_node {
  ng_list_iterator *func;
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
ng_list_append (struct ng_list *, ng_list_iterator *);

void
ng_list_foreach (struct ng_list *, void (*) (struct ng_list_node *));

#endif // ng_list_h
