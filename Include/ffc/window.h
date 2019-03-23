#ifndef WINDOW_H
#define WINDOW_H

#define WINDOW_WINDOWBOX_GENERAL 0

typedef struct{
    UINT32 Type;    
    UINT32 *pWindow; 
    GRAPHIC_GFX ActiveGfx; 
    GRAPHIC_GFX InactiveGfx;      
    GRAPHIC_AREA Area;
}WINDOW_WINDOWBOX;

#define WINDOW_STRINGBOX_GENERAL 0

typedef struct{
    UINT32 Type;   
    UINT8 Dirty;      
    UINT8 Alignment;
    GRAPHIC_GFX Gfx;    
    GRAPHIC_AREA Area; //area used by this device
    UINT8 *pName;         //name to show on string box
}WINDOW_STRINGBOX;

#define WINDOW_ICON_GENERAL 3

typedef struct{
    UINT32 Type;    
    UINT8 Dirty;    
    GRAPHIC_GFX ActiveGfx;
    GRAPHIC_GFX InactiveGfx; 
    //GRAPHIC_GFX SelectedGfx;
    GRAPHIC_AREA Area; //area used by this device
    UINT8 *pBitmap;
}WINDOW_ICON;

//window outline
#define WINDOW_OUTLINE_GENERAL 0

typedef struct{
    UINT32 Type;
    GRAPHIC_AREA OuterArea; //area used by this device     
    GRAPHIC_AREA InnerArea; //area used by this device
}WINDOW_OUTLINE;

//window edge
#define WINDOW_EDGE_THINK 2
#define WINDOW_EDGE_TOPEDGE_WIDTH 4
#define WINDOW_EDGE_BOTTOMEDGE_WIDTH 4
#define WINDOW_EDGE_LEFTTOPEDGE_HEIGHT 10
#define WINDOW_EDGE_RIGHTTOPEDGE_HEIGHT 10

#define WINDOW_EDGE_TOP         0
#define WINDOW_EDGE_BOTTOM      1
#define WINDOW_EDGE_RIGHT       2
#define WINDOW_EDGE_LEFT        3
#define WINDOW_EDGE_TOPLEFT     4 // conner use
#define WINDOW_EDGE_TOPRIGHT    5 // conner use
#define WINDOW_EDGE_BOTTOMLEFT  6 // conner use
#define WINDOW_EDGE_BOTTOMRIGHT 7 // conner use
#define WINDOW_EDGE_LEFTTOP     8 // conner use
#define WINDOW_EDGE_RIGHTTOP    9 // conner use


typedef struct{
    UINT32 Type;                        //left,right,top,bottom
    GRAPHIC_AREA Area;               //area to put devices
}WINDOW_EDGE;

// window device
#define WINDOW_DEVICE_BUTTON    0
#define WINDOW_DEVICE_SELECTOR  1
#define WINDOW_DEVICE_STRINGBOX 2
#define WINDOW_DEVICE_CAPTION   3
#define WINDOW_DEVICE_BOARD     4
#define WINDOW_DEVICE_EDGE      5
#define WINDOW_DEVICE_OUTLINE   6
#define WINDOW_DEVICE_ICON      7
#define WINDOW_DEVICE_WINDOWBOX 8

typedef struct window_device{
    UINT32 Type;                       //component,user device
    UINT32 DeviceNumberLeft;
    UINT32 DeviceNumberMiddle;
    UINT32 DeviceNumberRight;
    UINT32 *pDevice;                   //caption,board...
    struct window_device *Prev;
    struct window_device *Next;
}WINDOW_DEVICE;

//window table
#define WINDOW_TABLE_NONE        0
#define WINDOW_TABLE_OUTLINE     1
#define WINDOW_TABLE_HEADER      2
#define WINDOW_TABLE_FOOTER      3
#define WINDOW_TABLE_MENU        4
#define WINDOW_TABLE_ICON        5
#define WINDOW_TABLE_GENERAL     6 // for user application

