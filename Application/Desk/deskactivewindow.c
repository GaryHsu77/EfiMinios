#include <includes.h>

DESK_ACTIVEWINDOW_CONTROL DeskActiveWindowCtrl;

VOID DeskActiveWindowInit(VOID)
{
	EFI_STATUS Status ;	
    DeskActiveWindowCtrl.DirectContentDraw=FALSE;
    DeskActiveWindowCtrl.ActiveWindowDirty=FALSE;
    DeskActiveWindowCtrl.pActiveWindowMemory=(EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)NULL;
	Status = gBS->AllocatePool(EfiBootServicesData,DeskWorkCtrl.WorkMemoryLength*sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL),&(DeskActiveWindowCtrl.pActiveWindowMemory));
	if(Status != EFI_SUCCESS){
		GDP(L"ERROR : DeskActiveWindowInit allocated memory fail.");
		return;
	}
}

VOID DeskActiveWindowMovingMouseMapCapture(WINDOW *pWindow){ //from osd memory
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pSource;
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pDestination;
    UINT8 Height,Width;

    Width=DESK_MOUSE_MAP_WIDTH;
    Height=DESK_MOUSE_MAP_HEIGHT;
    pSource=DeskActiveWindowCtrl.pActiveWindowMemory
                 +pWindow->DisplayArea.W*DeskMouseCtrl.MouseRelativePosition.Y
                 +DeskMouseCtrl.MouseRelativePosition.X;
    pDestination=DeskMouseCtrl.pixel_array2;
    while(Height!=0){
		PixelArrayCopy(pSource,pDestination,Width);
        pSource=(EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)(pSource+pWindow->DisplayArea.W);
        pDestination=(EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)(pDestination+DESK_MOUSE_MAP_WIDTH);
        Height--;
    }
	PixelArrayCopy(DeskMouseCtrl.pixel_array2,DeskMouseCtrl.pixel_array,DeskMouseCtrl.MouseMemoryLength);
}

VOID DeskActiveWindowMovingMouseMapRecovery(WINDOW *pWindow){
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pSource;
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pDestination;
    UINT8 Height,Width;

    Width=DESK_MOUSE_MAP_WIDTH;
    Height=DESK_MOUSE_MAP_HEIGHT;
    pSource=DeskMouseCtrl.pixel_array2;
    pDestination=DeskActiveWindowCtrl.pActiveWindowMemory
                 +pWindow->DisplayArea.W*DeskMouseCtrl.MouseRelativePosition.Y
                 +DeskMouseCtrl.MouseRelativePosition.X;
    while(Height!=0){
		PixelArrayCopy(pSource,pDestination,Width);
        pDestination=(EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)(pDestination+pWindow->DisplayArea.W);
        pSource=(EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)(pSource+DESK_MOUSE_MAP_WIDTH);
        Height--;
    }
}

VOID DeskActiveWindowMovingMouseCursorDraw(WINDOW *pWindow){
    UINT8  i,j;//,k;
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pBitmapStart;

    pBitmapStart=DeskActiveWindowCtrl.pActiveWindowMemory
                 +pWindow->DisplayArea.W*DeskMouseCtrl.MouseRelativePosition.Y
                 +DeskMouseCtrl.MouseRelativePosition.X;
	
	for(i=0;i<DESK_MOUSE_MAP_HEIGHT;i++){
		for(j=0;j<DESK_MOUSE_MAP_WIDTH;j++){
			EFI_GRAPHICS_OUTPUT_BLT_PIXEL color = DeskMouseCursorPixel[i*DESK_MOUSE_MAP_WIDTH+j];
			if(color.Blue==0&&color.Green==0&&color.Red==0)continue;
			pBitmapStart[i*pWindow->DisplayArea.W+j]=DeskMouseCursorPixel[i*DESK_MOUSE_MAP_WIDTH+j];
		}
	}
}

VOID DeskActiveWindowMemory2OsdUpdate(WINDOW *pWindow){
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pSource,*pDestination;
    UINT32 Height,Width,j=0;

    if(pWindow==(WINDOW *)NULL) return;
    if(DeskActiveWindowCtrl.ActiveWindowDirty==FALSE) return;
    if((pWindow->DisplayArea.X+pWindow->DisplayArea.W)>DeskWorkCtrl.WorkArea.W) Width=DeskWorkCtrl.WorkArea.W-pWindow->DisplayArea.X;
    else Width=pWindow->DisplayArea.W;
    if((pWindow->DisplayArea.Y+pWindow->DisplayArea.H)>DeskWorkCtrl.WorkArea.H) Height=DeskWorkCtrl.WorkArea.H-pWindow->DisplayArea.Y;
    else Height=pWindow->DisplayArea.H;
    pSource=DeskActiveWindowCtrl.pActiveWindowMemory;
    pDestination=OsdCtrl.pPixMemory+DeskWorkCtrl.WorkArea.W*pWindow->DisplayArea.Y+pWindow->DisplayArea.X;

	while(Height!=0){
		PixelArrayCopy(pSource, pDestination, Width);
		PixelArrayDraw(pDestination, pWindow->DisplayArea.X, pWindow->DisplayArea.Y+j, Width, 1);
        pSource=(EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)(pSource+pWindow->DisplayArea.W);
        pDestination=(EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)(pDestination+DeskCtrl.DeskArea.W);
        Height--;
		j++;
    }
    DeskActiveWindowCtrl.ActiveWindowDirty=FALSE;
}

VOID DeskActiveWindowContent2OsdUpdate(WINDOW *pWindow){
    WINDOW_TABLE *pTable;
    WINDOW_DEVICE *pDevice;

    if(pWindow==(WINDOW *)NULL) return;
    pTable=pWindow->UserTableList;
    while(pTable!=(WINDOW_TABLE *)NULL){
        pDevice=pTable->DeviceList;
        while(pDevice!=(WINDOW_DEVICE *)NULL){
            if(pDevice->Type==WINDOW_DEVICE_CAPTION){
                DeskDeviceCaptionDraw(DESK_DEVICE_DRAW_OSD,pWindow,pTable,(CAPTION *)pDevice->pDevice);
            }
            else if(pDevice->Type==WINDOW_DEVICE_BOARD){
                DeskDeviceBoardDraw(DESK_DEVICE_DRAW_OSD,pWindow,pTable,(BOARD *)pDevice->pDevice);
            }
            else if(pDevice->Type==WINDOW_DEVICE_BUTTON){
                DeskDeviceButtonDraw(DESK_DEVICE_DRAW_OSD,pWindow,pTable,(WINDOW_BUTTON *)pDevice->pDevice);
            }
            else if(pDevice->Type==WINDOW_DEVICE_STRINGBOX){
                DeskDeviceStringboxDraw(DESK_DEVICE_DRAW_OSD,pWindow,pTable,(WINDOW_STRINGBOX *)pDevice->pDevice);
            }
            pDevice=pDevice->Next;
        }
        pTable=pTable->Next;
    }
    pWindow->Dirty=FALSE;
}

