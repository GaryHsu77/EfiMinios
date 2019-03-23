#include <includes.h>

#define ConsoleItemInfo     0
#define ConsoleItemHelp     1
#define ConsoleItemTask     2
#define ConsoleItemMemory   3
#define ConsoleItemDelete   4
#define ConsoleItemDeleteid 5
#define ConsoleItemXmodem   6
#define ConsoleItemDump     7
#define ConsoleItemRun      8
#define ConsoleItemVersion  9 
#define ConsoleItemFdc      10 

UINT8 ConsoleInfo[]="info";
UINT8 ConsoleHelp[]="help";
UINT8 ConsoleTask[]="task";
UINT8 ConsoleMemory[]="memory";
UINT8 ConsoleDelete[]="delete";
UINT8 ConsoleDeleteid[]="deleteid";
UINT8 ConsoleXmodem[]="xmodem";
UINT8 ConsoleDump[]="dump";
UINT8 ConsoleRun[]="run";
UINT8 ConsoleVersion[]="version";
UINT8 ConsoleFdc[]="fdc";

UINT8 *ConsoleCommand[]={
ConsoleInfo,
ConsoleHelp,
ConsoleTask,
ConsoleMemory,
ConsoleDelete,
ConsoleDeleteid,
ConsoleXmodem,
ConsoleDump,
ConsoleRun,
ConsoleVersion,
ConsoleFdc,
(UINT8 *)0
};

UINT8 ConsoleStringAll[]="all";
UINT8 ConsoleOsVersion[]="2015.09.25";

BOOLEAN ConsoleCreat(CONSOLE *pConsole)
{
	if(pConsole==(CONSOLE *)NULL) return FALSE;
	gBS->AllocatePool(EfiBootServicesData,CONSOLE_BUFFER_SIZE,&pConsole->pDataBuffer);
    if(pConsole->pDataBuffer==(UINT8 *)NULL){
        pConsole->State=ConsoleIdleState;
    	return FALSE;
    }
    pConsole->State=ConsoleInitialState;      
    pConsole->ExecuteState=ConsoleItemStopState;
    pConsole->ExecuteItem=0;
    pConsole->Argc=0;
    pConsole->Put=0;
	pConsole->pWindow=(WINDOW *)NULL;
	pConsole->pCaption=(CAPTION *)NULL;  
    return TRUE;
}

