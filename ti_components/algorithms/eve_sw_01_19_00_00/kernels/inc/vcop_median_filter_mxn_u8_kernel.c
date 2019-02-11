#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_select_kth_smallest_from_hist, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_select_kth_smallest_from_hist, __ALIGNOF__(int));
unsigned short __pblock_vcop_select_kth_smallest_from_hist[56];

unsigned int vcop_select_kth_smallest_from_hist_param_count(void)
{
   return 56u;
}

unsigned int vcop_select_kth_smallest_from_hist_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_select_kth_smallest_from_hist_init(
   __vptr_int16 blk_histo_B,
   __vptr_int16 coarse_hist_scratch_A,
   __vptr_int16 hist_scratch_C,
   __vptr_uint8 optr_A,
   unsigned short k,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (16)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)blk_histo_B+16);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)hist_scratch_C);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)hist_scratch_C+36*8u);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)coarse_hist_scratch_A);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)coarse_hist_scratch_A+2*8u);
   __vcop_pblock_init16(pblock, __offset+_PREG(16), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(17), -480);
   __vcop_pblock_init16(pblock, __offset+_PREG(18), 2);
   __vcop_pblock_init16(pblock, __offset+_PREG(19), -30);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)blk_histo_B);
   __offset += 22;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (16)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), 16);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)coarse_hist_scratch_A);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)hist_scratch_C);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)blk_histo_B);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), 2);
   __vcop_pblock_init16(pblock, __offset+_PREG(15), -30);
   __vcop_pblock_init16(pblock, __offset+_PREG(16), 36);
   __vcop_pblock_init16(pblock, __offset+_PREG(17), -540);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), k);
   __offset += 20;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (16)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)blk_histo_B+30);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)optr_A);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), -2);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), 30);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), 1);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), 0);
   __offset += 14;

   return 56u;
}

void vcop_select_kth_smallest_from_hist_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vidx", 16);
   #pragma VCC_VREG("Vk", 17);
   #pragma VCC_VREG("Vsum", 18);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vacc1", 19);
   #pragma VCC_VREG("Vacc2", 20);
   #pragma VCC_VREG("Vin1", 21);
   #pragma VCC_VREG("Vin2", 22);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("A2", "A0");
   #pragma EVE_REG("A0", "A1");
   #pragma EVE_REG("A1", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I0", "I3");
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 14u, 11u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(20), _VREG(19));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(20), _VREG(20));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(16), _PREG(17), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(18), _PREG(19), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(22), _AGEN(1), _VREG(21), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(6), _AGEN(1), _VREG(22), __vcop_alws());
   __vcop_vadd(_VREG(19), _VREG(21), _VREG(19));
   __vcop_vadd(_VREG(20), _VREG(22), _VREG(20));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_offst_np1(), __vcop_alws(), _VREG(21), _PREG(8), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_offst_np1(), __vcop_alws(), _VREG(22), _PREG(10), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_npt(), __vcop_last_i4(), _VREG(19), _PREG(12), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_npt(), __vcop_last_i4(), _VREG(20), _PREG(14), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VK16", 23);
   #pragma VCC_VREG("Vin", 24);
   #pragma VCC_VREG("flag", 25);
   #pragma VCC_VREG("Vin1", 26);
   #pragma VCC_VREG("Vin2", 27);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("A2", "A0");
   #pragma EVE_REG("A0", "A1");
   #pragma EVE_REG("A1", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I0", "I3");
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 16u, 10u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(18), _VREG(18));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(18), _VREG(16));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(20), _VREG(17));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(6), _VREG(23));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(18), _VREG(25));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(14), _PREG(15), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(16), _PREG(17), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_1pt(), _PREG(8), _AGEN(1), _VREG(24), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(10), _AGEN(2), _VPAIR(26,27), __vcop_alws());
   __vcop_vadd(_VREG(18), _VREG(24), _VREG(18));
   __vcop_vadd(_VREG(16), _VREG(23), _VREG(16));
   __vcop_vcmpge(_VREG(18), _VREG(17), _VREG(25));
   __vcop_vexitnz(__vcop_level_vloop(), _VREG(25));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_alws(), _VPAIR(26,27), _PREG(12), _AGEN(0), _PREG(0));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VK1", 28);
   #pragma VCC_VREG("Vin", 29);
   #pragma VCC_VREG("flag", 30);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("A2", "A0");
   #pragma EVE_REG("A0", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I0", "I3");
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 11u, 7u, 3u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(12), _VREG(28));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(14), _VREG(30));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(10), _PREG(11), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_1pt(), _PREG(6), _AGEN(1), _VREG(29), __vcop_alws());
   __vcop_vsub(_VREG(18), _VREG(29), _VREG(18));
   __vcop_vsub(_VREG(16), _VREG(28), _VREG(16));
   __vcop_vcmplt(_VREG(18), _VREG(17), _VREG(30));
   __vcop_vexitnz(__vcop_level_vloop(), _VREG(30));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_1pt(), __vcop_alws(), _VREG(16), _PREG(8), _AGEN(0), _PREG(0));
   __vcop_vloop_end(3u);

}

