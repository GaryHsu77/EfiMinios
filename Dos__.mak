MAIN_FOLDER= D:\Dragon
APP_FOLDER=$(MAIN_FOLDER)\Application
DESK_FOLDER=$(MAIN_FOLDER)\Application\Desk
DRIVER_FOLDER=$(MAIN_FOLDER)\Driver
MIDDLEWARE_FOLDER=$(MAIN_FOLDER)\Middleware
OSCORE_FOLDER=$(MAIN_FOLDER)\OsKernel
SYSTEM_FOLDER=$(MAIN_FOLDER)\SystemLib
BUILDTOOL_FOLDER=$(MAIN_FOLDER)\BuildTool
UI_FOLDER=$(MAIN_FOLDER)\UI


SDK_INSTALL_DIR= $(BUILDTOOL_FOLDER)\EFI_Toolkit_2.0
SDK_BUILD_ENV=em64t
PROCESSOR=IA64
TARGET=app
BUILD_DIR= D:\Dragon\$(PROCESSOR)
MAKE= "$(BUILDTOOL_FOLDER)\Compiler\AMD64\nmake.exe"
CC= "$(BUILDTOOL_FOLDER)\Compiler\AMD64\cl.exe"
LINK= "$(BUILDTOOL_FOLDER)\Compiler\AMD64\link.exe"
LIB= "$(BUILDTOOL_FOLDER)\Compiler\AMD64\lib.exe"
ASM= "$(BUILDTOOL_FOLDER)\Compiler\AMD64\ml64.exe"
FWIMAGE= $(SDK_INSTALL_DIR)\build\tools\bin\fwimage.exe
INCLUDEBASE= include\efi110
INCLUDE= -I $(SDK_INSTALL_DIR)\$(INCLUDEBASE)
INCLUDE= -I $(SDK_INSTALL_DIR)\$(INCLUDEBASE)\protocol $(INCLUDE) $(INCLUDE_H)
INCLUDE= -I $(SDK_INSTALL_DIR)\$(INCLUDEBASE)\ia64 $(INCLUDE) $(INCLUDE_H)
INCLUDE_H= -I $(MAIN_FOLDER)\Include
CFLAGS= /nologo /W3 /Gm /Zi /O1 /GF /Gy /Gs8192 /X /DEFIX64 /DEFI_NT_EMULATOR /DUNICODE /DEFI_DEBUG /DEFI_APP_102
AFLAGS= /nologo /W3 /WX /c /Zi /DDEBUG /DEFIX64
LIBEFI=$(SDK_INSTALL_DIR)\build\em64t\output\lib\libefi\libefi.lib
LIBC=$(SDK_INSTALL_DIR)\build\em64t\output\lib\libc\libc.lib
LIBM=$(SDK_INSTALL_DIR)\build\em64t\output\lib\libm\libm.lib
LIBDB=$(SDK_INSTALL_DIR)\build\em64t\output\lib\libdb\libdb.lib
LIBEFISHELL=$(SDK_INSTALL_DIR)\build\em64t\output\lib\libefishell\libefishell.lib
LIBSOCKET=$(SDK_INSTALL_DIR)\build\em64t\output\lib\libsocket\libsocket.lib
LIBTTY=$(SDK_INSTALL_DIR)\build\em64t\output\lib\libtty\libtty.lib
LIBS=$(LIBEFI) $(LIBC) $(LIBM) $(LIBDB) $(LIBEFISHELL) $(LIBSOCKET) $(LIBTTY)
LIBALL= $(BUILD_DIR)\libefiall64.lib
IMAGE_ENTRY_POINT=Dragon
FILES=$(DESK_FOLDER)\desk.c  \
	$(DESK_FOLDER)\deskactivewindow.c  \
	$(DESK_FOLDER)\deskbg.c  \
	$(DESK_FOLDER)\deskdevice.c  \
	$(DESK_FOLDER)\deskinactivewindow.c  \
	$(DESK_FOLDER)\desklib.c  \
	$(DESK_FOLDER)\deskmouse.c  \
	$(DESK_FOLDER)\desktable.c  \
	$(DESK_FOLDER)\desktask.c  \
	$(DESK_FOLDER)\desktime.c  \
	$(DESK_FOLDER)\deskwindow.c  \
	$(DESK_FOLDER)\deskwork.c  \
	$(DESK_FOLDER)\deskworkbar.c  \
	$(DRIVER_FOLDER)\driver_efi.c  \
	$(DRIVER_FOLDER)\driver_keyboard.c  \
	$(DRIVER_FOLDER)\driver_mouse.c  \
	$(DRIVER_FOLDER)\driver_rtc.c  \
	$(DRIVER_FOLDER)\driver_timer.c  \
	$(DRIVER_FOLDER)\driver_vga.c  \
	$(MIDDLEWARE_FOLDER)\mid_font.c  \
	$(MIDDLEWARE_FOLDER)\mid_font1.c  \
	$(MIDDLEWARE_FOLDER)\mid_gfxclut.c  \
	$(MIDDLEWARE_FOLDER)\mid_osd.c  \
	$(OSCORE_FOLDER)\os_core.c  \
	$(OSCORE_FOLDER)\os_entry.c  \
	$(OSCORE_FOLDER)\os_event.c  \
	$(OSCORE_FOLDER)\os_mmio_lib.c  \
	$(OSCORE_FOLDER)\os_roottask.c  \
	$(OSCORE_FOLDER)\os_scheduler.c  \
	$(OSCORE_FOLDER)\os_task.c  \
	$(OSCORE_FOLDER)\os_TaskLib.c  \
	$(OSCORE_FOLDER)\os_time.c  \
	$(SYSTEM_FOLDER)\sys_interrupt.c  \
	$(UI_FOLDER)\ui_board.c  \
	$(UI_FOLDER)\ui_caption.c  \
	$(UI_FOLDER)\ui_window.c  \
	$(SYSTEM_FOLDER)\STRING_LIB\sys_string.c  \
	$(SYSTEM_FOLDER)\NV_LIB\NVLib.c  \
	$(SYSTEM_FOLDER)\PCI_LIB\PCILib.c  \
	$(SYSTEM_FOLDER)\sys_gui.c  \
	$(DESK_FOLDER)\deskmenu.c  \
	$(DESK_FOLDER)\deskcontrolpanel.c  \
	$(DESK_FOLDER)\deskdebug.c  \
	$(MIDDLEWARE_FOLDER)\mid_console.c  \
	$(APP_FOLDER)\Shell\task_shell.c  \
	$(APP_FOLDER)\Bee\bee.c  \
	$(APP_FOLDER)\Bee\beebees.c  \
	$(APP_FOLDER)\Bee\beebullet.c  \
	$(APP_FOLDER)\Bee\beefighter.c  \
	$(APP_FOLDER)\Bee\beetask.c  \
	$(OSCORE_FOLDER)\os_sysLib.c  \
	$(APP_FOLDER)\Bomb\bomb.c  \
	$(APP_FOLDER)\Bomb\bombtask.c  \
	$(APP_FOLDER)\Calculator\calculator.c  \
	$(APP_FOLDER)\Calculator\calculatortask.c \
	$(APP_FOLDER)\2048\2048Task.c \
	$(APP_FOLDER)\2048\2048.c	
	
