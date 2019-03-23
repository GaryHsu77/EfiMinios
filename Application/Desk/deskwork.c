#include <includes.h>

const UINT8 DeskWorkWindowName[]="WORK";
DESK_WORKWINDOW_CONTROL DeskWorkCtrl;

VOID DeskWorkWindowInit(VOID)
{   
	EFI_STATUS Status ;	

    DeskWorkCtrl.WorkWindowDirty=FALSE;
    DeskWorkCtrl.pWorkMemory=(UINT8 *)NULL;
    DeskWorkCtrl.WorkGfx.BgColor=GFX_COLOR_YELLOWGREEN3;
    DeskWorkCtrl.WorkGfx.FgColor=GFX_COLOR_BLACK;
    DeskWorkCtrl.WorkGfx.FontColor=GFX_COLOR_WHITE; 
    
    DeskWorkCtrl.WorkArea.X=OsdCtrl.ScreenArea.X;
    DeskWorkCtrl.WorkArea.Y=OsdCtrl.ScreenArea.Y;
    DeskWorkCtrl.WorkArea.W=OsdCtrl.ScreenArea.W;
    DeskWorkCtrl.WorkArea.H=OsdCtrl.ScreenArea.H-DESK_WORKBAR_HEIGHT;
    
    DeskWorkCtrl.WorkMemoryLength=DeskWorkCtrl.WorkArea.W*DeskWorkCtrl.WorkArea.H;
    Status = gBS->AllocatePool(EfiBootServicesData,DeskWorkCtrl.WorkMemoryLength,&(DeskWorkCtrl.pWorkMemory));
	if(Status != EFI_SUCCESS)return;
	Status = gBS->AllocatePool(EfiBootServicesData,OsdCtrl.ScreenArea.W*OsdCtrl.ScreenArea.H*sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL),&DeskWorkCtrl.pixel_array);
    if(Status != EFI_SUCCESS)return;
	WindowVariableInit(&DeskWorkCtrl.Window,WINDOW_TYPE_WORK);
    DeskWorkCtrl.Window.pTitle=(UINT8 *)DeskWorkWindowName;  
    
    DeskWorkCtrl.Window.DisplayArea.X=DeskWorkCtrl.WorkArea.X;
    DeskWorkCtrl.Window.DisplayArea.Y=DeskWorkCtrl.WorkArea.Y;
    DeskWorkCtrl.Window.DisplayArea.W=DeskWorkCtrl.WorkArea.W;
    DeskWorkCtrl.Window.DisplayArea.H=DeskWorkCtrl.WorkArea.H;
    /*
    DeskWorkCtrl.Window.DeviceArea.X=DeskWorkCtrl.WorkArea.X;
    DeskWorkCtrl.Window.DeviceArea.Y=DeskWorkCtrl.WorkArea.Y;
    DeskWorkCtrl.Window.DeviceArea.W=DeskWorkCtrl.WorkArea.W;
    DeskWorkCtrl.Window.DeviceArea.H=DeskWorkCtrl.WorkArea.H;
    DeskWorkCtrl.Window.DeviceDisplayArea.X=DeskWorkCtrl.WorkArea.X;
    DeskWorkCtrl.Window.DeviceDisplayArea.Y=DeskWorkCtrl.WorkArea.Y;
    DeskWorkCtrl.Window.DeviceDisplayArea.W=DeskWorkCtrl.WorkArea.W;
    DeskWorkCtrl.Window.DeviceDisplayArea.H=DeskWorkCtrl.WorkArea.H;

    DeskWorkCtrl.Window.Outline.Type=WINDOW_OUTLINE_GENERAL;
    DeskWorkCtrl.Window.Outline.OuterArea.X=0; // no outer area
    DeskWorkCtrl.Window.Outline.OuterArea.Y=0; // no outer area
    DeskWorkCtrl.Window.Outline.OuterArea.W=0; // no outer area
    DeskWorkCtrl.Window.Outline.OuterArea.H=0; // no outer area
    DeskWorkCtrl.Window.Outline.InnerArea.X=0; // no inner area
    DeskWorkCtrl.Window.Outline.InnerArea.Y=0; // no inner area
    DeskWorkCtrl.Window.Outline.InnerArea.W=0; // no inner area
    DeskWorkCtrl.Window.Outline.InnerArea.H=0; // no inner area
    DeskWorkCtrl.Window.OutlineTable.DeviceList=(WINDOW_DEVICE *)NULL;
    DeskWorkCtrl.Window.OutlineTable.Area.X=0; // no outline table area
    DeskWorkCtrl.Window.OutlineTable.Area.Y=0;
    DeskWorkCtrl.Window.OutlineTable.Area.W=0;
    DeskWorkCtrl.Window.OutlineTable.Area.H=0;
    DeskWorkCtrl.Window.HeaderTable.DeviceList=(WINDOW_DEVICE *)NULL;
    DeskWorkCtrl.Window.HeaderTable.Area.X=0; // no header table area
    DeskWorkCtrl.Window.HeaderTable.Area.Y=0;
    DeskWorkCtrl.Window.HeaderTable.Area.W=0;
    DeskWorkCtrl.Window.HeaderTable.Area.H=0;
    */
    DeskWindowWindowListTailSet((WINDOW *)&DeskWorkCtrl.Window);
}
//initialize work window
VOID DeskWorkWindowMemoryDraw(VOID)
{
    UINT8 *pData;
    BOOLEAN HasDeskBg;
    
    //draw active desktop background picture
    HasDeskBg=FALSE;
    pData=(UINT8*)&DeskBackground;

    if((pData[0]=='B')||(pData[1]=='M'))
	{
		UINT32 height = *(UINT32*)&pData[Height_OFFSET];
		UINT32 width  = *(UINT32*)&pData[Width_OFFSET];
		if(width==OsdCtrl.ScreenArea.W&&height==OsdCtrl.ScreenArea.H) HasDeskBg=TRUE;
		else{
			//GDB : Do some info notify!
			GDP(L"GDB : DeskWorkWindowMemoryDraw");
			while(1){};
		}
	}
	
    if(HasDeskBg==TRUE){
        // copy bitmap to work window memory
        PixelBmpArraySet(DeskWorkCtrl.pixel_array, pData);
		PixelArrayCopy(DeskWorkCtrl.pixel_array, OsdCtrl.pPixMemory, DeskWorkCtrl.WorkMemoryLength);
    }
	DeskWorkCtrl.WorkWindowDirty=TRUE;
}

