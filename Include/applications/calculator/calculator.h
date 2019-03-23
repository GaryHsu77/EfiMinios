#ifndef CALCULATOR_H
#define CALCULATOR_H

#define CalculatorTaskIdleState 0
#define CalculatorTaskRunState  1
#define CalculatorTaskStopState 2

#define CalculatorIdleState    0
#define CalculatorInitialState 1
#define CalculatorRunState     2
#define CalculatorCloseState   3

#define CALCULATOR_WDN_STRINGBOX         (WINDOW_WDN_USERDEVICE)
#define CALCULATOR_WDN_NUMBERBUTTON0     (WINDOW_WDN_USERDEVICE+1)
#define CALCULATOR_WDN_NUMBERBUTTON1     (WINDOW_WDN_USERDEVICE+2)
#define CALCULATOR_WDN_NUMBERBUTTON2     (WINDOW_WDN_USERDEVICE+3)
#define CALCULATOR_WDN_NUMBERBUTTON3     (WINDOW_WDN_USERDEVICE+4)
#define CALCULATOR_WDN_NUMBERBUTTON4     (WINDOW_WDN_USERDEVICE+5)
#define CALCULATOR_WDN_NUMBERBUTTON5     (WINDOW_WDN_USERDEVICE+6)
#define CALCULATOR_WDN_NUMBERBUTTON6     (WINDOW_WDN_USERDEVICE+7)
#define CALCULATOR_WDN_NUMBERBUTTON7     (WINDOW_WDN_USERDEVICE+8)
#define CALCULATOR_WDN_NUMBERBUTTON8     (WINDOW_WDN_USERDEVICE+9)
#define CALCULATOR_WDN_NUMBERBUTTON9     (WINDOW_WDN_USERDEVICE+10)
#define CALCULATOR_WDN_NUMBERBUTTONDOT   (WINDOW_WDN_USERDEVICE+11)
#define CALCULATOR_WDN_NUMBERBUTTONADD   (WINDOW_WDN_USERDEVICE+12)
#define CALCULATOR_WDN_NUMBERBUTTONSUB   (WINDOW_WDN_USERDEVICE+13)
#define CALCULATOR_WDN_NUMBERBUTTONDIV   (WINDOW_WDN_USERDEVICE+14)
#define CALCULATOR_WDN_NUMBERBUTTONMUL   (WINDOW_WDN_USERDEVICE+15)
#define CALCULATOR_WDN_NUMBERBUTTONEQUAL (WINDOW_WDN_USERDEVICE+16)
#define CALCULATOR_WDN_NUMBERBUTTONCLEAR (WINDOW_WDN_USERDEVICE+17)

#define CALCULATOR_OPERATION_NONE 0
#define CALCULATOR_OPERATION_ADD  1
#define CALCULATOR_OPERATION_SUB  2
#define CALCULATOR_OPERATION_MUL  3
#define CALCULATOR_OPERATION_DIV  4

typedef struct{
    UINT8 TaskState;

    UINT8 WindowKey;
    UINT32 WindowMouse;
    UINT32 WindowEvent;
    
    UINT8 OperationType;
    UINT32 InputNumner;
    UINT32 Result;
    
    UINT8 NewArgument;
    UINT8 ArgumentIndex;
    UINT8 ArgumentBuffer[13];

    WINDOW_STRINGBOX StringBox;
    WINDOW_BUTTON NumberButton0;
    WINDOW_BUTTON NumberButton1;
    WINDOW_BUTTON NumberButton2;
    WINDOW_BUTTON NumberButton3;
    WINDOW_BUTTON NumberButton4;
    WINDOW_BUTTON NumberButton5;
    WINDOW_BUTTON NumberButton6;
    WINDOW_BUTTON NumberButton7;
    WINDOW_BUTTON NumberButton8;
    WINDOW_BUTTON NumberButton9;
    WINDOW_BUTTON AddButton;
    WINDOW_BUTTON SubButton;
    WINDOW_BUTTON MulButton;
    WINDOW_BUTTON DivButton;
    WINDOW_BUTTON DotButton;
    WINDOW_BUTTON EqualButton;
    WINDOW_BUTTON ClearButton;

    WINDOW_DEVICE WdStringBox;
    WINDOW_DEVICE WdNumberButton0;
    WINDOW_DEVICE WdNumberButton1;
    WINDOW_DEVICE WdNumberButton2;
    WINDOW_DEVICE WdNumberButton3;
    WINDOW_DEVICE WdNumberButton4;
    WINDOW_DEVICE WdNumberButton5;
    WINDOW_DEVICE WdNumberButton6;
    WINDOW_DEVICE WdNumberButton7;
    WINDOW_DEVICE WdNumberButton8;
    WINDOW_DEVICE WdNumberButton9;
    WINDOW_DEVICE WdAddButton;
    WINDOW_DEVICE WdSubButton;
    WINDOW_DEVICE WdMulButton;
    WINDOW_DEVICE WdDivButton;
    WINDOW_DEVICE WdDotButton;
    WINDOW_DEVICE WdEqualButton;
    WINDOW_DEVICE WdClearButton;

    WINDOW_TABLE UserTable;
    WINDOW Window;
}CALCULATOR_CONTORL;

void CalculatorInit(CALCULATOR_CONTORL *pCalculator);
void CalculatorSvc(CALCULATOR_CONTORL *pCalculator);
void CalculatorMemoryRelease(UINT8 *pMemory);
void CalculatorEventHandler(CALCULATOR_CONTORL *pCalculator);
void CalculatorKeyHandler(CALCULATOR_CONTORL *pCalculator);
void CalculatorArgumentReset(CALCULATOR_CONTORL *pCalculator);
UINT32 CalculatorNumberGet(CALCULATOR_CONTORL *pCalculator);
void CalculatorOperationDo(CALCULATOR_CONTORL *pCalculator);
void CalculatorUpdate(CALCULATOR_CONTORL *pCalculator);
void CalculatorArgumentAdd(CALCULATOR_CONTORL *pCalculator,UINT8 Data);
UINT8 CalculatorAscii2HexGet(UINT8 CharCode);
void CalculatorResult2StringConvert(CALCULATOR_CONTORL *pCalculator);

#endif