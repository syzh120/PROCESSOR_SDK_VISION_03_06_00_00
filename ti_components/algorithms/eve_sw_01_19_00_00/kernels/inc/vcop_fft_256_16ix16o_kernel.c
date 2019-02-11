#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_fft_256_16ix16o_stage_1, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_fft_256_16ix16o_stage_1, __ALIGNOF__(int));
unsigned short __pblock_vcop_fft_256_16ix16o_stage_1[38];

unsigned int vcop_fft_256_16ix16o_stage_1_param_count(void)
{
   return 38u;
}

unsigned int vcop_fft_256_16ix16o_stage_1_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_fft_256_16ix16o_stage_1_init(
   __vptr_int16 pInput,
   __vptr_int16 pOutput,
   __vptr_int16 pTwiddleFactor,
   unsigned short pitch,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   const int preg_ref1 = _PREG(20);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (numOfLines)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((1))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((64)/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_4PARAM,preg_ref1,RM_ROUND,scale));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), __vcop_store_round_sat(SM_4PARAM,preg_ref1,RM_ROUND,scale + 15));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pTwiddleFactor+8*sizeof(*pTwiddleFactor)*2*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pInput+64*sizeof(*pInput)*2*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pInput+64*sizeof(*pInput)*2*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pInput+64*sizeof(*pInput)*2*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pInput+64*sizeof(*pInput)*2*3);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pOutput+64*sizeof(*pOutput)*2*0);
   __vcop_pblock_4param_init(pblock, __offset+_PREG(20), (saturationLimit - 1), (saturationLimit - 1), -saturationLimit, -saturationLimit);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)pOutput+64*sizeof(*pOutput)*2*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)pOutput+64*sizeof(*pOutput)*2*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)pOutput+64*sizeof(*pOutput)*2*3);
   __vcop_pblock_init16(pblock, __offset+_PREG(30), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(31), 800);
   __vcop_pblock_init16(pblock, __offset+_PREG(32), (pitch) -(sizeof(*pInput)*2*64*4)*(((1))-1u) -(sizeof(*pInput)*2*8u)*(((64)/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(33), 96);
   __vcop_pblock_init16(pblock, __offset+_PREG(34), -672);
   __vcop_pblock_init32(pblock, __offset+_PREG(36), (uchar *)pTwiddleFactor+8*sizeof(*pTwiddleFactor)*2*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(38), (uchar *)pTwiddleFactor+8*sizeof(*pTwiddleFactor)*2*1);
   __offset += 38;

   return 38u;
}

void vcop_fft_256_16ix16o_stage_1_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VC1_76543210", 16);
   #pragma VCC_VREG("VC2_76543210", 17);
   #pragma VCC_VREG("VC3_76543210", 18);
   #pragma VCC_VREG("VS1_76543210", 19);
   #pragma VCC_VREG("VS2_76543210", 20);
   #pragma VCC_VREG("VS3_76543210", 21);
   #pragma VCC_VREG("VX0_76543210", 22);
   #pragma VCC_VREG("VX1_76543210", 23);
   #pragma VCC_VREG("VX2_76543210", 24);
   #pragma VCC_VREG("VX3_76543210", 25);
   #pragma VCC_VREG("VY0_76543210", 26);
   #pragma VCC_VREG("VY1_76543210", 27);
   #pragma VCC_VREG("VY2_76543210", 28);
   #pragma VCC_VREG("VY3_76543210", 29);
   #pragma VCC_VREG("V_x0r", 30);
   #pragma VCC_VREG("V_x1r", 31);
   #pragma VCC_VREG("V_x2r", 32);
   #pragma VCC_VREG("V_x3r", 33);
   #pragma VCC_VREG("V_y0i", 34);
   #pragma VCC_VREG("V_y1i", 35);
   #pragma VCC_VREG("V_y2i", 36);
   #pragma VCC_VREG("V_y3i", 37);
   #pragma VCC_VREG("Vxh0_76543210", 38);
   #pragma VCC_VREG("Vxh1_76543210", 39);
   #pragma VCC_VREG("Vxh20_76543210", 40);
   #pragma VCC_VREG("Vxh21_76543210", 41);
   #pragma VCC_VREG("Vxl0_76543210", 42);
   #pragma VCC_VREG("Vxl1_76543210", 43);
   #pragma VCC_VREG("Vxl20_76543210", 44);
   #pragma VCC_VREG("Vxl21_76543210", 45);
   #pragma VCC_VREG("Vxt1", 46);
   #pragma VCC_VREG("Vxt2", 47);
   #pragma VCC_VREG("Vxt3", 48);
   #pragma VCC_VREG("Vyt1", 49);
   #pragma VCC_VREG("Vyt2", 50);
   #pragma VCC_VREG("Vyt3", 51);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_in", "A0");
   #pragma EVE_REG("Addr_out", "A1");
   #pragma EVE_REG("Addr_tw", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("lineIdx", "I2");
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 51u, 19u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(30), _PREG(31), _PREG(32), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(30), _PREG(31), _PREG(31), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(33), _PREG(34), _PREG(34), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(36), _AGEN(2), _VPAIR(19,16), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(38), _AGEN(2), _VPAIR(20,17), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(8), _AGEN(2), _VPAIR(21,18), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(10), _AGEN(0), _VPAIR(22,26), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(12), _AGEN(0), _VPAIR(23,27), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(14), _AGEN(0), _VPAIR(24,28), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(16), _AGEN(0), _VPAIR(25,29), __vcop_alws());
   __vcop_vmove(_VREG(22), _VREG(38));
   __vcop_vmove(_VREG(24), _VREG(42));
   __vcop_vaddsub(_VREG(38), _VREG(42));
   __vcop_vmove(_VREG(23), _VREG(40));
   __vcop_vmove(_VREG(25), _VREG(44));
   __vcop_vaddsub(_VREG(40), _VREG(44));
   __vcop_vmove(_VREG(26), _VREG(39));
   __vcop_vmove(_VREG(28), _VREG(43));
   __vcop_vaddsub(_VREG(39), _VREG(43));
   __vcop_vmove(_VREG(27), _VREG(41));
   __vcop_vmove(_VREG(29), _VREG(45));
   __vcop_vaddsub(_VREG(41), _VREG(45));
   __vcop_vmove(_VREG(38), _VREG(30));
   __vcop_vmove(_VREG(40), _VREG(47));
   __vcop_vaddsub(_VREG(30), _VREG(47));
   __vcop_vmove(_VREG(42), _VREG(46));
   __vcop_vmove(_VREG(45), _VREG(48));
   __vcop_vaddsub(_VREG(46), _VREG(48));
   __vcop_vmove(_VREG(39), _VREG(34));
   __vcop_vmove(_VREG(41), _VREG(50));
   __vcop_vaddsub(_VREG(34), _VREG(50));
   __vcop_vmove(_VREG(43), _VREG(51));
   __vcop_vmove(_VREG(44), _VREG(49));
   __vcop_vaddsub(_VREG(51), _VREG(49));
   __vcop_vmpy(_VREG(47), _VREG(17), _VREG(32), _PREG(0));
   __vcop_vmpy(_VREG(50), _VREG(17), _VREG(36), _PREG(0));
   __vcop_vmadd(_VREG(50), _VREG(20), _VREG(32), _PREG(0));
   __vcop_vmsub(_VREG(47), _VREG(20), _VREG(36), _PREG(0));
   __vcop_vmpy(_VREG(46), _VREG(16), _VREG(31), _PREG(0));
   __vcop_vmpy(_VREG(49), _VREG(16), _VREG(35), _PREG(0));
   __vcop_vmpy(_VREG(48), _VREG(18), _VREG(33), _PREG(0));
   __vcop_vmpy(_VREG(51), _VREG(18), _VREG(37), _PREG(0));
   __vcop_vmadd(_VREG(51), _VREG(21), _VREG(33), _PREG(0));
   __vcop_vmsub(_VREG(48), _VREG(21), _VREG(37), _PREG(0));
   __vcop_vmadd(_VREG(49), _VREG(19), _VREG(31), _PREG(0));
   __vcop_vmsub(_VREG(46), _VREG(19), _VREG(35), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_alws(), _VPAIR(30,34), _PREG(18), _AGEN(1), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_alws(), _VPAIR(31,35), _PREG(24), _AGEN(1), _PREG(7));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_alws(), _VPAIR(32,36), _PREG(26), _AGEN(1), _PREG(7));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_alws(), _VPAIR(33,37), _PREG(28), _AGEN(1), _PREG(7));
   __vcop_vloop_end(1u);

}

