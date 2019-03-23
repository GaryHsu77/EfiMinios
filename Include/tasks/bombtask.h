#ifndef BOMBTASK_H
#define BOMBTASK_H

#define BOMB_TASK_STACK_SIZE 512
extern const UINT8 BombTaskName[];

void BombTaskInit(BOMB_CONTROL *pBombCtrl);
void BombTask(void);

#endif