VOID ConsoleSvc(CONSOLE *pConsole){
	UINT32 i;
	UINT8 CommandIndex;
    UINT8 (*GotoStart)(VOID);
    OS_TCB *pOsTask;
    OS_MEMORY *pOsMemory;
    OS_TIMER *pOsTimer;
    //WINDOW *pWindow;
    
	switch(pConsole->State){
        case ConsoleIdleState:
            break;
        case ConsoleInitialState:
            pConsole->State=ConsoleArgumentWaitState;
            break;
        case ConsoleArgumentWaitState:
            ConsoleArgumentSvc(pConsole);
            if(ConsoleArgumentCheck(pConsole)==TRUE) pConsole->State=ConsoleDispatchState;
            break;
        case ConsoleDispatchState:
            for(CommandIndex=0;;CommandIndex++){
                if(ConsoleCommand[CommandIndex]==(UINT8 *)0){
                    CaptionStringPrint(pConsole->pCaption,"\n cmd not found");
                    break;
                }
				
                if(SystemlibStringCompare((UINT8 *)pConsole->pArgv[0],(UINT8 *)ConsoleCommand[CommandIndex])==TRUE){
                    pConsole->ExecuteItem=CommandIndex;
                    pConsole->ExecuteState=ConsoleItemStartState;
                    pConsole->State=ConsoleExecutionState;
                    return;
                }
				
            }
            CaptionStringPrint(pConsole->pCaption,"\n$");
            ConsoleArgumentReset(pConsole);
            pConsole->State=ConsoleArgumentWaitState;
            break;
        case ConsoleExecutionState:
            switch(pConsole->ExecuteItem){
                case ConsoleItemInfo:
                    switch(pConsole->ExecuteState){
                        case ConsoleItemStartState:
							CaptionStringPrint(pConsole->pCaption,"\n =====================");
                            CaptionStringPrint(pConsole->pCaption,"\n | SYSTEM : UEFI x64 |");
                            CaptionStringPrint(pConsole->pCaption,"\n =====================");
                            pConsole->ExecuteState=ConsoleItemStopState;
                            break;
                        case ConsoleItemRunState:
                            break;
                        case ConsoleItemStopState:
                            pConsole->State=ConsoleExecutionStopState;
                            break;
                    }
                    break;
                case ConsoleItemHelp:
                    switch(pConsole->ExecuteState){
                        case ConsoleItemStartState:
                            if(pConsole->Argc<=1){
                                CaptionStringPrint(pConsole->pCaption,"\n command, info, help,");
                                CaptionStringPrint(pConsole->pCaption,"\n memory, task, delete,");
                                CaptionStringPrint(pConsole->pCaption,"\n deleteid, xmodem, dump,");
                                CaptionStringPrint(pConsole->pCaption,"\n run, version");
                                pConsole->ExecuteState=ConsoleItemStopState;
                                break;	
                            }
							
                            if(SystemlibStringCompare((UINT8 *)pConsole->pArgv[1],ConsoleInfo)==TRUE){                            	                        	
                                CaptionStringPrint(pConsole->pCaption,"'\nShows system informaton");
                                pConsole->ExecuteState=ConsoleItemStopState;
                                break;	
                            }  	
                            if(SystemlibStringCompare((UINT8 *)pConsole->pArgv[1],ConsoleHelp)==TRUE){                            	
                         	
                                CaptionStringPrint(pConsole->pCaption,"\nShows system commands");
                                pConsole->ExecuteState=ConsoleItemStopState;
                                break;	
                            }  	
                            if(SystemlibStringCompare((UINT8 *)pConsole->pArgv[1],ConsoleTask)==TRUE){                            	                       	
                                CaptionStringPrint(pConsole->pCaption,"\nShows task infomation.");           	
                                CaptionStringPrint(pConsole->pCaption,"\nusage: 1.task all");       	
                                CaptionStringPrint(pConsole->pCaption,"\n       2.task taskname");
                                pConsole->ExecuteState=ConsoleItemStopState;
                                break;	
                            }
                            if(SystemlibStringCompare((UINT8 *)pConsole->pArgv[1],ConsoleDelete)==TRUE){                            	                       	
                                CaptionStringPrint(pConsole->pCaption,"\nDelete task by name");                          	                       	
                                CaptionStringPrint(pConsole->pCaption,"\nusage: delete taskname");
                                pConsole->ExecuteState=ConsoleItemStopState;
                                break;	
                            }
                            if(SystemlibStringCompare((UINT8 *)pConsole->pArgv[1],ConsoleDelete)==TRUE){                           	                       	
                                CaptionStringPrint(pConsole->pCaption,"\nDelete task by id");                                   	                    	
                                CaptionStringPrint(pConsole->pCaption,"\nusage: deleteid taskid");
                                pConsole->ExecuteState=ConsoleItemStopState;
                                break;	
                            }
                            if(SystemlibStringCompare((UINT8 *)pConsole->pArgv[1],ConsoleXmodem)==TRUE){                            	
                                CaptionStringPrint(pConsole->pCaption,"\nDownload OS image."); 
                                pConsole->ExecuteState=ConsoleItemStopState;
                                break;	
                            }
                            if(SystemlibStringCompare((UINT8 *)pConsole->pArgv[1],ConsoleDump)==TRUE){                            	
                                CaptionStringPrint(pConsole->pCaption,"\nDump data of OS image."); 
                                pConsole->ExecuteState=ConsoleItemStopState;
                                break;	
                            }
                            if(SystemlibStringCompare((UINT8 *)pConsole->pArgv[1],ConsoleRun)==TRUE){                            	
                                CaptionStringPrint(pConsole->pCaption,"\nRun OS image."); 
                                pConsole->ExecuteState=ConsoleItemStopState;
                                break;	
                            }
                            if(SystemlibStringCompare((UINT8 *)pConsole->pArgv[1],ConsoleRun)==TRUE){                            	
                                CaptionStringPrint(pConsole->pCaption,"\nShow OS version"); 
                                pConsole->ExecuteState=ConsoleItemStopState;
                                break;	
                            }
                            CaptionStringPrint(pConsole->pCaption,"'\nNo this command.");
                            pConsole->ExecuteState=ConsoleItemStopState;
                            //pConsole->ExecuteState=ConsoleItemRunState;
                            break;
                        case ConsoleItemRunState:
                            pConsole->ExecuteState=ConsoleItemStopState;
                            break;
                        case ConsoleItemStopState:
                            pConsole->State=ConsoleExecutionStopState;
                            break;
                    }
                    break;
                case ConsoleItemTask:
                    switch(pConsole->ExecuteState){
                        case ConsoleItemStartState:
                            if(pConsole->Argc<=1){
                                CaptionStringPrint(pConsole->pCaption,"\nparameter too few");
                                pConsole->ExecuteState=ConsoleItemStopState;
                                break;	
                            }
							
                            if(SystemlibStringCompare((UINT8 *)pConsole->pArgv[1],ConsoleStringAll)==TRUE){
                                CaptionStringPrint(pConsole->pCaption,"\ntask list:");
                            	pOsTask=OsTaskCtrl.AllTaskList;
	                            while(pOsTask!=(OS_TCB *)OS_NULL){ 
		                            if(pOsTask!=(OS_TCB *)OS_NULL){
			                            CaptionStringPrint(pConsole->pCaption,"\n");
			                            CaptionStringPrint(pConsole->pCaption,pOsTask->pName);
			                            CaptionStringPrint(pConsole->pCaption," id:");
			                            CaptionUINT32Print(pConsole->pCaption,pOsTask->Id);
		                            }
	                                pOsTask=pOsTask->Next;
	                            }
                                pConsole->ExecuteState=ConsoleItemStopState;
                                break;	
                            }
							
                            pOsTask=OsTaskTaskGet(pConsole->pArgv[1]);
                            if(pOsTask==(OS_TCB *)OS_NULL){
                                CaptionStringPrint(pConsole->pCaption,"\ntask not found");
                                pConsole->ExecuteState=ConsoleItemStopState;
                                break;	
                            }
                            CaptionStringPrint(pConsole->pCaption,"\nTASK NAME: ");
                            CaptionStringPrint(pConsole->pCaption,pOsTask->pName);
                            
                            //CaptionStringPrint(pConsole->pCaption,"\nM.A:");
                            //CaptionU32Print(pConsole->pCaption,(U32)pOsTask);
                            //CaptionStringPrint(pConsole->pCaption," M.L:");
                            //CaptionU32Print(pConsole->pCaption,sizeof(OS_TASK));
                            
                            pOsMemory=pOsTask->MemoryList;
                            while(pOsMemory!=(OS_MEMORY *)OS_NULL){ 
	                            if(pOsMemory!=(OS_MEMORY *)OS_NULL){
		                            CaptionStringPrint(pConsole->pCaption,"\nM.A:");
		                            CaptionUINT32Print(pConsole->pCaption,(UINT32)pOsMemory->pMemory);
		                            CaptionStringPrint(pConsole->pCaption," M.L:");
		                            CaptionUINT32Print(pConsole->pCaption,pOsMemory->Length);
	                            }
                                pOsMemory=pOsMemory->TmNext;
                            }
                            
                            pOsTimer=pOsTask->TimerList;
                            while(pOsTimer!=(OS_TIMER *)OS_NULL){ 
	                            if(pOsTimer!=(OS_TIMER *)OS_NULL){
		                            CaptionStringPrint(pConsole->pCaption,"\nT.A:");
		                            CaptionUINT32Print(pConsole->pCaption,(UINT32)pOsTimer);
	                            }
                                pOsTimer=pOsTimer->TmNext;
                            }
                            
                            pConsole->ExecuteState=ConsoleItemStopState;
                            break;
                        case ConsoleItemRunState:
                            pConsole->ExecuteState=ConsoleItemStopState;
                            break;
                        case ConsoleItemStopState:
                            pConsole->State=ConsoleExecutionStopState;
                            break;
                    }
                    break;
                case ConsoleItemMemory:
                    switch(pConsole->ExecuteState){
                        case ConsoleItemStartState:
		                    CaptionStringPrint(pConsole->pCaption,"\nfree memory list");
                            //GDB pOsMemory=OsMemoryCtrl.FreeMemoryList;
                            //while(pOsMemory!=(OS_MEMORY *)OS_NULL){ 
	                        //    if(pOsMemory!=(OS_MEMORY *)OS_NULL){
		                    //       CaptionStringPrint(pConsole->pCaption,"\nM.A:");
		                    //        CaptionUINT32Print(pConsole->pCaption,(UINT32)pOsMemory->pMemory);
		                    //        CaptionStringPrint(pConsole->pCaption," M.L:");
		                    //        CaptionUINT32Print(pConsole->pCaption,pOsMemory->Length);
	                        //    }
                            //    pOsMemory=pOsMemory->Next;
                            //}
                            pConsole->ExecuteState=ConsoleItemStopState;
                            break;
                        case ConsoleItemRunState:
                            pConsole->ExecuteState=ConsoleItemStopState;
                            break;
                        case ConsoleItemStopState:
                            pConsole->State=ConsoleExecutionStopState;
                            break;
                    }
                    break;
                case ConsoleItemDelete:
                    switch(pConsole->ExecuteState){
                        case ConsoleItemStartState:
                            if(pConsole->Argc<=1){
                                CaptionStringPrint(pConsole->pCaption,"\n  ERROR : parameter too few");
                                pConsole->ExecuteState=ConsoleItemStopState;
                                break;	
                            }
                            pOsTask=OsTaskTaskGet(pConsole->pArgv[1]);
                            if(pOsTask==(OS_TCB *)OS_NULL){
                                CaptionStringPrint(pConsole->pCaption,"\ntask not found");
                                pConsole->ExecuteState=ConsoleItemStopState;
                                break;	
                            }
                            //CaptionStringPrint(pConsole->pCaption,"\ndelete ");
                            //CaptionStringPrint(pConsole->pCaption,pOsTask->pName);
                            DeskWindowWindowDelete((WINDOW *)pOsTask->Window);
                            OsKill(pOsTask);
                            pConsole->ExecuteState=ConsoleItemStopState;
                            break;
                        case ConsoleItemRunState:
                            pConsole->ExecuteState=ConsoleItemStopState;
                            break;
                        case ConsoleItemStopState:
                            pConsole->State=ConsoleExecutionStopState;
                            break;
                    }
                    break;
                case ConsoleItemDeleteid:
                    switch(pConsole->ExecuteState){
                        case ConsoleItemStartState:
                            CaptionStringPrint(pConsole->pCaption,"\ndeleteid");
                            if(pConsole->Argc<=1){
                            	CaptionStringPrint(pConsole->pCaption,"\n parameter too few");
                                pConsole->ExecuteState=ConsoleItemStopState;
                                break;	
                            }
                            i=SystemlibString2int(pConsole->pArgv[1]);
                            CaptionUINT32Print(pConsole->pCaption,i);
                            pOsTask=OsTaskTaskGetById(i);
                            if((pOsTask=OsTaskTaskGetById(i))!=(OS_TCB *)OS_NULL){
                                CaptionStringPrint(pConsole->pCaption,"\ntask name: ");
                                CaptionStringPrint(pConsole->pCaption,pOsTask->pName);
                            }
                            if((i==0)||(i==1)){
                            	CaptionStringPrint(pConsole->pCaption,"\n system task can't be deleted.");
                                pConsole->ExecuteState=ConsoleItemStopState;
                                break;	
                            }
                            //CaptionStringPrint(pConsole->pCaption,"\ndelete");
                            //CaptionStringPrint(pConsole->pCaption,pOsTask->pName);
                            DeskWindowWindowDelete((WINDOW *)pOsTask->Window);
                            OsKill(pOsTask);
                            pConsole->ExecuteState=ConsoleItemStopState;
                            break;
                        case ConsoleItemRunState:
                            pConsole->ExecuteState=ConsoleItemStopState;
                            break;
                        case ConsoleItemStopState:
                            pConsole->State=ConsoleExecutionStopState;
                            break;
                    }
                    break;
                case ConsoleItemXmodem:
                    switch(pConsole->ExecuteState){
                        case ConsoleItemStartState:
                            //pConsole->pMemory=OsMemoryAllocate(sizeof(XMODEM_CONTROL));
                            gBS->AllocatePool(EfiBootServicesData,sizeof(XMODEM_CONTROL),&pConsole->pMemory);
							if(pConsole->pMemory==(UINT8 *)NULL){             
                                CaptionStringPrint(pConsole->pCaption,"\nno memory for xmodem");               
                                pConsole->ExecuteState=ConsoleItemStopState;
                                break;	
                            }
                            //GDB Uart1BufferReset();
                            //GDB XmodemInit((XMODEM_CONTROL *)pConsole->pMemory);
                            pConsole->ExecuteState=ConsoleItemRunState;
                            break;
                        case ConsoleItemRunState:
                            //GDB XmodemSvc((XMODEM_CONTROL *)pConsole->pMemory);
                            //GDB if(XmodemStatusCheck((XMODEM_CONTROL *)pConsole->pMemory)==FALSE) return;
                            //GDB Uart1BufferReset();
                            CaptionStringPrint(pConsole->pCaption,"\n TotalBlockCount:");
                            CaptionUINT32Print(pConsole->pCaption,(UINT32)((XMODEM_CONTROL *)pConsole->pMemory)->TotalBlock);
                            CaptionStringPrint(pConsole->pCaption,"\n ByteCount:");
                            CaptionUINT32Print(pConsole->pCaption,(UINT32)((XMODEM_CONTROL *)pConsole->pMemory)->ByteCounter);
                            CaptionStringPrint(pConsole->pCaption,"\n pData:");
                            CaptionUINT32Print(pConsole->pCaption,(UINT32)((XMODEM_CONTROL *)pConsole->pMemory)->pMemory);
                            CaptionStringPrint(pConsole->pCaption,"\n xmodem transfer done");
                            //pOsTimer=(OS_TIMER *)(&((XMODEM_CONTROL *)pConsole->pMemory)->XmodemTimer);
                            //OsTimeTimerDelete(pOsTimer); 
                            //OsMemoryRelease(pConsole->pMemory);
							gBS->FreePool(pConsole->pMemory);
                            pConsole->ExecuteState=ConsoleItemStopState;
                            break;
                        case ConsoleItemStopState:
                            pConsole->State=ConsoleExecutionStopState;
                            break;
                    }
                    break;
                case ConsoleItemDump:
                    switch(pConsole->ExecuteState){
                        case ConsoleItemStartState:
                            SystemlibMemoryDump(pConsole->pCaption,(UINT8*)0xFFC00000,0x60);
                            pConsole->ExecuteState=ConsoleItemRunState;
                            break;
                        case ConsoleItemRunState:
                            pConsole->ExecuteState=ConsoleItemStopState;
                            break;
                        case ConsoleItemStopState:
                            pConsole->State=ConsoleExecutionStopState;
                            break;
                    }
                    break;
                case ConsoleItemRun:
                    switch(pConsole->ExecuteState){
                        case ConsoleItemStartState:
                            //CaptionStringPrint(pConsole->pCaption,"\nrun");      
                            /*GDB : Dangerous.
							GotoStart=(VOID (*)(VOID))IMAGE_ADDRESS;
                            (*GotoStart)();
							*/
                            pConsole->ExecuteState=ConsoleItemRunState;
                            break;
                        case ConsoleItemRunState:
                            pConsole->ExecuteState=ConsoleItemStopState;
                            break;
                        case ConsoleItemStopState:
                            pConsole->State=ConsoleExecutionStopState;
                            break;
                    }
                    break;
                case ConsoleItemVersion:
                    switch(pConsole->ExecuteState){
                        case ConsoleItemStartState:
                            CaptionStringPrint(pConsole->pCaption,"\n"); 
                            CaptionStringPrint(pConsole->pCaption,ConsoleOsVersion);  
                            pConsole->ExecuteState=ConsoleItemRunState;
                            break;
                        case ConsoleItemRunState:
                            pConsole->ExecuteState=ConsoleItemStopState;
                            break;
                        case ConsoleItemStopState:
                            pConsole->State=ConsoleExecutionStopState;
                            break;
                    }
                    break;
                case ConsoleItemFdc:
                    switch(pConsole->ExecuteState){
                        case ConsoleItemStartState:
                            CaptionStringPrint(pConsole->pCaption,"\nFloppy disk controller test.");  
                            //GDB FdcStart();
                            //GDB FdcSeekProcedure(1);
                            pConsole->ExecuteState=ConsoleItemRunState;
                            break;
                        case ConsoleItemRunState:
                            pConsole->ExecuteState=ConsoleItemStopState;
                            break;
                        case ConsoleItemStopState:
                            pConsole->State=ConsoleExecutionStopState;
                            break;
                    }
                    break;
            }
            break;
        case ConsoleExecutionStopState:
             CaptionStringPrint(pConsole->pCaption,"\n$");
             ConsoleArgumentReset(pConsole);
             pConsole->State=ConsoleArgumentWaitState;
            break;
        default:
            break;
	}
}

