#ifndef FONT_H
#define FONT_H

#define FONT8X8 1
#define FONT8X16 2

#define FONT_FONT8X8_CHARWIDTH 8
#define FONT_FONT8X8_CHARHEIGHT 8

#define FONT_FONT8X16_CHARWIDTH 8
#define FONT_FONT8X16_CHARHEIGHT 16


extern const UINT8 Font8x8CursorOn[];
extern const UINT8 Font8x8CursorOff[];
extern const UINT8 Font8x8EmptyChar[];
extern UINT8 *FontBitmapGet(UINT8 Style,UINT8 Data);

#endif
