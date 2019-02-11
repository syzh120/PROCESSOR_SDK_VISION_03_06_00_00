#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_fft_256_32inter_stage_1, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_fft_256_32inter_stage_1, __ALIGNOF__(int));
unsigned short __pblock_vcop_fft_256_32inter_stage_1[64];

unsigned int vcop_fft_256_32inter_stage_1_param_count(void)
{
   return 64u;
}

unsigned int vcop_fft_256_32inter_stage_1_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_fft_256_32inter_stage_1_init(
   __vptr_int16 pInput,
   __vptr_int32 pScratchWBUF,
   __vptr_uint16 pScratchWBUF16_lo,
   __vptr_int16 pScratchWBUF16_hi,
   __vptr_int32 pScratchH,
   __vptr_uint16 pScratchH16_lo,
   __vptr_int16 pScratchH16_hi,
   __vptr_int32 pOutput,
   __vptr_int16 pTwiddleFactor,
   unsigned short pitch,
   unsigned short numOfLines,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   const int preg_ref1 = _PREG(14);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (numOfLines)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((1))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((64)/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_ASYMM32,preg_ref1,RM_NONE,0));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pInput+64*sizeof(*pInput)*2*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pInput+64*sizeof(*pInput)*2*3);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pOutput+64*sizeof(*pOutput)*1*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), 2147483647);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pOutput+256*sizeof(*pOutput)+64*sizeof(*pOutput)*1*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pScratchWBUF+64*sizeof(*pScratchWBUF)*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pScratchH+64*sizeof(*pScratchH)*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)pScratchWBUF+64*sizeof(*pScratchWBUF)*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)pScratchH+64*sizeof(*pScratchH)*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)pScratchWBUF+64*sizeof(*pScratchWBUF)*3);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)pScratchH+64*sizeof(*pScratchH)*3);
   __vcop_pblock_init16(pblock, __offset+_PREG(30), 800);
   __vcop_pblock_init16(pblock, __offset+_PREG(31), (pitch) -(sizeof(*pInput)*2*64*4)*(((1))-1u) -(sizeof(*pInput)*2*8u)*(((64)/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(32), 1824);
   __vcop_pblock_init16(pblock, __offset+_PREG(33), (pitch) -(sizeof(*pScratchWBUF)*64*4)*(((1))-1u) -(sizeof(*pScratchWBUF)*8u)*(((64)/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(34), (uchar *)pInput+64*sizeof(*pInput)*2*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(36), (uchar *)pInput+64*sizeof(*pInput)*2*1);
   __offset += 36;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), (numOfLines)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), ((1))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((64)/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (3)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pScratchWBUF16_lo+64*sizeof(*pScratchWBUF)*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pScratchWBUF16_hi+64*sizeof(*pScratchWBUF)*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pScratchH16_lo+64*sizeof(*pScratchH)*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pScratchH16_hi+64*sizeof(*pScratchH)*1);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), __vcop_vop_round(3, 1));
   __vcop_pblock_init16(pblock, __offset+_PREG(15), 256);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pOutput+64*sizeof(*pOutput)*1*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pOutput+256*sizeof(*pOutput)+64*sizeof(*pOutput)*1*1);
   __vcop_pblock_init16(pblock, __offset+_PREG(20), -480);
   __vcop_pblock_init16(pblock, __offset+_PREG(21), 288);
   __vcop_pblock_init16(pblock, __offset+_PREG(22), (pitch) -(sizeof(*pScratchWBUF)*64*4)*(((1))-1u) -(sizeof(*pScratchWBUF)*8u)*(((64)/(8u))-1u) -(64*sizeof(*pScratchWBUF))*((3)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(23), 1312);
   __vcop_pblock_init16(pblock, __offset+_PREG(24), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(25), -736);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), 15);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)pTwiddleFactor+8u*sizeof(*pTwiddleFactor)*2*0);
   __offset += 28;

   return 64u;
}

void vcop_fft_256_32inter_stage_1_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VCos", 16);
   #pragma VCC_VREG("VInX", 17);
   #pragma VCC_VREG("VInX_hi", 18);
   #pragma VCC_VREG("VInX_lo", 19);
   #pragma VCC_VREG("VInY", 20);
   #pragma VCC_VREG("VInY_hi", 21);
   #pragma VCC_VREG("VInY_lo", 22);
   #pragma VCC_VREG("VK15", 23);
   #pragma VCC_VREG("VOutX", 24);
   #pragma VCC_VREG("VOutX0", 25);
   #pragma VCC_VREG("VOutX1", 26);
   #pragma VCC_VREG("VOutX2", 27);
   #pragma VCC_VREG("VOutX3", 28);
   #pragma VCC_VREG("VOutY", 29);
   #pragma VCC_VREG("VOutY0", 30);
   #pragma VCC_VREG("VOutY1", 31);
   #pragma VCC_VREG("VOutY2", 32);
   #pragma VCC_VREG("VOutY3", 33);
   #pragma VCC_VREG("VScatterOffset", 34);
   #pragma VCC_VREG("VSin", 35);
   #pragma VCC_VREG("VX0", 36);
   #pragma VCC_VREG("VX0_minus_X2", 37);
   #pragma VCC_VREG("VX0_plus_X2", 38);
   #pragma VCC_VREG("VX1", 39);
   #pragma VCC_VREG("VX1_minus_X3", 40);
   #pragma VCC_VREG("VX1_plus_X3", 41);
   #pragma VCC_VREG("VX2", 42);
   #pragma VCC_VREG("VX3", 43);
   #pragma VCC_VREG("VY0", 44);
   #pragma VCC_VREG("VY0_minus_Y2", 45);
   #pragma VCC_VREG("VY0_plus_Y2", 46);
   #pragma VCC_VREG("VY1", 47);
   #pragma VCC_VREG("VY1_minus_Y3", 48);
   #pragma VCC_VREG("VY1_plus_Y3", 49);
   #pragma VCC_VREG("VY2", 50);
   #pragma VCC_VREG("VY3", 51);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   #pragma EVE_REG("Addr_in", "A1");
   #pragma EVE_REG("Addr_out", "A2");
   #pragma EVE_REG("Addr_outH", "A3");
   #pragma EVE_REG("Addr_outWBUF", "A4");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("lineIdx", "I2");
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 42u, 18u, 1u);
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(30), _PREG(31), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(7), _PREG(30), _PREG(32), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(7), _PREG(30), _PREG(30), _PREG(0));
   __vcop_vagen(_AGEN(4), _PREG(7), _PREG(30), _PREG(33), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(34), _AGEN(1), _VPAIR(36,44), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(36), _AGEN(1), _VPAIR(39,47), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(8), _AGEN(1), _VPAIR(42,50), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(10), _AGEN(1), _VPAIR(43,51), __vcop_alws());
   __vcop_vmove(_VREG(36), _VREG(38));
   __vcop_vmove(_VREG(42), _VREG(37));
   __vcop_vaddsub(_VREG(38), _VREG(37));
   __vcop_vmove(_VREG(39), _VREG(41));
   __vcop_vmove(_VREG(43), _VREG(40));
   __vcop_vaddsub(_VREG(41), _VREG(40));
   __vcop_vmove(_VREG(44), _VREG(46));
   __vcop_vmove(_VREG(50), _VREG(45));
   __vcop_vaddsub(_VREG(46), _VREG(45));
   __vcop_vmove(_VREG(47), _VREG(49));
   __vcop_vmove(_VREG(51), _VREG(48));
   __vcop_vaddsub(_VREG(49), _VREG(48));
   __vcop_vmove(_VREG(38), _VREG(25));
   __vcop_vmove(_VREG(41), _VREG(27));
   __vcop_vaddsub(_VREG(25), _VREG(27));
   __vcop_vmove(_VREG(37), _VREG(26));
   __vcop_vmove(_VREG(48), _VREG(28));
   __vcop_vaddsub(_VREG(26), _VREG(28));
   __vcop_vmove(_VREG(46), _VREG(30));
   __vcop_vmove(_VREG(49), _VREG(32));
   __vcop_vaddsub(_VREG(30), _VREG(32));
   __vcop_vmove(_VREG(45), _VREG(33));
   __vcop_vmove(_VREG(40), _VREG(31));
   __vcop_vaddsub(_VREG(33), _VREG(31));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(25), _PREG(12), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(30), _PREG(16), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(26), _PREG(18), _AGEN(4), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(31), _PREG(20), _AGEN(3), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(27), _PREG(22), _AGEN(4), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(32), _PREG(24), _AGEN(3), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(28), _PREG(26), _AGEN(4), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(33), _PREG(28), _AGEN(3), _PREG(6));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   #pragma EVE_REG("Addr_inH", "A1");
   #pragma EVE_REG("Addr_inWBUF", "A2");
   #pragma EVE_REG("Addr_out", "A3");
   #pragma EVE_REG("Addr_tw", "A4");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("lineIdx", "I1");
   #pragma EVE_REG("I3", "I2");
   #pragma EVE_REG("I4", "I3");
   #pragma EVE_REG("twIdx", "I4");
   

   __vcop_vloop(__vcop_compute(), 24u, 14u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(26), _VREG(23));
   __vcop_vagen(_AGEN(1), _PREG(15), _PREG(20), _PREG(21), _PREG(21));
   __vcop_vagen(_AGEN(2), _PREG(15), _PREG(20), _PREG(21), _PREG(22));
   __vcop_vagen(_AGEN(3), _PREG(15), _PREG(20), _PREG(21), _PREG(23));
   __vcop_vagen(_AGEN(4), _PREG(24), _PREG(24), _PREG(25), _PREG(25));
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(28), _AGEN(4), _VPAIR(35,16), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(6), _AGEN(2), _VREG(19), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_ds2(), _PREG(8), _AGEN(2), _VREG(18), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(10), _AGEN(1), _VREG(22), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_ds2(), _PREG(12), _AGEN(1), _VREG(21), __vcop_alws());
   __vcop_vmpy(_VREG(19), _VREG(16), _VREG(24), _PREG(0));
   __vcop_vmpy(_VREG(22), _VREG(16), _VREG(29), _PREG(0));
   __vcop_vmadd(_VREG(22), _VREG(35), _VREG(24), _PREG(0));
   __vcop_vmsub(_VREG(19), _VREG(35), _VREG(29), _PREG(0));
   __vcop_vrnd(_VREG(24), _VREG(23), _VREG(24));
   __vcop_vrnd(_VREG(29), _VREG(23), _VREG(29));
   __vcop_vmadd(_VREG(18), _VREG(16), _VREG(24), _PREG(14));
   __vcop_vmadd(_VREG(21), _VREG(16), _VREG(29), _PREG(14));
   __vcop_vmadd(_VREG(21), _VREG(35), _VREG(24), _PREG(14));
   __vcop_vmsub(_VREG(18), _VREG(35), _VREG(29), _PREG(14));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(24), _PREG(16), _AGEN(3), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(29), _PREG(18), _AGEN(3), _PREG(0));
   __vcop_vloop_end(2u);

}

