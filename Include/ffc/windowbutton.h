#ifndef WINDOWBUTTON_H
#define WINDOWBUTTON_H

#define WINDOW_BUTTON_PUSHBUTTON    0 // button type
#define WINDOW_BUTTON_ONEPUSHBUTTON 1 //button type
#define WINDOW_BUTTON_HIDE          2
#define WINDOW_BUTTON_MAXIMUN       3
#define WINDOW_BUTTON_CLOSE         4

#define WINDOW_BUTTON_RELEASE 0       // button status
#define WINDOW_BUTTON_PRESS   1       // button status

typedef struct{
    UINT8 Type; 
    UINT8 Status;    //release,press
    UINT8 Active;    //true,false
    UINT8 Dirty;     //true,false
    UINT8 Outline;   //true,false
    UINT8 *pName;    //name to show on button
    UINT8 *pBitmap;  //bitmap to show on button...prior to Name
    UINT32 OutlineColor;
    GRAPHIC_GFX ReleaseGfx;
    GRAPHIC_GFX PressGfx;
    GRAPHIC_GFX InactiveGfx;
    GRAPHIC_AREA Area; //area used by this device
}WINDOW_BUTTON;

#endif
