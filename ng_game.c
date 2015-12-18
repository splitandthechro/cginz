#include "ng_game.h"

static struct ng_game_state *ng_state;

static void *
ng_game_run_thread(void *);

static void
ng_game_draw ();

struct ng_game_state *
ng_game_create_state (struct ng_game_configuration config) {
  ng_state = malloc (sizeof (struct ng_game_state));
  ng_state->config = config;
  ng_state->run = &ng_game_run;
  ng_state->loop = &ng_game_loop;
  return ng_state;
}

void
ng_game_run () {
  if (pthread_create (&ng_state->thread, NULL, ng_game_run_thread, NULL)) {
    ng_error ("Failed to create main game thread using pthreads.");
    return;
  }
}

void
ng_game_loop () {
  pthread_join (ng_state->thread, NULL);
}

static void *
ng_game_run_thread (void *dummy) {
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
  glutMainLoop ();
}

static void
ng_game_draw () {
  glClearColor (1.0f, 1.0f, 1.0f, 1.0f);
  glClear (GL_COLOR_BUFFER_BIT);
  glFlush ();
}
