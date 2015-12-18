#ifndef ng_game_h
#define ng_game_h

#ifndef ng_forward_h
#include "ng_forward.h"
#endif // ng_forward_h

struct ng_game_configuration {
  int window_width;
  int window_height;
  const char *window_title;
};

struct ng_game_state {
  struct ng_game_configuration config;
  void (*run) ();
  void (*loop) ();
  pthread_t thread;
};

struct ng_game_state *
ng_game_create_state (struct ng_game_configuration config);

void
ng_game_run ();

void
ng_game_loop ();

#endif // ng_game_h
