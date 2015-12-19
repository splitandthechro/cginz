#include "ng_game.h"

GameState *ng_game_create_state (GameConfiguration config) {
  GameTime *init_game_time = malloc (sizeof (GameTime));
  GameTimeState *init_game_time_state = malloc (sizeof (GameTimeState));
  ng_state = malloc (sizeof (GameState));
  ng_state->config = config;
  ng_state->run = &ng_game_run;
  ng_state->loop = &ng_game_loop;
  ng_state->add_update_hook = &ng_game_add_update_hook;
  ng_state->add_draw_hook = &ng_game_add_draw_hook;
  ng_state->time = init_game_time;
  ng_state->timestate = init_game_time_state;
  return ng_state;
}

void ng_game_run () {
  ng_actions_update = ng_list_new ();
  ng_actions_draw = ng_list_new ();
  if (pthread_create (&ng_state->thread, NULL, ng_game_run_thread, NULL)) {
    ng_error ("Failed to create main game thread using pthread");
    return;
  }
}

void ng_game_loop () {
  ng_info ("Joining game context thread");
  pthread_join (ng_state->thread, NULL);
}

static void *ng_game_run_thread (void *dummy) {
  char *argv[] = { "cginz", NULL };
  int argc = 1;
  glutInit (&argc, argv);
  glutInitDisplayMode (GLUT_RGBA | GLUT_SINGLE);
  glutInitWindowSize (
        /* width  */ ng_state->config.window_width,
        /* height */ ng_state->config.window_height
  );
  glutCreateWindow (ng_state->config.window_title);
  glutDisplayFunc (ng_game_draw);
  ng_game_run_game_loop ();
  return NULL;
}

static void ng_game_run_game_loop () {
  int start_time = glutGet (GLUT_ELAPSED_TIME);
  ng_state->timestate->time_game_last = 0;
  ng_state->timestate->time_game_current = 0;
  ng_state->timestate->time_update = .0f;
  ng_state->timestate->time_update_accum = .0f;
  ng_state->timestate->time_update_delta =
      1.0f / ng_state->config.framerate_target;
  ng_state->timestate->time_update_current =
      ng_state->timestate->time_game_current / 1000.0f;
  for (;;) {
    ng_game_run_game_loop_iteration ();
    glutMainLoopEvent ();
  }
}

static void ng_game_run_game_loop_iteration () {

  // Get the total elapsed time in milliseconds
  float time_now = glutGet (GLUT_ELAPSED_TIME);
  ng_state->timestate->time_game_current = time_now;

  // Fixed framerate update
  if (ng_state->config.framerate_fixed) {

    // Calculate timing data
    float time_new = time_now / 1000.0f;
    ng_state->timestate->time_update_frame =
        time_new - ng_state->timestate->time_update_current;
    ng_state->timestate->time_update_current = time_new;
    ng_state->timestate->time_update_accum +=
        ng_state->timestate->time_update_frame;

    // Update according to calculated timing data
    while (ng_state->timestate->time_update_accum
           >= ng_state->timestate->time_update_delta) {

      // Calculate total and elapsed time
      int time_total = time_now;
      int time_elapsed = time_now - ng_state->timestate->time_game_last;
      ng_state->timestate->time_game_last = time_now;

      // Update game time
      ng_state->time->total = time_total;
      ng_state->time->elapsed = time_elapsed;
      printf ("|Elapsed: %f\r\n", time_elapsed);

      // Update game
      ng_game_update ();

      // Update timing data
      ng_state->timestate->time_update_accum -=
          ng_state->timestate->time_update_delta;
      ng_state->timestate->time_update +=
          ng_state->timestate->time_update_delta;
    }
  }

  // Variable framerate update
  else {

    // Calculate total and elapsed time
    int time_total = time_now;
    int time_elapsed = time_now - ng_state->timestate->time_game_last;
    ng_state->timestate->time_game_last = time_now;

    // Update game time
    ng_state->time->total = time_total;
    ng_state->time->elapsed = time_elapsed;

    // Update game
    ng_game_update ();
  }
}

static void ng_game_draw () {
  ng_list_foreach (ng_actions_draw, ng_game_draw_node);
  glFlush ();
}

static void ng_game_draw_node (struct ng_list_node *node) {
  node->func (ng_state->time);
}

static void ng_game_update () {
  ng_list_foreach (ng_actions_update, ng_game_update_node);
}

static void ng_game_update_node (struct ng_list_node *node) {
  node->func (ng_state->time);
}

static void ng_game_add_update_hook (ng_list_iterator *func) {
  ng_list_append (ng_actions_update, func);
}

static void ng_game_add_draw_hook (ng_list_iterator *func) {
  ng_list_append (ng_actions_draw, func);
}
