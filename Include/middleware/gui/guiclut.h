#ifndef  GUI_CLUT_H
#define  GUI_CLUT_H

#define GUI_VGA_COLOR_MAX 16

typedef enum{
GUI_VGA_COLOR_BLACK=0,
GUI_VGA_COLOR_BLUE,
GUI_VGA_COLOR_GREEN,
GUI_VGA_COLOR_CYAN,
GUI_VGA_COLOR_RED,
GUI_VGA_COLOR_MAGENTA,
GUI_VGA_COLOR_BROWN,
GUI_VGA_COLOR_LIGHTGRAY,
GUI_VGA_COLOR_DARKGRAY,
GUI_VGA_COLOR_LIGHTBLUE,
GUI_VGA_COLOR_LIGHTGREEN,
GUI_VGA_COLOR_LIGHTCYAN,
GUI_VGA_COLOR_LIGHTRED,
GUI_VGA_COLOR_LIGHTMAGENTA,
GUI_VGA_COLOR_YELLOW,
GUI_VGA_COLOR_WHITE,
}GUI_VGA_COLOR_ENUM;

extern const UINT8 GuiVgaClut[];

#endif
