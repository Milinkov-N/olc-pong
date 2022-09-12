#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

// This needed because i have old SDK version
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

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
  int ball_Xpos;
  int ball_Ypos;
  int ball_Xdir;
  int ball_Ydir;
} state_t;

void run_pong(state_t *state);
void move_ball(state_t *state);
int key_events(state_t *state);
state_t *init_state();
void destroy_state(state_t *state);
void enable_vterm();
void hide_cursor();
void show_cursor();
void render(state_t *state);
void clear_screen();
int get_item_to_render(state_t *state, int row, int col);

int main(void) {
  state_t *state = init_state();
  enable_vterm();

  if (state) {
    hide_cursor();
    run_pong(state);
    show_cursor();
    clear_screen();
    destroy_state(state);
  }

  return 0;
}

void run_pong(state_t *state) {
  while (1) {
    render(state);
    move_ball(state);
    if (!key_events(state))
      break;
    Sleep(40);
    clear_screen();
  }
}

void move_ball(state_t *state) {
  if (state->ball_Ypos + 1 == H_EDGE)
    state->ball_Ydir = -1;
  else if (state->ball_Ypos == 1)
    state->ball_Ydir = 1;

  if (state->ball_Xpos + 1 == W_EDGE)
    state->ball_Xdir = -1;
  else if (state->ball_Xpos == 1)
    state->ball_Xdir = 1;

  state->ball_Xpos += state->ball_Xdir;
  state->ball_Ypos += state->ball_Ydir;
}

// For some unknown reason this function
// bugs render function and in first iteration
// render() prints garbage after each line.
// Moving key_events() logic directly to main loop
// fixes this issue
int key_events(state_t *state) {
  int exit_event = 1;
  if (_kbhit()) {
    char ch = _getch();
    if (ch == 'q')
      exit_event = 0;

    switch (ch) {
      case 'a':
        if (state->racketA_pos != 2)
          state->racketA_pos -= 1;
        break;
      case 'z':
        if (state->racketA_pos != H_EDGE - 2)
          state->racketA_pos += 1;
        break;
      case 'k':
        if (state->racketB_pos != 2)
          state->racketB_pos -= 1;
        break;
      case 'm':
        if (state->racketB_pos != H_EDGE - 2)
          state->racketB_pos += 1;
        break;
    }
  }

  return exit_event;
}

state_t *init_state() {
  state_t *state = NULL;

  if((state = malloc(sizeof(state_t)))) {
    state->playerA_score = 0;
    state->playerB_score = 0;
    state->racketA_pos   = H_EDGE / 2;
    state->racketB_pos   = H_EDGE / 2;
    state->ball_Xpos     = W_EDGE / 2;
    state->ball_Ypos     = H_EDGE / 2;
    state->ball_Xdir     = 1;
    state->ball_Ydir     = 1;
  }

  return state;
}

void destroy_state(state_t *state) {
  if (state)
    free(state);
}

void enable_vterm() {
  HANDLE h_stdout;
  DWORD stdout_mode = 0;

  h_stdout = GetStdHandle(STD_OUTPUT_HANDLE);
  GetConsoleMode(h_stdout, &stdout_mode);
  stdout_mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
  SetConsoleMode(h_stdout, stdout_mode);
}

void hide_cursor() {
  printf("\x1b[?25l");
}

void show_cursor() {
  printf("\x1b[?25h");
}

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
      }
    }
    printf("%s\r\n", line_buf);
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