VOID ConsoleArgumentSvc(CONSOLE *pConsole){
    UINT8 (*GotoStart)(VOID);
    UINT8 Data;
    
    if(pConsole->pWindow==(WINDOW *)NULL) return;
    if(pConsole->pWindow->Active==TRUE)  // this code is for desk debug use
        if(pConsole->pCaption->MyTimer.Timer==0)
            CaptionCursorToggle(pConsole->pCaption);
    if(WindowKeyBufferCheck(pConsole->pWindow)==BUFFER_EMPTY) return;
    /*while(WindowKeyBufferCheck(pConsole->pWindow)==BUFFER_EMPTY){ //this code is for shell use,but no work in desk debug
    	if(pConsole->pWindow->Active==TRUE){
            if(pConsole->pCaption->MyTimer.Timer==0){
                CaptionCursorToggle(pConsole->pCaption);
                return; // to check window message
            }    
        }
        OsYield(NULL,NULL);
    }*/
    CaptionCursorClear(pConsole->pCaption);
    Data=WindowKeyBufferGet(pConsole->pWindow);
    if(Data>=0x80){
    	switch(Data){
        	case KB_SPECIAL_F1_KEY:
        	case KB_SPECIAL_F2_KEY:
            case KB_SPECIAL_F3_KEY:
            case KB_SPECIAL_F4_KEY:
            case KB_SPECIAL_F5_KEY:
            case KB_SPECIAL_F6_KEY:
            case KB_SPECIAL_F7_KEY:
            case KB_SPECIAL_F8_KEY:
            case KB_SPECIAL_F9_KEY:
            case KB_SPECIAL_F10_KEY:
            case KB_SPECIAL_F11_KEY:
            case KB_SPECIAL_F12_KEY:
            case KB_SPECIAL_PRTSCR_KEY:
            case KB_SPECIAL_SCROLL_LOCK_KEY:
            case KB_SPECIAL_PAUSE_BREAK_KEY:
            case KB_SPECIAL_TAB_KEY:
            case KB_SPECIAL_SHIFT_AT_LEFT_KEY:
            case KB_SPECIAL_SHIFT_AT_RIGHT_KEY:
            case KB_SPECIAL_CTRL_AT_LEFT_KEY:
            case KB_SPECIAL_CTRL_AT_RIGHT_KEY:
            case KB_SPECIAL_WINDOW_AT_LEFT_KEY:
            case KB_SPECIAL_WINDOW_AT_RIGHT_KEY:
            case KB_SPECIAL_ATL_AT_LEFT_KEY:
            case KB_SPECIAL_ATL_AT_RIGHT_KEY:
            case KB_SPECIAL_MENUS_KEY:
            case KB_SPECIAL_INSERT_KEY:
            case KB_SPECIAL_HOME_KEY:
            case KB_SPECIAL_PAGE_DOWN_KEY:
            case KB_SPECIAL_END_KEY:
            case KB_SPECIAL_PAGE_UP_KEY:
            case KB_SPECIAL_CAP_LOCK_KEY:
            case KB_SPECIAL_UP_ARROW_KEY:
            case KB_SPECIAL_LEFT_ARROW_KEY:
            case KB_SPECIAL_DOWN_ARROW_KEY:
            case KB_SPECIAL_RIGHT_ARROW_KEY:
            case KB_SPECIAL_NUM_LOCK_KEY:
            case KB_SPECIAL_INS:
            default:
                break;
    	}
    }
    else{
	    switch(Data){
	        case  ASCII_NUL: // ^@
	            break;
	        case  ASCII_SOH: // ^A
	            break;
	        case  ASCII_STX: // ^B
	            break;
	        case  ASCII_ETX: // ^C
	            break;
	        case  ASCII_EOT: // ^D
	            break;
	        case  ASCII_ENQ: // ^E
	            break;
	        case  ASCII_ACK: // ^F
	            break;
	        case  ASCII_BEL: // ^G
	            break;
	        case  ASCII_BS:  // ^H
	            if(ConsoleArgumentBs(pConsole)==TRUE){
	            	CaptionDel(pConsole->pCaption);
	            }
	            break;
	        case  ASCII_HT:  // ^I
	            break;
	        case  ASCII_LF:  // ^J
	            break;
	        case  ASCII_VT:  // ^K
	            break;
	        case  ASCII_FF:  // ^L
	            break;
	        case  ASCII_CR:  // ^M
	            ConsoleArgumentKeyPut(pConsole,Data);
	            ConsoleArgumentParser(pConsole);
	            break;
	        case  ASCII_SO:  // ^N
	            break;
	        case  ASCII_SI:  // ^O
	            break;
	        case  ASCII_DLE: // ^P
	            break;
	        case  ASCII_DC1: // ^Q
	            break;
	        case  ASCII_DC2: // ^R
	            break;
	        case  ASCII_DC3: // ^S
	            break;
	        case  ASCII_DC4: // ^T
	            break;
	        case  ASCII_NAK: // ^U
	            break;
	        case  ASCII_SYN: // ^V
	            break;
	        case  ASCII_ETB: // ^W
	            break;
	        case  ASCII_CAN: // ^X
	            break;
	        case  ASCII_EM:  // ^Y
	            break;
	        case  ASCII_SUB: // ^Z
	            break;
	        case  ASCII_ESC: // ^[
	            break;
	        case  ASCII_FS:   /* ^\  */
	            break;
	        case  ASCII_GS:  // ^]
	            break;
	        case  ASCII_RS:  // ^^
	            break;
	        case  ASCII_US:  // ^_
	            break;
	        case  ASCII_DEL: //
	            //ConsoleArgumentDel();
	            break;
	        default:
	            if((Data>=0x20)&&(Data<=0x7e)){
	            	CaptionCharPut(pConsole->pCaption,Data);
	                ConsoleArgumentKeyPut(pConsole,Data);
	            }
	            break;
	    }
    }
}

