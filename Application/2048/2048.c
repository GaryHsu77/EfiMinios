#include <includes.h>

#define DEBUG_2048 0

const UINT8 G2048StringRestart[]="RESTART";
const UINT8 G2048StringClose[]="CLOSE";
const UINT8 G2048StringGameOver[]="GAME OVER";
const UINT8 G2048StringHit[]="HIT: ";

VOID Game2048Init(GAME2048_CONTROL *p2048gameCtrl){
	UINT8 i;
	EFI_STATUS Status;
	
	p2048gameCtrl->TaskState=G2048IdleState;
    if(BoardCreat(&p2048gameCtrl->Board, G2048_WINDOW_WIDTH, G2048_WINDOW_HEIGHT)==FALSE) return;
    p2048gameCtrl->Board.Area.X=0;
    p2048gameCtrl->Board.Area.Y=15+5;
    p2048gameCtrl->Board.Gfx.FgColor=GFX_COLOR_BLACK;
    p2048gameCtrl->Board.Gfx.BgColor=GFX_COLOR_BLACK;
    p2048gameCtrl->Board.Gfx.FontColor=GFX_COLOR_WHITE;
    BoardMemoryReset(&p2048gameCtrl->Board);
    p2048gameCtrl->WdBoard.DeviceNumberLeft=G2048_WDN_BOARD;
    p2048gameCtrl->WdBoard.DeviceNumberMiddle=G2048_WDN_BOARD;
    p2048gameCtrl->WdBoard.DeviceNumberRight=G2048_WDN_BOARD;
	p2048gameCtrl->WdBoard.Type=WINDOW_DEVICE_BOARD;
	p2048gameCtrl->WdBoard.pDevice=(UINT32 *)(&p2048gameCtrl->Board);
	
	
	for(i=0;i<BLK_NUM_MAX;i++){
		p2048gameCtrl->BLKs[i].BlkMemoryLength=BLK_WIDTH*BLK_HEIGHT;
		Status = gBS->AllocatePool(EfiBootServicesData,sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL)*p2048gameCtrl->BLKs[i].BlkMemoryLength,&p2048gameCtrl->BLKs[i].GraphicMemory);
		if(Status != EFI_SUCCESS){
			GDP(L"ERROR : p2048gameCtrl's BLKs GraphicMemory allocated buffer fail.");
			return;
		}
		Status = gBS->AllocatePool(EfiBootServicesData,sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL)*p2048gameCtrl->BLKs[i].BlkMemoryLength,&p2048gameCtrl->BLKs[i].RecoveryMemory);
		if(Status != EFI_SUCCESS){
			GDP(L"ERROR : p2048gameCtrl's BLKs RecoveryMemory allocated buffer fail.");
			return;
		}
	}
	
    p2048gameCtrl->RestartButton.Type=WINDOW_BUTTON_PUSHBUTTON;
    p2048gameCtrl->RestartButton.Status=WINDOW_BUTTON_RELEASE;
    p2048gameCtrl->RestartButton.Active=TRUE;
    p2048gameCtrl->RestartButton.Dirty=TRUE;
    p2048gameCtrl->RestartButton.Outline=TRUE;
    p2048gameCtrl->RestartButton.pName=G2048StringRestart;
    p2048gameCtrl->RestartButton.pBitmap=(UINT8 *)NULL;
    p2048gameCtrl->RestartButton.ReleaseGfx.BgColor=GFX_COLOR_GREEN;
    p2048gameCtrl->RestartButton.ReleaseGfx.FgColor=GFX_COLOR_GREEN;
    p2048gameCtrl->RestartButton.ReleaseGfx.FontColor=GFX_COLOR_WHITE;
    p2048gameCtrl->RestartButton.PressGfx.BgColor=GFX_COLOR_GREEN0;
    p2048gameCtrl->RestartButton.PressGfx.FgColor=GFX_COLOR_GREEN0;
    p2048gameCtrl->RestartButton.PressGfx.FontColor=GFX_COLOR_WHITE;
    p2048gameCtrl->RestartButton.InactiveGfx.BgColor=GFX_COLOR_LIGHTGRAY;
    p2048gameCtrl->RestartButton.InactiveGfx.FgColor=GFX_COLOR_LIGHTGRAY;
    p2048gameCtrl->RestartButton.InactiveGfx.FontColor=GFX_COLOR_BLUE;
    p2048gameCtrl->RestartButton.Area.X=0;
    p2048gameCtrl->RestartButton.Area.Y=2;
    p2048gameCtrl->RestartButton.Area.W=86;
    p2048gameCtrl->RestartButton.Area.H=10+4;
	p2048gameCtrl->WdRestartButton.Type=WINDOW_DEVICE_BUTTON;
	p2048gameCtrl->WdRestartButton.DeviceNumberLeft=BEE_WDN_RESTARTBUTTON;
	p2048gameCtrl->WdRestartButton.DeviceNumberMiddle=WINDOW_WDN_NULL;
	p2048gameCtrl->WdRestartButton.DeviceNumberRight=WINDOW_WDN_NULL;
	p2048gameCtrl->WdRestartButton.pDevice=(UINT32 *)(&p2048gameCtrl->RestartButton);

    p2048gameCtrl->CloseButton.Type=WINDOW_BUTTON_PUSHBUTTON;
    p2048gameCtrl->CloseButton.Status=WINDOW_BUTTON_RELEASE;
    p2048gameCtrl->CloseButton.Active=TRUE;
    p2048gameCtrl->CloseButton.Dirty=TRUE;
    p2048gameCtrl->CloseButton.Outline=TRUE;
    p2048gameCtrl->CloseButton.pName=G2048StringClose;
    p2048gameCtrl->CloseButton.pBitmap=(UINT8 *)NULL;
    p2048gameCtrl->CloseButton.ReleaseGfx.BgColor=GFX_COLOR_GREEN;
    p2048gameCtrl->CloseButton.ReleaseGfx.FgColor=GFX_COLOR_GREEN;
    p2048gameCtrl->CloseButton.ReleaseGfx.FontColor=GFX_COLOR_WHITE;
    p2048gameCtrl->CloseButton.PressGfx.BgColor=GFX_COLOR_GREEN0;
    p2048gameCtrl->CloseButton.PressGfx.FgColor=GFX_COLOR_GREEN0;
    p2048gameCtrl->CloseButton.PressGfx.FontColor=GFX_COLOR_WHITE;
    p2048gameCtrl->CloseButton.InactiveGfx.BgColor=GFX_COLOR_LIGHTGRAY;
    p2048gameCtrl->CloseButton.InactiveGfx.FgColor=GFX_COLOR_LIGHTGRAY;
    p2048gameCtrl->CloseButton.InactiveGfx.FontColor=GFX_COLOR_BLUE;
    p2048gameCtrl->CloseButton.Area.X=94;
    p2048gameCtrl->CloseButton.Area.Y=2;
    p2048gameCtrl->CloseButton.Area.W=62;
    p2048gameCtrl->CloseButton.Area.H=10+4;
	p2048gameCtrl->WdCloseButton.Type=WINDOW_DEVICE_BUTTON;
	p2048gameCtrl->WdCloseButton.DeviceNumberLeft=BEE_WDN_CLOSEBUTTON;
	p2048gameCtrl->WdCloseButton.DeviceNumberMiddle=WINDOW_WDN_NULL;
	p2048gameCtrl->WdCloseButton.DeviceNumberRight=WINDOW_WDN_NULL;
	p2048gameCtrl->WdCloseButton.pDevice=(UINT32 *)(&p2048gameCtrl->CloseButton);


    p2048gameCtrl->UserTable.Type=WINDOW_TABLE_GENERAL;
    p2048gameCtrl->UserTable.DeviceList=(WINDOW_DEVICE *)NULL;
    p2048gameCtrl->UserTable.Gfx.BgColor=GFX_COLOR_LIGHTBLUE;
    p2048gameCtrl->UserTable.Gfx.FgColor=GFX_COLOR_LIGHTBLUE;
    p2048gameCtrl->UserTable.Gfx.FontColor=GFX_COLOR_WHITE;
    p2048gameCtrl->UserTable.Area.X=0;
    p2048gameCtrl->UserTable.Area.Y=0;
    p2048gameCtrl->UserTable.Area.W=G2048_WINDOW_WIDTH;
    p2048gameCtrl->UserTable.Area.H=G2048_WINDOW_HEIGHT+15+10;
    DeskTableWindowDeviceAdd(&p2048gameCtrl->UserTable,&p2048gameCtrl->WdRestartButton);
    DeskTableWindowDeviceAdd(&p2048gameCtrl->UserTable,&p2048gameCtrl->WdCloseButton);
    DeskTableWindowDeviceAdd(&p2048gameCtrl->UserTable,&p2048gameCtrl->WdBoard);

	//window parameter
	WindowVariableInit(&p2048gameCtrl->Window,WINDOW_TYPE_APPLICATION);
    p2048gameCtrl->Window.pTitle=(UINT8 *)Task2048Name;  
    DeskTableUserTableAdd((WINDOW *)&p2048gameCtrl->Window,(WINDOW_TABLE *)&p2048gameCtrl->UserTable);
    WindowAreaInitial(&p2048gameCtrl->Window);
    WindowOutlineCalculate(&p2048gameCtrl->Window);
    WindowOutlineTableInitial(&p2048gameCtrl->Window);
    WindowHeaderCalculate(&p2048gameCtrl->Window);
    WindowHeaderTableInitial(&p2048gameCtrl->Window);
    DeskWindowWindowPut((WINDOW *)&p2048gameCtrl->Window); 
    ((OS_TCB *)OsTaskCurrent)->Window=(UINT32)&p2048gameCtrl->Window;
    
	p2048gameCtrl->TaskState=G2048RunState;
	p2048gameCtrl->State=G2048InitialState;
}