void vcop_fft_256_16ix16o_stage_1(
   __vptr_int16 pInput,
   __vptr_int16 pOutput,
   __vptr_int16 pTwiddleFactor,
   unsigned short pitch,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_256_16ix16o_stage_1_init(pInput, pOutput, pTwiddleFactor, pitch, numOfLines, scale, saturationLimit, __pblock_vcop_fft_256_16ix16o_stage_1);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_256_16ix16o_stage_1_vloops(__pblock_vcop_fft_256_16ix16o_stage_1);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_fft_256_16ix16o_stage_1_custom(
   __vptr_int16 pInput,
   __vptr_int16 pOutput,
   __vptr_int16 pTwiddleFactor,
   unsigned short pitch,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_256_16ix16o_stage_1_init(pInput, pOutput, pTwiddleFactor, pitch, numOfLines, scale, saturationLimit, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_256_16ix16o_stage_1_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_fft_256_16ix16o_stage_2, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_fft_256_16ix16o_stage_2, __ALIGNOF__(int));
unsigned short __pblock_vcop_fft_256_16ix16o_stage_2[50];

unsigned int vcop_fft_256_16ix16o_stage_2_param_count(void)
{
   return 50u;
}

unsigned int vcop_fft_256_16ix16o_stage_2_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_fft_256_16ix16o_stage_2_init(
   __vptr_int16 pInput,
   __vptr_int16 pOutput,
   __vptr_int16 pTwiddleFactor,
   __vptr_uint16 pScatterOffset,
   unsigned short pitch,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   const int preg_ref2 = _PREG(22);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (numOfLines)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (4)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_4PARAM,preg_ref2,RM_ROUND,scale));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), __vcop_store_round_sat(SM_4PARAM,preg_ref2,RM_ROUND,scale + 15));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pTwiddleFactor+8*sizeof(*pTwiddleFactor)*2*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pTwiddleFactor+8*sizeof(*pTwiddleFactor)*2*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pInput+16*sizeof(*pInput)*2*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pInput+16*sizeof(*pInput)*2*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pInput+16*sizeof(*pInput)*2*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pInput+16*sizeof(*pInput)*2*3);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pOutput+sizeof(*pOutput)*2*4*0);
   __vcop_pblock_4param_init(pblock, __offset+_PREG(22), (saturationLimit - 1), (saturationLimit - 1), -saturationLimit, -saturationLimit);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)pOutput+sizeof(*pOutput)*2*4*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)pOutput+sizeof(*pOutput)*2*4*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(30), (uchar *)pOutput+sizeof(*pInput)*2*4*3);
   __vcop_pblock_init32(pblock, __offset+_PREG(32), (uchar *)pOutput+sizeof(*pOutput)*2*4*0+sizeof(*pOutput));
   __vcop_pblock_init32(pblock, __offset+_PREG(34), (uchar *)pOutput+sizeof(*pOutput)*2*4*1+sizeof(*pOutput));
   __vcop_pblock_init32(pblock, __offset+_PREG(36), (uchar *)pOutput+sizeof(*pOutput)*2*4*2+sizeof(*pOutput));
   __vcop_pblock_init32(pblock, __offset+_PREG(38), (uchar *)pOutput+sizeof(*pOutput)*2*4*3+sizeof(*pOutput));
   __vcop_pblock_init16(pblock, __offset+_PREG(40), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(41), 224);
   __vcop_pblock_init16(pblock, __offset+_PREG(42), (pitch) -((16*4)*sizeof(*pInput)*2)*((4)-1u) -(8u*sizeof(*pInput)*2)*((2)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(43), 544);
   __vcop_pblock_init16(pblock, __offset+_PREG(44), -540);
   __vcop_pblock_init16(pblock, __offset+_PREG(45), 532);
   __vcop_pblock_init16(pblock, __offset+_PREG(46), 96);
   __vcop_pblock_init16(pblock, __offset+_PREG(47), -96);
   __vcop_pblock_init32(pblock, __offset+_PREG(48), (uchar *)pScatterOffset);
   __vcop_pblock_init32(pblock, __offset+_PREG(50), (uchar *)pTwiddleFactor+8*sizeof(*pTwiddleFactor)*2*0);
   __offset += 50;

   return 50u;
}