VOID DeskActiveWindowMemoryDraw(WINDOW *pWindow){
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL  *pMemory,*pMemory2;
    UINT32 Height,Width;
    WINDOW_TABLE *pTable;
    WINDOW_DEVICE *pDevice;
    GRAPHIC_POSITION Position;
    UINT8 *pString;
    
    if(pWindow==(WINDOW *)NULL) return;
    if(pWindow==DeskWindowCtrl.WindowListTail) return; // no draw work area if work area is active window
    if(pWindow==DeskWindowCtrl.WindowListHead) return; // no draw workbar area if work bar is active window
    // draw window content
    pTable=pWindow->UserTableList;
    while(pTable!=(WINDOW_TABLE *)NULL){
        DeskTableBackgroundDraw(DESK_DEVICE_DRAW_ACTIVEWINDOW,pWindow,pTable);
        pDevice=pTable->DeviceList;
        while(pDevice!=(WINDOW_DEVICE *)NULL){
            if(pDevice->Type==WINDOW_DEVICE_CAPTION){
                DeskDeviceCaptionDraw(DESK_DEVICE_DRAW_ACTIVEWINDOW,pWindow,pTable,(CAPTION *)pDevice->pDevice);
            }
            else if(pDevice->Type==WINDOW_DEVICE_BOARD){
                DeskDeviceBoardDraw(DESK_DEVICE_DRAW_ACTIVEWINDOW,pWindow,pTable,(BOARD *)pDevice->pDevice);
            }
            else if(pDevice->Type==WINDOW_DEVICE_BUTTON){
                DeskDeviceButtonDraw(DESK_DEVICE_DRAW_ACTIVEWINDOW,pWindow,pTable,(WINDOW_BUTTON *)pDevice->pDevice);
            }
            else if(pDevice->Type==WINDOW_DEVICE_STRINGBOX){
                DeskDeviceStringboxDraw(DESK_DEVICE_DRAW_ACTIVEWINDOW,pWindow,pTable,(WINDOW_STRINGBOX *)pDevice->pDevice);
            }
            pDevice=pDevice->Next;
        }
        pTable=pTable->Next;
    }
    Width=pWindow->Outline.OuterArea.W;
    Height=pWindow->Outline.OuterArea.H;
    pMemory=DeskActiveWindowCtrl.pActiveWindowMemory;
	PixelArray256Set(pMemory, GfxPaletteClut[GFX_COLOR_BLUE],Width);
    pMemory=pMemory+pWindow->Outline.OuterArea.W;
	PixelArray256Set(pMemory, GfxPaletteClut[GFX_COLOR_LIGHTBLUE3],Width);
    pMemory=DeskActiveWindowCtrl.pActiveWindowMemory+pWindow->Outline.OuterArea.W*(Height-2);
	PixelArray256Set(pMemory, GfxPaletteClut[GFX_COLOR_LIGHTBLUE3],Width);
    pMemory=pMemory+pWindow->Outline.OuterArea.W;
	PixelArray256Set(pMemory, GfxPaletteClut[GFX_COLOR_BLUE],Width);
    Height=Height-2;
    pMemory=DeskActiveWindowCtrl.pActiveWindowMemory+pWindow->Outline.OuterArea.W;
    while(Height!=0){
        pMemory2=pMemory;
		PixelArray256Set(pMemory2, GfxPaletteClut[GFX_COLOR_BLUE],1);
        pMemory2++;
		PixelArray256Set(pMemory2, GfxPaletteClut[GFX_COLOR_LIGHTBLUE3],1);
        pMemory2=pMemory+Width-2;
		PixelArray256Set(pMemory2, GfxPaletteClut[GFX_COLOR_LIGHTBLUE3],1);
        pMemory2++;
		PixelArray256Set(pMemory2, GfxPaletteClut[GFX_COLOR_BLUE],1);
        pMemory=pMemory+Width;
        Height--;
    }
    pTable=&pWindow->HeaderTable;
    pMemory=DeskActiveWindowCtrl.pActiveWindowMemory
            +pTable->Area.Y*pWindow->Outline.OuterArea.W
            +pTable->Area.X;
    Width=pTable->Area.W;
    Height=pTable->Area.H;
    while(Height!=1){
		PixelArray256Set(pMemory, GfxPaletteClut[GFX_COLOR_LIGHTBLUE0],Width);
        pMemory=pMemory+pWindow->Outline.OuterArea.W;
        Height--;
    }
	PixelArray256Set(pMemory, GfxPaletteClut[GFX_COLOR_LIGHTBLUE3],Width);
    if(pWindow->Type==WINDOW_TYPE_STARTMENU) Width=pTable->Area.W; 
    else Width=pTable->Area.W-10*3; // 3 icons+right window edge think
    Width=Width/STRING_SIZE;
    Position.X=pTable->Area.X;
    Position.Y=pTable->Area.Y+1;
    pString=pWindow->pTitle;
    while((*pString!=0)&&(Width!=0)){
        DeskActiveWindowMemoryTitleCharDraw(pWindow,FontBitmapGet(FONT8X8,*pString),(GRAPHIC_POSITION *)&Position);
        Position.X+=STRING_SIZE;
        pString++;
        Width--;
    }
    DeskDeviceButtonDraw(DESK_DEVICE_DRAW_ACTIVEWINDOW,pWindow,pTable,&pWindow->HideButton);
    DeskDeviceButtonDraw(DESK_DEVICE_DRAW_ACTIVEWINDOW,pWindow,pTable,&pWindow->MaximunButton);
    DeskDeviceButtonDraw(DESK_DEVICE_DRAW_ACTIVEWINDOW,pWindow,pTable,&pWindow->CloseButton);
    pWindow->Dirty=FALSE;
    DeskActiveWindowCtrl.ActiveWindowDirty=TRUE;
}

VOID DeskActiveWindowMemoryTitleCharDraw(WINDOW *pWindow,UINT8 *pBitmap,GRAPHIC_POSITION *pPosition){
    UINT8  i,j,tmp;
    UINT32 height = *(UINT32*)&pBitmap[Height_OFFSET];
	UINT32 width  = *(UINT32*)&pBitmap[Width_OFFSET];
	UINT32 size  = *(UINT32*)&pBitmap[Size_OFFSET];
	UINT8* bmp = &pBitmap[PIX_OFFSET];
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pBitmapStart;

    pBitmapStart=DeskActiveWindowCtrl.pActiveWindowMemory
                 +pWindow->Outline.OuterArea.W*pPosition->Y
                 +pPosition->X;
	tmp = height - 1;
	for(i=0;i<height;i++){
		for(j=0;j<width;j++) PixelArray256Set(pBitmapStart+j,bmp[j+tmp*width],1);
		pBitmapStart=pBitmapStart+pWindow->Outline.OuterArea.W;
		tmp--;
	}
}

VOID DeskActiveWindowMoveInit(WINDOW *pWindow){
    DeskMouseCtrl.MouseRelativePosition.X=DeskMouseCtrl.MousePointer.X-pWindow->DisplayArea.X;
    DeskMouseCtrl.MouseRelativePosition.Y=DeskMouseCtrl.MousePointer.Y-pWindow->DisplayArea.Y;
}

VOID DeskActiveWindowMoveStop(WINDOW *pWindow){
    DeskMouseCtrl.MousePointer.X=pWindow->DisplayArea.X+DeskMouseCtrl.MouseRelativePosition.X;
    DeskMouseCtrl.MousePointer.Y=pWindow->DisplayArea.Y+DeskMouseCtrl.MouseRelativePosition.Y;
    DeskMouseCtrl.MousePrevious.X=DeskMouseCtrl.MousePointer.X;
    DeskMouseCtrl.MousePrevious.Y=DeskMouseCtrl.MousePointer.Y;
}

