/*
 *******************************************************************************
 *
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *
 *******************************************************************************
 */

/*
 *  ======== mem_segment_definition.xs ========
 *  ======== Single file for the memory map configuration of all cores =========
 */

function getMemSegmentDefinition_external(core)
{
    KB=1024;
    MB=KB*KB;

    DDR3_ADDR                   = 0x80000000;
    DDR3_SIZE                   = 128*MB;

    DDR3_BASE_ADDR_0            = DDR3_ADDR;
    DDR3_BASE_SIZE_0            = 126*MB;

    /* The start address of the second mem section should be 16MB aligned.
     * This alignment is a must as a single 16MB mapping is used for EVE
     * to map SR0, REMOTE_LOG_MEM sections.
     * tlb_config_eveX.c need to be modified otherwise
     */
    DDR3_BASE_ADDR_1            = DDR3_BASE_ADDR_0 + DDR3_BASE_SIZE_0;
    DDR3_BASE_SIZE_1            = DDR3_SIZE - DDR3_BASE_SIZE_0;
    if(core=="ipu1_1" || core=="ipu1_0")
    {
        /*  for ipu1_0, ipu1_1, DDR3_BASE_ADDR_1 should be
         *  in non-cached virtual address of
         *  DDR3_BASE_ADDR_1 + 512*MB
         */
        DDR3_BASE_ADDR_1        = DDR3_BASE_ADDR_1+512*MB;
    }

    OCMC1_ADDR                  = 0x40300000;
    OCMC1_SIZE                  = 512*KB;

    DSP1_L2_SRAM_ADDR           = 0x40800000;
    DSP1_L2_SRAM_SIZE           = 288*KB;

    EVE1_SRAM_ADDR              = 0x42000000;
    EVE1_SRAM_SIZE              = 1*MB;

    TOTAL_MEM_SIZE              = (DDR3_SIZE);

    /* First 512 MB - cached */
    /* EVE vecs space should be align with 16MB boundary, and if possible try to fit
     * the entire vecs+code+data in 16MB section. In this case a single TLB map would
     * be enough to map vecs+code+data of an EVE.
     * tlb_config_eveX.c need to be modified if any of these EVE memory sections or
     * SR1_FRAME_BUFFER_MEM section is modified.
     */

    /* EVE self-branch instruction block - EVE1_VECS
     * In SBL, EVE self-branch instruction is inserted @ 0x80000000 if no AppImage for EVE.
     * This could overwrites the code/data loaded at 0x80000000.
     * So Reserving a small memory block in the beginning of the DDR @0x8000 0000 for
     * EVE self-branch instruction if no AppImage for EVE.
     * If EVE enabled, then the EVE VECS/DATA/CODE is placed @0x8000 0000,
     * and hence we did not observe any issue.
     * If EVE is disabled, then also DO NOT remove this EVE1_VECS section @0x80000000,
     * if no AppImage for EVE. This could overwrites the code/data loaded at 0x80000000
     */

    EVE1_VECS_SIZE              = 0.5*MB;
    EVE1_CODE_SIZE              =   2*MB;
    EVE1_DATA_SIZE              =   6*MB;
    IPU1_1_CODE_SIZE            =   2*MB;
    IPU1_1_DATA_SIZE            =   4*MB + 512*KB;
    IPU1_0_CODE_SIZE            =   7*MB + 512*KB;
    IPU1_0_DATA_SIZE            =  12*MB;
    DSP1_CODE_SIZE              =   1*MB + 499*KB;
    DSP1_DATA_SIZE              =  11*MB;
    DSP2_CODE_SIZE              = 256*KB;
    DSP2_DATA_SIZE              = 256*KB;
    SR1_FRAME_BUFFER_SIZE       =  74*MB;
    SR1_BUFF_ECC_ASIL_SIZE      =   4*KB;
    SR1_BUFF_ECC_QM_SIZE        =   4*KB;
    SR1_BUFF_NON_ECC_ASIL_SIZE  =   4*KB;

    /* Second 512 MB - non-cached */
    /* The start address of the second mem section should be 16MB aligned.
     * This alignment is a must as a single 16MB mapping is used for EVE
     * to map SR0, REMOTE_LOG_MEM sections.
     * tlb_config_eveX.c need to be modified otherwise
     */
    REMOTE_LOG_SIZE             =  160*KB;
    SYSTEM_IPC_SHM_SIZE         =  480*KB;
    LINK_STATS_SIZE             =  256*KB;
    HDVPSS_DESC_SIZE            =  256*KB;
    SR0_SIZE                    =  DDR3_BASE_SIZE_1 - (REMOTE_LOG_SIZE+SYSTEM_IPC_SHM_SIZE+HDVPSS_DESC_SIZE+LINK_STATS_SIZE);

    /* Cached Section */
    /* EVE vecs space should be align with 16MB boundary, and if possible try to fit
     * the entire vecs+code+data in 16MB section. In this case a single TLB map would
     * be enough to map vecs+code+data of an EVE.
     * tlb_config_eveX.c need to be modified if any of these EVE memory sections or
     * SR1_FRAME_BUFFER_MEM section is modified.
     */

    /* EVE self-branch instruction block - EVE1_VECS
     * In SBL, EVE self-branch instruction is inserted @ 0x80000000 if no AppImage for EVE.
     * This could overwrites the code/data loaded at 0x80000000.
     * So Reserving a small memory block in the beginning of the DDR @0x8000 0000 for
     * EVE self-branch instruction if no AppImage for EVE.
     * If EVE enabled, then the EVE VECS/DATA/CODE is placed @0x8000 0000,
     * and hence we did not observe any issue.
     * If EVE is disabled, then also DO NOT remove this EVE1_VECS section @0x80000000,
     * if no AppImage for EVE. This could overwrites the code/data loaded at 0x80000000
     */

    EVE1_VECS_ADDR             = DDR3_BASE_ADDR_0;
    EVE1_CODE_ADDR             = EVE1_VECS_ADDR             + EVE1_VECS_SIZE;
    EVE1_DATA_ADDR             = EVE1_CODE_ADDR             + EVE1_CODE_SIZE;
    IPU1_1_CODE_ADDR           = EVE1_DATA_ADDR             + EVE1_DATA_SIZE;
    IPU1_0_CODE_ADDR           = IPU1_1_CODE_ADDR           + IPU1_1_CODE_SIZE;
    DSP1_CODE_ADDR             = IPU1_0_CODE_ADDR           + IPU1_0_CODE_SIZE;
    DSP2_CODE_ADDR             = DSP1_CODE_ADDR             + DSP1_CODE_SIZE;
    IPU1_1_DATA_ADDR           = DSP2_CODE_ADDR             + DSP2_CODE_SIZE;
    IPU1_0_DATA_ADDR           = IPU1_1_DATA_ADDR           + IPU1_1_DATA_SIZE;
    DSP1_DATA_ADDR             = IPU1_0_DATA_ADDR           + IPU1_0_DATA_SIZE;
    DSP2_DATA_ADDR             = DSP1_DATA_ADDR             + DSP1_DATA_SIZE;
    SR1_BUFF_ECC_ASIL_ADDR     = DSP2_DATA_ADDR             + DSP2_DATA_SIZE;
    SR1_BUFF_ECC_QM_ADDR       = SR1_BUFF_ECC_ASIL_ADDR     + SR1_BUFF_ECC_ASIL_SIZE;
    SR1_BUFF_NON_ECC_ASIL_ADDR = SR1_BUFF_ECC_QM_ADDR       + SR1_BUFF_ECC_QM_SIZE;
    SR1_FRAME_BUFFER_ADDR      = SR1_BUFF_NON_ECC_ASIL_ADDR + SR1_BUFF_NON_ECC_ASIL_SIZE;

    /* Non Cached Section */
    /* The start address of the second mem section should be 16MB aligned.
     * This alignment is a must as a single 16MB mapping is used for EVE
     * to map SR0, REMOTE_LOG_MEM sections.
     * tlb_config_eveX.c need to be modified otherwise
     */
    SR0_ADDR                    = DDR3_BASE_ADDR_1;
    REMOTE_LOG_ADDR             = SR0_ADDR              + SR0_SIZE;
    LINK_STATS_ADDR             = REMOTE_LOG_ADDR       + REMOTE_LOG_SIZE;
    SYSTEM_IPC_SHM_ADDR         = LINK_STATS_ADDR       + LINK_STATS_SIZE;
    HDVPSS_DESC_ADDR            = SYSTEM_IPC_SHM_ADDR   + SYSTEM_IPC_SHM_SIZE;

    if ((SR1_FRAME_BUFFER_ADDR + SR1_FRAME_BUFFER_SIZE) > (DDR3_BASE_ADDR_0 + DDR3_BASE_SIZE_0))
    {
      throw xdc.$$XDCException("MEMORY_MAP OVERFLOW ERROR ",
                               "\nRegion End: " + "0x" + java.lang.Long.toHexString(DDR3_BASE_ADDR_0 + DDR3_BASE_SIZE_0) +
                               "\nActual End: " + "0x" + java.lang.Long.toHexString(SR1_FRAME_BUFFER_ADDR + SR1_FRAME_BUFFER_SIZE));
    }

    if ((HDVPSS_DESC_ADDR + HDVPSS_DESC_SIZE) > (DDR3_BASE_ADDR_1 + DDR3_BASE_SIZE_1))
    {
      throw xdc.$$XDCException("MEMORY_MAP OVERFLOW ERROR ",
                               "\nRegion End: " + "0x" + java.lang.Long.toHexString(DDR3_BASE_ADDR_1 + DDR3_BASE_SIZE_1) +
                               "\nActual End: " + "0x" + java.lang.Long.toHexString(HDVPSS_DESC_ADDR + HDVPSS_DESC_SIZE));
    }

    if ((DDR3_BASE_SIZE_1 + DDR3_BASE_SIZE_0) > (TOTAL_MEM_SIZE))
    {
      throw xdc.$$XDCException("MEMORY_MAP EXCEEDS DDR SIZE ERROR ",
                               "\nRegion End: " + "0x" + java.lang.Long.toHexString(DDR3_BASE_SIZE_1 + DDR3_BASE_SIZE_0) +
                               "\nActual End: " + "0x" + java.lang.Long.toHexString(TOTAL_MEM_SIZE));
    }

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
    memory[index++] = ["SR1_FRAME_BUFFER_MEM", {
            comment : "SR1_FRAME_BUFFER_MEM",
            name    : "SR1_FRAME_BUFFER_MEM",
            base    : SR1_FRAME_BUFFER_ADDR,
            len     : SR1_FRAME_BUFFER_SIZE
        }];
    memory[index++] = ["SR1_BUFF_ECC_ASIL_MEM", {
            comment : "SR1_BUFF_ECC_ASIL_MEM",
            name    : "SR1_BUFF_ECC_ASIL_MEM",
            base    : SR1_BUFF_ECC_ASIL_ADDR,
            len     : SR1_BUFF_ECC_ASIL_SIZE
    }];
    memory[index++] = ["SR1_BUFF_ECC_QM_MEM", {
            comment : "SR1_BUFF_ECC_QM_MEM",
            name    : "SR1_BUFF_ECC_QM_MEM",
            base    : SR1_BUFF_ECC_QM_ADDR,
            len     : SR1_BUFF_ECC_QM_SIZE
    }];
    memory[index++] = ["SR1_BUFF_NON_ECC_ASIL_MEM", {
            comment : "SR1_BUFF_NON_ECC_ASIL_MEM",
            name    : "SR1_BUFF_NON_ECC_ASIL_MEM",
            base    : SR1_BUFF_NON_ECC_ASIL_ADDR,
            len     : SR1_BUFF_NON_ECC_ASIL_SIZE
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
    memory[index++] = ["LINK_STATS_MEM", {
            comment : "LINK_STATS_MEM",
            name    : "LINK_STATS_MEM",
            base    : LINK_STATS_ADDR,
            len     : LINK_STATS_SIZE
        }];
    memory[index++] = ["SYSTEM_IPC_SHM_MEM", {
            comment : "SYSTEM_IPC_SHM_MEM",
            name    : "SYSTEM_IPC_SHM_MEM",
            base    : SYSTEM_IPC_SHM_ADDR,
            len     : SYSTEM_IPC_SHM_SIZE
        }];

    xdc.print("# !!! Core is [" + core + "] !!!" );

    if( core == "arp32_1" )
    {
            memory[index++] = ["OCMC_RAM1", {
                    comment: "OCMC_RAM1",
                    name: "OCMC_RAM1",
                    base: OCMC1_ADDR,
                    len:  OCMC1_SIZE
                }];
    }
    memory[index++] = ["DSP1_L2_SRAM", {
            comment: "DSP1_L2_SRAM",
            name: "DSP1_L2_SRAM",
            base: DSP1_L2_SRAM_ADDR,
            len:  DSP1_L2_SRAM_SIZE
        }];

    return (memory);
}

