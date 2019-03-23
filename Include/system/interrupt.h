#ifndef INTERRUPT_H
#define INTERRUPT_H

#define IDT_P   1          // present
#define IDT_SELECTOR 0x0008 // the same with cs selector

#define DPL_0 0 // highest 
#define DPL_1 1
#define DPL_2 2
#define DPL_3 3

#define	INT_CPU_DIVIDE_BY_0   0x00
#define	INT_CPU_SINGLE_STEP   0x01
#define	INT_CPU_NMI			0x02
#define	INT_CPU_BREAKPOINT	0x03
#define	INT_CPU_OVERFLOW		0x04
#define	INT_CPU_BOUND		    0x05
#define	INT_CPU_INVALID_OPCODE 0x06
#define	INT_CPU_NO_FPU	    0x07
#define	INT_CPU_DOUBLE_FAULT	0x08
#define	INT_CPU_FPU_SEGMENT_OVERFLOW	0x09
#define	INT_CPU_INVAL_TSS	    0x0A
#define	INT_CPU_INVALID_SEGMENT 0x0B
#define	INT_CPU_STACK_FAULT	0x0C
#define	INT_CPU_PROTECTION	0x0D
#define	INT_CPU_PAGE_FAULT	0x0E
#define	INT_CPU_UNDEFINE            0x0F //undefine is not cpu fault
#define	INT_CPU_FPU_ERROR	    0x10
#define	INT_CPU_ALIGNMENT_ERROR 0x11
#define	INT_CPU_MACHINE_ERROR	0x12
#define	INT_CPU_SIMD_ERROR	0x13

#define	INT_VECTOR_IRQ0			0x20
#define	INT_VECTOR_IRQ8			0x28

#define INT_VECTOR_OS_CSW       0x30 // CSW is breaf of context switch

#define CALL_GATE_16 4
#define TASK_GATE    5
#define INT_GATE_16  6
#define TRAP_GATE_16 7
#define CALL_GATE_32 12
#define INT_GATE_32  14
#define TRAP_GATE_32 15


// interrupt requests definition
#define IRQ0_TIMER        0
#define IRQ1_KEYBOARD     1 
#define IRQ2_PIC_SLACE    2
#define IRQ3_COM2         3
#define IRQ4_COM1         4
#define IRQ5_LPT2         5 
#define IRQ6_FDC          6 
#define IRQ7_LPT1         7

#define IRQ8_RTC          8
#define IRQ9_REDIR_IRQ2   9
#define IRQ10_USER0        10
#define IRQ11_USER1        11
#define IRQ12_MOUSE       12
#define IRQ13_FPU         13
#define IRQ14_HDC         14
#define IRQ15_USER2     15

//int setting*************************************>>>
#pragma pack (1)
struct IdtDescriptor{
	UINT16	Limit;
	UINTN	Base;
};
#pragma pack()

struct IntGate{
	UINT16  LoOffset;
	UINT16  Segment;
	UINT16  DescBits;   //Will be set to 0x0f00 Present=1, DPL = 0, D = 1 (32bit)
	UINT16  HiOffset;
#ifdef EFIx64
	UINT32  Hi32Offset;
	UINT32  Rsv;
#endif
};

typedef struct _PegaRegisterSet16
{
	UINT32 EIP;
	UINT32 EFLAG;
	UINT32 CS;
	UINT32 DS;
	UINT32 SS;
	UINT32 ES;
	UINT32 FS;
	UINT32 GS;
	UINT32 CR0;
	UINT32 CR1;
	UINT32 CR2;
	UINT32 CR3;
	UINT32 CR4;
	UINT32 DR0;
	UINT32 DR1;
	UINT32 DR2;
	UINT32 DR3;
	UINT32 DR4;
	UINT32 DR5;
	UINT32 DR6;
	UINT32 DR7;
	UINT32 EDI;
	UINT32 ESI;
	UINT32 EBP;
	UINT32 ESP;
	UINT32 EBX;
	UINT32 EDX;
	UINT32 ECX;
	UINT32 EAX;
}PegaRegisterSet16;

typedef struct _PegaRegisterSet32
{
	UINT32 EIP;
	UINT32 EFLAG;
	UINT32 CS;
	UINT32 DS;
	UINT32 SS;
	UINT32 ES;
	UINT32 FS;
	UINT32 GS;
	UINT32 CR0;
	UINT32 CR1;
	UINT32 CR2;
	UINT32 CR3;
	UINT32 CR4;
	UINT32 DR0;
	UINT32 DR1;
	UINT32 DR2;
	UINT32 DR3;
	UINT32 DR4;
	UINT32 DR5;
	UINT32 DR6;
	UINT32 DR7;
	UINT32 EDI;
	UINT32 ESI;
	UINT32 EBP;
	UINT32 ESP;
	UINT32 EBX;
	UINT32 EDX;
	UINT32 ECX;
	UINT32 EAX;
}PegaRegisterSet32;

