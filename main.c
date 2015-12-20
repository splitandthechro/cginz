#include "ng_forward.h"

void update_something ();
void draw_something ();

int main ()
{
  // Create the game configuration
  GameConfiguration config = {
    /* width            */ 640,
    /* height           */ 480,
    /* target framerate */ 60,
    /* fixed framerate  */ 1,
    /* title            */ "cginz"
  };

  // Create the game state
  GameState *game = ng_game_create_state (config);

  // Run the game and enter the gameloop
  game->run ();
  game->add_update_hook (update_something);
  game->add_draw_hook (draw_something);
  game->loop ();

  // Exit
  return EXIT_SUCCESS;
}

void update_something (GameTime *time) {
  printf ("Total: %f  Elapsed: %f\r\n",
          time->total, time->elapsed);
}

void draw_something (GameTime *time) {
  glClearColor (0.0f, 0.4f, 1.0f, 1.0f);
  glClear (GL_COLOR_BUFFER_BIT);
}
