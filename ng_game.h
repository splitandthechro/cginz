#ifndef ng_game_h
#define ng_game_h

#ifndef ng_forward_h
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <time.h>
#include <pthread.h>
#include "ng_log.h"
#include "ng_types.h"
#include "ng_list.h"
#endif // ng_forward_h

//region functions
GameState *ng_game_create_state (GameConfiguration config);

void ng_game_run ();

void
ng_game_loop ();
//endregion;

//region static globals
static GameState *ng_state;
static struct ng_list *ng_actions_update;
static struct ng_list *ng_actions_draw;
static double ng_t;
static double ng_dt;
static double ng_current_time;
static double ng_last_time;
static double ng_accum;
//endregion;

//region static functions
static void *ng_game_run_thread (void *);
static void ng_game_update ();
static void ng_game_update_node (struct ng_list_node *);
static void ng_game_draw ();
static void ng_game_draw_node (struct ng_list_node *);
static void ng_game_add_update_hook (ng_list_iterator *);
static void ng_game_add_draw_hook (ng_list_iterator *);
static void ng_game_run_game_loop ();
static void ng_game_run_game_loop_iteration ();
//endregion;

#endif // ng_game_h
