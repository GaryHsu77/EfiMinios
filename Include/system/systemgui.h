#ifndef SYSTEMGUI_H
#define SYSTEMGUI_H

#define SYSTEMGUI_WIDTH_MAX  320
#define SYSTEMGUI_HEIGHT_MAX 200

#define SYSTEMGUI_FONT_STYLE 0
#define SYSTEMGUI_CHAR_WIDTH 8
#define SYSTEMGUI_CHAR_HEIGHT 8
#define SYSTEMGUI_LINE_MAX 25
#define SYSTEMGUI_CHAR_MAX 40

typedef struct{
    UINT32 X;
    UINT32 Y;
}SYSTEMGUI_POSITION;

typedef struct{
    UINT32 H;
    UINT32 W;
}SYSTEMGUI_SIZE;

typedef struct{
    UINT32 BgColor;
    UINT32 FgColor;
    UINT32 FontColor;
}SYSTEMGUI_GFX;

typedef struct{
    UINT8 Width;
    UINT8 Height;
    //UINT8 UpperEdge;
    //UINT8 BottomEdge;
    //UINT8 LeftEdge;
    //UINT8 RightEdge;
}SYSTEMGUI_CELL;

typedef struct{
    UINT8  LineNum;
    UINT8  CharNum;
    UINT8  CurLineNum;
    UINT8  CurCharNum;
    UINT8  MaxCharNum;  // 640/8...80
    UINT8  MaxLineNum;  // 480/16...30
    UINT8  Height;      // line height...16
    UINT16 Width;       // line width...480
}SYSTEMGUI_TEXTLINE;

typedef struct{
    UINT8 Width;
    UINT8 Height;
}SYSTEMGUI_TEXTINFO;

typedef struct{
    UINT8 State;
    UINT8 Status;
    UINT8 Replace;
    UINT8 Initial;
    UINT8 ExecuteState;
    UINT8 ExecuteItem;
    UINT16 Timer;
    UINT8 CursorFlag;    // cursor status flag...on/off
    SYSTEMGUI_SIZE Area;
    SYSTEMGUI_POSITION Cursor;
    SYSTEMGUI_CELL Cell;
    SYSTEMGUI_GFX Gfx;
    SYSTEMGUI_TEXTLINE LineInfo;
    SYSTEMGUI_TEXTINFO TextInfo;
}SYSTEMGUI_CONTROL;

extern SYSTEMGUI_CONTROL SystemGuiCtrl;

VOID SystemGuiInit(VOID);
UINT8 SystemGuiSvc(UINT8);
UINT8 SystemGuiStatusCheck(UINT8);
UINT8 SystemGuiLineChange(UINT8);
VOID SystemGuiCursorAdvance(VOID);
VOID SystemGuiCharPut(UINT16 Data);
VOID SystemGuiDel(VOID);
VOID SystemGuiCursorToggle(VOID);
VOID SystemGuiCharDraw(UINT16 *);
VOID SystemGuiEmptyCharDraw(VOID);
VOID SystemGuiStringPrint(UINT16 *pString);
VOID SystemGuiCr(VOID);
VOID SystemGuiCursorClear(VOID);
VOID SystemDrawPoint(UINT32 x,UINT32 y,EFI_GRAPHICS_OUTPUT_BLT_PIXEL Color);
VOID SystemDrawStr(UINTN col,UINTN row,UINT8 *Str);

#endif

