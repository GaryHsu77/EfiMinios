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
# Set the base output name and type for this makefile
#

BASE_NAME = ftp

#
# Set entry point
#
!IFDEF OLD_SHELL
IMAGE_ENTRY_POINT = _LIBC_Start_Shellapp_A
!ELSE
IMAGE_ENTRY_POINT = _LIBC_Start_A
!ENDIF

#
# Globals needed by master.mak
#

TARGET_APP = $(BASE_NAME)
SOURCE_DIR = $(SDK_INSTALL_DIR)\cmds\$(BASE_NAME)
BUILD_DIR  = $(SDK_BUILD_DIR)\cmds\$(BASE_NAME)

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

#
# Libraries
#

LIBS = $(LIBS) \
       $(SDK_BUILD_DIR)\lib\libc\libc.lib \
       $(SDK_BUILD_DIR)\lib\libsocket\libsocket.lib \
!IFDEF OLD_SHELL
       $(SDK_BUILD_DIR)\lib\libefi\libefi.lib \
       $(SDK_BUILD_DIR)\lib\libefishell\libefishell.lib \
!ENDIF

#
# Default target
#

all : dirs $(LIBS) $(OBJECTS)

#
# Application object files
#

OBJECTS = $(OBJECTS) \
    $(BUILD_DIR)\cmds.obj \
    $(BUILD_DIR)\cmdtab.obj \
    $(BUILD_DIR)\complete.obj \
    $(BUILD_DIR)\domacro.obj \
    $(BUILD_DIR)\efimisc.obj \
    $(BUILD_DIR)\fetch.obj \
    $(BUILD_DIR)\ftp.obj \
    $(BUILD_DIR)\main.obj \
    $(BUILD_DIR)\ruserpass.obj \
    $(BUILD_DIR)\util.obj \

#
# Source file dependencies
#

$(BUILD_DIR)\cmds.obj      : $(*B).c $(INC_DEPS) ftp_var.h efimisc.h pathnames.h
$(BUILD_DIR)\cmdtab.obj    : $(*B).c $(INC_DEPS) ftp_var.h
$(BUILD_DIR)\complete.obj  : $(*B).c $(INC_DEPS) ftp_var.h
$(BUILD_DIR)\domacro.obj   : $(*B).c $(INC_DEPS) ftp_var.h
$(BUILD_DIR)\efimisc.obj   : $(*B).c $(INC_DEPS) efimisc.h histedit.h
$(BUILD_DIR)\fetch.obj     : $(*B).c $(INC_DEPS) ftp_var.h
$(BUILD_DIR)\ftp.obj       : $(*B).c $(INC_DEPS) ftp_var.h efimisc.h
$(BUILD_DIR)\main.obj      : $(*B).c $(INC_DEPS) ftp_var.h efimisc.h pathnames.h
$(BUILD_DIR)\ruserpass.obj : $(*B).c $(INC_DEPS) ftp_var.h
$(BUILD_DIR)\util.obj      : $(*B).c $(INC_DEPS) ftp_var.h efimisc.h pathnames.h

#
# Handoff to master.mak
#

!include $(SDK_INSTALL_DIR)\build\master.mak
