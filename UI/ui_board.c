#include <includes.h>

static const unsigned char BoardCursorOn[]={
0x88, 0x08,
0x03, 
0x03,
0x03,
0x03,
0x03,
0x03,
0x03,
0x03,
};

static const unsigned char BoardCursorOff[]={
0x88, 0x08,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
};

static const unsigned char BoardEmptyChar[]={
0x88, 0x08,
0x00,
0x00,
0x00,
0x00, 
0x00, 
0x00,
0x00, 
0x00, 
};

BOOLEAN BoardCreat(BOARD *pBoard,UINT32 Width,UINT32 Height){
	UINT32 MaxBoardWidth;
	UINT32 MaxBoardHeight;
	EFI_STATUS Status;
	
	MaxBoardWidth=DeskWorkCtrl.WorkArea.W-WINDOW_EDGE_THINK*2;
	MaxBoardHeight=DeskWorkCtrl.WorkArea.H-WINDOW_HEADER_HEIGHT-WINDOW_EDGE_THINK*2;
    if(Width>MaxBoardWidth) Width=MaxBoardWidth;
    if(Height>MaxBoardHeight) Height=MaxBoardHeight;
    pBoard->MemoryLength=Width*Height;
	Status = gBS->AllocatePool(EfiBootServicesData,sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL)*pBoard->MemoryLength,&pBoard->pBoardMemory);
	if(Status != EFI_SUCCESS){
		pBoard->Status=BOARD_STATUS_FAIL;
		return FALSE;
	}
    pBoard->Status=BOARD_STATUS_OK;
	pBoard->Cursor.X=0;
	pBoard->Cursor.Y=0;
    pBoard->Area.X=0;
    pBoard->Area.Y=0;
    pBoard->Area.W=Width;
    pBoard->Area.H=Height;
    pBoard->Gfx.FgColor=GFX_COLOR_BLUE1;
    pBoard->Gfx.BgColor=GFX_COLOR_BLUE1;
    pBoard->Gfx.FontColor=GFX_COLOR_BLACK;
    PixelArray256Set(pBoard->pBoardMemory,GfxPaletteClut[pBoard->Gfx.BgColor],pBoard->MemoryLength);
    pBoard->Dirty=TRUE;
    return TRUE;
}

VOID BoardStringPrint(BOARD *pBoard,UINT8 *pString){
	if(pBoard==(BOARD *)NULL) return;
	if(pBoard->Status!=BOARD_STATUS_OK) return;
	while(*pString!=0){
		if((*pString>=0x20)&&(*pString<0x7d)) BoardCharPut(pBoard,*pString);
		pString++;
	}
    pBoard->Dirty=TRUE;
}

VOID BoardCharPut(BOARD *pBoard,UINT8 Data){
	UINT8 *pFontBitmap;

	if(pBoard==(BOARD *)NULL) return;
	if(pBoard->Status!=BOARD_STATUS_OK) return;
    if((Data<0x20)||(Data>0x7e)) return;
    if((pBoard->Area.W-pBoard->Cursor.X)<FONT_FONT8X8_CHARWIDTH) return;  //no space
    if((pBoard->Area.H-pBoard->Cursor.Y)<FONT_FONT8X8_CHARHEIGHT) return; //no space
	pFontBitmap=FontBitmapGet(FONT8X8,Data);
	BoardCharDraw(pBoard,pFontBitmap);
	BoardCursorAdvance(pBoard);
    pBoard->Dirty=TRUE;
}

VOID BoardMemoryReset(BOARD *pBoard){
	if(pBoard==(BOARD *)NULL) return;
	if(pBoard->Status!=BOARD_STATUS_OK) return;
    PixelArray256Set(pBoard->pBoardMemory,GfxPaletteClut[pBoard->Gfx.BgColor],pBoard->MemoryLength);
}
	
VOID BoardGoto(BOARD *pBoard,GRAPHIC_POSITION *pPosition){
	if(pBoard==(BOARD *)NULL) return;
	if(pBoard->Area.W<=pPosition->X) pBoard->Cursor.X=0;
	else pBoard->Cursor.X=pPosition->X;
	if(pBoard->Area.H<=pPosition->Y) pBoard->Cursor.Y=0;
	else pBoard->Cursor.Y=pPosition->Y;
}

