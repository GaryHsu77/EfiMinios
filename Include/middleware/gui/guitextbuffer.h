#ifndef GUI_TEXT_BUFFER_H
#define GUI_TEXT_BUFFER_H

#define GUI_TEXT_BUFFER_SIZE 100
typedef struct{
	UINT8  Ready;  // ready for buffer use
    UINT32 Put;
    UINT32 Get;
    UINT8 Data[GUI_TEXT_BUFFER_SIZE];
}GUI_TEXT_BUFFER_CONTROL;

extern GUI_TEXT_BUFFER_CONTROL GuiTextBufferCtrl;
extern void GuiTextBufferInit(void);
extern void GuiTextBufferPut(UINT8);
extern UINT8 GuiTextBufferGet(void);
extern UINT8 GuiTextBufferCheck(void);

#endif
