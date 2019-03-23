#include <includes.h>

#define MouseIdleState 0
#define MouseStatusByteState 1
#define MouseXmovementState 2
#define MouseYmovementState 3
#define MouseZmovementState 4

const UINT8 MouseDriverName[]="DRIVER_MOUSE";
MOUSE_CONTROL *pOsDriverMouse;
MouseAccumulatorX = 0;
MouseAccumulatorY = 0;
const static Sensitive = 25;
VOID MouseInit(VOID)
{
	EFI_STATUS Status;
    
	Status = gBS->AllocatePool(EfiBootServicesData,sizeof(MOUSE_CONTROL),&pOsDriverMouse);
	if(Status != EFI_SUCCESS)return;
    //PicIrqDisable(IRQ12_MOUSE);
    pOsDriverMouse->Put=0;
    pOsDriverMouse->Get=0;
	Status = gBS->AllocatePool(EfiBootServicesData,MOUSE_KEYBUFFER_SZIE*sizeof(EFI_SIMPLE_POINTER_STATE),&(pOsDriverMouse->pDataBuffer));
	if(Status != EFI_SUCCESS)return;
    if(pOsDriverMouse->pDataBuffer!=(EFI_SIMPLE_POINTER_STATE *)NULL) pOsDriverMouse->BufferStatus=BUFFER_GOOD;
    else pOsDriverMouse->BufferStatus=BUFFER_FAIL;
    OsEventAdd(&pOsDriverMouse->MouseEvent,(UINT8 *)&MouseDriverName,OS_EVENT_MOUSE);
    //InterruptIrqHandlerSet(IRQ12_MOUSE,MouseHandler);
    pOsDriverMouse->State=MouseStatusByteState;
    //PicIrqEnable(IRQ12_MOUSE);
	
	SystemGuiStringPrint(L">>> Mouse init end <<<<<<<<<<\n");
}

INT32 GetTextX( IN INT32 GuidX )
{
  MouseAccumulatorX+=(GuidX*Sensitive/((INT32) SPP->Mode->ResolutionX));
  if(MouseAccumulatorX<0) MouseAccumulatorX = 0;
  if(MouseAccumulatorX+5>(INT32)OsdCtrl.ScreenArea.W) MouseAccumulatorX = OsdCtrl.ScreenArea.W-5;
  return MouseAccumulatorX;
}

INT32 GetTextY ( IN INT32 GuidY )
{
  MouseAccumulatorY+=(GuidY*Sensitive/((INT32) SPP->Mode->ResolutionY));
  if(MouseAccumulatorY<0) MouseAccumulatorY = 0;
  if(MouseAccumulatorY+5>(INT32)OsdCtrl.ScreenArea.H) MouseAccumulatorY = OsdCtrl.ScreenArea.H-5;
  return MouseAccumulatorY;
}

BOOLEAN MouseDataScan()
{
	EFI_SIMPLE_POINTER_STATE pointStatus;
	if(SPP->GetState(SPP, &pointStatus)==EFI_SUCCESS){
		MouseBufferPutIsr(pointStatus);
		//gST->ConOut->SetCursorPosition(gST->ConOut,0,0);
		//GDP(L"%d, %d\n", GetTextX(pointStatus.RelativeMovementX), GetTextY(pointStatus.RelativeMovementY));
		//GDP(L"%d, %d\n", pOsDriverMouse->Put, pOsDriverMouse->Get);
	}
	return FALSE;
}

VOID MouseEnable(VOID)
{
    //PicIrqDisable(IRQ12_MOUSE);
    if(pOsDriverKeyboard!=(KEYBOARD_CONTROL *)NULL) pOsDriverKeyboard->Ack=FALSE;
	KeyboardBusyWait();
	OutByte(KB_CMD_REG,KB_CMD_WRITE_MOUSE);
    KeyboardAckWait();
	if(pOsDriverKeyboard!=(KEYBOARD_CONTROL *)NULL) pOsDriverKeyboard->Ack=FALSE;
	KeyboardBusyWait();
	OutByte(KB_DATA_REG,MOUSE_CMD_ENABLE_DATA); 
    KeyboardAckWait();
    //PicIrqEnable(IRQ12_MOUSE);	
}

VOID MouseHandler(VOID){
}

UINT8 MouseBufferCheckIsr(VOID){
    if(pOsDriverMouse->Put!=pOsDriverMouse->Get){
        if(pOsDriverMouse->Put==(MOUSE_KEYBUFFER_SZIE-1)){
            if(pOsDriverMouse->Get==0) return BUFFER_FULL;
            else return BUFFER_NOT_EMPTY;
        }
        else{
            if((pOsDriverMouse->Put+1)==pOsDriverMouse->Get) return BUFFER_FULL;
            else return BUFFER_NOT_EMPTY;
        }
    }
    else return BUFFER_EMPTY;
}

UINT8 MouseBufferCheck(VOID){
    if(pOsDriverMouse->Put!=pOsDriverMouse->Get){
        if(pOsDriverMouse->Put==(MOUSE_KEYBUFFER_SZIE-1)){
            if(pOsDriverMouse->Get==0) return BUFFER_FULL;
            else return BUFFER_NOT_EMPTY;
        }
        else{
            if((pOsDriverMouse->Put+1)==pOsDriverMouse->Get) return BUFFER_FULL;
            else return BUFFER_NOT_EMPTY;
        }
    }
    else return BUFFER_EMPTY;
}

VOID MouseBufferPutIsr(EFI_SIMPLE_POINTER_STATE Data){
	if(pOsDriverMouse->BufferStatus==BUFFER_FAIL)return;
    if(MouseBufferCheckIsr()==BUFFER_FULL)return;
    if(pOsDriverMouse->Put==(MOUSE_KEYBUFFER_SZIE-1)){
        pOsDriverMouse->pDataBuffer[pOsDriverMouse->Put]=Data;
        pOsDriverMouse->Put=0;
    }
    else{
        pOsDriverMouse->pDataBuffer[pOsDriverMouse->Put]=Data;
        pOsDriverMouse->Put++;
    }
}

EFI_SIMPLE_POINTER_STATE MouseBufferGet(VOID)
{
    EFI_SIMPLE_POINTER_STATE Data;

	if(pOsDriverMouse->BufferStatus==BUFFER_FAIL) return Data;
    if(MouseBufferCheck()==BUFFER_EMPTY) return Data;
    if(pOsDriverMouse->Get==(MOUSE_KEYBUFFER_SZIE-1)){
        Data=pOsDriverMouse->pDataBuffer[pOsDriverMouse->Get];
        pOsDriverMouse->Get=0;
    }
    else{
        Data=pOsDriverMouse->pDataBuffer[pOsDriverMouse->Get];
        pOsDriverMouse->Get++;
    }
    return Data;
}

