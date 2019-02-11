# Filename: platforms.mk
#
# Platforms make file - Platform/SoC/targets are defined/derived in this file
#
# This file needs to change when:
#     1. a new platform/SoC is added, which also might have its own cores/ISAs
#

#
# Derive SOC from PLATFORM
#

# tda2xx (Vayu) EVM
ifeq ($(PLATFORM),tda2xx-evm)
 SOC = tda2xx
 PLATFORM_XDC = "ti.platforms.evmDRA7XX"
endif
#  am572x
ifeq ($(PLATFORM),am572x-evm)
 SOC = am572x
 PLATFORM_XDC = "ti.platforms.evmAM572X"
endif

ifeq ($(PLATFORM),am571x-evm)
 SOC = am571x
 PLATFORM_XDC = "ti.platforms.evmDRA7XX"
endif

# tda3xx (ADAS low)
ifeq ($(PLATFORM),tda3xx-evm)
 SOC = tda3xx
 PLATFORM_XDC = "ti.platforms.evmTDA3XX"
endif

#  dra72x (j6Eco)
ifeq ($(PLATFORM),dra72x-evm)
 SOC = dra72x
 PLATFORM_XDC = "ti.platforms.evmDRA7XX"
endif

#  tda2ex (j6Eco)
ifeq ($(PLATFORM),tda2ex-evm)
 SOC = dra72x
 PLATFORM_XDC = "ti.platforms.evmDRA7XX"
endif

#  am335x
ifeq ($(PLATFORM),am335x-evm)
 SOC = am335x
 PLATFORM_XDC = "ti.platforms.evmAM3359"
endif

#  am437x
ifeq ($(PLATFORM),am437x-evm)
 SOC = am437x
 PLATFORM_XDC = "ti.platforms.evmAM437X"
endif

# ti816x (Netra) catalog EVM
ifeq ($(PLATFORM),ti816x-evm)
 SOC = ti816x
 PLATFORM_XDC = "ti.platforms.evmTI816X"
endif

# ti816x (Netra) Simulator
ifeq ($(PLATFORM),ti816x-sim)
 SOC = ti816x
 ifeq ($(CORE),c6xdsp)
  PLATFORM_XDC = "ti.platforms.simDM8168"
 endif
endif

# ti814x (Centaurus) Catalog EVM
ifeq ($(PLATFORM),ti814x-evm)
 SOC = ti814x
 PLATFORM_XDC = "ti.platforms.evmTI814X"
endif

# c6a811x (J5Eco) Catalog EVM
ifeq ($(PLATFORM),c6a811x-evm)
 SOC = c6a811x
 PLATFORM_XDC = "ti.platforms.evmTI811X"
endif

# c6472 (Tomahawk) EVM
ifeq ($(PLATFORM),c6472-evm)
 SOC = c6472
 PLATFORM_XDC = "ti.platforms.evm6472"
endif

# tci6486 (Tomahawk) EVM
ifeq ($(PLATFORM),tci6486-evm)
 SOC = c6472
 PLATFORM_XDC = "ti.platforms.evmTCI6486"
endif

# tci6608 (Shannon) Simulator
ifeq ($(PLATFORM),tci6608-sim)
 SOC = c6608
 PLATFORM_XDC = "ti.platforms.simTCI6608"
endif

# tci6616 (Nyquist) Simulator
ifeq ($(PLATFORM),tci6616-sim)
 SOC = c6616
 PLATFORM_XDC = "ti.platforms.simTCI6616"
endif

# tci6614 (Appleton) Simulator
ifeq ($(PLATFORM),tci6614-sim)
 SOC = tci6614
 PLATFORM_XDC = "ti.platforms.simTCI6614"
endif

# c6657 (Gauss) Simulator
ifeq ($(PLATFORM),c6657-sim)
 SOC = c6657
 PLATFORM_XDC = "ti.platforms.simC6657"
endif

# tci6638k2k (Kepler2) Simulator
ifeq ($(PLATFORM),tci6638k2k-sim)
 SOC = tci6638k2k
 PLATFORM_XDC = "ti.platforms.simKepler"
endif

# c6670 (Nyquist) EVM
ifeq ($(PLATFORM),c6670-evm)
 SOC = c6670
 PLATFORM_XDC = "ti.platforms.evm6670"
endif

# c6678 (Shannon) EVM
ifeq ($(PLATFORM),c6678-evm)
 SOC = c6678
 PLATFORM_XDC = "ti.platforms.evm6678"
endif

# tci6614 (Appleton) EVM
ifeq ($(PLATFORM),tci6614-evm)
 SOC = tci6614
 PLATFORM_XDC = "ti.platforms.evmTCI6614"
