#include "ng_forward.h"

int main ()
{
  // Create the game configuration
  struct ng_game_configuration config = {
    /* width  */ 640,
    /* height */ 480,
    /* title  */ "cginz"
  };

  // Create the game state
  struct ng_game_state *game = ng_game_create_state (config);

  // Run the game and enter the gameloop
  game->run ();
  game->loop ();

  return EXIT_SUCCESS;
}

