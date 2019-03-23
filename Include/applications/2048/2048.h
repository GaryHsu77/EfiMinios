#ifndef G2048_H
#define G2048_H

#define G2048_WINDOW_WIDTH  450
#define G2048_WINDOW_HEIGHT 500

#define BLK_NUM_MAX 16
#define BEE_BEES_TIME 100 

#define BLK_WIDTH  100
#define BLK_HEIGHT 100

#define Task2048IdleState 0
#define Task2048RunState  1
#define Task2048StopState 2

#define G2048IdleState    0
#define G2048InitialState 1
#define G2048RunState     2
#define G2048CloseState   3

#define G2048_WDN_BOARD         WINDOW_WDN_USERDEVICE
#define G2048_WDN_RESTARTBUTTON (WINDOW_WDN_USERDEVICE+1)
#define G2048_WDN_CLOSEBUTTON   (WINDOW_WDN_USERDEVICE+2)

typedef struct g2048_control{
    GRAPHIC_AREA CurrentArea;
    GRAPHIC_AREA PreviousArea;
    GRAPHIC_GFX BlksGfx;
    UINT32 BlkMemoryLength;
    UINT8 SwingStatus;
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL *RecoveryMemory;
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL *GraphicMemory;
    struct g2048_control *Prev;
    struct g2048_control *Next;
}GAME2048_BLK;

typedef struct{
    UINT8 TaskState;
    UINT8 State;
    UINT8 Dirty;
    //UINT8 HitNumber;
    //UINT8 BeeCurrentPath;
    //UINT8 BeePreviousPath;
    //UINT8 FlyStep;
    //UINT8 HitCheck;
    UINT8 GameOver;
    UINT32 WindowEvent;
    
    GAME2048_BLK *BlkList;
    GAME2048_BLK BLKs[BLK_NUM_MAX];
    GAME2048_BLK *pCurrentBlk;

    WINDOW_BUTTON RestartButton;
    WINDOW_DEVICE WdRestartButton;
    WINDOW_BUTTON CloseButton;
    WINDOW_DEVICE WdCloseButton;
    BOARD Board;
    WINDOW_DEVICE WdBoard;
    WINDOW_TABLE UserTable;
    WINDOW Window;
}GAME2048_CONTROL;

VOID Task2048(VOID);
VOID Game2048Svc(GAME2048_CONTROL *p2048gameCtrl);
VOID Game2048Init(GAME2048_CONTROL *p2048gameCtrl);
VOID Game2048EventHandler(GAME2048_CONTROL *p2048gameCtrl);

extern const UINT8 Task2048Name[];

#endif
