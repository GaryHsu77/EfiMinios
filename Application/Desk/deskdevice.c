#include <includes.h>


// this function is use in mouse position check
BOOLEAN DeskDeviceAreaPositionCheck(WINDOW_DEVICE *pDevice,GRAPHIC_POSITION *pPosition){
    if(pDevice->Type==WINDOW_DEVICE_CAPTION){
        if(DesklibAreaPositionCheck(&((CAPTION *)pDevice->pDevice)->Area,pPosition)==TRUE) return TRUE;
        else return FALSE;
    }
    else if(pDevice->Type==WINDOW_DEVICE_BOARD){
        if(DesklibAreaPositionCheck(&((BOARD *)pDevice->pDevice)->Area,pPosition)==TRUE) return TRUE;
        else return FALSE;
    }
    else if(pDevice->Type==WINDOW_DEVICE_ICON){
        if(DesklibAreaPositionCheck(&((WINDOW_ICON *)pDevice->pDevice)->Area,pPosition)==TRUE) return TRUE;
        else return FALSE;
    }
    else if(pDevice->Type==WINDOW_DEVICE_EDGE){
        if(DesklibAreaPositionCheck(&((WINDOW_EDGE *)pDevice->pDevice)->Area,pPosition)==TRUE) return TRUE;
        else return FALSE;
    }
    else if(pDevice->Type==WINDOW_DEVICE_BUTTON){
        if(DesklibAreaPositionCheck(&((WINDOW_BUTTON *)pDevice->pDevice)->Area,pPosition)==TRUE) return TRUE;
        else return FALSE;
    }
    else if(pDevice->Type==WINDOW_DEVICE_STRINGBOX){
        if(DesklibAreaPositionCheck(&((WINDOW_STRINGBOX *)pDevice->pDevice)->Area,pPosition)==TRUE) return TRUE;
        else return FALSE;
    }
    else if(pDevice->Type==WINDOW_DEVICE_WINDOWBOX){
        if(DesklibAreaPositionCheck(&((WINDOW_WINDOWBOX *)pDevice->pDevice)->Area,pPosition)==TRUE) return TRUE;
        else return FALSE;
    }
    return FALSE;
}

BOOLEAN DeskDeviceDirtyCheck(WINDOW_DEVICE *pDevice){
    if(pDevice->Type==WINDOW_DEVICE_CAPTION){
        if(((CAPTION *)pDevice->pDevice)->Dirty==TRUE) return TRUE;
        else return FALSE;
    }
    else if(pDevice->Type==WINDOW_DEVICE_BOARD){
        if(((BOARD *)pDevice->pDevice)->Dirty==TRUE) return TRUE;
        else return FALSE;
    }
    else if(pDevice->Type==WINDOW_DEVICE_STRINGBOX){
        if(((WINDOW_STRINGBOX *)pDevice->pDevice)->Dirty==TRUE) return TRUE;
        else return FALSE;
    }
    else if(pDevice->Type==WINDOW_DEVICE_BUTTON){
        if(((WINDOW_BUTTON *)pDevice->pDevice)->Dirty==TRUE) return TRUE;
        else return FALSE;
    }
    return FALSE;
}

