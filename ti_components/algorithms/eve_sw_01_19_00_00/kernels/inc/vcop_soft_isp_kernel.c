#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_decompand_piecewise_linear, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_decompand_piecewise_linear, __ALIGNOF__(int));
unsigned short __pblock_vcop_decompand_piecewise_linear[44];

unsigned int vcop_decompand_piecewise_linear_param_count(void)
{
   return 44u;
}

unsigned int vcop_decompand_piecewise_linear_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_decompand_piecewise_linear_init(
   __vptr_uint16 inp_rc_data_A,
   __vptr_uint16 inp_cc_data_B,
   __vptr_uint16 out_rc_data_B,
   __vptr_uint16 out_cc_data_A,
   unsigned short blk_width,
   unsigned short blk_height,
   unsigned short in_stride,
   unsigned short out_stride,
   unsigned short p1,
   unsigned int p2,
   unsigned short pk,
   unsigned char r1,
   unsigned short r1r2,
   unsigned char shift,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (blk_height/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((blk_width + (8u) - 1)/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_TRUNC,shift));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 16);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), pk);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), r1);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), r1r2);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)inp_rc_data_A);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)out_rc_data_B);
   __vcop_pblock_init16(pblock, __offset+_PREG(18), (in_stride*sizeof(*inp_rc_data_A)) -(8u*sizeof(*inp_rc_data_A))*(((blk_width + (8u) - 1)/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(19), (out_stride*sizeof(*inp_rc_data_A)) -(8u*sizeof(*inp_rc_data_A))*(((blk_width + (8u) - 1)/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), p1);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), p2);
   __offset += 22;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (blk_height/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((blk_width + (8u) - 1)/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), pk);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), r1);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), r1r2);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)inp_cc_data_B);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)out_cc_data_A);
   __vcop_pblock_init16(pblock, __offset+_PREG(16), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(17), (in_stride*sizeof(*inp_rc_data_A)) -(8u*sizeof(*inp_rc_data_A))*(((blk_width + (8u) - 1)/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(18), (out_stride*sizeof(*inp_rc_data_A)) -(8u*sizeof(*inp_rc_data_A))*(((blk_width + (8u) - 1)/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), p1);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), p2);
   __offset += 22;

   return 44u;
}

void vcop_decompand_piecewise_linear_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vflag_s1", 16);
   #pragma VCC_VREG("Vflag_s3", 17);
   #pragma VCC_VREG("Vin", 18);
   #pragma VCC_VREG("Vout_s2", 19);
   #pragma VCC_VREG("Vout_s3", 20);
   #pragma VCC_VREG("Vp1", 21);
   #pragma VCC_VREG("Vp2", 22);
   #pragma VCC_VREG("Vpk", 23);
   #pragma VCC_VREG("Vr1", 24);
   #pragma VCC_VREG("Vr1r2", 25);
   #pragma VCC_VREG("Vtmp2", 26);
   #pragma VCC_VREG("Vtmp3", 27);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("AddrIn", "A0");
   #pragma EVE_REG("AddrOut", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 20u, 11u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(20), _VREG(21));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(22), _VREG(22));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(8), _VREG(23));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(10), _VREG(24));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(12), _VREG(25));
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(18), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(19), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(14), _AGEN(0), _VREG(18), __vcop_alws());
   __vcop_vsub(_VREG(18), _VREG(21), _VREG(26));
   __vcop_vsub(_VREG(18), _VREG(23), _VREG(27));
   __vcop_vmpy(_VREG(26), _VREG(24), _VREG(19), _PREG(0));
   __vcop_vmpy(_VREG(27), _VREG(25), _VREG(20), _PREG(0));
   __vcop_vcmpge(_VREG(21), _VREG(18), _VREG(16));
   __vcop_vcmpgt(_VREG(18), _VREG(23), _VREG(17));
   __vcop_vadd(_VREG(19), _VREG(21), _VREG(19));
   __vcop_vadd(_VREG(20), _VREG(22), _VREG(20));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(19), _PREG(16), _AGEN(1), _PREG(6));
   __vcop_vstore(__vcop_predicate(_VREG(16)), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(18), _PREG(16), _AGEN(1), _PREG(6));
   __vcop_vstore(__vcop_predicate(_VREG(17)), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(20), _PREG(16), _AGEN(1), _PREG(6));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vflag_s1", 28);
   #pragma VCC_VREG("Vflag_s3", 29);
   #pragma VCC_VREG("Vin", 30);
   #pragma VCC_VREG("Vout_s2", 31);
   #pragma VCC_VREG("Vout_s3", 32);
   #pragma VCC_VREG("Vp1", 33);
   #pragma VCC_VREG("Vp2", 34);
   #pragma VCC_VREG("Vpk", 35);
   #pragma VCC_VREG("Vr1", 36);
   #pragma VCC_VREG("Vr1r2", 37);
   #pragma VCC_VREG("Vtmp2", 38);
   #pragma VCC_VREG("Vtmp3", 39);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("AddrIn", "A0");
   #pragma EVE_REG("AddrOut", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 20u, 11u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(20), _VREG(33));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(22), _VREG(34));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(6), _VREG(35));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(8), _VREG(36));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(10), _VREG(37));
   __vcop_vagen(_AGEN(0), _PREG(16), _PREG(17), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(16), _PREG(18), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(12), _AGEN(0), _VREG(30), __vcop_alws());
   __vcop_vsub(_VREG(30), _VREG(33), _VREG(38));
   __vcop_vsub(_VREG(30), _VREG(35), _VREG(39));
   __vcop_vmpy(_VREG(38), _VREG(36), _VREG(31), _PREG(0));
   __vcop_vmpy(_VREG(39), _VREG(37), _VREG(32), _PREG(0));
   __vcop_vcmpge(_VREG(33), _VREG(30), _VREG(28));
   __vcop_vcmpgt(_VREG(30), _VREG(35), _VREG(29));
   __vcop_vadd(_VREG(31), _VREG(33), _VREG(31));
   __vcop_vadd(_VREG(32), _VREG(34), _VREG(32));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(31), _PREG(14), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_predicate(_VREG(28)), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(30), _PREG(14), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_predicate(_VREG(29)), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(32), _PREG(14), _AGEN(1), _PREG(0));
   __vcop_vloop_end(2u);

}

