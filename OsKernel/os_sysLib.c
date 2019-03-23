#include <includes.h>

BOOLEAN SystemlibAreaPositionCheck(GRAPHIC_AREA *pArea,GRAPHIC_POSITION *pPosition){
	if(pArea->W==0) return FALSE;
	if(pArea->H==0) return FALSE;
	if(pPosition->X<pArea->X) return FALSE;
	if(pPosition->Y<pArea->Y) return FALSE;
	if(pPosition->X>=(pArea->X+pArea->W)) return FALSE;
	if(pPosition->Y>=(pArea->Y+pArea->H)) return FALSE;
	return TRUE;
}

BOOLEAN SystemlibAreaOverlapCheck(GRAPHIC_AREA *pArea,GRAPHIC_AREA *pArea2){
	GRAPHIC_POSITION Position;
	UINT32 Width,Height;
	
	if((pArea->W*pArea->H)>=(pArea2->W*pArea2->H)){
		for(Width=0;Width<pArea2->W;Width++){
		    for(Height=0;Height<pArea2->H;Height++){
		        Position.X=pArea2->X+Width;
		        Position.Y=pArea2->Y+Height;
		        if(SystemlibAreaPositionCheck(pArea,&Position)==TRUE) return TRUE;
		    }
		}
	}
	else{
		for(Width=0;Width<pArea->W;Width++){
		    for(Height=0;Height<pArea->H;Height++){
		        Position.X=pArea->X+Width;
		        Position.Y=pArea->Y+Height;
		        if(SystemlibAreaPositionCheck(pArea2,&Position)==TRUE) return TRUE;
		    }
		}
	}
	return FALSE;
}