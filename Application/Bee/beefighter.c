#include <includes.h>

const UINT8 BeegameFighterBitmap[13]={
0x8b,0x08, //width&0x80,height
0x03,
0x0f,
0x03,
0x0f,
0x3f,
0xff,
0x3f,
0x0f,
0x03,
0x0f,
0x03
};

VOID BeegameFighterSvc(BEEGAME_CONTROL *pBeegameCtrl,UINT8 KeyData){
	UINT8  Xdir,Ydir;
	UINT16 Xmovement,Ymovement;
	BEEGAME_FIGHTER *pFighter;
    BEEGAME_BULLET *pBullet;
    MY_MUTEX mutex;
	
	pFighter=&pBeegameCtrl->Fighter;
	if(KeyData==EFI_KEY_LEFT){
	    if(pFighter->CurrentArea.X>1) pFighter->CurrentArea.X-=2;
		else pFighter->CurrentArea.X=0;	
	}
	else if(KeyData==EFI_KEY_RIGHT){
	    if(pFighter->CurrentArea.X<(pBeegameCtrl->Board.Area.W-pFighter->CurrentArea.W-2)) 
	        pFighter->CurrentArea.X+=2;
		else pFighter->CurrentArea.X=pBeegameCtrl->Board.Area.W-pFighter->CurrentArea.W;	
	}
	else if(KeyData==ASCII_SP){
        mutex = OsEnterCritical();
	    BeegameBulletMove(pBeegameCtrl);
		BeegameBeeBulletHitHandler(pBeegameCtrl);
		pBullet=BeegameFreeBulletListBulletGet(pBeegameCtrl);
		if(pBullet!=(BEEGAME_BULLET *)NULL){
			pBullet->CurrentArea.X=pFighter->CurrentArea.X+BEE_FIGHTER_WIDTH/2;
			pBullet->CurrentArea.Y=pFighter->CurrentArea.Y-2;
			pBullet->PreviousArea.X=pFighter->CurrentArea.X+BEE_FIGHTER_WIDTH/2;
			pBullet->PreviousArea.Y=pFighter->CurrentArea.Y-2;
	        BeegameBulletMapCapture(pBeegameCtrl,pBullet);
	        BeegameBulletDraw(pBeegameCtrl,pBullet);
	        BeegameBulletMapDraw(pBeegameCtrl,pBullet);
			BeegameUsedBulletListBulletPut(pBeegameCtrl,pBullet);
	    }
        OsExitCritical(mutex);
		return;
	}  // enject bullet
	else return;
	
	if(pFighter->CurrentArea.X!=pFighter->PreviousArea.X) pFighter->FighterDirty=TRUE;
	if(pFighter->CurrentArea.Y!=pFighter->PreviousArea.Y) pFighter->FighterDirty=TRUE;
	
    if(pFighter->FighterDirty==TRUE){
    	pFighter->FighterDirty=FALSE;
        mutex = OsEnterCritical();
    	BeegameFighterUpdate(pBeegameCtrl);
        OsExitCritical(mutex);
        pBeegameCtrl->Dirty=TRUE;
    }
}

VOID BeegameFighterUpdate(BEEGAME_CONTROL *pBeegameCtrl){
	BEEGAME_FIGHTER *pFighter;

	pFighter=&pBeegameCtrl->Fighter;
    BeegameFighterMapRecovery(pBeegameCtrl);
    pFighter->PreviousArea.X=pFighter->CurrentArea.X;
    pFighter->PreviousArea.Y=pFighter->CurrentArea.Y;
    BeegameFighterMapCapture(pBeegameCtrl);
    BeegameFighterDraw(pBeegameCtrl);
    BeegameFighterMapDraw(pBeegameCtrl);
}