void vcop_decompand_piecewise_linear(
   __vptr_uint16 inp_rc_data_A,
   __vptr_uint16 inp_cc_data_B,
   __vptr_uint16 out_rc_data_B,
   __vptr_uint16 out_cc_data_A,
   unsigned short blk_width,
   unsigned short blk_height,
   unsigned short in_stride,
   unsigned short out_stride,
   unsigned short p1,
   unsigned int p2,
   unsigned short pk,
   unsigned char r1,
   unsigned short r1r2,
   unsigned char shift)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_decompand_piecewise_linear_init(inp_rc_data_A, inp_cc_data_B, out_rc_data_B, out_cc_data_A, blk_width, blk_height, in_stride, out_stride, p1, p2, pk, r1, r1r2, shift, __pblock_vcop_decompand_piecewise_linear);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_decompand_piecewise_linear_vloops(__pblock_vcop_decompand_piecewise_linear);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_decompand_piecewise_linear_custom(
   __vptr_uint16 inp_rc_data_A,
   __vptr_uint16 inp_cc_data_B,
   __vptr_uint16 out_rc_data_B,
   __vptr_uint16 out_cc_data_A,
   unsigned short blk_width,
   unsigned short blk_height,
   unsigned short in_stride,
   unsigned short out_stride,
   unsigned short p1,
   unsigned int p2,
   unsigned short pk,
   unsigned char r1,
   unsigned short r1r2,
   unsigned char shift,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_decompand_piecewise_linear_init(inp_rc_data_A, inp_cc_data_B, out_rc_data_B, out_cc_data_A, blk_width, blk_height, in_stride, out_stride, p1, p2, pk, r1, r1r2, shift, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_decompand_piecewise_linear_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_black_clamp_c_balance, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_black_clamp_c_balance, __ALIGNOF__(int));
unsigned short __pblock_vcop_black_clamp_c_balance[34];

unsigned int vcop_black_clamp_c_balance_param_count(void)
{
   return 34u;
}

unsigned int vcop_black_clamp_c_balance_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_black_clamp_c_balance_init(
   __vptr_uint16 inp_rc_data_A,
   __vptr_uint16 inp_cc_data_B,
   __vptr_uint16 out_rc_data_A,
   __vptr_uint16 out_cc_data_B,
   unsigned short blk_width,
   unsigned short blk_height,
   unsigned short in_stride,
   unsigned short out_stride,
   unsigned short blackClamp[],
   unsigned short cBalanceGain[],
   unsigned char shift,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   const int preg_ref1 = _PREG(7);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (blk_height/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((blk_width + (2*(8u)) - 1)/(2*(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_SYMM,preg_ref1,RM_TRUNC,shift));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 65535);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), blackClamp[2]);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), blackClamp[3]);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), cBalanceGain[0]);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), cBalanceGain[1]);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), cBalanceGain[2]);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), cBalanceGain[3]);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)inp_rc_data_A);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)inp_cc_data_B);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)out_rc_data_A);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)out_cc_data_B);
   __vcop_pblock_init16(pblock, __offset+_PREG(28), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(29), (in_stride*sizeof(*inp_rc_data_A)) -((2*8u)*sizeof(*inp_rc_data_A))*(((blk_width + (2*(8u)) - 1)/(2*(8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(30), (out_stride*sizeof(*out_rc_data_A)) -((2*8u)*sizeof(*out_rc_data_A))*(((blk_width + (2*(8u)) - 1)/(2*(8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(32), blackClamp[0]);
   __vcop_pblock_init32(pblock, __offset+_PREG(34), blackClamp[1]);
   __offset += 34;

   return 34u;
}

void vcop_black_clamp_c_balance_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VblackClamp0", 16);
   #pragma VCC_VREG("VblackClamp1", 17);
   #pragma VCC_VREG("VblackClamp2", 18);
   #pragma VCC_VREG("VblackClamp3", 19);
   #pragma VCC_VREG("VcBalanceGain0", 20);
   #pragma VCC_VREG("VcBalanceGain1", 21);
   #pragma VCC_VREG("VcBalanceGain2", 22);
   #pragma VCC_VREG("VcBalanceGain3", 23);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vc1", 24);
   #pragma VCC_VREG("Vc1_o", 25);
   #pragma VCC_VREG("Vc2", 26);
   #pragma VCC_VREG("Vc2_o", 27);
   #pragma VCC_VREG("Vc3", 28);
   #pragma VCC_VREG("Vc3_o", 29);
   #pragma VCC_VREG("Vr", 30);
   #pragma VCC_VREG("Vr_o", 31);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("AddrIn", "A0");
   #pragma EVE_REG("AddrOut", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 23u, 17u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(32), _VREG(16));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(34), _VREG(17));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(8), _VREG(18));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(10), _VREG(19));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(12), _VREG(20));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(14), _VREG(21));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(16), _VREG(22));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(18), _VREG(23));
   __vcop_vagen(_AGEN(0), _PREG(28), _PREG(29), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(28), _PREG(30), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(20), _AGEN(0), _VPAIR(30,24), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(22), _AGEN(0), _VPAIR(26,28), __vcop_alws());
   __vcop_vsub(_VREG(30), _VREG(16), _VREG(30));
   __vcop_vsub(_VREG(24), _VREG(17), _VREG(24));
   __vcop_vsub(_VREG(26), _VREG(18), _VREG(26));
   __vcop_vsub(_VREG(28), _VREG(19), _VREG(28));
   __vcop_vmpy(_VREG(30), _VREG(20), _VREG(31), _PREG(0));
   __vcop_vmpy(_VREG(24), _VREG(21), _VREG(25), _PREG(0));
   __vcop_vmpy(_VREG(26), _VREG(22), _VREG(27), _PREG(0));
   __vcop_vmpy(_VREG(28), _VREG(23), _VREG(29), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(31,25), _PREG(24), _AGEN(1), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(27,29), _PREG(26), _AGEN(1), _PREG(6));
   __vcop_vloop_end(1u);

}

void vcop_black_clamp_c_balance(
   __vptr_uint16 inp_rc_data_A,
   __vptr_uint16 inp_cc_data_B,
   __vptr_uint16 out_rc_data_A,
   __vptr_uint16 out_cc_data_B,
   unsigned short blk_width,
   unsigned short blk_height,
   unsigned short in_stride,
   unsigned short out_stride,
   unsigned short blackClamp[],
   unsigned short cBalanceGain[],
   unsigned char shift)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_black_clamp_c_balance_init(inp_rc_data_A, inp_cc_data_B, out_rc_data_A, out_cc_data_B, blk_width, blk_height, in_stride, out_stride, blackClamp, cBalanceGain, shift, __pblock_vcop_black_clamp_c_balance);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_black_clamp_c_balance_vloops(__pblock_vcop_black_clamp_c_balance);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_black_clamp_c_balance_custom(
   __vptr_uint16 inp_rc_data_A,
   __vptr_uint16 inp_cc_data_B,
   __vptr_uint16 out_rc_data_A,
   __vptr_uint16 out_cc_data_B,
   unsigned short blk_width,
   unsigned short blk_height,
   unsigned short in_stride,
   unsigned short out_stride,
   unsigned short blackClamp[],
   unsigned short cBalanceGain[],
   unsigned char shift,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_black_clamp_c_balance_init(inp_rc_data_A, inp_cc_data_B, out_rc_data_A, out_cc_data_B, blk_width, blk_height, in_stride, out_stride, blackClamp, cBalanceGain, shift, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_black_clamp_c_balance_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_soft_isp_extract_r, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_soft_isp_extract_r, __ALIGNOF__(int));
unsigned short __pblock_vcop_soft_isp_extract_r[14];

unsigned int vcop_soft_isp_extract_r_param_count(void)
{
   return 14u;
}

unsigned int vcop_soft_isp_extract_r_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_soft_isp_extract_r_init(
   __vptr_uint16 inp_rc_data_A,
   __vptr_uint8 out_r_data_B,
   unsigned short blk_width,
   unsigned short blk_height,
   unsigned short in_stride,
   unsigned char shift,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (blk_height/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((blk_width + (2*(8u)) - 1)/(2*(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_TRUNC,shift));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(8), (in_stride*sizeof(*inp_rc_data_A)) -((2*8u)*sizeof(*inp_rc_data_A))*(((blk_width + (2*(8u)) - 1)/(2*(8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(9), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), ((blk_width/2)*sizeof(*out_r_data_B)) -(8u*sizeof(*out_r_data_B))*(((blk_width + (2*(8u)) - 1)/(2*(8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)inp_rc_data_A);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)out_r_data_B);
   __offset += 14;

   return 14u;
}

void vcop_soft_isp_extract_r_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vin", 16);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("AddrIn", "A0");
   #pragma EVE_REG("AddrOut", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 5u, 7u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(8), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(9), _PREG(10), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(12), _AGEN(0), _VREG(16), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(16), _PREG(14), _AGEN(1), _PREG(6));
   __vcop_vloop_end(1u);

}

void vcop_soft_isp_extract_r(
   __vptr_uint16 inp_rc_data_A,
   __vptr_uint8 out_r_data_B,
   unsigned short blk_width,
   unsigned short blk_height,
   unsigned short in_stride,
   unsigned char shift)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_soft_isp_extract_r_init(inp_rc_data_A, out_r_data_B, blk_width, blk_height, in_stride, shift, __pblock_vcop_soft_isp_extract_r);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_soft_isp_extract_r_vloops(__pblock_vcop_soft_isp_extract_r);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_soft_isp_extract_r_custom(
   __vptr_uint16 inp_rc_data_A,
   __vptr_uint8 out_r_data_B,
   unsigned short blk_width,
   unsigned short blk_height,
   unsigned short in_stride,
   unsigned char shift,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_soft_isp_extract_r_init(inp_rc_data_A, out_r_data_B, blk_width, blk_height, in_stride, shift, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_soft_isp_extract_r_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_stats_collector_dense, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_stats_collector_dense, __ALIGNOF__(int));
unsigned short __pblock_vcop_stats_collector_dense[68];

unsigned int vcop_stats_collector_dense_param_count(void)
{
   return 68u;
}

unsigned int vcop_stats_collector_dense_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_stats_collector_dense_init(
   __vptr_uint16 inp_rc_data_A,
   __vptr_uint16 inp_cc_data_B,
   __vptr_uint32 scratch_C,
   __vptr_uint32 out_sum_pix,
   __vptr_uint16 out_cnt_unsat_pix,
   unsigned short blk_width,
   unsigned short blk_height,
   unsigned short in_stride,
   unsigned char start_x,
   unsigned short saturationLimit,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (blk_height/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (blk_width/(2*(8u)))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)inp_rc_data_A+start_x*sizeof(*inp_rc_data_A));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)inp_rc_data_A+(1-start_x)*sizeof(*inp_rc_data_A));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)inp_cc_data_B);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)inp_cc_data_B+sizeof(*inp_rc_data_A));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)scratch_C);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)scratch_C+3*sizeof(*out_sum_pix));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)scratch_C+4*sizeof(*out_sum_pix));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)scratch_C+5*sizeof(*out_sum_pix));
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)scratch_C+6*sizeof(*out_sum_pix));
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)scratch_C+7*sizeof(*out_sum_pix));
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)out_cnt_unsat_pix);
   __vcop_pblock_init16(pblock, __offset+_PREG(28), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(29), (in_stride*sizeof(*inp_rc_data_A)) -((2*8u)*sizeof(*inp_rc_data_A))*((blk_width/(2*(8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(30),  -(in_stride*sizeof(*inp_rc_data_A))*((blk_height/2)-1u) -((2*8u)*sizeof(*inp_rc_data_A))*((blk_width/(2*(8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(32), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(34), saturationLimit);
   __offset += 34;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (blk_height/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (blk_width/(2*(8u)))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)inp_cc_data_B);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)scratch_C+1*sizeof(*out_sum_pix));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)scratch_C+2*sizeof(*out_sum_pix));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(13), (in_stride*sizeof(*inp_rc_data_A)) -((2*8u)*sizeof(*inp_rc_data_A))*((blk_width/(2*(8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(14),  -(in_stride*sizeof(*inp_rc_data_A))*((blk_height/2)-1u) -((2*8u)*sizeof(*inp_rc_data_A))*((blk_width/(2*(8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)inp_rc_data_A+(1-start_x)*sizeof(*inp_rc_data_A));
   __offset += 18;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (8)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)out_cnt_unsat_pix);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)out_sum_pix);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 36);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), -252);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), 2);
   __vcop_pblock_init16(pblock, __offset+_PREG(13), -14);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)scratch_C);
   __offset += 16;

   return 68u;
}

