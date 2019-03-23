#include <includes.h>

#define DeskIdleState    0
#define DeskInitialState 1
#define DeskRunState     2

BOOLEAN TIMER_START = FALSE;

// hide to workbar
const UINT8 DeskHideButton[]={
0x42, 0x4D, 0xC6, 0x4, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x36, 0x4, 0x0, 0x0, 0x28, 0x0, 0x0, 0x0, 0xC, 0x0, 0x0, 0x0, 0xC, 0x0, 0x0, 0x0, 0x1, 0x0, 0x8, 0x0, 0x0, 0x0, 0x0, 0x0, 0x90, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x80, 0x80, 0x0, 0x80, 0x0, 0x0, 0x0, 0x80, 0x0, 0x80, 0x0, 0x80, 0x80, 0x0, 0x0, 0xC0, 0xC0, 0xC0, 0x0, 0xC0, 0xDC, 0xC0, 0x0, 0xF0, 0xCA, 0xA6, 0x0, 0x0, 0x20, 0x40, 0x0, 0x0, 0x20, 0x60, 0x0, 0x0, 0x20, 0x80, 0x0, 0x0, 0x20, 0xA0, 0x0, 0x0, 0x20, 0xC0, 0x0, 0x0, 0x20, 0xE0, 0x0, 0x0, 0x40, 0x0, 0x0, 0x0, 0x40, 0x20, 0x0, 0x0, 0x40, 0x40, 0x0, 0x0, 0x40, 0x60, 0x0, 0x0, 0x40, 0x80, 0x0, 0x0, 0x40, 0xA0, 0x0, 0x0, 0x40, 0xC0, 0x0, 0x0, 0x40, 0xE0, 0x0, 0x0, 0x60, 0x0, 0x0, 0x0, 0x60, 0x20, 0x0, 0x0, 0x60, 0x40, 0x0, 0x0, 0x60, 0x60, 0x0, 0x0, 0x60, 0x80, 0x0, 0x0, 0x60, 0xA0, 0x0, 0x0, 0x60, 0xC0, 0x0, 0x0, 0x60, 0xE0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x80, 0x20, 0x0, 0x0, 0x80, 0x40, 0x0, 0x0, 0x80, 0x60, 0x0, 0x0, 0x80, 0x80, 0x0, 0x0, 0x80, 0xA0, 0x0, 0x0, 0x80, 0xC0, 0x0, 0x0, 0x80, 0xE0, 0x0, 0x0, 0xA0, 0x0, 0x0, 0x0, 0xA0, 0x20, 0x0, 0x0, 0xA0, 0x40, 0x0, 0x0, 0xA0, 0x60, 0x0, 0x0, 0xA0, 0x80, 0x0, 0x0, 0xA0, 0xA0, 0x0, 0x0, 0xA0, 0xC0, 0x0, 0x0, 0xA0, 0xE0, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0xC0, 0x20, 0x0, 0x0, 0xC0, 0x40, 0x0, 0x0, 0xC0, 0x60, 0x0, 0x0, 0xC0, 0x80, 0x0, 0x0, 0xC0, 0xA0, 0x0, 0x0, 0xC0, 0xC0, 0x0, 0x0, 0xC0, 0xE0, 0x0, 0x0, 0xE0, 0x0, 0x0, 0x0, 0xE0, 0x20, 0x0, 0x0, 0xE0, 0x40, 0x0, 0x0, 0xE0, 0x60, 0x0, 0x0, 0xE0, 0x80, 0x0, 0x0, 0xE0, 0xA0, 0x0, 0x0, 0xE0, 0xC0, 0x0, 0x0, 0xE0, 0xE0, 0x0, 0x40, 0x0, 0x0, 0x0, 0x40, 0x0, 0x20, 0x0, 0x40, 0x0, 0x40, 0x0, 0x40, 0x0, 0x60, 0x0, 0x40, 0x0, 0x80, 0x0, 0x40, 0x0, 0xA0, 0x0, 0x40, 0x0, 0xC0, 0x0, 0x40, 0x0, 0xE0, 0x0, 0x40, 0x20, 0x0, 0x0, 0x40, 0x20, 0x20, 0x0, 0x40, 0x20, 0x40, 0x0, 0x40, 0x20, 0x60, 0x0, 0x40, 0x20, 0x80, 0x0, 0x40, 0x20, 0xA0, 0x0, 0x40, 0x20, 0xC0, 0x0, 0x40, 0x20, 0xE0, 0x0, 0x40, 0x40, 0x0, 0x0, 0x40, 0x40, 0x20, 0x0, 0x40, 0x40, 0x40, 0x0, 0x40, 0x40, 0x60, 0x0, 0x40, 0x40, 0x80, 0x0, 0x40, 0x40, 0xA0, 0x0, 0x40, 0x40, 0xC0, 0x0, 0x40, 0x40, 0xE0, 0x0, 0x40, 0x60, 0x0, 0x0, 0x40, 0x60, 0x20, 0x0, 0x40, 0x60, 0x40, 0x0, 0x40, 0x60, 0x60, 0x0, 0x40, 0x60, 0x80, 0x0, 0x40, 0x60, 0xA0, 0x0, 0x40, 0x60, 0xC0, 0x0, 0x40, 0x60, 0xE0, 0x0, 0x40, 0x80, 0x0, 0x0, 0x40, 0x80, 0x20, 0x0, 0x40, 0x80, 0x40, 0x0, 0x40, 0x80, 0x60, 0x0, 0x40, 0x80, 0x80, 0x0, 0x40, 0x80, 0xA0, 0x0, 0x40, 0x80, 0xC0, 0x0, 0x40, 0x80, 0xE0, 0x0, 0x40, 0xA0, 0x0, 0x0, 0x40, 0xA0, 0x20, 0x0, 0x40, 0xA0, 0x40, 0x0, 0x40, 0xA0, 0x60, 0x0, 0x40, 0xA0, 0x80, 0x0, 0x40, 0xA0, 0xA0, 0x0, 0x40, 0xA0, 0xC0, 0x0, 0x40, 0xA0, 0xE0, 0x0, 0x40, 0xC0, 0x0, 0x0, 0x40, 0xC0, 0x20, 0x0, 0x40, 0xC0, 0x40, 0x0, 0x40, 0xC0, 0x60, 0x0, 0x40, 0xC0, 0x80, 0x0, 0x40, 0xC0, 0xA0, 0x0, 0x40, 0xC0, 0xC0, 0x0, 0x40, 0xC0, 0xE0, 0x0, 0x40, 0xE0, 0x0, 0x0, 0x40, 0xE0, 0x20, 0x0, 0x40, 0xE0, 0x40, 0x0, 0x40, 0xE0, 0x60, 0x0, 0x40, 0xE0, 0x80, 0x0, 0x40, 0xE0, 0xA0, 0x0, 0x40, 0xE0, 0xC0, 0x0, 0x40, 0xE0, 0xE0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x80, 0x0, 0x20, 0x0, 0x80, 0x0, 0x40, 0x0, 0x80, 0x0, 0x60, 0x0, 0x80, 0x0, 0x80, 0x0, 0x80, 0x0, 0xA0, 0x0, 0x80, 0x0, 0xC0, 0x0, 0x80, 0x0, 0xE0, 0x0, 0x80, 0x20, 0x0, 0x0, 0x80, 0x20, 0x20, 0x0, 0x80, 0x20, 0x40, 0x0, 0x80, 0x20, 0x60, 0x0, 0x80, 0x20, 0x80, 0x0, 0x80, 0x20, 0xA0, 0x0, 0x80, 0x20, 0xC0, 0x0, 0x80, 0x20, 0xE0, 0x0, 0x80, 0x40, 0x0, 0x0, 0x80, 0x40, 0x20, 0x0, 0x80, 0x40, 0x40, 0x0, 0x80, 0x40, 0x60, 0x0, 0x80, 0x40, 0x80, 0x0, 0x80, 0x40, 0xA0, 0x0, 0x80, 0x40, 0xC0, 0x0, 0x80, 0x40, 0xE0, 0x0, 0x80, 0x60, 0x0, 0x0, 0x80, 0x60, 0x20, 0x0, 0x80, 0x60, 0x40, 0x0, 0x80, 0x60, 0x60, 0x0, 0x80, 0x60, 0x80, 0x0, 0x80, 0x60, 0xA0, 0x0, 0x80, 0x60, 0xC0, 0x0, 0x80, 0x60, 0xE0, 0x0, 0x80, 0x80, 0x0, 0x0, 0x80, 0x80, 0x20, 0x0, 0x80, 0x80, 0x40, 0x0, 0x80, 0x80, 0x60, 0x0, 0x80, 0x80, 0x80, 0x0, 0x80, 0x80, 0xA0, 0x0, 0x80, 0x80, 0xC0, 0x0, 0x80, 0x80, 0xE0, 0x0, 0x80, 0xA0, 0x0, 0x0, 0x80, 0xA0, 0x20, 0x0, 0x80, 0xA0, 0x40, 0x0, 0x80, 0xA0, 0x60, 0x0, 0x80, 0xA0, 0x80, 0x0, 0x80, 0xA0, 0xA0, 0x0, 0x80, 0xA0, 0xC0, 0x0, 0x80, 0xA0, 0xE0, 0x0, 0x80, 0xC0, 0x0, 0x0, 0x80, 0xC0, 0x20, 0x0, 0x80, 0xC0, 0x40, 0x0, 0x80, 0xC0, 0x60, 0x0, 0x80, 0xC0, 0x80, 0x0, 0x80, 0xC0, 0xA0, 0x0, 0x80, 0xC0, 0xC0, 0x0, 0x80, 0xC0, 0xE0, 0x0, 0x80, 0xE0, 0x0, 0x0, 0x80, 0xE0, 0x20, 0x0, 0x80, 0xE0, 0x40, 0x0, 0x80, 0xE0, 0x60, 0x0, 0x80, 0xE0, 0x80, 0x0, 0x80, 0xE0, 0xA0, 0x0, 0x80, 0xE0, 0xC0, 0x0, 0x80, 0xE0, 0xE0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0xC0, 0x0, 0x20, 0x0, 0xC0, 0x0, 0x40, 0x0, 0xC0, 0x0, 0x60, 0x0, 0xC0, 0x0, 0x80, 0x0, 0xC0, 0x0, 0xA0, 0x0, 0xC0, 0x0, 0xC0, 0x0, 0xC0, 0x0, 0xE0, 0x0, 0xC0, 0x20, 0x0, 0x0, 0xC0, 0x20, 0x20, 0x0, 0xC0, 0x20, 0x40, 0x0, 0xC0, 0x20, 0x60, 0x0, 0xC0, 0x20, 0x80, 0x0, 0xC0, 0x20, 0xA0, 0x0, 0xC0, 0x20, 0xC0, 0x0, 0xC0, 0x20, 0xE0, 0x0, 0xC0, 0x40, 0x0, 0x0, 0xC0, 0x40, 0x20, 0x0, 0xC0, 0x40, 0x40, 0x0, 0xC0, 0x40, 0x60, 0x0, 0xC0, 0x40, 0x80, 0x0, 0xC0, 0x40, 0xA0, 0x0, 0xC0, 0x40, 0xC0, 0x0, 0xC0, 0x40, 0xE0, 0x0, 0xC0, 0x60, 0x0, 0x0, 0xC0, 0x60, 0x20, 0x0, 0xC0, 0x60, 0x40, 0x0, 0xC0, 0x60, 0x60, 0x0, 0xC0, 0x60, 0x80, 0x0, 0xC0, 0x60, 0xA0, 0x0, 0xC0, 0x60, 0xC0, 0x0, 0xC0, 0x60, 0xE0, 0x0, 0xC0, 0x80, 0x0, 0x0, 0xC0, 0x80, 0x20, 0x0, 0xC0, 0x80, 0x40, 0x0, 0xC0, 0x80, 0x60, 0x0, 0xC0, 0x80, 0x80, 0x0, 0xC0, 0x80, 0xA0, 0x0, 0xC0, 0x80, 0xC0, 0x0, 0xC0, 0x80, 0xE0, 0x0, 0xC0, 0xA0, 0x0, 0x0, 0xC0, 0xA0, 0x20, 0x0, 0xC0, 0xA0, 0x40, 0x0, 0xC0, 0xA0, 0x60, 0x0, 0xC0, 0xA0, 0x80, 0x0, 0xC0, 0xA0, 0xA0, 0x0, 0xC0, 0xA0, 0xC0, 0x0, 0xC0, 0xA0, 0xE0, 0x0, 0xC0, 0xC0, 0x0, 0x0, 0xC0, 0xC0, 0x20, 0x0, 0xC0, 0xC0, 0x40, 0x0, 0xC0, 0xC0, 0x60, 0x0, 0xC0, 0xC0, 0x80, 0x0, 0xC0, 0xC0, 0xA0, 0x0, 0xF0, 0xFB, 0xFF, 0x0, 0xA4, 0xA0, 0xA0, 0x0, 0x80, 0x80, 0x80, 0x0, 0x0, 0x0, 0xFF, 0x0, 0x0, 0xFF, 0x0, 0x0, 0x0, 0xFF, 0xFF, 0x0, 0xFF, 0x0, 0x0, 0x0, 0xFF, 0x0, 0xFF, 0x0, 0xFF, 0xFF, 0x0, 0x0, 0xFF, 0xFF, 0xFF, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0, 0x0, 0x0, 0x0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
};
// size to maximun
const UINT8 DeskMaximunButton[]={
0x42, 0x4D, 0xC6, 0x4, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x36, 0x4, 0x0, 0x0, 0x28, 0x0, 0x0, 0x0, 0xC, 0x0, 0x0, 0x0, 0xC, 0x0, 0x0, 0x0, 0x1, 0x0, 0x8, 0x0, 0x0, 0x0, 0x0, 0x0, 0x90, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x80, 0x80, 0x0, 0x80, 0x0, 0x0, 0x0, 0x80, 0x0, 0x80, 0x0, 0x80, 0x80, 0x0, 0x0, 0xC0, 0xC0, 0xC0, 0x0, 0xC0, 0xDC, 0xC0, 0x0, 0xF0, 0xCA, 0xA6, 0x0, 0x0, 0x20, 0x40, 0x0, 0x0, 0x20, 0x60, 0x0, 0x0, 0x20, 0x80, 0x0, 0x0, 0x20, 0xA0, 0x0, 0x0, 0x20, 0xC0, 0x0, 0x0, 0x20, 0xE0, 0x0, 0x0, 0x40, 0x0, 0x0, 0x0, 0x40, 0x20, 0x0, 0x0, 0x40, 0x40, 0x0, 0x0, 0x40, 0x60, 0x0, 0x0, 0x40, 0x80, 0x0, 0x0, 0x40, 0xA0, 0x0, 0x0, 0x40, 0xC0, 0x0, 0x0, 0x40, 0xE0, 0x0, 0x0, 0x60, 0x0, 0x0, 0x0, 0x60, 0x20, 0x0, 0x0, 0x60, 0x40, 0x0, 0x0, 0x60, 0x60, 0x0, 0x0, 0x60, 0x80, 0x0, 0x0, 0x60, 0xA0, 0x0, 0x0, 0x60, 0xC0, 0x0, 0x0, 0x60, 0xE0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x80, 0x20, 0x0, 0x0, 0x80, 0x40, 0x0, 0x0, 0x80, 0x60, 0x0, 0x0, 0x80, 0x80, 0x0, 0x0, 0x80, 0xA0, 0x0, 0x0, 0x80, 0xC0, 0x0, 0x0, 0x80, 0xE0, 0x0, 0x0, 0xA0, 0x0, 0x0, 0x0, 0xA0, 0x20, 0x0, 0x0, 0xA0, 0x40, 0x0, 0x0, 0xA0, 0x60, 0x0, 0x0, 0xA0, 0x80, 0x0, 0x0, 0xA0, 0xA0, 0x0, 0x0, 0xA0, 0xC0, 0x0, 0x0, 0xA0, 0xE0, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0xC0, 0x20, 0x0, 0x0, 0xC0, 0x40, 0x0, 0x0, 0xC0, 0x60, 0x0, 0x0, 0xC0, 0x80, 0x0, 0x0, 0xC0, 0xA0, 0x0, 0x0, 0xC0, 0xC0, 0x0, 0x0, 0xC0, 0xE0, 0x0, 0x0, 0xE0, 0x0, 0x0, 0x0, 0xE0, 0x20, 0x0, 0x0, 0xE0, 0x40, 0x0, 0x0, 0xE0, 0x60, 0x0, 0x0, 0xE0, 0x80, 0x0, 0x0, 0xE0, 0xA0, 0x0, 0x0, 0xE0, 0xC0, 0x0, 0x0, 0xE0, 0xE0, 0x0, 0x40, 0x0, 0x0, 0x0, 0x40, 0x0, 0x20, 0x0, 0x40, 0x0, 0x40, 0x0, 0x40, 0x0, 0x60, 0x0, 0x40, 0x0, 0x80, 0x0, 0x40, 0x0, 0xA0, 0x0, 0x40, 0x0, 0xC0, 0x0, 0x40, 0x0, 0xE0, 0x0, 0x40, 0x20, 0x0, 0x0, 0x40, 0x20, 0x20, 0x0, 0x40, 0x20, 0x40, 0x0, 0x40, 0x20, 0x60, 0x0, 0x40, 0x20, 0x80, 0x0, 0x40, 0x20, 0xA0, 0x0, 0x40, 0x20, 0xC0, 0x0, 0x40, 0x20, 0xE0, 0x0, 0x40, 0x40, 0x0, 0x0, 0x40, 0x40, 0x20, 0x0, 0x40, 0x40, 0x40, 0x0, 0x40, 0x40, 0x60, 0x0, 0x40, 0x40, 0x80, 0x0, 0x40, 0x40, 0xA0, 0x0, 0x40, 0x40, 0xC0, 0x0, 0x40, 0x40, 0xE0, 0x0, 0x40, 0x60, 0x0, 0x0, 0x40, 0x60, 0x20, 0x0, 0x40, 0x60, 0x40, 0x0, 0x40, 0x60, 0x60, 0x0, 0x40, 0x60, 0x80, 0x0, 0x40, 0x60, 0xA0, 0x0, 0x40, 0x60, 0xC0, 0x0, 0x40, 0x60, 0xE0, 0x0, 0x40, 0x80, 0x0, 0x0, 0x40, 0x80, 0x20, 0x0, 0x40, 0x80, 0x40, 0x0, 0x40, 0x80, 0x60, 0x0, 0x40, 0x80, 0x80, 0x0, 0x40, 0x80, 0xA0, 0x0, 0x40, 0x80, 0xC0, 0x0, 0x40, 0x80, 0xE0, 0x0, 0x40, 0xA0, 0x0, 0x0, 0x40, 0xA0, 0x20, 0x0, 0x40, 0xA0, 0x40, 0x0, 0x40, 0xA0, 0x60, 0x0, 0x40, 0xA0, 0x80, 0x0, 0x40, 0xA0, 0xA0, 0x0, 0x40, 0xA0, 0xC0, 0x0, 0x40, 0xA0, 0xE0, 0x0, 0x40, 0xC0, 0x0, 0x0, 0x40, 0xC0, 0x20, 0x0, 0x40, 0xC0, 0x40, 0x0, 0x40, 0xC0, 0x60, 0x0, 0x40, 0xC0, 0x80, 0x0, 0x40, 0xC0, 0xA0, 0x0, 0x40, 0xC0, 0xC0, 0x0, 0x40, 0xC0, 0xE0, 0x0, 0x40, 0xE0, 0x0, 0x0, 0x40, 0xE0, 0x20, 0x0, 0x40, 0xE0, 0x40, 0x0, 0x40, 0xE0, 0x60, 0x0, 0x40, 0xE0, 0x80, 0x0, 0x40, 0xE0, 0xA0, 0x0, 0x40, 0xE0, 0xC0, 0x0, 0x40, 0xE0, 0xE0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x80, 0x0, 0x20, 0x0, 0x80, 0x0, 0x40, 0x0, 0x80, 0x0, 0x60, 0x0, 0x80, 0x0, 0x80, 0x0, 0x80, 0x0, 0xA0, 0x0, 0x80, 0x0, 0xC0, 0x0, 0x80, 0x0, 0xE0, 0x0, 0x80, 0x20, 0x0, 0x0, 0x80, 0x20, 0x20, 0x0, 0x80, 0x20, 0x40, 0x0, 0x80, 0x20, 0x60, 0x0, 0x80, 0x20, 0x80, 0x0, 0x80, 0x20, 0xA0, 0x0, 0x80, 0x20, 0xC0, 0x0, 0x80, 0x20, 0xE0, 0x0, 0x80, 0x40, 0x0, 0x0, 0x80, 0x40, 0x20, 0x0, 0x80, 0x40, 0x40, 0x0, 0x80, 0x40, 0x60, 0x0, 0x80, 0x40, 0x80, 0x0, 0x80, 0x40, 0xA0, 0x0, 0x80, 0x40, 0xC0, 0x0, 0x80, 0x40, 0xE0, 0x0, 0x80, 0x60, 0x0, 0x0, 0x80, 0x60, 0x20, 0x0, 0x80, 0x60, 0x40, 0x0, 0x80, 0x60, 0x60, 0x0, 0x80, 0x60, 0x80, 0x0, 0x80, 0x60, 0xA0, 0x0, 0x80, 0x60, 0xC0, 0x0, 0x80, 0x60, 0xE0, 0x0, 0x80, 0x80, 0x0, 0x0, 0x80, 0x80, 0x20, 0x0, 0x80, 0x80, 0x40, 0x0, 0x80, 0x80, 0x60, 0x0, 0x80, 0x80, 0x80, 0x0, 0x80, 0x80, 0xA0, 0x0, 0x80, 0x80, 0xC0, 0x0, 0x80, 0x80, 0xE0, 0x0, 0x80, 0xA0, 0x0, 0x0, 0x80, 0xA0, 0x20, 0x0, 0x80, 0xA0, 0x40, 0x0, 0x80, 0xA0, 0x60, 0x0, 0x80, 0xA0, 0x80, 0x0, 0x80, 0xA0, 0xA0, 0x0, 0x80, 0xA0, 0xC0, 0x0, 0x80, 0xA0, 0xE0, 0x0, 0x80, 0xC0, 0x0, 0x0, 0x80, 0xC0, 0x20, 0x0, 0x80, 0xC0, 0x40, 0x0, 0x80, 0xC0, 0x60, 0x0, 0x80, 0xC0, 0x80, 0x0, 0x80, 0xC0, 0xA0, 0x0, 0x80, 0xC0, 0xC0, 0x0, 0x80, 0xC0, 0xE0, 0x0, 0x80, 0xE0, 0x0, 0x0, 0x80, 0xE0, 0x20, 0x0, 0x80, 0xE0, 0x40, 0x0, 0x80, 0xE0, 0x60, 0x0, 0x80, 0xE0, 0x80, 0x0, 0x80, 0xE0, 0xA0, 0x0, 0x80, 0xE0, 0xC0, 0x0, 0x80, 0xE0, 0xE0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0xC0, 0x0, 0x20, 0x0, 0xC0, 0x0, 0x40, 0x0, 0xC0, 0x0, 0x60, 0x0, 0xC0, 0x0, 0x80, 0x0, 0xC0, 0x0, 0xA0, 0x0, 0xC0, 0x0, 0xC0, 0x0, 0xC0, 0x0, 0xE0, 0x0, 0xC0, 0x20, 0x0, 0x0, 0xC0, 0x20, 0x20, 0x0, 0xC0, 0x20, 0x40, 0x0, 0xC0, 0x20, 0x60, 0x0, 0xC0, 0x20, 0x80, 0x0, 0xC0, 0x20, 0xA0, 0x0, 0xC0, 0x20, 0xC0, 0x0, 0xC0, 0x20, 0xE0, 0x0, 0xC0, 0x40, 0x0, 0x0, 0xC0, 0x40, 0x20, 0x0, 0xC0, 0x40, 0x40, 0x0, 0xC0, 0x40, 0x60, 0x0, 0xC0, 0x40, 0x80, 0x0, 0xC0, 0x40, 0xA0, 0x0, 0xC0, 0x40, 0xC0, 0x0, 0xC0, 0x40, 0xE0, 0x0, 0xC0, 0x60, 0x0, 0x0, 0xC0, 0x60, 0x20, 0x0, 0xC0, 0x60, 0x40, 0x0, 0xC0, 0x60, 0x60, 0x0, 0xC0, 0x60, 0x80, 0x0, 0xC0, 0x60, 0xA0, 0x0, 0xC0, 0x60, 0xC0, 0x0, 0xC0, 0x60, 0xE0, 0x0, 0xC0, 0x80, 0x0, 0x0, 0xC0, 0x80, 0x20, 0x0, 0xC0, 0x80, 0x40, 0x0, 0xC0, 0x80, 0x60, 0x0, 0xC0, 0x80, 0x80, 0x0, 0xC0, 0x80, 0xA0, 0x0, 0xC0, 0x80, 0xC0, 0x0, 0xC0, 0x80, 0xE0, 0x0, 0xC0, 0xA0, 0x0, 0x0, 0xC0, 0xA0, 0x20, 0x0, 0xC0, 0xA0, 0x40, 0x0, 0xC0, 0xA0, 0x60, 0x0, 0xC0, 0xA0, 0x80, 0x0, 0xC0, 0xA0, 0xA0, 0x0, 0xC0, 0xA0, 0xC0, 0x0, 0xC0, 0xA0, 0xE0, 0x0, 0xC0, 0xC0, 0x0, 0x0, 0xC0, 0xC0, 0x20, 0x0, 0xC0, 0xC0, 0x40, 0x0, 0xC0, 0xC0, 0x60, 0x0, 0xC0, 0xC0, 0x80, 0x0, 0xC0, 0xC0, 0xA0, 0x0, 0xF0, 0xFB, 0xFF, 0x0, 0xA4, 0xA0, 0xA0, 0x0, 0x80, 0x80, 0x80, 0x0, 0x0, 0x0, 0xFF, 0x0, 0x0, 0xFF, 0x0, 0x0, 0x0, 0xFF, 0xFF, 0x0, 0xFF, 0x0, 0x0, 0x0, 0xFF, 0x0, 0xFF, 0x0, 0xFF, 0xFF, 0x0, 0x0, 0xFF, 0xFF, 0xFF, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0, 0x0, 0x0, 0x0, 0xFF, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xFF, 0x0, 0x0, 0x0, 0x0, 0xFF, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xFF, 0x0, 0x0, 0x0, 0x0, 0xFF, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xFF, 0x0, 0x0, 0x0, 0x0, 0xFF, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xFF, 0x0, 0x0, 0x0, 0x0, 0xFF, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xFF, 0x0, 0x0, 0x0, 0x0, 0xFF, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xFF, 0x0, 0x0, 0x0, 0x0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
};
// close
const UINT8 DeskCloseButton[]={
0x42, 0x4D, 0xC6, 0x4, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x36, 0x4, 0x0, 0x0, 0x28, 0x0, 0x0, 0x0, 0xC, 0x0, 0x0, 0x0, 0xC, 0x0, 0x0, 0x0, 0x1, 0x0, 0x8, 0x0, 0x0, 0x0, 0x0, 0x0, 0x90, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x80, 0x80, 0x0, 0x80, 0x0, 0x0, 0x0, 0x80, 0x0, 0x80, 0x0, 0x80, 0x80, 0x0, 0x0, 0xC0, 0xC0, 0xC0, 0x0, 0xC0, 0xDC, 0xC0, 0x0, 0xF0, 0xCA, 0xA6, 0x0, 0x0, 0x20, 0x40, 0x0, 0x0, 0x20, 0x60, 0x0, 0x0, 0x20, 0x80, 0x0, 0x0, 0x20, 0xA0, 0x0, 0x0, 0x20, 0xC0, 0x0, 0x0, 0x20, 0xE0, 0x0, 0x0, 0x40, 0x0, 0x0, 0x0, 0x40, 0x20, 0x0, 0x0, 0x40, 0x40, 0x0, 0x0, 0x40, 0x60, 0x0, 0x0, 0x40, 0x80, 0x0, 0x0, 0x40, 0xA0, 0x0, 0x0, 0x40, 0xC0, 0x0, 0x0, 0x40, 0xE0, 0x0, 0x0, 0x60, 0x0, 0x0, 0x0, 0x60, 0x20, 0x0, 0x0, 0x60, 0x40, 0x0, 0x0, 0x60, 0x60, 0x0, 0x0, 0x60, 0x80, 0x0, 0x0, 0x60, 0xA0, 0x0, 0x0, 0x60, 0xC0, 0x0, 0x0, 0x60, 0xE0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x80, 0x20, 0x0, 0x0, 0x80, 0x40, 0x0, 0x0, 0x80, 0x60, 0x0, 0x0, 0x80, 0x80, 0x0, 0x0, 0x80, 0xA0, 0x0, 0x0, 0x80, 0xC0, 0x0, 0x0, 0x80, 0xE0, 0x0, 0x0, 0xA0, 0x0, 0x0, 0x0, 0xA0, 0x20, 0x0, 0x0, 0xA0, 0x40, 0x0, 0x0, 0xA0, 0x60, 0x0, 0x0, 0xA0, 0x80, 0x0, 0x0, 0xA0, 0xA0, 0x0, 0x0, 0xA0, 0xC0, 0x0, 0x0, 0xA0, 0xE0, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0xC0, 0x20, 0x0, 0x0, 0xC0, 0x40, 0x0, 0x0, 0xC0, 0x60, 0x0, 0x0, 0xC0, 0x80, 0x0, 0x0, 0xC0, 0xA0, 0x0, 0x0, 0xC0, 0xC0, 0x0, 0x0, 0xC0, 0xE0, 0x0, 0x0, 0xE0, 0x0, 0x0, 0x0, 0xE0, 0x20, 0x0, 0x0, 0xE0, 0x40, 0x0, 0x0, 0xE0, 0x60, 0x0, 0x0, 0xE0, 0x80, 0x0, 0x0, 0xE0, 0xA0, 0x0, 0x0, 0xE0, 0xC0, 0x0, 0x0, 0xE0, 0xE0, 0x0, 0x40, 0x0, 0x0, 0x0, 0x40, 0x0, 0x20, 0x0, 0x40, 0x0, 0x40, 0x0, 0x40, 0x0, 0x60, 0x0, 0x40, 0x0, 0x80, 0x0, 0x40, 0x0, 0xA0, 0x0, 0x40, 0x0, 0xC0, 0x0, 0x40, 0x0, 0xE0, 0x0, 0x40, 0x20, 0x0, 0x0, 0x40, 0x20, 0x20, 0x0, 0x40, 0x20, 0x40, 0x0, 0x40, 0x20, 0x60, 0x0, 0x40, 0x20, 0x80, 0x0, 0x40, 0x20, 0xA0, 0x0, 0x40, 0x20, 0xC0, 0x0, 0x40, 0x20, 0xE0, 0x0, 0x40, 0x40, 0x0, 0x0, 0x40, 0x40, 0x20, 0x0, 0x40, 0x40, 0x40, 0x0, 0x40, 0x40, 0x60, 0x0, 0x40, 0x40, 0x80, 0x0, 0x40, 0x40, 0xA0, 0x0, 0x40, 0x40, 0xC0, 0x0, 0x40, 0x40, 0xE0, 0x0, 0x40, 0x60, 0x0, 0x0, 0x40, 0x60, 0x20, 0x0, 0x40, 0x60, 0x40, 0x0, 0x40, 0x60, 0x60, 0x0, 0x40, 0x60, 0x80, 0x0, 0x40, 0x60, 0xA0, 0x0, 0x40, 0x60, 0xC0, 0x0, 0x40, 0x60, 0xE0, 0x0, 0x40, 0x80, 0x0, 0x0, 0x40, 0x80, 0x20, 0x0, 0x40, 0x80, 0x40, 0x0, 0x40, 0x80, 0x60, 0x0, 0x40, 0x80, 0x80, 0x0, 0x40, 0x80, 0xA0, 0x0, 0x40, 0x80, 0xC0, 0x0, 0x40, 0x80, 0xE0, 0x0, 0x40, 0xA0, 0x0, 0x0, 0x40, 0xA0, 0x20, 0x0, 0x40, 0xA0, 0x40, 0x0, 0x40, 0xA0, 0x60, 0x0, 0x40, 0xA0, 0x80, 0x0, 0x40, 0xA0, 0xA0, 0x0, 0x40, 0xA0, 0xC0, 0x0, 0x40, 0xA0, 0xE0, 0x0, 0x40, 0xC0, 0x0, 0x0, 0x40, 0xC0, 0x20, 0x0, 0x40, 0xC0, 0x40, 0x0, 0x40, 0xC0, 0x60, 0x0, 0x40, 0xC0, 0x80, 0x0, 0x40, 0xC0, 0xA0, 0x0, 0x40, 0xC0, 0xC0, 0x0, 0x40, 0xC0, 0xE0, 0x0, 0x40, 0xE0, 0x0, 0x0, 0x40, 0xE0, 0x20, 0x0, 0x40, 0xE0, 0x40, 0x0, 0x40, 0xE0, 0x60, 0x0, 0x40, 0xE0, 0x80, 0x0, 0x40, 0xE0, 0xA0, 0x0, 0x40, 0xE0, 0xC0, 0x0, 0x40, 0xE0, 0xE0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x80, 0x0, 0x20, 0x0, 0x80, 0x0, 0x40, 0x0, 0x80, 0x0, 0x60, 0x0, 0x80, 0x0, 0x80, 0x0, 0x80, 0x0, 0xA0, 0x0, 0x80, 0x0, 0xC0, 0x0, 0x80, 0x0, 0xE0, 0x0, 0x80, 0x20, 0x0, 0x0, 0x80, 0x20, 0x20, 0x0, 0x80, 0x20, 0x40, 0x0, 0x80, 0x20, 0x60, 0x0, 0x80, 0x20, 0x80, 0x0, 0x80, 0x20, 0xA0, 0x0, 0x80, 0x20, 0xC0, 0x0, 0x80, 0x20, 0xE0, 0x0, 0x80, 0x40, 0x0, 0x0, 0x80, 0x40, 0x20, 0x0, 0x80, 0x40, 0x40, 0x0, 0x80, 0x40, 0x60, 0x0, 0x80, 0x40, 0x80, 0x0, 0x80, 0x40, 0xA0, 0x0, 0x80, 0x40, 0xC0, 0x0, 0x80, 0x40, 0xE0, 0x0, 0x80, 0x60, 0x0, 0x0, 0x80, 0x60, 0x20, 0x0, 0x80, 0x60, 0x40, 0x0, 0x80, 0x60, 0x60, 0x0, 0x80, 0x60, 0x80, 0x0, 0x80, 0x60, 0xA0, 0x0, 0x80, 0x60, 0xC0, 0x0, 0x80, 0x60, 0xE0, 0x0, 0x80, 0x80, 0x0, 0x0, 0x80, 0x80, 0x20, 0x0, 0x80, 0x80, 0x40, 0x0, 0x80, 0x80, 0x60, 0x0, 0x80, 0x80, 0x80, 0x0, 0x80, 0x80, 0xA0, 0x0, 0x80, 0x80, 0xC0, 0x0, 0x80, 0x80, 0xE0, 0x0, 0x80, 0xA0, 0x0, 0x0, 0x80, 0xA0, 0x20, 0x0, 0x80, 0xA0, 0x40, 0x0, 0x80, 0xA0, 0x60, 0x0, 0x80, 0xA0, 0x80, 0x0, 0x80, 0xA0, 0xA0, 0x0, 0x80, 0xA0, 0xC0, 0x0, 0x80, 0xA0, 0xE0, 0x0, 0x80, 0xC0, 0x0, 0x0, 0x80, 0xC0, 0x20, 0x0, 0x80, 0xC0, 0x40, 0x0, 0x80, 0xC0, 0x60, 0x0, 0x80, 0xC0, 0x80, 0x0, 0x80, 0xC0, 0xA0, 0x0, 0x80, 0xC0, 0xC0, 0x0, 0x80, 0xC0, 0xE0, 0x0, 0x80, 0xE0, 0x0, 0x0, 0x80, 0xE0, 0x20, 0x0, 0x80, 0xE0, 0x40, 0x0, 0x80, 0xE0, 0x60, 0x0, 0x80, 0xE0, 0x80, 0x0, 0x80, 0xE0, 0xA0, 0x0, 0x80, 0xE0, 0xC0, 0x0, 0x80, 0xE0, 0xE0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0xC0, 0x0, 0x20, 0x0, 0xC0, 0x0, 0x40, 0x0, 0xC0, 0x0, 0x60, 0x0, 0xC0, 0x0, 0x80, 0x0, 0xC0, 0x0, 0xA0, 0x0, 0xC0, 0x0, 0xC0, 0x0, 0xC0, 0x0, 0xE0, 0x0, 0xC0, 0x20, 0x0, 0x0, 0xC0, 0x20, 0x20, 0x0, 0xC0, 0x20, 0x40, 0x0, 0xC0, 0x20, 0x60, 0x0, 0xC0, 0x20, 0x80, 0x0, 0xC0, 0x20, 0xA0, 0x0, 0xC0, 0x20, 0xC0, 0x0, 0xC0, 0x20, 0xE0, 0x0, 0xC0, 0x40, 0x0, 0x0, 0xC0, 0x40, 0x20, 0x0, 0xC0, 0x40, 0x40, 0x0, 0xC0, 0x40, 0x60, 0x0, 0xC0, 0x40, 0x80, 0x0, 0xC0, 0x40, 0xA0, 0x0, 0xC0, 0x40, 0xC0, 0x0, 0xC0, 0x40, 0xE0, 0x0, 0xC0, 0x60, 0x0, 0x0, 0xC0, 0x60, 0x20, 0x0, 0xC0, 0x60, 0x40, 0x0, 0xC0, 0x60, 0x60, 0x0, 0xC0, 0x60, 0x80, 0x0, 0xC0, 0x60, 0xA0, 0x0, 0xC0, 0x60, 0xC0, 0x0, 0xC0, 0x60, 0xE0, 0x0, 0xC0, 0x80, 0x0, 0x0, 0xC0, 0x80, 0x20, 0x0, 0xC0, 0x80, 0x40, 0x0, 0xC0, 0x80, 0x60, 0x0, 0xC0, 0x80, 0x80, 0x0, 0xC0, 0x80, 0xA0, 0x0, 0xC0, 0x80, 0xC0, 0x0, 0xC0, 0x80, 0xE0, 0x0, 0xC0, 0xA0, 0x0, 0x0, 0xC0, 0xA0, 0x20, 0x0, 0xC0, 0xA0, 0x40, 0x0, 0xC0, 0xA0, 0x60, 0x0, 0xC0, 0xA0, 0x80, 0x0, 0xC0, 0xA0, 0xA0, 0x0, 0xC0, 0xA0, 0xC0, 0x0, 0xC0, 0xA0, 0xE0, 0x0, 0xC0, 0xC0, 0x0, 0x0, 0xC0, 0xC0, 0x20, 0x0, 0xC0, 0xC0, 0x40, 0x0, 0xC0, 0xC0, 0x60, 0x0, 0xC0, 0xC0, 0x80, 0x0, 0xC0, 0xC0, 0xA0, 0x0, 0xF0, 0xFB, 0xFF, 0x0, 0xA4, 0xA0, 0xA0, 0x0, 0x80, 0x80, 0x80, 0x0, 0x0, 0x0, 0xFF, 0x0, 0x0, 0xFF, 0x0, 0x0, 0x0, 0xFF, 0xFF, 0x0, 0xFF, 0x0, 0x0, 0x0, 0xFF, 0x0, 0xFF, 0x0, 0xFF, 0xFF, 0x0, 0x0, 0xFF, 0xFF, 0xFF, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xFF, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xFF, 0x0, 0x0, 0x0, 0x0, 0x0, 0xFF, 0x0, 0x0, 0x0, 0x0, 0xFF, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xFF, 0x0, 0x0, 0xFF, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xFF, 0xFF, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xFF, 0xFF, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xFF, 0x0, 0x0, 0xFF, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xFF, 0x0, 0x0, 0x0, 0x0, 0xFF, 0x0, 0x0, 0x0, 0x0, 0x0, 0xFF, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xFF, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
};

