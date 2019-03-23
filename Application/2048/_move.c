#include "2048.h"

UINTN newBlkCount = 0;
void downMerge(UINTN x, UINTN y);

void blockMoveUp ()
{
		UINTN i,j,tmpi,tmpj,tmpd; 
		EFI_STATUS Status ;	
		EFI_INPUT_KEY *Key ;
		Status = ST->BootServices->LocateProtocol ( &GraphicsOutputProtocol, NULL, &GOP) ;
		for(i=0;i<4;i++){
			for(j=0;j<4;j++){
				if(block44[i][j].empty==1){
					//while ( ConIn->ReadKeyStroke (ConIn,Key) != EFI_SUCCESS )   ;
					tmpi=i;
					tmpj=j;
					if(tmpj!=0){
						while(block44[i][tmpj-1].empty==0){
							tmpj-=1;
							if(tmpj==0)break;
						}
					}
					if(j!=tmpj){
						GOP->Blt (GOP,&black,EfiUgaVideoFill,0,0,leftTopX+(i*100),leftTopY+(j*100),100,100,0) ;
						tmpd=block44[i][j].value;
						block44[i][j].empty=0;
						block44[i][j].value=0;
						GOP->Blt (GOP,&white,EfiUgaVideoFill,0,0,leftTopX+(tmpi*100),leftTopY+(tmpj*100),100,100,0) ;
						drawNum(tmpi,tmpj,tmpd);
						drawGNum(leftTopX+(tmpi*100),leftTopY+(tmpj*100),tmpd);
						newBlkCount+=1;
						falseNum=0;
						//testValue(444);
						//while ( ConIn->ReadKeyStroke (ConIn,Key) != EFI_SUCCESS )   ;
						upMerge(tmpi,tmpj);
					}
					//testValue(333);
					//while ( ConIn->ReadKeyStroke (ConIn,Key) != EFI_SUCCESS )   ;
					upMerge(i,j);
					
				}
			}
		}
		if(newBlkCount>0){
			newBlock ();
		}
		newBlkCount=0;
}

void upMerge(UINTN x, UINTN y)
{
		EFI_STATUS Status ;	
		UINTN tmpGd; 
		static CHAR16 MyStr2[3];
		EFI_INPUT_KEY *Key ;
		Status = ST->BootServices->LocateProtocol ( &GraphicsOutputProtocol, NULL, &GOP) ;
		if(y!=0){
			if((block44[x][y].value==block44[x][y-1].value)&&(block44[x][y].empty==1)){
				GOP->Blt (GOP,&black,EfiUgaVideoFill,0,0,leftTopX+(x*100),leftTopY+(y*100),100,100,0) ;
				tmpGd=(block44[x][y].value*2);
				block44[x][y].empty=0;
				block44[x][y].value=0;
				drawNum(x,y-1,tmpGd);
				//testValue(444);
				//testValue(x);
				//testValue(y);
				//testValue(leftTopX+(x*100));
				//testValue(leftTopY+((y-1)*100));
				//while ( ConIn->ReadKeyStroke (ConIn,Key) != EFI_SUCCESS )   ;
				drawGNum(leftTopX+(x*100),leftTopY+((y-1)*100),tmpGd);
				falseNum=0;
				newBlkCount+=1;
			}
		}
}

void blockMoveDown ()
{
		UINTN tmpi,tmpj,tmpd; 
		INTN i,j;
		EFI_STATUS Status ;	
		EFI_INPUT_KEY *Key ;
		Status = ST->BootServices->LocateProtocol ( &GraphicsOutputProtocol, NULL, &GOP) ;
		for(i=0;i<4;i++){
			for(j=3;j>=0;j--){
				if(block44[i][j].empty==1){
					tmpi=i;
					tmpj=j;
					if(tmpj!=3){
						while(block44[i][tmpj+1].empty==0){
							tmpj+=1;
							if(tmpj==3)break;
						}
					}
					if(j!=tmpj){
						GOP->Blt (GOP,&black,EfiUgaVideoFill,0,0,leftTopX+(i*100),leftTopY+(j*100),100,100,0) ;
						tmpd=block44[i][j].value;
						block44[i][j].empty=0;
						block44[i][j].value=0;
						GOP->Blt (GOP,&white,EfiUgaVideoFill,0,0,leftTopX+(tmpi*100),leftTopY+(tmpj*100),100,100,0) ;
						drawNum(tmpi,tmpj,tmpd);
						drawGNum(leftTopX+(tmpi*100),leftTopY+(tmpj*100),tmpd);
						newBlkCount+=1;
						falseNum=0;
						downMerge(tmpi,tmpj);
					}
					downMerge(i,j);			
				}
			}
		}
		if(newBlkCount>0){
			newBlock ();
		}
		newBlkCount=0;
}

void downMerge(UINTN x, UINTN y)
{
		EFI_STATUS Status ;	
		UINTN tmpGd; 
		EFI_INPUT_KEY *Key ;
		static CHAR16 MyStr2[3];
		Status = ST->BootServices->LocateProtocol ( &GraphicsOutputProtocol, NULL, &GOP) ;
		if(y!=3){
			if((block44[x][y].value==block44[x][y+1].value)&&(block44[x][y].empty==1)){
				GOP->Blt (GOP,&black,EfiUgaVideoFill,0,0,leftTopX+(x*100),leftTopY+(y*100),100,100,0) ;
				tmpGd=(block44[x][y].value*2);
				block44[x][y].empty=0;
				block44[x][y].value=0;
				drawNum(x,y+1,tmpGd);
				drawGNum(leftTopX+(x*100),leftTopY+((y+1)*100),tmpGd);
				falseNum=0;
				newBlkCount+=1;
			}
		}
}

