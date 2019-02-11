#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_nnInterpolate8b, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_nnInterpolate8b, __ALIGNOF__(int));
unsigned short __pblock_vcop_nnInterpolate8b[38];

unsigned int vcop_nnInterpolate8b_param_count(void)
{
   return 38u;
}

unsigned int vcop_nnInterpolate8b_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_nnInterpolate8b_init(
   __vptr_uint8 src,
   __vptr_uint8 dst,
   unsigned short outputBlockSize,
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 fracArray,
   __vptr_uint16 scratch,
   __vptr_uint16 stride_ptr,
   unsigned char QShift,
   long sat_high,
   long sat_high_set,
   long sat_low,
   long sat_low_set,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((outputBlockSize) + 2U*(8u)-1U) & ~(2U*(8u)-1U))/(2*(8u)))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)stride_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), 0x000000000F);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), -4);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)tluIndexArray);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)fracArray);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)scratch);
   __vcop_pblock_init16(pblock, __offset+_PREG(18), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(19), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), -QShift);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), QShift);
   __offset += 22;

   /* Loop 2 PREGS */
   const int preg_ref1 = _PREG(10);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (outputBlockSize)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_4PARAM,preg_ref1,RM_NONE,0));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 2);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)dst);
   __vcop_pblock_4param_init(pblock, __offset+_PREG(10), sat_high,sat_high_set,sat_low,sat_low_set);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)scratch);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)src);
   __offset += 16;

   return 38u;
}

void vcop_nnInterpolate8b_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VQShift", 16);
   #pragma VCC_VREG("Vstride", 17);
   #pragma VCC_VREG("negVQShift", 18);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vmaskx", 19);
   #pragma VCC_VREG("Vshifty", 20);
   #pragma VCC_VREG("fracMap1", 21);
   #pragma VCC_VREG("fracMap2", 22);
   #pragma VCC_VREG("roundedYFrac1", 23);
   #pragma VCC_VREG("roundedYFrac2", 24);
   #pragma VCC_VREG("tluIndex1", 25);
   #pragma VCC_VREG("tluIndex2", 26);
   #pragma VCC_VREG("yFrac1", 27);
   #pragma VCC_VREG("yFrac2", 28);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   #pragma EVE_REG("Addr1", "A1");
   #pragma EVE_REG("Addr2", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 18u, 11u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(20), _VREG(18));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(22), _VREG(16));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(8), _VREG(19));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(10), _VREG(20));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(18), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(19), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(6), _AGEN(0), _VREG(17), __vcop_once());
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(12), _AGEN(2), _VPAIR(25,26), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(14), _AGEN(1), _VPAIR(21,22), __vcop_alws());
   __vcop_vshf(_VREG(21), _VREG(20), _VREG(27));
   __vcop_vshf(_VREG(22), _VREG(20), _VREG(28));
   __vcop_vrnd(_VREG(27), _VREG(16), _VREG(23));
   __vcop_vrnd(_VREG(28), _VREG(16), _VREG(24));
   __vcop_vmadd(_VREG(23), _VREG(17), _VREG(25), _PREG(0));
   __vcop_vmadd(_VREG(24), _VREG(17), _VREG(26), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(25,26), _PREG(16), _AGEN(2), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vdata", 29);
   #pragma VCC_VREG("Vindex", 30);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("TLU_agen", "A1");
   #pragma EVE_REG("ind_agen", "A0");
   #pragma EVE_REG("out_agen", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_tablelkup(), 7u, 8u, 2u);
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(1), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(14), _AGEN(0), _VREG(30), __vcop_alws());
   __vcop_vtbload(__vcop_sizeBU(), __vcop_tableinfo(1, 1), _PREG(16), _AGEN(1), _VREG(30), _VREG(29), _PREG(0), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(29), _PREG(8), _AGEN(2), _PREG(6));
   __vcop_vloop_end(2u);

}

void vcop_nnInterpolate8b(
   __vptr_uint8 src,
   __vptr_uint8 dst,
   unsigned short outputBlockSize,
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 fracArray,
   __vptr_uint16 scratch,
   __vptr_uint16 stride_ptr,
   unsigned char QShift,
   long sat_high,
   long sat_high_set,
   long sat_low,
   long sat_low_set)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_nnInterpolate8b_init(src, dst, outputBlockSize, tluIndexArray, fracArray, scratch, stride_ptr, QShift, sat_high, sat_high_set, sat_low, sat_low_set, __pblock_vcop_nnInterpolate8b);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_nnInterpolate8b_vloops(__pblock_vcop_nnInterpolate8b);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_nnInterpolate8b_custom(
   __vptr_uint8 src,
   __vptr_uint8 dst,
   unsigned short outputBlockSize,
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 fracArray,
   __vptr_uint16 scratch,
   __vptr_uint16 stride_ptr,
   unsigned char QShift,
   long sat_high,
   long sat_high_set,
   long sat_low,
   long sat_low_set,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_nnInterpolate8b_init(src, dst, outputBlockSize, tluIndexArray, fracArray, scratch, stride_ptr, QShift, sat_high, sat_high_set, sat_low, sat_low_set, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_nnInterpolate8b_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

