#
# Copyright (c) 2013-2017, Texas Instruments Incorporated
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
# *  Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#
# *  Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#
# *  Neither the name of Texas Instruments Incorporated nor the names of
#    its contributors may be used to endorse or promote products derived
#    from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
# THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
# PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
# EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
# OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
# WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
# OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
# EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#

# Filename: platform.mk
#
# Platforms make file - Board/SoC/targets are defined/derived in this file
#
# This file needs to change when:
#     1. a new Board/SoC is added, which also might have its own cores/ISAs
#

#
# Derive SOC from BOARD
#

# TDA2XX
ifeq ($(BOARD),$(filter $(BOARD), tda2xx-evm tda2xx-mc tda2xx-evm-radar tda2xx-rvp tda2xx-cascade-radar))
 SOC = tda2xx
 SBL_RUN_ADDRESS=0x40300000
 SBL_DEV_ID=55
endif

# TDA2PX
ifeq ($(BOARD),$(filter $(BOARD), tda2px-evm tda2px-evm-radar))
 SOC = tda2px
 SBL_RUN_ADDRESS=0x40300000
 SBL_DEV_ID=88
endif

# DRA75X
ifeq ($(BOARD),$(filter $(BOARD), evmDRA75x dra75x))
 SOC = dra75x
 SBL_RUN_ADDRESS=0x40300000
 SBL_DEV_ID=55
endif

# AM572X
ifeq ($(BOARD),$(filter $(BOARD), am572x-evm am572x-idk evmAM572x idkAM572x))
 SOC = am572x
endif

# AM574X
ifeq ($(BOARD),$(filter $(BOARD), am574x-idk idkAM574x))
 SOC = am574x
endif

# TDA2EX
ifeq ($(BOARD),$(filter $(BOARD), tda2ex-evm tda2ex-eth-srv))
 SOC = tda2ex
 SBL_RUN_ADDRESS=0x40300000
 SBL_DEV_ID=66
endif

# DRA72x
ifeq ($(BOARD),$(filter $(BOARD), evmDRA72x dra72x))
 SOC = dra72x
 SBL_RUN_ADDRESS=0x40300000
 SBL_DEV_ID=66
endif

# AM571X
ifeq ($(BOARD),$(filter $(BOARD), am571x-evm  idkAM571x))
 SOC = am571x
endif

# TDA3XX
ifeq ($(BOARD),$(filter $(BOARD), tda3xx-evm tda3xx-rvp tda3xx-evm-radar tda3xx-ar12-booster tda3xx-ar12-alps tda3xx-ar12-rvp))
 SOC = tda3xx
 SBL_RUN_ADDRESS=0x00300000
 SBL_DEV_ID=77
endif

# DRA78X
ifeq ($(BOARD),$(filter $(BOARD), evmDRA78x))
 SOC = dra78x
 SBL_RUN_ADDRESS=0x00300000
 SBL_DEV_ID=77
endif

# K2H
ifeq ($(BOARD),$(filter $(BOARD),  evmK2H))
 SOC = k2h
endif

# K2K
ifeq ($(BOARD),$(filter $(BOARD),  evmK2K))
 SOC = k2k
endif

# K2L
ifeq ($(BOARD),$(filter $(BOARD),  evmK2L))
 SOC = k2l
endif

# K2E
ifeq ($(BOARD),$(filter $(BOARD),  evmK2E))
 SOC = k2e
endif

# C6657
ifeq ($(BOARD),$(filter $(BOARD),  evmC6657))
 SOC = c6657
endif

# C6678
ifeq ($(BOARD),$(filter $(BOARD),  evmC6678))
 SOC = c6678
endif

# k2g
ifeq ($(BOARD),$(filter $(BOARD),  evmK2G iceK2G))
 SOC = k2g
endif

# am335x
ifeq ($(BOARD),$(filter $(BOARD),  evmAM335x icev2AM335x iceAMIC110 skAM335x bbbAM335x))
 SOC = am335x
endif

# am437x
ifeq ($(BOARD),$(filter $(BOARD),  evmAM437x idkAM437x skAM437x))
 SOC = am437x
