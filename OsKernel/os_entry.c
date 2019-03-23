#include <includes.h>

EFI_SYSTEM_TABLE *gST;
EFI_BOOT_SERVICES *gBS;
EFI_RUNTIME_SERVICES *gRT;
EFI_HANDLE gHandle;

BOOLEAN MULTTASK = FALSE;

EFI_STATUS Dragon(EFI_HANDLE ThisHandle,EFI_SYSTEM_TABLE *SystemTable)
{
	static EFI_INPUT_KEY Key;

	InitializeShellApplication(ThisHandle, SystemTable);
	InitializeLib(ThisHandle, SystemTable);

	gST = SystemTable;
	gBS = SystemTable->BootServices;
	gRT = SystemTable->RuntimeServices;
	gHandle = ThisHandle;

	OsInit(); 
	OsTaskCreat(RootTask, TASK_DEFAULT_STACK_SIZE, "ROOT", 0, NULL);
	OsStart();
	
	return EFI_SUCCESS;
}
