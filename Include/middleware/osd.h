#ifndef OSD_H
#define OSD_H

typedef struct{
    GRAPHIC_AREA ScreenArea;
    UINT8 *pVideoMemory;
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pPixMemory;
	UINT32 PixLength;
    UINT8 BitsPerPixel;
}OSD_CONTROL;

extern OSD_CONTROL OsdCtrl;
extern VOID OsdInit(VOID);
#endif
