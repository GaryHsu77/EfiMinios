#include <includes.h>

VOID DeskTableUserTableAdd(WINDOW *pWindow,WINDOW_TABLE *pTable){
    WINDOW_TABLE *pTable2;
    MY_MUTEX mutex;

    if(pWindow==(WINDOW *)NULL) return;
    if(pTable==(WINDOW_TABLE *)NULL) return;
    mutex = OsEnterCritical();
    pTable->Prev=(WINDOW_TABLE *)NULL;
    pTable->Next=(WINDOW_TABLE *)NULL;
    if(pWindow->UserTableList==(WINDOW_TABLE *)NULL){
        pWindow->UserTableList=pTable;
    }
    else{
        pTable2=pWindow->UserTableList;
        while(pTable2->Next!=(WINDOW_TABLE *)NULL) pTable2=pTable2->Next;
        pTable2->Next=pTable;
        pTable->Prev=pTable2;
    }
    OsExitCritical(mutex);
}

VOID DeskTableWindowDeviceAdd(WINDOW_TABLE *pTable,WINDOW_DEVICE *pDevice){
    WINDOW_DEVICE *pDevice2;
    MY_MUTEX mutex;

    if(pTable==(WINDOW_TABLE *)NULL) return;
    if(pDevice==(WINDOW_DEVICE *)NULL) return;
    mutex = OsEnterCritical();
    pDevice->Prev=(WINDOW_DEVICE *)NULL;
    pDevice->Next=(WINDOW_DEVICE *)NULL;
    if(pTable->DeviceList==(WINDOW_DEVICE *)NULL){
        pTable->DeviceList=pDevice;
    }
    else{
        pDevice2=pTable->DeviceList;
        while(pDevice2->Next!=(WINDOW_DEVICE *)NULL) pDevice2=pDevice2->Next;
        pDevice2->Next=pDevice;
        pDevice->Prev=pDevice2;
    }
    OsExitCritical(mutex);
}

VOID DeskTableBackgroundDraw(UINT8 DrawPlace,WINDOW *pWindow,WINDOW_TABLE *pTable){
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pMemory;
    UINT32 Height,Width;
    GRAPHIC_POSITION Position;
	
    if(DrawPlace==DESK_DEVICE_DRAW_ACTIVEWINDOW){
		EFI_GRAPHICS_OUTPUT_BLT_PIXEL Color = Bmp2Rgb(GfxPaletteClut[pTable->Gfx.BgColor]);
        pMemory=DeskActiveWindowCtrl.pActiveWindowMemory+pWindow->DisplayArea.W*pTable->Area.Y+pTable->Area.X;
        Height=pTable->Area.H;
        Width=pTable->Area.W;
        while((Width!=0)&&(Height!=0)){
			PixelArraySet(pMemory, Color, Width);
            pMemory=pMemory+pWindow->DisplayArea.W;
            Height--;
        }
        pWindow->Dirty=TRUE;
    }
    else if(DrawPlace==DESK_DEVICE_DRAW_INACTIVEWINDOW){
		EFI_GRAPHICS_OUTPUT_BLT_PIXEL Color = Bmp2Rgb(GfxPaletteClut[pTable->Gfx.BgColor]);
        pMemory=DeskInactiveWindowCtrl.pInactiveWindowMemory+pWindow->DisplayArea.W*pTable->Area.Y+pTable->Area.X;
        Height=pTable->Area.H;
        Width=pTable->Area.W;
        while((Width!=0)&&(Height!=0)){
			PixelArraySet(pMemory, Color, Width);
            pMemory=pMemory+pWindow->DisplayArea.W;
            Height--;
        }
        pWindow->Dirty=TRUE;
    }
    else if(DrawPlace==DESK_DEVICE_DRAW_OSD){
		EFI_STATUS Status;
		EFI_GRAPHICS_OUTPUT_BLT_PIXEL Color = Bmp2Rgb(GfxPaletteClut[pTable->Gfx.BgColor]);
        Position.X=pWindow->DisplayArea.X+pTable->Area.X;
        Position.Y=pWindow->DisplayArea.Y+pTable->Area.Y;
        pMemory=OsdCtrl.pPixMemory+DeskWorkCtrl.WorkArea.W*Position.Y+Position.X;      
        if(pWindow->DeviceDisplayArea.H<pTable->Area.H) Height=pWindow->DeviceDisplayArea.H;
        else Height=pTable->Area.H;
        if(pWindow->DeviceDisplayArea.W<pTable->Area.W) Width=pWindow->DeviceDisplayArea.W;
        else Width=pTable->Area.W;
		
		if(GOP) {
			Status = GOP->Blt(GOP,&Color,EfiBltVideoFill,0,0,Position.X,Position.Y,Width,Height,0);
		}
		while(Height!=0){
			PixelArraySet(pMemory, Color, Width);
            pMemory=pMemory+DeskCtrl.DeskArea.W;
            Height--;
        }
    }
}