void vcop_fft_256_32inter_stage_1(
   __vptr_int16 pInput,
   __vptr_int32 pScratchWBUF,
   __vptr_uint16 pScratchWBUF16_lo,
   __vptr_int16 pScratchWBUF16_hi,
   __vptr_int32 pScratchH,
   __vptr_uint16 pScratchH16_lo,
   __vptr_int16 pScratchH16_hi,
   __vptr_int32 pOutput,
   __vptr_int16 pTwiddleFactor,
   unsigned short pitch,
   unsigned short numOfLines)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_256_32inter_stage_1_init(pInput, pScratchWBUF, pScratchWBUF16_lo, pScratchWBUF16_hi, pScratchH, pScratchH16_lo, pScratchH16_hi, pOutput, pTwiddleFactor, pitch, numOfLines, __pblock_vcop_fft_256_32inter_stage_1);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_256_32inter_stage_1_vloops(__pblock_vcop_fft_256_32inter_stage_1);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_fft_256_32inter_stage_1_custom(
   __vptr_int16 pInput,
   __vptr_int32 pScratchWBUF,
   __vptr_uint16 pScratchWBUF16_lo,
   __vptr_int16 pScratchWBUF16_hi,
   __vptr_int32 pScratchH,
   __vptr_uint16 pScratchH16_lo,
   __vptr_int16 pScratchH16_hi,
   __vptr_int32 pOutput,
   __vptr_int16 pTwiddleFactor,
   unsigned short pitch,
   unsigned short numOfLines,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_256_32inter_stage_1_init(pInput, pScratchWBUF, pScratchWBUF16_lo, pScratchWBUF16_hi, pScratchH, pScratchH16_lo, pScratchH16_hi, pOutput, pTwiddleFactor, pitch, numOfLines, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_256_32inter_stage_1_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_fft_256_32inter_stage_2, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_fft_256_32inter_stage_2, __ALIGNOF__(int));
unsigned short __pblock_vcop_fft_256_32inter_stage_2[92];

unsigned int vcop_fft_256_32inter_stage_2_param_count(void)
{
   return 92u;
}

unsigned int vcop_fft_256_32inter_stage_2_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_fft_256_32inter_stage_2_init(
   __vptr_int32 pInput,
   __vptr_int32 pScratch1,
   __vptr_uint16 pScratch1_16_lo,
   __vptr_int16 pScratch1_16_hi,
   __vptr_int32 pScratch2,
   __vptr_uint16 pScratch2_16_lo,
   __vptr_int16 pScratch2_16_hi,
   __vptr_int32 pOutput,
   __vptr_int16 pTwiddleFactor,
   __vptr_uint16 pScatterOffset,
   unsigned short pitch,
   unsigned short numOfLines,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   const int preg_ref2 = _PREG(22);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (numOfLines)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((4))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (((16)/ (8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_ASYMM32,preg_ref2,RM_NONE,0));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pInput+16*sizeof(*pInput)*1*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pInput+256*sizeof(*pInput)+16*sizeof(*pInput)*1*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pInput+16*sizeof(*pInput)*1*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pInput+256*sizeof(*pInput)+16*sizeof(*pInput)*1*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pInput+16*sizeof(*pInput)*1*3);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pInput+256*sizeof(*pInput)+16*sizeof(*pInput)*1*3);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pScratch1+16*1*sizeof(*pScratch1)*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), 2147483647);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)pScratch2+16*1*sizeof(*pScratch2)*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)pScratch1+16*1*sizeof(*pScratch1)*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)pScratch2+16*1*sizeof(*pScratch2)*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(30), (uchar *)pScratch1+16*1*sizeof(*pScratch1)*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(32), (uchar *)pScratch2+16*1*sizeof(*pScratch2)*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(34), (uchar *)pScratch1+16*1*sizeof(*pScratch1)*3);
   __vcop_pblock_init32(pblock, __offset+_PREG(36), (uchar *)pScratch2+16*1*sizeof(*pScratch2)*3);
   __vcop_pblock_init16(pblock, __offset+_PREG(38), 224);
   __vcop_pblock_init16(pblock, __offset+_PREG(39), (pitch) -((16*4)*sizeof(*pInput)*1)*(((4))-1u) -(8u*sizeof(*pInput)*1)*((((16)/ (8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(40), (uchar *)pInput+16*sizeof(*pInput)*1*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(42), (uchar *)pInput+256*sizeof(*pInput)+16*sizeof(*pInput)*1*0);
   __offset += 42;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (numOfLines)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((4))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (((16)/ (8u)))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pScratch2+16*1*sizeof(*pScratch2)*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pOutput+sizeof(*pOutput)*1*4*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pOutput+16*((16+1)*sizeof(*pOutput))+sizeof(*pOutput)*1*4*0);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(13), 224);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), 544);
   __vcop_pblock_init16(pblock, __offset+_PREG(15), -540);
   __vcop_pblock_init16(pblock, __offset+_PREG(16), 1620);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pScatterOffset);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pScratch1+16*1*sizeof(*pScratch1)*0);
   __offset += 20;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), (numOfLines)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), ((4))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (((16)/ (8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (3)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pScratch1_16_lo+16*sizeof(*pScratch1)*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pScratch1_16_hi+16*sizeof(*pScratch1)*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pScratch2_16_lo+16*sizeof(*pScratch2)*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pScratch2_16_hi+16*sizeof(*pScratch2)*1);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), __vcop_vop_round(3, 1));
   __vcop_pblock_init16(pblock, __offset+_PREG(15), 64);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pOutput+sizeof(*pOutput)*1*4*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pOutput+16*((16+1)*sizeof(*pOutput))+sizeof(*pOutput)*1*4*1);
   __vcop_pblock_init16(pblock, __offset+_PREG(20), -96);
   __vcop_pblock_init16(pblock, __offset+_PREG(21), 96);
   __vcop_pblock_init16(pblock, __offset+_PREG(22), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(23), 512);
   __vcop_pblock_init16(pblock, __offset+_PREG(24), -572);
   __vcop_pblock_init16(pblock, __offset+_PREG(25), 1588);
   __vcop_pblock_init16(pblock, __offset+_PREG(26), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(27), -160);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), 15);
   __vcop_pblock_init32(pblock, __offset+_PREG(30), (uchar *)pTwiddleFactor+8*sizeof(*pTwiddleFactor)*2*0);
   __offset += 30;

   return 92u;
}

