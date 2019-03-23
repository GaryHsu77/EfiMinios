#include <includes.h>

DESK_WINDOW_CONTROL DeskWindowCtrl;

VOID DeskWindowInit(VOID){
    DeskWindowCtrl.WindowListChange=FALSE;
    DeskWindowCtrl.ReclickStartButton=FALSE;
    DeskWindowCtrl.MenuWindowList=(WINDOW *)NULL;
    DeskWindowCtrl.WindowListHead=(WINDOW *)NULL;
    DeskWindowCtrl.WindowListTail=(WINDOW *)NULL;
    DeskWindowCtrl.pActiveWindow=(WINDOW *)NULL;
}

VOID DeskWindowWindowListHeadSet(WINDOW *pWindow){
    if(pWindow==(WINDOW *)NULL) return;
    pWindow->Next=(WINDOW *)NULL;
    pWindow->Prev=(WINDOW *)NULL;
    if(StrEqual(pWindow->pTitle,(UINT8*)DeskWorkbarName,7)==FALSE)return;
	
    DeskWindowCtrl.WindowListHead=pWindow;
    if(DeskWindowCtrl.WindowListTail!=(WINDOW *)NULL){
        DeskWindowCtrl.WindowListHead->Next=DeskWindowCtrl.WindowListTail;
        DeskWindowCtrl.WindowListTail->Prev=DeskWindowCtrl.WindowListHead;
    }
    DeskWindowCtrl.pActiveWindow=pWindow;
    DeskWindowCtrl.WindowListChange=TRUE;
    DeskWorkbarCtrl.WindowListChange=TRUE;
}

VOID DeskWindowWindowListTailSet(WINDOW *pWindow){
    if(pWindow==(WINDOW *)NULL) return;
    pWindow->Next=(WINDOW *)NULL;
    pWindow->Prev=(WINDOW *)NULL;
    if(StrEqual(pWindow->pTitle,(UINT8*)DeskWorkWindowName,4)==FALSE)return;
	
    DeskWindowCtrl.WindowListTail=pWindow;
    if(DeskWindowCtrl.WindowListHead!=(WINDOW *)NULL){
        DeskWindowCtrl.WindowListHead->Next=DeskWindowCtrl.WindowListTail;
        DeskWindowCtrl.WindowListTail->Prev=DeskWindowCtrl.WindowListHead;
    }
    DeskWindowCtrl.pActiveWindow=pWindow;
    DeskWindowCtrl.WindowListChange=TRUE;
    DeskWorkbarCtrl.WindowListChange=TRUE;
}

VOID DeskWindowWindowPut(WINDOW *pWindow)
{
    MY_MUTEX mutex;
    
    if(pWindow==(WINDOW *)NULL) return;
    if(DeskWindowCtrl.WindowListHead==(WINDOW *)NULL) return;
    if(DeskWindowCtrl.WindowListTail==(WINDOW *)NULL) return;
    mutex = OsEnterCritical();
    if(DeskWindowCtrl.pActiveWindow!=(WINDOW *)NULL){
        DeskWindowCtrl.pActiveWindow->Active=FALSE;
        DeskWindowCtrl.pActiveWindow->Dirty=TRUE;
    }
    pWindow->Prev=DeskWindowCtrl.WindowListHead;
    pWindow->Next=DeskWindowCtrl.WindowListHead->Next;
    DeskWindowCtrl.WindowListHead->Next->Prev=pWindow;
    DeskWindowCtrl.WindowListHead->Next=pWindow;
    pWindow->Active=TRUE;
    pWindow->Dirty=TRUE;
    DeskWindowCtrl.pActiveWindow=pWindow;
    pWindow->State=DESK_WINDOW_STATE_ONDESK;
    DeskWorkbarWindowListPut(pWindow);
    DeskWindowCtrl.WindowListChange=TRUE;
    DeskWorkbarCtrl.WindowListChange=TRUE;
    DeskActiveWindowCtrl.DirectContentDraw=FALSE;
    OsExitCritical(mutex);
}

