#include <includes.h>

OS_TIME_CONTROL OsTimeCtrl;

VOID OsTimeInit(VOID)
{   
    OsTimeCtrl.TimeTick=0;
    OsTimeCtrl.TimerList=(OS_TIMER *)OS_NULL;
    OsEventAdd(&OsTimeCtrl.TimeEvent,"OSTIME",OS_EVENT_TIME);
}

VOID OsTimeEventHandler(VOID)
{
    OS_TCB *pOsTask,*pOsTask2;
    OS_TCB *pHeadTask,*pTailTask;
    OS_TCB **pListHead,**pListTail;
    OS_EVENT *pEvent;
    OS_TIMER *pOsTimer;
//GDB    OS_RESOURCE *pResource;
	
    MY_MUTEX mutex = OsEnterCritical();
	
    OsTimeCtrl.TimeTick++;
    
    //handle os timer
    pOsTimer=OsTimeCtrl.TimerList;
    while(pOsTimer!=(OS_TIMER *)OS_NULL){
    	if(pOsTimer->Timer!=0) pOsTimer->Timer--;
    	pOsTimer=pOsTimer->Next;
    }
    // handle events
    pEvent=OsEventCtrl.EventList;
    while(pEvent!=(OS_EVENT *)OS_NULL){
    	pListHead=(OS_TCB **)(&pEvent->ListHead);
    	pListTail=(OS_TCB **)(&pEvent->ListTail);
    	pHeadTask=(OS_TCB *)pEvent->ListHead;
    	pTailTask=(OS_TCB *)pEvent->ListTail;
        pOsTask=pHeadTask;
        while(pOsTask!=(OS_TCB *)OS_NULL){
            if(pOsTask->TimeDelay!=0) pOsTask->TimeDelay--;
            if(pOsTask->TimeDelay==0){
                pOsTask2=pOsTask;
                if(pOsTask==pHeadTask){ 
                    if(pHeadTask->TmNext==(OS_TCB *)OS_NULL){
                        pEvent->ListHead=(UINT32 *)OS_NULL;
                        pEvent->ListTail=(UINT32 *)OS_NULL;
                        pOsTask=(OS_TCB *)OS_NULL;
                    }
                    else{
                        pEvent->ListHead=(UINT32 *)pHeadTask->TmNext;
                        pHeadTask=pHeadTask->TmNext;
                        pHeadTask->TmPrev=(OS_TCB *)OS_NULL; 
                        pOsTask=pHeadTask;             
                    }                
                }        
                else if(pOsTask==pTailTask){ 
            		pEvent->ListTail=(UINT32 *)pTailTask->TmPrev;
            		pTailTask=pTailTask->TmPrev;
            		pTailTask->TmNext=(OS_TCB *)OS_NULL;
            		pOsTask=(OS_TCB *)OS_NULL;
                }
                else{
                    pOsTask->TmPrev->TmNext=pOsTask->TmNext;
                    pOsTask->TmNext->TmPrev=pOsTask->TmPrev; 
                    pOsTask=pOsTask->TmNext;     
                }
                OsTaskReadyTaskPut(pOsTask2);
            }
            else pOsTask=pOsTask->TmNext;
        } 
        pEvent=pEvent->Next;   
    }
/*
    pResource=OsResourceCtrl.ResourceList;
    while(pResource!=(OS_EVENT *)OS_NULL){
    	pListHead=(OS_TCB **)(&pResource->ListHead);
    	pListTail=(OS_TCB **)(&pResource->ListTail);
    	pHeadTask=(OS_TCB *)pResource->ListHead;
    	pTailTask=(OS_TCB *)pResource->ListTail;
        pOsTask=pHeadTask;
        while(pOsTask!=(OS_TCB *)OS_NULL){
            if(pOsTask->TimeDelay!=0) pOsTask->TimeDelay--;
            if(pOsTask->TimeDelay==0){
                pOsTask2=pOsTask;
                if(pOsTask==pHeadTask){
                    if(pHeadTask->TmNext==(OS_TCB *)OS_NULL){
                        pResource->ListHead=(UINT32 *)OS_NULL;
                        pResource->ListTail=(UINT32 *)OS_NULL;
                        pOsTask=(OS_TCB *)OS_NULL;
                    }
                    else{
                        pResource->ListHead=(UINT32 *)pHeadTask->TmNext;
                        pHeadTask=pHeadTask->TmNext;
                        pHeadTask->TmPrev=(OS_TCB *)OS_NULL; 
                        pOsTask=pHeadTask;             
                    }                
                }        
                else if(pOsTask==pTailTask){
            		pResource->ListTail=(UINT32 *)pTailTask->TmPrev;
            		pTailTask=pTailTask->TmPrev;
            		pTailTask->TmNext=(OS_TCB *)OS_NULL;
            		pOsTask=(OS_TCB *)OS_NULL;
                }
                else{
                    pOsTask->TmPrev->TmNext=pOsTask->TmNext;
                    pOsTask->TmNext->TmPrev=pOsTask->TmPrev; 
                    pOsTask=pOsTask->TmNext;                                  
                }
                OsTaskReadyTaskPut(pOsTask2);
            }
            else pOsTask=pOsTask->TmNext;
        } 
        pResource=pResource->Next;   
    }
*/
    OsExitCritical(mutex);
}

