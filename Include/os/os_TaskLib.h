#include <efi.h>
#include <efiapi.h>
#include <efilib.h>

typedef EFI_TPL MY_MUTEX;
VOID MultiThread_Yield();

extern INTN MultiThread_SetJmp(TASK_REG *buf);
extern VOID MultiThread_LongJmp(TASK_REG *buf,int value);
extern UINTN MultiThread_GetSackPointer();
extern VOID MultiThread_SetSackPointer_and_call(VOID *tcb,UINTN StackPointer,Task_Func func,VOID *arg);
extern VOID MultiThread_RemoveThread(OS_TCB *tcb);