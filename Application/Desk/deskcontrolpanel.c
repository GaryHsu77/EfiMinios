#include <includes.h>

const UINT8 ControlPanelSystem[]="SYSTEM";
const UINT8 ControlPanelMouse[]="MOUSE";
const UINT8 ControlPanelKeyboard[]="KEYBOARD";
const UINT8 ControlPanelMonitor[]="MONITOR";
const UINT8 ControlPanelDrivers[]="DRIVERS";
const UINT8 ControlPanelPalette[]="PALETTE";

const UINT8 ControlPanelSystemInfo0[]="SYSTEM:";
const UINT8 ControlPanelSystemInfo1[]=" FORMOSA WINDOWS";
const UINT8 ControlPanelSystemInfo2[]=" VERSION 2010";
const UINT8 ControlPanelSystemInfo3[]="AUTHOR:";
const UINT8 ControlPanelSystemInfo4[]=" BOOK CHEN";
const UINT8 ControlPanelSystemInfo5[]="COMPUTER:";
const UINT8 ControlPanelSystemInfo6[]=" CPU: 80X86";
const UINT8 ControlPanelSystemInfo7[]=" RAM: 32MB";

const UINT8 ControlPanelMouseInfo0[]="MOUSE:";
const UINT8 ControlPanelMouseInfo1[]=" INTERFACE PS/2";
const UINT8 ControlPanelMouseInfo2[]=" 2 KEY";

const UINT8 ControlPanelKeyboardInfo0[]="KEYBOARD:";
const UINT8 ControlPanelKeyboardInfo1[]=" INTERFACE PS/2";
const UINT8 ControlPanelKeyboardInfo2[]=" STANDARD 101/102 KEYS";

const UINT8 ControlPanelMonitorInfo0[]="MONITOR:";
const UINT8 ControlPanelMonitorInfo1[]=" VGA 320X200";
const UINT8 ControlPanelMonitorInfo2[]=" 256 COLORS";

const UINT8 ControlPanelDriversInfo0[]="DRIVERS:";
const UINT8 ControlPanelDriversInfo1[]=" KEYBOARD";
const UINT8 ControlPanelDriversInfo2[]=" MOUSE";
const UINT8 ControlPanelDriversInfo3[]=" VGA";
const UINT8 ControlPanelDriversInfo4[]=" COM1";
const UINT8 ControlPanelDriversInfo5[]=" COM2";
const UINT8 ControlPanelDriversInfo6[]=" LPT1";
const UINT8 ControlPanelDriversInfo7[]=" FDC";

DESK_CONTROLPANEL_CONTROL DeskControlPanel;

