#include <includes.h>

const UINT8 DeskTimeWindowName[]="TIME";

DESK_TIME_CONTROL DeskTimeCtrl;

VOID DeskTimeInit(VOID){
    //window parameter
	WindowVariableInit(&DeskTimeCtrl.Window,WINDOW_TYPE_TIME);
    DeskTimeCtrl.Window.pTitle=(UINT8 *)DeskTimeWindowName;  
    
    //window table initial
    DeskTimeCtrl.Window.UserTableList=(WINDOW_TABLE *)NULL;
    DeskTimeCtrl.Window.OutlineTable.Type=WINDOW_TABLE_OUTLINE;
    DeskTimeCtrl.Window.OutlineTable.DeviceList=(WINDOW_DEVICE *)NULL;
    DeskTimeCtrl.Window.HeaderTable.Type=WINDOW_TABLE_HEADER;
    DeskTimeCtrl.Window.HeaderTable.DeviceList=(WINDOW_DEVICE *)NULL;
    DeskTimeCtrl.UserTable.Type=WINDOW_TABLE_GENERAL;
    DeskTimeCtrl.UserTable.DeviceList=(WINDOW_DEVICE *)NULL;
    DeskTableUserTableAdd((WINDOW *)&DeskTimeCtrl.Window,(WINDOW_TABLE *)&DeskTimeCtrl.UserTable);
    //user table initial for desk debug 
    BoardCreat(&DeskTimeCtrl.Board,100,70);
	DeskTimeCtrl.DeskDeviceBoard.Type=WINDOW_DEVICE_BOARD;
	DeskTimeCtrl.DeskDeviceBoard.pDevice=(UINT32 *)(&DeskTimeCtrl.Board);
    DeskTimeCtrl.UserTable.Area.X=0;
    DeskTimeCtrl.UserTable.Area.Y=0;
    DeskTimeCtrl.UserTable.Area.W=DeskTimeCtrl.Board.Area.W;
    DeskTimeCtrl.UserTable.Area.H=DeskTimeCtrl.Board.Area.H;
    DeskTableWindowDeviceAdd(&DeskTimeCtrl.UserTable,&DeskTimeCtrl.DeskDeviceBoard);
    
    WindowAreaInitial(&DeskTimeCtrl.Window); //display area,device area,devicedisplay area calculation 
    WindowOutlineCalculate(&DeskTimeCtrl.Window);
    WindowOutlineTableInitial(&DeskTimeCtrl.Window);
    WindowHeaderCalculate(&DeskTimeCtrl.Window);
    WindowHeaderTableInitial(&DeskTimeCtrl.Window);
}