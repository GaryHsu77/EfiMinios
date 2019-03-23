#ifndef POSTLOGO_BS_H
#define POSTLOGO_BS_H

typedef EFI_STATUS (*POST_LOGO_OVERWRITE)(UINT8 *LogoImage,UINTN LogoSize,BOOLEAN Force);
typedef EFI_STATUS (*POST_LOGO_START)(EFI_HANDLE);
typedef EFI_STATUS (*BMP_DRAW)(UINT8 *bmp,UINT32 size,INT32 x,INT32 y);
typedef EFI_STATUS (*JPEG_DRAW)(UINT8 *jpg,UINT32 size,INT32 x,INT32 y);
typedef EFI_STATUS (*PNG_DRAW)(UINT8 *png,UINT32 size,INT32 x,INT32 y);

typedef EFI_STATUS (*BMP_DRAW_EX)(UINT8 *bmp,UINT32 size,INT32 x,INT32 y,UINT32 Shadowx,UINT32 Shadowy,BOOLEAN Shadow,BOOLEAN Transparent);
typedef EFI_STATUS (*JPEG_DRAW_EX)(UINT8 *jpg,UINT32 size,INT32 x,INT32 y,UINT32 Shadowx,UINT32 Shadowy,BOOLEAN Shadow,BOOLEAN Transparent);
typedef EFI_STATUS (*PNG_DRAW_EX)(UINT8 *png,UINT32 size,INT32 x,INT32 y,UINT32 Shadowx,UINT32 Shadowy,BOOLEAN Shadow);

typedef struct _POSTLOGO_BS_PROTOCOL
{
	POST_LOGO_OVERWRITE PostLogoOverWrite;
	POST_LOGO_START PostLogoStart;
	BMP_DRAW BmpDraw;
	JPEG_DRAW JpegDraw;
	PNG_DRAW PngDraw;

	BMP_DRAW_EX BmpDrawEx;
	JPEG_DRAW_EX JpegDrawEx;
	PNG_DRAW_EX PngDrawEx;

	UINTN LogoDisplayMode;	//0:GOP Native Mode 0x0112:640x480 0x0115:800x600 0x0118:1024x768 0xFFFFFFFF:Resolution not specified

} POSTLOGO_BS_PROTOCOL;

#endif
