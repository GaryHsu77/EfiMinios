#include <includes.h>

DESK_INACTIVEWINDOW_CONTROL DeskInactiveWindowCtrl;

VOID DeskInactiveWindowInit(VOID)
{
	EFI_STATUS Status;
    DeskInactiveWindowCtrl.pInactiveWindowMemory=(EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)NULL;
	Status = gBS->AllocatePool(EfiBootServicesData,DeskWorkCtrl.WorkMemoryLength*sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL),&DeskInactiveWindowCtrl.pInactiveWindowMemory);
	if(Status != EFI_SUCCESS) return;
}

VOID DeskInactiveWindowMemory2WorkWindowUpdate(WINDOW *pWindow)
{
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pSource,*pDestination;
    UINT32 Height,Width;

	if(pWindow==(WINDOW *)NULL) return;
	if((pWindow->DisplayArea.X+pWindow->DisplayArea.W)>DeskWorkCtrl.WorkArea.W) Width=DeskWorkCtrl.WorkArea.W-pWindow->DisplayArea.X;
	else Width=pWindow->DisplayArea.W;
	if((pWindow->DisplayArea.Y+pWindow->DisplayArea.H)>DeskWorkCtrl.WorkArea.H) Height=DeskWorkCtrl.WorkArea.H-pWindow->DisplayArea.Y;
	else Height=pWindow->DisplayArea.H;
	pSource=DeskInactiveWindowCtrl.pInactiveWindowMemory;
	pDestination=DeskWorkCtrl.pixel_array+pWindow->DisplayArea.Y*DeskWorkCtrl.WorkArea.W+pWindow->DisplayArea.X;
	while(Height!=0){
        PixelArrayCopy(pSource,pDestination,Width);
		pSource=(EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)(pSource+pWindow->DisplayArea.W);
        pDestination=(EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)(pDestination+DeskCtrl.DeskArea.W);
        Height--;
    }
    DeskWorkCtrl.WorkWindowDirty=TRUE;
}

