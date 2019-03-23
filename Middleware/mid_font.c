#include <includes.h>

const UINT8 Font8x8CursorOn[]={
0x88, 0x08,
0x03, 
0x03,
0x03,
0x03,
0x03,
0x03,
0x03,
0x03,
};

const UINT8 Font8x8CursorOff[]={
0x88, 0x08,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
};

const UINT8 Font8x8EmptyChar[]={
0x88, 0x08,
0x00,
0x00,
0x00,
0x00, 
0x00, 
0x00,
0x00, 
0x00, 
};

UINT8 *FontBitmapGet(UINT8 Style,UINT8 Data)
{
    Data=Data-0x20;
    if(Style==1) return (UINT8 *)pFont1Char[Data];
	else{
		GDP(L"ERROR : FontBitmapGet function get incorrect style number.");
		return 0;
	}
    //else if(Style==2) return (UINT8 *)pFont2Char[Data];
    //else return (UINT8 *)pFont2Char[Data];
}
