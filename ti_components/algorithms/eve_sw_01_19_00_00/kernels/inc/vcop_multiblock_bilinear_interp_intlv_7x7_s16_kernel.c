#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_multiblock_bilinear_interp_intlv_7x7_s16, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_multiblock_bilinear_interp_intlv_7x7_s16, __ALIGNOF__(int));
unsigned short __pblock_vcop_multiblock_bilinear_interp_intlv_7x7_s16[32];

unsigned int vcop_multiblock_bilinear_interp_intlv_7x7_s16_param_count(void)
{
   return 32u;
}

unsigned int vcop_multiblock_bilinear_interp_intlv_7x7_s16_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_multiblock_bilinear_interp_intlv_7x7_s16_init(
   __vptr_int16 pIntlvGradXY_A,
   __vptr_uint16 pInpWts_X,
   __vptr_int16 pGradXBilinearInterpImg_B,
   __vptr_int16 pGradYBilinearInterpImg_C,
   unsigned short input1Stride,
   unsigned short input2Stride,
   unsigned short outputStride,
   unsigned short blkWidth,
   unsigned short blkHeight,
   unsigned short blkOffset,
   unsigned short shiftValue,
   unsigned short numKeyPoints,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (numKeyPoints)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (blkHeight)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((blkWidth+(8u)-1)/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_TRUNC,shiftValue));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 16);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pInpWts_X+2*input2Stride*sizeof(*pInpWts_X));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pInpWts_X+3*input2Stride*sizeof(*pInpWts_X));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pIntlvGradXY_A);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pIntlvGradXY_A+2*sizeof(*pIntlvGradXY_A));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pIntlvGradXY_A+input1Stride*sizeof(*pIntlvGradXY_A));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pIntlvGradXY_A+(input1Stride+2)*sizeof(*pIntlvGradXY_A));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pGradXBilinearInterpImg_B);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)pGradYBilinearInterpImg_C);
   __vcop_pblock_init16(pblock, __offset+_PREG(24), (outputStride*sizeof(*pIntlvGradXY_A)) -((8u*sizeof(*pIntlvGradXY_A)))*(((blkWidth+(8u)-1)/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(25), (outputStride*blkHeight*sizeof(*pIntlvGradXY_A)) -(outputStride*sizeof(*pIntlvGradXY_A))*((blkHeight)-1u) -((8u*sizeof(*pIntlvGradXY_A)))*(((blkWidth+(8u)-1)/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(26), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(27), (input1Stride*sizeof(*pIntlvGradXY_A)) -(2*(8u*sizeof(*pIntlvGradXY_A)))*(((blkWidth+(8u)-1)/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(28), (blkOffset*sizeof(*pIntlvGradXY_A)) -(input1Stride*sizeof(*pIntlvGradXY_A))*((blkHeight)-1u) -(2*(8u*sizeof(*pIntlvGradXY_A)))*(((blkWidth+(8u)-1)/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(29), 2);
   __vcop_pblock_init32(pblock, __offset+_PREG(30), (uchar *)pInpWts_X);
   __vcop_pblock_init32(pblock, __offset+_PREG(32), (uchar *)pInpWts_X+1*input2Stride*sizeof(*pInpWts_X));
   __offset += 32;

   return 32u;
}

void vcop_multiblock_bilinear_interp_intlv_7x7_s16_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VgradX", 16);
   #pragma VCC_VREG("VgradY", 17);
   #pragma VCC_VREG("Vpix00_Even", 18);
   #pragma VCC_VREG("Vpix00_Odd", 19);
   #pragma VCC_VREG("Vpix01_Even", 20);
   #pragma VCC_VREG("Vpix01_Odd", 21);
   #pragma VCC_VREG("Vpix10_Even", 22);
   #pragma VCC_VREG("Vpix10_Odd", 23);
   #pragma VCC_VREG("Vpix11_Even", 24);
   #pragma VCC_VREG("Vpix11_Odd", 25);
   #pragma VCC_VREG("Vwt0", 26);
   #pragma VCC_VREG("Vwt1", 27);
   #pragma VCC_VREG("Vwt2", 28);
   #pragma VCC_VREG("Vwt3", 29);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("AddrOut", "A0");
   #pragma EVE_REG("AddrPix", "A1");
   #pragma EVE_REG("AddrWt", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I2");
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 22u, 16u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(24), _PREG(25), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(26), _PREG(27), _PREG(28), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(0), _PREG(0), _PREG(29), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(30), _AGEN(2), _VREG(26), __vcop_i34_zero());
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(32), _AGEN(2), _VREG(27), __vcop_i34_zero());
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(8), _AGEN(2), _VREG(28), __vcop_i34_zero());
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(10), _AGEN(2), _VREG(29), __vcop_i34_zero());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(12), _AGEN(1), _VPAIR(19,18), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(14), _AGEN(1), _VPAIR(21,20), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(16), _AGEN(1), _VPAIR(23,22), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(18), _AGEN(1), _VPAIR(25,24), __vcop_alws());
   __vcop_vmpy(_VREG(29), _VREG(19), _VREG(16), _PREG(0));
   __vcop_vmpy(_VREG(29), _VREG(18), _VREG(17), _PREG(0));
   __vcop_vmadd(_VREG(28), _VREG(21), _VREG(16), _PREG(0));
   __vcop_vmadd(_VREG(28), _VREG(20), _VREG(17), _PREG(0));
   __vcop_vmadd(_VREG(27), _VREG(23), _VREG(16), _PREG(0));
   __vcop_vmadd(_VREG(27), _VREG(22), _VREG(17), _PREG(0));
   __vcop_vmadd(_VREG(26), _VREG(25), _VREG(16), _PREG(0));
   __vcop_vmadd(_VREG(26), _VREG(24), _VREG(17), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_npt(), __vcop_alws(), _VREG(16), _PREG(20), _AGEN(0), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_npt(), __vcop_alws(), _VREG(17), _PREG(22), _AGEN(0), _PREG(6));
   __vcop_vloop_end(1u);

}

void vcop_multiblock_bilinear_interp_intlv_7x7_s16(
   __vptr_int16 pIntlvGradXY_A,
   __vptr_uint16 pInpWts_X,
   __vptr_int16 pGradXBilinearInterpImg_B,
   __vptr_int16 pGradYBilinearInterpImg_C,
   unsigned short input1Stride,
   unsigned short input2Stride,
   unsigned short outputStride,
   unsigned short blkWidth,
   unsigned short blkHeight,
   unsigned short blkOffset,
   unsigned short shiftValue,
   unsigned short numKeyPoints)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_multiblock_bilinear_interp_intlv_7x7_s16_init(pIntlvGradXY_A, pInpWts_X, pGradXBilinearInterpImg_B, pGradYBilinearInterpImg_C, input1Stride, input2Stride, outputStride, blkWidth, blkHeight, blkOffset, shiftValue, numKeyPoints, __pblock_vcop_multiblock_bilinear_interp_intlv_7x7_s16);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_multiblock_bilinear_interp_intlv_7x7_s16_vloops(__pblock_vcop_multiblock_bilinear_interp_intlv_7x7_s16);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_multiblock_bilinear_interp_intlv_7x7_s16_custom(
   __vptr_int16 pIntlvGradXY_A,
   __vptr_uint16 pInpWts_X,
   __vptr_int16 pGradXBilinearInterpImg_B,
   __vptr_int16 pGradYBilinearInterpImg_C,
   unsigned short input1Stride,
   unsigned short input2Stride,
   unsigned short outputStride,
   unsigned short blkWidth,
   unsigned short blkHeight,
   unsigned short blkOffset,
   unsigned short shiftValue,
   unsigned short numKeyPoints,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_multiblock_bilinear_interp_intlv_7x7_s16_init(pIntlvGradXY_A, pInpWts_X, pGradXBilinearInterpImg_B, pGradYBilinearInterpImg_C, input1Stride, input2Stride, outputStride, blkWidth, blkHeight, blkOffset, shiftValue, numKeyPoints, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_multiblock_bilinear_interp_intlv_7x7_s16_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

