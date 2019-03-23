#include <includes.h>

OS_TASK_CONTROL OsTaskCtrl;

void OsTaskInit(void)
{
	UINT32 i; 
	OsTaskCtrl.TaskId=0;
	OsTaskCtrl.AllTaskList=(OS_TCB *)OS_NULL;
	for(i=0;i<OS_TOTAL_TASK_NUMBER;i++){
		OsTaskCtrl.ReadyListHead[i]=(OS_TCB *)OS_NULL;
		OsTaskCtrl.ReadyListTail[i]=(OS_TCB *)OS_NULL;
	}    
}

EFI_HANDLE OsTaskCreat(Task_Func function, UINT32 StackSize, UINT8* pTaskName, UINT8 Priority, VOID *Arg)
{
	OS_TCB *tcb;
	EFI_STATUS Status;
	MY_MUTEX mutex;
	VOID *Stack;
	mutex = OsEnterCritical();

	Status = gBS->AllocatePool(EfiBootServicesData,sizeof(OS_TCB),&tcb);
	if(Status != EFI_SUCCESS){
		return NULL;
	}

	gBS->SetMem(tcb->Signature, 4, 0);
	gBS->CopyMem(tcb->Signature,pTaskName,4);
	tcb->Next = NULL;

	Status = gBS->AllocatePool(EfiBootServicesData,StackSize,&Stack); // Use 8KB Stack
	if(Status != EFI_SUCCESS){
		gBS->FreePool(tcb);
		return NULL;
	}

	tcb->arg = Arg;
	tcb->function_p = function;

	tcb->Priority = Priority;
	tcb->MainThread = FALSE;
	tcb->FirstTime = TRUE;

    //task control structure initialization
    tcb->ResourceList=(OS_RESOURCE *)OS_NULL;
    tcb->TimerList=(OS_TIMER *)OS_NULL;
    tcb->MemoryList=(OS_MEMORY *)OS_NULL;
    tcb->Id=OsTaskCtrl.TaskId++;
    tcb->TimeDelay=0;
    tcb->Window=OS_NULL;
	
	tcb->ThreadTPL = gBS->RaiseTPL(TPL_HIGH_LEVEL);
	gBS->RestoreTPL(tcb->ThreadTPL);

	tcb->Stack = (EFI_PHYSICAL_ADDRESS)Stack;
	gBS->SetMem(&(tcb->Regs),sizeof(TASK_REG),0);
	tcb->Regs.MultiThread_SP = (UINTN)(tcb->Stack + StackSize);

	OsTaskReadyTaskPut(tcb);
	OsExitCritical(mutex);
	return (EFI_HANDLE)tcb;
}

BOOLEAN OsTaskReadyTaskPut(OS_TCB *pOsTask)
{
	OS_TCB **pListHead,**pListTail;
    OS_TCB *pHead,*pTail;
    
	if(pOsTask==(OS_TCB *)OS_NULL) return OS_FALSE;
    if(pOsTask->Priority>=OS_TASK_PRIORITY_MAX) return OS_FALSE; // no support priority level
    pOsTask->TmPrev=(OS_TCB *)OS_NULL;                 // clean linking relationship        
    pOsTask->TmNext=(OS_TCB *)OS_NULL;                 // clean linking relationship       
    pOsTask->Status=OS_TASK_READY;                      // task status ready for run
    pOsTask->PendingType=OS_PENDING_NONE;               // reset pending type
    pOsTask->TimeDelay=0;                               // reset delay timer  
    pListHead=&OsTaskCtrl.ReadyListHead[pOsTask->Priority];  // get task list head related to priority
    pListTail=&OsTaskCtrl.ReadyListTail[pOsTask->Priority];  // get task list head related to priority
    pHead=OsTaskCtrl.ReadyListHead[pOsTask->Priority];       // get head OS_TASK
    pTail=OsTaskCtrl.ReadyListTail[pOsTask->Priority];       // get tail OS_TASK
    if(pHead==(OS_TCB *)OS_NULL){                      // if list is empty, add task OS_TASK to list head
        *pListHead=pOsTask;      
        *pListTail=pOsTask;    
    }
    else{                                               // if list is not empty, add task OS_TASK to list head
    	pOsTask->TmPrev=pTail;
    	pTail->TmNext=pOsTask;
    	*pListTail=pOsTask;
    }
/*================================>>>
	if(ThreadList == NULL){
		ThreadList = pOsTask;
	}else{
		OS_TCB *tmp = ThreadList;
		while(tmp->Next != NULL){
			tmp = tmp->Next;
		}
		tmp->Next = pOsTask;
	}
//================================<<<*/
    return OS_TRUE;
}