endif

# omapl137
ifeq ($(BOARD),$(filter $(BOARD),  evmOMAPL137))
 SOC = omapl137
endif

# omapl138
ifeq ($(BOARD),$(filter $(BOARD),  lcdkOMAPL138))
 SOC = omapl138
endif

#
# Derive Target/ISA from CORE
#

# a8host
ifeq ($(CORE),a8host)
 ISA = a8
 ISA_EXT = a8
 ARCH = armv7a
endif

# a9host
ifeq ($(CORE),a9host)
 ISA = a9
 ISA_EXT = a9
 ARCH = armv7a
endif

# arm9_0
ifeq ($(CORE),arm9_0)
 ISA = arm9
 ISA_EXT = ae9
 ARCH = armv5
endif

# pru_0 and pru_1
ifeq ($(CORE),$(filter $(CORE), pru_0 pru_1))
 ISA = pru
 ISA_EXT = pru
 ifeq ($(CORE),pru_0)
  ARCH = PRU0
 else
  ARCH = PRU1
 endif
endif

# a15_0
ifeq ($(CORE),a15_0)
 ISA = a15
 ISA_EXT = a15
 ARCH = armv7a
endif

# ipu1_0/ipu1_1/ipu2_0/ipu2_1
ifeq ($(CORE),$(filter $(CORE), ipu1_0 ipu1_1 ipu2_0 ipu2_1))
 ISA = m4
 ISA_EXT = m4
 ARCH = armv7m
endif

# EVE
ifeq ($(CORE),$(filter $(CORE), arp32_1 arp32_2 arp32_3 arp32_4))
 ISA = arp32
 ISA_EXT = arp32
 ARCH = arp32
endif

# DSP for tda2xx/tda2px/am572x/tda2ex/dra72x/dra75x/am571x/tda3xx/dra78x/k2h/k2k/k2l/k2e/c6657/c6678/am574x
ifeq ($(CORE),$(filter $(CORE), c66x c66xdsp_1 c66xdsp_2))
 ISA = c66
 ISA_EXT = 66
 ARCH = c66x
endif

# C67x DSP
ifeq ($(CORE),c67x)
 ISA = c674
 ISA_EXT = 674
 ARCH = c67x
endif

# C674x DSP
ifeq ($(CORE),c674x)
 ISA = c674
 ISA_EXT = 674
 ARCH = c67x
endif

# a8host
ifeq ($(CORE),a8host)
 ISA = a8
 ISA_EXT = a8
 ARCH = armv7a
endif

#
# Derive XDC/ISA specific settings
#

ifeq ($(ISA),a15)
  TARGET_XDC = gnu.targets.arm.A15F
  ifeq ($(PLATFORM_XDC),)
    PLATFORM_XDC = "ti.platforms.evmDRA7XX:Cortex_A15"
    
    ifeq ($(BOARD),$(filter $(BOARD), evmAM572x))
      PLATFORM_XDC = "ti.platforms.evmAM572X"
    endif
    
    ifeq ($(BOARD),$(filter $(BOARD), idkAM572x))
      PLATFORM_XDC = "ti.platforms.idkAM572X"
    endif
    
    ifeq ($(BOARD),$(filter $(BOARD), idkAM574x))
      PLATFORM_XDC = "ti.platforms.idkAM572X"
    endif
    
    ifeq ($(BOARD),$(filter $(BOARD), idkAM571x))
      PLATFORM_XDC = "ti.platforms.idkAM571X"
    endif
    
    ifeq ($(SOC),$(filter $(SOC), k2h))
        PLATFORM_XDC = "ti.platforms.evmTCI6636K2H:Cortex A.66AK2H12"
    endif
    
    ifeq ($(SOC),$(filter $(SOC), k2k))
        PLATFORM_XDC = "ti.platforms.evmTCI6638K2K:Cortex A.TCI6638K2K"
    endif
    
    ifeq ($(SOC),$(filter $(SOC), k2g))
        PLATFORM_XDC = "ti.platforms.evmTCI66AK2G02"
    endif
  endif

  ENDIAN_EXT = fg
  FORMAT_EXT =

  # Define the file extensions
  OBJEXT = o$(FORMAT_EXT)$(ISA_EXT)$(ENDIAN_EXT)
  LIBEXT = a$(FORMAT_EXT)$(ISA_EXT)$(ENDIAN_EXT)
  EXEEXT = x$(FORMAT_EXT)$(ISA_EXT)$(ENDIAN_EXT)
  ASMEXT = s$(FORMAT_EXT)$(ISA_EXT)$(ENDIAN_EXT)