VOID BeegameFighterMapCapture(BEEGAME_CONTROL *pBeegameCtrl){
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pSource;
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pDestination;
	UINT8 Height;	
	BEEGAME_FIGHTER *pFighter;

	pFighter=&pBeegameCtrl->Fighter;
	Height=BEE_FIGHTER_HEIGHT;
	pSource=pBeegameCtrl->Board.pBoardMemory
	        +pBeegameCtrl->Board.Area.W*pFighter->CurrentArea.Y
	        +pFighter->CurrentArea.X;
	pDestination=pFighter->GraphicMemory;
	while(Height!=0){
        PixelArrayCopy(pSource,pDestination,BEE_FIGHTER_WIDTH);
        pSource=pSource+pBeegameCtrl->Board.Area.W;
        pDestination=pDestination+BEE_FIGHTER_WIDTH;
        Height--;
	}
    PixelArrayCopy(pFighter->GraphicMemory,pFighter->RecoveryMemory,pFighter->FighterMemoryLength);
}

VOID BeegameFighterMapDraw(BEEGAME_CONTROL *pBeegameCtrl){
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pSource;
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pDestination;
	UINT8 Height;	
	BEEGAME_FIGHTER *pFighter;

	pFighter=&pBeegameCtrl->Fighter;
	Height=BEE_FIGHTER_HEIGHT;
	pDestination=pBeegameCtrl->Board.pBoardMemory
	        +pBeegameCtrl->Board.Area.W*pFighter->CurrentArea.Y
	        +pFighter->CurrentArea.X;
	pSource=pFighter->GraphicMemory;
	while(Height!=0){
        PixelArrayCopy(pSource,pDestination,BEE_FIGHTER_WIDTH);
        pDestination=pDestination+pBeegameCtrl->Board.Area.W;
        pSource=pSource+BEE_FIGHTER_WIDTH;
        Height--;
	}
}

VOID BeegameFighterMapRecovery(BEEGAME_CONTROL *pBeegameCtrl){
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pSource;
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pDestination;
	UINT8 Height;	
	BEEGAME_FIGHTER *pFighter;

	pFighter=&pBeegameCtrl->Fighter;
	Height=BEE_FIGHTER_HEIGHT;
	pDestination=pBeegameCtrl->Board.pBoardMemory
	        +pBeegameCtrl->Board.Area.W*pFighter->PreviousArea.Y
	        +pFighter->PreviousArea.X;
	pSource=pFighter->RecoveryMemory;
	while(Height!=0){
        PixelArrayCopy(pSource,pDestination,BEE_FIGHTER_WIDTH);
        pDestination=pDestination+pBeegameCtrl->Board.Area.W;
        pSource=pSource+BEE_FIGHTER_WIDTH;
        Height--;
	}
}

VOID BeegameFighterDraw(BEEGAME_CONTROL *pBeegameCtrl){
    UINT8  HeightIndex,ColumnIndex,BitIndex;
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pMemory,*pBitmapStart,*pColMemory;
	UINT8 *pFighterBitmap;
    UINT8 Width;
    UINT8 Height;
    UINT8 BitValue;
    UINT8 BitmapFormat;
	BEEGAME_FIGHTER *pFighter;

	pFighter=&pBeegameCtrl->Fighter;
    pBitmapStart=pFighter->GraphicMemory;
	pFighterBitmap=BeegameFighterBitmap;
    Width=*pFighterBitmap;
    pFighterBitmap++;
    Height=*pFighterBitmap;
    pFighterBitmap++;
    if(Width&0x80) BitmapFormat=1;
    else BitmapFormat=0;
    Width&=0x7f;
    if(BitmapFormat==1){
        for(ColumnIndex=0;ColumnIndex<Width;ColumnIndex++){
            pColMemory=pBitmapStart+ColumnIndex;
            BitIndex=0;
            for(HeightIndex=0;HeightIndex<Height;HeightIndex++){
                pMemory=pColMemory+BEE_FIGHTER_WIDTH*HeightIndex; 
                BitValue=((*pFighterBitmap)<<BitIndex)&0x80;
                if(BitValue!=0) PixelArray256Set(pMemory,GfxPaletteClut[pBeegameCtrl->Fighter.FighterGfx.FontColor],1);
				BitIndex++;
	            if(BitIndex==8){
	                pFighterBitmap++;
	                BitIndex=0;
	            }
            }
            if(BitIndex!=0) pFighterBitmap++;
        }
    }	
}

