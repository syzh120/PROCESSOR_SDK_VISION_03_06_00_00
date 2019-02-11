#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_sobelXY_3x3_separable_uchar, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_sobelXY_3x3_separable_uchar, __ALIGNOF__(int));
unsigned short __pblock_vcop_sobelXY_3x3_separable_uchar[40];

unsigned int vcop_sobelXY_3x3_separable_uchar_param_count(void)
{
   return 40u;
}

unsigned int vcop_sobelXY_3x3_separable_uchar_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_sobelXY_3x3_separable_uchar_init(
   __vptr_uint8 inData,
   __vptr_int16 interimDataX,
   __vptr_int16 interimDataY,
   __vptr_int8 outDataX,
   __vptr_int8 outDataY,
   unsigned short computeWidth,
   unsigned short computeHeight,
   unsigned short inputPitch,
   unsigned short outputPitch,
   unsigned short roundShift,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (computeHeight + 2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((computeWidth) + 2*(8u)-1) & ~(2*(8u)-1))/(2 * (8u)))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)interimDataX);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)interimDataY);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), (inputPitch*sizeof(*inData)) -((2*8u)*sizeof(*inData))*(((((computeWidth) + 2*(8u)-1) & ~(2*(8u)-1))/(2 * (8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(13), (computeWidth*sizeof(*interimDataX)) -((2*8u)*sizeof(*interimDataX))*(((((computeWidth) + 2*(8u)-1) & ~(2*(8u)-1))/(2 * (8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)inData);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)inData+2*sizeof(*inData));
   __offset += 16;

   /* Loop 2 PREGS */
   const int preg_ref1 = _PREG(7);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (computeHeight)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((computeWidth) + 2*(8u)-1) & ~(2*(8u)-1))/(2 * (8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_ASYMM,preg_ref1,RM_ROUND,roundShift));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 127);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)interimDataX+2*computeWidth*sizeof(*interimDataX));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)interimDataY);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)interimDataY+2*computeWidth*sizeof(*interimDataY));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)outDataX);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)outDataY);
   __vcop_pblock_init16(pblock, __offset+_PREG(18), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(19), (computeWidth*sizeof(*interimDataX)) -((2*8u)*sizeof(*interimDataX))*(((((computeWidth) + 2*(8u)-1) & ~(2*(8u)-1))/(2 * (8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(20), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(21), (outputPitch*sizeof(*outDataX)) -((2*8u)*sizeof(*outDataX))*(((((computeWidth) + 2*(8u)-1) & ~(2*(8u)-1))/(2 * (8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)interimDataX);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)interimDataX+computeWidth*sizeof(*interimDataX));
   __offset += 24;

   return 40u;
}

void vcop_sobelXY_3x3_separable_uchar_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vin", 16);
   #pragma VCC_VREG("Vin0", 17);
   #pragma VCC_VREG("Vin0_plus2", 18);
   #pragma VCC_VREG("Vin1", 19);
   #pragma VCC_VREG("Vin1_plus2", 20);
   #pragma VCC_VREG("Vin2", 21);
   #pragma VCC_VREG("Vin3", 22);
   #pragma VCC_VREG("Vin4", 23);
   #pragma VCC_VREG("Vin5", 24);
   #pragma VCC_VREG("VinY0", 25);
   #pragma VCC_VREG("VinY1", 26);
   #pragma VCC_VREG("VinterimX1", 27);
   #pragma VCC_VREG("VinterimX2", 28);
   #pragma VCC_VREG("VinterimY1", 29);
   #pragma VCC_VREG("VinterimY2", 30);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("inAddr", "A0");
   #pragma EVE_REG("outAddr", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 13u, 8u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(10), _PREG(11), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(12), _PREG(13), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(14), _AGEN(0), _VPAIR(17,19), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(16), _AGEN(0), _VPAIR(21,22), __vcop_alws());
   __vcop_vsub(_VREG(17), _VREG(21), _VREG(27));
   __vcop_vsub(_VREG(19), _VREG(22), _VREG(28));
   __vcop_vadd(_VREG(17), _VREG(19), _VREG(29));
   __vcop_vadd(_VREG(19), _VREG(21), _VREG(30));
   __vcop_vadd3(_VREG(19), _VREG(21), _VREG(29));
   __vcop_vadd3(_VREG(21), _VREG(22), _VREG(30));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_alws(), _VPAIR(27,28), _PREG(6), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_alws(), _VPAIR(29,30), _PREG(8), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   #pragma EVE_REG("Addr1", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 16u, 12u, 2u);
   __vcop_vagen(_AGEN(0), _PREG(18), _PREG(19), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(20), _PREG(21), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(22), _AGEN(0), _VPAIR(17,19), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(24), _AGEN(0), _VPAIR(21,22), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(8), _AGEN(0), _VPAIR(23,24), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(10), _AGEN(0), _VPAIR(25,26), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(12), _AGEN(0), _VPAIR(18,20), __vcop_alws());
   __vcop_vadd(_VREG(17), _VREG(21), _VREG(27));
   __vcop_vadd(_VREG(19), _VREG(22), _VREG(28));
   __vcop_vadd3(_VREG(21), _VREG(23), _VREG(27));
   __vcop_vadd3(_VREG(22), _VREG(24), _VREG(28));
   __vcop_vsub(_VREG(25), _VREG(18), _VREG(29));
   __vcop_vsub(_VREG(26), _VREG(20), _VREG(30));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeB(), __vcop_intrlv(), __vcop_alws(), _VPAIR(27,28), _PREG(14), _AGEN(1), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeB(), __vcop_intrlv(), __vcop_alws(), _VPAIR(29,30), _PREG(16), _AGEN(1), _PREG(6));
   __vcop_vloop_end(2u);

}

void vcop_sobelXY_3x3_separable_uchar(
   __vptr_uint8 inData,
   __vptr_int16 interimDataX,
   __vptr_int16 interimDataY,
   __vptr_int8 outDataX,
   __vptr_int8 outDataY,
   unsigned short computeWidth,
   unsigned short computeHeight,
   unsigned short inputPitch,
   unsigned short outputPitch,
   unsigned short roundShift)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_sobelXY_3x3_separable_uchar_init(inData, interimDataX, interimDataY, outDataX, outDataY, computeWidth, computeHeight, inputPitch, outputPitch, roundShift, __pblock_vcop_sobelXY_3x3_separable_uchar);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_sobelXY_3x3_separable_uchar_vloops(__pblock_vcop_sobelXY_3x3_separable_uchar);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_sobelXY_3x3_separable_uchar_custom(
   __vptr_uint8 inData,
   __vptr_int16 interimDataX,
   __vptr_int16 interimDataY,
   __vptr_int8 outDataX,
   __vptr_int8 outDataY,
   unsigned short computeWidth,
   unsigned short computeHeight,
   unsigned short inputPitch,
   unsigned short outputPitch,
   unsigned short roundShift,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_sobelXY_3x3_separable_uchar_init(inData, interimDataX, interimDataY, outDataX, outDataY, computeWidth, computeHeight, inputPitch, outputPitch, roundShift, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_sobelXY_3x3_separable_uchar_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_sobelX_3x3_separable_uchar, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_sobelX_3x3_separable_uchar, __ALIGNOF__(int));
unsigned short __pblock_vcop_sobelX_3x3_separable_uchar[32];

unsigned int vcop_sobelX_3x3_separable_uchar_param_count(void)
{
   return 32u;
}

unsigned int vcop_sobelX_3x3_separable_uchar_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_sobelX_3x3_separable_uchar_init(
   __vptr_uint8 inData,
   __vptr_int16 interimData,
   __vptr_int8 outData,
   unsigned short computeWidth,
   unsigned short computeHeight,
   unsigned short inputPitch,
   unsigned short outputPitch,
   unsigned short roundShift,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (computeHeight + 2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((computeWidth) + 2*(8u)-1) & ~(2*(8u)-1))/(2 * (8u)))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)interimData);
   __vcop_pblock_init16(pblock, __offset+_PREG(8), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(9), (inputPitch*sizeof(*inData)) -((2*8u)*sizeof(*inData))*(((((computeWidth) + 2*(8u)-1) & ~(2*(8u)-1))/(2 * (8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), (computeWidth*sizeof(*interimData)) -((2*8u)*sizeof(*interimData))*(((((computeWidth) + 2*(8u)-1) & ~(2*(8u)-1))/(2 * (8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)inData);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)inData+2*sizeof(*inData));
   __offset += 14;

   /* Loop 2 PREGS */
   const int preg_ref2 = _PREG(7);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (computeHeight)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((computeWidth) + 2*(8u)-1) & ~(2*(8u)-1))/(2 * (8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_ASYMM,preg_ref2,RM_ROUND,roundShift));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 127);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)interimData+2*computeWidth*sizeof(*interimData));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)outData);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(13), (computeWidth*sizeof(*interimData)) -((2*8u)*sizeof(*interimData))*(((((computeWidth) + 2*(8u)-1) & ~(2*(8u)-1))/(2 * (8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(14), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(15), (outputPitch*sizeof(*outData)) -((2*8u)*sizeof(*outData))*(((((computeWidth) + 2*(8u)-1) & ~(2*(8u)-1))/(2 * (8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)interimData);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)interimData+computeWidth*sizeof(*interimData));
   __offset += 18;

   return 32u;
}

void vcop_sobelX_3x3_separable_uchar_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vin", 16);
   #pragma VCC_VREG("Vin0", 17);
   #pragma VCC_VREG("Vin0_plus2", 18);
   #pragma VCC_VREG("Vin1", 19);
   #pragma VCC_VREG("Vin1_plus2", 20);
   #pragma VCC_VREG("Vin2", 21);
   #pragma VCC_VREG("Vin3", 22);
   #pragma VCC_VREG("Vin4", 23);
   #pragma VCC_VREG("Vin5", 24);
   #pragma VCC_VREG("Vout0", 25);
   #pragma VCC_VREG("Vout1", 26);
   #pragma VCC_VREG("Vsum0", 27);
   #pragma VCC_VREG("Vsum1", 28);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("inAddr", "A0");
   #pragma EVE_REG("outAddr", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 8u, 7u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(8), _PREG(9), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(10), _PREG(11), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(12), _AGEN(0), _VPAIR(17,19), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(14), _AGEN(0), _VPAIR(18,20), __vcop_alws());
   __vcop_vsub(_VREG(17), _VREG(18), _VREG(27));
   __vcop_vsub(_VREG(19), _VREG(20), _VREG(28));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_alws(), _VPAIR(27,28), _PREG(6), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   #pragma EVE_REG("Addr1", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 11u, 9u, 2u);
   __vcop_vagen(_AGEN(0), _PREG(12), _PREG(13), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(14), _PREG(15), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(16), _AGEN(0), _VPAIR(17,19), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(18), _AGEN(0), _VPAIR(21,22), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(8), _AGEN(0), _VPAIR(23,24), __vcop_alws());
   __vcop_vadd(_VREG(17), _VREG(21), _VREG(25));
   __vcop_vadd(_VREG(19), _VREG(22), _VREG(26));
   __vcop_vadd3(_VREG(21), _VREG(23), _VREG(25));
   __vcop_vadd3(_VREG(22), _VREG(24), _VREG(26));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeB(), __vcop_intrlv(), __vcop_alws(), _VPAIR(25,26), _PREG(10), _AGEN(1), _PREG(6));
   __vcop_vloop_end(2u);

}

void vcop_sobelX_3x3_separable_uchar(
   __vptr_uint8 inData,
   __vptr_int16 interimData,
   __vptr_int8 outData,
   unsigned short computeWidth,
   unsigned short computeHeight,
   unsigned short inputPitch,
   unsigned short outputPitch,
   unsigned short roundShift)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_sobelX_3x3_separable_uchar_init(inData, interimData, outData, computeWidth, computeHeight, inputPitch, outputPitch, roundShift, __pblock_vcop_sobelX_3x3_separable_uchar);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_sobelX_3x3_separable_uchar_vloops(__pblock_vcop_sobelX_3x3_separable_uchar);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_sobelX_3x3_separable_uchar_custom(
   __vptr_uint8 inData,
   __vptr_int16 interimData,
   __vptr_int8 outData,
   unsigned short computeWidth,
   unsigned short computeHeight,
   unsigned short inputPitch,
   unsigned short outputPitch,
   unsigned short roundShift,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_sobelX_3x3_separable_uchar_init(inData, interimData, outData, computeWidth, computeHeight, inputPitch, outputPitch, roundShift, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_sobelX_3x3_separable_uchar_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_sobelY_3x3_separable_uchar, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_sobelY_3x3_separable_uchar, __ALIGNOF__(int));
unsigned short __pblock_vcop_sobelY_3x3_separable_uchar[30];

unsigned int vcop_sobelY_3x3_separable_uchar_param_count(void)
{
   return 30u;
}

unsigned int vcop_sobelY_3x3_separable_uchar_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_sobelY_3x3_separable_uchar_init(
   __vptr_uint8 inData,
   __vptr_int16 interimData,
   __vptr_int8 outData,
   unsigned short computeWidth,
   unsigned short computeHeight,
   unsigned short inputPitch,
   unsigned short outputPitch,
   unsigned short roundShift,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (computeHeight + 2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((computeWidth) + 2*(8u)-1) & ~(2*(8u)-1))/(2 * (8u)))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)interimData);
   __vcop_pblock_init16(pblock, __offset+_PREG(8), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(9), (inputPitch*sizeof(*inData)) -((2*8u)*sizeof(*inData))*(((((computeWidth) + 2*(8u)-1) & ~(2*(8u)-1))/(2 * (8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), (computeWidth*sizeof(*interimData)) -((2*8u)*sizeof(*interimData))*(((((computeWidth) + 2*(8u)-1) & ~(2*(8u)-1))/(2 * (8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)inData);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)inData+2*sizeof(*inData));
   __offset += 14;

   /* Loop 2 PREGS */
   const int preg_ref3 = _PREG(7);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (computeHeight)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((computeWidth) + 2*(8u)-1) & ~(2*(8u)-1))/(2 * (8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_ASYMM,preg_ref3,RM_ROUND,roundShift));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 127);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)outData);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), (computeWidth*sizeof(*interimData)) -((2*8u)*sizeof(*interimData))*(((((computeWidth) + 2*(8u)-1) & ~(2*(8u)-1))/(2 * (8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(13), (outputPitch*sizeof(*outData)) -((2*8u)*sizeof(*outData))*(((((computeWidth) + 2*(8u)-1) & ~(2*(8u)-1))/(2 * (8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)interimData);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)interimData+2*computeWidth*sizeof(*interimData));
   __offset += 16;

   return 30u;
}

void vcop_sobelY_3x3_separable_uchar_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vin0", 16);
   #pragma VCC_VREG("Vin0_plus2", 17);
   #pragma VCC_VREG("Vin1", 18);
   #pragma VCC_VREG("Vin1_plus2", 19);
   #pragma VCC_VREG("Vin2", 20);
   #pragma VCC_VREG("Vin3", 21);
   #pragma VCC_VREG("Vin4", 22);
   #pragma VCC_VREG("Vin5", 23);
   #pragma VCC_VREG("Vinterim1", 24);
   #pragma VCC_VREG("Vinterim2", 25);
   #pragma VCC_VREG("Vout0", 26);
   #pragma VCC_VREG("Vout1", 27);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   #pragma EVE_REG("Addr1", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 10u, 7u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(8), _PREG(9), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(10), _PREG(11), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(12), _AGEN(0), _VPAIR(16,18), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(14), _AGEN(0), _VPAIR(20,21), __vcop_alws());
   __vcop_vadd(_VREG(16), _VREG(18), _VREG(24));
   __vcop_vadd(_VREG(18), _VREG(20), _VREG(25));
   __vcop_vadd3(_VREG(18), _VREG(20), _VREG(24));
   __vcop_vadd3(_VREG(20), _VREG(21), _VREG(25));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_alws(), _VPAIR(24,25), _PREG(6), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("inAddr", "A0");
   #pragma EVE_REG("outAddr", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 8u, 8u, 2u);
   __vcop_vagen(_AGEN(0), _PREG(10), _PREG(11), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(12), _PREG(13), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(14), _AGEN(0), _VPAIR(16,18), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(16), _AGEN(0), _VPAIR(17,19), __vcop_alws());
   __vcop_vsub(_VREG(16), _VREG(17), _VREG(26));
   __vcop_vsub(_VREG(18), _VREG(19), _VREG(27));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeB(), __vcop_intrlv(), __vcop_alws(), _VPAIR(26,27), _PREG(8), _AGEN(1), _PREG(6));
   __vcop_vloop_end(2u);

}

void vcop_sobelY_3x3_separable_uchar(
   __vptr_uint8 inData,
   __vptr_int16 interimData,
   __vptr_int8 outData,
   unsigned short computeWidth,
   unsigned short computeHeight,
   unsigned short inputPitch,
   unsigned short outputPitch,
   unsigned short roundShift)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_sobelY_3x3_separable_uchar_init(inData, interimData, outData, computeWidth, computeHeight, inputPitch, outputPitch, roundShift, __pblock_vcop_sobelY_3x3_separable_uchar);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_sobelY_3x3_separable_uchar_vloops(__pblock_vcop_sobelY_3x3_separable_uchar);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_sobelY_3x3_separable_uchar_custom(
   __vptr_uint8 inData,
   __vptr_int16 interimData,
   __vptr_int8 outData,
   unsigned short computeWidth,
   unsigned short computeHeight,
   unsigned short inputPitch,
   unsigned short outputPitch,
   unsigned short roundShift,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_sobelY_3x3_separable_uchar_init(inData, interimData, outData, computeWidth, computeHeight, inputPitch, outputPitch, roundShift, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_sobelY_3x3_separable_uchar_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_sobelXy_3x3_L1_thresholding, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_sobelXy_3x3_L1_thresholding, __ALIGNOF__(int));
unsigned short __pblock_vcop_sobelXy_3x3_L1_thresholding[22];

unsigned int vcop_sobelXy_3x3_L1_thresholding_param_count(void)
{
   return 22u;
}

unsigned int vcop_sobelXy_3x3_L1_thresholding_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_sobelXy_3x3_L1_thresholding_init(
   __vptr_int8 gradX,
   __vptr_int8 gradY,
   __vptr_uint8 outData,
   unsigned short computeWidth,
   unsigned short computeHeight,
   unsigned short inputPitch,
   unsigned short outputPitch,
   unsigned short threshold,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   const int preg_ref4 = _PREG(14);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (computeHeight)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((computeWidth) + 2*(8u)-1) & ~(2*(8u)-1))/(2 * (8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_4PARAM,preg_ref4,RM_NONE,0));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 16);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)gradX);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)gradY);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)outData);
   __vcop_pblock_4param_init(pblock, __offset+_PREG(14), 1,255,0,0);
   __vcop_pblock_init16(pblock, __offset+_PREG(18), (inputPitch*sizeof(*gradX)) -((2*8u)*sizeof(*gradX))*(((((computeWidth) + 2*(8u)-1) & ~(2*(8u)-1))/(2 * (8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(19), (outputPitch*sizeof(*outData)) -((2*8u)*sizeof(*outData))*(((((computeWidth) + 2*(8u)-1) & ~(2*(8u)-1))/(2 * (8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), threshold);
   __offset += 22;

   return 22u;
}

void vcop_sobelXy_3x3_L1_thresholding_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VK0", 16);
   #pragma VCC_VREG("VgradX1", 17);
   #pragma VCC_VREG("VgradX2", 18);
   #pragma VCC_VREG("VgradY1", 19);
   #pragma VCC_VREG("VgradY2", 20);
   #pragma VCC_VREG("Vmag1", 21);
   #pragma VCC_VREG("Vmag2", 22);
   #pragma VCC_VREG("Vout1", 23);
   #pragma VCC_VREG("Vout2", 24);
   #pragma VCC_VREG("Vthreshold", 25);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_in", "A0");
   #pragma EVE_REG("Addr_out", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 14u, 11u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(20), _VREG(16));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(22), _VREG(25));
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(18), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(19), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeB(), __vcop_dintrlv(), _PREG(8), _AGEN(0), _VPAIR(17,18), __vcop_alws());
   __vcop_vload(__vcop_sizeB(), __vcop_dintrlv(), _PREG(10), _AGEN(0), _VPAIR(19,20), __vcop_alws());
   __vcop_vabs(_VREG(17), _VREG(21));
   __vcop_vabs(_VREG(18), _VREG(22));
   __vcop_vsad(_VREG(19), _VREG(16), _VREG(21));
   __vcop_vsad(_VREG(20), _VREG(16), _VREG(22));
   __vcop_vcmpgt(_VREG(21), _VREG(25), _VREG(23));
   __vcop_vcmpgt(_VREG(22), _VREG(25), _VREG(24));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(23,24), _PREG(12), _AGEN(1), _PREG(6));
   __vcop_vloop_end(1u);

}

void vcop_sobelXy_3x3_L1_thresholding(
   __vptr_int8 gradX,
   __vptr_int8 gradY,
   __vptr_uint8 outData,
   unsigned short computeWidth,
   unsigned short computeHeight,
   unsigned short inputPitch,
   unsigned short outputPitch,
   unsigned short threshold)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_sobelXy_3x3_L1_thresholding_init(gradX, gradY, outData, computeWidth, computeHeight, inputPitch, outputPitch, threshold, __pblock_vcop_sobelXy_3x3_L1_thresholding);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_sobelXy_3x3_L1_thresholding_vloops(__pblock_vcop_sobelXy_3x3_L1_thresholding);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_sobelXy_3x3_L1_thresholding_custom(
   __vptr_int8 gradX,
   __vptr_int8 gradY,
   __vptr_uint8 outData,
   unsigned short computeWidth,
   unsigned short computeHeight,
   unsigned short inputPitch,
   unsigned short outputPitch,
   unsigned short threshold,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_sobelXy_3x3_L1_thresholding_init(gradX, gradY, outData, computeWidth, computeHeight, inputPitch, outputPitch, threshold, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_sobelXy_3x3_L1_thresholding_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_sobelXy_3x3_L1_thresholding_binPack, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_sobelXy_3x3_L1_thresholding_binPack, __ALIGNOF__(int));
unsigned short __pblock_vcop_sobelXy_3x3_L1_thresholding_binPack[24];

unsigned int vcop_sobelXy_3x3_L1_thresholding_binPack_param_count(void)
{
   return 24u;
}

unsigned int vcop_sobelXy_3x3_L1_thresholding_binPack_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_sobelXy_3x3_L1_thresholding_binPack_init(
   __vptr_int8 gradX,
   __vptr_int8 gradY,
   __vptr_uint8 outData,
   unsigned short computeWidth,
   unsigned short computeHeight,
   unsigned short inputPitch,
   unsigned short outputPitch,
   unsigned short threshold,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (computeHeight)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((computeWidth) + 2*(8u)-1) & ~(2*(8u)-1))/(2 * (8u)))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)gradX);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)gradX+8u);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)gradY);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)gradY+8u);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)outData);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)outData+1);
   __vcop_pblock_init16(pblock, __offset+_PREG(18), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(19), (inputPitch*sizeof(*gradX)) -((2*8u)*sizeof(*gradX))*(((((computeWidth) + 2*(8u)-1) & ~(2*(8u)-1))/(2 * (8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(20), 2);
   __vcop_pblock_init16(pblock, __offset+_PREG(21), (outputPitch*sizeof(*outData)) -(2*sizeof(*outData))*(((((computeWidth) + 2*(8u)-1) & ~(2*(8u)-1))/(2 * (8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(22), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), threshold);
   __offset += 24;

   return 24u;
}

void vcop_sobelXy_3x3_L1_thresholding_binPack_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VK0", 16);
   #pragma VCC_VREG("VTest1", 17);
   #pragma VCC_VREG("VTest2", 18);
   #pragma VCC_VREG("VgX1", 19);
   #pragma VCC_VREG("VgX2", 20);
   #pragma VCC_VREG("VgY1", 21);
   #pragma VCC_VREG("VgY2", 22);
   #pragma VCC_VREG("Vo1", 23);
   #pragma VCC_VREG("Vo2", 24);
   #pragma VCC_VREG("Vthreshold", 25);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_in", "A0");
   #pragma EVE_REG("Addr_out", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 17u, 12u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(22), _VREG(16));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(24), _VREG(25));
   __vcop_vagen(_AGEN(0), _PREG(18), _PREG(19), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(20), _PREG(21), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeB(), __vcop_npt(), _PREG(6), _AGEN(0), _VREG(19), __vcop_alws());
   __vcop_vload(__vcop_sizeB(), __vcop_npt(), _PREG(8), _AGEN(0), _VREG(20), __vcop_alws());
   __vcop_vload(__vcop_sizeB(), __vcop_npt(), _PREG(10), _AGEN(0), _VREG(21), __vcop_alws());
   __vcop_vload(__vcop_sizeB(), __vcop_npt(), _PREG(12), _AGEN(0), _VREG(22), __vcop_alws());
   __vcop_vabs(_VREG(19), _VREG(17));
   __vcop_vabs(_VREG(20), _VREG(18));
   __vcop_vsad(_VREG(21), _VREG(16), _VREG(17));
   __vcop_vsad(_VREG(22), _VREG(16), _VREG(18));
   __vcop_vbitpk(_VREG(17), _VREG(25), _VREG(23));
   __vcop_vbitpk(_VREG(18), _VREG(25), _VREG(24));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_1pt(), __vcop_alws(), _VREG(23), _PREG(14), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_1pt(), __vcop_alws(), _VREG(24), _PREG(16), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_sobelXy_3x3_L1_thresholding_binPack(
   __vptr_int8 gradX,
   __vptr_int8 gradY,
   __vptr_uint8 outData,
   unsigned short computeWidth,
   unsigned short computeHeight,
   unsigned short inputPitch,
   unsigned short outputPitch,
   unsigned short threshold)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_sobelXy_3x3_L1_thresholding_binPack_init(gradX, gradY, outData, computeWidth, computeHeight, inputPitch, outputPitch, threshold, __pblock_vcop_sobelXy_3x3_L1_thresholding_binPack);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_sobelXy_3x3_L1_thresholding_binPack_vloops(__pblock_vcop_sobelXy_3x3_L1_thresholding_binPack);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_sobelXy_3x3_L1_thresholding_binPack_custom(
   __vptr_int8 gradX,
   __vptr_int8 gradY,
   __vptr_uint8 outData,
   unsigned short computeWidth,
   unsigned short computeHeight,
   unsigned short inputPitch,
   unsigned short outputPitch,
   unsigned short threshold,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_sobelXy_3x3_L1_thresholding_binPack_init(gradX, gradY, outData, computeWidth, computeHeight, inputPitch, outputPitch, threshold, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_sobelXy_3x3_L1_thresholding_binPack_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

