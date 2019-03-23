#include <includes.h>

OS_SCHEDULER_CONTROL OsSchedulerCtrl;

VOID OsSchedulerInit(VOID)
{  
    OsSchedulerCtrl.TaskSwitchTimer=OS_TASK_SWITCH_TIME;
    OsSchedulerCtrl.CurrentPriority=0;
}

BOOLEAN OsSchedulerRootTaskFind(VOID)
{
//	UINT32 i;
	OS_TCB *pOsTask;    
	
    if((pOsTask=OsTaskReadyTaskGet(0))==(OS_TCB *)OS_NULL) return FALSE;
    OsSchedulerCtrl.CurrentPriority=0; // root task is at 0 priority
    pOsTask->Status=OS_TASK_EXECUTION;
    OsTaskCurrent=pOsTask;
    OsTaskNext=pOsTask; 	// this line is important...if only roottask runs
                            // scheduler will not find next task
                            // OsTaskNext must be the same as OsTaskCurrent
//	for(i=0;i<sizeof(OS_TCB);i++){
//		if(((UINT8 *)tmp)[i]!=((UINT8 *)tmp)[i])
//			SystemGuiStringPrint(L"+i = %d+\n", i);
//	}
	return TRUE;
}

BOOLEAN OsSchedulerNextTaskFind(VOID)
{
	OS_TCB *pOsTask;    
    UINT8 TempPriority,i;
    MY_MUTEX mutex = OsEnterCritical();

    TempPriority=OsSchedulerCtrl.CurrentPriority;
    for(i=0;i<OS_TASK_PRIORITY_MAX;i++){
    	TempPriority++;
    	if(TempPriority==OS_TASK_PRIORITY_MAX) TempPriority=0;
    	if((pOsTask=OsTaskReadyTaskGet(TempPriority))!=(OS_TCB *)OS_NULL) break;
    } 
    if(pOsTask==(OS_TCB *)OS_NULL){
    	 OsExitCritical(mutex);
    	 return FALSE;
    }        
    OsSchedulerCtrl.CurrentPriority=TempPriority;
    OsSchedulerCtrl.TaskSwitchTimer=OS_TASK_SWITCH_TIME;   
    pOsTask->Status=OS_TASK_EXECUTION;
    OsTaskNext=pOsTask;
    pOsTask=OsTaskCurrent; 			  //if task's memory is released,
									  //pOsTask will point to a released memory,but that's ok
                                      //OsMemory will do nothing to this memory,
                                      //memory data in pOsTask is still valid at this moment
    if(pOsTask->Status==OS_TASK_EXECUTION) OsTaskReadyTaskPut(pOsTask);             
    OsExitCritical(mutex);
	return TRUE;
}



