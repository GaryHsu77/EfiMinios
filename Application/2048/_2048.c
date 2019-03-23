#include "2048.h"

EFI_GUID GraphicsOutputProtocol = {0x9042a9de,0x23dc,0x4a38,0x96,0xfb,0x7a,0xde,0xd0,0x80, 0x51, 0x6a };
EFI_GUID SimpleTextOutputInterface = {0x387477c2,0x69c7,0x11d2,0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b};
EFI_GUID SimpleTextInputGuid = {0x387477c1, 0x69c7, 0x11d2, 0x8e, 0x39, 0x0, 0xa0, 0xc9, 0x69, 0x72, 0x3b };
EFI_GUID PegaBSProtocol_guid = PEGA_BS_PROTOCOL_GUID;

EFI_GRAPHICS_OUTPUT_BLT_PIXEL white={0xff,0xff,0xff,0};
EFI_GRAPHICS_OUTPUT_BLT_PIXEL red={0,0,0xff,0};
EFI_GRAPHICS_OUTPUT_BLT_PIXEL black={0,0,0,0};
EFI_GRAPHICS_OUTPUT_BLT_PIXEL blue={0xff,0,0,0};
EFI_GRAPHICS_OUTPUT_BLT_PIXEL color;
EFI_GRAPHICS_OUTPUT_PROTOCOL *GOP;
SIMPLE_TEXT_OUTPUT_INTERFACE *TOI;
PEGA_BS_PROTOCOL *PegaBSProtocol;
SIMPLE_INPUT_INTERFACE *ConIn ;

EFI_SYSTEM_TABLE *GST;
EFI_RUNTIME_SERVICES *GRS;
EFI_BOOT_SERVICES *GBS;

UINTN leftTopX = 200;
UINTN leftTopY = 100+35;
UINTN lastx = 0;
UINTN lasty = 0;
UINTN falseNum = 0;
block block44[4][4];

void initializeBlock ();
void newBlock ();
void falseCheck ();

EFI_STATUS game (EFI_HANDLE Handle, EFI_SYSTEM_TABLE *ST)
{
		UINTN xl, yl, esc;
        EFI_STATUS Status ;	
		EFI_INPUT_KEY *Key ;
		GST = ST;
		GRS = ST->RuntimeServices;
		GBS = ST->BootServices;
        Status = GST->BootServices->LocateProtocol ( &GraphicsOutputProtocol, NULL, &GOP) ;

		InitializeLib(Handle,GST);
        xl = GOP->Mode->Info->HorizontalResolution ;
        yl = GOP->Mode->Info->VerticalResolution ;
		drawBlock(1,0,0,xl,yl);
		drawBackground();
		drawBlock(1,leftTopX,leftTopY,400,400);
		initializeBlock();
		drawBox();
		Status = GST->BootServices ->LocateProtocol ( &SimpleTextInputGuid, NULL, &ConIn) ;
        esc=0;
		
		while(esc==0){
			while ( ConIn->ReadKeyStroke (ConIn,Key) != EFI_SUCCESS )   ;
			switch (Key->ScanCode) {
            case 0x17:
                esc=1;
                break;
            case 0x01://up
                blockMoveUp ();
				drawBox();
				falseCheck();
                break;
			case 0x02://down
                blockMoveDown ();
				drawBox();
				falseCheck();
                break;
			case 0x04://left
                blockMoveLeft ();
				drawBox();
				falseCheck();
                break;
			case 0x03://right
                blockMoveRight ();
				drawBox();
				falseCheck();
                break;
			default:
			    esc=1;
                break;
           }
		}
        return EFI_SUCCESS ;
}

void initializeBlock ()
{
		UINTN i ,j; 
		for(i=0;i<4;i++){
			for(j=0;j<4;j++){
				block44[i][j].empty=0;
				block44[i][j].value=0;
			}
		}
		for(i=0;i<3;i++){
			newBlock();
		}
}

void newBlock ()
{
    UINTN tmp, xTmp, yTmp, valTmp, fcont, count, i ,j;
	EFI_STATUS Status ;	
	Status = GST->BootServices->LocateProtocol ( &GraphicsOutputProtocol, NULL, &GOP) ;
	valTmp=random(4);
	fcont=0;
	count=0;

	if(valTmp==0){
		valTmp=2;
    }else if((valTmp%2)!=0){
   	    valTmp+=1;
    };
	
	tmp=random(17);
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			fcont+=1;		
			if(fcont==tmp){
				xTmp=i;
				yTmp=j;
			}
		}
	}
	fcont=0;
	while(block44[xTmp][yTmp].empty==1){
		if(count>10){
			for(i=0;i<4;i++){
				for(j=0;j<4;j++){
					if(block44[i][j].empty==0){
						xTmp=i;
						yTmp=j;
					}
				}
			}
		}else{
			tmp=random(17);
			count+=1;
			fcont=0;
			for(i=0;i<4;i++){
				for(j=0;j<4;j++){
					if(fcont==tmp){
						xTmp=i;
						yTmp=j;
					}fcont+=1;
				}
			}
		}
	}
	block44[xTmp][yTmp].value=valTmp;
	GOP->Blt (GOP,&white,EfiUgaVideoFill,0,0,leftTopX+(xTmp*100),leftTopY+(yTmp*100),100,100,0) ;
	drawNum(xTmp,yTmp,valTmp);
	drawGNum(leftTopX+(xTmp*100),leftTopY+(yTmp*100),valTmp);
	
}

void falseCheck (){
	INTN count, i ,j;
	EFI_INPUT_KEY *Key ;
	count=0;
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			if(block44[i][j].empty==1)count+=1;
		}
	}
	testValue(count);
	if((count>=16)&&(falseNum==1)){
		drawOver();
		while ( ConIn->ReadKeyStroke (ConIn,Key) != EFI_SUCCESS )   ;
		reset();
		falseNum=0;
	}else if((count>=16)&&(falseNum==0)){
		falseNum=1;
	}
	else if((count<16)){
		falseNum=0;
	}
}