ASMFILES=$(OSCORE_FOLDER)\os_TaskLib_a.asm  \
	$(SYSTEM_FOLDER)\sys_intUtilx64.asm
OBJS=  \
	$(BUILD_DIR)\desk.obj \
	$(BUILD_DIR)\deskactivewindow.obj \
	$(BUILD_DIR)\deskbg.obj \
	$(BUILD_DIR)\deskdevice.obj \
	$(BUILD_DIR)\deskinactivewindow.obj \
	$(BUILD_DIR)\desklib.obj \
	$(BUILD_DIR)\deskmouse.obj \
	$(BUILD_DIR)\desktable.obj \
	$(BUILD_DIR)\desktask.obj \
	$(BUILD_DIR)\desktime.obj \
	$(BUILD_DIR)\deskwindow.obj \
	$(BUILD_DIR)\deskwork.obj \
	$(BUILD_DIR)\deskworkbar.obj \
	$(BUILD_DIR)\driver_efi.obj \
	$(BUILD_DIR)\driver_keyboard.obj \
	$(BUILD_DIR)\driver_mouse.obj \
	$(BUILD_DIR)\driver_rtc.obj \
	$(BUILD_DIR)\driver_timer.obj \
	$(BUILD_DIR)\driver_vga.obj \
	$(BUILD_DIR)\mid_font.obj \
	$(BUILD_DIR)\mid_font1.obj \
	$(BUILD_DIR)\mid_gfxclut.obj \
	$(BUILD_DIR)\mid_osd.obj \
	$(BUILD_DIR)\os_core.obj \
	$(BUILD_DIR)\os_entry.obj \
	$(BUILD_DIR)\os_event.obj \
	$(BUILD_DIR)\os_mmio_lib.obj \
	$(BUILD_DIR)\os_roottask.obj \
	$(BUILD_DIR)\os_scheduler.obj \
	$(BUILD_DIR)\sys_string.obj \
	$(BUILD_DIR)\NVLib.obj \
	$(BUILD_DIR)\PCILib.obj \
	$(BUILD_DIR)\os_task.obj \
	$(BUILD_DIR)\os_TaskLib.obj \
	$(BUILD_DIR)\os_time.obj \
	$(BUILD_DIR)\sys_interrupt.obj \
	$(BUILD_DIR)\ui_board.obj \
	$(BUILD_DIR)\ui_caption.obj \
	$(BUILD_DIR)\ui_window.obj \
	$(BUILD_DIR)\sys_gui.obj \
	$(BUILD_DIR)\deskmenu.obj \
	$(BUILD_DIR)\deskcontrolpanel.obj \
	$(BUILD_DIR)\deskdebug.obj \
	$(BUILD_DIR)\mid_console.obj \
	$(BUILD_DIR)\task_shell.obj \
	$(BUILD_DIR)\bee.obj \
	$(BUILD_DIR)\beebees.obj \
	$(BUILD_DIR)\beebullet.obj \
	$(BUILD_DIR)\beefighter.obj \
	$(BUILD_DIR)\beetask.obj \
	$(BUILD_DIR)\os_sysLib.obj \
	$(BUILD_DIR)\bomb.obj \
	$(BUILD_DIR)\bombtask.obj \
	$(BUILD_DIR)\calculator.obj \
	$(BUILD_DIR)\calculatortask.obj \
	$(BUILD_DIR)\2048Task.obj \
	$(BUILD_DIR)\2048.obj
	
