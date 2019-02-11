#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_fft_256_16ix32o_stage_4_overflow, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_fft_256_16ix32o_stage_4_overflow, __ALIGNOF__(int));
unsigned short __pblock_vcop_fft_256_16ix32o_stage_4_overflow[96];

unsigned int vcop_fft_256_16ix32o_stage_4_overflow_param_count(void)
{
   return 96u;
}

unsigned int vcop_fft_256_16ix32o_stage_4_overflow_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_fft_256_16ix32o_stage_4_overflow_init(
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
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((256)/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pOutput);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pOutput+8u*sizeof(*pOutput));
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), 64);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pScratch1);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pScratch2);
   __offset += 14;

   return 96u;
}

void vcop_fft_256_16ix32o_stage_4_overflow_vloops(
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
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(16), _VREG(35));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(18), _VREG(68));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeW(), __vcop_1pt(), _PREG(8), _AGEN(1), _VREG(67), __vcop_alws());
   __vcop_vmax(_VREG(67), _VREG(38), _VREG(38));
   __vcop_vsub(_VREG(38), _VREG(68), _VREG(34));
   __vcop_vmax(_VREG(35), _VREG(34), _VREG(34));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_1pt(), __vcop_alws(), _VREG(34), _PREG(10), _AGEN(0), _PREG(6));
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
   __vcop_vor(_VREG(16), _VREG(16), _VREG(24));
   __vcop_vor(_VREG(17), _VREG(17), _VREG(29));
   __vcop_vintrlv(_VREG(24), _VREG(29));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(24), _PREG(6), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(29), _PREG(8), _AGEN(2), _PREG(0));
   __vcop_vloop_end(4u);

}

void vcop_fft_256_16ix32o_stage_4_overflow(
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
   vcop_fft_256_16ix32o_stage_4_overflow_init(pInput, pScratch1, pScratch2, pOutput, pScaleFactor, numValidBits, numOfLines, __pblock_vcop_fft_256_16ix32o_stage_4_overflow);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_256_16ix32o_stage_4_overflow_vloops(__pblock_vcop_fft_256_16ix32o_stage_4_overflow);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_fft_256_16ix32o_stage_4_overflow_custom(
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
   vcop_fft_256_16ix32o_stage_4_overflow_init(pInput, pScratch1, pScratch2, pOutput, pScaleFactor, numValidBits, numOfLines, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_256_16ix32o_stage_4_overflow_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_fft_256_16ix32o_stage_4, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_fft_256_16ix32o_stage_4, __ALIGNOF__(int));
unsigned short __pblock_vcop_fft_256_16ix32o_stage_4[56];

unsigned int vcop_fft_256_16ix32o_stage_4_param_count(void)
{
   return 56u;
}

unsigned int vcop_fft_256_16ix32o_stage_4_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_fft_256_16ix32o_stage_4_init(
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
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (numOfLines)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((256)/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pOutput);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pOutput+8u*sizeof(*pOutput));
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), 64);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pScratch1);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pScratch2);
   __offset += 14;

   return 56u;
}

void vcop_fft_256_16ix32o_stage_4_vloops(
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
   

   __vcop_vloop(__vcop_compute(), 11u, 7u, 2u);
   __vcop_vagen(_AGEN(1), _PREG(10), _PREG(10), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(11), _PREG(11), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(12), _AGEN(1), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(14), _AGEN(1), _VREG(17), __vcop_alws());
   __vcop_vor(_VREG(16), _VREG(16), _VREG(18));
   __vcop_vor(_VREG(17), _VREG(17), _VREG(23));
   __vcop_vintrlv(_VREG(18), _VREG(23));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(18), _PREG(6), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(23), _PREG(8), _AGEN(2), _PREG(0));
   __vcop_vloop_end(2u);

}

void vcop_fft_256_16ix32o_stage_4(
   __vptr_int32 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int32 pOutput,
   unsigned short numOfLines)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_256_16ix32o_stage_4_init(pInput, pScratch1, pScratch2, pOutput, numOfLines, __pblock_vcop_fft_256_16ix32o_stage_4);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_256_16ix32o_stage_4_vloops(__pblock_vcop_fft_256_16ix32o_stage_4);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_fft_256_16ix32o_stage_4_custom(
   __vptr_int32 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int32 pOutput,
   unsigned short numOfLines,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_256_16ix32o_stage_4_init(pInput, pScratch1, pScratch2, pOutput, numOfLines, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_256_16ix32o_stage_4_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}