VOID BoardGotoxy(BOARD *pBoard,UINT32 X,UINT32 Y){
	if(pBoard==(BOARD *)NULL) return;
	if(pBoard->Area.W<=X) pBoard->Cursor.X=0;
	else pBoard->Cursor.X=X;
	if(pBoard->Area.H<=Y) pBoard->Cursor.Y=0;
	else pBoard->Cursor.Y=Y;
}

VOID BoardCursorAdvance(BOARD *pBoard){
	if(pBoard==(BOARD *)NULL) return;
	pBoard->Cursor.X=pBoard->Cursor.X+FONT_FONT8X8_CHARWIDTH;
}

VOID BoardUINT8Print(BOARD *pBoard,UINT8 Number){
    UINT8 i;
    
    
	if(pBoard==(BOARD *)NULL) return;
	if(pBoard->Status!=BOARD_STATUS_OK) return;
    i=(Number&0xf0)>>4;    
    if(i<10) i=i+0x30;
    else i=i+0x41-10;
    BoardCharPut(pBoard,i);
    i=Number&0x0f;
    if(i<10) i=i+0x30;
    else i=i+0x41-10;
    BoardCharPut(pBoard,i);
}

VOID BoardUINT16Print(BOARD *pBoard,UINT16 Number){
    UINT16 i;
    

	if(pBoard==(BOARD *)NULL) return;
	if(pBoard->Status!=BOARD_STATUS_OK) return;
    i=(Number&0xf000)>>12;    
    if(i<10) i=i+0x30;
    else i=i+0x41-10;
    BoardCharPut(pBoard,(UINT8)i);
    i=(Number&0x0f00)>>8;    
    if(i<10) i=i+0x30;
    else i=i+0x41-10;
    BoardCharPut(pBoard,(UINT8)i);
    i=(Number&0x00f0)>>4;    
    if(i<10) i=i+0x30;
    else i=i+0x41-10;
    BoardCharPut(pBoard,(UINT8)i);
    i=Number&0x000f;
    if(i<10) i=i+0x30;
    else i=i+0x41-10;
    BoardCharPut(pBoard,(UINT8)i);
}

VOID BoardUINT32Print(BOARD *pBoard,UINT32 Number){
    UINT32 i;
    
    
	if(pBoard==(BOARD *)NULL) return;
	if(pBoard->Status!=BOARD_STATUS_OK) return;
    i=(Number&0xf0000000)>>28;    
    if(i<10) i=i+0x30;
    else i=i+0x41-10;
    BoardCharPut(pBoard,(UINT8)i);
    i=(Number&0x0f000000)>>24;    
    if(i<10) i=i+0x30;
    else i=i+0x41-10;
    BoardCharPut(pBoard,(UINT8)i);
    i=(Number&0x00f00000)>>20;    
    if(i<10) i=i+0x30;
    else i=i+0x41-10;
    BoardCharPut(pBoard,(UINT8)i);
    i=(Number&0x000f0000)>>16;    
    if(i<10) i=i+0x30;
    else i=i+0x41-10;
    BoardCharPut(pBoard,(UINT8)i);
    i=(Number&0x0000f000)>>12;    
    if(i<10) i=i+0x30;
    else i=i+0x41-10;
    BoardCharPut(pBoard,(UINT8)i);
    i=(Number&0x00000f00)>>8;    
    if(i<10) i=i+0x30;
    else i=i+0x41-10;
    BoardCharPut(pBoard,(UINT8)i);
    i=(Number&0x000000f0)>>4;    
    if(i<10) i=i+0x30;
    else i=i+0x41-10;
    BoardCharPut(pBoard,(UINT8)i);
    i=Number&0x0000000f;
    if(i<10) i=i+0x30;
    else i=i+0x41-10;
    BoardCharPut(pBoard,(UINT8)i);
}

