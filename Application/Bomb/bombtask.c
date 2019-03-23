#include <includes.h>

#define DEBUG_BOMBTASK 1

const UINT8 BombTaskName[]="BOMB";

VOID BombTaskInit(BOMB_CONTROL *pBomb){
    BombInit(pBomb);
}

VOID BombTask(VOID){
    BOMB_CONTROL *pBomb;
	EFI_STATUS Status;
    
    //pBomb=(BOMB_CONTROL *)OsMemoryAllocate(sizeof(BOMB_CONTROL));
    //if(pBomb==(BOMB_CONTROL *)NULL) OsTaskFinish();
	Status = gBS->AllocatePool(EfiBootServicesData,sizeof(BOMB_CONTROL),&pBomb);
	if(Status != EFI_SUCCESS){
		OsTaskFinish();
		return FALSE;
	}
	
    BombTaskInit(pBomb);
    if(pBomb->TaskState==BombTaskIdleState) OsTaskFinish();
    while(1){
        if(pBomb->Window.Active==TRUE) BombSvc(pBomb);
        if(pBomb->State==BombCloseState) break;
        if(pBomb->Window.Message==WINDOW_WM_CLOSE){  //window event handler
            pBomb->Window.MessageAck=WINDOW_WM_ACK;
		    #if(DEBUG_BOMBTASK==1)		    
	            CaptionStringPrint(&DeskDebugCtrl.Caption,"\nBOMB window close message");
		    #endif
            break;
        }
        OsYield(NULL,NULL);
    }
    if(pBomb->State==BombCloseState); //no need to wait window close
    else while(pBomb->Window.State!=DESK_WINDOW_STATE_OFFDESK) OsYield(NULL,NULL); //wait until window deleted from desk
    #if(DEBUG_BOMBTASK==1)		    
	    CaptionStringPrint(&DeskDebugCtrl.Caption,"\ntask off");
	#endif
    OsFinish();
}
