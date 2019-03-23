#include <includes.h>

static VOID * ExpHandlerArray[16] = {
	Exp_00_Handler,Exp_01_Handler,Exp_02_Handler,Exp_03_Handler,Exp_04_Handler,Exp_05_Handler,Exp_06_Handler,Exp_07_Handler,
	Exp_08_Handler,Exp_09_Handler,Exp_0A_Handler,Exp_0B_Handler,Exp_0C_Handler,Exp_0D_Handler,Exp_0E_Handler,Exp_0F_Handler
};
struct IntGate *IDT=NULL;

void InterruptInit(void){
	InitIDT();

/*
    InterruptCpuIntHandlerSet(0,InterruptCpuInt0Handler);     // 0x00~0x1f
    InterruptCpuIntHandlerSet(1,InterruptCpuInt1Handler);
    InterruptCpuIntHandlerSet(2,InterruptCpuInt2Handler);
    InterruptCpuIntHandlerSet(3,InterruptCpuInt3Handler);
    InterruptCpuIntHandlerSet(4,InterruptCpuInt4Handler);
    InterruptCpuIntHandlerSet(5,InterruptCpuInt5Handler);
    InterruptCpuIntHandlerSet(6,InterruptCpuInt6Handler);
    InterruptCpuIntHandlerSet(7,InterruptCpuInt7Handler);
    InterruptCpuIntHandlerSet(8,InterruptCpuInt8Handler);
    InterruptCpuIntHandlerSet(9,InterruptCpuInt9Handler);
    InterruptCpuIntHandlerSet(10,InterruptCpuInt10Handler);
    InterruptCpuIntHandlerSet(11,InterruptCpuInt11Handler);
    InterruptCpuIntHandlerSet(12,InterruptCpuInt12Handler);
    InterruptCpuIntHandlerSet(13,InterruptCpuInt13Handler);
    InterruptCpuIntHandlerSet(14,InterruptCpuInt14Handler);
    InterruptCpuIntHandlerSet(15,InterruptCpuInt15Handler);
    InterruptCpuIntHandlerSet(16,InterruptCpuInt16Handler);
    InterruptCpuIntHandlerSet(17,InterruptCpuInt17Handler);
    InterruptCpuIntHandlerSet(18,InterruptCpuInt18Handler);
    InterruptCpuIntHandlerSet(19,InterruptCpuInt19Handler);
    
    InterruptIrqHandlerSet(0,InterruptIrq0Handler);  //0x20~0x2f
    InterruptIrqHandlerSet(1,InterruptIrq1Handler);
    InterruptIrqHandlerSet(2,InterruptIrq2Handler);
    InterruptIrqHandlerSet(3,InterruptIrq3Handler);
    InterruptIrqHandlerSet(4,InterruptIrq4Handler);
    InterruptIrqHandlerSet(5,InterruptIrq5Handler);
    InterruptIrqHandlerSet(6,InterruptIrq6Handler);
    InterruptIrqHandlerSet(7,InterruptIrq7Handler);
    InterruptIrqHandlerSet(8,InterruptIrq8Handler);
    InterruptIrqHandlerSet(9,InterruptIrq9Handler);
    InterruptIrqHandlerSet(10,InterruptIrq10Handler);
    InterruptIrqHandlerSet(11,InterruptIrq11Handler);
    InterruptIrqHandlerSet(12,InterruptIrq12Handler);
    InterruptIrqHandlerSet(13,InterruptIrq13Handler);
    InterruptIrqHandlerSet(14,InterruptIrq14Handler);
    InterruptIrqHandlerSet(15,InterruptIrq15Handler);
    
    InterruptSoftwareIntHandlerSet(0,InterruptSoftwareInt48Handler); //0x30~
*/
}

