#include <includes.h>

#define DEBUG_SHELLTASK 1

const UINT8 ShellTaskName[]="SHELL";

VOID ShellTaskInit(SHELL_CONTROL *pShell){
	pShell->TaskState=ShelltaskIdleState; 
    if(CaptionCreat(&pShell->Caption,55,10)==FALSE) return;
	pShell->DeskDeviceCaption.Type=WINDOW_DEVICE_CAPTION;
	pShell->DeskDeviceCaption.DeviceNumberLeft=SHELL_WDN_CAPTION;
	pShell->DeskDeviceCaption.DeviceNumberMiddle=SHELL_WDN_CAPTION;
	pShell->DeskDeviceCaption.DeviceNumberRight=SHELL_WDN_CAPTION;
	pShell->DeskDeviceCaption.pDevice=(UINT32 *)(&pShell->Caption);
	
	if(ConsoleCreat(&pShell->Console)==FALSE) return;
	pShell->Console.pWindow=(WINDOW *)&pShell->Window;
	pShell->Console.pCaption=(CAPTION *)&pShell->Caption;
	
    //setup user table 
    pShell->UserTable.Type=WINDOW_TABLE_GENERAL;
    pShell->UserTable.DeviceList=(WINDOW_DEVICE *)NULL;
    pShell->UserTable.Gfx.BgColor=GFX_COLOR_LIGHTBLUE;
    pShell->UserTable.Gfx.FgColor=GFX_COLOR_LIGHTBLUE;
    pShell->UserTable.Gfx.FontColor=GFX_COLOR_WHITE;
    pShell->UserTable.Area.X=0;
    pShell->UserTable.Area.Y=0;
    pShell->UserTable.Area.W=pShell->Caption.Area.W;
    pShell->UserTable.Area.H=pShell->Caption.Area.H;
    DeskTableWindowDeviceAdd(&pShell->UserTable,&pShell->DeskDeviceCaption);
    
    //window parameter
	WindowVariableInit(&pShell->Window,WINDOW_TYPE_APPLICATION);
    pShell->Window.pTitle=(UINT8 *)ShellTaskName;  
    pShell->Window.SizeVariable=TRUE;
    DeskTableUserTableAdd((WINDOW *)&pShell->Window,(WINDOW_TABLE *)&pShell->UserTable);
    WindowAreaInitial(&pShell->Window);
    WindowOutlineCalculate(&pShell->Window);
    WindowOutlineTableInitial(&pShell->Window);
    WindowHeaderCalculate(&pShell->Window);
    WindowHeaderTableInitial(&pShell->Window);
    DeskWindowWindowPut((WINDOW *)&pShell->Window);
    ((OS_TCB *)OsTaskCurrent)->Window=(UINT32)&pShell->Window;
	pShell->TaskState=ShelltaskRunState;
}

VOID ShellTask(VOID)
{
	EFI_STATUS Status ;	
	SHELL_CONTROL *pShell;
	
	//pShell=(SHELL_CONTROL *)OsMemoryAllocate(sizeof(SHELL_CONTROL));
	Status = gBS->AllocatePool(EfiBootServicesData,sizeof(SHELL_CONTROL),&(pShell));
	if(Status != EFI_SUCCESS)return;
	
	if(pShell==(SHELL_CONTROL *)NULL) OsTaskFinish();
    ShellTaskInit(pShell);
    if(pShell->TaskState==ShelltaskIdleState) OsTaskFinish(); 
    
	while(1){
        ConsoleSvc(&pShell->Console);
        if(pShell->Window.Message==WINDOW_WM_CLOSE){  //window event handler
            pShell->Window.MessageAck=WINDOW_WM_ACK;
		    #if(DEBUG_SHELLTASK==1)		    
	            CaptionStringPrint(&DeskDebugCtrl.Caption,"\nSHELL window close message");
		    #endif
            break;
        }
        OsYield(NULL,NULL);
    }
    while(pShell->Window.State!=DESK_WINDOW_STATE_OFFDESK) OsYield(NULL,NULL); //wait until window deleted from desk
	
	#if(DEBUG_SHELLTASK==1)		    
	    CaptionStringPrint(&DeskDebugCtrl.Caption,"\ntask off");
	#endif
    OsFinish();
}