VOID DeskActiveWindowMoveSvc(WINDOW *pWindow){
    EFI_SIMPLE_POINTER_STATE MouseSignal;
    UINT16 Xmovement,Ymovement;
	INT16 X_org,Y_org,X_new,Y_new;
    GRAPHIC_AREA CopyArea;
    GRAPHIC_AREA NewWindowArea;
    GRAPHIC_AREA OriginalWindowArea;
    UINT8 WindowMoveDirty;
    
    if(MouseBufferCheck()==BUFFER_EMPTY) return;
    NewWindowArea.X=pWindow->DisplayArea.X;
    NewWindowArea.Y=pWindow->DisplayArea.Y;
    NewWindowArea.H=pWindow->DisplayArea.H;
    NewWindowArea.W=pWindow->DisplayArea.W;
    OriginalWindowArea.X=pWindow->DisplayArea.X;
    OriginalWindowArea.Y=pWindow->DisplayArea.Y;
    OriginalWindowArea.H=pWindow->DisplayArea.H;
    OriginalWindowArea.W=pWindow->DisplayArea.W;
	
	X_org=DeskMouseCtrl.MousePointer.X;
	Y_org=DeskMouseCtrl.MousePointer.Y;
    MouseSignal=MouseBufferGet();
	if(!MULTTASK){
		DeskMouseCtrl.MousePointer.X = GetTextX(MouseSignal.RelativeMovementX);
		DeskMouseCtrl.MousePointer.Y = GetTextY(MouseSignal.RelativeMovementY);
	}
	X_new=DeskMouseCtrl.MousePointer.X;
	Y_new=DeskMouseCtrl.MousePointer.Y;

	if(MouseSignal.LeftButton)DeskMouseCtrl.MouseLeftButton=BUTTON_PRESS;
    else DeskMouseCtrl.MouseLeftButton=BUTTON_RELEASE;
	
    if(MouseSignal.RightButton) DeskMouseCtrl.MouseRightButton=BUTTON_PRESS;
    else DeskMouseCtrl.MouseRightButton=BUTTON_RELEASE;
	
	if(X_new>X_org){
		Xmovement=X_new-X_org;
		if(((NewWindowArea.X+NewWindowArea.W+Xmovement)<=DeskWorkCtrl.WorkArea.W))NewWindowArea.X+=Xmovement;
        else NewWindowArea.X=DeskWorkCtrl.WorkArea.W-NewWindowArea.W;
		WindowMoveDirty=TRUE;
	}else if(X_org>X_new){
		//check
		Xmovement=X_org-X_new;
		if(Xmovement>NewWindowArea.X)NewWindowArea.X=0;
		else if(((NewWindowArea.X-Xmovement)>0))NewWindowArea.X-=Xmovement;
        else NewWindowArea.X=0;
		WindowMoveDirty=TRUE;
	}
	
	if(Y_new>Y_org){
		Ymovement=Y_new-Y_org;
		if(((NewWindowArea.Y+NewWindowArea.H+Ymovement)<=DeskWorkCtrl.WorkArea.H))NewWindowArea.Y+=Ymovement;
        else NewWindowArea.Y=DeskWorkCtrl.WorkArea.H-NewWindowArea.H;
		WindowMoveDirty=TRUE;
	}else if(Y_org>Y_new){
		//check
		Ymovement=Y_org-Y_new;
		if(Ymovement>NewWindowArea.Y)NewWindowArea.Y=0;
		else if((NewWindowArea.Y-Ymovement)>0)NewWindowArea.Y-=Ymovement;
        else NewWindowArea.Y=0;
		WindowMoveDirty=TRUE;
	}
    if(WindowMoveDirty==FALSE) return;
	
    pWindow->DisplayArea.X=NewWindowArea.X;
    pWindow->DisplayArea.Y=NewWindowArea.Y;
    //draw active window at new position
    DeskActiveWindowCtrl.ActiveWindowDirty=TRUE; // set TRUE for DeskActiveWindowMemory2OsdUpdate()
    DeskActiveWindowMemory2OsdUpdate(pWindow);
    //DeskActiveWindowMovingMouseCursorDraw(pWindow);
    //clear old active window image
    if(NewWindowArea.X<OriginalWindowArea.X){
        if(NewWindowArea.Y<OriginalWindowArea.Y){
            if((OriginalWindowArea.X-NewWindowArea.X)>OriginalWindowArea.W) DeskWorkWindow2OsdCopy(&OriginalWindowArea);
            else if((OriginalWindowArea.Y-NewWindowArea.Y)>OriginalWindowArea.H) DeskWorkWindow2OsdCopy(&OriginalWindowArea);
            else{
                CopyArea.X=NewWindowArea.X+pWindow->DisplayArea.W;
                CopyArea.Y=OriginalWindowArea.Y;
                CopyArea.W=OriginalWindowArea.X-NewWindowArea.X;
                CopyArea.H=pWindow->DisplayArea.H;
                DeskWorkWindow2OsdCopy(&CopyArea);
                CopyArea.X=OriginalWindowArea.X;
                CopyArea.Y=NewWindowArea.Y+pWindow->DisplayArea.H;
                CopyArea.W=NewWindowArea.X+pWindow->DisplayArea.W-OriginalWindowArea.X;
                CopyArea.H=OriginalWindowArea.Y-NewWindowArea.Y;
                DeskWorkWindow2OsdCopy(&CopyArea);
            }
        }
        else if(NewWindowArea.Y>OriginalWindowArea.Y){
            if((OriginalWindowArea.X-NewWindowArea.X)>OriginalWindowArea.W) DeskWorkWindow2OsdCopy(&OriginalWindowArea);
            else if((NewWindowArea.Y-OriginalWindowArea.Y)>OriginalWindowArea.H) DeskWorkWindow2OsdCopy(&OriginalWindowArea);
            else{
                CopyArea.X=NewWindowArea.X+pWindow->DisplayArea.W;
                CopyArea.Y=OriginalWindowArea.Y;
                CopyArea.W=OriginalWindowArea.X-NewWindowArea.X;
                CopyArea.H=pWindow->DisplayArea.H;
                DeskWorkWindow2OsdCopy(&CopyArea);
                CopyArea.X=OriginalWindowArea.X;
                CopyArea.Y=OriginalWindowArea.Y;
                CopyArea.W=pWindow->DisplayArea.W;
                CopyArea.H=NewWindowArea.Y-OriginalWindowArea.Y;
                DeskWorkWindow2OsdCopy(&CopyArea);    
            }
        }
        else{
            if((OriginalWindowArea.X-NewWindowArea.X)>OriginalWindowArea.W) DeskWorkWindow2OsdCopy(&OriginalWindowArea);
            else{
                CopyArea.X=NewWindowArea.X+pWindow->DisplayArea.W;
                CopyArea.Y=OriginalWindowArea.Y;
                CopyArea.W=OriginalWindowArea.X-NewWindowArea.X;
                CopyArea.H=pWindow->DisplayArea.H;
                DeskWorkWindow2OsdCopy(&CopyArea);
            }
        }
    }
    else if(NewWindowArea.X>OriginalWindowArea.X){
        if(NewWindowArea.Y<OriginalWindowArea.Y){
            if((NewWindowArea.X-OriginalWindowArea.X)>OriginalWindowArea.W) DeskWorkWindow2OsdCopy(&OriginalWindowArea);
            else if((OriginalWindowArea.Y-NewWindowArea.Y)>OriginalWindowArea.H) DeskWorkWindow2OsdCopy(&OriginalWindowArea);
            else{
                CopyArea.X=OriginalWindowArea.X;
                CopyArea.Y=OriginalWindowArea.Y;
                CopyArea.W=NewWindowArea.X-OriginalWindowArea.X;
                CopyArea.H=pWindow->DisplayArea.H;
                DeskWorkWindow2OsdCopy(&CopyArea);
                CopyArea.X=NewWindowArea.X;
                CopyArea.Y=NewWindowArea.Y+pWindow->DisplayArea.H;
                CopyArea.W=OriginalWindowArea.X+pWindow->DisplayArea.W-NewWindowArea.X;
                CopyArea.H=OriginalWindowArea.Y-NewWindowArea.Y;
                DeskWorkWindow2OsdCopy(&CopyArea);
            }
        }
        else if(NewWindowArea.Y>OriginalWindowArea.Y){
            if((NewWindowArea.X-OriginalWindowArea.X)>OriginalWindowArea.W) DeskWorkWindow2OsdCopy(&OriginalWindowArea);
            else if((NewWindowArea.Y-OriginalWindowArea.Y)>OriginalWindowArea.H) DeskWorkWindow2OsdCopy(&OriginalWindowArea);
            else{
                CopyArea.X=OriginalWindowArea.X;
                CopyArea.Y=OriginalWindowArea.Y;
                CopyArea.W=NewWindowArea.X-OriginalWindowArea.X;
                CopyArea.H=pWindow->DisplayArea.H;
                DeskWorkWindow2OsdCopy(&CopyArea);    
                CopyArea.X=NewWindowArea.X;
                CopyArea.Y=OriginalWindowArea.Y;
                CopyArea.W=OriginalWindowArea.X+pWindow->DisplayArea.W-NewWindowArea.X;
                CopyArea.H=NewWindowArea.Y-OriginalWindowArea.Y;
                DeskWorkWindow2OsdCopy(&CopyArea);
            }
        }
        else{
            if((NewWindowArea.X-OriginalWindowArea.X)>OriginalWindowArea.W) DeskWorkWindow2OsdCopy(&OriginalWindowArea);
            else{
                CopyArea.X=OriginalWindowArea.X;
                CopyArea.Y=OriginalWindowArea.Y;
                CopyArea.W=NewWindowArea.X-OriginalWindowArea.X;
                CopyArea.H=pWindow->DisplayArea.H;
                DeskWorkWindow2OsdCopy(&CopyArea);
            }
        }
    }
    else{
        if(NewWindowArea.Y<OriginalWindowArea.Y){
            if((OriginalWindowArea.Y-NewWindowArea.Y)>OriginalWindowArea.H) DeskWorkWindow2OsdCopy(&OriginalWindowArea);
            else{
                CopyArea.X=OriginalWindowArea.X;
                CopyArea.Y=NewWindowArea.Y+pWindow->DisplayArea.H;
                CopyArea.W=pWindow->DisplayArea.W;
                CopyArea.H=OriginalWindowArea.Y-NewWindowArea.Y;
                DeskWorkWindow2OsdCopy(&CopyArea);
            }
        }
        else if(NewWindowArea.Y>OriginalWindowArea.Y){
            if((NewWindowArea.Y-OriginalWindowArea.Y)>OriginalWindowArea.H) DeskWorkWindow2OsdCopy(&OriginalWindowArea);
            else{
                CopyArea.X=OriginalWindowArea.X;
                CopyArea.Y=OriginalWindowArea.Y;
                CopyArea.W=pWindow->DisplayArea.W;
                CopyArea.H=NewWindowArea.Y-OriginalWindowArea.Y;
                DeskWorkWindow2OsdCopy(&CopyArea);
            }
        }
        else{
            //no move
        }
    }
}

