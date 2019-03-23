#include <includes.h>

VOID WindowVariableInit(WINDOW *pWindow,UINT8 WindowType){
    if(WindowType>WINDOW_TYPE_MAX) WindowType=WINDOW_TYPE_NONE;
    if(WindowType==WINDOW_TYPE_APPLICATION){
        pWindow->State=DESK_WINDOW_STATE_OFFDESK;
        pWindow->Type=WindowType; //DESK_WINDOW_TYPE_CONSOLE;
        pWindow->SizeVariable=FALSE; 
        pWindow->Removable=TRUE;     
    }
    else if(WindowType==WINDOW_TYPE_STARTMENU){
        pWindow->State=DESK_WINDOW_STATE_OFFDESK;
        pWindow->Type=WindowType; //DESK_WINDOW_TYPE_CONSOLE;
        pWindow->SizeVariable=FALSE; 
        pWindow->Removable=FALSE;
    }
    else{
        pWindow->State=DESK_WINDOW_STATE_OFFDESK;
        pWindow->Type=WindowType; //DESK_WINDOW_TYPE_CONSOLE;
        pWindow->SizeVariable=FALSE; 
        pWindow->Removable=TRUE;     
    }
    pWindow->DisplayType=DESK_WINDOW_STATUS_NORMAL;
    pWindow->Message=WINDOW_WM_NONE;
    pWindow->MessageAck=WINDOW_WM_ACK_NONE;
    pWindow->Dirty=FALSE;
    pWindow->Active=FALSE;
    pWindow->pTitle=(UINT8 *)NULL;
    pWindow->pFoot=(UINT8 *)NULL;
    pWindow->UserTableList=(WINDOW_TABLE *)NULL;
    pWindow->KeyPut=0;
    pWindow->KeyGet=0;
    pWindow->MousePut=0;
    pWindow->MouseGet=0;
    pWindow->EventPut=0;
    pWindow->EventGet=0;
    
    pWindow->WindowBox.Type=WINDOW_WINDOWBOX_GENERAL;
    pWindow->WindowBox.pWindow=(UINT32 *)pWindow;
    pWindow->WindowBox.ActiveGfx.BgColor=GFX_COLOR_BLACK;
    pWindow->WindowBox.ActiveGfx.FgColor=GFX_COLOR_BLACK;
    pWindow->WindowBox.ActiveGfx.FontColor=GFX_COLOR_WHITE;
    pWindow->WindowBox.InactiveGfx.BgColor=GFX_COLOR_BLACK;
    pWindow->WindowBox.InactiveGfx.FgColor=GFX_COLOR_BLACK;
    pWindow->WindowBox.InactiveGfx.FontColor=GFX_COLOR_WHITE;
    pWindow->WindowBox.Area.X=0;
    pWindow->WindowBox.Area.Y=0;
    pWindow->WindowBox.Area.W=0;
    pWindow->WindowBox.Area.H=0;
    pWindow->DeviceWindowBox.Type=WINDOW_DEVICE_WINDOWBOX;
    pWindow->DeviceWindowBox.DeviceNumberLeft=WINDOW_WDN_WINDOWBOX;
    pWindow->DeviceWindowBox.DeviceNumberMiddle=WINDOW_WDN_WINDOWBOX;
    pWindow->DeviceWindowBox.DeviceNumberRight=WINDOW_WDN_WINDOWBOX;
    pWindow->DeviceWindowBox.pDevice=(UINT32 *)&pWindow->WindowBox;
    pWindow->DeviceWindowBox.Prev=(WINDOW_DEVICE *)NULL;
    pWindow->DeviceWindowBox.Next=(WINDOW_DEVICE *)NULL;

    pWindow->OutlineTable.Type=WINDOW_TABLE_OUTLINE;
    pWindow->OutlineTable.Gfx.BgColor=GFX_COLOR_GRAY;
    pWindow->OutlineTable.Gfx.FgColor=GFX_COLOR_GRAY;
    pWindow->OutlineTable.Gfx.FontColor=GFX_COLOR_WHITE;
    pWindow->OutlineTable.Area.X=0;
    pWindow->OutlineTable.Area.Y=0;
    pWindow->OutlineTable.Area.W=0;
    pWindow->OutlineTable.Area.H=0;
    pWindow->OutlineTable.DeviceList=(WINDOW_DEVICE *)NULL;
    pWindow->OutlineTable.Prev=(WINDOW_TABLE *)NULL;
    pWindow->OutlineTable.Next=(WINDOW_TABLE *)NULL;
    
    pWindow->HeaderTable.Type=WINDOW_TABLE_HEADER;
    pWindow->HeaderTable.Gfx.BgColor=GFX_COLOR_GRAY;
    pWindow->HeaderTable.Gfx.FgColor=GFX_COLOR_GRAY;
    pWindow->HeaderTable.Gfx.FontColor=GFX_COLOR_WHITE;
    pWindow->HeaderTable.Area.X=0;
    pWindow->HeaderTable.Area.Y=0;
    pWindow->HeaderTable.Area.W=0;
    pWindow->HeaderTable.Area.H=0;
    pWindow->HeaderTable.DeviceList=(WINDOW_DEVICE *)NULL;
    pWindow->HeaderTable.Prev=(WINDOW_TABLE *)NULL;
    pWindow->HeaderTable.Next=(WINDOW_TABLE *)NULL;
    
    pWindow->Prev=(WINDOW *)NULL;
    pWindow->Next=(WINDOW *)NULL;
}

