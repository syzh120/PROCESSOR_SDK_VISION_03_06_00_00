#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_copy_fft_32ix32o_kernel, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_copy_fft_32ix32o_kernel, __ALIGNOF__(int));
unsigned short __pblock_vcop_copy_fft_32ix32o_kernel[10];

unsigned int vcop_copy_fft_32ix32o_kernel_param_count(void)
{
   return 10u;
}

unsigned int vcop_copy_fft_32ix32o_kernel_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_copy_fft_32ix32o_kernel_init(
   __vptr_int32 inputData,
   __vptr_int32 outputData,
   unsigned short numPoints,
   unsigned short numOfLines,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (numOfLines)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((2*numPoints) / (8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(7), (2*numPoints*sizeof(*inputData)) -(8u*sizeof(*inputData))*(((2*numPoints) / (8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)inputData);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)outputData);
   __offset += 10;

   return 10u;
}

void vcop_copy_fft_32ix32o_kernel_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vdata", 16);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 4u, 5u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(6), _PREG(7), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(8), _AGEN(0), _VREG(16), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(16), _PREG(10), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_copy_fft_32ix32o_kernel(
   __vptr_int32 inputData,
   __vptr_int32 outputData,
   unsigned short numPoints,
   unsigned short numOfLines)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_copy_fft_32ix32o_kernel_init(inputData, outputData, numPoints, numOfLines, __pblock_vcop_copy_fft_32ix32o_kernel);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_copy_fft_32ix32o_kernel_vloops(__pblock_vcop_copy_fft_32ix32o_kernel);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_copy_fft_32ix32o_kernel_custom(
   __vptr_int32 inputData,
   __vptr_int32 outputData,
   unsigned short numPoints,
   unsigned short numOfLines,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_copy_fft_32ix32o_kernel_init(inputData, outputData, numPoints, numOfLines, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_copy_fft_32ix32o_kernel_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_fft_transpose_output_32ix32o_kernel, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_fft_transpose_output_32ix32o_kernel, __ALIGNOF__(int));
unsigned short __pblock_vcop_fft_transpose_output_32ix32o_kernel[18];

unsigned int vcop_fft_transpose_output_32ix32o_kernel_param_count(void)
{
   return 18u;
}

unsigned int vcop_fft_transpose_output_32ix32o_kernel_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_fft_transpose_output_32ix32o_kernel_init(
   __vptr_int32 inputData,
   __vptr_int32 outputData,
   __vptr_uint16 pScatterIndex,
   unsigned short transposePitch,
   unsigned short numPoints,
   unsigned short numOfLines,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (numOfLines)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (numPoints / (8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)inputData+8u*sizeof(*outputData));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)outputData);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)outputData+sizeof(*outputData));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), 64);
   __vcop_pblock_init16(pblock, __offset+_PREG(13), (numPoints*sizeof(*inputData)*2) -(8u*sizeof(*inputData)*2)*((numPoints / (8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(14), (8u*transposePitch));
   __vcop_pblock_init16(pblock, __offset+_PREG(15), (sizeof(*inputData)*2) -(8u*transposePitch)*((numPoints / (8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pScatterIndex);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)inputData);
   __offset += 18;

   return 18u;
}

void vcop_fft_transpose_output_32ix32o_kernel_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VInputDataI", 16);
   #pragma VCC_VREG("VInputDataR", 17);
   #pragma VCC_VREG("VScatterOffset", 18);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   #pragma EVE_REG("inAddr", "A1");
   #pragma EVE_REG("outAddr", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 10u, 9u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(12), _PREG(13), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(14), _PREG(15), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(16), _AGEN(0), _VREG(18), __vcop_once());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(18), _AGEN(1), _VREG(17), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(6), _AGEN(1), _VREG(16), __vcop_alws());
   __vcop_vdintrlv(_VREG(17), _VREG(16));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_pdda(_VREG(18)), __vcop_alws(), _VREG(17), _PREG(8), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_pdda(_VREG(18)), __vcop_alws(), _VREG(16), _PREG(10), _AGEN(2), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_fft_transpose_output_32ix32o_kernel(
   __vptr_int32 inputData,
   __vptr_int32 outputData,
   __vptr_uint16 pScatterIndex,
   unsigned short transposePitch,
   unsigned short numPoints,
   unsigned short numOfLines)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_transpose_output_32ix32o_kernel_init(inputData, outputData, pScatterIndex, transposePitch, numPoints, numOfLines, __pblock_vcop_fft_transpose_output_32ix32o_kernel);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_transpose_output_32ix32o_kernel_vloops(__pblock_vcop_fft_transpose_output_32ix32o_kernel);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_fft_transpose_output_32ix32o_kernel_custom(
   __vptr_int32 inputData,
   __vptr_int32 outputData,
   __vptr_uint16 pScatterIndex,
   unsigned short transposePitch,
   unsigned short numPoints,
   unsigned short numOfLines,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_transpose_output_32ix32o_kernel_init(inputData, outputData, pScatterIndex, transposePitch, numPoints, numOfLines, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_transpose_output_32ix32o_kernel_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_fft_doppler_correction_32ix32o_kernel, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_fft_doppler_correction_32ix32o_kernel, __ALIGNOF__(int));
unsigned short __pblock_vcop_fft_doppler_correction_32ix32o_kernel[30];

unsigned int vcop_fft_doppler_correction_32ix32o_kernel_param_count(void)
{
   return 30u;
}

unsigned int vcop_fft_doppler_correction_32ix32o_kernel_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_fft_doppler_correction_32ix32o_kernel_init(
   __vptr_int32 inputData,
   __vptr_int32 outputData,
   __vptr_int16 dopplerCorrectionBuf,
   __vptr_uint16 pScatterIndex,
   unsigned short transposePitch,
   unsigned short numPoints,
   unsigned short numOfLines,
   unsigned short scaleFactor,
   unsigned short saturationLimit,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (numOfLines)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (numPoints / (8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), scaleFactor);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), 16 - scaleFactor);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pScatterIndex);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)inputData);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)inputData+8u*sizeof(*outputData));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)dopplerCorrectionBuf);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)outputData);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)outputData+sizeof(*outputData));
   __vcop_pblock_init16(pblock, __offset+_PREG(22), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(23),  -(8u*sizeof(*dopplerCorrectionBuf)*2)*((numPoints / (8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(24), 64);
   __vcop_pblock_init16(pblock, __offset+_PREG(25), (numPoints*sizeof(*inputData)*2) -(8u*sizeof(*inputData)*2)*((numPoints / (8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(26), (8u*transposePitch));
   __vcop_pblock_init16(pblock, __offset+_PREG(27), (sizeof(*inputData)*2) -(8u*transposePitch)*((numPoints / (8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(28), -16);
   __vcop_pblock_init32(pblock, __offset+_PREG(30), 0xFFFF);
   __offset += 30;

   return 30u;
}

void vcop_fft_doppler_correction_32ix32o_kernel_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VDopplerI", 16);
   #pragma VCC_VREG("VDopplerR", 17);
   #pragma VCC_VREG("VFFFF", 18);
   #pragma VCC_VREG("VInputDataI", 19);
   #pragma VCC_VREG("VInputDataI_hi", 20);
   #pragma VCC_VREG("VInputDataI_lo", 21);
   #pragma VCC_VREG("VInputDataR", 22);
   #pragma VCC_VREG("VInputDataR_hi", 23);
   #pragma VCC_VREG("VInputDataR_lo", 24);
   #pragma VCC_VREG("VKneg16", 25);
   #pragma VCC_VREG("VKscaleFactor_hi", 26);
   #pragma VCC_VREG("VKscaleFactor_lo", 27);
   #pragma VCC_VREG("VOutImg", 28);
   #pragma VCC_VREG("VOutImg_hi", 29);
   #pragma VCC_VREG("VOutReal", 30);
   #pragma VCC_VREG("VOutReal_hi", 31);
   #pragma VCC_VREG("VScatterOffset", 32);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   #pragma EVE_REG("dopplerAddr", "A1");
   #pragma EVE_REG("inAddr", "A2");
   #pragma EVE_REG("outAddr", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 38u, 15u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(28), _VREG(25));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(30), _VREG(18));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(6), _VREG(27));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(8), _VREG(26));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(22), _PREG(23), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(24), _PREG(25), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(26), _PREG(27), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(10), _AGEN(0), _VREG(32), __vcop_once());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(12), _AGEN(2), _VREG(22), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(14), _AGEN(2), _VREG(19), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(16), _AGEN(1), _VPAIR(17,16), __vcop_alws());
   __vcop_vdintrlv(_VREG(22), _VREG(19));
   __vcop_vand(_VREG(22), _VREG(18), _VREG(24));
   __vcop_vshf(_VREG(22), _VREG(25), _VREG(23));
   __vcop_vand(_VREG(19), _VREG(18), _VREG(21));
   __vcop_vshf(_VREG(19), _VREG(25), _VREG(20));
   __vcop_vmpy(_VREG(24), _VREG(17), _VREG(30), _PREG(0));
   __vcop_vmpy(_VREG(24), _VREG(16), _VREG(28), _PREG(0));
   __vcop_vmsub(_VREG(21), _VREG(16), _VREG(30), _PREG(0));
   __vcop_vmadd(_VREG(21), _VREG(17), _VREG(28), _PREG(0));
   __vcop_vrnd(_VREG(30), _VREG(27), _VREG(30));
   __vcop_vrnd(_VREG(28), _VREG(27), _VREG(28));
   __vcop_vmpy(_VREG(23), _VREG(17), _VREG(31), _PREG(0));
   __vcop_vmpy(_VREG(23), _VREG(16), _VREG(29), _PREG(0));
   __vcop_vshf(_VREG(31), _VREG(26), _VREG(31));
   __vcop_vshf(_VREG(29), _VREG(26), _VREG(29));
   __vcop_vadd(_VREG(30), _VREG(31), _VREG(30));
   __vcop_vadd(_VREG(28), _VREG(29), _VREG(28));
   __vcop_vmpy(_VREG(20), _VREG(16), _VREG(31), _PREG(0));
   __vcop_vmpy(_VREG(20), _VREG(17), _VREG(29), _PREG(0));
   __vcop_vshf(_VREG(31), _VREG(26), _VREG(31));
   __vcop_vshf(_VREG(29), _VREG(26), _VREG(29));
   __vcop_vsub(_VREG(30), _VREG(31), _VREG(30));
   __vcop_vadd(_VREG(28), _VREG(29), _VREG(28));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_pdda(_VREG(32)), __vcop_alws(), _VREG(30), _PREG(18), _AGEN(3), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_pdda(_VREG(32)), __vcop_alws(), _VREG(28), _PREG(20), _AGEN(3), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_fft_doppler_correction_32ix32o_kernel(
   __vptr_int32 inputData,
   __vptr_int32 outputData,
   __vptr_int16 dopplerCorrectionBuf,
   __vptr_uint16 pScatterIndex,
   unsigned short transposePitch,
   unsigned short numPoints,
   unsigned short numOfLines,
   unsigned short scaleFactor,
   unsigned short saturationLimit)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_doppler_correction_32ix32o_kernel_init(inputData, outputData, dopplerCorrectionBuf, pScatterIndex, transposePitch, numPoints, numOfLines, scaleFactor, saturationLimit, __pblock_vcop_fft_doppler_correction_32ix32o_kernel);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_doppler_correction_32ix32o_kernel_vloops(__pblock_vcop_fft_doppler_correction_32ix32o_kernel);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_fft_doppler_correction_32ix32o_kernel_custom(
   __vptr_int32 inputData,
   __vptr_int32 outputData,
   __vptr_int16 dopplerCorrectionBuf,
   __vptr_uint16 pScatterIndex,
   unsigned short transposePitch,
   unsigned short numPoints,
   unsigned short numOfLines,
   unsigned short scaleFactor,
   unsigned short saturationLimit,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_doppler_correction_32ix32o_kernel_init(inputData, outputData, dopplerCorrectionBuf, pScatterIndex, transposePitch, numPoints, numOfLines, scaleFactor, saturationLimit, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_doppler_correction_32ix32o_kernel_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_fft_doppler_pitch_removal_32ix32o, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_fft_doppler_pitch_removal_32ix32o, __ALIGNOF__(int));
unsigned short __pblock_vcop_fft_doppler_pitch_removal_32ix32o[12];

unsigned int vcop_fft_doppler_pitch_removal_32ix32o_param_count(void)
{
   return 12u;
}

unsigned int vcop_fft_doppler_pitch_removal_32ix32o_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_fft_doppler_pitch_removal_32ix32o_init(
   __vptr_int32 inputData,
   __vptr_int32 outputData,
   unsigned short inputPitch,
   unsigned short outputPitch,
   unsigned short numPoints,
   unsigned short numOfLines,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (numPoints)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((2*numOfLines) / (8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(7), (inputPitch) -(8u*sizeof(*inputData))*(((2*numOfLines) / (8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(8), (outputPitch) -(8u*sizeof(*outputData))*(((2*numOfLines) / (8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)inputData);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)outputData);
   __offset += 12;

   return 12u;
}

void vcop_fft_doppler_pitch_removal_32ix32o_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VInputData", 16);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("inAddr", "A0");
   #pragma EVE_REG("outAddr", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 5u, 6u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(6), _PREG(7), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(6), _PREG(8), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(10), _AGEN(0), _VREG(16), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(16), _PREG(12), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_fft_doppler_pitch_removal_32ix32o(
   __vptr_int32 inputData,
   __vptr_int32 outputData,
   unsigned short inputPitch,
   unsigned short outputPitch,
   unsigned short numPoints,
   unsigned short numOfLines)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_doppler_pitch_removal_32ix32o_init(inputData, outputData, inputPitch, outputPitch, numPoints, numOfLines, __pblock_vcop_fft_doppler_pitch_removal_32ix32o);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_doppler_pitch_removal_32ix32o_vloops(__pblock_vcop_fft_doppler_pitch_removal_32ix32o);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_fft_doppler_pitch_removal_32ix32o_custom(
   __vptr_int32 inputData,
   __vptr_int32 outputData,
   unsigned short inputPitch,
   unsigned short outputPitch,
   unsigned short numPoints,
   unsigned short numOfLines,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_doppler_pitch_removal_32ix32o_init(inputData, outputData, inputPitch, outputPitch, numPoints, numOfLines, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_doppler_pitch_removal_32ix32o_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