VOID BoardEmptyCharDraw(BOARD *pBoard){
    UINT8  i,j,k;
    UINT8 *pMemory,*pBitmapStart,*pColMemory;
    UINT8 Width;
    UINT8 Height;
    UINT8 BitValue;
    UINT8 FontFormat;
    UINT8 *pFontBitmap;
    
    
	if(pBoard==(BOARD *)NULL) return;
    pFontBitmap=(UINT8 *)BoardEmptyChar;
    pBitmapStart=(UINT8 *)((UINT32)pBoard->pBoardMemory+(UINT32)(pBoard->Area.W*pBoard->Cursor.Y)+(UINT32)(pBoard->Cursor.X));
    pMemory=pBitmapStart;
    Width=*pFontBitmap;
    pFontBitmap++;
    Height=*pFontBitmap;
    pFontBitmap++;
    if(Width&0x80) FontFormat=1; // vertical
    else FontFormat=0;
    Width&=0x7f;
    Height&=0x7f;
    if(FontFormat==1){
        for(j=0;j<Width;j++){
            pColMemory=pBitmapStart+j;
            k=0;
            for(i=0;i<Height;i++){
                pMemory=pColMemory+pBoard->Area.W*i;
                BitValue=((*pFontBitmap)<<k)&0x80;
	            *pMemory=GfxPaletteClut[pBoard->Gfx.BgColor];
                k++;
	            if(k==8){
	                pFontBitmap++;
	                k=0;
	            }
            }
            if(k!=0) pFontBitmap++;
        }
    }
}

VOID BoardCharDraw(BOARD *pBoard,UINT8 *pFontBitmap){
    UINT8  i,j,k;
    UINT8 *pMemory,*pBitmapStart,*pColMemory;
    UINT8 Width;
    UINT8 Height;
    UINT8 BitValue;
    UINT8 FontFormat;

	if(pBoard==(BOARD *)NULL) return;
    pBitmapStart=(UINT8 *)((UINT32)pBoard->pBoardMemory+(UINT32)(pBoard->Area.W*pBoard->Cursor.Y)+(UINT32)(pBoard->Cursor.X));
    pMemory=pBitmapStart;
    Width=*pFontBitmap;
    pFontBitmap++;
    Height=*pFontBitmap;
    pFontBitmap++;
    if(Width&0x80) FontFormat=1;
    else FontFormat=0;
    Width&=0x7f;
    Height&=0x7f;
    if(FontFormat==1){
    	for(i=0;i<FONT_FONT8X8_CHARHEIGHT;i++){
    		pColMemory=pBitmapStart+pBoard->Area.W*i;
    		SystemlibMemorySet(pColMemory,GfxPaletteClut[pBoard->Gfx.FgColor],FONT_FONT8X8_CHARWIDTH);
    	}
        for(j=0;j<Width;j++){
            pColMemory=pBitmapStart+j;
            k=0;
            for(i=0;i<Height;i++){
                pMemory=pColMemory+pBoard->Area.W*i; 
                BitValue=((*pFontBitmap)<<k)&0x80;
                if(BitValue!=0) *pMemory=GfxPaletteClut[pBoard->Gfx.FontColor];
	            else *pMemory=GfxPaletteClut[pBoard->Gfx.FgColor];
                k++;
	            if(k==8){
	                pFontBitmap++;
	                k=0;
	            }
            }
            if(k!=0) pFontBitmap++;
        }
    }
}

VOID BoardRectangleDraw(BOARD *pBoard,GRAPHIC_AREA *pArea,UINT8 ColorValue){
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pMemory;
	UINT32 Height;
    

	if(pBoard==(BOARD *)NULL) return;
	if(pBoard->Status!=BOARD_STATUS_OK) return;
	pMemory=pBoard->pBoardMemory+pBoard->Area.W*pArea->Y+pArea->X;
	Height=pArea->H;
	while(Height!=0){
		PixelArray256Set(pMemory,ColorValue,pArea->W);
		pMemory=pMemory+pBoard->Area.W;
		Height--;
	}
    pBoard->Dirty=TRUE;
}
