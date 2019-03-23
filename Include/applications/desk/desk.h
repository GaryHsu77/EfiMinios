#ifndef DESK_H
#define DESK_H

#define DESK_WINDOW_STATE_OFFDESK 0
#define DESK_WINDOW_STATE_ONDESK  1

#define DESK_WINDOW_STATUS_HIDE 0
#define DESK_WINDOW_STATUS_NORMAL 1
//#define DESK_WINDOW_STATUS_MAXIMUN 1
//#define DESK_WINDOW_STATUS_SIZABLE 2

#define DESK_WINDOW_ALIGN_TOPLEFT 0
#define DESK_WINDOW_ALIGN_BOTTOMLEFT 1
//#define DESK_WINDOW_ALIGN_TOPRIGHT 2
//#define DESK_WINDOW_ALIGN_BOTTOMRIGHT 3

#define DESK_WINDOW_HEIGHT_MINIMUN (WINDOW_HEADER_HEIGHT+WINDOW_EDGE_THINK*2)
#define DESK_WINDOW_WIDTH_MINIMUN (8*3+8*3+WINDOW_EDGE_THINK*2) // 8*3 for title string,8*3 for 3 icon, 2 edges for right edge,left edge
#define DESK_WINDOW_WIDTH_MAXIMUN  DeskWorkCtrl.WorkArea.W
#define DESK_WINDOW_HEIGHT_MAXIMUN DeskWorkCtrl.WorkArea.H

#define DESK_ACTIVE_WORKAREA 1 // active area
#define DESK_ACTIVE_WORKBAR  2
#define DESK_ACTIVE_WINDOW   3

#define DESK_BUTTON_PRESS 0
#define DESK_BUTTON_RELEASE 1

#define DESK_MOUSE_MAP_WIDTH 30
#define DESK_MOUSE_MAP_HEIGHT 30

#define DESK_KEYBUFFER_SIZE 100
#define DESK_MOUSEBUFFER_SIZE 400 

//desk
typedef struct{
    UINT8 State;
    OS_TIMER DeskTimer;
    OS_TIMER DeskEventTimer;
    GRAPHIC_AREA DeskArea;
}DESK_CONTROL;

extern DESK_CONTROL DeskCtrl;

extern const UINT8 DeskWorkWindowName[];
extern const UINT8 DeskWorkbarName[];

extern const UINT8 DeskHideButton[];
extern const UINT8 DeskMaximunButton[];
extern const UINT8 DeskCloseButton[];
	
void DeskInit(void);
void DeskSvc(void);

// ******
// desk time
// ******

typedef struct{
    BOARD Board;
    WINDOW_DEVICE DeskDeviceBoard;
    WINDOW_TABLE UserTable;
    WINDOW Window;
}DESK_TIME_CONTROL;

extern DESK_TIME_CONTROL DeskTimeCtrl;

void DeskTimeInit(void);

// ******
// desk debug
// ******

#define DESK_DEBUG_WDN_CAPTION WINDOW_WDN_USERDEVICE

typedef struct{
    CONSOLE Console;
    CAPTION Caption;
    WINDOW_DEVICE DeskDeviceCaption;
    WINDOW_TABLE UserTable;
    WINDOW Window;
}DESK_DEBUG_CONTROL;

extern DESK_DEBUG_CONTROL DeskDebugCtrl;

void DeskDebugInit(void);
// ******
//desk window 
// ******
typedef struct{
    UINT8 ReclickStartButton;
    UINT8 WindowListChange; // a flag to indicate window change
    WINDOW *pActiveWindow;
    WINDOW *MenuWindowList;
    WINDOW *WindowListHead;
    WINDOW *WindowListTail;
}DESK_WINDOW_CONTROL;

extern DESK_WINDOW_CONTROL DeskWindowCtrl;

