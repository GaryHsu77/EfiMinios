#include <includes.h>

const UINT8 BeegameBeeWingUp[]={ // bee swing up
0x8f,0x09, //width&0x80,height
0x20,0x00,
0x70,0x00,
0x70,0x00,
0x70,0x00,
0x90,0x00,
0xac,0x00,
0x5f,0x00,
0x3f,0x80,
0x5f,0x00,
0xac,0x00,
0x90,0x00,
0x70,0x00,
0x70,0x00,
0x70,0x00,
0x20,0x00,
};

const UINT8 BeegameBeeWingDown[]={ //bee swing down
0x8f,0x09, //width&0x80,height
0x08,0x00,
0x1c,0x00,
0x1c,0x00,
0x58,0x00,
0x88,0x00,
0xac,0x00,
0x5f,0x00,
0x3f,0x80,
0x5f,0x00,
0xac,0x00,
0x88,0x00,
0x58,0x00,
0x1c,0x00,
0x1c,0x00,
0x08,0x00,
};

const UINT8 BeegameBeeWingClose[]={ //bee swing down
0x8f,0x09, //width&0x80,height
0x00,0x00,
0x03,0x80,
0x07,0x00,
0x4e,0x00,
0x88,0x00,
0xac,0x00,
0x5f,0x00,
0x3f,0x80,
0x5f,0x00,
0xac,0x00,
0x88,0x00,
0x4e,0x00,
0x07,0x00,
0x03,0x80,
0x00,0x00,
};

const int BeegameBeeFlyingPath[BEE_PATH_MAX][54]={
{2,6,2,6,4,4,6,6,4,2,6,8,4,2,2,4,2,6,2,2,4,6,4,2,-2,-4,-4,-6,-4,-4,-2,-4,-6,4,2,4,2,4,4,6,8,6,4,2,-2,-4,-6,-4,-2,-4,-2,-8,-6,0},
{1,4,6,-6,-4,-4,-6,-6,-4,-4,-4,-4,-6,-6,-4,2,4,6,4,2,4,6,4,2,2,4,4,6,4,4,2,4,6,-4,-2,-4,-2,-4,-4,-6,-8,-6,-4,2,2,4,6,4,2,4,2,8,6,0},
{-4,4,2,2,2,4,6,6,4,2,2,2,4,6,4,2,4,6,-4,-2,-4,-6,-4,-2,-2,-4,-4,-6,-4,4,2,4,6,2,2,4,4,2,2,6,4,6,2,2,-2,-2,-6,-2,-4,-4,-2,-4,-6,0},
{-2,-2,-2,-6,-2,-2,-6,6,2,2,4,2,6,6,2,2,2,6,-2,-2,-4,-6,-4,-4,-2,-2,2,6,2,2,2,4,6,4,2,2,2,2,-2,-6,-4,-6,-2,-4,2,2,6,2,4,4,2,4,6,0},
{-2,-2,-4,-6,-4,2,6,6,2,2,4,2,6,6,2,2,-2,-6,-2,-4,-4,-6,-2,-2,-2,-2,-4,-6,-4,-2,-2,-2,-6,2,2,4,4,2,2,6,4,6,2,4,4,2,6,2,2,2,2,4,6,0},
{2,2,6,6,6,6,6,6,-2,-2,-4,-4,-6,-6,2,2,6,6,6,6,6,6,6,6,6,6,-2,-2,-6,-6,-6,-6,-6,-2,-2,-2,-4,-2,2,6,4,6,2,2,4,2,6,2,4,2,4,4,6,0},
{2,2,2,4,4,2,2,4,4,2,4,2,6,6,6,2,2,6,2,4,4,6,2,2,-4,-4,-6,-6,-6,-6,-6,-6,-4,-2,-2,-2,-4,-4,-2,-6,-4,-6,-2,-4,2,2,6,4,4,2,2,4,6,0},
{2,4,2,-6,-2,-2,6,6,2,4,2,2,-6,-6,-4,-4,-2,-6,2,2,2,6,2,2,4,4,2,6,2,2,2,2,-6,-2,-2,-4,-4,-4,-2,-6,-4,-6,-2,-2,2,2,6,4,4,2,2,4,6,0},
{-2,-4,2,6,4,5,2,4,2,6,4,5,2,2,-2,-2,-4,-6,-2,-4,-4,-6,-2,-2,-4,-4,-2,-6,-2,-2,-4,-4,-6,-2,-2,2,2,4,4,6,4,6,2,2,4,2,6,2,2,4,2,4,6,0},
{-2,-2,2,2,2,2,6,-6,-2,-2,-4,-2,-6,6,2,2,2,6,6,6,6,6,2,2,-4,-2,-6,-4,-5,-6,-4,-2,-6,2,2,4,4,2,2,6,4,6,2,2,-2,-2,-6,-2,-2,-2,-1,-4,-6,0},
};