VOID Game2048Svc(GAME2048_CONTROL *p2048gameCtrl){
	UINT8 KeyData;
	UINT8 i;
	
	switch(p2048gameCtrl->State){
        case BeeIdleState:
            break;
        case G2048InitialState:
		    //p2048gameCtrl->HitNumber=0;
		    //p2048gameCtrl->BeeCurrentPath=0;
		    //p2048gameCtrl->BeePreviousPath=0;
            //p2048gameCtrl->FlyStep=0;
			//p2048gameCtrl->HitCheck=FALSE;
			p2048gameCtrl->GameOver=FALSE;
			p2048gameCtrl->pCurrentBlk=(GAME2048_BLK *)NULL;
			//p2048gameCtrl->BulletTimer.Timer=0;
			//p2048gameCtrl->BeesTimer.Timer=0;
			for(i=0;i<4;i++){
			    p2048gameCtrl->BLKs[i].BlksGfx.BgColor=GFX_COLOR_WHITE;
			    p2048gameCtrl->BLKs[i].BlksGfx.FgColor=GFX_COLOR_WHITE;
			    p2048gameCtrl->BLKs[i].BlksGfx.FontColor=GFX_COLOR_YELLOW;
				//p2048gameCtrl->BLKs[i].SwingStatus=BEE_BEES_SWINGOFF;
				p2048gameCtrl->BLKs[i].CurrentArea.X=25+100*i;
				p2048gameCtrl->BLKs[i].CurrentArea.Y=70;
				p2048gameCtrl->BLKs[i].CurrentArea.W=BLK_WIDTH;
				p2048gameCtrl->BLKs[i].CurrentArea.H=BLK_HEIGHT;
				p2048gameCtrl->BLKs[i].PreviousArea.X=25+100*i;
				p2048gameCtrl->BLKs[i].PreviousArea.Y=70;
				p2048gameCtrl->BLKs[i].PreviousArea.W=BLK_WIDTH;
				p2048gameCtrl->BLKs[i].PreviousArea.H=BLK_HEIGHT;
			}
			for(;i<8;i++){
			    p2048gameCtrl->BLKs[i].BlksGfx.BgColor=GFX_COLOR_WHITE;
			    p2048gameCtrl->BLKs[i].BlksGfx.FgColor=GFX_COLOR_WHITE;
			    p2048gameCtrl->BLKs[i].BlksGfx.FontColor=GFX_COLOR_YELLOW;
				//p2048gameCtrl->BLKs[i].SwingStatus=BEE_BEES_SWINGOFF;
				p2048gameCtrl->BLKs[i].CurrentArea.X=25+100*i;
				p2048gameCtrl->BLKs[i].CurrentArea.Y=70+100;
				p2048gameCtrl->BLKs[i].CurrentArea.W=BLK_WIDTH;
				p2048gameCtrl->BLKs[i].CurrentArea.H=BLK_HEIGHT;
				p2048gameCtrl->BLKs[i].PreviousArea.X=25+100*i;
				p2048gameCtrl->BLKs[i].PreviousArea.Y=70+100;
				p2048gameCtrl->BLKs[i].PreviousArea.W=BLK_WIDTH;
				p2048gameCtrl->BLKs[i].PreviousArea.H=BLK_HEIGHT;
			}
			for(;i<12;i++){
			    p2048gameCtrl->BLKs[i].BlksGfx.BgColor=GFX_COLOR_WHITE;
			    p2048gameCtrl->BLKs[i].BlksGfx.FgColor=GFX_COLOR_WHITE;
			    p2048gameCtrl->BLKs[i].BlksGfx.FontColor=GFX_COLOR_YELLOW;
				//p2048gameCtrl->BLKs[i].SwingStatus=BEE_BEES_SWINGOFF;
				p2048gameCtrl->BLKs[i].CurrentArea.X=25+100*i;
				p2048gameCtrl->BLKs[i].CurrentArea.Y=70+200;
				p2048gameCtrl->BLKs[i].CurrentArea.W=BLK_WIDTH;
				p2048gameCtrl->BLKs[i].CurrentArea.H=BLK_HEIGHT;
				p2048gameCtrl->BLKs[i].PreviousArea.X=25+100*i;
				p2048gameCtrl->BLKs[i].PreviousArea.Y=70+200;
				p2048gameCtrl->BLKs[i].PreviousArea.W=BLK_WIDTH;
				p2048gameCtrl->BLKs[i].PreviousArea.H=BLK_HEIGHT;
			}
			for(;i<16;i++){
			    p2048gameCtrl->BLKs[i].BlksGfx.BgColor=GFX_COLOR_WHITE;
			    p2048gameCtrl->BLKs[i].BlksGfx.FgColor=GFX_COLOR_WHITE;
			    p2048gameCtrl->BLKs[i].BlksGfx.FontColor=GFX_COLOR_YELLOW;
				//p2048gameCtrl->BLKs[i].SwingStatus=BEE_BEES_SWINGOFF;
				p2048gameCtrl->BLKs[i].CurrentArea.X=25+100*i;
				p2048gameCtrl->BLKs[i].CurrentArea.Y=70+300;
				p2048gameCtrl->BLKs[i].CurrentArea.W=BLK_WIDTH;
				p2048gameCtrl->BLKs[i].CurrentArea.H=BLK_HEIGHT;
				p2048gameCtrl->BLKs[i].PreviousArea.X=25+100*i;
				p2048gameCtrl->BLKs[i].PreviousArea.Y=70+300;
				p2048gameCtrl->BLKs[i].PreviousArea.W=BLK_WIDTH;
				p2048gameCtrl->BLKs[i].PreviousArea.H=BLK_HEIGHT;
			}

            BoardMemoryReset(&p2048gameCtrl->Board);
            for(KeyData=0;KeyData<BBE_BEES_MAX;KeyData++){
                G2048BlkMapCapture(p2048gameCtrl,&p2048gameCtrl->Bees[KeyData]);
                G2048BlkBmpDraw(p2048gameCtrl,&p2048gameCtrl->Bees[KeyData]);
                G2048BlkMapDraw(p2048gameCtrl,&p2048gameCtrl->Bees[KeyData]);
            }
	        p2048gameCtrl->Dirty=FALSE;
	        p2048gameCtrl->Board.Dirty=TRUE;
	        p2048gameCtrl->State=G2048RunState;
            break;
		case G2048RunState:
		/*
		    if(WindowEventBufferCheck(&p2048gameCtrl->Window)!=BUFFER_EMPTY){
		    	p2048gameCtrl->WindowEvent=WindowEventBufferGet(&p2048gameCtrl->Window);
		    	if(p2048gameCtrl->WindowEvent!=0){
		    		#if(DEBUG_2048==1)
		    		    CaptionStringPrint(&DeskDebugCtrl.Caption,"\nevent ");
		    		    CaptionUINT8Print(&DeskDebugCtrl.Caption,(UINT8)p2048gameCtrl->WindowEvent);
		    		#endif
		        }
			    BeegameEventHandler(p2048gameCtrl);
			    if(p2048gameCtrl->State!=G2048RunState) break;
		    }
		    if(p2048gameCtrl->GameOver==TRUE){ 
		    	OsYield(NULL,NULL);
		    	break;
		    }
		    if(WindowKeyBufferCheck(&p2048gameCtrl->Window)!=BUFFER_EMPTY){
		    	KeyData=WindowKeyBufferGet(&p2048gameCtrl->Window);
		        //CaptionUINT8Print(&DeskDebugCtrl.Caption,KeyData);
		    	BeegameFighterSvc(p2048gameCtrl,KeyData);
		    }
		    if(p2048gameCtrl->BulletTimer.Timer==0){
		        p2048gameCtrl->BulletTimer.Timer=BEE_BULLET_TIME;
		        BeegameBulletMove(p2048gameCtrl);		        
			    p2048gameCtrl->HitCheck=TRUE;
		    }
		    if(p2048gameCtrl->BeesTimer.Timer==0){
		        p2048gameCtrl->BeesTimer.Timer=BEE_BEES_TIME;
		        BeegameBeeMove(p2048gameCtrl);	        
			    p2048gameCtrl->HitCheck=TRUE;
		    }
		    if(p2048gameCtrl->HitCheck==TRUE){        
			    p2048gameCtrl->HitCheck=FALSE;
		        BeegameBeeBulletHitHandler(p2048gameCtrl);
		    }
		    if(p2048gameCtrl->GameOver==TRUE){
		    	BoardGotoxy(&p2048gameCtrl->Board,50,50);
		    	BoardStringPrint(&p2048gameCtrl->Board,G2048StringGameOver);
		    	BoardGotoxy(&p2048gameCtrl->Board,50,70);
		    	BoardStringPrint(&p2048gameCtrl->Board,G2048StringHit);
		    	BoardUINT8Print(&p2048gameCtrl->Board,p2048gameCtrl->HitNumber);
		    }
            if(p2048gameCtrl->Dirty==TRUE){
            	p2048gameCtrl->Dirty=FALSE;
            	p2048gameCtrl->Board.Dirty=TRUE;
            }
		    if((p2048gameCtrl->BulletTimer.Timer!=0)
	         &&(p2048gameCtrl->BeesTimer.Timer!=0)
	         &&(WindowKeyBufferCheck(&p2048gameCtrl->Window)==BUFFER_EMPTY)) OsYield(NULL,NULL);
        */
			break;
    }
}

VOID Game2048EventHandler(GAME2048_CONTROL *p2048gameCtrl){
    switch((UINT8)p2048gameCtrl->WindowEvent){
    	case BEE_WDN_BOARD:
    	    //do nothing
    	    break;
    	case BEE_WDN_RESTARTBUTTON:
    	    p2048gameCtrl->State=G2048InitialState;
    	    break;
    	case BEE_WDN_CLOSEBUTTON:
            DeskWindowWindowDelete((WINDOW *)((OS_TCB *)OsTaskCurrent)->Window);
    	    p2048gameCtrl->State=BeeCloseState;
    	    break;
    	default:
    	    break;
    }
}