OS_TCB *OsTaskReadyTaskGet(UINT8 Priority)
{
    OS_TCB **pListHead,**pListTail;
    OS_TCB *pHead,*pTail,*pOsTask;

    if(Priority>=OS_TASK_PRIORITY_MAX) return (OS_TCB *)OS_NULL;
    pHead=OsTaskCtrl.ReadyListHead[Priority];        
    if(pHead==(OS_TCB *)OS_NULL) return (OS_TCB *)OS_NULL;
    pListHead=&OsTaskCtrl.ReadyListHead[Priority];
    pListTail=&OsTaskCtrl.ReadyListTail[Priority];
    pTail=OsTaskCtrl.ReadyListTail[Priority];
    if(pHead==pTail){
        pOsTask=pHead;
        *pListHead=(OS_TCB *)OS_NULL;
        *pListTail=(OS_TCB *)OS_NULL;
    }
    else{
    	pOsTask=pHead;
    	pHead=pHead->TmNext;
    	pHead->TmPrev=(OS_TCB *)OS_NULL;
    	*pListHead=pHead;
    }    
    pOsTask->TmPrev=(OS_TCB *)OS_NULL;        
    pOsTask->TmPrev=(OS_TCB *)OS_NULL;
    return pOsTask;
}

BOOLEAN OsTaskReadyTaskDelete(OS_TCB *pOsTask)
{
    OS_TCB **pListHead,**pListTail;
    OS_TCB *pHead,*pTail,*pOsTask2;
	
	if(pOsTask->Priority>=OS_TASK_PRIORITY_MAX) return FALSE;
	pOsTask2=OsTaskCtrl.ReadyListHead[pOsTask->Priority];
	while(pOsTask2!=(OS_TCB *)OS_NULL){
		if(pOsTask2==pOsTask) break;
		pOsTask2=pOsTask2->TmNext;
	}
	if(pOsTask2==(OS_TCB *)OS_NULL) return FALSE;
    pHead=OsTaskCtrl.ReadyListHead[pOsTask->Priority];     
    pTail=OsTaskCtrl.ReadyListTail[pOsTask->Priority];   
    pListHead=&OsTaskCtrl.ReadyListHead[pOsTask->Priority];
    pListTail=&OsTaskCtrl.ReadyListTail[pOsTask->Priority];
    if(pOsTask==pHead){
	    if(pOsTask==pTail){
	        *pListHead=(OS_TCB *)OS_NULL;
	        *pListTail=(OS_TCB *)OS_NULL;
	    }
	    else{
	        pOsTask->TmNext->TmPrev=(OS_TCB *)OS_NULL;
	        *pListHead=pOsTask->TmNext;
	    }
	}
	else if(pOsTask==pTail){
	        pOsTask->TmPrev->TmNext=(OS_TCB *)OS_NULL;
	        *pListTail=pOsTask->TmPrev;
	}
	else{
	    pOsTask->TmPrev->TmNext=pOsTask->TmNext;
	    pOsTask->TmNext->TmPrev=pOsTask->TmPrev;
	}
    return TRUE;
}

BOOLEAN OsTaskAllTaskListTaskPut(OS_TCB *pOsTask)
{
	if(pOsTask==(OS_TCB *)OS_NULL) return FALSE;
    pOsTask->Prev=(OS_TCB *)OS_NULL;                 // clean linking relationship        
    pOsTask->Next=(OS_TCB *)OS_NULL;                 // clean linking relationship   
    if(OsTaskCtrl.AllTaskList==(OS_TCB *)OS_NULL){
    	OsTaskCtrl.AllTaskList=pOsTask;
    }
    else{
        pOsTask->Next=OsTaskCtrl.AllTaskList; 
        OsTaskCtrl.AllTaskList->Prev=pOsTask;
        OsTaskCtrl.AllTaskList=pOsTask;
    }	
    return TRUE;	
}

