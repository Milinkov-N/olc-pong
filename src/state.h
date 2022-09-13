#ifndef OLC_PONG_STATE_H_
#define OLC_PONG_STATE_H_

#include <stdio.h>
#include <stdlib.h>

#define HEIGHT 25
#define WIDTH 81

#define H_EDGE (HEIGHT - 1)
#define W_EDGE (WIDTH - 1)

typedef struct State {
  int playerA_score;
  int playerB_score;
  int racketA_pos;
  int racketB_pos;
  int ball_Xpos;
  int ball_Ypos;
  int ball_Xdir;
  int ball_Ydir;
} state_t;

state_t *init_state();
void destroy_state(state_t *state);

void move_ball(state_t *state);
int is_racketA_pos(state_t *state, int row);
int is_racketB_pos(state_t *state, int row);
void reset_ball_pos(state_t *state);

#endif  // OLC_PONG_STATE_H_