endif

ifeq ($(ISA),m4)
  ifeq ($(FORMAT),ELF)
    TARGET_XDC = ti.targets.arm.elf.M4
    FORMAT_EXT = e
  else
    TARGET_XDC = ti.targets.arm.M4
  endif
  ifeq ($(PLATFORM_XDC),)
    ifeq ($(SOC),$(filter $(SOC), dra72x dra75x tda2xx tda2px tda2ex am572x am571x am574x))
      ifeq ($(CORE),$(filter $(CORE), ipu1_0 ipu2_0))
        PLATFORM_XDC = "ti.platforms.evmDRA7XX"
      else
        PLATFORM_XDC = "ti.platforms.evmDRA7XX"
      endif
    endif
    
    ifeq ($(BOARD),$(filter $(BOARD), evmAM572x))
      PLATFORM_XDC = "ti.platforms.evmAM572X"
    endif
    
    ifeq ($(BOARD),$(filter $(BOARD), idkAM572x))
      PLATFORM_XDC = "ti.platforms.idkAM572X"
    endif
    
    ifeq ($(BOARD),$(filter $(BOARD), idkAM571x))
      PLATFORM_XDC = "ti.platforms.idkAM571X"
    endif
    
    ifeq ($(BOARD),$(filter $(BOARD), idkAM574x))
      PLATFORM_XDC = "ti.platforms.idkAM572X"
    endif
    
    ifeq ($(SOC),$(filter $(SOC), tda3xx dra78x))
      ifeq ($(CORE),ipu1_0)
        PLATFORM_XDC = "ti.platforms.evmTDA3XX:IPU_1_0"
      else
        PLATFORM_XDC = "ti.platforms.evmTDA3XX:IPU_1_1"
      endif
    endif
  endif

  # If ENDIAN is set to "big", set ENDIAN_EXT to "e", that would be used in
  #    in the filename extension of object/library/executable files
  ifeq ($(ENDIAN),big)
    ENDIAN_EXT = e
  endif

  # Define the file extensions
  OBJEXT = o$(FORMAT_EXT)$(ISA_EXT)$(ENDIAN_EXT)
  LIBEXT = a$(FORMAT_EXT)$(ISA_EXT)$(ENDIAN_EXT)
  EXEEXT = x$(FORMAT_EXT)$(ISA_EXT)$(ENDIAN_EXT)
  ASMEXT = s$(FORMAT_EXT)$(ISA_EXT)$(ENDIAN_EXT)
endif


