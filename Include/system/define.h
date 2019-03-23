#ifndef DEFINE_H
#define DEFINE_H

#define ON 1
#define OFF 0

#define BUFFER_FAIL 0
#define BUFFER_GOOD 1

#define BUFFER_EMPTY     0
#define BUFFER_NOT_EMPTY 1
#define BUFFER_FULL      2

#define BUTTON_RELEASE 0
#define BUTTON_PRESS   1

#define ALIGN_RIGHT       0
#define ALIGN_LEFT        1
#define ALIGN_TOP         2
#define ALIGN_BOTTOM      3
#define ALIGN_LEFTTOP     4
#define ALIGN_LEFTBOTTOM  5
#define ALIGN_RIGHTTOP    6
#define ALIGN_RIGHTBOTTOM 7

#define	GDT_SIZE	128
#define	IDT_SIZE	256

#define IMAGE_ADDRESS 0x00100000 // image start from 1mb at sdram
//#define IMAGE_ADDRESS 0x00020000 // image start from 128k at ram

typedef union {
    UINT32 ul;
    UINT8  uc[4];
}UN_UL;

// graphics definition
typedef struct{
    UINT32 X;
    UINT32 Y;
}GRAPHIC_POSITION;

typedef struct{
    UINT32 X;
    UINT32 Y;
    UINT32 W;
    UINT32 H;
}GRAPHIC_AREA;

typedef struct{
    UINT32 BgColor;
    UINT32 FgColor;
    UINT32 FontColor;
}GRAPHIC_GFX;


#endif