// caption
VOID DeskDeviceCaptionDraw(UINT8 DrawPlace,WINDOW *pWindow,WINDOW_TABLE *pTable,CAPTION *pCaption){
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pMemory,*pMemory2;
    UINT32 Height,Width;
    GRAPHIC_POSITION Position;
    MY_MUTEX mutex;
    
    mutex = OsEnterCritical();
    if(DrawPlace==DESK_DEVICE_DRAW_ACTIVEWINDOW){
        Position.X=pTable->Area.X+pCaption->Area.X;
        Position.Y=pTable->Area.Y+pCaption->Area.Y;
        if(pWindow->DeviceDisplayArea.W>=pCaption->Area.W) Width=pCaption->Area.W;
        else Width=pWindow->DeviceDisplayArea.W;
        if(pWindow->DeviceDisplayArea.H>=pCaption->Area.H) Height=pCaption->Area.H;
        else Height=pWindow->DeviceDisplayArea.H;
        pMemory=(EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)(DeskActiveWindowCtrl.pActiveWindowMemory+pWindow->DisplayArea.W*Position.Y+Position.X);
        pMemory2=pCaption->pCaptionMemory;
        while((Height!=0)&&(Width!=0)){
			PixelArrayCopy(pMemory2,pMemory,Width);
            pMemory=(EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)(pMemory+pWindow->DisplayArea.W);
            pMemory2=(EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)(pMemory2+pCaption->Area.W);
            Height--;
        }
        pCaption->Dirty=FALSE;
        pWindow->Dirty=TRUE;
    }
    else if(DrawPlace==DESK_DEVICE_DRAW_INACTIVEWINDOW){
        Position.X=pTable->Area.X+pCaption->Area.X;
        Position.Y=pTable->Area.Y+pCaption->Area.Y;
        if(pWindow->DeviceDisplayArea.W>=pCaption->Area.W) Width=pCaption->Area.W;
        else Width=pWindow->DeviceDisplayArea.W;
        if(pWindow->DeviceDisplayArea.H>=pCaption->Area.H) Height=pCaption->Area.H;
        else Height=pWindow->DeviceDisplayArea.H;
        pMemory=(EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)(DeskInactiveWindowCtrl.pInactiveWindowMemory+pWindow->DisplayArea.W*Position.Y+Position.X); 
        pMemory2=pCaption->pCaptionMemory;
        while((Height!=0)&&(Width!=0)){
			PixelArrayCopy(pMemory2,pMemory,Width);
            pMemory=(EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)(pMemory+pWindow->DisplayArea.W);
            pMemory2=(EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)(pMemory2+pCaption->Area.W);
            Height--;
        }
        pCaption->Dirty=FALSE;
        pWindow->Dirty=TRUE;
    }
    else if(DrawPlace==DESK_DEVICE_DRAW_OSD){
		UINT8 j = 0;
        Position.X=pWindow->DisplayArea.X+pTable->Area.X+pCaption->Area.X;
        Position.Y=pWindow->DisplayArea.Y+pTable->Area.Y+pCaption->Area.Y;
        if(pWindow->DeviceDisplayArea.W>=pCaption->Area.W) Width=pCaption->Area.W;
        else Width=pWindow->DeviceDisplayArea.W;
        if(pWindow->DeviceDisplayArea.H>=pCaption->Area.H) Height=pCaption->Area.H;
        else Height=pWindow->DeviceDisplayArea.H;
        pMemory=(EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)(OsdCtrl.pPixMemory+DeskWorkCtrl.WorkArea.W*Position.Y+Position.X);            
        pMemory2=pCaption->pCaptionMemory;
        while((Height!=0)&&(Width!=0)){
			PixelArrayCopy(pMemory2,pMemory,Width);
			PixelArrayDraw(pMemory, Position.X, Position.Y+j, Width, 1);
            pMemory=(EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)(pMemory+DeskCtrl.DeskArea.W);
            pMemory2=(EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)(pMemory2+pCaption->Area.W);
            Height--;j++;
        }
        pCaption->Dirty=FALSE;
    }
    OsExitCritical(mutex);
}

// board
VOID DeskDeviceBoardDraw(UINT8 DrawPlace,WINDOW *pWindow,WINDOW_TABLE *pTable,BOARD *pBoard){
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pMemory,*pMemory2;
    UINT32 Height,Width;
    GRAPHIC_POSITION Position;
    MY_MUTEX mutex;
    
    mutex = OsEnterCritical();
    if(DrawPlace==DESK_DEVICE_DRAW_ACTIVEWINDOW){
        Position.X=pTable->Area.X+pBoard->Area.X;
        Position.Y=pTable->Area.Y+pBoard->Area.Y;
        pMemory=DeskActiveWindowCtrl.pActiveWindowMemory+pWindow->DisplayArea.W*Position.Y+Position.X;
        pMemory2=pBoard->pBoardMemory;
        Height=pBoard->Area.H;
        Width=pBoard->Area.W;
        while((Height!=0)&&(Width!=0)){
			PixelArrayCopy(pMemory2,pMemory,Width);
            pMemory=(EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)(pMemory+pWindow->DisplayArea.W);
            pMemory2=(EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)(pMemory2+pBoard->Area.W);
            Height--;
        }
        pBoard->Dirty=FALSE;
        pWindow->Dirty=TRUE;
    }
    else if(DrawPlace==DESK_DEVICE_DRAW_INACTIVEWINDOW){
        Position.X=pTable->Area.X+pBoard->Area.X;
        Position.Y=pTable->Area.Y+pBoard->Area.Y;
        pMemory=(EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)(DeskInactiveWindowCtrl.pInactiveWindowMemory+pWindow->DisplayArea.W*Position.Y+Position.X);
        pMemory2=pBoard->pBoardMemory;
        Height=pBoard->Area.H;
        Width=pBoard->Area.W;
        while((Height!=0)&&(Width!=0)){
			PixelArrayCopy(pMemory2,pMemory,Width);
            pMemory=(EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)(pMemory+pWindow->DisplayArea.W);
            pMemory2=(EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)(pMemory2+pBoard->Area.W);
            Height--;
        }
        pBoard->Dirty=FALSE;
        pWindow->Dirty=TRUE;
    }
    else if(DrawPlace==DESK_DEVICE_DRAW_OSD){
		UINT8 j = 0;
        Position.X=pWindow->DisplayArea.X+pTable->Area.X+pBoard->Area.X;
        Position.Y=pWindow->DisplayArea.Y+pTable->Area.Y+pBoard->Area.Y;
        pMemory2=(EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)(OsdCtrl.pPixMemory+DeskWorkCtrl.WorkArea.W*Position.Y+Position.X);    
        pMemory=pBoard->pBoardMemory;
        Height=pBoard->Area.H;
        Width=pBoard->Area.W;
        while((Height!=0)&&(Width!=0)){
			PixelArrayCopy(pMemory,pMemory2,Width);
			PixelArrayDraw(pMemory2, Position.X, Position.Y+j, Width, 1);
            pMemory=(EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)(pMemory+pBoard->Area.W);
            pMemory2=(EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)(pMemory2+DeskCtrl.DeskArea.W);
            Height--;j++;
        }
        pBoard->Dirty=FALSE;
    }
    OsExitCritical(mutex);
}

