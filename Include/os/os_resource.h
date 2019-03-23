#ifndef OS_RESOURCE_H
#define OS_RESOURCE_H

typedef struct{
    OS_RESOURCE *ResourceList;
}OS_RESOURCE_CONTROL;

extern OS_RESOURCE_CONTROL OsResourceCtrl;

void OsResourceInit(void);
BOOLEAN OsResourceAdd(OS_RESOURCE *pResource,UINT8 *pResourceName,UINT32 ResourceType);
UINT32 OsResourceNumberGet(void);
BOOLEAN OsResourceTaskPut(OS_RESOURCE *pResource,OS_TCB *pTask);
OS_TCB *OsResourceTaskGet(OS_RESOURCE *pResource);
BOOLEAN OsResourceAllocate(OS_RESOURCE *pResource,UINT16 TimeTick);
BOOLEAN OsResourceRelease(OS_RESOURCE *pResource);
BOOLEAN OsResourceTaskDelete(OS_TCB *pOsTask);

#endif