void DeskWindowInit(void);
void DeskWindowWindowListHeadSet(WINDOW *pWindow);
void DeskWindowWindowListTailSet(WINDOW *pWindow);
void DeskWindowWindowPut(WINDOW *pWindow);
void DeskWindowWindowDelete(WINDOW *pWindow);
void DeskWindowActiveWindowSet(WINDOW *pWindow);
WINDOW *DeskWindowActiveWindowGet(void);
BOOLEAN DeskWindowActiveWindowContentCheck(void);
BOOLEAN DeskWindowInactiveWindowContentCheck(void);
BOOLEAN DeskWindowWindowListCheck(void);
void DeskWindowInactiveWindowDraw(void);
void DeskWindowActiveWindowToggle(WINDOW *pWindow);
BOOLEAN DeskWindowWindowCheck(WINDOW *pWindow);
void DeskWindowWindowHideSet(WINDOW *pWindow);
void DeskWindowActiveWindowDelete(WINDOW *pWindow);
WINDOW *DeskWindowMousePositionWindowGet(GRAPHIC_POSITION *pPosition);
void DeskWindowMousePositionInfomationGet(GRAPHIC_POSITION *pPosition);

//desk active window
typedef struct{
    UINT8 ActiveWindowDirty;
    UINT8 DirectContentDraw;
    //GDB UINT8 *pActiveWindowMemory;
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pActiveWindowMemory;
}DESK_ACTIVEWINDOW_CONTROL;

extern DESK_ACTIVEWINDOW_CONTROL DeskActiveWindowCtrl;

void DeskActiveWindowInit(void);
void DeskActiveWindowMovingMouseMapCapture(WINDOW *pWindow);
void DeskActiveWindowMovingMouseMapRecovery(WINDOW *pWindow);
void DeskActiveWindowMovingMouseCursorDraw(WINDOW *pWindow);
void DeskActiveWindowMemory2OsdUpdate(WINDOW *pWindow);
void DeskActiveWindowContent2OsdUpdate(WINDOW *pWindow);
void DeskActiveWindowMemoryDraw(WINDOW *pWindow); 
void DeskActiveWindowMemoryTitleCharDraw(WINDOW *pWindow,UINT8 *pBitmap,GRAPHIC_POSITION *pPosition);
void DeskActiveWindowMoveInit(WINDOW *pWindow);
void DeskActiveWindowMoveStop(WINDOW *pWindow);
void DeskActiveWindowMoveSvc(WINDOW *pWindow);
void DeskActiveWindowMoveSvc3(WINDOW *pWindow);
void DeskActiveWindowMoveSvc2(WINDOW *pWindow);
void DeskActiveWindowAdjust(UINT8 CursorType,WINDOW *pWindow);

//desk work window
typedef struct{ 
    UINT8 WorkWindowDirty;
    UINT32 WorkMemoryLength;
    UINT8 *pWorkMemory;
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pixel_array;
    GRAPHIC_GFX WorkGfx; 
    GRAPHIC_AREA WorkArea;
    WINDOW Window;
}DESK_WORKWINDOW_CONTROL;

extern DESK_WORKWINDOW_CONTROL DeskWorkCtrl;

void DeskWorkWindowInit(void);
void DeskWorkWindowMemoryDraw(void);
void DeskWorkWindow2OsdUpdate(void);
void DeskWorkWindow2OsdCopy(GRAPHIC_AREA *pArea);

//desk work bar window
#define DESK_WORKBAR_HEIGHT 28
#define DESK_WORKBAR_UPPEREDGE 1
#define DESK_WORKBAR_BOTTOMEDGE 1
#define DESK_WORKBAR_RIGHTEDGE 1
#define DESK_WORKBAR_LEFTEDGE  1
    
#define DESK_WORKBAR_WINDOWAREA_X OsdCtrl.ScreenArea.X
#define DESK_WORKBAR_WINDOWAREA_Y (OsdCtrl.ScreenArea.Y+OsdCtrl.ScreenArea.H-DESK_WORKBAR_HEIGHT)
#define DESK_WORKBAR_WINDOWAREA_W OsdCtrl.ScreenArea.W
#define DESK_WORKBAR_WINDOWAREA_H DESK_WORKBAR_HEIGHT

    
#define DESK_WORKBAR_STARTAREA_X DESK_WORKBAR_LEFTEDGE
#define DESK_WORKBAR_STARTAREA_Y DESK_WORKBAR_UPPEREDGE
#define DESK_WORKBAR_STARTAREA_W (5*8+2)
#define DESK_WORKBAR_STARTAREA_H (ESK_WORKBAR_HEIGHT-DESK_WORKBAR_UPPEREDGE-DESK_WORKBAR_BOTTOMEDGE)

