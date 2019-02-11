#
#  Copyright (c) 2012, Texas Instruments Incorporated
#  All rights reserved.
#
#  Redistribution and use in source and binary forms, with or without
#  modification, are permitted provided that the following conditions
#  are met:
#
#  *  Redistributions of source code must retain the above copyright
#     notice, this list of conditions and the following disclaimer.
#
#  *  Redistributions in binary form must reproduce the above copyright
#     notice, this list of conditions and the following disclaimer in the
#     documentation and/or other materials provided with the distribution.
#
#  *  Neither the name of Texas Instruments Incorporated nor the names of
#     its contributors may be used to endorse or promote products derived
#     from this software without specific prior written permission.
#
#  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
#  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
#  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
#  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
#  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
#  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
#  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
#  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
#  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
#  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
#  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
#

#
#  ======== xdcrules.mak ========
#  definition of XDC rules
#

# If not set in the environment, set XDCOPTIONS to verbose (the 'v' option)
XDCOPTIONS ?= v

# JOBS is the max number of parallel build commands to run concurrently.
# You can often get a build performance lift by setting JOBS to a value > 1,
# however debugging build errors is tough(!), so the default setting is 1.
JOBS ?= 1


# This command actually performs the build.
#
# Note that $(XDCARGS) is set in xdcpaths.mak
# Note also that we explicitly set XDCBUILDCFG to the one in
# examples/_config.bld so we don't inadvertantly pick up any other config.bld
# found along XDCPATH.

all:
%::
	"$(XDC_INSTALL_DIR)/xdc" --jobs=$(JOBS) \
            XDCBUILDCFG="$(FC_INSTALL_DIR)/framework_components.bld" \
            XDCPATH="$(XDC_PATH)" \
            XDCOPTIONS=$(XDCOPTIONS) XDCARGS="$(XDCARGS)" $@ -PD .
