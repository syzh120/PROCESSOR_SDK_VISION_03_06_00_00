# Filename: platform.mk
#
# Platforms make file - Platform/SoC/targets are defined/derived in this file
#
# This file needs to change when:
#     1. a new platform/SoC is added, which also might have its own cores/ISAs
#

#
# Derive SOC from PLATFORM
#

# TDA2XX EVM
ifeq ($(PLATFORM),$(filter $(PLATFORM), tda2xx-evm tda2xx-rvp))
 SOC = tda2xx
 SOCFAMILY = tda2xx
endif

# TDA2PX EVM
ifeq ($(PLATFORM),tda2px-evm)
 SOC = tda2px
 SOCFAMILY = tda2xx
endif

# TDA3XX EVM
ifeq ($(PLATFORM),$(filter $(PLATFORM), tda3xx-evm tda3xx-rvp))
 SOC = tda3xx
 SOCFAMILY = tda3xx
endif

# TDA2EX EVM
ifeq ($(PLATFORM),tda2ex-evm)
 SOC = tda2ex
 SOCFAMILY = tda2xx
endif


# Derive Target/ISA from CORE

# m3vpss
ifeq ($(CORE),m3vpss)
 ISA = m3
 ARCH = armv7m
endif

# m3video
ifeq ($(CORE),m3video)
 ISA = m3
 ARCH = armv7m
endif

# m4
ifeq ($(CORE),m4)
 ISA = m4
 ARCH = armv7m
endif

# m4vpss
ifeq ($(CORE),m4vpss)
 ISA = m4
 ARCH = armv7m
endif

# m4video
ifeq ($(CORE),m4video)
 ISA = m4
 ARCH = armv7m
endif

# ipu1_0
ifeq ($(CORE),ipu1_0)
 ISA = m4
 ARCH = armv7m
endif

# ipu1_1
ifeq ($(CORE),ipu1_1)
 ISA = m4
 ARCH = armv7m
endif

# ipu2
ifeq ($(CORE),ipu2)
 ISA = m4
 ARCH = armv7m
endif

# ipu2_0
ifeq ($(CORE),ipu2_0)
 ISA = m4
 ARCH = armv7m
endif

# a8host
ifeq ($(CORE),a8host)
 ISA = a8
 ARCH = armv7a
endif

# DSP
ifeq ($(CORE),c6xdsp)
 ISA = 674
 ARCH = c67x
endif

# DSP for tda2xx
ifeq ($(CORE),c66x)
 ISA = 66
 ARCH = c66x
endif

# DSP for tda2xx
ifeq ($(CORE),c66xdsp)
 ISA = 66
 ARCH = c66x
endif

# DSP for Vayu
ifeq ($(CORE),c66xdsp_1)
 ISA = 66
 ARCH = c66x
endif

ifeq ($(CORE),c66xdsp_2)
 ISA = 66
 ARCH = c66x
endif

# EVE
ifeq ($(CORE),arp32_1)
 ISA = arp32
 ARCH = arp32
endif

ifeq ($(CORE),arp32_2)
 ISA = arp32
 ARCH = arp32
endif

ifeq ($(CORE),arp32_3)
 ISA = arp32
 ARCH = arp32
endif

ifeq ($(CORE),arp32_4)
 ISA = arp32
 ARCH = arp32
endif

# a15_0
ifeq ($(CORE),a15_0)
 ISA = a15
 ARCH = armv7a
endif

ifeq ($(CORE),a15host)
 ISA = a15
 ARCH = armv7a
endif
#
# Derive XDC/ISA specific settings
#