VOID DeskInactiveWindowMemoryDraw(WINDOW *pWindow)
{	
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pMemory,*pMemory2;
    UINT32 Height,Width;
    WINDOW_TABLE *pTable;
    WINDOW_DEVICE *pDevice;
    GRAPHIC_POSITION Position;
    UINT8 *pString;
	
	if(pWindow==(WINDOW *)NULL) return;
	if(pWindow==DeskWindowCtrl.WindowListTail) return; // no draw work area if work area is active window
	if(pWindow==DeskWindowCtrl.WindowListHead) return; // no draw workbar area if work bar is active window
	// draw window content first
    pTable=pWindow->UserTableList;
    while(pTable!=(WINDOW_TABLE *)NULL){
    	DeskTableBackgroundDraw(DESK_DEVICE_DRAW_INACTIVEWINDOW,pWindow,pTable);
    	pDevice=pTable->DeviceList;
    	while(pDevice!=(WINDOW_DEVICE *)NULL){
	    	if(pDevice->Type==WINDOW_DEVICE_CAPTION){
	    	    DeskDeviceCaptionDraw(DESK_DEVICE_DRAW_INACTIVEWINDOW,pWindow,pTable,(CAPTION *)pDevice->pDevice);
	    	}
	    	else if(pDevice->Type==WINDOW_DEVICE_BOARD){
	    		DeskDeviceBoardDraw(DESK_DEVICE_DRAW_INACTIVEWINDOW,pWindow,pTable,(BOARD *)pDevice->pDevice);
	    	}
	    	else if(pDevice->Type==WINDOW_DEVICE_BUTTON){
	    		DeskDeviceButtonDraw(DESK_DEVICE_DRAW_INACTIVEWINDOW,pWindow,pTable,(WINDOW_BUTTON *)pDevice->pDevice);
	    	}
	    	else if(pDevice->Type==WINDOW_DEVICE_STRINGBOX){
	    		DeskDeviceStringboxDraw(DESK_DEVICE_DRAW_INACTIVEWINDOW,pWindow,pTable,(WINDOW_STRINGBOX *)pDevice->pDevice);
	    	}
	    	pDevice=pDevice->Next;
    	}
    	pTable=pTable->Next;
    }
	
	Width=pWindow->Outline.OuterArea.W;
	Height=pWindow->Outline.OuterArea.H;
	pMemory=DeskInactiveWindowCtrl.pInactiveWindowMemory;
	PixelArray256Set(pMemory,GfxPaletteClut[GFX_COLOR_DEEPGRAY],Width);
	pMemory=pMemory+pWindow->Outline.OuterArea.W;
	PixelArray256Set(pMemory,GfxPaletteClut[GFX_COLOR_LIGHTGRAY],Width);
	pMemory=DeskInactiveWindowCtrl.pInactiveWindowMemory+pWindow->Outline.OuterArea.W*(Height-2);
	PixelArray256Set(pMemory,GfxPaletteClut[GFX_COLOR_LIGHTGRAY],Width);
	pMemory=pMemory+pWindow->Outline.OuterArea.W;
	PixelArray256Set(pMemory,GfxPaletteClut[GFX_COLOR_DEEPGRAY],Width);
	Height=Height-2;
	pMemory=DeskInactiveWindowCtrl.pInactiveWindowMemory+pWindow->Outline.OuterArea.W;
	while(Height!=0){
		pMemory2=pMemory;
		PixelArray256Set(pMemory2,GfxPaletteClut[GFX_COLOR_DEEPGRAY],1);
		pMemory2++;
		PixelArray256Set(pMemory2,GfxPaletteClut[GFX_COLOR_LIGHTGRAY],1);
		pMemory2=pMemory+Width-2;
		PixelArray256Set(pMemory2,GfxPaletteClut[GFX_COLOR_LIGHTGRAY],1);
		pMemory2++;
		PixelArray256Set(pMemory2,GfxPaletteClut[GFX_COLOR_DEEPGRAY],1);
		pMemory=pMemory+Width;
		Height--;
	}
    pTable=&pWindow->HeaderTable;
	pMemory=DeskInactiveWindowCtrl.pInactiveWindowMemory
	        +pTable->Area.Y*pWindow->Outline.OuterArea.W
	        +pTable->Area.X;
	Width=pTable->Area.W;
	Height=pTable->Area.H;
	while(Height!=1){
		PixelArray256Set(pMemory,GfxPaletteClut[GFX_COLOR_GRAY],Width);
		pMemory=pMemory+pWindow->Outline.OuterArea.W;
		Height--;
	}
	PixelArray256Set(pMemory,GfxPaletteClut[GFX_COLOR_LIGHTGRAY],Width);
	if(pWindow->Type==WINDOW_TYPE_STARTMENU) Width=pTable->Area.W; 
	else Width=pTable->Area.W-10*3; // 3 icons+right window edge think
	Width=Width/STRING_SIZE;
    Position.X=pTable->Area.X;
    Position.Y=pTable->Area.Y+1;
    pString=pWindow->pTitle;
    while((*pString!=0)&&(Width!=0)){
        DeskInactiveWindowMemoryTitleCharDraw(pWindow,FontBitmapGet(FONT8X8,*pString),(GRAPHIC_POSITION *)&Position);
        Position.X+=STRING_SIZE;
        pString++;
        Width--;
    }
	DeskDeviceButtonDraw(DESK_DEVICE_DRAW_INACTIVEWINDOW,pWindow,pTable,&pWindow->HideButton);
	DeskDeviceButtonDraw(DESK_DEVICE_DRAW_INACTIVEWINDOW,pWindow,pTable,&pWindow->MaximunButton);
	DeskDeviceButtonDraw(DESK_DEVICE_DRAW_INACTIVEWINDOW,pWindow,pTable,&pWindow->CloseButton);
    pWindow->Dirty=FALSE;
}

VOID DeskInactiveWindowMemoryTitleCharDraw(WINDOW *pWindow,UINT8 *pBitmap,GRAPHIC_POSITION *pPosition)
{
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pBitmapStart;
    UINT8  i,j,tmp;
	UINT32 height = *(UINT32*)&pBitmap[Height_OFFSET];
	UINT32 width  = *(UINT32*)&pBitmap[Width_OFFSET];
	UINT32 size  = *(UINT32*)&pBitmap[Size_OFFSET];
	UINT8* bmp = &pBitmap[PIX_OFFSET];

    pBitmapStart=DeskInactiveWindowCtrl.pInactiveWindowMemory
                 +pWindow->Outline.OuterArea.W*pPosition->Y
                 +pPosition->X;
	tmp = height - 1;
    for(i=0;i<height;i++){
		for(j=0;j<width;j++) PixelArray256Set(pBitmapStart+j,bmp[j+tmp*width],1);
		pBitmapStart=pBitmapStart+pWindow->Outline.OuterArea.W;
		tmp--;
	}
}

