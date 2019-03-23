#include <includes.h>

VOID DeskTaskInit(VOID)
{
	DeskInit();
}

VOID DeskTask(VOID *Arg)
{
    DeskTaskInit();
	SystemGuiStringPrint(L">>> DeskTaskInit end <<<<<<<<<<\n");
    while(1){
    	//while((KeyboardKeyBufferCheck()==BUFFER_EMPTY)
    	//    &&(MouseBufferCheck()==BUFFER_EMPTY)) OsYield(NULL,NULL);
    	DeskSvc();
        OsTaskSwitchOut(); 
    }
}
