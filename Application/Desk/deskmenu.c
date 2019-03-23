#include <includes.h>

const UINT8 DeskMenuStringStartMenu[]="START MENU";
const UINT8 DeskMenuStringControlPanel[]="CONTROL PANEL";
const UINT8 DeskMenuStringPrograms[]="PROGRAMS";
const UINT8 DeskMenuStringShell[]="SHELL";
const UINT8 DeskMenuStringDebuger[]="DEBUGER";
const UINT8 DeskMenuStringHyperTerminal[]="HYPER TERMINAL";
const UINT8 DeskMenuStringCalculator[]="CALCULATOR";
const UINT8 DeskMenuString2048[]="2048";
const UINT8 DeskMenuStringGameBomb[]="GAME BOMB";
const UINT8 DeskMenuStringGameBee[]="GAME BEE";
const UINT8 DeskMenuStringSystem[]="SYSTEM";
const UINT8 DeskMenuStringMouse[]="MOUSE";
const UINT8 DeskMenuStringKeyboard[]="KEYBOARD";
const UINT8 DeskMenuStringMonitor[]="MONITOR";
const UINT8 DeskMenuStringDrivers[]="DRIVER";
const UINT8 DeskMenuStringPalette[]="PALETTE";


DESK_MENU_CONTROL DeskMenuCtrl;

UINT8 Menu_W = DESK_MENU_STARTMENU_WIDTH-4;
UINT8 MENU_ITEM_HEIGHT = 14;

