#ifndef BEE_H
#define BEE_H

#define BEE_WINDOW_WIDTH  200
#define BEE_WINDOW_HEIGHT 155

//bee fighter
#define BEE_FIGHTER_WIDTH 11
#define BEE_FIGHTER_HEIGHT 9 //5

typedef struct{
    GRAPHIC_AREA CurrentArea;
    GRAPHIC_AREA PreviousArea;
    GRAPHIC_GFX FighterGfx;
    UINT32 FighterMemoryLength;
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL *RecoveryMemory;
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL *GraphicMemory;
    UINT8 FighterDirty;
}BEEGAME_FIGHTER;


//bee bullet
#define BEE_BULLET_TIME 20 

#define BEE_BULLET_WIDTH 1
#define BEE_BULLET_HEIGHT 2

typedef struct beebullet_control{
    GRAPHIC_AREA CurrentArea;
    GRAPHIC_AREA PreviousArea;
    GRAPHIC_GFX BulletGfx;
    UINT32 BulletMemoryLength;
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL *RecoveryMemory;
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL *GraphicMemory;
    struct beebullet_control *Prev;
    struct beebullet_control *Next;
}BEEGAME_BULLET;

//bees
#define BEE_BEES_TIME 100 

#define BEE_BEES_WIDTH  15
#define BEE_BEES_HEIGHT 9

#define BEE_BEES_SWINGUP   0
#define BEE_BEES_SWINGDOWN 1
#define BEE_BEES_SWINGOFF  2

typedef struct beebees_control{
    GRAPHIC_AREA CurrentArea;
    GRAPHIC_AREA PreviousArea;
    GRAPHIC_GFX BeesGfx;
    UINT32 BeesMemoryLength;
    UINT8 SwingStatus;
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL *RecoveryMemory;
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL *GraphicMemory;
    struct beebees_control *Prev;
    struct beebees_control *Next;
}BEEGAME_BEE;

#define BeetaskIdleState 0
#define BeetaskRunState  1
#define BeetaskStopState 2

#define BeeIdleState    0
#define BeeInitialState 1
#define BeeRunState     2
#define BeeCloseState   3

#define BBE_BULLET_MAX 10
#define BBE_BEES_MAX   5

#define BEE_WDN_BOARD         WINDOW_WDN_USERDEVICE
#define BEE_WDN_RESTARTBUTTON (WINDOW_WDN_USERDEVICE+1)
#define BEE_WDN_CLOSEBUTTON   (WINDOW_WDN_USERDEVICE+2)

#define BEE_PATH_MAX 10

typedef struct{
    UINT8 TaskState;
    UINT8 State;
    UINT8 Dirty;
    UINT8 HitNumber;
    UINT8 BeeCurrentPath;
    UINT8 BeePreviousPath;
    UINT8 FlyStep;
    UINT8 HitCheck;
    UINT8 GameOver;
    UINT32 WindowEvent;
    
    BEEGAME_BULLET *FreeBulletList;
    BEEGAME_BULLET *UsedBulletList;
    BEEGAME_BULLET Bullets[BBE_BULLET_MAX];
    OS_TIMER BulletTimer;
    
    BEEGAME_BEE *BeeList;
    BEEGAME_BEE Bees[BBE_BEES_MAX];
    BEEGAME_BEE *pCurrentBee;
    OS_TIMER BeesTimer;
    
    BEEGAME_FIGHTER Fighter;

    WINDOW_BUTTON RestartButton;
    WINDOW_DEVICE WdRestartButton;
    WINDOW_BUTTON CloseButton;
    WINDOW_DEVICE WdCloseButton;
    BOARD Board;
    WINDOW_DEVICE WdBoard;
    WINDOW_TABLE UserTable;
    WINDOW Window;
}BEEGAME_CONTROL;

extern const UINT8 BeegameFighterBitmap[13];

VOID BeegameSvc(BEEGAME_CONTROL *pBee);
VOID BeegameInit(BEEGAME_CONTROL *pBee);
VOID BeegameEventHandler(BEEGAME_CONTROL *pBeegameCtrl);

VOID BeegameFighterSvc(BEEGAME_CONTROL *pBeegameCtrl,UINT8 KeyData);
VOID BeegameFighterUpdate(BEEGAME_CONTROL *pBeegameCtrl);
VOID BeegameFighterMapCapture(BEEGAME_CONTROL *pBeegameCtrl);
VOID BeegameFighterDraw(BEEGAME_CONTROL *pBeegameCtrl);
VOID BeegameFighterMapRecovery(BEEGAME_CONTROL *pBeegameCtrl);
VOID BeegameFighterMapDraw(BEEGAME_CONTROL *pBeegameCtrl);

VOID BeegameFreeBulletListBulletPut(BEEGAME_CONTROL *pBeegameCtrl,BEEGAME_BULLET *pBullet);
BEEGAME_BULLET *BeegameFreeBulletListBulletGet(BEEGAME_CONTROL *pBeegameCtrl);
VOID BeegameUsedBulletListBulletPut(BEEGAME_CONTROL *pBeegameCtrl,BEEGAME_BULLET *pBullet);
VOID BeegameUsedBulletListBulletDelete(BEEGAME_CONTROL *pBeegameCtrl,BEEGAME_BULLET *pBullet);

VOID BeegameBulletMove(BEEGAME_CONTROL *pBeegameCtrl);
VOID BeegameBulletUpdate(BEEGAME_CONTROL *pBeegameCtrl,BEEGAME_BULLET *pBullet);
VOID BeegameBulletMapRecovery(BEEGAME_CONTROL *pBeegameCtrl,BEEGAME_BULLET *pBullet);
VOID BeegameBulletMapCapture(BEEGAME_CONTROL *pBeegameCtrl,BEEGAME_BULLET *pBullet);
VOID BeegameBulletDraw(BEEGAME_CONTROL *pBeegameCtrl,BEEGAME_BULLET *pBullet);
VOID BeegameBulletMapDraw(BEEGAME_CONTROL *pBeegameCtrl,BEEGAME_BULLET *pBullet);

VOID BeegameBeeMove(BEEGAME_CONTROL *pBeegameCtrl);
VOID BeegameBeeUpdate(BEEGAME_CONTROL *pBeegameCtrl,BEEGAME_BEE *pBee);
VOID BeegameBeeMapRecovery(BEEGAME_CONTROL *pBeegameCtrl,BEEGAME_BEE *pBee);
VOID BeegameBeeMapClear(BEEGAME_CONTROL *pBeegameCtrl,BEEGAME_BEE *pBee);
VOID BeegameBeeMapCapture(BEEGAME_CONTROL *pBeegameCtrl,BEEGAME_BEE *pBee);
VOID BeegameBeeDraw(BEEGAME_CONTROL *pBeegameCtrl,BEEGAME_BEE *pBee);
VOID BeegameBeeMapDraw(BEEGAME_CONTROL *pBeegameCtrl,BEEGAME_BEE *pBee);
VOID BeegameBeeBulletHitHandler(BEEGAME_CONTROL *pBeegameCtrl);
VOID BeegameBeeListBeePut(BEEGAME_CONTROL *pBeegameCtrl,BEEGAME_BEE *pBee);
BEEGAME_BEE *BeegameBeeListBeeGet(BEEGAME_CONTROL *pBeegameCtrl);

#endif
