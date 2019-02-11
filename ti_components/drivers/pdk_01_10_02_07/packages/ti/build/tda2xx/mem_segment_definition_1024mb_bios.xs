/*
 *******************************************************************************
 *
 * Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *
 *******************************************************************************
 */

/*
 *  ======== mem_segment_definition.xs ========
 *  ======== Single file for the memory map configuration of all cores =========
 */

var KB=1024;
var MB=KB*KB;

var DDR3_ADDR;
var DDR3_SIZE;

var DDR3_BASE_ADDR_0;
var DDR3_BASE_SIZE_0;
var DDR3_BASE_ADDR_1;
var DDR3_BASE_SIZE_1;

var OCMC1_ADDR;
var OCMC2_ADDR;
var OCMC3_ADDR;

var OCMC1_SIZE;
var OCMC2_SIZE;
var OCMC3_SIZE;

var DSP1_L2_SRAM_ADDR;
var DSP1_L2_SRAM_SIZE;

var DSP2_L2_SRAM_ADDR;
var DSP2_L2_SRAM_SIZE;

var EVE1_SRAM_ADDR;
var EVE1_SRAM_SIZE;

var EVE2_SRAM_ADDR;
var EVE2_SRAM_SIZE;

var EVE3_SRAM_ADDR;
var EVE3_SRAM_SIZE;

var EVE4_SRAM_ADDR;
var EVE4_SRAM_SIZE;

var SR0_ADDR;
var SR0_SIZE;

var IPU1_1_CODE_ADDR;
var IPU1_1_CODE_SIZE;

var IPU1_1_DATA_ADDR;
var IPU1_1_DATA_SIZE;

var IPU1_1_BSS_ADDR;
var IPU1_1_BSS_SIZE;

var SR1_FRAME_BUFFER_ADDR;
var SR1_FRAME_BUFFER_SIZE;

var IPU1_0_CODE_ADDR;
var IPU1_0_CODE_SIZE;

var IPU1_0_DATA_ADDR;
var IPU1_0_DATA_SIZE;

var IPU1_0_BSS_ADDR;
var IPU1_0_BSS_SIZE;

var DSP1_CODE_ADDR;
var DSP1_CODE_SIZE;

var DSP1_DATA_ADDR;
var DSP1_DATA_SIZE;

var DSP2_CODE_ADDR;
var DSP2_CODE_SIZE;

var DSP2_DATA_ADDR;
var DSP2_DATA_SIZE;

var EVE1_CODE_ADDR;
var EVE1_CODE_SIZE;

var EVE1_DATA_ADDR;
var EVE1_DATA_SIZE;

var EVE1_VECS_ADDR;
var EVE1_VECS_SIZE;

var EVE2_CODE_ADDR;
var EVE2_CODE_SIZE;

var EVE2_DATA_ADDR;
var EVE2_DATA_SIZE;

var EVE2_VECS_ADDR;
var EVE2_VECS_SIZE;

var EVE3_CODE_ADDR;
var EVE3_CODE_SIZE;

var EVE3_DATA_ADDR;
var EVE3_DATA_SIZE;

var EVE3_VECS_ADDR;
var EVE3_VECS_SIZE;

var EVE4_CODE_ADDR;
var EVE4_CODE_SIZE;

var EVE4_DATA_ADDR;
var EVE4_DATA_SIZE;

var EVE4_VECS_ADDR;
var EVE4_VECS_SIZE;

var A15_0_CODE_ADDR;
var A15_0_CODE_SIZE;

var A15_0_DATA_ADDR;
var A15_0_DATA_SIZE;

var HDVPSS_DESC_ADDR;
var HDVPSS_DESC_SIZE;

var REMOTE_LOG_ADDR;
var REMOTE_LOG_SIZE;

DDR3_ADDR                   = 0x80000000;
DDR3_SIZE                   = 1024*MB;

DDR3_BASE_ADDR_0            = 0x80000000;
DDR3_BASE_SIZE_0            = 512*MB;

/* The start address of the second mem section should be 16MB aligned.
 * This alignment is a must as a single 16MB mapping is used for EVE
 * to map SR0, REMOTE_LOG_MEM sections.
 * tlb_config_eveX.c need to be modified otherwise
 */
DDR3_BASE_ADDR_1            = 0xA0000000;
DDR3_BASE_SIZE_1            = 512*MB;

OCMC1_ADDR                  = 0x40300000;
OCMC1_SIZE                  = 512*KB;

OCMC2_ADDR                  = 0x40400000;
OCMC2_SIZE                  = 1*MB;

