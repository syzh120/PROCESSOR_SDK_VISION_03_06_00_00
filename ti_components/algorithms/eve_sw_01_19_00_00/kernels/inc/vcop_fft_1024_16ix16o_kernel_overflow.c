#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_fft_1024_16ix16o_stage_1_overflow, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_fft_1024_16ix16o_stage_1_overflow, __ALIGNOF__(int));
unsigned short __pblock_vcop_fft_1024_16ix16o_stage_1_overflow[106];

unsigned int vcop_fft_1024_16ix16o_stage_1_overflow_param_count(void)
{
   return 106u;
}

unsigned int vcop_fft_1024_16ix16o_stage_1_overflow_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_fft_1024_16ix16o_stage_1_overflow_init(
   __vptr_int16 pInput,
   __vptr_int32 pScratchL,
   __vptr_int32 pScratchH,
   __vptr_int32 pScratchWBuf,
   __vptr_int16 pOutput,
   __vptr_int16 pTwiddleFactor,
   __vptr_uint8 pScaleFactor,
   unsigned char numValidBits,
   unsigned short pitch,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   const int preg_ref1 = _PREG(18);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (numOfLines)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((1))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((256)/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_ASYMM32,preg_ref1,RM_NONE,0));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pInput+256*sizeof(*pInput)*2*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pInput+256*sizeof(*pInput)*2*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pInput+256*sizeof(*pInput)*2*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pInput+256*sizeof(*pInput)*2*3);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pScratchWBuf+256*sizeof(*pScratchWBuf)*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), 2147483647);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pScratchH+256*sizeof(*pScratchH)*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)pScratchWBuf+256*sizeof(*pScratchWBuf)*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)pScratchH+256*sizeof(*pScratchH)*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)pScratchWBuf+256*sizeof(*pScratchWBuf)*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)pScratchH+256*sizeof(*pScratchH)*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(30), (uchar *)pScratchWBuf+256*sizeof(*pScratchWBuf)*3);
   __vcop_pblock_init32(pblock, __offset+_PREG(32), (uchar *)pScratchH+256*sizeof(*pScratchH)*3);
   __vcop_pblock_init16(pblock, __offset+_PREG(34), 3104);
   __vcop_pblock_init16(pblock, __offset+_PREG(35), (pitch) -(sizeof(*pInput)*2*256*4)*(((1))-1u) -(sizeof(*pInput)*2*8u)*(((256)/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(36), 4294967295);
   __vcop_pblock_init32(pblock, __offset+_PREG(38), 0x8000000000);
   __offset += 38;

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
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (numOfLines)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((1))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((256)/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pOutput);
   __vcop_pblock_init16(pblock, __offset+_PREG(8), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(9), 3104);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pScratchWBuf+256*sizeof(*pScratchWBuf)*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pScratchH+256*sizeof(*pScratchH)*0);
   __offset += 12;

   /* Loop 5 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), (numOfLines)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), ((1))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((256)/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (3)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_ROUND,15));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 1024);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pScratchH+256*sizeof(*pScratchH)*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pOutput+256*sizeof(*pOutput)*2*1);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), -2016);
   __vcop_pblock_init16(pblock, __offset+_PREG(13), 1056);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(15), -3040);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pTwiddleFactor+8u*sizeof(*pTwiddleFactor)*2*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pScratchWBuf+256*sizeof(*pScratchWBuf)*1);
   __offset += 18;

   return 106u;
}

void vcop_fft_1024_16ix16o_stage_1_overflow_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VCos", 16);
   #pragma VCC_VREG("VInX", 17);
   #pragma VCC_VREG("VInY", 18);
   #pragma VCC_VREG("VInterim1", 19);
   #pragma VCC_VREG("VInterim2", 20);
   #pragma VCC_VREG("VInterim3", 21);
   #pragma VCC_VREG("VInterim4", 22);
   #pragma VCC_VREG("VMax", 23);
   #pragma VCC_VREG("VMin", 24);
   #pragma VCC_VREG("VOutX", 25);
   #pragma VCC_VREG("VOutX0", 26);
   #pragma VCC_VREG("VOutX1", 27);
   #pragma VCC_VREG("VOutX2", 28);
   #pragma VCC_VREG("VOutX3", 29);
   #pragma VCC_VREG("VOutY", 30);
   #pragma VCC_VREG("VOutY0", 31);
   #pragma VCC_VREG("VOutY1", 32);
   #pragma VCC_VREG("VOutY2", 33);
   #pragma VCC_VREG("VOutY3", 34);
   #pragma VCC_VREG("VScaleIn", 35);
   #pragma VCC_VREG("VScaleMinus", 36);
   #pragma VCC_VREG("VScatterOffset", 37);
   #pragma VCC_VREG("VSin", 38);
   #pragma VCC_VREG("VTemp", 39);
   #pragma VCC_VREG("VX0", 40);
   #pragma VCC_VREG("VX0_minus_X2", 41);
   #pragma VCC_VREG("VX0_plus_X2", 42);
   #pragma VCC_VREG("VX1", 43);
   #pragma VCC_VREG("VX1_minus_X3", 44);
   #pragma VCC_VREG("VX1_plus_X3", 45);
   #pragma VCC_VREG("VX2", 46);
   #pragma VCC_VREG("VX3", 47);
   #pragma VCC_VREG("VY0", 48);
   #pragma VCC_VREG("VY0_minus_Y2", 49);
   #pragma VCC_VREG("VY0_plus_Y2", 50);
   #pragma VCC_VREG("VY1", 51);
   #pragma VCC_VREG("VY1_minus_Y3", 52);
   #pragma VCC_VREG("VY1_plus_Y3", 53);
   #pragma VCC_VREG("VY2", 54);
   #pragma VCC_VREG("VY3", 55);

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
   

   __vcop_vloop(__vcop_compute(), 58u, 19u, 1u);
   __vcop_vinit(__vcop_sizeWU(), __vcop_once(), _PREG(36), _VREG(24));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(38), _VREG(23));
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(34), _PREG(35), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(7), _PREG(34), _PREG(34), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(8), _AGEN(1), _VPAIR(40,48), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(10), _AGEN(1), _VPAIR(43,51), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(12), _AGEN(1), _VPAIR(46,54), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(14), _AGEN(1), _VPAIR(47,55), __vcop_alws());
   __vcop_vmove(_VREG(40), _VREG(42));
   __vcop_vmove(_VREG(46), _VREG(41));
   __vcop_vaddsub(_VREG(42), _VREG(41));
   __vcop_vmove(_VREG(43), _VREG(45));
   __vcop_vmove(_VREG(47), _VREG(44));
   __vcop_vaddsub(_VREG(45), _VREG(44));
   __vcop_vmove(_VREG(48), _VREG(50));
   __vcop_vmove(_VREG(54), _VREG(49));
   __vcop_vaddsub(_VREG(50), _VREG(49));
   __vcop_vmove(_VREG(51), _VREG(53));
   __vcop_vmove(_VREG(55), _VREG(52));
   __vcop_vaddsub(_VREG(53), _VREG(52));
   __vcop_vmove(_VREG(42), _VREG(26));
   __vcop_vmove(_VREG(45), _VREG(28));
   __vcop_vaddsub(_VREG(26), _VREG(28));
   __vcop_vmove(_VREG(41), _VREG(27));
   __vcop_vmove(_VREG(52), _VREG(29));
   __vcop_vaddsub(_VREG(27), _VREG(29));
   __vcop_vmove(_VREG(50), _VREG(31));
   __vcop_vmove(_VREG(53), _VREG(33));
   __vcop_vaddsub(_VREG(31), _VREG(33));
   __vcop_vmove(_VREG(49), _VREG(34));
   __vcop_vmove(_VREG(44), _VREG(32));
   __vcop_vaddsub(_VREG(34), _VREG(32));
   __vcop_vmin(_VREG(26), _VREG(28), _VREG(19));
   __vcop_vmax(_VREG(26), _VREG(28), _VREG(20));
   __vcop_vmin(_VREG(27), _VREG(29), _VREG(21));
   __vcop_vmax(_VREG(27), _VREG(29), _VREG(22));
   __vcop_vmin(_VREG(19), _VREG(21), _VREG(19));
   __vcop_vmax(_VREG(20), _VREG(22), _VREG(20));
   __vcop_vmin(_VREG(31), _VREG(33), _VREG(21));
   __vcop_vmax(_VREG(31), _VREG(33), _VREG(22));
   __vcop_vmin(_VREG(19), _VREG(21), _VREG(19));
   __vcop_vmax(_VREG(20), _VREG(22), _VREG(20));
   __vcop_vmin(_VREG(34), _VREG(32), _VREG(21));
   __vcop_vmax(_VREG(34), _VREG(32), _VREG(22));
   __vcop_vmin(_VREG(19), _VREG(21), _VREG(19));
   __vcop_vmax(_VREG(20), _VREG(22), _VREG(20));
   __vcop_vmin(_VREG(24), _VREG(19), _VREG(24));
   __vcop_vmax(_VREG(23), _VREG(20), _VREG(23));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(26), _PREG(16), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(31), _PREG(20), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(27), _PREG(22), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(32), _PREG(24), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(28), _PREG(26), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(33), _PREG(28), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(29), _PREG(30), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(34), _PREG(32), _AGEN(2), _PREG(6));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VK0", 56);
   #pragma VCC_VREG("VK1", 57);
   #pragma VCC_VREG("VKMinus1", 58);
   #pragma VCC_VREG("VLmbd1", 59);
   #pragma VCC_VREG("VLmbd2", 60);
   #pragma VCC_VREG("VLmbdFinal1", 61);
   #pragma VCC_VREG("VLmbdFinal2", 62);
   #pragma VCC_VREG("VMask", 63);
   #pragma VCC_VREG("VNeg1", 64);
   #pragma VCC_VREG("VNeg2", 65);
   #pragma VCC_VREG("VPos1", 66);
   #pragma VCC_VREG("VPos2", 67);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 25u, 9u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(16), _VREG(56));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(18), _VREG(57));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(8), _VREG(58));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vcmplt(_VREG(24), _VREG(56), _VREG(63));
   __vcop_vor(_VREG(58), _VREG(58), _VREG(64));
   __vcop_vsel(_VREG(63), _VREG(24), _VREG(64));
   __vcop_vcmplt(_VREG(23), _VREG(56), _VREG(63));
   __vcop_vor(_VREG(58), _VREG(58), _VREG(65));
   __vcop_vsel(_VREG(63), _VREG(23), _VREG(65));
   __vcop_vlmbd(_VREG(64), _VREG(56), _VREG(59));
   __vcop_vlmbd(_VREG(65), _VREG(56), _VREG(60));
   __vcop_vmax(_VREG(59), _VREG(60), _VREG(61));
   __vcop_vcmpge(_VREG(24), _VREG(56), _VREG(63));
   __vcop_vor(_VREG(56), _VREG(56), _VREG(66));
   __vcop_vsel(_VREG(63), _VREG(24), _VREG(66));
   __vcop_vcmpge(_VREG(23), _VREG(56), _VREG(63));
   __vcop_vor(_VREG(56), _VREG(56), _VREG(67));
   __vcop_vsel(_VREG(63), _VREG(23), _VREG(67));
   __vcop_vlmbd(_VREG(66), _VREG(57), _VREG(59));
   __vcop_vlmbd(_VREG(67), _VREG(57), _VREG(60));
   __vcop_vmax(_VREG(59), _VREG(60), _VREG(62));
   __vcop_vmax(_VREG(61), _VREG(62), _VREG(61));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_npt(), __vcop_alws(), _VREG(61), _PREG(10), _AGEN(0), _PREG(6));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VKMinus1", 68);
   #pragma VCC_VREG("VLmbd", 69);
   #pragma VCC_VREG("VNumValidBits", 70);
   #pragma VCC_VREG("VScale", 71);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   #pragma EVE_REG("addrIn", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 13u, 10u, 3u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(18), _VREG(39));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(8), _VREG(68));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(10), _VREG(70));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_1pt(), _PREG(20), _AGEN(0), _VREG(35), __vcop_once());
   __vcop_vload(__vcop_sizeH(), __vcop_1pt(), _PREG(12), _AGEN(1), _VREG(69), __vcop_alws());
   __vcop_vmax(_VREG(69), _VREG(39), _VREG(39));
   __vcop_vsub(_VREG(39), _VREG(70), _VREG(71));
   __vcop_vmax(_VREG(35), _VREG(71), _VREG(71));
   __vcop_vmpy(_VREG(71), _VREG(68), _VREG(36), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_1pt(), __vcop_alws(), _VREG(71), _PREG(20), _AGEN(0), _PREG(6));
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
   

   __vcop_vloop(__vcop_compute(), 9u, 6u, 4u);
   __vcop_vagen(_AGEN(1), _PREG(8), _PREG(9), _PREG(9), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(8), _PREG(9), _PREG(9), _PREG(0));
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(10), _AGEN(1), _VREG(17), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(12), _AGEN(1), _VREG(18), __vcop_alws());
   __vcop_vshf(_VREG(17), _VREG(36), _VREG(25));
   __vcop_vshf(_VREG(18), _VREG(36), _VREG(30));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_alws(), _VPAIR(25,30), _PREG(6), _AGEN(2), _PREG(0));
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
   

   __vcop_vloop(__vcop_compute(), 15u, 9u, 5u);
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(12), _PREG(13), _PREG(13));
   __vcop_vagen(_AGEN(2), _PREG(7), _PREG(12), _PREG(13), _PREG(13));
   __vcop_vagen(_AGEN(3), _PREG(14), _PREG(14), _PREG(15), _PREG(15));
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(16), _AGEN(3), _VPAIR(38,16), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(18), _AGEN(1), _VREG(17), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(8), _AGEN(1), _VREG(18), __vcop_alws());
   __vcop_vshf(_VREG(17), _VREG(36), _VREG(17));
   __vcop_vshf(_VREG(18), _VREG(36), _VREG(18));
   __vcop_vmpy(_VREG(17), _VREG(16), _VREG(25), _PREG(0));
   __vcop_vmpy(_VREG(18), _VREG(16), _VREG(30), _PREG(0));
   __vcop_vmadd(_VREG(18), _VREG(38), _VREG(25), _PREG(0));
   __vcop_vmsub(_VREG(17), _VREG(38), _VREG(30), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_alws(), _VPAIR(25,30), _PREG(10), _AGEN(2), _PREG(6));
   __vcop_vloop_end(5u);

}

void vcop_fft_1024_16ix16o_stage_1_overflow(
   __vptr_int16 pInput,
   __vptr_int32 pScratchL,
   __vptr_int32 pScratchH,
   __vptr_int32 pScratchWBuf,
   __vptr_int16 pOutput,
   __vptr_int16 pTwiddleFactor,
   __vptr_uint8 pScaleFactor,
   unsigned char numValidBits,
   unsigned short pitch,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_1024_16ix16o_stage_1_overflow_init(pInput, pScratchL, pScratchH, pScratchWBuf, pOutput, pTwiddleFactor, pScaleFactor, numValidBits, pitch, numOfLines, scale, saturationLimit, __pblock_vcop_fft_1024_16ix16o_stage_1_overflow);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_1024_16ix16o_stage_1_overflow_vloops(__pblock_vcop_fft_1024_16ix16o_stage_1_overflow);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_fft_1024_16ix16o_stage_1_overflow_custom(
   __vptr_int16 pInput,
   __vptr_int32 pScratchL,
   __vptr_int32 pScratchH,
   __vptr_int32 pScratchWBuf,
   __vptr_int16 pOutput,
   __vptr_int16 pTwiddleFactor,
   __vptr_uint8 pScaleFactor,
   unsigned char numValidBits,
   unsigned short pitch,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_1024_16ix16o_stage_1_overflow_init(pInput, pScratchL, pScratchH, pScratchWBuf, pOutput, pTwiddleFactor, pScaleFactor, numValidBits, pitch, numOfLines, scale, saturationLimit, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_1024_16ix16o_stage_1_overflow_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_fft_1024_16ix16o_stage_2_overflow, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_fft_1024_16ix16o_stage_2_overflow, __ALIGNOF__(int));
unsigned short __pblock_vcop_fft_1024_16ix16o_stage_2_overflow[106];

unsigned int vcop_fft_1024_16ix16o_stage_2_overflow_param_count(void)
{
   return 106u;
}

unsigned int vcop_fft_1024_16ix16o_stage_2_overflow_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_fft_1024_16ix16o_stage_2_overflow_init(
   __vptr_int16 pInput,
   __vptr_int32 pScratchL,
   __vptr_int32 pScratchH,
   __vptr_int32 pScratchWBuf,
   __vptr_int16 pOutput,
   __vptr_int16 pTwiddleFactor,
   __vptr_uint8 pScaleFactor,
   unsigned char numValidBits,
   unsigned short pitch,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   const int preg_ref4 = _PREG(18);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (numOfLines)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((4))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((64)/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_ASYMM32,preg_ref4,RM_NONE,0));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pInput+64*sizeof(*pInput)*2*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pInput+64*sizeof(*pInput)*2*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pInput+64*sizeof(*pInput)*2*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pInput+64*sizeof(*pInput)*2*3);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pScratchWBuf+64*sizeof(*pScratchWBuf)*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), 2147483647);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pScratchH+64*sizeof(*pScratchH)*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)pScratchWBuf+64*sizeof(*pScratchWBuf)*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)pScratchH+64*sizeof(*pScratchH)*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)pScratchWBuf+64*sizeof(*pScratchWBuf)*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)pScratchH+64*sizeof(*pScratchH)*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(30), (uchar *)pScratchWBuf+64*sizeof(*pScratchWBuf)*3);
   __vcop_pblock_init32(pblock, __offset+_PREG(32), (uchar *)pScratchH+64*sizeof(*pScratchH)*3);
   __vcop_pblock_init16(pblock, __offset+_PREG(34), 800);
   __vcop_pblock_init16(pblock, __offset+_PREG(35), (pitch) -(sizeof(*pInput)*2*64*4)*(((4))-1u) -(sizeof(*pInput)*2*8u)*(((64)/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(36), 4294967295);
   __vcop_pblock_init32(pblock, __offset+_PREG(38), 0x8000000000);
   __offset += 38;

   /* Loop 2 PREGS */
   const int preg_ref5 = _PREG(12);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_4PARAM,preg_ref5,RM_NONE,0));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), -1);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pInput);
   __vcop_pblock_4param_init(pblock, __offset+_PREG(12), 40,40,0,0);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), 1);
   __offset += 18;

   /* Loop 3 PREGS */
   const int preg_ref6 = _PREG(14);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_4PARAM,preg_ref6,RM_NONE,0));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 2);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), -1);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), numValidBits - 2);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pInput);
   __vcop_pblock_4param_init(pblock, __offset+_PREG(14), 40,40,0,0);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pScaleFactor);
   __offset += 20;

   /* Loop 4 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (numOfLines)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((4))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((64)/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pOutput);
   __vcop_pblock_init16(pblock, __offset+_PREG(8), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(9), 800);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pScratchWBuf+64*sizeof(*pScratchWBuf)*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pScratchH+64*sizeof(*pScratchH)*0);
   __offset += 12;

   /* Loop 5 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), (numOfLines)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), ((4))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((64)/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (3)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_ROUND,15));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 256);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pScratchH+64*sizeof(*pScratchH)*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pOutput+64*sizeof(*pOutput)*2*1);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), -480);
   __vcop_pblock_init16(pblock, __offset+_PREG(13), 288);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(15), -736);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pTwiddleFactor+8u*sizeof(*pTwiddleFactor)*2*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pScratchWBuf+64*sizeof(*pScratchWBuf)*1);
   __offset += 18;

   return 106u;
}

void vcop_fft_1024_16ix16o_stage_2_overflow_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VCos", 16);
   #pragma VCC_VREG("VInX", 17);
   #pragma VCC_VREG("VInY", 18);
   #pragma VCC_VREG("VInterim1", 19);
   #pragma VCC_VREG("VInterim2", 20);
   #pragma VCC_VREG("VInterim3", 21);
   #pragma VCC_VREG("VInterim4", 22);
   #pragma VCC_VREG("VMax", 23);
   #pragma VCC_VREG("VMin", 24);
   #pragma VCC_VREG("VOutX", 25);
   #pragma VCC_VREG("VOutX0", 26);
   #pragma VCC_VREG("VOutX1", 27);
   #pragma VCC_VREG("VOutX2", 28);
   #pragma VCC_VREG("VOutX3", 29);
   #pragma VCC_VREG("VOutY", 30);
   #pragma VCC_VREG("VOutY0", 31);
   #pragma VCC_VREG("VOutY1", 32);
   #pragma VCC_VREG("VOutY2", 33);
   #pragma VCC_VREG("VOutY3", 34);
   #pragma VCC_VREG("VScaleIn", 35);
   #pragma VCC_VREG("VScaleMinus", 36);
   #pragma VCC_VREG("VScatterOffset", 37);
   #pragma VCC_VREG("VSin", 38);
   #pragma VCC_VREG("VTemp", 39);
   #pragma VCC_VREG("VX0", 40);
   #pragma VCC_VREG("VX0_minus_X2", 41);
   #pragma VCC_VREG("VX0_plus_X2", 42);
   #pragma VCC_VREG("VX1", 43);
   #pragma VCC_VREG("VX1_minus_X3", 44);
   #pragma VCC_VREG("VX1_plus_X3", 45);
   #pragma VCC_VREG("VX2", 46);
   #pragma VCC_VREG("VX3", 47);
   #pragma VCC_VREG("VY0", 48);
   #pragma VCC_VREG("VY0_minus_Y2", 49);
   #pragma VCC_VREG("VY0_plus_Y2", 50);
   #pragma VCC_VREG("VY1", 51);
   #pragma VCC_VREG("VY1_minus_Y3", 52);
   #pragma VCC_VREG("VY1_plus_Y3", 53);
   #pragma VCC_VREG("VY2", 54);
   #pragma VCC_VREG("VY3", 55);

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
   

   __vcop_vloop(__vcop_compute(), 58u, 19u, 1u);
   __vcop_vinit(__vcop_sizeWU(), __vcop_once(), _PREG(36), _VREG(24));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(38), _VREG(23));
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(34), _PREG(35), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(7), _PREG(34), _PREG(34), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(8), _AGEN(1), _VPAIR(40,48), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(10), _AGEN(1), _VPAIR(43,51), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(12), _AGEN(1), _VPAIR(46,54), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(14), _AGEN(1), _VPAIR(47,55), __vcop_alws());
   __vcop_vmove(_VREG(40), _VREG(42));
   __vcop_vmove(_VREG(46), _VREG(41));
   __vcop_vaddsub(_VREG(42), _VREG(41));
   __vcop_vmove(_VREG(43), _VREG(45));
   __vcop_vmove(_VREG(47), _VREG(44));
   __vcop_vaddsub(_VREG(45), _VREG(44));
   __vcop_vmove(_VREG(48), _VREG(50));
   __vcop_vmove(_VREG(54), _VREG(49));
   __vcop_vaddsub(_VREG(50), _VREG(49));
   __vcop_vmove(_VREG(51), _VREG(53));
   __vcop_vmove(_VREG(55), _VREG(52));
   __vcop_vaddsub(_VREG(53), _VREG(52));
   __vcop_vmove(_VREG(42), _VREG(26));
   __vcop_vmove(_VREG(45), _VREG(28));
   __vcop_vaddsub(_VREG(26), _VREG(28));
   __vcop_vmove(_VREG(41), _VREG(27));
   __vcop_vmove(_VREG(52), _VREG(29));
   __vcop_vaddsub(_VREG(27), _VREG(29));
   __vcop_vmove(_VREG(50), _VREG(31));
   __vcop_vmove(_VREG(53), _VREG(33));
   __vcop_vaddsub(_VREG(31), _VREG(33));
   __vcop_vmove(_VREG(49), _VREG(34));
   __vcop_vmove(_VREG(44), _VREG(32));
   __vcop_vaddsub(_VREG(34), _VREG(32));
   __vcop_vmin(_VREG(26), _VREG(28), _VREG(19));
   __vcop_vmax(_VREG(26), _VREG(28), _VREG(20));
   __vcop_vmin(_VREG(27), _VREG(29), _VREG(21));
   __vcop_vmax(_VREG(27), _VREG(29), _VREG(22));
   __vcop_vmin(_VREG(19), _VREG(21), _VREG(19));
   __vcop_vmax(_VREG(20), _VREG(22), _VREG(20));
   __vcop_vmin(_VREG(31), _VREG(33), _VREG(21));
   __vcop_vmax(_VREG(31), _VREG(33), _VREG(22));
   __vcop_vmin(_VREG(19), _VREG(21), _VREG(19));
   __vcop_vmax(_VREG(20), _VREG(22), _VREG(20));
   __vcop_vmin(_VREG(34), _VREG(32), _VREG(21));
   __vcop_vmax(_VREG(34), _VREG(32), _VREG(22));
   __vcop_vmin(_VREG(19), _VREG(21), _VREG(19));
   __vcop_vmax(_VREG(20), _VREG(22), _VREG(20));
   __vcop_vmin(_VREG(24), _VREG(19), _VREG(24));
   __vcop_vmax(_VREG(23), _VREG(20), _VREG(23));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(26), _PREG(16), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(31), _PREG(20), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(27), _PREG(22), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(32), _PREG(24), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(28), _PREG(26), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(33), _PREG(28), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(29), _PREG(30), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(34), _PREG(32), _AGEN(2), _PREG(6));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VK0", 56);
   #pragma VCC_VREG("VK1", 57);
   #pragma VCC_VREG("VKMinus1", 58);
   #pragma VCC_VREG("VLmbd1", 59);
   #pragma VCC_VREG("VLmbd2", 60);
   #pragma VCC_VREG("VLmbdFinal1", 61);
   #pragma VCC_VREG("VLmbdFinal2", 62);
   #pragma VCC_VREG("VMask", 63);
   #pragma VCC_VREG("VNeg1", 64);
   #pragma VCC_VREG("VNeg2", 65);
   #pragma VCC_VREG("VPos1", 66);
   #pragma VCC_VREG("VPos2", 67);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 25u, 9u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(16), _VREG(56));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(18), _VREG(57));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(8), _VREG(58));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vcmplt(_VREG(24), _VREG(56), _VREG(63));
   __vcop_vor(_VREG(58), _VREG(58), _VREG(64));
   __vcop_vsel(_VREG(63), _VREG(24), _VREG(64));
   __vcop_vcmplt(_VREG(23), _VREG(56), _VREG(63));
   __vcop_vor(_VREG(58), _VREG(58), _VREG(65));
   __vcop_vsel(_VREG(63), _VREG(23), _VREG(65));
   __vcop_vlmbd(_VREG(64), _VREG(56), _VREG(59));
   __vcop_vlmbd(_VREG(65), _VREG(56), _VREG(60));
   __vcop_vmax(_VREG(59), _VREG(60), _VREG(61));
   __vcop_vcmpge(_VREG(24), _VREG(56), _VREG(63));
   __vcop_vor(_VREG(56), _VREG(56), _VREG(66));
   __vcop_vsel(_VREG(63), _VREG(24), _VREG(66));
   __vcop_vcmpge(_VREG(23), _VREG(56), _VREG(63));
   __vcop_vor(_VREG(56), _VREG(56), _VREG(67));
   __vcop_vsel(_VREG(63), _VREG(23), _VREG(67));
   __vcop_vlmbd(_VREG(66), _VREG(57), _VREG(59));
   __vcop_vlmbd(_VREG(67), _VREG(57), _VREG(60));
   __vcop_vmax(_VREG(59), _VREG(60), _VREG(62));
   __vcop_vmax(_VREG(61), _VREG(62), _VREG(61));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_npt(), __vcop_alws(), _VREG(61), _PREG(10), _AGEN(0), _PREG(6));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VKMinus1", 68);
   #pragma VCC_VREG("VLmbd", 69);
   #pragma VCC_VREG("VNumValidBits", 70);
   #pragma VCC_VREG("VScale", 71);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   #pragma EVE_REG("addrIn", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 13u, 10u, 3u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(18), _VREG(39));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(8), _VREG(68));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(10), _VREG(70));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_1pt(), _PREG(20), _AGEN(0), _VREG(35), __vcop_once());
   __vcop_vload(__vcop_sizeH(), __vcop_1pt(), _PREG(12), _AGEN(1), _VREG(69), __vcop_alws());
   __vcop_vmax(_VREG(69), _VREG(39), _VREG(39));
   __vcop_vsub(_VREG(39), _VREG(70), _VREG(71));
   __vcop_vmax(_VREG(35), _VREG(71), _VREG(71));
   __vcop_vmpy(_VREG(71), _VREG(68), _VREG(36), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_1pt(), __vcop_alws(), _VREG(71), _PREG(20), _AGEN(0), _PREG(6));
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
   

   __vcop_vloop(__vcop_compute(), 9u, 6u, 4u);
   __vcop_vagen(_AGEN(1), _PREG(8), _PREG(9), _PREG(9), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(8), _PREG(9), _PREG(9), _PREG(0));
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(10), _AGEN(1), _VREG(17), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(12), _AGEN(1), _VREG(18), __vcop_alws());
   __vcop_vshf(_VREG(17), _VREG(36), _VREG(25));
   __vcop_vshf(_VREG(18), _VREG(36), _VREG(30));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_alws(), _VPAIR(25,30), _PREG(6), _AGEN(2), _PREG(0));
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
   

   __vcop_vloop(__vcop_compute(), 15u, 9u, 5u);
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(12), _PREG(13), _PREG(13));
   __vcop_vagen(_AGEN(2), _PREG(7), _PREG(12), _PREG(13), _PREG(13));
   __vcop_vagen(_AGEN(3), _PREG(14), _PREG(14), _PREG(15), _PREG(15));
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(16), _AGEN(3), _VPAIR(38,16), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(18), _AGEN(1), _VREG(17), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(8), _AGEN(1), _VREG(18), __vcop_alws());
   __vcop_vshf(_VREG(17), _VREG(36), _VREG(17));
   __vcop_vshf(_VREG(18), _VREG(36), _VREG(18));
   __vcop_vmpy(_VREG(17), _VREG(16), _VREG(25), _PREG(0));
   __vcop_vmpy(_VREG(18), _VREG(16), _VREG(30), _PREG(0));
   __vcop_vmadd(_VREG(18), _VREG(38), _VREG(25), _PREG(0));
   __vcop_vmsub(_VREG(17), _VREG(38), _VREG(30), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_alws(), _VPAIR(25,30), _PREG(10), _AGEN(2), _PREG(6));
   __vcop_vloop_end(5u);

}

void vcop_fft_1024_16ix16o_stage_2_overflow(
   __vptr_int16 pInput,
   __vptr_int32 pScratchL,
   __vptr_int32 pScratchH,
   __vptr_int32 pScratchWBuf,
   __vptr_int16 pOutput,
   __vptr_int16 pTwiddleFactor,
   __vptr_uint8 pScaleFactor,
   unsigned char numValidBits,
   unsigned short pitch,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_1024_16ix16o_stage_2_overflow_init(pInput, pScratchL, pScratchH, pScratchWBuf, pOutput, pTwiddleFactor, pScaleFactor, numValidBits, pitch, numOfLines, scale, saturationLimit, __pblock_vcop_fft_1024_16ix16o_stage_2_overflow);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_1024_16ix16o_stage_2_overflow_vloops(__pblock_vcop_fft_1024_16ix16o_stage_2_overflow);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_fft_1024_16ix16o_stage_2_overflow_custom(
   __vptr_int16 pInput,
   __vptr_int32 pScratchL,
   __vptr_int32 pScratchH,
   __vptr_int32 pScratchWBuf,
   __vptr_int16 pOutput,
   __vptr_int16 pTwiddleFactor,
   __vptr_uint8 pScaleFactor,
   unsigned char numValidBits,
   unsigned short pitch,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_1024_16ix16o_stage_2_overflow_init(pInput, pScratchL, pScratchH, pScratchWBuf, pOutput, pTwiddleFactor, pScaleFactor, numValidBits, pitch, numOfLines, scale, saturationLimit, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_1024_16ix16o_stage_2_overflow_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_fft_1024_16ix16o_stage_3_overflow, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_fft_1024_16ix16o_stage_3_overflow, __ALIGNOF__(int));
unsigned short __pblock_vcop_fft_1024_16ix16o_stage_3_overflow[146];

unsigned int vcop_fft_1024_16ix16o_stage_3_overflow_param_count(void)
{
   return 146u;
}

unsigned int vcop_fft_1024_16ix16o_stage_3_overflow_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_fft_1024_16ix16o_stage_3_overflow_init(
   __vptr_int16 pInput,
   __vptr_int32 pScratchL,
   __vptr_int32 pScratchH,
   __vptr_int32 pScratchWBuf,
   __vptr_int16 pOutput,
   __vptr_int16 pTwiddleFactor,
   __vptr_uint16 pScatterOffset,
   __vptr_uint8 pScaleFactor,
   unsigned char numValidBits,
   unsigned short pitch,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   const int preg_ref7 = _PREG(20);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), (numOfLines)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), ((16)/ 4)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (4)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((16)/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_ASYMM32,preg_ref7,RM_NONE,0));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pInput+16*sizeof(*pInput)*2*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pInput+16*sizeof(*pInput)*2*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pInput+16*sizeof(*pInput)*2*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pInput+16*sizeof(*pInput)*2*3);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pScratchL+16*sizeof(*pScratchL)*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), 2147483647);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)pScratchH+16*sizeof(*pScratchH)*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)pScratchL+16*sizeof(*pScratchL)*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)pScratchH+16*sizeof(*pScratchH)*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)pScratchL+16*sizeof(*pScratchL)*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(30), (uchar *)pScratchH+16*sizeof(*pScratchH)*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(32), (uchar *)pScratchL+16*sizeof(*pScratchL)*3);
   __vcop_pblock_init32(pblock, __offset+_PREG(34), (uchar *)pScratchH+16*sizeof(*pScratchH)*3);
   __vcop_pblock_init16(pblock, __offset+_PREG(36), 224);
   __vcop_pblock_init16(pblock, __offset+_PREG(37), (pitch) -(4*(16*4)*sizeof(*pInput)*2)*(((16)/ 4)-1u) -((16*4)*sizeof(*pInput)*2)*((4)-1u) -(8u*sizeof(*pInput)*2)*(((16)/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(38), 4294967295);
   __vcop_pblock_init32(pblock, __offset+_PREG(40), 0x8000000000);
   __offset += 40;

   /* Loop 2 PREGS */
   const int preg_ref8 = _PREG(12);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_4PARAM,preg_ref8,RM_NONE,0));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), -1);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pOutput);
   __vcop_pblock_4param_init(pblock, __offset+_PREG(12), 40,40,0,0);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), 1);
   __offset += 18;

   /* Loop 3 PREGS */
   const int preg_ref9 = _PREG(14);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_4PARAM,preg_ref9,RM_NONE,0));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 2);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), -1);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), numValidBits - 2);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pOutput);
   __vcop_pblock_4param_init(pblock, __offset+_PREG(14), 40,40,0,0);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pScaleFactor);
   __offset += 20;

   /* Loop 4 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), (numOfLines)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), ((16)/ 4)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (4)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (((16)/ (8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_ROUND,15));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pScratchL+16*sizeof(*pScratchL)*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pScratchH+16*sizeof(*pScratchH)*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pScratchL+16*sizeof(*pScratchL)*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pScratchH+16*sizeof(*pScratchH)*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pOutput+16*sizeof(*pOutput)*2*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pOutput+16*sizeof(*pOutput)*2*0+sizeof(*pOutput));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pOutput+16*sizeof(*pOutput)*2*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)pOutput+16*sizeof(*pOutput)*2*1+sizeof(*pOutput));
   __vcop_pblock_init16(pblock, __offset+_PREG(24), 224);
   __vcop_pblock_init16(pblock, __offset+_PREG(25), 2080);
   __vcop_pblock_init16(pblock, __offset+_PREG(26), -2064);
   __vcop_pblock_init16(pblock, __offset+_PREG(27), -2124);
   __vcop_pblock_init16(pblock, __offset+_PREG(28), 2020);
   __vcop_pblock_init16(pblock, __offset+_PREG(29), 96);
   __vcop_pblock_init16(pblock, __offset+_PREG(30), -96);
   __vcop_pblock_init32(pblock, __offset+_PREG(32), (uchar *)pScatterOffset);
   __vcop_pblock_init32(pblock, __offset+_PREG(34), (uchar *)pTwiddleFactor+8*sizeof(*pTwiddleFactor)*2*0);
   __offset += 34;

   /* Loop 5 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), (numOfLines)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), ((16)/ 4)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (4)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (((16)/ (8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_ROUND,15));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pScratchL+16*sizeof(*pScratchL)*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pScratchH+16*sizeof(*pScratchH)*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pScratchL+16*sizeof(*pScratchL)*3);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pScratchH+16*sizeof(*pScratchH)*3);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pOutput+16*sizeof(*pOutput)*2*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pOutput+16*sizeof(*pOutput)*2*2+sizeof(*pOutput));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pOutput+16*sizeof(*pOutput)*2*3);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)pOutput+16*sizeof(*pOutput)*2*3+sizeof(*pOutput));
   __vcop_pblock_init16(pblock, __offset+_PREG(24), 224);
   __vcop_pblock_init16(pblock, __offset+_PREG(25), 2080);
   __vcop_pblock_init16(pblock, __offset+_PREG(26), -2064);
   __vcop_pblock_init16(pblock, __offset+_PREG(27), -2124);
   __vcop_pblock_init16(pblock, __offset+_PREG(28), 2020);
   __vcop_pblock_init16(pblock, __offset+_PREG(29), 96);
   __vcop_pblock_init16(pblock, __offset+_PREG(30), -96);
   __vcop_pblock_init32(pblock, __offset+_PREG(32), (uchar *)pTwiddleFactor+8*sizeof(*pTwiddleFactor)*2*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(34), (uchar *)pTwiddleFactor+8*sizeof(*pTwiddleFactor)*2*2);
   __offset += 34;

   return 146u;
}

void vcop_fft_1024_16ix16o_stage_3_overflow_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VMax", 16);
   #pragma VCC_VREG("VMin", 17);
   #pragma VCC_VREG("VScaleIn", 18);
   #pragma VCC_VREG("VScaleMinus", 19);
   #pragma VCC_VREG("VScatterOffset", 20);
   #pragma VCC_VREG("VTemp", 21);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VInterim1", 22);
   #pragma VCC_VREG("VInterim2", 23);
   #pragma VCC_VREG("VInterim3", 24);
   #pragma VCC_VREG("VInterim4", 25);
   #pragma VCC_VREG("VOutX0", 26);
   #pragma VCC_VREG("VOutX1", 27);
   #pragma VCC_VREG("VOutX2", 28);
   #pragma VCC_VREG("VOutX3", 29);
   #pragma VCC_VREG("VOutY0", 30);
   #pragma VCC_VREG("VOutY1", 31);
   #pragma VCC_VREG("VOutY2", 32);
   #pragma VCC_VREG("VOutY3", 33);
   #pragma VCC_VREG("VX0", 34);
   #pragma VCC_VREG("VX0_minus_X2", 35);
   #pragma VCC_VREG("VX0_plus_X2", 36);
   #pragma VCC_VREG("VX1", 37);
   #pragma VCC_VREG("VX1_minus_X3", 38);
   #pragma VCC_VREG("VX1_plus_X3", 39);
   #pragma VCC_VREG("VX2", 40);
   #pragma VCC_VREG("VX3", 41);
   #pragma VCC_VREG("VY0", 42);
   #pragma VCC_VREG("VY0_minus_Y2", 43);
   #pragma VCC_VREG("VY0_plus_Y2", 44);
   #pragma VCC_VREG("VY1", 45);
   #pragma VCC_VREG("VY1_minus_Y3", 46);
   #pragma VCC_VREG("VY1_plus_Y3", 47);
   #pragma VCC_VREG("VY2", 48);
   #pragma VCC_VREG("VY3", 49);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   #pragma EVE_REG("Addr_in", "A1");
   #pragma EVE_REG("Addr_out", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("lineIdx", "I1");
   #pragma EVE_REG("I2", "I2");
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 59u, 20u, 1u);
   __vcop_vinit(__vcop_sizeWU(), __vcop_once(), _PREG(38), _VREG(17));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(40), _VREG(16));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(8), _VREG(20));
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(36), _PREG(36), _PREG(37));
   __vcop_vagen(_AGEN(2), _PREG(7), _PREG(36), _PREG(36), _PREG(36));
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(10), _AGEN(1), _VPAIR(34,42), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(12), _AGEN(1), _VPAIR(37,45), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(14), _AGEN(1), _VPAIR(40,48), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(16), _AGEN(1), _VPAIR(41,49), __vcop_alws());
   __vcop_vmove(_VREG(34), _VREG(36));
   __vcop_vmove(_VREG(40), _VREG(35));
   __vcop_vaddsub(_VREG(36), _VREG(35));
   __vcop_vmove(_VREG(37), _VREG(39));
   __vcop_vmove(_VREG(41), _VREG(38));
   __vcop_vaddsub(_VREG(39), _VREG(38));
   __vcop_vmove(_VREG(42), _VREG(44));
   __vcop_vmove(_VREG(48), _VREG(43));
   __vcop_vaddsub(_VREG(44), _VREG(43));
   __vcop_vmove(_VREG(45), _VREG(47));
   __vcop_vmove(_VREG(49), _VREG(46));
   __vcop_vaddsub(_VREG(47), _VREG(46));
   __vcop_vmove(_VREG(36), _VREG(26));
   __vcop_vmove(_VREG(39), _VREG(28));
   __vcop_vaddsub(_VREG(26), _VREG(28));
   __vcop_vmove(_VREG(35), _VREG(27));
   __vcop_vmove(_VREG(46), _VREG(29));
   __vcop_vaddsub(_VREG(27), _VREG(29));
   __vcop_vmove(_VREG(44), _VREG(30));
   __vcop_vmove(_VREG(47), _VREG(32));
   __vcop_vaddsub(_VREG(30), _VREG(32));
   __vcop_vmove(_VREG(43), _VREG(33));
   __vcop_vmove(_VREG(38), _VREG(31));
   __vcop_vaddsub(_VREG(33), _VREG(31));
   __vcop_vmin(_VREG(26), _VREG(28), _VREG(22));
   __vcop_vmax(_VREG(26), _VREG(28), _VREG(23));
   __vcop_vmin(_VREG(27), _VREG(29), _VREG(24));
   __vcop_vmax(_VREG(27), _VREG(29), _VREG(25));
   __vcop_vmin(_VREG(22), _VREG(24), _VREG(22));
   __vcop_vmax(_VREG(23), _VREG(25), _VREG(23));
   __vcop_vmin(_VREG(30), _VREG(32), _VREG(24));
   __vcop_vmax(_VREG(30), _VREG(32), _VREG(25));
   __vcop_vmin(_VREG(22), _VREG(24), _VREG(22));
   __vcop_vmax(_VREG(23), _VREG(25), _VREG(23));
   __vcop_vmin(_VREG(33), _VREG(31), _VREG(24));
   __vcop_vmax(_VREG(33), _VREG(31), _VREG(25));
   __vcop_vmin(_VREG(22), _VREG(24), _VREG(22));
   __vcop_vmax(_VREG(23), _VREG(25), _VREG(23));
   __vcop_vmin(_VREG(17), _VREG(22), _VREG(17));
   __vcop_vmax(_VREG(16), _VREG(23), _VREG(16));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(26), _PREG(18), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(30), _PREG(22), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(27), _PREG(24), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(31), _PREG(26), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(28), _PREG(28), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(32), _PREG(30), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(29), _PREG(32), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(33), _PREG(34), _AGEN(2), _PREG(6));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VK0", 50);
   #pragma VCC_VREG("VK1", 51);
   #pragma VCC_VREG("VKMinus1", 52);
   #pragma VCC_VREG("VLmbd1", 53);
   #pragma VCC_VREG("VLmbd2", 54);
   #pragma VCC_VREG("VLmbdFinal1", 55);
   #pragma VCC_VREG("VLmbdFinal2", 56);
   #pragma VCC_VREG("VMask", 57);
   #pragma VCC_VREG("VNeg1", 58);
   #pragma VCC_VREG("VNeg2", 59);
   #pragma VCC_VREG("VPos1", 60);
   #pragma VCC_VREG("VPos2", 61);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 25u, 9u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(16), _VREG(50));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(18), _VREG(51));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(8), _VREG(52));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vcmplt(_VREG(17), _VREG(50), _VREG(57));
   __vcop_vor(_VREG(52), _VREG(52), _VREG(58));
   __vcop_vsel(_VREG(57), _VREG(17), _VREG(58));
   __vcop_vcmplt(_VREG(16), _VREG(50), _VREG(57));
   __vcop_vor(_VREG(52), _VREG(52), _VREG(59));
   __vcop_vsel(_VREG(57), _VREG(16), _VREG(59));
   __vcop_vlmbd(_VREG(58), _VREG(50), _VREG(53));
   __vcop_vlmbd(_VREG(59), _VREG(50), _VREG(54));
   __vcop_vmax(_VREG(53), _VREG(54), _VREG(55));
   __vcop_vcmpge(_VREG(17), _VREG(50), _VREG(57));
   __vcop_vor(_VREG(50), _VREG(50), _VREG(60));
   __vcop_vsel(_VREG(57), _VREG(17), _VREG(60));
   __vcop_vcmpge(_VREG(16), _VREG(50), _VREG(57));
   __vcop_vor(_VREG(50), _VREG(50), _VREG(61));
   __vcop_vsel(_VREG(57), _VREG(16), _VREG(61));
   __vcop_vlmbd(_VREG(60), _VREG(51), _VREG(53));
   __vcop_vlmbd(_VREG(61), _VREG(51), _VREG(54));
   __vcop_vmax(_VREG(53), _VREG(54), _VREG(56));
   __vcop_vmax(_VREG(55), _VREG(56), _VREG(55));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_npt(), __vcop_alws(), _VREG(55), _PREG(10), _AGEN(0), _PREG(6));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VKMinus1", 62);
   #pragma VCC_VREG("VLmbd", 63);
   #pragma VCC_VREG("VNumValidBits", 64);
   #pragma VCC_VREG("VScale", 65);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   #pragma EVE_REG("addrIn", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 13u, 10u, 3u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(18), _VREG(21));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(8), _VREG(62));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(10), _VREG(64));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_1pt(), _PREG(20), _AGEN(0), _VREG(18), __vcop_once());
   __vcop_vload(__vcop_sizeH(), __vcop_1pt(), _PREG(12), _AGEN(1), _VREG(63), __vcop_alws());
   __vcop_vmax(_VREG(63), _VREG(21), _VREG(21));
   __vcop_vsub(_VREG(21), _VREG(64), _VREG(65));
   __vcop_vmax(_VREG(18), _VREG(65), _VREG(65));
   __vcop_vmpy(_VREG(65), _VREG(62), _VREG(19), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_1pt(), __vcop_alws(), _VREG(65), _PREG(20), _AGEN(0), _PREG(6));
   __vcop_vloop_end(3u);

   /* VLOOP 4 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VCos0", 66);
   #pragma VCC_VREG("VCos1", 67);
   #pragma VCC_VREG("VInX0", 68);
   #pragma VCC_VREG("VInX1", 69);
   #pragma VCC_VREG("VInY0", 70);
   #pragma VCC_VREG("VInY1", 71);
   #pragma VCC_VREG("VOutX0", 72);
   #pragma VCC_VREG("VOutX1", 73);
   #pragma VCC_VREG("VOutY0", 74);
   #pragma VCC_VREG("VOutY1", 75);
   #pragma VCC_VREG("VSin0", 76);
   #pragma VCC_VREG("VSin1", 77);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   #pragma EVE_REG("Addr_in", "A1");
   #pragma EVE_REG("Addr_out", "A2");
   #pragma EVE_REG("Addr_tw", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("lineIdx", "I1");
   #pragma EVE_REG("I4", "I2");
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 23u, 17u, 4u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(24), _PREG(24), _PREG(24));
   __vcop_vagen(_AGEN(2), _PREG(25), _PREG(26), _PREG(27), _PREG(28));
   __vcop_vagen(_AGEN(3), _PREG(29), _PREG(30), _PREG(30), _PREG(30));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(32), _AGEN(0), _VREG(20), __vcop_once());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(34), _AGEN(3), _VPAIR(77,67), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(8), _AGEN(1), _VREG(68), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(10), _AGEN(1), _VREG(70), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(12), _AGEN(1), _VREG(69), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(14), _AGEN(1), _VREG(71), __vcop_alws());
   __vcop_vshf(_VREG(68), _VREG(19), _VREG(72));
   __vcop_vshf(_VREG(70), _VREG(19), _VREG(74));
   __vcop_vshf(_VREG(69), _VREG(19), _VREG(69));
   __vcop_vshf(_VREG(71), _VREG(19), _VREG(71));
   __vcop_vmpy(_VREG(69), _VREG(67), _VREG(73), _PREG(0));
   __vcop_vmpy(_VREG(71), _VREG(67), _VREG(75), _PREG(0));
   __vcop_vmadd(_VREG(71), _VREG(77), _VREG(73), _PREG(0));
   __vcop_vmsub(_VREG(69), _VREG(77), _VREG(75), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_pdda(_VREG(20)), __vcop_alws(), _VREG(72), _PREG(16), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_pdda(_VREG(20)), __vcop_alws(), _VREG(74), _PREG(18), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_pdda(_VREG(20)), __vcop_alws(), _VREG(73), _PREG(20), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_pdda(_VREG(20)), __vcop_alws(), _VREG(75), _PREG(22), _AGEN(2), _PREG(6));
   __vcop_vloop_end(4u);

   /* VLOOP 5 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VCos2", 78);
   #pragma VCC_VREG("VCos3", 79);
   #pragma VCC_VREG("VInX2", 80);
   #pragma VCC_VREG("VInX3", 81);
   #pragma VCC_VREG("VInY2", 82);
   #pragma VCC_VREG("VInY3", 83);
   #pragma VCC_VREG("VOutX2", 84);
   #pragma VCC_VREG("VOutX3", 85);
   #pragma VCC_VREG("VOutY2", 86);
   #pragma VCC_VREG("VOutY3", 87);
   #pragma VCC_VREG("VSin2", 88);
   #pragma VCC_VREG("VSin3", 89);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   #pragma EVE_REG("Addr_in", "A1");
   #pragma EVE_REG("Addr_out", "A2");
   #pragma EVE_REG("Addr_tw", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("lineIdx", "I1");
   #pragma EVE_REG("I4", "I2");
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 27u, 17u, 5u);
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(24), _PREG(24), _PREG(24));
   __vcop_vagen(_AGEN(2), _PREG(25), _PREG(26), _PREG(27), _PREG(28));
   __vcop_vagen(_AGEN(3), _PREG(29), _PREG(30), _PREG(30), _PREG(30));
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(32), _AGEN(3), _VPAIR(88,78), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(34), _AGEN(3), _VPAIR(89,79), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(8), _AGEN(1), _VREG(80), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(10), _AGEN(1), _VREG(82), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(12), _AGEN(1), _VREG(81), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(14), _AGEN(1), _VREG(83), __vcop_alws());
   __vcop_vshf(_VREG(80), _VREG(19), _VREG(80));
   __vcop_vshf(_VREG(82), _VREG(19), _VREG(82));
   __vcop_vshf(_VREG(81), _VREG(19), _VREG(81));
   __vcop_vshf(_VREG(83), _VREG(19), _VREG(83));
   __vcop_vmpy(_VREG(80), _VREG(78), _VREG(84), _PREG(0));
   __vcop_vmpy(_VREG(82), _VREG(78), _VREG(86), _PREG(0));
   __vcop_vmadd(_VREG(82), _VREG(88), _VREG(84), _PREG(0));
   __vcop_vmsub(_VREG(80), _VREG(88), _VREG(86), _PREG(0));
   __vcop_vmpy(_VREG(81), _VREG(79), _VREG(85), _PREG(0));
   __vcop_vmpy(_VREG(83), _VREG(79), _VREG(87), _PREG(0));
   __vcop_vmadd(_VREG(83), _VREG(89), _VREG(85), _PREG(0));
   __vcop_vmsub(_VREG(81), _VREG(89), _VREG(87), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_pdda(_VREG(20)), __vcop_alws(), _VREG(84), _PREG(16), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_pdda(_VREG(20)), __vcop_alws(), _VREG(86), _PREG(18), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_pdda(_VREG(20)), __vcop_alws(), _VREG(85), _PREG(20), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_pdda(_VREG(20)), __vcop_alws(), _VREG(87), _PREG(22), _AGEN(2), _PREG(6));
   __vcop_vloop_end(5u);

}

void vcop_fft_1024_16ix16o_stage_3_overflow(
   __vptr_int16 pInput,
   __vptr_int32 pScratchL,
   __vptr_int32 pScratchH,
   __vptr_int32 pScratchWBuf,
   __vptr_int16 pOutput,
   __vptr_int16 pTwiddleFactor,
   __vptr_uint16 pScatterOffset,
   __vptr_uint8 pScaleFactor,
   unsigned char numValidBits,
   unsigned short pitch,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_1024_16ix16o_stage_3_overflow_init(pInput, pScratchL, pScratchH, pScratchWBuf, pOutput, pTwiddleFactor, pScatterOffset, pScaleFactor, numValidBits, pitch, numOfLines, scale, saturationLimit, __pblock_vcop_fft_1024_16ix16o_stage_3_overflow);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_1024_16ix16o_stage_3_overflow_vloops(__pblock_vcop_fft_1024_16ix16o_stage_3_overflow);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_fft_1024_16ix16o_stage_3_overflow_custom(
   __vptr_int16 pInput,
   __vptr_int32 pScratchL,
   __vptr_int32 pScratchH,
   __vptr_int32 pScratchWBuf,
   __vptr_int16 pOutput,
   __vptr_int16 pTwiddleFactor,
   __vptr_uint16 pScatterOffset,
   __vptr_uint8 pScaleFactor,
   unsigned char numValidBits,
   unsigned short pitch,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_1024_16ix16o_stage_3_overflow_init(pInput, pScratchL, pScratchH, pScratchWBuf, pOutput, pTwiddleFactor, pScatterOffset, pScaleFactor, numValidBits, pitch, numOfLines, scale, saturationLimit, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_1024_16ix16o_stage_3_overflow_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_fft_1024_16ix16o_stage_4_overflow, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_fft_1024_16ix16o_stage_4_overflow, __ALIGNOF__(int));
unsigned short __pblock_vcop_fft_1024_16ix16o_stage_4_overflow[114];

unsigned int vcop_fft_1024_16ix16o_stage_4_overflow_param_count(void)
{
   return 114u;
}

unsigned int vcop_fft_1024_16ix16o_stage_4_overflow_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_fft_1024_16ix16o_stage_4_overflow_init(
   __vptr_int16 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int16 pOutput,
   __vptr_int16 pTwiddleFactor,
   __vptr_uint8 pScaleFactor,
   unsigned char numValidBits,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   const int preg_ref10 = _PREG(18);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (numOfLines)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((64)/ (8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((4))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_ASYMM32,preg_ref10,RM_NONE,0));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 260);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pInput+65*sizeof(*pOutput)*2*4*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pInput+65*sizeof(*pOutput)*2*4*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pInput+65*sizeof(*pOutput)*2*4*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pInput+65*sizeof(*pOutput)*2*4*3);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pScratch1+64*sizeof(*pOutput)*2*4*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), 2147483647);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pScratch2+64*sizeof(*pOutput)*2*4*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)pScratch1+64*sizeof(*pOutput)*2*4*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)pScratch2+64*sizeof(*pOutput)*2*4*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)pScratch1+64*sizeof(*pOutput)*2*4*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)pScratch2+64*sizeof(*pOutput)*2*4*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(30), (uchar *)pScratch1+64*sizeof(*pOutput)*2*4*3);
   __vcop_pblock_init32(pblock, __offset+_PREG(32), (uchar *)pScratch2+64*sizeof(*pOutput)*2*4*3);
   __vcop_pblock_init16(pblock, __offset+_PREG(34), -748);
   __vcop_pblock_init16(pblock, __offset+_PREG(35), 3156);
   __vcop_pblock_init16(pblock, __offset+_PREG(36), 256);
   __vcop_pblock_init16(pblock, __offset+_PREG(37), -736);
   __vcop_pblock_init16(pblock, __offset+_PREG(38), 3104);
   __vcop_pblock_init32(pblock, __offset+_PREG(40), 4294967295);
   __vcop_pblock_init32(pblock, __offset+_PREG(42), 0x8000000000);
   __offset += 42;

   /* Loop 2 PREGS */
   const int preg_ref11 = _PREG(12);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_4PARAM,preg_ref11,RM_NONE,0));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), -1);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pInput);
   __vcop_pblock_4param_init(pblock, __offset+_PREG(12), 40,40,0,0);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), 1);
   __offset += 18;

   /* Loop 3 PREGS */
   const int preg_ref12 = _PREG(14);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_4PARAM,preg_ref12,RM_NONE,0));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 2);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), -1);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), numValidBits - 2);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pInput);
   __vcop_pblock_4param_init(pblock, __offset+_PREG(14), 40,40,0,0);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pScaleFactor);
   __offset += 20;

   /* Loop 4 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (numOfLines)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((64)/ (8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((4))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pOutput);
   __vcop_pblock_init16(pblock, __offset+_PREG(8), 256);
   __vcop_pblock_init16(pblock, __offset+_PREG(9), -736);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 3104);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pScratch1);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pScratch2);
   __offset += 14;

   /* Loop 5 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), (numOfLines)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), ((64)/ (8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((4))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (3)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_ROUND,15));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 1024);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pScratch2+64*sizeof(*pOutput)*2*4);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pOutput+64*sizeof(*pOutput)*2*4);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), -1792);
   __vcop_pblock_init16(pblock, __offset+_PREG(13), -2784);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), 1056);
   __vcop_pblock_init16(pblock, __offset+_PREG(15), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(16), -352);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pTwiddleFactor);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pScratch1+64*sizeof(*pOutput)*2*4);
   __offset += 20;

   return 114u;
}

void vcop_fft_1024_16ix16o_stage_4_overflow_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VCos", 16);
   #pragma VCC_VREG("VInX", 17);
   #pragma VCC_VREG("VInY", 18);
   #pragma VCC_VREG("VInterim1", 19);
   #pragma VCC_VREG("VInterim2", 20);
   #pragma VCC_VREG("VInterim3", 21);
   #pragma VCC_VREG("VInterim4", 22);
   #pragma VCC_VREG("VMax", 23);
   #pragma VCC_VREG("VMin", 24);
   #pragma VCC_VREG("VOutX", 25);
   #pragma VCC_VREG("VOutX0", 26);
   #pragma VCC_VREG("VOutX1", 27);
   #pragma VCC_VREG("VOutX2", 28);
   #pragma VCC_VREG("VOutX3", 29);
   #pragma VCC_VREG("VOutY", 30);
   #pragma VCC_VREG("VOutY0", 31);
   #pragma VCC_VREG("VOutY1", 32);
   #pragma VCC_VREG("VOutY2", 33);
   #pragma VCC_VREG("VOutY3", 34);
   #pragma VCC_VREG("VScaleIn", 35);
   #pragma VCC_VREG("VScaleMinus", 36);
   #pragma VCC_VREG("VScatterOffset", 37);
   #pragma VCC_VREG("VSin", 38);
   #pragma VCC_VREG("VTemp", 39);
   #pragma VCC_VREG("VX0", 40);
   #pragma VCC_VREG("VX0_minus_X2", 41);
   #pragma VCC_VREG("VX0_plus_X2", 42);
   #pragma VCC_VREG("VX1", 43);
   #pragma VCC_VREG("VX1_minus_X3", 44);
   #pragma VCC_VREG("VX1_plus_X3", 45);
   #pragma VCC_VREG("VX2", 46);
   #pragma VCC_VREG("VX3", 47);
   #pragma VCC_VREG("VY0", 48);
   #pragma VCC_VREG("VY0_minus_Y2", 49);
   #pragma VCC_VREG("VY0_plus_Y2", 50);
   #pragma VCC_VREG("VY1", 51);
   #pragma VCC_VREG("VY1_minus_Y3", 52);
   #pragma VCC_VREG("VY1_plus_Y3", 53);
   #pragma VCC_VREG("VY2", 54);
   #pragma VCC_VREG("VY3", 55);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   #pragma EVE_REG("Addr_in", "A1");
   #pragma EVE_REG("Addr_out", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("lineIdx", "I2");
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 58u, 21u, 1u);
   __vcop_vinit(__vcop_sizeWU(), __vcop_once(), _PREG(40), _VREG(24));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(42), _VREG(23));
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(34), _PREG(35), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(36), _PREG(37), _PREG(38), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(8), _AGEN(1), _VPAIR(40,48), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(10), _AGEN(1), _VPAIR(43,51), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(12), _AGEN(1), _VPAIR(46,54), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(14), _AGEN(1), _VPAIR(47,55), __vcop_alws());
   __vcop_vmove(_VREG(40), _VREG(42));
   __vcop_vmove(_VREG(46), _VREG(41));
   __vcop_vaddsub(_VREG(42), _VREG(41));
   __vcop_vmove(_VREG(43), _VREG(45));
   __vcop_vmove(_VREG(47), _VREG(44));
   __vcop_vaddsub(_VREG(45), _VREG(44));
   __vcop_vmove(_VREG(48), _VREG(50));
   __vcop_vmove(_VREG(54), _VREG(49));
   __vcop_vaddsub(_VREG(50), _VREG(49));
   __vcop_vmove(_VREG(51), _VREG(53));
   __vcop_vmove(_VREG(55), _VREG(52));
   __vcop_vaddsub(_VREG(53), _VREG(52));
   __vcop_vmove(_VREG(42), _VREG(26));
   __vcop_vmove(_VREG(45), _VREG(28));
   __vcop_vaddsub(_VREG(26), _VREG(28));
   __vcop_vmove(_VREG(41), _VREG(27));
   __vcop_vmove(_VREG(52), _VREG(29));
   __vcop_vaddsub(_VREG(27), _VREG(29));
   __vcop_vmove(_VREG(50), _VREG(31));
   __vcop_vmove(_VREG(53), _VREG(33));
   __vcop_vaddsub(_VREG(31), _VREG(33));
   __vcop_vmove(_VREG(49), _VREG(34));
   __vcop_vmove(_VREG(44), _VREG(32));
   __vcop_vaddsub(_VREG(34), _VREG(32));
   __vcop_vmin(_VREG(26), _VREG(28), _VREG(19));
   __vcop_vmax(_VREG(26), _VREG(28), _VREG(20));
   __vcop_vmin(_VREG(27), _VREG(29), _VREG(21));
   __vcop_vmax(_VREG(27), _VREG(29), _VREG(22));
   __vcop_vmin(_VREG(19), _VREG(21), _VREG(19));
   __vcop_vmax(_VREG(20), _VREG(22), _VREG(20));
   __vcop_vmin(_VREG(31), _VREG(33), _VREG(21));
   __vcop_vmax(_VREG(31), _VREG(33), _VREG(22));
   __vcop_vmin(_VREG(19), _VREG(21), _VREG(19));
   __vcop_vmax(_VREG(20), _VREG(22), _VREG(20));
   __vcop_vmin(_VREG(34), _VREG(32), _VREG(21));
   __vcop_vmax(_VREG(34), _VREG(32), _VREG(22));
   __vcop_vmin(_VREG(19), _VREG(21), _VREG(19));
   __vcop_vmax(_VREG(20), _VREG(22), _VREG(20));
   __vcop_vmin(_VREG(24), _VREG(19), _VREG(24));
   __vcop_vmax(_VREG(23), _VREG(20), _VREG(23));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(26), _PREG(16), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(31), _PREG(20), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(27), _PREG(22), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(32), _PREG(24), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(28), _PREG(26), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(33), _PREG(28), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(29), _PREG(30), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(34), _PREG(32), _AGEN(2), _PREG(6));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VK0", 56);
   #pragma VCC_VREG("VK1", 57);
   #pragma VCC_VREG("VKMinus1", 58);
   #pragma VCC_VREG("VLmbd1", 59);
   #pragma VCC_VREG("VLmbd2", 60);
   #pragma VCC_VREG("VLmbdFinal1", 61);
   #pragma VCC_VREG("VLmbdFinal2", 62);
   #pragma VCC_VREG("VMask", 63);
   #pragma VCC_VREG("VNeg1", 64);
   #pragma VCC_VREG("VNeg2", 65);
   #pragma VCC_VREG("VPos1", 66);
   #pragma VCC_VREG("VPos2", 67);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 25u, 9u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(16), _VREG(56));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(18), _VREG(57));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(8), _VREG(58));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vcmplt(_VREG(24), _VREG(56), _VREG(63));
   __vcop_vor(_VREG(58), _VREG(58), _VREG(64));
   __vcop_vsel(_VREG(63), _VREG(24), _VREG(64));
   __vcop_vcmplt(_VREG(23), _VREG(56), _VREG(63));
   __vcop_vor(_VREG(58), _VREG(58), _VREG(65));
   __vcop_vsel(_VREG(63), _VREG(23), _VREG(65));
   __vcop_vlmbd(_VREG(64), _VREG(56), _VREG(59));
   __vcop_vlmbd(_VREG(65), _VREG(56), _VREG(60));
   __vcop_vmax(_VREG(59), _VREG(60), _VREG(61));
   __vcop_vcmpge(_VREG(24), _VREG(56), _VREG(63));
   __vcop_vor(_VREG(56), _VREG(56), _VREG(66));
   __vcop_vsel(_VREG(63), _VREG(24), _VREG(66));
   __vcop_vcmpge(_VREG(23), _VREG(56), _VREG(63));
   __vcop_vor(_VREG(56), _VREG(56), _VREG(67));
   __vcop_vsel(_VREG(63), _VREG(23), _VREG(67));
   __vcop_vlmbd(_VREG(66), _VREG(57), _VREG(59));
   __vcop_vlmbd(_VREG(67), _VREG(57), _VREG(60));
   __vcop_vmax(_VREG(59), _VREG(60), _VREG(62));
   __vcop_vmax(_VREG(61), _VREG(62), _VREG(61));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_npt(), __vcop_alws(), _VREG(61), _PREG(10), _AGEN(0), _PREG(6));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VKMinus1", 68);
   #pragma VCC_VREG("VLmbd", 69);
   #pragma VCC_VREG("VNumValidBits", 70);
   #pragma VCC_VREG("VScale", 71);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   #pragma EVE_REG("addrIn", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 13u, 10u, 3u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(18), _VREG(39));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(8), _VREG(68));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(10), _VREG(70));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_1pt(), _PREG(20), _AGEN(0), _VREG(35), __vcop_once());
   __vcop_vload(__vcop_sizeH(), __vcop_1pt(), _PREG(12), _AGEN(1), _VREG(69), __vcop_alws());
   __vcop_vmax(_VREG(69), _VREG(39), _VREG(39));
   __vcop_vsub(_VREG(39), _VREG(70), _VREG(71));
   __vcop_vmax(_VREG(35), _VREG(71), _VREG(71));
   __vcop_vmpy(_VREG(71), _VREG(68), _VREG(36), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_1pt(), __vcop_alws(), _VREG(71), _PREG(20), _AGEN(0), _PREG(6));
   __vcop_vloop_end(3u);

   /* VLOOP 4 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   #pragma EVE_REG("Addr_in", "A1");
   #pragma EVE_REG("Addr_ou", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("lineIdx", "I2");
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 9u, 7u, 4u);
   __vcop_vagen(_AGEN(1), _PREG(8), _PREG(9), _PREG(10), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(8), _PREG(9), _PREG(10), _PREG(0));
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(12), _AGEN(1), _VREG(17), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(14), _AGEN(1), _VREG(18), __vcop_alws());
   __vcop_vshf(_VREG(17), _VREG(36), _VREG(25));
   __vcop_vshf(_VREG(18), _VREG(36), _VREG(30));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_alws(), _VPAIR(25,30), _PREG(6), _AGEN(2), _PREG(0));
   __vcop_vloop_end(4u);

   /* VLOOP 5 Start */

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
   

   __vcop_vloop(__vcop_compute(), 15u, 10u, 5u);
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(12), _PREG(13), _PREG(14));
   __vcop_vagen(_AGEN(2), _PREG(7), _PREG(12), _PREG(13), _PREG(14));
   __vcop_vagen(_AGEN(3), _PREG(15), _PREG(15), _PREG(16), _PREG(16));
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(18), _AGEN(3), _VPAIR(38,16), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(20), _AGEN(1), _VREG(17), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(8), _AGEN(1), _VREG(18), __vcop_alws());
   __vcop_vshf(_VREG(17), _VREG(36), _VREG(17));
   __vcop_vshf(_VREG(18), _VREG(36), _VREG(18));
   __vcop_vmpy(_VREG(17), _VREG(16), _VREG(25), _PREG(0));
   __vcop_vmpy(_VREG(18), _VREG(16), _VREG(30), _PREG(0));
   __vcop_vmadd(_VREG(18), _VREG(38), _VREG(25), _PREG(0));
   __vcop_vmsub(_VREG(17), _VREG(38), _VREG(30), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_alws(), _VPAIR(25,30), _PREG(10), _AGEN(2), _PREG(6));
   __vcop_vloop_end(5u);

}

