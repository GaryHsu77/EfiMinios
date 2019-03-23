#ifndef KERNEL_ASM_H
#define KERNEL_ASM_H

typedef struct{
    UINT16 SegmentLength;      //segment length [15:0]
    UINT16 BaseAddress;        //base address [15:0]
    UINT8  BaseAddress2;	    //base address [23:16]
    UINT8  Attribute;          //P+DPL+S+TYPE+A
    UINT8  SegmentLength2;     //G+D+AVL+segment length [19:16]
    UINT8  BaseAddress3;       //base address [31:24]
}DESCRIPTOR;

#define GDT_NULL    0 //0th gdt
#define GDT_CODE    1 //1st gdt
#define GDT_DATA    2 //2nd gdt
#define GDT_STACK   3 //3rd gdt
#define GDT_EXTRA   4 //4th gdt
#define GDT_FLAG    4 //4th gdt
#define GDT_VIDEO   5 //5th gdt
#define GDT_TSS     6 //6th gdt...for tss segment use
#define LDT_BASE    7 //7th gdt...for ldt use

#define KERNEL_CS GDT_CODE
#define KERNEL_DS GDT_DATA
#define KERNEL_SS GDT_STACK
#define KERNEL_ES GDT_EXTRA
#define KERNEL_FS GDT_FLAG
#define KERNEL_GS GDT_VIDEO

#define TASK_CS GDT_CODE
#define TASK_DS GDT_DATA
#define TASK_SS GDT_STACK
#define TASK_ES GDT_EXTRA
#define TASK_FS GDT_FLAG
#define TASK_GS GDT_VIDEO

extern UINT8 CursorPosition;
extern UINT8 CharacterAttribute;
extern GATE IdtTable[IDT_SIZE];
extern DESCRIPTOR GdtTable[128];
//extern INT_HANDLER CpuIntHandlersTable[20];
//extern INT_HANDLER CpuIntExecutorTable[20];
//extern INT_HANDLER IrqHandlersTable[16];
//extern INT_HANDLER IrqExecutorTable[16];
//extern INT_HANDLER SoftwareIntHandlersTable[1];
//extern INT_HANDLER SoftwareIntExecutorTable[1];

void EnableIrq(UINT8 IrqNumber);
void DisableIrq(UINT8 IrqNumber);

VOID OsTaskSwitchOut(VOID); //task level task switch called by OsYield() IN OsCore.c

#endif