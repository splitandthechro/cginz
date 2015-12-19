#ifndef ng_list_h
#define ng_list_h

#ifndef ng_forward_h
#include "ng_forward.h"
#endif // ng_forward_h

// List node
struct ng_list_node {
  void *data;
  struct ng_list_node *next;
};

// List
struct ng_list {
  int count;
  int size;
  struct ng_list_node *head;
  struct ng_list_node *tail;
};

#endif // ng_list_h