VOID WindowOutlineCalculate(WINDOW *pWindow){
    pWindow->OutlineTable.Area.X=0;
    pWindow->OutlineTable.Area.Y=0;
    pWindow->OutlineTable.Area.W=pWindow->DisplayArea.W;
    pWindow->OutlineTable.Area.H=pWindow->DisplayArea.H;
    
    pWindow->Outline.Type=WINDOW_OUTLINE_GENERAL;
    pWindow->Outline.OuterArea.X=0;
    pWindow->Outline.OuterArea.Y=0;
    pWindow->Outline.OuterArea.W=pWindow->DisplayArea.W;
    pWindow->Outline.OuterArea.H=pWindow->DisplayArea.H;
    pWindow->Outline.InnerArea.X=WINDOW_EDGE_THINK;
    pWindow->Outline.InnerArea.Y=WINDOW_EDGE_THINK;
    pWindow->Outline.InnerArea.W=pWindow->DisplayArea.W-WINDOW_EDGE_THINK*2;
    pWindow->Outline.InnerArea.H=pWindow->DisplayArea.H-WINDOW_EDGE_THINK*2;

    pWindow->TopLeftEdge.Type=WINDOW_EDGE_TOPLEFT;
    pWindow->TopLeftEdge.Area.X=0;
    pWindow->TopLeftEdge.Area.Y=0;
    pWindow->TopLeftEdge.Area.W=4;
    pWindow->TopLeftEdge.Area.H=WINDOW_EDGE_THINK;
    
    pWindow->TopEdge.Type=WINDOW_EDGE_TOP;
    pWindow->TopEdge.Area.X=4;
    pWindow->TopEdge.Area.Y=0;
    pWindow->TopEdge.Area.W=pWindow->Outline.OuterArea.W-4*2;
    pWindow->TopEdge.Area.H=WINDOW_EDGE_THINK;
    
    pWindow->TopRightEdge.Type=WINDOW_EDGE_TOPRIGHT;
    pWindow->TopRightEdge.Area.X=pWindow->Outline.OuterArea.W-4;
    pWindow->TopRightEdge.Area.Y=0;
    pWindow->TopRightEdge.Area.W=4;
    pWindow->TopRightEdge.Area.H=WINDOW_EDGE_THINK;
    
    pWindow->BottomLeftEdge.Type=WINDOW_EDGE_BOTTOMLEFT;
    pWindow->BottomLeftEdge.Area.X=0;
    pWindow->BottomLeftEdge.Area.Y=pWindow->Outline.OuterArea.H-2;
    pWindow->BottomLeftEdge.Area.W=4;
    pWindow->BottomLeftEdge.Area.H=WINDOW_EDGE_THINK;
    
    pWindow->BottomEdge.Type=WINDOW_EDGE_BOTTOM;
    pWindow->BottomEdge.Area.X=4;
    pWindow->BottomEdge.Area.Y=pWindow->Outline.OuterArea.H-2;
    pWindow->BottomEdge.Area.W=pWindow->Outline.OuterArea.W-4*2;
    pWindow->BottomEdge.Area.H=WINDOW_EDGE_THINK;
    
    pWindow->BottomRightEdge.Type=WINDOW_EDGE_BOTTOMRIGHT;
    pWindow->BottomRightEdge.Area.X=pWindow->Outline.OuterArea.W-4;
    pWindow->BottomRightEdge.Area.Y=pWindow->Outline.OuterArea.H-2;
    pWindow->BottomRightEdge.Area.W=4;
    pWindow->BottomRightEdge.Area.H=WINDOW_EDGE_THINK;
    
    pWindow->LeftTopEdge.Type=WINDOW_EDGE_LEFTTOP;
    pWindow->LeftTopEdge.Area.X=0;
    pWindow->LeftTopEdge.Area.Y=WINDOW_EDGE_THINK;
    pWindow->LeftTopEdge.Area.W=WINDOW_EDGE_THINK;
    pWindow->LeftTopEdge.Area.H=WINDOW_EDGE_LEFTTOPEDGE_HEIGHT;
    
    pWindow->LeftEdge.Type=WINDOW_EDGE_LEFT;
    pWindow->LeftEdge.Area.X=0;
    pWindow->LeftEdge.Area.Y=WINDOW_EDGE_THINK+WINDOW_EDGE_LEFTTOPEDGE_HEIGHT;
    pWindow->LeftEdge.Area.W=WINDOW_EDGE_THINK;
    pWindow->LeftEdge.Area.H=pWindow->Outline.OuterArea.H-WINDOW_EDGE_THINK*2-WINDOW_EDGE_LEFTTOPEDGE_HEIGHT;
    
    pWindow->RightTopEdge.Type=WINDOW_EDGE_RIGHTTOP;
    pWindow->RightTopEdge.Area.X=pWindow->Outline.OuterArea.W-WINDOW_EDGE_THINK;
    pWindow->RightTopEdge.Area.Y=WINDOW_EDGE_THINK;
    pWindow->RightTopEdge.Area.W=WINDOW_EDGE_THINK;
    pWindow->RightTopEdge.Area.H=WINDOW_EDGE_RIGHTTOPEDGE_HEIGHT;
    
    pWindow->RightEdge.Type=WINDOW_EDGE_RIGHT;
    pWindow->RightEdge.Area.X=pWindow->Outline.OuterArea.W-WINDOW_EDGE_THINK;
    pWindow->RightEdge.Area.Y=WINDOW_EDGE_THINK+WINDOW_EDGE_LEFTTOPEDGE_HEIGHT;
    pWindow->RightEdge.Area.W=WINDOW_EDGE_THINK;
    pWindow->RightEdge.Area.H=pWindow->Outline.OuterArea.H-WINDOW_EDGE_THINK*2-WINDOW_EDGE_RIGHTTOPEDGE_HEIGHT;
}