#define DESK_WORKBAR_TIMEAREA_X (DESK_WORKBAR_WINDOWAREA_W-DESK_WORKBAR_LEFTEDGE-(8*8+2))
#define DESK_WORKBAR_TIMEAREA_Y DESK_WORKBAR_UPPEREDGE
#define DESK_WORKBAR_TIMEAREA_W (8*8+2)
#define DESK_WORKBAR_TIMEAREA_H (DESK_WORKBAR_HEIGHT-DESK_WORKBAR_UPPEREDGE-DESK_WORKBAR_BOTTOMEDGE)

#define DESK_WORKBAR_WINDOWLISTAREA_X (DESK_WORKBAR_LEFTEDGE+DESK_WORKBAR_STARTAREA_W+1)
#define DESK_WORKBAR_WINDOWLISTAREA_Y DESK_WORKBAR_UPPEREDGE
#define DESK_WORKBAR_WINDOWLISTAREA_W (DESK_WORKBAR_TIMEAREA_X-(DESK_WORKBAR_STARTAREA_X+DESK_WORKBAR_STARTAREA_W)-1)
#define DESK_WORKBAR_WINDOWLISTAREA_H (DESK_WORKBAR_HEIGHT-DESK_WORKBAR_UPPEREDGE-DESK_WORKBAR_BOTTOMEDGE)

#define WINDOW_BOX_HEIGHT (DESK_WORKBAR_HEIGHT-DESK_WORKBAR_UPPEREDGE-DESK_WORKBAR_BOTTOMEDGE)
#define WINDOW_BOX_WIDTH (12*2+2)  //2 char+2edges

#define DESK_WORKBAR_WD_STARTBUTTON 100
#define DESK_WORKBAR_WD_TIMEBOX     101

typedef struct{
    UINT8 WindowListChange;
    UINT8 TimeWindowTimeDirty;
    UINT8 TimePreviousMinute;
    UINT32 WindowMemoryLength;
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pWindowMemory;
    OS_TIME PreviousTime;
    OS_TIME CurrentTime;
    OS_TIMER TimeMonitor;
    
    WINDOW_TABLE StartTable;
    WINDOW_TABLE WindowListTable;
    WINDOW_TABLE TimeTable;
    
    WINDOW_BUTTON StartButton;
    WINDOW_DEVICE WdStartButton;
    WINDOW_STRINGBOX TimeBox;
    WINDOW_DEVICE WdTimeBox;
    
    GRAPHIC_GFX WorkBarGfx; 
    WINDOW *WindowListHead;
    WINDOW Window;
}DESK_WORKBAR_CONTROL;

extern DESK_WORKBAR_CONTROL DeskWorkbarCtrl;

void DeskWorkbarInit(void);
void DeskWorkbarMemoryReset(void);
void DeskWorkbarTimeUpdate(void);
void DeskWorkbarTimeDraw(void);
void DeskWorkbarTimeWindowDraw(void);
void DeskWorkbarWindowListDraw(void);
void DeskWorkbarDraw(void);
//void DeskWorkbarMemoryStringDraw(GRAPHIC_POSITION *pPosition,UINT8 *pString);
//void DeskWorkbarMemoryCharDraw(WINDOW *pWindow,UINT8 *pBitmap,GRAPHIC_POSITION *pPosition);
void DeskWorkbarWindowListPut(WINDOW *pWindow);
void DeskWorkbarWindowListDelete(WINDOW *pWindow);
void DeskWorkbarWindowListDelete2(WINDOW *pWindow);
void DeskWorkbarWindowListCalculate(void);
BOOLEAN DeskWorkbarDirtyCheck(void);

//desk inactive window memory
typedef struct{
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pInactiveWindowMemory;
}DESK_INACTIVEWINDOW_CONTROL;

extern DESK_INACTIVEWINDOW_CONTROL DeskInactiveWindowCtrl;

