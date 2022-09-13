#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "state.h"
#include "graphics.h"
#include "vterm.h"

void run_pong(state_t *state);
int key_events(state_t *state);

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
  int skipped_frames = 0;
  while (1) {
    render(state);
    if (skipped_frames != 2) {
      skipped_frames++;
    } else {
      move_ball(state);
      skipped_frames = 0;
    }
    if (!key_events(state)
      || state->playerA_score == 9
      || state->playerB_score == 9)
      break;
    Sleep(20);
    clear_screen();
  }
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
