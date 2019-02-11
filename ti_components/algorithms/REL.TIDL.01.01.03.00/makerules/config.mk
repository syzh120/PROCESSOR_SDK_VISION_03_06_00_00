#
# Copyright (C) 2018 Texas Instruments Incorporated - http://www.ti.com/
#
#
#  Redistribution and use in source and binary forms, with or without
#  modification, are permitted provided that the following conditions
#  are met:
#
#    Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#
#    Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the  
#    distribution.
#
#    Neither the name of Texas Instruments Incorporated nor the names of
#    its contributors may be used to endorse or promote products derived
#    from this software without specific prior written permission.
#
#  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
#  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
#  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
#  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
#  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
#  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
#  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
#  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
#  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
#  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
#  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#

DSP_TOOLS           ?="/datalocal1/ti_components/cg_tools/linux/C6000_7.4.2"
ARP32_TOOLS         ?="/datalocal1/ti_components/cg_tools/linux/arp32_1.0.7"
TIARM_TOOLS         ?="/datalocal1/ti_components/cg_tools/linux/ti-cgt-arm_5.2.5"
XDAIS_PATH          ?="/datalocal1/ti_components/codecs/xdais_7_24_00_04"
UTILS_PATH          ?="C:\ti\ccsv5\utils\cygwin"
VXLIB_PATH          ?="/datalocal1/ti_components/algorithms/vxlib_c66x_1_1_1_0"
DMAUTILS_PATH       ?=/datalocal1/ti_components/algorithms/REL.DMAUTILS.00.08.00.02/dmautils
ALGFRAMEWORK_PATH   ?=a0393754@bangvideoapps01:/datalocal1/ti_components/algorithms/REL.ALGFRAMEWORK.02.08.00.00/algframework
MATHLIB_INSTALL_DIR ?="/datalocal1/ti_components/algorithms/mathlib_c66x_3_1_0_0"
SHOW_COMMANDS       ?= 0
LINUXENV            ?= x86
LINUX_BUILD_TOOLS   ?="/home/uid/tools/linaro-2017.11"

# Default platform
# Supported values: vayu,vme
TARGET_SOC ?= vayu

# Default CORE is dsp
# Supported values: dsp, eve, arm
CORE ?= dsp

# Default TI_DEVICE
# Supported values: PC, TI_DEVICE (SIMULATORS or EMULATOR )
TARGET_PLATFORM ?= TI_DEVICE

# Default C66
# Supported C64T, C64P, C64, C66, C674, C67, C67P, m4
TARGET_CPU ?= C66

ifeq ($(CORE),eve)
TARGET_CPU:=
endif
