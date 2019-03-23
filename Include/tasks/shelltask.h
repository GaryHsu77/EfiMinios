#ifndef SHELLTASK_H
#define SHELLTASK_H

#define ShelltaskIdleState 0
#define ShelltaskRunState 1

#define SHELL_WDN_CAPTION WINDOW_WDN_USERDEVICE

typedef struct{
    UINT8 TaskState;
    CONSOLE Console;
    CAPTION Caption;
    WINDOW_DEVICE DeskDeviceCaption;
    WINDOW_TABLE UserTable;
    WINDOW Window;
}SHELL_CONTROL;

#define SHELL_TASK_STACK_SIZE 512
extern const UINT8 ShellTaskName[];

void ShellTaskInit(SHELL_CONTROL *pShell);
void ShellTask(void);

#endif