void vcop_fft_256_16ix16o_stage_2_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VC1_76543210", 16);
   #pragma VCC_VREG("VC2_76543210", 17);
   #pragma VCC_VREG("VC3_76543210", 18);
   #pragma VCC_VREG("VS1_76543210", 19);
   #pragma VCC_VREG("VS2_76543210", 20);
   #pragma VCC_VREG("VS3_76543210", 21);
   #pragma VCC_VREG("VScatterOffset", 22);
   #pragma VCC_VREG("VX0_76543210", 23);
   #pragma VCC_VREG("VX1_76543210", 24);
   #pragma VCC_VREG("VX2_76543210", 25);
   #pragma VCC_VREG("VX3_76543210", 26);
   #pragma VCC_VREG("VY0_76543210", 27);
   #pragma VCC_VREG("VY1_76543210", 28);
   #pragma VCC_VREG("VY2_76543210", 29);
   #pragma VCC_VREG("VY3_76543210", 30);
   #pragma VCC_VREG("V_x0r", 31);
   #pragma VCC_VREG("V_x1r", 32);
   #pragma VCC_VREG("V_x2r", 33);
   #pragma VCC_VREG("V_x3r", 34);
   #pragma VCC_VREG("V_y0i", 35);
   #pragma VCC_VREG("V_y1i", 36);
   #pragma VCC_VREG("V_y2i", 37);
   #pragma VCC_VREG("V_y3i", 38);
   #pragma VCC_VREG("Vxh0_76543210", 39);
   #pragma VCC_VREG("Vxh1_76543210", 40);
   #pragma VCC_VREG("Vxh20_76543210", 41);
   #pragma VCC_VREG("Vxh21_76543210", 42);
   #pragma VCC_VREG("Vxl0_76543210", 43);
   #pragma VCC_VREG("Vxl1_76543210", 44);
   #pragma VCC_VREG("Vxl20_76543210", 45);
   #pragma VCC_VREG("Vxl21_76543210", 46);
   #pragma VCC_VREG("Vxt1", 47);
   #pragma VCC_VREG("Vxt2", 48);
   #pragma VCC_VREG("Vxt3", 49);
   #pragma VCC_VREG("Vyt1", 50);
   #pragma VCC_VREG("Vyt2", 51);
   #pragma VCC_VREG("Vyt3", 52);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   #pragma EVE_REG("Addr_in", "A1");
   #pragma EVE_REG("Addr_ou", "A2");
   #pragma EVE_REG("Addr_tw", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("lineIdx", "I2");
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 57u, 25u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(40), _PREG(41), _PREG(42), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(43), _PREG(44), _PREG(45), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(46), _PREG(47), _PREG(47), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(48), _AGEN(0), _VREG(22), __vcop_once());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(50), _AGEN(3), _VPAIR(19,16), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(8), _AGEN(3), _VPAIR(20,17), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(10), _AGEN(3), _VPAIR(21,18), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(12), _AGEN(1), _VPAIR(23,27), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(14), _AGEN(1), _VPAIR(24,28), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(16), _AGEN(1), _VPAIR(25,29), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(18), _AGEN(1), _VPAIR(26,30), __vcop_alws());
   __vcop_vmove(_VREG(23), _VREG(39));
   __vcop_vmove(_VREG(25), _VREG(43));
   __vcop_vaddsub(_VREG(39), _VREG(43));
   __vcop_vmove(_VREG(24), _VREG(41));
   __vcop_vmove(_VREG(26), _VREG(45));
   __vcop_vaddsub(_VREG(41), _VREG(45));
   __vcop_vmove(_VREG(27), _VREG(40));
   __vcop_vmove(_VREG(29), _VREG(44));
   __vcop_vaddsub(_VREG(40), _VREG(44));
   __vcop_vmove(_VREG(28), _VREG(42));
   __vcop_vmove(_VREG(30), _VREG(46));
   __vcop_vaddsub(_VREG(42), _VREG(46));
   __vcop_vmove(_VREG(39), _VREG(31));
   __vcop_vmove(_VREG(41), _VREG(48));
   __vcop_vaddsub(_VREG(31), _VREG(48));
   __vcop_vmove(_VREG(43), _VREG(47));
   __vcop_vmove(_VREG(46), _VREG(49));
   __vcop_vaddsub(_VREG(47), _VREG(49));
   __vcop_vmove(_VREG(40), _VREG(35));
   __vcop_vmove(_VREG(42), _VREG(51));
   __vcop_vaddsub(_VREG(35), _VREG(51));
   __vcop_vmove(_VREG(44), _VREG(52));
   __vcop_vmove(_VREG(45), _VREG(50));
   __vcop_vaddsub(_VREG(52), _VREG(50));
   __vcop_vmpy(_VREG(48), _VREG(17), _VREG(33), _PREG(0));
   __vcop_vmpy(_VREG(51), _VREG(17), _VREG(37), _PREG(0));
   __vcop_vmadd(_VREG(51), _VREG(20), _VREG(33), _PREG(0));
   __vcop_vmsub(_VREG(48), _VREG(20), _VREG(37), _PREG(0));
   __vcop_vmpy(_VREG(47), _VREG(16), _VREG(32), _PREG(0));
   __vcop_vmpy(_VREG(50), _VREG(16), _VREG(36), _PREG(0));
   __vcop_vmpy(_VREG(49), _VREG(18), _VREG(34), _PREG(0));
   __vcop_vmpy(_VREG(52), _VREG(18), _VREG(38), _PREG(0));
   __vcop_vmadd(_VREG(50), _VREG(19), _VREG(32), _PREG(0));
   __vcop_vmsub(_VREG(47), _VREG(19), _VREG(36), _PREG(0));
   __vcop_vmadd(_VREG(52), _VREG(21), _VREG(34), _PREG(0));
   __vcop_vmsub(_VREG(49), _VREG(21), _VREG(38), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_pdda(_VREG(22)), __vcop_alws(), _VREG(31), _PREG(20), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_pdda(_VREG(22)), __vcop_alws(), _VREG(32), _PREG(26), _AGEN(2), _PREG(7));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_pdda(_VREG(22)), __vcop_alws(), _VREG(33), _PREG(28), _AGEN(2), _PREG(7));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_pdda(_VREG(22)), __vcop_alws(), _VREG(34), _PREG(30), _AGEN(2), _PREG(7));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_pdda(_VREG(22)), __vcop_alws(), _VREG(35), _PREG(32), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_pdda(_VREG(22)), __vcop_alws(), _VREG(36), _PREG(34), _AGEN(2), _PREG(7));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_pdda(_VREG(22)), __vcop_alws(), _VREG(37), _PREG(36), _AGEN(2), _PREG(7));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_pdda(_VREG(22)), __vcop_alws(), _VREG(38), _PREG(38), _AGEN(2), _PREG(7));
   __vcop_vloop_end(1u);

}

