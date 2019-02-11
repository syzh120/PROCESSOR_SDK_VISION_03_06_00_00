#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_interference_zero_out_kernel, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_interference_zero_out_kernel, __ALIGNOF__(int));
unsigned short __pblock_vcop_interference_zero_out_kernel[16];

unsigned int vcop_interference_zero_out_kernel_param_count(void)
{
   return 16u;
}

unsigned int vcop_interference_zero_out_kernel_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_interference_zero_out_kernel_init(
   __vptr_int16 inputData,
   __vptr_int16 outputData,
   unsigned short interferenceThreshold,
   unsigned short numPoints,
   unsigned short numOfLines,
   unsigned short inputPitch,
   unsigned short outputPitch,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   const int preg_ref1 = _PREG(8);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (numOfLines)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (numPoints / (8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_4PARAM,preg_ref1,RM_NONE,0));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32);
   __vcop_pblock_4param_init(pblock, __offset+_PREG(8), interferenceThreshold,0,-(interferenceThreshold - 1),0);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), (inputPitch) -(8u*sizeof(*inputData)*2)*((numPoints / (8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(13), (outputPitch) -(8u*sizeof(*inputData)*2)*((numPoints / (8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)inputData);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)outputData);
   __offset += 16;

   return 16u;
}

void vcop_interference_zero_out_kernel_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VInputDataI", 16);
   #pragma VCC_VREG("VInputDataR", 17);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("inAddr", "A0");
   #pragma EVE_REG("outAddr", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 5u, 8u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(12), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(13), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(14), _AGEN(0), _VPAIR(17,16), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_alws(), _VPAIR(17,16), _PREG(16), _AGEN(1), _PREG(6));
   __vcop_vloop_end(1u);

}

void vcop_interference_zero_out_kernel(
   __vptr_int16 inputData,
   __vptr_int16 outputData,
   unsigned short interferenceThreshold,
   unsigned short numPoints,
   unsigned short numOfLines,
   unsigned short inputPitch,
   unsigned short outputPitch)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_interference_zero_out_kernel_init(inputData, outputData, interferenceThreshold, numPoints, numOfLines, inputPitch, outputPitch, __pblock_vcop_interference_zero_out_kernel);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_interference_zero_out_kernel_vloops(__pblock_vcop_interference_zero_out_kernel);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_interference_zero_out_kernel_custom(
   __vptr_int16 inputData,
   __vptr_int16 outputData,
   unsigned short interferenceThreshold,
   unsigned short numPoints,
   unsigned short numOfLines,
   unsigned short inputPitch,
   unsigned short outputPitch,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_interference_zero_out_kernel_init(inputData, outputData, interferenceThreshold, numPoints, numOfLines, inputPitch, outputPitch, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_interference_zero_out_kernel_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_dcoffset_kernel, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_dcoffset_kernel, __ALIGNOF__(int));
unsigned short __pblock_vcop_dcoffset_kernel[34];

unsigned int vcop_dcoffset_kernel_param_count(void)
{
   return 34u;
}

unsigned int vcop_dcoffset_kernel_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_dcoffset_kernel_init(
   __vptr_int16 inputData,
   __vptr_int32 scratchBuf,
   __vptr_uint16 pScatterIndex,
   __vptr_int16 dcOffsetBuf,
   unsigned short inputPitch,
   unsigned short transposeStride,
   unsigned short numPoints,
   unsigned short numOfLines,
   unsigned short shift,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (numOfLines)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (numPoints / (8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)inputData);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)scratchBuf);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)scratchBuf+numOfLines*sizeof(*scratchBuf));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), 4);
   __vcop_pblock_init16(pblock, __offset+_PREG(13), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), (inputPitch) -(8u*sizeof(*inputData)*2)*((numPoints / (8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pScatterIndex);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), 0);
   __offset += 18;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((((numOfLines) + (8u)-1) & ~((8u)-1)) / (8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_TRUNC,shift));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)scratchBuf+numOfLines*sizeof(*scratchBuf));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)dcOffsetBuf);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), (transposeStride));
   __vcop_pblock_init16(pblock, __offset+_PREG(13), (8u*sizeof(*scratchBuf)) -(transposeStride)*(((8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)scratchBuf);
   __offset += 16;

   return 34u;
}

void vcop_dcoffset_kernel_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VInputDataI", 16);
   #pragma VCC_VREG("VInputDataR", 17);
   #pragma VCC_VREG("Vindex", 18);
   #pragma VCC_VREG("VsumImg", 19);
   #pragma VCC_VREG("VsumReal", 20);
   #pragma VCC_VREG("Vtemp1", 21);
   #pragma VCC_VREG("Vtemp2", 22);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   #pragma EVE_REG("outAddr", "A1");
   #pragma EVE_REG("inAddr", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 12u, 9u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(18), _VREG(20));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(18), _VREG(19));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(12), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(13), _PREG(14), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(16), _AGEN(0), _VREG(18), __vcop_once());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(6), _AGEN(2), _VPAIR(17,16), __vcop_alws());
   __vcop_vadd(_VREG(20), _VREG(17), _VREG(20));
   __vcop_vadd(_VREG(19), _VREG(16), _VREG(19));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_pdda(_VREG(18)), __vcop_last_i4(), _VREG(20), _PREG(8), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_pdda(_VREG(18)), __vcop_last_i4(), _VREG(19), _PREG(10), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   #pragma EVE_REG("outAddr", "A1");
   #pragma EVE_REG("addrOut", "A2");
   #pragma EVE_REG("addrIn", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("i", "I3");
   #pragma EVE_REG("j", "I4");
   

   __vcop_vloop(__vcop_compute(), 12u, 8u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(14), _VREG(20));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(14), _VREG(19));
   __vcop_vagen(_AGEN(2), _PREG(0), _PREG(7), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(12), _PREG(13), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(16), _AGEN(3), _VREG(21), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(8), _AGEN(3), _VREG(22), __vcop_alws());
   __vcop_vadd(_VREG(20), _VREG(21), _VREG(20));
   __vcop_vadd(_VREG(19), _VREG(22), _VREG(19));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_last_i4(), _VPAIR(20,19), _PREG(10), _AGEN(2), _PREG(6));
   __vcop_vloop_end(2u);

}

