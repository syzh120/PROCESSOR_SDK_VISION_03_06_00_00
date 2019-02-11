#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_BayerCFA_interpolate_short_BGGR, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_BayerCFA_interpolate_short_BGGR, __ALIGNOF__(int));
unsigned short __pblock_vcop_BayerCFA_interpolate_short_BGGR[76];

unsigned int vcop_BayerCFA_interpolate_short_BGGR_param_count(void)
{
   return 76u;
}

unsigned int vcop_BayerCFA_interpolate_short_BGGR_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_BayerCFA_interpolate_short_BGGR_init(
   __vptr_uint16 CFA_short,
   unsigned int in_w,
   unsigned int blk_w,
   unsigned int blk_h,
   __vptr_uint16 R_short,
   __vptr_uint16 G_short,
   __vptr_uint16 B_short,
   unsigned int out_stride,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (((blk_h/2) +1))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (((blk_w/((8u) * 2))+1))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)CFA_short+in_w*sizeof(*CFA_short));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)B_short);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)G_short);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)R_short);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)G_short+out_stride*sizeof(*CFA_short));
   __vcop_pblock_init16(pblock, __offset+_PREG(16), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(17), (2*in_w*sizeof(*CFA_short)) -(2*(sizeof(*CFA_short)*8u))*((((blk_w/((8u) * 2))+1))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(18), (2*out_stride*sizeof(*CFA_short)) -(2*(sizeof(*CFA_short)*8u))*((((blk_w/((8u) * 2))+1))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)CFA_short);
   __offset += 22;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (((blk_h/2)+1))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (blk_w/((8u) * 2))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_TRUNC,1));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)R_short);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)R_short+2*sizeof(*CFA_short));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)B_short+sizeof(*CFA_short));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)R_short+sizeof(*CFA_short));
   __vcop_pblock_init16(pblock, __offset+_PREG(16), (2*out_stride*sizeof(*CFA_short)) -(2*8u*sizeof(*CFA_short))*((blk_w/((8u) * 2))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)B_short);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)B_short+2*sizeof(*CFA_short));
   __offset += 20;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((blk_h+1))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (blk_w/((8u) * 2))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_TRUNC,1));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)G_short+sizeof(*CFA_short));
   __vcop_pblock_init16(pblock, __offset+_PREG(10), (out_stride*sizeof(*CFA_short)) -(2*8u*sizeof(*CFA_short))*((blk_w/((8u) * 2))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)G_short);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)G_short+2*sizeof(*CFA_short));
   __offset += 14;

   /* Loop 4 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (blk_w/((8u) * 2))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (blk_h/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_TRUNC,1));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)B_short+2*out_stride*sizeof(*CFA_short));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)R_short+2*out_stride*sizeof(*CFA_short));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)B_short+out_stride*sizeof(*CFA_short));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)R_short+out_stride*sizeof(*CFA_short));
   __vcop_pblock_init16(pblock, __offset+_PREG(16), (2*out_stride*sizeof(*CFA_short)));
   __vcop_pblock_init16(pblock, __offset+_PREG(17), (2*8u*sizeof(*CFA_short)) -(2*out_stride*sizeof(*CFA_short))*((blk_h/2)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)B_short);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)R_short);
   __offset += 20;

   return 76u;
}

void vcop_BayerCFA_interpolate_short_BGGR_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vzero_a", 16);
   #pragma VCC_VREG("Vzero_b", 17);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VB0", 18);
   #pragma VCC_VREG("VB0_copy", 19);
   #pragma VCC_VREG("VG0", 20);
   #pragma VCC_VREG("VG1", 21);
   #pragma VCC_VREG("VR0", 22);
   #pragma VCC_VREG("VR0_copy", 23);
   #pragma VCC_VREG("VR1", 24);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_in", "A0");
   #pragma EVE_REG("Addr_out", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 13u, 11u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(20), _VREG(16));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(20), _VREG(17));
   __vcop_vagen(_AGEN(0), _PREG(16), _PREG(17), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(16), _PREG(18), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(22), _AGEN(0), _VPAIR(18,20), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(6), _AGEN(0), _VPAIR(21,22), __vcop_alws());
   __vcop_vor(_VREG(18), _VREG(18), _VREG(19));
   __vcop_vor(_VREG(22), _VREG(22), _VREG(23));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(19,16), _PREG(8), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_skip(), __vcop_alws(), _VREG(20), _PREG(10), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(23,17), _PREG(12), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_skip(), __vcop_alws(), _VREG(21), _PREG(14), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VB0", 25);
   #pragma VCC_VREG("VB1", 26);
   #pragma VCC_VREG("VR0", 27);
   #pragma VCC_VREG("VR1", 28);
   #pragma VCC_VREG("Vbx", 29);
   #pragma VCC_VREG("Vrx", 30);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 10u, 10u, 2u);
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(16), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(18), _AGEN(0), _VREG(25), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(20), _AGEN(0), _VREG(26), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(8), _AGEN(0), _VREG(27), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(10), _AGEN(0), _VREG(28), __vcop_alws());
   __vcop_vadd(_VREG(25), _VREG(26), _VREG(29));
   __vcop_vadd(_VREG(27), _VREG(28), _VREG(30));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_skip(), __vcop_alws(), _VREG(29), _PREG(12), _AGEN(0), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_skip(), __vcop_alws(), _VREG(30), _PREG(14), _AGEN(0), _PREG(6));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VG0", 31);
   #pragma VCC_VREG("VG1", 32);
   #pragma VCC_VREG("Vgx", 33);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 6u, 7u, 3u);
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(10), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(12), _AGEN(0), _VREG(31), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(14), _AGEN(0), _VREG(32), __vcop_alws());
   __vcop_vadd(_VREG(31), _VREG(32), _VREG(33));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_skip(), __vcop_alws(), _VREG(33), _PREG(8), _AGEN(0), _PREG(6));
   __vcop_vloop_end(3u);

   /* VLOOP 4 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VB0_lp3", 34);
   #pragma VCC_VREG("VB1_lp3", 35);
   #pragma VCC_VREG("VB2", 36);
   #pragma VCC_VREG("VB3", 37);
   #pragma VCC_VREG("VR0_lp3", 38);
   #pragma VCC_VREG("VR1_lp3", 39);
   #pragma VCC_VREG("VR2", 40);
   #pragma VCC_VREG("VR3", 41);
   #pragma VCC_VREG("Vb0", 42);
   #pragma VCC_VREG("Vb1", 43);
   #pragma VCC_VREG("Vr0", 44);
   #pragma VCC_VREG("Vr1", 45);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_toprow", "A0");
   #pragma EVE_REG("Addr", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 17u, 10u, 4u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(7), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(16), _PREG(17), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(18), _AGEN(0), _VPAIR(34,35), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(20), _AGEN(0), _VPAIR(38,39), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(8), _AGEN(1), _VPAIR(36,37), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(10), _AGEN(1), _VPAIR(40,41), __vcop_alws());
   __vcop_vadd(_VREG(34), _VREG(36), _VREG(42));
   __vcop_vadd(_VREG(35), _VREG(37), _VREG(43));
   __vcop_vadd(_VREG(38), _VREG(40), _VREG(44));
   __vcop_vadd(_VREG(39), _VREG(41), _VREG(45));
   __vcop_vor(_VREG(36), _VREG(36), _VREG(34));
   __vcop_vor(_VREG(37), _VREG(37), _VREG(35));
   __vcop_vor(_VREG(40), _VREG(40), _VREG(38));
   __vcop_vor(_VREG(41), _VREG(41), _VREG(39));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(42,43), _PREG(12), _AGEN(1), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(44,45), _PREG(14), _AGEN(1), _PREG(6));
   __vcop_vloop_end(4u);

}

void vcop_BayerCFA_interpolate_short_BGGR(
   __vptr_uint16 CFA_short,
   unsigned int in_w,
   unsigned int blk_w,
   unsigned int blk_h,
   __vptr_uint16 R_short,
   __vptr_uint16 G_short,
   __vptr_uint16 B_short,
   unsigned int out_stride)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_BayerCFA_interpolate_short_BGGR_init(CFA_short, in_w, blk_w, blk_h, R_short, G_short, B_short, out_stride, __pblock_vcop_BayerCFA_interpolate_short_BGGR);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_BayerCFA_interpolate_short_BGGR_vloops(__pblock_vcop_BayerCFA_interpolate_short_BGGR);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_BayerCFA_interpolate_short_BGGR_custom(
   __vptr_uint16 CFA_short,
   unsigned int in_w,
   unsigned int blk_w,
   unsigned int blk_h,
   __vptr_uint16 R_short,
   __vptr_uint16 G_short,
   __vptr_uint16 B_short,
   unsigned int out_stride,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_BayerCFA_interpolate_short_BGGR_init(CFA_short, in_w, blk_w, blk_h, R_short, G_short, B_short, out_stride, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_BayerCFA_interpolate_short_BGGR_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_BayerCFA_interpolate_short_GRBG, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_BayerCFA_interpolate_short_GRBG, __ALIGNOF__(int));
unsigned short __pblock_vcop_BayerCFA_interpolate_short_GRBG[76];

unsigned int vcop_BayerCFA_interpolate_short_GRBG_param_count(void)
{
   return 76u;
}

unsigned int vcop_BayerCFA_interpolate_short_GRBG_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_BayerCFA_interpolate_short_GRBG_init(
   __vptr_uint16 CFA_short,
   unsigned int in_w,
   unsigned int blk_w,
   unsigned int blk_h,
   __vptr_uint16 R_short,
   __vptr_uint16 G_short,
   __vptr_uint16 B_short,
   unsigned int out_stride,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (((blk_h/2) +1))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (((blk_w/((8u) * 2))+1))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)CFA_short+in_w*sizeof(*CFA_short));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)B_short);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)G_short);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)R_short);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)G_short+out_stride*sizeof(*CFA_short));
   __vcop_pblock_init16(pblock, __offset+_PREG(16), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(17), (2*in_w*sizeof(*CFA_short)) -(2*(sizeof(*CFA_short)*8u))*((((blk_w/((8u) * 2))+1))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(18), (2*out_stride*sizeof(*CFA_short)) -(2*(sizeof(*CFA_short)*8u))*((((blk_w/((8u) * 2))+1))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)CFA_short);
   __offset += 22;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (((blk_h/2)+1))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (blk_w/((8u) * 2))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_TRUNC,1));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)R_short);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)R_short+2*sizeof(*CFA_short));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)B_short+sizeof(*CFA_short));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)R_short+sizeof(*CFA_short));
   __vcop_pblock_init16(pblock, __offset+_PREG(16), (2*out_stride*sizeof(*CFA_short)) -(2*8u*sizeof(*CFA_short))*((blk_w/((8u) * 2))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)B_short);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)B_short+2*sizeof(*CFA_short));
   __offset += 20;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((blk_h+1))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (blk_w/((8u) * 2))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_TRUNC,1));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)G_short+sizeof(*CFA_short));
   __vcop_pblock_init16(pblock, __offset+_PREG(10), (out_stride*sizeof(*CFA_short)) -(2*8u*sizeof(*CFA_short))*((blk_w/((8u) * 2))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)G_short);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)G_short+2*sizeof(*CFA_short));
   __offset += 14;

   /* Loop 4 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (blk_w/((8u) * 2))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (blk_h/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_TRUNC,1));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)B_short+2*out_stride*sizeof(*CFA_short));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)R_short+2*out_stride*sizeof(*CFA_short));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)B_short+out_stride*sizeof(*CFA_short));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)R_short+out_stride*sizeof(*CFA_short));
   __vcop_pblock_init16(pblock, __offset+_PREG(16), (2*out_stride*sizeof(*CFA_short)));
   __vcop_pblock_init16(pblock, __offset+_PREG(17), (2*8u*sizeof(*CFA_short)) -(2*out_stride*sizeof(*CFA_short))*((blk_h/2)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)B_short);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)R_short);
   __offset += 20;

   return 76u;
}

void vcop_BayerCFA_interpolate_short_GRBG_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vzero_a", 16);
   #pragma VCC_VREG("Vzero_b", 17);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VB0", 18);
   #pragma VCC_VREG("VB0_copy", 19);
   #pragma VCC_VREG("VG0", 20);
   #pragma VCC_VREG("VG1", 21);
   #pragma VCC_VREG("VR0", 22);
   #pragma VCC_VREG("VR0_copy", 23);
   #pragma VCC_VREG("VR1", 24);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_in", "A0");
   #pragma EVE_REG("Addr_out", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 13u, 11u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(20), _VREG(16));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(20), _VREG(17));
   __vcop_vagen(_AGEN(0), _PREG(16), _PREG(17), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(16), _PREG(18), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(22), _AGEN(0), _VPAIR(20,22), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(6), _AGEN(0), _VPAIR(18,21), __vcop_alws());
   __vcop_vor(_VREG(18), _VREG(18), _VREG(19));
   __vcop_vor(_VREG(22), _VREG(22), _VREG(23));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(19,16), _PREG(8), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_skip(), __vcop_alws(), _VREG(20), _PREG(10), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(23,17), _PREG(12), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_skip(), __vcop_alws(), _VREG(21), _PREG(14), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VB0", 25);
   #pragma VCC_VREG("VB1", 26);
   #pragma VCC_VREG("VR0", 27);
   #pragma VCC_VREG("VR1", 28);
   #pragma VCC_VREG("Vbx", 29);
   #pragma VCC_VREG("Vrx", 30);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 10u, 10u, 2u);
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(16), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(18), _AGEN(0), _VREG(25), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(20), _AGEN(0), _VREG(26), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(8), _AGEN(0), _VREG(27), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(10), _AGEN(0), _VREG(28), __vcop_alws());
   __vcop_vadd(_VREG(25), _VREG(26), _VREG(29));
   __vcop_vadd(_VREG(27), _VREG(28), _VREG(30));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_skip(), __vcop_alws(), _VREG(29), _PREG(12), _AGEN(0), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_skip(), __vcop_alws(), _VREG(30), _PREG(14), _AGEN(0), _PREG(6));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VG0", 31);
   #pragma VCC_VREG("VG1", 32);
   #pragma VCC_VREG("Vgx", 33);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 6u, 7u, 3u);
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(10), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(12), _AGEN(0), _VREG(31), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(14), _AGEN(0), _VREG(32), __vcop_alws());
   __vcop_vadd(_VREG(31), _VREG(32), _VREG(33));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_skip(), __vcop_alws(), _VREG(33), _PREG(8), _AGEN(0), _PREG(6));
   __vcop_vloop_end(3u);

   /* VLOOP 4 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VB0_lp3", 34);
   #pragma VCC_VREG("VB1_lp3", 35);
   #pragma VCC_VREG("VB2", 36);
   #pragma VCC_VREG("VB3", 37);
   #pragma VCC_VREG("VR0_lp3", 38);
   #pragma VCC_VREG("VR1_lp3", 39);
   #pragma VCC_VREG("VR2", 40);
   #pragma VCC_VREG("VR3", 41);
   #pragma VCC_VREG("Vb0", 42);
   #pragma VCC_VREG("Vb1", 43);
   #pragma VCC_VREG("Vr0", 44);
   #pragma VCC_VREG("Vr1", 45);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_toprow", "A0");
   #pragma EVE_REG("Addr", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 17u, 10u, 4u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(7), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(16), _PREG(17), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(18), _AGEN(0), _VPAIR(34,35), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(20), _AGEN(0), _VPAIR(38,39), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(8), _AGEN(1), _VPAIR(36,37), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(10), _AGEN(1), _VPAIR(40,41), __vcop_alws());
   __vcop_vadd(_VREG(34), _VREG(36), _VREG(42));
   __vcop_vadd(_VREG(35), _VREG(37), _VREG(43));
   __vcop_vadd(_VREG(38), _VREG(40), _VREG(44));
   __vcop_vadd(_VREG(39), _VREG(41), _VREG(45));
   __vcop_vor(_VREG(36), _VREG(36), _VREG(34));
   __vcop_vor(_VREG(37), _VREG(37), _VREG(35));
   __vcop_vor(_VREG(40), _VREG(40), _VREG(38));
   __vcop_vor(_VREG(41), _VREG(41), _VREG(39));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(42,43), _PREG(12), _AGEN(1), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(44,45), _PREG(14), _AGEN(1), _PREG(6));
   __vcop_vloop_end(4u);

}

void vcop_BayerCFA_interpolate_short_GRBG(
   __vptr_uint16 CFA_short,
   unsigned int in_w,
   unsigned int blk_w,
   unsigned int blk_h,
   __vptr_uint16 R_short,
   __vptr_uint16 G_short,
   __vptr_uint16 B_short,
   unsigned int out_stride)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_BayerCFA_interpolate_short_GRBG_init(CFA_short, in_w, blk_w, blk_h, R_short, G_short, B_short, out_stride, __pblock_vcop_BayerCFA_interpolate_short_GRBG);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_BayerCFA_interpolate_short_GRBG_vloops(__pblock_vcop_BayerCFA_interpolate_short_GRBG);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_BayerCFA_interpolate_short_GRBG_custom(
   __vptr_uint16 CFA_short,
   unsigned int in_w,
   unsigned int blk_w,
   unsigned int blk_h,
   __vptr_uint16 R_short,
   __vptr_uint16 G_short,
   __vptr_uint16 B_short,
   unsigned int out_stride,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_BayerCFA_interpolate_short_GRBG_init(CFA_short, in_w, blk_w, blk_h, R_short, G_short, B_short, out_stride, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_BayerCFA_interpolate_short_GRBG_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_BayerCFA_interpolate_short_RGGB, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_BayerCFA_interpolate_short_RGGB, __ALIGNOF__(int));
unsigned short __pblock_vcop_BayerCFA_interpolate_short_RGGB[76];

unsigned int vcop_BayerCFA_interpolate_short_RGGB_param_count(void)
{
   return 76u;
}

unsigned int vcop_BayerCFA_interpolate_short_RGGB_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_BayerCFA_interpolate_short_RGGB_init(
   __vptr_uint16 CFA_short,
   unsigned int in_w,
   unsigned int blk_w,
   unsigned int blk_h,
   __vptr_uint16 R_short,
   __vptr_uint16 G_short,
   __vptr_uint16 B_short,
   unsigned int out_stride,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (((blk_h/2) +1))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (((blk_w/((8u) * 2))+1))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)CFA_short+in_w*sizeof(*CFA_short));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)B_short);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)G_short);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)R_short);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)G_short+out_stride*sizeof(*CFA_short));
   __vcop_pblock_init16(pblock, __offset+_PREG(16), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(17), (2*in_w*sizeof(*CFA_short)) -(2*(sizeof(*CFA_short)*8u))*((((blk_w/((8u) * 2))+1))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(18), (2*out_stride*sizeof(*CFA_short)) -(2*(sizeof(*CFA_short)*8u))*((((blk_w/((8u) * 2))+1))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)CFA_short);
   __offset += 22;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (((blk_h/2)+1))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (blk_w/((8u) * 2))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_TRUNC,1));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)R_short);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)R_short+2*sizeof(*CFA_short));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)B_short+sizeof(*CFA_short));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)R_short+sizeof(*CFA_short));
   __vcop_pblock_init16(pblock, __offset+_PREG(16), (2*out_stride*sizeof(*CFA_short)) -(2*8u*sizeof(*CFA_short))*((blk_w/((8u) * 2))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)B_short);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)B_short+2*sizeof(*CFA_short));
   __offset += 20;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((blk_h+1))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (blk_w/((8u) * 2))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_TRUNC,1));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)G_short+sizeof(*CFA_short));
   __vcop_pblock_init16(pblock, __offset+_PREG(10), (out_stride*sizeof(*CFA_short)) -(2*8u*sizeof(*CFA_short))*((blk_w/((8u) * 2))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)G_short);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)G_short+2*sizeof(*CFA_short));
   __offset += 14;

   /* Loop 4 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (blk_w/((8u) * 2))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (blk_h/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_TRUNC,1));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)B_short+2*out_stride*sizeof(*CFA_short));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)R_short+2*out_stride*sizeof(*CFA_short));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)B_short+out_stride*sizeof(*CFA_short));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)R_short+out_stride*sizeof(*CFA_short));
   __vcop_pblock_init16(pblock, __offset+_PREG(16), (2*out_stride*sizeof(*CFA_short)));
   __vcop_pblock_init16(pblock, __offset+_PREG(17), (2*8u*sizeof(*CFA_short)) -(2*out_stride*sizeof(*CFA_short))*((blk_h/2)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)B_short);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)R_short);
   __offset += 20;

   return 76u;
}

void vcop_BayerCFA_interpolate_short_RGGB_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vzero_a", 16);
   #pragma VCC_VREG("Vzero_b", 17);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VB0", 18);
   #pragma VCC_VREG("VB0_copy", 19);
   #pragma VCC_VREG("VG0", 20);
   #pragma VCC_VREG("VG1", 21);
   #pragma VCC_VREG("VR0", 22);
   #pragma VCC_VREG("VR0_copy", 23);
   #pragma VCC_VREG("VR1", 24);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_in", "A0");
   #pragma EVE_REG("Addr_out", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 13u, 11u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(20), _VREG(16));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(20), _VREG(17));
   __vcop_vagen(_AGEN(0), _PREG(16), _PREG(17), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(16), _PREG(18), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(22), _AGEN(0), _VPAIR(22,20), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(6), _AGEN(0), _VPAIR(21,18), __vcop_alws());
   __vcop_vor(_VREG(18), _VREG(18), _VREG(19));
   __vcop_vor(_VREG(22), _VREG(22), _VREG(23));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(19,16), _PREG(8), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_skip(), __vcop_alws(), _VREG(20), _PREG(10), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(23,17), _PREG(12), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_skip(), __vcop_alws(), _VREG(21), _PREG(14), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VB0", 25);
   #pragma VCC_VREG("VB1", 26);
   #pragma VCC_VREG("VR0", 27);
   #pragma VCC_VREG("VR1", 28);
   #pragma VCC_VREG("Vbx", 29);
   #pragma VCC_VREG("Vrx", 30);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 10u, 10u, 2u);
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(16), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(18), _AGEN(0), _VREG(25), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(20), _AGEN(0), _VREG(26), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(8), _AGEN(0), _VREG(27), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(10), _AGEN(0), _VREG(28), __vcop_alws());
   __vcop_vadd(_VREG(25), _VREG(26), _VREG(29));
   __vcop_vadd(_VREG(27), _VREG(28), _VREG(30));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_skip(), __vcop_alws(), _VREG(29), _PREG(12), _AGEN(0), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_skip(), __vcop_alws(), _VREG(30), _PREG(14), _AGEN(0), _PREG(6));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VG0", 31);
   #pragma VCC_VREG("VG1", 32);
   #pragma VCC_VREG("Vgx", 33);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 6u, 7u, 3u);
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(10), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(12), _AGEN(0), _VREG(31), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(14), _AGEN(0), _VREG(32), __vcop_alws());
   __vcop_vadd(_VREG(31), _VREG(32), _VREG(33));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_skip(), __vcop_alws(), _VREG(33), _PREG(8), _AGEN(0), _PREG(6));
   __vcop_vloop_end(3u);

   /* VLOOP 4 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VB0_lp3", 34);
   #pragma VCC_VREG("VB1_lp3", 35);
   #pragma VCC_VREG("VB2", 36);
   #pragma VCC_VREG("VB3", 37);
   #pragma VCC_VREG("VR0_lp3", 38);
   #pragma VCC_VREG("VR1_lp3", 39);
   #pragma VCC_VREG("VR2", 40);
   #pragma VCC_VREG("VR3", 41);
   #pragma VCC_VREG("Vb0", 42);
   #pragma VCC_VREG("Vb1", 43);
   #pragma VCC_VREG("Vr0", 44);
   #pragma VCC_VREG("Vr1", 45);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_toprow", "A0");
   #pragma EVE_REG("Addr", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 17u, 10u, 4u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(7), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(16), _PREG(17), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(18), _AGEN(0), _VPAIR(34,35), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(20), _AGEN(0), _VPAIR(38,39), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(8), _AGEN(1), _VPAIR(36,37), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(10), _AGEN(1), _VPAIR(40,41), __vcop_alws());
   __vcop_vadd(_VREG(34), _VREG(36), _VREG(42));
   __vcop_vadd(_VREG(35), _VREG(37), _VREG(43));
   __vcop_vadd(_VREG(38), _VREG(40), _VREG(44));
   __vcop_vadd(_VREG(39), _VREG(41), _VREG(45));
   __vcop_vor(_VREG(36), _VREG(36), _VREG(34));
   __vcop_vor(_VREG(37), _VREG(37), _VREG(35));
   __vcop_vor(_VREG(40), _VREG(40), _VREG(38));
   __vcop_vor(_VREG(41), _VREG(41), _VREG(39));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(42,43), _PREG(12), _AGEN(1), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(44,45), _PREG(14), _AGEN(1), _PREG(6));
   __vcop_vloop_end(4u);

}

void vcop_BayerCFA_interpolate_short_RGGB(
   __vptr_uint16 CFA_short,
   unsigned int in_w,
   unsigned int blk_w,
   unsigned int blk_h,
   __vptr_uint16 R_short,
   __vptr_uint16 G_short,
   __vptr_uint16 B_short,
   unsigned int out_stride)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_BayerCFA_interpolate_short_RGGB_init(CFA_short, in_w, blk_w, blk_h, R_short, G_short, B_short, out_stride, __pblock_vcop_BayerCFA_interpolate_short_RGGB);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_BayerCFA_interpolate_short_RGGB_vloops(__pblock_vcop_BayerCFA_interpolate_short_RGGB);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_BayerCFA_interpolate_short_RGGB_custom(
   __vptr_uint16 CFA_short,
   unsigned int in_w,
   unsigned int blk_w,
   unsigned int blk_h,
   __vptr_uint16 R_short,
   __vptr_uint16 G_short,
   __vptr_uint16 B_short,
   unsigned int out_stride,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_BayerCFA_interpolate_short_RGGB_init(CFA_short, in_w, blk_w, blk_h, R_short, G_short, B_short, out_stride, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_BayerCFA_interpolate_short_RGGB_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_BayerCFA_interpolate_short_GBRG, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_BayerCFA_interpolate_short_GBRG, __ALIGNOF__(int));
unsigned short __pblock_vcop_BayerCFA_interpolate_short_GBRG[76];

unsigned int vcop_BayerCFA_interpolate_short_GBRG_param_count(void)
{
   return 76u;
}

unsigned int vcop_BayerCFA_interpolate_short_GBRG_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_BayerCFA_interpolate_short_GBRG_init(
   __vptr_uint16 CFA_short,
   unsigned int in_w,
   unsigned int blk_w,
   unsigned int blk_h,
   __vptr_uint16 R_short,
   __vptr_uint16 G_short,
   __vptr_uint16 B_short,
   unsigned int out_stride,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (((blk_h/2) +1))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (((blk_w/((8u) * 2))+1))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)CFA_short+in_w*sizeof(*CFA_short));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)B_short);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)G_short);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)R_short);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)G_short+out_stride*sizeof(*CFA_short));
   __vcop_pblock_init16(pblock, __offset+_PREG(16), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(17), (2*in_w*sizeof(*CFA_short)) -(2*(sizeof(*CFA_short)*8u))*((((blk_w/((8u) * 2))+1))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(18), (2*out_stride*sizeof(*CFA_short)) -(2*(sizeof(*CFA_short)*8u))*((((blk_w/((8u) * 2))+1))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)CFA_short);
   __offset += 22;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (((blk_h/2)+1))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (blk_w/((8u) * 2))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_TRUNC,1));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)R_short);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)R_short+2*sizeof(*CFA_short));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)B_short+sizeof(*CFA_short));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)R_short+sizeof(*CFA_short));
   __vcop_pblock_init16(pblock, __offset+_PREG(16), (2*out_stride*sizeof(*CFA_short)) -(2*8u*sizeof(*CFA_short))*((blk_w/((8u) * 2))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)B_short);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)B_short+2*sizeof(*CFA_short));
   __offset += 20;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((blk_h+1))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (blk_w/((8u) * 2))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_TRUNC,1));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)G_short+sizeof(*CFA_short));
   __vcop_pblock_init16(pblock, __offset+_PREG(10), (out_stride*sizeof(*CFA_short)) -(2*8u*sizeof(*CFA_short))*((blk_w/((8u) * 2))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)G_short);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)G_short+2*sizeof(*CFA_short));
   __offset += 14;

   /* Loop 4 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (blk_w/((8u) * 2))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (blk_h/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_TRUNC,1));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)B_short+2*out_stride*sizeof(*CFA_short));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)R_short+2*out_stride*sizeof(*CFA_short));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)B_short+out_stride*sizeof(*CFA_short));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)R_short+out_stride*sizeof(*CFA_short));
   __vcop_pblock_init16(pblock, __offset+_PREG(16), (2*out_stride*sizeof(*CFA_short)));
   __vcop_pblock_init16(pblock, __offset+_PREG(17), (2*8u*sizeof(*CFA_short)) -(2*out_stride*sizeof(*CFA_short))*((blk_h/2)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)B_short);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)R_short);
   __offset += 20;

   return 76u;
}

void vcop_BayerCFA_interpolate_short_GBRG_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vzero_a", 16);
   #pragma VCC_VREG("Vzero_b", 17);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VB0", 18);
   #pragma VCC_VREG("VB0_copy", 19);
   #pragma VCC_VREG("VG0", 20);
   #pragma VCC_VREG("VG1", 21);
   #pragma VCC_VREG("VR0", 22);
   #pragma VCC_VREG("VR0_copy", 23);
   #pragma VCC_VREG("VR1", 24);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_in", "A0");
   #pragma EVE_REG("Addr_out", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 13u, 11u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(20), _VREG(16));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(20), _VREG(17));
   __vcop_vagen(_AGEN(0), _PREG(16), _PREG(17), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(16), _PREG(18), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(22), _AGEN(0), _VPAIR(20,18), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(6), _AGEN(0), _VPAIR(22,21), __vcop_alws());
   __vcop_vor(_VREG(18), _VREG(18), _VREG(19));
   __vcop_vor(_VREG(22), _VREG(22), _VREG(23));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(19,16), _PREG(8), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_skip(), __vcop_alws(), _VREG(20), _PREG(10), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(23,17), _PREG(12), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_skip(), __vcop_alws(), _VREG(21), _PREG(14), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VB0", 25);
   #pragma VCC_VREG("VB1", 26);
   #pragma VCC_VREG("VR0", 27);
   #pragma VCC_VREG("VR1", 28);
   #pragma VCC_VREG("Vbx", 29);
   #pragma VCC_VREG("Vrx", 30);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 10u, 10u, 2u);
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(16), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(18), _AGEN(0), _VREG(25), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(20), _AGEN(0), _VREG(26), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(8), _AGEN(0), _VREG(27), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(10), _AGEN(0), _VREG(28), __vcop_alws());
   __vcop_vadd(_VREG(25), _VREG(26), _VREG(29));
   __vcop_vadd(_VREG(27), _VREG(28), _VREG(30));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_skip(), __vcop_alws(), _VREG(29), _PREG(12), _AGEN(0), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_skip(), __vcop_alws(), _VREG(30), _PREG(14), _AGEN(0), _PREG(6));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VG0", 31);
   #pragma VCC_VREG("VG1", 32);
   #pragma VCC_VREG("Vgx", 33);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 6u, 7u, 3u);
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(10), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(12), _AGEN(0), _VREG(31), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(14), _AGEN(0), _VREG(32), __vcop_alws());
   __vcop_vadd(_VREG(31), _VREG(32), _VREG(33));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_skip(), __vcop_alws(), _VREG(33), _PREG(8), _AGEN(0), _PREG(6));
   __vcop_vloop_end(3u);

   /* VLOOP 4 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VB0_lp3", 34);
   #pragma VCC_VREG("VB1_lp3", 35);
   #pragma VCC_VREG("VB2", 36);
   #pragma VCC_VREG("VB3", 37);
   #pragma VCC_VREG("VR0_lp3", 38);
   #pragma VCC_VREG("VR1_lp3", 39);
   #pragma VCC_VREG("VR2", 40);
   #pragma VCC_VREG("VR3", 41);
   #pragma VCC_VREG("Vb0", 42);
   #pragma VCC_VREG("Vb1", 43);
   #pragma VCC_VREG("Vr0", 44);
   #pragma VCC_VREG("Vr1", 45);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_toprow", "A0");
   #pragma EVE_REG("Addr", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 17u, 10u, 4u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(7), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(16), _PREG(17), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(18), _AGEN(0), _VPAIR(34,35), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(20), _AGEN(0), _VPAIR(38,39), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(8), _AGEN(1), _VPAIR(36,37), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(10), _AGEN(1), _VPAIR(40,41), __vcop_alws());
   __vcop_vadd(_VREG(34), _VREG(36), _VREG(42));
   __vcop_vadd(_VREG(35), _VREG(37), _VREG(43));
   __vcop_vadd(_VREG(38), _VREG(40), _VREG(44));
   __vcop_vadd(_VREG(39), _VREG(41), _VREG(45));
   __vcop_vor(_VREG(36), _VREG(36), _VREG(34));
   __vcop_vor(_VREG(37), _VREG(37), _VREG(35));
   __vcop_vor(_VREG(40), _VREG(40), _VREG(38));
   __vcop_vor(_VREG(41), _VREG(41), _VREG(39));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(42,43), _PREG(12), _AGEN(1), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(44,45), _PREG(14), _AGEN(1), _PREG(6));
   __vcop_vloop_end(4u);

}

void vcop_BayerCFA_interpolate_short_GBRG(
   __vptr_uint16 CFA_short,
   unsigned int in_w,
   unsigned int blk_w,
   unsigned int blk_h,
   __vptr_uint16 R_short,
   __vptr_uint16 G_short,
   __vptr_uint16 B_short,
   unsigned int out_stride)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_BayerCFA_interpolate_short_GBRG_init(CFA_short, in_w, blk_w, blk_h, R_short, G_short, B_short, out_stride, __pblock_vcop_BayerCFA_interpolate_short_GBRG);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_BayerCFA_interpolate_short_GBRG_vloops(__pblock_vcop_BayerCFA_interpolate_short_GBRG);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_BayerCFA_interpolate_short_GBRG_custom(
   __vptr_uint16 CFA_short,
   unsigned int in_w,
   unsigned int blk_w,
   unsigned int blk_h,
   __vptr_uint16 R_short,
   __vptr_uint16 G_short,
   __vptr_uint16 B_short,
   unsigned int out_stride,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_BayerCFA_interpolate_short_GBRG_init(CFA_short, in_w, blk_w, blk_h, R_short, G_short, B_short, out_stride, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_BayerCFA_interpolate_short_GBRG_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