VOID DeskWindowWindowDelete(WINDOW *pWindow){
    WINDOW *pWindow2;
    MY_MUTEX mutex;
    
    if(pWindow==(WINDOW *)NULL) return;
    if(DeskWindowCtrl.WindowListHead==(WINDOW *)NULL) return;
    if(DeskWindowCtrl.WindowListTail==(WINDOW *)NULL) return;
    if(DeskWindowCtrl.WindowListHead==pWindow) return;
    if(DeskWindowCtrl.WindowListTail==pWindow) return;
    //make sure window exists
    pWindow2=DeskWindowCtrl.WindowListHead;
    while(pWindow2!=(WINDOW *)NULL){
        if(pWindow2==pWindow) break;
        pWindow2=pWindow2->Next;
    }
    if(pWindow2==(WINDOW *)NULL) return; //window not found
    mutex = OsEnterCritical();
    if(DeskWindowCtrl.MenuWindowList==(WINDOW *)NULL){
        if(DeskWindowCtrl.pActiveWindow==pWindow){
            DeskWindowCtrl.WindowListTail->Active=TRUE;
            DeskWindowCtrl.WindowListTail->Dirty=TRUE;
            DeskWindowCtrl.pActiveWindow=DeskWindowCtrl.WindowListTail;
            pWindow->Prev->Next=pWindow->Next;
            pWindow->Next->Prev=pWindow->Prev;
        }
        else{
            pWindow->Prev->Next=pWindow->Next;
            pWindow->Next->Prev=pWindow->Prev;
        }
        pWindow->Active=FALSE;
        pWindow->State=DESK_WINDOW_STATE_OFFDESK;
        DeskWorkbarWindowListDelete2(pWindow);
        DeskWindowCtrl.WindowListChange=TRUE;
        DeskWorkbarCtrl.WindowListChange=TRUE;
    }
    else{
        pWindow->Prev->Next=pWindow->Next;
        pWindow->Next->Prev=pWindow->Prev;
        //pWindow->Active=FALSE;   //no need this line...window is not active if menu window exists
        pWindow->State=DESK_WINDOW_STATE_OFFDESK;
        DeskWorkbarWindowListDelete2(pWindow);
        DeskWindowCtrl.WindowListChange=TRUE;
        DeskWorkbarCtrl.WindowListChange=TRUE;
    }
    OsExitCritical(mutex);
}

VOID DeskWindowActiveWindowSet(WINDOW *pWindow){
    WINDOW *pWindow2;
    MY_MUTEX mutex;
    
    if(pWindow==(WINDOW *)NULL) return;
    if(DeskWindowCtrl.WindowListHead==(WINDOW *)NULL) return;
    if(DeskWindowCtrl.WindowListTail==(WINDOW *)NULL) return;
    if(pWindow==DeskWindowCtrl.pActiveWindow) return;
    //if(DeskWindowCtrl.MenuWindowList!=(WINDOW *)NULL) return;
    mutex = OsEnterCritical();
    if(DeskWindowCtrl.pActiveWindow!=(WINDOW *)NULL){
        DeskWindowCtrl.pActiveWindow->Active=FALSE;
        DeskWindowCtrl.pActiveWindow->Dirty=TRUE;
        DeskWindowCtrl.pActiveWindow=(WINDOW *)NULL;
        DeskWindowCtrl.WindowListChange=TRUE;
        DeskWorkbarCtrl.WindowListChange=TRUE;
    }
    if(pWindow->Type==WINDOW_TYPE_STARTMENU){
        pWindow->Active=TRUE;        
        pWindow->Dirty=TRUE;
        DeskWindowCtrl.pActiveWindow=pWindow;
        DeskWindowCtrl.WindowListChange=TRUE;
        DeskWorkbarCtrl.WindowListChange=TRUE;
        OsExitCritical(mutex);
        return;
    }
    pWindow2=DeskWindowCtrl.WindowListHead;
    while(pWindow2!=(WINDOW *)NULL){
        if(pWindow2==pWindow){
            if(pWindow2==DeskWindowCtrl.WindowListHead); //skip head is alwayse head
            else if(pWindow2==DeskWindowCtrl.WindowListTail); // skip tail is alwayse tail
            else{
                //rearrange window position in window list
                pWindow2->Prev->Next=pWindow2->Next;
                pWindow2->Next->Prev=pWindow2->Prev;
                pWindow2->Prev=DeskWindowCtrl.WindowListHead;
                pWindow2->Next=DeskWindowCtrl.WindowListHead->Next;
                DeskWindowCtrl.WindowListHead->Next->Prev=pWindow2;
                DeskWindowCtrl.WindowListHead->Next=pWindow2;
            }
            pWindow2->DisplayType=DESK_WINDOW_STATUS_NORMAL;
            pWindow2->Active=TRUE;        
            pWindow2->Dirty=TRUE;
            DeskWindowCtrl.pActiveWindow=pWindow2;
            DeskWindowCtrl.WindowListChange=TRUE;
            DeskWorkbarCtrl.WindowListChange=TRUE;
            OsExitCritical(mutex);
            return;
        }
        pWindow2=pWindow2->Next;

    }
    OsExitCritical(mutex);
}

