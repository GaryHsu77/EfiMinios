#ifndef CONSOLE_H
#define CONSOLE_H

#define ConsoleIdleState          0
#define ConsoleInitialState       1
#define ConsoleArgumentWaitState   2
#define ConsoleDispatchState      3
#define ConsoleExecutionState     4
#define ConsoleExecutionStopState 5

#define ConsoleItemStartState 0
#define ConsoleItemRunState   1
#define ConsoleItemStopState  2

#define ConsoleArgumentSearchState    0
#define ConsoleArgumentGoThroughState 1
#define ConsoleArgumentDoneState      2

#define CONSOLE_ARGV_MAX   5
#define CONSOLE_BUFFER_SIZE 100
#define CONSOLE_LINE_MAX 5
#define CONSOLE_CHAR_MAX 30

typedef struct{
    UINT8 State;  
    UINT8 ExecuteItem;
    UINT8 ExecuteState;
    UINT8 Argc;
    UINT8 *pArgv[CONSOLE_ARGV_MAX];
    UINT8 Put;
    UINT8 *pDataBuffer;
    UINT8 *pMemory;
    CAPTION *pCaption;
    WINDOW *pWindow;
}CONSOLE;

BOOLEAN ConsoleCreat(CONSOLE *pConsole);
void ConsoleSvc(CONSOLE *pConsole);
void ConsoleArgumentSvc(CONSOLE *pConsole);	
void ConsoleArgumentParser(CONSOLE *pConsole);
BOOLEAN ConsoleArgumentCheck(CONSOLE *pConsole);	
void ConsoleArgumentReset(CONSOLE *pConsole);
BOOLEAN ConsoleArgumentBs(CONSOLE *pConsole);	
void ConsoleArgumentKeyPut(CONSOLE *pConsole,UINT8 Data);
	
#endif