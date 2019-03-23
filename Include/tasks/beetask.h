#ifndef BEETASK_H
#define BEETASK_H

#define BEE_TASK_STACK_SIZE 512
extern const UINT8 BeeTaskName[];

void BeeTaskInit(BEEGAME_CONTROL *pBeegameCtrl);
void BeeTask(void);
void BeeMemoryCopy(UINT8* pSource,UINT8* pDestination,UINT32 Length);

#endif
