#include "vterm.h"

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
