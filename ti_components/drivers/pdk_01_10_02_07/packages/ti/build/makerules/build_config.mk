#
# Copyright (c) 2013-2016, Texas Instruments Incorporated
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
#     4. Profile needs to change (debug/release)
#     5. Build option changes (xdc/make/full)
#

# Global options

# Endianness : Allowed values = little | big
ENDIAN = little

# Format : Allowed values = COFF | ELF
FORMAT = ELF

#
# BOARD specific
#
CFLAGS_GLOBAL_tda2xx-evm    = -DSOC_TDA2XX
CFLAGS_GLOBAL_tda2xx-rvp    = -DSOC_TDA2XX -DBOARD_TYPE_TDA2XX_RVP
CFLAGS_GLOBAL_tda2px-evm    = -DSOC_TDA2PX
CFLAGS_GLOBAL_evmDRA75x     = -DSOC_DRA75x
CFLAGS_GLOBAL_evmAM572x     = -DSOC_AM572x -DevmAM572x
CFLAGS_GLOBAL_idkAM572x     = -DSOC_AM572x -DidkAM572x
CFLAGS_GLOBAL_idkAM574x     = -DSOC_AM574x -DidkAM574x
CFLAGS_GLOBAL_am572x-evm    = -DSOC_AM572x
CFLAGS_GLOBAL_am572x-idk    = -DSOC_AM572x
CFLAGS_GLOBAL_am574x-idk    = -DSOC_AM574x
CFLAGS_GLOBAL_tda2ex-evm    = -DSOC_TDA2EX
CFLAGS_GLOBAL_tda2ex-eth-srv = -DSOC_TDA2EX -DBOARD_TYPE_TDA2EX_ETH_SRV
CFLAGS_GLOBAL_evmDRA72x     = -DSOC_DRA72x
CFLAGS_GLOBAL_idkAM571x     = -DSOC_AM571x -DidkAM571x
CFLAGS_GLOBAL_am571x-evm    = -DSOC_AM571x
CFLAGS_GLOBAL_tda3xx-evm    = -DSOC_TDA3XX
CFLAGS_GLOBAL_tda3xx-rvp    = -DSOC_TDA3XX
CFLAGS_GLOBAL_evmDRA78x     = -DSOC_DRA78x
CFLAGS_GLOBAL_evmK2L        = -DSOC_K2L -DevmK2L
CFLAGS_GLOBAL_evmK2E        = -DSOC_K2E -DevmK2E
CFLAGS_GLOBAL_evmK2H        = -DSOC_K2H -DevmK2H
CFLAGS_GLOBAL_evmK2K        = -DSOC_K2K -DevmK2K
CFLAGS_GLOBAL_evmK2G        = -DSOC_K2G -DevmK2G
CFLAGS_GLOBAL_iceK2G        = -DSOC_K2G -DiceK2G
CFLAGS_GLOBAL_evmC6657      = -DSOC_C6657 -DevmC6657
CFLAGS_GLOBAL_evmC6678      = -DSOC_C6678 -DevmC6678
CFLAGS_GLOBAL_evmAM335x     = -DSOC_AM335x -DevmAM335x
CFLAGS_GLOBAL_icev2AM335x   = -DSOC_AM335x -Dicev2AM335x
CFLAGS_GLOBAL_iceAMIC110    = -DSOC_AM335x -DiceAMIC110
CFLAGS_GLOBAL_skAM335x      = -DSOC_AM335x -DskAM335x
CFLAGS_GLOBAL_bbbAM335x     = -DSOC_AM335x -DbbbAM335x
CFLAGS_GLOBAL_evmAM437x     = -DSOC_AM437x -DevmAM437x
CFLAGS_GLOBAL_idkAM437x     = -DSOC_AM437x -DidkAM437x
CFLAGS_GLOBAL_skAM437x      = -DSOC_AM437x -DskAM437x
CFLAGS_GLOBAL_evmOMAPL137	= -DSOC_OMAPL137
CFLAGS_GLOBAL_lcdkOMAPL138	= -DSOC_OMAPL138
CFLAGS_GLOBAL_tda3xx-evm-radar      = -DSOC_TDA3XX
CFLAGS_GLOBAL_tda2xx-evm-radar      = -DSOC_TDA2XX
CFLAGS_GLOBAL_tda2xx-cascade-radar  = -DSOC_TDA2XX -DBOARD_TYPE_TDA2XX_CASCADE_RADAR
CFLAGS_GLOBAL_tda2px-evm-radar      = -DSOC_TDA2PX
CFLAGS_GLOBAL_tda3xx-ar12-booster   = -DSOC_TDA3XX
CFLAGS_GLOBAL_tda3xx-ar12-alps      = -DSOC_TDA3XX
CFLAGS_GLOBAL_tda3xx-ar12-rvp       = -DSOC_TDA3XX

