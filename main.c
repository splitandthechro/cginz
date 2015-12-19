#include "ng_forward.h"

void draw_something ();

int main ()
{
  // Create the game configuration
  GameConfiguration config = {
    /* width  */ 640,
    /* height */ 480,
    /* title  */ "cginz"
  };

  // Create the game state
  GameState *game = ng_game_create_state (config);

  // Run the game and enter the gameloop
  game->run ();
  game->add_draw_hook (draw_something);
  game->loop ();

  // Exit
  return EXIT_SUCCESS;
}

void draw_something () {
  glClearColor (0.0f, 0.4f, 1.0f, 1.0f);
  glClear (GL_COLOR_BUFFER_BIT);
}
