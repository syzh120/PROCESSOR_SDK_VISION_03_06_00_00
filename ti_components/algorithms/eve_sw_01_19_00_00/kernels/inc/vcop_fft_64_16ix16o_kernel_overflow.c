#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_fft_64_16ix16o_stage_1_overflow, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_fft_64_16ix16o_stage_1_overflow, __ALIGNOF__(int));
unsigned short __pblock_vcop_fft_64_16ix16o_stage_1_overflow[126];

unsigned int vcop_fft_64_16ix16o_stage_1_overflow_param_count(void)
{
   return 126u;
}

unsigned int vcop_fft_64_16ix16o_stage_1_overflow_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_fft_64_16ix16o_stage_1_overflow_init(
   __vptr_int16 pInput,
   __vptr_int32 pScratchH,
   __vptr_int32 pScratchWBuf,
   __vptr_int16 pOutput,
   __vptr_int16 pTwiddleFactor,
   __vptr_uint16 pScatterOffset,
   __vptr_uint8 pScaleFactor,
   unsigned char numValidBits,
   unsigned short pitch,
   unsigned short numOfLines,
   unsigned short saturationLimit,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   const int preg_ref1 = _PREG(22);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (numOfLines / (2))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((2))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((16)/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_ASYMM32,preg_ref1,RM_NONE,0));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), 4294967295);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), 0x8000000000);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pInput+16*sizeof(*pInput)*2*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pInput+16*sizeof(*pInput)*2*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pInput+16*sizeof(*pInput)*2*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pInput+16*sizeof(*pInput)*2*3);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pScratchWBuf+16*sizeof(*pScratchWBuf)*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), 2147483647);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)pScratchH+16*sizeof(*pScratchH)*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)pScratchWBuf+16*sizeof(*pScratchWBuf)*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)pScratchH+16*sizeof(*pScratchH)*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(30), (uchar *)pScratchWBuf+16*sizeof(*pScratchWBuf)*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(32), (uchar *)pScratchH+16*sizeof(*pScratchH)*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(34), (uchar *)pScratchWBuf+16*sizeof(*pScratchWBuf)*3);
   __vcop_pblock_init32(pblock, __offset+_PREG(36), (uchar *)pScratchH+16*sizeof(*pScratchH)*3);
   __vcop_pblock_init16(pblock, __offset+_PREG(38), (pitch) -(sizeof(*pInput)*2*8u)*(((16)/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(39), (pitch*2) -(pitch)*(((2))-1u) -(sizeof(*pInput)*2*8u)*(((16)/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(40), (pitch) -(sizeof(*pScratchH)*8u)*(((16)/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(41), (pitch*2) -(pitch)*(((2))-1u) -(sizeof(*pScratchH)*8u)*(((16)/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(42), 1);
   __vcop_pblock_init32(pblock, __offset+_PREG(44), (uchar *)pScatterOffset);
   __offset += 44;

   /* Loop 2 PREGS */
   const int preg_ref2 = _PREG(12);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_4PARAM,preg_ref2,RM_NONE,0));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), -1);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pOutput);
   __vcop_pblock_4param_init(pblock, __offset+_PREG(12), 40,40,0,0);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), 1);
   __offset += 18;

   /* Loop 3 PREGS */
   const int preg_ref3 = _PREG(14);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_4PARAM,preg_ref3,RM_NONE,0));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 2);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), -1);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), numValidBits - 2);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pOutput);
   __vcop_pblock_4param_init(pblock, __offset+_PREG(14), 40,40,0,0);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pScaleFactor);
   __offset += 20;

   /* Loop 4 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (numOfLines / (2))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((2))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((16)/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pOutput+1*sizeof(*pOutput)*2*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pOutput+1*sizeof(*pOutput)*2*0+sizeof(*pOutput));
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), (pitch) -(8u*sizeof(*pScratchH))*(((16)/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), (pitch*2) -(pitch)*(((2))-1u) -(8u*sizeof(*pScratchH))*(((16)/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(13), 288);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), -272);
   __vcop_pblock_init16(pblock, __offset+_PREG(15), 272);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pScratchWBuf+16*sizeof(*pScratchWBuf)*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pScratchH+16*sizeof(*pScratchH)*0);
   __offset += 18;

   /* Loop 5 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), (numOfLines / (2))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), ((2))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((16)/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (3)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_ROUND,15));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 64);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pScratchH+16*sizeof(*pScratchH));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pOutput+1*sizeof(*pOutput)*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pOutput+1*sizeof(*pOutput)*2+sizeof(*pOutput));
   __vcop_pblock_init16(pblock, __offset+_PREG(14), -96);
   __vcop_pblock_init16(pblock, __offset+_PREG(15), (pitch) -(8u*sizeof(*pScratchWBuf))*(((16)/(8u))-1u) -(16*sizeof(*pScratchWBuf))*((3)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(16), (pitch*2) -(pitch)*(((2))-1u) -(8u*sizeof(*pScratchWBuf))*(((16)/(8u))-1u) -(16*sizeof(*pScratchWBuf))*((3)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(17), 4);
   __vcop_pblock_init16(pblock, __offset+_PREG(18), 280);
   __vcop_pblock_init16(pblock, __offset+_PREG(19), -280);
   __vcop_pblock_init16(pblock, __offset+_PREG(20), 264);
   __vcop_pblock_init16(pblock, __offset+_PREG(21), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(22), -160);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)pTwiddleFactor+8*sizeof(*pTwiddleFactor)*2*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)pScratchWBuf+16*sizeof(*pScratchWBuf));
   __offset += 26;

   return 126u;
}

void vcop_fft_64_16ix16o_stage_1_overflow_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VCond", 16);
   #pragma VCC_VREG("VCos", 17);
   #pragma VCC_VREG("VInX", 18);
   #pragma VCC_VREG("VInY", 19);
   #pragma VCC_VREG("VInterim1", 20);
   #pragma VCC_VREG("VInterim2", 21);
   #pragma VCC_VREG("VInterim3", 22);
   #pragma VCC_VREG("VInterim4", 23);
   #pragma VCC_VREG("VMax", 24);
   #pragma VCC_VREG("VMin", 25);
   #pragma VCC_VREG("VOutX", 26);
   #pragma VCC_VREG("VOutX0", 27);
   #pragma VCC_VREG("VOutX1", 28);
   #pragma VCC_VREG("VOutX2", 29);
   #pragma VCC_VREG("VOutX3", 30);
   #pragma VCC_VREG("VOutY", 31);
   #pragma VCC_VREG("VOutY0", 32);
   #pragma VCC_VREG("VOutY1", 33);
   #pragma VCC_VREG("VOutY2", 34);
   #pragma VCC_VREG("VOutY3", 35);
   #pragma VCC_VREG("VScaleIn", 36);
   #pragma VCC_VREG("VScaleMinus", 37);
   #pragma VCC_VREG("VScatterOffset", 38);
   #pragma VCC_VREG("VSin", 39);
   #pragma VCC_VREG("VTemp", 40);
   #pragma VCC_VREG("VX0", 41);
   #pragma VCC_VREG("VX0_minus_X2", 42);
   #pragma VCC_VREG("VX0_plus_X2", 43);
   #pragma VCC_VREG("VX1", 44);
   #pragma VCC_VREG("VX1_minus_X3", 45);
   #pragma VCC_VREG("VX1_plus_X3", 46);
   #pragma VCC_VREG("VX2", 47);
   #pragma VCC_VREG("VX3", 48);
   #pragma VCC_VREG("VY0", 49);
   #pragma VCC_VREG("VY0_minus_Y2", 50);
   #pragma VCC_VREG("VY0_plus_Y2", 51);
   #pragma VCC_VREG("VY1", 52);
   #pragma VCC_VREG("VY1_minus_Y3", 53);
   #pragma VCC_VREG("VY1_plus_Y3", 54);
   #pragma VCC_VREG("VY2", 55);
   #pragma VCC_VREG("VY3", 56);

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
   

   __vcop_vloop(__vcop_compute(), 60u, 22u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(42), _VREG(16));
   __vcop_vinit(__vcop_sizeWU(), __vcop_once(), _PREG(8), _VREG(25));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(10), _VREG(24));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(38), _PREG(39), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(7), _PREG(40), _PREG(41), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(44), _AGEN(0), _VREG(38), __vcop_once());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(12), _AGEN(1), _VPAIR(41,49), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(14), _AGEN(1), _VPAIR(44,52), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(16), _AGEN(1), _VPAIR(47,55), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(18), _AGEN(1), _VPAIR(48,56), __vcop_alws());
   __vcop_vmove(_VREG(41), _VREG(43));
   __vcop_vmove(_VREG(47), _VREG(42));
   __vcop_vaddsub(_VREG(43), _VREG(42));
   __vcop_vmove(_VREG(44), _VREG(46));
   __vcop_vmove(_VREG(48), _VREG(45));
   __vcop_vaddsub(_VREG(46), _VREG(45));
   __vcop_vmove(_VREG(49), _VREG(51));
   __vcop_vmove(_VREG(55), _VREG(50));
   __vcop_vaddsub(_VREG(51), _VREG(50));
   __vcop_vmove(_VREG(52), _VREG(54));
   __vcop_vmove(_VREG(56), _VREG(53));
   __vcop_vaddsub(_VREG(54), _VREG(53));
   __vcop_vmove(_VREG(43), _VREG(27));
   __vcop_vmove(_VREG(46), _VREG(29));
   __vcop_vaddsub(_VREG(27), _VREG(29));
   __vcop_vmove(_VREG(42), _VREG(28));
   __vcop_vmove(_VREG(53), _VREG(30));
   __vcop_vaddsub(_VREG(28), _VREG(30));
   __vcop_vmove(_VREG(51), _VREG(32));
   __vcop_vmove(_VREG(54), _VREG(34));
   __vcop_vaddsub(_VREG(32), _VREG(34));
   __vcop_vmove(_VREG(50), _VREG(35));
   __vcop_vmove(_VREG(45), _VREG(33));
   __vcop_vaddsub(_VREG(35), _VREG(33));
   __vcop_vmin(_VREG(27), _VREG(29), _VREG(20));
   __vcop_vmax(_VREG(27), _VREG(29), _VREG(21));
   __vcop_vmin(_VREG(28), _VREG(30), _VREG(22));
   __vcop_vmax(_VREG(28), _VREG(30), _VREG(23));
   __vcop_vmin(_VREG(20), _VREG(22), _VREG(20));
   __vcop_vmax(_VREG(21), _VREG(23), _VREG(21));
   __vcop_vmin(_VREG(32), _VREG(34), _VREG(22));
   __vcop_vmax(_VREG(32), _VREG(34), _VREG(23));
   __vcop_vmin(_VREG(20), _VREG(22), _VREG(20));
   __vcop_vmax(_VREG(21), _VREG(23), _VREG(21));
   __vcop_vmin(_VREG(35), _VREG(33), _VREG(22));
   __vcop_vmax(_VREG(35), _VREG(33), _VREG(23));
   __vcop_vmin(_VREG(20), _VREG(22), _VREG(20));
   __vcop_vmax(_VREG(21), _VREG(23), _VREG(21));
   __vcop_vmin(_VREG(25), _VREG(20), _VREG(25));
   __vcop_vmax(_VREG(24), _VREG(21), _VREG(24));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(27), _PREG(20), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(32), _PREG(24), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(28), _PREG(26), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(33), _PREG(28), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(29), _PREG(30), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(34), _PREG(32), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(30), _PREG(34), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(35), _PREG(36), _AGEN(2), _PREG(6));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VK0", 57);
   #pragma VCC_VREG("VK1", 58);
   #pragma VCC_VREG("VKMinus1", 59);
   #pragma VCC_VREG("VLmbd1", 60);
   #pragma VCC_VREG("VLmbd2", 61);
   #pragma VCC_VREG("VLmbdFinal1", 62);
   #pragma VCC_VREG("VLmbdFinal2", 63);
   #pragma VCC_VREG("VMask", 64);
   #pragma VCC_VREG("VNeg1", 65);
   #pragma VCC_VREG("VNeg2", 66);
   #pragma VCC_VREG("VPos1", 67);
   #pragma VCC_VREG("VPos2", 68);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 25u, 9u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(16), _VREG(57));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(18), _VREG(58));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(8), _VREG(59));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vcmplt(_VREG(25), _VREG(57), _VREG(64));
   __vcop_vor(_VREG(59), _VREG(59), _VREG(65));
   __vcop_vsel(_VREG(64), _VREG(25), _VREG(65));
   __vcop_vcmplt(_VREG(24), _VREG(57), _VREG(64));
   __vcop_vor(_VREG(59), _VREG(59), _VREG(66));
   __vcop_vsel(_VREG(64), _VREG(24), _VREG(66));
   __vcop_vlmbd(_VREG(65), _VREG(57), _VREG(60));
   __vcop_vlmbd(_VREG(66), _VREG(57), _VREG(61));
   __vcop_vmax(_VREG(60), _VREG(61), _VREG(62));
   __vcop_vcmpge(_VREG(25), _VREG(57), _VREG(64));
   __vcop_vor(_VREG(57), _VREG(57), _VREG(67));
   __vcop_vsel(_VREG(64), _VREG(25), _VREG(67));
   __vcop_vcmpge(_VREG(24), _VREG(57), _VREG(64));
   __vcop_vor(_VREG(57), _VREG(57), _VREG(68));
   __vcop_vsel(_VREG(64), _VREG(24), _VREG(68));
   __vcop_vlmbd(_VREG(67), _VREG(58), _VREG(60));
   __vcop_vlmbd(_VREG(68), _VREG(58), _VREG(61));
   __vcop_vmax(_VREG(60), _VREG(61), _VREG(63));
   __vcop_vmax(_VREG(62), _VREG(63), _VREG(62));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_npt(), __vcop_alws(), _VREG(62), _PREG(10), _AGEN(0), _PREG(6));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VKMinus1", 69);
   #pragma VCC_VREG("VLmbd", 70);
   #pragma VCC_VREG("VNumValidBits", 71);
   #pragma VCC_VREG("VScale", 72);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   #pragma EVE_REG("addrIn", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 13u, 10u, 3u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(18), _VREG(40));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(8), _VREG(69));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(10), _VREG(71));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_1pt(), _PREG(20), _AGEN(0), _VREG(36), __vcop_once());
   __vcop_vload(__vcop_sizeH(), __vcop_1pt(), _PREG(12), _AGEN(1), _VREG(70), __vcop_alws());
   __vcop_vmax(_VREG(70), _VREG(40), _VREG(40));
   __vcop_vsub(_VREG(40), _VREG(71), _VREG(72));
   __vcop_vmax(_VREG(36), _VREG(72), _VREG(72));
   __vcop_vmpy(_VREG(72), _VREG(69), _VREG(37), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_1pt(), __vcop_alws(), _VREG(72), _PREG(20), _AGEN(0), _PREG(6));
   __vcop_vloop_end(3u);

   /* VLOOP 4 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   #pragma EVE_REG("Addr_in", "A1");
   #pragma EVE_REG("Addr_out", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("lineIdx", "I2");
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 10u, 9u, 4u);
   __vcop_vagen(_AGEN(1), _PREG(10), _PREG(11), _PREG(12), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(13), _PREG(14), _PREG(15), _PREG(0));
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(16), _AGEN(1), _VREG(18), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(18), _AGEN(1), _VREG(19), __vcop_alws());
   __vcop_vshf(_VREG(18), _VREG(37), _VREG(18));
   __vcop_vshf(_VREG(19), _VREG(37), _VREG(19));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_pdda(_VREG(38)), __vcop_alws(), _VREG(18), _PREG(6), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_pdda(_VREG(38)), __vcop_alws(), _VREG(19), _PREG(8), _AGEN(2), _PREG(0));
   __vcop_vloop_end(4u);

   /* VLOOP 5 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   #pragma EVE_REG("Addr_in", "A1");
   #pragma EVE_REG("Addr_out", "A2");
   #pragma EVE_REG("Addr_tw", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("lineIdx", "I1");
   #pragma EVE_REG("I3", "I2");
   #pragma EVE_REG("I4", "I3");
   #pragma EVE_REG("twIdx", "I4");
   

   __vcop_vloop(__vcop_compute(), 16u, 13u, 5u);
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(14), _PREG(15), _PREG(16));
   __vcop_vagen(_AGEN(2), _PREG(17), _PREG(18), _PREG(19), _PREG(20));
   __vcop_vagen(_AGEN(3), _PREG(21), _PREG(21), _PREG(22), _PREG(22));
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(24), _AGEN(3), _VPAIR(39,17), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(26), _AGEN(1), _VREG(18), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(8), _AGEN(1), _VREG(19), __vcop_alws());
   __vcop_vshf(_VREG(18), _VREG(37), _VREG(18));
   __vcop_vshf(_VREG(19), _VREG(37), _VREG(19));
   __vcop_vmpy(_VREG(18), _VREG(17), _VREG(26), _PREG(0));
   __vcop_vmpy(_VREG(19), _VREG(17), _VREG(31), _PREG(0));
   __vcop_vmadd(_VREG(19), _VREG(39), _VREG(26), _PREG(0));
   __vcop_vmsub(_VREG(18), _VREG(39), _VREG(31), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_pdda(_VREG(38)), __vcop_alws(), _VREG(26), _PREG(10), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_pdda(_VREG(38)), __vcop_alws(), _VREG(31), _PREG(12), _AGEN(2), _PREG(6));
   __vcop_vloop_end(5u);

}

void vcop_fft_64_16ix16o_stage_1_overflow(
   __vptr_int16 pInput,
   __vptr_int32 pScratchH,
   __vptr_int32 pScratchWBuf,
   __vptr_int16 pOutput,
   __vptr_int16 pTwiddleFactor,
   __vptr_uint16 pScatterOffset,
   __vptr_uint8 pScaleFactor,
   unsigned char numValidBits,
   unsigned short pitch,
   unsigned short numOfLines,
   unsigned short saturationLimit)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_64_16ix16o_stage_1_overflow_init(pInput, pScratchH, pScratchWBuf, pOutput, pTwiddleFactor, pScatterOffset, pScaleFactor, numValidBits, pitch, numOfLines, saturationLimit, __pblock_vcop_fft_64_16ix16o_stage_1_overflow);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_64_16ix16o_stage_1_overflow_vloops(__pblock_vcop_fft_64_16ix16o_stage_1_overflow);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_fft_64_16ix16o_stage_1_overflow_custom(
   __vptr_int16 pInput,
   __vptr_int32 pScratchH,
   __vptr_int32 pScratchWBuf,
   __vptr_int16 pOutput,
   __vptr_int16 pTwiddleFactor,
   __vptr_uint16 pScatterOffset,
   __vptr_uint8 pScaleFactor,
   unsigned char numValidBits,
   unsigned short pitch,
   unsigned short numOfLines,
   unsigned short saturationLimit,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_64_16ix16o_stage_1_overflow_init(pInput, pScratchH, pScratchWBuf, pOutput, pTwiddleFactor, pScatterOffset, pScaleFactor, numValidBits, pitch, numOfLines, saturationLimit, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_64_16ix16o_stage_1_overflow_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_fft_64_16ix16o_stage_2_overflow, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_fft_64_16ix16o_stage_2_overflow, __ALIGNOF__(int));
unsigned short __pblock_vcop_fft_64_16ix16o_stage_2_overflow[116];

unsigned int vcop_fft_64_16ix16o_stage_2_overflow_param_count(void)
{
   return 116u;
}

unsigned int vcop_fft_64_16ix16o_stage_2_overflow_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_fft_64_16ix16o_stage_2_overflow_init(
   __vptr_int16 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int16 pOutput,
   __vptr_int16 pTwiddleFactor,
   __vptr_uint16 pScatterOffset,
   __vptr_uint8 pScaleFactor,
   __vptr_int16 pInterimBuf,
   unsigned char numValidBits,
   unsigned short numOfLines,
   unsigned short saturationLimit,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (numOfLines / (2))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((4))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), 0x8000000000);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pScatterOffset);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pInput+4*((8u+1)*4)*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pInput+4*((8u+1)*4)*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pInput+4*((8u+1)*4)*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pInput+4*((8u+1)*4)*3);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pScratch1+4*((8u+1)*4)*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pScratch2+4*((8u+1)*4)*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)pScratch1+4*((8u+1)*4)*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)pScratch2+4*((8u+1)*4)*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)pScratch1+4*((8u+1)*4)*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)pScratch2+4*((8u+1)*4)*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(30), (uchar *)pScratch1+4*((8u+1)*4)*3);
   __vcop_pblock_init32(pblock, __offset+_PREG(32), (uchar *)pScratch2+4*((8u+1)*4)*3);
   __vcop_pblock_init16(pblock, __offset+_PREG(34), 36);
   __vcop_pblock_init16(pblock, __offset+_PREG(35), 468);
   __vcop_pblock_init16(pblock, __offset+_PREG(36), 64);
   __vcop_pblock_init16(pblock, __offset+_PREG(37), 352);
   __vcop_pblock_init32(pblock, __offset+_PREG(38), 1);
   __vcop_pblock_init32(pblock, __offset+_PREG(40), 4294967295);
   __offset += 40;

   /* Loop 2 PREGS */
   const int preg_ref4 = _PREG(12);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_4PARAM,preg_ref4,RM_NONE,0));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), -1);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pInterimBuf);
   __vcop_pblock_4param_init(pblock, __offset+_PREG(12), 40,40,0,0);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), 1);
   __offset += 18;

   /* Loop 3 PREGS */
   const int preg_ref5 = _PREG(14);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_4PARAM,preg_ref5,RM_NONE,0));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 2);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), -1);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), numValidBits - 2);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pInterimBuf);
   __vcop_pblock_4param_init(pblock, __offset+_PREG(14), 40,40,0,0);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pScaleFactor);
   __offset += 20;

   /* Loop 4 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (numOfLines / (2))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((4))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pOutput);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pOutput+sizeof(*pOutput));
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 36);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), 468);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), 64);
   __vcop_pblock_init16(pblock, __offset+_PREG(13), 352);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pScratch1);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pScratch2);
   __offset += 16;

   /* Loop 5 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (numOfLines / (2))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((4))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (3)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_ROUND,15));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 144);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pScratch2+4*((8u+1)*4));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pOutput+4*sizeof(*pOutput)*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pOutput+4*sizeof(*pOutput)*2+sizeof(*pOutput));
   __vcop_pblock_init16(pblock, __offset+_PREG(14), -252);
   __vcop_pblock_init16(pblock, __offset+_PREG(15), 180);
   __vcop_pblock_init16(pblock, __offset+_PREG(16), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(17), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(18), 320);
   __vcop_pblock_init16(pblock, __offset+_PREG(19), -352);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pTwiddleFactor+8*sizeof(*pTwiddleFactor)*2*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)pScratch1+4*((8u+1)*4));
   __offset += 22;

   return 116u;
}

void vcop_fft_64_16ix16o_stage_2_overflow_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VCond", 16);
   #pragma VCC_VREG("VCos", 17);
   #pragma VCC_VREG("VInX", 18);
   #pragma VCC_VREG("VInY", 19);
   #pragma VCC_VREG("VInterim1", 20);
   #pragma VCC_VREG("VInterim2", 21);
   #pragma VCC_VREG("VInterim3", 22);
   #pragma VCC_VREG("VInterim4", 23);
   #pragma VCC_VREG("VMax", 24);
   #pragma VCC_VREG("VMin", 25);
   #pragma VCC_VREG("VOutX", 26);
   #pragma VCC_VREG("VOutX0", 27);
   #pragma VCC_VREG("VOutX1", 28);
   #pragma VCC_VREG("VOutX2", 29);
   #pragma VCC_VREG("VOutX3", 30);
   #pragma VCC_VREG("VOutY", 31);
   #pragma VCC_VREG("VOutY0", 32);
   #pragma VCC_VREG("VOutY1", 33);
   #pragma VCC_VREG("VOutY2", 34);
   #pragma VCC_VREG("VOutY3", 35);
   #pragma VCC_VREG("VScaleIn", 36);
   #pragma VCC_VREG("VScaleMinus", 37);
   #pragma VCC_VREG("VScatterOffset", 38);
   #pragma VCC_VREG("VSin", 39);
   #pragma VCC_VREG("VTemp", 40);
   #pragma VCC_VREG("VX0", 41);
   #pragma VCC_VREG("VX0_minus_X2", 42);
   #pragma VCC_VREG("VX0_plus_X2", 43);
   #pragma VCC_VREG("VX1", 44);
   #pragma VCC_VREG("VX1_minus_X3", 45);
   #pragma VCC_VREG("VX1_plus_X3", 46);
   #pragma VCC_VREG("VX2", 47);
   #pragma VCC_VREG("VX3", 48);
   #pragma VCC_VREG("VY0", 49);
   #pragma VCC_VREG("VY0_minus_Y2", 50);
   #pragma VCC_VREG("VY0_plus_Y2", 51);
   #pragma VCC_VREG("VY1", 52);
   #pragma VCC_VREG("VY1_minus_Y3", 53);
   #pragma VCC_VREG("VY1_plus_Y3", 54);
   #pragma VCC_VREG("VY2", 55);
   #pragma VCC_VREG("VY3", 56);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   #pragma EVE_REG("Addr_in", "A1");
   #pragma EVE_REG("Addr_out", "A2");
   #pragma EVE_REG("Addr_pscatter", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("lineIdx", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 61u, 20u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(38), _VREG(16));
   __vcop_vinit(__vcop_sizeWU(), __vcop_once(), _PREG(40), _VREG(25));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(6), _VREG(24));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(34), _PREG(35), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(34), _PREG(35), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(8), _AGEN(0), _VREG(38), __vcop_once());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(10), _AGEN(1), _VPAIR(41,49), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(12), _AGEN(1), _VPAIR(44,52), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(14), _AGEN(1), _VPAIR(47,55), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(16), _AGEN(1), _VPAIR(48,56), __vcop_alws());
   __vcop_vmove(_VREG(41), _VREG(43));
   __vcop_vmove(_VREG(47), _VREG(42));
   __vcop_vaddsub(_VREG(43), _VREG(42));
   __vcop_vmove(_VREG(44), _VREG(46));
   __vcop_vmove(_VREG(48), _VREG(45));
   __vcop_vaddsub(_VREG(46), _VREG(45));
   __vcop_vmove(_VREG(49), _VREG(51));
   __vcop_vmove(_VREG(55), _VREG(50));
   __vcop_vaddsub(_VREG(51), _VREG(50));
   __vcop_vmove(_VREG(52), _VREG(54));
   __vcop_vmove(_VREG(56), _VREG(53));
   __vcop_vaddsub(_VREG(54), _VREG(53));
   __vcop_vmove(_VREG(43), _VREG(27));
   __vcop_vmove(_VREG(46), _VREG(29));
   __vcop_vaddsub(_VREG(27), _VREG(29));
   __vcop_vmove(_VREG(42), _VREG(28));
   __vcop_vmove(_VREG(53), _VREG(30));
   __vcop_vaddsub(_VREG(28), _VREG(30));
   __vcop_vmove(_VREG(51), _VREG(32));
   __vcop_vmove(_VREG(54), _VREG(34));
   __vcop_vaddsub(_VREG(32), _VREG(34));
   __vcop_vmove(_VREG(50), _VREG(35));
   __vcop_vmove(_VREG(45), _VREG(33));
   __vcop_vaddsub(_VREG(35), _VREG(33));
   __vcop_vmin(_VREG(27), _VREG(29), _VREG(20));
   __vcop_vmax(_VREG(27), _VREG(29), _VREG(21));
   __vcop_vmin(_VREG(28), _VREG(30), _VREG(22));
   __vcop_vmax(_VREG(28), _VREG(30), _VREG(23));
   __vcop_vmin(_VREG(20), _VREG(22), _VREG(20));
   __vcop_vmax(_VREG(21), _VREG(23), _VREG(21));
   __vcop_vmin(_VREG(32), _VREG(34), _VREG(22));
   __vcop_vmax(_VREG(32), _VREG(34), _VREG(23));
   __vcop_vmin(_VREG(20), _VREG(22), _VREG(20));
   __vcop_vmax(_VREG(21), _VREG(23), _VREG(21));
   __vcop_vmin(_VREG(35), _VREG(33), _VREG(22));
   __vcop_vmax(_VREG(35), _VREG(33), _VREG(23));
   __vcop_vmin(_VREG(20), _VREG(22), _VREG(20));
   __vcop_vmax(_VREG(21), _VREG(23), _VREG(21));
   __vcop_vmin(_VREG(25), _VREG(20), _VREG(25));
   __vcop_vmax(_VREG(24), _VREG(21), _VREG(24));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(27), _PREG(18), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(32), _PREG(20), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(28), _PREG(22), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(33), _PREG(24), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(29), _PREG(26), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(34), _PREG(28), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(30), _PREG(30), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(35), _PREG(32), _AGEN(2), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VK0", 57);
   #pragma VCC_VREG("VK1", 58);
   #pragma VCC_VREG("VKMinus1", 59);
   #pragma VCC_VREG("VLmbd1", 60);
   #pragma VCC_VREG("VLmbd2", 61);
   #pragma VCC_VREG("VLmbdFinal1", 62);
   #pragma VCC_VREG("VLmbdFinal2", 63);
   #pragma VCC_VREG("VMask", 64);
   #pragma VCC_VREG("VNeg1", 65);
   #pragma VCC_VREG("VNeg2", 66);
   #pragma VCC_VREG("VPos1", 67);
   #pragma VCC_VREG("VPos2", 68);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 25u, 9u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(16), _VREG(57));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(18), _VREG(58));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(8), _VREG(59));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vcmplt(_VREG(25), _VREG(57), _VREG(64));
   __vcop_vor(_VREG(59), _VREG(59), _VREG(65));
   __vcop_vsel(_VREG(64), _VREG(25), _VREG(65));
   __vcop_vcmplt(_VREG(24), _VREG(57), _VREG(64));
   __vcop_vor(_VREG(59), _VREG(59), _VREG(66));
   __vcop_vsel(_VREG(64), _VREG(24), _VREG(66));
   __vcop_vlmbd(_VREG(65), _VREG(57), _VREG(60));
   __vcop_vlmbd(_VREG(66), _VREG(57), _VREG(61));
   __vcop_vmax(_VREG(60), _VREG(61), _VREG(62));
   __vcop_vcmpge(_VREG(25), _VREG(57), _VREG(64));
   __vcop_vor(_VREG(57), _VREG(57), _VREG(67));
   __vcop_vsel(_VREG(64), _VREG(25), _VREG(67));
   __vcop_vcmpge(_VREG(24), _VREG(57), _VREG(64));
   __vcop_vor(_VREG(57), _VREG(57), _VREG(68));
   __vcop_vsel(_VREG(64), _VREG(24), _VREG(68));
   __vcop_vlmbd(_VREG(67), _VREG(58), _VREG(60));
   __vcop_vlmbd(_VREG(68), _VREG(58), _VREG(61));
   __vcop_vmax(_VREG(60), _VREG(61), _VREG(63));
   __vcop_vmax(_VREG(62), _VREG(63), _VREG(62));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_npt(), __vcop_alws(), _VREG(62), _PREG(10), _AGEN(0), _PREG(6));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VKMinus1", 69);
   #pragma VCC_VREG("VLmbd", 70);
   #pragma VCC_VREG("VNumValidBits", 71);
   #pragma VCC_VREG("VScale", 72);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   #pragma EVE_REG("addrIn", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 13u, 10u, 3u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(18), _VREG(40));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(8), _VREG(69));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(10), _VREG(71));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_1pt(), _PREG(20), _AGEN(0), _VREG(36), __vcop_once());
   __vcop_vload(__vcop_sizeH(), __vcop_1pt(), _PREG(12), _AGEN(1), _VREG(70), __vcop_alws());
   __vcop_vmax(_VREG(70), _VREG(40), _VREG(40));
   __vcop_vsub(_VREG(40), _VREG(71), _VREG(72));
   __vcop_vmax(_VREG(36), _VREG(72), _VREG(72));
   __vcop_vmpy(_VREG(72), _VREG(69), _VREG(37), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_1pt(), __vcop_alws(), _VREG(72), _PREG(20), _AGEN(0), _PREG(6));
   __vcop_vloop_end(3u);

   /* VLOOP 4 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   #pragma EVE_REG("Addr_in", "A1");
   #pragma EVE_REG("Addr_out", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("lineIdx", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 10u, 8u, 4u);
   __vcop_vagen(_AGEN(1), _PREG(10), _PREG(11), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(12), _PREG(13), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(14), _AGEN(1), _VREG(18), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(16), _AGEN(1), _VREG(19), __vcop_alws());
   __vcop_vshf(_VREG(18), _VREG(37), _VREG(18));
   __vcop_vshf(_VREG(19), _VREG(37), _VREG(19));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_pdda(_VREG(38)), __vcop_alws(), _VREG(18), _PREG(6), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_pdda(_VREG(38)), __vcop_alws(), _VREG(19), _PREG(8), _AGEN(2), _PREG(0));
   __vcop_vloop_end(4u);

   /* VLOOP 5 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   #pragma EVE_REG("Addr_in", "A1");
   #pragma EVE_REG("Addr_out", "A2");
   #pragma EVE_REG("Addr_tw", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("lineIdx", "I2");
   #pragma EVE_REG("I4", "I3");
   #pragma EVE_REG("twIdx", "I4");
   

   __vcop_vloop(__vcop_compute(), 16u, 11u, 5u);
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(14), _PREG(15), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(16), _PREG(17), _PREG(18), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(17), _PREG(17), _PREG(19), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(20), _AGEN(3), _VPAIR(39,17), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(22), _AGEN(1), _VREG(18), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(8), _AGEN(1), _VREG(19), __vcop_alws());
   __vcop_vshf(_VREG(18), _VREG(37), _VREG(18));
   __vcop_vshf(_VREG(19), _VREG(37), _VREG(19));
   __vcop_vmpy(_VREG(18), _VREG(17), _VREG(26), _PREG(0));
   __vcop_vmpy(_VREG(19), _VREG(17), _VREG(31), _PREG(0));
   __vcop_vmadd(_VREG(19), _VREG(39), _VREG(26), _PREG(0));
   __vcop_vmsub(_VREG(18), _VREG(39), _VREG(31), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_pdda(_VREG(38)), __vcop_alws(), _VREG(26), _PREG(10), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_pdda(_VREG(38)), __vcop_alws(), _VREG(31), _PREG(12), _AGEN(2), _PREG(6));
   __vcop_vloop_end(5u);

}

void vcop_fft_64_16ix16o_stage_2_overflow(
   __vptr_int16 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int16 pOutput,
   __vptr_int16 pTwiddleFactor,
   __vptr_uint16 pScatterOffset,
   __vptr_uint8 pScaleFactor,
   __vptr_int16 pInterimBuf,
   unsigned char numValidBits,
   unsigned short numOfLines,
   unsigned short saturationLimit)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_64_16ix16o_stage_2_overflow_init(pInput, pScratch1, pScratch2, pOutput, pTwiddleFactor, pScatterOffset, pScaleFactor, pInterimBuf, numValidBits, numOfLines, saturationLimit, __pblock_vcop_fft_64_16ix16o_stage_2_overflow);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_64_16ix16o_stage_2_overflow_vloops(__pblock_vcop_fft_64_16ix16o_stage_2_overflow);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_fft_64_16ix16o_stage_2_overflow_custom(
   __vptr_int16 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int16 pOutput,
   __vptr_int16 pTwiddleFactor,
   __vptr_uint16 pScatterOffset,
   __vptr_uint8 pScaleFactor,
   __vptr_int16 pInterimBuf,
   unsigned char numValidBits,
   unsigned short numOfLines,
   unsigned short saturationLimit,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_64_16ix16o_stage_2_overflow_init(pInput, pScratch1, pScratch2, pOutput, pTwiddleFactor, pScatterOffset, pScaleFactor, pInterimBuf, numValidBits, numOfLines, saturationLimit, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_64_16ix16o_stage_2_overflow_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_fft_64_16ix16o_stage_3_overflow, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_fft_64_16ix16o_stage_3_overflow, __ALIGNOF__(int));
unsigned short __pblock_vcop_fft_64_16ix16o_stage_3_overflow[86];

unsigned int vcop_fft_64_16ix16o_stage_3_overflow_param_count(void)
{
   return 86u;
}

unsigned int vcop_fft_64_16ix16o_stage_3_overflow_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_fft_64_16ix16o_stage_3_overflow_init(
   __vptr_int16 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int16 pOutput,
   __vptr_uint8 pScaleFactor,
   __vptr_int16 pInterimBuf,
   unsigned char numValidBits,
   unsigned short numOfLines,
   unsigned short saturationLimit,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (numOfLines)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((16) / (8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), 0x8000000000);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pInput+16*sizeof(*pInput)*2*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pInput+16*sizeof(*pInput)*2*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pInput+16*sizeof(*pInput)*2*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pInput+16*sizeof(*pInput)*2*3);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pScratch1+16*sizeof(*pScratch1)*1*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pScratch2+16*sizeof(*pScratch2)*1*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pScratch1+16*sizeof(*pScratch1)*1*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)pScratch2+16*sizeof(*pScratch2)*1*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)pScratch1+16*sizeof(*pScratch1)*1*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)pScratch2+16*sizeof(*pScratch2)*1*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)pScratch1+16*sizeof(*pScratch1)*1*3);
   __vcop_pblock_init32(pblock, __offset+_PREG(30), (uchar *)pScratch2+16*sizeof(*pScratch2)*1*3);
   __vcop_pblock_init16(pblock, __offset+_PREG(32), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(33), 240);
   __vcop_pblock_init32(pblock, __offset+_PREG(34), 1);
   __vcop_pblock_init32(pblock, __offset+_PREG(36), 4294967295);
   __offset += 36;

   /* Loop 2 PREGS */
   const int preg_ref6 = _PREG(12);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_4PARAM,preg_ref6,RM_NONE,0));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), -1);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pInterimBuf);
   __vcop_pblock_4param_init(pblock, __offset+_PREG(12), 40,40,0,0);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), 1);
   __offset += 18;

   /* Loop 3 PREGS */
   const int preg_ref7 = _PREG(14);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_4PARAM,preg_ref7,RM_NONE,0));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 2);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), -1);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), numValidBits - 2);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pInterimBuf);
   __vcop_pblock_4param_init(pblock, __offset+_PREG(14), 40,40,0,0);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pScaleFactor);
   __offset += 20;

   /* Loop 4 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (numOfLines)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((64)/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pOutput);
   __vcop_pblock_init16(pblock, __offset+_PREG(8), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(9), 48);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pScratch1);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pScratch2);
   __offset += 12;

   return 86u;
}

void vcop_fft_64_16ix16o_stage_3_overflow_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VCond", 16);
   #pragma VCC_VREG("VCos", 17);
   #pragma VCC_VREG("VInX", 18);
   #pragma VCC_VREG("VInY", 19);
   #pragma VCC_VREG("VInterim1", 20);
   #pragma VCC_VREG("VInterim2", 21);
   #pragma VCC_VREG("VInterim3", 22);
   #pragma VCC_VREG("VInterim4", 23);
   #pragma VCC_VREG("VMax", 24);
   #pragma VCC_VREG("VMin", 25);
   #pragma VCC_VREG("VOutX", 26);
   #pragma VCC_VREG("VOutX0", 27);
   #pragma VCC_VREG("VOutX1", 28);
   #pragma VCC_VREG("VOutX2", 29);
   #pragma VCC_VREG("VOutX3", 30);
   #pragma VCC_VREG("VOutY", 31);
   #pragma VCC_VREG("VOutY0", 32);
   #pragma VCC_VREG("VOutY1", 33);
   #pragma VCC_VREG("VOutY2", 34);
   #pragma VCC_VREG("VOutY3", 35);
   #pragma VCC_VREG("VScaleIn", 36);
   #pragma VCC_VREG("VScaleMinus", 37);
   #pragma VCC_VREG("VScatterOffset", 38);
   #pragma VCC_VREG("VSin", 39);
   #pragma VCC_VREG("VTemp", 40);
   #pragma VCC_VREG("VX0", 41);
   #pragma VCC_VREG("VX0_minus_X2", 42);
   #pragma VCC_VREG("VX0_plus_X2", 43);
   #pragma VCC_VREG("VX1", 44);
   #pragma VCC_VREG("VX1_minus_X3", 45);
   #pragma VCC_VREG("VX1_plus_X3", 46);
   #pragma VCC_VREG("VX2", 47);
   #pragma VCC_VREG("VX3", 48);
   #pragma VCC_VREG("VY0", 49);
   #pragma VCC_VREG("VY0_minus_Y2", 50);
   #pragma VCC_VREG("VY0_plus_Y2", 51);
   #pragma VCC_VREG("VY1", 52);
   #pragma VCC_VREG("VY1_minus_Y3", 53);
   #pragma VCC_VREG("VY1_plus_Y3", 54);
   #pragma VCC_VREG("VY2", 55);
   #pragma VCC_VREG("VY3", 56);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   #pragma EVE_REG("Addr_in", "A1");
   #pragma EVE_REG("Addr_out", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("lineIdx", "I3");
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 59u, 18u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(34), _VREG(16));
   __vcop_vinit(__vcop_sizeWU(), __vcop_once(), _PREG(36), _VREG(25));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(6), _VREG(24));
   __vcop_vagen(_AGEN(1), _PREG(32), _PREG(33), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(32), _PREG(33), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(8), _AGEN(1), _VPAIR(41,49), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(10), _AGEN(1), _VPAIR(44,52), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(12), _AGEN(1), _VPAIR(47,55), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(14), _AGEN(1), _VPAIR(48,56), __vcop_alws());
   __vcop_vmove(_VREG(41), _VREG(43));
   __vcop_vmove(_VREG(47), _VREG(42));
   __vcop_vaddsub(_VREG(43), _VREG(42));
   __vcop_vmove(_VREG(44), _VREG(46));
   __vcop_vmove(_VREG(48), _VREG(45));
   __vcop_vaddsub(_VREG(46), _VREG(45));
   __vcop_vmove(_VREG(49), _VREG(51));
   __vcop_vmove(_VREG(55), _VREG(50));
   __vcop_vaddsub(_VREG(51), _VREG(50));
   __vcop_vmove(_VREG(52), _VREG(54));
   __vcop_vmove(_VREG(56), _VREG(53));
   __vcop_vaddsub(_VREG(54), _VREG(53));
   __vcop_vmove(_VREG(43), _VREG(27));
   __vcop_vmove(_VREG(46), _VREG(29));
   __vcop_vaddsub(_VREG(27), _VREG(29));
   __vcop_vmove(_VREG(42), _VREG(28));
   __vcop_vmove(_VREG(53), _VREG(30));
   __vcop_vaddsub(_VREG(28), _VREG(30));
   __vcop_vmove(_VREG(51), _VREG(32));
   __vcop_vmove(_VREG(54), _VREG(34));
   __vcop_vaddsub(_VREG(32), _VREG(34));
   __vcop_vmove(_VREG(50), _VREG(35));
   __vcop_vmove(_VREG(45), _VREG(33));
   __vcop_vaddsub(_VREG(35), _VREG(33));
   __vcop_vmin(_VREG(27), _VREG(29), _VREG(20));
   __vcop_vmax(_VREG(27), _VREG(29), _VREG(21));
   __vcop_vmin(_VREG(28), _VREG(30), _VREG(22));
   __vcop_vmax(_VREG(28), _VREG(30), _VREG(23));
   __vcop_vmin(_VREG(20), _VREG(22), _VREG(20));
   __vcop_vmax(_VREG(21), _VREG(23), _VREG(21));
   __vcop_vmin(_VREG(32), _VREG(34), _VREG(22));
   __vcop_vmax(_VREG(32), _VREG(34), _VREG(23));
   __vcop_vmin(_VREG(20), _VREG(22), _VREG(20));
   __vcop_vmax(_VREG(21), _VREG(23), _VREG(21));
   __vcop_vmin(_VREG(35), _VREG(33), _VREG(22));
   __vcop_vmax(_VREG(35), _VREG(33), _VREG(23));
   __vcop_vmin(_VREG(20), _VREG(22), _VREG(20));
   __vcop_vmax(_VREG(21), _VREG(23), _VREG(21));
   __vcop_vmin(_VREG(25), _VREG(20), _VREG(25));
   __vcop_vmax(_VREG(24), _VREG(21), _VREG(24));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(27), _PREG(16), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(32), _PREG(18), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(28), _PREG(20), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(33), _PREG(22), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(29), _PREG(24), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(34), _PREG(26), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(30), _PREG(28), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(35), _PREG(30), _AGEN(2), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VK0", 57);
   #pragma VCC_VREG("VK1", 58);
   #pragma VCC_VREG("VKMinus1", 59);
   #pragma VCC_VREG("VLmbd1", 60);
   #pragma VCC_VREG("VLmbd2", 61);
   #pragma VCC_VREG("VLmbdFinal1", 62);
   #pragma VCC_VREG("VLmbdFinal2", 63);
   #pragma VCC_VREG("VMask", 64);
   #pragma VCC_VREG("VNeg1", 65);
   #pragma VCC_VREG("VNeg2", 66);
   #pragma VCC_VREG("VPos1", 67);
   #pragma VCC_VREG("VPos2", 68);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 25u, 9u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(16), _VREG(57));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(18), _VREG(58));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(8), _VREG(59));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vcmplt(_VREG(25), _VREG(57), _VREG(64));
   __vcop_vor(_VREG(59), _VREG(59), _VREG(65));
   __vcop_vsel(_VREG(64), _VREG(25), _VREG(65));
   __vcop_vcmplt(_VREG(24), _VREG(57), _VREG(64));
   __vcop_vor(_VREG(59), _VREG(59), _VREG(66));
   __vcop_vsel(_VREG(64), _VREG(24), _VREG(66));
   __vcop_vlmbd(_VREG(65), _VREG(57), _VREG(60));
   __vcop_vlmbd(_VREG(66), _VREG(57), _VREG(61));
   __vcop_vmax(_VREG(60), _VREG(61), _VREG(62));
   __vcop_vcmpge(_VREG(25), _VREG(57), _VREG(64));
   __vcop_vor(_VREG(57), _VREG(57), _VREG(67));
   __vcop_vsel(_VREG(64), _VREG(25), _VREG(67));
   __vcop_vcmpge(_VREG(24), _VREG(57), _VREG(64));
   __vcop_vor(_VREG(57), _VREG(57), _VREG(68));
   __vcop_vsel(_VREG(64), _VREG(24), _VREG(68));
   __vcop_vlmbd(_VREG(67), _VREG(58), _VREG(60));
   __vcop_vlmbd(_VREG(68), _VREG(58), _VREG(61));
   __vcop_vmax(_VREG(60), _VREG(61), _VREG(63));
   __vcop_vmax(_VREG(62), _VREG(63), _VREG(62));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_npt(), __vcop_alws(), _VREG(62), _PREG(10), _AGEN(0), _PREG(6));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VKMinus1", 69);
   #pragma VCC_VREG("VLmbd", 70);
   #pragma VCC_VREG("VNumValidBits", 71);
   #pragma VCC_VREG("VScale", 72);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   #pragma EVE_REG("addrIn", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 13u, 10u, 3u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(18), _VREG(40));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(8), _VREG(69));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(10), _VREG(71));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_1pt(), _PREG(20), _AGEN(0), _VREG(36), __vcop_once());
   __vcop_vload(__vcop_sizeH(), __vcop_1pt(), _PREG(12), _AGEN(1), _VREG(70), __vcop_alws());
   __vcop_vmax(_VREG(70), _VREG(40), _VREG(40));
   __vcop_vsub(_VREG(40), _VREG(71), _VREG(72));
   __vcop_vmax(_VREG(36), _VREG(72), _VREG(72));
   __vcop_vmpy(_VREG(72), _VREG(69), _VREG(37), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_1pt(), __vcop_alws(), _VREG(72), _PREG(20), _AGEN(0), _PREG(6));
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
   __vcop_vagen(_AGEN(1), _PREG(8), _PREG(9), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(8), _PREG(8), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(10), _AGEN(1), _VREG(18), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(12), _AGEN(1), _VREG(19), __vcop_alws());
   __vcop_vshf(_VREG(18), _VREG(37), _VREG(26));
   __vcop_vshf(_VREG(19), _VREG(37), _VREG(31));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_alws(), _VPAIR(26,31), _PREG(6), _AGEN(2), _PREG(0));
   __vcop_vloop_end(4u);

}

void vcop_fft_64_16ix16o_stage_3_overflow(
   __vptr_int16 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int16 pOutput,
   __vptr_uint8 pScaleFactor,
   __vptr_int16 pInterimBuf,
   unsigned char numValidBits,
   unsigned short numOfLines,
   unsigned short saturationLimit)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_64_16ix16o_stage_3_overflow_init(pInput, pScratch1, pScratch2, pOutput, pScaleFactor, pInterimBuf, numValidBits, numOfLines, saturationLimit, __pblock_vcop_fft_64_16ix16o_stage_3_overflow);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_64_16ix16o_stage_3_overflow_vloops(__pblock_vcop_fft_64_16ix16o_stage_3_overflow);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_fft_64_16ix16o_stage_3_overflow_custom(
   __vptr_int16 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int16 pOutput,
   __vptr_uint8 pScaleFactor,
   __vptr_int16 pInterimBuf,
   unsigned char numValidBits,
   unsigned short numOfLines,
   unsigned short saturationLimit,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_64_16ix16o_stage_3_overflow_init(pInput, pScratch1, pScratch2, pOutput, pScaleFactor, pInterimBuf, numValidBits, numOfLines, saturationLimit, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_64_16ix16o_stage_3_overflow_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

