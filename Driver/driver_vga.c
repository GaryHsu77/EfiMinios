#include <includes.h>

static RGBQUAD bitmap_rgb_table[256];
static UINT32 **bitmap_context=NULL;
VGA_CONTROL *pOsDriverVga;

VOID GetBitmapColorTable(UINT8* bmp)
{
	UINTN i, c=0;

	for(i=0;i<256;i++){
		bitmap_rgb_table[i].rgbBlue=bmp[0x36+c];c++;
		bitmap_rgb_table[i].rgbGreen=bmp[0x36+c];c++;
		bitmap_rgb_table[i].rgbRed=bmp[0x36+c];c++;
		bitmap_rgb_table[i].rgbReserved=bmp[0x36+c];c++;
	}
}

VOID VgaInit(VOID) 
{
	EFI_STATUS Status;
	Status = gBS->AllocatePool(EfiBootServicesData,sizeof(VGA_CONTROL),&pOsDriverVga);
	if(Status != EFI_SUCCESS){
		return;
	}
	pOsDriverVga->EFI_GOP=GOP;
    pOsDriverVga->pVideoMemory=(UINT8 *)NULL;
    pOsDriverVga->Area.X=0;
    pOsDriverVga->Area.Y=0;
	pOsDriverVga->Area.H=GOP->Mode->Info->VerticalResolution ;
    pOsDriverVga->Area.W=GOP->Mode->Info->HorizontalResolution ;
    pOsDriverVga->BitsPerPixel=8; //GDB : no use.
    //GDB pOsDriverVga->pVideoMemory=0;
	Status = gBS->AllocatePool(EfiBootServicesData,pOsDriverVga->Area.H*pOsDriverVga->Area.W*sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL),&pOsDriverVga->pPixMemory);
    if(Status != EFI_SUCCESS)return;
	GetBitmapColorTable((UINT8*)&DeskBackground); //GDB : MAKE SURE BMP HAS COLOR TABLE.
	
	SystemGuiStringPrint(L">>> VgaInit end      <<<<<<<<<<\n");
}

EFI_GRAPHICS_OUTPUT_BLT_PIXEL Bmp2Rgb(UINT8 bmp)
{

	UINT32 bitmap = RGB(bitmap_rgb_table[bmp].rgbRed,bitmap_rgb_table[bmp].rgbGreen,bitmap_rgb_table[bmp].rgbBlue);
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL Color;
	Color.Blue = (bitmap >>16) & 0x0FF;
	Color.Green = (bitmap >>8) & 0x0FF;
	Color.Red = (bitmap >>0) & 0x0FF;
	Color.Reserved = 0;
										  
	return Color;
}

VOID PixelBmpArraySet(EFI_GRAPHICS_OUTPUT_BLT_PIXEL* pixArr, UINT8* pic)
{
	UINT16 i, j, h_tmp, w_tmp;
	UINT32 height = *(UINT32*)&pic[Height_OFFSET];
	UINT32 width  = *(UINT32*)&pic[Width_OFFSET];
	UINT32 size  = *(UINT32*)&pic[Size_OFFSET];
	UINT8* bmp = &pic[PIX_OFFSET];
	//EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pixel_array;
		
	gBS->FreePool(pixArr);
	gBS->AllocatePool(EfiBootServicesData,width*height*sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL),&pixArr);

	if(size>height*width)
		w_tmp=(width+((size-(height*width))/height));
	else	
		w_tmp=width;
		
	h_tmp = height-1;
	for(i=0;i<height;i++){
		for(j=0;j<w_tmp;j++){
			if(j<=width){
				EFI_GRAPHICS_OUTPUT_BLT_PIXEL Color;
				Color = Bmp2Rgb(bmp[w_tmp*i+j]);
				pixArr[h_tmp*width+j]= Color;
				//GOP->Blt(GOP,&Color,EfiBltVideoFill,0,0,Start_x+j,Start_y+i,1,1,0);
			}
		}
		h_tmp--;
	}
}

