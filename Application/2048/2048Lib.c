VOID G2048BlkMapDraw(GAME2048_CONTROL *p2048gameCtrl,GAME2048_BLK *p2048gameBlk)
{
	//GDB : Draw assign blk to broad
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pSource;
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pDestination;
	UINT8 Height;	
	
	Height=BLK_HEIGHT;
	pDestination=p2048gameCtrl->Board.pBoardMemory
	             +p2048gameCtrl->Board.Area.W*p2048gameBlk->CurrentArea.Y
	             +p2048gameBlk->CurrentArea.X;
	pSource=p2048gameBlk->GraphicMemory;
	while(Height!=0){
        PixelArrayCopy(pSource,pDestination,BLK_WIDTH);
        pDestination=pDestination+p2048gameCtrl->Board.Area.W;
        pSource=pSource+BLK_WIDTH;
        Height--;
	}
}

VOID G2048BlkBmpDraw(GAME2048_CONTROL *p2048gameCtrl,GAME2048_BLK *p2048gameBlk)
{
	//GDB : draw blk bitmap.
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pBitmapStart;
	UINT8  i,j,tmp;ory,*pBitmapStart,*pColMemory;
	UINT32 i, j, h_tmp, w_tmp;
	UINT32 height = *(UINT32*)&pic[Height_OFFSET];
	UINT32 width  = *(UINT32*)&pic[Width_OFFSET];
	UINT32 size  = *(UINT32*)&pic[Size_OFFSET];
	UINT8* bmp = &pic[PIX_OFFSET];
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pixel_array;	
    
    pBitmapStart=p2048gameBlk->GraphicMemory;
	switch (p2048gameBlk->BlkNum) {
        case 2:
            pBeesBitmap=BikBmp_2;
			break;
        case 4://up
			pBeesBitmap=BikBmp_4;
			break;
		case 8://up
            pBeesBitmap=BikBmp_8;
			break;
		case 16://up
            pBeesBitmap=BikBmp_16;
			break;
		case 32://up
            pBeesBitmap=BikBmp_32
			break;
		case 64://up
            pBeesBitmap=BikBmp_64;
			break;
		case 128://up
            pBeesBitmap=BikBmp_128;
			break;
		case 256://up
            pBeesBitmap=BikBmp_256;
			break;
		case 512://up
            pBeesBitmap=BikBmp_512;
			break;
		case 1024://up
            pBeesBitmap=BikBmp_1024;
			break;
		case 2048://up
            pBeesBitmap=BikBmp_2048;
			while ( ConIn->ReadKeyStroke (ConIn,Key) != EFI_SUCCESS )   ;
			drawWin ();
			while ( ConIn->ReadKeyStroke (ConIn,Key) != EFI_SUCCESS )   ;
			reset();
            break;
		default:
			pBeesBitmap=BikBmp_Null;
            break;
    }
	
    tmp = height - 1;
	for(i=0;i<height;i++){
		for(j=0;j<width;j++) PixelArray256Set(pBitmapStart+j,bmp[j+tmp*width],1);
		pBitmapStart=pBitmapStart+pWindow->Outline.OuterArea.W;
		tmp--;
	}
}

VOID G2048BlkMapCapture(GAME2048_CONTROL *p2048gameCtrl,GAME2048_BLK *p2048gameBlk){
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pSource;
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pDestination;
	UINT8 Height;	
	
	Height=BLK_HEIGHT;
	pSource=p2048gameCtrl->Board.pBoardMemory
	        +p2048gameCtrl->Board.Area.W*p2048gameBlk->CurrentArea.Y
	        +p2048gameBlk->CurrentArea.X;
	pDestination=p2048gameBlk->GraphicMemory;
	while(Height!=0){
		PixelArrayCopy(pSource,pDestination,BLK_WIDTH);
        pSource=pSource+p2048gameCtrl->Board.Area.W;
        pDestination=pDestination+BLK_WIDTH;
        Height--;
	}
    PixelArrayCopy(p2048gameBlk->GraphicMemory,p2048gameBlk->RecoveryMemory,p2048gameBlk->BlkMemoryLength);
}