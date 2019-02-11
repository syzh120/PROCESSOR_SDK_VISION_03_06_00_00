#
#   Copyright (c) 2015, Texas Instruments Incorporated
#
#   Redistribution and use in source and binary forms, with or without
#   modification, are permitted provided that the following conditions
#   are met:
#
#   *  Redistributions of source code must retain the above copyright
#      notice, this list of conditions and the following disclaimer.
#
#   *  Redistributions in binary form must reproduce the above copyright
#      notice, this list of conditions and the following disclaimer in the
#      documentation and/or other materials provided with the distribution.
#
#   *  Neither the name of Texas Instruments Incorporated nor the names of
#      its contributors may be used to endorse or promote products derived
#      from this software without specific prior written permission.
#
#   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
#   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
#   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
#   PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
#   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
#   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
#   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
#   OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
#   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
#   OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
#   EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#

# Override the build verbosity here
#   V=0: least verbose
#   V=1: most verbose
ifneq ($(V),1)
MAKE = @$(MAKE_COMMAND) --no-print-directory
RM_HOST := @$(RM_HOST)
ifeq ($(V),0)
CCPREF := @$(CCPREF)
ASPREF := @$(ASPREF)
LDPREF := @$(LDPREF)
ARPREF := @$(ARPREF) 2>/dev/null
UMPREF := @$(UMPREF)
MKASMOFF_HOST := @$(MKASMOFF_HOST)
else
QUIET_ROOT := $(PROJECT_ROOT)
CCPREF_CMD := $(CCPREF)
CCPREF = @echo "Compiling " $(<:$(QUIET_ROOT)/%=%) && $(CCPREF_CMD)
ASPREF_CMD := $(ASPREF)
ASPREF = @echo "Assembling" $(<:$(QUIET_ROOT)/%=%) && $(ASPREF_CMD)
LDPREF_CMD := $(LDPREF)
LDPREF = @echo "Linking   " $(@:$(QUIET_ROOT)/%=%) && $(LDPREF_CMD)
ARPREF_CMD := $(ARPREF) 2>/dev/null
ARPREF = @echo "Archiving " $(@:$(QUIET_ROOT)/%=%) && $(ARPREF_CMD)
UMPREF_CMD := $(UMPREF)
UMPREF = @echo "Usemsg     " $(@:$(QUIET_ROOT)/%=%) && $(UMPREF_CMD)
MKASMOFF_CMD := $(MKASMOFF_HOST)
MKASMOFF_HOST = @echo "Generating" $(CURDIR:$(QUIET_ROOT)/%=%)/$@ && \
    $(MKASMOFF_CMD)
endif
endif