typedef struct window_table{
    UINT32 Type;                        //outline,header,...
    GRAPHIC_AREA Area;               //area to put devices
    GRAPHIC_GFX Gfx;
    WINDOW_DEVICE *DeviceList;         //for device management
    struct window_table *Prev;
    struct window_table *Next;
}WINDOW_TABLE;

/******
* os window control structure definition
*******/
#define WINDOW_WM_NONE   0
#define WINDOW_WM_CLOSE  1

#define WINDOW_WM_ACK_NONE 0
#define WINDOW_WM_NACK     1
#define WINDOW_WM_ACK      2

#define WINDOW_ATTRIBUTE_FIXSIZE      0x00
#define WINDOW_ATTRIBUTE_VARIABLESIZE 0x01

#define WINDOW_ATTRIBUTE_FIXSIZE      0x00
#define WINDOW_ATTRIBUTE_VARIABLESIZE 0x01

#define WINDOW_TYPE_NONE          0  // work area window
#define WINDOW_TYPE_WORK          1  // work area window
#define WINDOW_TYPE_WORKBAR       2  // workbar area window
#define WINDOW_TYPE_CONSOLE       3
#define WINDOW_TYPE_DESKDEBUG     4
#define WINDOW_TYPE_TIME          5
#define WINDOW_TYPE_CONTROLPANEL  6
#define WINDOW_TYPE_APPLICATION   7
#define WINDOW_TYPE_STARTMENU     8
#define WINDOW_TYPE_MAX           8

#define WINDOW_WDN_NULL                    0 //window null device number
#define WINDOW_WDN_OUTLINE_TOPLEFTEDGE     1 //window default device number
#define WINDOW_WDN_OUTLINE_TOPEDGE         2
#define WINDOW_WDN_OUTLINE_TOPRIGHTEDGE    3
#define WINDOW_WDN_OUTLINE_BOTTOMLEFTEDGE  4
#define WINDOW_WDN_OUTLINE_BOTTOMEDGE      5
#define WINDOW_WDN_OUTLINE_BOTTOMRIGHTEDGE 6
#define WINDOW_WDN_OUTLINE_LEFTTOPEDGE     7
#define WINDOW_WDN_OUTLINE_LEFTEDGE        8
#define WINDOW_WDN_OUTLINE_RIGHTTOPEDGE    9
#define WINDOW_WDN_OUTLINE_RIGHTEDGE       10
//#define WINDOW_WD_HEADER_HIDEICON         11
//#define WINDOW_WD_HEADER_MAXIMUNICON      12
//#define WINDOW_WD_HEADER_CLOSEICON        13
#define WINDOW_WDN_HEADER_HIDEBUTTON       14
#define WINDOW_WDN_HEADER_MAXIMUNBUTTON    15
#define WINDOW_WDN_HEADER_CLOSEBUTTON      16
#define WINDOW_WDN_WINDOWBOX               17
#define WINDOW_WDN_USERDEVICE             100


#define WINDOW_HEADER_HEIGHT 14

#define WINDOW_KEYBUFFER_SIZE 50
#define WINDOW_MOUSEBUFFER_SIZE 50
#define WINDOW_EVENTBUFFER_SIZE 50