BOOLEAN OsTaskAllTaskListTaskDelete(OS_TCB *pOsTask){
	OS_TCB *pOsTask2;

	if(OsTaskCtrl.AllTaskList==(OS_TCB *)OS_NULL) return FALSE;	
	pOsTask2=OsTaskCtrl.AllTaskList;
	while(pOsTask2!=(OS_TCB *)OS_NULL){
		if(pOsTask2==pOsTask) break;
		pOsTask2=pOsTask2->Next;
	}
	if(pOsTask2==(OS_TCB *)OS_NULL) return FALSE; //task is not found in alltasklist
	if(pOsTask==OsTaskCtrl.AllTaskList){
		if(pOsTask->Next==(OS_TCB *)OS_NULL){
			OsTaskCtrl.AllTaskList=(OS_TCB *)OS_NULL;
		}
		else{
		    pOsTask->Next->Prev=(OS_TCB *)OS_NULL;
		    OsTaskCtrl.AllTaskList=pOsTask->Next;
		}
	}
	else{
		if(pOsTask->Next==(OS_TCB *)OS_NULL){
			pOsTask->Prev->Next=(OS_TCB *)OS_NULL;
		}
		else{
		    pOsTask->Prev->Next=pOsTask->Next;
		    pOsTask->Next->Prev=pOsTask->Prev;
		}
	}
    pOsTask->Prev=(OS_TCB *)OS_NULL;
    pOsTask->Next=(OS_TCB *)OS_NULL;
    return TRUE;	
}

VOID OsTaskTaskPut(OS_TCB *pOsTask)
{
	if(pOsTask==(OS_TCB *)OS_NULL) return;
    if(OsTaskReadyTaskPut(pOsTask)==FALSE) return; //add task to task priority list
	OsTaskAllTaskListTaskPut(pOsTask);
}

BOOLEAN OsTaskTaskDelete(OS_TCB *pOsTask)
{
	if(pOsTask==(OS_TCB *)OS_NULL) return OS_FALSE;
	if(pOsTask->Status==OS_TASK_EXECUTION) pOsTask->Status=OS_TASK_FREE;
	else if(pOsTask->Status==OS_TASK_READY) OsTaskReadyTaskDelete(pOsTask);
	else if(pOsTask->Status==OS_TASK_PENDING){
//GDB		if(pOsTask->PendingType==OS_PENDING_TIME) OsEventTaskDelete(pOsTask);
//GDB		else if(pOsTask->PendingType==OS_PENDING_RESOURCE) OsResourceTaskDelete(pOsTask);
//GDB		else if(pOsTask->PendingType==OS_PENDING_EVENT) OsEventTaskDelete(pOsTask);
//GDB		else if(pOsTask->PendingType==OS_PENDING_NONE){;} // this case should never happen
//GDB		else{;} // this case should never happen
	}
	OsTaskAllTaskListTaskDelete(pOsTask);  //delete task from all-task-list
    return TRUE;
}

BOOLEAN OsTaskTaskCheck(UINT8 *pTaskName){
	OS_TCB *pOsTask;

	pOsTask=OsTaskCtrl.AllTaskList;
	while(pOsTask!=(OS_TCB *)OS_NULL){
		if(StrEqual(pOsTask->pName,pTaskName,4)==OS_TRUE) return TRUE;
		pOsTask=pOsTask->Next;
	}
    return FALSE;
}

BOOLEAN OsTaskTaskCheckById(UINT32 TaskId){
	OS_TCB *pOsTask;

	pOsTask=OsTaskCtrl.AllTaskList;
	while(pOsTask!=(OS_TCB *)OS_NULL){
		if(pOsTask->Id==TaskId) return TRUE;	
		pOsTask=pOsTask->Next;
	}
    return FALSE;
}

OS_TCB *OsTaskTaskGet(UINT8 *pTaskName)
{
	OS_TCB *pOsTask;

	pOsTask=OsTaskCtrl.AllTaskList;
	while(pOsTask!=(OS_TCB *)OS_NULL){
		if(StrEqual(pOsTask->pName,pTaskName,4)==OS_TRUE) return pOsTask;	
		pOsTask=pOsTask->Next;
	}
    return (OS_TCB *)OS_NULL;
}

OS_TCB *OsTaskTaskGetById(UINT32 TaskId)
{
	OS_TCB *pOsTask;

	pOsTask=OsTaskCtrl.AllTaskList;
	while(pOsTask!=(OS_TCB *)OS_NULL){
		if(pOsTask->Id==TaskId) return pOsTask;	
		pOsTask=pOsTask->Next;
	}
    return (OS_TCB *)OS_NULL;
}

VOID OsTaskMemoryPut(OS_TCB *pOsTask,OS_MEMORY *pOsMemory)
{

}

VOID OsTaskMemoryDelete(OS_TCB *pOsTask,OS_MEMORY *pOsMemory)
{

}

VOID OsTaskResourcePut(OS_TCB *pOsTask,OS_RESOURCE *pOsResource)
{
	
}

VOID OsTaskResourceDelete(OS_TCB *pOsTask,OS_RESOURCE *pOsResource)
{
	
}

VOID OsTaskFinish(void)
{

}