void InitIDT()
{
	UINT16 CSSelector;
	UINTN i,IntHandlerPtr;
	struct IdtDescriptor pIDT;

	OsLibMemorySet((UINT8 *)&pIDT,sizeof(struct IdtDescriptor),0);
	OsLibMemorySet((UINT8 *)IDT,IDT_SIZE*sizeof(struct IntGate),0);
	CSSelector = DebugGetCS();

	for(i=0;i<IDT_SIZE;i++){
		if(i < 16)
			IntHandlerPtr = (UINTN)ExpHandlerArray[i];
		else
			IntHandlerPtr = (UINTN)IntDummyHandler;
		IDT[i].LoOffset=(UINT16)(IntHandlerPtr & 0x0FFFF);
		IDT[i].HiOffset=(UINT16)(((IntHandlerPtr) >> 16) & 0x0FFFF);
		IDT[i].Segment=CSSelector;
		IDT[i].DescBits=0x8E00;  //Present=1, DPL = 0, D = 1 (32bit)
#ifdef EFIx64
		IDT[i].Hi32Offset = (UINT32)(((IntHandlerPtr) >> 32) & 0x0FFFFFFFF);
		IDT[i].Rsv = 0;
#endif
	}
	pIDT.Base = (UINTN)IDT;
	pIDT.Limit = IDT_SIZE*sizeof(struct IntGate) -1;

	DebugLoadIDT(&pIDT);
}

VOID IntDummyCallback()
{
	Print (L"#");
}

