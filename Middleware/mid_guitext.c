#include <includes.h>

static const unsigned char CursorOn[]={
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
static const unsigned char CursorOff[]={
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
static const unsigned char EmptyChar[]={
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

VOID GuiTextInit(VOID);
VOID GuiTextMemoryInit(VOID);
VOID GuiTextCursorAdvance(VOID);
VOID GuiTextGfxTextDraw(UINT8 *);
VOID GuiTextScroll(VOID);
VOID GuiTextCharPut(UINT8 Data);
VOID GuiTextDel(VOID);
VOID GuiTextCursorToggle(VOID);
VOID GuiTextCharDraw(UINT8 *);
VOID GuiTextCursorAdvance(VOID);
VOID GuiTextEmptyCharDraw(VOID);
VOID GuiTextStringPrint(UINT8 *pString);
VOID GuiTextCr(VOID);
VOID GuiTextCursorClear(VOID);
VOID GuiTextMemoryBackup(VOID);
VOID GuiTextMemoryRecovery(VOID);

UINT8 *pGuiTextMemory;
GUI_TEXT_CONTROL *pGuiTextCtrl;

VOID GuiTextArgumentKeyPut(UINT8 Data);

VOID GuiTextInit(VOID){
    pGuiTextCtrl=(GUI_TEXT_CONTROL *)OsMemoryAllocate(sizeof(GUI_TEXT_CONTROL));
	//pGuiTextCtrl->Area.W=GUI_TEXT_WIDTH_MAX;
	//pGuiTextCtrl->Area.H=GUI_TEXT_HEIGHT_MAX;
	pGuiTextCtrl->Area.W=pOsDriverVga->Area.W;
	pGuiTextCtrl->Area.H=pOsDriverVga->Area.H;
	pGuiTextCtrl->Cursor.X=0;
	pGuiTextCtrl->Cursor.Y=0;
	pGuiTextCtrl->Cell.Width=8;
	pGuiTextCtrl->Cell.Height=8;
	pGuiTextCtrl->Gfx.BgColor=GFX_COLOR_BLACK;
	pGuiTextCtrl->Gfx.FgColor=GFX_COLOR_BLACK;
	pGuiTextCtrl->Gfx.FontColor=GFX_COLOR_WHITE;
	pGuiTextCtrl->LineInfo.CurLineNum=0;
	pGuiTextCtrl->LineInfo.CurCharNum=0;
	pGuiTextCtrl->LineInfo.MaxCharNum=GUI_TEXT_CHAR_MAX;
	pGuiTextCtrl->LineInfo.MaxLineNum=GUI_TEXT_LINE_MAX;
	pGuiTextCtrl->LineInfo.Height=GUI_TEXT_CHAR_HEIGHT;
	pGuiTextCtrl->LineInfo.Width=GUI_TEXT_WIDTH_MAX;
	pGuiTextCtrl->CursorFlag=OFF;
	pGuiTextCtrl->Replace=FALSE;
	pGuiTextCtrl->Status=0;
	pGuiTextCtrl->Initial=FALSE;
    pGuiTextCtrl->MyTimer.Timer=0;
	OsTimeTimerPut(&pGuiTextCtrl->MyTimer);
	GuiTextMemoryInit();
}
VOID GuiTextMemoryInit(VOID){
    UINT8 BgColor;
    UINT8 *pMemory;
    U32 Length;

    BgColor=GfxPaletteClut[pGuiTextCtrl->Gfx.BgColor];
    pGuiTextMemory=pOsDriverVga->pVideoMemory;
    pMemory=pGuiTextMemory;
    for(Length=0;Length<64000;Length++){
        *pMemory++=BgColor;
    }
}
VOID GuiTextScroll(VOID){
	U32 Length;
	UINT8 *pSource,*pDestination;
	UINT8 i;
	
	Length=320*192;
	pSource=(UINT8 *)((U32)pGuiTextMemory+320*8);
	pDestination=pGuiTextMemory;
	while(Length!=0){
		*pDestination=*pSource;
		pSource++;
		pDestination++;
		Length--;
	}
	Length=320*8;
	pSource=(UINT8 *)((U32)pGuiTextMemory+320*192);
	i=GfxPaletteClut[pGuiTextCtrl->Gfx.BgColor];
	while(Length!=0){
		*pSource=i;
		pSource++;
		Length--;
	}
}
VOID GuiTextCursorAdvance(VOID){
	if(pGuiTextCtrl->LineInfo.CurCharNum>=(GUI_TEXT_CHAR_MAX-1)){
		pGuiTextCtrl->LineInfo.CurCharNum=0;
		if(pGuiTextCtrl->LineInfo.CurLineNum<(GUI_TEXT_LINE_MAX-1)){
			pGuiTextCtrl->LineInfo.CurLineNum++;
		}
		else GuiTextScroll();
	}
	else{
		pGuiTextCtrl->LineInfo.CurCharNum++;
	}
	pGuiTextCtrl->Cursor.X=pGuiTextCtrl->LineInfo.CurCharNum*GUI_TEXT_CHAR_WIDTH;
	pGuiTextCtrl->Cursor.Y=pGuiTextCtrl->LineInfo.CurLineNum*GUI_TEXT_CHAR_HEIGHT;
}
VOID GuiTextStringPrint(UINT8 *pString){
	while(*pString!=0){
		if((*pString>=0x20)&&(*pString<0x7d)) GuiTextCharPut(*pString);
		else if(*pString==0x0a) GuiTextCr(); 
		pString++;
	}
}
VOID GuiTextCr(VOID){ // carriage return...enter key
	if(pGuiTextCtrl->LineInfo.CurLineNum<(GUI_TEXT_LINE_MAX-1)){
		pGuiTextCtrl->LineInfo.CurLineNum++;
	}
	else GuiTextScroll();
	pGuiTextCtrl->LineInfo.CurCharNum=0;
	pGuiTextCtrl->Cursor.X=pGuiTextCtrl->LineInfo.CurCharNum*GUI_TEXT_CHAR_WIDTH;
	pGuiTextCtrl->Cursor.Y=pGuiTextCtrl->LineInfo.CurLineNum*GUI_TEXT_CHAR_HEIGHT;
}
VOID GuiTextDel(VOID){
	if(pGuiTextCtrl->LineInfo.CurCharNum>0){
		pGuiTextCtrl->LineInfo.CurCharNum--;
	}
    pGuiTextCtrl->Cursor.X=pGuiTextCtrl->LineInfo.CurCharNum*GUI_TEXT_CHAR_WIDTH;
    pGuiTextCtrl->Cursor.Y=pGuiTextCtrl->LineInfo.CurLineNum*GUI_TEXT_CHAR_HEIGHT;
    GuiTextEmptyCharDraw();
}
VOID GuiTextCharPut(UINT8 Data){
	UINT8 *pFontBitmap;

	pFontBitmap=FontBitmapGet(GUI_TEXT_FONT_STYLE,Data);
	GuiTextCharDraw(pFontBitmap);
	GuiTextCursorAdvance();
}
VOID GuiTextCursorToggle(VOID){
	if(pGuiTextCtrl->CursorFlag==ON){
		GuiTextCharDraw((UINT8 *)CursorOff);
		pGuiTextCtrl->CursorFlag=OFF;
		pGuiTextCtrl->MyTimer.Timer=1000; 
	}
	else{
		GuiTextCharDraw((UINT8 *)CursorOn);
		pGuiTextCtrl->CursorFlag=ON;
		pGuiTextCtrl->MyTimer.Timer=1000;
	}
}
VOID GuiTextCursorClear(VOID){
	GuiTextCharDraw((UINT8 *)CursorOff);
	pGuiTextCtrl->CursorFlag=OFF;
	pGuiTextCtrl->MyTimer.Timer=1000;
}
VOID GuiTextEmptyCharDraw(VOID){
    UINT8  i,j,k;
    UINT8 *pMemory,*pBitmapStart,*pColMemory;
    UINT8 Width;
    UINT8 Height;
    UINT8 BitValue;
    UINT8 FontFormat;
    UINT8 *pFontBitmap;
    
    
    pFontBitmap=(UINT8 *)EmptyChar;
    pBitmapStart=(UINT8 *)((U32)pGuiTextMemory+(U32)(GUI_TEXT_WIDTH_MAX*pGuiTextCtrl->Cursor.Y)+(U32)(pGuiTextCtrl->Cursor.X));
    pMemory=pBitmapStart;
    Width=*pFontBitmap;
    pFontBitmap++;
    Height=*pFontBitmap;
    pFontBitmap++;
    if(Width&0x80) FontFormat=1; // vertical
    else FontFormat=0;
    Width&=0x7f;
    Height&=0x7f;
    pGuiTextCtrl->TextInfo.Width=Width;
    pGuiTextCtrl->TextInfo.Height=Height;
    if(FontFormat==1){
        for(j=0;j<Width;j++){
            pColMemory=pBitmapStart+j;
            k=0;
            for(i=0;i<Height;i++){
                pMemory=pColMemory+GUI_TEXT_WIDTH_MAX*i;
                BitValue=((*pFontBitmap)<<k)&0x80;
	            *pMemory=GfxPaletteClut[pGuiTextCtrl->Gfx.BgColor];
                k++;
	            if(k==8){
	                pFontBitmap++;
	                k=0;
	            }
            }
            if(k!=0) pFontBitmap++;
        }
    }
    else{
	    for(i=0;i<Height;i++){
	        pMemory=pBitmapStart+GUI_TEXT_WIDTH_MAX*i;
	        k=0;
	        for(j=0;j<Width;j++){
	            BitValue=((*pFontBitmap)<<k)&0x80;
	            *pMemory=GfxPaletteClut[pGuiTextCtrl->Gfx.BgColor];
	            k++;
	            if(k==8){
	                pFontBitmap++;
	                k=0;
	            }
	            pMemory++;
	        }
	        if(k!=0) pFontBitmap++;
	    }
    }
}

VOID GuiTextCharDraw(UINT8 *pFontBitmap){
    UINT8  i,j,k;
    UINT8 *pMemory,*pBitmapStart,*pColMemory;
    UINT8 Width;
    UINT8 Height;
    UINT8 BitValue;
    UINT8 FontFormat;

    pBitmapStart=(UINT8 *)((U32)pGuiTextMemory+(U32)(GUI_TEXT_WIDTH_MAX*pGuiTextCtrl->Cursor.Y)+(U32)(pGuiTextCtrl->Cursor.X));
    pMemory=pBitmapStart;
    Width=*pFontBitmap;
    pFontBitmap++;
    Height=*pFontBitmap;
    pFontBitmap++;
    if(Width&0x80) FontFormat=1;
    else FontFormat=0;
    Width&=0x7f;
    Height&=0x7f;
    pGuiTextCtrl->TextInfo.Width=Width;
    pGuiTextCtrl->TextInfo.Height=Height;
    if(FontFormat==1){
        for(j=0;j<Width;j++){
            pColMemory=pBitmapStart+j;
            k=0;
            for(i=0;i<Height;i++){
                pMemory=pColMemory+GUI_TEXT_WIDTH_MAX*i; 
                BitValue=((*pFontBitmap)<<k)&0x80;
                if(BitValue!=0) *pMemory=GfxPaletteClut[pGuiTextCtrl->Gfx.FontColor];
	            else *pMemory=GfxPaletteClut[pGuiTextCtrl->Gfx.FgColor];
                k++;
	            if(k==8){
	                pFontBitmap++;
	                k=0;
	            }
            }
            if(k!=0) pFontBitmap++;
        }
    }
    else{
	    for(i=0;i<Height;i++){
	        pMemory=pBitmapStart+GUI_TEXT_WIDTH_MAX*i;
	        k=0;
	        for(j=0;j<Width;j++){
	            BitValue=((*pFontBitmap)<<k)&0x80;
	            if(BitValue!=0) *pMemory=GfxPaletteClut[pGuiTextCtrl->Gfx.FontColor];
	            else *pMemory=GfxPaletteClut[pGuiTextCtrl->Gfx.FgColor];
	            k++;
	            if(k==8){
	                pFontBitmap++;
	                k=0;
	            }
	            pMemory++;
	        }
	        if(k!=0) pFontBitmap++;
	    }
    }
}


VOID GuiTextMemoryBackup(VOID){
    SystemlibMemoryCopy(pOsDriverVga->pVideoMemory,(UINT8 *)0x00090000,64000);
}

VOID GuiTextMemoryRecovery(VOID){
    SystemlibMemoryCopy((UINT8 *)0x00090000,pOsDriverVga->pVideoMemory,64000);
}