void vcop_dcoffset_kernel(
   __vptr_int16 inputData,
   __vptr_int32 scratchBuf,
   __vptr_uint16 pScatterIndex,
   __vptr_int16 dcOffsetBuf,
   unsigned short inputPitch,
   unsigned short transposeStride,
   unsigned short numPoints,
   unsigned short numOfLines,
   unsigned short shift)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_dcoffset_kernel_init(inputData, scratchBuf, pScatterIndex, dcOffsetBuf, inputPitch, transposeStride, numPoints, numOfLines, shift, __pblock_vcop_dcoffset_kernel);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_dcoffset_kernel_vloops(__pblock_vcop_dcoffset_kernel);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_dcoffset_kernel_custom(
   __vptr_int16 inputData,
   __vptr_int32 scratchBuf,
   __vptr_uint16 pScatterIndex,
   __vptr_int16 dcOffsetBuf,
   unsigned short inputPitch,
   unsigned short transposeStride,
   unsigned short numPoints,
   unsigned short numOfLines,
   unsigned short shift,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_dcoffset_kernel_init(inputData, scratchBuf, pScatterIndex, dcOffsetBuf, inputPitch, transposeStride, numPoints, numOfLines, shift, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_dcoffset_kernel_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_windowing_kernel, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_windowing_kernel, __ALIGNOF__(int));
unsigned short __pblock_vcop_windowing_kernel[26];

unsigned int vcop_windowing_kernel_param_count(void)
{
   return 26u;
}

unsigned int vcop_windowing_kernel_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_windowing_kernel_init(
   __vptr_int16 inputData,
   __vptr_int16 winCoefficients,
   __vptr_int16 dcOffsetBuf,
   __vptr_int16 outputData,
   unsigned short numPoints,
   unsigned short numOfLines,
   unsigned short scaleFactor,
   unsigned short saturationLimit,
   unsigned short inputPitch,
   unsigned short outputPitch,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   const int preg_ref2 = _PREG(14);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (numOfLines)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (numPoints / (8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_4PARAM,preg_ref2,RM_ROUND,scaleFactor));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 4);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)inputData);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)winCoefficients);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)outputData);
   __vcop_pblock_4param_init(pblock, __offset+_PREG(14), (saturationLimit - 1), (saturationLimit - 1), -saturationLimit, -saturationLimit);
   __vcop_pblock_init16(pblock, __offset+_PREG(18), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(19),  -(8u*sizeof(*winCoefficients))*((numPoints / (8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(20), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(21), (inputPitch) -(8u*sizeof(*inputData)*2)*((numPoints / (8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(22), (outputPitch) -(8u*sizeof(*outputData)*2)*((numPoints / (8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)dcOffsetBuf);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)dcOffsetBuf+sizeof(*dcOffsetBuf));
   __offset += 26;

   return 26u;
}

void vcop_windowing_kernel_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VDcOffsetImg", 16);
   #pragma VCC_VREG("VDcOffsetReal", 17);
   #pragma VCC_VREG("VInputDataI", 18);
   #pragma VCC_VREG("VInputDataR", 19);
   #pragma VCC_VREG("VWinCoeff", 20);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addrDcOffset", "A0");
   #pragma EVE_REG("coeffAddr", "A1");
   #pragma EVE_REG("inAddr", "A2");
   #pragma EVE_REG("outAddr", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("j", "I3");
   #pragma EVE_REG("i", "I4");
   

   __vcop_vloop(__vcop_compute(), 14u, 13u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(7), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(18), _PREG(19), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(20), _PREG(21), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(20), _PREG(22), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_1pt(), _PREG(24), _AGEN(0), _VREG(17), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeH(), __vcop_1pt(), _PREG(26), _AGEN(0), _VREG(16), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(8), _AGEN(2), _VPAIR(19,18), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(10), _AGEN(1), _VREG(20), __vcop_alws());
   __vcop_vsub(_VREG(19), _VREG(17), _VREG(19));
   __vcop_vsub(_VREG(18), _VREG(16), _VREG(18));
   __vcop_vmpy(_VREG(19), _VREG(20), _VREG(19), _PREG(0));
   __vcop_vmpy(_VREG(18), _VREG(20), _VREG(18), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_alws(), _VPAIR(19,18), _PREG(12), _AGEN(3), _PREG(6));
   __vcop_vloop_end(1u);

}

void vcop_windowing_kernel(
   __vptr_int16 inputData,
   __vptr_int16 winCoefficients,
   __vptr_int16 dcOffsetBuf,
   __vptr_int16 outputData,
   unsigned short numPoints,
   unsigned short numOfLines,
   unsigned short scaleFactor,
   unsigned short saturationLimit,
   unsigned short inputPitch,
   unsigned short outputPitch)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_windowing_kernel_init(inputData, winCoefficients, dcOffsetBuf, outputData, numPoints, numOfLines, scaleFactor, saturationLimit, inputPitch, outputPitch, __pblock_vcop_windowing_kernel);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_windowing_kernel_vloops(__pblock_vcop_windowing_kernel);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_windowing_kernel_custom(
   __vptr_int16 inputData,
   __vptr_int16 winCoefficients,
   __vptr_int16 dcOffsetBuf,
   __vptr_int16 outputData,
   unsigned short numPoints,
   unsigned short numOfLines,
   unsigned short scaleFactor,
   unsigned short saturationLimit,
   unsigned short inputPitch,
   unsigned short outputPitch,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_windowing_kernel_init(inputData, winCoefficients, dcOffsetBuf, outputData, numPoints, numOfLines, scaleFactor, saturationLimit, inputPitch, outputPitch, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_windowing_kernel_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_windowing_with_transpose_kernel, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_windowing_with_transpose_kernel, __ALIGNOF__(int));
unsigned short __pblock_vcop_windowing_with_transpose_kernel[24];

unsigned int vcop_windowing_with_transpose_kernel_param_count(void)
{
   return 24u;
}

unsigned int vcop_windowing_with_transpose_kernel_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_windowing_with_transpose_kernel_init(
   __vptr_int16 inputData,
   __vptr_int16 winCoefficients,
   __vptr_int16 outputData,
   __vptr_uint16 pScatterIndex,
   unsigned short inputPitch,
   unsigned short transposePitch,
   unsigned short numPoints,
   unsigned short numOfLines,
   unsigned short scaleFactor,
   unsigned short saturationLimit,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   const int preg_ref3 = _PREG(12);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (numOfLines)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (numPoints / (8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_4PARAM,preg_ref3,RM_ROUND,scaleFactor));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 2);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)inputData);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)outputData);
   __vcop_pblock_4param_init(pblock, __offset+_PREG(12), (saturationLimit - 1), (saturationLimit - 1), -saturationLimit, -saturationLimit);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)outputData+sizeof(*outputData));
   __vcop_pblock_init16(pblock, __offset+_PREG(18), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(19), (inputPitch) -(8u*sizeof(*inputData)*2)*((numPoints / (8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(20), (8u*transposePitch));
   __vcop_pblock_init16(pblock, __offset+_PREG(21), (sizeof(*outputData)*2) -(8u*transposePitch)*((numPoints / (8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)pScatterIndex);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)winCoefficients);
   __offset += 24;

   return 24u;
}

void vcop_windowing_with_transpose_kernel_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VDcOffsetImg", 16);
   #pragma VCC_VREG("VDcOffsetReal", 17);
   #pragma VCC_VREG("VIndex", 18);
   #pragma VCC_VREG("VInputDataI", 19);
   #pragma VCC_VREG("VInputDataR", 20);
   #pragma VCC_VREG("VWinCoeff", 21);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   #pragma EVE_REG("coeffAddr", "A1");
   #pragma EVE_REG("inAddr", "A2");
   #pragma EVE_REG("outAddr", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("j", "I3");
   #pragma EVE_REG("i", "I4");
   

   __vcop_vloop(__vcop_compute(), 12u, 12u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(7), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(18), _PREG(19), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(20), _PREG(21), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(22), _AGEN(0), _VREG(18), __vcop_once());
   __vcop_vload(__vcop_sizeH(), __vcop_1pt(), _PREG(24), _AGEN(1), _VREG(21), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(8), _AGEN(2), _VPAIR(20,19), __vcop_alws());
   __vcop_vmpy(_VREG(20), _VREG(21), _VREG(20), _PREG(0));
   __vcop_vmpy(_VREG(19), _VREG(21), _VREG(19), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_pdda(_VREG(18)), __vcop_alws(), _VREG(20), _PREG(10), _AGEN(3), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_pdda(_VREG(18)), __vcop_alws(), _VREG(19), _PREG(16), _AGEN(3), _PREG(6));
   __vcop_vloop_end(1u);

}

void vcop_windowing_with_transpose_kernel(
   __vptr_int16 inputData,
   __vptr_int16 winCoefficients,
   __vptr_int16 outputData,
   __vptr_uint16 pScatterIndex,
   unsigned short inputPitch,
   unsigned short transposePitch,
   unsigned short numPoints,
   unsigned short numOfLines,
   unsigned short scaleFactor,
   unsigned short saturationLimit)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_windowing_with_transpose_kernel_init(inputData, winCoefficients, outputData, pScatterIndex, inputPitch, transposePitch, numPoints, numOfLines, scaleFactor, saturationLimit, __pblock_vcop_windowing_with_transpose_kernel);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_windowing_with_transpose_kernel_vloops(__pblock_vcop_windowing_with_transpose_kernel);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_windowing_with_transpose_kernel_custom(
   __vptr_int16 inputData,
   __vptr_int16 winCoefficients,
   __vptr_int16 outputData,
   __vptr_uint16 pScatterIndex,
   unsigned short inputPitch,
   unsigned short transposePitch,
   unsigned short numPoints,
   unsigned short numOfLines,
   unsigned short scaleFactor,
   unsigned short saturationLimit,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_windowing_with_transpose_kernel_init(inputData, winCoefficients, outputData, pScatterIndex, inputPitch, transposePitch, numPoints, numOfLines, scaleFactor, saturationLimit, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_windowing_with_transpose_kernel_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_sign_extension_kernel, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_sign_extension_kernel, __ALIGNOF__(int));
unsigned short __pblock_vcop_sign_extension_kernel[14];

unsigned int vcop_sign_extension_kernel_param_count(void)
{
   return 14u;
}

unsigned int vcop_sign_extension_kernel_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_sign_extension_kernel_init(
   __vptr_uint16 inputData,
   __vptr_int16 outputData,
   unsigned short numPoints,
   unsigned short numOfLines,
   unsigned short inputPitch,
   unsigned short outputPitch,
   unsigned short inBits,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (numOfLines)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (numPoints / (8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_TRUNC,(40 - inBits)));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)outputData);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), (inputPitch) -(8u*sizeof(*inputData)*2)*((numPoints / (8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(11), (outputPitch) -(8u*sizeof(*outputData)*2)*((numPoints / (8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (40 - inBits));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)inputData);
   __offset += 14;

   return 14u;
}

void vcop_sign_extension_kernel_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VInImg", 16);
   #pragma VCC_VREG("VInReal", 17);
   #pragma VCC_VREG("VShift", 18);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("inAddr", "A0");
   #pragma EVE_REG("outAddr", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 8u, 7u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(12), _VREG(18));
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(10), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(11), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(14), _AGEN(0), _VPAIR(17,16), __vcop_alws());
   __vcop_vshf(_VREG(17), _VREG(18), _VREG(17));
   __vcop_vshf(_VREG(16), _VREG(18), _VREG(16));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_alws(), _VPAIR(17,16), _PREG(8), _AGEN(1), _PREG(6));
   __vcop_vloop_end(1u);

}

void vcop_sign_extension_kernel(
   __vptr_uint16 inputData,
   __vptr_int16 outputData,
   unsigned short numPoints,
   unsigned short numOfLines,
   unsigned short inputPitch,
   unsigned short outputPitch,
   unsigned short inBits)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_sign_extension_kernel_init(inputData, outputData, numPoints, numOfLines, inputPitch, outputPitch, inBits, __pblock_vcop_sign_extension_kernel);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_sign_extension_kernel_vloops(__pblock_vcop_sign_extension_kernel);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_sign_extension_kernel_custom(
   __vptr_uint16 inputData,
   __vptr_int16 outputData,
   unsigned short numPoints,
   unsigned short numOfLines,
   unsigned short inputPitch,
   unsigned short outputPitch,
   unsigned short inBits,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_sign_extension_kernel_init(inputData, outputData, numPoints, numOfLines, inputPitch, outputPitch, inBits, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_sign_extension_kernel_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