VOID WindowOutlineTableInitial(WINDOW *pWindow){
    pWindow->DeviceTopLeftEdge.DeviceNumberLeft=WINDOW_WDN_OUTLINE_TOPLEFTEDGE;
    pWindow->DeviceTopLeftEdge.DeviceNumberMiddle=WINDOW_WDN_OUTLINE_TOPLEFTEDGE;
    pWindow->DeviceTopLeftEdge.DeviceNumberRight=WINDOW_WDN_OUTLINE_TOPLEFTEDGE;
    pWindow->DeviceTopLeftEdge.Type=WINDOW_DEVICE_EDGE;
    pWindow->DeviceTopLeftEdge.pDevice=(UINT32 *)&pWindow->TopLeftEdge;
    
    pWindow->DeviceTopEdge.DeviceNumberLeft=WINDOW_WDN_OUTLINE_TOPEDGE;
    pWindow->DeviceTopEdge.DeviceNumberMiddle=WINDOW_WDN_OUTLINE_TOPEDGE;
    pWindow->DeviceTopEdge.DeviceNumberRight=WINDOW_WDN_OUTLINE_TOPEDGE;
    pWindow->DeviceTopEdge.Type=WINDOW_DEVICE_EDGE;
    pWindow->DeviceTopEdge.pDevice=(UINT32 *)&pWindow->TopEdge;
    
    pWindow->DeviceTopRightEdge.DeviceNumberLeft=WINDOW_WDN_OUTLINE_TOPRIGHTEDGE;
    pWindow->DeviceTopRightEdge.DeviceNumberMiddle=WINDOW_WDN_OUTLINE_TOPRIGHTEDGE;
    pWindow->DeviceTopRightEdge.DeviceNumberRight=WINDOW_WDN_OUTLINE_TOPRIGHTEDGE;
    pWindow->DeviceTopRightEdge.Type=WINDOW_DEVICE_EDGE;
    pWindow->DeviceTopRightEdge.pDevice=(UINT32 *)&pWindow->TopRightEdge;
    
    pWindow->DeviceBottomLeftEdge.DeviceNumberLeft=WINDOW_WDN_OUTLINE_BOTTOMLEFTEDGE;
    pWindow->DeviceBottomLeftEdge.DeviceNumberMiddle=WINDOW_WDN_OUTLINE_BOTTOMLEFTEDGE;
    pWindow->DeviceBottomLeftEdge.DeviceNumberRight=WINDOW_WDN_OUTLINE_BOTTOMLEFTEDGE;
    pWindow->DeviceBottomLeftEdge.Type=WINDOW_DEVICE_EDGE;
    pWindow->DeviceBottomLeftEdge.pDevice=(UINT32 *)&pWindow->BottomLeftEdge;
    
    pWindow->DeviceBottomEdge.DeviceNumberLeft=WINDOW_WDN_OUTLINE_BOTTOMEDGE;
    pWindow->DeviceBottomEdge.DeviceNumberMiddle=WINDOW_WDN_OUTLINE_BOTTOMEDGE;
    pWindow->DeviceBottomEdge.DeviceNumberRight=WINDOW_WDN_OUTLINE_BOTTOMEDGE;
    pWindow->DeviceBottomEdge.Type=WINDOW_DEVICE_EDGE;
    pWindow->DeviceBottomEdge.pDevice=(UINT32 *)&pWindow->BottomEdge;
    
    pWindow->DeviceBottomRightEdge.DeviceNumberLeft=WINDOW_WDN_OUTLINE_BOTTOMRIGHTEDGE;
    pWindow->DeviceBottomRightEdge.DeviceNumberMiddle=WINDOW_WDN_OUTLINE_BOTTOMRIGHTEDGE;
    pWindow->DeviceBottomRightEdge.DeviceNumberRight=WINDOW_WDN_OUTLINE_BOTTOMRIGHTEDGE;
    pWindow->DeviceBottomRightEdge.Type=WINDOW_DEVICE_EDGE;
    pWindow->DeviceBottomRightEdge.pDevice=(UINT32 *)&pWindow->BottomRightEdge;
    
    pWindow->DeviceLeftTopEdge.DeviceNumberLeft=WINDOW_WDN_OUTLINE_LEFTTOPEDGE;
    pWindow->DeviceLeftTopEdge.DeviceNumberMiddle=WINDOW_WDN_OUTLINE_LEFTTOPEDGE;
    pWindow->DeviceLeftTopEdge.DeviceNumberRight=WINDOW_WDN_OUTLINE_LEFTTOPEDGE;
    pWindow->DeviceLeftTopEdge.Type=WINDOW_DEVICE_EDGE;
    pWindow->DeviceLeftTopEdge.pDevice=(UINT32 *)&pWindow->LeftTopEdge;
    
    pWindow->DeviceLeftEdge.DeviceNumberLeft=WINDOW_WDN_OUTLINE_LEFTEDGE;
    pWindow->DeviceLeftEdge.DeviceNumberMiddle=WINDOW_WDN_OUTLINE_LEFTEDGE;
    pWindow->DeviceLeftEdge.DeviceNumberRight=WINDOW_WDN_OUTLINE_LEFTEDGE;
    pWindow->DeviceLeftEdge.Type=WINDOW_DEVICE_EDGE;
    pWindow->DeviceLeftEdge.pDevice=(UINT32 *)&pWindow->LeftEdge;
    
    pWindow->DeviceRightTopEdge.DeviceNumberLeft=WINDOW_WDN_OUTLINE_RIGHTTOPEDGE;
    pWindow->DeviceRightTopEdge.DeviceNumberMiddle=WINDOW_WDN_OUTLINE_RIGHTTOPEDGE;
    pWindow->DeviceRightTopEdge.DeviceNumberRight=WINDOW_WDN_OUTLINE_RIGHTTOPEDGE;
    pWindow->DeviceRightTopEdge.Type=WINDOW_DEVICE_EDGE;
    pWindow->DeviceRightTopEdge.pDevice=(UINT32 *)&pWindow->RightTopEdge;
    
    pWindow->DeviceRightEdge.DeviceNumberLeft=WINDOW_WDN_OUTLINE_RIGHTEDGE;
    pWindow->DeviceRightEdge.DeviceNumberMiddle=WINDOW_WDN_OUTLINE_RIGHTEDGE;
    pWindow->DeviceRightEdge.DeviceNumberRight=WINDOW_WDN_OUTLINE_RIGHTEDGE;
    pWindow->DeviceRightEdge.Type=WINDOW_DEVICE_EDGE;
    pWindow->DeviceRightEdge.pDevice=(UINT32 *)&pWindow->RightEdge;
    
    DeskTableWindowDeviceAdd(&pWindow->OutlineTable,&pWindow->DeviceTopLeftEdge);
    DeskTableWindowDeviceAdd(&pWindow->OutlineTable,&pWindow->DeviceTopEdge);
    DeskTableWindowDeviceAdd(&pWindow->OutlineTable,&pWindow->DeviceTopRightEdge);
    DeskTableWindowDeviceAdd(&pWindow->OutlineTable,&pWindow->DeviceBottomLeftEdge);
    DeskTableWindowDeviceAdd(&pWindow->OutlineTable,&pWindow->DeviceBottomEdge);
    DeskTableWindowDeviceAdd(&pWindow->OutlineTable,&pWindow->DeviceBottomRightEdge);
    DeskTableWindowDeviceAdd(&pWindow->OutlineTable,&pWindow->DeviceLeftTopEdge);
    DeskTableWindowDeviceAdd(&pWindow->OutlineTable,&pWindow->DeviceLeftEdge);
    DeskTableWindowDeviceAdd(&pWindow->OutlineTable,&pWindow->DeviceRightTopEdge);
    DeskTableWindowDeviceAdd(&pWindow->OutlineTable,&pWindow->DeviceRightEdge);
}

