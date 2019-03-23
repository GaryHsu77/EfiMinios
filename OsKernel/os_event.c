#include <includes.h>

OS_EVENT_CONTROL OsEventCtrl;

VOID OsEventInit(VOID){
	OsEventCtrl.EventList=(OS_EVENT *)OS_NULL;	
}

BOOLEAN OsEventAdd(OS_EVENT *pEvent,UINT8 *pEventName,UINT32 EventType){
	OS_EVENT *pOsEvent;
    MY_MUTEX mutex;
	
    if(pEvent==(OS_EVENT *)OS_NULL) return FALSE;
    mutex = OsEnterCritical();
    pEvent->pName=pEventName;
    pEvent->Type=EventType;
    pEvent->ListHead=(UINT32 *)OS_NULL;
    pEvent->ListTail=(UINT32 *)OS_NULL;
    pEvent->Prev=(OS_EVENT *)OS_NULL;
    pEvent->Next=(OS_EVENT *)OS_NULL;
	if(OsEventCtrl.EventList==(OS_EVENT *)OS_NULL){
		OsEventCtrl.EventList=pEvent;
	}
	else{
	    pOsEvent=OsEventCtrl.EventList;
        pOsEvent->Prev=pEvent;
	    pEvent->Next=pOsEvent;
	    OsEventCtrl.EventList=pEvent;
	}
    OsExitCritical(mutex);
	return TRUE;
}

BOOLEAN OsEventDelete(OS_EVENT *pEvent){
	OS_EVENT *pOsEvent;
    MY_MUTEX mutex;

    if(pEvent==(OS_EVENT *)OS_NULL) return FALSE; 
    if(OsEventCtrl.EventList==(OS_EVENT *)OS_NULL) return FALSE; 
    mutex = OsEnterCritical();
    pOsEvent=OsEventCtrl.EventList;
    while(pOsEvent!=(OS_EVENT *)OS_NULL){
    	if(pOsEvent==pEvent){ //event found
    		if(pOsEvent==OsEventCtrl.EventList){
    			if(OsEventCtrl.EventList->Next!=(OS_EVENT *)OS_NULL){
    				OsEventCtrl.EventList->Next->Prev=(OS_EVENT *)OS_NULL;
    			}
    			OsEventCtrl.EventList=OsEventCtrl.EventList->Next;
    		}
    		else{
    			pOsEvent->Prev->Next=pOsEvent->Next;
    			pOsEvent->Next->Prev=pOsEvent->Prev;
    			pOsEvent->Prev=(OS_EVENT *)OS_NULL;
    			pOsEvent->Next=(OS_EVENT *)OS_NULL;
    		}
            OsExitCritical(mutex);
			return TRUE;
    	}
    	else pOsEvent=pOsEvent->Next;
    }
    OsExitCritical(mutex);
    return FALSE;
}

BOOLEAN OsEventTaskPut(OS_EVENT *pEvent,OS_TCB *pOsTask){
    OS_TCB **pListHead,**pListTail;
    OS_TCB *pHeadTask,*pTailTask;
    //OS_EVENT *pOsEvent;
    
	if(pEvent==(OS_EVENT *)OS_NULL) return FALSE;
	if(pOsTask==(OS_TCB *)OS_NULL) return FALSE;
	pOsTask->TmNext=(OS_TCB *)OS_NULL;
	pOsTask->TmPrev=(OS_TCB *)OS_NULL;
	pListHead=(OS_TCB **)(&pEvent->ListHead);
	pListTail=(OS_TCB **)(&pEvent->ListTail);
	pHeadTask=(OS_TCB *)pEvent->ListHead;
	pTailTask=(OS_TCB *)pEvent->ListTail;
	if(pHeadTask==(OS_TCB *)OS_NULL){
		*pListHead=pOsTask;
		*pListTail=pOsTask;
	}
	else{
		pOsTask->TmPrev=pTailTask;
		pTailTask->TmNext=pOsTask;
		*pListTail=pOsTask;
	}
    return TRUE;
}