// button
VOID DeskDeviceButtonDraw(UINT8 DrawPlace,WINDOW *pWindow,WINDOW_TABLE *pTable,WINDOW_BUTTON *pButton)
{
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pPixArr;
	UINT8 *pMemory;
    UINT32 Height,Width;
    GRAPHIC_POSITION Position;
    
    if((pButton->Area.W==0)||(pButton->Area.H==0)) return;
    if(DrawPlace==DESK_DEVICE_DRAW_ACTIVEWINDOW){
        //draw background
        Position.X=pTable->Area.X+pButton->Area.X;
        Position.Y=pTable->Area.Y+pButton->Area.Y;
        Height=pButton->Area.H;
        Width=pButton->Area.W;
        pPixArr=DeskActiveWindowCtrl.pActiveWindowMemory
                +pWindow->Outline.OuterArea.W*Position.Y+Position.X;
        while(Height!=0){
            if(pButton->Active==TRUE){
                if(pButton->Status==WINDOW_BUTTON_RELEASE) PixelArray256Set(pPixArr,GfxPaletteClut[pButton->ReleaseGfx.BgColor],Width);
				else PixelArray256Set(pPixArr,GfxPaletteClut[pButton->PressGfx.BgColor],Width);
            }
            else PixelArray256Set(pPixArr,GfxPaletteClut[pButton->InactiveGfx.BgColor],Width);
            pPixArr=pPixArr+pWindow->Outline.OuterArea.W;
            Height--;
        }
        //draw icon content
        Width=pButton->Area.W;
        Width=Width/8;
        pMemory=pButton->pName;
        Position.X=pTable->Area.X+pButton->Area.X+1;
        Position.Y=pTable->Area.Y+pButton->Area.Y+1;
        if(pButton->pBitmap!=(UINT8 *)NULL){                    
            ///* GDB : Windows general title button.
			if(pButton->Active==TRUE){
                if(pButton->Status==WINDOW_BUTTON_RELEASE)
                    DeskDeviceActiveWindowMemoryCharDraw(pWindow,pButton->pBitmap,&Position,&pButton->ReleaseGfx);
                else DeskDeviceActiveWindowMemoryCharDraw(pWindow,pButton->pBitmap,&Position,&pButton->PressGfx);
            }
            else DeskDeviceActiveWindowMemoryCharDraw(pWindow,pButton->pBitmap,&Position,&pButton->InactiveGfx);
			//*/
		}
        else if(pMemory!=(UINT8 *)NULL){
            while((Width!=0)&&(*pMemory!=0)){      
                if(pButton->Active==TRUE){
                   if(pButton->Status==WINDOW_BUTTON_RELEASE)
                        DeskDeviceActiveWindowMemoryCharDraw(pWindow,FontBitmapGet(FONT8X8,*pMemory),&Position,&pButton->ReleaseGfx);
                    else DeskDeviceActiveWindowMemoryCharDraw(pWindow,FontBitmapGet(FONT8X8,*pMemory),&Position,&pButton->PressGfx);
                }
                else DeskDeviceActiveWindowMemoryCharDraw(pWindow,FontBitmapGet(FONT8X8,*pMemory),&Position,&pButton->InactiveGfx);
                pMemory++;
                Width--;
                Position.X=Position.X+STRING_SIZE;
            }
        }
        //draw outline
        if(pButton->Outline==TRUE){
            Position.X=pTable->Area.X+pButton->Area.X;
            Position.Y=pTable->Area.Y+pButton->Area.Y;
            Height=pButton->Area.H;
            Width=pButton->Area.W;
            pPixArr=DeskActiveWindowCtrl.pActiveWindowMemory
                    +pWindow->Outline.OuterArea.W*Position.Y
                    +Position.X;
			PixelArray256Set(pPixArr,GfxPaletteClut[pButton->OutlineColor],Width);
            pPixArr=DeskActiveWindowCtrl.pActiveWindowMemory
                    +pWindow->Outline.OuterArea.W*(Position.Y+Height-1)
                    +Position.X;
			PixelArray256Set(pPixArr,GfxPaletteClut[pButton->OutlineColor],Width);
            pPixArr=DeskActiveWindowCtrl.pActiveWindowMemory
                    +pWindow->Outline.OuterArea.W*Position.Y
                    +Position.X;
            while(Height!=0){
				PixelArray256Set(pPixArr,GfxPaletteClut[pButton->OutlineColor],1);
				PixelArray256Set(pPixArr+Width-1,GfxPaletteClut[pButton->OutlineColor],1);
                pPixArr=pPixArr+pWindow->Outline.OuterArea.W;
                Height--;
            }
        }
        pButton->Dirty=FALSE;
        pWindow->Dirty=TRUE;
    }
    else if(DrawPlace==DESK_DEVICE_DRAW_INACTIVEWINDOW){
        Position.X=pTable->Area.X+pButton->Area.X;
        Position.Y=pTable->Area.Y+pButton->Area.Y;
        Height=pButton->Area.H;
        Width=pButton->Area.W;
        pPixArr=DeskInactiveWindowCtrl.pInactiveWindowMemory
                +pWindow->Outline.OuterArea.W*Position.Y+Position.X;
        while(Height!=0){
            if(pButton->Active==TRUE){
                if(pButton->Status==WINDOW_BUTTON_RELEASE)
					PixelArray256Set(pPixArr,GfxPaletteClut[pButton->ReleaseGfx.BgColor],Width);
                else PixelArray256Set(pPixArr,GfxPaletteClut[pButton->PressGfx.BgColor],Width);
            }
            else PixelArray256Set(pPixArr,GfxPaletteClut[pButton->InactiveGfx.BgColor],Width);
            pPixArr=pPixArr+pWindow->Outline.OuterArea.W;
            Height--;
        }
        Width=pButton->Area.W;
        Width=Width/STRING_SIZE;
        pMemory=pButton->pName;
        Position.X=pTable->Area.X+pButton->Area.X+1;
        Position.Y=pTable->Area.Y+pButton->Area.Y+1;
        if(pButton->pBitmap!=(UINT8 *)NULL){        
			///* GDB : Windows general title button.
            if(pButton->Active==TRUE){
                if(pButton->Status==WINDOW_BUTTON_RELEASE)
                    DeskDeviceInactiveWindowMemoryCharDraw(pWindow,pButton->pBitmap,&Position,&pButton->ReleaseGfx);
                else DeskDeviceInactiveWindowMemoryCharDraw(pWindow,pButton->pBitmap,&Position,&pButton->PressGfx);          
            }
            else DeskDeviceInactiveWindowMemoryCharDraw(pWindow,pButton->pBitmap,&Position,&pButton->InactiveGfx);          
			//*/
		}
        else if(pMemory!=(UINT8 *)NULL){
            while((Width!=0)&&(*pMemory!=0)){   
                if(pButton->Active==TRUE){
                    if(pButton->Status==WINDOW_BUTTON_RELEASE)
                        DeskDeviceInactiveWindowMemoryCharDraw(pWindow,FontBitmapGet(FONT8X8,*pMemory),&Position,&pButton->ReleaseGfx);
                    else DeskDeviceInactiveWindowMemoryCharDraw(pWindow,FontBitmapGet(FONT8X8,*pMemory),&Position,&pButton->PressGfx);
                }
                else DeskDeviceInactiveWindowMemoryCharDraw(pWindow,FontBitmapGet(FONT8X8,*pMemory),&Position,&pButton->InactiveGfx);
                pMemory++;
                Width--;
                Position.X=Position.X+STRING_SIZE;
            }
        }
        if(pButton->Outline==TRUE){
            Position.X=pTable->Area.X+pButton->Area.X;
            Position.Y=pTable->Area.Y+pButton->Area.Y;
            Height=pButton->Area.H;
            Width=pButton->Area.W;
            pPixArr=DeskInactiveWindowCtrl.pInactiveWindowMemory
                    +pWindow->Outline.OuterArea.W*Position.Y
                    +Position.X;
			PixelArray256Set(pPixArr,GfxPaletteClut[pButton->OutlineColor],Width);
            pPixArr=DeskInactiveWindowCtrl.pInactiveWindowMemory
                    +pWindow->Outline.OuterArea.W*(Position.Y+Height-1)
                    +Position.X;
			PixelArray256Set(pPixArr,GfxPaletteClut[pButton->OutlineColor],Width);
            pPixArr=DeskInactiveWindowCtrl.pInactiveWindowMemory
                    +pWindow->Outline.OuterArea.W*Position.Y
                    +Position.X;
            while(Height!=0){
				PixelArray256Set(pPixArr,GfxPaletteClut[pButton->OutlineColor],1);
				PixelArray256Set(pPixArr,GfxPaletteClut[pButton->OutlineColor],1);
                pPixArr=pPixArr+pWindow->Outline.OuterArea.W;
                Height--;
            }
        }
        pButton->Dirty=FALSE;
        pWindow->Dirty=TRUE;
    }
    else if(DrawPlace==DESK_DEVICE_DRAW_OSD){
        Position.X=pWindow->DisplayArea.X+pTable->Area.X+pButton->Area.X;
        Position.Y=pWindow->DisplayArea.Y+pTable->Area.Y+pButton->Area.Y;
        Height=pButton->Area.H;
        Width=pButton->Area.W;
        pPixArr=OsdCtrl.pPixMemory+DeskWorkCtrl.WorkArea.W*Position.Y+Position.X;
        while(Height!=0){
            if(pButton->Active==TRUE){
                if(pButton->Status==WINDOW_BUTTON_RELEASE){
					PixelArray256Set(pPixArr,GfxPaletteClut[pButton->ReleaseGfx.BgColor],Width);
					BoxDraw(GfxPaletteClut[pButton->ReleaseGfx.BgColor], Width, 1, Position.X, Position.Y);
				}
                else {
					PixelArray256Set(pPixArr,GfxPaletteClut[pButton->PressGfx.BgColor],Width);
					BoxDraw(GfxPaletteClut[pButton->PressGfx.BgColor], Width, 1, Position.X, Position.Y);
				}
			}
            else {
				PixelArray256Set(pPixArr,GfxPaletteClut[pButton->InactiveGfx.BgColor],Width);
				BoxDraw(GfxPaletteClut[pButton->InactiveGfx.BgColor], Width, 1, Position.X, Position.Y);
            }
			pPixArr=pPixArr+DeskWorkCtrl.WorkArea.W;
            Height--;
			Position.Y++;
        }
        Width=pButton->Area.W;
        Width=Width/STRING_SIZE;
        pMemory=pButton->pName;
        Position.X=pWindow->DisplayArea.X+pTable->Area.X+pButton->Area.X+1;
        Position.Y=pWindow->DisplayArea.Y+pTable->Area.Y+pButton->Area.Y+1;
        if(pButton->pBitmap!=(UINT8 *)NULL){                       
            if(pButton->Active==TRUE){
                if(pButton->Status==WINDOW_BUTTON_RELEASE)
                   DeskDeviceOsdCharDraw(pButton->pBitmap,&Position,&pButton->ReleaseGfx);
                else DeskDeviceOsdCharDraw(pButton->pBitmap,&Position,&pButton->PressGfx);        
			}
            else DeskDeviceOsdCharDraw(pButton->pBitmap,&Position,&pButton->InactiveGfx);    
        }
        else if(pMemory!=(UINT8 *)NULL){
            while(Width!=0){
                if(*pMemory==0) break;
				if(pButton->Active==TRUE){
					if(pButton->Status==WINDOW_BUTTON_RELEASE)
						DeskDeviceOsdCharDraw(FontBitmapGet(FONT8X8,*pMemory),&Position,&pButton->ReleaseGfx);
                    else DeskDeviceOsdCharDraw(FontBitmapGet(FONT8X8,*pMemory),&Position,&pButton->PressGfx);        
                }
                else DeskDeviceOsdCharDraw(FontBitmapGet(FONT8X8,*pMemory),&Position,&pButton->InactiveGfx);     
                pMemory++;
                Width--;
                Position.X=Position.X+STRING_SIZE;
            }
        }
		
        if(pButton->Outline==TRUE){
            Position.X=pWindow->DisplayArea.X+pTable->Area.X+pButton->Area.X;
            Position.Y=pWindow->DisplayArea.Y+pTable->Area.Y+pButton->Area.Y;
            Height=pButton->Area.H;
            Width=pButton->Area.W;
			pPixArr=OsdCtrl.pPixMemory
                    +DeskWorkCtrl.WorkArea.W*Position.Y
                    +Position.X;
			PixelArray256Set(pPixArr,GfxPaletteClut[pButton->OutlineColor],Width);
			BoxDraw(GfxPaletteClut[pButton->OutlineColor], Width, 1, Position.X, Position.Y);
			pPixArr=OsdCtrl.pPixMemory
                    +DeskWorkCtrl.WorkArea.W*(Position.Y+Height-1)
                    +Position.X;
			PixelArray256Set(pPixArr,GfxPaletteClut[pButton->OutlineColor],Width);
			BoxDraw(GfxPaletteClut[pButton->OutlineColor], Width, 1, Position.X, Position.Y+Height-1);
			pPixArr=OsdCtrl.pPixMemory
                    +DeskWorkCtrl.WorkArea.W*Position.Y
                    +Position.X;
			
            while(Height!=0){
				PixelArray256Set(pPixArr,GfxPaletteClut[pButton->OutlineColor],1);
				PixelArray256Set(pPixArr+Width-1,GfxPaletteClut[pButton->OutlineColor],1);
                pPixArr=pPixArr+DeskWorkCtrl.WorkArea.W;
				BoxDraw(GfxPaletteClut[pButton->OutlineColor], 1, 1, Position.X, Position.Y);
				BoxDraw(GfxPaletteClut[pButton->OutlineColor], 1, 1, Position.X+Width-1, Position.Y);
				Position.Y++;
                Height--;
            }
        }
        pButton->Dirty=FALSE;
    }
}