VOID DeskActiveWindowMoveSvc3(WINDOW *pWindow){
    EFI_SIMPLE_POINTER_STATE MouseSignal;
    UINT16 Xmovement,Ymovement;
    UINT32 i,j;
    GRAPHIC_AREA CopyArea;
    GRAPHIC_AREA WindowMovingArea;
    GRAPHIC_POSITION WindowPreviousPosition;
    UINT8 WindowMoveDirty;
    
    if(MouseBufferCheck()==BUFFER_EMPTY) return;
    WindowMovingArea.X=pWindow->DisplayArea.X;
    WindowMovingArea.Y=pWindow->DisplayArea.Y;
    WindowMovingArea.H=pWindow->DisplayArea.H;
    WindowMovingArea.W=pWindow->DisplayArea.W;
    WindowPreviousPosition.X=pWindow->DisplayArea.X;
    WindowPreviousPosition.Y=pWindow->DisplayArea.Y;
	
	MouseSignal=MouseBufferGet();

	if(MouseSignal.LeftButton)DeskMouseCtrl.MouseLeftButton=BUTTON_PRESS;
    else DeskMouseCtrl.MouseLeftButton=BUTTON_RELEASE;
	
    if(MouseSignal.RightButton) DeskMouseCtrl.MouseRightButton=BUTTON_PRESS;
    else DeskMouseCtrl.MouseRightButton=BUTTON_RELEASE;
	
	//GDB : This function need to debuger strictly.
    
	Xmovement=((MouseSignal.RelativeMovementX)*25/((INT32) SPP->Mode->ResolutionX));    
    Ymovement=((MouseSignal.RelativeMovementY)*25/((INT32) SPP->Mode->ResolutionY));
	
	if(Xmovement!=0){
		if(((WindowMovingArea.X+WindowMovingArea.W+Xmovement)<=DeskWorkCtrl.WorkArea.W))WindowMovingArea.X+=Xmovement;
        else WindowMovingArea.X=DeskWorkCtrl.WorkArea.W-WindowMovingArea.W;
		WindowMoveDirty=TRUE;
	}
	if(Ymovement!=0){
		if(((WindowMovingArea.Y+WindowMovingArea.H+Ymovement)<=DeskWorkCtrl.WorkArea.H))WindowMovingArea.Y+=Ymovement;
        else WindowMovingArea.Y=DeskWorkCtrl.WorkArea.H-WindowMovingArea.H;
		WindowMoveDirty=TRUE;
	}
    if(WindowMoveDirty==FALSE) return;
    pWindow->DisplayArea.X=WindowMovingArea.X;
    pWindow->DisplayArea.Y=WindowMovingArea.Y;
    //draw active window at new position
    DeskActiveWindowCtrl.ActiveWindowDirty=TRUE; // set TRUE for DeskActiveWindowMemory2OsdUpdate()
    DeskActiveWindowMemory2OsdUpdate(pWindow);
    //DeskActiveWindowMovingMouseCursorDraw(pWindow);
    //clear old active window image
    if(WindowMovingArea.X<WindowPreviousPosition.X){
        if(WindowMovingArea.Y<WindowPreviousPosition.Y){
            // copy left area
            CopyArea.X=WindowMovingArea.X+pWindow->DisplayArea.W;
            CopyArea.Y=WindowPreviousPosition.Y;
            
            i=WindowPreviousPosition.X+pWindow->DisplayArea.W-1;
            if(i>(DeskWorkCtrl.WorkArea.W-1)) i=DeskWorkCtrl.WorkArea.W-1;
            CopyArea.W=i-CopyArea.X+1;
            
            i=CopyArea.Y+pWindow->DisplayArea.H-1;
            if(i>=DeskWorkCtrl.WorkArea.H) i=DeskWorkCtrl.WorkArea.H-1;
            CopyArea.H=i-CopyArea.Y+1;
            
            DeskWorkWindow2OsdCopy(&CopyArea);
            
            //copy bottom area
            j=CopyArea.X;
            CopyArea.X=WindowPreviousPosition.X;
            CopyArea.Y=WindowMovingArea.Y+pWindow->DisplayArea.H;
            CopyArea.W=j-CopyArea.X;
            
            i=WindowPreviousPosition.Y+pWindow->DisplayArea.H-1;
            if(i>(DeskWorkCtrl.WorkArea.H-1)) i=DeskWorkCtrl.WorkArea.H-1;
            CopyArea.H=i-CopyArea.Y+1;
            
            DeskWorkWindow2OsdCopy(&CopyArea);
        }
        else if(WindowMovingArea.Y>WindowPreviousPosition.Y){
            CopyArea.X=WindowMovingArea.X+pWindow->DisplayArea.W;
            CopyArea.Y=WindowPreviousPosition.Y;
            
            i=WindowPreviousPosition.X+pWindow->DisplayArea.W-1;
            if(i>(DeskWorkCtrl.WorkArea.W-1)) i=DeskWorkCtrl.WorkArea.W-1;
            CopyArea.W=i-CopyArea.X+1;

            
            i=CopyArea.Y+pWindow->DisplayArea.H-1;
            if(i>=DeskWorkCtrl.WorkArea.H) i=DeskWorkCtrl.WorkArea.H-1;
            CopyArea.H=i-CopyArea.Y+1;
            
            DeskWorkWindow2OsdCopy(&CopyArea);
            
            CopyArea.X=WindowPreviousPosition.X;
            CopyArea.Y=WindowPreviousPosition.Y;
            i=CopyArea.X+pWindow->DisplayArea.W-1;
            if(i>=DeskWorkCtrl.WorkArea.W) i=DeskWorkCtrl.WorkArea.W-1;
            CopyArea.W=i-CopyArea.X+1;
            CopyArea.H=WindowMovingArea.Y-WindowPreviousPosition.Y;
            
            DeskWorkWindow2OsdCopy(&CopyArea);    
        }
        else{
            CopyArea.X=WindowMovingArea.X+pWindow->DisplayArea.W;
            CopyArea.Y=WindowPreviousPosition.Y;
            
            i=WindowPreviousPosition.X+pWindow->DisplayArea.W-1;
            if(i>(DeskWorkCtrl.WorkArea.W-1)) i=DeskWorkCtrl.WorkArea.W-1;
            CopyArea.W=i-CopyArea.X+1;
            
            i=CopyArea.Y+pWindow->DisplayArea.H-1;
            if(i>=DeskWorkCtrl.WorkArea.H) i=DeskWorkCtrl.WorkArea.H-1;
            CopyArea.H=i-CopyArea.Y+1;
            
            DeskWorkWindow2OsdCopy(&CopyArea);
        }
    }
    else if(WindowMovingArea.X>WindowPreviousPosition.X){
        if(WindowMovingArea.Y<WindowPreviousPosition.Y){
            // copy left area
            CopyArea.X=WindowPreviousPosition.X;
            CopyArea.Y=WindowPreviousPosition.Y;
            CopyArea.W=WindowMovingArea.X-WindowPreviousPosition.X;
            
            i=CopyArea.Y+pWindow->DisplayArea.H-1;
            if(i>=DeskWorkCtrl.WorkArea.H) i=DeskWorkCtrl.WorkArea.H-1;
            CopyArea.H=i-CopyArea.Y+1;
            
            DeskWorkWindow2OsdCopy(&CopyArea);
            //copy bottom area
            CopyArea.X=WindowMovingArea.X;
            CopyArea.Y=WindowMovingArea.Y+pWindow->DisplayArea.H;
            
            i=WindowPreviousPosition.X+pWindow->DisplayArea.W-1;
            if(i>=DeskWorkCtrl.WorkArea.W) i=DeskWorkCtrl.WorkArea.W-1;
            CopyArea.W=i-CopyArea.X+1;
            
            i=WindowPreviousPosition.Y+pWindow->DisplayArea.H-1;
            if(i>=DeskWorkCtrl.WorkArea.H) i=DeskWorkCtrl.WorkArea.H-1;
            CopyArea.H=i-CopyArea.Y+1;

            DeskWorkWindow2OsdCopy(&CopyArea);
        }
        else if(WindowMovingArea.Y>WindowPreviousPosition.Y){
            // copy left area
            CopyArea.X=WindowPreviousPosition.X;
            CopyArea.Y=WindowPreviousPosition.Y;

            CopyArea.W=WindowMovingArea.X-WindowPreviousPosition.X;
            
            i=CopyArea.Y+pWindow->DisplayArea.H-1;
            if(i>=DeskWorkCtrl.WorkArea.H) i=DeskWorkCtrl.WorkArea.H-1;
            CopyArea.H=i-CopyArea.Y+1;
            
            DeskWorkWindow2OsdCopy(&CopyArea);    
            //copy upper area
            CopyArea.X=WindowMovingArea.X;
            CopyArea.Y=WindowPreviousPosition.Y;
            
            i=WindowPreviousPosition.X+pWindow->DisplayArea.W-1;
            if(i>=DeskWorkCtrl.WorkArea.H) i=DeskWorkCtrl.WorkArea.W-1;
            CopyArea.W=i-CopyArea.X+1;

            CopyArea.H=WindowMovingArea.Y-WindowPreviousPosition.Y;
            
            DeskWorkWindow2OsdCopy(&CopyArea);
            
        }
        else{
            // copy left area
            CopyArea.X=WindowPreviousPosition.X;
            CopyArea.Y=WindowPreviousPosition.Y;

            CopyArea.W=WindowMovingArea.X-WindowPreviousPosition.X;
            
            i=CopyArea.Y+pWindow->DisplayArea.H-1;
            if(i>=DeskWorkCtrl.WorkArea.H) i=DeskWorkCtrl.WorkArea.H-1;
            CopyArea.H=i-CopyArea.Y+1;
            
            DeskWorkWindow2OsdCopy(&CopyArea);
        }
    }
    else{
        if(WindowMovingArea.Y<WindowPreviousPosition.Y){
            CopyArea.X=WindowPreviousPosition.X;
            CopyArea.Y=WindowMovingArea.Y+pWindow->DisplayArea.H;
            
            i=WindowPreviousPosition.X+pWindow->DisplayArea.W-1;
            if(i>(DeskWorkCtrl.WorkArea.W-1)) i=DeskWorkCtrl.WorkArea.W-1;
            CopyArea.W=i-CopyArea.X+1;


            i=WindowPreviousPosition.Y+pWindow->DisplayArea.H-1;
            if(i>(DeskWorkCtrl.WorkArea.H-1)) i=DeskWorkCtrl.WorkArea.H-1;
            CopyArea.H=i-CopyArea.Y+1;
            
            DeskWorkWindow2OsdCopy(&CopyArea);
        }
        else if(WindowMovingArea.Y>WindowPreviousPosition.Y){
            CopyArea.X=WindowPreviousPosition.X;
            CopyArea.Y=WindowPreviousPosition.Y;
            
            i=WindowPreviousPosition.X+pWindow->DisplayArea.W-1;
            if(i>(DeskWorkCtrl.WorkArea.W-1)) i=DeskWorkCtrl.WorkArea.W-1;
            CopyArea.W=i-CopyArea.X+1;

            
            CopyArea.H=WindowMovingArea.Y-WindowPreviousPosition.Y;
            
            DeskWorkWindow2OsdCopy(&CopyArea);
        }
        else{
            //no move
        }
    }
}