void vcop_stats_collector_dense_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vsatlmt", 16);
   #pragma VCC_VREG("Vsum_c3", 17);
   #pragma VCC_VREG("Vsum_r", 18);
   #pragma VCC_VREG("Vub_cnt", 19);
   #pragma VCC_VREG("Vunsatsum_c1", 20);
   #pragma VCC_VREG("Vunsatsum_c2", 21);
   #pragma VCC_VREG("Vunsatsum_c3", 22);
   #pragma VCC_VREG("Vunsatsum_r", 23);
   #pragma VCC_VREG("Vc1", 24);
   #pragma VCC_VREG("Vc2", 25);
   #pragma VCC_VREG("Vc3", 26);
   #pragma VCC_VREG("Vflag", 27);
   #pragma VCC_VREG("Vflag1", 28);
   #pragma VCC_VREG("Vflag2", 29);
   #pragma VCC_VREG("Vflag_c1", 30);
   #pragma VCC_VREG("Vflag_c2", 31);
   #pragma VCC_VREG("Vflag_c3", 32);
   #pragma VCC_VREG("Vflag_r", 33);
   #pragma VCC_VREG("Vr", 34);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("AddrOut", "A0");
   #pragma EVE_REG("AddrIn", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I0", "I2");
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 36u, 17u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i34_zero(), _PREG(32), _VREG(18));
   __vcop_vinit(__vcop_sizeW(), __vcop_i34_zero(), _PREG(32), _VREG(17));
   __vcop_vinit(__vcop_sizeW(), __vcop_i34_zero(), _PREG(32), _VREG(23));
   __vcop_vinit(__vcop_sizeW(), __vcop_i34_zero(), _PREG(32), _VREG(20));
   __vcop_vinit(__vcop_sizeW(), __vcop_i34_zero(), _PREG(32), _VREG(21));
   __vcop_vinit(__vcop_sizeW(), __vcop_i34_zero(), _PREG(32), _VREG(22));
   __vcop_vinit(__vcop_sizeW(), __vcop_i34_zero(), _PREG(32), _VREG(19));
   __vcop_vinit(__vcop_sizeW(), __vcop_i34_zero(), _PREG(34), _VREG(16));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(1), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(28), _PREG(29), _PREG(30), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(6), _AGEN(1), _VREG(34), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(8), _AGEN(1), _VREG(24), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(10), _AGEN(1), _VREG(25), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(12), _AGEN(1), _VREG(26), __vcop_alws());
   __vcop_vcmplt(_VREG(34), _VREG(16), _VREG(33));
   __vcop_vcmplt(_VREG(24), _VREG(16), _VREG(30));
   __vcop_vcmplt(_VREG(25), _VREG(16), _VREG(31));
   __vcop_vcmplt(_VREG(26), _VREG(16), _VREG(32));
   __vcop_vand(_VREG(33), _VREG(30), _VREG(28));
   __vcop_vand(_VREG(31), _VREG(32), _VREG(29));
   __vcop_vand(_VREG(28), _VREG(29), _VREG(27));
   __vcop_vadd(_VREG(18), _VREG(34), _VREG(18));
   __vcop_vmadd(_VREG(27), _VREG(34), _VREG(23), _PREG(0));
   __vcop_vmadd(_VREG(27), _VREG(24), _VREG(20), _PREG(0));
   __vcop_vmadd(_VREG(27), _VREG(25), _VREG(21), _PREG(0));
   __vcop_vmadd(_VREG(27), _VREG(26), _VREG(22), _PREG(0));
   __vcop_vadd(_VREG(17), _VREG(26), _VREG(17));
   __vcop_vadd(_VREG(19), _VREG(27), _VREG(19));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_offst_np1(), __vcop_last_i34(), _VREG(18), _PREG(14), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_offst_np1(), __vcop_last_i34(), _VREG(17), _PREG(16), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_offst_np1(), __vcop_last_i34(), _VREG(23), _PREG(18), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_offst_np1(), __vcop_last_i34(), _VREG(20), _PREG(20), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_offst_np1(), __vcop_last_i34(), _VREG(21), _PREG(22), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_offst_np1(), __vcop_last_i34(), _VREG(22), _PREG(24), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_last_i34(), _VREG(19), _PREG(26), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vsum_c1", 35);
   #pragma VCC_VREG("Vsum_c2", 36);
   #pragma VCC_VREG("Vc1", 37);
   #pragma VCC_VREG("Vc2", 38);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("AddrOut", "A0");
   #pragma EVE_REG("AddrIn", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I0", "I2");
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 11u, 9u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i34_zero(), _PREG(16), _VREG(35));
   __vcop_vinit(__vcop_sizeW(), __vcop_i34_zero(), _PREG(16), _VREG(36));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(1), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(12), _PREG(13), _PREG(14), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(18), _AGEN(1), _VREG(37), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(6), _AGEN(1), _VREG(38), __vcop_alws());
   __vcop_vadd(_VREG(35), _VREG(37), _VREG(35));
   __vcop_vadd(_VREG(36), _VREG(38), _VREG(36));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_offst_np1(), __vcop_last_i34(), _VREG(35), _PREG(8), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_offst_np1(), __vcop_last_i34(), _VREG(36), _PREG(10), _AGEN(0), _PREG(0));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vout", 39);
   #pragma VCC_VREG("Vub_cnt", 40);
   #pragma VCC_VREG("Vcnt", 41);
   #pragma VCC_VREG("Vin", 42);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   #pragma EVE_REG("AddrIn", "A1");
   #pragma EVE_REG("AddrIn_cnt", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I0", "I3");
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 12u, 8u, 3u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(14), _VREG(39));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(14), _VREG(40));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(1), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(10), _PREG(11), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(12), _PREG(13), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(16), _AGEN(1), _VREG(42), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(6), _AGEN(2), _VREG(41), __vcop_alws());
   __vcop_vadd(_VREG(39), _VREG(42), _VREG(39));
   __vcop_vadd(_VREG(40), _VREG(41), _VREG(40));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_last_i4(), _VREG(39), _PREG(8), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_last_i4(), _VREG(40), _PREG(6), _AGEN(0), _PREG(0));
   __vcop_vloop_end(3u);

}