VOID DeskWorkWindow2OsdUpdate(VOID)
{
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL  *pSource;
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL  *pDestination;
    UINT32 Height,Width,j;
    WINDOW *pWindow;
    
    if(DeskWorkCtrl.WorkWindowDirty==FALSE) return;
    pWindow=DeskWindowActiveWindowGet();
    if((pWindow==DeskWindowCtrl.WindowListHead)||(pWindow==DeskWindowCtrl.WindowListTail)){
        Height=DeskWorkCtrl.WorkArea.H;
        Width=DeskWorkCtrl.WorkArea.W;
        pSource=DeskWorkCtrl.pixel_array;
        pDestination=OsdCtrl.pPixMemory;
		j=0;
        while((Height!=0)&&(Width!=0)){
			PixelArrayCopy(pSource,pDestination,Width);
			PixelArrayDraw(pDestination, 0, 0+j, Width, 1);
            pSource=pSource+Width;
            pDestination=pDestination+Width;
            Height--;j++;
        }
    }
    else{
        //upper part
        if(pWindow->DisplayArea.Y!=0){
            Height=pWindow->DisplayArea.Y;
             Width=DeskWorkCtrl.WorkArea.W;
			pSource=DeskWorkCtrl.pixel_array;
            pDestination=OsdCtrl.pPixMemory;
			j=0;
            while((Height!=0)&&(Width!=0)){
				PixelArrayCopy(pSource, pDestination, Width);
				PixelArrayDraw(pDestination, 0, 0+j, Width, 1);
                pSource=(EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)(pSource+Width);
                pDestination=(EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)(pDestination+Width);
                Height--;j++;
            }
        }
        //left part
        if(pWindow->DisplayArea.X!=0){
            Height=pWindow->DisplayArea.H;
            Width=pWindow->DisplayArea.X;
            pSource=DeskWorkCtrl.pixel_array+DeskWorkCtrl.WorkArea.W*pWindow->DisplayArea.Y;
            pDestination=OsdCtrl.pPixMemory+DeskWorkCtrl.WorkArea.W*pWindow->DisplayArea.Y;
			j=0;
            while((Height!=0)&&(Width!=0)){
				PixelArrayCopy(pSource, pDestination, Width);
				PixelArrayDraw(pDestination, 0, pWindow->DisplayArea.Y+j, Width, 1);
                pSource=(EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)(pSource+DeskWorkCtrl.WorkArea.W);
                pDestination=(EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)(pDestination+DeskWorkCtrl.WorkArea.W);
                Height--;j++;
            }
        }
        //right part
        if((pWindow->DisplayArea.X+pWindow->DisplayArea.W)<DeskWorkCtrl.WorkArea.W){
            Height=pWindow->DisplayArea.H;
            Width=DeskWorkCtrl.WorkArea.W-(pWindow->DisplayArea.X+pWindow->DisplayArea.W);
            pSource=DeskWorkCtrl.pixel_array+
                    DeskWorkCtrl.WorkArea.W*pWindow->DisplayArea.Y+
                    pWindow->DisplayArea.X+
                    pWindow->DisplayArea.W;
            pDestination=OsdCtrl.pPixMemory+
                         DeskWorkCtrl.WorkArea.W*pWindow->DisplayArea.Y+
                         pWindow->DisplayArea.X+
                         pWindow->DisplayArea.W;
			j=0;
            while((Height!=0)&&(Width!=0)){
				PixelArrayCopy(pSource, pDestination, Width);
				PixelArrayDraw(pDestination, pWindow->DisplayArea.X+pWindow->DisplayArea.W, pWindow->DisplayArea.Y+j, Width, 1);
                pSource=(EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)(pSource+DeskWorkCtrl.WorkArea.W);
                pDestination=(EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)(pDestination+DeskWorkCtrl.WorkArea.W);;
                Height--;j++;
            }
        }
        //bottom part
        if((pWindow->DisplayArea.Y+pWindow->DisplayArea.H)<DeskWorkCtrl.WorkArea.H){
            Height=DeskWorkCtrl.WorkArea.H-(pWindow->DisplayArea.Y+pWindow->DisplayArea.H);
            Width=DeskWorkCtrl.WorkArea.W;
            pSource=DeskWorkCtrl.pixel_array+DeskWorkCtrl.WorkArea.W*(pWindow->DisplayArea.Y+pWindow->DisplayArea.H);
            pDestination=OsdCtrl.pPixMemory+DeskWorkCtrl.WorkArea.W*(pWindow->DisplayArea.Y+pWindow->DisplayArea.H);
            j=0;
			while((Height!=0)&&(Width!=0)){
				PixelArrayCopy(pSource, pDestination, Width);
				PixelArrayDraw(pDestination, 0, pWindow->DisplayArea.Y+pWindow->DisplayArea.H+j, Width, 1);
                pSource=(EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)(pSource+DeskWorkCtrl.WorkArea.W);
                pDestination=(EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)(pDestination+DeskWorkCtrl.WorkArea.W);
                Height--;j++;
            }
        }
    }
    DeskWorkCtrl.Window.Dirty=FALSE;
    DeskWorkCtrl.WorkWindowDirty=FALSE;
}

// for active window moving use
VOID DeskWorkWindow2OsdCopy(GRAPHIC_AREA *pArea)
{
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pSource,*pDestination;
    UINT32 Height,Width,j=0;

    if(pArea->W==0) return;
    if(pArea->H==0) return;

    pSource=(EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)(DeskWorkCtrl.pixel_array+DeskWorkCtrl.WorkArea.W*pArea->Y+pArea->X);    
    pDestination=(EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)(OsdCtrl.pPixMemory+OsdCtrl.ScreenArea.W*pArea->Y+pArea->X);    
    pDestination=(EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)(OsdCtrl.pPixMemory+OsdCtrl.ScreenArea.W*pArea->Y+pArea->X);    
    Height=pArea->H;
    Width=pArea->W;
    while((Height!=0)&&(Width!=0)){
		PixelArrayCopy(pSource,pDestination,Width);
		PixelArrayDraw(pDestination, pArea->X, pArea->Y+j, Width, 1);
        pSource=(EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)(pSource+DeskWorkCtrl.WorkArea.W);
        pDestination=(EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)(pDestination+OsdCtrl.ScreenArea.W);
        Height--;
		j++;
    }
}
