#ifndef MY_2048_H
#define MY_2048_H

#include <efi.h>
#include <efilib.h>
#include "GraphicsOutput.h"
#include "ForImage.h"
#include "PEGABSProtocol/BSProtocol.h"

#define EFI_TEXT_ATTR(foreground,background)  \
((foreground) | ((background) << 4))

extern EFI_GUID GraphicsOutputProtocol;
extern EFI_GUID SimpleTextOutputInterface;
extern EFI_GUID SimpleTextInputGuid;
extern EFI_GUID PegaBSProtocol_guid;

extern EFI_SYSTEM_TABLE *GST;
extern EFI_RUNTIME_SERVICES *GRS;
extern EFI_BOOT_SERVICES *GBS;

extern EFI_GRAPHICS_OUTPUT_PROTOCOL *GOP;
extern SIMPLE_TEXT_OUTPUT_INTERFACE *TOI;
extern SIMPLE_INPUT_INTERFACE *ConIn ;
extern PEGA_BS_PROTOCOL *PegaBSProtocol ;

extern EFI_GRAPHICS_OUTPUT_BLT_PIXEL black;
extern EFI_GRAPHICS_OUTPUT_BLT_PIXEL white;
extern EFI_GRAPHICS_OUTPUT_BLT_PIXEL blue;
extern EFI_GRAPHICS_OUTPUT_BLT_PIXEL red;
extern EFI_GRAPHICS_OUTPUT_BLT_PIXEL color;

extern UINTN leftTopX;
extern UINTN leftTopY;
extern UINTN falseNum;

extern UINTN random();
extern void drawNum();
extern void drawGNum();
extern void drawTitle();
extern void drawBox();
extern void drawBackground();
extern void drawWin();
extern void testValue();
extern void upMerge();
extern void blockMoveUp ();
extern void newBlock ();
extern void drawBlock();
extern void downMerge();
extern void blockMoveDown ();
extern void leftMerge();
extern void blockMoveLeft ();
extern void rightMerge();
extern void blockMoveRight ();
extern void reset();

typedef  struct block{
		UINTN empty;
		UINTN value;
}block;

extern block block44[4][4];


#endif