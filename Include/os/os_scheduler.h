#ifndef OS_SCHEDULER_H
#define OS_SCHEDULER_H

typedef struct{
    UINT16 TaskSwitchTimer;  // timer for task switch
    UINT8  CurrentPriority;
}OS_SCHEDULER_CONTROL;

extern OS_SCHEDULER_CONTROL OsSchedulerCtrl;

VOID OsSchedulerInit(VOID);
UINT8 OsSchedulerRootTaskFind(VOID);
BOOLEAN OsSchedulerNextTaskFind(VOID);

#endif
