#include <includes.h>

OSD_CONTROL OsdCtrl;

VOID OsdInit(VOID)
{
	//GDB OsdCtrl.pVideoMemory=pOsDriverVga->pVideoMemory;
	OsdCtrl.pPixMemory=pOsDriverVga->pPixMemory;
	OsdCtrl.BitsPerPixel=pOsDriverVga->BitsPerPixel;
	OsdCtrl.ScreenArea.X=pOsDriverVga->Area.X;
	OsdCtrl.ScreenArea.Y=pOsDriverVga->Area.Y;
	OsdCtrl.ScreenArea.W=pOsDriverVga->Area.W;
	OsdCtrl.ScreenArea.H=pOsDriverVga->Area.H;
	OsdCtrl.PixLength = OsdCtrl.ScreenArea.W*OsdCtrl.ScreenArea.H;
	
	SystemGuiStringPrint(L">>> OsdInit end      <<<<<<<<<<\n");
}