VOID BeegameBeeMove(BEEGAME_CONTROL *pBeegameCtrl)
{
    MY_MUTEX mutex;

    mutex = OsEnterCritical();
    if(pBeegameCtrl->pCurrentBee==(BEEGAME_BEE *)NULL){
    	pBeegameCtrl->pCurrentBee=BeegameBeeListBeeGet(pBeegameCtrl);
    	if(pBeegameCtrl->pCurrentBee==(BEEGAME_BEE *)NULL){
    		pBeegameCtrl->GameOver=TRUE;
            OsExitCritical(mutex);
            return;
        }
	    pBeegameCtrl->BeeCurrentPath=RootTaskRandomNumberGet()%BEE_PATH_MAX;
	    if(pBeegameCtrl->BeeCurrentPath==pBeegameCtrl->BeePreviousPath){
	        pBeegameCtrl->BeeCurrentPath++;
	        pBeegameCtrl->BeeCurrentPath=pBeegameCtrl->BeeCurrentPath%BEE_PATH_MAX;
	    }
	    pBeegameCtrl->BeePreviousPath=pBeegameCtrl->BeeCurrentPath;
	    pBeegameCtrl->FlyStep=0;
    	BeegameBeeMapRecovery(pBeegameCtrl,pBeegameCtrl->pCurrentBee); // kill bees image
    	pBeegameCtrl->pCurrentBee->SwingStatus=BEE_BEES_SWINGUP;
    	pBeegameCtrl->pCurrentBee->CurrentArea.Y=20;
    	pBeegameCtrl->pCurrentBee->PreviousArea.Y=20;
    	pBeegameCtrl->pCurrentBee->CurrentArea.X=pBeegameCtrl->Board.Area.W/2;
    	pBeegameCtrl->pCurrentBee->PreviousArea.X=pBeegameCtrl->Board.Area.W/2;
        BeegameBeeMapCapture(pBeegameCtrl,pBeegameCtrl->pCurrentBee);
        BeegameBeeDraw(pBeegameCtrl,pBeegameCtrl->pCurrentBee);
        BeegameBeeMapDraw(pBeegameCtrl,pBeegameCtrl->pCurrentBee);
        pBeegameCtrl->Dirty=TRUE;
        OsExitCritical(mutex);
        return;
    }
    BeegameBeeMapRecovery(pBeegameCtrl,pBeegameCtrl->pCurrentBee); // kill bees image
    if(pBeegameCtrl->pCurrentBee->SwingStatus==BEE_BEES_SWINGUP) pBeegameCtrl->pCurrentBee->SwingStatus=BEE_BEES_SWINGDOWN;
    else pBeegameCtrl->pCurrentBee->SwingStatus=BEE_BEES_SWINGUP;
    if(BeegameBeeFlyingPath[pBeegameCtrl->BeeCurrentPath][pBeegameCtrl->FlyStep]!=0){
        pBeegameCtrl->pCurrentBee->CurrentArea.X=pBeegameCtrl->pCurrentBee->CurrentArea.X
              +BeegameBeeFlyingPath[pBeegameCtrl->BeeCurrentPath][pBeegameCtrl->FlyStep++];
    }
    pBeegameCtrl->pCurrentBee->CurrentArea.Y+=2;
    if(pBeegameCtrl->pCurrentBee->CurrentArea.Y>=(BEE_WINDOW_HEIGHT-BEE_BEES_HEIGHT)){
    	pBeegameCtrl->pCurrentBee=(BEEGAME_BEE *)NULL;
    }
    else{
        pBeegameCtrl->pCurrentBee->PreviousArea.X=pBeegameCtrl->pCurrentBee->CurrentArea.X;
        pBeegameCtrl->pCurrentBee->PreviousArea.Y=pBeegameCtrl->pCurrentBee->CurrentArea.Y;
        BeegameBeeMapCapture(pBeegameCtrl,pBeegameCtrl->pCurrentBee);
        BeegameBeeDraw(pBeegameCtrl,pBeegameCtrl->pCurrentBee);
        BeegameBeeMapDraw(pBeegameCtrl,pBeegameCtrl->pCurrentBee);
    }
    OsExitCritical(mutex);
    pBeegameCtrl->Dirty=TRUE;
}