OS_TCB *OsEventTaskGet(OS_EVENT *pEvent){
    OS_TCB **pListHead,**pListTail;
    OS_TCB *pHeadTask,*pTailTask,*pOsTask;

	if(pEvent==(OS_EVENT *)OS_NULL) return (OS_TCB *)OS_NULL;
	if(pEvent->ListHead==(UINT32 *)OS_NULL) return (OS_TCB *)OS_NULL;
	pListHead=(OS_TCB **)(&pEvent->ListHead);
	pListTail=(OS_TCB **)(&pEvent->ListTail);
	pHeadTask=(OS_TCB *)pEvent->ListHead;
	pTailTask=(OS_TCB *)pEvent->ListTail;
    if(pHeadTask==pTailTask){
        pOsTask=pHeadTask;
        *pListHead=(OS_TCB *)OS_NULL;
        *pListTail=(OS_TCB *)OS_NULL;
    }
    else{
    	pOsTask=pHeadTask;
    	pHeadTask=pHeadTask->TmNext;
    	pHeadTask->TmPrev=(OS_TCB *)OS_NULL;
    	*pListHead=pHeadTask;
    }    
    pOsTask->TmNext=(OS_TCB *)OS_NULL;        
    pOsTask->TmPrev=(OS_TCB *)OS_NULL;
    return pOsTask;
}

BOOLEAN OsEventWait(OS_EVENT *pEvent,UINT16 TimeTick){
    OS_TCB *pOsTask;
    MY_MUTEX mutex;
	
	if(pEvent==(OS_EVENT *)OS_NULL) return FALSE;
    mutex = OsEnterCritical();
    pOsTask=(OS_TCB *)OsTaskCurrent;
    pOsTask->Status=OS_TASK_PENDING;
    pOsTask->PendingType=OS_PENDING_EVENT;
    pOsTask->TimeDelay=TimeTick;     
    OsEventTaskPut(pEvent,pOsTask);
    OsTaskSwitchOut();
    OsExitCritical(mutex);
    return TRUE;
}

void OsEventUp(OS_EVENT *pEvent){
	OS_TCB *pOsTask;
    MY_MUTEX mutex;

	if(pEvent->ListHead==(UINT32 *)OS_NULL) return;
    mutex = OsEnterCritical();
	while((pOsTask=OsEventTaskGet(pEvent))!=(OS_TCB *)OS_NULL){
		OsTaskReadyTaskPut(pOsTask);
	}
    OsExitCritical(mutex);
}

BOOLEAN OsEventTaskCheck(UINT8 *pTaskName){
	OS_EVENT *pOsEvent;
	OS_TCB *pOsTask;
	
	if(pTaskName==(UINT8 *)OS_NULL) return FALSE;
    pOsEvent=OsEventCtrl.EventList;
	while(pOsEvent!=(OS_EVENT *)OS_NULL){
    	pOsTask=(OS_TCB *)pOsEvent->ListHead;
    	while(pOsTask!=(OS_TCB *)OS_NULL){
    		if(StrEqual(pOsTask->pName,pTaskName,4)==TRUE) return TRUE;	
    		pOsTask=pOsTask->TmNext;
    	}
		pOsEvent=pOsEvent->Next;
    } 
    return FALSE;
}

BOOLEAN OsEventTaskDelete(OS_TCB *pOsTask){
	OS_EVENT *pOsEvent;
	OS_TCB *pOsTask2;
	
	pOsEvent=OsEventCtrl.EventList;
	while(pOsEvent!=(OS_EVENT *)OS_NULL){
    	pOsTask2=(OS_TCB *)pOsEvent->ListHead;
    	while(pOsTask2!=(OS_TCB *)OS_NULL){
    		if(pOsTask2==pOsTask){
    			if(pOsTask2==(OS_TCB *)pOsEvent->ListHead){
    			    if(pOsTask2==(OS_TCB *)pOsEvent->ListTail){
    			        pOsEvent->ListHead=(UINT32 *)OS_NULL;
    			        pOsEvent->ListTail=(UINT32 *)OS_NULL;
    			    }
    			    else{
    			        pOsTask2->TmNext->TmPrev=(OS_TCB *)OS_NULL;
    			        pOsEvent->ListHead=(UINT32 *)pOsTask2->TmNext;
    			    }
    			}
    			else if(pOsTask2==(OS_TCB *)pOsEvent->ListTail){
    			        pOsTask2->TmPrev->TmNext=(OS_TCB *)OS_NULL;
    			        pOsEvent->ListTail=(UINT32 *)pOsTask2->TmPrev;
    			}
    			else{
    			    pOsTask2->TmPrev->TmNext=pOsTask2->TmNext;
    			    pOsTask2->TmNext->TmPrev=pOsTask2->TmPrev;
    			}
    		    return TRUE;	
    		}
    		pOsTask2=pOsTask2->TmNext;
    	}
		pOsEvent=pOsEvent->Next;
    } 
    return FALSE;
}
