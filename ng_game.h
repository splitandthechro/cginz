#ifndef ng_game_h
#define ng_game_h

#ifndef ng_forward_h
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <pthread.h>
#include "ng_log.h"
#include "ng_list.h"
#endif // ng_forward_h

// Game configuration
struct ng_game_configuration {
  int window_width;
  int window_height;
  const char *window_title;
};

// Game state
struct ng_game_state {
  struct ng_game_configuration config;
  void (*run) ();
  void (*loop) ();
  void (*add_update_hook) (void (*) ());
  void (*add_draw_hook) (void (*) ());
  pthread_t thread;
};

struct ng_game_state *
ng_game_create_state (struct ng_game_configuration config);

void
ng_game_run ();

void
ng_game_loop ();

#endif // ng_game_h