VOID WindowHeaderCalculate(WINDOW *pWindow){
    pWindow->HeaderTable.Area.X=WINDOW_EDGE_THINK;
    pWindow->HeaderTable.Area.Y=WINDOW_EDGE_THINK;
    pWindow->HeaderTable.Area.W=pWindow->Outline.InnerArea.W;
    pWindow->HeaderTable.Area.H=WINDOW_HEADER_HEIGHT;

    //header icon...close icon
    pWindow->CloseButton.Type=WINDOW_BUTTON_CLOSE;
    pWindow->CloseButton.Status=WINDOW_BUTTON_RELEASE;
    pWindow->CloseButton.Active=TRUE;
    pWindow->CloseButton.Dirty=TRUE;
    pWindow->CloseButton.Outline=TRUE;
    pWindow->CloseButton.OutlineColor=GFX_COLOR_WHITE;
    pWindow->CloseButton.pName=(UINT8 *)NULL;
    pWindow->CloseButton.pBitmap=(UINT8 *)DeskCloseButton;
    pWindow->CloseButton.ReleaseGfx.BgColor=GFX_COLOR_BLUE3;
    pWindow->CloseButton.ReleaseGfx.FgColor=GFX_COLOR_BLUE3;
    pWindow->CloseButton.ReleaseGfx.FontColor=GFX_COLOR_WHITE;
    pWindow->CloseButton.PressGfx.BgColor=GFX_COLOR_LIGHTBLUE2;
    pWindow->CloseButton.PressGfx.FgColor=GFX_COLOR_LIGHTBLUE2;
    pWindow->CloseButton.PressGfx.FontColor=GFX_COLOR_WHITE;
    pWindow->CloseButton.InactiveGfx.BgColor=GFX_COLOR_LIGHTGRAY;
    pWindow->CloseButton.InactiveGfx.FgColor=GFX_COLOR_LIGHTGRAY;
    pWindow->CloseButton.InactiveGfx.FontColor=GFX_COLOR_BLUE;
    pWindow->CloseButton.Area.X=pWindow->HeaderTable.Area.W-13;
    pWindow->CloseButton.Area.Y=1; //1;
    pWindow->CloseButton.Area.W=12;
    pWindow->CloseButton.Area.H=12; //8;
    //header icon...maximun icon
    pWindow->MaximunButton.Type=WINDOW_BUTTON_MAXIMUN;
    pWindow->MaximunButton.Status=WINDOW_BUTTON_RELEASE;
    pWindow->MaximunButton.Active=TRUE;
    pWindow->MaximunButton.Dirty=TRUE;
    pWindow->MaximunButton.Outline=TRUE;
    pWindow->MaximunButton.OutlineColor=GFX_COLOR_WHITE;
    pWindow->MaximunButton.pName=(UINT8 *)NULL;
    pWindow->MaximunButton.pBitmap=(UINT8 *)DeskMaximunButton;
    pWindow->MaximunButton.ReleaseGfx.BgColor=GFX_COLOR_BLUE3;
    pWindow->MaximunButton.ReleaseGfx.FgColor=GFX_COLOR_BLUE3;
    pWindow->MaximunButton.ReleaseGfx.FontColor=GFX_COLOR_WHITE;
    pWindow->MaximunButton.PressGfx.BgColor=GFX_COLOR_LIGHTBLUE2;
    pWindow->MaximunButton.PressGfx.FgColor=GFX_COLOR_LIGHTBLUE2;
    pWindow->MaximunButton.PressGfx.FontColor=GFX_COLOR_WHITE;
    pWindow->MaximunButton.InactiveGfx.BgColor=GFX_COLOR_LIGHTGRAY;
    pWindow->MaximunButton.InactiveGfx.FgColor=GFX_COLOR_LIGHTGRAY;
    pWindow->MaximunButton.InactiveGfx.FontColor=GFX_COLOR_BLUE;
    pWindow->MaximunButton.Area.X=pWindow->HeaderTable.Area.W-26;
    pWindow->MaximunButton.Area.Y=1; //1;
    pWindow->MaximunButton.Area.W=12;
    pWindow->MaximunButton.Area.H=12; //8;
    //header icon...hide icon
    pWindow->HideButton.Type=WINDOW_BUTTON_HIDE;
    pWindow->HideButton.Status=WINDOW_BUTTON_RELEASE;
    pWindow->HideButton.Active=TRUE;
    pWindow->HideButton.Dirty=TRUE;
    pWindow->HideButton.Outline=TRUE;
    pWindow->HideButton.OutlineColor=GFX_COLOR_WHITE;
    pWindow->HideButton.pName=(UINT8 *)NULL;
    pWindow->HideButton.pBitmap=(UINT8 *)DeskHideButton;
    pWindow->HideButton.ReleaseGfx.BgColor=GFX_COLOR_BLUE3;
    pWindow->HideButton.ReleaseGfx.FgColor=GFX_COLOR_BLUE3;
    pWindow->HideButton.ReleaseGfx.FontColor=GFX_COLOR_WHITE;
    pWindow->HideButton.PressGfx.BgColor=GFX_COLOR_LIGHTBLUE2;
    pWindow->HideButton.PressGfx.FgColor=GFX_COLOR_LIGHTBLUE2;
    pWindow->HideButton.PressGfx.FontColor=GFX_COLOR_WHITE;
    pWindow->HideButton.InactiveGfx.BgColor=GFX_COLOR_LIGHTGRAY;
    pWindow->HideButton.InactiveGfx.FgColor=GFX_COLOR_LIGHTGRAY;
    pWindow->HideButton.InactiveGfx.FontColor=GFX_COLOR_BLUE;
    pWindow->HideButton.Area.X=pWindow->HeaderTable.Area.W-39;
    pWindow->HideButton.Area.Y=1; //1;
    pWindow->HideButton.Area.W=12;
    pWindow->HideButton.Area.H=12; //8;
    
    if(pWindow->Type==WINDOW_TYPE_STARTMENU){
        pWindow->CloseButton.Area.X=0;
        pWindow->CloseButton.Area.Y=0;
        pWindow->CloseButton.Area.W=0;
        pWindow->CloseButton.Area.H=0;
        
        pWindow->MaximunButton.Area.X=0;
        pWindow->MaximunButton.Area.Y=0;
        pWindow->MaximunButton.Area.W=0;
        pWindow->MaximunButton.Area.H=0;
        
        pWindow->HideButton.Area.X=0;
        pWindow->HideButton.Area.Y=0;
        pWindow->HideButton.Area.W=0;
        pWindow->HideButton.Area.H=0;
    }
}

