#ifndef OS_MEMORY_H
#define OS_MEMORY_H

#define OS_MEMORY_START SYSTEM_MEMORY_BASE
#define OS_MEMORY_LENGTH (SYSTEM_MEMORY_TOTAL-SYSTEM_MEMORY_BASE) 

typedef struct{
    UINT8 *pMemoryStart;
    UINT8 *pMemoryCurrent;
    UINT32 MemoryTotalLength;
    OS_MEMORY *UsedMemoryList;
    OS_MEMORY *FreeMemoryList;
}OS_MEMORY_CONTROL;

extern OS_MEMORY_CONTROL OsMemoryCtrl;

void OsMemoryInit(void);
UINT8 *OsMemoryAllocate(UINT32 Length);
BOOLEAN OsMemoryRelease(UINT8 *pMemory);
void OsMemoryUsedMemoryPut(OS_MEMORY *pOsMemory);
void OsMemoryFreeMemoryPut(OS_MEMORY *pOsMemory);
OS_MEMORY *OsMemoryFreeMemoryScan(UINT32 Length);
BOOLEAN OsMemoryOwnerChange(UINT8 *pMemory,OS_TCB *pTask);

#endif
