#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_multiblock_bilinear_interp_7x7_u8, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_multiblock_bilinear_interp_7x7_u8, __ALIGNOF__(int));
unsigned short __pblock_vcop_multiblock_bilinear_interp_7x7_u8[30];

unsigned int vcop_multiblock_bilinear_interp_7x7_u8_param_count(void)
{
   return 30u;
}

unsigned int vcop_multiblock_bilinear_interp_7x7_u8_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_multiblock_bilinear_interp_7x7_u8_init(
   __vptr_uint8 pIn_A,
   __vptr_uint16 pInpWts_B,
   __vptr_uint8 pOutBilinearInterpImg_C,
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
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 8);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pInpWts_B+2*input2Stride*sizeof(*pInpWts_B));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pInpWts_B+3*input2Stride*sizeof(*pInpWts_B));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pIn_A);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pIn_A+sizeof(*pIn_A));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pIn_A+input1Stride*sizeof(*pIn_A));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pIn_A+(input1Stride+1)*sizeof(*pIn_A));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pOutBilinearInterpImg_C);
   __vcop_pblock_init16(pblock, __offset+_PREG(22), (outputStride*sizeof(*pIn_A)) -((8u*sizeof(*pIn_A)))*(((blkWidth+(8u)-1)/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(23), (outputStride*blkHeight*sizeof(*pIn_A)) -(outputStride*sizeof(*pIn_A))*((blkHeight)-1u) -((8u*sizeof(*pIn_A)))*(((blkWidth+(8u)-1)/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(24), (input1Stride*sizeof(*pIn_A)) -((8u*sizeof(*pIn_A)))*(((blkWidth+(8u)-1)/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(25), (blkOffset*sizeof(*pIn_A)) -(input1Stride*sizeof(*pIn_A))*((blkHeight)-1u) -((8u*sizeof(*pIn_A)))*(((blkWidth+(8u)-1)/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(26), 2);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)pInpWts_B);
   __vcop_pblock_init32(pblock, __offset+_PREG(30), (uchar *)pInpWts_B+1*input2Stride*sizeof(*pInpWts_B));
   __offset += 30;

   return 30u;
}

void vcop_multiblock_bilinear_interp_7x7_u8_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vout", 16);
   #pragma VCC_VREG("Vpix00", 17);
   #pragma VCC_VREG("Vpix01", 18);
   #pragma VCC_VREG("Vpix10", 19);
   #pragma VCC_VREG("Vpix11", 20);
   #pragma VCC_VREG("Vwt0", 21);
   #pragma VCC_VREG("Vwt1", 22);
   #pragma VCC_VREG("Vwt2", 23);
   #pragma VCC_VREG("Vwt3", 24);

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
   

   __vcop_vloop(__vcop_compute(), 17u, 15u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(22), _PREG(23), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(24), _PREG(25), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(0), _PREG(0), _PREG(26), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(28), _AGEN(2), _VREG(21), __vcop_i34_zero());
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(30), _AGEN(2), _VREG(22), __vcop_i34_zero());
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(8), _AGEN(2), _VREG(23), __vcop_i34_zero());
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(10), _AGEN(2), _VREG(24), __vcop_i34_zero());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(12), _AGEN(1), _VREG(17), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(14), _AGEN(1), _VREG(18), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(16), _AGEN(1), _VREG(19), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(18), _AGEN(1), _VREG(20), __vcop_alws());
   __vcop_vmpy(_VREG(24), _VREG(17), _VREG(16), _PREG(0));
   __vcop_vmadd(_VREG(22), _VREG(19), _VREG(16), _PREG(0));
   __vcop_vmadd(_VREG(23), _VREG(18), _VREG(16), _PREG(0));
   __vcop_vmadd(_VREG(21), _VREG(20), _VREG(16), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(16), _PREG(20), _AGEN(0), _PREG(6));
   __vcop_vloop_end(1u);

}

void vcop_multiblock_bilinear_interp_7x7_u8(
   __vptr_uint8 pIn_A,
   __vptr_uint16 pInpWts_B,
   __vptr_uint8 pOutBilinearInterpImg_C,
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
   vcop_multiblock_bilinear_interp_7x7_u8_init(pIn_A, pInpWts_B, pOutBilinearInterpImg_C, input1Stride, input2Stride, outputStride, blkWidth, blkHeight, blkOffset, shiftValue, numKeyPoints, __pblock_vcop_multiblock_bilinear_interp_7x7_u8);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_multiblock_bilinear_interp_7x7_u8_vloops(__pblock_vcop_multiblock_bilinear_interp_7x7_u8);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_multiblock_bilinear_interp_7x7_u8_custom(
   __vptr_uint8 pIn_A,
   __vptr_uint16 pInpWts_B,
   __vptr_uint8 pOutBilinearInterpImg_C,
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
   vcop_multiblock_bilinear_interp_7x7_u8_init(pIn_A, pInpWts_B, pOutBilinearInterpImg_C, input1Stride, input2Stride, outputStride, blkWidth, blkHeight, blkOffset, shiftValue, numKeyPoints, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_multiblock_bilinear_interp_7x7_u8_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