OCMC3_ADDR                  = 0x40500000;
OCMC3_SIZE                  = 1*MB;

DSP1_L2_SRAM_ADDR           = 0x40800000;
DSP1_L2_SRAM_SIZE           = 288*KB;

DSP2_L2_SRAM_ADDR           = 0x41000000;
DSP2_L2_SRAM_SIZE           = 288*KB;

EVE1_SRAM_ADDR              = 0x42000000;
EVE1_SRAM_SIZE              = 1*MB;

EVE2_SRAM_ADDR              = 0x42100000;
EVE2_SRAM_SIZE              = 1*MB;

EVE3_SRAM_ADDR              = 0x42200000;
EVE3_SRAM_SIZE              = 1*MB;

EVE4_SRAM_ADDR              = 0x42300000;
EVE4_SRAM_SIZE              = 1*MB;

var TOTAL_MEM_SIZE          = (DDR3_SIZE);

/* First 512 MB - cached */
/* EVE vecs space should be align with 16MB boundary, and if possible try to fit
 * the entire vecs+code+data in 16MB section. In this case a single TLB map would
 * be enough to map vecs+code+data of an EVE.
 * tlb_config_eveX.c need to be modified if any of these EVE memory sections or
 * SR1_FRAME_BUFFER_MEM section is modified.
 */
EVE1_VECS_SIZE              = 0.5*MB;
EVE1_CODE_SIZE              =   2*MB;
EVE1_DATA_SIZE              =13.5*MB;
EVE2_VECS_SIZE              = 0.5*MB;
EVE2_CODE_SIZE              =   2*MB;
EVE2_DATA_SIZE              =13.5*MB;
EVE3_VECS_SIZE              = 0.5*MB;
EVE3_CODE_SIZE              =   2*MB;
EVE3_DATA_SIZE              =13.5*MB;
EVE4_VECS_SIZE              = 0.5*MB;
EVE4_CODE_SIZE              =   2*MB;
EVE4_DATA_SIZE              =13.5*MB;
IPU1_1_CODE_SIZE            =   2*MB;
IPU1_1_BSS_SIZE             =   8*MB;
IPU1_1_DATA_SIZE            =   4*MB;
IPU1_0_CODE_SIZE            =   6*MB;
IPU1_0_BSS_SIZE             =   8*MB;
IPU1_0_DATA_SIZE            =   4*MB;
SR1_FRAME_BUFFER_SIZE       = 256*MB;
DSP1_CODE_SIZE              =   2*MB;
DSP1_DATA_SIZE              =  64*MB;
DSP2_CODE_SIZE              =   2*MB;
DSP2_DATA_SIZE              =  64*MB;
A15_0_CODE_SIZE             =   2*MB;
A15_0_DATA_SIZE             =  14*MB;



/* Second 512 MB - non-cached */
/* The start address of the second mem section should be 16MB aligned.
 * This alignment is a must as a single 16MB mapping is used for EVE
 * to map SR0, EMOTE_LOG_MEM sections.
 * tlb_config_eveX.c need to be modified otherwise
 */
SR0_SIZE                    =  13*MB;
REMOTE_LOG_SIZE             =1024*KB;
HDVPSS_DESC_SIZE            =   2*MB;


/* Cached Section */
/* EVE vecs space should be align with 16MB boundary, and if possible try to fit
 * the entire vecs+code+data in 16MB section. In this case a single TLB map would
 * be enough to map vecs+code+data of an EVE.
 * tlb_config_eveX.c need to be modified if any of these EVE memory sections or
 * SR1_FRAME_BUFFER_MEM section is modified.
 */
