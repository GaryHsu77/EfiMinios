#include <includes.h>

const UINT8 DeskDeskDebugWindowName[]="DEBUGER";

DESK_DEBUG_CONTROL DeskDebugCtrl;

VOID DeskDebugInit(VOID){
	//window parameter
	WindowVariableInit(&DeskDebugCtrl.Window,WINDOW_TYPE_DESKDEBUG);
    DeskDebugCtrl.Window.pTitle=(UINT8 *)DeskDeskDebugWindowName;  

    //window table initial
    DeskDebugCtrl.Window.UserTableList=(WINDOW_TABLE *)NULL;
    DeskDebugCtrl.Window.OutlineTable.Type=WINDOW_TABLE_OUTLINE;
    DeskDebugCtrl.Window.OutlineTable.DeviceList=(WINDOW_DEVICE *)NULL;
    DeskDebugCtrl.Window.HeaderTable.Type=WINDOW_TABLE_HEADER;
    DeskDebugCtrl.Window.HeaderTable.DeviceList=(WINDOW_DEVICE *)NULL;
    DeskDebugCtrl.UserTable.Type=WINDOW_TABLE_GENERAL;
    DeskDebugCtrl.UserTable.DeviceList=(WINDOW_DEVICE *)NULL;
    DeskTableUserTableAdd(&DeskDebugCtrl.Window,&DeskDebugCtrl.UserTable);
    
    //user table initial for desk debuger 
    if(ConsoleCreat(&DeskDebugCtrl.Console)==FALSE) return;
    if(CaptionCreat(&DeskDebugCtrl.Caption,30,20)==FALSE) return;
	DeskDebugCtrl.Console.pWindow=(WINDOW *)&DeskDebugCtrl.Window;
	DeskDebugCtrl.Console.pCaption=(CAPTION *)&DeskDebugCtrl.Caption;
	DeskDebugCtrl.DeskDeviceCaption.DeviceNumberLeft=DESK_DEBUG_WDN_CAPTION;
	DeskDebugCtrl.DeskDeviceCaption.DeviceNumberMiddle=WINDOW_WDN_NULL;
	DeskDebugCtrl.DeskDeviceCaption.DeviceNumberRight=WINDOW_WDN_NULL;
    
	DeskDebugCtrl.DeskDeviceCaption.Type=WINDOW_DEVICE_CAPTION;
	DeskDebugCtrl.DeskDeviceCaption.pDevice=(UINT32 *)(&DeskDebugCtrl.Caption);
    DeskDebugCtrl.UserTable.Area.X=0;
    DeskDebugCtrl.UserTable.Area.Y=0;
    DeskDebugCtrl.UserTable.Area.W=DeskDebugCtrl.Caption.Area.W;
    DeskDebugCtrl.UserTable.Area.H=DeskDebugCtrl.Caption.Area.H;
    DeskTableWindowDeviceAdd(&DeskDebugCtrl.UserTable,&DeskDebugCtrl.DeskDeviceCaption);
    
    WindowAreaInitial(&DeskDebugCtrl.Window);      
    WindowOutlineCalculate(&DeskDebugCtrl.Window);
    WindowOutlineTableInitial(&DeskDebugCtrl.Window);
    WindowHeaderCalculate(&DeskDebugCtrl.Window);
    WindowHeaderTableInitial(&DeskDebugCtrl.Window);
    
    // add window to desk
    //DeskWindowWindowPut((WINDOW *)&DeskDebugCtrl.Window);
}