WINDOW *DeskWindowActiveWindowGet(VOID){
    return DeskWindowCtrl.pActiveWindow;
}

BOOLEAN DeskWindowActiveWindowContentCheck(VOID){
    WINDOW_TABLE *pTable;
    WINDOW_DEVICE *pDevice;
    
    if(DeskWindowCtrl.pActiveWindow==(WINDOW *)NULL) return FALSE;
    if(DeskWindowCtrl.pActiveWindow->Dirty==TRUE) return TRUE;
    pTable=DeskWindowCtrl.pActiveWindow->UserTableList;
    while(pTable!=(WINDOW_TABLE *)NULL){
        pDevice=pTable->DeviceList;
        while(pDevice!=(WINDOW_DEVICE *)NULL){
            if(DeskDeviceDirtyCheck(pDevice)==TRUE) return TRUE;
            pDevice=pDevice->Next;
        }
        pTable=pTable->Next;
    }
    return FALSE;
}

BOOLEAN DeskWindowInactiveWindowContentCheck(VOID){
    WINDOW *pWindow;
    WINDOW_TABLE *pTable;
    WINDOW_DEVICE *pDevice;
                     	
    if(DeskWindowCtrl.MenuWindowList!=(WINDOW *)NULL){
        pWindow=DeskWindowCtrl.MenuWindowList; // head is workbar,no check workbar here.
        while(pWindow!=(WINDOW *)NULL){
            if(pWindow==DeskWindowCtrl.pActiveWindow);
            else{
                if(pWindow->Dirty==TRUE) return TRUE;
                pTable=pWindow->UserTableList;
                while(pTable!=(WINDOW_TABLE *)NULL){
                    pDevice=pTable->DeviceList;
                    while(pDevice!=(WINDOW_DEVICE *)NULL){
                        if(DeskDeviceDirtyCheck(pDevice)==TRUE) return TRUE;
                        pDevice=pDevice->Next;
                    }
                    pTable=pTable->Next;
                }
            }
            pWindow=pWindow->Next;
        }    
    }
    
    pWindow=DeskWindowCtrl.WindowListHead->Next; // head is workbar,no check workbar here.
    while(pWindow!=(WINDOW *)NULL){
        if(pWindow==DeskWindowCtrl.pActiveWindow);
        else if(pWindow->DisplayType==DESK_WINDOW_STATUS_HIDE);
        else{
            if(pWindow->Dirty==TRUE) return TRUE;
            pTable=pWindow->UserTableList;
            while(pTable!=(WINDOW_TABLE *)NULL){
                pDevice=pTable->DeviceList;
                while(pDevice!=(WINDOW_DEVICE *)NULL){
                    if(DeskDeviceDirtyCheck(pDevice)==TRUE) return TRUE;
                    pDevice=pDevice->Next;
                }
                pTable=pTable->Next;
            }
        }
        pWindow=pWindow->Next;
    }
    return FALSE;
}

BOOLEAN DeskWindowWindowListCheck(VOID){
    if(DeskWindowCtrl.WindowListChange==TRUE){
        DeskWindowCtrl.WindowListChange=FALSE;
        return TRUE;
    }
    else return FALSE;
}

VOID DeskWindowInactiveWindowDraw(VOID)
{
    WINDOW *pWindow;

    DeskWorkWindowMemoryDraw();                   // redraw work area window first
    pWindow=DeskWindowCtrl.WindowListTail->Prev;  // skip desk window
    while(pWindow!=(WINDOW *)NULL){            
        if(pWindow==DeskWindowCtrl.pActiveWindow); //skip active window
        else if(pWindow==DeskWindowCtrl.WindowListHead); //skip workbar
        else if(pWindow->DisplayType==DESK_WINDOW_STATUS_HIDE);
        else{
            DeskInactiveWindowMemoryDraw(pWindow);
            DeskInactiveWindowMemory2WorkWindowUpdate(pWindow);
        }
        pWindow=pWindow->Prev;
    }
    if(DeskWindowCtrl.MenuWindowList==(WINDOW *)NULL) return;
    pWindow=DeskWindowCtrl.MenuWindowList;
    while(pWindow!=(WINDOW *)NULL){
        if(pWindow!=DeskWindowCtrl.pActiveWindow){
            DeskInactiveWindowMemoryDraw(pWindow);
            DeskInactiveWindowMemory2WorkWindowUpdate(pWindow);
        }
        pWindow=pWindow->Next;
    }
}