EVE1_VECS_ADDR              = DDR3_BASE_ADDR_0;
EVE1_CODE_ADDR              = EVE1_VECS_ADDR        + EVE1_VECS_SIZE;
EVE1_DATA_ADDR              = EVE1_CODE_ADDR        + EVE1_CODE_SIZE;
EVE2_VECS_ADDR              = EVE1_DATA_ADDR        + EVE1_DATA_SIZE;
EVE2_CODE_ADDR              = EVE2_VECS_ADDR        + EVE2_VECS_SIZE;
EVE2_DATA_ADDR              = EVE2_CODE_ADDR        + EVE2_CODE_SIZE;
EVE3_VECS_ADDR              = EVE2_DATA_ADDR        + EVE2_DATA_SIZE;
EVE3_CODE_ADDR              = EVE3_VECS_ADDR        + EVE3_VECS_SIZE;
EVE3_DATA_ADDR              = EVE3_CODE_ADDR        + EVE3_CODE_SIZE;
EVE4_VECS_ADDR              = EVE3_DATA_ADDR        + EVE3_DATA_SIZE;
EVE4_CODE_ADDR              = EVE4_VECS_ADDR        + EVE4_VECS_SIZE;
EVE4_DATA_ADDR              = EVE4_CODE_ADDR        + EVE4_CODE_SIZE;
IPU1_1_CODE_ADDR            = EVE4_DATA_ADDR        + EVE4_DATA_SIZE;
IPU1_1_DATA_ADDR            = IPU1_1_CODE_ADDR      + IPU1_1_CODE_SIZE;
IPU1_1_BSS_ADDR             = IPU1_1_DATA_ADDR      + IPU1_1_DATA_SIZE;
IPU1_0_CODE_ADDR            = IPU1_1_BSS_ADDR       + IPU1_1_BSS_SIZE;
IPU1_0_DATA_ADDR            = IPU1_0_CODE_ADDR      + IPU1_0_CODE_SIZE;
IPU1_0_BSS_ADDR             = IPU1_0_DATA_ADDR      + IPU1_0_DATA_SIZE;
SR1_FRAME_BUFFER_ADDR       = IPU1_0_BSS_ADDR       + IPU1_0_BSS_SIZE;
DSP1_CODE_ADDR              = SR1_FRAME_BUFFER_ADDR + SR1_FRAME_BUFFER_SIZE;
DSP1_DATA_ADDR              = DSP1_CODE_ADDR        + DSP1_CODE_SIZE;
DSP2_CODE_ADDR              = DSP1_DATA_ADDR        + DSP1_DATA_SIZE;
DSP2_DATA_ADDR              = DSP2_CODE_ADDR        + DSP2_CODE_SIZE;
A15_0_CODE_ADDR             = DSP2_DATA_ADDR        + DSP2_DATA_SIZE;
A15_0_DATA_ADDR             = A15_0_CODE_ADDR       + A15_0_CODE_SIZE;


/* Non Cached Section */
/* The start address of the second mem section should be 16MB aligned.
 * This alignment is a must as a single 16MB mapping is used for EVE
 * to map SR0, EMOTE_LOG_MEM sections.
 * tlb_config_eveX.c need to be modified otherwise
 */
SR0_ADDR                    = DDR3_BASE_ADDR_1;
REMOTE_LOG_ADDR             = SR0_ADDR              + SR0_SIZE;
HDVPSS_DESC_ADDR            = REMOTE_LOG_ADDR       + REMOTE_LOG_SIZE;

if ((A15_0_DATA_ADDR + A15_0_DATA_SIZE) > (DDR3_BASE_ADDR_0 + DDR3_BASE_SIZE_0))
{
  throw xdc.$$XDCException("MEMORY_MAP OVERFLOW ERROR ",
                           "\nRegion End: " + "0x" + java.lang.Long.toHexString(DDR3_BASE_ADDR_0 + DDR3_BASE_SIZE_0) +
                           "\nActual End: " + "0x" + java.lang.Long.toHexString(A15_0_DATA_ADDR + A15_0_DATA_SIZE));
}

if ((HDVPSS_DESC_ADDR + HDVPSS_DESC_SIZE) > (DDR3_BASE_ADDR_1 + DDR3_BASE_SIZE_1))
{
  throw xdc.$$XDCException("MEMORY_MAP OVERFLOW ERROR ",
                           "\nRegion End: " + "0x" + java.lang.Long.toHexString(DDR3_BASE_ADDR_1 + DDR3_BASE_SIZE_1) +
                           "\nActual End: " + "0x" + java.lang.Long.toHexString(HDVPSS_DESC_ADDR + HDVPSS_DESC_SIZE));
}

if ((DDR3_BASE_SIZE_1 + DDR3_BASE_SIZE_0) > (TOTAL_MEM_SIZE))
{
  throw xdc.$$XDCException("MEMORY_MAP EXCEEDS 256mb ERROR ",
                           "\nRegion End: " + "0x" + java.lang.Long.toHexString(DDR3_BASE_SIZE_1 + DDR3_BASE_SIZE_0) +
                           "\nActual End: " + "0x" + java.lang.Long.toHexString(TOTAL_MEM_SIZE));
}


