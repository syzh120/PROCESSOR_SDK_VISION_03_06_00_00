#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_fft_doppler_correction_kernel, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_fft_doppler_correction_kernel, __ALIGNOF__(int));
unsigned short __pblock_vcop_fft_doppler_correction_kernel[24];

unsigned int vcop_fft_doppler_correction_kernel_param_count(void)
{
   return 24u;
}

unsigned int vcop_fft_doppler_correction_kernel_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_fft_doppler_correction_kernel_init(
   __vptr_int16 inputData,
   __vptr_int16 outputData,
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
   const int preg_ref1 = _PREG(12);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (numOfLines)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (numPoints / (8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_4PARAM,preg_ref1,RM_ROUND,scaleFactor));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)dopplerCorrectionBuf);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)outputData);
   __vcop_pblock_4param_init(pblock, __offset+_PREG(12), (saturationLimit - 1), (saturationLimit - 1), -saturationLimit, -saturationLimit);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)outputData+sizeof(*outputData));
   __vcop_pblock_init16(pblock, __offset+_PREG(18),  -(8u*sizeof(*dopplerCorrectionBuf)*2)*((numPoints / (8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(19), (numPoints*sizeof(*inputData)*2) -(8u*sizeof(*inputData)*2)*((numPoints / (8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(20), (8u*transposePitch));
   __vcop_pblock_init16(pblock, __offset+_PREG(21), (sizeof(*inputData)*2) -(8u*transposePitch)*((numPoints / (8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)pScatterIndex);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)inputData);
   __offset += 24;

   return 24u;
}

void vcop_fft_doppler_correction_kernel_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VDopplerI", 16);
   #pragma VCC_VREG("VDopplerR", 17);
   #pragma VCC_VREG("VInputDataI", 18);
   #pragma VCC_VREG("VInputDataR", 19);
   #pragma VCC_VREG("VOutImg", 20);
   #pragma VCC_VREG("VOutReal", 21);
   #pragma VCC_VREG("VScatterOffset", 22);

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
   

   __vcop_vloop(__vcop_compute(), 14u, 12u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(18), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(7), _PREG(19), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(20), _PREG(21), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(22), _AGEN(0), _VREG(22), __vcop_once());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(24), _AGEN(2), _VPAIR(19,18), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(8), _AGEN(1), _VPAIR(17,16), __vcop_alws());
   __vcop_vmpy(_VREG(19), _VREG(17), _VREG(21), _PREG(0));
   __vcop_vmsub(_VREG(18), _VREG(16), _VREG(21), _PREG(0));
   __vcop_vmpy(_VREG(19), _VREG(16), _VREG(20), _PREG(0));
   __vcop_vmadd(_VREG(18), _VREG(17), _VREG(20), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_pdda(_VREG(22)), __vcop_alws(), _VREG(21), _PREG(10), _AGEN(3), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_pdda(_VREG(22)), __vcop_alws(), _VREG(20), _PREG(16), _AGEN(3), _PREG(6));
   __vcop_vloop_end(1u);

}

void vcop_fft_doppler_correction_kernel(
   __vptr_int16 inputData,
   __vptr_int16 outputData,
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
   vcop_fft_doppler_correction_kernel_init(inputData, outputData, dopplerCorrectionBuf, pScatterIndex, transposePitch, numPoints, numOfLines, scaleFactor, saturationLimit, __pblock_vcop_fft_doppler_correction_kernel);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_doppler_correction_kernel_vloops(__pblock_vcop_fft_doppler_correction_kernel);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_fft_doppler_correction_kernel_custom(
   __vptr_int16 inputData,
   __vptr_int16 outputData,
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
   vcop_fft_doppler_correction_kernel_init(inputData, outputData, dopplerCorrectionBuf, pScatterIndex, transposePitch, numPoints, numOfLines, scaleFactor, saturationLimit, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_doppler_correction_kernel_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_fft_doppler_pitch_removal, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_fft_doppler_pitch_removal, __ALIGNOF__(int));
unsigned short __pblock_vcop_fft_doppler_pitch_removal[12];

unsigned int vcop_fft_doppler_pitch_removal_param_count(void)
{
   return 12u;
}

unsigned int vcop_fft_doppler_pitch_removal_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_fft_doppler_pitch_removal_init(
   __vptr_int16 inputData,
   __vptr_int16 outputData,
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
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (numOfLines / (8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(7), (inputPitch) -(8u*sizeof(*inputData)*2)*((numOfLines / (8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(8), (outputPitch) -(8u*sizeof(*outputData)*2)*((numOfLines / (8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)inputData);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)outputData);
   __offset += 12;

   return 12u;
}

void vcop_fft_doppler_pitch_removal_vloops(
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
   

   __vcop_vloop(__vcop_compute(), 5u, 6u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(6), _PREG(7), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(6), _PREG(8), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(10), _AGEN(0), _VPAIR(17,16), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_alws(), _VPAIR(17,16), _PREG(12), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_fft_doppler_pitch_removal(
   __vptr_int16 inputData,
   __vptr_int16 outputData,
   unsigned short inputPitch,
   unsigned short outputPitch,
   unsigned short numPoints,
   unsigned short numOfLines)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_doppler_pitch_removal_init(inputData, outputData, inputPitch, outputPitch, numPoints, numOfLines, __pblock_vcop_fft_doppler_pitch_removal);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_doppler_pitch_removal_vloops(__pblock_vcop_fft_doppler_pitch_removal);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_fft_doppler_pitch_removal_custom(
   __vptr_int16 inputData,
   __vptr_int16 outputData,
   unsigned short inputPitch,
   unsigned short outputPitch,
   unsigned short numPoints,
   unsigned short numOfLines,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_doppler_pitch_removal_init(inputData, outputData, inputPitch, outputPitch, numPoints, numOfLines, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_doppler_pitch_removal_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

