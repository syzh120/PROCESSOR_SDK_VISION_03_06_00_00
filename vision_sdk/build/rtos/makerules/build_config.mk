# Filename: build_config.mk
#
# Build configuration make file - This file contains all the options that are
#                                 frequently changed
#
# This file changes when:
#     1. format needs to change (eg: COFF/ELF)
#     2. Endian-ness needs to change (little/big)
#     3. global compiler and linker options need to change (one entry for each
#                                                           core)
#     4. Profile needs to change (debug/release/prod_release)
#     5. Build option changes (xdc/make/full)
#

# Global options

# Build - Allowed values = full | xdc | make
#         This "builds" packages based on the setting:
#                 full - build both XDC and make (all the packages/components)
#                 xdc  - build and configure only XDC packages
#                 make - build only make based components and link everything
# NOTE: BUILD need not be defined at all, which case it behaves like it is set
#       to "full". This is to ensure backward compatibility.
BUILD = full

# Endianness : Allowed values = little | big
ENDIAN = little

# Format : Allowed values = COFF | ELF
FORMAT = ELF

# Platform memory: available external memory
PLATFORM_MEM = $(DDR_MEM)

#
# Platform specific
#
CFLAGS_GLOBAL_tda2xx-rvp = -DTDA2XX_BUILD -DTDA2XX_FAMILY_BUILD -DPLATFORM_EVM_SI
CFLAGS_GLOBAL_tda2xx-rvp += -DVPS_VIP_BUILD

ifeq ($(A15_TARGET_OS),$(filter $(A15_TARGET_OS), Linux Qnx))
ifeq ($(PLATFORM), tda2xx-rvp)
CFLAGS_GLOBAL_tda2xx-rvp += -DUSE_LINUX_INTC_NUMBERS
endif
endif

CFLAGS_GLOBAL_tda2xx-evm = -DTDA2XX_BUILD -DTDA2XX_FAMILY_BUILD -DPLATFORM_EVM_SI
CFLAGS_GLOBAL_tda2xx-evm += -DVPS_VIP_BUILD

CFLAGS_GLOBAL_tda2px-evm = -DTDA2PX_BUILD -DTDA2XX_FAMILY_BUILD -DPLATFORM_EVM_SI
CFLAGS_GLOBAL_tda2px-evm += -DVPS_VIP_BUILD

CFLAGS_GLOBAL_tda3xx-evm = -DTDA3XX_BUILD -DTDA3XX_FAMILY_BUILD -DPLATFORM_EVM_SI
CFLAGS_GLOBAL_tda3xx-evm += -DVPS_VIP_BUILD

CFLAGS_GLOBAL_tda3xx-rvp = -DTDA3XX_BUILD -DTDA3XX_FAMILY_BUILD -DPLATFORM_EVM_SI -DBOARD_TYPE_TDA3XX_RVP
CFLAGS_GLOBAL_tda3xx-rvp += -DVPS_VIP_BUILD

CFLAGS_GLOBAL_tda2ex-evm = -DTDA2EX_BUILD -DTDA2XX_FAMILY_BUILD -DPLATFORM_EVM_SI
CFLAGS_GLOBAL_tda2ex-evm += -DVPS_VIP_BUILD

ifeq ($(VPE_INCLUDE),yes)
CFLAGS_GLOBAL_tda2xx-rvp += -DVPS_VPE_BUILD
CFLAGS_GLOBAL_tda2xx-evm += -DVPS_VPE_BUILD
CFLAGS_GLOBAL_tda2px-evm += -DVPS_VPE_BUILD
CFLAGS_GLOBAL_tda2ex-evm += -DVPS_VPE_BUILD
endif

ifeq ($(CAL_INCLUDE),yes)
CFLAGS_GLOBAL_tda2ex-evm += -DVPS_CAL_BUILD
CFLAGS_GLOBAL_tda2px-evm += -DVPS_CAL_BUILD
CFLAGS_GLOBAL_tda3xx-evm += -DVPS_CAL_BUILD
CFLAGS_GLOBAL_tda3xx-rvp += -DVPS_CAL_BUILD
endif

ifeq ($(ISS_INCLUDE),yes)
CFLAGS_GLOBAL_tda3xx-evm += -DVPS_ISS_BUILD
CFLAGS_GLOBAL_tda3xx-rvp += -DVPS_ISS_BUILD
CFLAGS_GLOBAL_tda2px-evm += -DVPS_ISS_BUILD
endif

ifeq ($(DSS_INCLUDE),yes)
CFLAGS_GLOBAL_tda2xx-rvp += -DVPS_DSS_BUILD
CFLAGS_GLOBAL_tda2xx-evm += -DVPS_DSS_BUILD
CFLAGS_GLOBAL_tda2px-evm += -DVPS_DSS_BUILD
CFLAGS_GLOBAL_tda3xx-evm += -DVPS_DSS_BUILD
CFLAGS_GLOBAL_tda3xx-rvp += -DVPS_DSS_BUILD
CFLAGS_GLOBAL_tda2ex-evm += -DVPS_DSS_BUILD
endif

ifeq ($(DATA_VIS_INCLUDE),yes)
CFLAGS_GLOBAL_tda2xx-rvp += -DDATA_VIS_INCLUDE
CFLAGS_GLOBAL_tda2xx-evm += -DDATA_VIS_INCLUDE
CFLAGS_GLOBAL_tda2px-evm += -DDATA_VIS_INCLUDE
CFLAGS_GLOBAL_tda3xx-evm += -DDATA_VIS_INCLUDE
CFLAGS_GLOBAL_tda2ex-evm += -DDATA_VIS_INCLUDE
endif