function getMemSegmentDefinition_external(core)
{
    var memory = new Array();
    var index = 0;

    memory[index++] = ["IPU1_1_CODE_MEM", {
            comment : "IPU1_1_CODE_MEM",
            name    : "IPU1_1_CODE_MEM",
            base    : IPU1_1_CODE_ADDR,
            len     : IPU1_1_CODE_SIZE
        }];
    memory[index++] = ["IPU1_1_DATA_MEM", {
            comment : "IPU1_1_DATA_MEM",
            name    : "IPU1_1_DATA_MEM",
            base    : IPU1_1_DATA_ADDR,
            len     : IPU1_1_DATA_SIZE
        }];
    memory[index++] = ["IPU1_1_BSS_MEM", {
            comment : "IPU1_1_BSS_MEM",
            name    : "IPU1_1_BSS_MEM",
            base    : IPU1_1_BSS_ADDR,
            len     : IPU1_1_BSS_SIZE
        }];
    memory[index++] = ["IPU1_0_CODE_MEM", {
            comment : "IPU1_0_CODE_MEM",
            name    : "IPU1_0_CODE_MEM",
            base    : IPU1_0_CODE_ADDR,
            len     : IPU1_0_CODE_SIZE
        }];
    memory[index++] = ["IPU1_0_DATA_MEM", {
            comment : "IPU1_0_DATA_MEM",
            name    : "IPU1_0_DATA_MEM",
            base    : IPU1_0_DATA_ADDR,
            len     : IPU1_0_DATA_SIZE
        }];
    memory[index++] = ["IPU1_0_BSS_MEM", {
            comment : "IPU1_0_BSS_MEM",
            name    : "IPU1_0_BSS_MEM",
            base    : IPU1_0_BSS_ADDR,
            len     : IPU1_0_BSS_SIZE
        }];
    memory[index++] = ["DSP1_CODE_MEM", {
            comment : "DSP1_CODE_MEM",
            name    : "DSP1_CODE_MEM",
            base    : DSP1_CODE_ADDR,
            len     : DSP1_CODE_SIZE
        }];
    memory[index++] = ["DSP1_DATA_MEM", {
            comment : "DSP1_DATA_MEM",
            name    : "DSP1_DATA_MEM",
            base    : DSP1_DATA_ADDR,
            len     : DSP1_DATA_SIZE
        }];

    memory[index++] = ["DSP2_CODE_MEM", {
            comment : "DSP2_CODE_MEM",
            name    : "DSP2_CODE_MEM",
            base    : DSP2_CODE_ADDR,
            len     : DSP2_CODE_SIZE
        }];
    memory[index++] = ["DSP2_DATA_MEM", {
            comment : "DSP2_DATA_MEM",
            name    : "DSP2_DATA_MEM",
            base    : DSP2_DATA_ADDR,
            len     : DSP2_DATA_SIZE
        }];

    memory[index++] = ["A15_0_CODE_MEM", {
            comment : "A15_0_CODE_MEM",
            name    : "A15_0_CODE_MEM",
            base    : A15_0_CODE_ADDR,
            len     : A15_0_CODE_SIZE
        }];
    memory[index++] = ["A15_0_DATA_MEM", {
            comment : "A15_0_DATA_MEM",
            name    : "A15_0_DATA_MEM",
            base    : A15_0_DATA_ADDR,
            len     : A15_0_DATA_SIZE
        }];


    memory[index++] = ["EVE1_VECS_MEM", {
            comment : "EVE1_VECS_MEM",
            name    : "EVE1_VECS_MEM",
            base    : EVE1_VECS_ADDR,
            len     : EVE1_VECS_SIZE
        }];
    memory[index++] = ["EVE1_CODE_MEM", {
            comment : "EVE1_CODE_MEM",
            name    : "EVE1_CODE_MEM",
            base    : EVE1_CODE_ADDR,
            len     : EVE1_CODE_SIZE
        }];
    memory[index++] = ["EVE1_DATA_MEM", {
            comment : "EVE1_DATA_MEM",
            name    : "EVE1_DATA_MEM",
            base    : EVE1_DATA_ADDR,
            len     : EVE1_DATA_SIZE
        }];
    memory[index++] = ["EVE2_VECS_MEM", {
            comment : "EVE2_VECS_MEM",
            name    : "EVE2_VECS_MEM",
            base    : EVE2_VECS_ADDR,
            len     : EVE2_VECS_SIZE
        }];
    memory[index++] = ["EVE2_CODE_MEM", {
            comment : "EVE2_CODE_MEM",
            name    : "EVE2_CODE_MEM",
            base    : EVE2_CODE_ADDR,
            len     : EVE2_CODE_SIZE
        }];
    memory[index++] = ["EVE2_DATA_MEM", {
            comment : "EVE2_DATA_MEM",
            name    : "EVE2_DATA_MEM",
            base    : EVE2_DATA_ADDR,
            len     : EVE2_DATA_SIZE
        }];
    memory[index++] = ["EVE3_VECS_MEM", {
            comment : "EVE3_VECS_MEM",
            name    : "EVE3_VECS_MEM",
            base    : EVE3_VECS_ADDR,
            len     : EVE3_VECS_SIZE
        }];
    memory[index++] = ["EVE3_CODE_MEM", {
            comment : "EVE3_CODE_MEM",
            name    : "EVE3_CODE_MEM",
            base    : EVE3_CODE_ADDR,
            len     : EVE3_CODE_SIZE
        }];
    memory[index++] = ["EVE3_DATA_MEM", {
            comment : "EVE3_DATA_MEM",
            name    : "EVE3_DATA_MEM",
            base    : EVE3_DATA_ADDR,
            len     : EVE3_DATA_SIZE
        }];
    memory[index++] = ["EVE4_VECS_MEM", {
            comment : "EVE4_VECS_MEM",
            name    : "EVE4_VECS_MEM",
            base    : EVE4_VECS_ADDR,
            len     : EVE4_VECS_SIZE
        }];
    memory[index++] = ["EVE4_CODE_MEM", {
            comment : "EVE4_CODE_MEM",
            name    : "EVE4_CODE_MEM",
            base    : EVE4_CODE_ADDR,
            len     : EVE4_CODE_SIZE
        }];
    memory[index++] = ["EVE4_DATA_MEM", {
            comment : "EVE4_DATA_MEM",
            name    : "EVE4_DATA_MEM",
            base    : EVE4_DATA_ADDR,
            len     : EVE4_DATA_SIZE
        }];
    memory[index++] = ["SR1_FRAME_BUFFER_MEM", {
            comment : "SR1_FRAME_BUFFER_MEM",
            name    : "SR1_FRAME_BUFFER_MEM",
            base    : SR1_FRAME_BUFFER_ADDR,
            len     : SR1_FRAME_BUFFER_SIZE
        }];
    memory[index++] = ["SR0", {
            comment : "SR0",
            name    : "SR0",
            base    : SR0_ADDR,
            len     : SR0_SIZE
        }];
    memory[index++] = ["HDVPSS_DESC_MEM", {
            comment : "HDVPSS_DESC_MEM",
            name    : "HDVPSS_DESC_MEM",
            base    : HDVPSS_DESC_ADDR,
            len     : HDVPSS_DESC_SIZE
        }];
    memory[index++] = ["REMOTE_LOG_MEM", {
            comment : "REMOTE_LOG_MEM",
            name    : "REMOTE_LOG_MEM",
            base    : REMOTE_LOG_ADDR,
            len     : REMOTE_LOG_SIZE
        }];

/*  Memory name OCMC_RAM1, 2 & 3 are defined internally in evmDRA7XX platform
    So no need to specify them explicitly for IPU1, A15
*/
    xdc.print("# !!! Core is [" + core + "] !!!" );

    if( core == "c66xdsp_1" ||
        core == "c66xdsp_2" ||
        core == "arp32_1"   ||
        core == "arp32_2"   ||
        core == "arp32_3"   ||
        core == "arp32_4"
    )
    {
            memory[index++] = ["OCMC_RAM1", {
                    comment: "OCMC_RAM1",
                    name: "OCMC_RAM1",
                    base: OCMC1_ADDR,
                    len:  OCMC1_SIZE
                }];
            memory[index++] = ["OCMC_RAM2", {
                    comment: "OCMC_RAM2",
                    name: "OCMC_RAM2",
                    base: OCMC2_ADDR,
                    len:  OCMC2_SIZE
                }];
            memory[index++] = ["OCMC_RAM3", {
                    comment: "OCMC_RAM3",
                    name: "OCMC_RAM3",
                    base: OCMC3_ADDR,
                    len:  OCMC3_SIZE
                }];
    }
    memory[index++] = ["DSP1_L2_SRAM", {
            comment: "DSP1_L2_SRAM",
            name: "DSP1_L2_SRAM",
            base: DSP1_L2_SRAM_ADDR,
            len:  DSP1_L2_SRAM_SIZE
        }];
    memory[index++] = ["DSP2_L2_SRAM", {
            comment: "DSP2_L2_SRAM",
            name: "DSP2_L2_SRAM",
            base: DSP2_L2_SRAM_ADDR,
            len:  DSP2_L2_SRAM_SIZE
        }];

    return (memory);
}
