#include <includes.h>

BOOLEAN DesklibAreaPositionCheck(GRAPHIC_AREA *pArea,GRAPHIC_POSITION *pPosition)
{
	//gST->ConOut->SetCursorPosition(gST->ConOut,0,0);
	if(pArea->W==0) {
		//if(dbSwitch)GDP(L"DesklibAreaPositionCheck fail : 1\n");
		return FALSE;
	}
	if(pArea->H==0) {
		//if(dbSwitch)GDP(L"DesklibAreaPositionCheck fail : 2\n");
		return FALSE;
	}
	if(pPosition->X<pArea->X) {
		//if(dbSwitch)(L"DesklibAreaPositionCheck fail : 3 (%d, %d)\n", pPosition->X, pArea->X);
		return FALSE;
	}
	if(pPosition->Y<pArea->Y) {
		//if(dbSwitch) GDP(L"DesklibAreaPositionCheck fail : 4 (%d, %d)\n", pPosition->Y, pArea->Y);
		return FALSE;
	}
	if(pPosition->X>=(pArea->X+pArea->W)) {
		//if(dbSwitch) GDP(L"DesklibAreaPositionCheck fail : 5 (%d, %d)\n", pPosition->X, (pArea->X+pArea->W));
		return FALSE;
	}
	if(pPosition->Y>=(pArea->Y+pArea->H)) {
		//if(dbSwitch) GDP(L"DesklibAreaPositionCheck fail : 6\n");
		return FALSE;
	}
	//if(dbSwitch) GDP(L"DesklibAreaPositionCheck success : 7 (%d, %d)\n", pPosition->Y, pArea->Y);
	return TRUE;
}