VOID DeskActiveWindowMoveSvc2(WINDOW *pWindow){
    /*GDB
	UN_UL MouseSignal;
    UINT8  Xdir,Ydir;
    UINT16 Xmovement,Ymovement;
    UINT32 i,j;
    GRAPHIC_AREA CopyArea;
    GRAPHIC_AREA WindowMovingArea;
    GRAPHIC_POSITION WindowPreviousPosition;
    UINT8 WindowMoveDirty;
    
    if(MouseBufferCheck()==BUFFER_EMPTY) return;
    WindowMovingArea.X=pWindow->DisplayArea.X;
    WindowMovingArea.Y=pWindow->DisplayArea.Y;
    WindowMovingArea.H=pWindow->DisplayArea.H;
    WindowMovingArea.W=pWindow->DisplayArea.W;
    WindowPreviousPosition.X=pWindow->DisplayArea.X;
    WindowPreviousPosition.Y=pWindow->DisplayArea.Y;
	
    MouseSignal.ul=MouseBufferGet();
    if(MouseSignal.uc[0]==0xfa) return;    
    if(MouseSignal.uc[0]&MOUSE_STATUS_LEFTBUTTON) DeskMouseCtrl.MouseLeftButton=BUTTON_PRESS;
    else DeskMouseCtrl.MouseLeftButton=BUTTON_RELEASE;
    if(MouseSignal.uc[0]&MOUSE_STATUS_RIGHTBUTTON) DeskMouseCtrl.MouseRightButton=BUTTON_PRESS;
    else DeskMouseCtrl.MouseRightButton=BUTTON_RELEASE;
    if(MouseSignal.uc[0]&MOUSE_STATUS_MIDDLEBUTTON) DeskMouseCtrl.MouseMiddleButton=BUTTON_PRESS;
    else DeskMouseCtrl.MouseMiddleButton=BUTTON_RELEASE;
    if(MouseSignal.uc[0]&MOUSE_STATUS_XSIGN){
        Xdir=MOUSE_DIRECTION_LEFT;
        if(MouseSignal.uc[0]&MOUSE_STATUS_XOVERFLOW) Xmovement=0x100;
        else Xmovement=0x100-MouseSignal.uc[1];
    }
    else{
        Xdir=MOUSE_DIRECTION_RIGHT;
        if(MouseSignal.uc[0]&MOUSE_STATUS_XOVERFLOW) Xmovement=0xff;
        else Xmovement=MouseSignal.uc[1];
    }
    if(MouseSignal.uc[0]&MOUSE_STATUS_YSIGN){
        Ydir=MOUSE_DIRECTION_DOWN;
        if(MouseSignal.uc[0]&MOUSE_STATUS_YOVERFLOW) Ymovement=0x100;
        else Ymovement=0x100-MouseSignal.uc[2];
    }
    else{
        Ydir=MOUSE_DIRECTION_UP;
        if(MouseSignal.uc[0]&MOUSE_STATUS_YOVERFLOW) Ymovement=0xff;
        else Ymovement=MouseSignal.uc[2];
    }
    //if((Xmovement<=1)&&(Ymovement<=1)) return; // movement too small
    if(Xdir==MOUSE_DIRECTION_LEFT){
        if(WindowMovingArea.X>=Xmovement) WindowMovingArea.X-=Xmovement;
        else WindowMovingArea.X=0;
    }
    else if(Xdir==MOUSE_DIRECTION_RIGHT){
        if((DeskWorkCtrl.WorkArea.W-(WindowMovingArea.X+WindowMovingArea.W))>=Xmovement)
            WindowMovingArea.X+=Xmovement;
        else WindowMovingArea.X=DeskWorkCtrl.WorkArea.W-WindowMovingArea.W;
    }
    if(Ydir==MOUSE_DIRECTION_UP){
        if(WindowMovingArea.Y>=Ymovement) WindowMovingArea.Y-=Ymovement;
        else WindowMovingArea.Y=0;
    }
    else if(Ydir==MOUSE_DIRECTION_DOWN){
        if((DeskWorkCtrl.WorkArea.H-(WindowMovingArea.Y+WindowMovingArea.H))>=Ymovement)
            WindowMovingArea.Y+=Ymovement;
        else WindowMovingArea.Y=DeskWorkCtrl.WorkArea.H-WindowMovingArea.H;
    }
	
    if(WindowMovingArea.X!=WindowPreviousPosition.X) WindowMoveDirty=TRUE;
    if(WindowMovingArea.Y!=WindowPreviousPosition.Y) WindowMoveDirty=TRUE;
    if(WindowMoveDirty==FALSE) return;
    pWindow->DisplayArea.X=WindowMovingArea.X;
    pWindow->DisplayArea.Y=WindowMovingArea.Y;
    //draw active window at new position
    DeskActiveWindowCtrl.ActiveWindowDirty=TRUE; // set TRUE for DeskActiveWindowMemory2OsdUpdate()
    DeskActiveWindowMemory2OsdUpdate(pWindow);
    //DeskActiveWindowMovingMouseCursorDraw(pWindow);
    //clear old active window image
    if(WindowMovingArea.X<WindowPreviousPosition.X){
        if(WindowMovingArea.Y<WindowPreviousPosition.Y){
            // copy left area
            CopyArea.X=WindowMovingArea.X+pWindow->DisplayArea.W;
            CopyArea.Y=WindowPreviousPosition.Y;
            
            i=WindowPreviousPosition.X+pWindow->DisplayArea.W-1;
            if(i>(DeskWorkCtrl.WorkArea.W-1)) i=DeskWorkCtrl.WorkArea.W-1;
            if(CopyArea.X<=(DeskWorkCtrl.WorkArea.W-1)) CopyArea.W=i-CopyArea.X+1;
            else CopyArea.W=0;
            
            i=CopyArea.Y+pWindow->DisplayArea.H-1;
            if(i>=DeskWorkCtrl.WorkArea.H) i=DeskWorkCtrl.WorkArea.H-1;
            CopyArea.H=i-CopyArea.Y+1;
            
            DeskWorkWindow2OsdCopy(&CopyArea);
            
            //copy bottom area
            j=CopyArea.X;
            CopyArea.X=WindowPreviousPosition.X;
            CopyArea.Y=WindowMovingArea.Y+pWindow->DisplayArea.H;
            CopyArea.W=j-CopyArea.X;
            
            i=WindowPreviousPosition.Y+pWindow->DisplayArea.H-1;
            if(i>(DeskWorkCtrl.WorkArea.H-1)) i=DeskWorkCtrl.WorkArea.H-1;
            if(CopyArea.Y<=(DeskWorkCtrl.WorkArea.H-1)) CopyArea.H=i-CopyArea.Y+1;
            else CopyArea.H=0; // no x direction area exist
            
            DeskWorkWindow2OsdCopy(&CopyArea);
        }
        else if(WindowMovingArea.Y>WindowPreviousPosition.Y){
            CopyArea.X=WindowMovingArea.X+pWindow->DisplayArea.W;
            CopyArea.Y=WindowPreviousPosition.Y;
            
            i=WindowPreviousPosition.X+pWindow->DisplayArea.W-1;
            if(i>(DeskWorkCtrl.WorkArea.W-1)) i=DeskWorkCtrl.WorkArea.W-1;
            if(CopyArea.X<=(DeskWorkCtrl.WorkArea.W-1)) CopyArea.W=i-CopyArea.X+1;
            else CopyArea.W=0;
            
            i=CopyArea.Y+pWindow->DisplayArea.H-1;
            if(i>=DeskWorkCtrl.WorkArea.H) i=DeskWorkCtrl.WorkArea.H-1;
            CopyArea.H=i-CopyArea.Y+1;
            
            DeskWorkWindow2OsdCopy(&CopyArea);
            
            CopyArea.X=WindowPreviousPosition.X;
            CopyArea.Y=WindowPreviousPosition.Y;
            i=CopyArea.X+pWindow->DisplayArea.W-1;
            if(i>=DeskWorkCtrl.WorkArea.W) i=DeskWorkCtrl.WorkArea.W-1;
            CopyArea.W=i-CopyArea.X+1;
            CopyArea.H=WindowMovingArea.Y-WindowPreviousPosition.Y;
            
            DeskWorkWindow2OsdCopy(&CopyArea);    
        }
        else{
            CopyArea.X=WindowMovingArea.X+pWindow->DisplayArea.W;
            CopyArea.Y=WindowPreviousPosition.Y;
            
            i=WindowPreviousPosition.X+pWindow->DisplayArea.W-1;
            if(i>(DeskWorkCtrl.WorkArea.W-1)) i=DeskWorkCtrl.WorkArea.W-1;
            if(CopyArea.X<=(DeskWorkCtrl.WorkArea.W-1)) CopyArea.W=i-CopyArea.X+1;
            else CopyArea.W=0;
            
            i=CopyArea.Y+pWindow->DisplayArea.H-1;
            if(i>=DeskWorkCtrl.WorkArea.H) i=DeskWorkCtrl.WorkArea.H-1;
            CopyArea.H=i-CopyArea.Y+1;
            
            DeskWorkWindow2OsdCopy(&CopyArea);
        }
    }
    else if(WindowMovingArea.X>WindowPreviousPosition.X){
        if(WindowMovingArea.Y<WindowPreviousPosition.Y){
            // copy left area
            CopyArea.X=WindowPreviousPosition.X;
            CopyArea.Y=WindowPreviousPosition.Y;

            CopyArea.W=WindowMovingArea.X-WindowPreviousPosition.X;
            
            i=CopyArea.Y+pWindow->DisplayArea.H-1;
            if(i>=DeskWorkCtrl.WorkArea.H) i=DeskWorkCtrl.WorkArea.H-1;
            CopyArea.H=i-CopyArea.Y+1;
            
            DeskWorkWindow2OsdCopy(&CopyArea);
            //copy bottom area
            CopyArea.X=WindowMovingArea.X;
            CopyArea.Y=WindowMovingArea.Y+pWindow->DisplayArea.H;
            
            i=WindowPreviousPosition.X+pWindow->DisplayArea.W-1;
            if(i>=DeskWorkCtrl.WorkArea.W) i=DeskWorkCtrl.WorkArea.W-1;
            CopyArea.W=i-CopyArea.X+1;
            
            i=WindowPreviousPosition.Y+pWindow->DisplayArea.H-1;
            if(i>=DeskWorkCtrl.WorkArea.H) i=DeskWorkCtrl.WorkArea.H-1;
            CopyArea.H=i-CopyArea.Y+1;

            DeskWorkWindow2OsdCopy(&CopyArea);
        }
        else if(WindowMovingArea.Y>WindowPreviousPosition.Y){
            // copy left area
            CopyArea.X=WindowPreviousPosition.X;
            CopyArea.Y=WindowPreviousPosition.Y;

            CopyArea.W=WindowMovingArea.X-WindowPreviousPosition.X;
            
            i=CopyArea.Y+pWindow->DisplayArea.H-1;
            if(i>=DeskWorkCtrl.WorkArea.H) i=DeskWorkCtrl.WorkArea.H-1;
            CopyArea.H=i-CopyArea.Y+1;
            
            DeskWorkWindow2OsdCopy(&CopyArea);    
            //copy upper area
            CopyArea.X=WindowMovingArea.X;
            CopyArea.Y=WindowPreviousPosition.Y;
            
            i=WindowPreviousPosition.X+pWindow->DisplayArea.W-1;
            if(i>=DeskWorkCtrl.WorkArea.H) i=DeskWorkCtrl.WorkArea.W-1;
            CopyArea.W=i-CopyArea.X+1;

            CopyArea.H=WindowMovingArea.Y-WindowPreviousPosition.Y;
            
            DeskWorkWindow2OsdCopy(&CopyArea);
            
        }
        else{
            // copy left area
            CopyArea.X=WindowPreviousPosition.X;
            CopyArea.Y=WindowPreviousPosition.Y;

            CopyArea.W=WindowMovingArea.X-WindowPreviousPosition.X;
            
            i=CopyArea.Y+pWindow->DisplayArea.H-1;
            if(i>=DeskWorkCtrl.WorkArea.H) i=DeskWorkCtrl.WorkArea.H-1;
            CopyArea.H=i-CopyArea.Y+1;
            
            DeskWorkWindow2OsdCopy(&CopyArea);
        }
    }
    else{
        if(WindowMovingArea.Y<WindowPreviousPosition.Y){
            CopyArea.X=WindowPreviousPosition.X;
            CopyArea.Y=WindowMovingArea.Y+pWindow->DisplayArea.H;
            
            i=WindowPreviousPosition.X+pWindow->DisplayArea.W-1;
            if(i>(DeskWorkCtrl.WorkArea.W-1)) i=DeskWorkCtrl.WorkArea.W-1;
            if(CopyArea.X<=(DeskWorkCtrl.WorkArea.W-1)) CopyArea.W=i-CopyArea.X+1;
            else CopyArea.W=0;

            i=WindowPreviousPosition.Y+pWindow->DisplayArea.H-1;
            if(i>(DeskWorkCtrl.WorkArea.H-1)) i=DeskWorkCtrl.WorkArea.H-1;
            if(CopyArea.Y<=(DeskWorkCtrl.WorkArea.H-1)) CopyArea.H=i-CopyArea.Y+1;
            else CopyArea.H=0;
            
            DeskWorkWindow2OsdCopy(&CopyArea);
        }
        else if(WindowMovingArea.Y>WindowPreviousPosition.Y){
            CopyArea.X=WindowPreviousPosition.X;
            CopyArea.Y=WindowPreviousPosition.Y;
            
            i=WindowPreviousPosition.X+pWindow->DisplayArea.W-1;
            if(i>(DeskWorkCtrl.WorkArea.W-1)) i=DeskWorkCtrl.WorkArea.W-1;
            if(CopyArea.X<=(DeskWorkCtrl.WorkArea.W-1)) CopyArea.W=i-CopyArea.X+1;
            else CopyArea.W=0;
            
            CopyArea.H=WindowMovingArea.Y-WindowPreviousPosition.Y;
            
            DeskWorkWindow2OsdCopy(&CopyArea);
        }
        else{
            //no move
        }
    }
	GDB*/
}

