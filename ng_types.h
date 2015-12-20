#ifndef ng_types_h
#define ng_types_h

#ifndef ng_forward_h
#include <pthread.h>
#endif // ng_forward_h

//region structs
typedef struct ng_game_configuration {
  int window_width;
  int window_height;
  int framerate_target;
  unsigned char framerate_fixed;
  const char *window_title;
} GameConfiguration;

typedef struct ng_game_time {
  double total;
  double total_seconds;
  double elapsed;
  double elapsed_seconds;
} GameTime;

typedef struct ng_game_state {
  GameConfiguration config;
  void (*run) ();
  void (*loop) ();
  void (*add_update_hook) (void (*) ());
  void (*add_draw_hook) (void (*) ());
  pthread_t thread;
  GameTime *time;
} GameState;
//endregion;

#endif // ng_types_h
