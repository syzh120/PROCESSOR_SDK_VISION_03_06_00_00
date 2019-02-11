#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_prune_big_list, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_prune_big_list, __ALIGNOF__(int));
unsigned short __pblock_vcop_prune_big_list[42];

unsigned int vcop_prune_big_list_param_count(void)
{
   return 42u;
}

unsigned int vcop_prune_big_list_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_prune_big_list_init(
   __vptr_uint32 inList_A,
   __vptr_uint16 inSortedIndexList_B,
   __vptr_uint32 inSortedIndexList32_B,
   __vptr_uint32 outList_C,
   __vptr_uint32 nonBestNSize_C,
   unsigned short threshold,
   unsigned short bestN,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (bestN)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)outList_C);
   __vcop_pblock_init16(pblock, __offset+_PREG(8), 4);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)inSortedIndexList_B);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)inList_A);
   __offset += 12;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (1)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)inSortedIndexList32_B+(bestN+8u)*sizeof(*inSortedIndexList32_B));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), 4294901760);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)inSortedIndexList32_B+bestN*sizeof(*inSortedIndexList32_B));
   __offset += 10;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((bestN+(2 * (8u))-1)/(2 * (8u)))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), -16);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), 255);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)inSortedIndexList32_B);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)inSortedIndexList32_B+8u*sizeof(*inSortedIndexList32_B));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)nonBestNSize_C);
   __vcop_pblock_init16(pblock, __offset+_PREG(16), 64);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), threshold);
   __offset += 20;

   return 42u;
}

void vcop_prune_big_list_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VSh", 16);
   #pragma VCC_VREG("Value", 17);
   #pragma VCC_VREG("Vdata1", 18);
   #pragma VCC_VREG("Vdata2", 19);
   #pragma VCC_VREG("Vindex", 20);
   #pragma VCC_VREG("Vindex1", 21);
   #pragma VCC_VREG("Vindex2", 22);
   #pragma VCC_VREG("Vt", 23);
   #pragma VCC_VREG("Vtabledata", 24);
   #pragma VCC_VREG("count", 25);
   #pragma VCC_VREG("count1", 26);
   #pragma VCC_VREG("count2", 27);
   #pragma VCC_VREG("flag", 28);
   #pragma VCC_VREG("flag1", 29);
   #pragma VCC_VREG("flag2", 30);
   #pragma VCC_VREG("mask1", 31);
   #pragma VCC_VREG("mask2", 32);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("index_addr", "A0");
   #pragma EVE_REG("out_addr", "A2");
   #pragma EVE_REG("table_addr", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_tablelkup(), 7u, 6u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(8), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(8), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(10), _AGEN(0), _VREG(20), __vcop_alws());
   __vcop_vtbload(__vcop_sizeWU(), __vcop_tableinfo(1, 1), _PREG(12), _AGEN(1), _VREG(20), _VREG(24), _PREG(0), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(24), _PREG(6), _AGEN(2), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   #pragma EVE_REG("index_addr", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 6u, 5u, 2u);
   __vcop_vinit(__vcop_sizeWU(), __vcop_alws(), _PREG(8), _VREG(20));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(20), _PREG(10), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(20), _PREG(6), _AGEN(1), _PREG(0));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   #pragma EVE_REG("index_addr", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 22u, 10u, 3u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(18), _VREG(25));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(20), _VREG(23));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(6), _VREG(16));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(8), _VREG(17));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(16), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(10), _AGEN(1), _VREG(21), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(12), _AGEN(1), _VREG(22), __vcop_alws());
   __vcop_vshf(_VREG(21), _VREG(16), _VREG(18));
   __vcop_vshf(_VREG(22), _VREG(16), _VREG(19));
   __vcop_vbitpk(_VREG(23), _VREG(18), _VREG(31));
   __vcop_vbitpk(_VREG(23), _VREG(19), _VREG(32));
   __vcop_vcmpgt(_VREG(17), _VREG(31), _VREG(29));
   __vcop_vcmpgt(_VREG(17), _VREG(32), _VREG(30));
   __vcop_vor(_VREG(29), _VREG(30), _VREG(28));
   __vcop_vbitc(_VREG(31), _VREG(26));
   __vcop_vbitc(_VREG(32), _VREG(27));
   __vcop_vadd(_VREG(25), _VREG(26), _VREG(25));
   __vcop_vadd(_VREG(25), _VREG(27), _VREG(25));
   __vcop_vexitnz(__vcop_level_vloop(), _VREG(28));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(25), _PREG(14), _AGEN(0), _PREG(0));
   __vcop_vloop_end(3u);

}

void vcop_prune_big_list(
   __vptr_uint32 inList_A,
   __vptr_uint16 inSortedIndexList_B,
   __vptr_uint32 inSortedIndexList32_B,
   __vptr_uint32 outList_C,
   __vptr_uint32 nonBestNSize_C,
   unsigned short threshold,
   unsigned short bestN)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_prune_big_list_init(inList_A, inSortedIndexList_B, inSortedIndexList32_B, outList_C, nonBestNSize_C, threshold, bestN, __pblock_vcop_prune_big_list);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_prune_big_list_vloops(__pblock_vcop_prune_big_list);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_prune_big_list_custom(
   __vptr_uint32 inList_A,
   __vptr_uint16 inSortedIndexList_B,
   __vptr_uint32 inSortedIndexList32_B,
   __vptr_uint32 outList_C,
   __vptr_uint32 nonBestNSize_C,
   unsigned short threshold,
   unsigned short bestN,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_prune_big_list_init(inList_A, inSortedIndexList_B, inSortedIndexList32_B, outList_C, nonBestNSize_C, threshold, bestN, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_prune_big_list_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