VOID DeskControlPanelInit(VOID){
	/* creat windows used in control panel*/
	//control panel...system window
	//window parameter
	WindowVariableInit(&DeskControlPanel.SystemWindow,WINDOW_TYPE_CONTROLPANEL);
    DeskControlPanel.SystemWindow.pTitle=(UINT8 *)ControlPanelSystem; 
    //window table initial
    DeskControlPanel.SystemWindow.UserTableList=(WINDOW_TABLE *)NULL;
    DeskControlPanel.SystemWindow.OutlineTable.Type=WINDOW_TABLE_OUTLINE;
    DeskControlPanel.SystemWindow.OutlineTable.DeviceList=(WINDOW_DEVICE *)NULL;
    DeskControlPanel.SystemWindow.HeaderTable.Type=WINDOW_TABLE_HEADER;
    DeskControlPanel.SystemWindow.HeaderTable.DeviceList=(WINDOW_DEVICE *)NULL;
    DeskControlPanel.SystemUserTable.Type=WINDOW_TABLE_GENERAL;
    DeskControlPanel.SystemUserTable.DeviceList=(WINDOW_DEVICE *)NULL;
    DeskTableUserTableAdd(&DeskControlPanel.SystemWindow,&DeskControlPanel.SystemUserTable);
    //creat user device
    BoardCreat(&DeskControlPanel.SystemBoard,140,80);
	DeskControlPanel.DeskDeviceSystem.Type=WINDOW_DEVICE_BOARD;
	DeskControlPanel.DeskDeviceSystem.pDevice=(UINT32 *)(&DeskControlPanel.SystemBoard);
    DeskControlPanel.SystemUserTable.Area.X=0;
    DeskControlPanel.SystemUserTable.Area.Y=0;
    DeskControlPanel.SystemUserTable.Area.W=DeskControlPanel.SystemBoard.Area.W;
    DeskControlPanel.SystemUserTable.Area.H=DeskControlPanel.SystemBoard.Area.H;
    DeskTableWindowDeviceAdd(&DeskControlPanel.SystemUserTable,&DeskControlPanel.DeskDeviceSystem);
    //setup table and device relationship ,and calculate area parameters
    WindowAreaInitial(&DeskControlPanel.SystemWindow); //display area,device area,devicedisplay area calculation 
    WindowOutlineCalculate(&DeskControlPanel.SystemWindow);
    WindowOutlineTableInitial(&DeskControlPanel.SystemWindow);
    WindowHeaderCalculate(&DeskControlPanel.SystemWindow);
    WindowHeaderTableInitial(&DeskControlPanel.SystemWindow);

    DeskControlPanelSystemWindowDraw();
	//control panel...mouse window
	//window parameter
	WindowVariableInit(&DeskControlPanel.MouseWindow,WINDOW_TYPE_CONTROLPANEL);
    DeskControlPanel.MouseWindow.pTitle=(UINT8 *)ControlPanelMouse;  
    
    DeskControlPanel.MouseWindow.WindowBox.Type=WINDOW_WINDOWBOX_GENERAL;
    DeskControlPanel.MouseWindow.WindowBox.pWindow=(UINT32 *)&DeskControlPanel.MouseWindow;
    DeskControlPanel.MouseWindow.WindowBox.ActiveGfx.BgColor=GFX_COLOR_BLUE3;
    DeskControlPanel.MouseWindow.WindowBox.ActiveGfx.FgColor=GFX_COLOR_BLUE3;
    DeskControlPanel.MouseWindow.WindowBox.ActiveGfx.FontColor=GFX_COLOR_WHITE;
    DeskControlPanel.MouseWindow.WindowBox.InactiveGfx.BgColor=GFX_COLOR_GRAY;
    DeskControlPanel.MouseWindow.WindowBox.InactiveGfx.FgColor=GFX_COLOR_GRAY;
    DeskControlPanel.MouseWindow.WindowBox.InactiveGfx.FontColor=GFX_COLOR_WHITE;
    
    DeskControlPanel.MouseWindow.WindowBox.Area.X=0;
    DeskControlPanel.MouseWindow.WindowBox.Area.Y=0;
    DeskControlPanel.MouseWindow.WindowBox.Area.W=0;
    DeskControlPanel.MouseWindow.WindowBox.Area.H=0;
    DeskControlPanel.MouseWindow.DeviceWindowBox.DeviceNumberLeft=WINDOW_WDN_WINDOWBOX;
    DeskControlPanel.MouseWindow.DeviceWindowBox.DeviceNumberMiddle=WINDOW_WDN_NULL;
    DeskControlPanel.MouseWindow.DeviceWindowBox.DeviceNumberRight=WINDOW_WDN_NULL;
    DeskControlPanel.MouseWindow.DeviceWindowBox.Type=WINDOW_DEVICE_WINDOWBOX;
    DeskControlPanel.MouseWindow.DeviceWindowBox.pDevice=(UINT32 *)&DeskControlPanel.MouseWindow.WindowBox;
    //window table initial
    DeskControlPanel.MouseWindow.UserTableList=(WINDOW_TABLE *)NULL;
    DeskControlPanel.MouseWindow.OutlineTable.Type=WINDOW_TABLE_OUTLINE;
    DeskControlPanel.MouseWindow.OutlineTable.DeviceList=(WINDOW_DEVICE *)NULL;
    DeskControlPanel.MouseWindow.HeaderTable.Type=WINDOW_TABLE_HEADER;
    DeskControlPanel.MouseWindow.HeaderTable.DeviceList=(WINDOW_DEVICE *)NULL;
    DeskControlPanel.MouseUserTable.Type=WINDOW_TABLE_GENERAL;
    DeskControlPanel.MouseUserTable.DeviceList=(WINDOW_DEVICE *)NULL;
    DeskTableUserTableAdd(&DeskControlPanel.MouseWindow,&DeskControlPanel.MouseUserTable);
    //creat user device
    BoardCreat(&DeskControlPanel.MouseBoard,130,30);
	DeskControlPanel.DeskDeviceMouse.Type=WINDOW_DEVICE_BOARD;
	DeskControlPanel.DeskDeviceMouse.pDevice=(UINT32 *)(&DeskControlPanel.MouseBoard);
    DeskControlPanel.MouseUserTable.Area.X=0;
    DeskControlPanel.MouseUserTable.Area.Y=0;
    DeskControlPanel.MouseUserTable.Area.W=DeskControlPanel.MouseBoard.Area.W;
    DeskControlPanel.MouseUserTable.Area.H=DeskControlPanel.MouseBoard.Area.H;
    DeskTableWindowDeviceAdd(&DeskControlPanel.MouseUserTable,&DeskControlPanel.DeskDeviceMouse);
    
    //setup table and device relationship ,and calculate area parameters
    WindowAreaInitial(&DeskControlPanel.MouseWindow);
    WindowOutlineCalculate(&DeskControlPanel.MouseWindow);
    WindowOutlineTableInitial(&DeskControlPanel.MouseWindow);
    WindowHeaderCalculate(&DeskControlPanel.MouseWindow);
    WindowHeaderTableInitial(&DeskControlPanel.MouseWindow);
    
    DeskControlPanelMouseWindowDraw();
	//control panel...keyboard window
	//window parameter
	WindowVariableInit(&DeskControlPanel.KeyboardWindow,WINDOW_TYPE_CONTROLPANEL);
    DeskControlPanel.KeyboardWindow.pTitle=(UINT8 *)ControlPanelKeyboard;
    
    DeskControlPanel.KeyboardWindow.WindowBox.Type=WINDOW_WINDOWBOX_GENERAL;
    DeskControlPanel.KeyboardWindow.WindowBox.pWindow=(UINT32 *)&DeskControlPanel.KeyboardWindow;
    DeskControlPanel.KeyboardWindow.WindowBox.ActiveGfx.BgColor=GFX_COLOR_BLUE3;
    DeskControlPanel.KeyboardWindow.WindowBox.ActiveGfx.FgColor=GFX_COLOR_BLUE3;
    DeskControlPanel.KeyboardWindow.WindowBox.ActiveGfx.FontColor=GFX_COLOR_WHITE;
    DeskControlPanel.KeyboardWindow.WindowBox.InactiveGfx.BgColor=GFX_COLOR_GRAY;
    DeskControlPanel.KeyboardWindow.WindowBox.InactiveGfx.FgColor=GFX_COLOR_GRAY;
    DeskControlPanel.KeyboardWindow.WindowBox.InactiveGfx.FontColor=GFX_COLOR_WHITE;
    
    DeskControlPanel.KeyboardWindow.WindowBox.Area.X=0;
    DeskControlPanel.KeyboardWindow.WindowBox.Area.Y=0;
    DeskControlPanel.KeyboardWindow.WindowBox.Area.W=0;
    DeskControlPanel.KeyboardWindow.WindowBox.Area.H=0;
    DeskControlPanel.KeyboardWindow.DeviceWindowBox.DeviceNumberLeft=WINDOW_WDN_WINDOWBOX;
    DeskControlPanel.KeyboardWindow.DeviceWindowBox.DeviceNumberMiddle=WINDOW_WDN_NULL;
    DeskControlPanel.KeyboardWindow.DeviceWindowBox.DeviceNumberRight=WINDOW_WDN_NULL;
    DeskControlPanel.KeyboardWindow.DeviceWindowBox.Type=WINDOW_DEVICE_WINDOWBOX;
    DeskControlPanel.KeyboardWindow.DeviceWindowBox.pDevice=(UINT32 *)&DeskControlPanel.KeyboardWindow.WindowBox;
	//window tables initialize
    DeskControlPanel.KeyboardWindow.UserTableList=(WINDOW_TABLE *)NULL;
    DeskControlPanel.KeyboardWindow.OutlineTable.Type=WINDOW_TABLE_OUTLINE;
    DeskControlPanel.KeyboardWindow.OutlineTable.DeviceList=(WINDOW_DEVICE *)NULL;
    DeskControlPanel.KeyboardWindow.HeaderTable.Type=WINDOW_TABLE_HEADER;
    DeskControlPanel.KeyboardWindow.HeaderTable.DeviceList=(WINDOW_DEVICE *)NULL;
    DeskControlPanel.KeyboardUserTable.Type=WINDOW_TABLE_GENERAL;
    DeskControlPanel.KeyboardUserTable.DeviceList=(WINDOW_DEVICE *)NULL;
    DeskTableUserTableAdd(&DeskControlPanel.KeyboardWindow,&DeskControlPanel.KeyboardUserTable);
    //creat device
    BoardCreat(&DeskControlPanel.KeyboardBoard,180,30);
	DeskControlPanel.DeskDeviceKeyboard.Type=WINDOW_DEVICE_BOARD;
	DeskControlPanel.DeskDeviceKeyboard.pDevice=(UINT32 *)(&DeskControlPanel.KeyboardBoard);
    DeskControlPanel.KeyboardUserTable.Area.X=0;
    DeskControlPanel.KeyboardUserTable.Area.Y=0;
    DeskControlPanel.KeyboardUserTable.Area.W=DeskControlPanel.KeyboardBoard.Area.W;
    DeskControlPanel.KeyboardUserTable.Area.H=DeskControlPanel.KeyboardBoard.Area.H;
    DeskTableWindowDeviceAdd(&DeskControlPanel.KeyboardUserTable,&DeskControlPanel.DeskDeviceKeyboard);
    
    //setup table and device relationship ,and calculate area parameters
    WindowAreaInitial(&DeskControlPanel.KeyboardWindow);
    WindowOutlineCalculate(&DeskControlPanel.KeyboardWindow);
    WindowOutlineTableInitial(&DeskControlPanel.KeyboardWindow);
    WindowHeaderCalculate(&DeskControlPanel.KeyboardWindow);
    WindowHeaderTableInitial(&DeskControlPanel.KeyboardWindow);
    
    DeskControlPanelKeyboardWindowDraw();
	//control panel...Monitor window 
	//window parameter
	WindowVariableInit(&DeskControlPanel.MonitorWindow,WINDOW_TYPE_CONTROLPANEL);
    DeskControlPanel.MonitorWindow.pTitle=(UINT8 *)ControlPanelMonitor;  
    
    DeskControlPanel.MonitorWindow.WindowBox.Type=WINDOW_WINDOWBOX_GENERAL;
    DeskControlPanel.MonitorWindow.WindowBox.pWindow=(UINT32 *)&DeskControlPanel.MonitorWindow;
    DeskControlPanel.MonitorWindow.WindowBox.ActiveGfx.BgColor=GFX_COLOR_BLUE3;
    DeskControlPanel.MonitorWindow.WindowBox.ActiveGfx.FgColor=GFX_COLOR_BLUE3;
    DeskControlPanel.MonitorWindow.WindowBox.ActiveGfx.FontColor=GFX_COLOR_WHITE;
    DeskControlPanel.MonitorWindow.WindowBox.InactiveGfx.BgColor=GFX_COLOR_GRAY;
    DeskControlPanel.MonitorWindow.WindowBox.InactiveGfx.FgColor=GFX_COLOR_GRAY;
    DeskControlPanel.MonitorWindow.WindowBox.InactiveGfx.FontColor=GFX_COLOR_WHITE;
    
    DeskControlPanel.MonitorWindow.WindowBox.Area.X=0;
    DeskControlPanel.MonitorWindow.WindowBox.Area.Y=0;
    DeskControlPanel.MonitorWindow.WindowBox.Area.W=0;
    DeskControlPanel.MonitorWindow.WindowBox.Area.H=0;
    DeskControlPanel.MonitorWindow.DeviceWindowBox.DeviceNumberLeft=WINDOW_WDN_WINDOWBOX;
    DeskControlPanel.MonitorWindow.DeviceWindowBox.DeviceNumberMiddle=WINDOW_WDN_NULL;
    DeskControlPanel.MonitorWindow.DeviceWindowBox.DeviceNumberRight=WINDOW_WDN_NULL;
    DeskControlPanel.MonitorWindow.DeviceWindowBox.Type=WINDOW_DEVICE_WINDOWBOX;
    DeskControlPanel.MonitorWindow.DeviceWindowBox.pDevice=(UINT32 *)&DeskControlPanel.MonitorWindow.WindowBox;
	//window tables initialize
    DeskControlPanel.MonitorWindow.UserTableList=(WINDOW_TABLE *)NULL;
    DeskControlPanel.MonitorWindow.OutlineTable.Type=WINDOW_TABLE_OUTLINE;
    DeskControlPanel.MonitorWindow.OutlineTable.DeviceList=(WINDOW_DEVICE *)NULL;
    DeskControlPanel.MonitorWindow.HeaderTable.Type=WINDOW_TABLE_HEADER;
    DeskControlPanel.MonitorWindow.HeaderTable.DeviceList=(WINDOW_DEVICE *)NULL;
    DeskControlPanel.MonitorUserTable.Type=WINDOW_TABLE_GENERAL;
    DeskControlPanel.MonitorUserTable.DeviceList=(WINDOW_DEVICE *)NULL;
    DeskTableUserTableAdd(&DeskControlPanel.MonitorWindow,&DeskControlPanel.MonitorUserTable);
    //creat device
    BoardCreat(&DeskControlPanel.MonitorBoard,100,30);
	DeskControlPanel.DeskDeviceMonitor.Type=WINDOW_DEVICE_BOARD;
	DeskControlPanel.DeskDeviceMonitor.pDevice=(UINT32 *)(&DeskControlPanel.MonitorBoard);
    DeskControlPanel.MonitorUserTable.Area.X=0;
    DeskControlPanel.MonitorUserTable.Area.Y=0;
    DeskControlPanel.MonitorUserTable.Area.W=DeskControlPanel.MonitorBoard.Area.W;
    DeskControlPanel.MonitorUserTable.Area.H=DeskControlPanel.MonitorBoard.Area.H;
    DeskTableWindowDeviceAdd(&DeskControlPanel.MonitorUserTable,&DeskControlPanel.DeskDeviceMonitor);
    
    //setup table and device relationship ,and calculate area parameters
    WindowAreaInitial(&DeskControlPanel.MonitorWindow);
    WindowOutlineCalculate(&DeskControlPanel.MonitorWindow);
    WindowOutlineTableInitial(&DeskControlPanel.MonitorWindow);
    WindowHeaderCalculate(&DeskControlPanel.MonitorWindow);
    WindowHeaderTableInitial(&DeskControlPanel.MonitorWindow);
    
    DeskControlPanelMonitorWindowDraw();
    //control panel...drivers window
	//window parameter
	WindowVariableInit(&DeskControlPanel.DriversWindow,WINDOW_TYPE_CONTROLPANEL);
    DeskControlPanel.DriversWindow.pTitle=(UINT8 *)ControlPanelDrivers;  
    
    DeskControlPanel.DriversWindow.WindowBox.Type=WINDOW_WINDOWBOX_GENERAL;
    DeskControlPanel.DriversWindow.WindowBox.pWindow=(UINT32 *)&DeskControlPanel.DriversWindow;
    DeskControlPanel.DriversWindow.WindowBox.ActiveGfx.BgColor=GFX_COLOR_BLUE3;
    DeskControlPanel.DriversWindow.WindowBox.ActiveGfx.FgColor=GFX_COLOR_BLUE3;
    DeskControlPanel.DriversWindow.WindowBox.ActiveGfx.FontColor=GFX_COLOR_WHITE;
    DeskControlPanel.DriversWindow.WindowBox.InactiveGfx.BgColor=GFX_COLOR_GRAY;
    DeskControlPanel.DriversWindow.WindowBox.InactiveGfx.FgColor=GFX_COLOR_GRAY;
    DeskControlPanel.DriversWindow.WindowBox.InactiveGfx.FontColor=GFX_COLOR_WHITE;
    
    DeskControlPanel.DriversWindow.WindowBox.Area.X=0;
    DeskControlPanel.DriversWindow.WindowBox.Area.Y=0;
    DeskControlPanel.DriversWindow.WindowBox.Area.W=0;
    DeskControlPanel.DriversWindow.WindowBox.Area.H=0;
    DeskControlPanel.DriversWindow.DeviceWindowBox.DeviceNumberLeft=WINDOW_WDN_WINDOWBOX;
    DeskControlPanel.DriversWindow.DeviceWindowBox.DeviceNumberMiddle=WINDOW_WDN_NULL;
    DeskControlPanel.DriversWindow.DeviceWindowBox.DeviceNumberRight=WINDOW_WDN_NULL;
    DeskControlPanel.DriversWindow.DeviceWindowBox.Type=WINDOW_DEVICE_WINDOWBOX;
    DeskControlPanel.DriversWindow.DeviceWindowBox.pDevice=(UINT32 *)&DeskControlPanel.DriversWindow.WindowBox;
	//window tables initialize
    DeskControlPanel.DriversWindow.UserTableList=(WINDOW_TABLE *)NULL;
    DeskControlPanel.DriversWindow.OutlineTable.Type=WINDOW_TABLE_OUTLINE;
    DeskControlPanel.DriversWindow.OutlineTable.DeviceList=(WINDOW_DEVICE *)NULL;
    DeskControlPanel.DriversWindow.HeaderTable.Type=WINDOW_TABLE_HEADER;
    DeskControlPanel.DriversWindow.HeaderTable.DeviceList=(WINDOW_DEVICE *)NULL;
    DeskControlPanel.DriversUserTable.Type=WINDOW_TABLE_GENERAL;
    DeskControlPanel.DriversUserTable.DeviceList=(WINDOW_DEVICE *)NULL;
    DeskTableUserTableAdd(&DeskControlPanel.DriversWindow,&DeskControlPanel.DriversUserTable);
    //creat device
    BoardCreat(&DeskControlPanel.DriversBoard,80,72);
	DeskControlPanel.DeskDeviceDrivers.Type=WINDOW_DEVICE_BOARD;
	DeskControlPanel.DeskDeviceDrivers.pDevice=(UINT32 *)(&DeskControlPanel.DriversBoard);
    DeskControlPanel.DriversUserTable.Area.X=0;
    DeskControlPanel.DriversUserTable.Area.Y=0;
    DeskControlPanel.DriversUserTable.Area.W=DeskControlPanel.DriversBoard.Area.W;
    DeskControlPanel.DriversUserTable.Area.H=DeskControlPanel.DriversBoard.Area.H;
    DeskTableWindowDeviceAdd(&DeskControlPanel.DriversUserTable,&DeskControlPanel.DeskDeviceDrivers);
    //setup table and device relationship ,and calculate area parameters
    WindowAreaInitial(&DeskControlPanel.DriversWindow);
    WindowOutlineCalculate(&DeskControlPanel.DriversWindow);
    WindowOutlineTableInitial(&DeskControlPanel.DriversWindow);
    WindowHeaderCalculate(&DeskControlPanel.DriversWindow);
    WindowHeaderTableInitial(&DeskControlPanel.DriversWindow);

    DeskControlPanelDriversWindowDraw();
    
    //control panel...palette window
	//window parameter
	WindowVariableInit(&DeskControlPanel.PaletteWindow,WINDOW_TYPE_CONTROLPANEL);
    DeskControlPanel.PaletteWindow.pTitle=(UINT8 *)ControlPanelPalette;  
    
    DeskControlPanel.PaletteWindow.WindowBox.Type=WINDOW_WINDOWBOX_GENERAL;
    DeskControlPanel.PaletteWindow.WindowBox.pWindow=(UINT32 *)&DeskControlPanel.PaletteWindow;
    DeskControlPanel.PaletteWindow.WindowBox.ActiveGfx.BgColor=GFX_COLOR_BLUE3;
    DeskControlPanel.PaletteWindow.WindowBox.ActiveGfx.FgColor=GFX_COLOR_BLUE3;
    DeskControlPanel.PaletteWindow.WindowBox.ActiveGfx.FontColor=GFX_COLOR_WHITE;
    DeskControlPanel.PaletteWindow.WindowBox.InactiveGfx.BgColor=GFX_COLOR_GRAY;
    DeskControlPanel.PaletteWindow.WindowBox.InactiveGfx.FgColor=GFX_COLOR_GRAY;
    DeskControlPanel.PaletteWindow.WindowBox.InactiveGfx.FontColor=GFX_COLOR_WHITE;
    
    DeskControlPanel.PaletteWindow.WindowBox.Area.X=0;
    DeskControlPanel.PaletteWindow.WindowBox.Area.Y=0;
    DeskControlPanel.PaletteWindow.WindowBox.Area.W=0;
    DeskControlPanel.PaletteWindow.WindowBox.Area.H=0;
    DeskControlPanel.PaletteWindow.DeviceWindowBox.DeviceNumberLeft=WINDOW_WDN_WINDOWBOX;
    DeskControlPanel.PaletteWindow.DeviceWindowBox.DeviceNumberMiddle=WINDOW_WDN_NULL;
    DeskControlPanel.PaletteWindow.DeviceWindowBox.DeviceNumberRight=WINDOW_WDN_NULL;
    DeskControlPanel.PaletteWindow.DeviceWindowBox.Type=WINDOW_DEVICE_WINDOWBOX;
    DeskControlPanel.PaletteWindow.DeviceWindowBox.pDevice=(UINT32 *)&DeskControlPanel.PaletteWindow.WindowBox;
	//window tables initialize
    DeskControlPanel.PaletteWindow.UserTableList=(WINDOW_TABLE *)NULL;
    DeskControlPanel.PaletteWindow.OutlineTable.Type=WINDOW_TABLE_OUTLINE;
    DeskControlPanel.PaletteWindow.OutlineTable.DeviceList=(WINDOW_DEVICE *)NULL;
    DeskControlPanel.PaletteWindow.HeaderTable.Type=WINDOW_TABLE_HEADER;
    DeskControlPanel.PaletteWindow.HeaderTable.DeviceList=(WINDOW_DEVICE *)NULL;
    DeskControlPanel.PaletteUserTable.Type=WINDOW_TABLE_GENERAL;
    DeskControlPanel.PaletteUserTable.DeviceList=(WINDOW_DEVICE *)NULL;
    DeskTableUserTableAdd(&DeskControlPanel.PaletteWindow,&DeskControlPanel.PaletteUserTable);
    //creat device
    BoardCreat(&DeskControlPanel.PaletteBoard,8*16,8*16); // 256 8*8 squares
	DeskControlPanel.DeskDevicePalette.Type=WINDOW_DEVICE_BOARD;
	DeskControlPanel.DeskDevicePalette.pDevice=(UINT32 *)(&DeskControlPanel.PaletteBoard);
    DeskControlPanel.PaletteUserTable.Area.X=0;
    DeskControlPanel.PaletteUserTable.Area.Y=0;
    DeskControlPanel.PaletteUserTable.Area.W=DeskControlPanel.PaletteBoard.Area.W;
    DeskControlPanel.PaletteUserTable.Area.H=DeskControlPanel.PaletteBoard.Area.H;
    DeskTableWindowDeviceAdd(&DeskControlPanel.PaletteUserTable,&DeskControlPanel.DeskDevicePalette);
    //setup table and device relationship ,and calculate area parameters
    WindowAreaInitial(&DeskControlPanel.PaletteWindow);
    WindowOutlineCalculate(&DeskControlPanel.PaletteWindow);
    WindowOutlineTableInitial(&DeskControlPanel.PaletteWindow);
    WindowHeaderCalculate(&DeskControlPanel.PaletteWindow);
    WindowHeaderTableInitial(&DeskControlPanel.PaletteWindow);
    
    DeskControlPanelPaletteWindowDraw();
}