typedef struct window{
    UINT8 State;                       //on desk,off desk
    UINT8 Type;                        //workbar window,work window, general window,time window 
    UINT8 DisplayType;
    UINT8 SizeVariable;                //
    UINT8 Removable;                   //
    UINT8 MessageAck;                  //window close message to task
    UINT8 Message;                     //task ack to window
    UINT8 Active;                      //active or inactive
    UINT8 Dirty;                       //window is dirty to display...status changed,window sizing...
    UINT8 *pTitle;                     //window name
    UINT8 *pFoot;                      //window foot name...not used now
    
    //quick reference window variables
    GRAPHIC_AREA DisplayArea;       // window's display area
    GRAPHIC_AREA DeviceArea;        // area for devices
    GRAPHIC_AREA DeviceDisplayArea; // area for devices display
    
    //tables in window
    WINDOW_TABLE *UserTableList;       // list of tables of user device list
    WINDOW_TABLE OutlineTable;
    WINDOW_TABLE HeaderTable;
    
    //outline area and edges
    WINDOW_OUTLINE Outline;   
    WINDOW_EDGE TopLeftEdge;
    WINDOW_EDGE TopEdge;
    WINDOW_EDGE TopRightEdge;
    WINDOW_EDGE BottomLeftEdge;
    WINDOW_EDGE BottomEdge;
    WINDOW_EDGE BottomRightEdge;
    WINDOW_EDGE LeftTopEdge;
    WINDOW_EDGE LeftEdge;
    WINDOW_EDGE RightTopEdge;
    WINDOW_EDGE RightEdge;
    WINDOW_DEVICE DeviceTopLeftEdge;
    WINDOW_DEVICE DeviceTopEdge;
    WINDOW_DEVICE DeviceTopRightEdge;
    WINDOW_DEVICE DeviceBottomLeftEdge;
    WINDOW_DEVICE DeviceBottomEdge;
    WINDOW_DEVICE DeviceBottomRightEdge;
    WINDOW_DEVICE DeviceLeftTopEdge;
    WINDOW_DEVICE DeviceLeftEdge;
    WINDOW_DEVICE DeviceRightTopEdge;
    WINDOW_DEVICE DeviceRightEdge;
    
    WINDOW_BUTTON HideButton;
    WINDOW_BUTTON MaximunButton;    
    WINDOW_BUTTON CloseButton;    
    WINDOW_DEVICE WdHideButton;
    WINDOW_DEVICE WdMaximunButton;
    WINDOW_DEVICE WdCloseButton;

    WINDOW_WINDOWBOX WindowBox;     //for workbar use
    WINDOW_DEVICE DeviceWindowBox;  //for workbar use
    
    UINT8 KeyPut;
    UINT8 KeyGet;
    UINT16 KeyBuffer[WINDOW_KEYBUFFER_SIZE];
    
    UINT8 MousePut;
    UINT8 MouseGet;
    UINT32 MouseBuffer[WINDOW_MOUSEBUFFER_SIZE];
    
    UINT8 EventPut;
    UINT8 EventGet;
    UINT32 EventBuffer[WINDOW_EVENTBUFFER_SIZE];
    
    struct window *Prev;         // window link list for work area use 
    struct window *Next;
}WINDOW;

void WindowVariableInit(WINDOW *pWindow,UINT8 WindowType);
void WindowParameterInit(WINDOW *pWindow);
void WindowOutlineCalculate(WINDOW *pWindow);
void WindowOutlineTableInitial(WINDOW *pWindow);
void WindowHeaderCalculate(WINDOW *pWindow);
void WindowHeaderTableInitial(WINDOW *pWindow);
void WindowAreaInitial(WINDOW *pWindow);
void WindowAreaAdjust(WINDOW *pWindow);

BOOLEAN WindowKeyBufferCheck(WINDOW *pWindow);
void WindowKeyBufferPut(WINDOW *pWindow,UINT16 Data);
UINT8 WindowKeyBufferGet(WINDOW *pWindow);
BOOLEAN WindowMouseBufferCheck(WINDOW *pWindow);
void WindowMouseBufferPut(WINDOW *pWindow,UINT32 Data);
UINT32 WindowMouseBufferGet(WINDOW *pWindow);
BOOLEAN WindowEventBufferCheck(WINDOW *pWindow);
void WindowEventBufferPut(WINDOW *pWindow,UINT32 Data);
UINT32 WindowEventBufferGet(WINDOW *pWindow);

#endif