// this function is use by workbar window select
VOID DeskWindowActiveWindowToggle(WINDOW *pWindow)
{ 
    MY_MUTEX mutex;
    
    if(pWindow==DeskWindowCtrl.WindowListTail) return;
    if(pWindow==DeskWindowCtrl.WindowListHead) return;
    mutex = OsEnterCritical();
    if((pWindow->DisplayType!=DESK_WINDOW_STATUS_HIDE)   
     &&(pWindow==DeskWindowCtrl.WindowListHead->Next)){  
        //if window is active and not hide on desk,set window to hide.
        //DeskWindowCtrl.WindowListHead->Active=FALSE;
        //pWindow->Active=FALSE;
        //pWindow->Dirty=TRUE;
        pWindow->DisplayType=DESK_WINDOW_STATUS_HIDE;
        DeskWindowCtrl.WindowListChange=TRUE;
        DeskWorkbarCtrl.WindowListChange=TRUE;
    }
    else if(pWindow->DisplayType!=DESK_WINDOW_STATUS_HIDE){
        //if window not active and not hide on desk,set window to active.
        DeskWindowCtrl.WindowListHead->Active=FALSE;
        
        pWindow->Prev->Next=pWindow->Next;
        pWindow->Next->Prev=pWindow->Prev;
        pWindow->Prev=DeskWindowCtrl.WindowListHead;
        pWindow->Next=DeskWindowCtrl.WindowListHead->Next;
        DeskWindowCtrl.WindowListHead->Next->Prev=pWindow;
        DeskWindowCtrl.WindowListHead->Next=pWindow;
        pWindow->Active=TRUE;
        pWindow->Dirty=TRUE;
        pWindow->DisplayType=DESK_WINDOW_STATUS_NORMAL;
        DeskWindowCtrl.pActiveWindow=pWindow;
        DeskWindowCtrl.WindowListChange=TRUE;
        DeskWorkbarCtrl.WindowListChange=TRUE;
    }
    else if(pWindow->DisplayType==DESK_WINDOW_STATUS_HIDE){
        DeskWindowCtrl.WindowListHead->Active=FALSE;
        //set window as active general window
        pWindow->Prev->Next=pWindow->Next;
        pWindow->Next->Prev=pWindow->Prev;
        pWindow->Prev=DeskWindowCtrl.WindowListHead;
        pWindow->Next=DeskWindowCtrl.WindowListHead->Next;
        DeskWindowCtrl.WindowListHead->Next->Prev=pWindow;
        DeskWindowCtrl.WindowListHead->Next=pWindow;
        pWindow->Active=TRUE;
        pWindow->Dirty=TRUE;
        pWindow->DisplayType=DESK_WINDOW_STATUS_NORMAL;
        DeskWindowCtrl.pActiveWindow=pWindow;
        DeskWindowCtrl.WindowListChange=TRUE;
        DeskWorkbarCtrl.WindowListChange=TRUE;
    }
    OsExitCritical(mutex);
}

BOOLEAN DeskWindowWindowCheck(WINDOW *pWindow)
{
    WINDOW *pWindow2;
    
    pWindow2=DeskWindowCtrl.WindowListHead;
    while(pWindow2!=(WINDOW *)NULL){
        if(pWindow2==pWindow) return TRUE;
        pWindow2=pWindow2->Next;
    }
    return FALSE;
}

