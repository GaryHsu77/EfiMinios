#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2005, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************

#**********************************************************************
# $Header: /Alaska/Tools/VC6/vc6.mak 2     1/18/05 3:22p Felixp $
#
# $Revision: 2 $
#
# $Date: 1/18/05 3:22p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/Tools/VC6/vc6.mak $
# 
# 2     1/18/05 3:22p Felixp
# PrintDebugMessage renamed to Trace
# 
# 1     12/23/04 9:56a Felixp
# 
# 1     7/13/04 10:48a Felixp
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	vc6.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
LFLAGS = $(LFLAGS) /DLL
EXT=dll
LFLAGS = $(LFLAGS) /ENTRY:$(ENTRY_POINT)

{$(BUILD_DIR)}.dll{$(BUILD_DIR)}.efi:
	$(FWIMAGE) $(PE_TYPE) $< $@

#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2005, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************