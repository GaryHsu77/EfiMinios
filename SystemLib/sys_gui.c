#include <includes.h>

VOID SystemGuiInit(VOID);
VOID SystemGuiMemoryInit(VOID);
VOID SystemGuiCharPut(UINT16 Data);
VOID SystemGuiDel(VOID);
VOID SystemGuiCursorToggle(VOID);
VOID SystemGuiCharDraw(UINT16 *);
VOID SystemGuiCursorAdvance(VOID);
VOID SystemGuiEmptyCharDraw(VOID);
VOID SystemGuiStringPrint(UINT16 *pString);
VOID SystemGuiCr(VOID);
VOID SystemGuiCursorClear(VOID);

UINT16 *pSystemGuiMemory;
SYSTEMGUI_CONTROL SystemGuiCtrl;

VOID SystemGuiArgumentKeyPut(UINT16 Data);

VOID SystemGuiInit(VOID)
{
	
}

VOID SystemGuiMemoryInit(VOID)
{
}


VOID SystemGuiCursorAdvance(VOID)
{

}

VOID SystemGuiStringPrint(UINT16 *pString)
{
	Print(L"%s", pString);
}

VOID SystemGuiCr(VOID)
{
	
}

VOID SystemGuiDel(VOID)
{

}

VOID SystemGuiCharPut(UINT16 Data)
{
}

VOID SystemGuiCursorToggle(VOID)
{
}

VOID SystemGuiCursorClear(VOID)
{
	gST->ConOut->EnableCursor(gST->ConOut,FALSE);
}

VOID SystemGuiEmptyCharDraw(VOID)
{
}

VOID SystemGuiCharDraw(UINT16 *pFontBitmap)
{
}

VOID SystemDrawPoint(UINT32 x,UINT32 y,EFI_GRAPHICS_OUTPUT_BLT_PIXEL Color)
{
	MY_MUTEX mutex = OsEnterCritical();
	if(GOP) GOP->Blt(GOP,&Color,EfiBltVideoFill,0,0,x,y,1,1,0);
	OsExitCritical(mutex);
}

VOID SystemDrawStr(UINTN col,UINTN row,UINT8 *Str)
{
	//UINT8 i,j;
	MY_MUTEX mutex = OsEnterCritical();
	//gST->ConOut->SetCursorPosition(gST->ConOut,col,row);
	/*
	while(*Str!=0){
		UINT16* tmp;
		*tmp = *Str;
		//gST->ConOut->OutputString(gST->ConOut,tmp);
		GDP(L"%c", tmp);
		Str++;
		GDP(L"3\n");
	}
	GDP(L"4\n");
	*/
	/*
	GDP(L"\n");
	for(i=0;i<10;i++){
		GDP(L"%x ", Str[i]);
	}
	GDP(L"\n");
	for(i=0;i<10;i++){
		UINT16* tmp;
		*tmp = *Str;
		GDP(L"%x ", tmp[0]);
	}
	*/
	OsExitCritical(mutex);
}