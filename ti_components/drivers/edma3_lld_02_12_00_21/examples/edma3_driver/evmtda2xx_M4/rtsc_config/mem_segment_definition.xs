/*******************************************************************************
 *                                                                             *
 * Copyright (c) 2011 Texas Instruments Incorporated - http://www.ti.com/      *
 *                        ALL RIGHTS RESERVED                                  *
 *                                                                             *
 ******************************************************************************/

/*
 *  ======== mem_segment_definition.xs ========
 */


function getMemSegmentDefinitionIPU_1_0()
{
    var memory = new Array();

    memory[0] = ["CODE_CORE_IPU1_0",
    {
          name: "CODE_CORE_IPU1_0",
          base: 0x84000000,
          len:  0x01000000,
          space: "code",
          access: "RWX"
    }];

    memory[1] = ["PRIVATE_DATA_CORE_IPU1_0",
    {
          name: "PRIVATE_DATA_CORE_IPU1_0",
          base: 0x85000000,
          len:  0x01800000,
          space: "data",
          access: "RWX"
    }];

    memory[2] = ["HDVPSS_DESCRIPTOR_NON_CACHED",
    {
          name: "HDVPSS_DESCRIPTOR_NON_CACHED",
          base: 0xA1800000,
          len:  0x00800000,
          space: "data",
          access: "RWX"
    }];

    memory[3] = ["SHARED_MEM",
    {
          name: "SHARED_MEM",
          base: 0xA2000000,
          len:  0x01000000,
          space: "data",
          access: "RWX"
    }];

    memory[4] = ["SHARED_FRAME_BUFFER",
    {
          name: "SHARED_FRAME_BUFFER",
          base: 0x8A000000,
          len:  0x04000000,
          space: "data",
          access: "RWX"
    }];

    memory[5] = ["SHARED_CTRL",
    {
          name: "SHARED_CTRL",
          base: 0xA0000000,
          len:  0x01000000,
          space: "code/data",
          access: "RWX"
    }];

    memory[6] = ["SHARED_LOG_MEM",
    {
          name: "SHARED_LOG_MEM",
          base: 0xA1000000,
          len:  0x00700000,
          space: "data",
          access: "RWX"
    }];
    
    return (memory);
}

function getMemSegmentDefinitionIPU_1_1()
{
    var memory = new Array();

    memory[0] = ["CODE_CORE_IPU1_1",
    {
          name: "CODE_CORE_IPU1_1",
          base: 0x86800000,
          len:  0x01000000,
          space: "code",
          access: "RWX"
    }];

    memory[1] = ["PRIVATE_DATA_CORE_IPU1_1",
    {
          name: "PRIVATE_DATA_CORE_IPU1_1",
          base: 0x87800000,
          len:  0x01800000,
          space: "data",
          access: "RWX"
    }];

    memory[2] = ["SHARED_MEM",
    {
          name: "SHARED_MEM",
          base: 0xA2000000,
          len:  0x01000000,
          space: "data",
          access: "RWX"
    }];

    memory[3] = ["SHARED_FRAME_BUFFER",
    {
          name: "SHARED_FRAME_BUFFER",
          base: 0x8A000000,
          len:  0x04000000,
          space: "data",
          access: "RWX"
    }];

    memory[4] = ["SHARED_CTRL",
    {
          name: "SHARED_CTRL",
          base: 0xA0000000,
          len:  0x01000000,
          space: "code/data",
          access: "RWX"
    }];

    memory[5] = ["SHARED_LOG_MEM",
    {
          name: "SHARED_LOG_MEM",
          base: 0xA1000000,
          len:  0x00700000,
          space: "data",
          access: "RWX"
    }];
    
    return (memory);
}

function getMemSegmentDefinitionDSP_1()
{
    var memory = new Array();

    memory[0] = ["CODE_CORE_DSP1",
    {
          name: "CODE_CORE_DSP1",
          base: 0x83100000,
          len:  0x00700000,
          space: "code",
          access: "RWX"
    }];

    memory[1] = ["PRIVATE_DATA_CORE_DSP1",
    {
          name: "PRIVATE_DATA_CORE_DSP1",
          base: 0x83800000,
          len:  0x00800000,
          space: "data",
          access: "RWX"
    }];

    memory[2] = ["SHARED_MEM",
    {
          name: "SHARED_MEM",
          base: 0xA2000000,
          len:  0x01000000,
          space: "data",
          access: "RWX"
    }];

    memory[3] = ["SHARED_FRAME_BUFFER",
    {
          name: "SHARED_FRAME_BUFFER",
          base: 0x8A000000,
          len:  0x04000000,
          space: "data",
          access: "RWX"
    }];

    memory[4] = ["SHARED_CTRL",
    {
          name: "SHARED_CTRL",
          base: 0xA0000000,
          len:  0x01000000,
          space: "code/data",
          access: "RWX"
    }];

    memory[5] = ["SHARED_LOG_MEM",
    {
          name: "SHARED_LOG_MEM",
          base: 0xA1000000,
          len:  0x00700000,
          space: "data",
          access: "RWX"
    }];
    
    return (memory);
}

function getMemSegmentDefinitionHOST()
{
    var memory = new Array();

    memory[8] = ["CODE_CORE_HOST",
    {
          name: "CODE_CORE_HOST",
          base: 0x89000000,
          len:  0x00800000,
          space: "code",
          access: "RWX"
    }];

    memory[9] = ["PRIVATE_DATA_CORE_HOST",
    {
          name: "PRIVATE_DATA_CORE_HOST",
          base: 0x89800000,
          len:  0x00800000,
          space: "data",
          access: "RWX"
    }];

    memory[10] = ["SHARED_MEM",
    {
          name: "SHARED_MEM",
          base: 0xA2000000,
          len:  0x01000000,
          space: "data",
          access: "RWX"
    }];

    memory[11] = ["SHARED_FRAME_BUFFER",
    {
          name: "SHARED_FRAME_BUFFER",
          base: 0x8A000000,
          len:  0x04000000,
          space: "data",
          access: "RWX"
    }];

    memory[12] = ["SHARED_CTRL",
    {
          name: "SHARED_CTRL",
          base: 0xA0000000,
          len:  0x01000000,
          space: "code/data",
          access: "RWX"
    }];

    memory[13] = ["SHARED_LOG_MEM",
    {
          name: "SHARED_LOG_MEM",
          base: 0xA1000000,
          len:  0x00700000,
          space: "data",
          access: "RWX"
    }];

    return (memory);
}
