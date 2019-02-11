#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_nnInterpolate420SPchroma, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_nnInterpolate420SPchroma, __ALIGNOF__(int));
unsigned short __pblock_vcop_nnInterpolate420SPchroma[36];

unsigned int vcop_nnInterpolate420SPchroma_param_count(void)
{
   return 36u;
}

unsigned int vcop_nnInterpolate420SPchroma_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_nnInterpolate420SPchroma_init(
   __vptr_uint8 src,
   __vptr_uint16 dst,
   unsigned short numMappedPixels,
   __vptr_uint16 tluIndexArray,
   __vptr_uint16 scatterStoreArray,
   __vptr_uint8 scratchHbuf8b,
   __vptr_uint16 scratchHbuf16b,
   long sat_high,
   long sat_high_set,
   long sat_low,
   long sat_low_set,
   unsigned short dst_end_offset,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   const int preg_ref1 = _PREG(10);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (numMappedPixels)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_4PARAM,preg_ref1,RM_NONE,0));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 2);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)scratchHbuf8b);
   __vcop_pblock_4param_init(pblock, __offset+_PREG(10), sat_high,sat_high_set,sat_low,sat_low_set);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)tluIndexArray);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)src);
   __offset += 16;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (1)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), dst_end_offset);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)scatterStoreArray+2*numMappedPixels);
   __offset += 8;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((numMappedPixels) + (8u)-1U) & ~((8u)-1U))/((8u)))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)dst);
   __vcop_pblock_init16(pblock, __offset+_PREG(8), 16);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)scratchHbuf16b);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)scatterStoreArray);
   __offset += 12;

   return 36u;
}

void vcop_nnInterpolate420SPchroma_vloops(
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
   

   __vcop_vloop(__vcop_tablelkup(), 7u, 8u, 1u);
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(7), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(14), _AGEN(0), _VREG(17), __vcop_alws());
   __vcop_vtbload(__vcop_sizeBU(), __vcop_tableinfo(1, 2), _PREG(16), _AGEN(1), _VREG(17), _VREG(16), _PREG(0), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(16), _PREG(8), _AGEN(2), _PREG(6));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Voffset", 18);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 4u, 4u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(6), _VREG(18));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(18), _PREG(8), _AGEN(0), _PREG(0));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("scatterStore", 19);
   #pragma VCC_VREG("srcUV", 20);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   #pragma EVE_REG("Addr2", "A1");
   #pragma EVE_REG("Addr_out", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 7u, 6u, 3u);
   __vcop_vagen(_AGEN(0), _PREG(8), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(8), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(10), _AGEN(0), _VREG(20), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(12), _AGEN(1), _VREG(19), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_sdda(_VREG(19)), __vcop_alws(), _VREG(20), _PREG(6), _AGEN(2), _PREG(0));
   __vcop_vloop_end(3u);

}

void vcop_nnInterpolate420SPchroma(
   __vptr_uint8 src,
   __vptr_uint16 dst,
   unsigned short numMappedPixels,
   __vptr_uint16 tluIndexArray,
   __vptr_uint16 scatterStoreArray,
   __vptr_uint8 scratchHbuf8b,
   __vptr_uint16 scratchHbuf16b,
   long sat_high,
   long sat_high_set,
   long sat_low,
   long sat_low_set,
   unsigned short dst_end_offset)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_nnInterpolate420SPchroma_init(src, dst, numMappedPixels, tluIndexArray, scatterStoreArray, scratchHbuf8b, scratchHbuf16b, sat_high, sat_high_set, sat_low, sat_low_set, dst_end_offset, __pblock_vcop_nnInterpolate420SPchroma);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_nnInterpolate420SPchroma_vloops(__pblock_vcop_nnInterpolate420SPchroma);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_nnInterpolate420SPchroma_custom(
   __vptr_uint8 src,
   __vptr_uint16 dst,
   unsigned short numMappedPixels,
   __vptr_uint16 tluIndexArray,
   __vptr_uint16 scatterStoreArray,
   __vptr_uint8 scratchHbuf8b,
   __vptr_uint16 scratchHbuf16b,
   long sat_high,
   long sat_high_set,
   long sat_low,
   long sat_low_set,
   unsigned short dst_end_offset,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_nnInterpolate420SPchroma_init(src, dst, numMappedPixels, tluIndexArray, scatterStoreArray, scratchHbuf8b, scratchHbuf16b, sat_high, sat_high_set, sat_low, sat_low_set, dst_end_offset, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_nnInterpolate420SPchroma_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_nnInterpolate420SPchromaBB, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_nnInterpolate420SPchromaBB, __ALIGNOF__(int));
unsigned short __pblock_vcop_nnInterpolate420SPchromaBB[16];

unsigned int vcop_nnInterpolate420SPchromaBB_param_count(void)
{
   return 16u;
}

unsigned int vcop_nnInterpolate420SPchromaBB_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_nnInterpolate420SPchromaBB_init(
   __vptr_uint8 src,
   __vptr_uint8 dst,
   unsigned short outputBlockSize,
   __vptr_uint16 tluIndexArray,
   long sat_high,
   long sat_high_set,
   long sat_low,
   long sat_low_set,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   const int preg_ref2 = _PREG(10);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (outputBlockSize)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_4PARAM,preg_ref2,RM_NONE,0));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 2);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)dst);
   __vcop_pblock_4param_init(pblock, __offset+_PREG(10), sat_high,sat_high_set,sat_low,sat_low_set);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)tluIndexArray);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)src);
   __offset += 16;

   return 16u;
}

void vcop_nnInterpolate420SPchromaBB_vloops(
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
   

   __vcop_vloop(__vcop_tablelkup(), 7u, 8u, 1u);
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(7), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(14), _AGEN(0), _VREG(17), __vcop_alws());
   __vcop_vtbload(__vcop_sizeBU(), __vcop_tableinfo(1, 2), _PREG(16), _AGEN(1), _VREG(17), _VREG(16), _PREG(0), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(16), _PREG(8), _AGEN(2), _PREG(6));
   __vcop_vloop_end(1u);

}

void vcop_nnInterpolate420SPchromaBB(
   __vptr_uint8 src,
   __vptr_uint8 dst,
   unsigned short outputBlockSize,
   __vptr_uint16 tluIndexArray,
   long sat_high,
   long sat_high_set,
   long sat_low,
   long sat_low_set)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_nnInterpolate420SPchromaBB_init(src, dst, outputBlockSize, tluIndexArray, sat_high, sat_high_set, sat_low, sat_low_set, __pblock_vcop_nnInterpolate420SPchromaBB);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_nnInterpolate420SPchromaBB_vloops(__pblock_vcop_nnInterpolate420SPchromaBB);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_nnInterpolate420SPchromaBB_custom(
   __vptr_uint8 src,
   __vptr_uint8 dst,
   unsigned short outputBlockSize,
   __vptr_uint16 tluIndexArray,
   long sat_high,
   long sat_high_set,
   long sat_low,
   long sat_low_set,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_nnInterpolate420SPchromaBB_init(src, dst, outputBlockSize, tluIndexArray, sat_high, sat_high_set, sat_low, sat_low_set, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_nnInterpolate420SPchromaBB_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

