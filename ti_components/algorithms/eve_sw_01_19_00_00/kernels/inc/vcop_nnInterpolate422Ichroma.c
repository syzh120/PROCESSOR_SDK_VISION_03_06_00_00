#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_nnInterpolate422Ichroma, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_nnInterpolate422Ichroma, __ALIGNOF__(int));
unsigned short __pblock_vcop_nnInterpolate422Ichroma[36];

unsigned int vcop_nnInterpolate422Ichroma_param_count(void)
{
   return 36u;
}

unsigned int vcop_nnInterpolate422Ichroma_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_nnInterpolate422Ichroma_init(
   __vptr_uint8 src,
   __vptr_uint8 dst,
   unsigned short numMappedPixels,
   __vptr_uint16 tluIndexArray,
   __vptr_uint16 scatterStoreArray,
   __vptr_uint8 scratchHbuf,
   unsigned short src_size,
   long sat_high,
   long sat_high_set,
   long sat_low,
   long sat_low_set,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   const int preg_ref1 = _PREG(8);
   const int preg_ref2 = _PREG(14);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (numMappedPixels)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_4PARAM,preg_ref1,RM_NONE,0));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), __vcop_store_round_sat(SM_4PARAM,preg_ref2,RM_NONE,0));
   __vcop_pblock_4param_init(pblock, __offset+_PREG(8), src_size, src_size, 0, 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)scratchHbuf);
   __vcop_pblock_4param_init(pblock, __offset+_PREG(14), sat_high,sat_high_set,sat_low,sat_low_set);
   __vcop_pblock_init16(pblock, __offset+_PREG(18), 2);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)tluIndexArray);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)src);
   __offset += 22;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((numMappedPixels) + (8u)-1U) & ~((8u)-1U))/((8u)))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)scatterStoreArray);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)dst);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), 16);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), 1);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)scratchHbuf);
   __offset += 14;

   return 36u;
}

void vcop_nnInterpolate422Ichroma_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vdata", 16);
   #pragma VCC_VREG("Vindex", 17);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("TLU_agen", "A1");
   #pragma EVE_REG("ind_agen", "A0");
   #pragma EVE_REG("out_agen", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_tablelkup(), 7u, 11u, 1u);
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(0), _PREG(18), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(1), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(20), _AGEN(0), _VREG(17), __vcop_alws());
   __vcop_vtbload(__vcop_sizeBU(), __vcop_tableinfo(1, 1), _PREG(22), _AGEN(1), _VREG(17), _VREG(16), _PREG(6), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(16), _PREG(12), _AGEN(2), _PREG(7));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vin1", 18);
   #pragma VCC_VREG("Vone", 19);
   #pragma VCC_VREG("scatterStore", 20);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   #pragma EVE_REG("Addr2", "A1");
   #pragma EVE_REG("Addr_out", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 9u, 7u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(12), _VREG(19));
   __vcop_vagen(_AGEN(0), _PREG(10), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(11), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(14), _AGEN(0), _VREG(18), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(6), _AGEN(1), _VREG(20), __vcop_alws());
   __vcop_vshf(_VREG(20), _VREG(19), _VREG(20));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_sdda(_VREG(20)), __vcop_alws(), _VREG(18), _PREG(8), _AGEN(2), _PREG(0));
   __vcop_vloop_end(2u);

}