VOID BeegameBeeBulletHitHandler(BEEGAME_CONTROL *pBeegameCtrl){
	BEEGAME_BEE *pBeegameBee,*pBeegameBee2;
    BEEGAME_BULLET *pBullet,*pBullet2;
    
    if(pBeegameCtrl->UsedBulletList==(BEEGAME_BULLET *)NULL) return;
    if(pBeegameCtrl->pCurrentBee==(BEEGAME_BEE *)NULL) return;
    pBullet=pBeegameCtrl->UsedBulletList;
    while(pBullet!=(BEEGAME_BULLET *)NULL){ 	
    	if(SystemlibAreaOverlapCheck(&pBeegameCtrl->pCurrentBee->CurrentArea,&pBullet->CurrentArea)==TRUE){
            pBeegameCtrl->HitNumber++;
            BeegameBulletMapRecovery(pBeegameCtrl,pBullet);
     	    BeegameUsedBulletListBulletDelete(pBeegameCtrl,pBullet);	
            BeegameBeeMapClear(pBeegameCtrl,pBeegameCtrl->pCurrentBee);	
      	    pBeegameCtrl->pCurrentBee=(BEEGAME_BEE *)NULL;
       	    break;
       	}
        pBullet=pBullet->Next;
    }
}

VOID BeegameBeeUpdate(BEEGAME_CONTROL *pBeegameCtrl,BEEGAME_BEE *pBeegameBee){
    BeegameBeeMapRecovery(pBeegameCtrl,pBeegameBee);
    pBeegameBee->PreviousArea.X=pBeegameBee->CurrentArea.X;
    pBeegameBee->PreviousArea.Y=pBeegameBee->CurrentArea.Y;
    BeegameBeeMapCapture(pBeegameCtrl,pBeegameBee);
    BeegameBeeDraw(pBeegameCtrl,pBeegameBee);
    BeegameBeeMapDraw(pBeegameCtrl,pBeegameBee);
}

VOID BeegameBeeMapCapture(BEEGAME_CONTROL *pBeegameCtrl,BEEGAME_BEE *pBeegameBee){
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pSource;
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pDestination;
	UINT8 Height;	
	
	Height=BEE_BEES_HEIGHT;
	pSource=pBeegameCtrl->Board.pBoardMemory
	        +pBeegameCtrl->Board.Area.W*pBeegameBee->CurrentArea.Y
	        +pBeegameBee->CurrentArea.X;
	pDestination=pBeegameBee->GraphicMemory;
	while(Height!=0){
		PixelArrayCopy(pSource,pDestination,BEE_BEES_WIDTH);
        pSource=pSource+pBeegameCtrl->Board.Area.W;
        pDestination=pDestination+BEE_BEES_WIDTH;
        Height--;
	}
    PixelArrayCopy(pBeegameBee->GraphicMemory,pBeegameBee->RecoveryMemory,pBeegameBee->BeesMemoryLength);
}

VOID BeegameBeeMapDraw(BEEGAME_CONTROL *pBeegameCtrl,BEEGAME_BEE *pBeegameBee){
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pSource;
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pDestination;
	UINT8 Height;	
	
	Height=BEE_BEES_HEIGHT;
	pDestination=pBeegameCtrl->Board.pBoardMemory
	             +pBeegameCtrl->Board.Area.W*pBeegameBee->CurrentArea.Y
	             +pBeegameBee->CurrentArea.X;
	pSource=pBeegameBee->GraphicMemory;
	while(Height!=0){
        PixelArrayCopy(pSource,pDestination,BEE_BEES_WIDTH);
        pDestination=pDestination+pBeegameCtrl->Board.Area.W;
        pSource=pSource+BEE_BEES_WIDTH;
        Height--;
	}
}

VOID BeegameBeeMapRecovery(BEEGAME_CONTROL *pBeegameCtrl,BEEGAME_BEE *pBeegameBee){
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pSource;
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pDestination;
	UINT8 Height;	

	Height=BEE_BEES_HEIGHT;
	pDestination=pBeegameCtrl->Board.pBoardMemory
	             +pBeegameCtrl->Board.Area.W*pBeegameBee->PreviousArea.Y
	             +pBeegameBee->PreviousArea.X;
	pSource=pBeegameBee->RecoveryMemory;
	while(Height!=0){
        PixelArrayCopy(pSource,pDestination,BEE_BEES_WIDTH);
        pDestination=pDestination+pBeegameCtrl->Board.Area.W;
        pSource=pSource+BEE_BEES_WIDTH;
        Height--;
	}
}