ifeq ($(ISA),m4)
  ifeq ($(FORMAT),ELF)
    TARGET_XDC = ti.targets.arm.elf.M4
    FORMAT_EXT = e
  else
    TARGET_XDC = ti.targets.arm.M4
  endif

  ifeq ($(SOCFAMILY),tda2xx)
    ifeq ($(CORE),m4video)
      PLATFORM_XDC = "ti.platforms.evmDRA7XX:IPU_1_1"
    endif
    ifeq ($(CORE),m4vpss)
      PLATFORM_XDC = "ti.platforms.evmDRA7XX:IPU_1_0"
    endif
  endif

  ifeq ($(SOCFAMILY),tda2xx)
    ifeq ($(CORE),ipu1_1)
      PLATFORM_XDC = "ti.platforms.evmDRA7XX:IPU_1_1"
    endif
    ifeq ($(CORE),ipu1_0)
      PLATFORM_XDC = "ti.platforms.evmDRA7XX:IPU_1_0"
    endif
    ifeq ($(CORE),ipu2)
      PLATFORM_XDC = "ti.platforms.evmDRA7XX:IPU_2"
    endif
  endif

  ifeq ($(SOCFAMILY),tda3xx)
    ifeq ($(CORE),m4video)
      PLATFORM_XDC = "ti.platforms.evmTDA3XX:IPU_1_1"
    endif
    ifeq ($(CORE),m4vpss)
      PLATFORM_XDC = "ti.platforms.evmTDA3XX:IPU_1_0"
    endif
  endif

  ifeq ($(SOCFAMILY),tda3xx)
    ifeq ($(CORE),ipu1_1)
      PLATFORM_XDC = "ti.platforms.evmTDA3XX:IPU_1_1"
    endif
    ifeq ($(CORE),ipu1_0)
      PLATFORM_XDC = "ti.platforms.evmTDA3XX:IPU_1_0"
    endif
  endif

  # If ENDIAN is set to "big", set ENDIAN_EXT to "e", that would be used in
  #    in the filename extension of object/library/executable files
  ifeq ($(ENDIAN),big)
    ENDIAN_EXT = e
  endif

  # Define the file extensions
  OBJEXT = o$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)
  LIBEXT = a$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)
  EXEEXT = x$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)
  ASMEXT = s$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)
endif


ifeq ($(SOCFAMILY),tda2xx)
	ifeq ($(ISA),a15)
	  TARGET_XDC = gnu.targets.arm.A15F
	  PLATFORM_XDC = "ti.platforms.evmDRA7XX:Cortex_A15"

	  ENDIAN_EXT = fg
	  FORMAT_EXT =

	  # Define the file extensions
	  OBJEXT = o$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)
	  LIBEXT = a$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)
	  EXEEXT = x$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)
	  ASMEXT = s$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)
	endif
endif

ifeq ($(ISA),66)
  ifeq ($(FORMAT),ELF)
    TARGET_XDC = ti.targets.elf.C66
    FORMAT_EXT = e
  else
    TARGET_XDC = ti.targets.C66
  endif

  ifeq ($(SOCFAMILY),tda2xx)
    ifeq ($(CORE),c66xdsp)
      PLATFORM_XDC = "ti.platforms.evmDRA7XX:DSP_1"
    endif
  endif

  ifeq ($(SOCFAMILY),tda2xx)
    ifeq ($(CORE),c66xdsp_1)
      PLATFORM_XDC = "ti.platforms.evmDRA7XX:DSP_1"
    endif
    ifeq ($(CORE),c66xdsp_2)
      PLATFORM_XDC = "ti.platforms.evmDRA7XX:DSP_2"
    endif
  endif

  ifeq ($(SOCFAMILY),tda3xx)
    ifeq ($(CORE),c66xdsp)
      PLATFORM_XDC = "ti.platforms.evmTDA3XX:DSP_1"
    endif
  endif

  ifeq ($(SOCFAMILY),tda3xx)
    ifeq ($(CORE),c66xdsp_1)
      PLATFORM_XDC = "ti.platforms.evmTDA3XX:DSP_1"
    endif
    ifeq ($(CORE),c66xdsp_2)
      PLATFORM_XDC = "ti.platforms.evmTDA3XX:DSP_2"
    endif
  endif


  # If ENDIAN is set to "big", set ENDIAN_EXT to "e", that would be used in
  #    in the filename extension of object/library/executable files
  ifeq ($(ENDIAN),big)
    ENDIAN_EXT = e
  endif

  # Define the file extensions
  OBJEXT = o$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)
  LIBEXT = a$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)
  EXEEXT = x$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)
  ASMEXT = s$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)
endif


