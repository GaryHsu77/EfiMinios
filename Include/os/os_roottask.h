#ifndef OS_ROOTTASK_H
#define OS_ROOTTASK_H

extern UINT8 RootTaskName[];

typedef struct{
   OS_TIME SystemTime;
   UINT8 RandomNumber;
}ROOTTASK_CONTROL;

extern ROOTTASK_CONTROL RoottaskCtrl;

VOID OsRootTaskStart(VOID);
VOID RootTaskInit(VOID);
VOID RootTask(VOID *Arg);
VOID RootTaskTimeUpdate(VOID);
VOID RootTaskTimeGet(OS_TIME *pTime);
UINT8 RootTaskTimeSecondGet(VOID);
UINT8 RootTaskRandomNumberGet(VOID);
	
#endif