void blockMoveLeft ()
{
		INTN i,j,tmpi,tmpj,tmpd;
		EFI_STATUS Status ;	
		EFI_INPUT_KEY *Key ;
		Status = ST->BootServices->LocateProtocol ( &GraphicsOutputProtocol, NULL, &GOP) ;
		for(i=0;i<4;i++){
			for(j=3;j>=0;j--){
				if(block44[i][j].empty==1){
					tmpi=i;
					tmpj=j;
					if(tmpi!=0){
						while(block44[tmpi-1][j].empty==0){
							tmpi-=1;
							if(tmpi==0)break;
						}
					}
					if(i!=tmpi){
						GOP->Blt (GOP,&black,EfiUgaVideoFill,0,0,leftTopX+(i*100),leftTopY+(j*100),100,100,0) ;
						tmpd=block44[i][j].value;
						block44[i][j].empty=0;
						block44[i][j].value=0;
						GOP->Blt (GOP,&white,EfiUgaVideoFill,0,0,leftTopX+(tmpi*100),leftTopY+(tmpj*100),100,100,0) ;
						drawNum(tmpi,tmpj,tmpd);
						drawGNum(leftTopX+(tmpi*100),leftTopY+(tmpj*100),tmpd);
						newBlkCount+=1;
						falseNum=0;
						leftMerge(tmpi,tmpj);
					}
					leftMerge(tmpi,tmpj);			
				}
			}
		}
		if(newBlkCount>0){
			newBlock ();
		}
		newBlkCount=0;
}

void leftMerge(UINTN x, UINTN y)
{
		EFI_STATUS Status ;	
		UINTN tmpGd; 
		EFI_INPUT_KEY *Key ;
		static CHAR16 MyStr2[3];
		Status = ST->BootServices->LocateProtocol ( &GraphicsOutputProtocol, NULL, &GOP) ;
		if(x!=0){
			if((block44[x][y].value==block44[x-1][y].value)&&(block44[x][y].empty==1)){
				GOP->Blt (GOP,&black,EfiUgaVideoFill,0,0,leftTopX+(x*100),leftTopY+(y*100),100,100,0) ;
				tmpGd=(block44[x][y].value*2);
				block44[x][y].empty=0;
				block44[x][y].value=0;
				drawNum(x-1,y,tmpGd);
				drawGNum(leftTopX+((x-1)*100),leftTopY+((y)*100),tmpGd);
				falseNum=0;
				newBlkCount+=1;
			}
		}
}

void blockMoveRight ()
{
		INTN i,j,tmpi,tmpj,tmpd;
		EFI_STATUS Status ;	
		EFI_INPUT_KEY *Key ;
		Status = ST->BootServices->LocateProtocol ( &GraphicsOutputProtocol, NULL, &GOP) ;
		for(i=3;i>=0;i--){
			for(j=3;j>=0;j--){
				if(block44[i][j].empty==1){
					tmpi=i;
					tmpj=j;
					if(tmpi!=3){
						while(block44[tmpi+1][j].empty==0){
							tmpi+=1;
							if(tmpi==3)break;
						}
					}
					if(i!=tmpi){
						GOP->Blt (GOP,&black,EfiUgaVideoFill,0,0,leftTopX+(i*100),leftTopY+(j*100),100,100,0) ;
						tmpd=block44[i][j].value;
						block44[i][j].empty=0;
						block44[i][j].value=0;
						GOP->Blt (GOP,&white,EfiUgaVideoFill,0,0,leftTopX+(tmpi*100),leftTopY+(tmpj*100),100,100,0) ;
						drawNum(tmpi,tmpj,tmpd);
						drawGNum(leftTopX+(tmpi*100),leftTopY+(tmpj*100),tmpd);
						falseNum=0;
						newBlkCount+=1;
						rightMerge(tmpi,tmpj);
					}
					rightMerge(tmpi,tmpj);			
				}
			}
		}
		if(newBlkCount>0){
			newBlock ();
		}
		newBlkCount=0;
}

void rightMerge(UINTN x, UINTN y)
{
		EFI_STATUS Status ;	
		UINTN tmpGd; 
		EFI_INPUT_KEY *Key ;
		static CHAR16 MyStr2[3];
		Status = ST->BootServices->LocateProtocol ( &GraphicsOutputProtocol, NULL, &GOP) ;
		if(x!=3){
			if((block44[x][y].value==block44[x+1][y].value)&&(block44[x][y].empty==1)){
				GOP->Blt (GOP,&black,EfiUgaVideoFill,0,0,leftTopX+(x*100),leftTopY+(y*100),100,100,0) ;
				tmpGd=(block44[x][y].value*2);
				block44[x][y].empty=0;
				block44[x][y].value=0;
				drawNum(x+1,y,tmpGd);
				drawGNum(leftTopX+((x+1)*100),leftTopY+((y)*100),tmpGd);
				newBlkCount+=1;
				falseNum=0;
			}
		}
}