VOID ConsoleArgumentParser(CONSOLE *pConsole){
	UINT8 ByteIndex;
	UINT8 ParserState;

    ByteIndex=0;
    ParserState=ConsoleArgumentSearchState;
    pConsole->Argc=0;
    while(1){
        switch(ParserState){
            case ConsoleArgumentSearchState:
                if(pConsole->pDataBuffer[ByteIndex]==ASCII_SP){;}    
                else if(pConsole->pDataBuffer[ByteIndex]==ASCII_CR){ 
                    pConsole->pDataBuffer[ByteIndex]=0;
                    ParserState=ConsoleArgumentDoneState;
                }
                else{
                    pConsole->pArgv[pConsole->Argc]=&pConsole->pDataBuffer[ByteIndex];
                    pConsole->Argc++;
                    ParserState=ConsoleArgumentGoThroughState;
                }
                break;
            case ConsoleArgumentGoThroughState:
                if(pConsole->pDataBuffer[ByteIndex]==ASCII_CR){
                    pConsole->pDataBuffer[ByteIndex]=0;
                    ParserState=ConsoleArgumentDoneState;
                }
                else if(pConsole->pDataBuffer[ByteIndex]==ASCII_SP){
                    pConsole->pDataBuffer[ByteIndex]=0;
                    ParserState=ConsoleArgumentSearchState;
                }
                if(pConsole->Argc>=CONSOLE_ARGV_MAX){
                    ParserState=ConsoleArgumentDoneState;	
                }
                break;
            case ConsoleArgumentDoneState:
                if(pConsole->Put==CONSOLE_BUFFER_SIZE){ 
                    ConsoleArgumentReset(pConsole);
                    return;
                }
                return;
        }
        ByteIndex++;
    }
}

BOOLEAN ConsoleArgumentCheck(CONSOLE *pConsole){
    if(pConsole->Argc>0) return TRUE;
    return FALSE;
}

VOID ConsoleArgumentReset(CONSOLE *pConsole){
    pConsole->Put=0;
    pConsole->Argc=0;
}

BOOLEAN ConsoleArgumentBs(CONSOLE *pConsole){
    if(pConsole->Put==0) return FALSE;
    else{
        pConsole->Put--;
        return TRUE;
    }
}

VOID ConsoleArgumentKeyPut(CONSOLE *pConsole,UINT8 Data){
	if(pConsole->State==ConsoleIdleState) return;
    if(pConsole->Put<(CONSOLE_BUFFER_SIZE-1)){
        pConsole->pDataBuffer[pConsole->Put]=Data;
        pConsole->Put++;
    }
}