#
# SOC specific
#
CFLAGS_GLOBAL_tda2xx         = -DSOC_TDA2XX
CFLAGS_GLOBAL_tda2px         = -DSOC_TDA2PX
CFLAGS_GLOBAL_dra75x         = -DSOC_DRA75x
CFLAGS_GLOBAL_am572x         = -DSOC_AM572x
CFLAGS_GLOBAL_am574x         = -DSOC_AM574x
CFLAGS_GLOBAL_tda2ex         = -DSOC_TDA2EX
CFLAGS_GLOBAL_dra72x         = -DSOC_DRA72x
CFLAGS_GLOBAL_am571x         = -DSOC_AM571x
CFLAGS_GLOBAL_tda3xx         = -DSOC_TDA3XX
CFLAGS_GLOBAL_dra78x         = -DSOC_DRA78x
CFLAGS_GLOBAL_k2l            = -DSOC_K2L
CFLAGS_GLOBAL_k2e            = -DSOC_K2E
CFLAGS_GLOBAL_k2h            = -DSOC_K2H
CFLAGS_GLOBAL_k2k            = -DSOC_K2K
CFLAGS_GLOBAL_k2g            = -DSOC_K2G
CFLAGS_GLOBAL_c6657          = -DSOC_C6657
CFLAGS_GLOBAL_c6678          = -DSOC_C6678
CFLAGS_GLOBAL_am335x         = -DSOC_AM335x
CFLAGS_GLOBAL_am437x         = -DSOC_AM437x
CFLAGS_GLOBAL_omapl137		 = -DSOC_OMAPL137
CFLAGS_GLOBAL_omapl138		 = -DSOC_OMAPL138

#
# Core specific options - Cores of tda2xx, tda2px, am572x, tda2ex, am571x, tda3xx, dra75x, dra78x, am574x
#

# ipu1_0 - Benelli - Core 1 (Cortex-M4)
CFLAGS_GLOBAL_ipu1_0 = -g -ms -DMAKEFILE_BUILD
LNKFLAGS_GLOBAL_ipu1_0 = -x --zero_init=on

# ipu1_1 - Benneli - Core 0 (Cortex-M4)
CFLAGS_GLOBAL_ipu1_1 = -g -ms -DMAKEFILE_BUILD
LNKFLAGS_GLOBAL_ipu1_1 = -x --zero_init=on

# ipu2_0 - Benelli - Core 1 (Cortex-M4)
CFLAGS_GLOBAL_ipu2_0 = -g -ms -DMAKEFILE_BUILD
LNKFLAGS_GLOBAL_ipu2_0 = -x --zero_init=on

# ipu2_1 - Benneli - Core 0 (Cortex-M4)
CFLAGS_GLOBAL_ipu2_1 = -g -ms -DMAKEFILE_BUILD
LNKFLAGS_GLOBAL_ipu2_1 = -x --zero_init=on

# arp32_1 - EVE
CFLAGS_GLOBAL_arp32_1 = -DMAKEFILE_BUILD
LNKFLAGS_GLOBAL_arp32_1 =

# arp32_2 - EVE
CFLAGS_GLOBAL_arp32_2 = -DMAKEFILE_BUILD
LNKFLAGS_GLOBAL_arp32_2 =

# arp32_3 - EVE
CFLAGS_GLOBAL_arp32_3 = -DMAKEFILE_BUILD
LNKFLAGS_GLOBAL_arp32_3 =

# arp32_4 - EVE
CFLAGS_GLOBAL_arp32_4 = -DMAKEFILE_BUILD
LNKFLAGS_GLOBAL_arp32_4 =

# a8host - Cortex-A8
CFLAGS_GLOBAL_a8host = -DMAKEFILE_BUILD
LNKFLAGS_GLOBAL_a8host =

# a9host - Cortex-A9
CFLAGS_GLOBAL_a9host = -DMAKEFILE_BUILD
LNKFLAGS_GLOBAL_a9host =

# arm9_0 - ARM926
CFLAGS_GLOBAL_arm9_0 = -DMAKEFILE_BUILD
LNKFLAGS_GLOBAL_arm9_0 =

# PRUSS - PRU 0
CFLAGS_GLOBAL_pru_0 = -DMAKEFILE_BUILD
LNKFLAGS_GLOBAL_pru_0 = --define=PRU0 --define=pru0

# PRUSS - PRU 1
CFLAGS_GLOBAL_pru_1 = -DMAKEFILE_BUILD
LNKFLAGS_GLOBAL_pru_1 = --define=PRU1 --define=pru1

# a15_0 - Cortex-A15
CFLAGS_GLOBAL_a15_0 = -DMAKEFILE_BUILD
LNKFLAGS_GLOBAL_a15_0 =

# dsp - IMPLEMENTED for tda2xx, tda2px, am572x, tda2ex, am571x am574x
CFLAGS_GLOBAL_c66x = -DMAKEFILE_BUILD
LNKFLAGS_GLOBAL_c66x = -x
CFLAGS_GLOBAL_c66xdsp_1 = -DMAKEFILE_BUILD
LNKFLAGS_GLOBAL_c66xdsp_1 = -x
CFLAGS_GLOBAL_c66xdsp_2 = -DMAKEFILE_BUILD
LNKFLAGS_GLOBAL_c66xdsp_2 = -x

# dsp - IMPLEMENTED for omapl137, omapl138
CFLAGS_GLOBAL_c674x = -DMAKEFILE_BUILD
LNKFLAGS_GLOBAL_c674x = -x

# Nothing beyond this point