VOID DeskControlPanelSystemWindowDraw(VOID){
	GRAPHIC_POSITION Position;
	
    Position.X=1;
    Position.Y=1;
	BoardGoto(&DeskControlPanel.SystemBoard,&Position);
    BoardStringPrint(&DeskControlPanel.SystemBoard,ControlPanelSystemInfo0);
	Position.X=1;
    Position.Y=1+8;
	BoardGoto(&DeskControlPanel.SystemBoard,&Position);
    BoardStringPrint(&DeskControlPanel.SystemBoard,ControlPanelSystemInfo1);
	Position.X=1;
    Position.Y=1+8*2;
	BoardGoto(&DeskControlPanel.SystemBoard,&Position);
    BoardStringPrint(&DeskControlPanel.SystemBoard,ControlPanelSystemInfo2);
	Position.X=1;
    Position.Y=1+8*4;
	BoardGoto(&DeskControlPanel.SystemBoard,&Position);
    BoardStringPrint(&DeskControlPanel.SystemBoard,ControlPanelSystemInfo3);
	Position.X=1;
    Position.Y=1+8*5;
	BoardGoto(&DeskControlPanel.SystemBoard,&Position);
    BoardStringPrint(&DeskControlPanel.SystemBoard,ControlPanelSystemInfo4);
	Position.X=1;
    Position.Y=1+8*7;
	BoardGoto(&DeskControlPanel.SystemBoard,&Position);
    BoardStringPrint(&DeskControlPanel.SystemBoard,ControlPanelSystemInfo5);
	Position.X=1;
    Position.Y=1+8*8;
	BoardGoto(&DeskControlPanel.SystemBoard,&Position);
    BoardStringPrint(&DeskControlPanel.SystemBoard,ControlPanelSystemInfo6);
	Position.X=1;
    Position.Y=1+8*9;
	BoardGoto(&DeskControlPanel.SystemBoard,&Position);
    BoardStringPrint(&DeskControlPanel.SystemBoard,ControlPanelSystemInfo7);
    
}

