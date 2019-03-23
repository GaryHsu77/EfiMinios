#include <includes.h>

#define DEBUG_CALCULATORTASK 1

VOID CalculatorTaskInit(CALCULATOR_CONTORL *pCalculator){
	CalculatorInit(pCalculator);
}

VOID CalculatorTask(VOID){
	CALCULATOR_CONTORL *pCalculator;
	EFI_STATUS Status;
	
	//pCalculator=(CALCULATOR_CONTORL *)OsMemoryAllocate(sizeof(CALCULATOR_CONTORL));
	//if(pCalculator==(CALCULATOR_CONTORL *)NULL) OsTaskFinish();
	Status = gBS->AllocatePool(EfiBootServicesData,sizeof(CALCULATOR_CONTORL),&pCalculator);
	if(Status != EFI_SUCCESS){
		OsTaskFinish();
		return FALSE;
	}
	CalculatorTaskInit(pCalculator);
	if(pCalculator->TaskState==CalculatorTaskIdleState) OsTaskFinish();
    while(1){
        CalculatorSvc(pCalculator);
	    if(pCalculator->Window.Message==WINDOW_WM_CLOSE){  //window event handler
	        pCalculator->Window.MessageAck=WINDOW_WM_ACK;
		    #if(DEBUG_CALCULATORTASK==1)		    
	            CaptionStringPrint(&DeskDebugCtrl.Caption,"\nCALCULATOR window close message");
		    #endif
	        break;
	    }
        OsYield(NULL,NULL);
    }
    while(pCalculator->Window.State!=DESK_WINDOW_STATE_OFFDESK) OsYield(NULL,NULL); //wait until window deleted from desk
	#if(DEBUG_CALCULATORTASK==1)		    
	    CaptionStringPrint(&DeskDebugCtrl.Caption,"\ntask off");
	#endif
    OsFinish();
}

