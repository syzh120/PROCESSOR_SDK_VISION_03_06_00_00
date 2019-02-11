#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_fft_128_16ix32o_radix2_stage_4_overflow, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_fft_128_16ix32o_radix2_stage_4_overflow, __ALIGNOF__(int));
unsigned short __pblock_vcop_fft_128_16ix32o_radix2_stage_4_overflow[78];

unsigned int vcop_fft_128_16ix32o_radix2_stage_4_overflow_param_count(void)
{
   return 78u;
}

unsigned int vcop_fft_128_16ix32o_radix2_stage_4_overflow_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_fft_128_16ix32o_radix2_stage_4_overflow_init(
   __vptr_int32 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int32 pOutput,
   __vptr_uint8 pScaleFactor,
   unsigned char numValidBits,
   unsigned short numOfLines,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (numOfLines)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (32 / (8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (2)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pInput+2*8u*sizeof(*pInput)*1*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pInput+128*sizeof(*pInput)+2*8u*sizeof(*pInput)*1*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pInput+2*8u*sizeof(*pInput)*1*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pInput+128*sizeof(*pInput)+2*8u*sizeof(*pInput)*1*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pScratch1+2*8u*sizeof(*pScratch1)*4*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pScratch2+2*8u*sizeof(*pScratch1)*4*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pScratch1+2*8u*sizeof(*pScratch2)*4*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pScratch2+2*8u*sizeof(*pScratch2)*4*1);
   __vcop_pblock_init16(pblock, __offset+_PREG(22), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(23), 96);
   __vcop_pblock_init16(pblock, __offset+_PREG(24), 608);
   __vcop_pblock_init16(pblock, __offset+_PREG(25), 288);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), 4294967295);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), 0x8000000000);
   __offset += 28;

   /* Loop 2 PREGS */
   const int preg_ref1 = _PREG(12);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_4PARAM,preg_ref1,RM_NONE,0));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), -1);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pInput);
   __vcop_pblock_4param_init(pblock, __offset+_PREG(12), 40,40,0,0);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), 1);
   __offset += 18;

   /* Loop 3 PREGS */
   const int preg_ref2 = _PREG(12);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_4PARAM,preg_ref2,RM_NONE,0));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 4);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pInput);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pScaleFactor);
   __vcop_pblock_4param_init(pblock, __offset+_PREG(12), 40,40,0,0);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), numValidBits - 2);
   __offset += 18;

   /* Loop 4 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (numOfLines)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((128)/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pOutput);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pOutput+8u*sizeof(*pOutput));
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), 64);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pScratch1);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pScratch2);
   __offset += 14;

   return 78u;
}

void vcop_fft_128_16ix32o_radix2_stage_4_overflow_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VInX", 16);
   #pragma VCC_VREG("VInY", 17);
   #pragma VCC_VREG("VMax1", 18);
   #pragma VCC_VREG("VMin1", 19);
   #pragma VCC_VREG("VOutX", 20);
   #pragma VCC_VREG("VOutY", 21);
   #pragma VCC_VREG("VScale", 22);
   #pragma VCC_VREG("VScaleIn", 23);
   #pragma VCC_VREG("VScaleMinus", 24);
   #pragma VCC_VREG("VTemp", 25);
   #pragma VCC_VREG("VTemp1", 26);
   #pragma VCC_VREG("VTemp2", 27);
   #pragma VCC_VREG("VTemp3", 28);
   #pragma VCC_VREG("VTemp4", 29);
   #pragma VCC_VREG("Vx0", 30);
   #pragma VCC_VREG("Vx0_minus_x1", 31);
   #pragma VCC_VREG("Vx0_plus_x1", 32);
   #pragma VCC_VREG("Vx1", 33);
   #pragma VCC_VREG("Vy0", 34);
   #pragma VCC_VREG("Vy0_minus_y1", 35);
   #pragma VCC_VREG("Vy0_plus_y1", 36);
   #pragma VCC_VREG("Vy1", 37);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   #pragma EVE_REG("addr_in", "A1");
   #pragma EVE_REG("addr_out", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("lineIdx", "I2");
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 28u, 14u, 1u);
   __vcop_vinit(__vcop_sizeWU(), __vcop_once(), _PREG(26), _VREG(19));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(28), _VREG(18));
   __vcop_vagen(_AGEN(1), _PREG(22), _PREG(23), _PREG(24), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(22), _PREG(22), _PREG(25), _PREG(0));
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(6), _AGEN(1), _VREG(30), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(8), _AGEN(1), _VREG(34), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(10), _AGEN(1), _VREG(33), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(12), _AGEN(1), _VREG(37), __vcop_alws());
   __vcop_vmove(_VREG(30), _VREG(32));
   __vcop_vmove(_VREG(33), _VREG(31));
   __vcop_vaddsub(_VREG(32), _VREG(31));
   __vcop_vmove(_VREG(34), _VREG(36));
   __vcop_vmove(_VREG(37), _VREG(35));
   __vcop_vaddsub(_VREG(36), _VREG(35));
   __vcop_vmin(_VREG(32), _VREG(36), _VREG(26));
   __vcop_vmin(_VREG(31), _VREG(35), _VREG(27));
   __vcop_vmax(_VREG(32), _VREG(36), _VREG(28));
   __vcop_vmax(_VREG(31), _VREG(35), _VREG(29));
   __vcop_vmin(_VREG(26), _VREG(27), _VREG(26));
   __vcop_vmax(_VREG(28), _VREG(29), _VREG(28));
   __vcop_vmin(_VREG(19), _VREG(26), _VREG(19));
   __vcop_vmax(_VREG(18), _VREG(28), _VREG(18));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(32), _PREG(14), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(36), _PREG(16), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(31), _PREG(18), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(35), _PREG(20), _AGEN(2), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VK0", 38);
   #pragma VCC_VREG("VK1", 39);
   #pragma VCC_VREG("VKMinus1", 40);
   #pragma VCC_VREG("VLmbd1", 41);
   #pragma VCC_VREG("VLmbd2", 42);
   #pragma VCC_VREG("VLmbdFinal1", 43);
   #pragma VCC_VREG("VLmbdFinal2", 44);
   #pragma VCC_VREG("VMask", 45);
   #pragma VCC_VREG("VNeg1", 46);
   #pragma VCC_VREG("VNeg2", 47);
   #pragma VCC_VREG("VPos1", 48);
   #pragma VCC_VREG("VPos2", 49);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 25u, 9u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(16), _VREG(38));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(18), _VREG(39));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(8), _VREG(40));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vcmplt(_VREG(19), _VREG(38), _VREG(45));
   __vcop_vor(_VREG(40), _VREG(40), _VREG(46));
   __vcop_vsel(_VREG(45), _VREG(19), _VREG(46));
   __vcop_vcmplt(_VREG(18), _VREG(38), _VREG(45));
   __vcop_vor(_VREG(40), _VREG(40), _VREG(47));
   __vcop_vsel(_VREG(45), _VREG(18), _VREG(47));
   __vcop_vlmbd(_VREG(46), _VREG(38), _VREG(41));
   __vcop_vlmbd(_VREG(47), _VREG(38), _VREG(42));
   __vcop_vmax(_VREG(41), _VREG(42), _VREG(43));
   __vcop_vcmpge(_VREG(19), _VREG(38), _VREG(45));
   __vcop_vor(_VREG(38), _VREG(38), _VREG(48));
   __vcop_vsel(_VREG(45), _VREG(19), _VREG(48));
   __vcop_vcmpge(_VREG(18), _VREG(38), _VREG(45));
   __vcop_vor(_VREG(38), _VREG(38), _VREG(49));
   __vcop_vsel(_VREG(45), _VREG(18), _VREG(49));
   __vcop_vlmbd(_VREG(48), _VREG(39), _VREG(41));
   __vcop_vlmbd(_VREG(49), _VREG(39), _VREG(42));
   __vcop_vmax(_VREG(41), _VREG(42), _VREG(44));
   __vcop_vmax(_VREG(43), _VREG(44), _VREG(43));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(43), _PREG(10), _AGEN(0), _PREG(6));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VLmbd", 50);
   #pragma VCC_VREG("VNumValidBits", 51);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   #pragma EVE_REG("addrIn", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 11u, 9u, 3u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(16), _VREG(25));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(16), _VREG(23));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(18), _VREG(51));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeW(), __vcop_1pt(), _PREG(8), _AGEN(1), _VREG(50), __vcop_alws());
   __vcop_vmax(_VREG(50), _VREG(25), _VREG(25));
   __vcop_vsub(_VREG(25), _VREG(51), _VREG(22));
   __vcop_vmax(_VREG(23), _VREG(22), _VREG(22));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_1pt(), __vcop_alws(), _VREG(22), _PREG(10), _AGEN(0), _PREG(6));
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
   

   __vcop_vloop(__vcop_compute(), 11u, 7u, 4u);
   __vcop_vagen(_AGEN(1), _PREG(10), _PREG(10), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(11), _PREG(11), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(12), _AGEN(1), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(14), _AGEN(1), _VREG(17), __vcop_alws());
   __vcop_vor(_VREG(16), _VREG(16), _VREG(20));
   __vcop_vor(_VREG(17), _VREG(17), _VREG(21));
   __vcop_vintrlv(_VREG(20), _VREG(21));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(20), _PREG(6), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(21), _PREG(8), _AGEN(2), _PREG(0));
   __vcop_vloop_end(4u);

}

void vcop_fft_128_16ix32o_radix2_stage_4_overflow(
   __vptr_int32 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int32 pOutput,
   __vptr_uint8 pScaleFactor,
   unsigned char numValidBits,
   unsigned short numOfLines)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_128_16ix32o_radix2_stage_4_overflow_init(pInput, pScratch1, pScratch2, pOutput, pScaleFactor, numValidBits, numOfLines, __pblock_vcop_fft_128_16ix32o_radix2_stage_4_overflow);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_128_16ix32o_radix2_stage_4_overflow_vloops(__pblock_vcop_fft_128_16ix32o_radix2_stage_4_overflow);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_fft_128_16ix32o_radix2_stage_4_overflow_custom(
   __vptr_int32 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int32 pOutput,
   __vptr_uint8 pScaleFactor,
   unsigned char numValidBits,
   unsigned short numOfLines,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_128_16ix32o_radix2_stage_4_overflow_init(pInput, pScratch1, pScratch2, pOutput, pScaleFactor, numValidBits, numOfLines, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_128_16ix32o_radix2_stage_4_overflow_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_fft_128_16ix32o_radix2_stage_4, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_fft_128_16ix32o_radix2_stage_4, __ALIGNOF__(int));
unsigned short __pblock_vcop_fft_128_16ix32o_radix2_stage_4[38];

unsigned int vcop_fft_128_16ix32o_radix2_stage_4_param_count(void)
{
   return 38u;
}

unsigned int vcop_fft_128_16ix32o_radix2_stage_4_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_fft_128_16ix32o_radix2_stage_4_init(
   __vptr_int32 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int32 pOutput,
   unsigned short numOfLines,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (numOfLines)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (32 / (8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (2)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pInput+2*8u*sizeof(*pInput)*1*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pInput+128*sizeof(*pInput)+2*8u*sizeof(*pInput)*1*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pScratch1+2*8u*sizeof(*pScratch1)*4*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pScratch2+2*8u*sizeof(*pScratch1)*4*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pScratch1+2*8u*sizeof(*pScratch2)*4*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pScratch2+2*8u*sizeof(*pScratch2)*4*1);
   __vcop_pblock_init16(pblock, __offset+_PREG(18), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(19), 96);
   __vcop_pblock_init16(pblock, __offset+_PREG(20), 608);
   __vcop_pblock_init16(pblock, __offset+_PREG(21), 288);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)pInput+2*8u*sizeof(*pInput)*1*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)pInput+128*sizeof(*pInput)+2*8u*sizeof(*pInput)*1*0);
   __offset += 24;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (numOfLines)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((128)/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pOutput);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pOutput+8u*sizeof(*pOutput));
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), 64);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pScratch1);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pScratch2);
   __offset += 14;

   return 38u;
}

void vcop_fft_128_16ix32o_radix2_stage_4_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VInX", 16);
   #pragma VCC_VREG("VInY", 17);
   #pragma VCC_VREG("VOutX", 18);
   #pragma VCC_VREG("VOutY", 19);
   #pragma VCC_VREG("VTemp1", 20);
   #pragma VCC_VREG("VTemp2", 21);
   #pragma VCC_VREG("VTemp3", 22);
   #pragma VCC_VREG("VTemp4", 23);
   #pragma VCC_VREG("Vx0", 24);
   #pragma VCC_VREG("Vx0_minus_x1", 25);
   #pragma VCC_VREG("Vx0_plus_x1", 26);
   #pragma VCC_VREG("Vx1", 27);
   #pragma VCC_VREG("Vy0", 28);
   #pragma VCC_VREG("Vy0_minus_y1", 29);
   #pragma VCC_VREG("Vy0_plus_y1", 30);
   #pragma VCC_VREG("Vy1", 31);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   #pragma EVE_REG("addr_in", "A1");
   #pragma EVE_REG("addr_out", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("lineIdx", "I2");
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 18u, 12u, 1u);
   __vcop_vagen(_AGEN(1), _PREG(18), _PREG(19), _PREG(20), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(18), _PREG(18), _PREG(21), _PREG(0));
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(22), _AGEN(1), _VREG(24), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(24), _AGEN(1), _VREG(28), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(6), _AGEN(1), _VREG(27), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(8), _AGEN(1), _VREG(31), __vcop_alws());
   __vcop_vmove(_VREG(24), _VREG(26));
   __vcop_vmove(_VREG(27), _VREG(25));
   __vcop_vaddsub(_VREG(26), _VREG(25));
   __vcop_vmove(_VREG(28), _VREG(30));
   __vcop_vmove(_VREG(31), _VREG(29));
   __vcop_vaddsub(_VREG(30), _VREG(29));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(26), _PREG(10), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(30), _PREG(12), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(25), _PREG(14), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(29), _PREG(16), _AGEN(2), _PREG(0));
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
   

   __vcop_vloop(__vcop_compute(), 11u, 7u, 2u);
   __vcop_vagen(_AGEN(1), _PREG(10), _PREG(10), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(11), _PREG(11), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(12), _AGEN(1), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(14), _AGEN(1), _VREG(17), __vcop_alws());
   __vcop_vor(_VREG(16), _VREG(16), _VREG(18));
   __vcop_vor(_VREG(17), _VREG(17), _VREG(19));
   __vcop_vintrlv(_VREG(18), _VREG(19));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(18), _PREG(6), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(19), _PREG(8), _AGEN(2), _PREG(0));
   __vcop_vloop_end(2u);

}

void vcop_fft_128_16ix32o_radix2_stage_4(
   __vptr_int32 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int32 pOutput,
   unsigned short numOfLines)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_128_16ix32o_radix2_stage_4_init(pInput, pScratch1, pScratch2, pOutput, numOfLines, __pblock_vcop_fft_128_16ix32o_radix2_stage_4);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_128_16ix32o_radix2_stage_4_vloops(__pblock_vcop_fft_128_16ix32o_radix2_stage_4);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_fft_128_16ix32o_radix2_stage_4_custom(
   __vptr_int32 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int32 pOutput,
   unsigned short numOfLines,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_128_16ix32o_radix2_stage_4_init(pInput, pScratch1, pScratch2, pOutput, numOfLines, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_128_16ix32o_radix2_stage_4_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}
