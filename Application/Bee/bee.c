#include <includes.h>

#define DEBUG_BEE 0

const UINT8 BeeStringRestart[]="RESTART";
const UINT8 BeeStringClose[]="CLOSE";
const UINT8 BeeStringGameOver[]="GAME OVER";
const UINT8 BeeStringHit[]="HIT: ";

VOID BeegameInit(BEEGAME_CONTROL *pBeegameCtrl){
	UINT8 i;
	EFI_STATUS Status;
	
	pBeegameCtrl->TaskState=BeetaskIdleState;
    if(BoardCreat(&pBeegameCtrl->Board,BEE_WINDOW_WIDTH,BEE_WINDOW_HEIGHT)==FALSE) return;
    pBeegameCtrl->Board.Area.X=0;
    pBeegameCtrl->Board.Area.Y=15+5;
    pBeegameCtrl->Board.Gfx.FgColor=GFX_COLOR_BLACK;
    pBeegameCtrl->Board.Gfx.BgColor=GFX_COLOR_BLACK;
    pBeegameCtrl->Board.Gfx.FontColor=GFX_COLOR_WHITE;
    BoardMemoryReset(&pBeegameCtrl->Board);
    pBeegameCtrl->WdBoard.DeviceNumberLeft=BEE_WDN_BOARD;
    pBeegameCtrl->WdBoard.DeviceNumberMiddle=BEE_WDN_BOARD;
    pBeegameCtrl->WdBoard.DeviceNumberRight=BEE_WDN_BOARD;
	pBeegameCtrl->WdBoard.Type=WINDOW_DEVICE_BOARD;
	pBeegameCtrl->WdBoard.pDevice=(UINT32 *)(&pBeegameCtrl->Board);
	
	pBeegameCtrl->Fighter.FighterMemoryLength=BEE_FIGHTER_WIDTH*BEE_FIGHTER_HEIGHT;
    Status = gBS->AllocatePool(EfiBootServicesData,sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL)*pBeegameCtrl->Fighter.FighterMemoryLength,&pBeegameCtrl->Fighter.GraphicMemory);
	if(Status != EFI_SUCCESS){
		GDP(L"ERROR : pBeegameCtrl's Fighter GraphicMemory allocated buffer fail.");
		return;
	}
    Status = gBS->AllocatePool(EfiBootServicesData,sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL)*pBeegameCtrl->Fighter.FighterMemoryLength,&pBeegameCtrl->Fighter.RecoveryMemory);
	if(Status != EFI_SUCCESS){
		GDP(L"ERROR : pBeegameCtrl's Fighter RecoveryMemory allocated buffer fail.");
		return;
	}
	if(pBeegameCtrl->Fighter.GraphicMemory==(EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)NULL) return;
    if(pBeegameCtrl->Fighter.RecoveryMemory==(EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)NULL) return;
    pBeegameCtrl->Fighter.FighterDirty=FALSE;
    
	for(i=0;i<BBE_BEES_MAX;i++){
		pBeegameCtrl->Bees[i].BeesMemoryLength=BEE_BEES_WIDTH*BEE_BEES_HEIGHT;
		Status = gBS->AllocatePool(EfiBootServicesData,sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL)*pBeegameCtrl->Bees[i].BeesMemoryLength,&pBeegameCtrl->Bees[i].GraphicMemory);
		if(Status != EFI_SUCCESS){
			GDP(L"ERROR : pBeegameCtrl's Bees GraphicMemory allocated buffer fail.");
			return;
		}
		Status = gBS->AllocatePool(EfiBootServicesData,sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL)*pBeegameCtrl->Bees[i].BeesMemoryLength,&pBeegameCtrl->Bees[i].RecoveryMemory);
		if(Status != EFI_SUCCESS){
			GDP(L"ERROR : pBeegameCtrl's Bees RecoveryMemory allocated buffer fail.");
			return;
		}
	    if(pBeegameCtrl->Bees[i].GraphicMemory==(EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)NULL) return;
	    if(pBeegameCtrl->Bees[i].RecoveryMemory==(EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)NULL) return;
	}
	
    for(i=0;i<BBE_BULLET_MAX;i++){
		pBeegameCtrl->Bullets[i].BulletMemoryLength=BEE_BULLET_WIDTH*BEE_BULLET_HEIGHT;
		Status = gBS->AllocatePool(EfiBootServicesData,sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL)*pBeegameCtrl->Bullets[i].BulletMemoryLength,&pBeegameCtrl->Bullets[i].GraphicMemory);
		if(Status != EFI_SUCCESS){
			GDP(L"ERROR : pBeegameCtrl's Bullets GraphicMemory allocated buffer fail.");
			return;
		}
	    Status = gBS->AllocatePool(EfiBootServicesData,sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL)*pBeegameCtrl->Bullets[i].BulletMemoryLength,&pBeegameCtrl->Bullets[i].RecoveryMemory);
		if(Status != EFI_SUCCESS){
			GDP(L"ERROR : pBeegameCtrl's Bullets RecoveryMemory allocated buffer fail.");
			return;
		}
		if(pBeegameCtrl->Bullets[i].GraphicMemory==(EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)NULL) return;
	    if(pBeegameCtrl->Bullets[i].RecoveryMemory==(EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)NULL) return;
	}
	
    pBeegameCtrl->RestartButton.Type=WINDOW_BUTTON_PUSHBUTTON;
    pBeegameCtrl->RestartButton.Status=WINDOW_BUTTON_RELEASE;
    pBeegameCtrl->RestartButton.Active=TRUE;
    pBeegameCtrl->RestartButton.Dirty=TRUE;
    pBeegameCtrl->RestartButton.Outline=TRUE;
    pBeegameCtrl->RestartButton.pName=BeeStringRestart;
    pBeegameCtrl->RestartButton.pBitmap=(UINT8 *)NULL;
    pBeegameCtrl->RestartButton.ReleaseGfx.BgColor=GFX_COLOR_GREEN;
    pBeegameCtrl->RestartButton.ReleaseGfx.FgColor=GFX_COLOR_GREEN;
    pBeegameCtrl->RestartButton.ReleaseGfx.FontColor=GFX_COLOR_WHITE;
    pBeegameCtrl->RestartButton.PressGfx.BgColor=GFX_COLOR_GREEN0;
    pBeegameCtrl->RestartButton.PressGfx.FgColor=GFX_COLOR_GREEN0;
    pBeegameCtrl->RestartButton.PressGfx.FontColor=GFX_COLOR_WHITE;
    pBeegameCtrl->RestartButton.InactiveGfx.BgColor=GFX_COLOR_LIGHTGRAY;
    pBeegameCtrl->RestartButton.InactiveGfx.FgColor=GFX_COLOR_LIGHTGRAY;
    pBeegameCtrl->RestartButton.InactiveGfx.FontColor=GFX_COLOR_BLUE;
    pBeegameCtrl->RestartButton.Area.X=0;
    pBeegameCtrl->RestartButton.Area.Y=2;
    pBeegameCtrl->RestartButton.Area.W=86;
    pBeegameCtrl->RestartButton.Area.H=10+4;
	pBeegameCtrl->WdRestartButton.Type=WINDOW_DEVICE_BUTTON;
	pBeegameCtrl->WdRestartButton.DeviceNumberLeft=BEE_WDN_RESTARTBUTTON;
	pBeegameCtrl->WdRestartButton.DeviceNumberMiddle=WINDOW_WDN_NULL;
	pBeegameCtrl->WdRestartButton.DeviceNumberRight=WINDOW_WDN_NULL;
	pBeegameCtrl->WdRestartButton.pDevice=(UINT32 *)(&pBeegameCtrl->RestartButton);

    pBeegameCtrl->CloseButton.Type=WINDOW_BUTTON_PUSHBUTTON;
    pBeegameCtrl->CloseButton.Status=WINDOW_BUTTON_RELEASE;
    pBeegameCtrl->CloseButton.Active=TRUE;
    pBeegameCtrl->CloseButton.Dirty=TRUE;
    pBeegameCtrl->CloseButton.Outline=TRUE;
    pBeegameCtrl->CloseButton.pName=BeeStringClose;
    pBeegameCtrl->CloseButton.pBitmap=(UINT8 *)NULL;
    pBeegameCtrl->CloseButton.ReleaseGfx.BgColor=GFX_COLOR_GREEN;
    pBeegameCtrl->CloseButton.ReleaseGfx.FgColor=GFX_COLOR_GREEN;
    pBeegameCtrl->CloseButton.ReleaseGfx.FontColor=GFX_COLOR_WHITE;
    pBeegameCtrl->CloseButton.PressGfx.BgColor=GFX_COLOR_GREEN0;
    pBeegameCtrl->CloseButton.PressGfx.FgColor=GFX_COLOR_GREEN0;
    pBeegameCtrl->CloseButton.PressGfx.FontColor=GFX_COLOR_WHITE;
    pBeegameCtrl->CloseButton.InactiveGfx.BgColor=GFX_COLOR_LIGHTGRAY;
    pBeegameCtrl->CloseButton.InactiveGfx.FgColor=GFX_COLOR_LIGHTGRAY;
    pBeegameCtrl->CloseButton.InactiveGfx.FontColor=GFX_COLOR_BLUE;
    pBeegameCtrl->CloseButton.Area.X=94;
    pBeegameCtrl->CloseButton.Area.Y=2;
    pBeegameCtrl->CloseButton.Area.W=62;
    pBeegameCtrl->CloseButton.Area.H=10+4;
	pBeegameCtrl->WdCloseButton.Type=WINDOW_DEVICE_BUTTON;
	pBeegameCtrl->WdCloseButton.DeviceNumberLeft=BEE_WDN_CLOSEBUTTON;
	pBeegameCtrl->WdCloseButton.DeviceNumberMiddle=WINDOW_WDN_NULL;
	pBeegameCtrl->WdCloseButton.DeviceNumberRight=WINDOW_WDN_NULL;
	pBeegameCtrl->WdCloseButton.pDevice=(UINT32 *)(&pBeegameCtrl->CloseButton);


    pBeegameCtrl->UserTable.Type=WINDOW_TABLE_GENERAL;
    pBeegameCtrl->UserTable.DeviceList=(WINDOW_DEVICE *)NULL;
    pBeegameCtrl->UserTable.Gfx.BgColor=GFX_COLOR_LIGHTBLUE;
    pBeegameCtrl->UserTable.Gfx.FgColor=GFX_COLOR_LIGHTBLUE;
    pBeegameCtrl->UserTable.Gfx.FontColor=GFX_COLOR_WHITE;
    pBeegameCtrl->UserTable.Area.X=0;
    pBeegameCtrl->UserTable.Area.Y=0;
    pBeegameCtrl->UserTable.Area.W=BEE_WINDOW_WIDTH;
    pBeegameCtrl->UserTable.Area.H=BEE_WINDOW_HEIGHT+15+10;
    DeskTableWindowDeviceAdd(&pBeegameCtrl->UserTable,&pBeegameCtrl->WdRestartButton);
    DeskTableWindowDeviceAdd(&pBeegameCtrl->UserTable,&pBeegameCtrl->WdCloseButton);
    DeskTableWindowDeviceAdd(&pBeegameCtrl->UserTable,&pBeegameCtrl->WdBoard);

	//window parameter
	WindowVariableInit(&pBeegameCtrl->Window,WINDOW_TYPE_APPLICATION);
    pBeegameCtrl->Window.pTitle=(UINT8 *)BeeTaskName;  
    DeskTableUserTableAdd((WINDOW *)&pBeegameCtrl->Window,(WINDOW_TABLE *)&pBeegameCtrl->UserTable);
    WindowAreaInitial(&pBeegameCtrl->Window);
    WindowOutlineCalculate(&pBeegameCtrl->Window);
    WindowOutlineTableInitial(&pBeegameCtrl->Window);
    WindowHeaderCalculate(&pBeegameCtrl->Window);
    WindowHeaderTableInitial(&pBeegameCtrl->Window);
    DeskWindowWindowPut((WINDOW *)&pBeegameCtrl->Window); 
    ((OS_TCB *)OsTaskCurrent)->Window=(UINT32)&pBeegameCtrl->Window;
    
	OsTimeTimerPut(&pBeegameCtrl->BulletTimer);
	OsTimeTimerPut(&pBeegameCtrl->BeesTimer);
	pBeegameCtrl->TaskState=BeetaskRunState;
	pBeegameCtrl->State=BeeInitialState;
}