void vcop_fft_1024_16ix16o_stage_4_overflow(
   __vptr_int16 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int16 pOutput,
   __vptr_int16 pTwiddleFactor,
   __vptr_uint8 pScaleFactor,
   unsigned char numValidBits,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_1024_16ix16o_stage_4_overflow_init(pInput, pScratch1, pScratch2, pOutput, pTwiddleFactor, pScaleFactor, numValidBits, numOfLines, scale, saturationLimit, __pblock_vcop_fft_1024_16ix16o_stage_4_overflow);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_1024_16ix16o_stage_4_overflow_vloops(__pblock_vcop_fft_1024_16ix16o_stage_4_overflow);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_fft_1024_16ix16o_stage_4_overflow_custom(
   __vptr_int16 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int16 pOutput,
   __vptr_int16 pTwiddleFactor,
   __vptr_uint8 pScaleFactor,
   unsigned char numValidBits,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_1024_16ix16o_stage_4_overflow_init(pInput, pScratch1, pScratch2, pOutput, pTwiddleFactor, pScaleFactor, numValidBits, numOfLines, scale, saturationLimit, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_1024_16ix16o_stage_4_overflow_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_fft_1024_16ix16o_stage_5_overflow, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_fft_1024_16ix16o_stage_5_overflow, __ALIGNOF__(int));
unsigned short __pblock_vcop_fft_1024_16ix16o_stage_5_overflow[88];

unsigned int vcop_fft_1024_16ix16o_stage_5_overflow_param_count(void)
{
   return 88u;
}

unsigned int vcop_fft_1024_16ix16o_stage_5_overflow_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_fft_1024_16ix16o_stage_5_overflow_init(
   __vptr_int16 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int16 pOutput,
   __vptr_uint8 pScaleFactor,
   unsigned char numValidBits,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (numOfLines)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (((256)/ 4)/ (8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (4)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pInput+64*sizeof(*pOutput)*2*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pInput+64*sizeof(*pOutput)*2*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pInput+64*sizeof(*pOutput)*2*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pInput+64*sizeof(*pOutput)*2*3);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pScratch1+64*sizeof(*pOutput)*2*4*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pScratch2+64*sizeof(*pOutput)*2*4*0);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pScratch1+64*sizeof(*pOutput)*2*4*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pScratch2+64*sizeof(*pOutput)*2*4*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)pScratch1+64*sizeof(*pOutput)*2*4*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)pScratch2+64*sizeof(*pOutput)*2*4*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)pScratch1+64*sizeof(*pOutput)*2*4*3);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)pScratch2+64*sizeof(*pOutput)*2*4*3);
   __vcop_pblock_init16(pblock, __offset+_PREG(30), 1024);
   __vcop_pblock_init16(pblock, __offset+_PREG(31), -3040);
   __vcop_pblock_init16(pblock, __offset+_PREG(32), 800);
   __vcop_pblock_init16(pblock, __offset+_PREG(33), 256);
   __vcop_pblock_init16(pblock, __offset+_PREG(34), -736);
   __vcop_pblock_init16(pblock, __offset+_PREG(35), 3104);
   __vcop_pblock_init32(pblock, __offset+_PREG(36), 4294967295);
   __vcop_pblock_init32(pblock, __offset+_PREG(38), 0x8000000000);
   __offset += 38;

   /* Loop 2 PREGS */
   const int preg_ref13 = _PREG(12);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_4PARAM,preg_ref13,RM_NONE,0));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), -1);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pInput);
   __vcop_pblock_4param_init(pblock, __offset+_PREG(12), 40,40,0,0);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), 1);
   __offset += 18;

   /* Loop 3 PREGS */
   const int preg_ref14 = _PREG(14);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_4PARAM,preg_ref14,RM_NONE,0));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 2);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), -1);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), numValidBits - 2);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pInput);
   __vcop_pblock_4param_init(pblock, __offset+_PREG(14), 40,40,0,0);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pScaleFactor);
   __offset += 20;

   /* Loop 4 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (numOfLines)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((1024)/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pOutput);
   __vcop_pblock_init16(pblock, __offset+_PREG(8), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pScratch1);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pScratch2);
   __offset += 12;

   return 88u;
}

void vcop_fft_1024_16ix16o_stage_5_overflow_vloops(
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
   #pragma VCC_VREG("VScaleIn", 34);
   #pragma VCC_VREG("VScaleMinus", 35);
   #pragma VCC_VREG("VScatterOffset", 36);
   #pragma VCC_VREG("VTemp", 37);
   #pragma VCC_VREG("VX0", 38);
   #pragma VCC_VREG("VX0_minus_X2", 39);
   #pragma VCC_VREG("VX0_plus_X2", 40);
   #pragma VCC_VREG("VX1", 41);
   #pragma VCC_VREG("VX1_minus_X3", 42);
   #pragma VCC_VREG("VX1_plus_X3", 43);
   #pragma VCC_VREG("VX2", 44);
   #pragma VCC_VREG("VX3", 45);
   #pragma VCC_VREG("VY0", 46);
   #pragma VCC_VREG("VY0_minus_Y2", 47);
   #pragma VCC_VREG("VY0_plus_Y2", 48);
   #pragma VCC_VREG("VY1", 49);
   #pragma VCC_VREG("VY1_minus_Y3", 50);
   #pragma VCC_VREG("VY1_plus_Y3", 51);
   #pragma VCC_VREG("VY2", 52);
   #pragma VCC_VREG("VY3", 53);

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
   

   __vcop_vloop(__vcop_compute(), 58u, 19u, 1u);
   __vcop_vinit(__vcop_sizeWU(), __vcop_once(), _PREG(36), _VREG(23));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(38), _VREG(22));
   __vcop_vagen(_AGEN(1), _PREG(30), _PREG(31), _PREG(32), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(33), _PREG(34), _PREG(35), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(6), _AGEN(1), _VPAIR(38,46), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(8), _AGEN(1), _VPAIR(41,49), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(10), _AGEN(1), _VPAIR(44,52), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(12), _AGEN(1), _VPAIR(45,53), __vcop_alws());
   __vcop_vmove(_VREG(38), _VREG(40));
   __vcop_vmove(_VREG(44), _VREG(39));
   __vcop_vaddsub(_VREG(40), _VREG(39));
   __vcop_vmove(_VREG(41), _VREG(43));
   __vcop_vmove(_VREG(45), _VREG(42));
   __vcop_vaddsub(_VREG(43), _VREG(42));
   __vcop_vmove(_VREG(46), _VREG(48));
   __vcop_vmove(_VREG(52), _VREG(47));
   __vcop_vaddsub(_VREG(48), _VREG(47));
   __vcop_vmove(_VREG(49), _VREG(51));
   __vcop_vmove(_VREG(53), _VREG(50));
   __vcop_vaddsub(_VREG(51), _VREG(50));
   __vcop_vmove(_VREG(40), _VREG(25));
   __vcop_vmove(_VREG(43), _VREG(27));
   __vcop_vaddsub(_VREG(25), _VREG(27));
   __vcop_vmove(_VREG(39), _VREG(26));
   __vcop_vmove(_VREG(50), _VREG(28));
   __vcop_vaddsub(_VREG(26), _VREG(28));
   __vcop_vmove(_VREG(48), _VREG(30));
   __vcop_vmove(_VREG(51), _VREG(32));
   __vcop_vaddsub(_VREG(30), _VREG(32));
   __vcop_vmove(_VREG(47), _VREG(33));
   __vcop_vmove(_VREG(42), _VREG(31));
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
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(25), _PREG(14), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(30), _PREG(16), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(26), _PREG(18), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(31), _PREG(20), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(27), _PREG(22), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(32), _PREG(24), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(28), _PREG(26), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(33), _PREG(28), _AGEN(2), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VK0", 54);
   #pragma VCC_VREG("VK1", 55);
   #pragma VCC_VREG("VKMinus1", 56);
   #pragma VCC_VREG("VLmbd1", 57);
   #pragma VCC_VREG("VLmbd2", 58);
   #pragma VCC_VREG("VLmbdFinal1", 59);
   #pragma VCC_VREG("VLmbdFinal2", 60);
   #pragma VCC_VREG("VMask", 61);
   #pragma VCC_VREG("VNeg1", 62);
   #pragma VCC_VREG("VNeg2", 63);
   #pragma VCC_VREG("VPos1", 64);
   #pragma VCC_VREG("VPos2", 65);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 25u, 9u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(16), _VREG(54));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(18), _VREG(55));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(8), _VREG(56));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vcmplt(_VREG(23), _VREG(54), _VREG(61));
   __vcop_vor(_VREG(56), _VREG(56), _VREG(62));
   __vcop_vsel(_VREG(61), _VREG(23), _VREG(62));
   __vcop_vcmplt(_VREG(22), _VREG(54), _VREG(61));
   __vcop_vor(_VREG(56), _VREG(56), _VREG(63));
   __vcop_vsel(_VREG(61), _VREG(22), _VREG(63));
   __vcop_vlmbd(_VREG(62), _VREG(54), _VREG(57));
   __vcop_vlmbd(_VREG(63), _VREG(54), _VREG(58));
   __vcop_vmax(_VREG(57), _VREG(58), _VREG(59));
   __vcop_vcmpge(_VREG(23), _VREG(54), _VREG(61));
   __vcop_vor(_VREG(54), _VREG(54), _VREG(64));
   __vcop_vsel(_VREG(61), _VREG(23), _VREG(64));
   __vcop_vcmpge(_VREG(22), _VREG(54), _VREG(61));
   __vcop_vor(_VREG(54), _VREG(54), _VREG(65));
   __vcop_vsel(_VREG(61), _VREG(22), _VREG(65));
   __vcop_vlmbd(_VREG(64), _VREG(55), _VREG(57));
   __vcop_vlmbd(_VREG(65), _VREG(55), _VREG(58));
   __vcop_vmax(_VREG(57), _VREG(58), _VREG(60));
   __vcop_vmax(_VREG(59), _VREG(60), _VREG(59));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_npt(), __vcop_alws(), _VREG(59), _PREG(10), _AGEN(0), _PREG(6));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VKMinus1", 66);
   #pragma VCC_VREG("VLmbd", 67);
   #pragma VCC_VREG("VNumValidBits", 68);
   #pragma VCC_VREG("VScale", 69);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   #pragma EVE_REG("addrIn", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 13u, 10u, 3u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(18), _VREG(37));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(8), _VREG(66));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(10), _VREG(68));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_1pt(), _PREG(20), _AGEN(0), _VREG(34), __vcop_once());
   __vcop_vload(__vcop_sizeH(), __vcop_1pt(), _PREG(12), _AGEN(1), _VREG(67), __vcop_alws());
   __vcop_vmax(_VREG(67), _VREG(37), _VREG(37));
   __vcop_vsub(_VREG(37), _VREG(68), _VREG(69));
   __vcop_vmax(_VREG(34), _VREG(69), _VREG(69));
   __vcop_vmpy(_VREG(69), _VREG(66), _VREG(35), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_1pt(), __vcop_alws(), _VREG(69), _PREG(20), _AGEN(0), _PREG(6));
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
   __vcop_vshf(_VREG(16), _VREG(35), _VREG(24));
   __vcop_vshf(_VREG(17), _VREG(35), _VREG(29));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_alws(), _VPAIR(24,29), _PREG(6), _AGEN(2), _PREG(0));
   __vcop_vloop_end(4u);

}

void vcop_fft_1024_16ix16o_stage_5_overflow(
   __vptr_int16 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int16 pOutput,
   __vptr_uint8 pScaleFactor,
   unsigned char numValidBits,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_1024_16ix16o_stage_5_overflow_init(pInput, pScratch1, pScratch2, pOutput, pScaleFactor, numValidBits, numOfLines, scale, saturationLimit, __pblock_vcop_fft_1024_16ix16o_stage_5_overflow);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_1024_16ix16o_stage_5_overflow_vloops(__pblock_vcop_fft_1024_16ix16o_stage_5_overflow);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_fft_1024_16ix16o_stage_5_overflow_custom(
   __vptr_int16 pInput,
   __vptr_int32 pScratch1,
   __vptr_int32 pScratch2,
   __vptr_int16 pOutput,
   __vptr_uint8 pScaleFactor,
   unsigned char numValidBits,
   unsigned short numOfLines,
   unsigned short scale,
   unsigned short saturationLimit,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_1024_16ix16o_stage_5_overflow_init(pInput, pScratch1, pScratch2, pOutput, pScaleFactor, numValidBits, numOfLines, scale, saturationLimit, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_1024_16ix16o_stage_5_overflow_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