endif

# c6657 (Gauss) EVM
ifeq ($(PLATFORM),c6657-evm)
 SOC = c6657
 PLATFORM_XDC = "ti.platforms.evm6657"
endif

# tci6638k2k (Kepler2) EVM
ifeq ($(PLATFORM),tci6638k2k-evm)
 SOC = tci6638k2k
 CFLAGS_LOCAL_a15host += -DGENERIC
 PLATFORM_XDC = "ti.platforms.evmTCI6638K2K"
endif

# tci6630k2l EVM
ifeq ($(PLATFORM),tci6630k2l-evm)
 SOC = tci6630k2l
 CFLAGS_LOCAL_a15host += -DGENERIC
 PLATFORM_XDC = "ti.platforms.evmTCI6630K2L"
endif

# c66ak2e EVM
ifeq ($(PLATFORM),c66ak2e-evm)
 SOC = c66ak2e
 CFLAGS_LOCAL_a15host += -DGENERIC
 PLATFORM_XDC = "ti.platforms.evmC66AK2E"
endif

# tci6636k2h (Hawking) EVM
ifeq ($(PLATFORM),tci6636k2h-evm)
 SOC = tci6636k2h
 CFLAGS_LOCAL_a15host += -DGENERIC
 PLATFORM_XDC = "ti.platforms.evmTCI6636K2H"
endif

# tci66ak2g02 EVM
ifeq ($(PLATFORM),tci66ak2g02-evm)
 SOC = tci66ak2g02
 CFLAGS_LOCAL_a15host += -DGENERIC
 PLATFORM_XDC = "ti.platforms.evmTCI66AK2G02"
endif

# omapl137 (Primus) EVM
ifeq ($(PLATFORM),omapl137-evm)
 SOC = omapl137
 PLATFORM_XDC = "ti.platforms.evmOMAPL137"
endif

# omapl138 (Freon) EVM
ifeq ($(PLATFORM),omapl138-evm)
 SOC = omapl138
 PLATFORM_XDC = "ti.platforms.evmOMAPL138"
endif

# c6748 (Freon) EVM
ifeq ($(PLATFORM),c6748-evm)
 SOC = omapl138
 PLATFORM_XDC = "ti.platforms.evm6748"
endif

# da830 (Primus) EVM
ifeq ($(PLATFORM),da830-evm)
 SOC = omapl137
 PLATFORM_XDC = "ti.platforms.evmDA830"
endif

# omap4 EVM
ifeq ($(PLATFORM),omap4-evm)
 SOC = omap4
 PLATFORM_XDC = "ti.platforms.sdp4430"
endif

# Generic platform
ifeq ($(PLATFORM),generic)
 SOC = generic
 PLATFORM_XDC =
endif

# Derive Target/ISA from CORE

# m4
ifeq ($(CORE),m4)
 ISA = m4
endif

# a15host user space
ifeq ($(CORE),a15host)
 ISA = a15
endif

# m3vpss
ifeq ($(CORE),m3vpss)
 ISA = m3
endif

# m3video
ifeq ($(CORE),m3video)
 ISA = m3
endif

# a8host
ifeq ($(CORE),a8host)
 ISA = a8
endif

# arm9
ifeq ($(CORE),arm9)
 ISA = arm9
endif

# c6xdsp
ifeq ($(CORE),c6xdsp)
 ifeq ($(SOC),ti816x)
  ISA = 674
 endif
 ifeq ($(SOC),tda2xx)
  ISA = 66
 endif
 ifeq ($(SOC),tda3xx)
  ISA = 66
 endif
 ifeq ($(SOC),dra72x)
  ISA = 66
 endif
 ifeq ($(SOC),am572x)
  ISA = 66
 endif
 ifeq ($(SOC),am571x)
  ISA = 66
 endif
 ifeq ($(SOC),ti814x)
  ISA = 674
 endif
 ifeq ($(SOC),c6a811x)
  ISA = 674
 endif
 ifeq ($(SOC),omapl137)
  ISA = 674
 endif
 ifeq ($(SOC),omapl138)
  ISA = 674
 endif
 ifeq ($(SOC),c6472)
  ISA = 64p
 endif
 ifeq ($(SOC),c6608)
  ISA = 66
 endif
 ifeq ($(SOC),c66ak2e)
  ISA = 66
 endif
 ifeq ($(SOC),c6616)
  ISA = 66
 endif
 ifeq ($(SOC),tci6614)
  ISA = 66
 endif
 ifeq ($(SOC),c6657)
  ISA = 66
 endif
 ifeq ($(SOC),c6670)
  ISA = 66
 endif
 ifeq ($(SOC),c6678)
  ISA = 66
 endif
 ifeq ($(SOC),tci6638k2k)
  ISA = 66
 endif
 ifeq ($(SOC),tci6630k2l)
  ISA = 66
 endif
 ifeq ($(SOC),tci6636k2h)
  ISA = 66
 endif
 ifeq ($(SOC),tci66ak2g02)
  ISA = 66
 endif
 ifeq ($(SOC),omap4)
  ISA = 64t
 endif