VOID DeskControlPanelMouseWindowDraw(VOID){
	GRAPHIC_POSITION Position;

	Position.X=1;
    Position.Y=1;
	BoardGoto(&DeskControlPanel.MouseBoard,&Position);
    BoardStringPrint(&DeskControlPanel.MouseBoard,ControlPanelMouseInfo0);
	Position.X=1;
    Position.Y=1+8;
	BoardGoto(&DeskControlPanel.MouseBoard,&Position);
    BoardStringPrint(&DeskControlPanel.MouseBoard,ControlPanelMouseInfo1);
	Position.X=1;
    Position.Y=1+8*2;
	BoardGoto(&DeskControlPanel.MouseBoard,&Position);
    BoardStringPrint(&DeskControlPanel.MouseBoard,ControlPanelMouseInfo2);
}

VOID DeskControlPanelKeyboardWindowDraw(VOID){
	GRAPHIC_POSITION Position;

	Position.X=1;
    Position.Y=1;
	BoardGoto(&DeskControlPanel.KeyboardBoard,&Position);
    BoardStringPrint(&DeskControlPanel.KeyboardBoard,ControlPanelKeyboardInfo0);
	Position.X=1;
    Position.Y=1+8;
	BoardGoto(&DeskControlPanel.KeyboardBoard,&Position);
    BoardStringPrint(&DeskControlPanel.KeyboardBoard,ControlPanelKeyboardInfo1);
	Position.X=1;
    Position.Y=1+8*2;
	BoardGoto(&DeskControlPanel.KeyboardBoard,&Position);
    BoardStringPrint(&DeskControlPanel.KeyboardBoard,ControlPanelKeyboardInfo2);
}

