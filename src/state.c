#include "state.h"

state_t *init_state() {
  state_t *state = NULL;

  if((state = malloc(sizeof(state_t)))) {
    state->playerA_score = 0;
    state->playerB_score = 0;
    state->racketA_pos   = H_EDGE / 2;
    state->racketB_pos   = H_EDGE / 2;
    state->ball_Xpos     = W_EDGE / 2;
    state->ball_Ypos     = H_EDGE / 2;
    state->ball_Xdir     = -1;
    state->ball_Ydir     = -1;
  }

  return state;
}

void destroy_state(state_t *state) {
  if (state)
    free(state);
}

void move_ball(state_t *state) {
  if (state->ball_Ypos + 1 == H_EDGE)
    state->ball_Ydir = -1;
  else if (state->ball_Ypos == 1)
    state->ball_Ydir = 1;

  else if (state->ball_Xpos - 1 == 1
    && is_racketA_pos(state, state->ball_Ypos)) {
    state->ball_Xdir = 1;
  } else if (state->ball_Xpos == 1) {
    reset_ball_pos(state);
    state->playerB_score++;
  } else if (state->ball_Xpos + 1 == W_EDGE - 1
    && is_racketB_pos(state, state->ball_Ypos)) {
    state->ball_Xdir = -1;
  } else if (state->ball_Xpos + 1 == W_EDGE) {
    reset_ball_pos(state);
    state->playerA_score++;
  }

  state->ball_Xpos += state->ball_Xdir;
  state->ball_Ypos += state->ball_Ydir;
}

int is_racketA_pos(state_t *state, int row) {
  return (row == state->racketA_pos
    || row == state->racketA_pos - 1
    || row == state->racketA_pos + 1);
}

int is_racketB_pos(state_t *state, int row) {
  return (row == state->racketB_pos
    || row == state->racketB_pos - 1
    || row == state->racketB_pos + 1);
}

void reset_ball_pos(state_t *state) {
  state->ball_Xpos = W_EDGE / 2;
  state->ball_Ypos = H_EDGE / 2;  
}