void vcop_fft_256_16ix16o_stage_2(
   __vptr_int16 pInput,
   __vptr_int16 pOutput,
   __vptr_int16 pTwiddleFactor,
   __vptr_uint16 pScatterOffset,
   unsigned short pitch,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_256_16ix16o_stage_2_init(pInput, pOutput, pTwiddleFactor, pScatterOffset, pitch, numOfLines, scale, saturationLimit, __pblock_vcop_fft_256_16ix16o_stage_2);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_256_16ix16o_stage_2_vloops(__pblock_vcop_fft_256_16ix16o_stage_2);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_fft_256_16ix16o_stage_2_custom(
   __vptr_int16 pInput,
   __vptr_int16 pOutput,
   __vptr_int16 pTwiddleFactor,
   __vptr_uint16 pScatterOffset,
   unsigned short pitch,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_256_16ix16o_stage_2_init(pInput, pOutput, pTwiddleFactor, pScatterOffset, pitch, numOfLines, scale, saturationLimit, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_256_16ix16o_stage_2_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_fft_256_16ix16o_stage_3, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_fft_256_16ix16o_stage_3, __ALIGNOF__(int));
unsigned short __pblock_vcop_fft_256_16ix16o_stage_3[40];

unsigned int vcop_fft_256_16ix16o_stage_3_param_count(void)
{
   return 40u;
}

unsigned int vcop_fft_256_16ix16o_stage_3_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_fft_256_16ix16o_stage_3_init(
   __vptr_int16 pInput,
   __vptr_int16 pOutput,
   __vptr_int16 pTwiddleFactor,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   const int preg_ref3 = _PREG(20);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (numOfLines)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (4)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_4PARAM,preg_ref3,RM_ROUND,scale));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), __vcop_store_round_sat(SM_4PARAM,preg_ref3,RM_ROUND,15 + scale));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pTwiddleFactor+8*sizeof(*pTwiddleFactor)*2*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pInput+4*(17*sizeof(*pOutput)*2)*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pInput+4*(17*sizeof(*pOutput)*2)*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pInput+4*(17*sizeof(*pOutput)*2)*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pInput+4*(17*sizeof(*pOutput)*2)*3);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pOutput+4*(2*8u)*sizeof(*pOutput)*2*0);
   __vcop_pblock_4param_init(pblock, __offset+_PREG(20), (saturationLimit - 1), (saturationLimit - 1), -saturationLimit, -saturationLimit);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)pOutput+4*(2*8u)*sizeof(*pOutput)*2*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)pOutput+4*(2*8u)*sizeof(*pOutput)*2*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)pOutput+4*(2*8u)*sizeof(*pOutput)*2*3);
   __vcop_pblock_init16(pblock, __offset+_PREG(30), 68);
   __vcop_pblock_init16(pblock, __offset+_PREG(31), -172);
   __vcop_pblock_init16(pblock, __offset+_PREG(32), 852);
   __vcop_pblock_init16(pblock, __offset+_PREG(33), 64);
   __vcop_pblock_init16(pblock, __offset+_PREG(34), -160);
   __vcop_pblock_init16(pblock, __offset+_PREG(35), 800);
   __vcop_pblock_init16(pblock, __offset+_PREG(36), 96);
   __vcop_pblock_init16(pblock, __offset+_PREG(37), -288);
   __vcop_pblock_init32(pblock, __offset+_PREG(38), (uchar *)pTwiddleFactor+8*sizeof(*pTwiddleFactor)*2*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(40), (uchar *)pTwiddleFactor+8*sizeof(*pTwiddleFactor)*2*1);
   __offset += 40;

   return 40u;
}