VOID WindowHeaderTableInitial(WINDOW *pWindow){
    if(pWindow->Type==WINDOW_TYPE_STARTMENU) return;
    pWindow->WdCloseButton.DeviceNumberLeft=WINDOW_WDN_HEADER_CLOSEBUTTON;
    pWindow->WdCloseButton.DeviceNumberMiddle=WINDOW_WDN_NULL;
    pWindow->WdCloseButton.DeviceNumberRight=WINDOW_WDN_NULL;
    pWindow->WdCloseButton.Type=WINDOW_DEVICE_BUTTON;
    pWindow->WdCloseButton.pDevice=(UINT32 *)&pWindow->CloseButton;
    pWindow->WdCloseButton.Prev=(WINDOW_DEVICE *)NULL;
    pWindow->WdCloseButton.Next=(WINDOW_DEVICE *)NULL;
    pWindow->WdMaximunButton.DeviceNumberLeft=WINDOW_WDN_HEADER_MAXIMUNBUTTON;
    pWindow->WdMaximunButton.DeviceNumberMiddle=WINDOW_WDN_NULL;
    pWindow->WdMaximunButton.DeviceNumberRight=WINDOW_WDN_NULL;
    pWindow->WdMaximunButton.Type=WINDOW_DEVICE_BUTTON;
    pWindow->WdMaximunButton.pDevice=(UINT32 *)&pWindow->MaximunButton;
    pWindow->WdMaximunButton.Prev=(WINDOW_DEVICE *)NULL;
    pWindow->WdMaximunButton.Next=(WINDOW_DEVICE *)NULL;
    pWindow->WdHideButton.DeviceNumberLeft=WINDOW_WDN_HEADER_HIDEBUTTON;
    pWindow->WdHideButton.DeviceNumberMiddle=WINDOW_WDN_NULL;
    pWindow->WdHideButton.DeviceNumberRight=WINDOW_WDN_NULL;
    pWindow->WdHideButton.Type=WINDOW_DEVICE_BUTTON;
    pWindow->WdHideButton.pDevice=(UINT32 *)&pWindow->HideButton;
    pWindow->WdHideButton.Prev=(WINDOW_DEVICE *)NULL;
    pWindow->WdHideButton.Next=(WINDOW_DEVICE *)NULL;
    DeskTableWindowDeviceAdd(&pWindow->HeaderTable,&pWindow->WdHideButton);
    DeskTableWindowDeviceAdd(&pWindow->HeaderTable,&pWindow->WdMaximunButton);
    DeskTableWindowDeviceAdd(&pWindow->HeaderTable,&pWindow->WdCloseButton);
}

