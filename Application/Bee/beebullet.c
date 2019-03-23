#include <includes.h>

const UINT8 BeegameBulletBitmap[]={
0x81,0x02, //width&0x80,height
0xc0,
};

VOID BeegameBulletMove(BEEGAME_CONTROL *pBeegameCtrl){
	BEEGAME_BULLET *pBullet,*pBullet2;
    MY_MUTEX mutex;

    if(pBeegameCtrl->UsedBulletList==(BEEGAME_BULLET *)NULL) return;
    mutex = OsEnterCritical();
    pBullet=pBeegameCtrl->UsedBulletList;
    while(pBullet->Next!=(BEEGAME_BULLET *)NULL) pBullet=pBullet->Next;
    while(pBullet!=(BEEGAME_BULLET *)NULL){
	    BeegameBulletMapRecovery(pBeegameCtrl,pBullet); // kill bullet image
	    pBullet->CurrentArea.Y-=2;
	    if(pBullet->CurrentArea.Y>15){ // redraw bullet
		    pBullet->PreviousArea.X=pBullet->CurrentArea.X;
		    pBullet->PreviousArea.Y=pBullet->CurrentArea.Y;
		    BeegameBulletMapCapture(pBeegameCtrl,pBullet);
		    BeegameBulletDraw(pBeegameCtrl,pBullet);
		    BeegameBulletMapDraw(pBeegameCtrl,pBullet);
	        pBullet=pBullet->Prev;
	    }
	    else{
	        pBullet2=pBullet->Prev;
	        BeegameUsedBulletListBulletDelete(pBeegameCtrl,pBullet); //kill bullet from used bullet list
	        pBullet=pBullet2;
	    }
    }
    OsExitCritical(mutex);
    pBeegameCtrl->Dirty=TRUE;
}

VOID BeegameBulletUpdate(BEEGAME_CONTROL *pBeegameCtrl,BEEGAME_BULLET *pBullet){
    BeegameBulletMapRecovery(pBeegameCtrl,pBullet);
    pBullet->PreviousArea.X=pBullet->CurrentArea.X;
    pBullet->PreviousArea.Y=pBullet->CurrentArea.Y;
    BeegameBulletMapCapture(pBeegameCtrl,pBullet);
    BeegameBulletDraw(pBeegameCtrl,pBullet);
    BeegameBulletMapDraw(pBeegameCtrl,pBullet);
}

VOID BeegameBulletMapCapture(BEEGAME_CONTROL *pBeegameCtrl,BEEGAME_BULLET *pBullet){
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pSource;
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pDestination;
	UINT8 Height;	

	Height=BEE_BULLET_HEIGHT;
	pSource=pBeegameCtrl->Board.pBoardMemory
	        +pBeegameCtrl->Board.Area.W*pBullet->CurrentArea.Y
	        +pBullet->CurrentArea.X;
	pDestination=pBullet->GraphicMemory;
	while(Height!=0){
        PixelArrayCopy(pSource,pDestination,BEE_BULLET_WIDTH);
        pSource=pSource+pBeegameCtrl->Board.Area.W;
        pDestination=pDestination+BEE_BULLET_WIDTH;
        Height--;
	}
    PixelArrayCopy(pBullet->GraphicMemory,pBullet->RecoveryMemory,pBullet->BulletMemoryLength);
}

VOID BeegameBulletMapDraw(BEEGAME_CONTROL *pBeegameCtrl,BEEGAME_BULLET *pBullet){
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pSource;
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pDestination;
	UINT8 Height;	

	Height=BEE_BULLET_HEIGHT;
	pDestination=pBeegameCtrl->Board.pBoardMemory
	        +pBeegameCtrl->Board.Area.W*pBullet->CurrentArea.Y
	        +pBullet->CurrentArea.X;
	pSource=pBullet->GraphicMemory;
	while(Height!=0){
        PixelArrayCopy(pSource,pDestination,BEE_BULLET_WIDTH);
        pDestination=pDestination+pBeegameCtrl->Board.Area.W;
        pSource=pSource+BEE_BULLET_WIDTH;
        Height--;
	}
}

VOID BeegameBulletMapRecovery(BEEGAME_CONTROL *pBeegameCtrl,BEEGAME_BULLET *pBullet){
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pSource;
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pDestination;
	UINT8 Height;	

	Height=BEE_BULLET_HEIGHT;
	pDestination=pBeegameCtrl->Board.pBoardMemory
	        +pBeegameCtrl->Board.Area.W*pBullet->PreviousArea.Y
	        +pBullet->PreviousArea.X;
	pSource=pBullet->RecoveryMemory;
	while(Height!=0){
        PixelArrayCopy(pSource,pDestination,BEE_BULLET_WIDTH);
        pDestination=pDestination+pBeegameCtrl->Board.Area.W;
        pSource=pSource+BEE_BULLET_WIDTH;
        Height--;
	}
}