VOID DeskWindowWindowHideSet(WINDOW *pWindow){
    WINDOW *pWindow2;
    
    if(pWindow==(WINDOW *)NULL) return;
    if(pWindow==DeskWindowCtrl.WindowListHead) return;
    if(pWindow==DeskWindowCtrl.WindowListTail) return;
    pWindow->Active=FALSE;
    pWindow->Dirty=TRUE;
    pWindow->DisplayType=DESK_WINDOW_STATUS_HIDE;
    pWindow2=pWindow->Next;
    while(pWindow2!=DeskWindowCtrl.WindowListTail){
        if(pWindow2->DisplayType!=DESK_WINDOW_STATUS_HIDE) break;
        pWindow2=pWindow2->Next;
    }
    if(pWindow2==DeskWindowCtrl.WindowListTail){
        //CaptionStringPrint(&DeskDebugCtrl.Console.Caption,"\n meet tail");    
        DeskWindowCtrl.WindowListTail->Active=TRUE;
        DeskWindowCtrl.WindowListTail->Dirty=TRUE;
        DeskWindowCtrl.pActiveWindow=DeskWindowCtrl.WindowListTail;
        DeskWindowCtrl.WindowListChange=TRUE;
        DeskWorkbarCtrl.WindowListChange=TRUE;
    }
    else{
        //CaptionStringPrint(&DeskDebugCtrl.Console.Caption,"\n has next window");
        pWindow2->Prev->Next=pWindow2->Next;
        pWindow2->Next->Prev=pWindow2->Prev;
        pWindow2->Prev=DeskWindowCtrl.WindowListHead;
        pWindow2->Next=DeskWindowCtrl.WindowListHead->Next;
        DeskWindowCtrl.WindowListHead->Next->Prev=pWindow2;
        DeskWindowCtrl.WindowListHead->Next=pWindow2;
        pWindow2->Active=TRUE;
        pWindow2->Dirty=TRUE;
        DeskWindowCtrl.pActiveWindow=pWindow2;
        DeskWindowCtrl.WindowListChange=TRUE;
        DeskWorkbarCtrl.WindowListChange=TRUE;
    }
}

VOID DeskWindowActiveWindowDelete(WINDOW *pWindow){
    if(DeskWindowCtrl.WindowListHead==(WINDOW *)NULL) return;
    if(DeskWindowCtrl.WindowListTail==(WINDOW *)NULL) return;
    if(pWindow==DeskWindowCtrl.WindowListHead) return;
    if(pWindow==DeskWindowCtrl.WindowListTail) return;
    if(DeskWindowWindowCheck(pWindow)==FALSE) return;
    pWindow->Prev->Next=pWindow->Next;   //delete from desk
    pWindow->Next->Prev=pWindow->Prev;   //delete from workbar window device list
    pWindow->Active=FALSE;
    pWindow->State=DESK_WINDOW_STATE_OFFDESK;
    DeskWindowCtrl.pActiveWindow=DeskWindowCtrl.WindowListTail;
    DeskWindowCtrl.WindowListChange=TRUE;
    DeskWorkbarCtrl.WindowListChange=TRUE;
    DeskWorkbarWindowListDelete(pWindow);
    //CaptionStringPrint(&DeskDebugCtrl.Console.Caption,"\n window deleted.");
    //todo:find next active window on desk
}


WINDOW *DeskWindowMousePositionWindowGet(GRAPHIC_POSITION *pPosition){
    WINDOW *pWindow;
    MY_MUTEX mutex;
    if(pPosition==(GRAPHIC_POSITION *)NULL) return (WINDOW *)NULL;
    if(DeskWindowCtrl.WindowListHead==(WINDOW *)NULL) return (WINDOW *)NULL;
    if(DeskWindowCtrl.WindowListTail==(WINDOW *)NULL) return (WINDOW *)NULL;
    mutex = OsEnterCritical();
    if(DeskWindowCtrl.MenuWindowList!=(WINDOW *)NULL){
        pWindow=DeskWindowCtrl.MenuWindowList;
        while(pWindow!=(WINDOW *)NULL){
            if(((pWindow->DisplayArea.X+pWindow->DisplayArea.W)>pPosition->X)
              &&((pWindow->DisplayArea.Y+pWindow->DisplayArea.H)>pPosition->Y)
              &&(pWindow->DisplayArea.X<=pPosition->X)
              &&(pWindow->DisplayArea.Y<=pPosition->Y)){
                OsExitCritical(mutex);
                return pWindow;
            }
            pWindow=pWindow->Next;
        }
    }
    pWindow=DeskWindowCtrl.WindowListHead;
    while(pWindow!=(WINDOW *)NULL){
        if(pWindow->DisplayType==DESK_WINDOW_STATUS_HIDE) pWindow=pWindow->Next;
        else{
            if(((pWindow->DisplayArea.X+pWindow->DisplayArea.W)>pPosition->X)
              &&((pWindow->DisplayArea.Y+pWindow->DisplayArea.H)>pPosition->Y)
              &&(pWindow->DisplayArea.X<=pPosition->X)
              &&(pWindow->DisplayArea.Y<=pPosition->Y)){
                OsExitCritical(mutex);
                return pWindow;
            }
            pWindow=pWindow->Next;
        }
    }
    OsExitCritical(mutex);
    return (WINDOW *)NULL;
}