void vcop_stats_collector_dense(
   __vptr_uint16 inp_rc_data_A,
   __vptr_uint16 inp_cc_data_B,
   __vptr_uint32 scratch_C,
   __vptr_uint32 out_sum_pix,
   __vptr_uint16 out_cnt_unsat_pix,
   unsigned short blk_width,
   unsigned short blk_height,
   unsigned short in_stride,
   unsigned char start_x,
   unsigned short saturationLimit)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_stats_collector_dense_init(inp_rc_data_A, inp_cc_data_B, scratch_C, out_sum_pix, out_cnt_unsat_pix, blk_width, blk_height, in_stride, start_x, saturationLimit, __pblock_vcop_stats_collector_dense);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_stats_collector_dense_vloops(__pblock_vcop_stats_collector_dense);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_stats_collector_dense_custom(
   __vptr_uint16 inp_rc_data_A,
   __vptr_uint16 inp_cc_data_B,
   __vptr_uint32 scratch_C,
   __vptr_uint32 out_sum_pix,
   __vptr_uint16 out_cnt_unsat_pix,
   unsigned short blk_width,
   unsigned short blk_height,
   unsigned short in_stride,
   unsigned char start_x,
   unsigned short saturationLimit,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_stats_collector_dense_init(inp_rc_data_A, inp_cc_data_B, scratch_C, out_sum_pix, out_cnt_unsat_pix, blk_width, blk_height, in_stride, start_x, saturationLimit, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_stats_collector_dense_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_rccc_to_cccc, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_rccc_to_cccc, __ALIGNOF__(int));
unsigned short __pblock_vcop_rccc_to_cccc[164];

unsigned int vcop_rccc_to_cccc_param_count(void)
{
   return 164u;
}

unsigned int vcop_rccc_to_cccc_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_rccc_to_cccc_init(
   __vptr_uint16 inp_rc_data_A,
   __vptr_uint16 inp_cc_data_B,
   unsigned short blk_width,
   unsigned short blk_height,
   unsigned short in_stride,
   __vptr_uint16 sum_c1,
   __vptr_uint16 sum_c2,
   __vptr_uint16 med,
   __vptr_uint16 low,
   __vptr_uint16 high,
   __vptr_uint8 edge_flag,
   __vptr_uint8 strip_flag,
   __vptr_uint8 c1_flag,
   __vptr_uint8 c2_flag,
   __vptr_uint16 ov,
   __vptr_uint16 oh,
   __vptr_uint8 flag_vert,
   __vptr_uint8 flag_horz,
   unsigned char start_x,
   unsigned char offset_cc,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((blk_height/2 - 2))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (((blk_width/2 - 2) + (8u) - 1)/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_TRUNC,2));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)inp_rc_data_A+(2*in_stride+start_x-1)*sizeof(*inp_rc_data_A));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)inp_rc_data_A+(2*in_stride+start_x+1)*sizeof(*inp_rc_data_A));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)inp_cc_data_B+(offset_cc*in_stride+start_x-2)*sizeof(*inp_rc_data_A));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)inp_cc_data_B+(offset_cc*in_stride+start_x+2)*sizeof(*inp_rc_data_A));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)inp_cc_data_B+((offset_cc+1)*in_stride+start_x-2)*sizeof(*inp_rc_data_A));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)inp_cc_data_B+((offset_cc+1)*in_stride+start_x+2)*sizeof(*inp_rc_data_A));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)sum_c1);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)sum_c2);
   __vcop_pblock_init16(pblock, __offset+_PREG(24), (in_stride*sizeof(*inp_rc_data_A)) -((2*8u)*sizeof(*inp_rc_data_A))*((((blk_width/2 - 2) + (8u) - 1)/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(25), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(26), ((blk_width/2-2)*sizeof(*sum_c1)) -(8u*sizeof(*sum_c1))*((((blk_width/2 - 2) + (8u) - 1)/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)inp_rc_data_A+(start_x-1)*sizeof(*inp_rc_data_A));
   __vcop_pblock_init32(pblock, __offset+_PREG(30), (uchar *)inp_rc_data_A+(start_x+1)*sizeof(*inp_rc_data_A));
   __offset += 30;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((blk_height/2 - 2))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (((blk_width/2 - 2) + (8u) - 1)/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_TRUNC,1));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), -2);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)inp_rc_data_A+(in_stride+(start_x-1))*sizeof(*inp_rc_data_A));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)inp_rc_data_A+(in_stride+(start_x+1))*sizeof(*inp_rc_data_A));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)inp_cc_data_B+(offset_cc*in_stride+start_x)*sizeof(*inp_rc_data_A));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)inp_cc_data_B+((offset_cc+1)*in_stride+start_x)*sizeof(*inp_rc_data_A));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)med);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)low);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)high);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)edge_flag);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)strip_flag);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)c1_flag);
   __vcop_pblock_init32(pblock, __offset+_PREG(30), (uchar *)c2_flag);
   __vcop_pblock_init16(pblock, __offset+_PREG(32), (in_stride*sizeof(*inp_rc_data_A)) -((2*8u)*sizeof(*inp_rc_data_A))*((((blk_width/2 - 2) + (8u) - 1)/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(33), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(34), ((blk_width/2-2)) -(8u)*((((blk_width/2 - 2) + (8u) - 1)/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(35), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(36), ((blk_width/2-2)*2) -(8u*2)*((((blk_width/2 - 2) + (8u) - 1)/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(38), 1);
   __vcop_pblock_init32(pblock, __offset+_PREG(40), 2);
   __offset += 40;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((blk_height/2 - 2))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (((blk_width/2 - 2) + (8u) - 1)/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_TRUNC,2));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)inp_rc_data_A+(in_stride+(start_x+1))*sizeof(*inp_rc_data_A));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)inp_cc_data_B+(offset_cc*in_stride+start_x-1)*sizeof(*inp_rc_data_A));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)inp_cc_data_B+(offset_cc*in_stride+start_x)*sizeof(*inp_rc_data_A));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)inp_cc_data_B+(offset_cc*in_stride+start_x+1)*sizeof(*inp_rc_data_A));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)inp_cc_data_B+((offset_cc+1)*in_stride+start_x-1)*sizeof(*inp_rc_data_A));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)inp_cc_data_B+((offset_cc+1)*in_stride+start_x)*sizeof(*inp_rc_data_A));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)inp_cc_data_B+((offset_cc+1)*in_stride+start_x+1)*sizeof(*inp_rc_data_A));
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)ov);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)oh);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)flag_vert);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)flag_horz);
   __vcop_pblock_init16(pblock, __offset+_PREG(30), (in_stride*sizeof(*inp_rc_data_A)) -((2*8u)*sizeof(*inp_rc_data_A))*((((blk_width/2 - 2) + (8u) - 1)/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(31), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(32), ((blk_width/2-2)) -(8u)*((((blk_width/2 - 2) + (8u) - 1)/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(33), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(34), ((blk_width/2-2)*2) -(8u*2)*((((blk_width/2 - 2) + (8u) - 1)/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(36), 1);
   __vcop_pblock_init32(pblock, __offset+_PREG(38), (uchar *)inp_rc_data_A+(in_stride+(start_x-1))*sizeof(*inp_rc_data_A));
   __offset += 38;

   /* Loop 4 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((blk_height/2 - 2))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (((blk_width/2 - 2) + (8u) - 1)/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)med);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)sum_c1);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)sum_c2);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)c1_flag);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)c2_flag);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)low);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)high);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)inp_rc_data_A+(in_stride+start_x)*2);
   __vcop_pblock_init16(pblock, __offset+_PREG(22), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(23), ((blk_width/2-2)) -(8u)*((((blk_width/2 - 2) + (8u) - 1)/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(24), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(25), ((blk_width/2-2)*2) -(8u*2)*((((blk_width/2 - 2) + (8u) - 1)/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(26), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(27), (in_stride*2) -((2*8u)*2)*((((blk_width/2 - 2) + (8u) - 1)/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(28), 1);
   __vcop_pblock_init32(pblock, __offset+_PREG(30), 0);
   __offset += 30;

   /* Loop 5 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((blk_height/2 - 2))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (((blk_width/2 - 2) + (8u) - 1)/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)strip_flag);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)ov);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)oh);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)flag_vert);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)flag_horz);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)inp_rc_data_A+(in_stride+start_x)*2);
   __vcop_pblock_init16(pblock, __offset+_PREG(18), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(19), ((blk_width/2-2)) -(8u)*((((blk_width/2 - 2) + (8u) - 1)/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(20), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(21), ((blk_width/2-2)*2) -(8u*2)*((((blk_width/2 - 2) + (8u) - 1)/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(22), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(23), (in_stride*2) -((2*8u)*2)*((((blk_width/2 - 2) + (8u) - 1)/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)med);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)edge_flag);
   __offset += 26;

   return 164u;
}

void vcop_rccc_to_cccc_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("C1", 16);
   #pragma VCC_VREG("C2", 17);
   #pragma VCC_VREG("C3", 18);
   #pragma VCC_VREG("C4", 19);
   #pragma VCC_VREG("C5", 20);
   #pragma VCC_VREG("C6", 21);
   #pragma VCC_VREG("C7", 22);
   #pragma VCC_VREG("C8", 23);
   #pragma VCC_VREG("CD1", 24);
   #pragma VCC_VREG("CD2", 25);
   #pragma VCC_VREG("D1", 26);
   #pragma VCC_VREG("D2", 27);
   #pragma VCC_VREG("Vsum_c1", 28);
   #pragma VCC_VREG("Vsum_c2", 29);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("AddrIn", "A0");
   #pragma EVE_REG("AddrOut", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 19u, 15u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(24), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(25), _PREG(26), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(28), _AGEN(0), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(30), _AGEN(0), _VREG(17), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(8), _AGEN(0), _VREG(22), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(10), _AGEN(0), _VREG(23), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(12), _AGEN(0), _VREG(18), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(14), _AGEN(0), _VREG(19), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(16), _AGEN(0), _VREG(20), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(18), _AGEN(0), _VREG(21), __vcop_alws());
   __vcop_vadd(_VREG(17), _VREG(19), _VREG(26));
   __vcop_vadd(_VREG(16), _VREG(18), _VREG(24));
   __vcop_vadd(_VREG(20), _VREG(22), _VREG(27));
   __vcop_vadd(_VREG(21), _VREG(23), _VREG(25));
   __vcop_vadd(_VREG(26), _VREG(27), _VREG(28));
   __vcop_vadd(_VREG(24), _VREG(25), _VREG(29));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(28), _PREG(20), _AGEN(1), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(29), _PREG(22), _AGEN(1), _PREG(6));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("AVG", 30);
   #pragma VCC_VREG("B", 31);
   #pragma VCC_VREG("B_", 32);
   #pragma VCC_VREG("F1", 33);
   #pragma VCC_VREG("F2", 34);
   #pragma VCC_VREG("F3", 35);
   #pragma VCC_VREG("F4", 36);
   #pragma VCC_VREG("L", 37);
   #pragma VCC_VREG("L_", 38);
   #pragma VCC_VREG("R", 39);
   #pragma VCC_VREG("R_", 40);
   #pragma VCC_VREG("S", 41);
   #pragma VCC_VREG("S1", 42);
   #pragma VCC_VREG("S2", 43);
   #pragma VCC_VREG("T", 44);
   #pragma VCC_VREG("T_", 45);
   #pragma VCC_VREG("VK1", 46);
   #pragma VCC_VREG("VK2", 47);
   #pragma VCC_VREG("VM2", 48);
   #pragma VCC_VREG("Vc1_flag", 49);
   #pragma VCC_VREG("Vc2_flag", 50);
   #pragma VCC_VREG("Vedge_flag", 51);
   #pragma VCC_VREG("Vmed2", 52);
   #pragma VCC_VREG("Vstrip_flag", 53);
   #pragma VCC_VREG("sTM", 54);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("AddrIn", "A0");
   #pragma EVE_REG("AddrOut1", "A1");
   #pragma EVE_REG("AddrOut2", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 43u, 20u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(38), _VREG(46));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(40), _VREG(47));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(8), _VREG(48));
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(32), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(33), _PREG(34), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(35), _PREG(36), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(10), _AGEN(0), _VREG(37), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(12), _AGEN(0), _VREG(39), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(14), _AGEN(0), _VREG(44), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(16), _AGEN(0), _VREG(31), __vcop_alws());
   __vcop_vadd(_VREG(44), _VREG(31), _VREG(42));
   __vcop_vadd(_VREG(37), _VREG(39), _VREG(43));
   __vcop_vadd(_VREG(42), _VREG(43), _VREG(41));
   __vcop_vshf(_VREG(41), _VREG(48), _VREG(30));
   __vcop_vcmpge(_VREG(44), _VREG(30), _VREG(45));
   __vcop_vcmpge(_VREG(37), _VREG(30), _VREG(38));
   __vcop_vcmpge(_VREG(39), _VREG(30), _VREG(40));
   __vcop_vcmpge(_VREG(31), _VREG(30), _VREG(32));
   __vcop_vadd(_VREG(45), _VREG(38), _VREG(42));
   __vcop_vadd(_VREG(40), _VREG(32), _VREG(43));
   __vcop_vadd(_VREG(42), _VREG(43), _VREG(54));
   __vcop_vcmpeq(_VREG(38), _VREG(40), _VREG(33));
   __vcop_vcmpeq(_VREG(54), _VREG(47), _VREG(34));
   __vcop_vcmpeq(_VREG(45), _VREG(38), _VREG(35));
   __vcop_vcmpeq(_VREG(45), _VREG(40), _VREG(36));
   __vcop_vand(_VREG(33), _VREG(34), _VREG(53));
   __vcop_vand(_VREG(34), _VREG(35), _VREG(49));
   __vcop_vand(_VREG(34), _VREG(36), _VREG(50));
   __vcop_vsort2(_VREG(44), _VREG(37));
   __vcop_vsort2(_VREG(39), _VREG(31));
   __vcop_vsort2(_VREG(44), _VREG(39));
   __vcop_vsort2(_VREG(37), _VREG(31));
   __vcop_vadd(_VREG(37), _VREG(39), _VREG(52));
   __vcop_vxor(_VREG(34), _VREG(46), _VREG(51));
   __vcop_vsort2(_VREG(37), _VREG(39));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(52), _PREG(18), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(37), _PREG(20), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(39), _PREG(22), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(51), _PREG(24), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(53), _PREG(26), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(49), _PREG(28), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(50), _PREG(30), _AGEN(1), _PREG(0));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("A11", 55);
   #pragma VCC_VREG("A12", 56);
   #pragma VCC_VREG("A13", 57);
   #pragma VCC_VREG("A21", 58);
   #pragma VCC_VREG("A23", 59);
   #pragma VCC_VREG("A31", 60);
   #pragma VCC_VREG("A32", 61);
   #pragma VCC_VREG("A33", 62);
   #pragma VCC_VREG("S", 63);
   #pragma VCC_VREG("S1", 64);
   #pragma VCC_VREG("S2", 65);
   #pragma VCC_VREG("VK1", 66);
   #pragma VCC_VREG("Vflag_horz", 67);
   #pragma VCC_VREG("Vflag_vert", 68);
   #pragma VCC_VREG("Voh", 69);
   #pragma VCC_VREG("Voh_", 70);
   #pragma VCC_VREG("Vov", 71);
   #pragma VCC_VREG("Vov_", 72);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("AddrIn", "A0");
   #pragma EVE_REG("AddrOut1", "A1");
   #pragma EVE_REG("AddrOut2", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 28u, 19u, 3u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(36), _VREG(66));
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(30), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(31), _PREG(32), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(33), _PREG(34), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(38), _AGEN(0), _VREG(58), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(8), _AGEN(0), _VREG(59), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(10), _AGEN(0), _VREG(55), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(12), _AGEN(0), _VREG(56), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(14), _AGEN(0), _VREG(57), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(16), _AGEN(0), _VREG(60), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(18), _AGEN(0), _VREG(61), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(20), _AGEN(0), _VREG(62), __vcop_alws());
   __vcop_vadd(_VREG(55), _VREG(57), _VREG(64));
   __vcop_vadd(_VREG(60), _VREG(62), _VREG(65));
   __vcop_vadd(_VREG(64), _VREG(65), _VREG(63));
   __vcop_vadd(_VREG(56), _VREG(61), _VREG(72));
   __vcop_vadd(_VREG(58), _VREG(59), _VREG(70));
   __vcop_vshf(_VREG(72), _VREG(66), _VREG(71));
   __vcop_vshf(_VREG(70), _VREG(66), _VREG(69));
   __vcop_vabsdif(_VREG(71), _VREG(63), _VREG(64));
   __vcop_vabsdif(_VREG(69), _VREG(63), _VREG(65));
   __vcop_vcmpgt(_VREG(64), _VREG(65), _VREG(68));
   __vcop_vcmpge(_VREG(65), _VREG(64), _VREG(67));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(71), _PREG(22), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(69), _PREG(24), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(68), _PREG(26), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(67), _PREG(28), _AGEN(1), _PREG(0));
   __vcop_vloop_end(3u);

   /* VLOOP 4 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VK0", 73);
   #pragma VCC_VREG("VK1", 74);
   #pragma VCC_VREG("Vc1_flag", 75);
   #pragma VCC_VREG("Vc2_flag", 76);
   #pragma VCC_VREG("Vflag_c2", 77);
   #pragma VCC_VREG("Vhigh", 78);
   #pragma VCC_VREG("Vlow", 79);
   #pragma VCC_VREG("Vmed", 80);
   #pragma VCC_VREG("Vmed2", 81);
   #pragma VCC_VREG("Vout_c1", 82);
   #pragma VCC_VREG("Vout_c1_", 83);
   #pragma VCC_VREG("Vout_c2", 84);
   #pragma VCC_VREG("Vout_c2_", 85);
   #pragma VCC_VREG("Vsum_c1", 86);
   #pragma VCC_VREG("Vsum_c2", 87);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("AddrIn1", "A0");
   #pragma EVE_REG("AddrIn2", "A1");
   #pragma EVE_REG("AddrOut", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 23u, 15u, 4u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(28), _VREG(74));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(30), _VREG(73));
   __vcop_vagen(_AGEN(0), _PREG(22), _PREG(23), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(24), _PREG(25), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(26), _PREG(27), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(6), _AGEN(1), _VREG(80), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(8), _AGEN(1), _VREG(86), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(10), _AGEN(1), _VREG(87), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(12), _AGEN(0), _VREG(75), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(14), _AGEN(0), _VREG(76), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(16), _AGEN(1), _VREG(79), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(18), _AGEN(1), _VREG(78), __vcop_alws());
   __vcop_vshf(_VREG(80), _VREG(74), _VREG(81));
   __vcop_vadd(_VREG(76), _VREG(73), _VREG(77));
   __vcop_vsub(_VREG(81), _VREG(86), _VREG(82));
   __vcop_vsub(_VREG(81), _VREG(87), _VREG(84));
   __vcop_vmin(_VREG(82), _VREG(78), _VREG(83));
   __vcop_vmin(_VREG(84), _VREG(78), _VREG(85));
   __vcop_vmax(_VREG(83), _VREG(79), _VREG(82));
   __vcop_vmax(_VREG(85), _VREG(79), _VREG(84));
   __vcop_vstore(__vcop_predicate(_VREG(75)), __vcop_sizeHU(), __vcop_skip(), __vcop_alws(), _VREG(82), _PREG(20), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_predicate(_VREG(77)), __vcop_sizeHU(), __vcop_skip(), __vcop_alws(), _VREG(84), _PREG(20), _AGEN(2), _PREG(0));
   __vcop_vloop_end(4u);

   /* VLOOP 5 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vedge_flag", 88);
   #pragma VCC_VREG("Vflag_horz", 89);
   #pragma VCC_VREG("Vflag_vert", 90);
   #pragma VCC_VREG("Vmed", 91);
   #pragma VCC_VREG("Voh", 92);
   #pragma VCC_VREG("Vov", 93);
   #pragma VCC_VREG("Vstrip_flag", 94);
   #pragma VCC_VREG("Vstrip_horz", 95);
   #pragma VCC_VREG("Vstrip_vert", 96);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("AddrIn1", "A0");
   #pragma EVE_REG("AddrIn2", "A1");
   #pragma EVE_REG("AddrOut", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 16u, 13u, 5u);
   __vcop_vagen(_AGEN(0), _PREG(18), _PREG(19), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(20), _PREG(21), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(22), _PREG(23), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(24), _AGEN(1), _VREG(91), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(26), _AGEN(0), _VREG(88), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(6), _AGEN(0), _VREG(94), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(8), _AGEN(1), _VREG(93), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(10), _AGEN(1), _VREG(92), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(12), _AGEN(0), _VREG(90), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(14), _AGEN(0), _VREG(89), __vcop_alws());
   __vcop_vand(_VREG(94), _VREG(90), _VREG(96));
   __vcop_vand(_VREG(94), _VREG(89), _VREG(95));
   __vcop_vstore(__vcop_predicate(_VREG(88)), __vcop_sizeHU(), __vcop_skip(), __vcop_alws(), _VREG(91), _PREG(16), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_predicate(_VREG(96)), __vcop_sizeHU(), __vcop_skip(), __vcop_alws(), _VREG(93), _PREG(16), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_predicate(_VREG(95)), __vcop_sizeHU(), __vcop_skip(), __vcop_alws(), _VREG(92), _PREG(16), _AGEN(2), _PREG(0));
   __vcop_vloop_end(5u);

}

void vcop_rccc_to_cccc(
   __vptr_uint16 inp_rc_data_A,
   __vptr_uint16 inp_cc_data_B,
   unsigned short blk_width,
   unsigned short blk_height,
   unsigned short in_stride,
   __vptr_uint16 sum_c1,
   __vptr_uint16 sum_c2,
   __vptr_uint16 med,
   __vptr_uint16 low,
   __vptr_uint16 high,
   __vptr_uint8 edge_flag,
   __vptr_uint8 strip_flag,
   __vptr_uint8 c1_flag,
   __vptr_uint8 c2_flag,
   __vptr_uint16 ov,
   __vptr_uint16 oh,
   __vptr_uint8 flag_vert,
   __vptr_uint8 flag_horz,
   unsigned char start_x,
   unsigned char offset_cc)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_rccc_to_cccc_init(inp_rc_data_A, inp_cc_data_B, blk_width, blk_height, in_stride, sum_c1, sum_c2, med, low, high, edge_flag, strip_flag, c1_flag, c2_flag, ov, oh, flag_vert, flag_horz, start_x, offset_cc, __pblock_vcop_rccc_to_cccc);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_rccc_to_cccc_vloops(__pblock_vcop_rccc_to_cccc);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_rccc_to_cccc_custom(
   __vptr_uint16 inp_rc_data_A,
   __vptr_uint16 inp_cc_data_B,
   unsigned short blk_width,
   unsigned short blk_height,
   unsigned short in_stride,
   __vptr_uint16 sum_c1,
   __vptr_uint16 sum_c2,
   __vptr_uint16 med,
   __vptr_uint16 low,
   __vptr_uint16 high,
   __vptr_uint8 edge_flag,
   __vptr_uint8 strip_flag,
   __vptr_uint8 c1_flag,
   __vptr_uint8 c2_flag,
   __vptr_uint16 ov,
   __vptr_uint16 oh,
   __vptr_uint8 flag_vert,
   __vptr_uint8 flag_horz,
   unsigned char start_x,
   unsigned char offset_cc,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_rccc_to_cccc_init(inp_rc_data_A, inp_cc_data_B, blk_width, blk_height, in_stride, sum_c1, sum_c2, med, low, high, edge_flag, strip_flag, c1_flag, c2_flag, ov, oh, flag_vert, flag_horz, start_x, offset_cc, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_rccc_to_cccc_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_gbce_simple, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_gbce_simple, __ALIGNOF__(int));
unsigned short __pblock_vcop_gbce_simple[32];

unsigned int vcop_gbce_simple_param_count(void)
{
   return 32u;
}

unsigned int vcop_gbce_simple_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_gbce_simple_init(
   __vptr_uint16 inp_rc_data_A,
   __vptr_uint16 inp_cc_data_B,
   __vptr_uint8 out_rc_data_B,
   __vptr_uint8 out_cc_data_A,
   unsigned short blockWidth,
   unsigned short blockHeight,
   unsigned short blockStride,
   unsigned char shift,
   __vptr_uint8 pGbceToneCurve_C,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   const int preg_ref2 = _PREG(7);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (blockHeight/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((blockWidth + (4) - 1)/(4))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_SYMM,preg_ref2,RM_TRUNC,shift));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 4095);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)out_rc_data_B);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), ((blockStride*sizeof(*inp_rc_data_A))) -((sizeof(*inp_rc_data_A)*4))*(((blockWidth + (4) - 1)/(4))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), 4);
   __vcop_pblock_init16(pblock, __offset+_PREG(13), ((blockWidth*sizeof(*out_rc_data_B))) -((sizeof(*out_rc_data_B)*4))*(((blockWidth + (4) - 1)/(4))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)inp_rc_data_A);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pGbceToneCurve_C);
   __offset += 16;

   /* Loop 2 PREGS */
   const int preg_ref3 = _PREG(7);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (blockHeight/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((blockWidth + (4) - 1)/(4))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_SYMM,preg_ref3,RM_TRUNC,shift));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 4095);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)out_cc_data_A);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), ((blockStride*sizeof(*inp_rc_data_A))) -((sizeof(*inp_rc_data_A)*4))*(((blockWidth + (4) - 1)/(4))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), 4);
   __vcop_pblock_init16(pblock, __offset+_PREG(13), ((blockWidth*sizeof(*out_rc_data_B))) -((sizeof(*out_rc_data_B)*4))*(((blockWidth + (4) - 1)/(4))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)inp_cc_data_B);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pGbceToneCurve_C);
   __offset += 16;

   return 32u;
}

