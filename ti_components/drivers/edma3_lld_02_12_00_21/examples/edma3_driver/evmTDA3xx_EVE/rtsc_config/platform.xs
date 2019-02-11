/*******************************************************************************
 *                                                                             *
 * Copyright (c) 2011 Texas Instruments Incorporated - http://www.ti.com/      *
 *                        ALL RIGHTS RESERVED                                  *
 *                                                                             *
 ******************************************************************************/

/*
 *  ======== platform.xs ========
 */

var Build = xdc.useModule('xdc.bld.BuildEnvironment');

var MemSegDefine = xdc.loadCapsule("mem_segment_definition.xs");

Build.platformTable["ti.platforms.evmDRA7XX:IPU_1_0"] =
{
	externalMemoryMap: MemSegDefine.getMemSegmentDefinitionIPU_1_0(),
	codeMemory:"CODE_CORE_IPU1_0",
	dataMemory:"PRIVATE_DATA_CORE_IPU1_0",
	stackMemory:"PRIVATE_DATA_CORE_IPU1_0"
};

Build.platformTable["ti.platforms.evmDRA7XX:IPU_1_1"] =
{
	externalMemoryMap: MemSegDefine.getMemSegmentDefinitionIPU_1_1(),
	codeMemory:"CODE_CORE_IPU1_1",
	dataMemory:"PRIVATE_DATA_CORE_IPU1_1",
	stackMemory:"PRIVATE_DATA_CORE_IPU1_1"
};

Build.platformTable["ti.platforms.evmDRA7XX:DSP_1"] =
{
    externalMemoryMap: MemSegDefine.getMemSegmentDefinitionDSP_1(),
    codeMemory:"CODE_CORE_DSP1",
    dataMemory:"PRIVATE_DATA_CORE_DSP1",
    stackMemory:"PRIVATE_DATA_CORE_DSP1"
};

Build.platformTable["ti.platforms.evmDRA7XX:Cortex_A15"] =
{
    externalMemoryMap: MemSegDefine.getMemSegmentDefinitionHOST(),
    codeMemory:"CODE_CORE_HOST",
    dataMemory:"PRIVATE_DATA_CORE_HOST",
    stackMemory:"PRIVATE_DATA_CORE_HOST"
};

Build.platformTable["ti.platforms.evmDRA7XX:EVE_1"] =
{
    externalMemoryMap: MemSegDefine.getMemSegmentDefinitionEVE(),
    codeMemory:"CODE_CORE_EVE",
    dataMemory:"PRIVATE_DATA_CORE_EVE",
    stackMemory:"PRIVATE_DATA_CORE_EVE"
};
