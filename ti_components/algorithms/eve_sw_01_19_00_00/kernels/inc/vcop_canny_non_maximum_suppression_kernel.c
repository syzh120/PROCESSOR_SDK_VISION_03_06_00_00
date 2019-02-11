#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_canny_bin_indexing, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_canny_bin_indexing, __ALIGNOF__(int));
unsigned short __pblock_vcop_canny_bin_indexing[20];

unsigned int vcop_canny_bin_indexing_param_count(void)
{
   return 20u;
}

unsigned int vcop_canny_bin_indexing_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_canny_bin_indexing_init(
   __vptr_int16 pGx,
   __vptr_int16 pGy,
   __vptr_uint8 pIndex,
   unsigned short computeWidth,
   unsigned short computeHeight,
   unsigned short pitch,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (computeHeight)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((computeWidth) + 2*(8u)-1) & ~(2*(8u)-1))/(2 * (8u)))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (39554));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pGx);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pGy);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pIndex);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(15), (pitch*sizeof(*pGx)) -((2*8u)*sizeof(*pGx))*(((((computeWidth) + 2*(8u)-1) & ~(2*(8u)-1))/(2 * (8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(16), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(17), (pitch*sizeof(*pIndex)) -((2*8u)*sizeof(*pIndex))*(((((computeWidth) + 2*(8u)-1) & ~(2*(8u)-1))/(2 * (8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(18), 2);
   __vcop_pblock_init16(pblock, __offset+_PREG(19), 14);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (6786));
   __offset += 20;

   return 20u;
}

void vcop_canny_bin_indexing_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Gx1", 16);
   #pragma VCC_VREG("Gx2", 17);
   #pragma VCC_VREG("Gy1", 18);
   #pragma VCC_VREG("Gy2", 19);
   #pragma VCC_VREG("VGxTan22_5_1", 20);
   #pragma VCC_VREG("VGxTan22_5_2", 21);
   #pragma VCC_VREG("VGxTan67_5_1", 22);
   #pragma VCC_VREG("VGxTan67_5_2", 23);
   #pragma VCC_VREG("VK1", 24);
   #pragma VCC_VREG("VK2", 25);
   #pragma VCC_VREG("VKQshift", 26);
   #pragma VCC_VREG("VKtan22_5Q", 27);
   #pragma VCC_VREG("VKtan67_5Q", 28);
   #pragma VCC_VREG("VKzero", 29);
   #pragma VCC_VREG("Vindex1", 30);
   #pragma VCC_VREG("Vindex2", 31);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("AddrIn", "A0");
   #pragma EVE_REG("AddrOut", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("row", "I3");
   #pragma EVE_REG("col", "I4");
   

   __vcop_vloop(__vcop_compute(), 34u, 10u, 1u);
   __vcop_vinit(__vcop_sizeHU(), __vcop_once(), _PREG(1), _VREG(24));
   __vcop_vinit(__vcop_sizeHU(), __vcop_once(), _PREG(18), _VREG(25));
   __vcop_vinit(__vcop_sizeHU(), __vcop_alws(), _PREG(0), _VREG(29));
   __vcop_vinit(__vcop_sizeHU(), __vcop_alws(), _PREG(19), _VREG(26));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(20), _VREG(27));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(6), _VREG(28));
   __vcop_vagen(_AGEN(0), _PREG(14), _PREG(15), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(16), _PREG(17), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(8), _AGEN(0), _VPAIR(16,17), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(10), _AGEN(0), _VPAIR(18,19), __vcop_alws());
   __vcop_vxor(_VREG(16), _VREG(18), _VREG(30));
   __vcop_vxor(_VREG(17), _VREG(19), _VREG(31));
   __vcop_vcmplt(_VREG(30), _VREG(29), _VREG(30));
   __vcop_vcmplt(_VREG(31), _VREG(29), _VREG(31));
   __vcop_vabs(_VREG(16), _VREG(16));
   __vcop_vabs(_VREG(17), _VREG(17));
   __vcop_vabs(_VREG(18), _VREG(18));
   __vcop_vabs(_VREG(19), _VREG(19));
   __vcop_vshf(_VREG(18), _VREG(26), _VREG(18));
   __vcop_vshf(_VREG(19), _VREG(26), _VREG(19));
   __vcop_vmpy(_VREG(16), _VREG(27), _VREG(20), _PREG(0));
   __vcop_vmpy(_VREG(17), _VREG(27), _VREG(21), _PREG(0));
   __vcop_vmpy(_VREG(16), _VREG(28), _VREG(22), _PREG(0));
   __vcop_vmpy(_VREG(17), _VREG(28), _VREG(23), _PREG(0));
   __vcop_vcmpgt(_VREG(18), _VREG(20), _VREG(16));
   __vcop_vcmpgt(_VREG(19), _VREG(21), _VREG(17));
   __vcop_vcmpgt(_VREG(18), _VREG(22), _VREG(18));
   __vcop_vcmpgt(_VREG(19), _VREG(23), _VREG(19));
   __vcop_vshfor(_VREG(16), _VREG(25), _VREG(30));
   __vcop_vshfor(_VREG(17), _VREG(25), _VREG(31));
   __vcop_vshfor(_VREG(18), _VREG(24), _VREG(30));
   __vcop_vshfor(_VREG(19), _VREG(24), _VREG(31));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(30,31), _PREG(12), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_canny_bin_indexing(
   __vptr_int16 pGx,
   __vptr_int16 pGy,
   __vptr_uint8 pIndex,
   unsigned short computeWidth,
   unsigned short computeHeight,
   unsigned short pitch)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_canny_bin_indexing_init(pGx, pGy, pIndex, computeWidth, computeHeight, pitch, __pblock_vcop_canny_bin_indexing);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_canny_bin_indexing_vloops(__pblock_vcop_canny_bin_indexing);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_canny_bin_indexing_custom(
   __vptr_int16 pGx,
   __vptr_int16 pGy,
   __vptr_uint8 pIndex,
   unsigned short computeWidth,
   unsigned short computeHeight,
   unsigned short pitch,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_canny_bin_indexing_init(pGx, pGy, pIndex, computeWidth, computeHeight, pitch, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_canny_bin_indexing_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_canny_nms_max_cases, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_canny_nms_max_cases, __ALIGNOF__(int));
unsigned short __pblock_vcop_canny_nms_max_cases[30];

unsigned int vcop_canny_nms_max_cases_param_count(void)
{
   return 30u;
}

unsigned int vcop_canny_nms_max_cases_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_canny_nms_max_cases_init(
   __vptr_uint16 pMag,
   __vptr_uint16 pCase1Max,
   __vptr_uint16 pCase2Max,
   __vptr_uint16 pCase3Max,
   __vptr_uint16 pCase4Max,
   unsigned short computeWidth,
   unsigned short computeHeight,
   unsigned short pitch,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (computeHeight)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((computeWidth) + 2*(8u)-1) & ~(2*(8u)-1))/(2 * (8u)))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pMag+pitch*sizeof(*pMag));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pMag+pitch*sizeof(*pMag)+sizeof(*pMag)*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pMag+2*pitch*sizeof(*pMag)*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pMag+2*pitch*sizeof(*pMag)+sizeof(*pMag)*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pCase1Max);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pCase2Max);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pCase3Max);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pCase3Max+8u*sizeof(*pCase3Max));
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)pCase4Max);
   __vcop_pblock_init16(pblock, __offset+_PREG(24), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(25), (pitch*sizeof(*pMag)) -(sizeof(*pMag)*(2*8u))*(((((computeWidth) + 2*(8u)-1) & ~(2*(8u)-1))/(2 * (8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(26), (pitch*sizeof(*pCase1Max)) -(sizeof(*pCase1Max)*(2*8u))*(((((computeWidth) + 2*(8u)-1) & ~(2*(8u)-1))/(2 * (8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)pMag);
   __vcop_pblock_init32(pblock, __offset+_PREG(30), (uchar *)pMag+sizeof(*pMag)*2);
   __offset += 30;

   return 30u;
}

void vcop_canny_nms_max_cases_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vcase1MaxEven", 16);
   #pragma VCC_VREG("Vcase1MaxOdd", 17);
   #pragma VCC_VREG("Vcase2MaxEven", 18);
   #pragma VCC_VREG("Vcase2MaxOdd", 19);
   #pragma VCC_VREG("Vcase3MaxEven", 20);
   #pragma VCC_VREG("Vcase3MaxOdd", 21);
   #pragma VCC_VREG("Vcase4MaxEven", 22);
   #pragma VCC_VREG("Vcase4MaxOdd", 23);
   #pragma VCC_VREG("VcenterPixelEven", 24);
   #pragma VCC_VREG("VcenterPixelOdd", 25);
   #pragma VCC_VREG("Vflag1", 26);
   #pragma VCC_VREG("Vflag2", 27);
   #pragma VCC_VREG("magBotRowEven", 28);
   #pragma VCC_VREG("magBotRowEvenPlus2", 29);
   #pragma VCC_VREG("magBotRowOdd", 30);
   #pragma VCC_VREG("magBotRowOddPlus2", 31);
   #pragma VCC_VREG("magMidRowEven", 32);
   #pragma VCC_VREG("magMidRowEvenPlus2", 33);
   #pragma VCC_VREG("magMidRowOdd", 34);
   #pragma VCC_VREG("magMidRowOddPlus2", 35);
   #pragma VCC_VREG("magTopRowEven", 36);
   #pragma VCC_VREG("magTopRowEvenPlus2", 37);
   #pragma VCC_VREG("magTopRowOdd", 38);
   #pragma VCC_VREG("magTopRowOddPlus2", 39);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addrMag", "A0");
   #pragma EVE_REG("addrOut", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("row", "I3");
   #pragma EVE_REG("col", "I4");
   

   __vcop_vloop(__vcop_compute(), 41u, 15u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(24), _PREG(25), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(24), _PREG(26), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(28), _AGEN(0), _VPAIR(38,36), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(30), _AGEN(0), _VPAIR(39,37), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(6), _AGEN(0), _VPAIR(34,32), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(8), _AGEN(0), _VPAIR(35,33), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(10), _AGEN(0), _VPAIR(30,28), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(12), _AGEN(0), _VPAIR(31,29), __vcop_alws());
   __vcop_vor(_VREG(32), _VREG(32), _VREG(24));
   __vcop_vor(_VREG(35), _VREG(35), _VREG(25));
   __vcop_vmax(_VREG(34), _VREG(35), _VREG(17));
   __vcop_vcmpge(_VREG(24), _VREG(17), _VREG(26));
   __vcop_vmpy(_VREG(24), _VREG(26), _VREG(17), _PREG(0));
   __vcop_vmax(_VREG(32), _VREG(33), _VREG(16));
   __vcop_vcmpge(_VREG(25), _VREG(16), _VREG(27));
   __vcop_vmpy(_VREG(25), _VREG(27), _VREG(16), _PREG(0));
   __vcop_vmax(_VREG(36), _VREG(28), _VREG(20));
   __vcop_vcmpge(_VREG(24), _VREG(20), _VREG(26));
   __vcop_vmpy(_VREG(24), _VREG(26), _VREG(20), _PREG(0));
   __vcop_vmax(_VREG(39), _VREG(31), _VREG(21));
   __vcop_vcmpge(_VREG(25), _VREG(21), _VREG(27));
   __vcop_vmpy(_VREG(25), _VREG(27), _VREG(21), _PREG(0));
   __vcop_vmax(_VREG(38), _VREG(31), _VREG(23));
   __vcop_vcmpge(_VREG(24), _VREG(23), _VREG(26));
   __vcop_vmpy(_VREG(24), _VREG(26), _VREG(23), _PREG(0));
   __vcop_vmax(_VREG(36), _VREG(29), _VREG(22));
   __vcop_vcmpge(_VREG(25), _VREG(22), _VREG(27));
   __vcop_vmpy(_VREG(25), _VREG(27), _VREG(22), _PREG(0));
   __vcop_vmax(_VREG(30), _VREG(39), _VREG(19));
   __vcop_vcmpge(_VREG(24), _VREG(19), _VREG(26));
   __vcop_vmpy(_VREG(24), _VREG(26), _VREG(19), _PREG(0));
   __vcop_vmax(_VREG(28), _VREG(37), _VREG(18));
   __vcop_vcmpge(_VREG(25), _VREG(18), _VREG(27));
   __vcop_vmpy(_VREG(25), _VREG(27), _VREG(18), _PREG(0));
   __vcop_vintrlv(_VREG(20), _VREG(21));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(17,16), _PREG(14), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(19,18), _PREG(16), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(20), _PREG(18), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(21), _PREG(20), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(23,22), _PREG(22), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_canny_nms_max_cases(
   __vptr_uint16 pMag,
   __vptr_uint16 pCase1Max,
   __vptr_uint16 pCase2Max,
   __vptr_uint16 pCase3Max,
   __vptr_uint16 pCase4Max,
   unsigned short computeWidth,
   unsigned short computeHeight,
   unsigned short pitch)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_canny_nms_max_cases_init(pMag, pCase1Max, pCase2Max, pCase3Max, pCase4Max, computeWidth, computeHeight, pitch, __pblock_vcop_canny_nms_max_cases);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_canny_nms_max_cases_vloops(__pblock_vcop_canny_nms_max_cases);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_canny_nms_max_cases_custom(
   __vptr_uint16 pMag,
   __vptr_uint16 pCase1Max,
   __vptr_uint16 pCase2Max,
   __vptr_uint16 pCase3Max,
   __vptr_uint16 pCase4Max,
   unsigned short computeWidth,
   unsigned short computeHeight,
   unsigned short pitch,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_canny_nms_max_cases_init(pMag, pCase1Max, pCase2Max, pCase3Max, pCase4Max, computeWidth, computeHeight, pitch, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_canny_nms_max_cases_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_canny_nms_double_thresholding, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_canny_nms_double_thresholding, __ALIGNOF__(int));
unsigned short __pblock_vcop_canny_nms_double_thresholding[34];

unsigned int vcop_canny_nms_double_thresholding_param_count(void)
{
   return 34u;
}

unsigned int vcop_canny_nms_double_thresholding_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_canny_nms_double_thresholding_init(
   __vptr_uint8 pIndex,
   __vptr_uint16 pCase1Max,
   __vptr_uint16 pCase2Max,
   __vptr_uint16 pCase3Max,
   __vptr_uint16 pCase4Max,
   __vptr_uint8 pOutVal,
   unsigned char lowThreshold,
   unsigned char highThreshold,
   unsigned short width,
   unsigned short height,
   unsigned short pitch,
   unsigned short outputPitch,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   const int preg_ref1 = _PREG(24);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (height)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((width) + 2*(8u)-1) & ~(2*(8u)-1))/(2 * (8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_4PARAM,preg_ref1,RM_NONE,0));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pCase2Max);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pCase3Max);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pCase4Max);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), 1);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), 4);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), highThreshold);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), lowThreshold);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)pOutVal);
   __vcop_pblock_4param_init(pblock, __offset+_PREG(24), 5,255,0,0);
   __vcop_pblock_init16(pblock, __offset+_PREG(28), (pitch*sizeof(*pCase1Max)) -(sizeof(*pCase1Max)*(2*8u))*(((((width) + 2*(8u)-1) & ~(2*(8u)-1))/(2 * (8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(29), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(30), (pitch*sizeof(*pIndex)) -(sizeof(*pIndex)*(2*8u))*(((((width) + 2*(8u)-1) & ~(2*(8u)-1))/(2 * (8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(31), (outputPitch*sizeof(*pOutVal)) -(sizeof(*pOutVal)*(2*8u))*(((((width) + 2*(8u)-1) & ~(2*(8u)-1))/(2 * (8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(32), (uchar *)pIndex+sizeof(*pIndex)+pitch*sizeof(*pIndex));
   __vcop_pblock_init32(pblock, __offset+_PREG(34), (uchar *)pCase1Max);
   __offset += 34;

   return 34u;
}

void vcop_canny_nms_double_thresholding_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vcase2Max_1", 16);
   #pragma VCC_VREG("Vcase2Max_2", 17);
   #pragma VCC_VREG("Vcase3Max_1", 18);
   #pragma VCC_VREG("Vcase3Max_2", 19);
   #pragma VCC_VREG("Vcase4Max_1", 20);
   #pragma VCC_VREG("Vcase4Max_2", 21);
   #pragma VCC_VREG("VcenterPix1", 22);
   #pragma VCC_VREG("VcenterPix2", 23);
   #pragma VCC_VREG("VhighThreshold", 24);
   #pragma VCC_VREG("Vindex1", 25);
   #pragma VCC_VREG("Vindex2", 26);
   #pragma VCC_VREG("Vk1", 27);
   #pragma VCC_VREG("Vk4", 28);
   #pragma VCC_VREG("VlowThreshold", 29);
   #pragma VCC_VREG("Vmask1", 30);
   #pragma VCC_VREG("Vmask2", 31);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addrCaseVal", "A0");
   #pragma EVE_REG("addrIndex", "A1");
   #pragma EVE_REG("addrOut", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("row", "I3");
   #pragma EVE_REG("col", "I4");
   

   __vcop_vloop(__vcop_compute(), 38u, 17u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(14), _VREG(27));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(16), _VREG(28));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(18), _VREG(24));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(20), _VREG(29));
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(28), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(29), _PREG(30), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(29), _PREG(31), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(32), _AGEN(1), _VPAIR(25,26), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(34), _AGEN(0), _VPAIR(22,23), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(8), _AGEN(0), _VPAIR(16,17), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(10), _AGEN(0), _VPAIR(18,19), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(12), _AGEN(0), _VPAIR(20,21), __vcop_alws());
   __vcop_vcmpeq(_VREG(25), _VREG(28), _VREG(30));
   __vcop_vcmpeq(_VREG(26), _VREG(28), _VREG(31));
   __vcop_vsel(_VREG(30), _VREG(16), _VREG(22));
   __vcop_vsel(_VREG(31), _VREG(17), _VREG(23));
   __vcop_vadd(_VREG(28), _VREG(27), _VREG(28));
   __vcop_vcmpeq(_VREG(25), _VREG(28), _VREG(30));
   __vcop_vcmpeq(_VREG(26), _VREG(28), _VREG(31));
   __vcop_vsel(_VREG(30), _VREG(20), _VREG(22));
   __vcop_vsel(_VREG(31), _VREG(21), _VREG(23));
   __vcop_vcmpgt(_VREG(25), _VREG(28), _VREG(30));
   __vcop_vcmpgt(_VREG(26), _VREG(28), _VREG(31));
   __vcop_vsel(_VREG(30), _VREG(18), _VREG(22));
   __vcop_vsel(_VREG(31), _VREG(19), _VREG(23));
   __vcop_vcmpge(_VREG(22), _VREG(29), _VREG(30));
   __vcop_vcmpge(_VREG(23), _VREG(29), _VREG(31));
   __vcop_vsub(_VREG(27), _VREG(27), _VREG(18));
   __vcop_vor(_VREG(18), _VREG(18), _VREG(16));
   __vcop_vor(_VREG(18), _VREG(18), _VREG(17));
   __vcop_vsel(_VREG(30), _VREG(27), _VREG(16));
   __vcop_vsel(_VREG(31), _VREG(27), _VREG(17));
   __vcop_vcmpge(_VREG(22), _VREG(24), _VREG(30));
   __vcop_vcmpge(_VREG(23), _VREG(24), _VREG(31));
   __vcop_vsel(_VREG(30), _VREG(28), _VREG(16));
   __vcop_vsel(_VREG(31), _VREG(28), _VREG(17));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(16,17), _PREG(22), _AGEN(2), _PREG(6));
   __vcop_vloop_end(1u);

}

void vcop_canny_nms_double_thresholding(
   __vptr_uint8 pIndex,
   __vptr_uint16 pCase1Max,
   __vptr_uint16 pCase2Max,
   __vptr_uint16 pCase3Max,
   __vptr_uint16 pCase4Max,
   __vptr_uint8 pOutVal,
   unsigned char lowThreshold,
   unsigned char highThreshold,
   unsigned short width,
   unsigned short height,
   unsigned short pitch,
   unsigned short outputPitch)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_canny_nms_double_thresholding_init(pIndex, pCase1Max, pCase2Max, pCase3Max, pCase4Max, pOutVal, lowThreshold, highThreshold, width, height, pitch, outputPitch, __pblock_vcop_canny_nms_double_thresholding);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_canny_nms_double_thresholding_vloops(__pblock_vcop_canny_nms_double_thresholding);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_canny_nms_double_thresholding_custom(
   __vptr_uint8 pIndex,
   __vptr_uint16 pCase1Max,
   __vptr_uint16 pCase2Max,
   __vptr_uint16 pCase3Max,
   __vptr_uint16 pCase4Max,
   __vptr_uint8 pOutVal,
   unsigned char lowThreshold,
   unsigned char highThreshold,
   unsigned short width,
   unsigned short height,
   unsigned short pitch,
   unsigned short outputPitch,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_canny_nms_double_thresholding_init(pIndex, pCase1Max, pCase2Max, pCase3Max, pCase4Max, pOutVal, lowThreshold, highThreshold, width, height, pitch, outputPitch, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_canny_nms_double_thresholding_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

