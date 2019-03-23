#include <includes.h>

TIMER_CONTROL *pOsDriverTimer;

VOID TimerInit(VOID){
	EFI_STATUS Status ;	

	Status = gBS->AllocatePool(EfiBootServicesData,sizeof(TIMER_CONTROL),&pOsDriverTimer);
	if(Status != EFI_SUCCESS)return;
    //PicIrqDisable(IRQ0_TIMER);
    OutByte(TIMER_MODE,RATE_GENERATOR);
    OutByte(TIMER0,(UINT8)(TIMER_FREQ/HZ));
    OutByte(TIMER0,(UINT8)((TIMER_FREQ/HZ)>>8));
    pOsDriverTimer->MyTimer.Timer=0;
	OsTimeTimerPut(&pOsDriverTimer->MyTimer);
    //InterruptIrqHandlerSet(IRQ0_TIMER,TimerHandler);
    //PicIrqEnable(IRQ0_TIMER);
	
	SystemGuiStringPrint(L">>> TimerInit end    <<<<<<<<<<\n");
}

VOID TimerHandler(VOID){
	if(!TIMER_START)return;
    if(OsSchedulerCtrl.TaskSwitchTimer!=0) OsSchedulerCtrl.TaskSwitchTimer--;
    if(OsRunning==TRUE){
        #if(OS_TIME_EVENT_ENABLE==1)
            OsTimeEventHandler(); 
        #endif
        if(OsSchedulerCtrl.TaskSwitchTimer==0){
            #if(OS_INT_LEVEL_CSW_ENABLE==1)
				//GDB: If this do that will cause mouse unwork!
				//OsTaskSwitchOut();
            #endif
        }
	}
}