//******
// stringbox
//******
VOID DeskDeviceStringboxDraw(UINT8 DrawPlace,WINDOW *pWindow,WINDOW_TABLE *pTable,WINDOW_STRINGBOX *pStringbox){
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pPixArr;
	UINT8 *pMemory;
    UINT32 Height,Width;
    GRAPHIC_POSITION Position;
    
    if(DrawPlace==DESK_DEVICE_DRAW_ACTIVEWINDOW){
        Position.X=pTable->Area.X+pStringbox->Area.X;
        Position.Y=pTable->Area.Y+pStringbox->Area.Y;
        Height=pStringbox->Area.H;
        Width=pStringbox->Area.W;
        pPixArr=DeskActiveWindowCtrl.pActiveWindowMemory
                +pWindow->Outline.OuterArea.W*Position.Y
                +Position.X;
        while(Height!=0){
            PixelArray256Set(pPixArr,GfxPaletteClut[pStringbox->Gfx.BgColor],Width);
			pPixArr=pPixArr+pWindow->Outline.OuterArea.W;
            Height--;
        }
        Width=pStringbox->Area.W;
        Width=Width/STRING_SIZE;
        pMemory=pStringbox->pName;
        Position.X=pTable->Area.X+pStringbox->Area.X+1;
        Position.Y=pTable->Area.Y+pStringbox->Area.Y+1;
        while((Width!=0)&&(*pMemory!=0)){
            DeskDeviceActiveWindowMemoryCharDraw(pWindow,FontBitmapGet(FONT8X8,*pMemory),&Position,&pStringbox->Gfx);
            pMemory++;
            Width--;
            Position.X=Position.X+STRING_SIZE;
        }
        pStringbox->Dirty=FALSE;
        pWindow->Dirty=TRUE;
    }
    else if(DrawPlace==DESK_DEVICE_DRAW_INACTIVEWINDOW){
        Position.X=pTable->Area.X+pStringbox->Area.X;
        Position.Y=pTable->Area.Y+pStringbox->Area.Y;
        Height=pStringbox->Area.H;
        Width=pStringbox->Area.W;
        pPixArr=DeskInactiveWindowCtrl.pInactiveWindowMemory
                +pWindow->Outline.OuterArea.W*Position.Y
                +Position.X;
        while(Height!=0){
            PixelArray256Set(pPixArr,GfxPaletteClut[pStringbox->Gfx.BgColor],Width);
			pPixArr=pPixArr+pWindow->Outline.OuterArea.W;
            Height--;
        }
        Width=pStringbox->Area.W;
        Width=Width/STRING_SIZE;
        pMemory=pStringbox->pName;
        Position.X=pTable->Area.X+pStringbox->Area.X+1;
        Position.Y=pTable->Area.Y+pStringbox->Area.Y+1;
        while((Width!=0)&&(*pMemory!=0)){
            DeskDeviceInactiveWindowMemoryCharDraw(pWindow,FontBitmapGet(FONT8X8,*pMemory),&Position,&pStringbox->Gfx);
            pMemory++;
            Width--;
            Position.X=Position.X+STRING_SIZE;
        }
        pStringbox->Dirty=FALSE;
        pWindow->Dirty=TRUE;
    }
    else if(DrawPlace==DESK_DEVICE_DRAW_OSD){
        Position.X=pWindow->DisplayArea.X+pTable->Area.X+pStringbox->Area.X;
        Position.Y=pWindow->DisplayArea.Y+pTable->Area.Y+pStringbox->Area.Y;
        Height=pStringbox->Area.H;
        Width=pStringbox->Area.W;
        pPixArr=OsdCtrl.pPixMemory+DeskWorkCtrl.WorkArea.W*Position.Y+Position.X;
        while(Height!=0){
            PixelArray256Set(pPixArr,GfxPaletteClut[pStringbox->Gfx.BgColor],Width);
			BoxDraw(GfxPaletteClut[pStringbox->Gfx.BgColor], Width, 1, Position.X, Position.Y);
			pPixArr=pPixArr+DeskWorkCtrl.WorkArea.W;
            Height--;
			Position.Y++;
        }
        Width=pStringbox->Area.W;
        Width=Width/STRING_SIZE;
        pMemory=pStringbox->pName;
        Position.X=pWindow->DisplayArea.X+pTable->Area.X+pStringbox->Area.X+1;
        Position.Y=pWindow->DisplayArea.Y+pTable->Area.Y+pStringbox->Area.Y+1;
        while((Width!=0)&&(*pMemory!=0)){
            DeskDeviceOsdCharDraw(FontBitmapGet(FONT8X8,*pMemory),&Position,&pStringbox->Gfx);
            pMemory++;
            Width--;
			Position.X=Position.X+STRING_SIZE;
        }
        pStringbox->Dirty=FALSE;
    }
}