VOID DeskMenuInit(VOID){
    //start menu
    DeskMenuCtrl.StartTable.Type=WINDOW_TABLE_GENERAL;
    DeskMenuCtrl.StartTable.DeviceList=(WINDOW_DEVICE *)NULL;
    DeskMenuCtrl.StartTable.Gfx.BgColor=GFX_COLOR_BLUE1;
    DeskMenuCtrl.StartTable.Gfx.FgColor=GFX_COLOR_BLUE1;
    DeskMenuCtrl.StartTable.Gfx.FontColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.StartTable.Area.X=0;
    DeskMenuCtrl.StartTable.Area.Y=0;
    DeskMenuCtrl.StartTable.Area.W=DESK_MENU_STARTMENU_WIDTH;
    DeskMenuCtrl.StartTable.Area.H=DESK_MENU_STARTMENU_HEIGHT;
    
    WindowVariableInit(&DeskMenuCtrl.StartWindow,WINDOW_TYPE_STARTMENU);
    DeskMenuCtrl.StartWindow.pTitle=(UINT8 *)DeskMenuStringStartMenu;   
    DeskMenuCtrl.StartWindow.UserTableList=(WINDOW_TABLE *)NULL;
    DeskMenuCtrl.StartWindow.OutlineTable.Type=WINDOW_TABLE_OUTLINE;
    DeskMenuCtrl.StartWindow.OutlineTable.DeviceList=(WINDOW_DEVICE *)NULL;
    DeskMenuCtrl.StartWindow.HeaderTable.Type=WINDOW_TABLE_HEADER;
    DeskMenuCtrl.StartWindow.HeaderTable.DeviceList=(WINDOW_DEVICE *)NULL;
    DeskTableUserTableAdd(&DeskMenuCtrl.StartWindow,&DeskMenuCtrl.StartTable);

    WindowAreaInitial(&DeskMenuCtrl.StartWindow);
    WindowOutlineCalculate(&DeskMenuCtrl.StartWindow);
    WindowOutlineTableInitial(&DeskMenuCtrl.StartWindow);
    WindowHeaderCalculate(&DeskMenuCtrl.StartWindow);
    WindowHeaderTableInitial(&DeskMenuCtrl.StartWindow);
    
    DeskMenuCtrl.StartWindow.DisplayArea.X=0;
    DeskMenuCtrl.StartWindow.DisplayArea.Y=OsdCtrl.ScreenArea.H-DESK_WORKBAR_HEIGHT-DeskMenuCtrl.StartWindow.DisplayArea.H;

    DeskTableWindowDeviceAdd(&DeskMenuCtrl.StartTable,&DeskMenuCtrl.WdControlPanelButton);    
    DeskTableWindowDeviceAdd(&DeskMenuCtrl.StartTable,&DeskMenuCtrl.WdProgramsButton);    
    DeskTableWindowDeviceAdd(&DeskMenuCtrl.StartTable,&DeskMenuCtrl.WdShellButton);
    DeskTableWindowDeviceAdd(&DeskMenuCtrl.StartTable,&DeskMenuCtrl.WdDebugerButton);
    
    DeskMenuCtrl.ControlPanelButton.Type=WINDOW_BUTTON_PUSHBUTTON;
    DeskMenuCtrl.ControlPanelButton.Status=WINDOW_BUTTON_RELEASE;
    DeskMenuCtrl.ControlPanelButton.Active=TRUE;
    DeskMenuCtrl.ControlPanelButton.Dirty=TRUE;
    DeskMenuCtrl.ControlPanelButton.Outline=FALSE; //TRUE;
    DeskMenuCtrl.ControlPanelButton.pName=(UINT8*)DeskMenuStringControlPanel;
    DeskMenuCtrl.ControlPanelButton.pBitmap=(UINT8 *)NULL;
    DeskMenuCtrl.ControlPanelButton.ReleaseGfx.BgColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.ControlPanelButton.ReleaseGfx.FgColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.ControlPanelButton.ReleaseGfx.FontColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.ControlPanelButton.PressGfx.BgColor=GFX_COLOR_GREEN0;
    DeskMenuCtrl.ControlPanelButton.PressGfx.FgColor=GFX_COLOR_GREEN0;
    DeskMenuCtrl.ControlPanelButton.PressGfx.FontColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.ControlPanelButton.InactiveGfx.BgColor=GFX_COLOR_WHITE;
    DeskMenuCtrl.ControlPanelButton.InactiveGfx.FgColor=GFX_COLOR_WHITE;
    DeskMenuCtrl.ControlPanelButton.InactiveGfx.FontColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.ControlPanelButton.Area.X=2;
    DeskMenuCtrl.ControlPanelButton.Area.Y=2;
    DeskMenuCtrl.ControlPanelButton.Area.W=Menu_W;
    DeskMenuCtrl.ControlPanelButton.Area.H=STRING_SIZE+2;
    DeskMenuCtrl.WdControlPanelButton.Type=WINDOW_DEVICE_BUTTON;
    DeskMenuCtrl.WdControlPanelButton.DeviceNumberLeft=DESK_MENU_WDN_CONTROLPANEL;
    DeskMenuCtrl.WdControlPanelButton.DeviceNumberMiddle=WINDOW_WDN_NULL;
    DeskMenuCtrl.WdControlPanelButton.DeviceNumberRight=WINDOW_WDN_NULL;
    DeskMenuCtrl.WdControlPanelButton.pDevice=(UINT32 *)(&DeskMenuCtrl.ControlPanelButton);
    
    DeskMenuCtrl.ProgramsButton.Type=WINDOW_BUTTON_PUSHBUTTON;
    DeskMenuCtrl.ProgramsButton.Status=WINDOW_BUTTON_RELEASE;
    DeskMenuCtrl.ProgramsButton.Active=TRUE;
    DeskMenuCtrl.ProgramsButton.Dirty=TRUE;
    DeskMenuCtrl.ProgramsButton.Outline=FALSE; //TRUE;
    DeskMenuCtrl.ProgramsButton.pName=(UINT8*)DeskMenuStringPrograms;
    DeskMenuCtrl.ProgramsButton.pBitmap=(UINT8 *)NULL;
    DeskMenuCtrl.ProgramsButton.ReleaseGfx.BgColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.ProgramsButton.ReleaseGfx.FgColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.ProgramsButton.ReleaseGfx.FontColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.ProgramsButton.PressGfx.BgColor=GFX_COLOR_GREEN0;
    DeskMenuCtrl.ProgramsButton.PressGfx.FgColor=GFX_COLOR_GREEN0;
    DeskMenuCtrl.ProgramsButton.PressGfx.FontColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.ProgramsButton.InactiveGfx.BgColor=GFX_COLOR_WHITE;
    DeskMenuCtrl.ProgramsButton.InactiveGfx.FgColor=GFX_COLOR_WHITE;
    DeskMenuCtrl.ProgramsButton.InactiveGfx.FontColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.ProgramsButton.Area.X=2;
    DeskMenuCtrl.ProgramsButton.Area.Y=2+2+2+STRING_SIZE;
    DeskMenuCtrl.ProgramsButton.Area.W=Menu_W;
    DeskMenuCtrl.ProgramsButton.Area.H=STRING_SIZE+2;
    DeskMenuCtrl.WdProgramsButton.Type=WINDOW_DEVICE_BUTTON;
    DeskMenuCtrl.WdProgramsButton.DeviceNumberLeft=DESK_MENU_WDN_PROGRAMS;
    DeskMenuCtrl.WdProgramsButton.DeviceNumberMiddle=WINDOW_WDN_NULL;
    DeskMenuCtrl.WdProgramsButton.DeviceNumberRight=WINDOW_WDN_NULL;
    DeskMenuCtrl.WdProgramsButton.pDevice=(UINT32 *)(&DeskMenuCtrl.ProgramsButton);
    
    DeskMenuCtrl.ShellButton.Type=WINDOW_BUTTON_PUSHBUTTON;
    DeskMenuCtrl.ShellButton.Status=WINDOW_BUTTON_RELEASE;
    DeskMenuCtrl.ShellButton.Active=TRUE;
    DeskMenuCtrl.ShellButton.Dirty=TRUE;
    DeskMenuCtrl.ShellButton.Outline=FALSE; //TRUE;
    DeskMenuCtrl.ShellButton.pName=(UINT8*)DeskMenuStringShell;
    DeskMenuCtrl.ShellButton.pBitmap=(UINT8 *)NULL;
    DeskMenuCtrl.ShellButton.ReleaseGfx.BgColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.ShellButton.ReleaseGfx.FgColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.ShellButton.ReleaseGfx.FontColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.ShellButton.PressGfx.BgColor=GFX_COLOR_GREEN0;
    DeskMenuCtrl.ShellButton.PressGfx.FgColor=GFX_COLOR_GREEN0;
    DeskMenuCtrl.ShellButton.PressGfx.FontColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.ShellButton.InactiveGfx.BgColor=GFX_COLOR_WHITE;
    DeskMenuCtrl.ShellButton.InactiveGfx.FgColor=GFX_COLOR_WHITE;
    DeskMenuCtrl.ShellButton.InactiveGfx.FontColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.ShellButton.Area.X=2;
    DeskMenuCtrl.ShellButton.Area.Y=2+2+2+2+2+STRING_SIZE*2;
    DeskMenuCtrl.ShellButton.Area.W=Menu_W;
    DeskMenuCtrl.ShellButton.Area.H=STRING_SIZE+2;
    DeskMenuCtrl.WdShellButton.Type=WINDOW_DEVICE_BUTTON;
    DeskMenuCtrl.WdShellButton.DeviceNumberLeft=DESK_MENU_WDN_SHELL;
    DeskMenuCtrl.WdShellButton.DeviceNumberMiddle=WINDOW_WDN_NULL;
    DeskMenuCtrl.WdShellButton.DeviceNumberRight=WINDOW_WDN_NULL;
    DeskMenuCtrl.WdShellButton.pDevice=(UINT32 *)(&DeskMenuCtrl.ShellButton);
    
    DeskMenuCtrl.DebugerButton.Type=WINDOW_BUTTON_PUSHBUTTON;
    DeskMenuCtrl.DebugerButton.Status=WINDOW_BUTTON_RELEASE;
    DeskMenuCtrl.DebugerButton.Active=TRUE;
    DeskMenuCtrl.DebugerButton.Dirty=TRUE;
    DeskMenuCtrl.DebugerButton.Outline=FALSE; //TRUE;
    DeskMenuCtrl.DebugerButton.pName=(UINT8*)DeskMenuStringDebuger;
    DeskMenuCtrl.DebugerButton.pBitmap=(UINT8 *)NULL;
    DeskMenuCtrl.DebugerButton.ReleaseGfx.BgColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.DebugerButton.ReleaseGfx.FgColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.DebugerButton.ReleaseGfx.FontColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.DebugerButton.PressGfx.BgColor=GFX_COLOR_GREEN0;
    DeskMenuCtrl.DebugerButton.PressGfx.FgColor=GFX_COLOR_GREEN0;
    DeskMenuCtrl.DebugerButton.PressGfx.FontColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.DebugerButton.InactiveGfx.BgColor=GFX_COLOR_WHITE;
    DeskMenuCtrl.DebugerButton.InactiveGfx.FgColor=GFX_COLOR_WHITE;
    DeskMenuCtrl.DebugerButton.InactiveGfx.FontColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.DebugerButton.Area.X=2;
    DeskMenuCtrl.DebugerButton.Area.Y=2+2+2+2+2+2+2+STRING_SIZE*3;
    DeskMenuCtrl.DebugerButton.Area.W=Menu_W;
    DeskMenuCtrl.DebugerButton.Area.H=STRING_SIZE+2;
    DeskMenuCtrl.WdDebugerButton.Type=WINDOW_DEVICE_BUTTON;
    DeskMenuCtrl.WdDebugerButton.DeviceNumberLeft=DESK_MENU_WDN_DEBUGER;
    DeskMenuCtrl.WdDebugerButton.DeviceNumberMiddle=WINDOW_WDN_NULL;
    DeskMenuCtrl.WdDebugerButton.DeviceNumberRight=WINDOW_WDN_NULL;
    DeskMenuCtrl.WdDebugerButton.pDevice=(UINT32 *)(&DeskMenuCtrl.DebugerButton);
    
    
    //*****
    // control panel window
    //*****
    DeskMenuCtrl.ControlPanelTable.Type=WINDOW_TABLE_GENERAL;
    DeskMenuCtrl.ControlPanelTable.DeviceList=(WINDOW_DEVICE *)NULL;
    DeskMenuCtrl.ControlPanelTable.Gfx.BgColor=GFX_COLOR_BLUE1;
    DeskMenuCtrl.ControlPanelTable.Gfx.FgColor=GFX_COLOR_BLUE1;
    DeskMenuCtrl.ControlPanelTable.Gfx.FontColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.ControlPanelTable.Area.X=0;
    DeskMenuCtrl.ControlPanelTable.Area.Y=0;
    DeskMenuCtrl.ControlPanelTable.Area.W=DESK_MENU_CONTROLPANEL_WIDTH;
    DeskMenuCtrl.ControlPanelTable.Area.H=DESK_MENU_CONTROLPANEL_HEIGHT;
    
    WindowVariableInit(&DeskMenuCtrl.ControlPanelWindow,WINDOW_TYPE_STARTMENU);
    DeskMenuCtrl.ControlPanelWindow.pTitle=(UINT8 *)DeskMenuStringControlPanel;   
    DeskMenuCtrl.ControlPanelWindow.UserTableList=(WINDOW_TABLE *)NULL;
    DeskMenuCtrl.ControlPanelWindow.OutlineTable.Type=WINDOW_TABLE_OUTLINE;
    DeskMenuCtrl.ControlPanelWindow.OutlineTable.DeviceList=(WINDOW_DEVICE *)NULL;
    DeskMenuCtrl.ControlPanelWindow.HeaderTable.Type=WINDOW_TABLE_HEADER;
    DeskMenuCtrl.ControlPanelWindow.HeaderTable.DeviceList=(WINDOW_DEVICE *)NULL;
    DeskTableUserTableAdd(&DeskMenuCtrl.ControlPanelWindow,&DeskMenuCtrl.ControlPanelTable);
    
    WindowAreaInitial(&DeskMenuCtrl.ControlPanelWindow);
    WindowOutlineCalculate(&DeskMenuCtrl.ControlPanelWindow);
    WindowOutlineTableInitial(&DeskMenuCtrl.ControlPanelWindow);
    WindowHeaderCalculate(&DeskMenuCtrl.ControlPanelWindow);
    WindowHeaderTableInitial(&DeskMenuCtrl.ControlPanelWindow);
    
    DeskMenuCtrl.ControlPanelWindow.DisplayArea.X=DeskMenuCtrl.StartWindow.DisplayArea.W;
    DeskMenuCtrl.ControlPanelWindow.DisplayArea.Y=OsdCtrl.ScreenArea.H-DESK_WORKBAR_HEIGHT-DeskMenuCtrl.ControlPanelWindow.DisplayArea.H;

    DeskTableWindowDeviceAdd(&DeskMenuCtrl.ControlPanelTable,&DeskMenuCtrl.WdSystemButton);  
    DeskTableWindowDeviceAdd(&DeskMenuCtrl.ControlPanelTable,&DeskMenuCtrl.WdMouseButton);    
    DeskTableWindowDeviceAdd(&DeskMenuCtrl.ControlPanelTable,&DeskMenuCtrl.WdKeyboardButton);    
    DeskTableWindowDeviceAdd(&DeskMenuCtrl.ControlPanelTable,&DeskMenuCtrl.WdMonitorButton);    
    DeskTableWindowDeviceAdd(&DeskMenuCtrl.ControlPanelTable,&DeskMenuCtrl.WdDriversButton);    
    DeskTableWindowDeviceAdd(&DeskMenuCtrl.ControlPanelTable,&DeskMenuCtrl.WdPaletteButton);    
    
    DeskMenuCtrl.SystemButton.Type=WINDOW_BUTTON_PUSHBUTTON;
    DeskMenuCtrl.SystemButton.Status=WINDOW_BUTTON_RELEASE;
    DeskMenuCtrl.SystemButton.Active=TRUE;
    DeskMenuCtrl.SystemButton.Dirty=TRUE;
    DeskMenuCtrl.SystemButton.Outline=FALSE; //TRUE;
    DeskMenuCtrl.SystemButton.pName=(UINT8*)DeskMenuStringSystem;
    DeskMenuCtrl.SystemButton.pBitmap=(UINT8 *)NULL;
    DeskMenuCtrl.SystemButton.ReleaseGfx.BgColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.SystemButton.ReleaseGfx.FgColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.SystemButton.ReleaseGfx.FontColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.SystemButton.PressGfx.BgColor=GFX_COLOR_GREEN0;
    DeskMenuCtrl.SystemButton.PressGfx.FgColor=GFX_COLOR_GREEN0;
    DeskMenuCtrl.SystemButton.PressGfx.FontColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.SystemButton.InactiveGfx.BgColor=GFX_COLOR_WHITE;
    DeskMenuCtrl.SystemButton.InactiveGfx.FgColor=GFX_COLOR_WHITE;
    DeskMenuCtrl.SystemButton.InactiveGfx.FontColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.SystemButton.Area.X=2;
    DeskMenuCtrl.SystemButton.Area.Y=2;
    DeskMenuCtrl.SystemButton.Area.W=Menu_W;
    DeskMenuCtrl.SystemButton.Area.H=STRING_SIZE+2;
    DeskMenuCtrl.WdSystemButton.Type=WINDOW_DEVICE_BUTTON;
    DeskMenuCtrl.WdSystemButton.DeviceNumberLeft=DESK_MENU_WDN_SYSTEM;
    DeskMenuCtrl.WdSystemButton.DeviceNumberMiddle=WINDOW_WDN_NULL;
    DeskMenuCtrl.WdSystemButton.DeviceNumberRight=WINDOW_WDN_NULL;
    DeskMenuCtrl.WdSystemButton.pDevice=(UINT32 *)(&DeskMenuCtrl.SystemButton);
    
    DeskMenuCtrl.MouseButton.Type=WINDOW_BUTTON_PUSHBUTTON;
    DeskMenuCtrl.MouseButton.Status=WINDOW_BUTTON_RELEASE;
    DeskMenuCtrl.MouseButton.Active=TRUE;
    DeskMenuCtrl.MouseButton.Dirty=TRUE;
    DeskMenuCtrl.MouseButton.Outline=FALSE; //TRUE;
    DeskMenuCtrl.MouseButton.pName=(UINT8*)DeskMenuStringMouse;
    DeskMenuCtrl.MouseButton.pBitmap=(UINT8 *)NULL;
    DeskMenuCtrl.MouseButton.ReleaseGfx.BgColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.MouseButton.ReleaseGfx.FgColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.MouseButton.ReleaseGfx.FontColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.MouseButton.PressGfx.BgColor=GFX_COLOR_GREEN0;
    DeskMenuCtrl.MouseButton.PressGfx.FgColor=GFX_COLOR_GREEN0;
    DeskMenuCtrl.MouseButton.PressGfx.FontColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.MouseButton.InactiveGfx.BgColor=GFX_COLOR_WHITE;
    DeskMenuCtrl.MouseButton.InactiveGfx.FgColor=GFX_COLOR_WHITE;
    DeskMenuCtrl.MouseButton.InactiveGfx.FontColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.MouseButton.Area.X=2;
    DeskMenuCtrl.MouseButton.Area.Y=2+2+2+STRING_SIZE;
    DeskMenuCtrl.MouseButton.Area.W=Menu_W;
    DeskMenuCtrl.MouseButton.Area.H=STRING_SIZE+2;
    DeskMenuCtrl.WdMouseButton.Type=WINDOW_DEVICE_BUTTON;
    DeskMenuCtrl.WdMouseButton.DeviceNumberLeft=DESK_MENU_WDN_MOUSE;
    DeskMenuCtrl.WdMouseButton.DeviceNumberMiddle=WINDOW_WDN_NULL;
    DeskMenuCtrl.WdMouseButton.DeviceNumberRight=WINDOW_WDN_NULL;
    DeskMenuCtrl.WdMouseButton.pDevice=(UINT32 *)(&DeskMenuCtrl.MouseButton);
    
    DeskMenuCtrl.KeyboardButton.Type=WINDOW_BUTTON_PUSHBUTTON;
    DeskMenuCtrl.KeyboardButton.Status=WINDOW_BUTTON_RELEASE;
    DeskMenuCtrl.KeyboardButton.Active=TRUE;
    DeskMenuCtrl.KeyboardButton.Dirty=TRUE;
    DeskMenuCtrl.KeyboardButton.Outline=FALSE; //TRUE;
    DeskMenuCtrl.KeyboardButton.pName=(UINT8*)DeskMenuStringKeyboard;
    DeskMenuCtrl.KeyboardButton.pBitmap=(UINT8 *)NULL;
    DeskMenuCtrl.KeyboardButton.ReleaseGfx.BgColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.KeyboardButton.ReleaseGfx.FgColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.KeyboardButton.ReleaseGfx.FontColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.KeyboardButton.PressGfx.BgColor=GFX_COLOR_GREEN0;
    DeskMenuCtrl.KeyboardButton.PressGfx.FgColor=GFX_COLOR_GREEN0;
    DeskMenuCtrl.KeyboardButton.PressGfx.FontColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.KeyboardButton.InactiveGfx.BgColor=GFX_COLOR_WHITE;
    DeskMenuCtrl.KeyboardButton.InactiveGfx.FgColor=GFX_COLOR_WHITE;
    DeskMenuCtrl.KeyboardButton.InactiveGfx.FontColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.KeyboardButton.Area.X=2;
    DeskMenuCtrl.KeyboardButton.Area.Y=2+2+2+2+2+STRING_SIZE*2;
    DeskMenuCtrl.KeyboardButton.Area.W=Menu_W;
    DeskMenuCtrl.KeyboardButton.Area.H=STRING_SIZE+2;
    DeskMenuCtrl.WdKeyboardButton.Type=WINDOW_DEVICE_BUTTON;
    DeskMenuCtrl.WdKeyboardButton.DeviceNumberLeft=DESK_MENU_WDN_KEYBOARD;
    DeskMenuCtrl.WdKeyboardButton.DeviceNumberMiddle=WINDOW_WDN_NULL;
    DeskMenuCtrl.WdKeyboardButton.DeviceNumberRight=WINDOW_WDN_NULL;
    DeskMenuCtrl.WdKeyboardButton.pDevice=(UINT32 *)(&DeskMenuCtrl.KeyboardButton);
    
    DeskMenuCtrl.MonitorButton.Type=WINDOW_BUTTON_PUSHBUTTON;
    DeskMenuCtrl.MonitorButton.Status=WINDOW_BUTTON_RELEASE;
    DeskMenuCtrl.MonitorButton.Active=TRUE;
    DeskMenuCtrl.MonitorButton.Dirty=TRUE;
    DeskMenuCtrl.MonitorButton.Outline=FALSE; //TRUE;
    DeskMenuCtrl.MonitorButton.pName=(UINT8*)DeskMenuStringMonitor;
    DeskMenuCtrl.MonitorButton.pBitmap=(UINT8 *)NULL;
    DeskMenuCtrl.MonitorButton.ReleaseGfx.BgColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.MonitorButton.ReleaseGfx.FgColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.MonitorButton.ReleaseGfx.FontColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.MonitorButton.PressGfx.BgColor=GFX_COLOR_GREEN0;
    DeskMenuCtrl.MonitorButton.PressGfx.FgColor=GFX_COLOR_GREEN0;
    DeskMenuCtrl.MonitorButton.PressGfx.FontColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.MonitorButton.InactiveGfx.BgColor=GFX_COLOR_WHITE;
    DeskMenuCtrl.MonitorButton.InactiveGfx.FgColor=GFX_COLOR_WHITE;
    DeskMenuCtrl.MonitorButton.InactiveGfx.FontColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.MonitorButton.Area.X=2;
    DeskMenuCtrl.MonitorButton.Area.Y=2+(4+STRING_SIZE)*3;
    DeskMenuCtrl.MonitorButton.Area.W=Menu_W;
    DeskMenuCtrl.MonitorButton.Area.H=STRING_SIZE+2;
    DeskMenuCtrl.WdMonitorButton.Type=WINDOW_DEVICE_BUTTON;
    DeskMenuCtrl.WdMonitorButton.DeviceNumberLeft=DESK_MENU_WDN_MONITOR;
    DeskMenuCtrl.WdMonitorButton.DeviceNumberMiddle=WINDOW_WDN_NULL;
    DeskMenuCtrl.WdMonitorButton.DeviceNumberRight=WINDOW_WDN_NULL;
    DeskMenuCtrl.WdMonitorButton.pDevice=(UINT32 *)(&DeskMenuCtrl.MonitorButton);
    
    DeskMenuCtrl.DriversButton.Type=WINDOW_BUTTON_PUSHBUTTON;
    DeskMenuCtrl.DriversButton.Status=WINDOW_BUTTON_RELEASE;
    DeskMenuCtrl.DriversButton.Active=TRUE;
    DeskMenuCtrl.DriversButton.Dirty=TRUE;
    DeskMenuCtrl.DriversButton.Outline=FALSE; //TRUE;
    DeskMenuCtrl.DriversButton.pName=(UINT8*)DeskMenuStringDrivers;
    DeskMenuCtrl.DriversButton.pBitmap=(UINT8 *)NULL;
    DeskMenuCtrl.DriversButton.ReleaseGfx.BgColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.DriversButton.ReleaseGfx.FgColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.DriversButton.ReleaseGfx.FontColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.DriversButton.PressGfx.BgColor=GFX_COLOR_GREEN0;
    DeskMenuCtrl.DriversButton.PressGfx.FgColor=GFX_COLOR_GREEN0;
    DeskMenuCtrl.DriversButton.PressGfx.FontColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.DriversButton.InactiveGfx.BgColor=GFX_COLOR_WHITE;
    DeskMenuCtrl.DriversButton.InactiveGfx.FgColor=GFX_COLOR_WHITE;
    DeskMenuCtrl.DriversButton.InactiveGfx.FontColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.DriversButton.Area.X=2;
    DeskMenuCtrl.DriversButton.Area.Y=2+(4+STRING_SIZE)*4;
    DeskMenuCtrl.DriversButton.Area.W=Menu_W;
    DeskMenuCtrl.DriversButton.Area.H=STRING_SIZE+2;
    DeskMenuCtrl.WdDriversButton.Type=WINDOW_DEVICE_BUTTON;
    DeskMenuCtrl.WdDriversButton.DeviceNumberLeft=DESK_MENU_WDN_DRIVERS;
    DeskMenuCtrl.WdDriversButton.DeviceNumberMiddle=WINDOW_WDN_NULL;
    DeskMenuCtrl.WdDriversButton.DeviceNumberRight=WINDOW_WDN_NULL;
    DeskMenuCtrl.WdDriversButton.pDevice=(UINT32 *)(&DeskMenuCtrl.DriversButton);
    
    DeskMenuCtrl.PaletteButton.Type=WINDOW_BUTTON_PUSHBUTTON;
    DeskMenuCtrl.PaletteButton.Status=WINDOW_BUTTON_RELEASE;
    DeskMenuCtrl.PaletteButton.Active=TRUE;
    DeskMenuCtrl.PaletteButton.Dirty=TRUE;
    DeskMenuCtrl.PaletteButton.Outline=FALSE; //TRUE;
    DeskMenuCtrl.PaletteButton.pName=(UINT8*)DeskMenuStringPalette;
    DeskMenuCtrl.PaletteButton.pBitmap=(UINT8 *)NULL;
    DeskMenuCtrl.PaletteButton.ReleaseGfx.BgColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.PaletteButton.ReleaseGfx.FgColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.PaletteButton.ReleaseGfx.FontColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.PaletteButton.PressGfx.BgColor=GFX_COLOR_GREEN0;
    DeskMenuCtrl.PaletteButton.PressGfx.FgColor=GFX_COLOR_GREEN0;
    DeskMenuCtrl.PaletteButton.PressGfx.FontColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.PaletteButton.InactiveGfx.BgColor=GFX_COLOR_WHITE;
    DeskMenuCtrl.PaletteButton.InactiveGfx.FgColor=GFX_COLOR_WHITE;
    DeskMenuCtrl.PaletteButton.InactiveGfx.FontColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.PaletteButton.Area.X=2;
    DeskMenuCtrl.PaletteButton.Area.Y=2+(4+STRING_SIZE)*5;
    DeskMenuCtrl.PaletteButton.Area.W=Menu_W;
    DeskMenuCtrl.PaletteButton.Area.H=STRING_SIZE+2;
    DeskMenuCtrl.WdPaletteButton.Type=WINDOW_DEVICE_BUTTON;
    DeskMenuCtrl.WdPaletteButton.DeviceNumberLeft=DESK_MENU_WDN_PALETTE;
    DeskMenuCtrl.WdPaletteButton.DeviceNumberMiddle=WINDOW_WDN_NULL;
    DeskMenuCtrl.WdPaletteButton.DeviceNumberRight=WINDOW_WDN_NULL;
    DeskMenuCtrl.WdPaletteButton.pDevice=(UINT32 *)(&DeskMenuCtrl.PaletteButton);

    //*****
    // programs window
    //*****
    DeskMenuCtrl.ProgramsTable.Type=WINDOW_TABLE_GENERAL;
    DeskMenuCtrl.ProgramsTable.DeviceList=(WINDOW_DEVICE *)NULL;
    DeskMenuCtrl.ProgramsTable.Gfx.BgColor=GFX_COLOR_BLUE1;
    DeskMenuCtrl.ProgramsTable.Gfx.FgColor=GFX_COLOR_BLUE1;
    DeskMenuCtrl.ProgramsTable.Gfx.FontColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.ProgramsTable.Area.X=0;
    DeskMenuCtrl.ProgramsTable.Area.Y=0;
    DeskMenuCtrl.ProgramsTable.Area.W=DESK_MENU_PROGRAMS_WIDTH;
    DeskMenuCtrl.ProgramsTable.Area.H=DESK_MENU_PROGRAMS_HEIGHT+MENU_ITEM_HEIGHT;
    
    WindowVariableInit(&DeskMenuCtrl.ProgramsWindow,WINDOW_TYPE_STARTMENU);
    DeskMenuCtrl.ProgramsWindow.pTitle=(UINT8 *)DeskMenuStringPrograms;   
    DeskMenuCtrl.ProgramsWindow.UserTableList=(WINDOW_TABLE *)NULL;
    DeskMenuCtrl.ProgramsWindow.OutlineTable.Type=WINDOW_TABLE_OUTLINE;
    DeskMenuCtrl.ProgramsWindow.OutlineTable.DeviceList=(WINDOW_DEVICE *)NULL;
    DeskMenuCtrl.ProgramsWindow.HeaderTable.Type=WINDOW_TABLE_HEADER;
    DeskMenuCtrl.ProgramsWindow.HeaderTable.DeviceList=(WINDOW_DEVICE *)NULL;
    DeskTableUserTableAdd(&DeskMenuCtrl.ProgramsWindow,&DeskMenuCtrl.ProgramsTable);
    
    WindowAreaInitial(&DeskMenuCtrl.ProgramsWindow);
    WindowOutlineCalculate(&DeskMenuCtrl.ProgramsWindow);
    WindowOutlineTableInitial(&DeskMenuCtrl.ProgramsWindow);
    WindowHeaderCalculate(&DeskMenuCtrl.ProgramsWindow);
    WindowHeaderTableInitial(&DeskMenuCtrl.ProgramsWindow);
    
    DeskMenuCtrl.ProgramsWindow.DisplayArea.X=DeskMenuCtrl.StartWindow.DisplayArea.W;
    DeskMenuCtrl.ProgramsWindow.DisplayArea.Y=OsdCtrl.ScreenArea.H-DESK_WORKBAR_HEIGHT-DeskMenuCtrl.ProgramsWindow.DisplayArea.H; 

    DeskTableWindowDeviceAdd(&DeskMenuCtrl.ProgramsTable,&DeskMenuCtrl.WdShellButton2);  
    DeskTableWindowDeviceAdd(&DeskMenuCtrl.ProgramsTable,&DeskMenuCtrl.WdCalculatorButton);  
    DeskTableWindowDeviceAdd(&DeskMenuCtrl.ProgramsTable,&DeskMenuCtrl.WdGameBombButton);  
    DeskTableWindowDeviceAdd(&DeskMenuCtrl.ProgramsTable,&DeskMenuCtrl.WdGameBeeButton); 
	DeskTableWindowDeviceAdd(&DeskMenuCtrl.ProgramsTable,&DeskMenuCtrl.WdGame2048Button);
    DeskMenuCtrl.ShellButton2.Type=WINDOW_BUTTON_PUSHBUTTON;
    DeskMenuCtrl.ShellButton2.Status=WINDOW_BUTTON_RELEASE;
    DeskMenuCtrl.ShellButton2.Active=TRUE;
    DeskMenuCtrl.ShellButton2.Dirty=TRUE;
    DeskMenuCtrl.ShellButton2.Outline=FALSE; //TRUE;
    DeskMenuCtrl.ShellButton2.pName=(UINT8*)DeskMenuStringShell;
    DeskMenuCtrl.ShellButton2.pBitmap=(UINT8 *)NULL;
    DeskMenuCtrl.ShellButton2.ReleaseGfx.BgColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.ShellButton2.ReleaseGfx.FgColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.ShellButton2.ReleaseGfx.FontColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.ShellButton2.PressGfx.BgColor=GFX_COLOR_GREEN0;
    DeskMenuCtrl.ShellButton2.PressGfx.FgColor=GFX_COLOR_GREEN0;
    DeskMenuCtrl.ShellButton2.PressGfx.FontColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.ShellButton2.InactiveGfx.BgColor=GFX_COLOR_WHITE;
    DeskMenuCtrl.ShellButton2.InactiveGfx.FgColor=GFX_COLOR_WHITE;
    DeskMenuCtrl.ShellButton2.InactiveGfx.FontColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.ShellButton2.Area.X=2;
    DeskMenuCtrl.ShellButton2.Area.Y=2;
    DeskMenuCtrl.ShellButton2.Area.W=Menu_W;
    DeskMenuCtrl.ShellButton2.Area.H=STRING_SIZE+2;
    DeskMenuCtrl.WdShellButton2.Type=WINDOW_DEVICE_BUTTON;
    DeskMenuCtrl.WdShellButton2.DeviceNumberLeft=DESK_MENU_WDN_SHELL2;
    DeskMenuCtrl.WdShellButton2.DeviceNumberMiddle=WINDOW_WDN_NULL;
    DeskMenuCtrl.WdShellButton2.DeviceNumberRight=WINDOW_WDN_NULL;
    DeskMenuCtrl.WdShellButton2.pDevice=(UINT32 *)(&DeskMenuCtrl.ShellButton2);
    
    DeskMenuCtrl.CalculatorButton.Type=WINDOW_BUTTON_PUSHBUTTON;
    DeskMenuCtrl.CalculatorButton.Status=WINDOW_BUTTON_RELEASE;
    DeskMenuCtrl.CalculatorButton.Active=TRUE;
    DeskMenuCtrl.CalculatorButton.Dirty=TRUE;
    DeskMenuCtrl.CalculatorButton.Outline=FALSE; //TRUE;
    DeskMenuCtrl.CalculatorButton.pName=(UINT8*)DeskMenuStringCalculator;
    DeskMenuCtrl.CalculatorButton.pBitmap=(UINT8 *)NULL;
    DeskMenuCtrl.CalculatorButton.ReleaseGfx.BgColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.CalculatorButton.ReleaseGfx.FgColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.CalculatorButton.ReleaseGfx.FontColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.CalculatorButton.PressGfx.BgColor=GFX_COLOR_GREEN0;
    DeskMenuCtrl.CalculatorButton.PressGfx.FgColor=GFX_COLOR_GREEN0;
    DeskMenuCtrl.CalculatorButton.PressGfx.FontColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.CalculatorButton.InactiveGfx.BgColor=GFX_COLOR_WHITE;
    DeskMenuCtrl.CalculatorButton.InactiveGfx.FgColor=GFX_COLOR_WHITE;
    DeskMenuCtrl.CalculatorButton.InactiveGfx.FontColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.CalculatorButton.Area.X=2;
    DeskMenuCtrl.CalculatorButton.Area.Y=2+(4+STRING_SIZE);
    DeskMenuCtrl.CalculatorButton.Area.W=Menu_W;
    DeskMenuCtrl.CalculatorButton.Area.H=STRING_SIZE+2;
    DeskMenuCtrl.WdCalculatorButton.Type=WINDOW_DEVICE_BUTTON;
    DeskMenuCtrl.WdCalculatorButton.DeviceNumberLeft=DESK_MENU_WDN_CALCULATOR;
    DeskMenuCtrl.WdCalculatorButton.DeviceNumberMiddle=WINDOW_WDN_NULL;
    DeskMenuCtrl.WdCalculatorButton.DeviceNumberRight=WINDOW_WDN_NULL;
    DeskMenuCtrl.WdCalculatorButton.pDevice=(UINT32 *)(&DeskMenuCtrl.CalculatorButton);
    
    DeskMenuCtrl.GameBombButton.Type=WINDOW_BUTTON_PUSHBUTTON;
    DeskMenuCtrl.GameBombButton.Status=WINDOW_BUTTON_RELEASE;
    DeskMenuCtrl.GameBombButton.Active=TRUE;
    DeskMenuCtrl.GameBombButton.Dirty=TRUE;
    DeskMenuCtrl.GameBombButton.Outline=FALSE; //TRUE;
    DeskMenuCtrl.GameBombButton.pName=(UINT8*)DeskMenuStringGameBomb;
    DeskMenuCtrl.GameBombButton.pBitmap=(UINT8 *)NULL;
    DeskMenuCtrl.GameBombButton.ReleaseGfx.BgColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.GameBombButton.ReleaseGfx.FgColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.GameBombButton.ReleaseGfx.FontColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.GameBombButton.PressGfx.BgColor=GFX_COLOR_GREEN0;
    DeskMenuCtrl.GameBombButton.PressGfx.FgColor=GFX_COLOR_GREEN0;
    DeskMenuCtrl.GameBombButton.PressGfx.FontColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.GameBombButton.InactiveGfx.BgColor=GFX_COLOR_WHITE;
    DeskMenuCtrl.GameBombButton.InactiveGfx.FgColor=GFX_COLOR_WHITE;
    DeskMenuCtrl.GameBombButton.InactiveGfx.FontColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.GameBombButton.Area.X=2;
    DeskMenuCtrl.GameBombButton.Area.Y=2+(4+STRING_SIZE)*2;
    DeskMenuCtrl.GameBombButton.Area.W=Menu_W;
    DeskMenuCtrl.GameBombButton.Area.H=STRING_SIZE+2;
    DeskMenuCtrl.WdGameBombButton.Type=WINDOW_DEVICE_BUTTON;
    DeskMenuCtrl.WdGameBombButton.DeviceNumberLeft=DESK_MENU_WDN_GAMEBOMB;
    DeskMenuCtrl.WdGameBombButton.DeviceNumberMiddle=WINDOW_WDN_NULL;
    DeskMenuCtrl.WdGameBombButton.DeviceNumberRight=WINDOW_WDN_NULL;
    DeskMenuCtrl.WdGameBombButton.pDevice=(UINT32 *)(&DeskMenuCtrl.GameBombButton);
    
    DeskMenuCtrl.GameBeeButton.Type=WINDOW_BUTTON_PUSHBUTTON;
    DeskMenuCtrl.GameBeeButton.Status=WINDOW_BUTTON_RELEASE;
    DeskMenuCtrl.GameBeeButton.Active=TRUE;
    DeskMenuCtrl.GameBeeButton.Dirty=TRUE;
    DeskMenuCtrl.GameBeeButton.Outline=FALSE; //TRUE;
    DeskMenuCtrl.GameBeeButton.pName=(UINT8*)DeskMenuStringGameBee;
    DeskMenuCtrl.GameBeeButton.pBitmap=(UINT8 *)NULL;
    DeskMenuCtrl.GameBeeButton.ReleaseGfx.BgColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.GameBeeButton.ReleaseGfx.FgColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.GameBeeButton.ReleaseGfx.FontColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.GameBeeButton.PressGfx.BgColor=GFX_COLOR_GREEN0;
    DeskMenuCtrl.GameBeeButton.PressGfx.FgColor=GFX_COLOR_GREEN0;
    DeskMenuCtrl.GameBeeButton.PressGfx.FontColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.GameBeeButton.InactiveGfx.BgColor=GFX_COLOR_WHITE;
    DeskMenuCtrl.GameBeeButton.InactiveGfx.FgColor=GFX_COLOR_WHITE;
    DeskMenuCtrl.GameBeeButton.InactiveGfx.FontColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.GameBeeButton.Area.X=2;
    DeskMenuCtrl.GameBeeButton.Area.Y=2+(4+STRING_SIZE)*3;
    DeskMenuCtrl.GameBeeButton.Area.W=Menu_W;
    DeskMenuCtrl.GameBeeButton.Area.H=STRING_SIZE+2;
    DeskMenuCtrl.WdGameBeeButton.Type=WINDOW_DEVICE_BUTTON;
    DeskMenuCtrl.WdGameBeeButton.DeviceNumberLeft=DESK_MENU_WDN_GAMEBEE;
    DeskMenuCtrl.WdGameBeeButton.DeviceNumberMiddle=WINDOW_WDN_NULL;
    DeskMenuCtrl.WdGameBeeButton.DeviceNumberRight=WINDOW_WDN_NULL;
    DeskMenuCtrl.WdGameBeeButton.pDevice=(UINT32 *)(&DeskMenuCtrl.GameBeeButton);
	
	DeskMenuCtrl.Game2048Button.Type=WINDOW_BUTTON_PUSHBUTTON;
    DeskMenuCtrl.Game2048Button.Status=WINDOW_BUTTON_RELEASE;
    DeskMenuCtrl.Game2048Button.Active=TRUE;
    DeskMenuCtrl.Game2048Button.Dirty=TRUE;
    DeskMenuCtrl.Game2048Button.Outline=FALSE; //TRUE;
    DeskMenuCtrl.Game2048Button.pName=(UINT8*)DeskMenuString2048;
    DeskMenuCtrl.Game2048Button.pBitmap=(UINT8 *)NULL;
    DeskMenuCtrl.Game2048Button.ReleaseGfx.BgColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.Game2048Button.ReleaseGfx.FgColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.Game2048Button.ReleaseGfx.FontColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.Game2048Button.PressGfx.BgColor=GFX_COLOR_GREEN0;
    DeskMenuCtrl.Game2048Button.PressGfx.FgColor=GFX_COLOR_GREEN0;
    DeskMenuCtrl.Game2048Button.PressGfx.FontColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.Game2048Button.InactiveGfx.BgColor=GFX_COLOR_WHITE;
    DeskMenuCtrl.Game2048Button.InactiveGfx.FgColor=GFX_COLOR_WHITE;
    DeskMenuCtrl.Game2048Button.InactiveGfx.FontColor=GFX_COLOR_BLACK;
    DeskMenuCtrl.Game2048Button.Area.X=2;
    DeskMenuCtrl.Game2048Button.Area.Y=2+(4+STRING_SIZE)*4;
    DeskMenuCtrl.Game2048Button.Area.W=Menu_W;
    DeskMenuCtrl.Game2048Button.Area.H=STRING_SIZE+2;
    DeskMenuCtrl.WdGame2048Button.Type=WINDOW_DEVICE_BUTTON;
    DeskMenuCtrl.WdGame2048Button.DeviceNumberLeft=DESK_MENU_WDN_2048;
    DeskMenuCtrl.WdGame2048Button.DeviceNumberMiddle=WINDOW_WDN_NULL;
    DeskMenuCtrl.WdGame2048Button.DeviceNumberRight=WINDOW_WDN_NULL;
    DeskMenuCtrl.WdGame2048Button.pDevice=(UINT32 *)(&DeskMenuCtrl.Game2048Button);
    
}