VOID DeskControlPanelMonitorWindowDraw(VOID){
	GRAPHIC_POSITION Position;
	
	Position.X=1;
    Position.Y=1;
	BoardGoto(&DeskControlPanel.MonitorBoard,&Position);
    BoardStringPrint(&DeskControlPanel.MonitorBoard,ControlPanelMonitorInfo0);
	Position.X=1;
    Position.Y=1+8;
	BoardGoto(&DeskControlPanel.MonitorBoard,&Position);
    BoardStringPrint(&DeskControlPanel.MonitorBoard,ControlPanelMonitorInfo1);
	Position.X=1;
    Position.Y=1+8*2;
	BoardGoto(&DeskControlPanel.MonitorBoard,&Position);
    BoardStringPrint(&DeskControlPanel.MonitorBoard,ControlPanelMonitorInfo2);
}

VOID DeskControlPanelDriversWindowDraw(VOID){
	GRAPHIC_POSITION Position;
	
	Position.X=1;
    Position.Y=1;
	BoardGoto(&DeskControlPanel.DriversBoard,&Position);
    BoardStringPrint(&DeskControlPanel.DriversBoard,ControlPanelDriversInfo0);
	Position.X=1;
    Position.Y=1+8;
	BoardGoto(&DeskControlPanel.DriversBoard,&Position);
    BoardStringPrint(&DeskControlPanel.DriversBoard,ControlPanelDriversInfo1);
	Position.X=1;
    Position.Y=1+8*2;
	BoardGoto(&DeskControlPanel.DriversBoard,&Position);
    BoardStringPrint(&DeskControlPanel.DriversBoard,ControlPanelDriversInfo2);
	Position.X=1;
    Position.Y=1+8*3;
	BoardGoto(&DeskControlPanel.DriversBoard,&Position);
    BoardStringPrint(&DeskControlPanel.DriversBoard,ControlPanelDriversInfo3);
	Position.X=1;
    Position.Y=1+8*4;
	BoardGoto(&DeskControlPanel.DriversBoard,&Position);
    BoardStringPrint(&DeskControlPanel.DriversBoard,ControlPanelDriversInfo4);
	Position.X=1;
    Position.Y=1+8*5;
	BoardGoto(&DeskControlPanel.DriversBoard,&Position);
    BoardStringPrint(&DeskControlPanel.DriversBoard,ControlPanelDriversInfo5);
	Position.X=1;
    Position.Y=1+8*6;
	BoardGoto(&DeskControlPanel.DriversBoard,&Position);
    BoardStringPrint(&DeskControlPanel.DriversBoard,ControlPanelDriversInfo6);
	Position.X=1;
    Position.Y=1+8*7;
	BoardGoto(&DeskControlPanel.DriversBoard,&Position);
    BoardStringPrint(&DeskControlPanel.DriversBoard,ControlPanelDriversInfo7);
}

VOID DeskControlPanelPaletteWindowDraw(VOID){
	GRAPHIC_AREA Area;
	UINT8 ColorValue,i,j;
	
	Area.X=0;
	Area.Y=0;
	Area.W=8;
	Area.H=8;
	ColorValue=0;
	for(j=0;j<16;j++){
		for(i=0;i<16;i++){
		    BoardRectangleDraw(&DeskControlPanel.PaletteBoard,&Area,ColorValue);
		    Area.X=Area.X+8;
		    ColorValue++;
	    }
	    Area.Y=Area.Y+8;
	    Area.X=0;
    }
}


