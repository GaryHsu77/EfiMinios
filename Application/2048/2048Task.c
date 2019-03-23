#include <includes.h>

#define DEBUG_2048TASK 1

const UINT8 Task2048Name[]="2048";

VOID Task2048Init(GAME2048_CONTROL *p2048gameCtrl){
	Game2048Init(p2048gameCtrl);	
}

VOID Task2048(VOID){
	GAME2048_CONTROL *p2048gameCtrl;
	EFI_STATUS Status;
	
	Status = gBS->AllocatePool(EfiBootServicesData,sizeof(GAME2048_CONTROL),&p2048gameCtrl);
	if(Status != EFI_SUCCESS){
		OsTaskFinish();
		return FALSE;
	}
    Task2048Init(p2048gameCtrl);
	if(p2048gameCtrl->TaskState==Task2048IdleState) OsTaskFinish();
    while(1){
        while((p2048gameCtrl->Window.Message!=WINDOW_WM_CLOSE)
            &&(p2048gameCtrl->Window.Active==FALSE)) OsYield(NULL,NULL);
		OsYield(NULL,NULL);
    	if(p2048gameCtrl->Window.Active==TRUE) Game2048Svc(p2048gameCtrl);
	    if(p2048gameCtrl->State==G2048CloseState) break;
	    if(p2048gameCtrl->Window.Message==WINDOW_WM_CLOSE){  //window event handler
	        p2048gameCtrl->Window.MessageAck=WINDOW_WM_ACK;
		    #if(DEBUG_2048TASK==1)		    
	            CaptionStringPrint(&DeskDebugCtrl.Caption,"\n2048 window close message");
		    #endif
	        break;
	    }
    }
    if(p2048gameCtrl->State==G2048CloseState); //no need to wait window close
    else while(p2048gameCtrl->Window.State!=DESK_WINDOW_STATE_OFFDESK) OsYield(NULL,NULL); //wait until window deleted from desk
    #if(DEBUG_2048TASK==1)		    
	    CaptionStringPrint(&DeskDebugCtrl.Caption,"\ntask off");
	#endif
    OsFinish();
}