//******
// icon
//******
VOID DeskDeviceIconDraw(UINT8 DrawPlace,WINDOW *pWindow,WINDOW_TABLE *pTable,WINDOW_ICON *pIcon){
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pPixArr;
    UINT32 Height,Width;
    GRAPHIC_POSITION Position;
    
    if(DrawPlace==DESK_DEVICE_DRAW_ACTIVEWINDOW){
        Position.X=pTable->Area.X+pIcon->Area.X;
        Position.Y=pTable->Area.Y+pIcon->Area.Y;
        Height=pIcon->Area.H;
        Width=pIcon->Area.W;
        pPixArr=DeskActiveWindowCtrl.pActiveWindowMemory
                +pWindow->Outline.OuterArea.W*Position.Y+Position.X;
        while(Height!=0){
            PixelArray256Set(pPixArr,GfxPaletteClut[pIcon->ActiveGfx.BgColor],Width);
			pPixArr=pPixArr+pWindow->Outline.OuterArea.W;
            Height--;
        }
        DeskDeviceActiveWindowMemoryCharDraw(pWindow,pIcon->pBitmap,&Position,&pIcon->ActiveGfx);
        //pWindow->Dirty=TRUE;
    }
    else if(DrawPlace==DESK_DEVICE_DRAW_INACTIVEWINDOW){
        Position.X=pTable->Area.X+pIcon->Area.X;
        Position.Y=pTable->Area.Y+pIcon->Area.Y;
        Height=pIcon->Area.H;
        Width=pIcon->Area.W;
        pPixArr=DeskInactiveWindowCtrl.pInactiveWindowMemory
                +pWindow->Outline.OuterArea.W*Position.Y+Position.X;
        while(Height!=0){
            PixelArray256Set(pPixArr,GfxPaletteClut[pIcon->InactiveGfx.BgColor],Width);
			pPixArr=pPixArr+pWindow->Outline.OuterArea.W;
            Height--;
        }
        DeskDeviceInactiveWindowMemoryCharDraw(pWindow,pIcon->pBitmap,&Position,&pIcon->ActiveGfx);
        //pWindow->Dirty=TRUE;
    }
    else if(DrawPlace==DESK_DEVICE_DRAW_OSD){
        Position.X=pWindow->DisplayArea.X+pTable->Area.X+pIcon->Area.X;
        Position.Y=pWindow->DisplayArea.X+pTable->Area.Y+pIcon->Area.Y;
        Height=pIcon->Area.H;
        Width=pIcon->Area.W;
        pPixArr=OsdCtrl.pPixMemory+DeskWorkCtrl.WorkArea.W*Position.Y+Position.X;
        while(Height!=0){
            PixelArray256Set(pPixArr,GfxPaletteClut[pIcon->ActiveGfx.BgColor],Width);
			BoxDraw(GfxPaletteClut[pIcon->ActiveGfx.BgColor], Width, 1, Position.X, Position.Y);
			pPixArr=pPixArr+DeskWorkCtrl.WorkArea.W;
            Height--;
			Position.Y++;
        }
        Position.X=pWindow->DisplayArea.X+pTable->Area.X+pIcon->Area.X+1;
        Position.Y=pWindow->DisplayArea.X+pTable->Area.Y+pIcon->Area.Y+1;
        DeskDeviceOsdCharDraw(pIcon->pBitmap,&Position,&pIcon->ActiveGfx);
    }
}

