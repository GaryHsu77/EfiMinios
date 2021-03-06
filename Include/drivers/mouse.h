#ifndef MOUSE_H
#define MOUSE_H

#define MOUSE_STATUS_LEFTBUTTON 0x01
#define MOUSE_STATUS_RIGHTBUTTON 0x02
#define MOUSE_STATUS_MIDDLEBUTTON 0x04
#define MOUSE_STATUS_FIXONE 0x08
#define MOUSE_STATUS_XSIGN 0x10
#define MOUSE_STATUS_YSIGN 0x20
#define MOUSE_STATUS_XOVERFLOW 0x40
#define MOUSE_STATUS_YOVERFLOW 0x80

#define MOUSE_CMD_RESET 0xff
#define MOUSE_CMD_RESEND 0xfe
#define MOUSE_CMD_SETDEFAULT 0xf6
#define MOUSE_CMD_DISABLE_DATA 0xf5
#define MOUSE_CMD_ENABLE_DATA 0xf4
#define MOUSE_CMD_SET_SAMPLERATE 0xf3
#define MOUSE_CMD_GET_DEVICEID 0xf2
#define MOUSE_CMD_SET_REMOTEMODE 0xf0
#define MOUSE_CMD_SET_WRAPMODE 0xee 
#define MOUSE_CMD_RESET_WRAPMODE 0xec
#define MOUSE_CMD_READ_DATA 0xeb
#define MOUSE_CMD_SET_STREAMMODE 0xea
#define MOUSE_CMD_STATUS_REQUEST 0xe9
#define MOUSE_CMD_SET_RESOLUTION 0xe8
#define MOUSE_CMD_SET_SCALING2 0xe7
#define MOUSE_CMD_SET_SCALING1 0xe6

#define MOUSE_KEYBUFFER_SZIE 10

#define MOUSE_DIRECTION_LEFT  0
#define MOUSE_DIRECTION_RIGHT 1
#define MOUSE_DIRECTION_UP    2
#define MOUSE_DIRECTION_DOWN  3

typedef struct{
    UINT8 State;
    UINT8 BufferStatus;
    UINT8 Put;
    UINT8 Get;
    EFI_SIMPLE_POINTER_STATE *pDataBuffer;
    UN_UL MouseSignal;
    OS_EVENT MouseEvent;
}MOUSE_CONTROL;

extern MOUSE_CONTROL *pOsDriverMouse;

VOID MouseInit(VOID);
VOID MouseEnable(VOID);
VOID MouseSvc(VOID);
BOOLEAN MouseDataScan();
VOID MouseHandler(VOID);
UINT8 MouseBufferCheckIsr(VOID);
UINT8 MouseBufferCheck(VOID);
VOID MouseBufferPutIsr(EFI_SIMPLE_POINTER_STATE Data);
EFI_SIMPLE_POINTER_STATE MouseBufferGet(VOID);
INT32 GetTextX( IN INT32 GuidX );
INT32 GetTextY ( IN INT32 GuidY );
#endif