void vcop_gbce_simple_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vin", 16);
   #pragma VCC_VREG("Vout", 17);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("index_addr", "A0");
   #pragma EVE_REG("out_addr", "A2");
   #pragma EVE_REG("table_addr", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_tablelkup(), 7u, 8u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(10), _PREG(11), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(12), _PREG(13), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(14), _AGEN(0), _VREG(16), __vcop_alws());
   __vcop_vtbload(__vcop_sizeBU(), __vcop_tableinfo(4, 1), _PREG(16), _AGEN(1), _VREG(16), _VREG(17), _PREG(6), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(17), _PREG(8), _AGEN(2), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("index_addr", "A0");
   #pragma EVE_REG("out_addr", "A2");
   #pragma EVE_REG("table_addr", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_tablelkup(), 7u, 8u, 2u);
   __vcop_vagen(_AGEN(0), _PREG(10), _PREG(11), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(12), _PREG(13), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(14), _AGEN(0), _VREG(16), __vcop_alws());
   __vcop_vtbload(__vcop_sizeBU(), __vcop_tableinfo(4, 1), _PREG(16), _AGEN(1), _VREG(16), _VREG(17), _PREG(6), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(17), _PREG(8), _AGEN(2), _PREG(0));
   __vcop_vloop_end(2u);

}