void vcop_fft_256_16ix16o_stage_3_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VC1_76543210", 16);
   #pragma VCC_VREG("VC2_76543210", 17);
   #pragma VCC_VREG("VC3_76543210", 18);
   #pragma VCC_VREG("VS1_76543210", 19);
   #pragma VCC_VREG("VS2_76543210", 20);
   #pragma VCC_VREG("VS3_76543210", 21);
   #pragma VCC_VREG("VX0_76543210", 22);
   #pragma VCC_VREG("VX1_76543210", 23);
   #pragma VCC_VREG("VX2_76543210", 24);
   #pragma VCC_VREG("VX3_76543210", 25);
   #pragma VCC_VREG("VY0_76543210", 26);
   #pragma VCC_VREG("VY1_76543210", 27);
   #pragma VCC_VREG("VY2_76543210", 28);
   #pragma VCC_VREG("VY3_76543210", 29);
   #pragma VCC_VREG("V_x0r", 30);
   #pragma VCC_VREG("V_x1r", 31);
   #pragma VCC_VREG("V_x2r", 32);
   #pragma VCC_VREG("V_x3r", 33);
   #pragma VCC_VREG("V_y0i", 34);
   #pragma VCC_VREG("V_y1i", 35);
   #pragma VCC_VREG("V_y2i", 36);
   #pragma VCC_VREG("V_y3i", 37);
   #pragma VCC_VREG("Vxh0_76543210", 38);
   #pragma VCC_VREG("Vxh1_76543210", 39);
   #pragma VCC_VREG("Vxh20_76543210", 40);
   #pragma VCC_VREG("Vxh21_76543210", 41);
   #pragma VCC_VREG("Vxl0_76543210", 42);
   #pragma VCC_VREG("Vxl1_76543210", 43);
   #pragma VCC_VREG("Vxl20_76543210", 44);
   #pragma VCC_VREG("Vxl21_76543210", 45);
   #pragma VCC_VREG("Vxt1", 46);
   #pragma VCC_VREG("Vxt2", 47);
   #pragma VCC_VREG("Vxt3", 48);
   #pragma VCC_VREG("Vyt1", 49);
   #pragma VCC_VREG("Vyt2", 50);
   #pragma VCC_VREG("Vyt3", 51);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_in", "A0");
   #pragma EVE_REG("Addr_out", "A1");
   #pragma EVE_REG("Addr_tw", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("lineIdx", "I2");
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 51u, 20u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(30), _PREG(31), _PREG(32), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(33), _PREG(34), _PREG(35), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(36), _PREG(37), _PREG(37), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(38), _AGEN(2), _VPAIR(19,16), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(40), _AGEN(2), _VPAIR(20,17), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(8), _AGEN(2), _VPAIR(21,18), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(10), _AGEN(0), _VPAIR(22,26), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(12), _AGEN(0), _VPAIR(23,27), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(14), _AGEN(0), _VPAIR(24,28), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(16), _AGEN(0), _VPAIR(25,29), __vcop_alws());
   __vcop_vmove(_VREG(22), _VREG(38));
   __vcop_vmove(_VREG(24), _VREG(42));
   __vcop_vaddsub(_VREG(38), _VREG(42));
   __vcop_vmove(_VREG(23), _VREG(40));
   __vcop_vmove(_VREG(25), _VREG(44));
   __vcop_vaddsub(_VREG(40), _VREG(44));
   __vcop_vmove(_VREG(26), _VREG(39));
   __vcop_vmove(_VREG(28), _VREG(43));
   __vcop_vaddsub(_VREG(39), _VREG(43));
   __vcop_vmove(_VREG(27), _VREG(41));
   __vcop_vmove(_VREG(29), _VREG(45));
   __vcop_vaddsub(_VREG(41), _VREG(45));
   __vcop_vmove(_VREG(38), _VREG(30));
   __vcop_vmove(_VREG(40), _VREG(47));
   __vcop_vaddsub(_VREG(30), _VREG(47));
   __vcop_vmove(_VREG(42), _VREG(46));
   __vcop_vmove(_VREG(45), _VREG(48));
   __vcop_vaddsub(_VREG(46), _VREG(48));
   __vcop_vmove(_VREG(39), _VREG(34));
   __vcop_vmove(_VREG(41), _VREG(50));
   __vcop_vaddsub(_VREG(34), _VREG(50));
   __vcop_vmove(_VREG(43), _VREG(51));
   __vcop_vmove(_VREG(44), _VREG(49));
   __vcop_vaddsub(_VREG(51), _VREG(49));
   __vcop_vmpy(_VREG(47), _VREG(17), _VREG(32), _PREG(0));
   __vcop_vmpy(_VREG(50), _VREG(17), _VREG(36), _PREG(0));
   __vcop_vmadd(_VREG(50), _VREG(20), _VREG(32), _PREG(0));
   __vcop_vmsub(_VREG(47), _VREG(20), _VREG(36), _PREG(0));
   __vcop_vmpy(_VREG(46), _VREG(16), _VREG(31), _PREG(0));
   __vcop_vmpy(_VREG(49), _VREG(16), _VREG(35), _PREG(0));
   __vcop_vmpy(_VREG(48), _VREG(18), _VREG(33), _PREG(0));
   __vcop_vmpy(_VREG(51), _VREG(18), _VREG(37), _PREG(0));
   __vcop_vmadd(_VREG(49), _VREG(19), _VREG(31), _PREG(0));
   __vcop_vmsub(_VREG(46), _VREG(19), _VREG(35), _PREG(0));
   __vcop_vmadd(_VREG(51), _VREG(21), _VREG(33), _PREG(0));
   __vcop_vmsub(_VREG(48), _VREG(21), _VREG(37), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_alws(), _VPAIR(30,34), _PREG(18), _AGEN(1), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_alws(), _VPAIR(31,35), _PREG(24), _AGEN(1), _PREG(7));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_alws(), _VPAIR(32,36), _PREG(26), _AGEN(1), _PREG(7));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_alws(), _VPAIR(33,37), _PREG(28), _AGEN(1), _PREG(7));
   __vcop_vloop_end(1u);

}

