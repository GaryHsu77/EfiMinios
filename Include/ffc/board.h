#ifndef BOARD_H
#define BOARD_H

#define BOARD_STATUS_FAIL 0
#define BOARD_STATUS_OK   1

typedef struct{
    UINT8 Status;
    UINT8 Dirty;
    UINT8 CursorFlag;
    GRAPHIC_AREA Area;
    GRAPHIC_GFX Gfx;
    GRAPHIC_POSITION Cursor;
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL* pBoardMemory;
    UINT32 MemoryLength;
}BOARD;

BOOLEAN BoardCreat(BOARD *pBoard,UINT32 Width,UINT32 Height);
void BoardGoto(BOARD *pBoard,GRAPHIC_POSITION *pPosition);
void BoardGotoxy(BOARD *pBoard,UINT32 X,UINT32 Y);
void BoardCharPut(BOARD *pBoard,UINT8 Data);
void BoardCharDraw(BOARD *pBoard,UINT8 *pFontBitmap);
void BoardStringPrint(BOARD *pBoard,UINT8 *pString);
void BoardCharPut(BOARD *pBoard,UINT8 Data);
void BoardEmptyCharDraw(BOARD *pBoard);	
void BoardUINT8Print(BOARD *pBoard,UINT8 Number);
void BoardUINT16Print(BOARD *pBoard,UINT16 Number);
void BoardUINT32Print(BOARD *pBoard,UINT32 Number);
void BoardMemoryReset(BOARD *pBoard);
void BoardRectangleDraw(BOARD *pBoard,GRAPHIC_AREA *pArea,UINT8 ColorValue);
void BoardCursorAdvance(BOARD *pBoard);

#endif
