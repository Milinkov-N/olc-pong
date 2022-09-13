#ifndef OLC_PONG_VTERM_H_
#define OLC_PONG_VTERM_H_

#include <stdio.h>
#include <windows.h>

// This needed because i have old SDK version
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

void enable_vterm();
void hide_cursor();
void show_cursor();

#endif  // OLC_PONG_VTERM_H_