void vcop_fft_256_32inter_stage_2_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VCos", 16);
   #pragma VCC_VREG("VInX", 17);
   #pragma VCC_VREG("VInX_hi", 18);
   #pragma VCC_VREG("VInX_lo", 19);
   #pragma VCC_VREG("VInY", 20);
   #pragma VCC_VREG("VInY_hi", 21);
   #pragma VCC_VREG("VInY_lo", 22);
   #pragma VCC_VREG("VK15", 23);
   #pragma VCC_VREG("VOutX", 24);
   #pragma VCC_VREG("VOutX0", 25);
   #pragma VCC_VREG("VOutX1", 26);
   #pragma VCC_VREG("VOutX2", 27);
   #pragma VCC_VREG("VOutX3", 28);
   #pragma VCC_VREG("VOutY", 29);
   #pragma VCC_VREG("VOutY0", 30);
   #pragma VCC_VREG("VOutY1", 31);
   #pragma VCC_VREG("VOutY2", 32);
   #pragma VCC_VREG("VOutY3", 33);
   #pragma VCC_VREG("VScatterOffset", 34);
   #pragma VCC_VREG("VSin", 35);
   #pragma VCC_VREG("VX0", 36);
   #pragma VCC_VREG("VX0_minus_X2", 37);
   #pragma VCC_VREG("VX0_plus_X2", 38);
   #pragma VCC_VREG("VX1", 39);
   #pragma VCC_VREG("VX1_minus_X3", 40);
   #pragma VCC_VREG("VX1_plus_X3", 41);
   #pragma VCC_VREG("VX2", 42);
   #pragma VCC_VREG("VX3", 43);
   #pragma VCC_VREG("VY0", 44);
   #pragma VCC_VREG("VY0_minus_Y2", 45);
   #pragma VCC_VREG("VY0_plus_Y2", 46);
   #pragma VCC_VREG("VY1", 47);
   #pragma VCC_VREG("VY1_minus_Y3", 48);
   #pragma VCC_VREG("VY1_plus_Y3", 49);
   #pragma VCC_VREG("VY2", 50);
   #pragma VCC_VREG("VY3", 51);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_in", "A0");
   #pragma EVE_REG("Addr_out", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("lineIdx", "I2");
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 43u, 21u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(38), _PREG(39), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(38), _PREG(38), _PREG(0));
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(40), _AGEN(0), _VREG(36), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(42), _AGEN(0), _VREG(44), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(8), _AGEN(0), _VREG(39), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(10), _AGEN(0), _VREG(47), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(12), _AGEN(0), _VREG(42), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(14), _AGEN(0), _VREG(50), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(16), _AGEN(0), _VREG(43), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(18), _AGEN(0), _VREG(51), __vcop_alws());
   __vcop_vmove(_VREG(36), _VREG(38));
   __vcop_vmove(_VREG(42), _VREG(37));
   __vcop_vaddsub(_VREG(38), _VREG(37));
   __vcop_vmove(_VREG(39), _VREG(41));
   __vcop_vmove(_VREG(43), _VREG(40));
   __vcop_vaddsub(_VREG(41), _VREG(40));
   __vcop_vmove(_VREG(44), _VREG(46));
   __vcop_vmove(_VREG(50), _VREG(45));
   __vcop_vaddsub(_VREG(46), _VREG(45));
   __vcop_vmove(_VREG(47), _VREG(49));
   __vcop_vmove(_VREG(51), _VREG(48));
   __vcop_vaddsub(_VREG(49), _VREG(48));
   __vcop_vmove(_VREG(38), _VREG(25));
   __vcop_vmove(_VREG(41), _VREG(27));
   __vcop_vaddsub(_VREG(25), _VREG(27));
   __vcop_vmove(_VREG(37), _VREG(26));
   __vcop_vmove(_VREG(48), _VREG(28));
   __vcop_vaddsub(_VREG(26), _VREG(28));
   __vcop_vmove(_VREG(46), _VREG(30));
   __vcop_vmove(_VREG(49), _VREG(32));
   __vcop_vaddsub(_VREG(30), _VREG(32));
   __vcop_vmove(_VREG(45), _VREG(33));
   __vcop_vmove(_VREG(40), _VREG(31));
   __vcop_vaddsub(_VREG(33), _VREG(31));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(25), _PREG(20), _AGEN(1), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(30), _PREG(24), _AGEN(1), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(26), _PREG(26), _AGEN(1), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(31), _PREG(28), _AGEN(1), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(27), _PREG(30), _AGEN(1), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(32), _PREG(32), _AGEN(1), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(28), _PREG(34), _AGEN(1), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(33), _PREG(36), _AGEN(1), _PREG(6));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   #pragma EVE_REG("Addr_in", "A1");
   #pragma EVE_REG("Addr_out", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("lineIdx", "I2");
   #pragma EVE_REG("I4", "I3");
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 9u, 10u, 2u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(12), _PREG(13), _PREG(13), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(14), _PREG(15), _PREG(16), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(18), _AGEN(0), _VREG(34), __vcop_once());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(20), _AGEN(1), _VREG(17), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(6), _AGEN(1), _VREG(20), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_pdda(_VREG(34)), __vcop_alws(), _VREG(17), _PREG(8), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_pdda(_VREG(34)), __vcop_alws(), _VREG(20), _PREG(10), _AGEN(2), _PREG(0));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   #pragma EVE_REG("Addr_in", "A1");
   #pragma EVE_REG("Addr_out", "A2");
   #pragma EVE_REG("Addr_tw", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("lineIdx", "I1");
   #pragma EVE_REG("I4", "I2");
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("twIdx", "I4");
   

   __vcop_vloop(__vcop_compute(), 23u, 15u, 3u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(28), _VREG(23));
   __vcop_vagen(_AGEN(1), _PREG(15), _PREG(20), _PREG(21), _PREG(21));
   __vcop_vagen(_AGEN(2), _PREG(22), _PREG(23), _PREG(24), _PREG(25));
   __vcop_vagen(_AGEN(3), _PREG(26), _PREG(26), _PREG(27), _PREG(27));
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(30), _AGEN(3), _VPAIR(35,16), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(6), _AGEN(1), _VREG(19), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_ds2(), _PREG(8), _AGEN(1), _VREG(18), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(10), _AGEN(1), _VREG(22), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_ds2(), _PREG(12), _AGEN(1), _VREG(21), __vcop_alws());
   __vcop_vmpy(_VREG(19), _VREG(16), _VREG(24), _PREG(0));
   __vcop_vmpy(_VREG(22), _VREG(16), _VREG(29), _PREG(0));
   __vcop_vmadd(_VREG(22), _VREG(35), _VREG(24), _PREG(0));
   __vcop_vmsub(_VREG(19), _VREG(35), _VREG(29), _PREG(0));
   __vcop_vrnd(_VREG(24), _VREG(23), _VREG(24));
   __vcop_vrnd(_VREG(29), _VREG(23), _VREG(29));
   __vcop_vmadd(_VREG(18), _VREG(16), _VREG(24), _PREG(14));
   __vcop_vmadd(_VREG(21), _VREG(16), _VREG(29), _PREG(14));
   __vcop_vmadd(_VREG(21), _VREG(35), _VREG(24), _PREG(14));
   __vcop_vmsub(_VREG(18), _VREG(35), _VREG(29), _PREG(14));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_pdda(_VREG(34)), __vcop_alws(), _VREG(24), _PREG(16), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_pdda(_VREG(34)), __vcop_alws(), _VREG(29), _PREG(18), _AGEN(2), _PREG(0));
   __vcop_vloop_end(3u);

}