void DeskInactiveWindowInit(void);
void DeskInactiveWindowMemory2WorkWindowUpdate(WINDOW *pWindow);
void DeskInactiveWindowMemoryDraw(WINDOW *pWindow);
void DeskInactiveWindowMemoryTitleCharDraw(WINDOW *pWindow,UINT8 *pBitmap,GRAPHIC_POSITION *pPosition);

/********
// desk mouse
*********/

extern const UINT8 DeskMouseCursor[];
extern EFI_GRAPHICS_OUTPUT_BLT_PIXEL* DeskMouseCursorPixel;
extern const UINT8 DeskMouseCursorYdir[];
extern const UINT8 DeskMouseCursorXdir[];
extern const UINT8 DeskMouseCursorLurddir[];
extern const UINT8 DeskMouseCursorLdrudir[];

#define DESK_MOUSE_CURSOR_NORMAL    0
#define DESK_MOUSE_CURSOR_UP        1
#define DESK_MOUSE_CURSOR_DOWN      2
#define DESK_MOUSE_CURSOR_LEFT      3
#define DESK_MOUSE_CURSOR_RIGHT     4
#define DESK_MOUSE_CURSOR_LEFTUP    5
#define DESK_MOUSE_CURSOR_LEFTDOWN  6
#define DESK_MOUSE_CURSOR_RIGHTUP   7
#define DESK_MOUSE_CURSOR_RIGHTDOWN 8 

typedef struct{
    OS_TIMER MouseTimer;
    UINT8 MouseCursorType;
    WINDOW *pWindow;        //mouse allocate window
    WINDOW *pCurrentWindow; // mouse detect window as moving
    WINDOW_TABLE *pTable;   //mouse allocate table
    WINDOW_TABLE *pCurrentTable; // mouse detect window as moving
    WINDOW_DEVICE *pDevice; //mouse allocate device
    WINDOW_DEVICE *pCurrentDevice; // mouse detect window as moving
    WINDOW *pWindowPrevious; // mouse detect window as moving
    GRAPHIC_POSITION MousePointer;
    GRAPHIC_POSITION MousePrevious;
    GRAPHIC_POSITION OriginalWindowEdge;
    GRAPHIC_POSITION NewWindowEdge;
    GRAPHIC_POSITION MouseRelativePosition;
    GRAPHIC_AREA MouseArea;
    GRAPHIC_GFX MouseGfx;
    UINT32 MouseMemoryLength;
    // mouse icon
    UINT8 *pMouseMemory2;
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pixel_array2; //GDB
    UINT8 *pMouseMemory;
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pixel_array; //GDB
    UINT8 MouseDirty;
    UINT8 MouseAtLeftBoundary;
    UINT8 MouseAtRightBoundary;
    UINT8 MouseAtUpBoundary;
    UINT8 MouseAtDownBoundary;
    // mouse info 
    UINT8 MouseLeftButton;
    UINT8 MouseRightButton;
    UINT8 MouseMiddleButton;
    UINT8 HasMouse;
    UINT8 MousePut;
    UINT8 MouseGet;
    UINT32 *pMouseBuffer;
    
}DESK_MOUSE_CONTROL;

extern DESK_MOUSE_CONTROL 	DeskMouseCtrl;

void DeskMouseInit(void);
void DeskMouse2OsdUpdate(void);
void DeskMouse2OsdDraw(void);
void DeskMouse2OsdClear(void);
void DeskMouseMapCapture(void);
void DeskMouseCursorDraw(void);
void DeskMouseSvc(void);
void DeskMouseLeftButtonReleaseWait(void);
void DeskMouseLeftButtonReleaseWait2(void);
void DeskMouseRightButtonReleaseWait(void);
void DeskMouseMiddleButtonReleaseWait(void);
BOOLEAN DeskMouseOverlapCheck(WINDOW *pWindow);

//desk menu
#define DESK_MENU_STARTMENU_WIDTH  170
#define DESK_MENU_STARTMENU_HEIGHT 67

#define DESK_MENU_CONTROLPANEL_WIDTH  170
#define DESK_MENU_CONTROLPANEL_HEIGHT 97

#define DESK_MENU_PROGRAMS_WIDTH  170
#define DESK_MENU_PROGRAMS_HEIGHT 67

