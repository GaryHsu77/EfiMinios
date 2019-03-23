#ifndef INCLUDES_H
#define INCLUDES_H

#include <efi.h>
#include <efiapi.h>
#include <efilib.h>
#include "efi\GraphicsOutput.h"
#include "efi\CPU.h"
#include "efi\efi_define.h" 

#include "system\define.h"
//#include "system\intelx86.h"
#include "system\debug.h"         
#include "system\system.h"        
#include "system\memory.h"
#include "system\entry.h"
#include "system\interrupt.h"
#include "system\systemgui.h"
//#include "system\systemdebug.h"

#include "os\os_define.h"
//#include "os\os_lib_a.h"
#include "os\os_task.h"
#include "os\os_TaskLib.h"
#include "os\os_core.h"
#include "os\os_event.h"
#include "os\os_resource.h"
#include "os\os_time.h"
#include "os\os_scheduler.h"
#include "os\os_memory.h"
#include "os\os_roottask.h"
#include "os\os_lib.h"

#include "drivers\pic.h"
#include "drivers\pic_a.h"
#include "drivers\timer.h"
#include "drivers\keyboard.h"
#include "drivers\mouse.h"
#include "drivers\uart1.h"
#include "drivers\uart2.h"
#include "drivers\lptport2.h"
#include "drivers\lptport1.h"
#include "drivers\vga.h"
#include "drivers\rtc.h"
//#include "drivers\fdc.h"

#include "ffc\windowbutton.h"
#include "ffc\window.h"
#include "ffc\caption.h"
#include "ffc\board.h"

#include "middleware\osd.h"
#include "middleware\console.h"
#include "middleware\xmodem.h"
#include "middleware\gfxclut.h"
#include "middleware\font\font.h"
#include "middleware\font\font1.h"
#include "middleware\font\font2.h"
#include "middleware\gui\gui.h"
#include "middleware\gui\guiclut.h"
#include "middleware\gui\guitext.h"
#include "middleware\gui\guitextbuffer.h"

#include "applications\desk\desk.h"
#include "applications\bee\bee.h"
#include "applications\bomb\bomb.h"
#include "applications\calculator\calculator.h"
#include "applications\2048\2048.h"

#include "tasks\desktask.h"
#include "tasks\shelltask.h"
#include "tasks\terminaltask.h"
#include "tasks\calculatortask.h"
#include "tasks\beetask.h"
#include "tasks\bombtask.h"

#include "system\systemlib.h"
#include "lib\PCILib.h"
#include "lib\NVLib.h"

#include "Build\driverHandleList.h"

#endif
