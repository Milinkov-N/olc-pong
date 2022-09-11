#include <stdio.h>
#include <stdlib.h>

#define HEIGHT 25
#define WIDTH 81

#define H_EDGE (HEIGHT - 1)
#define W_EDGE (WIDTH - 1)

#define RI_BALL 1
#define RI_RACKET_LEFT 2
#define RI_RACKET_RIGHT 3
#define RI_CORNER 4
#define RI_HOR_LINE 5
#define RI_VER_LINE 6
#define RI_VOID 7

typedef struct State {
  int playerA_score;
  int playerB_score;
  int racketA_pos;
  int racketB_pos;
} state_t;

state_t *init_state();
void destroy_state(state_t *state);
void render(state_t *state);
int get_item_to_render(state_t *state, int row, int col);

int main(void) {
  state_t *state = init_state();
  render(state);
  destroy_state(state);
  return 0;
}

state_t *init_state() {
  state_t *state = NULL;

  if((state = malloc(sizeof(state_t)))) {
    state->playerA_score = 0;
    state->playerB_score = 0;
    state->racketA_pos = H_EDGE / 2;
    state->racketB_pos = H_EDGE / 2;
  }

  return state;
}

void destroy_state(state_t *state) {
  if (state)
    free(state);
}

void render(state_t *state) {
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      switch (get_item_to_render(state, i, j)) {
        case RI_BALL:         printf("o"); break;
        case RI_RACKET_LEFT:  printf("]"); break;
        case RI_RACKET_RIGHT: printf("["); break;
        case RI_CORNER:       printf("+"); break;
        case RI_HOR_LINE:     printf("-"); break;
        case RI_VER_LINE:     printf("|"); break;
        case RI_VOID:         printf(" "); break;
      }
    }
    printf("\n");
  }
}

int get_item_to_render(state_t *state, int row, int col) {
  int item;

  int racketA_pos = (row == state->racketA_pos
    || row == state->racketA_pos - 1
    || row == state->racketA_pos + 1);
  int racketB_pos = (row == state->racketB_pos
    || row == state->racketB_pos - 1
    || row == state->racketB_pos + 1);
  int left_corners = (row == 0
    && (col == 0 || col == W_EDGE));
  int right_corners = ( row == H_EDGE
    && (col == 0 || col == W_EDGE));
  int hor_in_field = (col > 0 && col < W_EDGE);
  int top_bottom = row > 0 && row < H_EDGE;
  int left_right_middle = (col == 0
    || col == W_EDGE
    || col == WIDTH / 2);

  if (row == H_EDGE / 2 && col == W_EDGE / 2)
    item = RI_BALL;
  else if (racketA_pos && col == 1)
    item = RI_RACKET_LEFT;
  else if (racketB_pos && col == W_EDGE - 1)
    item = RI_RACKET_RIGHT;
  else if (left_corners || right_corners)
    item = RI_CORNER;
  else if ((row == 0 && hor_in_field)
    || (row == H_EDGE && hor_in_field))
    item = RI_HOR_LINE;
  else if (top_bottom && left_right_middle)
    item = RI_VER_LINE;
  else
    item = RI_VOID;

  return item;
}