#########DSP Support############
ifeq ($(ISA),c66)
  ifeq ($(FORMAT),ELF)
    TARGET_XDC = ti.targets.elf.C66
    FORMAT_EXT = e
  else
    TARGET_XDC = ti.targets.C66
  endif
  ifeq ($(PLATFORM_XDC),)
    ifeq ($(SOC),$(filter $(SOC), dra72x dra75x tda2xx tda2px tda2ex am571x am574x))
      ifeq ($(CORE),c66x)
        PLATFORM_XDC = "ti.platforms.evmDRA7XX"
      else
        PLATFORM_XDC = "ti.platforms.evmDRA7XX"
      endif
    endif
    
    ifeq ($(SOC),$(filter $(SOC), am572x))
      PLATFORM_XDC = "ti.platforms.evmAM572X"
    endif
    
    ifeq ($(BOARD),$(filter $(BOARD), evmAM572x))
      PLATFORM_XDC = "ti.platforms.evmAM572X"
    endif
    
    ifeq ($(BOARD),$(filter $(BOARD), idkAM572x))
      PLATFORM_XDC = "ti.platforms.idkAM572X"
    endif
    
    ifeq ($(BOARD),$(filter $(BOARD), idkAM571x))
      PLATFORM_XDC = "ti.platforms.idkAM571X"
    endif
    
    ifeq ($(BOARD),$(filter $(BOARD), idkAM574x))
      PLATFORM_XDC = "ti.platforms.idkAM572X"
    endif
    
    ifeq ($(SOC),$(filter $(SOC), tda3xx dra78x))
      ifeq ($(CORE),$(filter $(CORE), c66x c66xdsp_1 c66xdsp_2))
        PLATFORM_XDC = "ti.platforms.evmTDA3XX"
      else
        PLATFORM_XDC = "ti.platforms.evmTDA3XX"
      endif
    endif
    
    ifeq ($(SOC),k2h)
      PLATFORM_XDC = "ti.platforms.evmTCI6636K2H"
    endif
    
    ifeq ($(SOC),k2k)
      PLATFORM_XDC = "ti.platforms.evmTCI6638K2K"
    endif
    
    ifeq ($(SOC),k2g)
      PLATFORM_XDC = "ti.platforms.evmTCI66AK2G02"
    endif
  endif

  # If ENDIAN is set to "big", set ENDIAN_EXT to "e", that would be used in
  #    in the filename extension of object/library/executable files
  ifeq ($(ENDIAN),big)
    ENDIAN_EXT = e
  endif

  # Define the file extensions
  OBJEXT = o$(FORMAT_EXT)$(ISA_EXT)$(ENDIAN_EXT)
  LIBEXT = a$(FORMAT_EXT)$(ISA_EXT)$(ENDIAN_EXT)
  EXEEXT = x$(FORMAT_EXT)$(ISA_EXT)$(ENDIAN_EXT)
  ASMEXT = s$(FORMAT_EXT)$(ISA_EXT)$(ENDIAN_EXT)
endif

ifeq ($(ISA),arp32)
  ifeq ($(FORMAT),ELF)
    ENDIAN_EXT = F
    FORMAT_EXT = e
  endif

  # If ENDIAN is set to "big", set ENDIAN_EXT to "e", that would be used in
  #    in the filename extension of object/library/executable files
  ifeq ($(ENDIAN),big)
    ENDIAN_EXT = e
  endif

  # Define the file extensions
  OBJEXT = o$(FORMAT_EXT)$(ISA_EXT)$(ENDIAN_EXT)
  LIBEXT = a$(FORMAT_EXT)$(ISA_EXT)$(ENDIAN_EXT)
  EXEEXT = x$(FORMAT_EXT)$(ISA_EXT)$(ENDIAN_EXT)
  ASMEXT = s$(FORMAT_EXT)$(ISA_EXT)$(ENDIAN_EXT)
endif

ifeq ($(ISA),a8)
  TARGET_XDC = gnu.targets.arm.A8F

  PLATFORM_XDC = "ti.platforms.evmAM3359"

  ENDIAN_EXT = fg
  FORMAT_EXT =

  # Define the file extensions
  OBJEXT = o$(FORMAT_EXT)$(ISA_EXT)$(ENDIAN_EXT)
  LIBEXT = a$(FORMAT_EXT)$(ISA_EXT)$(ENDIAN_EXT)
  EXEEXT = x$(FORMAT_EXT)$(ISA_EXT)$(ENDIAN_EXT)
  ASMEXT = s$(FORMAT_EXT)$(ISA_EXT)$(ENDIAN_EXT)
endif

ifeq ($(ISA),pru)

  ENDIAN_EXT =
  FORMAT_EXT =

  # Define the file extensions
  OBJEXT = o$(FORMAT_EXT)$(ISA_EXT)$(ENDIAN_EXT)
  HEADEREXT = h$(FORMAT_EXT)$(ENDIAN_EXT)
  OUTEXT = out
endif

