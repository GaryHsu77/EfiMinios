#ifndef TERMINALTASK_H
#define TERMINALTASK_H

#define TerminaltaskIdleState 0
#define TerminaltaskRunState 1

#define TERMINAL_WDN_CAPTION WINDOW_WDN_USERDEVICE
#define TERMINAL_WDN_CAPTION2 (WINDOW_WDN_USERDEVICE+1)

typedef struct{
    UINT8 State;
    CAPTION Caption;
    WINDOW_DEVICE DeskDeviceCaption;
    CAPTION Caption2;
    WINDOW_DEVICE DeskDeviceCaption2;
    WINDOW_TABLE UserTable;
    WINDOW Window;
}TERMINALTASK_CONTROL;

#define TERMINAL_TASK_STACK_SIZE 512
extern const UINT8 TerminalTaskName[];

void TerminalTaskInit(TERMINALTASK_CONTROL *pTerminal);
void TerminalTask(void);
void TerminalSvc(TERMINALTASK_CONTROL *pTerminal);

#endif