void vcop_gbce_simple(
   __vptr_uint16 inp_rc_data_A,
   __vptr_uint16 inp_cc_data_B,
   __vptr_uint8 out_rc_data_B,
   __vptr_uint8 out_cc_data_A,
   unsigned short blockWidth,
   unsigned short blockHeight,
   unsigned short blockStride,
   unsigned char shift,
   __vptr_uint8 pGbceToneCurve_C)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_gbce_simple_init(inp_rc_data_A, inp_cc_data_B, out_rc_data_B, out_cc_data_A, blockWidth, blockHeight, blockStride, shift, pGbceToneCurve_C, __pblock_vcop_gbce_simple);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_gbce_simple_vloops(__pblock_vcop_gbce_simple);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_gbce_simple_custom(
   __vptr_uint16 inp_rc_data_A,
   __vptr_uint16 inp_cc_data_B,
   __vptr_uint8 out_rc_data_B,
   __vptr_uint8 out_cc_data_A,
   unsigned short blockWidth,
   unsigned short blockHeight,
   unsigned short blockStride,
   unsigned char shift,
   __vptr_uint8 pGbceToneCurve_C,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_gbce_simple_init(inp_rc_data_A, inp_cc_data_B, out_rc_data_B, out_cc_data_A, blockWidth, blockHeight, blockStride, shift, pGbceToneCurve_C, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_gbce_simple_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_gbce_interp, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_gbce_interp, __ALIGNOF__(int));
unsigned short __pblock_vcop_gbce_interp[72];

unsigned int vcop_gbce_interp_param_count(void)
{
   return 72u;
}

unsigned int vcop_gbce_interp_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_gbce_interp_init(
   __vptr_uint16 inp_rc_data_A,
   __vptr_uint16 inp_cc_data_B,
   __vptr_uint8 scratch_rc_out_B,
   __vptr_uint8 scratch_cc_out_A,
   __vptr_uint8 out_rc_data_B,
   __vptr_uint8 out_cc_data_A,
   unsigned short blockWidth,
   unsigned short blockHeight,
   unsigned short blockStride,
   unsigned char shift,
   unsigned short mask,
   __vptr_uint8 pGbceToneCurve_C,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   const int preg_ref4 = _PREG(7);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (blockHeight/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((blockWidth + (4) - 1)/(4))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_SYMM,preg_ref4,RM_TRUNC,shift));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 4094);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)scratch_rc_out_B);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), ((blockStride*sizeof(*inp_rc_data_A))) -((sizeof(*inp_rc_data_A)*4))*(((blockWidth + (4) - 1)/(4))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), ((blockWidth*sizeof(*scratch_rc_out_B)*2)) -((sizeof(*scratch_rc_out_B)*4*2))*(((blockWidth + (4) - 1)/(4))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)inp_rc_data_A);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pGbceToneCurve_C);
   __offset += 16;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (blockHeight/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((blockWidth + (8u) - 1)/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_TRUNC,shift));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 8);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), mask);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), 1);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)out_rc_data_B);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), ((blockStride*sizeof(*inp_rc_data_A))) -(8u)*(((blockWidth + (8u) - 1)/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(15), ((blockWidth*sizeof(*out_rc_data_B))) -(sizeof(*out_rc_data_B)*8u)*(((blockWidth + (8u) - 1)/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(16), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(17), ((blockWidth*sizeof(*scratch_rc_out_B)*2)) -((2*8u))*(((blockWidth + (8u) - 1)/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)inp_rc_data_A);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)scratch_rc_out_B);
   __offset += 20;

   /* Loop 3 PREGS */
   const int preg_ref5 = _PREG(7);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (blockHeight/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((blockWidth + (4) - 1)/(4))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_SYMM,preg_ref5,RM_TRUNC,shift));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 4094);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)scratch_cc_out_A);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), ((blockStride*sizeof(*inp_rc_data_A))) -((sizeof(*inp_rc_data_A)*4))*(((blockWidth + (4) - 1)/(4))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), ((blockWidth*sizeof(*scratch_rc_out_B)*2)) -((sizeof(*scratch_rc_out_B)*4*2))*(((blockWidth + (4) - 1)/(4))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)inp_cc_data_B);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pGbceToneCurve_C);
   __offset += 16;

   /* Loop 4 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (blockHeight/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((blockWidth + (8u) - 1)/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_TRUNC,shift));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 8);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), mask);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), 1);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)out_cc_data_A);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), ((blockStride*sizeof(*inp_rc_data_A))) -(8u)*(((blockWidth + (8u) - 1)/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(15), ((blockWidth*sizeof(*out_rc_data_B))) -(sizeof(*out_rc_data_B)*8u)*(((blockWidth + (8u) - 1)/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(16), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(17), ((blockWidth*sizeof(*scratch_rc_out_B)*2)) -((2*8u))*(((blockWidth + (8u) - 1)/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)inp_cc_data_B);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)scratch_cc_out_A);
   __offset += 20;

   return 72u;
}

void vcop_gbce_interp_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vin", 16);
   #pragma VCC_VREG("Vout", 17);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("index_addr", "A0");
   #pragma EVE_REG("out_addr", "A2");
   #pragma EVE_REG("table_addr", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_tablelkup(), 7u, 8u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(10), _PREG(11), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(10), _PREG(12), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(14), _AGEN(0), _VREG(16), __vcop_alws());
   __vcop_vtbload(__vcop_sizeBU(), __vcop_tableinfo(4, 2), _PREG(16), _AGEN(1), _VREG(16), _VREG(17), _PREG(6), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(17), _PREG(8), _AGEN(2), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VK1", 18);
   #pragma VCC_VREG("Vmask", 19);
   #pragma VCC_VREG("Vout1", 20);
   #pragma VCC_VREG("Vout2", 21);
   #pragma VCC_VREG("Vshift", 22);
   #pragma VCC_VREG("Vwgt1", 23);
   #pragma VCC_VREG("Vwgt2", 24);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("AddrIn", "A0");
   #pragma EVE_REG("AddrOut", "A1");
   #pragma EVE_REG("AddrScratch", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 14u, 10u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(8), _VREG(19));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(10), _VREG(18));
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(14), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(15), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(16), _PREG(17), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(18), _AGEN(0), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(20), _AGEN(2), _VPAIR(20,21), __vcop_alws());
   __vcop_vand(_VREG(16), _VREG(19), _VREG(24));
   __vcop_vadd(_VREG(19), _VREG(18), _VREG(22));
   __vcop_vsub(_VREG(22), _VREG(24), _VREG(23));
   __vcop_vmpy(_VREG(21), _VREG(24), _VREG(17), _PREG(0));
   __vcop_vmadd(_VREG(20), _VREG(23), _VREG(17), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(17), _PREG(12), _AGEN(1), _PREG(6));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("index_addr", "A0");
   #pragma EVE_REG("out_addr", "A2");
   #pragma EVE_REG("table_addr", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_tablelkup(), 7u, 8u, 3u);
   __vcop_vagen(_AGEN(0), _PREG(10), _PREG(11), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(10), _PREG(12), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(14), _AGEN(0), _VREG(16), __vcop_alws());
   __vcop_vtbload(__vcop_sizeBU(), __vcop_tableinfo(4, 2), _PREG(16), _AGEN(1), _VREG(16), _VREG(17), _PREG(6), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(17), _PREG(8), _AGEN(2), _PREG(0));
   __vcop_vloop_end(3u);

   /* VLOOP 4 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VK1", 25);
   #pragma VCC_VREG("Vmask", 26);
   #pragma VCC_VREG("Vout1", 27);
   #pragma VCC_VREG("Vout2", 28);
   #pragma VCC_VREG("Vshift", 29);
   #pragma VCC_VREG("Vwgt1", 30);
   #pragma VCC_VREG("Vwgt2", 31);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("AddrIn", "A0");
   #pragma EVE_REG("AddrOut", "A1");
   #pragma EVE_REG("AddrScratch", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 14u, 10u, 4u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(8), _VREG(26));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(10), _VREG(25));
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(14), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(15), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(16), _PREG(17), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(18), _AGEN(0), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(20), _AGEN(2), _VPAIR(27,28), __vcop_alws());
   __vcop_vand(_VREG(16), _VREG(26), _VREG(31));
   __vcop_vadd(_VREG(26), _VREG(25), _VREG(29));
   __vcop_vsub(_VREG(29), _VREG(31), _VREG(30));
   __vcop_vmpy(_VREG(28), _VREG(31), _VREG(17), _PREG(0));
   __vcop_vmadd(_VREG(27), _VREG(30), _VREG(17), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(17), _PREG(12), _AGEN(1), _PREG(6));
   __vcop_vloop_end(4u);

}

void vcop_gbce_interp(
   __vptr_uint16 inp_rc_data_A,
   __vptr_uint16 inp_cc_data_B,
   __vptr_uint8 scratch_rc_out_B,
   __vptr_uint8 scratch_cc_out_A,
   __vptr_uint8 out_rc_data_B,
   __vptr_uint8 out_cc_data_A,
   unsigned short blockWidth,
   unsigned short blockHeight,
   unsigned short blockStride,
   unsigned char shift,
   unsigned short mask,
   __vptr_uint8 pGbceToneCurve_C)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_gbce_interp_init(inp_rc_data_A, inp_cc_data_B, scratch_rc_out_B, scratch_cc_out_A, out_rc_data_B, out_cc_data_A, blockWidth, blockHeight, blockStride, shift, mask, pGbceToneCurve_C, __pblock_vcop_gbce_interp);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_gbce_interp_vloops(__pblock_vcop_gbce_interp);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_gbce_interp_custom(
   __vptr_uint16 inp_rc_data_A,
   __vptr_uint16 inp_cc_data_B,
   __vptr_uint8 scratch_rc_out_B,
   __vptr_uint8 scratch_cc_out_A,
   __vptr_uint8 out_rc_data_B,
   __vptr_uint8 out_cc_data_A,
   unsigned short blockWidth,
   unsigned short blockHeight,
   unsigned short blockStride,
   unsigned char shift,
   unsigned short mask,
   __vptr_uint8 pGbceToneCurve_C,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_gbce_interp_init(inp_rc_data_A, inp_cc_data_B, scratch_rc_out_B, scratch_cc_out_A, out_rc_data_B, out_cc_data_A, blockWidth, blockHeight, blockStride, shift, mask, pGbceToneCurve_C, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_gbce_interp_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