VOID BeegameSvc(BEEGAME_CONTROL *pBeegameCtrl){
	UINT8 KeyData;
	UINT8 i;
	
	switch(pBeegameCtrl->State){
        case BeeIdleState:
            break;
        case BeeInitialState:
		    pBeegameCtrl->HitNumber=0;
		    pBeegameCtrl->BeeCurrentPath=0;
		    pBeegameCtrl->BeePreviousPath=0;
            pBeegameCtrl->FlyStep=0;
			pBeegameCtrl->HitCheck=FALSE;
			pBeegameCtrl->GameOver=FALSE;
			pBeegameCtrl->pCurrentBee=(BEEGAME_BEE *)NULL;
			pBeegameCtrl->BulletTimer.Timer=0;
			pBeegameCtrl->BeesTimer.Timer=0;
			
		    pBeegameCtrl->Fighter.FighterGfx.BgColor=GFX_COLOR_BLACK;
		    pBeegameCtrl->Fighter.FighterGfx.FgColor=GFX_COLOR_BLACK;
		    pBeegameCtrl->Fighter.FighterGfx.FontColor=GFX_COLOR_RED;
			pBeegameCtrl->Fighter.CurrentArea.X=(pBeegameCtrl->Board.Area.W-9)/2;
			pBeegameCtrl->Fighter.CurrentArea.Y=pBeegameCtrl->Board.Area.H-BEE_FIGHTER_HEIGHT;
			pBeegameCtrl->Fighter.CurrentArea.W=BEE_FIGHTER_WIDTH;
			pBeegameCtrl->Fighter.CurrentArea.H=BEE_FIGHTER_HEIGHT;
			pBeegameCtrl->Fighter.PreviousArea.X=(pBeegameCtrl->Board.Area.W-9)/2;
			pBeegameCtrl->Fighter.PreviousArea.Y=pBeegameCtrl->Board.Area.H-BEE_FIGHTER_HEIGHT;
			pBeegameCtrl->Fighter.PreviousArea.W=BEE_FIGHTER_WIDTH;
			pBeegameCtrl->Fighter.PreviousArea.H=BEE_FIGHTER_HEIGHT;
	
			for(i=0;i<BBE_BULLET_MAX;i++){
			    pBeegameCtrl->Bullets[i].BulletGfx.BgColor=GFX_COLOR_BLACK;
			    pBeegameCtrl->Bullets[i].BulletGfx.FgColor=GFX_COLOR_BLACK;
			    pBeegameCtrl->Bullets[i].BulletGfx.FontColor=GFX_COLOR_YELLOW;
				pBeegameCtrl->Bullets[i].CurrentArea.X=0;
				pBeegameCtrl->Bullets[i].CurrentArea.Y=0;
				pBeegameCtrl->Bullets[i].CurrentArea.W=BEE_BULLET_WIDTH;
				pBeegameCtrl->Bullets[i].CurrentArea.H=BEE_BULLET_HEIGHT;
				pBeegameCtrl->Bullets[i].PreviousArea.X=0;
				pBeegameCtrl->Bullets[i].PreviousArea.Y=0;
				pBeegameCtrl->Bullets[i].PreviousArea.W=BEE_BULLET_WIDTH;
				pBeegameCtrl->Bullets[i].PreviousArea.H=BEE_BULLET_HEIGHT;
			}
			pBeegameCtrl->FreeBulletList=(BEEGAME_BULLET *)NULL;
			pBeegameCtrl->UsedBulletList=(BEEGAME_BULLET *)NULL;
			for(i=0;i<BBE_BULLET_MAX;i++){
			    BeegameFreeBulletListBulletPut(pBeegameCtrl,&pBeegameCtrl->Bullets[i]);
		    }
			for(i=0;i<BBE_BEES_MAX;i++){
			    pBeegameCtrl->Bees[i].BeesGfx.BgColor=GFX_COLOR_WHITE;
			    pBeegameCtrl->Bees[i].BeesGfx.FgColor=GFX_COLOR_WHITE;
			    pBeegameCtrl->Bees[i].BeesGfx.FontColor=GFX_COLOR_YELLOW;
				pBeegameCtrl->Bees[i].SwingStatus=BEE_BEES_SWINGOFF;
				pBeegameCtrl->Bees[i].CurrentArea.X=5+20*i;
				pBeegameCtrl->Bees[i].CurrentArea.Y=5;
				pBeegameCtrl->Bees[i].CurrentArea.W=BEE_BEES_WIDTH;
				pBeegameCtrl->Bees[i].CurrentArea.H=BEE_BEES_HEIGHT;
				pBeegameCtrl->Bees[i].PreviousArea.X=5+20*i;
				pBeegameCtrl->Bees[i].PreviousArea.Y=5;
				pBeegameCtrl->Bees[i].PreviousArea.W=BEE_BEES_WIDTH;
				pBeegameCtrl->Bees[i].PreviousArea.H=BEE_BEES_HEIGHT;
			}
			pBeegameCtrl->BeeList=(BEEGAME_BEE *)NULL;
			for(i=0;i<BBE_BEES_MAX;i++){
			    BeegameBeeListBeePut(pBeegameCtrl,&pBeegameCtrl->Bees[i]);
		    }
            BoardMemoryReset(&pBeegameCtrl->Board);
            BeegameFighterMapCapture(pBeegameCtrl);
            BeegameFighterUpdate(pBeegameCtrl);
            for(KeyData=0;KeyData<BBE_BEES_MAX;KeyData++){
                BeegameBeeMapCapture(pBeegameCtrl,&pBeegameCtrl->Bees[KeyData]);
                BeegameBeeDraw(pBeegameCtrl,&pBeegameCtrl->Bees[KeyData]);
                BeegameBeeMapDraw(pBeegameCtrl,&pBeegameCtrl->Bees[KeyData]);
            }
	        pBeegameCtrl->Dirty=FALSE;
	        pBeegameCtrl->Board.Dirty=TRUE;
	        pBeegameCtrl->State=BeeRunState;
            break;
		case BeeRunState:
		    if(WindowEventBufferCheck(&pBeegameCtrl->Window)!=BUFFER_EMPTY){
		    	pBeegameCtrl->WindowEvent=WindowEventBufferGet(&pBeegameCtrl->Window);
		    	if(pBeegameCtrl->WindowEvent!=0){
		    		#if(DEBUG_BEE==1)
		    		    CaptionStringPrint(&DeskDebugCtrl.Caption,"\nevent ");
		    		    CaptionUINT8Print(&DeskDebugCtrl.Caption,(UINT8)pBeegameCtrl->WindowEvent);
		    		#endif
		        }
			    BeegameEventHandler(pBeegameCtrl);
			    if(pBeegameCtrl->State!=BeeRunState) break;
		    }
		    if(pBeegameCtrl->GameOver==TRUE){ 
		    	OsYield(NULL,NULL);
		    	break;
		    }
		    if(WindowKeyBufferCheck(&pBeegameCtrl->Window)!=BUFFER_EMPTY){
		    	KeyData=WindowKeyBufferGet(&pBeegameCtrl->Window);
		        //CaptionUINT8Print(&DeskDebugCtrl.Caption,KeyData);
		    	BeegameFighterSvc(pBeegameCtrl,KeyData);
		    }
		    if(pBeegameCtrl->BulletTimer.Timer==0){
		        pBeegameCtrl->BulletTimer.Timer=BEE_BULLET_TIME;
		        BeegameBulletMove(pBeegameCtrl);		        
			    pBeegameCtrl->HitCheck=TRUE;
		    }
		    if(pBeegameCtrl->BeesTimer.Timer==0){
		        pBeegameCtrl->BeesTimer.Timer=BEE_BEES_TIME;
		        BeegameBeeMove(pBeegameCtrl);	        
			    pBeegameCtrl->HitCheck=TRUE;
		    }
		    if(pBeegameCtrl->HitCheck==TRUE){        
			    pBeegameCtrl->HitCheck=FALSE;
		        BeegameBeeBulletHitHandler(pBeegameCtrl);
		    }
		    if(pBeegameCtrl->GameOver==TRUE){
		    	BoardGotoxy(&pBeegameCtrl->Board,50,50);
		    	BoardStringPrint(&pBeegameCtrl->Board,BeeStringGameOver);
		    	BoardGotoxy(&pBeegameCtrl->Board,50,70);
		    	BoardStringPrint(&pBeegameCtrl->Board,BeeStringHit);
		    	BoardUINT8Print(&pBeegameCtrl->Board,pBeegameCtrl->HitNumber);
		    }
            if(pBeegameCtrl->Dirty==TRUE){
            	pBeegameCtrl->Dirty=FALSE;
            	pBeegameCtrl->Board.Dirty=TRUE;
            }
		    if((pBeegameCtrl->BulletTimer.Timer!=0)
	         &&(pBeegameCtrl->BeesTimer.Timer!=0)
	         &&(WindowKeyBufferCheck(&pBeegameCtrl->Window)==BUFFER_EMPTY)) OsYield(NULL,NULL);
            break;
    }
}

VOID BeegameEventHandler(BEEGAME_CONTROL *pBeegameCtrl){
    switch((UINT8)pBeegameCtrl->WindowEvent){
    	case BEE_WDN_BOARD:
    	    //do nothing
    	    break;
    	case BEE_WDN_RESTARTBUTTON:
    	    pBeegameCtrl->State=BeeInitialState;
    	    break;
    	case BEE_WDN_CLOSEBUTTON:
            DeskWindowWindowDelete((WINDOW *)((OS_TCB *)OsTaskCurrent)->Window);
    	    pBeegameCtrl->State=BeeCloseState;
    	    break;
    	default:
    	    break;
    }
}
