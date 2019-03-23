#ifndef OSTASK_H
#define OSTASK_H

#define OS_TOTAL_TASK_NUMBER 10
#define OS_TASK_PRIORITY_MAX 10
#define TASK_DEFAULT_STACK_SIZE (64*1024) //GDB

typedef struct{
    UINT32 TaskId;
    OS_TCB *AllTaskList;
    OS_TCB *ReadyListHead[OS_TASK_PRIORITY_MAX];
    OS_TCB *ReadyListTail[OS_TASK_PRIORITY_MAX];
}OS_TASK_CONTROL;

extern OS_TASK_CONTROL OsTaskCtrl;

VOID OsTaskInit(VOID);
EFI_HANDLE OsTaskCreat(Task_Func function, UINT32 StackSize, UINT8* pTaskName, UINT8 Priority, VOID *Arg);
OS_TCB *OsTaskFreeTaskGet(VOID);
VOID OsTaskFreeTaskPut(OS_TCB *pOsTcb);

BOOLEAN OsTaskReadyTaskPut(OS_TCB *pOsTcb);
OS_TCB *OsTaskReadyTaskGet(UINT8 Priority);
BOOLEAN OsTaskReadyTaskDelete(OS_TCB *pOsTask);

BOOLEAN OsTaskAllTaskListTaskPut(OS_TCB *pOsTask);
BOOLEAN OsTaskAllTaskListTaskDelete(OS_TCB *pOsTask);

VOID OsTaskTaskPut(OS_TCB *pOsTask);
BOOLEAN OsTaskTaskDelete(OS_TCB *pOsTask);
BOOLEAN OsTaskTaskCheck(UINT8 *pTaskName);
BOOLEAN OsTaskTaskCheckById(UINT32 TaskId);
OS_TCB *OsTaskTaskGet(UINT8 *pTaskName);
OS_TCB *OsTaskTaskGetById(UINT32 TaskId);

VOID OsTaskFinish(VOID);
VOID OsTaskMemoryDelete(OS_TCB *pOsTask,OS_MEMORY *pOsMemory);
VOID OsTaskMemoryPut(OS_TCB *pOsTask,OS_MEMORY *pOsMemory);
VOID OsTaskResourcePut(OS_TCB *pOsTask,OS_RESOURCE *pOsResource);
VOID OsTaskResourceDelete(OS_TCB *pOsTask,OS_RESOURCE *pOsResource);

extern INTN TASK_SetJmp(TASK_REG *buf);
extern VOID TASK_LongJmp(TASK_REG *buf,int value);
extern UINTN TASK_GetSackPointer();
extern VOID TASK_SetSackPointer_and_call(VOID *tcb,UINTN StackPointer,VOID* func,VOID *arg);

#endif