VOID OsTimeDelay(UINT32 Ticks)
{
    OS_TCB *pOsTask;
    MY_MUTEX mutex = OsEnterCritical();
	
    if(Ticks==0){
        OsExitCritical(mutex);
        return;    
    }
    pOsTask=(OS_TCB *)OsTaskCurrent;
    pOsTask->Status=OS_TASK_PENDING;
    pOsTask->PendingType=OS_PENDING_TIME;
    pOsTask->TimeDelay=Ticks;        
    OsEventTaskPut(&OsTimeCtrl.TimeEvent,pOsTask);
    OsTaskSwitchOut();
    OsExitCritical(mutex);
}

VOID OsTimeTimerPut(OS_TIMER *pOsTimer)
{
    OS_TCB *pOsTask;
    MY_MUTEX mutex;
    
	if(pOsTimer==(OS_TIMER *)OS_NULL) return;
    mutex = OsEnterCritical();
	
    //add timer onto os timer list
	pOsTimer->Prev=(OS_TIMER *)OS_NULL;
	pOsTimer->Next=(OS_TIMER *)OS_NULL;
	if(OsTimeCtrl.TimerList==(OS_TIMER *)OS_NULL){
		OsTimeCtrl.TimerList=pOsTimer;
	}
	else{
	    pOsTimer->Next=OsTimeCtrl.TimerList;
	    OsTimeCtrl.TimerList->Prev=pOsTimer;
	    OsTimeCtrl.TimerList=pOsTimer;
	}
    //add timer onto task timer list
	pOsTask=(OS_TCB *)OsTaskCurrent;
	pOsTimer->TmPrev=(OS_TIMER *)OS_NULL;
	pOsTimer->TmNext=(OS_TIMER *)OS_NULL;
	if(pOsTask->TimerList==(OS_TIMER *)OS_NULL){
		pOsTask->TimerList=pOsTimer;
	}
	else{
	    pOsTimer->TmNext=pOsTask->TimerList;
	    pOsTask->TimerList->TmPrev=pOsTimer;
	    pOsTask->TimerList=pOsTimer;
	}
    OsExitCritical(mutex);
}


VOID OsTimeTimerDelete(OS_TIMER *pOsTimer)
{
//GDB    OS_TCB *pOsTask;
    OS_TIMER *pOsTimer2;
    MY_MUTEX mutex;

	if(pOsTimer==(OS_TIMER *)OS_NULL) return;
    mutex = OsEnterCritical();
	
    pOsTimer2=OsTimeCtrl.TimerList;
    while(pOsTimer2!=(OS_TIMER *)OS_NULL){
        if(pOsTimer2==pOsTimer) break;
        pOsTimer2=pOsTimer2->Next;
    }
    if(pOsTimer2==(OS_TIMER *)OS_NULL){ // timer no found
    	OsExitCritical(mutex);
    	return;
    }
    //delete timer from os timer list
	if(pOsTimer==OsTimeCtrl.TimerList){
		if(pOsTimer->Next==(OS_TIMER *)OS_NULL) OsTimeCtrl.TimerList=(OS_TIMER *)OS_NULL;
		else{
		    pOsTimer->Next->Prev=(OS_TIMER *)OS_NULL;
		    OsTimeCtrl.TimerList=pOsTimer->Next;
		}
	}
	else{
		if(pOsTimer->Next==(OS_TIMER *)OS_NULL) pOsTimer->Prev->Next=(OS_TIMER *)OS_NULL;
		else{
		    pOsTimer->Prev->Next=pOsTimer->Next;
		    pOsTimer->Next->Prev=pOsTimer->Prev;
		}
	}
	pOsTimer->Next=(OS_TIMER *)OS_NULL;
	pOsTimer->Prev=(OS_TIMER *)OS_NULL;
    OsExitCritical(mutex);
}

UINT32 OsTimeTimetickGet(VOID)
{
	return OsTimeCtrl.TimeTick;
}