VOID DeskActiveWindowAdjust(UINT8 CursorType,WINDOW *pWindow){
    UINT32 EdgeDifferenceXdir;
    UINT32 EdgeDifferenceYdir;
    GRAPHIC_AREA DeviceDisplayArea;
    GRAPHIC_AREA WindowDisplayArea;
    
    if(pWindow->SizeVariable==FALSE) return;
    DeviceDisplayArea.X=pWindow->DeviceDisplayArea.X;
    DeviceDisplayArea.Y=pWindow->DeviceDisplayArea.Y;
    DeviceDisplayArea.W=pWindow->DeviceDisplayArea.W;
    DeviceDisplayArea.H=pWindow->DeviceDisplayArea.H;
    WindowDisplayArea.X=pWindow->DisplayArea.X;
    WindowDisplayArea.Y=pWindow->DisplayArea.Y;
    WindowDisplayArea.W=pWindow->DisplayArea.W;
    WindowDisplayArea.H=pWindow->DisplayArea.H;
    switch(CursorType){
        case DESK_MOUSE_CURSOR_UP:
            if(DeskMouseCtrl.OriginalWindowEdge.Y<DeskMouseCtrl.NewWindowEdge.Y){ // get smaller  in vertical
                if(WindowDisplayArea.H==DESK_WINDOW_HEIGHT_MINIMUN);
                else if((WindowDisplayArea.Y+WindowDisplayArea.H)<DeskMouseCtrl.NewWindowEdge.Y); //illegal
                else{
                    EdgeDifferenceYdir=DeskMouseCtrl.NewWindowEdge.Y-DeskMouseCtrl.OriginalWindowEdge.Y;
                    if(WindowDisplayArea.H>=(EdgeDifferenceYdir+DESK_WINDOW_HEIGHT_MINIMUN)){
                        WindowDisplayArea.Y=WindowDisplayArea.Y+EdgeDifferenceYdir;
                        WindowDisplayArea.H=WindowDisplayArea.H-EdgeDifferenceYdir;
                    }
                    else{
                        WindowDisplayArea.Y=WindowDisplayArea.Y+(WindowDisplayArea.H-DESK_WINDOW_HEIGHT_MINIMUN);
                        WindowDisplayArea.H=DESK_WINDOW_HEIGHT_MINIMUN;
                    }  
                }  
            }
            else if(DeskMouseCtrl.OriginalWindowEdge.Y>DeskMouseCtrl.NewWindowEdge.Y){ // get larger in vertical
                EdgeDifferenceYdir=DeskMouseCtrl.OriginalWindowEdge.Y-DeskMouseCtrl.NewWindowEdge.Y;
                if((DeviceDisplayArea.H+EdgeDifferenceYdir)<=pWindow->DeviceArea.H){
                    WindowDisplayArea.Y=WindowDisplayArea.Y-EdgeDifferenceYdir;
                    WindowDisplayArea.H=WindowDisplayArea.H+EdgeDifferenceYdir;
                }
                else{
                    WindowDisplayArea.Y=WindowDisplayArea.Y-(pWindow->DeviceArea.H-DeviceDisplayArea.H);
                    WindowDisplayArea.H=WindowDisplayArea.H+(pWindow->DeviceArea.H-DeviceDisplayArea.H);
                } 
            }
            break;
        case DESK_MOUSE_CURSOR_DOWN:
            if(DeskMouseCtrl.OriginalWindowEdge.Y<DeskMouseCtrl.NewWindowEdge.Y){ // get larger in vertical
                EdgeDifferenceYdir=DeskMouseCtrl.NewWindowEdge.Y-DeskMouseCtrl.OriginalWindowEdge.Y;
                if((DeviceDisplayArea.H+EdgeDifferenceYdir)<=pWindow->DeviceArea.H){
                    WindowDisplayArea.H=WindowDisplayArea.H+EdgeDifferenceYdir;    
                }
                else{
                    WindowDisplayArea.H=pWindow->DeviceArea.H+WINDOW_HEADER_HEIGHT+WINDOW_EDGE_THINK*2;
                }
                if((WindowDisplayArea.Y+WindowDisplayArea.H)>DeskWorkCtrl.WorkArea.H){
                    WindowDisplayArea.H=DeskWorkCtrl.WorkArea.H-WindowDisplayArea.Y;
                }
            }
            else if(DeskMouseCtrl.OriginalWindowEdge.Y>DeskMouseCtrl.NewWindowEdge.Y){ // get smaller  in vertical
                if(WindowDisplayArea.H==DESK_WINDOW_HEIGHT_MINIMUN);
                else if(WindowDisplayArea.Y>DeskMouseCtrl.NewWindowEdge.Y); //illegal
                else{
                    EdgeDifferenceYdir=DeskMouseCtrl.OriginalWindowEdge.Y-DeskMouseCtrl.NewWindowEdge.Y;
                    if((WindowDisplayArea.H-EdgeDifferenceYdir)>=DESK_WINDOW_HEIGHT_MINIMUN)
                        WindowDisplayArea.H=WindowDisplayArea.H-EdgeDifferenceYdir;
                    else WindowDisplayArea.H=DESK_WINDOW_HEIGHT_MINIMUN;
                }
            }
            break;
        case DESK_MOUSE_CURSOR_LEFT:
            if(DeskMouseCtrl.OriginalWindowEdge.X<DeskMouseCtrl.NewWindowEdge.X){ // get smaller  in vertical
                if(WindowDisplayArea.W==DESK_WINDOW_WIDTH_MINIMUN);
                else if((WindowDisplayArea.X+WindowDisplayArea.W)<DeskMouseCtrl.NewWindowEdge.X); //illegal  
                else{
                    EdgeDifferenceXdir=DeskMouseCtrl.NewWindowEdge.X-DeskMouseCtrl.OriginalWindowEdge.X;
                    if(WindowDisplayArea.W>=(EdgeDifferenceXdir+DESK_WINDOW_WIDTH_MINIMUN)){
                        WindowDisplayArea.X=WindowDisplayArea.X+EdgeDifferenceXdir;
                        WindowDisplayArea.W=WindowDisplayArea.W-EdgeDifferenceXdir;
                    }
                    else{
                        WindowDisplayArea.X=WindowDisplayArea.X+(WindowDisplayArea.W-DESK_WINDOW_WIDTH_MINIMUN);
                        WindowDisplayArea.W=DESK_WINDOW_WIDTH_MINIMUN;
                    }
                }
            }
            else if(DeskMouseCtrl.OriginalWindowEdge.X>DeskMouseCtrl.NewWindowEdge.X){ // get larger in vertical 
                EdgeDifferenceXdir=DeskMouseCtrl.OriginalWindowEdge.X-DeskMouseCtrl.NewWindowEdge.X;
                if((DeviceDisplayArea.W+EdgeDifferenceXdir)<=pWindow->DeviceArea.W){
                    WindowDisplayArea.X=WindowDisplayArea.X-EdgeDifferenceXdir;
                    WindowDisplayArea.W=WindowDisplayArea.W+EdgeDifferenceXdir;
                }
                else{
                    WindowDisplayArea.X=WindowDisplayArea.X-(pWindow->DeviceArea.W-DeviceDisplayArea.W);
                    WindowDisplayArea.W=WindowDisplayArea.W+(pWindow->DeviceArea.W-DeviceDisplayArea.W);
                }
            }
            break;
        case DESK_MOUSE_CURSOR_RIGHT:
            if(DeskMouseCtrl.OriginalWindowEdge.X<DeskMouseCtrl.NewWindowEdge.X){ // get larger in vertical
                EdgeDifferenceXdir=DeskMouseCtrl.NewWindowEdge.X-DeskMouseCtrl.OriginalWindowEdge.X;
                if((DeviceDisplayArea.W+EdgeDifferenceXdir)<=pWindow->DeviceArea.W){
                    WindowDisplayArea.W=WindowDisplayArea.W+EdgeDifferenceXdir;
                }
                else{
                    WindowDisplayArea.W=pWindow->DeviceArea.W+WINDOW_EDGE_THINK*2;
                }
                if((WindowDisplayArea.X+WindowDisplayArea.W)>DeskWorkCtrl.WorkArea.W){
                    WindowDisplayArea.W=DeskWorkCtrl.WorkArea.W-WindowDisplayArea.X;
                }
            }
            else if(DeskMouseCtrl.OriginalWindowEdge.X>DeskMouseCtrl.NewWindowEdge.X){ // get smaller  in vertical
                if(WindowDisplayArea.W==DESK_WINDOW_WIDTH_MINIMUN);
                else if(WindowDisplayArea.X>DeskMouseCtrl.NewWindowEdge.X); //illegal
                else{
                    EdgeDifferenceXdir=DeskMouseCtrl.OriginalWindowEdge.X-DeskMouseCtrl.NewWindowEdge.X;
                    if((WindowDisplayArea.W-EdgeDifferenceXdir)>=DESK_WINDOW_WIDTH_MINIMUN)
                        WindowDisplayArea.W=WindowDisplayArea.W-EdgeDifferenceXdir;
                    else WindowDisplayArea.W=DESK_WINDOW_WIDTH_MINIMUN;
                }
            }
            break;
        case DESK_MOUSE_CURSOR_LEFTUP:
            //left part
            if(DeskMouseCtrl.OriginalWindowEdge.X<DeskMouseCtrl.NewWindowEdge.X){ // get smaller  in vertical
                if(WindowDisplayArea.W==DESK_WINDOW_WIDTH_MINIMUN);
                else if((WindowDisplayArea.X+WindowDisplayArea.W)<DeskMouseCtrl.NewWindowEdge.X); //illegal  
                else{
                    EdgeDifferenceXdir=DeskMouseCtrl.NewWindowEdge.X-DeskMouseCtrl.OriginalWindowEdge.X;
                    if(WindowDisplayArea.W>=(EdgeDifferenceXdir+DESK_WINDOW_WIDTH_MINIMUN)){
                        WindowDisplayArea.X=WindowDisplayArea.X+EdgeDifferenceXdir;
                        WindowDisplayArea.W=WindowDisplayArea.W-EdgeDifferenceXdir;
                    }
                    else{
                        WindowDisplayArea.X=WindowDisplayArea.X+(WindowDisplayArea.W-DESK_WINDOW_WIDTH_MINIMUN);
                        WindowDisplayArea.W=DESK_WINDOW_WIDTH_MINIMUN;
                    }
                }
            }
            else if(DeskMouseCtrl.OriginalWindowEdge.X>DeskMouseCtrl.NewWindowEdge.X){ // get larger in vertical 
                EdgeDifferenceXdir=DeskMouseCtrl.OriginalWindowEdge.X-DeskMouseCtrl.NewWindowEdge.X;
                if((DeviceDisplayArea.W+EdgeDifferenceXdir)<=pWindow->DeviceArea.W){
                    WindowDisplayArea.X=WindowDisplayArea.X-EdgeDifferenceXdir;
                    WindowDisplayArea.W=WindowDisplayArea.W+EdgeDifferenceXdir;
                }
                else{
                    WindowDisplayArea.X=WindowDisplayArea.X-(pWindow->DeviceArea.W-DeviceDisplayArea.W);
                    WindowDisplayArea.W=WindowDisplayArea.W+(pWindow->DeviceArea.W-DeviceDisplayArea.W);
                }
            }
            //up part
            if(DeskMouseCtrl.OriginalWindowEdge.Y<DeskMouseCtrl.NewWindowEdge.Y){ // get smaller  in vertical
                if(WindowDisplayArea.H==DESK_WINDOW_HEIGHT_MINIMUN);
                if((WindowDisplayArea.Y+WindowDisplayArea.H)<DeskMouseCtrl.NewWindowEdge.Y); //illegal
                else{
                    EdgeDifferenceYdir=DeskMouseCtrl.NewWindowEdge.Y-DeskMouseCtrl.OriginalWindowEdge.Y;
                    if(WindowDisplayArea.H>=(EdgeDifferenceYdir+DESK_WINDOW_HEIGHT_MINIMUN)){
                        WindowDisplayArea.Y=WindowDisplayArea.Y+EdgeDifferenceYdir;
                        WindowDisplayArea.H=WindowDisplayArea.H-EdgeDifferenceYdir;
                    }
                    else{
                        WindowDisplayArea.Y=WindowDisplayArea.Y+(WindowDisplayArea.H-DESK_WINDOW_HEIGHT_MINIMUN);
                        WindowDisplayArea.H=DESK_WINDOW_HEIGHT_MINIMUN;
                    }    
                }
            }
            else if(DeskMouseCtrl.OriginalWindowEdge.Y>DeskMouseCtrl.NewWindowEdge.Y){ // get larger in vertical
                EdgeDifferenceYdir=DeskMouseCtrl.OriginalWindowEdge.Y-DeskMouseCtrl.NewWindowEdge.Y;
                if((DeviceDisplayArea.H+EdgeDifferenceYdir)<=pWindow->DeviceArea.H){
                    WindowDisplayArea.Y=WindowDisplayArea.Y-EdgeDifferenceYdir;
                    WindowDisplayArea.H=WindowDisplayArea.H+EdgeDifferenceYdir;
                }
                else{
                    WindowDisplayArea.Y=WindowDisplayArea.Y-(pWindow->DeviceArea.H-DeviceDisplayArea.H);
                    WindowDisplayArea.H=WindowDisplayArea.H+(pWindow->DeviceArea.H-DeviceDisplayArea.H);
                } 
            }
            break;
        case DESK_MOUSE_CURSOR_LEFTDOWN:
            //left part
            if(DeskMouseCtrl.OriginalWindowEdge.X<DeskMouseCtrl.NewWindowEdge.X){ // get smaller  in vertical
                if(WindowDisplayArea.W==DESK_WINDOW_WIDTH_MINIMUN);
                else if((WindowDisplayArea.X+WindowDisplayArea.W)<DeskMouseCtrl.NewWindowEdge.X); //illegal  
                else{
                    EdgeDifferenceXdir=DeskMouseCtrl.NewWindowEdge.X-DeskMouseCtrl.OriginalWindowEdge.X;
                    if(WindowDisplayArea.W>=(EdgeDifferenceXdir+DESK_WINDOW_WIDTH_MINIMUN)){
                        WindowDisplayArea.X=WindowDisplayArea.X+EdgeDifferenceXdir;
                        WindowDisplayArea.W=WindowDisplayArea.W-EdgeDifferenceXdir;
                     }
                     else{
                        WindowDisplayArea.X=WindowDisplayArea.X+(WindowDisplayArea.W-DESK_WINDOW_WIDTH_MINIMUN);
                        WindowDisplayArea.W=DESK_WINDOW_WIDTH_MINIMUN;
                     }
                }
            }
            else if(DeskMouseCtrl.OriginalWindowEdge.X>DeskMouseCtrl.NewWindowEdge.X){ // get larger in vertical 
                EdgeDifferenceXdir=DeskMouseCtrl.OriginalWindowEdge.X-DeskMouseCtrl.NewWindowEdge.X;
                if((DeviceDisplayArea.W+EdgeDifferenceXdir)<=pWindow->DeviceArea.W){
                    WindowDisplayArea.X=WindowDisplayArea.X-EdgeDifferenceXdir;
                    WindowDisplayArea.W=WindowDisplayArea.W+EdgeDifferenceXdir;
                }
                else{
                    WindowDisplayArea.X=WindowDisplayArea.X-(pWindow->DeviceArea.W-DeviceDisplayArea.W);
                    WindowDisplayArea.W=WindowDisplayArea.W+(pWindow->DeviceArea.W-DeviceDisplayArea.W);
                }
            }
            //down part
            if(DeskMouseCtrl.OriginalWindowEdge.Y<DeskMouseCtrl.NewWindowEdge.Y){ // get larger in vertical
                EdgeDifferenceYdir=DeskMouseCtrl.NewWindowEdge.Y-DeskMouseCtrl.OriginalWindowEdge.Y;
                if((DeviceDisplayArea.H+EdgeDifferenceYdir)<=pWindow->DeviceArea.H){
                    WindowDisplayArea.H=WindowDisplayArea.H+EdgeDifferenceYdir;    
                }
                else{
                    WindowDisplayArea.H=pWindow->DeviceArea.H+WINDOW_HEADER_HEIGHT+WINDOW_EDGE_THINK*2;
                }
                if((WindowDisplayArea.Y+WindowDisplayArea.H)>DeskWorkCtrl.WorkArea.H){
                    WindowDisplayArea.H=DeskWorkCtrl.WorkArea.H-WindowDisplayArea.Y;
                }
            }
            else if(DeskMouseCtrl.OriginalWindowEdge.Y>DeskMouseCtrl.NewWindowEdge.Y){ // get smaller  in vertical
                if(WindowDisplayArea.H==DESK_WINDOW_HEIGHT_MINIMUN);
                else if(WindowDisplayArea.Y>DeskMouseCtrl.NewWindowEdge.Y); //illegal
                else{
                    EdgeDifferenceYdir=DeskMouseCtrl.OriginalWindowEdge.Y-DeskMouseCtrl.NewWindowEdge.Y;
                    if((WindowDisplayArea.H-EdgeDifferenceYdir)>=DESK_WINDOW_HEIGHT_MINIMUN)
                        WindowDisplayArea.H=WindowDisplayArea.H-EdgeDifferenceYdir;
                    else WindowDisplayArea.H=DESK_WINDOW_HEIGHT_MINIMUN;
                }
            }
            break;
        case DESK_MOUSE_CURSOR_RIGHTUP:
            
            //right part
            if(DeskMouseCtrl.OriginalWindowEdge.X<DeskMouseCtrl.NewWindowEdge.X){ // get larger in vertical
                EdgeDifferenceXdir=DeskMouseCtrl.NewWindowEdge.X-DeskMouseCtrl.OriginalWindowEdge.X;
                if((DeviceDisplayArea.W+EdgeDifferenceXdir)<=pWindow->DeviceArea.W){
                    WindowDisplayArea.W=WindowDisplayArea.W+EdgeDifferenceXdir;
                }
                else{
                    WindowDisplayArea.W=pWindow->DeviceArea.W+(WINDOW_EDGE_THINK+WINDOW_EDGE_THINK);
                }
                if((WindowDisplayArea.X+WindowDisplayArea.W)>DeskWorkCtrl.WorkArea.W){
                    WindowDisplayArea.W=DeskWorkCtrl.WorkArea.W-WindowDisplayArea.X;
                }
            }
            else if(DeskMouseCtrl.OriginalWindowEdge.X>DeskMouseCtrl.NewWindowEdge.X){ // get smaller  in vertical
                if(WindowDisplayArea.W==DESK_WINDOW_WIDTH_MINIMUN);
                else if(WindowDisplayArea.X>DeskMouseCtrl.NewWindowEdge.X); //illegal
                else{
                    EdgeDifferenceXdir=DeskMouseCtrl.OriginalWindowEdge.X-DeskMouseCtrl.NewWindowEdge.X;
                    if((WindowDisplayArea.W-EdgeDifferenceXdir)>=DESK_WINDOW_WIDTH_MINIMUN)
                        WindowDisplayArea.W=WindowDisplayArea.W-EdgeDifferenceXdir;
                    else WindowDisplayArea.W=DESK_WINDOW_WIDTH_MINIMUN;
                }
            }
            //up part
            if(DeskMouseCtrl.OriginalWindowEdge.Y<DeskMouseCtrl.NewWindowEdge.Y){ // get smaller  in vertical
                if(WindowDisplayArea.H==DESK_WINDOW_HEIGHT_MINIMUN);
                else if((WindowDisplayArea.Y+WindowDisplayArea.H)<DeskMouseCtrl.NewWindowEdge.Y); //illegal
                else{
                    EdgeDifferenceYdir=DeskMouseCtrl.NewWindowEdge.Y-DeskMouseCtrl.OriginalWindowEdge.Y;
                    if(WindowDisplayArea.H>=(EdgeDifferenceYdir+DESK_WINDOW_HEIGHT_MINIMUN)){
                        WindowDisplayArea.Y=WindowDisplayArea.Y+EdgeDifferenceYdir;
                        WindowDisplayArea.H=WindowDisplayArea.H-EdgeDifferenceYdir;
                    }
                    else{
                        WindowDisplayArea.Y=WindowDisplayArea.Y+(WindowDisplayArea.H-DESK_WINDOW_HEIGHT_MINIMUN);
                        WindowDisplayArea.H=DESK_WINDOW_HEIGHT_MINIMUN;
                    }
                }    
            }
            else if(DeskMouseCtrl.OriginalWindowEdge.Y>DeskMouseCtrl.NewWindowEdge.Y){ // get larger in vertical
                EdgeDifferenceYdir=DeskMouseCtrl.OriginalWindowEdge.Y-DeskMouseCtrl.NewWindowEdge.Y;
                if((DeviceDisplayArea.H+EdgeDifferenceYdir)<=pWindow->DeviceArea.H){
                    WindowDisplayArea.Y=WindowDisplayArea.Y-EdgeDifferenceYdir;
                    WindowDisplayArea.H=WindowDisplayArea.H+EdgeDifferenceYdir;
                }
                else{
                    WindowDisplayArea.Y=WindowDisplayArea.Y-(pWindow->DeviceArea.H-DeviceDisplayArea.H);
                    WindowDisplayArea.H=WindowDisplayArea.H+(pWindow->DeviceArea.H-DeviceDisplayArea.H);
                } 
            }
            break;
        case DESK_MOUSE_CURSOR_RIGHTDOWN:
            //right part
            if(DeskMouseCtrl.OriginalWindowEdge.X<DeskMouseCtrl.NewWindowEdge.X){ // get larger in vertical
                EdgeDifferenceXdir=DeskMouseCtrl.NewWindowEdge.X-DeskMouseCtrl.OriginalWindowEdge.X;
                if((DeviceDisplayArea.W+EdgeDifferenceXdir)<=pWindow->DeviceArea.W){
                    WindowDisplayArea.W=WindowDisplayArea.W+EdgeDifferenceXdir;
                }
                else{
                    WindowDisplayArea.W=pWindow->DeviceArea.W+(WINDOW_EDGE_THINK+WINDOW_EDGE_THINK);
                }
                if((WindowDisplayArea.X+WindowDisplayArea.W)>DeskWorkCtrl.WorkArea.W){
                    WindowDisplayArea.W=DeskWorkCtrl.WorkArea.W-WindowDisplayArea.X;
                }
            }
            else if(DeskMouseCtrl.OriginalWindowEdge.X>DeskMouseCtrl.NewWindowEdge.X){ // get smaller  in vertical
                if(WindowDisplayArea.W==DESK_WINDOW_WIDTH_MINIMUN);
                else if(WindowDisplayArea.X>DeskMouseCtrl.NewWindowEdge.X); //illegal
                else{
                    EdgeDifferenceXdir=DeskMouseCtrl.OriginalWindowEdge.X-DeskMouseCtrl.NewWindowEdge.X;
                    if((WindowDisplayArea.W-EdgeDifferenceXdir)>=DESK_WINDOW_WIDTH_MINIMUN)
                        WindowDisplayArea.W=WindowDisplayArea.W-EdgeDifferenceXdir;
                    else WindowDisplayArea.W=DESK_WINDOW_WIDTH_MINIMUN;
                }
            }
            //down part
            if(DeskMouseCtrl.OriginalWindowEdge.Y<DeskMouseCtrl.NewWindowEdge.Y){ // get larger in vertical
                EdgeDifferenceYdir=DeskMouseCtrl.NewWindowEdge.Y-DeskMouseCtrl.OriginalWindowEdge.Y;
                if((DeviceDisplayArea.H+EdgeDifferenceYdir)<=pWindow->DeviceArea.H){
                    WindowDisplayArea.H=WindowDisplayArea.H+EdgeDifferenceYdir;    
                }
                else{
                    WindowDisplayArea.H=pWindow->DeviceArea.H+WINDOW_HEADER_HEIGHT+WINDOW_EDGE_THINK*2;
                }
                if((WindowDisplayArea.Y+WindowDisplayArea.H)>DeskWorkCtrl.WorkArea.H){
                    WindowDisplayArea.H=DeskWorkCtrl.WorkArea.H-WindowDisplayArea.Y;
                }
            }
            else if(DeskMouseCtrl.OriginalWindowEdge.Y>DeskMouseCtrl.NewWindowEdge.Y){ // get smaller  in vertical
                if(WindowDisplayArea.H==DESK_WINDOW_HEIGHT_MINIMUN);
                else if(WindowDisplayArea.Y>DeskMouseCtrl.NewWindowEdge.Y); //illegal
                else{
                    EdgeDifferenceYdir=DeskMouseCtrl.OriginalWindowEdge.Y-DeskMouseCtrl.NewWindowEdge.Y;
                    if((WindowDisplayArea.H-EdgeDifferenceYdir)>=DESK_WINDOW_HEIGHT_MINIMUN)
                        WindowDisplayArea.H=WindowDisplayArea.H-EdgeDifferenceYdir;
                    else WindowDisplayArea.H=DESK_WINDOW_HEIGHT_MINIMUN;
                }
            }
            break;
        default:
            break;
    }
    pWindow->DisplayArea.X=WindowDisplayArea.X;
    pWindow->DisplayArea.Y=WindowDisplayArea.Y;
    pWindow->DisplayArea.W=WindowDisplayArea.W;
    pWindow->DisplayArea.H=WindowDisplayArea.H;
    WindowAreaAdjust(pWindow);
}
