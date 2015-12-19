#include "ng_game.h"

GameState *ng_game_create_state (GameConfiguration config) {
  ng_info ("Creating game configuration");
  ng_state = malloc (sizeof (GameState));
  ng_state->config = config;
  ng_state->run = &ng_game_run;
  ng_state->loop = &ng_game_loop;
  ng_state->add_update_hook = &ng_game_add_update_hook;
  ng_state->add_draw_hook = &ng_game_add_draw_hook;
  return ng_state;
}

void ng_game_run () {
  ng_info ("Creating action lists for drawing and updating");
  ng_actions_update = ng_list_new ();
  ng_actions_draw = ng_list_new ();
  ng_info ("Creating main game thread using pthread");
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
  for (;;) {
    ng_game_run_game_loop_iteration ();
    glutMainLoopEvent ();
  }
}

static void ng_game_run_game_loop_iteration () {
  ng_game_update ();
}

static void ng_game_draw () {
  ng_list_foreach (ng_actions_draw, ng_game_draw_node);
  glFlush ();
}

static void ng_game_draw_node (struct ng_list_node *node) {
  node->func ();
}

static void ng_game_update () {
  ng_list_foreach (ng_actions_update, ng_game_update_node);
}

static void ng_game_update_node (struct ng_list_node *node) {
  node->func ();
}

static void ng_game_add_update_hook (void (*func) ()) {
  ng_list_append (ng_actions_update, func);
}

static void ng_game_add_draw_hook (void (*func) ()) {
  ng_list_append (ng_actions_draw, func);
}