DESK_CONTROL DeskCtrl;

VOID DeskInit(VOID)
{
    DeskCtrl.DeskArea.X=OsdCtrl.ScreenArea.X;
    DeskCtrl.DeskArea.Y=OsdCtrl.ScreenArea.Y;
    DeskCtrl.DeskArea.W=OsdCtrl.ScreenArea.W;
    DeskCtrl.DeskArea.H=OsdCtrl.ScreenArea.H;
    DeskCtrl.DeskTimer.Timer=100;
    OsTimeTimerPut((OS_TIMER *)&DeskCtrl.DeskTimer);
    DeskCtrl.DeskEventTimer.Timer=100;
    OsTimeTimerPut((OS_TIMER *)&DeskCtrl.DeskEventTimer);
    DeskCtrl.State=DeskInitialState;

    // order of the following function could not be changed
    DeskWindowInit();
    DeskWorkWindowInit();
    DeskWorkbarInit(); 
    DeskActiveWindowInit();
    DeskInactiveWindowInit();
    // order of the the following function could be changed
    DeskDebugInit();
    DeskTimeInit();
    DeskControlPanelInit();
    DeskMenuInit();
    DeskMouseInit();
}

VOID DeskSvc(VOID)
{
    UINT8 ActiveWindowDrawed;
    UINT32 MouseData;
    WINDOW *pWindow,*pWindow2;
    WINDOW_TABLE *pTable;
    WINDOW_DEVICE *pDevice;

    switch(DeskCtrl.State){
        case DeskIdleState:
            break;
        case DeskInitialState:
			//{
			//EFI_GRAPHICS_OUTPUT_BLT_PIXEL Color = Bmp2Rgb(GfxPaletteClut[GFX_COLOR_LIGHTBLUE4]);
			//GOP->Blt(GOP,&Color,EfiBltVideoFill,0,0,5,5,30,20,0);
			//while(1){};
			//}
			SystemGuiCursorClear();
            DeskWorkWindowMemoryDraw();
            DeskWorkWindow2OsdUpdate();
            DeskWorkbarDraw();
            DeskMouseMapCapture();
            DeskCtrl.State=DeskRunState;
			TIMER_START = TRUE; //GDB : I don't sure this token that is necessary.
            break;
		
        case DeskRunState:
            if(KeyboardKeyBufferCheck()!=BUFFER_EMPTY) // handle keyboard signal
                WindowKeyBufferPut(DeskWindowActiveWindowGet(),KeyboardKeyBufferGet());
            ConsoleSvc(&DeskDebugCtrl.Console);
            DeskMouseSvc(); //handle mouse signal
            if(DeskMouseCtrl.HasMouse==TRUE){
                if(DeskMouseCtrl.MouseDirty==TRUE){ // mouse moving event
                    MouseData=(DeskMouseCtrl.MousePointer.X)+(DeskMouseCtrl.MousePointer.Y<<14);
                    if(DeskMouseCtrl.MouseLeftButton==BUTTON_PRESS) MouseData=MouseData|0x10000000;
                    if(DeskMouseCtrl.MouseRightButton==BUTTON_PRESS) MouseData=MouseData|0x20000000;
                    if(DeskMouseCtrl.MouseMiddleButton==BUTTON_PRESS) MouseData=MouseData|0x40000000;
                    WindowMouseBufferPut(DeskWindowActiveWindowGet(),MouseData);
                    DeskWindowMousePositionInfomationGet(&DeskMouseCtrl.MousePointer);
                    if(DeskMouseCtrl.pWindow!=DeskMouseCtrl.pCurrentWindow){
                        DeskMouseCtrl.pCurrentWindow=DeskMouseCtrl.pWindow;
                        if(DeskMouseCtrl.pWindow!=(WINDOW *)NULL){
                             //CaptionStringPrint(&DeskDebugCtrl.Caption,"\n");
                             //CaptionStringPrint(&DeskDebugCtrl.Caption,DeskMouseCtrl.pWindow->pTitle);
							 //SystemDrawStr(0,0,pWindow->pTitle);
                        }
                    }
                    if(DeskMouseCtrl.pTable!=DeskMouseCtrl.pCurrentTable){
                        DeskMouseCtrl.pCurrentTable=DeskMouseCtrl.pTable;
                        if(DeskMouseCtrl.pTable!=(WINDOW_TABLE *)NULL){
                            //CaptionStringPrint(&DeskDebugCtrl.Caption,"table");
                            //CaptionUINT8Print(&DeskDebugCtrl.Caption,DeskMouseCtrl.pTable->Type);
							//SystemDrawStr(0,0,"table");
                        }
                    }
                    if(DeskMouseCtrl.pDevice!=DeskMouseCtrl.pCurrentDevice){
                        DeskMouseCtrl.pCurrentDevice=DeskMouseCtrl.pDevice;
                        if(DeskMouseCtrl.pDevice!=(WINDOW_DEVICE *)NULL){
                            //CaptionStringPrint(&DeskDebugCtrl.Caption,"device");
                            //CaptionUINT8Print(&DeskDebugCtrl.Caption,DeskMouseCtrl.pDevice->Type);
                            //CaptionStringPrint(&DeskDebugCtrl.Caption,"num");
                            //CaptionUINT8Print(&DeskDebugCtrl.Caption,DeskMouseCtrl.pDevice->DeviceNumberLeft);
							//SystemDrawStr(0,0,"device");
                        }
                    }
                    DeskMouse2OsdUpdate();
                    DeskMouseCtrl.MouseDirty=FALSE;
                }
            }
            if((DeskMouseCtrl.MouseLeftButton==BUTTON_PRESS)&&(DeskMouseCtrl.MouseRightButton==BUTTON_PRESS)) 
				break; // press-two-button is not allowed 
            if((DeskMouseCtrl.MouseLeftButton==BUTTON_PRESS)&&(DeskMouseCtrl.MouseMiddleButton==BUTTON_PRESS)) 
				break; // press-two-button is not allowed 
            if((DeskMouseCtrl.MouseLeftButton==BUTTON_PRESS)&&(DeskMouseCtrl.MouseMiddleButton==BUTTON_PRESS)) 
				break; // press-two-button is not allowed 
			
            if(DeskMouseCtrl.MouseLeftButton==BUTTON_PRESS){ // mouse left button press event
                //GDB if(DeskMouseCtrl.MouseTimer.Timer!=0) 
				//GDB 	break; // Avoid mouse next press comes too fast.     
                DeskMouse2OsdClear(); // clear mouse image on osd

                //this is a special case for start button, re-click on start button s.t. start menu is cleared
                if((DeskMouseCtrl.pCurrentWindow==DeskWindowCtrl.WindowListHead)&&(DeskMouseCtrl.pCurrentTable==&DeskWorkbarCtrl.StartTable)
                 &&(DeskMouseCtrl.pCurrentDevice==&DeskWorkbarCtrl.WdStartButton)&&(DeskWindowCtrl.MenuWindowList!=(WINDOW *)NULL)){
                    gST->ConOut->SetCursorPosition(gST->ConOut,0,0);
					GDP(L"STATE 1\n");
					DeskWindowCtrl.MenuWindowList=(WINDOW *)NULL;
                    DeskWindowCtrl.pActiveWindow=DeskWindowCtrl.WindowListHead;
                    DeskWindowCtrl.pActiveWindow->Active=TRUE;
                    DeskWindowCtrl.pActiveWindow->Dirty=TRUE;
                    DeskWindowCtrl.WindowListChange=TRUE;
                    DeskWindowCtrl.ReclickStartButton=TRUE;
                }
				
                //this is a special case for start button, click on area out of start menu s.t. start menu is cleared
                if((DeskWindowCtrl.MenuWindowList!=(WINDOW *)NULL)&&(DeskMouseCtrl.pCurrentWindow->Type!=WINDOW_TYPE_STARTMENU)){
                    gST->ConOut->SetCursorPosition(gST->ConOut,0,0);
					GDP(L"STATE 2\n");
					DeskWindowCtrl.MenuWindowList=(WINDOW *)NULL;
                    DeskWindowCtrl.pActiveWindow=DeskWindowCtrl.WindowListHead;
                    DeskWindowCtrl.pActiveWindow->Active=TRUE;
                    DeskWindowCtrl.pActiveWindow->Dirty=TRUE;
                    DeskWindowCtrl.WindowListChange=TRUE;
                    DeskWindowCtrl.ReclickStartButton=FALSE;
                }
				
                ActiveWindowDrawed=FALSE;
                DeskWindowActiveWindowSet(DeskMouseCtrl.pCurrentWindow);
                pWindow=DeskWindowActiveWindowGet();
                if((DeskWindowWindowListCheck()==TRUE)||(DeskWindowInactiveWindowContentCheck()==TRUE)){
					gST->ConOut->SetCursorPosition(gST->ConOut,0,0);
					GDP(L"STATE 3\n");
                    DeskWindowInactiveWindowDraw();          // redraw inactive windows on work area memory
					DeskWorkWindow2OsdUpdate();
                    if((pWindow!=DeskWindowCtrl.WindowListHead)&&(pWindow!=DeskWindowCtrl.WindowListTail)){
                        DeskActiveWindowMemoryDraw(pWindow);
                        DeskActiveWindowMemory2OsdUpdate(pWindow);
                        ActiveWindowDrawed=TRUE;
                    }
                    DeskWorkbarWindowListDraw();
                }

                //force active window redraw because of DirectContentDraw
                if((DeskActiveWindowCtrl.DirectContentDraw==TRUE)&&(ActiveWindowDrawed==FALSE)){
					gST->ConOut->SetCursorPosition(gST->ConOut,0,0);
					GDP(L"STATE 4\n");
                    if((pWindow!=DeskWindowCtrl.WindowListHead)&&(pWindow!=DeskWindowCtrl.WindowListTail)){
                        DeskActiveWindowMemoryDraw(pWindow);
                        DeskActiveWindowMemory2OsdUpdate(pWindow);
                    }
                }
                DeskActiveWindowCtrl.DirectContentDraw=FALSE;
                //draw mouse again
                DeskMouseMapCapture(); 
                DeskMouseCursorDraw();
                DeskMouse2OsdDraw();
				gST->ConOut->SetCursorPosition(gST->ConOut,0,0);
				GDP(L"STATE 5\n");
                if(pWindow->Type==WINDOW_TYPE_STARTMENU){ // general window on desk
					gST->ConOut->SetCursorPosition(gST->ConOut,0,0);
					GDP(L"STATE 6\n");
                    if(DeskMouseCtrl.pCurrentTable==(WINDOW_TABLE *)&DeskMouseCtrl.pCurrentWindow->OutlineTable){
                        DeskMouseLeftButtonReleaseWait();
                    }
                    else if(DeskMouseCtrl.pCurrentTable==(WINDOW_TABLE *)&DeskMouseCtrl.pCurrentWindow->HeaderTable){   
                        DeskMouseLeftButtonReleaseWait();
                    }
                    else{
                        pTable=DeskMouseCtrl.pCurrentWindow->UserTableList;
                        while(pTable!=(WINDOW_TABLE *)NULL){
                            if(pTable==DeskMouseCtrl.pCurrentTable) break;
                            else pTable=pTable->Next;
                        }
                        if(pTable!=(WINDOW_TABLE *)NULL){
                            pDevice=DeskMouseCtrl.pCurrentDevice;
                            if(pDevice!=(WINDOW_DEVICE *)NULL){
                                switch(pDevice->Type){
                                    case WINDOW_DEVICE_BUTTON:
                                        DeskMouse2OsdClear();
                                        ((WINDOW_BUTTON *)pDevice->pDevice)->Status=WINDOW_BUTTON_PRESS;
                                        DeskDeviceButtonDraw(DESK_DEVICE_DRAW_OSD,pWindow,pTable,(WINDOW_BUTTON *)pDevice->pDevice);
                                        DeskMouseMapCapture();
                                        DeskMouseCursorDraw();
                                        DeskMouse2OsdDraw();
                                        DeskMouseLeftButtonReleaseWait();
                                        ((WINDOW_BUTTON *)pDevice->pDevice)->Status=WINDOW_BUTTON_RELEASE;
                                        DeskMouse2OsdClear();
                                        DeskDeviceButtonDraw(DESK_DEVICE_DRAW_OSD,pWindow,pTable,(WINDOW_BUTTON *)pDevice->pDevice);
                                        DeskMouseMapCapture();
                                        DeskMouseCursorDraw();
                                        DeskMouse2OsdDraw();
										
                                        // ensure selected device is the same after mouse key release
                                        if((DeskMouseCtrl.pWindow==pWindow) 
                                         &&(DeskMouseCtrl.pTable==pTable)
                                         &&(DeskMouseCtrl.pDevice==pDevice)){
                                            DeskMenuEventHandler(pDevice->DeviceNumberLeft);
                                            DeskMouse2OsdClear();
                                            DeskWindowInactiveWindowDraw();        // redraw inactive windows on work area memory
                                            DeskWorkWindow2OsdUpdate();
                                            pWindow2=DeskWindowActiveWindowGet();       //get actvie window pointer
                                            if((pWindow2!=DeskWindowCtrl.WindowListHead)
                                             &&(pWindow2!=DeskWindowCtrl.WindowListTail)){
                                                DeskActiveWindowMemoryDraw(pWindow2);   // draw active window on active window memory
                                                DeskActiveWindowMemory2OsdUpdate(pWindow2);
                                            }
											
                                            DeskWorkbarWindowListDraw();
                                            DeskMouseMapCapture();
                                            DeskMouseCursorDraw();
                                            DeskMouse2OsdDraw();
                                        }
                                        break;
                                    default:
                                        DeskMouseLeftButtonReleaseWait();
                                        break;
                                }
                            }
                            else DeskMouseLeftButtonReleaseWait();
                        }
                        else DeskMouseLeftButtonReleaseWait();
                    }
                }
                else if(pWindow==DeskWindowCtrl.WindowListHead){
					gST->ConOut->SetCursorPosition(gST->ConOut,0,0);
					GDP(L"STATE 7\n");
                    if(DeskMouseCtrl.pCurrentTable==&DeskWorkbarCtrl.StartTable){
                        if(DeskMouseCtrl.pCurrentDevice==&DeskWorkbarCtrl.WdStartButton){
                            if(DeskWindowCtrl.ReclickStartButton==TRUE){
                                DeskWindowCtrl.ReclickStartButton=FALSE;
                                DeskMouse2OsdClear();
                                ((WINDOW_BUTTON *)DeskWorkbarCtrl.WdStartButton.pDevice)->Status=WINDOW_BUTTON_PRESS;
                                DeskDeviceButtonDraw(DESK_DEVICE_DRAW_OSD,pWindow,DeskMouseCtrl.pCurrentTable,(WINDOW_BUTTON *)DeskMouseCtrl.pCurrentDevice->pDevice);
                                DeskMouseMapCapture(); 
                                DeskMouseCursorDraw();
                                DeskMouse2OsdDraw();
                                DeskMouseLeftButtonReleaseWait();
                                DeskMouse2OsdClear();
                                ((WINDOW_BUTTON *)DeskWorkbarCtrl.WdStartButton.pDevice)->Status=WINDOW_BUTTON_RELEASE;
                                DeskDeviceButtonDraw(DESK_DEVICE_DRAW_OSD,pWindow,DeskMouseCtrl.pCurrentTable,(WINDOW_BUTTON *)DeskMouseCtrl.pCurrentDevice->pDevice);                            
                                DeskMouseMapCapture(); 
                                DeskMouseCursorDraw();
                                DeskMouse2OsdDraw();
                            }
                            else{
                                DeskMouse2OsdClear(); // clear mouse image on osd
                                ((WINDOW_BUTTON *)DeskWorkbarCtrl.WdStartButton.pDevice)->Status=WINDOW_BUTTON_PRESS;
                                DeskDeviceButtonDraw(DESK_DEVICE_DRAW_OSD,pWindow,DeskMouseCtrl.pCurrentTable,(WINDOW_BUTTON *)DeskMouseCtrl.pCurrentDevice->pDevice);                                
                                if(DeskWindowCtrl.pActiveWindow!=(WINDOW *)NULL){
                                    DeskWindowCtrl.pActiveWindow->Active=FALSE;
                                    DeskWindowCtrl.pActiveWindow->Dirty=TRUE;
                                }
                                DeskWindowCtrl.pActiveWindow=&DeskMenuCtrl.StartWindow;
                                DeskMenuCtrl.StartWindow.Active=TRUE;
                                DeskMenuCtrl.StartWindow.Dirty=TRUE;
                                DeskMenuCtrl.StartWindow.State=DESK_WINDOW_STATE_ONDESK;
                                DeskMenuCtrl.StartWindow.Next=(WINDOW *)NULL;
                                DeskMenuCtrl.StartWindow.Prev=(WINDOW *)NULL;
                                DeskWindowCtrl.WindowListChange=TRUE;
                                DeskWindowCtrl.MenuWindowList=&DeskMenuCtrl.StartWindow;                         
                                DeskWindowInactiveWindowDraw();             // redraw inactive windows on work area memory
                                DeskWorkWindow2OsdUpdate();
                                DeskActiveWindowMemoryDraw(DeskWindowCtrl.pActiveWindow);       // draw active window on active window memory
								DeskActiveWindowMemory2OsdUpdate(DeskWindowCtrl.pActiveWindow);
								DeskWorkbarWindowListDraw();
                                DeskMouseMapCapture(); 
                                DeskMouseCursorDraw();
                                DeskMouse2OsdDraw();
                                DeskMouseLeftButtonReleaseWait();
                                DeskMouse2OsdClear();
                                ((WINDOW_BUTTON *)DeskWorkbarCtrl.WdStartButton.pDevice)->Status=WINDOW_BUTTON_RELEASE;
                                DeskDeviceButtonDraw(DESK_DEVICE_DRAW_OSD,pWindow,DeskMouseCtrl.pCurrentTable,(WINDOW_BUTTON *)DeskMouseCtrl.pCurrentDevice->pDevice);                            
                                DeskMouseMapCapture(); 
                                DeskMouseCursorDraw();
                                DeskMouse2OsdDraw();
                            }
                        }
                        else DeskMouseLeftButtonReleaseWait();
                    }
                    else if(DeskMouseCtrl.pCurrentTable==&DeskWorkbarCtrl.WindowListTable){
                        if(DeskMouseCtrl.pCurrentDevice!=(WINDOW_DEVICE *)NULL){
                            pWindow=(WINDOW *)(((WINDOW_WINDOWBOX *)DeskMouseCtrl.pCurrentDevice->pDevice)->pWindow);
                            if(pWindow!=(WINDOW *)NULL) {
                                DeskWindowActiveWindowToggle(pWindow);
                                if(DeskWindowWindowListCheck()==TRUE){
                                    DeskWindowInactiveWindowDraw();        // redraw inactive windows on work area memory
                                    DeskWorkWindow2OsdUpdate();
                                    pWindow2=DeskWindowActiveWindowGet();
                                    if((pWindow2!=DeskWindowCtrl.WindowListHead)
                                     &&(pWindow2!=DeskWindowCtrl.WindowListTail)){
                                        DeskActiveWindowMemoryDraw(pWindow2);   // draw active window on active window memory
                                        DeskActiveWindowMemory2OsdUpdate(pWindow2);
                                    }
                                    DeskWorkbarWindowListDraw();       //And it will be not dirty,and no draw again.
                                }
                            }
                            DeskMouseMapCapture();
                            DeskMouseCursorDraw();
                            DeskMouse2OsdDraw();
                        }
                        DeskMouseLeftButtonReleaseWait();
                    }
                    else if(DeskMouseCtrl.pCurrentTable==&DeskWorkbarCtrl.TimeTable){
                        if((DeskMouseCtrl.pCurrentDevice==&DeskWorkbarCtrl.WdTimeBox)
                         &&(DeskTimeCtrl.Window.State==DESK_WINDOW_STATE_OFFDESK)){
                            DeskWindowWindowPut((WINDOW *)&DeskTimeCtrl.Window); 
                        }
                        DeskMouseLeftButtonReleaseWait();
                    }
                    else DeskMouseLeftButtonReleaseWait();
                }
                else if(pWindow==DeskWindowCtrl.WindowListTail){ // work window
					gST->ConOut->SetCursorPosition(gST->ConOut,0,0);
					GDP(L"STATE 8\n");
                    DeskMouseLeftButtonReleaseWait();
                }
                else{ // general window on desk
					gST->ConOut->SetCursorPosition(gST->ConOut,0,0);
					GDP(L"STATE 9\n");
                    if(DeskMouseCtrl.pCurrentTable==(WINDOW_TABLE *)&DeskMouseCtrl.pCurrentWindow->OutlineTable){
                        pDevice=DeskMouseCtrl.pCurrentDevice;
                        if((pDevice!=(WINDOW_DEVICE *)NULL)&&(pDevice->Type==WINDOW_DEVICE_EDGE)){
                            switch(((WINDOW_EDGE *)pDevice->pDevice)->Type){
                                case WINDOW_EDGE_TOP:
                                    DeskMouseCtrl.OriginalWindowEdge.X=DeskMouseCtrl.MousePointer.X;
                                    DeskMouseCtrl.OriginalWindowEdge.Y=DeskMouseCtrl.MousePointer.Y;
                                    DeskMouseLeftButtonReleaseWait2();
                                    DeskMouse2OsdClear();
                                    DeskMouseCtrl.NewWindowEdge.X=DeskMouseCtrl.MousePointer.X;
                                    DeskMouseCtrl.NewWindowEdge.Y=DeskMouseCtrl.MousePointer.Y;
                                    if(DeskMouseCtrl.OriginalWindowEdge.Y!=DeskMouseCtrl.NewWindowEdge.Y){
                                        DeskActiveWindowAdjust(DESK_MOUSE_CURSOR_UP,pWindow);
                                        DeskWindowInactiveWindowDraw();                // redraw inactive windows on work area memory
                                        DeskWorkWindow2OsdUpdate();                    // update work window to osd
                                        if((pWindow!=DeskWindowCtrl.WindowListHead)
                                         &&(pWindow!=DeskWindowCtrl.WindowListTail)){
                                            DeskActiveWindowMemoryDraw(pWindow);       // draw active window on active window memory
                                            DeskActiveWindowMemory2OsdUpdate(pWindow); // update active window to osd
                                        }
                                    }  
                                    DeskMouseMapCapture();
                                    DeskMouseCursorDraw();
                                    DeskMouse2OsdDraw();
                                    break;
                                case WINDOW_EDGE_BOTTOM:
                                    DeskMouseCtrl.OriginalWindowEdge.X=DeskMouseCtrl.MousePointer.X;
                                    DeskMouseCtrl.OriginalWindowEdge.Y=DeskMouseCtrl.MousePointer.Y;
                                    DeskMouseLeftButtonReleaseWait2();
                                    DeskMouse2OsdClear();
                                    DeskMouseCtrl.NewWindowEdge.X=DeskMouseCtrl.MousePointer.X;
                                    DeskMouseCtrl.NewWindowEdge.Y=DeskMouseCtrl.MousePointer.Y;
                                    if(DeskMouseCtrl.OriginalWindowEdge.Y!=DeskMouseCtrl.NewWindowEdge.Y){      
                                        DeskActiveWindowAdjust(DESK_MOUSE_CURSOR_DOWN,pWindow);
                                        DeskWindowInactiveWindowDraw();                // redraw inactive windows on work area memory
                                        DeskWorkWindow2OsdUpdate();                    // update work window to osd
                                       if((pWindow!=DeskWindowCtrl.WindowListHead)
                                         &&(pWindow!=DeskWindowCtrl.WindowListTail)){
                                            DeskActiveWindowMemoryDraw(pWindow);       // draw active window on active window memory
                                            DeskActiveWindowMemory2OsdUpdate(pWindow); // update active window to osd
                                        }
                                    }  
                                    DeskMouseMapCapture();
                                    DeskMouseCursorDraw();
                                    DeskMouse2OsdDraw();
                                    break;
                                case WINDOW_EDGE_RIGHT:
                                    DeskMouseCtrl.OriginalWindowEdge.X=DeskMouseCtrl.MousePointer.X;
                                    DeskMouseCtrl.OriginalWindowEdge.Y=DeskMouseCtrl.MousePointer.Y;
                                    DeskMouseLeftButtonReleaseWait2();
                                    DeskMouse2OsdClear();
                                    DeskMouseCtrl.NewWindowEdge.X=DeskMouseCtrl.MousePointer.X;
                                    DeskMouseCtrl.NewWindowEdge.Y=DeskMouseCtrl.MousePointer.Y;
                                    if(DeskMouseCtrl.OriginalWindowEdge.X!=DeskMouseCtrl.NewWindowEdge.X){      
                                        DeskActiveWindowAdjust(DESK_MOUSE_CURSOR_RIGHT,pWindow);
                                        DeskWindowInactiveWindowDraw();                // redraw inactive windows on work area memory
                                        DeskWorkWindow2OsdUpdate();                    // update work window to osd
                                        if((pWindow!=DeskWindowCtrl.WindowListHead)
                                         &&(pWindow!=DeskWindowCtrl.WindowListTail)){
                                            DeskActiveWindowMemoryDraw(pWindow);       // draw active window on active window memory
                                            DeskActiveWindowMemory2OsdUpdate(pWindow); // update active window to osd
                                        }
                                    }  
                                    DeskMouseMapCapture();
                                    DeskMouseCursorDraw();
                                    DeskMouse2OsdDraw();
                                    break;
                                case WINDOW_EDGE_LEFT:                                       
                                    DeskMouseCtrl.OriginalWindowEdge.X=DeskMouseCtrl.MousePointer.X;
                                    DeskMouseCtrl.OriginalWindowEdge.Y=DeskMouseCtrl.MousePointer.Y;
                                    DeskMouseLeftButtonReleaseWait2();
                                    DeskMouse2OsdClear();
                                    DeskMouseCtrl.NewWindowEdge.X=DeskMouseCtrl.MousePointer.X;
                                    DeskMouseCtrl.NewWindowEdge.Y=DeskMouseCtrl.MousePointer.Y;
                                    if(DeskMouseCtrl.OriginalWindowEdge.X!=DeskMouseCtrl.NewWindowEdge.X){    
                                        DeskActiveWindowAdjust(DESK_MOUSE_CURSOR_LEFT,pWindow);
                                        DeskWindowInactiveWindowDraw();        // redraw inactive windows on work area memory
                                        DeskWorkWindow2OsdUpdate();            // update work window to osd
                                        if((pWindow!=DeskWindowCtrl.WindowListHead)
                                         &&(pWindow!=DeskWindowCtrl.WindowListTail)){
                                            DeskActiveWindowMemoryDraw(pWindow);   // draw active window on active window memory
                                            DeskActiveWindowMemory2OsdUpdate(pWindow); // update active window to osd
                                        }
                                    }        
                                    DeskMouseMapCapture();
                                    DeskMouseCursorDraw();
                                    DeskMouse2OsdDraw();
                                    break;
                                case WINDOW_EDGE_TOPLEFT:
                                    DeskMouseCtrl.OriginalWindowEdge.X=DeskMouseCtrl.MousePointer.X;
                                    DeskMouseCtrl.OriginalWindowEdge.Y=DeskMouseCtrl.MousePointer.Y;
                                    DeskMouseLeftButtonReleaseWait2();
                                    DeskMouse2OsdClear();
                                    DeskMouseCtrl.NewWindowEdge.X=DeskMouseCtrl.MousePointer.X;
                                    DeskMouseCtrl.NewWindowEdge.Y=DeskMouseCtrl.MousePointer.Y;
                                    if(DeskMouseCtrl.OriginalWindowEdge.X!=DeskMouseCtrl.NewWindowEdge.X){    
                                        DeskActiveWindowAdjust(DESK_MOUSE_CURSOR_LEFTUP,pWindow);
                                        DeskWindowInactiveWindowDraw();        // redraw inactive windows on work area memory
                                        DeskWorkWindow2OsdUpdate();            // update work window to osd
                                        if((pWindow!=DeskWindowCtrl.WindowListHead)
                                         &&(pWindow!=DeskWindowCtrl.WindowListTail)){
                                            DeskActiveWindowMemoryDraw(pWindow);   // draw active window on active window memory
                                            DeskActiveWindowMemory2OsdUpdate(pWindow); // update active window to osd
                                        }
                                    }        
                                    DeskMouseMapCapture();
                                    DeskMouseCursorDraw();
                                    DeskMouse2OsdDraw();
                                    break;
                                case WINDOW_EDGE_TOPRIGHT:
                                    DeskMouseCtrl.OriginalWindowEdge.X=DeskMouseCtrl.MousePointer.X;
                                    DeskMouseCtrl.OriginalWindowEdge.Y=DeskMouseCtrl.MousePointer.Y;
                                    DeskMouseLeftButtonReleaseWait2();
                                    DeskMouse2OsdClear();
                                    DeskMouseCtrl.NewWindowEdge.X=DeskMouseCtrl.MousePointer.X;
                                    DeskMouseCtrl.NewWindowEdge.Y=DeskMouseCtrl.MousePointer.Y;
                                    if(DeskMouseCtrl.OriginalWindowEdge.X!=DeskMouseCtrl.NewWindowEdge.X){    
                                        DeskActiveWindowAdjust(DESK_MOUSE_CURSOR_RIGHTUP,pWindow);
                                        DeskWindowInactiveWindowDraw();        // redraw inactive windows on work area memory
                                        DeskWorkWindow2OsdUpdate();            // update work window to osd
                                        if((pWindow!=DeskWindowCtrl.WindowListHead)
                                         &&(pWindow!=DeskWindowCtrl.WindowListTail)){
                                            DeskActiveWindowMemoryDraw(pWindow);   // draw active window on active window memory
                                            DeskActiveWindowMemory2OsdUpdate(pWindow); // update active window to osd
                                        }
                                    }        
                                    DeskMouseMapCapture();
                                    DeskMouseCursorDraw();
                                    DeskMouse2OsdDraw();
                                    break;
                                case WINDOW_EDGE_BOTTOMLEFT:
                                    DeskMouseCtrl.OriginalWindowEdge.X=DeskMouseCtrl.MousePointer.X;
                                    DeskMouseCtrl.OriginalWindowEdge.Y=DeskMouseCtrl.MousePointer.Y;
                                    DeskMouseLeftButtonReleaseWait2();
                                    DeskMouse2OsdClear();
                                    DeskMouseCtrl.NewWindowEdge.X=DeskMouseCtrl.MousePointer.X;
                                    DeskMouseCtrl.NewWindowEdge.Y=DeskMouseCtrl.MousePointer.Y;
                                    if(DeskMouseCtrl.OriginalWindowEdge.X!=DeskMouseCtrl.NewWindowEdge.X){    
                                        DeskActiveWindowAdjust(DESK_MOUSE_CURSOR_LEFTDOWN,pWindow);
                                        DeskWindowInactiveWindowDraw();        // redraw inactive windows on work area memory
                                        DeskWorkWindow2OsdUpdate();            // update work window to osd
                                        if((pWindow!=DeskWindowCtrl.WindowListHead)
                                         &&(pWindow!=DeskWindowCtrl.WindowListTail)){
                                            DeskActiveWindowMemoryDraw(pWindow);   // draw active window on active window memory
                                            DeskActiveWindowMemory2OsdUpdate(pWindow); // update active window to osd
                                        }
                                    }        
                                    DeskMouseMapCapture();
                                    DeskMouseCursorDraw();
                                    DeskMouse2OsdDraw();
                                    break;
                                case WINDOW_EDGE_BOTTOMRIGHT:
                                    DeskMouseCtrl.OriginalWindowEdge.X=DeskMouseCtrl.MousePointer.X;
                                    DeskMouseCtrl.OriginalWindowEdge.Y=DeskMouseCtrl.MousePointer.Y;
                                    DeskMouseLeftButtonReleaseWait2();
                                    DeskMouse2OsdClear();
                                    DeskMouseCtrl.NewWindowEdge.X=DeskMouseCtrl.MousePointer.X;
                                    DeskMouseCtrl.NewWindowEdge.Y=DeskMouseCtrl.MousePointer.Y;
                                    if(DeskMouseCtrl.OriginalWindowEdge.X!=DeskMouseCtrl.NewWindowEdge.X){    
                                        DeskActiveWindowAdjust(DESK_MOUSE_CURSOR_RIGHTDOWN,pWindow);
                                        DeskWindowInactiveWindowDraw();        // redraw inactive windows on work area memory
                                        DeskWorkWindow2OsdUpdate();            // update work window to osd
                                        if((pWindow!=DeskWindowCtrl.WindowListHead)
                                         &&(pWindow!=DeskWindowCtrl.WindowListTail)){
                                            DeskActiveWindowMemoryDraw(pWindow);   // draw active window on active window memory
                                            DeskActiveWindowMemory2OsdUpdate(pWindow); // update active window to osd
                                        } 
                                    }        
                                    DeskMouseMapCapture();
                                    DeskMouseCursorDraw();
                                    DeskMouse2OsdDraw();
                                    break;
                                case WINDOW_EDGE_LEFTTOP:
                                    DeskMouseCtrl.OriginalWindowEdge.X=DeskMouseCtrl.MousePointer.X;
                                    DeskMouseCtrl.OriginalWindowEdge.Y=DeskMouseCtrl.MousePointer.Y;
                                    DeskMouseLeftButtonReleaseWait2();
                                    DeskMouse2OsdClear();
                                    DeskMouseCtrl.NewWindowEdge.X=DeskMouseCtrl.MousePointer.X;
                                    DeskMouseCtrl.NewWindowEdge.Y=DeskMouseCtrl.MousePointer.Y;
                                    if(DeskMouseCtrl.OriginalWindowEdge.X!=DeskMouseCtrl.NewWindowEdge.X){    
                                        DeskActiveWindowAdjust(DESK_MOUSE_CURSOR_LEFTUP,pWindow);
                                        DeskWindowInactiveWindowDraw();                // redraw inactive windows on work area memory
                                        DeskWorkWindow2OsdUpdate();                    // update work window to osd
                                        if((pWindow!=DeskWindowCtrl.WindowListHead)
                                         &&(pWindow!=DeskWindowCtrl.WindowListTail)){
                                            DeskActiveWindowMemoryDraw(pWindow);       // draw active window on active window memory
                                            DeskActiveWindowMemory2OsdUpdate(pWindow); // update active window to osd
                                        }
                                    }        
                                    DeskMouseMapCapture();
                                    DeskMouseCursorDraw();
                                    DeskMouse2OsdDraw();
                                    break;
                                case WINDOW_EDGE_RIGHTTOP:
                                    DeskMouseCtrl.OriginalWindowEdge.X=DeskMouseCtrl.MousePointer.X;
                                    DeskMouseCtrl.OriginalWindowEdge.Y=DeskMouseCtrl.MousePointer.Y;
                                    DeskMouseLeftButtonReleaseWait2();
                                    DeskMouse2OsdClear();
                                    DeskMouseCtrl.NewWindowEdge.X=DeskMouseCtrl.MousePointer.X;
                                    DeskMouseCtrl.NewWindowEdge.Y=DeskMouseCtrl.MousePointer.Y;
                                    if(DeskMouseCtrl.OriginalWindowEdge.X!=DeskMouseCtrl.NewWindowEdge.X){    
                                        DeskActiveWindowAdjust(DESK_MOUSE_CURSOR_RIGHTUP,pWindow);
                                        DeskWindowInactiveWindowDraw();        // redraw inactive windows on work area memory
                                        DeskWorkWindow2OsdUpdate();            // update work window to osd
                                        if((pWindow!=DeskWindowCtrl.WindowListHead)
                                         &&(pWindow!=DeskWindowCtrl.WindowListTail)){
                                            DeskActiveWindowMemoryDraw(pWindow);   // draw active window on active window memory
                                            DeskActiveWindowMemory2OsdUpdate(pWindow); // update active window to osd
                                        }
                                    }
                                    DeskMouseMapCapture();
                                    DeskMouseCursorDraw();
                                    DeskMouse2OsdDraw();
                                    break;
                            }
                        }
                        else DeskMouseLeftButtonReleaseWait();
                    }
                    else if(DeskMouseCtrl.pCurrentTable==(WINDOW_TABLE *)&DeskMouseCtrl.pCurrentWindow->HeaderTable){
                        //CaptionStringPrint(&DeskDebugCtrl.Caption,"\nWINDOW_HEADER"); 
                        pTable=DeskMouseCtrl.pCurrentTable;
                        pDevice=DeskMouseCtrl.pCurrentDevice;
                        if(pDevice!=(WINDOW_DEVICE *)NULL){
                            switch(((WINDOW_BUTTON *)pDevice->pDevice)->Type){
                                case WINDOW_BUTTON_HIDE:
                                    DeskMouse2OsdClear();
                                    ((WINDOW_BUTTON *)pDevice->pDevice)->Status=WINDOW_BUTTON_PRESS;
                                    DeskDeviceButtonDraw(DESK_DEVICE_DRAW_OSD,pWindow,pTable,(WINDOW_BUTTON *)pDevice->pDevice);
                                    DeskMouseMapCapture();
                                    DeskMouseCursorDraw();
                                    DeskMouse2OsdDraw();
                                    DeskMouseLeftButtonReleaseWait();
                                    DeskMouse2OsdClear();
                                    ((WINDOW_BUTTON *)pDevice->pDevice)->Status=WINDOW_BUTTON_RELEASE;
                                    DeskDeviceButtonDraw(DESK_DEVICE_DRAW_OSD,pWindow,pTable,(WINDOW_BUTTON *)pDevice->pDevice);
                                    DeskMouseMapCapture();
                                    DeskMouseCursorDraw();
                                    DeskMouse2OsdDraw();
                                    // ensure selected device is the same after mouse key release
                                    if((DeskMouseCtrl.pWindow==pWindow)&&(DeskMouseCtrl.pTable==pTable)&&(DeskMouseCtrl.pDevice==pDevice)){
                                        DeskMouse2OsdClear();                           //kill normal mouse image
                                        DeskWindowWindowHideSet(pWindow);                  //set active window minimun
                                        DeskWindowInactiveWindowDraw();                //redraw inactive windows on work area memory
                                        DeskWorkWindow2OsdUpdate();                    //update work window to osd
                                        pWindow=DeskWindowActiveWindowGet();               //get actvie window pointer
                                        if((pWindow!=DeskWindowCtrl.WindowListHead)
                                         &&(pWindow!=DeskWindowCtrl.WindowListTail)){
                                            DeskActiveWindowMemoryDraw(pWindow);       //draw active window on active window memory
                                            DeskActiveWindowMemory2OsdUpdate(pWindow); // update active window to osd
                                        }
                                        DeskWorkbarWindowListDraw();
                                        DeskMouseMapCapture();
                                        DeskMouseCursorDraw();
                                        DeskMouse2OsdDraw();
                                        //CaptionStringPrint(&DeskDebugCtrl.Caption,"\nWINDOW_BUTTON_HIDE"); 
                                    }
                                    break;
                                case WINDOW_BUTTON_MAXIMUN:
                                    DeskMouse2OsdClear();
                                    ((WINDOW_BUTTON *)pDevice->pDevice)->Status=WINDOW_BUTTON_PRESS;
                                    DeskDeviceButtonDraw(DESK_DEVICE_DRAW_OSD,pWindow,pTable,(WINDOW_BUTTON *)pDevice->pDevice);
                                    DeskMouseMapCapture();
                                    DeskMouseCursorDraw();
                                    DeskMouse2OsdDraw();
                                    DeskMouseLeftButtonReleaseWait();
                                    ((WINDOW_BUTTON *)pDevice->pDevice)->Status=WINDOW_BUTTON_RELEASE;
                                    DeskMouse2OsdClear();
                                    DeskDeviceButtonDraw(DESK_DEVICE_DRAW_OSD,pWindow,pTable,(WINDOW_BUTTON *)pDevice->pDevice);
                                    DeskMouseMapCapture();
                                    DeskMouseCursorDraw();
                                    DeskMouse2OsdDraw();
                                    // ensure selected device is the same after mouse key release
                                    if((DeskMouseCtrl.pWindow==pWindow)&&(DeskMouseCtrl.pTable==pTable)&&(DeskMouseCtrl.pDevice==pDevice)){
                                        //todo:recovery window to maximun
                                        //CaptionStringPrint(&DeskDebugCtrl.Caption,"\nWINDOW_ICON_MAXIMUN");
                                    }
                                    break;
                                case WINDOW_BUTTON_CLOSE:
                                    DeskMouse2OsdClear();
                                    ((WINDOW_BUTTON *)pDevice->pDevice)->Status=WINDOW_BUTTON_PRESS;
                                    DeskDeviceButtonDraw(DESK_DEVICE_DRAW_OSD,pWindow,pTable,(WINDOW_BUTTON *)pDevice->pDevice);
                                    DeskMouseMapCapture();
                                    DeskMouseCursorDraw();
                                    DeskMouse2OsdDraw();
                                    DeskMouseLeftButtonReleaseWait();
                                    ((WINDOW_BUTTON *)pDevice->pDevice)->Status=WINDOW_BUTTON_RELEASE;
                                    DeskMouse2OsdClear();
                                    DeskDeviceButtonDraw(DESK_DEVICE_DRAW_OSD,pWindow,pTable,(WINDOW_BUTTON *)pDevice->pDevice);
                                    DeskMouseMapCapture();
                                    DeskMouseCursorDraw();
                                    DeskMouse2OsdDraw();
                                    // ensure selected device is the same after mouse key release
                                    if((DeskMouseCtrl.pWindow==pWindow)&&(DeskMouseCtrl.pTable==pTable)&&(DeskMouseCtrl.pDevice==pDevice)){
                                        //CaptionStringPrint(&DeskDebugCtrl.Caption,"\nWINDOW_ICON_CLOSE");
                                        DeskMouse2OsdClear();  
                                        if(pWindow->Type==WINDOW_TYPE_TIME){
                                            DeskWindowActiveWindowDelete(pWindow);
                                        }
                                        else if(pWindow->Type==WINDOW_TYPE_DESKDEBUG){
                                            DeskWindowActiveWindowDelete(pWindow);
                                        }
                                        else if(pWindow->Type==WINDOW_TYPE_CONTROLPANEL){
                                            DeskWindowActiveWindowDelete(pWindow);
                                        }
                                        else if(pWindow->Type==WINDOW_TYPE_APPLICATION){
                                            pWindow->MessageAck=WINDOW_WM_ACK_NONE;
                                            pWindow->Message=WINDOW_WM_CLOSE;
                                            DeskCtrl.DeskEventTimer.Timer=1000;
                                            while((pWindow->MessageAck==WINDOW_WM_ACK_NONE)&&(DeskCtrl.DeskEventTimer.Timer!=0)) OsTaskSwitchOut();
                                            if(DeskCtrl.DeskEventTimer.Timer==0){
                                                //CaptionStringPrint(&DeskDebugCtrl.Caption,"\ntask has no response");
                                            }
                                            else{
                                                DeskWindowActiveWindowDelete(pWindow);
                                            }
                                        }
                                        pWindow=DeskWindowActiveWindowGet();               //get actvie window pointer
                                        if(DeskWindowWindowListCheck()==TRUE){
                                            DeskWindowInactiveWindowDraw();                // redraw inactive windows on work area memory
                                            DeskWorkWindow2OsdUpdate();                    // update work window to osd
                                            if((pWindow!=DeskWindowCtrl.WindowListHead)
                                             &&(pWindow!=DeskWindowCtrl.WindowListTail)){
                                                DeskActiveWindowMemoryDraw(pWindow);       // draw active window on active window memory
                                                DeskActiveWindowMemory2OsdUpdate(pWindow); // update active window to osd
                                            }
                                            DeskWorkbarWindowListDraw();   
                                        }
                                        DeskMouseMapCapture();
                                        DeskMouseCursorDraw();
                                        DeskMouse2OsdDraw();
                                    }                                    
                                    break;
                                default:
                                    //CaptionStringPrint(&DeskDebugCtrl.Caption,"\nHEADER NONE");
                                    //CaptionUINT8Print(&DeskDebugCtrl.Caption,((WINDOW_BUTTON *)pDevice->pDevice)->Type);
                                    break;
                            }
                            //DeskMouseLeftButtonReleaseWait();
                        }
                        else{
                            //window moving...mouse cursor is not at icons,then it is case for window moving
                            if(pWindow->Removable==TRUE){
                                DeskMouse2OsdClear();
                                DeskActiveWindowMoveInit(pWindow);
                                DeskActiveWindowMovingMouseMapCapture(pWindow);    //capture
                                DeskActiveWindowMovingMouseCursorDraw(pWindow);
                                DeskActiveWindowCtrl.ActiveWindowDirty=TRUE;       //set TRUE for DeskActiveWindowMemory2OsdUpdate()
                                DeskActiveWindowMemory2OsdUpdate(pWindow);
                                while(DeskMouseCtrl.MouseLeftButton==BUTTON_PRESS){
                                    if(!MULTTASK)MouseDataScan();
									DeskActiveWindowMoveSvc(pWindow);
                                }
                                DeskActiveWindowMovingMouseMapRecovery(pWindow);   //capture
                                DeskActiveWindowCtrl.ActiveWindowDirty=TRUE;       //force active window update to osd
                                DeskActiveWindowMemory2OsdUpdate(pWindow);
                                DeskActiveWindowMoveStop(pWindow);
                                DeskMouseMapCapture();
                            }
                            DeskMouseLeftButtonReleaseWait();
                        }
                    }
                    else{
                        pTable=DeskMouseCtrl.pCurrentWindow->UserTableList;
                        while(pTable!=(WINDOW_TABLE *)NULL){
                            if(pTable==DeskMouseCtrl.pCurrentTable) break;
                            else pTable=pTable->Next;
                        }
                        if(pTable!=(WINDOW_TABLE *)NULL){
                            //CaptionStringPrint(&DeskDebugCtrl.Caption,"user table");
                            pDevice=DeskMouseCtrl.pCurrentDevice;
                            if(pDevice!=(WINDOW_DEVICE *)NULL){
                                switch(pDevice->Type){
                                    case WINDOW_DEVICE_BUTTON:
                                        //CaptionStringPrint(&DeskDebugCtrl.Caption,"button");
                                        DeskMouse2OsdClear();
                                        ((WINDOW_BUTTON *)pDevice->pDevice)->Status=WINDOW_BUTTON_PRESS;
                                        DeskDeviceButtonDraw(DESK_DEVICE_DRAW_OSD,pWindow,pTable,(WINDOW_BUTTON *)pDevice->pDevice);
                                        DeskMouseMapCapture();
                                        DeskMouseCursorDraw();
                                        DeskMouse2OsdDraw();
                                        DeskMouseLeftButtonReleaseWait();
                                        ((WINDOW_BUTTON *)pDevice->pDevice)->Status=WINDOW_BUTTON_RELEASE;
                                        DeskMouse2OsdClear();
                                        DeskDeviceButtonDraw(DESK_DEVICE_DRAW_OSD,pWindow,pTable,(WINDOW_BUTTON *)pDevice->pDevice);
                                        DeskMouseMapCapture();
                                        DeskMouseCursorDraw();
                                        DeskMouse2OsdDraw();
                                        // ensure selected device is the same after mouse key release
                                        if((DeskMouseCtrl.pWindow==pWindow) 
                                         &&(DeskMouseCtrl.pTable==pTable)
                                         &&(DeskMouseCtrl.pDevice==pDevice)){
                                            WindowEventBufferPut(DeskWindowActiveWindowGet(),pDevice->DeviceNumberLeft); 
                                        }
                                        break;
                                    default:
                                        DeskMouseLeftButtonReleaseWait();
                                        break;
                                }
                            }
                            else DeskMouseLeftButtonReleaseWait();
                        }
                        else DeskMouseLeftButtonReleaseWait();
                    }
                }
                DeskMouseCtrl.MouseTimer.Timer=400;        // this value is a experience value
            }
            if(DeskMouseCtrl.MouseRightButton==BUTTON_PRESS){
                if(DeskMouseCtrl.MouseTimer.Timer!=0) break; 
                DeskMouse2OsdClear(); // clear mouse image on osd
                if((DeskWindowCtrl.MenuWindowList!=(WINDOW *)NULL)
                 &&(DeskMouseCtrl.pCurrentWindow->Type!=WINDOW_TYPE_STARTMENU)){
                    DeskWindowCtrl.MenuWindowList=(WINDOW *)NULL;
                    DeskWindowCtrl.pActiveWindow=DeskWindowCtrl.WindowListHead;
                    DeskWindowCtrl.pActiveWindow->Active=TRUE;
                    DeskWindowCtrl.pActiveWindow->Dirty=TRUE;
                    DeskWindowCtrl.WindowListChange=TRUE;
                    DeskWindowCtrl.ReclickStartButton=FALSE;
                }
                DeskWindowActiveWindowSet(DeskMouseCtrl.pCurrentWindow);
                pWindow=DeskWindowActiveWindowGet();
                if((DeskWindowWindowListCheck()==TRUE)||(DeskWindowInactiveWindowContentCheck()==TRUE)){
                    DeskWindowInactiveWindowDraw();          // redraw inactive windows on work area memory
                    DeskWorkWindow2OsdUpdate();
                    if((pWindow!=DeskWindowCtrl.WindowListHead)
                     &&(pWindow!=DeskWindowCtrl.WindowListTail)){
                        DeskActiveWindowMemoryDraw(pWindow);     // draw active window on active window memory
                        DeskActiveWindowMemory2OsdUpdate(pWindow);
                    }
                    DeskWorkbarWindowListDraw();
                }
                //draw mouse again
                DeskMouseMapCapture(); 
                DeskMouseCursorDraw();
                DeskMouse2OsdDraw();
                if(pWindow==DeskWindowCtrl.WindowListHead){                    
                    if(DeskMouseCtrl.pCurrentTable==&DeskWorkbarCtrl.StartTable){
                        if(DeskMouseCtrl.pCurrentDevice==&DeskWorkbarCtrl.WdStartButton) 
                            DeskMouseRightButtonReleaseWait();
                        else DeskMouseRightButtonReleaseWait();
                    }
                    else if(DeskMouseCtrl.pCurrentTable==&DeskWorkbarCtrl.WindowListTable){
                        if(DeskMouseCtrl.pCurrentDevice!=(WINDOW_DEVICE *)NULL){
                            // press on window box
                            pWindow=(WINDOW *)(((WINDOW_WINDOWBOX *)DeskMouseCtrl.pCurrentDevice->pDevice)->pWindow);
                            if(pWindow!=(WINDOW *)NULL) {
                                DeskWindowActiveWindowToggle(pWindow);
                                if(DeskWindowWindowListCheck()==TRUE){
                                    DeskWindowInactiveWindowDraw();        // redraw inactive windows on work area memory
                                    DeskWorkWindow2OsdUpdate();
                                    pWindow2=DeskWindowActiveWindowGet();
                                    if((pWindow2!=DeskWindowCtrl.WindowListHead)
                                     &&(pWindow2!=DeskWindowCtrl.WindowListTail)){
                                        DeskActiveWindowMemoryDraw(pWindow2);   // draw active window on active window memory
                                        DeskActiveWindowMemory2OsdUpdate(pWindow2);
                                    }
                                    DeskWorkbarWindowListDraw();       //And it will be not dirty,and no draw again.
                                }
                            }
                            DeskMouseMapCapture();
                            DeskMouseCursorDraw();
                            DeskMouse2OsdDraw();
                        }
                        DeskMouseRightButtonReleaseWait();

                    }
                    else if(DeskMouseCtrl.pCurrentTable==&DeskWorkbarCtrl.TimeTable){
                        if(DeskMouseCtrl.pCurrentDevice==&DeskWorkbarCtrl.WdTimeBox){
                            DeskMouseRightButtonReleaseWait();
                        }
                        else DeskMouseRightButtonReleaseWait();
                    }
                    else DeskMouseRightButtonReleaseWait();
                }
                else if(pWindow==DeskWindowCtrl.WindowListTail){
                    DeskMouseRightButtonReleaseWait();
                }
                else{ // general window on desk
                    if(DeskMouseCtrl.pCurrentTable==(WINDOW_TABLE *)&DeskMouseCtrl.pCurrentWindow->OutlineTable){
                        DeskMouseRightButtonReleaseWait();
                    }
                    else if(DeskMouseCtrl.pCurrentTable==(WINDOW_TABLE *)&DeskMouseCtrl.pCurrentWindow->HeaderTable){
                        DeskMouseRightButtonReleaseWait();
                    }
                    else{
                        pTable=DeskMouseCtrl.pCurrentWindow->UserTableList;
                        while(pTable!=(WINDOW_TABLE *)NULL){
                            if(pTable==DeskMouseCtrl.pCurrentTable) break;
                            else pTable=pTable->Next;
                        }
                        if(pTable!=(WINDOW_TABLE *)NULL){
                            //CaptionStringPrint(&DeskDebugCtrl.Caption,"user table");
                            pDevice=DeskMouseCtrl.pCurrentDevice;
                            if(pDevice!=(WINDOW_DEVICE *)NULL){
                                switch(pDevice->Type){
                                    case WINDOW_DEVICE_BUTTON:
                                        DeskMouseRightButtonReleaseWait();
                                        if((DeskMouseCtrl.pWindow==pWindow) 
                                         &&(DeskMouseCtrl.pTable==pTable)
                                         &&(DeskMouseCtrl.pDevice==pDevice)){
                                            WindowEventBufferPut(DeskWindowActiveWindowGet(),pDevice->DeviceNumberRight); 
                                        }
                                        break;
                                    default:
                                        DeskMouseRightButtonReleaseWait();
                                        break;
                                }
                            }
                            else DeskMouseRightButtonReleaseWait();
                        }
                        else DeskMouseRightButtonReleaseWait();
                    }
                }
                DeskMouseCtrl.MouseTimer.Timer=400;        // this value is a experience value
            }
            if(DeskMouseCtrl.MouseMiddleButton==BUTTON_PRESS){
                if(DeskMouseCtrl.MouseTimer.Timer!=0) break; 
                DeskMouse2OsdClear(); // clear mouse image on osd
                if((DeskWindowCtrl.MenuWindowList!=(WINDOW *)NULL)
                 &&(DeskMouseCtrl.pCurrentWindow->Type!=WINDOW_TYPE_STARTMENU)){
                    DeskWindowCtrl.MenuWindowList=(WINDOW *)NULL;
                    DeskWindowCtrl.pActiveWindow=DeskWindowCtrl.WindowListHead;
                    DeskWindowCtrl.pActiveWindow->Active=TRUE;
                    DeskWindowCtrl.pActiveWindow->Dirty=TRUE;
                    DeskWindowCtrl.WindowListChange=TRUE;
                    DeskWindowCtrl.ReclickStartButton=FALSE;
                }
                DeskWindowActiveWindowSet(DeskMouseCtrl.pCurrentWindow);
                pWindow=DeskWindowActiveWindowGet();
                if((DeskWindowWindowListCheck()==TRUE)||(DeskWindowInactiveWindowContentCheck()==TRUE)){
                    DeskWindowInactiveWindowDraw();          // redraw inactive windows on work area memory
                    DeskWorkWindow2OsdUpdate();
                    DeskActiveWindowMemoryDraw(pWindow);     // draw active window on active window memory
                    DeskActiveWindowMemory2OsdUpdate(pWindow);
                    DeskWorkbarWindowListDraw();
                }
                //draw mouse again
                DeskMouseMapCapture(); 
                DeskMouseCursorDraw();
                DeskMouse2OsdDraw();
                if(pWindow==DeskWindowCtrl.WindowListHead) DeskMouseMiddleButtonReleaseWait();
                else if(pWindow==DeskWindowCtrl.WindowListTail) DeskMouseMiddleButtonReleaseWait();
                else{ // general window on desk
                    if(DeskMouseCtrl.pCurrentTable==(WINDOW_TABLE *)&DeskMouseCtrl.pCurrentWindow->OutlineTable){
                        DeskMouseMiddleButtonReleaseWait();
                    }
                    else if(DeskMouseCtrl.pCurrentTable==(WINDOW_TABLE *)&DeskMouseCtrl.pCurrentWindow->HeaderTable){
                        DeskMouseMiddleButtonReleaseWait();
                    }
                    else{
                        pTable=DeskMouseCtrl.pCurrentWindow->UserTableList;
                        while(pTable!=(WINDOW_TABLE *)NULL){
                            if(pTable==DeskMouseCtrl.pCurrentTable) break;
                            else pTable=pTable->Next;
                        }
                        if(pTable!=(WINDOW_TABLE *)NULL){
                            pDevice=DeskMouseCtrl.pCurrentDevice;
                            if(pDevice!=(WINDOW_DEVICE *)NULL){
                                switch(pDevice->Type){
                                    case WINDOW_DEVICE_BUTTON:
                                        DeskMouseMiddleButtonReleaseWait();
                                        if((DeskMouseCtrl.pWindow==pWindow) 
                                         &&(DeskMouseCtrl.pTable==pTable)
                                         &&(DeskMouseCtrl.pDevice==pDevice)){
                                            WindowEventBufferPut(DeskWindowActiveWindowGet(),pDevice->DeviceNumberMiddle); 
                                        }
                                        break;
                                    default:
                                        DeskMouseMiddleButtonReleaseWait();
                                        break;
                                }
                            }
                            else DeskMouseMiddleButtonReleaseWait();
                        }
                        else DeskMouseMiddleButtonReleaseWait();
                    }
                }
                DeskMouseCtrl.MouseTimer.Timer=400;        // this value is a experience value
            }
            if(DeskWorkbarCtrl.TimeMonitor.Timer==0){
                DeskMouse2OsdClear();  // kill mouse cursor
                RootTaskTimeGet(&DeskWorkbarCtrl.PreviousTime);
                DeskWorkbarTimeUpdate();
                DeskWorkbarTimeDraw();
                DeskWorkbarTimeWindowDraw();  
                DeskMouseMapCapture();   // redraw mouse
                DeskMouseCursorDraw();   // redraw mouse
                DeskMouse2OsdDraw();     // redraw mouse   
                DeskWorkbarCtrl.TimeMonitor.Timer=1000;               
            }
			
            if(DeskCtrl.DeskTimer.Timer==0){
				//GDB : Need to debug why active windows will clean if this block uncomment. 
                /*if(DeskWindowCtrl.WindowListChange==TRUE){
                    DeskWindowCtrl.WindowListChange=FALSE;
                    DeskMouse2OsdClear();  // kill mouse cursor
					DeskWindowInactiveWindowDraw();        // draw inactive windows on work area memory
                    DeskWorkWindow2OsdUpdate();
                    DeskWorkbarWindowListDraw();
                    DeskMouseMapCapture();   // redraw mouse
                    DeskMouseCursorDraw();   // redraw mouse
                    DeskMouse2OsdDraw();     // redraw mouse 
                }*/               	
                if(DeskWindowInactiveWindowContentCheck()==TRUE){   
                    DeskMouse2OsdClear();  // kill mouse cursor
                    DeskWindowInactiveWindowDraw();        // draw inactive windows on work area memory
                    DeskWorkWindow2OsdUpdate();
                    DeskMouseMapCapture();   // redraw mouse
                    DeskMouseCursorDraw();   // redraw mouse
                    DeskMouse2OsdDraw();     // redraw mouse 
                }               	
                //DeskWorkbarWindowListDraw();
                DeskCtrl.DeskTimer.Timer=1000;
            }
			
            //check if mouse is overlap with window to decide to redraw mouse or not
            pWindow=DeskWindowActiveWindowGet(); 
            if(pWindow==DeskWindowCtrl.WindowListHead);
            else if(pWindow==DeskWindowCtrl.WindowListTail);                
            else{
                MY_MUTEX mutex = OsEnterCritical();
                if(DeskWindowActiveWindowContentCheck()==TRUE){ //need timer?? 0.1 sec or ...
                    if(DeskMouseOverlapCheck(pWindow)==TRUE) DeskMouse2OsdClear();  // kill mouse cursor
                    if(DeskActiveWindowCtrl.DirectContentDraw==FALSE){
                        DeskActiveWindowMemoryDraw(pWindow);   // draw active window on active window
                        DeskActiveWindowMemory2OsdUpdate(pWindow);
                        DeskActiveWindowCtrl.DirectContentDraw=TRUE;
                    }
                    else{ 
                        //DeskActiveWindowMemoryDraw(pWindow);   // draw active window on active window
                        //DeskActiveWindowMemory2OsdUpdate(pWindow);
                        DeskActiveWindowContent2OsdUpdate(pWindow);
                    }
                    if(DeskMouseOverlapCheck(pWindow)==TRUE){
                        DeskMouseMapCapture();   // redraw mouse
                        DeskMouseCursorDraw();   // redraw mouse
                        DeskMouse2OsdDraw();     // redraw mouse
                    }
                }
                OsExitCritical(mutex);
            }
            break;
    }
}
