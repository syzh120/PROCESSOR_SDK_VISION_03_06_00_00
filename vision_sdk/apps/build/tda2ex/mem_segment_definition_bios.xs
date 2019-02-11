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
    /*Define a variable to use as a flag to enable the performance optimizations if the NDK Processor to use is A15*/
    var NdkProcToUse = java.lang.System.getenv("NDK_PROC_TO_USE");

    KB=1024;
    MB=KB*KB;

    DDR3_ADDR                   = 0x80000000;
    DDR3_SIZE                   = 512*MB;

    DDR3_BASE_ADDR_0            = DDR3_ADDR;
    DDR3_BASE_SIZE_0            = 508*MB;

    /* The start address of the second mem section should be 16MB aligned.
     * This alignment is a must as a single 16MB mapping is used for EVE
     * to map SR0, REMOTE_LOG_MEM sections.
     * tlb_config_eveX.c need to be modified otherwise
     */
    DDR3_BASE_ADDR_1            = DDR3_BASE_ADDR_0 + DDR3_BASE_SIZE_0;
    DDR3_BASE_SIZE_1            = DDR3_SIZE - DDR3_BASE_SIZE_0;
    if(core=="ipu1_1" || core=="ipu1_0" || core=="ipu2" || core=="a15_0")
    {
        /*  for ipu1_0, ipu1_1, ipu2 DDR3_BASE_ADDR_1 should be
         *  in non-cached virtual address of
         *  DDR3_BASE_ADDR_1 + 512*MB
         */
        DDR3_BASE_ADDR_1        = DDR3_BASE_ADDR_1+512*MB;
    }

    DSP1_L2_SRAM_ADDR           = 0x40800000;
    DSP1_L2_SRAM_SIZE           = 288*KB;

    TOTAL_MEM_SIZE              = (DDR3_SIZE);

    /*CPDMA DECS IN DDR3*/
    HOST_0_BUFF_DESC_SIZE       =   2*MB;
    /* First 512 MB - cached
     * SR1_FRAME_BUFFER_MEM section is modified.
     */
    NDK_DATA_SIZE               =   4*MB;
    IPU1_1_CODE_SIZE            =   2*MB;
    IPU1_1_DATA_SIZE            =  10*MB;
    IPU1_0_CODE_SIZE            =  10*MB;
    IPU1_0_DATA_SIZE            =  12*MB;
    IPU2_CODE_SIZE              =   2*MB;
    IPU2_DATA_SIZE              =  10*MB;
    DSP1_CODE_SIZE              =   2*MB;
    DSP1_DATA_SIZE              =  13*MB;
    DSP1_DATA_SIZE_2            =   2*MB;
    /* A15_0_CODE_SIZE reduced since it is not used in .bld file.
     * Check .bld for details. Originally 2 + 14 MB.
     */
    A15_0_DATA_SIZE             =  13*MB;
    if(java.lang.System.getenv("ECC_FFI_INCLUDE")=="yes")
    {
        /* Ensure ECC regions are 64kB aligned */
        SR1_FRAME_BUFFER_SIZE       = 309*MB;
        SR1_BUFF_ECC_ASIL_SIZE      =   1*MB;
        SR1_BUFF_ECC_QM_SIZE        =  40*MB;
        SR1_BUFF_NON_ECC_ASIL_SIZE  =   1*MB;
    }
    else
    {
        SR1_BUFF_ECC_ASIL_SIZE      =   4*KB;
        SR1_BUFF_ECC_QM_SIZE        =   4*KB;
        SR1_BUFF_NON_ECC_ASIL_SIZE  =   4*KB;
        SR1_FRAME_BUFFER_SIZE       = 351*MB - (SR1_BUFF_ECC_ASIL_SIZE + SR1_BUFF_ECC_QM_SIZE + SR1_BUFF_NON_ECC_ASIL_SIZE);
    }

    /* Second 512 MB - non-cached */
    REMOTE_LOG_SIZE             =  160*KB;
    SYSTEM_IPC_SHM_SIZE         =  480*KB;
    LINK_STATS_SIZE             =  256*KB;
    HDVPSS_DESC_SIZE            = 1024*KB;
    SR0_SIZE                    =  128*KB;
    OPENVX_SHM_SIZE             =    2*MB;


    /* Cached Section
     * SR1_FRAME_BUFFER_MEM section is modified.
     */

    /* Changes for ECC
     * EVE code will run only from non-ECC region
     * All code section should be next to non-ECC region (using EVE section) to
     * allow them to be easily taken out of ECC region for debugging.
     * Make sure DSP1_DATA_ADDR_2 and DSP2_DATA_ADDR_2 are immediately after
     * SR1_BUFF_ECC_QM_ADDR and should be 2*MB in total - this size should
     * be kept constant across all platforms and should match the increment
     * to heapStats.heapSize in utils_xmc_mpu.c
     */
    /* To store CPDMA buffer descriptors in the DDR, we are using a 512 MB page. We have to define
     * the first 2MB as non-cacheable and the rest of the page as cacheable, this is done in the A15
     * config file. We need to put this at the start of the page, whenever A15 is the NDK processor
     * to use.
     */ 
    if(NdkProcToUse == "a15_0") 
    {
        HOST_0_BUFF_DESC_ADDR      = DDR3_BASE_ADDR_0; 
        NDK_DATA_ADDR              = HOST_0_BUFF_DESC_ADDR      + HOST_0_BUFF_DESC_SIZE;
    }
    else
    {
        NDK_DATA_ADDR           = DDR3_BASE_ADDR_0;
    }
    IPU1_1_CODE_ADDR           = NDK_DATA_ADDR              + NDK_DATA_SIZE;
    IPU1_0_CODE_ADDR           = IPU1_1_CODE_ADDR           + IPU1_1_CODE_SIZE;
    IPU2_CODE_ADDR             = IPU1_0_CODE_ADDR           + IPU1_0_CODE_SIZE;
    DSP1_CODE_ADDR             = IPU2_CODE_ADDR             + IPU2_CODE_SIZE;
    IPU1_1_DATA_ADDR           = DSP1_CODE_ADDR             + DSP1_CODE_SIZE;
    IPU1_0_DATA_ADDR           = IPU1_1_DATA_ADDR           + IPU1_1_DATA_SIZE;
    IPU2_DATA_ADDR             = IPU1_0_DATA_ADDR           + IPU1_0_DATA_SIZE;
    DSP1_DATA_ADDR             = IPU2_DATA_ADDR             + IPU2_DATA_SIZE;
    A15_0_DATA_ADDR            = DSP1_DATA_ADDR             + DSP1_DATA_SIZE;
    SR1_BUFF_ECC_ASIL_ADDR     = A15_0_DATA_ADDR            + A15_0_DATA_SIZE;
    SR1_BUFF_ECC_QM_ADDR       = SR1_BUFF_ECC_ASIL_ADDR     + SR1_BUFF_ECC_ASIL_SIZE;
    DSP1_DATA_ADDR_2           = SR1_BUFF_ECC_QM_ADDR       + SR1_BUFF_ECC_QM_SIZE;
    SR1_BUFF_NON_ECC_ASIL_ADDR = DSP1_DATA_ADDR_2           + DSP1_DATA_SIZE_2;
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
    OPENVX_SHM_ADDR             = HDVPSS_DESC_ADDR      + HDVPSS_DESC_SIZE;

    if ((SR1_FRAME_BUFFER_ADDR + SR1_FRAME_BUFFER_SIZE) > (DDR3_BASE_ADDR_0 + DDR3_BASE_SIZE_0))
    {
      throw xdc.$$XDCException("MEMORY_MAP OVERFLOW ERROR ",
                               "\nRegion End: " + "0x" + java.lang.Long.toHexString(DDR3_BASE_ADDR_0 + DDR3_BASE_SIZE_0) +
                               "\nActual End: " + "0x" + java.lang.Long.toHexString(SR1_FRAME_BUFFER_ADDR + SR1_FRAME_BUFFER_SIZE));
    }

    if ((OPENVX_SHM_ADDR + OPENVX_SHM_SIZE) > (DDR3_BASE_ADDR_1 + DDR3_BASE_SIZE_1))
    {
        throw xdc.$$XDCException("MEMORY_MAP OVERFLOW ERROR with OpenVx",
                           "\nRegion End: " + "0x" + java.lang.Long.toHexString(DDR3_BASE_ADDR_1 + DDR3_BASE_SIZE_1) +
                           "\nActual End: " + "0x" + java.lang.Long.toHexString(OPENVX_SHM_ADDR + OPENVX_SHM_SIZE));
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
    memory[index++] = ["IPU2_CODE_MEM", {
            comment : "IPU2_CODE_MEM",
            name    : "IPU2_CODE_MEM",
            base    : IPU2_CODE_ADDR,
            len     : IPU2_CODE_SIZE
        }];
    memory[index++] = ["IPU2_DATA_MEM", {
            comment : "IPU2_DATA_MEM",
            name    : "IPU2_DATA_MEM",
            base    : IPU2_DATA_ADDR,
            len     : IPU2_DATA_SIZE
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
    memory[index++] = ["DSP1_DATA_MEM_2", {
            comment : "DSP1_DATA_MEM_2",
            name    : "DSP1_DATA_MEM_2",
            base    : DSP1_DATA_ADDR_2,
            len     : DSP1_DATA_SIZE_2
        }];
    /* Add the newly created section for storing buffer descriptors to the memory whenever
     * A15 is the NDK processor.
     */
    if(NdkProcToUse == "a15_0")
    {
        memory[index++] = ["HOST_0_BUFF_DESC_MEM", {
                comment : "CPDMA_EXT_RAM_BUFF_DESC",
                name    : "HOST_0_BUFF_DESC_MEM",
                base    : HOST_0_BUFF_DESC_ADDR,
                len     : HOST_0_BUFF_DESC_SIZE
            }];
    }
    memory[index++] = ["NDK_MEM", {
            comment : "NDK_MEM",
            name    : "NDK_MEM",
            base    : NDK_DATA_ADDR,
            len     : NDK_DATA_SIZE
        }];
    memory[index++] = ["A15_0_DATA_MEM", {
            comment : "A15_0_DATA_MEM",
            name    : "A15_0_DATA_MEM",
            base    : A15_0_DATA_ADDR,
            len     : A15_0_DATA_SIZE
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

    memory[index++] = ["DSP1_L2_SRAM", {
            comment: "DSP1_L2_SRAM",
            name: "DSP1_L2_SRAM",
            base: DSP1_L2_SRAM_ADDR,
            len:  DSP1_L2_SRAM_SIZE
        }];

    if(java.lang.System.getenv("OPENVX_INCLUDE")=="yes")
    {
        memory[index++] = ["OPENVX_SHM_MEM", {
                comment: "OPENVX_SHM_MEM",
                name: "OPENVX_SHM_MEM",
                base: OPENVX_SHM_ADDR,
               len:  OPENVX_SHM_SIZE
        }];
    }

    return (memory);
}