#define DESK_MENU_WDN_CONTROLPANEL      (WINDOW_WDN_USERDEVICE)
#define DESK_MENU_WDN_PROGRAMS          (WINDOW_WDN_USERDEVICE+1)
#define DESK_MENU_WDN_SHELL             (WINDOW_WDN_USERDEVICE+2)
#define DESK_MENU_WDN_DEBUGER           (WINDOW_WDN_USERDEVICE+3)

#define DESK_MENU_WDN_SYSTEM            (WINDOW_WDN_USERDEVICE+4)
#define DESK_MENU_WDN_MOUSE             (WINDOW_WDN_USERDEVICE+5)
#define DESK_MENU_WDN_KEYBOARD          (WINDOW_WDN_USERDEVICE+6)
#define DESK_MENU_WDN_MONITOR           (WINDOW_WDN_USERDEVICE+7)
#define DESK_MENU_WDN_DRIVERS           (WINDOW_WDN_USERDEVICE+8)
#define DESK_MENU_WDN_PALETTE           (WINDOW_WDN_USERDEVICE+9)

#define DESK_MENU_WDN_SHELL2            (WINDOW_WDN_USERDEVICE+10)
#define DESK_MENU_WDN_CALCULATOR        (WINDOW_WDN_USERDEVICE+11)
#define DESK_MENU_WDN_GAMEBOMB          (WINDOW_WDN_USERDEVICE+12)
#define DESK_MENU_WDN_GAMEBEE           (WINDOW_WDN_USERDEVICE+13)
#define DESK_MENU_WDN_2048           	(WINDOW_WDN_USERDEVICE+14)

typedef struct{
    WINDOW_BUTTON ControlPanelButton;
    WINDOW_BUTTON ProgramsButton;
    WINDOW_BUTTON ShellButton;
    WINDOW_BUTTON DebugerButton;
    WINDOW_DEVICE WdControlPanelButton;
    WINDOW_DEVICE WdProgramsButton;
    WINDOW_DEVICE WdShellButton;
    WINDOW_DEVICE WdDebugerButton;
    WINDOW_TABLE StartTable;
    WINDOW StartWindow; 
    
    WINDOW_BUTTON SystemButton;
    WINDOW_BUTTON MouseButton;
    WINDOW_BUTTON KeyboardButton;
    WINDOW_BUTTON MonitorButton;
    WINDOW_BUTTON DriversButton;
    WINDOW_BUTTON PaletteButton;
    WINDOW_DEVICE WdSystemButton;
    WINDOW_DEVICE WdMouseButton;
    WINDOW_DEVICE WdKeyboardButton;
    WINDOW_DEVICE WdMonitorButton;
    WINDOW_DEVICE WdDriversButton;
    WINDOW_DEVICE WdPaletteButton;
    WINDOW_TABLE ControlPanelTable;
    WINDOW ControlPanelWindow; 
    
    WINDOW_BUTTON ShellButton2;
    WINDOW_BUTTON CalculatorButton;
    WINDOW_BUTTON GameBombButton;
    WINDOW_BUTTON GameBeeButton;
	WINDOW_BUTTON Game2048Button;
    WINDOW_DEVICE WdShellButton2;
    WINDOW_DEVICE WdCalculatorButton;
    WINDOW_DEVICE WdGameBombButton;
    WINDOW_DEVICE WdGameBeeButton;
	WINDOW_DEVICE WdGame2048Button;
    WINDOW_TABLE ProgramsTable;
    WINDOW ProgramsWindow; 
}DESK_MENU_CONTROL;

extern DESK_MENU_CONTROL DeskMenuCtrl;

void DeskMenuInit(void);
void DeskMenuEventHandler(UINT32 EventNumber);

//control panel

