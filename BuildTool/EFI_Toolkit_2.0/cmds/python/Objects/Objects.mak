#
# Copyright (c) 1999, 2000
# Intel Corporation.
# All rights reserved.
# 
# Redistribution and use in source and binary forms, with or without modification,
# are permitted provided that the following conditions are met:
# 
# 1. Redistributions of source code must retain the above copyright notice,
#    this list of conditions and the following disclaimer.
# 
# 2. Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.
# 
# 3. All advertising materials mentioning features or use of this software must
#    display the following acknowledgement:
# 
#    This product includes software developed by Intel Corporation and its
#    contributors.
# 
# 4. Neither the name of Intel Corporation or its contributors may be used to
#    endorse or promote products derived from this software without specific
#    prior written permission.
# 
# THIS SOFTWARE IS PROVIDED BY INTEL CORPORATION AND CONTRIBUTORS ``AS IS'' AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED.  IN NO EVENT SHALL INTEL CORPORATION OR CONTRIBUTORS BE LIABLE FOR
# ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
# ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
# 

#
# Include sdk.env environment
#

!include $(SDK_INSTALL_DIR)\build\$(SDK_BUILD_ENV)\sdk.env

#
# Set the base output name
#

BASE_NAME = Objects

#
# Globals needed by master.mak
#

TARGET_LIB = $(BASE_NAME)
SOURCE_DIR = $(SDK_INSTALL_DIR)\cmds\python\$(BASE_NAME)
BUILD_DIR  = $(SDK_BUILD_DIR)\cmds\python\$(BASE_NAME)

#
# Additional compile flags
#

C_FLAGS = /D __STDC__ $(C_FLAGS)

#
# Include paths
#

!include $(SDK_INSTALL_DIR)\include\$(EFI_INC_DIR)\makefile.hdr
INC = -I $(SDK_INSTALL_DIR)\include\$(EFI_INC_DIR) \
      -I $(SDK_INSTALL_DIR)\include\$(EFI_INC_DIR)\$(PROCESSOR) $(INC)

!include $(SDK_INSTALL_DIR)\include\bsd\makefile.hdr
INC = -I $(SDK_INSTALL_DIR)\include\bsd $(INC)

!include ..\include\makefile.hdr
INC = -I ..\include $(INC)

#
# Default target
#

all : dirs $(OBJECTS)

#
# Local include dependencies
#

#
# Library object files
#

OBJECTS = $(OBJECTS) \
    $(BUILD_DIR)\abstract.obj \
    $(BUILD_DIR)\boolobject.obj \
    $(BUILD_DIR)\bufferobject.obj \
    $(BUILD_DIR)\cellobject.obj \
    $(BUILD_DIR)\classobject.obj \
    $(BUILD_DIR)\cobject.obj \
    $(BUILD_DIR)\complexobject.obj \
    $(BUILD_DIR)\descrobject.obj \
    $(BUILD_DIR)\dictobject.obj \
    $(BUILD_DIR)\enumobject.obj \
    $(BUILD_DIR)\fileobject.obj \
    $(BUILD_DIR)\floatobject.obj \
    $(BUILD_DIR)\frameobject.obj \
    $(BUILD_DIR)\funcobject.obj \
    $(BUILD_DIR)\genobject.obj \
    $(BUILD_DIR)\intobject.obj \
    $(BUILD_DIR)\iterobject.obj \
    $(BUILD_DIR)\listobject.obj \
    $(BUILD_DIR)\longobject.obj \
    $(BUILD_DIR)\methodobject.obj \
    $(BUILD_DIR)\moduleobject.obj \
    $(BUILD_DIR)\object.obj \
    $(BUILD_DIR)\obmalloc.obj \
    $(BUILD_DIR)\rangeobject.obj \
    $(BUILD_DIR)\setobject.obj \
    $(BUILD_DIR)\sliceobject.obj \
    $(BUILD_DIR)\stringobject.obj \
    $(BUILD_DIR)\structseq.obj \
    $(BUILD_DIR)\tupleobject.obj \
    $(BUILD_DIR)\typeobject.obj \
    $(BUILD_DIR)\unicodectype.obj \
    $(BUILD_DIR)\unicodeobject.obj \
    $(BUILD_DIR)\weakrefobject.obj \
        

#
# Source file dependencies
#


#
# Handoff to master.mak
#

!include $(SDK_INSTALL_DIR)\build\master.mak