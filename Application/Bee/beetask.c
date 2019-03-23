#include <includes.h>

#define DEBUG_BEETASK 1

const UINT8 BeeTaskName[]="BEE";

VOID BeeTaskInit(BEEGAME_CONTROL *pBeegameCtrl){
	BeegameInit(pBeegameCtrl);	
}

VOID BeeTask(VOID){
	BEEGAME_CONTROL *pBeegameCtrl;
	EFI_STATUS Status;
	
	//pBeegameCtrl=(BEEGAME_CONTROL *)OsMemoryAllocate(sizeof(BEEGAME_CONTROL));
	//if(pBeegameCtrl==(BEEGAME_CONTROL *)NULL) OsTaskFinish();
	Status = gBS->AllocatePool(EfiBootServicesData,sizeof(BEEGAME_CONTROL),&pBeegameCtrl);
	if(Status != EFI_SUCCESS){
		OsTaskFinish();
		return FALSE;
	}
    BeeTaskInit(pBeegameCtrl);
	if(pBeegameCtrl->TaskState==BeetaskIdleState) OsTaskFinish();
    while(1){
        while((pBeegameCtrl->Window.Message!=WINDOW_WM_CLOSE)
            &&(pBeegameCtrl->Window.Active==FALSE)) OsYield(NULL,NULL);
    	if(pBeegameCtrl->Window.Active==TRUE) BeegameSvc(pBeegameCtrl);
	    if(pBeegameCtrl->State==BeeCloseState) break;
	    if(pBeegameCtrl->Window.Message==WINDOW_WM_CLOSE){  //window event handler
	        pBeegameCtrl->Window.MessageAck=WINDOW_WM_ACK;
		    #if(DEBUG_BEETASK==1)		    
	            CaptionStringPrint(&DeskDebugCtrl.Caption,"\nBEE window close message");
		    #endif
	        break;
	    }
    }
    if(pBeegameCtrl->State==BeeCloseState); //no need to wait window close
    else while(pBeegameCtrl->Window.State!=DESK_WINDOW_STATE_OFFDESK) OsYield(NULL,NULL); //wait until window deleted from desk
    #if(DEBUG_BEETASK==1)		    
	    CaptionStringPrint(&DeskDebugCtrl.Caption,"\ntask off");
	#endif
    OsFinish();
}