VOID BeegameBeeMapClear(BEEGAME_CONTROL *pBeegameCtrl,BEEGAME_BEE *pBeegameBee){
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pDestination;
	UINT8 Height;	
	UINT8 BgColor;

    BgColor=GfxPaletteClut[pBeegameCtrl->Board.Gfx.BgColor];
	Height=BEE_BEES_HEIGHT;
	pDestination=pBeegameCtrl->Board.pBoardMemory
	             +pBeegameCtrl->Board.Area.W*pBeegameBee->PreviousArea.Y
	             +pBeegameBee->PreviousArea.X;
	while(Height!=0){
        PixelArray256Set(pDestination,BgColor,BEE_BEES_WIDTH);
        pDestination=pDestination+pBeegameCtrl->Board.Area.W;
        Height--;
	}
}

VOID BeegameBeeDraw(BEEGAME_CONTROL *pBeegameCtrl,BEEGAME_BEE *pBeegameBee){
    UINT8  HeightIndex,ColumnIndex,BitIndex;
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pMemory,*pBitmapStart,*pColMemory;
	UINT8 *pBeesBitmap;
    UINT8 Width;
    UINT8 Height;
    UINT8 BitValue;
    UINT8 BitmapFormat;
    
    pBitmapStart=pBeegameBee->GraphicMemory;
    if(pBeegameBee->SwingStatus==BEE_BEES_SWINGUP) pBeesBitmap=BeegameBeeWingUp;
    else if(pBeegameBee->SwingStatus==BEE_BEES_SWINGDOWN) pBeesBitmap=BeegameBeeWingDown;
    else pBeesBitmap=BeegameBeeWingClose;
    Width=*pBeesBitmap;
    pBeesBitmap++;
    Height=*pBeesBitmap;
    pBeesBitmap++;
    if(Width&0x80) BitmapFormat=1;
    else BitmapFormat=0;
    Width&=0x7f;
    if(BitmapFormat==1){
        for(ColumnIndex=0;ColumnIndex<Width;ColumnIndex++){
            pColMemory=pBitmapStart+ColumnIndex;
            BitIndex=0;
            for(HeightIndex=0;HeightIndex<Height;HeightIndex++){
                pMemory=pColMemory+BEE_BEES_WIDTH*HeightIndex; 
                BitValue=((*pBeesBitmap)<<BitIndex)&0x80;
                if(BitValue!=0) PixelArray256Set(pMemory,GfxPaletteClut[pBeegameBee->BeesGfx.FontColor],1);
				BitIndex++;
	            if(BitIndex==8){
	                pBeesBitmap++;
	                BitIndex=0;
	            }
            }
            if(BitIndex!=0) pBeesBitmap++;
        }
    }	
}

VOID BeegameBeeListBeePut(BEEGAME_CONTROL *pBeegameCtrl,BEEGAME_BEE *pBeegameBee){
	pBeegameBee->Prev=(BEEGAME_BEE *)NULL;        
	pBeegameBee->Next=(BEEGAME_BEE *)NULL;
    if(pBeegameCtrl->BeeList==(BEEGAME_BEE *)NULL)
        pBeegameCtrl->BeeList=pBeegameBee;
    else{
        pBeegameCtrl->BeeList->Prev=pBeegameBee;
        pBeegameBee->Next=pBeegameCtrl->BeeList;            
        pBeegameCtrl->BeeList=pBeegameBee; 
    }    
}

BEEGAME_BEE *BeegameBeeListBeeGet(BEEGAME_CONTROL *pBeegameCtrl){
	BEEGAME_BEE *pBeegameBee;
	
	if(pBeegameCtrl->BeeList==(BEEGAME_BEE *)NULL) return (BEEGAME_BEE *)NULL;
	pBeegameBee=pBeegameCtrl->BeeList;
	pBeegameCtrl->BeeList=pBeegameCtrl->BeeList->Next;
	pBeegameBee->Prev=(BEEGAME_BEE *)NULL;        
	pBeegameBee->Next=(BEEGAME_BEE *)NULL;
	return pBeegameBee;
}
