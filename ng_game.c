#include "ng_game.h"

GameState *ng_game_create_state (GameConfiguration config) {
  GameTime *init_time = malloc (sizeof (GameTime));
  ng_state = malloc (sizeof (GameState));
  ng_state->config = config;
  ng_state->run = &ng_game_run;
  ng_state->loop = &ng_game_loop;
  ng_state->add_update_hook = &ng_game_add_update_hook;
  ng_state->add_draw_hook = &ng_game_add_draw_hook;
  ng_state->time = init_time;
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
  ng_t = 0.0f;
  ng_dt = 1.0f / ng_state->config.framerate_target;
  ng_current_time = start_time / 1000.0f;
  ng_accum = 0.0f;
  ng_last_time = 0.0f;
  for (;;) {
    ng_game_run_game_loop_iteration ();
    glutMainLoopEvent ();
  }
}

static void ng_game_run_game_loop_iteration () {

  // Calculate timing data
  double new_time = glutGet (GLUT_ELAPSED_TIME) / 1000.0f;
  double frame_time = new_time - ng_current_time;
  ng_current_time = new_time;
  ng_accum += frame_time;

  // Fixed framerate update
  if (ng_state->config.framerate_fixed) {

    // Update according to calculated timing data
    while (ng_accum >= ng_dt) {

      // Calculate total and elapsed time
      double new_total_time = glutGet (GLUT_ELAPSED_TIME);
      double total_time = new_total_time;
      double elapsed_time = new_total_time - ng_last_time;
      ng_last_time = new_total_time;

      // Update game time
      ng_state->time->total = total_time;
      ng_state->time->total_seconds = total_time / 1000.0f;
      ng_state->time->elapsed = elapsed_time;
      ng_state->time->elapsed_seconds = elapsed_time / 1000.0f;

      // Update game
      ng_game_update ();

      // Update timing data
      ng_accum -= ng_dt;
      ng_t += ng_dt;
    }
  }

  // Variable framerate update
  else {

    // Calculate total and elapsed time
    double new_total_time = glutGet (GLUT_ELAPSED_TIME);
    double total_time = new_total_time;
    double elapsed_time = new_total_time - ng_last_time;
    ng_last_time = new_total_time;

    // Update game time
    ng_state->time->total = total_time;
    ng_state->time->total_seconds = total_time / 1000.0f;
    ng_state->time->elapsed = elapsed_time;
    ng_state->time->elapsed_seconds = elapsed_time / 1000.0f;

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