void vcop_fft_256_32inter_stage_2(
   __vptr_int32 pInput,
   __vptr_int32 pScratch1,
   __vptr_uint16 pScratch1_16_lo,
   __vptr_int16 pScratch1_16_hi,
   __vptr_int32 pScratch2,
   __vptr_uint16 pScratch2_16_lo,
   __vptr_int16 pScratch2_16_hi,
   __vptr_int32 pOutput,
   __vptr_int16 pTwiddleFactor,
   __vptr_uint16 pScatterOffset,
   unsigned short pitch,
   unsigned short numOfLines)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_256_32inter_stage_2_init(pInput, pScratch1, pScratch1_16_lo, pScratch1_16_hi, pScratch2, pScratch2_16_lo, pScratch2_16_hi, pOutput, pTwiddleFactor, pScatterOffset, pitch, numOfLines, __pblock_vcop_fft_256_32inter_stage_2);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_256_32inter_stage_2_vloops(__pblock_vcop_fft_256_32inter_stage_2);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_fft_256_32inter_stage_2_custom(
   __vptr_int32 pInput,
   __vptr_int32 pScratch1,
   __vptr_uint16 pScratch1_16_lo,
   __vptr_int16 pScratch1_16_hi,
   __vptr_int32 pScratch2,
   __vptr_uint16 pScratch2_16_lo,
   __vptr_int16 pScratch2_16_hi,
   __vptr_int32 pOutput,
   __vptr_int16 pTwiddleFactor,
   __vptr_uint16 pScatterOffset,
   unsigned short pitch,
   unsigned short numOfLines,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_256_32inter_stage_2_init(pInput, pScratch1, pScratch1_16_lo, pScratch1_16_hi, pScratch2, pScratch2_16_lo, pScratch2_16_hi, pOutput, pTwiddleFactor, pScatterOffset, pitch, numOfLines, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_256_32inter_stage_2_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_fft_256_32inter_stage_3, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_fft_256_32inter_stage_3, __ALIGNOF__(int));
unsigned short __pblock_vcop_fft_256_32inter_stage_3[90];

unsigned int vcop_fft_256_32inter_stage_3_param_count(void)
{
   return 90u;
}

unsigned int vcop_fft_256_32inter_stage_3_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_fft_256_32inter_stage_3_init(
   __vptr_int32 pInput,
   __vptr_int32 pScratch1,
   __vptr_uint16 pScratch1_16_lo,
   __vptr_int16 pScratch1_16_hi,
   __vptr_int32 pScratch2,
   __vptr_uint16 pScratch2_16_lo,
   __vptr_int16 pScratch2_16_hi,
   __vptr_int32 pOutput,
   __vptr_int16 pTwiddleFactor,
   unsigned short numOfLines,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   const int preg_ref3 = _PREG(22);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (numOfLines)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((16)/ (8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((4))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_ASYMM32,preg_ref3,RM_NONE,0));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 68);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pInput+4*((16+1)*sizeof(*pOutput))*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pInput+16*((16+1)*sizeof(*pOutput))+4*((16+1)*sizeof(*pOutput))*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pInput+4*((16+1)*sizeof(*pOutput))*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pInput+16*((16+1)*sizeof(*pOutput))+4*((16+1)*sizeof(*pOutput))*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pInput+4*((16+1)*sizeof(*pOutput))*3);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pInput+16*((16+1)*sizeof(*pOutput))+4*((16+1)*sizeof(*pOutput))*3);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pScratch1+16*sizeof(*pScratch1)*1*4*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), 2147483647);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)pScratch2+16*sizeof(*pScratch2)*0*4*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)pScratch1+16*sizeof(*pScratch1)*1*4*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)pScratch2+16*sizeof(*pScratch2)*1*4*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(30), (uchar *)pScratch1+16*sizeof(*pScratch1)*1*4*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(32), (uchar *)pScratch2+16*sizeof(*pScratch2)*1*4*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(34), (uchar *)pScratch1+16*sizeof(*pScratch1)*1*4*3);
   __vcop_pblock_init32(pblock, __offset+_PREG(36), (uchar *)pScratch2+16*sizeof(*pScratch2)*1*4*3);
   __vcop_pblock_init16(pblock, __offset+_PREG(38), -172);
   __vcop_pblock_init16(pblock, __offset+_PREG(39), 1940);
   __vcop_pblock_init16(pblock, __offset+_PREG(40), 64);
   __vcop_pblock_init16(pblock, __offset+_PREG(41), -160);
   __vcop_pblock_init16(pblock, __offset+_PREG(42), 800);
   __vcop_pblock_init32(pblock, __offset+_PREG(44), (uchar *)pInput+4*((16+1)*sizeof(*pOutput))*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(46), (uchar *)pInput+16*((16+1)*sizeof(*pOutput))+4*((16+1)*sizeof(*pOutput))*0);
   __offset += 46;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (numOfLines)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((16)/ (8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((4))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pOutput+4*16*sizeof(*pOutput)*1*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pOutput+256*sizeof(*pOutput)+4*16*sizeof(*pOutput)*1*0);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 64);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), -160);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), 800);
   __vcop_pblock_init16(pblock, __offset+_PREG(13), 1824);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pScratch1+16*sizeof(*pScratch1)*4*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pScratch2+16*sizeof(*pScratch1)*4*0);
   __offset += 16;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), (numOfLines)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), ((16)/ (8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((4))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (3)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pScratch1_16_lo+16*sizeof(*pScratch1)*4*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pScratch1_16_hi+16*sizeof(*pScratch1)*4*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pScratch2_16_lo+16*sizeof(*pScratch2)*4*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pScratch2_16_hi+16*sizeof(*pScratch2)*4*1);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), __vcop_vop_round(3, 1));
   __vcop_pblock_init16(pblock, __offset+_PREG(15), 256);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pOutput+4*16*sizeof(*pOutput)*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pOutput+256*sizeof(*pOutput)+4*16*sizeof(*pOutput)*1);
   __vcop_pblock_init16(pblock, __offset+_PREG(20), -448);
   __vcop_pblock_init16(pblock, __offset+_PREG(21), -672);
   __vcop_pblock_init16(pblock, __offset+_PREG(22), 288);
   __vcop_pblock_init16(pblock, __offset+_PREG(23), 1312);
   __vcop_pblock_init16(pblock, __offset+_PREG(24), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(25), -352);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), 15);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)pTwiddleFactor+8*sizeof(*pTwiddleFactor)*2*0);
   __offset += 28;

   return 90u;
}

