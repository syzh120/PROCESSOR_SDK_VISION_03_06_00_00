#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_foreach_multiblock_bilinear_interp_7x7_u8, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_foreach_multiblock_bilinear_interp_7x7_u8, __ALIGNOF__(int));
unsigned short __pblock_vcop_foreach_multiblock_bilinear_interp_7x7_u8[416];

unsigned short __ctrl_vcop_foreach_multiblock_bilinear_interp_7x7_u8[1];

unsigned int vcop_foreach_multiblock_bilinear_interp_7x7_u8_param_count(void)
{
   return 416u;
}

unsigned int vcop_foreach_multiblock_bilinear_interp_7x7_u8_ctrl_count(void)
{
   return 1u;
}

unsigned int vcop_foreach_multiblock_bilinear_interp_7x7_u8_init(
   __vptr_uint8_arr pIn_A,
   __vptr_uint16_arr pInpWts_B,
   __vptr_uint8_arr pOutBilinearInterpImg_C,
   unsigned short input1Stride,
   unsigned short input2Stride,
   unsigned short outputStride,
   unsigned short outBlkWidth,
   unsigned short outBlkHeight,
   unsigned short shiftValue,
   unsigned short numKeyPoints,
   unsigned short pblock[])
{
   int I0;
   int __offset = 0;
   /* Loop 1 PREGS */

   __ctrl_vcop_foreach_multiblock_bilinear_interp_7x7_u8[0] = numKeyPoints - 1;
   for (I0 = 0; I0 < numKeyPoints; I0++)
   {
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (outBlkHeight)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((outBlkWidth+(8u)-1)/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_TRUNC,shiftValue));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 8);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pInpWts_B[I0]+2*input2Stride*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pInpWts_B[I0]+3*input2Stride*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pIn_A[I0]);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pIn_A[I0]+1);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pIn_A[I0]+input1Stride*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pIn_A[I0]+(input1Stride+1)*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pOutBilinearInterpImg_C[I0]);
   __vcop_pblock_init16(pblock, __offset+_PREG(22), (outputStride*1) -((8u*1))*(((outBlkWidth+(8u)-1)/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(23), (input1Stride*1) -((8u*1))*(((outBlkWidth+(8u)-1)/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)pInpWts_B[I0]);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)pInpWts_B[I0]+1*input2Stride*2);
   __offset += 26;
   }


   return 416u;
}

void vcop_foreach_multiblock_bilinear_interp_7x7_u8_vloops(
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
   #pragma EVE_REG("I0", "I0");
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I3", "I4");
   

   __vcop_rpt(__ctrl_vcop_foreach_multiblock_bilinear_interp_7x7_u8[0]);
   __vcop_vloop(__vcop_compute(), 17u, 13u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(22), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(23), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(24), _AGEN(2), _VREG(21), __vcop_once());
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(26), _AGEN(2), _VREG(22), __vcop_once());
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(8), _AGEN(2), _VREG(23), __vcop_once());
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(10), _AGEN(2), _VREG(24), __vcop_once());
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

void vcop_foreach_multiblock_bilinear_interp_7x7_u8(
   __vptr_uint8_arr pIn_A,
   __vptr_uint16_arr pInpWts_B,
   __vptr_uint8_arr pOutBilinearInterpImg_C,
   unsigned short input1Stride,
   unsigned short input2Stride,
   unsigned short outputStride,
   unsigned short outBlkWidth,
   unsigned short outBlkHeight,
   unsigned short shiftValue,
   unsigned short numKeyPoints)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_foreach_multiblock_bilinear_interp_7x7_u8_init(pIn_A, pInpWts_B, pOutBilinearInterpImg_C, input1Stride, input2Stride, outputStride, outBlkWidth, outBlkHeight, shiftValue, numKeyPoints, __pblock_vcop_foreach_multiblock_bilinear_interp_7x7_u8);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_foreach_multiblock_bilinear_interp_7x7_u8_vloops(__pblock_vcop_foreach_multiblock_bilinear_interp_7x7_u8);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_foreach_multiblock_bilinear_interp_7x7_u8_custom(
   __vptr_uint8_arr pIn_A,
   __vptr_uint16_arr pInpWts_B,
   __vptr_uint8_arr pOutBilinearInterpImg_C,
   unsigned short input1Stride,
   unsigned short input2Stride,
   unsigned short outputStride,
   unsigned short outBlkWidth,
   unsigned short outBlkHeight,
   unsigned short shiftValue,
   unsigned short numKeyPoints,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_foreach_multiblock_bilinear_interp_7x7_u8_init(pIn_A, pInpWts_B, pOutBilinearInterpImg_C, input1Stride, input2Stride, outputStride, outBlkWidth, outBlkHeight, shiftValue, numKeyPoints, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_foreach_multiblock_bilinear_interp_7x7_u8_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