#
# Core specific options - Cores of tda2xx (Vayu), ti814x (Centaurus), ti8149 (CentEve) and ti811x (J5ECO)
#

# m3video - Ducati - Core 0 (Cortex-M3)

# Profile: Allowed values = debug | release | prod_release
CFLAGS_GLOBAL_m3video =  -g -ms  -D___DSPBIOS___ -D___DUCATI_FW___
LNKFLAGS_GLOBAL_m3video = -x --zero_init=off

# m3vpss - Ducati - Core 1 (Cortex-M3)

# Profile: Allowed values = debug | release | prod_release
CFLAGS_GLOBAL_m3vpss =  -g -ms  -D___DSPBIOS___ -D___DUCATI_FW___
LNKFLAGS_GLOBAL_m3vpss = -x --zero_init=off

# m4video - Benelli - Core 0 (Cortex-M4)

# Profile: Allowed values = debug | release | prod_release
CFLAGS_GLOBAL_m4video =  -g -ms  -D___DSPBIOS___ -D___DUCATI_FW___
LNKFLAGS_GLOBAL_m4video = -x --zero_init=off

# m4vpss - Benneli - Core 1 (Cortex-M4)

# Profile: Allowed values = debug | release | prod_release
CFLAGS_GLOBAL_m4vpss =  -g -ms  -D___DSPBIOS___ -D___DUCATI_FW___
LNKFLAGS_GLOBAL_m4vpss = -x --zero_init=off

# ipu1_1 - Benelli - Core 1 (Cortex-M4)

# Profile: Allowed values = debug | release | prod_release
CFLAGS_GLOBAL_ipu1_1 =  -g -ms  -D___DSPBIOS___ -D___DUCATI_FW___
# AVB NSP RELATED MACRO
CFLAGS_GLOBAL_ipu1_1 += -D_NDK_EXTERN_CONFIG -D_INCLUDE_NIMU_CODE -DMSGLEVEL=3 -D_INCLUDE_IPv6_CODE
LNKFLAGS_GLOBAL_ipu1_1 = -x --zero_init=off

# ipu1_0 - Benneli - Core 0 (Cortex-M4)

# Profile: Allowed values = debug | release | prod_release
CFLAGS_GLOBAL_ipu1_0 =  -g -ms  -D___DSPBIOS___ -D___DUCATI_FW___
# AVB NSP RELATED MACRO
CFLAGS_GLOBAL_ipu1_0 += -D_NDK_EXTERN_CONFIG -D_INCLUDE_NIMU_CODE -DMSGLEVEL=3 -D_INCLUDE_IPv6_CODE
LNKFLAGS_GLOBAL_ipu1_0 = -x --zero_init=off --dynamic --retain=_Ipc_ResetVector --retain=.resource_table --cinit_compression=off
ifeq ($(FAST_BOOT_INCLUDE), yes)
LNKFLAGS_GLOBAL_ipu1_0 += --cinit_compression=lzss --ram_model
endif

# ipu2 - Benneli - Core 0 & 1 (Cortex-M4)

# Profile: Allowed values = debug | release | prod_release
CFLAGS_GLOBAL_ipu2 =  -g -ms  -D___DSPBIOS___ -D___DUCATI_FW___
LNKFLAGS_GLOBAL_ipu2 = -x --zero_init=on --dynamic --retain=_Ipc_ResetVector --retain=.resource_table --cinit_compression=off
ifeq ($(FAST_BOOT_INCLUDE), yes)
LNKFLAGS_GLOBAL_ipu2 += --cinit_compression=lzss --ram_model
endif

# a8host - Cortex-A8

# Profile: Allowed values = debug | release
PROFILE_a8host = debug
CFLAGS_GLOBAL_a8host = -c -x c -Wunused -Wall -g
LNKFLAGS_GLOBAL_a8host =

# a15host - Cortex-A15

# Profile: Allowed values = debug | release
#PROFILE_a15_0 = debug
CFLAGS_GLOBAL_a15_0 += -D_NDK_EXTERN_CONFIG -D_INCLUDE_NIMU_CODE -DMSGLEVEL=3 -D_INCLUDE_IPv6_CODE

LNKFLAGS_GLOBAL_a15_0 =

# dsp - IMPLEMENTED
# Profile: Allowed values = debug | release
PROFILE_c6xdsp = debug
CFLAGS_GLOBAL_c6xdsp =

# dsp - IMPLEMENTED for Vayu
# Profile: Allowed values = debug | release
PROFILE_c66x = debug
CFLAGS_GLOBAL_c66x =

# dsp - IMPLEMENTED for Vayu
# Profile: Allowed values = debug | release
PROFILE_c66xdsp = debug
CFLAGS_GLOBAL_c66xdsp =

# dsp - IMPLEMENTED for Vayu
# Profile: Allowed values = debug | release
# PROFILE_c66xdsp_1 = debug
CFLAGS_GLOBAL_c66xdsp_1 =

# Profile: Allowed values = debug | release
# PROFILE_c66xdsp_2 = debug
CFLAGS_GLOBAL_c66xdsp_2 =

# eve - IMPLEMENTED for Vayu
# Profile: Allowed values = debug | release
# PROFILE_arp32_1 = debug
CFLAGS_GLOBAL_arp32_1 =

# Profile: Allowed values = debug | release
# PROFILE_arp32_2 = debug
CFLAGS_GLOBAL_arp32_2 =

# Profile: Allowed values = debug | release
# PROFILE_arp32_3 = debug
CFLAGS_GLOBAL_arp32_3 =

# Profile: Allowed values = debug | release
# PROFILE_arp32_4 = debug
CFLAGS_GLOBAL_arp32_4 =

# Nothing beyond this point