endif

# EVE - arp32
ifeq ($(CORE),eve)
 ISA = arp32
endif

# Platform and SOC is generic; use the core name same as ISA (eg: 674)
ifeq ($(SOC),generic)
  ISA = $(CORE)
endif

#
# Derive XDC/ISA specific settings
#
ifeq ($(ISA),m4)
  COMPILER = TMS470
  ifeq ($(FORMAT),ELF)
    TARGET_XDC = ti.targets.arm.elf.M4
    FORMAT_EXT = e
  else
    TARGET_XDC = ti.targets.arm.M4
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

ifeq ($(ISA),a15)
  TARGET_XDC = gnu.targets.arm.A15F
  CFLAGS_LOCAL_a15host += -DGCC_BUILD
  COMPILER = LINARO_GCC
  FORMAT_EXT =
  ENDIAN_EXT = fg

  # Define the file extensions
  OBJEXT = o$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)
  OBJEXT_SO = $(OBJEXT)_so
  LIBEXT = a$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)
  LIBEXT_SO = $(LIBEXT)_so
  EXEEXT = x$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)
  ASMEXT = s$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)
endif

ifeq ($(ISA),m3)
  COMPILER = TMS470
  ifeq ($(FORMAT),ELF)
    TARGET_XDC = ti.targets.arm.elf.M3
    FORMAT_EXT = e
  else
    TARGET_XDC = ti.targets.arm.M3
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

ifeq ($(ISA),674)
  COMPILER = C6000
  ifeq ($(FORMAT),ELF)
    TARGET_XDC = ti.targets.elf.C674
    FORMAT_EXT = e
  else
    TARGET_XDC = ti.targets.C674
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

ifeq ($(ISA),64p)
  COMPILER = C6000
  ifeq ($(FORMAT),ELF)
   ifeq ($(ENDIAN),big)
    TARGET_XDC = ti.targets.elf.C64P_big_endian
   else
    TARGET_XDC = ti.targets.elf.C64P
   endif
    FORMAT_EXT = e
  else
   ifeq ($(ENDIAN),big)
    TARGET_XDC = ti.targets.C64P_big_endian
   else
    TARGET_XDC = ti.targets.C64P
   endif
  endif

  # If ENDIAN is set to "big", set ENDIAN_EXT to "e", that would be used in
  #    in the filename extension of object/library/executable files
  ifeq ($(ENDIAN),big)
    ENDIAN_EXT = e
  endif

  # Define the file extensions
  OBJEXT = o$(FORMAT_EXT)64P$(ENDIAN_EXT)
  LIBEXT = a$(FORMAT_EXT)64P$(ENDIAN_EXT)
  EXEEXT = x$(FORMAT_EXT)64P$(ENDIAN_EXT)
  ASMEXT = s$(FORMAT_EXT)64P$(ENDIAN_EXT)
endif

ifeq ($(ISA),64t)
  COMPILER = C6000
  ifeq ($(FORMAT),ELF)
   ifeq ($(ENDIAN),big)
    TARGET_XDC = ti.targets.elf.C64T_big_endian
   else
    TARGET_XDC = ti.targets.elf.C64T
   endif
    FORMAT_EXT = e
  else
   ifeq ($(ENDIAN),big)
    TARGET_XDC = ti.targets.C64T_big_endian
   else
    TARGET_XDC = ti.targets.C64T
   endif
  endif

  # If ENDIAN is set to "big", set ENDIAN_EXT to "e", that would be used in
  #    in the filename extension of object/library/executable files
  ifeq ($(ENDIAN),big)
    ENDIAN_EXT = e
  endif

  # Define the file extensions
  OBJEXT = o$(FORMAT_EXT)64T$(ENDIAN_EXT)
  LIBEXT = a$(FORMAT_EXT)64T$(ENDIAN_EXT)
  EXEEXT = x$(FORMAT_EXT)64T$(ENDIAN_EXT)
  ASMEXT = s$(FORMAT_EXT)64T$(ENDIAN_EXT)
endif

