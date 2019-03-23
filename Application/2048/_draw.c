#include "2048.h"
#include "2048pic.h"

void drawNum (UINTN x, UINTN y, UINTN v)
{
		EFI_STATUS Status ;	
		static CHAR16 MyStr2[3];
		Status = ST->BootServices->LocateProtocol ( &SimpleTextOutputInterface, NULL, &TOI) ;
		TOI->SetCursorPosition(TOI, 30+(x*13), 7+(y*5));
		TOI->SetAttribute(TOI,EFI_TEXT_ATTR(EFI_BLUE,EFI_WHITE));
		ValueToString(MyStr2,FALSE,v);
	    //TOI->OutputString(TOI,MyStr2);
		block44[x][y].empty=1;
		block44[x][y].value=v;
		TOI->SetCursorPosition(TOI, 1, 1);
		//drawBlock(1,0,0,800,90);
}

void drawGNum (UINTN x, UINTN y, UINTN v)
{
		EFI_STATUS Status ;	
		EFI_INPUT_KEY *Key ;
		Status = GST->BootServices->LocateProtocol (&PegaBSProtocol_guid,NULL,&PegaBSProtocol) ;
		switch (v) {
            case 2:
                PegaBSProtocol->PostLogoBS->PngDraw(num_2,num_2_size,x,y);
                break;
            case 4://up
                PegaBSProtocol->PostLogoBS->PngDraw(num_4,num_4_size,x,y);
                break;
			case 8://up
                PegaBSProtocol->PostLogoBS->PngDraw(num_8,num_8_size,x,y);
                break;
			case 16://up
                PegaBSProtocol->PostLogoBS->PngDraw(num_16,num_16_size,x,y);
                break;
			case 32://up
                PegaBSProtocol->PostLogoBS->PngDraw(num_32,num_32_size,x,y);
                break;
			case 64://up
                PegaBSProtocol->PostLogoBS->PngDraw(num_64,num_64_size,x,y);
                break;
			case 128://up
                PegaBSProtocol->PostLogoBS->PngDraw(num_128,num_128_size,x,y);
                break;
			case 256://up
                PegaBSProtocol->PostLogoBS->PngDraw(num_256,num_256_size,x,y);
                break;
			case 512://up
                PegaBSProtocol->PostLogoBS->PngDraw(num_512,num_512_size,x,y);
                break;
			case 1024://up
                PegaBSProtocol->PostLogoBS->PngDraw(num_1024,num_1024_size,x,y);
                break;
			case 2048://up
                PegaBSProtocol->PostLogoBS->PngDraw(num_2048,num_2048_size,x,y);
				while ( ConIn->ReadKeyStroke (ConIn,Key) != EFI_SUCCESS )   ;
				drawWin ();
				while ( ConIn->ReadKeyStroke (ConIn,Key) != EFI_SUCCESS )   ;
				reset();
                break;
			default:
			    drawNum (x, y, v);
                break;
           }		
}

void drawOver ()
{
		EFI_STATUS Status ;	
		Status = GST->BootServices->LocateProtocol (&PegaBSProtocol_guid,NULL,&PegaBSProtocol) ;
        PegaBSProtocol->PostLogoBS->PngDraw(gameover,gameover_size,leftTopX+2,leftTopY+2);   
}

void drawWin ()
{
		EFI_STATUS Status ;	
		Status = GST->BootServices->LocateProtocol (&PegaBSProtocol_guid,NULL,&PegaBSProtocol) ;
        PegaBSProtocol->PostLogoBS->PngDraw(win,win_size,leftTopX+2,leftTopY+2);   
}

void drawTitle ()
{
		drawBlock(3,leftTopX+10,15,80,5);
		drawBlock(3,leftTopX+90,15,5,35);
		drawBlock(3,leftTopX+10,50,80,5);
		drawBlock(3,leftTopX+10,50,5,35);
		drawBlock(3,leftTopX+10,85,80,5);
		
		drawBlock(3,leftTopX+110,15,80,5);
		drawBlock(3,leftTopX+190,15,5,70);
		drawBlock(3,leftTopX+110,15,5,70);
		drawBlock(3,leftTopX+110,85,80,5);
		
		drawBlock(3,leftTopX+210,15,5,35);
		drawBlock(3,leftTopX+290,15,5,85);
		drawBlock(3,leftTopX+210,50,80,5);
		
		drawBlock(3,leftTopX+310,15,80,5);
		drawBlock(3,leftTopX+390,15,5,70);
		drawBlock(3,leftTopX+310,50,80,5);
		drawBlock(3,leftTopX+310,15,5,70);
		drawBlock(3,leftTopX+310,85,80,5);
}

void drawBox ()
{
		drawBlock(2,leftTopX,leftTopY,5,400);
		drawBlock(2,leftTopX+100,leftTopY,5,400);
		drawBlock(2,leftTopX+200,leftTopY,5,400);
		drawBlock(2,leftTopX+300,leftTopY,5,400);
		drawBlock(2,leftTopX+400,leftTopY,5,400);
		drawBlock(2,leftTopX,leftTopY,400,5);
		drawBlock(2,leftTopX,leftTopY+100,400,5);
		drawBlock(2,leftTopX,leftTopY+200,400,5);
		drawBlock(2,leftTopX,leftTopY+300,400,5);
		drawBlock(2,leftTopX,leftTopY+400,400+5,5);
}

void drawBackground ()
{
		EFI_STATUS Status ;	
		Status = GST->BootServices->LocateProtocol (&PegaBSProtocol_guid,NULL,&PegaBSProtocol) ;
		PegaBSProtocol->PostLogoBS->PngDraw(background,background_size,(leftTopX-50),0);
}

void drawBlock(UINTN black,UINTN x,UINTN y,UINTN width,UINTN high)
{
		EFI_STATUS Status ;
		Status = ST->BootServices->LocateProtocol ( &GraphicsOutputProtocol, NULL, &GOP) ;
		if(black==1){
			GOP->Blt (GOP,&black,EfiUgaVideoFill,0,0,x,y,width,high,0) ;
		}else if(black==0){
			GOP->Blt (GOP,&white,EfiUgaVideoFill,0,0,x,y,width,high,0) ;
		}else if(black==2){
			GOP->Blt (GOP,&blue,EfiUgaVideoFill,0,0,x,y,width,high,0) ;
		}else{
			GOP->Blt (GOP,&blue,EfiUgaVideoFill,0,0,x,y,width,high,0) ;
		}
}

void testValue (UINTN x)
{
		EFI_STATUS Status ;	
		static CHAR16 MyStr2[3];
		Status = ST->BootServices->LocateProtocol ( &SimpleTextOutputInterface, NULL, &TOI) ;
		TOI->SetCursorPosition(TOI, 1, 1);
		TOI->SetAttribute(TOI,EFI_TEXT_ATTR(EFI_BLUE,EFI_WHITE));
		TOI->OutputString(TOI,L" test=");
		ValueToString(MyStr2,FALSE,x);
	    TOI->OutputString(TOI,MyStr2);
		TOI->OutputString(TOI,L" ");
}

void reset ()
{
		EFI_STATUS Status ;	
		UINTN xl, yl;
		Status = ST->BootServices->LocateProtocol ( &GraphicsOutputProtocol, NULL, &GOP) ;
		xl = GOP->Mode->Info->HorizontalResolution ;
        yl = GOP->Mode->Info->VerticalResolution ;
		drawBlock(1,leftTopX,leftTopY,400,400);
		initializeBlock();
		drawBox();
}
