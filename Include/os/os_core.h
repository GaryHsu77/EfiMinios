#ifndef OSCORE_H
#define OSCORE_H

extern const UINT8 OsUnkown[];
extern UINT32 OsTaskSwHook;
extern BOOLEAN OsRunning;
extern OS_TCB *ThreadList;
extern OS_TCB *OsTaskCurrent;
extern OS_TCB *OsTaskNext;
extern EFI_EVENT TaskSwitch_Event;
extern BOOLEAN MULTTASK;
VOID OsInit();
VOID OsCoreInit();
VOID OsYield(EFI_EVENT Event,VOID *Context);
VOID OsStart();
VOID OsFinish();
VOID OsKill(OS_TCB *pOsTask);

#endif