void vcop_fft_256_32inter_stage_3_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VCos", 16);
   #pragma VCC_VREG("VInX", 17);
   #pragma VCC_VREG("VInX_hi", 18);
   #pragma VCC_VREG("VInX_lo", 19);
   #pragma VCC_VREG("VInY", 20);
   #pragma VCC_VREG("VInY_hi", 21);
   #pragma VCC_VREG("VInY_lo", 22);
   #pragma VCC_VREG("VK15", 23);
   #pragma VCC_VREG("VOutX", 24);
   #pragma VCC_VREG("VOutX0", 25);
   #pragma VCC_VREG("VOutX1", 26);
   #pragma VCC_VREG("VOutX2", 27);
   #pragma VCC_VREG("VOutX3", 28);
   #pragma VCC_VREG("VOutY", 29);
   #pragma VCC_VREG("VOutY0", 30);
   #pragma VCC_VREG("VOutY1", 31);
   #pragma VCC_VREG("VOutY2", 32);
   #pragma VCC_VREG("VOutY3", 33);
   #pragma VCC_VREG("VScatterOffset", 34);
   #pragma VCC_VREG("VSin", 35);
   #pragma VCC_VREG("VX0", 36);
   #pragma VCC_VREG("VX0_minus_X2", 37);
   #pragma VCC_VREG("VX0_plus_X2", 38);
   #pragma VCC_VREG("VX1", 39);
   #pragma VCC_VREG("VX1_minus_X3", 40);
   #pragma VCC_VREG("VX1_plus_X3", 41);
   #pragma VCC_VREG("VX2", 42);
   #pragma VCC_VREG("VX3", 43);
   #pragma VCC_VREG("VY0", 44);
   #pragma VCC_VREG("VY0_minus_Y2", 45);
   #pragma VCC_VREG("VY0_plus_Y2", 46);
   #pragma VCC_VREG("VY1", 47);
   #pragma VCC_VREG("VY1_minus_Y3", 48);
   #pragma VCC_VREG("VY1_plus_Y3", 49);
   #pragma VCC_VREG("VY2", 50);
   #pragma VCC_VREG("VY3", 51);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   #pragma EVE_REG("Addr_in", "A1");
   #pragma EVE_REG("Addr_out", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("lineIdx", "I2");
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 44u, 23u, 1u);
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(38), _PREG(39), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(40), _PREG(41), _PREG(42), _PREG(0));
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(44), _AGEN(1), _VREG(36), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(46), _AGEN(1), _VREG(44), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(8), _AGEN(1), _VREG(39), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(10), _AGEN(1), _VREG(47), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(12), _AGEN(1), _VREG(42), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(14), _AGEN(1), _VREG(50), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(16), _AGEN(1), _VREG(43), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(18), _AGEN(1), _VREG(51), __vcop_alws());
   __vcop_vmove(_VREG(36), _VREG(38));
   __vcop_vmove(_VREG(42), _VREG(37));
   __vcop_vaddsub(_VREG(38), _VREG(37));
   __vcop_vmove(_VREG(39), _VREG(41));
   __vcop_vmove(_VREG(43), _VREG(40));
   __vcop_vaddsub(_VREG(41), _VREG(40));
   __vcop_vmove(_VREG(44), _VREG(46));
   __vcop_vmove(_VREG(50), _VREG(45));
   __vcop_vaddsub(_VREG(46), _VREG(45));
   __vcop_vmove(_VREG(47), _VREG(49));
   __vcop_vmove(_VREG(51), _VREG(48));
   __vcop_vaddsub(_VREG(49), _VREG(48));
   __vcop_vmove(_VREG(38), _VREG(25));
   __vcop_vmove(_VREG(41), _VREG(27));
   __vcop_vaddsub(_VREG(25), _VREG(27));
   __vcop_vmove(_VREG(37), _VREG(26));
   __vcop_vmove(_VREG(48), _VREG(28));
   __vcop_vaddsub(_VREG(26), _VREG(28));
   __vcop_vmove(_VREG(46), _VREG(30));
   __vcop_vmove(_VREG(49), _VREG(32));
   __vcop_vaddsub(_VREG(30), _VREG(32));
   __vcop_vmove(_VREG(45), _VREG(33));
   __vcop_vmove(_VREG(40), _VREG(31));
   __vcop_vaddsub(_VREG(33), _VREG(31));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(25), _PREG(20), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(30), _PREG(24), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(26), _PREG(26), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(31), _PREG(28), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(27), _PREG(30), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(32), _PREG(32), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(28), _PREG(34), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(33), _PREG(36), _AGEN(2), _PREG(6));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   #pragma EVE_REG("Addr_in", "A1");
   #pragma EVE_REG("Addr_ou", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("lineIdx", "I2");
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 8u, 8u, 2u);
   __vcop_vagen(_AGEN(1), _PREG(10), _PREG(11), _PREG(12), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(10), _PREG(11), _PREG(13), _PREG(0));
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(14), _AGEN(1), _VREG(17), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(16), _AGEN(1), _VREG(20), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(17), _PREG(6), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(20), _PREG(8), _AGEN(2), _PREG(0));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   #pragma EVE_REG("Addr_in", "A1");
   #pragma EVE_REG("Addr_ou", "A2");
   #pragma EVE_REG("Addr_tw", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("lineIdx", "I1");
   #pragma EVE_REG("I3", "I2");
   #pragma EVE_REG("I4", "I3");
   #pragma EVE_REG("twIdx", "I4");
   

   __vcop_vloop(__vcop_compute(), 23u, 14u, 3u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(26), _VREG(23));
   __vcop_vagen(_AGEN(1), _PREG(15), _PREG(20), _PREG(21), _PREG(22));
   __vcop_vagen(_AGEN(2), _PREG(15), _PREG(20), _PREG(21), _PREG(23));
   __vcop_vagen(_AGEN(3), _PREG(24), _PREG(24), _PREG(25), _PREG(25));
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(28), _AGEN(3), _VPAIR(35,16), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(6), _AGEN(1), _VREG(19), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_ds2(), _PREG(8), _AGEN(1), _VREG(18), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(10), _AGEN(1), _VREG(22), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_ds2(), _PREG(12), _AGEN(1), _VREG(21), __vcop_alws());
   __vcop_vmpy(_VREG(19), _VREG(16), _VREG(24), _PREG(0));
   __vcop_vmpy(_VREG(22), _VREG(16), _VREG(29), _PREG(0));
   __vcop_vmadd(_VREG(22), _VREG(35), _VREG(24), _PREG(0));
   __vcop_vmsub(_VREG(19), _VREG(35), _VREG(29), _PREG(0));
   __vcop_vrnd(_VREG(24), _VREG(23), _VREG(24));
   __vcop_vrnd(_VREG(29), _VREG(23), _VREG(29));
   __vcop_vmadd(_VREG(18), _VREG(16), _VREG(24), _PREG(14));
   __vcop_vmadd(_VREG(21), _VREG(16), _VREG(29), _PREG(14));
   __vcop_vmadd(_VREG(21), _VREG(35), _VREG(24), _PREG(14));
   __vcop_vmsub(_VREG(18), _VREG(35), _VREG(29), _PREG(14));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(24), _PREG(16), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(29), _PREG(18), _AGEN(2), _PREG(0));
   __vcop_vloop_end(3u);

}