void vcop_nnInterpolate422Ichroma(
   __vptr_uint8 src,
   __vptr_uint8 dst,
   unsigned short numMappedPixels,
   __vptr_uint16 tluIndexArray,
   __vptr_uint16 scatterStoreArray,
   __vptr_uint8 scratchHbuf,
   unsigned short src_size,
   long sat_high,
   long sat_high_set,
   long sat_low,
   long sat_low_set)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_nnInterpolate422Ichroma_init(src, dst, numMappedPixels, tluIndexArray, scatterStoreArray, scratchHbuf, src_size, sat_high, sat_high_set, sat_low, sat_low_set, __pblock_vcop_nnInterpolate422Ichroma);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_nnInterpolate422Ichroma_vloops(__pblock_vcop_nnInterpolate422Ichroma);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_nnInterpolate422Ichroma_custom(
   __vptr_uint8 src,
   __vptr_uint8 dst,
   unsigned short numMappedPixels,
   __vptr_uint16 tluIndexArray,
   __vptr_uint16 scatterStoreArray,
   __vptr_uint8 scratchHbuf,
   unsigned short src_size,
   long sat_high,
   long sat_high_set,
   long sat_low,
   long sat_low_set,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_nnInterpolate422Ichroma_init(src, dst, numMappedPixels, tluIndexArray, scatterStoreArray, scratchHbuf, src_size, sat_high, sat_high_set, sat_low, sat_low_set, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_nnInterpolate422Ichroma_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_nnInterpolate422IchromaBB, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_nnInterpolate422IchromaBB, __ALIGNOF__(int));
unsigned short __pblock_vcop_nnInterpolate422IchromaBB[28];

unsigned int vcop_nnInterpolate422IchromaBB_param_count(void)
{
   return 28u;
}

unsigned int vcop_nnInterpolate422IchromaBB_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_nnInterpolate422IchromaBB_init(
   __vptr_uint8 src,
   __vptr_uint8 dst,
   unsigned short outputBlockSize,
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 scratchHbuf,
   __vptr_uint8 scattered_ofst,
   long sat_high,
   long sat_high_set,
   long sat_low,
   long sat_low_set,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   const int preg_ref3 = _PREG(10);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (outputBlockSize)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_4PARAM,preg_ref3,RM_NONE,0));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 2);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)scratchHbuf);
   __vcop_pblock_4param_init(pblock, __offset+_PREG(10), sat_high,sat_high_set,sat_low,sat_low_set);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)tluIndexArray);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)src);
   __offset += 16;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((outputBlockSize) + (8u)-1U) & ~((8u)-1U))/((8u)))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)dst);
   __vcop_pblock_init16(pblock, __offset+_PREG(8), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(9), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)scattered_ofst);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)scratchHbuf);
   __offset += 12;

   return 28u;
}

void vcop_nnInterpolate422IchromaBB_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("scat_ofst", 16);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vdata", 17);
   #pragma VCC_VREG("Vindex", 18);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("TLU_agen", "A1");
   #pragma EVE_REG("ind_agen", "A0");
   #pragma EVE_REG("out_agen", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_tablelkup(), 7u, 8u, 1u);
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(1), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(14), _AGEN(0), _VREG(18), __vcop_alws());
   __vcop_vtbload(__vcop_sizeBU(), __vcop_tableinfo(1, 1), _PREG(16), _AGEN(1), _VREG(18), _VREG(17), _PREG(0), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(17), _PREG(8), _AGEN(2), _PREG(6));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vin1", 19);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   #pragma EVE_REG("Addr1", "A1");
   #pragma EVE_REG("Addr2", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 7u, 6u, 2u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(8), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(9), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(10), _AGEN(0), _VREG(16), __vcop_once());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(12), _AGEN(1), _VREG(19), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_pdda(_VREG(16)), __vcop_alws(), _VREG(19), _PREG(6), _AGEN(2), _PREG(0));
   __vcop_vloop_end(2u);

}

void vcop_nnInterpolate422IchromaBB(
   __vptr_uint8 src,
   __vptr_uint8 dst,
   unsigned short outputBlockSize,
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 scratchHbuf,
   __vptr_uint8 scattered_ofst,
   long sat_high,
   long sat_high_set,
   long sat_low,
   long sat_low_set)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_nnInterpolate422IchromaBB_init(src, dst, outputBlockSize, tluIndexArray, scratchHbuf, scattered_ofst, sat_high, sat_high_set, sat_low, sat_low_set, __pblock_vcop_nnInterpolate422IchromaBB);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_nnInterpolate422IchromaBB_vloops(__pblock_vcop_nnInterpolate422IchromaBB);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_nnInterpolate422IchromaBB_custom(
   __vptr_uint8 src,
   __vptr_uint8 dst,
   unsigned short outputBlockSize,
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 scratchHbuf,
   __vptr_uint8 scattered_ofst,
   long sat_high,
   long sat_high_set,
   long sat_low,
   long sat_low_set,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_nnInterpolate422IchromaBB_init(src, dst, outputBlockSize, tluIndexArray, scratchHbuf, scattered_ofst, sat_high, sat_high_set, sat_low, sat_low_set, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_nnInterpolate422IchromaBB_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

