#ifndef GUI_TEXT_H
#define GUI_TEXT_H

#define GUI_MODE_MAX  4
#define GUI_MODE_TEXT 0
#define GUI_MODE_MENU 1
#define GUI_MODE_XWIN 2
#define GUI_MODE_GAME 3

#define GUI_WIDTH_MAX  320
#define GUI_HEIGHT_MAX 200

#define GUI_TEXT_FONT_STYLE FONT8X8
//#define GUI_TEXT_FONT_STYLE FONT8X16

#if(GUI_TEXT_FONT_STYLE==FONT8X8)

#define GUI_TEXT_CHAR_WIDTH 8
#define GUI_TEXT_CHAR_HEIGHT 8
#define GUI_TEXT_LINE_MAX 25
#define GUI_TEXT_CHAR_MAX 40

#else

#define GUI_TEXT_CHAR_WIDTH 8
#define GUI_TEXT_CHAR_HEIGHT 16
#define GUI_TEXT_LINE_MAX 12
#define GUI_TEXT_CHAR_MAX 40

#endif

#define GUI_TEXT_WIDTH_MAX GUI_WIDTH_MAX
#define GUI_TEXT_HEIGHT_MAX GUI_HEIGHT_MAX

typedef struct{
    UINT32 X;
    UINT32 Y;
}GUI_TEXT_POSITION;

typedef struct{
    UINT32 H;
    UINT32 W;
}GUI_TEXT_SIZE;

typedef struct{
    UINT32 BgColor;
    UINT32 FgColor;
    UINT32 FontColor;
}GUI_TEXT_GFX;

typedef struct{
    UINT8 Width;
    UINT8 Height;
    //UINT8 UpperEdge;
    //UINT8 BottomEdge;
    //UINT8 LeftEdge;
    //UINT8 RightEdge;
}GUI_TEXT_CELL;

typedef struct{
    UINT8  LineNum;
    UINT8  CharNum;
    UINT8  CurLineNum;
    UINT8  CurCharNum;
    UINT8  MaxCharNum;  // 640/8...80
    UINT8  MaxLineNum;  // 480/16...30
    UINT8  Height;      // line height...16
    UINT16 Width;       // line width...480
}GUI_TEXT_TEXTLINE;

typedef struct{
    UINT8 Width;
    UINT8 Height;
}GUI_TEXT_TEXTINFO;

#define GUI_TEXT_BUFFER_MAX 100

typedef struct{
	UINT8 Put;
	UINT8 Data[GUI_TEXT_BUFFER_MAX];
}GUI_TEXT_BUFFER;

typedef struct{
    UINT8 State;
    UINT8 Status;
    UINT8 Replace;
    UINT8 Initial;
    UINT8 ExecuteState;
    UINT8 ExecuteItem;
    //UINT16 Timer;
    UINT8 CursorFlag;    // cursor status flag...on/off
    GUI_TEXT_SIZE Area;
    GUI_TEXT_POSITION Cursor;
    GUI_TEXT_CELL Cell;
    GUI_TEXT_GFX Gfx;
    GUI_TEXT_TEXTLINE LineInfo;
    GUI_TEXT_TEXTINFO TextInfo;
    //GUI_TEXT_BUFFER  Buffer;
    OS_TIMER MyTimer;
}GUI_TEXT_CONTROL;

//extern OSD_IMAGE GuiTextImage;
//extern GUI_TEXT_CONTROL GuiTextCtrl;
extern GUI_TEXT_CONTROL *pGuiTextCtrl;
extern void GuiTextInit(void);
extern void GuiTextSvc(void);
extern void GuiTextPlay(void);

//argument parser
/*#define GUI_TEXT_ARGUMENT_ARGV_MAX  10
#define GUI_TEXT_ARGUMENT_INDEX_MAX 100
typedef struct{
    unsigned char State;
    unsigned char Status;
    unsigned char HasInput;
    unsigned char Insert;
    unsigned char *pArgv[GUI_TEXT_ARGUMENT_ARGV_MAX];
    unsigned char Argc;
    unsigned char Index;
    unsigned char Get;
    unsigned char Put;
    unsigned char Data[GUI_TEXT_ARGUMENT_INDEX_MAX];
}GUI_TEXT_ARGUMENT_CONTROL;

extern GUI_TEXT_ARGUMENT_CONTROL GuiTextArgCtrl;
*/
void GuiTextInit(void);
void GuiTextSvc(void);
UINT8 GuiTextStatusCheck(void);
void GuiTextMemoryInit(void);
void GuiTextLineChange(void);
void GuiTextCursorAdvance(void);
void GuiTextGfxTextDraw(UINT8 *);
void GuiTextScroll(void);
void GuiTextCharPut(UINT8 Data);
void GuiTextDel(void);
void GuiTextCursorToggle(void);
void GuiTextCharDraw(UINT8 *);
void GuiTextCursorAdvance(void);
void GuiTextEmptyCharDraw(void);
void GuiTextStringPrint(UINT8 *pString);
void GuiTextCr(void);
void GuiTextCursorClear(void);
void GuiTextKeyParser(UINT8 Data);
void GuiDump(void);
void GuiTextUINT8Print(UINT8 Data);

#endif

