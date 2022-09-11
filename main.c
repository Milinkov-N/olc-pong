#include <stdio.h>

#define HEIGHT 26
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

void render();
int get_item_to_render(int row, int col);

int main(void) {
  render();
  return 0;
}

void render() {
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      switch (get_item_to_render(i, j)) {
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

int get_item_to_render(int row, int col) {
  int item;

  int vertical_racket_pos = (row == H_EDGE / 2
    || row == H_EDGE / 2 - 1
    || row == H_EDGE / 2 + 1);
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
  else if (vertical_racket_pos && col == 1)
    item = RI_RACKET_LEFT;
  else if (vertical_racket_pos && col == W_EDGE - 1)
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