ifeq ($(ISA),a9)
  TARGET_XDC = gnu.targets.arm.A9F

  PLATFORM_XDC = "ti.platforms.evmAM437X"

  ENDIAN_EXT = fg
  FORMAT_EXT =

  # Define the file extensions
  OBJEXT = o$(FORMAT_EXT)$(ISA_EXT)$(ENDIAN_EXT)
  LIBEXT = a$(FORMAT_EXT)$(ISA_EXT)$(ENDIAN_EXT)
  EXEEXT = x$(FORMAT_EXT)$(ISA_EXT)$(ENDIAN_EXT)
  ASMEXT = s$(FORMAT_EXT)$(ISA_EXT)$(ENDIAN_EXT)
endif

ifeq ($(ISA),arm9)
  TARGET_XDC = ti.targets.arm.elf.Arm9
  FORMAT_EXT =
 ifeq ($(SOC),$(filter $(SOC), omapl137))
  PLATFORM_XDC = "ti.platforms.evmOMAPL137"
 endif

 ifeq ($(SOC),$(filter $(SOC), omapl138))
  PLATFORM_XDC = "ti.platforms.evmOMAPL138"
 endif

  # Define the file extensions
  OBJEXT = o$(FORMAT_EXT)$(ISA_EXT)$(ENDIAN_EXT)
  LIBEXT = $(FORMAT_EXT)$(ISA_EXT)$(ENDIAN_EXT)
  EXEEXT = x$(FORMAT_EXT)$(ISA_EXT)$(ENDIAN_EXT)
  ASMEXT = s$(FORMAT_EXT)$(ISA_EXT)$(ENDIAN_EXT)
endif

#########DSP Support - c67xx ############
ifeq ($(ISA),c674)
  ifeq ($(FORMAT),ELF)
    TARGET_XDC = ti.targets.elf.C674
    FORMAT_EXT = e
  else
    TARGET_XDC = ti.targets.C674
  endif

  ifeq ($(SOC),$(filter $(SOC), omapl137))
    ifeq ($(CORE),c674x)
      PLATFORM_XDC = "ti.platforms.evmOMAPL137"
    endif
  endif

  ifeq ($(SOC),$(filter $(SOC), omapl138))
    ifeq ($(CORE),c674x)
      PLATFORM_XDC = "ti.platforms.evmOMAPL138"
    endif
  endif

  # Define the file extensions
  OBJEXT = o$(FORMAT_EXT)$(ISA_EXT)$(ENDIAN_EXT)
  LIBEXT = a$(FORMAT_EXT)$(ISA_EXT)$(ENDIAN_EXT)
  EXEEXT = x$(FORMAT_EXT)$(ISA_EXT)$(ENDIAN_EXT)
  ASMEXT = s$(FORMAT_EXT)$(ISA_EXT)$(ENDIAN_EXT)
endif

ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px tda2ex dra72x dra75x))
  SBL_CORE_ID_a15_0 = 0
  SBL_CORE_ID_a15_1 = 1
  SBL_CORE_ID_ipu1_0 = 2
  SBL_CORE_ID_ipu1_1 = 3
  SBL_CORE_ID_ipu1 = 4
  SBL_CORE_ID_ipu2_0 = 5
  SBL_CORE_ID_ipu2_1 = 6
  SBL_CORE_ID_ipu2 = 7
  SBL_CORE_ID_c66x = 8
  SBL_CORE_ID_c66xdsp_1 = 8
  SBL_CORE_ID_c66xdsp_2 = 9
  SBL_CORE_ID_arp32_1 = 10
  SBL_CORE_ID_arp32_2 = 11
  SBL_CORE_ID_arp32_3 = 12
  SBL_CORE_ID_arp32_4 = 13
endif

ifeq ($(SOC),$(filter $(SOC), tda3xx dra78x))
  SBL_CORE_ID_ipu1_0 = 2
  SBL_CORE_ID_ipu1_1 = 3
  SBL_CORE_ID_ipu1 = 14
  SBL_CORE_ID_c66x = 6
  SBL_CORE_ID_c66xdsp_1 = 6
  SBL_CORE_ID_c66xdsp_2 = 7
  SBL_CORE_ID_arp32_1 = 8
endif

export SOC
export ARCH

# Nothing beyond this point