void vcop_fft_256_32inter_stage_3(
   __vptr_int32 pInput,
   __vptr_int32 pScratch1,
   __vptr_uint16 pScratch1_16_lo,
   __vptr_int16 pScratch1_16_hi,
   __vptr_int32 pScratch2,
   __vptr_uint16 pScratch2_16_lo,
   __vptr_int16 pScratch2_16_hi,
   __vptr_int32 pOutput,
   __vptr_int16 pTwiddleFactor,
   unsigned short numOfLines)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_256_32inter_stage_3_init(pInput, pScratch1, pScratch1_16_lo, pScratch1_16_hi, pScratch2, pScratch2_16_lo, pScratch2_16_hi, pOutput, pTwiddleFactor, numOfLines, __pblock_vcop_fft_256_32inter_stage_3);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_256_32inter_stage_3_vloops(__pblock_vcop_fft_256_32inter_stage_3);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_fft_256_32inter_stage_3_custom(
   __vptr_int32 pInput,
   __vptr_int32 pScratch1,
   __vptr_uint16 pScratch1_16_lo,
   __vptr_int16 pScratch1_16_hi,
   __vptr_int32 pScratch2,
   __vptr_uint16 pScratch2_16_lo,
   __vptr_int16 pScratch2_16_hi,
   __vptr_int32 pOutput,
   __vptr_int16 pTwiddleFactor,
   unsigned short numOfLines,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_256_32inter_stage_3_init(pInput, pScratch1, pScratch1_16_lo, pScratch1_16_hi, pScratch2, pScratch2_16_lo, pScratch2_16_hi, pOutput, pTwiddleFactor, numOfLines, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_256_32inter_stage_3_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_fft_256_16ix16o_32inter_stage_4_overflow, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_fft_256_16ix16o_32inter_stage_4_overflow, __ALIGNOF__(int));
unsigned short __pblock_vcop_fft_256_16ix16o_32inter_stage_4_overflow[94];

unsigned int vcop_fft_256_16ix16o_32inter_stage_4_overflow_param_count(void)
{
   return 94u;
}

unsigned int vcop_fft_256_16ix16o_32inter_stage_4_overflow_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_fft_256_16ix16o_32inter_stage_4_overflow_init(
   __vptr_int32 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int16 pOutput,
   __vptr_uint8 pScaleFactor,
   unsigned char numValidBits,
   unsigned short numOfLines,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (numOfLines)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (4)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pInput+1*(2*8u)*sizeof(*pInput)*1*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pInput+256*sizeof(*pInput)+1*(2*8u)*sizeof(*pInput)*1*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pInput+1*(2*8u)*sizeof(*pInput)*1*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pInput+256*sizeof(*pInput)+1*(2*8u)*sizeof(*pInput)*1*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pInput+1*(2*8u)*sizeof(*pInput)*1*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pInput+256*sizeof(*pInput)+1*(2*8u)*sizeof(*pInput)*1*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pInput+1*(2*8u)*sizeof(*pInput)*1*3);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pInput+256*sizeof(*pInput)+1*(2*8u)*sizeof(*pInput)*1*3);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)pScratch1+1*4*(2*8u)*sizeof(*pScratch1)*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)pScratch2+1*4*(2*8u)*sizeof(*pScratch2)*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)pScratch1+1*4*(2*8u)*sizeof(*pScratch1)*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)pScratch2+1*4*(2*8u)*sizeof(*pScratch2)*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(30), (uchar *)pScratch1+1*4*(2*8u)*sizeof(*pScratch1)*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(32), (uchar *)pScratch2+1*4*(2*8u)*sizeof(*pScratch2)*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(34), (uchar *)pScratch1+1*4*(2*8u)*sizeof(*pScratch1)*3);
   __vcop_pblock_init32(pblock, __offset+_PREG(36), (uchar *)pScratch2+1*4*(2*8u)*sizeof(*pScratch2)*3);
   __vcop_pblock_init16(pblock, __offset+_PREG(38), 256);
   __vcop_pblock_init16(pblock, __offset+_PREG(39), -736);
   __vcop_pblock_init16(pblock, __offset+_PREG(40), 1248);
   __vcop_pblock_init16(pblock, __offset+_PREG(41), 64);
   __vcop_pblock_init16(pblock, __offset+_PREG(42), -160);
   __vcop_pblock_init16(pblock, __offset+_PREG(43), 800);
   __vcop_pblock_init32(pblock, __offset+_PREG(44), 4294967295);
   __vcop_pblock_init32(pblock, __offset+_PREG(46), 0x8000000000);
   __offset += 46;

   /* Loop 2 PREGS */
   const int preg_ref4 = _PREG(12);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_4PARAM,preg_ref4,RM_NONE,0));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), -1);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pInput);
   __vcop_pblock_4param_init(pblock, __offset+_PREG(12), 40,40,0,0);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), 1);
   __offset += 18;

   /* Loop 3 PREGS */
   const int preg_ref5 = _PREG(12);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_4PARAM,preg_ref5,RM_NONE,0));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 4);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), numValidBits - 2);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pInput);
   __vcop_pblock_4param_init(pblock, __offset+_PREG(12), 40,40,0,0);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pScaleFactor);
   __offset += 18;

   /* Loop 4 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (numOfLines)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((256)/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pOutput);
   __vcop_pblock_init16(pblock, __offset+_PREG(8), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pScratch1);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pScratch2);
   __offset += 12;

   return 94u;
}

void vcop_fft_256_16ix16o_32inter_stage_4_overflow_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VInX", 16);
   #pragma VCC_VREG("VInY", 17);
   #pragma VCC_VREG("VInterim1", 18);
   #pragma VCC_VREG("VInterim2", 19);
   #pragma VCC_VREG("VInterim3", 20);
   #pragma VCC_VREG("VInterim4", 21);
   #pragma VCC_VREG("VMax", 22);
   #pragma VCC_VREG("VMin", 23);
   #pragma VCC_VREG("VOutX", 24);
   #pragma VCC_VREG("VOutX0", 25);
   #pragma VCC_VREG("VOutX1", 26);
   #pragma VCC_VREG("VOutX2", 27);
   #pragma VCC_VREG("VOutX3", 28);
   #pragma VCC_VREG("VOutY", 29);
   #pragma VCC_VREG("VOutY0", 30);
   #pragma VCC_VREG("VOutY1", 31);
   #pragma VCC_VREG("VOutY2", 32);
   #pragma VCC_VREG("VOutY3", 33);
   #pragma VCC_VREG("VScale", 34);
   #pragma VCC_VREG("VScaleIn", 35);
   #pragma VCC_VREG("VScaleMinus", 36);
   #pragma VCC_VREG("VScatterOffset", 37);
   #pragma VCC_VREG("VTemp", 38);
   #pragma VCC_VREG("VX0", 39);
   #pragma VCC_VREG("VX0_minus_X2", 40);
   #pragma VCC_VREG("VX0_plus_X2", 41);
   #pragma VCC_VREG("VX1", 42);
   #pragma VCC_VREG("VX1_minus_X3", 43);
   #pragma VCC_VREG("VX1_plus_X3", 44);
   #pragma VCC_VREG("VX2", 45);
   #pragma VCC_VREG("VX3", 46);
   #pragma VCC_VREG("VY0", 47);
   #pragma VCC_VREG("VY0_minus_Y2", 48);
   #pragma VCC_VREG("VY0_plus_Y2", 49);
   #pragma VCC_VREG("VY1", 50);
   #pragma VCC_VREG("VY1_minus_Y3", 51);
   #pragma VCC_VREG("VY1_plus_Y3", 52);
   #pragma VCC_VREG("VY2", 53);
   #pragma VCC_VREG("VY3", 54);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   #pragma EVE_REG("Addr_in", "A1");
   #pragma EVE_REG("Addr_out", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("lineIdx", "I2");
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 62u, 23u, 1u);
   __vcop_vinit(__vcop_sizeWU(), __vcop_once(), _PREG(44), _VREG(23));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(46), _VREG(22));
   __vcop_vagen(_AGEN(1), _PREG(38), _PREG(39), _PREG(40), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(41), _PREG(42), _PREG(43), _PREG(0));
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(6), _AGEN(1), _VREG(39), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(8), _AGEN(1), _VREG(47), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(10), _AGEN(1), _VREG(42), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(12), _AGEN(1), _VREG(50), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(14), _AGEN(1), _VREG(45), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(16), _AGEN(1), _VREG(53), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(18), _AGEN(1), _VREG(46), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(20), _AGEN(1), _VREG(54), __vcop_alws());
   __vcop_vmove(_VREG(39), _VREG(41));
   __vcop_vmove(_VREG(45), _VREG(40));
   __vcop_vaddsub(_VREG(41), _VREG(40));
   __vcop_vmove(_VREG(42), _VREG(44));
   __vcop_vmove(_VREG(46), _VREG(43));
   __vcop_vaddsub(_VREG(44), _VREG(43));
   __vcop_vmove(_VREG(47), _VREG(49));
   __vcop_vmove(_VREG(53), _VREG(48));
   __vcop_vaddsub(_VREG(49), _VREG(48));
   __vcop_vmove(_VREG(50), _VREG(52));
   __vcop_vmove(_VREG(54), _VREG(51));
   __vcop_vaddsub(_VREG(52), _VREG(51));
   __vcop_vmove(_VREG(41), _VREG(25));
   __vcop_vmove(_VREG(44), _VREG(27));
   __vcop_vaddsub(_VREG(25), _VREG(27));
   __vcop_vmove(_VREG(40), _VREG(26));
   __vcop_vmove(_VREG(51), _VREG(28));
   __vcop_vaddsub(_VREG(26), _VREG(28));
   __vcop_vmove(_VREG(49), _VREG(30));
   __vcop_vmove(_VREG(52), _VREG(32));
   __vcop_vaddsub(_VREG(30), _VREG(32));
   __vcop_vmove(_VREG(48), _VREG(33));
   __vcop_vmove(_VREG(43), _VREG(31));
   __vcop_vaddsub(_VREG(33), _VREG(31));
   __vcop_vmin(_VREG(25), _VREG(27), _VREG(18));
   __vcop_vmax(_VREG(25), _VREG(27), _VREG(19));
   __vcop_vmin(_VREG(26), _VREG(28), _VREG(20));
   __vcop_vmax(_VREG(26), _VREG(28), _VREG(21));
   __vcop_vmin(_VREG(18), _VREG(20), _VREG(18));
   __vcop_vmax(_VREG(19), _VREG(21), _VREG(19));
   __vcop_vmin(_VREG(30), _VREG(32), _VREG(20));
   __vcop_vmax(_VREG(30), _VREG(32), _VREG(21));
   __vcop_vmin(_VREG(18), _VREG(20), _VREG(18));
   __vcop_vmax(_VREG(19), _VREG(21), _VREG(19));
   __vcop_vmin(_VREG(33), _VREG(31), _VREG(20));
   __vcop_vmax(_VREG(33), _VREG(31), _VREG(21));
   __vcop_vmin(_VREG(18), _VREG(20), _VREG(18));
   __vcop_vmax(_VREG(19), _VREG(21), _VREG(19));
   __vcop_vmin(_VREG(23), _VREG(18), _VREG(23));
   __vcop_vmax(_VREG(22), _VREG(19), _VREG(22));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(25), _PREG(22), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(30), _PREG(24), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(26), _PREG(26), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(31), _PREG(28), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(27), _PREG(30), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(32), _PREG(32), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(28), _PREG(34), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(33), _PREG(36), _AGEN(2), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VK0", 55);
   #pragma VCC_VREG("VK1", 56);
   #pragma VCC_VREG("VKMinus1", 57);
   #pragma VCC_VREG("VLmbd1", 58);
   #pragma VCC_VREG("VLmbd2", 59);
   #pragma VCC_VREG("VLmbdFinal1", 60);
   #pragma VCC_VREG("VLmbdFinal2", 61);
   #pragma VCC_VREG("VMask", 62);
   #pragma VCC_VREG("VNeg1", 63);
   #pragma VCC_VREG("VNeg2", 64);
   #pragma VCC_VREG("VPos1", 65);
   #pragma VCC_VREG("VPos2", 66);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 25u, 9u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(16), _VREG(55));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(18), _VREG(56));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(8), _VREG(57));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vcmplt(_VREG(23), _VREG(55), _VREG(62));
   __vcop_vor(_VREG(57), _VREG(57), _VREG(63));
   __vcop_vsel(_VREG(62), _VREG(23), _VREG(63));
   __vcop_vcmplt(_VREG(22), _VREG(55), _VREG(62));
   __vcop_vor(_VREG(57), _VREG(57), _VREG(64));
   __vcop_vsel(_VREG(62), _VREG(22), _VREG(64));
   __vcop_vlmbd(_VREG(63), _VREG(55), _VREG(58));
   __vcop_vlmbd(_VREG(64), _VREG(55), _VREG(59));
   __vcop_vmax(_VREG(58), _VREG(59), _VREG(60));
   __vcop_vcmpge(_VREG(23), _VREG(55), _VREG(62));
   __vcop_vor(_VREG(55), _VREG(55), _VREG(65));
   __vcop_vsel(_VREG(62), _VREG(23), _VREG(65));
   __vcop_vcmpge(_VREG(22), _VREG(55), _VREG(62));
   __vcop_vor(_VREG(55), _VREG(55), _VREG(66));
   __vcop_vsel(_VREG(62), _VREG(22), _VREG(66));
   __vcop_vlmbd(_VREG(65), _VREG(56), _VREG(58));
   __vcop_vlmbd(_VREG(66), _VREG(56), _VREG(59));
   __vcop_vmax(_VREG(58), _VREG(59), _VREG(61));
   __vcop_vmax(_VREG(60), _VREG(61), _VREG(60));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(60), _PREG(10), _AGEN(0), _PREG(6));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VLmbd", 67);
   #pragma VCC_VREG("VNumValidBits", 68);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   #pragma EVE_REG("addrIn", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 11u, 9u, 3u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(16), _VREG(38));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(8), _VREG(68));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_1pt(), _PREG(18), _AGEN(0), _VREG(35), __vcop_once());
   __vcop_vload(__vcop_sizeW(), __vcop_1pt(), _PREG(10), _AGEN(1), _VREG(67), __vcop_alws());
   __vcop_vmax(_VREG(67), _VREG(38), _VREG(38));
   __vcop_vsub(_VREG(38), _VREG(68), _VREG(34));
   __vcop_vmax(_VREG(35), _VREG(34), _VREG(34));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_1pt(), __vcop_alws(), _VREG(34), _PREG(18), _AGEN(0), _PREG(6));
   __vcop_vloop_end(3u);

   /* VLOOP 4 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   #pragma EVE_REG("Addr_in", "A1");
   #pragma EVE_REG("Addr_out", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("lineIdx", "I3");
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 9u, 6u, 4u);
   __vcop_vagen(_AGEN(1), _PREG(8), _PREG(8), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(8), _PREG(8), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(10), _AGEN(1), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(12), _AGEN(1), _VREG(17), __vcop_alws());
   __vcop_vrnd(_VREG(16), _VREG(34), _VREG(24));
   __vcop_vrnd(_VREG(17), _VREG(34), _VREG(29));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_alws(), _VPAIR(24,29), _PREG(6), _AGEN(2), _PREG(0));
   __vcop_vloop_end(4u);

}

void vcop_fft_256_16ix16o_32inter_stage_4_overflow(
   __vptr_int32 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int16 pOutput,
   __vptr_uint8 pScaleFactor,
   unsigned char numValidBits,
   unsigned short numOfLines)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_256_16ix16o_32inter_stage_4_overflow_init(pInput, pScratch1, pScratch2, pOutput, pScaleFactor, numValidBits, numOfLines, __pblock_vcop_fft_256_16ix16o_32inter_stage_4_overflow);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_256_16ix16o_32inter_stage_4_overflow_vloops(__pblock_vcop_fft_256_16ix16o_32inter_stage_4_overflow);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_fft_256_16ix16o_32inter_stage_4_overflow_custom(
   __vptr_int32 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int16 pOutput,
   __vptr_uint8 pScaleFactor,
   unsigned char numValidBits,
   unsigned short numOfLines,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_256_16ix16o_32inter_stage_4_overflow_init(pInput, pScratch1, pScratch2, pOutput, pScaleFactor, numValidBits, numOfLines, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_256_16ix16o_32inter_stage_4_overflow_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_fft_256_16ix16o_32inter_stage_4, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_fft_256_16ix16o_32inter_stage_4, __ALIGNOF__(int));
unsigned short __pblock_vcop_fft_256_16ix16o_32inter_stage_4[58];

unsigned int vcop_fft_256_16ix16o_32inter_stage_4_param_count(void)
{
   return 58u;
}

unsigned int vcop_fft_256_16ix16o_32inter_stage_4_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_fft_256_16ix16o_32inter_stage_4_init(
   __vptr_int32 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int16 pOutput,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (numOfLines)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (4)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pInput+1*(2*8u)*sizeof(*pInput)*1*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pInput+256*sizeof(*pInput)+1*(2*8u)*sizeof(*pInput)*1*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pInput+1*(2*8u)*sizeof(*pInput)*1*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pInput+256*sizeof(*pInput)+1*(2*8u)*sizeof(*pInput)*1*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pInput+1*(2*8u)*sizeof(*pInput)*1*3);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pInput+256*sizeof(*pInput)+1*(2*8u)*sizeof(*pInput)*1*3);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pScratch1+1*4*(2*8u)*sizeof(*pScratch1)*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pScratch2+1*4*(2*8u)*sizeof(*pScratch2)*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)pScratch1+1*4*(2*8u)*sizeof(*pScratch1)*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)pScratch2+1*4*(2*8u)*sizeof(*pScratch2)*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)pScratch1+1*4*(2*8u)*sizeof(*pScratch1)*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)pScratch2+1*4*(2*8u)*sizeof(*pScratch2)*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(30), (uchar *)pScratch1+1*4*(2*8u)*sizeof(*pScratch1)*3);
   __vcop_pblock_init32(pblock, __offset+_PREG(32), (uchar *)pScratch2+1*4*(2*8u)*sizeof(*pScratch2)*3);
   __vcop_pblock_init16(pblock, __offset+_PREG(34), 256);
   __vcop_pblock_init16(pblock, __offset+_PREG(35), -736);
   __vcop_pblock_init16(pblock, __offset+_PREG(36), 1248);
   __vcop_pblock_init16(pblock, __offset+_PREG(37), 64);
   __vcop_pblock_init16(pblock, __offset+_PREG(38), -160);
   __vcop_pblock_init16(pblock, __offset+_PREG(39), 800);
   __vcop_pblock_init32(pblock, __offset+_PREG(40), (uchar *)pInput+1*(2*8u)*sizeof(*pInput)*1*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(42), (uchar *)pInput+256*sizeof(*pInput)+1*(2*8u)*sizeof(*pInput)*1*0);
   __offset += 42;

   /* Loop 2 PREGS */
   const int preg_ref6 = _PREG(10);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (numOfLines)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((256)/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_4PARAM,preg_ref6,RM_ROUND,scale));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pOutput);
   __vcop_pblock_4param_init(pblock, __offset+_PREG(10), (saturationLimit - 1), (saturationLimit - 1), -saturationLimit, -saturationLimit);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pScratch1);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pScratch2);
   __offset += 16;

   return 58u;
}