VOID WindowAreaInitial(WINDOW *pWindow){
    WINDOW_TABLE  *pTable;
    
    pTable=pWindow->UserTableList;
    if(pTable==(WINDOW_TABLE  *)NULL){
        pWindow->DisplayArea.X=0;
        pWindow->DisplayArea.Y=0;
        pWindow->DisplayArea.W=DESK_WINDOW_WIDTH_MINIMUN;
        pWindow->DisplayArea.H=DESK_WINDOW_HEIGHT_MINIMUN;
        
        pWindow->DeviceArea.X=WINDOW_EDGE_THINK;
        pWindow->DeviceArea.Y=WINDOW_EDGE_THINK+WINDOW_HEADER_HEIGHT;
        pWindow->DeviceArea.W=pWindow->DisplayArea.W-WINDOW_EDGE_THINK*2;
        pWindow->DeviceArea.H=0;   
        
        pWindow->DeviceDisplayArea.X=WINDOW_EDGE_THINK;
        pWindow->DeviceDisplayArea.Y=WINDOW_EDGE_THINK+WINDOW_HEADER_HEIGHT;
        pWindow->DeviceDisplayArea.W=pWindow->DisplayArea.W-WINDOW_EDGE_THINK*2;
        pWindow->DeviceDisplayArea.H=0;   
    }
    else{
        pWindow->DisplayArea.X=0;
        pWindow->DisplayArea.Y=0;
        pWindow->DisplayArea.W=pTable->Area.W+WINDOW_EDGE_THINK*2;
        pWindow->DisplayArea.H=pTable->Area.H+WINDOW_HEADER_HEIGHT+WINDOW_EDGE_THINK*2;
        if((pWindow->DisplayArea.X+pWindow->DisplayArea.W)>DESK_WINDOW_WIDTH_MAXIMUN){
            pWindow->DisplayArea.W=DESK_WINDOW_WIDTH_MAXIMUN-pWindow->DisplayArea.X;
        }
        if((pWindow->DisplayArea.Y+pWindow->DisplayArea.H)>DESK_WINDOW_HEIGHT_MAXIMUN){
            pWindow->DisplayArea.H=DESK_WINDOW_HEIGHT_MAXIMUN-pWindow->DisplayArea.Y;
        }
        
        pWindow->DeviceArea.X=WINDOW_EDGE_THINK;
        pWindow->DeviceArea.Y=WINDOW_EDGE_THINK+WINDOW_HEADER_HEIGHT;
        pWindow->DeviceArea.W=pTable->Area.W;
        pWindow->DeviceArea.H=pTable->Area.H; 
        
        pWindow->DeviceDisplayArea.X=WINDOW_EDGE_THINK;
        pWindow->DeviceDisplayArea.Y=WINDOW_EDGE_THINK+WINDOW_HEADER_HEIGHT;
        pWindow->DeviceDisplayArea.W=pWindow->DisplayArea.W-WINDOW_EDGE_THINK*2;
        pWindow->DeviceDisplayArea.H=pWindow->DisplayArea.H-WINDOW_HEADER_HEIGHT-WINDOW_EDGE_THINK*2;
        
        pTable->Area.X=pWindow->DeviceArea.X;
        pTable->Area.Y=pWindow->DeviceArea.Y;
    }
}