VOID DeskMenuEventHandler(UINT32 WindowEvent)
{
	UINT8 TEMP = (UINT8)WindowEvent;
    //CaptionStringPrint(&DeskDebugCtrl.Caption,"\nEvent: ");
    //CaptionUINT8Print(&DeskDebugCtrl.Caption,(UINT8)WindowEvent);
    switch(TEMP){
        case DESK_MENU_WDN_CONTROLPANEL:
            DeskMenuCtrl.StartWindow.Next=&DeskMenuCtrl.ControlPanelWindow;
            DeskMenuCtrl.ControlPanelWindow.Prev=&DeskMenuCtrl.StartWindow;
            DeskMenuCtrl.ControlPanelWindow.Next=(WINDOW *)NULL;
            DeskMenuCtrl.StartWindow.Active=FALSE;
            DeskMenuCtrl.StartWindow.Dirty=TRUE;
            DeskMenuCtrl.ControlPanelWindow.Active=TRUE;
            DeskMenuCtrl.ControlPanelWindow.Dirty=TRUE;
            DeskWindowCtrl.pActiveWindow=&DeskMenuCtrl.ControlPanelWindow;
            DeskWindowCtrl.WindowListChange=TRUE;
            break;
        case DESK_MENU_WDN_PROGRAMS:
            DeskMenuCtrl.StartWindow.Next=&DeskMenuCtrl.ProgramsWindow;
            DeskMenuCtrl.ProgramsWindow.Prev=&DeskMenuCtrl.StartWindow;
            DeskMenuCtrl.ProgramsWindow.Next=(WINDOW *)NULL;
            DeskMenuCtrl.StartWindow.Active=FALSE;
            DeskMenuCtrl.StartWindow.Dirty=TRUE;
            DeskMenuCtrl.ProgramsWindow.Active=TRUE;
            DeskMenuCtrl.ProgramsWindow.Dirty=TRUE;
            DeskWindowCtrl.pActiveWindow=&DeskMenuCtrl.ProgramsWindow;
            DeskWindowCtrl.WindowListChange=TRUE;
            break;
        case DESK_MENU_WDN_SHELL:
            DeskWindowCtrl.MenuWindowList=(WINDOW *)NULL;
            DeskWindowCtrl.pActiveWindow=DeskWindowCtrl.WindowListHead;
            DeskWindowCtrl.pActiveWindow->Active=TRUE;
            DeskWindowCtrl.pActiveWindow->Dirty=TRUE;
            DeskWindowCtrl.WindowListChange=TRUE;
            OsTaskCreat(ShellTask,SHELL_TASK_STACK_SIZE,&ShellTaskName,0, NULL);	
            break;
        case DESK_MENU_WDN_DEBUGER:
            DeskWindowCtrl.MenuWindowList=(WINDOW *)NULL;
            DeskWindowCtrl.pActiveWindow=DeskWindowCtrl.WindowListHead;
            DeskWindowCtrl.pActiveWindow->Active=TRUE;
            DeskWindowCtrl.pActiveWindow->Dirty=TRUE;
            DeskWindowCtrl.WindowListChange=TRUE;
            if(DeskDebugCtrl.Window.State==DESK_WINDOW_STATE_OFFDESK)
                DeskWindowWindowPut((WINDOW *)&DeskDebugCtrl.Window);
            break;
        case DESK_MENU_WDN_SYSTEM:
            DeskWindowCtrl.MenuWindowList=(WINDOW *)NULL;
            DeskWindowCtrl.pActiveWindow=DeskWindowCtrl.WindowListHead;
            DeskWindowCtrl.pActiveWindow->Active=TRUE;
            DeskWindowCtrl.pActiveWindow->Dirty=TRUE;
            DeskWindowCtrl.WindowListChange=TRUE;
            if(DeskControlPanel.SystemWindow.State==DESK_WINDOW_STATE_OFFDESK)
                 DeskWindowWindowPut((WINDOW *)&DeskControlPanel.SystemWindow);
            break;
        case DESK_MENU_WDN_MOUSE:
            DeskWindowCtrl.MenuWindowList=(WINDOW *)NULL;
            DeskWindowCtrl.pActiveWindow=DeskWindowCtrl.WindowListHead;
            DeskWindowCtrl.pActiveWindow->Active=TRUE;
            DeskWindowCtrl.pActiveWindow->Dirty=TRUE;
            DeskWindowCtrl.WindowListChange=TRUE;
            if(DeskControlPanel.MouseWindow.State==DESK_WINDOW_STATE_OFFDESK)
                DeskWindowWindowPut((WINDOW *)&DeskControlPanel.MouseWindow);
            break;
        case DESK_MENU_WDN_KEYBOARD:
            DeskWindowCtrl.MenuWindowList=(WINDOW *)NULL;
            DeskWindowCtrl.pActiveWindow=DeskWindowCtrl.WindowListHead;
            DeskWindowCtrl.pActiveWindow->Active=TRUE;
            DeskWindowCtrl.pActiveWindow->Dirty=TRUE;
            DeskWindowCtrl.WindowListChange=TRUE;
            if(DeskControlPanel.KeyboardWindow.State==DESK_WINDOW_STATE_OFFDESK)
                DeskWindowWindowPut((WINDOW *)&DeskControlPanel.KeyboardWindow);
            break;
        case DESK_MENU_WDN_MONITOR:
            DeskWindowCtrl.MenuWindowList=(WINDOW *)NULL;
            DeskWindowCtrl.pActiveWindow=DeskWindowCtrl.WindowListHead;
            DeskWindowCtrl.pActiveWindow->Active=TRUE;
            DeskWindowCtrl.pActiveWindow->Dirty=TRUE;
            DeskWindowCtrl.WindowListChange=TRUE;
            if(DeskControlPanel.MonitorWindow.State==DESK_WINDOW_STATE_OFFDESK)
                DeskWindowWindowPut((WINDOW *)&DeskControlPanel.MonitorWindow);
            break;
        case DESK_MENU_WDN_DRIVERS:
            DeskWindowCtrl.MenuWindowList=(WINDOW *)NULL;
            DeskWindowCtrl.pActiveWindow=DeskWindowCtrl.WindowListHead;
            DeskWindowCtrl.pActiveWindow->Active=TRUE;
            DeskWindowCtrl.pActiveWindow->Dirty=TRUE;
            DeskWindowCtrl.WindowListChange=TRUE;
            if(DeskControlPanel.DriversWindow.State==DESK_WINDOW_STATE_OFFDESK)
                DeskWindowWindowPut((WINDOW *)&DeskControlPanel.DriversWindow);
            break;
        case DESK_MENU_WDN_PALETTE:
            DeskWindowCtrl.MenuWindowList=(WINDOW *)NULL;
            DeskWindowCtrl.pActiveWindow=DeskWindowCtrl.WindowListHead;
            DeskWindowCtrl.pActiveWindow->Active=TRUE;
            DeskWindowCtrl.pActiveWindow->Dirty=TRUE;
            DeskWindowCtrl.WindowListChange=TRUE;
            if(DeskControlPanel.PaletteWindow.State==DESK_WINDOW_STATE_OFFDESK)
                 DeskWindowWindowPut((WINDOW *)&DeskControlPanel.PaletteWindow);
            break;
        case DESK_MENU_WDN_SHELL2:
            DeskWindowCtrl.MenuWindowList=(WINDOW *)NULL;
            DeskWindowCtrl.pActiveWindow=DeskWindowCtrl.WindowListHead;
            DeskWindowCtrl.pActiveWindow->Active=TRUE;
            DeskWindowCtrl.pActiveWindow->Dirty=TRUE;
            DeskWindowCtrl.WindowListChange=TRUE;
			OsTaskCreat(ShellTask, SHELL_TASK_STACK_SIZE, &ShellTaskName, 0, NULL);
            break;
        case DESK_MENU_WDN_CALCULATOR:
            DeskWindowCtrl.MenuWindowList=(WINDOW *)NULL;
            DeskWindowCtrl.pActiveWindow=DeskWindowCtrl.WindowListHead;
            DeskWindowCtrl.pActiveWindow->Active=TRUE;
            DeskWindowCtrl.pActiveWindow->Dirty=TRUE;
            DeskWindowCtrl.WindowListChange=TRUE;
            OsTaskCreat(CalculatorTask,CALCULATOR_TASK_STACK_SIZE,&CalculatorTaskName,0, NULL);
            break;
        case DESK_MENU_WDN_GAMEBOMB:
            DeskWindowCtrl.MenuWindowList=(WINDOW *)NULL;
            DeskWindowCtrl.pActiveWindow=DeskWindowCtrl.WindowListHead;
            DeskWindowCtrl.pActiveWindow->Active=TRUE;
            DeskWindowCtrl.pActiveWindow->Dirty=TRUE;
            DeskWindowCtrl.WindowListChange=TRUE;
            OsTaskCreat(BombTask,BOMB_TASK_STACK_SIZE,&BombTaskName,0, NULL);
            break;
        case DESK_MENU_WDN_GAMEBEE:
            DeskWindowCtrl.MenuWindowList=(WINDOW *)NULL;
            DeskWindowCtrl.pActiveWindow=DeskWindowCtrl.WindowListHead;
            DeskWindowCtrl.pActiveWindow->Active=TRUE;
            DeskWindowCtrl.pActiveWindow->Dirty=TRUE;
            DeskWindowCtrl.WindowListChange=TRUE;
            OsTaskCreat(BeeTask,BEE_TASK_STACK_SIZE,&BeeTaskName,0, NULL);	
            break;
/*GDB		case DESK_MENU_WDN_2048:
            DeskWindowCtrl.MenuWindowList=(WINDOW *)NULL;
            DeskWindowCtrl.pActiveWindow=DeskWindowCtrl.WindowListHead;
            DeskWindowCtrl.pActiveWindow->Active=TRUE;
            DeskWindowCtrl.pActiveWindow->Dirty=TRUE;
            DeskWindowCtrl.WindowListChange=TRUE;
            OsTaskCreat(Task2048,BEE_TASK_STACK_SIZE,&Task2048Name,0, NULL);	
            break; GDB*/
        default:
            break;
    }
}