VOID ExtHandler_Debugger(PegaRegisterSet *Regs,UINTN Vector)
{
}
/*
void InterruptCpuIntHandlerSet(U8 IntNumber,INT_HANDLER IntHandler){
    if(IntNumber>=20) return;                 //invalid cpu fault int number
    CpuIntHandlersTable[IntNumber]=IntHandler;
}

void InterruptIrqHandlerSet(U8 IrqNumber,INT_HANDLER IrqHandler){
    if(IrqNumber>=16) return;                 //invalid irq number
    IrqHandlersTable[IrqNumber]=IrqHandler;
}

void InterruptSoftwareIntHandlerSet(U8 IntNumber,INT_HANDLER IntHandler){
    if(IntNumber>=1) return;                 //invalid int number
    SoftwareIntHandlersTable[IntNumber]=IntHandler;
}

void InterruptIdtEntrySet(U8 IntNumber,U8 IdtType,INT_HANDLER Handler,U8 IdtDpl){
    GATE* pGate;
    U32 Base;

    pGate=&IdtTable[IntNumber];
    Base=(U32)Handler;
    pGate->OffsetLow=Base&0x0000ffff;
    pGate->Selector=IDT_SELECTOR;
    pGate->Dcount=0x00;
    pGate->Attribute=(IDT_P<<7)|(IdtDpl<<5)|IdtType;
    pGate->OffsetHigh=(Base>>16)&0x0000ffff;
}

void InterruptIdtTableFill(void){
    InterruptIdtEntrySet(INT_CPU_DIVIDE_BY_0,	     INT_GATE_32,CpuIntExecutorTable[0],DPL_3);
    InterruptIdtEntrySet(INT_CPU_SINGLE_STEP,	     INT_GATE_32,CpuIntExecutorTable[1],DPL_3);
    InterruptIdtEntrySet(INT_CPU_NMI,	             INT_GATE_32,CpuIntExecutorTable[2],DPL_3);
    InterruptIdtEntrySet(INT_CPU_BREAKPOINT,	     INT_GATE_32,CpuIntExecutorTable[3],DPL_3);
    InterruptIdtEntrySet(INT_CPU_OVERFLOW,	     INT_GATE_32,CpuIntExecutorTable[4],DPL_3);
    InterruptIdtEntrySet(INT_CPU_BOUND,	         INT_GATE_32,CpuIntExecutorTable[5],DPL_3);
    InterruptIdtEntrySet(INT_CPU_INVALID_OPCODE,	 INT_GATE_32,CpuIntExecutorTable[6],DPL_3);
    InterruptIdtEntrySet(INT_CPU_NO_FPU,	         INT_GATE_32,CpuIntExecutorTable[7],DPL_3);
    InterruptIdtEntrySet(INT_CPU_DOUBLE_FAULT,     INT_GATE_32,CpuIntExecutorTable[8],DPL_3);
    InterruptIdtEntrySet(INT_CPU_FPU_SEGMENT_OVERFLOW, INT_GATE_32,CpuIntExecutorTable[9],DPL_3);
    InterruptIdtEntrySet(INT_CPU_INVAL_TSS,	     INT_GATE_32,CpuIntExecutorTable[10],DPL_3);
    InterruptIdtEntrySet(INT_CPU_INVALID_SEGMENT,  INT_GATE_32,CpuIntExecutorTable[11],DPL_3);
    InterruptIdtEntrySet(INT_CPU_STACK_FAULT,      INT_GATE_32,CpuIntExecutorTable[12],DPL_3);
    InterruptIdtEntrySet(INT_CPU_PROTECTION,	     INT_GATE_32,CpuIntExecutorTable[13],DPL_3);
    InterruptIdtEntrySet(INT_CPU_PAGE_FAULT,	     INT_GATE_32,CpuIntExecutorTable[14],DPL_3);
    //InterruptIdtEntrySet(INT_CPU_UNDEFINE,	             INT_GATE_32,CpuIntExecutorTable[15],DPL_3); //undefine means this int is not defined.
    InterruptIdtEntrySet(INT_CPU_FPU_ERROR,	     INT_GATE_32,CpuIntExecutorTable[16],DPL_3);
    InterruptIdtEntrySet(INT_CPU_ALIGNMENT_ERROR,	 INT_GATE_32,CpuIntExecutorTable[17],DPL_3);
    InterruptIdtEntrySet(INT_CPU_MACHINE_ERROR,	 INT_GATE_32,CpuIntExecutorTable[18],DPL_3);
    InterruptIdtEntrySet(INT_CPU_SIMD_ERROR,	     INT_GATE_32,CpuIntExecutorTable[19],DPL_3);
    
    InterruptIdtEntrySet(INT_VECTOR_IRQ0+0,	     INT_GATE_32,IrqExecutorTable[0],DPL_3);
    InterruptIdtEntrySet(INT_VECTOR_IRQ0+1,	     INT_GATE_32,IrqExecutorTable[1],DPL_3);
    InterruptIdtEntrySet(INT_VECTOR_IRQ0+2,	     INT_GATE_32,IrqExecutorTable[2],DPL_3);
    InterruptIdtEntrySet(INT_VECTOR_IRQ0+3,	     INT_GATE_32,IrqExecutorTable[3],DPL_3);
    InterruptIdtEntrySet(INT_VECTOR_IRQ0+4,	     INT_GATE_32,IrqExecutorTable[4],DPL_3);
    InterruptIdtEntrySet(INT_VECTOR_IRQ0+5,	     INT_GATE_32,IrqExecutorTable[5],DPL_3);
    InterruptIdtEntrySet(INT_VECTOR_IRQ0+6,	     INT_GATE_32,IrqExecutorTable[6],DPL_3);
    InterruptIdtEntrySet(INT_VECTOR_IRQ0+7,	     INT_GATE_32,IrqExecutorTable[7],DPL_3);
    InterruptIdtEntrySet(INT_VECTOR_IRQ8+0,	     INT_GATE_32,IrqExecutorTable[8],DPL_3);
    InterruptIdtEntrySet(INT_VECTOR_IRQ8+1,	     INT_GATE_32,IrqExecutorTable[9],DPL_3);
    InterruptIdtEntrySet(INT_VECTOR_IRQ8+2,	     INT_GATE_32,IrqExecutorTable[10],DPL_3);
    InterruptIdtEntrySet(INT_VECTOR_IRQ8+3,	     INT_GATE_32,IrqExecutorTable[11],DPL_3);
    InterruptIdtEntrySet(INT_VECTOR_IRQ8+4,	     INT_GATE_32,IrqExecutorTable[12],DPL_3);
    InterruptIdtEntrySet(INT_VECTOR_IRQ8+5,	     INT_GATE_32,IrqExecutorTable[13],DPL_3);
    InterruptIdtEntrySet(INT_VECTOR_IRQ8+6,	     INT_GATE_32,IrqExecutorTable[14],DPL_3);
    InterruptIdtEntrySet(INT_VECTOR_IRQ8+7,	     INT_GATE_32,IrqExecutorTable[15],DPL_3);
    
    InterruptIdtEntrySet(INT_VECTOR_OS_CSW,	     INT_GATE_32,SoftwareIntExecutorTable[0],DPL_3);
}

void InterruptIrq0Handler(void){
}

void InterruptIrq1Handler(void){
}

void InterruptIrq2Handler(void){
}

void InterruptIrq3Handler(void){
}

void InterruptIrq4Handler(void){
}

void InterruptIrq5Handler(void){
}

void InterruptIrq6Handler(void){
}

void InterruptIrq7Handler(void){
}

void InterruptIrq8Handler(void){
}

void InterruptIrq9Handler(void){
}

void InterruptIrq10Handler(void){
}

void InterruptIrq11Handler(void){
}

void InterruptIrq12Handler(void){
}

void InterruptIrq13Handler(void){
}

void InterruptIrq14Handler(void){
}

void InterruptIrq15Handler(void){
}

void InterruptCpuInt0Handler(void){
	SystemGuiInit();
	SystemGuiStringPrint("Cpu fault 0");
	SystemGuiStringPrint("\nFAULT TYPE: DIVIDE BY 0");
	SystemGuiStringPrint("\nSYSTEM HALT");
    SystemHalt();
}
void InterruptCpuInt1Handler(void){
	SystemGuiInit();
	SystemGuiStringPrint("Cpu fault 1");
	SystemGuiStringPrint("\nFAULT TYPE: SINGLE STEP");
	SystemGuiStringPrint("\nSINGLE STEP IS FOR DEBUG USE.");
	SystemGuiStringPrint("\nSYSTEM HALT");
    SystemHalt();
}
void InterruptCpuInt2Handler(void){
	SystemGuiInit();
	SystemGuiStringPrint("Cpu fault 2");
	SystemGuiStringPrint("\nFAULT TYPE: NON MASKABLE INTERRUPT");
	SystemGuiStringPrint("\nNMI IS NOT SUPPORTED.");
	SystemGuiStringPrint("\nSYSTEM HALT");
    SystemHalt();
}
void InterruptCpuInt3Handler(void){
	SystemGuiInit();
	SystemGuiStringPrint("Cpu fault 3");
	SystemGuiStringPrint("\nFAULT TYPE: BREAK POINT");
	SystemGuiStringPrint("\nBREAK POINT IS FOR DEBUG USE.");
	SystemGuiStringPrint("\nSYSTEM HALT");
    SystemHalt();
}
void InterruptCpuInt4Handler(void){
	SystemGuiInit();
	SystemGuiStringPrint("Cpu fault 4");
	SystemGuiStringPrint("\nFAULT TYPE: OVERFLOW");
	SystemGuiStringPrint("\nSYSTEM HALT");
    SystemHalt();
}
void InterruptCpuInt5Handler(void){
	SystemGuiInit();
	SystemGuiStringPrint("Cpu fault 5");
	SystemGuiStringPrint("\nFAULT TYPE: BOUND");
	SystemGuiStringPrint("\nSYSTEM HALT");
    SystemHalt();
}
void InterruptCpuInt6Handler(void){
	SystemGuiInit();
	SystemGuiStringPrint("Cpu fault 6");
	SystemGuiStringPrint("\nFAULT TYPE: INVALID OP CODE");
	SystemGuiStringPrint("\nSYSTEM HALT");
    SystemHalt();
}
void InterruptCpuInt7Handler(void){
	SystemGuiInit();
	SystemGuiStringPrint("Cpu fault 7");
	SystemGuiStringPrint("\nFAULT TYPE: NO FPU");
	SystemGuiStringPrint("\nSYSTEM HALT");
    SystemHalt();
}
void InterruptCpuInt8Handler(void){
	SystemGuiInit();
	SystemGuiStringPrint("Cpu fault 8");
	SystemGuiStringPrint("\nFAULT TYPE: DOUBLE FAULT");
	SystemGuiStringPrint("\nSYSTEM HALT");
    SystemHalt();
}
void InterruptCpuInt9Handler(void){
	SystemGuiInit();
	SystemGuiStringPrint("Cpu fault 9");
	SystemGuiStringPrint("\nFAULT TYPE: FPU SEGMENT OVERFLOW");
	SystemGuiStringPrint("\nSYSTEM HALT");
    SystemHalt();
}
void InterruptCpuInt10Handler(void){
	SystemGuiInit();
	SystemGuiStringPrint("Cpu fault 10");
	SystemGuiStringPrint("\nFAULT TYPE: INVALID TSS");
	SystemGuiStringPrint("\nSYSTEM HALT");
    SystemHalt();
}
void InterruptCpuInt11Handler(void){
	SystemGuiInit();
	SystemGuiStringPrint("Cpu fault 11");
	SystemGuiStringPrint("\nFAULT TYPE: SEGMENT NOT PRESENT");
	SystemGuiStringPrint("\nSYSTEM HALT");
    SystemHalt();
}
void InterruptCpuInt12Handler(void){
	SystemGuiInit();
	SystemGuiStringPrint("Cpu fault 12");
	SystemGuiStringPrint("\nFAULT TYPE: STACK SEGMENT OVERFLOW");
	SystemGuiStringPrint("\nSYSTEM HALT");
    SystemHalt();
}
void InterruptCpuInt13Handler(void){
	SystemGuiInit();
	SystemGuiStringPrint("Cpu fault 13");
	SystemGuiStringPrint("\nFAULT TYPE: GENERAL PROTECTION");
	SystemGuiStringPrint("\nSYSTEM HALT");
    SystemHalt();
}
void InterruptCpuInt14Handler(void){
	SystemGuiInit();
	SystemGuiStringPrint("Cpu fault 14");
	SystemGuiStringPrint("\nFAULT TYPE: PAGE FAULT");
	SystemGuiStringPrint("\nSYSTEM HALT");
    SystemHalt();
}
void InterruptCpuInt15Handler(void){
	SystemGuiInit();
	SystemGuiStringPrint("Cpu fault 15");
	SystemGuiStringPrint("\nFAULT TYPE: UNDEFINE.");
	SystemGuiStringPrint("\nTHIS FAULT TYPE SHOULD NOT HAPPEN ,BECAUSE IT IS UNDEFINED.");
	SystemGuiStringPrint("\nSYSTEM HALT");
    SystemHalt();
}
void InterruptCpuInt16Handler(void){
	SystemGuiInit();
	SystemGuiStringPrint("Cpu fault 16");
	SystemGuiStringPrint("\nFAULT TYPE: FPU ERROR");
	SystemGuiStringPrint("\nSYSTEM HALT");
    SystemHalt();
}
void InterruptCpuInt17Handler(void){
	SystemGuiInit();
	SystemGuiStringPrint("Cpu fault 17");
	SystemGuiStringPrint("\nFAULT TYPE: ALIGNMENT ERROR");
	SystemGuiStringPrint("\nSYSTEM HALT");
    SystemHalt();
}
void InterruptCpuInt18Handler(void){
	SystemGuiInit();
	SystemGuiStringPrint("Cpu fault 18");
	SystemGuiStringPrint("\nFAULT TYPE: MACHINE ERROR");
	SystemGuiStringPrint("\nSYSTEM HALT");
    SystemHalt();
}
void InterruptCpuInt19Handler(void){
	SystemGuiInit();
	SystemGuiStringPrint("Cpu fault 19");
	SystemGuiStringPrint("\nFAULT TYPE: SIMD ERROR");
	SystemGuiStringPrint("\nSYSTEM HALT");
    SystemHalt();
}

void InterruptSoftwareInt48Handler(void){
    OsSchedulerNextTaskFind();                          
}
*/