typedef struct{
    BOARD SystemBoard;
    BOARD MouseBoard;
    BOARD KeyboardBoard;
    BOARD MonitorBoard;
    BOARD DriversBoard;
    BOARD PaletteBoard;

    WINDOW_DEVICE DeskDeviceSystem;
    WINDOW_DEVICE DeskDeviceMouse;
    WINDOW_DEVICE DeskDeviceKeyboard;
    WINDOW_DEVICE DeskDeviceMonitor;
    WINDOW_DEVICE DeskDeviceDrivers;
    WINDOW_DEVICE DeskDevicePalette;

    WINDOW_TABLE SystemUserTable;
    WINDOW_TABLE MouseUserTable;
    WINDOW_TABLE KeyboardUserTable;
    WINDOW_TABLE MonitorUserTable;
    WINDOW_TABLE DriversUserTable;
    WINDOW_TABLE PaletteUserTable;

    WINDOW SystemWindow; 
    WINDOW MouseWindow;
    WINDOW KeyboardWindow;
    WINDOW MonitorWindow;
    WINDOW DriversWindow;
    WINDOW PaletteWindow;
}DESK_CONTROLPANEL_CONTROL;

extern const UINT8 ControlPanelSystem[];
extern const UINT8 ControlPanelMouse[];
extern const UINT8 ControlPanelKeyboard[];
extern const UINT8 ControlPanelMonitor[];
extern const UINT8 ControlPanelDrivers[];
extern const UINT8 ControlPanelPalette[];

extern DESK_CONTROLPANEL_CONTROL DeskControlPanel;

void DeskControlPanelInit(void);
void DeskControlPanelSystemWindowDraw(void);
void DeskControlPanelMouseWindowDraw(void);
void DeskControlPanelKeyboardWindowDraw(void);
void DeskControlPanelMonitorWindowDraw(void);
void DeskControlPanelDriversWindowDraw(void);
void DeskControlPanelPaletteWindowDraw(void);

//desk table
void DeskTableUserTableAdd(WINDOW *pWindow,WINDOW_TABLE *pTable);
void DeskTableWindowDeviceAdd(WINDOW_TABLE *pTable,WINDOW_DEVICE *pDevice);
void DeskTableBackgroundDraw(UINT8 DrawPlace,WINDOW *pWindow,WINDOW_TABLE *pTable);

//desk device
#define DESK_DEVICE_DRAW_ACTIVEWINDOW   0
#define DESK_DEVICE_DRAW_INACTIVEWINDOW 1
#define DESK_DEVICE_DRAW_OSD            2

BOOLEAN DeskDeviceAreaPositionCheck(WINDOW_DEVICE *pDevice,GRAPHIC_POSITION *pPosition);
BOOLEAN DeskDeviceDirtyCheck(WINDOW_DEVICE *pDevice);
void DeskDeviceCaptionDraw(UINT8 DrawPlace,WINDOW *pWindow,WINDOW_TABLE *pTable,CAPTION *pCaption);
void DeskDeviceBoardDraw(UINT8 DrawPlace,WINDOW *pWindow,WINDOW_TABLE *pTable,BOARD *pBoard);
void DeskDeviceButtonDraw(UINT8 DrawPlace,WINDOW *pWindow,WINDOW_TABLE *pTable,WINDOW_BUTTON *pButton);
void DeskDeviceStringboxDraw(UINT8 DrawPlace,WINDOW *pWindow,WINDOW_TABLE *pTable,WINDOW_STRINGBOX *pStringbox);
void DeskDeviceIconDraw(UINT8 DrawPlace,WINDOW *pWindow,WINDOW_TABLE *pTable,WINDOW_ICON *pIcon);
void DeskDeviceWindowboxDraw(UINT8 DrawPlace,WINDOW *pWindow,WINDOW_TABLE *pTable,WINDOW_WINDOWBOX *pWindowbox);
void DeskDeviceActiveWindowMemoryCharDraw(WINDOW *pWindow,UINT8 *pBitmap,GRAPHIC_POSITION *pPosition,GRAPHIC_GFX *pGfx);
void DeskDeviceInactiveWindowMemoryCharDraw(WINDOW *pWindow,UINT8 *pBitmap,GRAPHIC_POSITION *pPosition,GRAPHIC_GFX *pGfx);
void DeskDeviceOsdCharDraw(UINT8 *pBitmap,GRAPHIC_POSITION *pPosition,GRAPHIC_GFX *pGfx);

//deskbg
extern const UINT8 DeskBackground[];
extern BOOLEAN TIMER_START;

//desklib
BOOLEAN DesklibAreaPositionCheck(GRAPHIC_AREA *pArea,GRAPHIC_POSITION *pPosition);

#endif