void vcop_fft_256_16ix16o_32inter_stage_4_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VInX", 16);
   #pragma VCC_VREG("VInY", 17);
   #pragma VCC_VREG("VOutX", 18);
   #pragma VCC_VREG("VOutX0", 19);
   #pragma VCC_VREG("VOutX1", 20);
   #pragma VCC_VREG("VOutX2", 21);
   #pragma VCC_VREG("VOutX3", 22);
   #pragma VCC_VREG("VOutY", 23);
   #pragma VCC_VREG("VOutY0", 24);
   #pragma VCC_VREG("VOutY1", 25);
   #pragma VCC_VREG("VOutY2", 26);
   #pragma VCC_VREG("VOutY3", 27);
   #pragma VCC_VREG("VX0", 28);
   #pragma VCC_VREG("VX0_minus_X2", 29);
   #pragma VCC_VREG("VX0_plus_X2", 30);
   #pragma VCC_VREG("VX1", 31);
   #pragma VCC_VREG("VX1_minus_X3", 32);
   #pragma VCC_VREG("VX1_plus_X3", 33);
   #pragma VCC_VREG("VX2", 34);
   #pragma VCC_VREG("VX3", 35);
   #pragma VCC_VREG("VY0", 36);
   #pragma VCC_VREG("VY0_minus_Y2", 37);
   #pragma VCC_VREG("VY0_plus_Y2", 38);
   #pragma VCC_VREG("VY1", 39);
   #pragma VCC_VREG("VY1_minus_Y3", 40);
   #pragma VCC_VREG("VY1_plus_Y3", 41);
   #pragma VCC_VREG("VY2", 42);
   #pragma VCC_VREG("VY3", 43);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   #pragma EVE_REG("Addr_in", "A1");
   #pragma EVE_REG("Addr_out", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("lineIdx", "I2");
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 44u, 21u, 1u);
   __vcop_vagen(_AGEN(1), _PREG(34), _PREG(35), _PREG(36), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(37), _PREG(38), _PREG(39), _PREG(0));
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(40), _AGEN(1), _VREG(28), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(42), _AGEN(1), _VREG(36), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(6), _AGEN(1), _VREG(31), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(8), _AGEN(1), _VREG(39), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(10), _AGEN(1), _VREG(34), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(12), _AGEN(1), _VREG(42), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(14), _AGEN(1), _VREG(35), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(16), _AGEN(1), _VREG(43), __vcop_alws());
   __vcop_vmove(_VREG(28), _VREG(30));
   __vcop_vmove(_VREG(34), _VREG(29));
   __vcop_vaddsub(_VREG(30), _VREG(29));
   __vcop_vmove(_VREG(31), _VREG(33));
   __vcop_vmove(_VREG(35), _VREG(32));
   __vcop_vaddsub(_VREG(33), _VREG(32));
   __vcop_vmove(_VREG(36), _VREG(38));
   __vcop_vmove(_VREG(42), _VREG(37));
   __vcop_vaddsub(_VREG(38), _VREG(37));
   __vcop_vmove(_VREG(39), _VREG(41));
   __vcop_vmove(_VREG(43), _VREG(40));
   __vcop_vaddsub(_VREG(41), _VREG(40));
   __vcop_vmove(_VREG(30), _VREG(19));
   __vcop_vmove(_VREG(33), _VREG(21));
   __vcop_vaddsub(_VREG(19), _VREG(21));
   __vcop_vmove(_VREG(29), _VREG(20));
   __vcop_vmove(_VREG(40), _VREG(22));
   __vcop_vaddsub(_VREG(20), _VREG(22));
   __vcop_vmove(_VREG(38), _VREG(24));
   __vcop_vmove(_VREG(41), _VREG(26));
   __vcop_vaddsub(_VREG(24), _VREG(26));
   __vcop_vmove(_VREG(37), _VREG(27));
   __vcop_vmove(_VREG(32), _VREG(25));
   __vcop_vaddsub(_VREG(27), _VREG(25));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(19), _PREG(18), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(24), _PREG(20), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(20), _PREG(22), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(25), _PREG(24), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(21), _PREG(26), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(26), _PREG(28), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(22), _PREG(30), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(27), _PREG(32), _AGEN(2), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   #pragma EVE_REG("Addr_in", "A1");
   #pragma EVE_REG("Addr_out", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("lineIdx", "I3");
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 9u, 8u, 2u);
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(7), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(7), _PREG(7), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(14), _AGEN(1), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(16), _AGEN(1), _VREG(17), __vcop_alws());
   __vcop_vor(_VREG(16), _VREG(16), _VREG(18));
   __vcop_vor(_VREG(17), _VREG(17), _VREG(23));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_alws(), _VPAIR(18,23), _PREG(8), _AGEN(2), _PREG(6));
   __vcop_vloop_end(2u);

}

void vcop_fft_256_16ix16o_32inter_stage_4(
   __vptr_int32 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int16 pOutput,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_256_16ix16o_32inter_stage_4_init(pInput, pScratch1, pScratch2, pOutput, numOfLines, scale, saturationLimit, __pblock_vcop_fft_256_16ix16o_32inter_stage_4);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_256_16ix16o_32inter_stage_4_vloops(__pblock_vcop_fft_256_16ix16o_32inter_stage_4);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_fft_256_16ix16o_32inter_stage_4_custom(
   __vptr_int32 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int16 pOutput,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_256_16ix16o_32inter_stage_4_init(pInput, pScratch1, pScratch2, pOutput, numOfLines, scale, saturationLimit, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_256_16ix16o_32inter_stage_4_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