VOID WindowAreaAdjust(WINDOW *pWindow){
    WINDOW_TABLE  *pTable;
    
    pTable=pWindow->UserTableList;
    if(pTable==(WINDOW_TABLE  *)NULL){
        pWindow->DeviceDisplayArea.X=WINDOW_EDGE_THINK;
        pWindow->DeviceDisplayArea.Y=WINDOW_EDGE_THINK+WINDOW_HEADER_HEIGHT;
        pWindow->DeviceDisplayArea.W=pWindow->DisplayArea.W-WINDOW_EDGE_THINK*2;
        pWindow->DeviceDisplayArea.H=0;   
    }
    else{
        pWindow->DeviceDisplayArea.X=WINDOW_EDGE_THINK;
        pWindow->DeviceDisplayArea.Y=WINDOW_EDGE_THINK+WINDOW_HEADER_HEIGHT;
        pWindow->DeviceDisplayArea.W=pWindow->DisplayArea.W-WINDOW_EDGE_THINK*2;
        pWindow->DeviceDisplayArea.H=pWindow->DisplayArea.H-WINDOW_HEADER_HEIGHT-WINDOW_EDGE_THINK*2;
    }
    WindowOutlineCalculate(pWindow);
    WindowHeaderCalculate(pWindow);
}

BOOLEAN WindowKeyBufferCheck(WINDOW *pWindow){
    if(pWindow->KeyPut!=pWindow->KeyGet){
        if(pWindow->KeyPut==(WINDOW_KEYBUFFER_SIZE-1)){
            if(pWindow->KeyGet==0) return BUFFER_FULL;
            else return BUFFER_NOT_EMPTY;
        }
        else{
            if((pWindow->KeyPut+1)==pWindow->KeyGet) return BUFFER_FULL;
            else return BUFFER_NOT_EMPTY;
        }
    }
    else return BUFFER_EMPTY;
}