void vcop_fft_256_16ix16o_stage_3(
   __vptr_int16 pInput,
   __vptr_int16 pOutput,
   __vptr_int16 pTwiddleFactor,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_256_16ix16o_stage_3_init(pInput, pOutput, pTwiddleFactor, numOfLines, scale, saturationLimit, __pblock_vcop_fft_256_16ix16o_stage_3);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_256_16ix16o_stage_3_vloops(__pblock_vcop_fft_256_16ix16o_stage_3);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_fft_256_16ix16o_stage_3_custom(
   __vptr_int16 pInput,
   __vptr_int16 pOutput,
   __vptr_int16 pTwiddleFactor,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_256_16ix16o_stage_3_init(pInput, pOutput, pTwiddleFactor, numOfLines, scale, saturationLimit, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_256_16ix16o_stage_3_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_fft_256_16ix16o_stage_4, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_fft_256_16ix16o_stage_4, __ALIGNOF__(int));
unsigned short __pblock_vcop_fft_256_16ix16o_stage_4[32];

unsigned int vcop_fft_256_16ix16o_stage_4_param_count(void)
{
   return 32u;
}

unsigned int vcop_fft_256_16ix16o_stage_4_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_fft_256_16ix16o_stage_4_init(
   __vptr_int16 pInput,
   __vptr_int16 pOutput,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   const int preg_ref4 = _PREG(14);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (numOfLines)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (4)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_4PARAM,preg_ref4,RM_ROUND,scale));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 256);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pInput+1*(2*8u)*sizeof(*pInput)*2*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pInput+1*(2*8u)*sizeof(*pInput)*2*3);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pOutput+1*4*(2*8u)*sizeof(*pOutput)*2*0);
   __vcop_pblock_4param_init(pblock, __offset+_PREG(14), (saturationLimit - 1), (saturationLimit - 1), -saturationLimit, -saturationLimit);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pOutput+1*4*(2*8u)*sizeof(*pOutput)*2*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pOutput+1*4*(2*8u)*sizeof(*pOutput)*2*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)pOutput+1*4*(2*8u)*sizeof(*pOutput)*2*3);
   __vcop_pblock_init16(pblock, __offset+_PREG(24), -736);
   __vcop_pblock_init16(pblock, __offset+_PREG(25), 224);
   __vcop_pblock_init16(pblock, __offset+_PREG(26), 64);
   __vcop_pblock_init16(pblock, __offset+_PREG(27), -160);
   __vcop_pblock_init16(pblock, __offset+_PREG(28), 800);
   __vcop_pblock_init32(pblock, __offset+_PREG(30), (uchar *)pInput+1*(2*8u)*sizeof(*pInput)*2*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(32), (uchar *)pInput+1*(2*8u)*sizeof(*pInput)*2*1);
   __offset += 32;

   return 32u;
}