ifeq ($(ISA),arp32)
  ifeq ($(FORMAT),ELF)
    TARGET_XDC = ti.targets.arp32.elf.ARP32_far
    ENDIAN_EXT = F
    FORMAT_EXT = e
  else
    TARGET_XDC = ti.targets.arp32
  endif

  ifeq ($(SOCFAMILY),tda2xx)
    ifeq ($(CORE),arp32_1)
      PLATFORM_XDC = "ti.platforms.evmDRA7XX:EVE_1"
    endif
    ifeq ($(CORE),arp32_2)
      PLATFORM_XDC = "ti.platforms.evmDRA7XX:EVE_2"
    endif
    ifeq ($(CORE),arp32_3)
      PLATFORM_XDC = "ti.platforms.evmDRA7XX:EVE_3"
    endif
    ifeq ($(CORE),arp32_4)
      PLATFORM_XDC = "ti.platforms.evmDRA7XX:EVE_4"
    endif
  endif

  ifeq ($(SOCFAMILY),tda3xx)
    ifeq ($(CORE),arp32_1)
      PLATFORM_XDC = "ti.platforms.evmTDA3XX:EVE_1"
    endif
  endif

  # If ENDIAN is set to "big", set ENDIAN_EXT to "e", that would be used in
  #    in the filename extension of object/library/executable files
  ifeq ($(ENDIAN),big)
    ENDIAN_EXT = e
  endif

  # Define the file extensions
  OBJEXT = o$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)
  LIBEXT = a$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)
  EXEEXT = x$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)
  ASMEXT = s$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)
endif



ifeq ($(CORE),ipu1_0)
  CFGARGS_XDC = "\"{mode: \\\"$(IPC_MODE)\\\", coreName: \\\"IPU1-CORE0\\\", platformMem: \\\"$(PLATFORM_MEM)\\\"}\""
endif
ifeq ($(CORE),ipu1_1)
  CFGARGS_XDC = "\"{mode: \\\"$(IPC_MODE)\\\", coreName: \\\"IPU1-CORE1\\\",  platformMem: \\\"$(PLATFORM_MEM)\\\"}\""
endif
ifeq ($(CORE),ipu2)
  CFGARGS_XDC = "\"{mode: \\\"$(IPC_MODE)\\\", coreName: \\\"IPU2-CORES\\\", platformMem: \\\"$(PLATFORM_MEM)\\\"}\""
endif
ifeq ($(CORE),a15_0)
  CFGARGS_XDC = "\"{mode: \\\"$(IPC_MODE)\\\", coreName:\\\"A15-0\\\", platformMem: \\\"$(PLATFORM_MEM)\\\"}\""
endif
ifeq ($(CORE),c66xdsp_1)
  CFGARGS_XDC = "\"{mode: \\\"$(IPC_MODE)\\\", coreName:\\\"DSP-1\\\",  platformMem: \\\"$(PLATFORM_MEM)\\\"}\""
endif
ifeq ($(CORE),c66xdsp_2)
  CFGARGS_XDC = "\"{mode: \\\"$(IPC_MODE)\\\", coreName:\\\"DSP-2\\\",  platformMem: \\\"$(PLATFORM_MEM)\\\"}\""
endif
ifeq ($(CORE),arp32_1)
  CFGARGS_XDC = "\"{mode: \\\"$(IPC_MODE)\\\", coreName:\\\"EVE-1\\\",  platformMem: \\\"$(PLATFORM_MEM)\\\"}\""
endif
ifeq ($(CORE),arp32_2)
  CFGARGS_XDC = "\"{mode: \\\"$(IPC_MODE)\\\", coreName:\\\"EVE-2\\\",  platformMem: \\\"$(PLATFORM_MEM)\\\"}\""
endif
ifeq ($(CORE),arp32_3)
  CFGARGS_XDC = "\"{mode: \\\"$(IPC_MODE)\\\", coreName:\\\"EVE-3\\\",  platformMem: \\\"$(PLATFORM_MEM)\\\"}\""
endif
ifeq ($(CORE),arp32_4)
  CFGARGS_XDC = "\"{mode: \\\"$(IPC_MODE)\\\", coreName:\\\"EVE-4\\\",  platformMem: \\\"$(PLATFORM_MEM)\\\"}\""
endif

export SOC
export SOCFAMILY

# Nothing beyond this point