void vcop_select_kth_smallest_from_hist(
   __vptr_int16 blk_histo_B,
   __vptr_int16 coarse_hist_scratch_A,
   __vptr_int16 hist_scratch_C,
   __vptr_uint8 optr_A,
   unsigned short k)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_select_kth_smallest_from_hist_init(blk_histo_B, coarse_hist_scratch_A, hist_scratch_C, optr_A, k, __pblock_vcop_select_kth_smallest_from_hist);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_select_kth_smallest_from_hist_vloops(__pblock_vcop_select_kth_smallest_from_hist);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_select_kth_smallest_from_hist_custom(
   __vptr_int16 blk_histo_B,
   __vptr_int16 coarse_hist_scratch_A,
   __vptr_int16 hist_scratch_C,
   __vptr_uint8 optr_A,
   unsigned short k,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_select_kth_smallest_from_hist_init(blk_histo_B, coarse_hist_scratch_A, hist_scratch_C, optr_A, k, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_select_kth_smallest_from_hist_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_update_block_histogram_8c, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_update_block_histogram_8c, __ALIGNOF__(int));
unsigned short __pblock_vcop_update_block_histogram_8c[100];

unsigned int vcop_update_block_histogram_8c_param_count(void)
{
   return 100u;
}

unsigned int vcop_update_block_histogram_8c_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_update_block_histogram_8c_init(
   __vptr_uint8 inp_data_A,
   __vptr_uint8 last_strip_A,
   __vptr_int16 histo_B,
   __vptr_int8 wgt_ones_C,
   __vptr_int8 wgt_delta_C,
   __vptr_int16 scratch_histo_C,
   __vptr_int16 blk_histo_B,
   unsigned int blk_wdth,
   unsigned int blk_hght,
   unsigned int blk_stride,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (((8)*256)/(2*(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)histo_B);
   __offset += 10;

   /* Loop 2 PREGS */
   const int preg_ref1 = _PREG(10);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (blk_hght)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (((8)*((blk_wdth-1)/(8)))/(8))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_4PARAM,preg_ref1,RM_NONE,0));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 8);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)histo_B);
   __vcop_pblock_4param_init(pblock, __offset+_PREG(10), 255, 255, 0, 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), ((blk_stride*sizeof(*inp_data_A))) -(8*sizeof(*inp_data_A))*((((8)*((blk_wdth-1)/(8)))/(8))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)inp_data_A);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)wgt_ones_C);
   __offset += 18;

   /* Loop 3 PREGS */
   const int preg_ref2 = _PREG(10);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (blk_hght)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_4PARAM,preg_ref2,RM_NONE,0));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), ((blk_stride*sizeof(*inp_data_A))));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)histo_B);
   __vcop_pblock_4param_init(pblock, __offset+_PREG(10), 255, 255, 0, 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)last_strip_A);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)wgt_delta_C);
   __offset += 16;

   /* Loop 4 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (16)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (2)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)histo_B+32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)histo_B+2*32);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)histo_B+3*32);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)histo_B+4*32);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)histo_B+5*32);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)histo_B+6*32);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)histo_B+7*32);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)scratch_histo_C);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)scratch_histo_C+36*8u);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)scratch_histo_C+2*36*8u);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)scratch_histo_C+3*36*8u);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)scratch_histo_C+4*36*8u);
   __vcop_pblock_init32(pblock, __offset+_PREG(30), (uchar *)scratch_histo_C+5*36*8u);
   __vcop_pblock_init32(pblock, __offset+_PREG(32), (uchar *)scratch_histo_C+6*36*8u);
   __vcop_pblock_init32(pblock, __offset+_PREG(34), (uchar *)scratch_histo_C+7*36*8u);
   __vcop_pblock_init16(pblock, __offset+_PREG(36), 2);
   __vcop_pblock_init16(pblock, __offset+_PREG(37), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(38), 240);
   __vcop_pblock_init32(pblock, __offset+_PREG(40), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(42), (uchar *)histo_B);
   __offset += 42;

   /* Loop 5 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (8)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (4)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)blk_histo_B);
   __vcop_pblock_init16(pblock, __offset+_PREG(8), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(9), 72);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), -180);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), 36);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)scratch_histo_C);
   __offset += 14;

   return 100u;
}

void vcop_update_block_histogram_8c_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VKe_0", 16);
   #pragma VCC_VREG("VKo_0", 17);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("A0", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 5u, 5u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(8), _VREG(17));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(8), _VREG(16));
   __vcop_vagen(_AGEN(0), _PREG(6), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_alws(), _VPAIR(17,16), _PREG(10), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vdata", 18);
   #pragma VCC_VREG("Vindex", 19);
   #pragma VCC_VREG("Vweight", 20);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("hist_agen", "A1");
   #pragma EVE_REG("ind_agen", "A0");
   #pragma EVE_REG("wgt_agen", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_histogram(), 9u, 9u, 2u);
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(14), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(16), _AGEN(0), _VREG(19), __vcop_alws());
   __vcop_vload(__vcop_sizeB(), __vcop_npt(), _PREG(18), _AGEN(2), _VREG(20), __vcop_alws());
   __vcop_vhistload(__vcop_sizeH(), 8, _PREG(8), _AGEN(1), _VREG(19), _VREG(18), _PREG(6), __vcop_alws());
   __vcop_hist_vadd(_VREG(18), _VREG(20), _VREG(18));
   __vcop_vhiststore(__vcop_sizeH(), 8, __vcop_alws(), _VREG(18), _PREG(8), _AGEN(1), _VREG(19));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vdata", 21);
   #pragma VCC_VREG("Vindex", 22);
   #pragma VCC_VREG("Vweight", 23);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("hist_agen", "A1");
   #pragma EVE_REG("ind_agen", "A0");
   #pragma EVE_REG("wgt_agen", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_histogram(), 9u, 8u, 3u);
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(14), _AGEN(0), _VREG(22), __vcop_alws());
   __vcop_vload(__vcop_sizeB(), __vcop_npt(), _PREG(16), _AGEN(2), _VREG(23), __vcop_alws());
   __vcop_vhistload(__vcop_sizeH(), 8, _PREG(8), _AGEN(1), _VREG(22), _VREG(21), _PREG(6), __vcop_alws());
   __vcop_hist_vadd(_VREG(21), _VREG(23), _VREG(21));
   __vcop_vhiststore(__vcop_sizeH(), 8, __vcop_alws(), _VREG(21), _PREG(8), _AGEN(1), _VREG(22));
   __vcop_vloop_end(3u);

   /* VLOOP 4 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vacc1", 24);
   #pragma VCC_VREG("Vacc2", 25);
   #pragma VCC_VREG("Vacc3", 26);
   #pragma VCC_VREG("Vacc4", 27);
   #pragma VCC_VREG("Vacc5", 28);
   #pragma VCC_VREG("Vacc6", 29);
   #pragma VCC_VREG("Vacc7", 30);
   #pragma VCC_VREG("Vacc8", 31);
   #pragma VCC_VREG("Vin1", 32);
   #pragma VCC_VREG("Vin2", 33);
   #pragma VCC_VREG("Vin3", 34);
   #pragma VCC_VREG("Vin4", 35);
   #pragma VCC_VREG("Vin5", 36);
   #pragma VCC_VREG("Vin6", 37);
   #pragma VCC_VREG("Vin7", 38);
   #pragma VCC_VREG("Vin8", 39);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("A1", "A0");
   #pragma EVE_REG("A0", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 35u, 21u, 4u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(40), _VREG(24));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(40), _VREG(25));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(40), _VREG(26));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(40), _VREG(27));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(40), _VREG(28));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(40), _VREG(29));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(40), _VREG(30));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(40), _VREG(31));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(36), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(37), _PREG(38), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(42), _AGEN(1), _VREG(32), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(6), _AGEN(1), _VREG(33), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(8), _AGEN(1), _VREG(34), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(10), _AGEN(1), _VREG(35), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(12), _AGEN(1), _VREG(36), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(14), _AGEN(1), _VREG(37), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(16), _AGEN(1), _VREG(38), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(18), _AGEN(1), _VREG(39), __vcop_alws());
   __vcop_vadd(_VREG(24), _VREG(32), _VREG(24));
   __vcop_vadd(_VREG(25), _VREG(33), _VREG(25));
   __vcop_vadd(_VREG(26), _VREG(34), _VREG(26));
   __vcop_vadd(_VREG(27), _VREG(35), _VREG(27));
   __vcop_vadd(_VREG(28), _VREG(36), _VREG(28));
   __vcop_vadd(_VREG(29), _VREG(37), _VREG(29));
   __vcop_vadd(_VREG(30), _VREG(38), _VREG(30));
   __vcop_vadd(_VREG(31), _VREG(39), _VREG(31));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_offst_np1(), __vcop_last_i4(), _VREG(24), _PREG(20), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_offst_np1(), __vcop_last_i4(), _VREG(25), _PREG(22), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_offst_np1(), __vcop_last_i4(), _VREG(26), _PREG(24), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_offst_np1(), __vcop_last_i4(), _VREG(27), _PREG(26), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_offst_np1(), __vcop_last_i4(), _VREG(28), _PREG(28), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_offst_np1(), __vcop_last_i4(), _VREG(29), _PREG(30), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_offst_np1(), __vcop_last_i4(), _VREG(30), _PREG(32), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_offst_np1(), __vcop_last_i4(), _VREG(31), _PREG(34), _AGEN(0), _PREG(0));
   __vcop_vloop_end(4u);

   /* VLOOP 5 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vacc1", 40);
   #pragma VCC_VREG("Vacc2", 41);
   #pragma VCC_VREG("Vin1", 42);
   #pragma VCC_VREG("Vin2", 43);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("A1", "A0");
   #pragma EVE_REG("A0", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I2");
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 9u, 7u, 5u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(12), _VREG(40));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(12), _VREG(41));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(8), _PREG(8), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(9), _PREG(10), _PREG(11), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(14), _AGEN(1), _VPAIR(42,43), __vcop_alws());
   __vcop_vadd(_VREG(40), _VREG(42), _VREG(40));
   __vcop_vadd(_VREG(41), _VREG(43), _VREG(41));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_last_i4(), _VPAIR(40,41), _PREG(6), _AGEN(0), _PREG(0));
   __vcop_vloop_end(5u);

}

void vcop_update_block_histogram_8c(
   __vptr_uint8 inp_data_A,
   __vptr_uint8 last_strip_A,
   __vptr_int16 histo_B,
   __vptr_int8 wgt_ones_C,
   __vptr_int8 wgt_delta_C,
   __vptr_int16 scratch_histo_C,
   __vptr_int16 blk_histo_B,
   unsigned int blk_wdth,
   unsigned int blk_hght,
   unsigned int blk_stride)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_update_block_histogram_8c_init(inp_data_A, last_strip_A, histo_B, wgt_ones_C, wgt_delta_C, scratch_histo_C, blk_histo_B, blk_wdth, blk_hght, blk_stride, __pblock_vcop_update_block_histogram_8c);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_update_block_histogram_8c_vloops(__pblock_vcop_update_block_histogram_8c);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_update_block_histogram_8c_custom(
   __vptr_uint8 inp_data_A,
   __vptr_uint8 last_strip_A,
   __vptr_int16 histo_B,
   __vptr_int8 wgt_ones_C,
   __vptr_int8 wgt_delta_C,
   __vptr_int16 scratch_histo_C,
   __vptr_int16 blk_histo_B,
   unsigned int blk_wdth,
   unsigned int blk_hght,
   unsigned int blk_stride,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_update_block_histogram_8c_init(inp_data_A, last_strip_A, histo_B, wgt_ones_C, wgt_delta_C, scratch_histo_C, blk_histo_B, blk_wdth, blk_hght, blk_stride, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_update_block_histogram_8c_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

