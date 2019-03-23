#ifndef BS_PROTOCOL_H
#define BS_PROTOCOL_H

//BIN: GUID rules:
//BIN: GUID is composed of 1 32-bit DWord, 2 16-bit Words, and 8 8-bit Bytes.
//BIN: When using '.NET Visual Studio' to generate GUID, the format of GUID is:
//BIN: A02CF7D6-1F0A-411d-B3A2-AF71455EB188 (just an example)
//BIN: Be careful about the word 'B3A2'!!
//BIN: The word 'B3A2' belongs to the 8 8-bit Bytes, not a 16-bit word.
//BIN: Take care of this scenario because X86 is little-endian.
//BIN: The order of 'B3A2' in memory is 'B3,A2'(Byte order), not 'A2,B3'(Word order).
//BIN: So when we declare a new GUID, we should split the third word (ex.'B3A2')
//BIN: into 2 8-bit Bytes. So the format of GUID declaration is:
//BIN: 0xA02CF7D6, 0x1F0A, 0x411d, 0xB3, 0xA2, 0xAF, 0x71, 0x45, 0x5E, 0xB1, 0x88
//BIN:                             ^^^^^^^^^^ (Take care of this)

#define PEGA_BACKUP_BOOT_VAR_GUID \
   {\
	0x7E661A90, 0x2428, 0x4388, 0xAA, 0x4A, 0x83, 0x29, 0x20, 0xE4, 0xDA, 0x49 \
   }

#define PEGA_BS_PROTOCOL_GUID \
   { \
	0xA51612B2, 0x6F18, 0x4dbc, 0x84, 0x2F, 0x54, 0x02, 0x29, 0x73, 0xDB, 0xF6 \
   }

#include "POSTLogoBS.h"


typedef struct _POSTLOGO_BS_PROTOCOL	POSTLOGO_BS_PROTOCOL;


typedef struct _PEGA_BS_PROTOCOL
{
	VOID						*SBChipBS;
	VOID						*VGABS;
	POSTLOGO_BS_PROTOCOL		*PostLogoBS;
	VOID						*PostWaveBS;
	VOID						*CrisisBS;
	VOID						*CommonBS;
	VOID            			*CustomerBS;
	VOID						*OEMBS;
	VOID						*PROJBS;
	//new protocol will be added below here, please don't change above protocol sequence.
} PEGA_BS_PROTOCOL;

#endif
