#ifndef CAPTION_H
#define CAPTION_H

#define CAPTION_STATUS_FAIL 0
#define CAPTION_STATUS_OK   1

typedef struct{
    UINT8 Status;
    UINT8 Dirty;
    UINT8 CursorFlag;
    UINT8 MaxChar;
    UINT8 MaxLine;
    UINT8 CurCharNum;
    UINT8 CurLineNum;
    GRAPHIC_AREA Area;
    GRAPHIC_GFX Gfx;
    GRAPHIC_POSITION Cursor;
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL* pCaptionMemory;
    UINT32 MemoryLength;
    OS_TIMER MyTimer;
}CAPTION;

BOOLEAN CaptionCreat(CAPTION *pCaption,UINT8 CharNumber,UINT8 LineNumber);
VOID CaptionCharPut(CAPTION *pCaption,UINT8 Data);
VOID CaptionEmptyCharDraw(CAPTION *pCaption);
VOID CaptionCharDraw(CAPTION *pCaption,UINT8 *pFontBitmap);
VOID CaptionScroll(CAPTION *pCaption);
VOID CaptionStringPrint(CAPTION *pCaption,UINT8 *pString);
VOID CaptionCr(CAPTION *pCaption);	
VOID CaptionDel(CAPTION *pCaption);	
VOID CaptionCursorAdvance(CAPTION *pCaption);
VOID CaptionCursorToggle(CAPTION *pCaption);	
VOID CaptionCursorClear(CAPTION *pCaption);
VOID CaptionEmptyCharDraw(CAPTION *pCaption);	
VOID CaptionCharDraw(CAPTION *pCaption,UINT8 *pFontBitmap);
VOID CaptionUINT8Print(CAPTION *pCaption,UINT8 Number);
VOID CaptionUINT16Print(CAPTION *pCaption,UINT16 Number);
VOID CaptionUINT32Print(CAPTION *pCaption,UINT32 Number);
#endif
