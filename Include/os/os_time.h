#ifndef OS_TIME_H
#define OS_TIME_H

typedef struct{
    UINT32 TimeTick;
    OS_EVENT TimeEvent;
    OS_TIMER *TimerList;
}OS_TIME_CONTROL;

extern OS_EVENT *OsTimeEventListHead;
extern OS_TCB *OsTimeDelayListHead;
extern OS_TIME_CONTROL OsTimeCtrl;
extern VOID OsTimeInit(VOID);
extern VOID OsTimeEventHandler(VOID);
extern VOID OsTimeDelay(UINT32 Ticks);
extern VOID OsTimeEventListPut(OS_EVENT *pOsEvent);
extern UINT8 OsTimeEventListDelete(OS_EVENT *pOsEvent);
VOID OsTimeTimerPut(OS_TIMER *pOsTimer);
VOID OsTimeTimerDelete(OS_TIMER *pOsTimer);
UINT32 OsTimeTimetickGet(VOID);

#endif