VOID BeegameBulletDraw(BEEGAME_CONTROL *pBeegameCtrl,BEEGAME_BULLET *pBullet){
    UINT8  HeightIndex,ColumnIndex,BitIndex;
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pMemory,*pBitmapStart,*pColMemory;
	UINT8 *pBulletBitmap;
    UINT8 Width;
    UINT8 Height;
    UINT8 BitValue;
    UINT8 BitmapFormat;

    pBitmapStart=pBullet->GraphicMemory;
	pBulletBitmap=BeegameBulletBitmap;
    Width=*pBulletBitmap;
    pBulletBitmap++;
    Height=*pBulletBitmap;
    pBulletBitmap++;
    if(Width&0x80) BitmapFormat=1;
    else BitmapFormat=0;
    Width&=0x7f;
    if(BitmapFormat==1){
        for(ColumnIndex=0;ColumnIndex<Width;ColumnIndex++){
            pColMemory=pBitmapStart+ColumnIndex;
            BitIndex=0;
            for(HeightIndex=0;HeightIndex<Height;HeightIndex++){
                pMemory=pColMemory+BEE_BULLET_WIDTH*HeightIndex; 
                BitValue=((*pBulletBitmap)<<BitIndex)&0x80;
                if(BitValue!=0) PixelArray256Set(pMemory,GfxPaletteClut[pBullet->BulletGfx.FontColor],1);
				BitIndex++;
	            if(BitIndex==8){
	                pBulletBitmap++;
	                BitIndex=0;
	            }
            }
            if(BitIndex!=0) pBulletBitmap++;
        }
    }	
}

VOID BeegameFreeBulletListBulletPut(BEEGAME_CONTROL *pBeegameCtrl,BEEGAME_BULLET *pBullet){
	pBullet->Prev=(BEEGAME_BULLET *)NULL;        
	pBullet->Next=(BEEGAME_BULLET *)NULL;
    if(pBeegameCtrl->FreeBulletList==(BEEGAME_BULLET *)NULL){
        pBeegameCtrl->FreeBulletList=pBullet;
    } 
    else{
        pBeegameCtrl->FreeBulletList->Prev=pBullet;
        pBullet->Next=pBeegameCtrl->FreeBulletList;  
        pBeegameCtrl->FreeBulletList=pBullet; 
    }    
}

BEEGAME_BULLET *BeegameFreeBulletListBulletGet(BEEGAME_CONTROL *pBeegameCtrl){
    BEEGAME_BULLET *pBullet;
    
    if(pBeegameCtrl->FreeBulletList==(BEEGAME_BULLET *)NULL) return (BEEGAME_BULLET *)NULL;
    pBullet=pBeegameCtrl->FreeBulletList;
    if(pBullet->Next!=(BEEGAME_BULLET *)NULL){
        pBeegameCtrl->FreeBulletList=pBullet->Next;
        pBeegameCtrl->FreeBulletList->Prev=(BEEGAME_BULLET *)NULL;  
    }
    else pBeegameCtrl->FreeBulletList=(BEEGAME_BULLET *)NULL;
	pBullet->Prev=(BEEGAME_BULLET *)NULL;        
	pBullet->Next=(BEEGAME_BULLET *)NULL;
    return pBullet;
}

VOID BeegameUsedBulletListBulletPut(BEEGAME_CONTROL *pBeegameCtrl,BEEGAME_BULLET *pBullet){
	pBullet->Prev=(BEEGAME_BULLET *)NULL;        
	pBullet->Next=(BEEGAME_BULLET *)NULL;
    if(pBeegameCtrl->UsedBulletList==(BEEGAME_BULLET *)NULL)
        pBeegameCtrl->UsedBulletList=pBullet;
    else{
        pBeegameCtrl->UsedBulletList->Prev=pBullet;
        pBullet->Next=pBeegameCtrl->UsedBulletList;          
        pBullet->Prev=(BEEGAME_BULLET *)NULL;    
        pBeegameCtrl->UsedBulletList=pBullet; 
    }    
}

VOID BeegameUsedBulletListBulletDelete(BEEGAME_CONTROL *pBeegameCtrl,BEEGAME_BULLET *pBullet){
    BEEGAME_BULLET *pBullet2;

    pBullet2=pBeegameCtrl->UsedBulletList;
    while(pBullet2!=(BEEGAME_BULLET *)NULL){
    	if(pBullet==pBullet2) break;
    	pBullet2=pBullet2->Next;
    }
    if(pBullet2==(BEEGAME_BULLET *)NULL) return; // no found in used bullet list
    if(pBullet==pBeegameCtrl->UsedBulletList){
        if(pBullet->Next!=(BEEGAME_BULLET *)NULL){
            pBeegameCtrl->UsedBulletList=pBullet->Next;
            pBeegameCtrl->UsedBulletList->Prev=(BEEGAME_BULLET *)NULL;  
        }
        else pBeegameCtrl->UsedBulletList=(BEEGAME_BULLET *)NULL;
    }
    else{
        if(pBullet->Next!=(BEEGAME_BULLET *)NULL){
            pBullet->Prev->Next=pBullet->Next;
            pBullet->Next->Prev=pBullet->Prev;  
        }
        else pBullet->Prev->Next=(BEEGAME_BULLET *)NULL;
    }
    pBullet->Prev=(BEEGAME_BULLET *)NULL;        
    pBullet->Next=(BEEGAME_BULLET *)NULL;
    BeegameFreeBulletListBulletPut(pBeegameCtrl,pBullet);
}
