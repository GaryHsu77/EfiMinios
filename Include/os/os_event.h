#ifndef OS_EVENT_H
#define OS_EVENT_H

typedef struct{
    OS_EVENT *EventList;
}OS_EVENT_CONTROL;
 
extern OS_EVENT_CONTROL OsEventCtrl;

VOID OsEventInit(VOID);
BOOLEAN OsEventAdd(OS_EVENT *pEvent,UINT8 *pEventName,UINT32 EventType);
UINT32 OsEventNumberGet(VOID);
BOOLEAN OsEventTaskPut(OS_EVENT *pEvent,OS_TCB *pTask);
OS_TCB *OsEventTaskGet(OS_EVENT *pEvent);
VOID OsEventUp(OS_EVENT *pEvent);
BOOLEAN OsEventTaskCheck(UINT8 *pTaskName);
BOOLEAN OsEventTaskDelete(OS_TCB *pOsTask);

#endif