VOID PixelArrayDraw(EFI_GRAPHICS_OUTPUT_BLT_PIXEL* pixArr, UINT16 Start_x, UINT16 Start_y, UINT32 width, UINT32 height)
{
	EFI_STATUS Status;
	Status = GOP->Blt(GOP,pixArr,EfiBltBufferToVideo,0,0,Start_x,Start_y,width,height,width*sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));
	if(Status != EFI_SUCCESS){
		gST->ConOut->SetCursorPosition(gST->ConOut,0,0);
		GDP(L"GOP draw error.(Maybe out of range.)\n", Status);
		return;
	}
}

VOID BmpDraw(UINT8* pic,UINT32 psize, UINT16 Start_x, UINT16 Start_y, BOOLEAN DrawOsd)
{
	UINT32 i, j, h_tmp, w_tmp;
	UINT32 height = *(UINT32*)&pic[Height_OFFSET];
	UINT32 width  = *(UINT32*)&pic[Width_OFFSET];
	UINT32 size  = *(UINT32*)&pic[Size_OFFSET];
	UINT8* bmp = &pic[PIX_OFFSET];
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pixel_array;
		
	gBS->AllocatePool(EfiBootServicesData,width*height*sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL),&pixel_array);

	if(size>height*width)
		w_tmp=(width+((size-(height*width))/height));
	else	
		w_tmp=width;
		
	h_tmp = height-1;
	for(i=0;i<height;i++){
		for(j=0;j<w_tmp;j++){
			if(j<=width){
				EFI_GRAPHICS_OUTPUT_BLT_PIXEL Color;
				Color = Bmp2Rgb(bmp[w_tmp*i+j]);
				pixel_array[h_tmp*width+j]= Color;
				//GOP->Blt(GOP,&Color,EfiBltVideoFill,0,0,Start_x+j,Start_y+i,1,1,0);
			}
		}
		h_tmp--;
	}
	GOP->Blt(GOP,pixel_array,EfiBltBufferToVideo,0,0,Start_x,Start_y,width,height,width*sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));
	if(DrawOsd){
		UINT32 c = 0;
		for(i=0;i<height;i++){
			c = 0;
			for(j=OsdCtrl.ScreenArea.W*Start_y+Start_x;j<=OsdCtrl.ScreenArea.W*Start_y+Start_x+width;j++){
				OsdCtrl.pPixMemory[j]=pixel_array[i*width+c];
				c++;
			}
			Start_y++;
		}
	}
	gBS->FreePool(pixel_array);
}

VOID BoxDraw(UINT8 color, UINT32 Width, UINT32 Height, UINT16 x, UINT16 y)
{
	EFI_STATUS Status;
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL Color = Bmp2Rgb(color);
	if(GOP) {
		Status = GOP->Blt(GOP,&Color,EfiBltVideoFill,0,0,x,y,Width,Height,0);
		// if(x>500){
		// gST->ConOut->SetCursorPosition(gST->ConOut,0,0);
		// GDP(L"%d, %d, %d, %d", x, y, Width, Height);
		// while(1){};
		// }
	}
}

VOID PixelArrayCopy(EFI_GRAPHICS_OUTPUT_BLT_PIXEL* source, EFI_GRAPHICS_OUTPUT_BLT_PIXEL* dest, UINT32 len)
{
	UINT32 i;
	for(i=0;i<len;i++){
		dest[i]=source[i];
	}
}

VOID PixelArraySet(EFI_GRAPHICS_OUTPUT_BLT_PIXEL* source, EFI_GRAPHICS_OUTPUT_BLT_PIXEL color, UINT32 len)
{
	UINT32 i;
	for(i=0;i<len;i++){
		source[i]=color;
	}
}

VOID PixelArray256Set(EFI_GRAPHICS_OUTPUT_BLT_PIXEL* source, UINT8 color, UINT32 len)
{
	UINT32 i;
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL Color = Bmp2Rgb(color);
	for(i=0;i<len;i++){
		source[i]=Color;
	}
}



