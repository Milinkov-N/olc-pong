#ifndef OLC_PONG_GRAPHICS_H_
#define OLC_PONG_GRAPHICS_H_

#include <stdio.h>

#include "state.h"

#define RI_BALL 1
#define RI_RACKET_LEFT 2
#define RI_RACKET_RIGHT 3
#define RI_SCORE_PLAYER_A 4
#define RI_SCORE_PLAYER_B 5
#define RI_CORNER 6
#define RI_HOR_LINE 7
#define RI_VER_LINE 8
#define RI_VOID 9

void render(state_t *state);
void clear_screen();
int get_item_to_render(state_t *state, int row, int col);

#endif  // OLC_PONG_GRAPHICS_H_