//******
// windowbox..only draw on osd
//******
VOID DeskDeviceWindowboxDraw(UINT8 DrawPlace,WINDOW *pWindow,WINDOW_TABLE *pTable,WINDOW_WINDOWBOX *pWindowbox){
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pPixArr;
	WINDOW *pWindow2;
    UINT32 Height,Width,temp;
    GRAPHIC_POSITION Position;

    if(DrawPlace==DESK_DEVICE_DRAW_OSD){
        //CaptionStringPrint(&DeskDebugCtrl.Caption,"windowbox draw");
        pWindow2=(WINDOW *)pWindowbox->pWindow;
        Position.X=pWindow->DisplayArea.X+pTable->Area.X+pWindowbox->Area.X;
        Position.Y=pWindow->DisplayArea.Y+pTable->Area.Y+pWindowbox->Area.Y;
		temp=Position.Y;
        Height=pWindowbox->Area.H;
        Width=pWindowbox->Area.W;
        pPixArr=OsdCtrl.pPixMemory+DeskWorkCtrl.WorkArea.W*Position.Y+Position.X;
        while(Height!=0){
            if(pWindow2->Active==TRUE) {
				PixelArray256Set(pPixArr,GfxPaletteClut[pWindowbox->ActiveGfx.BgColor],Width);
				BoxDraw(GfxPaletteClut[pWindowbox->InactiveGfx.BgColor], Width, 1, Position.X, Position.Y);
			}else {
				PixelArray256Set(pPixArr,GfxPaletteClut[pWindowbox->InactiveGfx.BgColor],Width);
				BoxDraw(GfxPaletteClut[pWindowbox->InactiveGfx.BgColor], Width, 1, Position.X, Position.Y);
			}
			pPixArr=pPixArr+DeskWorkCtrl.WorkArea.W;
            Height--;
			Position.Y++;
        }
        Position.X=Position.X+1;
        Position.Y=temp+1;
        if(pWindow2->Active==TRUE) DeskDeviceOsdCharDraw(FontBitmapGet(FONT8X8,pWindow2->pTitle[0]),&Position,&pWindowbox->ActiveGfx);
        else DeskDeviceOsdCharDraw(FontBitmapGet(FONT8X8,pWindow2->pTitle[0]),&Position,&pWindowbox->InactiveGfx);
        Position.X=Position.X+STRING_SIZE;
        if(pWindow2->Active==TRUE) DeskDeviceOsdCharDraw(FontBitmapGet(FONT8X8,'.'),&Position,&pWindowbox->ActiveGfx);
        else DeskDeviceOsdCharDraw(FontBitmapGet(FONT8X8,'.'),&Position,&pWindowbox->InactiveGfx);
    }
}