VOID DeskWindowMousePositionInfomationGet(GRAPHIC_POSITION *pPosition)
{
    WINDOW *pWindow;
    WINDOW_TABLE *pTable;
    WINDOW_DEVICE *pDevice;
    GRAPHIC_POSITION Position;
    GRAPHIC_POSITION DevicePosition;
    MY_MUTEX mutex;
    
    if(pPosition==(GRAPHIC_POSITION *)NULL) return;
    if(DeskWindowCtrl.WindowListHead==(WINDOW *)NULL) return;
    if(DeskWindowCtrl.WindowListTail==(WINDOW *)NULL) return;
    mutex = OsEnterCritical();
    pWindow=(WINDOW *)NULL;
    if(DeskWindowCtrl.MenuWindowList!=(WINDOW *)NULL){
        pWindow=DeskWindowCtrl.MenuWindowList;
        while(pWindow!=(WINDOW *)NULL){
            if(DesklibAreaPositionCheck(&pWindow->DisplayArea,pPosition)==TRUE) break;
            pWindow=pWindow->Next;
        }
    }
    if(pWindow==(WINDOW *)NULL){
        pWindow=DeskWindowCtrl.WindowListHead;
        while(pWindow!=(WINDOW *)NULL){
            if(pWindow->DisplayType==DESK_WINDOW_STATUS_HIDE);
            else if(DesklibAreaPositionCheck(&pWindow->DisplayArea,pPosition)==TRUE) break;
            pWindow=pWindow->Next;
        }
    }
    OsExitCritical(mutex);
    DeskMouseCtrl.pWindow=(WINDOW *)NULL;
    DeskMouseCtrl.pTable=(WINDOW_TABLE *)NULL;
    DeskMouseCtrl.pDevice=(WINDOW_DEVICE *)NULL;
    DeskMouseCtrl.MouseCursorType=DESK_MOUSE_CURSOR_NORMAL;
    if(pWindow==(WINDOW *)NULL) return; // this case should never happen
    DeskMouseCtrl.pWindow=pWindow;
    if(pWindow==DeskWindowCtrl.WindowListHead){
        Position.X=pPosition->X-pWindow->DisplayArea.X;
        Position.Y=pPosition->Y-pWindow->DisplayArea.Y;
        pTable=pWindow->UserTableList;
        while(pTable!=(WINDOW_TABLE *)NULL){
            if(DesklibAreaPositionCheck(&pTable->Area,&Position)==TRUE){
                DeskMouseCtrl.pTable=pTable;
                pDevice=pTable->DeviceList;
                DevicePosition.X=Position.X-pTable->Area.X;
                DevicePosition.Y=Position.Y-pTable->Area.Y;
                while(pDevice!=(WINDOW_DEVICE *)NULL){
                    if(DeskDeviceAreaPositionCheck(pDevice,&DevicePosition)==TRUE){
                        DeskMouseCtrl.pDevice=pDevice;
                        return;
                    }
                    pDevice=pDevice->Next;
                }
                DeskMouseCtrl.pDevice=(WINDOW_DEVICE *)NULL;
                return;
            }
            pTable=pTable->Next;
        }
        DeskMouseCtrl.pTable=(WINDOW_TABLE *)NULL;
        DeskMouseCtrl.pDevice=(WINDOW_DEVICE *)NULL;
        return;
    }
    if(pWindow==DeskWindowCtrl.WindowListTail){
        DeskMouseCtrl.pTable=(WINDOW_TABLE *)NULL;
        DeskMouseCtrl.pDevice=(WINDOW_DEVICE *)NULL;
        return;
    }
    Position.X=pPosition->X-pWindow->DisplayArea.X;
    Position.Y=pPosition->Y-pWindow->DisplayArea.Y;
    if((DesklibAreaPositionCheck(&pWindow->Outline.OuterArea,&Position)==TRUE)
     &&(DesklibAreaPositionCheck(&pWindow->Outline.InnerArea,&Position)==FALSE)){
        //CaptionStringPrint(&DeskDebugCtrl.Caption,"outline.");
        DeskMouseCtrl.pTable=&pWindow->OutlineTable;
        pDevice=pWindow->OutlineTable.DeviceList;
        while(pDevice!=(WINDOW_DEVICE *)NULL){
        	//CaptionStringPrint(&DeskDebugCtrl.Caption,"edge.");
            if(DeskDeviceAreaPositionCheck(pDevice,&Position)==TRUE){
                DeskMouseCtrl.pDevice=pDevice;
                switch(((WINDOW_EDGE *)pDevice->pDevice)->Type){
                    case WINDOW_EDGE_TOP:
                        DeskMouseCtrl.MouseCursorType=DESK_MOUSE_CURSOR_UP;
                        break;
                    case WINDOW_EDGE_BOTTOM:
                        DeskMouseCtrl.MouseCursorType=DESK_MOUSE_CURSOR_DOWN;
                        break;
                    case WINDOW_EDGE_RIGHT:
                        DeskMouseCtrl.MouseCursorType=DESK_MOUSE_CURSOR_RIGHT;
                        break;
                    case WINDOW_EDGE_LEFT:
                        DeskMouseCtrl.MouseCursorType=DESK_MOUSE_CURSOR_LEFT;
                        break;
                    case WINDOW_EDGE_TOPLEFT:
                        DeskMouseCtrl.MouseCursorType=DESK_MOUSE_CURSOR_LEFTUP;
                        break;
                    case WINDOW_EDGE_TOPRIGHT:
                        DeskMouseCtrl.MouseCursorType=DESK_MOUSE_CURSOR_RIGHTUP;
                        break;
                    case WINDOW_EDGE_BOTTOMLEFT:
                        DeskMouseCtrl.MouseCursorType=DESK_MOUSE_CURSOR_LEFTDOWN;
                        break;
                    case WINDOW_EDGE_BOTTOMRIGHT:
                        DeskMouseCtrl.MouseCursorType=DESK_MOUSE_CURSOR_RIGHTDOWN;
                        break;
                    case WINDOW_EDGE_LEFTTOP:
                        DeskMouseCtrl.MouseCursorType=DESK_MOUSE_CURSOR_LEFTUP;
                        break;
                    case WINDOW_EDGE_RIGHTTOP:
                        DeskMouseCtrl.MouseCursorType=DESK_MOUSE_CURSOR_RIGHTUP;
                        break;
                }
                return;
            }
            pDevice=pDevice->Next;
        }
        DeskMouseCtrl.pDevice=(WINDOW_DEVICE *)NULL;
        return;
    }
    if(DesklibAreaPositionCheck(&pWindow->HeaderTable.Area,&Position)==TRUE){
        DeskMouseCtrl.pTable=&pWindow->HeaderTable;
        pDevice=pWindow->HeaderTable.DeviceList;
        DevicePosition.X=Position.X-DeskMouseCtrl.pTable->Area.X;
        DevicePosition.Y=Position.Y-DeskMouseCtrl.pTable->Area.Y;
        while(pDevice!=(WINDOW_DEVICE *)NULL){
            if(DeskDeviceAreaPositionCheck(pDevice,&DevicePosition)==TRUE){
                DeskMouseCtrl.pDevice=pDevice;
                return;
            }
            pDevice=pDevice->Next;
        }
        DeskMouseCtrl.pDevice=(WINDOW_DEVICE *)NULL;
        return;
    }
    pTable=pWindow->UserTableList;
    while(pTable!=(WINDOW_TABLE *)NULL){
        if(DesklibAreaPositionCheck(&pTable->Area,&Position)==TRUE){
            DeskMouseCtrl.pTable=pTable;
            pDevice=pTable->DeviceList;
            DevicePosition.X=Position.X-pTable->Area.X;
            DevicePosition.Y=Position.Y-pTable->Area.Y;
            while(pDevice!=(WINDOW_DEVICE *)NULL){
                if(DeskDeviceAreaPositionCheck(pDevice,&DevicePosition)==TRUE){
                    DeskMouseCtrl.pDevice=pDevice;
                    return;
                }
                pDevice=pDevice->Next;
            }
            DeskMouseCtrl.pDevice=(WINDOW_DEVICE *)NULL;
            return;
        }
        pTable=pTable->Next;
    }
    DeskMouseCtrl.pTable=(WINDOW_TABLE *)NULL;
    DeskMouseCtrl.pDevice=(WINDOW_DEVICE *)NULL;
    return;
}