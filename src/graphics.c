#include "graphics.h"

void render(state_t *state) {
  for (int i = 0; i < HEIGHT; i++) {
    char line_buf[WIDTH] = {0};
    for (int j = 0; j < WIDTH; j++) {
      switch (get_item_to_render(state, i, j)) {
        case RI_BALL:         line_buf[j] = 'o'; break;
        case RI_RACKET_LEFT:  line_buf[j] = ']'; break;
        case RI_RACKET_RIGHT: line_buf[j] = '['; break; 
        case RI_CORNER:       line_buf[j] = '+'; break;
        case RI_HOR_LINE:     line_buf[j] = '-'; break;
        case RI_VER_LINE:     line_buf[j] = '|'; break;
        case RI_VOID:         line_buf[j] = ' '; break;
        case RI_SCORE_PLAYER_A:
          line_buf[j] = state->playerA_score + 48;
          break;
        case RI_SCORE_PLAYER_B:
          line_buf[j] = state->playerB_score + 48;
          break;
      }
    }
    printf("%s\n", line_buf);
  }
}

void clear_screen() {
  for (int i = 0; i <= HEIGHT; i++) {
    printf("\x1b[2K");
    if (i != HEIGHT)
      printf("\x1b[1A");
  }
  printf("\r");
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

  if (row == state->ball_Ypos && col == state->ball_Xpos)
    item = RI_BALL;
  else if (racketA_pos && col == 1)
    item = RI_RACKET_LEFT;
  else if (racketB_pos && col == W_EDGE - 1)
    item = RI_RACKET_RIGHT;
  else if (row == 1 && col == W_EDGE / 2 - 2)
    item = RI_SCORE_PLAYER_A;
  else if (row == 1 && col == W_EDGE / 2 + 2)
    item = RI_SCORE_PLAYER_B;
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