void vcop_fft_256_16ix16o_stage_4_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VC1_76543210", 16);
   #pragma VCC_VREG("VC2_76543210", 17);
   #pragma VCC_VREG("VC3_76543210", 18);
   #pragma VCC_VREG("VS1_76543210", 19);
   #pragma VCC_VREG("VS2_76543210", 20);
   #pragma VCC_VREG("VS3_76543210", 21);
   #pragma VCC_VREG("VX0_76543210", 22);
   #pragma VCC_VREG("VX1_76543210", 23);
   #pragma VCC_VREG("VX2_76543210", 24);
   #pragma VCC_VREG("VX3_76543210", 25);
   #pragma VCC_VREG("VY0_76543210", 26);
   #pragma VCC_VREG("VY1_76543210", 27);
   #pragma VCC_VREG("VY2_76543210", 28);
   #pragma VCC_VREG("VY3_76543210", 29);
   #pragma VCC_VREG("V_x0r", 30);
   #pragma VCC_VREG("V_x1r", 31);
   #pragma VCC_VREG("V_x2r", 32);
   #pragma VCC_VREG("V_x3r", 33);
   #pragma VCC_VREG("V_y0i", 34);
   #pragma VCC_VREG("V_y1i", 35);
   #pragma VCC_VREG("V_y2i", 36);
   #pragma VCC_VREG("V_y3i", 37);
   #pragma VCC_VREG("Vxh0_76543210", 38);
   #pragma VCC_VREG("Vxh1_76543210", 39);
   #pragma VCC_VREG("Vxh20_76543210", 40);
   #pragma VCC_VREG("Vxh21_76543210", 41);
   #pragma VCC_VREG("Vxl0_76543210", 42);
   #pragma VCC_VREG("Vxl1_76543210", 43);
   #pragma VCC_VREG("Vxl20_76543210", 44);
   #pragma VCC_VREG("Vxl21_76543210", 45);
   #pragma VCC_VREG("Vxt1", 46);
   #pragma VCC_VREG("Vxt2", 47);
   #pragma VCC_VREG("Vxt3", 48);
   #pragma VCC_VREG("Vyt1", 49);
   #pragma VCC_VREG("Vyt2", 50);
   #pragma VCC_VREG("Vyt3", 51);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_in", "A0");
   #pragma EVE_REG("Addr_out", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("lineIdx", "I2");
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 35u, 16u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(24), _PREG(25), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(26), _PREG(27), _PREG(28), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(30), _AGEN(0), _VPAIR(22,26), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(32), _AGEN(0), _VPAIR(23,27), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(8), _AGEN(0), _VPAIR(24,28), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(10), _AGEN(0), _VPAIR(25,29), __vcop_alws());
   __vcop_vmove(_VREG(22), _VREG(38));
   __vcop_vmove(_VREG(24), _VREG(42));
   __vcop_vaddsub(_VREG(38), _VREG(42));
   __vcop_vmove(_VREG(23), _VREG(40));
   __vcop_vmove(_VREG(25), _VREG(44));
   __vcop_vaddsub(_VREG(40), _VREG(44));
   __vcop_vmove(_VREG(26), _VREG(39));
   __vcop_vmove(_VREG(28), _VREG(43));
   __vcop_vaddsub(_VREG(39), _VREG(43));
   __vcop_vmove(_VREG(27), _VREG(41));
   __vcop_vmove(_VREG(29), _VREG(45));
   __vcop_vaddsub(_VREG(41), _VREG(45));
   __vcop_vmove(_VREG(38), _VREG(30));
   __vcop_vmove(_VREG(40), _VREG(47));
   __vcop_vaddsub(_VREG(30), _VREG(47));
   __vcop_vmove(_VREG(42), _VREG(46));
   __vcop_vmove(_VREG(45), _VREG(48));
   __vcop_vaddsub(_VREG(46), _VREG(48));
   __vcop_vmove(_VREG(39), _VREG(34));
   __vcop_vmove(_VREG(41), _VREG(50));
   __vcop_vaddsub(_VREG(34), _VREG(50));
   __vcop_vmove(_VREG(43), _VREG(51));
   __vcop_vmove(_VREG(44), _VREG(49));
   __vcop_vaddsub(_VREG(51), _VREG(49));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_alws(), _VPAIR(30,34), _PREG(12), _AGEN(1), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_alws(), _VPAIR(46,49), _PREG(18), _AGEN(1), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_alws(), _VPAIR(47,50), _PREG(20), _AGEN(1), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_alws(), _VPAIR(48,51), _PREG(22), _AGEN(1), _PREG(6));
   __vcop_vloop_end(1u);

}

void vcop_fft_256_16ix16o_stage_4(
   __vptr_int16 pInput,
   __vptr_int16 pOutput,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_256_16ix16o_stage_4_init(pInput, pOutput, numOfLines, scale, saturationLimit, __pblock_vcop_fft_256_16ix16o_stage_4);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_256_16ix16o_stage_4_vloops(__pblock_vcop_fft_256_16ix16o_stage_4);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_fft_256_16ix16o_stage_4_custom(
   __vptr_int16 pInput,
   __vptr_int16 pOutput,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_256_16ix16o_stage_4_init(pInput, pOutput, numOfLines, scale, saturationLimit, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_256_16ix16o_stage_4_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

