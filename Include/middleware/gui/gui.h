#ifndef GUI_H
#define GUI_H

#define GUI_RESOURCE 1

typedef struct{
    OS_RESOURCE GuiResource;
}GUI_CONTROL;

extern GUI_CONTROL GuiCtrl;

void GuiCharPrint(UINT8 CharValue);
BOOLEAN GuiStringPrint(UINT8* pString);
void GuiBackSpace(void);
void GuiUINT8Print(UINT8 Number);
void GuiUINT16Print(UINT16 Number);
void GuiUINT32Print(UINT32 Number);

#endif
