#include <includes.h>

ROOTTASK_CONTROL RoottaskCtrl;

FUNPTR * RootTaskInitHookList[] = {RootTaskInitList};

VOID RootTaskInitHook()
{
	UINT8 i;
	UINT8 Length = sizeof(RootTaskInitHookList) / sizeof(RootTaskInitHookList);
	
	Length = 6; //GDB
	for(i = 0; i<Length; i++){
		RootTaskInitHookList[i]();
	}
}

VOID RootTaskInit()
{
	//drivers initialization
//GDB    InterruptInit();      //interrupt initialization
//GDB	 SystemGuiStringPrint(L">>> InitIDT end <<<<<<<<<<\n");
//GDB1	 VgaInit();            //vga initialization
//GDB1   KeyboardInit();       //keyboard initialization
//GDB1   MouseInit();          //mouse initialization
//GDB    Uart1Init();          //com1 initialization and install event
//GDB    Uart2Init();          //com2 initialization and install event
//GDB    Lpt1Init();           //lpt1 initialization
//GDB1   RtcInit();            //rtc initialization  and install event 
//GDB    FdcInit();           //fdc1 initialization
//GDB1   TimerInit();          //timer initialization
    //middleware initialization...must be done after drivers
//GDB    GuiInit();            //gui initalization and install resource
//GDB    GuiTextInit();
//GDB1   OsdInit();            //osd initialization
    
	RootTaskInitHook();
	
    RoottaskCtrl.SystemTime.Second=0;
    RoottaskCtrl.SystemTime.Minute=0;
    RoottaskCtrl.SystemTime.Hour=0;
    RoottaskCtrl.SystemTime.Day=0;
    RoottaskCtrl.SystemTime.Date=0;
    RoottaskCtrl.SystemTime.Month=0;
    RoottaskCtrl.SystemTime.Year=0;
    RoottaskCtrl.RandomNumber=0;
}

VOID RootTask(VOID *Arg)
{
	EFI_STATUS Status;
	RootTaskInit();
	SystemGuiStringPrint(L"\n>>> RootTask Start   <<<<<<<<<<\n");

	//GDB : I don't why system will hang if MULTTASK set true.
	//if(MULTTASK){
		Status = gBS->CreateEvent(EVT_TIMER | EVT_NOTIFY_SIGNAL,TPL_NOTIFY,OsTaskSwitchOut,NULL,&TaskSwitch_Event);
		if(Status != EFI_SUCCESS){
			gBS->FreePool(OsTaskCurrent);
		}

		Status = gBS->SetTimer(TaskSwitch_Event,TimerPeriodic,500);
		if(Status != EFI_SUCCESS){
			gBS->CloseEvent(TaskSwitch_Event);
			gBS->FreePool(OsTaskCurrent);
		}
	//}
	
	while(1){
		KeyboardDataScan();
		MouseDataScan();
    	if(KeyboardKeyBufferCheck()!=BUFFER_EMPTY){
    		OsEventUp(&pOsDriverKeyboard->KeyboardEvent);
    	}
		
    	if(MouseBufferCheck()!=BUFFER_EMPTY){
    		OsEventUp(&pOsDriverMouse->MouseEvent);
    	}
		
    	//if(Uart1RxBufferCheck()!=BUFFER_EMPTY){
    	//	OsEventUp(&pOsDriverUart1->Uart1Event);
    	//}
		
    	//if(pOsDriverUart2->HasData==true){
    	//	OsEventUp(&pOsDriverUart2->Uart2Event);
    	//}
		
    	if(pOsDriverRtc->HasUpdate==TRUE){
    		RootTaskTimeUpdate();
    		OsEventUp(&pOsDriverRtc->RtcEvent);
        }
		
        //if(pOsDriverKeyboard->LedChange==true){
        //    KeyboardSetLed();
        //    pOsDriverKeyboard->LedChange=false;
        //}
    	RoottaskCtrl.RandomNumber++;
        OsTaskSwitchOut();
    }
}

VOID OsRootTaskStart()
{
	OS_TCB *tmp = OsTaskCurrent;
	tmp->FirstTime = FALSE;
	
	OsTaskCreat(DeskTask, TASK_DEFAULT_STACK_SIZE, "DESK", 0, NULL);	
	MultiThread_SetSackPointer_and_call((void *)tmp,tmp->Regs.MultiThread_SP,tmp->function_p,tmp->arg);
}

VOID RootTaskTimeUpdate(VOID)
{
	MY_MUTEX mutex;
    
    if(pOsDriverRtc->HasUpdate==FALSE) return;
    mutex = OsEnterCritical();
    pOsDriverRtc->HasUpdate=FALSE;
    RoottaskCtrl.SystemTime.Second=pOsDriverRtc->Second;
    RoottaskCtrl.SystemTime.Minute=pOsDriverRtc->Minute;
    RoottaskCtrl.SystemTime.Hour=pOsDriverRtc->Hour;
    RoottaskCtrl.SystemTime.Day=pOsDriverRtc->Day;
    RoottaskCtrl.SystemTime.Date=pOsDriverRtc->Date;
    RoottaskCtrl.SystemTime.Month=pOsDriverRtc->Month;
    RoottaskCtrl.SystemTime.Year=pOsDriverRtc->Year;
    OsExitCritical(mutex);
}

VOID RootTaskTimeGet(OS_TIME *pTime)
{
    MY_MUTEX mutex;
	
    mutex = OsEnterCritical();
    pTime->Second=RoottaskCtrl.SystemTime.Second;
    pTime->Minute=RoottaskCtrl.SystemTime.Minute;
    pTime->Hour=RoottaskCtrl.SystemTime.Hour;
    pTime->Day=RoottaskCtrl.SystemTime.Day;
    pTime->Date=RoottaskCtrl.SystemTime.Date;
    pTime->Month=RoottaskCtrl.SystemTime.Month;
    pTime->Year=RoottaskCtrl.SystemTime.Year;
    OsExitCritical(mutex);
}

UINT8 RootTaskTimeSecondGet(VOID){
    return RoottaskCtrl.SystemTime.Second;
}

UINT8 RootTaskRandomNumberGet(VOID){
    return RoottaskCtrl.RandomNumber;
}