ASMOBJS=  \
	$(BUILD_DIR)\os_TaskLib_a.obj \
	$(BUILD_DIR)\sys_intUtilx64.obj
all: CREATE_ENV_DIR $(OBJS) $(ASMOBJS) $(LIBALL)
	$(LINK) /NOLOGO /MACHINE:AMD64 /SUBSYSTEM:CONSOLE /NODEFAULTLIB /IGNORE:4086 /DEBUG /OPT:REF /DLL /ENTRY:$(IMAGE_ENTRY_POINT) $(OBJS) $(ASMOBJS) $(LIBALL) /OUT:$(BUILD_DIR)\$(IMAGE_ENTRY_POINT).dll
	$(FWIMAGE) $(TARGET) $(BUILD_DIR)\$(IMAGE_ENTRY_POINT).dll $(MAIN_FOLDER)\$(IMAGE_ENTRY_POINT).efi
$(BUILD_DIR)\desk.obj: $(DESK_FOLDER)\desk.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) $(INCLUDE_H) /c $(DESK_FOLDER)\desk.c /Fo$(BUILD_DIR)\desk.obj
$(BUILD_DIR)\deskactivewindow.obj: $(DESK_FOLDER)\deskactivewindow.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) $(INCLUDE_H) /c $(DESK_FOLDER)\deskactivewindow.c /Fo$(BUILD_DIR)\deskactivewindow.obj
$(BUILD_DIR)\deskbg.obj: $(DESK_FOLDER)\deskbg.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) $(INCLUDE_H) /c $(DESK_FOLDER)\deskbg.c /Fo$(BUILD_DIR)\deskbg.obj
$(BUILD_DIR)\deskdevice.obj: $(DESK_FOLDER)\deskdevice.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) $(INCLUDE_H) /c $(DESK_FOLDER)\deskdevice.c /Fo$(BUILD_DIR)\deskdevice.obj
$(BUILD_DIR)\deskinactivewindow.obj: $(DESK_FOLDER)\deskinactivewindow.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) $(INCLUDE_H) /c $(DESK_FOLDER)\deskinactivewindow.c /Fo$(BUILD_DIR)\deskinactivewindow.obj
$(BUILD_DIR)\desklib.obj: $(DESK_FOLDER)\desklib.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) $(INCLUDE_H) /c $(DESK_FOLDER)\desklib.c /Fo$(BUILD_DIR)\desklib.obj
$(BUILD_DIR)\deskmouse.obj: $(DESK_FOLDER)\deskmouse.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) $(INCLUDE_H) /c $(DESK_FOLDER)\deskmouse.c /Fo$(BUILD_DIR)\deskmouse.obj
$(BUILD_DIR)\desktable.obj: $(DESK_FOLDER)\desktable.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) $(INCLUDE_H) /c $(DESK_FOLDER)\desktable.c /Fo$(BUILD_DIR)\desktable.obj
$(BUILD_DIR)\desktask.obj: $(DESK_FOLDER)\desktask.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) $(INCLUDE_H) /c $(DESK_FOLDER)\desktask.c /Fo$(BUILD_DIR)\desktask.obj
$(BUILD_DIR)\desktime.obj: $(DESK_FOLDER)\desktime.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) $(INCLUDE_H) /c $(DESK_FOLDER)\desktime.c /Fo$(BUILD_DIR)\desktime.obj
$(BUILD_DIR)\deskwindow.obj: $(DESK_FOLDER)\deskwindow.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) $(INCLUDE_H) /c $(DESK_FOLDER)\deskwindow.c /Fo$(BUILD_DIR)\deskwindow.obj
$(BUILD_DIR)\deskwork.obj: $(DESK_FOLDER)\deskwork.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) $(INCLUDE_H) /c $(DESK_FOLDER)\deskwork.c /Fo$(BUILD_DIR)\deskwork.obj
$(BUILD_DIR)\deskworkbar.obj: $(DESK_FOLDER)\deskworkbar.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) $(INCLUDE_H) /c $(DESK_FOLDER)\deskworkbar.c /Fo$(BUILD_DIR)\deskworkbar.obj
$(BUILD_DIR)\driver_efi.obj: $(DRIVER_FOLDER)\driver_efi.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) $(INCLUDE_H) /c $(DRIVER_FOLDER)\driver_efi.c /Fo$(BUILD_DIR)\driver_efi.obj
$(BUILD_DIR)\driver_keyboard.obj: $(DRIVER_FOLDER)\driver_keyboard.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) $(INCLUDE_H) /c $(DRIVER_FOLDER)\driver_keyboard.c /Fo$(BUILD_DIR)\driver_keyboard.obj
$(BUILD_DIR)\driver_mouse.obj: $(DRIVER_FOLDER)\driver_mouse.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) $(INCLUDE_H) /c $(DRIVER_FOLDER)\driver_mouse.c /Fo$(BUILD_DIR)\driver_mouse.obj
$(BUILD_DIR)\driver_rtc.obj: $(DRIVER_FOLDER)\driver_rtc.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) $(INCLUDE_H) /c $(DRIVER_FOLDER)\driver_rtc.c /Fo$(BUILD_DIR)\driver_rtc.obj
$(BUILD_DIR)\driver_timer.obj: $(DRIVER_FOLDER)\driver_timer.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) $(INCLUDE_H) /c $(DRIVER_FOLDER)\driver_timer.c /Fo$(BUILD_DIR)\driver_timer.obj
$(BUILD_DIR)\driver_vga.obj: $(DRIVER_FOLDER)\driver_vga.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) $(INCLUDE_H) /c $(DRIVER_FOLDER)\driver_vga.c /Fo$(BUILD_DIR)\driver_vga.obj
$(BUILD_DIR)\mid_font.obj: $(MIDDLEWARE_FOLDER)\mid_font.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) $(INCLUDE_H) /c $(MIDDLEWARE_FOLDER)\mid_font.c /Fo$(BUILD_DIR)\mid_font.obj
$(BUILD_DIR)\mid_font1.obj: $(MIDDLEWARE_FOLDER)\mid_font1.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) $(INCLUDE_H) /c $(MIDDLEWARE_FOLDER)\mid_font1.c /Fo$(BUILD_DIR)\mid_font1.obj
$(BUILD_DIR)\mid_gfxclut.obj: $(MIDDLEWARE_FOLDER)\mid_gfxclut.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) $(INCLUDE_H) /c $(MIDDLEWARE_FOLDER)\mid_gfxclut.c /Fo$(BUILD_DIR)\mid_gfxclut.obj
$(BUILD_DIR)\mid_osd.obj: $(MIDDLEWARE_FOLDER)\mid_osd.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) $(INCLUDE_H) /c $(MIDDLEWARE_FOLDER)\mid_osd.c /Fo$(BUILD_DIR)\mid_osd.obj
$(BUILD_DIR)\os_core.obj: $(OSCORE_FOLDER)\os_core.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) $(INCLUDE_H) /c $(OSCORE_FOLDER)\os_core.c /Fo$(BUILD_DIR)\os_core.obj
$(BUILD_DIR)\os_entry.obj: $(OSCORE_FOLDER)\os_entry.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) $(INCLUDE_H) /c $(OSCORE_FOLDER)\os_entry.c /Fo$(BUILD_DIR)\os_entry.obj
$(BUILD_DIR)\os_event.obj: $(OSCORE_FOLDER)\os_event.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) $(INCLUDE_H) /c $(OSCORE_FOLDER)\os_event.c /Fo$(BUILD_DIR)\os_event.obj
$(BUILD_DIR)\os_mmio_lib.obj: $(OSCORE_FOLDER)\os_mmio_lib.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) $(INCLUDE_H) /c $(OSCORE_FOLDER)\os_mmio_lib.c /Fo$(BUILD_DIR)\os_mmio_lib.obj
$(BUILD_DIR)\os_roottask.obj: $(OSCORE_FOLDER)\os_roottask.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) $(INCLUDE_H) /c $(OSCORE_FOLDER)\os_roottask.c /Fo$(BUILD_DIR)\os_roottask.obj
$(BUILD_DIR)\os_scheduler.obj: $(OSCORE_FOLDER)\os_scheduler.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) $(INCLUDE_H) /c $(OSCORE_FOLDER)\os_scheduler.c /Fo$(BUILD_DIR)\os_scheduler.obj
$(BUILD_DIR)\sys_string.obj: $(SYSTEM_FOLDER)\STRING_LIB\sys_string.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) $(INCLUDE_H) /c $(SYSTEM_FOLDER)\STRING_LIB\sys_string.c /Fo$(BUILD_DIR)\sys_string.obj
$(BUILD_DIR)\NVLib.obj: $(SYSTEM_FOLDER)\NV_LIB\NVLib.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) $(INCLUDE_H) /c $(SYSTEM_FOLDER)\NV_LIB\NVLib.c /Fo$(BUILD_DIR)\NVLib.obj
$(BUILD_DIR)\PCILib.obj: $(SYSTEM_FOLDER)\PCI_LIB\PCILib.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) $(INCLUDE_H) /c $(SYSTEM_FOLDER)\PCI_LIB\PCILib.c /Fo$(BUILD_DIR)\PCILib.obj
$(BUILD_DIR)\os_task.obj: $(OSCORE_FOLDER)\os_task.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) $(INCLUDE_H) /c $(OSCORE_FOLDER)\os_task.c /Fo$(BUILD_DIR)\os_task.obj
$(BUILD_DIR)\os_TaskLib.obj: $(OSCORE_FOLDER)\os_TaskLib.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) $(INCLUDE_H) /c $(OSCORE_FOLDER)\os_TaskLib.c /Fo$(BUILD_DIR)\os_TaskLib.obj
$(BUILD_DIR)\os_time.obj: $(OSCORE_FOLDER)\os_time.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) $(INCLUDE_H) /c $(OSCORE_FOLDER)\os_time.c /Fo$(BUILD_DIR)\os_time.obj
$(BUILD_DIR)\sys_interrupt.obj: $(SYSTEM_FOLDER)\sys_interrupt.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) $(INCLUDE_H) /c $(SYSTEM_FOLDER)\sys_interrupt.c /Fo$(BUILD_DIR)\sys_interrupt.obj
$(BUILD_DIR)\ui_board.obj: $(UI_FOLDER)\ui_board.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) $(INCLUDE_H) /c $(UI_FOLDER)\ui_board.c /Fo$(BUILD_DIR)\ui_board.obj
$(BUILD_DIR)\ui_caption.obj: $(UI_FOLDER)\ui_caption.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) $(INCLUDE_H) /c $(UI_FOLDER)\ui_caption.c /Fo$(BUILD_DIR)\ui_caption.obj
$(BUILD_DIR)\ui_window.obj: $(UI_FOLDER)\ui_window.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) $(INCLUDE_H) /c $(UI_FOLDER)\ui_window.c /Fo$(BUILD_DIR)\ui_window.obj
$(BUILD_DIR)\sys_gui.obj: $(SYSTEM_FOLDER)\sys_gui.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) $(INCLUDE_H) /c $(SYSTEM_FOLDER)\sys_gui.c /Fo$(BUILD_DIR)\sys_gui.obj
$(BUILD_DIR)\deskmenu.obj: $(DESK_FOLDER)\deskmenu.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) $(INCLUDE_H) /c $(DESK_FOLDER)\deskmenu.c /Fo$(BUILD_DIR)\deskmenu.obj
$(BUILD_DIR)\deskcontrolpanel.obj: $(DESK_FOLDER)\deskcontrolpanel.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) $(INCLUDE_H) /c $(DESK_FOLDER)\deskcontrolpanel.c /Fo$(BUILD_DIR)\deskcontrolpanel.obj
$(BUILD_DIR)\deskdebug.obj: $(DESK_FOLDER)\deskdebug.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) $(INCLUDE_H) /c $(DESK_FOLDER)\deskdebug.c /Fo$(BUILD_DIR)\deskdebug.obj
$(BUILD_DIR)\mid_console.obj: $(MIDDLEWARE_FOLDER)\mid_console.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) $(INCLUDE_H) /c $(MIDDLEWARE_FOLDER)\mid_console.c /Fo$(BUILD_DIR)\mid_console.obj
$(BUILD_DIR)\task_shell.obj: $(APP_FOLDER)\Shell\task_shell.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) $(INCLUDE_H) /c $(APP_FOLDER)\Shell\task_shell.c /Fo$(BUILD_DIR)\task_shell.obj
$(BUILD_DIR)\bee.obj: $(APP_FOLDER)\Bee\bee.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) $(INCLUDE_H) /c $(APP_FOLDER)\Bee\bee.c /Fo$(BUILD_DIR)\bee.obj
$(BUILD_DIR)\beebees.obj: $(APP_FOLDER)\Bee\beebees.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) $(INCLUDE_H) /c $(APP_FOLDER)\Bee\beebees.c /Fo$(BUILD_DIR)\beebees.obj
$(BUILD_DIR)\beebullet.obj: $(APP_FOLDER)\Bee\beebullet.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) $(INCLUDE_H) /c $(APP_FOLDER)\Bee\beebullet.c /Fo$(BUILD_DIR)\beebullet.obj
$(BUILD_DIR)\beefighter.obj: $(APP_FOLDER)\Bee\beefighter.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) $(INCLUDE_H) /c $(APP_FOLDER)\Bee\beefighter.c /Fo$(BUILD_DIR)\beefighter.obj
$(BUILD_DIR)\beetask.obj: $(APP_FOLDER)\Bee\beetask.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) $(INCLUDE_H) /c $(APP_FOLDER)\Bee\beetask.c /Fo$(BUILD_DIR)\beetask.obj
$(BUILD_DIR)\os_sysLib.obj: $(OSCORE_FOLDER)\os_sysLib.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) $(INCLUDE_H) /c $(OSCORE_FOLDER)\os_sysLib.c /Fo$(BUILD_DIR)\os_sysLib.obj
$(BUILD_DIR)\bomb.obj: $(APP_FOLDER)\Bomb\bomb.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) $(INCLUDE_H) /c $(APP_FOLDER)\Bomb\bomb.c /Fo$(BUILD_DIR)\bomb.obj
$(BUILD_DIR)\bombtask.obj: $(APP_FOLDER)\Bomb\bombtask.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) $(INCLUDE_H) /c $(APP_FOLDER)\Bomb\bombtask.c /Fo$(BUILD_DIR)\bombtask.obj
$(BUILD_DIR)\calculator.obj: $(APP_FOLDER)\Calculator\calculator.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) $(INCLUDE_H) /c $(APP_FOLDER)\Calculator\calculator.c /Fo$(BUILD_DIR)\calculator.obj
$(BUILD_DIR)\calculatortask.obj: $(APP_FOLDER)\Calculator\calculatortask.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) $(INCLUDE_H) /c $(APP_FOLDER)\Calculator\calculatortask.c /Fo$(BUILD_DIR)\calculatortask.obj
$(BUILD_DIR)\2048Task.obj: $(APP_FOLDER)\2048\2048Task.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) $(INCLUDE_H) /c $(APP_FOLDER)\2048\2048Task.c /Fo$(BUILD_DIR)\2048Task.obj
$(BUILD_DIR)\2048.obj: $(APP_FOLDER)\2048\2048.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) $(INCLUDE_H) /c $(APP_FOLDER)\2048\2048.c /Fo$(BUILD_DIR)\2048.obj
$(BUILD_DIR)\os_TaskLib_a.obj: $(OSCORE_FOLDER)\os_TaskLib_a.asm $(HEADERS)
	$(ASM) $(AFLAGS) $(INCLUDE) $(INCLUDE_H) /Fo$(BUILD_DIR)\os_TaskLib_a.obj /c $(OSCORE_FOLDER)\os_TaskLib_a.asm
$(BUILD_DIR)\sys_intUtilx64.obj: $(SYSTEM_FOLDER)\sys_intUtilx64.asm $(HEADERS)
	$(ASM) $(AFLAGS) $(INCLUDE) $(INCLUDE_H) /Fo$(BUILD_DIR)\sys_intUtilx64.obj /c $(SYSTEM_FOLDER)\sys_intUtilx64.asm
$(LIBALL): 
	cd $(SDK_INSTALL_DIR)\lib
	$(MAKE) -f lib.mak all
	cd $(BUILD_DIR)
	$(LIB) /nologo $(LIBS) /OUT:$(LIBALL)
CREATE_ENV_DIR: 
!IF !EXIST($(BUILD_DIR))
    @mkdir $(BUILD_DIR)
!ENDIF