//...
VOID DeskDeviceActiveWindowMemoryCharDraw(WINDOW *pWindow,UINT8 *pBitmap,GRAPHIC_POSITION *pPosition,GRAPHIC_GFX *pGfx){
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pBitmapStart;
	UINT8  i,j,tmp;
	UINT32 height = *(UINT32*)&pBitmap[Height_OFFSET];
	UINT32 width  = *(UINT32*)&pBitmap[Width_OFFSET];
	UINT32 size  = *(UINT32*)&pBitmap[Size_OFFSET];
	UINT8* bmp = &pBitmap[PIX_OFFSET];
	
    pBitmapStart=DeskActiveWindowCtrl.pActiveWindowMemory
                 +pWindow->DisplayArea.W*pPosition->Y+pPosition->X;
	
	tmp = height - 1;
	for(i=0;i<height;i++){
		for(j=0;j<width;j++) PixelArray256Set(pBitmapStart+j,bmp[j+tmp*width],1);
		pBitmapStart=pBitmapStart+pWindow->Outline.OuterArea.W;
		tmp--;
	}
}

VOID DeskDeviceInactiveWindowMemoryCharDraw(WINDOW *pWindow,UINT8 *pBitmap,GRAPHIC_POSITION *pPosition,GRAPHIC_GFX *pGfx){
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pBitmapStart;
	UINT8  i,j,tmp;
	UINT32 height = *(UINT32*)&pBitmap[Height_OFFSET];
	UINT32 width  = *(UINT32*)&pBitmap[Width_OFFSET];
	UINT32 size  = *(UINT32*)&pBitmap[Size_OFFSET];
	UINT8* bmp = &pBitmap[PIX_OFFSET];

    pBitmapStart=DeskInactiveWindowCtrl.pInactiveWindowMemory
                 +pWindow->DisplayArea.W*pPosition->Y+pPosition->X;
     
	tmp = height - 1;
    for(i=0;i<height;i++){
		for(j=0;j<width;j++) PixelArray256Set(pBitmapStart+j,bmp[j+tmp*width],1);
		pBitmapStart=pBitmapStart+pWindow->Outline.OuterArea.W;
		tmp--;
	}
}

VOID DeskDeviceOsdCharDraw(UINT8 *pBitmap,GRAPHIC_POSITION *pPosition,GRAPHIC_GFX *pGfx)
{    
	BmpDraw(pBitmap, 12*12, pPosition->X, pPosition->Y, TRUE);
}

VOID DeskDeviceOsdBitmapDraw(UINT8 *pBitmap,GRAPHIC_POSITION *pPosition,GRAPHIC_GFX *pGfx)
{
	BmpDraw(pBitmap, 12*12, pPosition->X, pPosition->Y, TRUE);
}