typedef struct _PegaRegisterSet64
{
	UINT64 RIP;
	UINT64 RFLAG;
	UINT64 CS;
	UINT64 DS;
	UINT64 SS;
	UINT64 ES;
	UINT64 FS;
	UINT64 GS;
	UINT64 CR0;
	UINT64 CR1;
	UINT64 CR2;
	UINT64 CR3;
	UINT64 CR4;
	UINT64 CR8;
	UINT64 DR0;
	UINT64 DR1;
	UINT64 DR2;
	UINT64 DR3;
	UINT64 DR4;
	UINT64 DR5;
	UINT64 DR6;
	UINT64 DR7;
	UINT64 R15;
	UINT64 R14;
	UINT64 R13;
	UINT64 R12;
	UINT64 R11;
	UINT64 R10;
	UINT64 R9;
	UINT64 R8;
	UINT64 RDI;
	UINT64 RSI;
	UINT64 RBP;
	UINT64 RSP;
	UINT64 RBX;
	UINT64 RDX;
	UINT64 RCX;
	UINT64 RAX;
}PegaRegisterSet64;

typedef union _PegaRegisterSet{
	PegaRegisterSet16 Regs16;
	PegaRegisterSet32 Regs32;
	PegaRegisterSet64 Regs64;
}PegaRegisterSet;

extern struct IntGate *IDT;

UINT16 DebugGetCS();
VOID InterruptInit(VOID);
VOID InitIDT();
VOID DebugLoadIDT(struct IdtDescriptor *IDTp);

VOID Exp_00_Handler();
VOID Exp_01_Handler();
VOID Exp_02_Handler();
VOID Exp_03_Handler();
VOID Exp_04_Handler();
VOID Exp_05_Handler();
VOID Exp_06_Handler();
VOID Exp_07_Handler();
VOID Exp_08_Handler();
VOID Exp_09_Handler();
VOID Exp_0A_Handler();
VOID Exp_0B_Handler();
VOID Exp_0C_Handler();
VOID Exp_0D_Handler();
VOID Exp_0E_Handler();
VOID Exp_0F_Handler();
VOID IntDummyHandler();

//int setting*************************************<<<

VOID InterruptCpuIntHandlerSet(UINT8 IntNumber,UINTN IntHandler);
VOID InterruptSoftwareIntHandlerSet(UINT8 IntNumber,UINTN IntHandler);
VOID InterruptIrqHandlerSet(UINT8 IrqNumber,UINTN IrqHandler);
VOID InterruptIdtEntrySet(UINT8 IntNumber,UINTN Handler);
VOID InterruptIdtTableFill(VOID);

VOID InterruptIrq0Handler(VOID);
VOID InterruptIrq1Handler(VOID);
VOID InterruptIrq2Handler(VOID);
VOID InterruptIrq3Handler(VOID);
VOID InterruptIrq4Handler(VOID);
VOID InterruptIrq5Handler(VOID);
VOID InterruptIrq6Handler(VOID);
VOID InterruptIrq7Handler(VOID);
VOID InterruptIrq8Handler(VOID);
VOID InterruptIrq9Handler(VOID);
VOID InterruptIrq10Handler(VOID);
VOID InterruptIrq11Handler(VOID);
VOID InterruptIrq12Handler(VOID);
VOID InterruptIrq13Handler(VOID);
VOID InterruptIrq14Handler(VOID);
VOID InterruptIrq15Handler(VOID);

VOID InterruptCpuInt0Handler(VOID);
VOID InterruptCpuInt1Handler(VOID);
VOID InterruptCpuInt2Handler(VOID);
VOID InterruptCpuInt3Handler(VOID);
VOID InterruptCpuInt4Handler(VOID);
VOID InterruptCpuInt5Handler(VOID);
VOID InterruptCpuInt6Handler(VOID);
VOID InterruptCpuInt7Handler(VOID);
VOID InterruptCpuInt8Handler(VOID);
VOID InterruptCpuInt9Handler(VOID);
VOID InterruptCpuInt10Handler(VOID);
VOID InterruptCpuInt11Handler(VOID);
VOID InterruptCpuInt12Handler(VOID);
VOID InterruptCpuInt13Handler(VOID);
VOID InterruptCpuInt14Handler(VOID);
VOID InterruptCpuInt15Handler(VOID);
VOID InterruptCpuInt16Handler(VOID);
VOID InterruptCpuInt17Handler(VOID);
VOID InterruptCpuInt18Handler(VOID);
VOID InterruptCpuInt19Handler(VOID);

VOID InterruptSoftwareInt48Handler(VOID);


#endif