ifeq ($(ISA),66)
  COMPILER = C6000
  ifeq ($(FORMAT),ELF)
   ifeq ($(ENDIAN),big)
    TARGET_XDC = ti.targets.elf.C66_big_endian
   else
    TARGET_XDC = ti.targets.elf.C66
   endif
    FORMAT_EXT = e
  else
   ifeq ($(ENDIAN),big)
    TARGET_XDC = ti.targets.C66_big_endian
   else
    TARGET_XDC = ti.targets.C66
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

ifeq ($(ISA),a8)
  ifeq ($(TOOLCHAIN_a8),TI)
    TARGET_XDC = ti.targets.arm.elf.A8Fnv
    ifeq ($(FORMAT),ELF)
      FORMAT_EXT = e
    endif
    ifeq ($(ENDIAN),big)
      ENDIAN_EXT = efnv
    else
      ENDIAN_EXT = fnv
    endif
  COMPILER = TMS470
  else
    TARGET_XDC = gnu.targets.arm.A8F
    CFLAGS_LOCAL_a8host += -DGCC_BUILD
    FORMAT_EXT =
    ENDIAN_EXT = fg
    COMPILER = LINARO_GCC
  endif

  # Define the file extensions
  OBJEXT = o$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)
  LIBEXT = a$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)
  EXEEXT = x$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)
  ASMEXT = s$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)
endif

ifeq ($(ISA),arm9)
  ifeq ($(TOOLCHAIN_arm9),GCC)
    TARGET_XDC = gnu.targets.arm.A9F
    CFLAGS_LOCAL_arm9 += -DGCC_BUILD
    FORMAT_EXT = a
    ENDIAN_EXT = fg
    COMPILER = LINARO_GCC
  else
    COMPILER = TMS470
    TARGET_XDC = ti.targets.arm.elf.Arm9
    ifeq ($(FORMAT),ELF)
      FORMAT_EXT = e
    endif
    ifeq ($(ENDIAN),big)
      ENDIAN_EXT = e
    endif
  endif

  # Define the file extensions
  OBJEXT = o$(FORMAT_EXT)9$(ENDIAN_EXT)
  LIBEXT = a$(FORMAT_EXT)9$(ENDIAN_EXT)
  EXEEXT = x$(FORMAT_EXT)9$(ENDIAN_EXT)
  ASMEXT = s$(FORMAT_EXT)9$(ENDIAN_EXT)
endif

ifeq ($(ISA),arp32)
  ifeq ($(FORMAT),ELF)
    TARGET_XDC = ti.targets.arp32.elf.ARP32_far
    ENDIAN_EXT = F
    FORMAT_EXT = e
  else
    TARGET_XDC = ti.targets.arp32.elf.ARP32
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

ifeq (sim,$(findstring sim,$(PLATFORM)))
  OMX_PLATFORM = sim
endif
export COMPILER
ifeq (ti816x-evm,$(findstring ti816x-evm,$(PLATFORM)))
 # Don't know why platform define for XDC is separate for A8. TO DO.
 ifeq ($(CORE),a8host)
  OMX_PLATFORM = evmSi
 else
  OMX_PLATFORM = evmSi816X
 endif
endif

ifeq ($(CORE),m3vpss)
  CFGARGS_XDC = \"{mode: \\\"$(IPC_MODE)\\\", coreName: \\\"VPSS-M3\\\", tiler: \\\"DucatiTilerMemMgr\\\", platformMem: \\\"$(PLATFORM_MEM)\\\", maxResolution: \\\"$(MAX_RESOLUTION)\\\", omxBuildPlatform: \\\"$(OMX_PLATFORM)\\\"}\"
endif
ifeq ($(CORE),m3video)
  CFGARGS_XDC = \"{mode: \\\"$(IPC_MODE)\\\", coreName:\\\"VIDEO-M3\\\", tiler: \\\"DucatiTilerMemMgr\\\", platformMem: \\\"$(PLATFORM_MEM)\\\", maxResolution: \\\"$(MAX_RESOLUTION)\\\", omxBuildPlatform: \\\"$(OMX_PLATFORM)\\\"}\"
endif
ifeq ($(CORE),c6xdsp)
  CFGARGS_XDC =
endif
ifeq ($(CORE),a8host)
  CFGARGS_XDC = \"{mode: \\\"$(IPC_MODE)\\\", coreName:\\\"HOST\\\", tiler: \\\"NullTilerMemMgr\\\", platformMem: \\\"$(PLATFORM_MEM)\\\", maxResolution: \\\"$(MAX_RESOLUTION)\\\", omxBuildPlatform: \\\"$(OMX_PLATFORM)\\\"}\"
endif

# Nothing beyond this point
