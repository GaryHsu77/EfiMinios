#include <includes.h>

static const unsigned char CaptionCursorOn[]={
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
static const unsigned char CaptionCursorOff[]={
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
static const unsigned char CaptionEmptyChar[]={
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
const UINT8 LINE_BLANK = 0;
BOOLEAN CaptionCreat(CAPTION *pCaption,UINT8 CharNumber,UINT8 LineNumber){
	UINT32 MaxCharValue;
	UINT32 MaxLineValue;
	EFI_STATUS Status;
	
	MaxCharValue=DeskWorkCtrl.WorkArea.W-WINDOW_EDGE_THINK*2;
	MaxCharValue=(MaxCharValue/STRING_SIZE);
	MaxLineValue=DeskWorkCtrl.WorkArea.H-WINDOW_HEADER_HEIGHT-WINDOW_EDGE_THINK*2;
	MaxLineValue=(MaxLineValue/(STRING_SIZE+LINE_BLANK));
    if(CharNumber>(UINT8)MaxCharValue) pCaption->MaxChar=(UINT8)MaxCharValue;
    else pCaption->MaxChar=CharNumber;
    if(LineNumber>(UINT8)MaxLineValue) pCaption->MaxLine=(UINT8)MaxLineValue;
    else pCaption->MaxLine=LineNumber;
    pCaption->MemoryLength=(UINT32)pCaption->MaxChar*pCaption->MaxLine*STRING_SIZE*(STRING_SIZE+LINE_BLANK);
	Status = gBS->AllocatePool(EfiBootServicesData,pCaption->MemoryLength*sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL),&pCaption->pCaptionMemory);
	if(Status != EFI_SUCCESS){
		pCaption->Status=CAPTION_STATUS_FAIL;
		return FALSE;
	}
    pCaption->Status=CAPTION_STATUS_OK;
    pCaption->CurCharNum=0;
    pCaption->CurLineNum=0;
	pCaption->Cursor.X=0;
	pCaption->Cursor.Y=0;
    pCaption->Area.X=0;
    pCaption->Area.Y=0;
    pCaption->Area.W=((UINT32)pCaption->MaxChar)*STRING_SIZE;
    pCaption->Area.H=((UINT32)pCaption->MaxLine)*(STRING_SIZE+LINE_BLANK);
    pCaption->Gfx.FgColor=GFX_COLOR_BLACK;
    pCaption->Gfx.BgColor=GFX_COLOR_BLACK;
    pCaption->Gfx.FontColor=GFX_COLOR_WHITE;
    pCaption->MyTimer.Timer=0;
	OsTimeTimerPut(&pCaption->MyTimer);
    PixelArray256Set(pCaption->pCaptionMemory, GfxPaletteClut[pCaption->Gfx.BgColor],pCaption->MemoryLength);
	CaptionStringPrint(pCaption,"$");
    return TRUE;
}

VOID CaptionScroll(CAPTION *pCaption){
	UINT32 Length;
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pSource,*pDestination;
	UINT8 i;
	
	if(pCaption==(CAPTION *)NULL) return;
	Length=pCaption->Area.W*(pCaption->Area.H-(STRING_SIZE+LINE_BLANK));
	pSource=(EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)(pCaption->pCaptionMemory+pCaption->Area.W*STRING_SIZE);
	pDestination=pCaption->pCaptionMemory;
	PixelArrayCopy(pSource,pDestination,Length);
	Length=pCaption->Area.W*STRING_SIZE;
	pSource=(EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)(pCaption->pCaptionMemory+pCaption->Area.W*(pCaption->Area.H-STRING_SIZE));
	i=GfxPaletteClut[pCaption->Gfx.BgColor];
	PixelArray256Set(pSource, GfxPaletteClut[pCaption->Gfx.BgColor],Length);
    pCaption->Dirty=TRUE;
}

VOID CaptionStringPrint(CAPTION *pCaption,UINT8 *pString){
	MY_MUTEX mutex;
    
	if(pCaption==(CAPTION *)NULL) return;
    mutex = OsEnterCritical();
	while(*pString!=0){
		if((*pString>=0x20)&&(*pString<0x7d)) CaptionCharPut(pCaption,*pString);
		else if(*pString==0x0a) CaptionCr(pCaption); 
		pString++;
	}
    pCaption->Dirty=TRUE;
    OsExitCritical(mutex);
}

VOID CaptionCr(CAPTION *pCaption){
	if(pCaption==(CAPTION *)NULL) return;
	if(pCaption->CurLineNum<(pCaption->MaxLine-1)){
		pCaption->CurLineNum++;
	}
	else CaptionScroll(pCaption);
	pCaption->CurCharNum=0;
	pCaption->Cursor.X=pCaption->CurCharNum*STRING_SIZE;
	pCaption->Cursor.Y=pCaption->CurLineNum*(STRING_SIZE+LINE_BLANK);
    pCaption->Dirty=TRUE;
}

VOID CaptionDel(CAPTION *pCaption){
	if(pCaption==(CAPTION *)NULL) return;
	if(pCaption->CurCharNum>0) pCaption->CurCharNum--;
    pCaption->Cursor.X=pCaption->CurCharNum*STRING_SIZE;
    pCaption->Cursor.Y=pCaption->CurLineNum*(STRING_SIZE+LINE_BLANK);
    CaptionEmptyCharDraw(pCaption);
    pCaption->Dirty=TRUE;
}

VOID CaptionCursorAdvance(CAPTION *pCaption){
	if(pCaption==(CAPTION *)NULL) return;
	if(pCaption->CurCharNum>=(pCaption->MaxChar-1)){
		pCaption->CurCharNum=0;
		if(pCaption->CurLineNum<(pCaption->MaxLine-1)){
			pCaption->CurLineNum++;
		}
		else CaptionScroll(pCaption);
	}
	else pCaption->CurCharNum++;
	pCaption->Cursor.X=(UINT32)pCaption->CurCharNum*STRING_SIZE;
	pCaption->Cursor.Y=(UINT32)pCaption->CurLineNum*(STRING_SIZE+LINE_BLANK);
    pCaption->Dirty=TRUE;
}

VOID CaptionCursorToggle(CAPTION *pCaption){
	if(pCaption==(CAPTION *)NULL) return;
	if(pCaption->CursorFlag==ON){
		CaptionCharDraw(pCaption,(UINT8 *)CaptionCursorOff);
		pCaption->CursorFlag=OFF;
		pCaption->MyTimer.Timer=1000; 
	}
	else{
		CaptionCharDraw(pCaption,(UINT8 *)CaptionCursorOn);
		pCaption->CursorFlag=ON;
		pCaption->MyTimer.Timer=1000;
	}
    pCaption->Dirty=TRUE;
}

VOID CaptionCursorClear(CAPTION *pCaption){
	if(pCaption==(CAPTION *)NULL) return;
	CaptionCharDraw(pCaption,(UINT8 *)CaptionCursorOff);
	pCaption->CursorFlag=OFF;
	pCaption->MyTimer.Timer=1000;
    pCaption->Dirty=TRUE;
}

VOID CaptionCharPut(CAPTION *pCaption,UINT8 Data){
	UINT8 *pFontBitmap;

	if(pCaption==(CAPTION *)NULL) return;
    if((Data<0x20)||(Data>0x7e)) return;
	pFontBitmap=FontBitmapGet(FONT8X8,Data);
	CaptionCharDraw(pCaption,pFontBitmap);
	CaptionCursorAdvance(pCaption);
    pCaption->Dirty=TRUE;
}

VOID CaptionUINT8Print(CAPTION *pCaption,UINT8 Number){
    UINT8 i;
    
	if(pCaption==(CAPTION *)NULL) return;
    i=(Number&0xf0)>>4;    
    if(i<10) i=i+0x30;
    else i=i+0x41-10;
    CaptionCharPut(pCaption,i);
    i=Number&0x0f;
    if(i<10) i=i+0x30;
    else i=i+0x41-10;
    CaptionCharPut(pCaption,i);
}

VOID CaptionUINT16Print(CAPTION *pCaption,UINT16 Number){
    UINT16 i;

	if(pCaption==(CAPTION *)NULL) return;
    i=(Number&0xf000)>>12;    
    if(i<10) i=i+0x30;
    else i=i+0x41-10;
    CaptionCharPut(pCaption,(UINT8)i);
    i=(Number&0x0f00)>>8;    
    if(i<10) i=i+0x30;
    else i=i+0x41-10;
    CaptionCharPut(pCaption,(UINT8)i);
    i=(Number&0x00f0)>>4;    
    if(i<10) i=i+0x30;
    else i=i+0x41-10;
    CaptionCharPut(pCaption,(UINT8)i);
    i=Number&0x000f;
    if(i<10) i=i+0x30;
    else i=i+0x41-10;
    CaptionCharPut(pCaption,(UINT8)i);
}

VOID CaptionUINT32Print(CAPTION *pCaption,UINT32 Number){
    UINT32 i;
    
	if(pCaption==(CAPTION *)NULL) return;
    i=(Number&0xf0000000)>>28;    
    if(i<10) i=i+0x30;
    else i=i+0x41-10;
    CaptionCharPut(pCaption,(UINT8)i);
    i=(Number&0x0f000000)>>24;    
    if(i<10) i=i+0x30;
    else i=i+0x41-10;
    CaptionCharPut(pCaption,(UINT8)i);
    i=(Number&0x00f00000)>>20;    
    if(i<10) i=i+0x30;
    else i=i+0x41-10;
    CaptionCharPut(pCaption,(UINT8)i);
    i=(Number&0x000f0000)>>16;    
    if(i<10) i=i+0x30;
    else i=i+0x41-10;
    CaptionCharPut(pCaption,(UINT8)i);
    i=(Number&0x0000f000)>>12;    
    if(i<10) i=i+0x30;
    else i=i+0x41-10;
    CaptionCharPut(pCaption,(UINT8)i);
    i=(Number&0x00000f00)>>8;    
    if(i<10) i=i+0x30;
    else i=i+0x41-10;
    CaptionCharPut(pCaption,(UINT8)i);
    i=(Number&0x000000f0)>>4;    
    if(i<10) i=i+0x30;
    else i=i+0x41-10;
    CaptionCharPut(pCaption,(UINT8)i);
    i=Number&0x0000000f;
    if(i<10) i=i+0x30;
    else i=i+0x41-10;
    CaptionCharPut(pCaption,(UINT8)i);
}

VOID CaptionEmptyCharDraw(CAPTION *pCaption)
{
    // UINT8  i,j,k;
    // UINT8 *pMemory,*pBitmapStart,*pColMemory;
    // UINT8 Width;
    // UINT8 Height;
    // UINT8 BitValue;
    // UINT8 FontFormat;
    // UINT8 *pFontBitmap;
	UINT8  i,j,tmp;
    UINT32 height = STRING_SIZE;
	UINT32 width  = STRING_SIZE;
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pBitmapStart;
    
	if(pCaption==(CAPTION *)NULL) return;

	pBitmapStart=(EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)(pCaption->pCaptionMemory
                       +pCaption->CurLineNum*pCaption->MaxChar*STRING_SIZE*(STRING_SIZE+LINE_BLANK)
                       +(pCaption->CurCharNum*STRING_SIZE));
	tmp = height - 1;
	for(i=0;i<height;i++){
		for(j=0;j<width;j++) PixelArray256Set(pBitmapStart+j,0,1);
		pBitmapStart=pBitmapStart+pCaption->Area.W;
		tmp--;
	}
}

VOID CaptionCharDraw(CAPTION *pCaption,UINT8 *pFontBitmap)
{
	UINT8  i,j,tmp;
    UINT32 height = *(UINT32*)&pFontBitmap[Height_OFFSET];
	UINT32 width  = *(UINT32*)&pFontBitmap[Width_OFFSET];
	UINT32 size  = *(UINT32*)&pFontBitmap[Size_OFFSET];
	UINT8* bmp = &pFontBitmap[PIX_OFFSET];
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pBitmapStart;

	if(pCaption==(CAPTION *)NULL) return;
    pBitmapStart=(EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)(pCaption->pCaptionMemory+pCaption->Area.W*pCaption->Cursor.Y+pCaption->Cursor.X);
	
	tmp = height - 1;
	for(i=0;i<height;i++){
		for(j=0;j<width;j++) PixelArray256Set(pBitmapStart+j,bmp[j+tmp*width],1);
		pBitmapStart=pBitmapStart+pCaption->Area.W;
		tmp--;
	}
}
