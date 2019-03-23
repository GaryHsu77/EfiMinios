#include <includes.h>

OS_TCB *ThreadList = NULL;
OS_TCB *OsTaskCurrent = NULL;
OS_TCB *OsTaskNext = NULL;
BOOLEAN OsRunning;
EFI_EVENT TaskSwitch_Event = NULL;

FUNPTR * BeforeTaskSwitchHookList[] = {TaskSwitchHookList};

VOID OsInit()
{
	EfiInit();
	OsCoreInit();
	OsTaskInit();
	OsSchedulerInit();
	OsEventInit();
	//OsResourceInit();
	OsTimeInit();
	//OsMemoryInit();
}

VOID OsCoreInit()
{
	OsRunning=FALSE;
}

VOID OsStart()
{  
   if(OsRunning==FALSE)
		if(OsSchedulerRootTaskFind()==TRUE){
			OsRunning=TRUE; //GDB : Is this need?
			OsRootTaskStart();
		}
   while(1);
}

VOID BeforeOsTaskSwitchHook()
{
	UINT8 i;
	UINT8 Length = sizeof(BeforeTaskSwitchHookList) / sizeof(BeforeTaskSwitchHookList);
	
	
	Length = 2; //GDB
	for(i = 0; i<Length; i++){
		BeforeTaskSwitchHookList[i]();
	}
}

VOID OsTaskSwitchOut(VOID)
{
	//KeyboardDataScan();
	//MouseDataScan();
	BeforeOsTaskSwitchHook(); //GDB 
	//GDB RtcHandler();
	//GDB TimerHandler();
	OsYield(NULL,NULL);
}

VOID OsYield(EFI_EVENT Event,VOID *Context)
{ 
	MY_MUTEX mutex;
	static BOOLEAN InDispatcher = FALSE;

	if(InDispatcher == TRUE)return;
	mutex = OsEnterCritical();
	InDispatcher = TRUE;
	if(OsTaskCurrent != NULL){
		if(MultiThread_SetJmp(&(OsTaskCurrent->Regs)) == 0){
			//GDB Print(L"%a",OsTaskCurrent->Signature);
			//GDB if(StrEqual(OsTaskCurrent->Signature,"DESK",4))Print(L"%a",OsTaskCurrent->Signature);
			OsTaskCurrent->FirstTime = FALSE;
			if(OsSchedulerNextTaskFind()){
				OsTaskCurrent = OsTaskNext;
				if(OsTaskCurrent->FirstTime){
					OS_TCB *tmp = OsTaskCurrent;
					tmp->FirstTime = FALSE;
					OsExitCritical(mutex);
					gBS->RestoreTPL(tmp->ThreadTPL);

					InDispatcher = FALSE;
					MultiThread_SetSackPointer_and_call((void *)tmp,tmp->Regs.MultiThread_SP,tmp->function_p,tmp->arg);
				}else{
					MultiThread_LongJmp(&(OsTaskCurrent->Regs),0xFF);
				}
			}else{
				MultiThread_LongJmp(&(OsTaskCurrent->Regs),0xFF);
			}
		}else{
			//To Nothing
		}
	}

	InDispatcher = FALSE;
	OsExitCritical(mutex);
}

VOID OsFinish()
{
	MY_MUTEX mutex;
	OS_TCB *pOsTask;
	//OS_RESOURCE *pOsResource,*pOsResource2;
	//OS_MEMORY *pOsMemory,*pOsMemory2;
	OS_TIMER *pOsTimer,*pOsTimer2;

    mutex = OsEnterCritical();
    pOsTask=(OS_TCB *)OsTaskCurrent; // put os task control struct back to free list
    OsTaskTaskDelete(pOsTask);        // delete task from task queue
    // release all resource used by task
	/*
    pOsResource=pOsTask->ResourceList;
    if(pOsResource!=(OS_RESOURCE *)OS_NULL) pOsResource2=pOsResource->TmNext;
    while(pOsResource!=(OS_RESOURCE *)OS_NULL){
    	OsResourceRelease(pOsResource);
    	pOsResource=pOsResource2;
    	if(pOsResource2!=(OS_RESOURCE *)OS_NULL) pOsResource2=pOsResource->TmNext;
    }
	*/
    // release all timer used by task
    pOsTimer=pOsTask->TimerList;
    if(pOsTimer!=(OS_TIMER *)OS_NULL) pOsTimer2=pOsTimer->TmNext;
    while(pOsTimer!=(OS_TIMER *)OS_NULL){
    	OsTimeTimerDelete(pOsTimer);
    	pOsTimer=pOsTimer2;
    	if(pOsTimer!=(OS_TIMER *)OS_NULL) pOsTimer2=pOsTimer->TmNext;
    }
    // release all memory used by task
	/*
    pOsMemory=pOsTask->MemoryList;
    if(pOsMemory!=(OS_MEMORY *)OS_NULL) pOsMemory2=pOsMemory->TmNext;
    while(pOsMemory!=(OS_MEMORY *)OS_NULL){
    	OsMemoryRelease(pOsMemory->pMemory);
    	pOsMemory=pOsMemory2;
    	if(pOsMemory!=(OS_MEMORY *)OS_NULL) pOsMemory2=pOsMemory->TmNext;
    }
	*/
    OsTaskSwitchOut();                // task level task switch
    OsExitCritical(mutex);        	  //this line should never execute
    while(1);                         //this line should never execute
}

VOID OsKill(OS_TCB *pOsTask)
{
	MY_MUTEX mutex;
	//OS_RESOURCE *pOsResource,*pOsResource2;
	//OS_MEMORY *pOsMemory,*pOsMemory2;
	OS_TIMER *pOsTimer,*pOsTimer2;

    mutex = OsEnterCritical(); 
    OsTaskTaskDelete(pOsTask);        // delete task from task queue
    
	// release all resource used by task
	/*
    pOsResource=pOsTask->ResourceList;
    if(pOsTask->ResourceList!=(OS_RESOURCE *)OS_NULL) pOsResource2=pOsResource->TmNext;
    while(pOsResource!=(OS_RESOURCE *)OS_NULL){
    	OsResourceRelease(pOsResource);
    	pOsResource=pOsResource2;
    	if(pOsResource2!=(OS_RESOURCE *)OS_NULL) pOsResource2=pOsResource->TmNext;
    }
	*/
	
    // release all timer used by task
    pOsTimer=pOsTask->TimerList;
    if(pOsTimer!=(OS_TIMER *)OS_NULL) pOsTimer2=pOsTimer->TmNext;
    while(pOsTimer!=(OS_TIMER *)OS_NULL){
    	OsTimeTimerDelete(pOsTimer);
    	pOsTimer=pOsTimer2;
    	if(pOsTimer!=(OS_TIMER *)OS_NULL) pOsTimer2=pOsTimer->TmNext;
    }
	
    // release all memory used by task
	/*
    pOsMemory=pOsTask->MemoryList;
    if(pOsMemory!=(OS_MEMORY *)OS_NULL) pOsMemory2=pOsMemory->TmNext;
    while(pOsMemory!=(OS_MEMORY *)OS_NULL){
    	OsMemoryRelease(pOsMemory->pMemory);
    	pOsMemory=pOsMemory2;
    	if(pOsMemory!=(OS_MEMORY *)OS_NULL) pOsMemory2=pOsMemory->TmNext;
    }
	*/
    if(pOsTask==(OS_TCB *)OsTaskCurrent){
    	 OsTaskSwitchOut(); //need task switch
         OsExitCritical(mutex);
    	 while(1);
    }
    OsExitCritical(mutex);
}