VOID WindowKeyBufferPut(WINDOW *pWindow,UINT16 Data){
    if(WindowKeyBufferCheck(pWindow)==BUFFER_FULL) return;
    if(pWindow->KeyPut==(WINDOW_KEYBUFFER_SIZE-1)){
        pWindow->KeyBuffer[pWindow->KeyPut]=Data;
        pWindow->KeyPut=0;
    }
    else{
        pWindow->KeyBuffer[pWindow->KeyPut]=Data;
        pWindow->KeyPut++;
    }
}

UINT8 WindowKeyBufferGet(WINDOW *pWindow){
    UINT8 Data;

    if(WindowKeyBufferCheck(pWindow)==BUFFER_EMPTY) return 0;
    if(pWindow->KeyGet==(WINDOW_KEYBUFFER_SIZE-1)){
		//GDB : Maybe conversion to uint8 is uncorrect.
        Data=(UINT8)pWindow->KeyBuffer[pWindow->KeyGet];
        pWindow->KeyGet=0;
    }
    else{
		//GDB : Maybe conversion to uint8 is uncorrect.
        Data=(UINT8)pWindow->KeyBuffer[pWindow->KeyGet];
        pWindow->KeyGet++;
    }
    return Data;
}


BOOLEAN WindowMouseBufferCheck(WINDOW *pWindow){
    if(pWindow->MousePut!=pWindow->MouseGet){
        if(pWindow->MousePut==(WINDOW_MOUSEBUFFER_SIZE-1)){
            if(pWindow->MouseGet==0) return BUFFER_FULL;
            else return BUFFER_NOT_EMPTY;
        }
        else{
            if((pWindow->MousePut+1)==pWindow->MouseGet) return BUFFER_FULL;
            else return BUFFER_NOT_EMPTY;
        }
    }
    else return BUFFER_EMPTY;
}

VOID WindowMouseBufferPut(WINDOW *pWindow,UINT32 Data){
    if(WindowMouseBufferCheck(pWindow)==BUFFER_FULL) return;
    if(pWindow->MousePut==(WINDOW_MOUSEBUFFER_SIZE-1)){
        pWindow->MouseBuffer[pWindow->MousePut]=Data;
        pWindow->MousePut=0;
    }
    else{
        pWindow->MouseBuffer[pWindow->MousePut]=Data;
        pWindow->MousePut++;
    }
}

UINT32 WindowMouseBufferGet(WINDOW *pWindow){
    UINT32 Data;

    if(WindowMouseBufferCheck(pWindow)==BUFFER_EMPTY) return 0;
    if(pWindow->MouseGet==(WINDOW_MOUSEBUFFER_SIZE-1)){
        Data=pWindow->MouseBuffer[pWindow->MouseGet];
        pWindow->MouseGet=0;
    }
    else{
        Data=pWindow->MouseBuffer[pWindow->MouseGet];
        pWindow->MouseGet++;
    }
    return Data;
}

BOOLEAN WindowEventBufferCheck(WINDOW *pWindow){
    if(pWindow->EventPut!=pWindow->EventGet){
        if(pWindow->EventPut==(WINDOW_EVENTBUFFER_SIZE-1)){
            if(pWindow->EventGet==0) return BUFFER_FULL;
            else return BUFFER_NOT_EMPTY;
        }
        else{
            if((pWindow->EventPut+1)==pWindow->EventGet) return BUFFER_FULL;
            else return BUFFER_NOT_EMPTY;
        }
    }
    else return BUFFER_EMPTY;
}

VOID WindowEventBufferPut(WINDOW *pWindow,UINT32 Data){
    if(WindowEventBufferCheck(pWindow)==BUFFER_FULL) return;
    if(pWindow->EventPut==(WINDOW_EVENTBUFFER_SIZE-1)){
        pWindow->EventBuffer[pWindow->EventPut]=Data;
        pWindow->EventPut=0;
    }
    else{
        pWindow->EventBuffer[pWindow->EventPut]=Data;
        pWindow->EventPut++;
    }
}

UINT32 WindowEventBufferGet(WINDOW *pWindow){
    UINT32 Data;

    if(WindowEventBufferCheck(pWindow)==BUFFER_EMPTY) return 0;
    if(pWindow->EventGet==(WINDOW_EVENTBUFFER_SIZE-1)){
        Data=pWindow->EventBuffer[pWindow->EventGet];
        pWindow->EventGet=0;
    }
    else{
        Data=pWindow->EventBuffer[pWindow->EventGet];
        pWindow->EventGet++;
    }
    return Data;
}







