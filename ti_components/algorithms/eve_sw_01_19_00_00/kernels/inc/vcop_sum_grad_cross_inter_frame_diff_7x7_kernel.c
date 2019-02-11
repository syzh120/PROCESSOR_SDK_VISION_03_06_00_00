#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_sum_grad_cross_inter_frame_diff_7x7, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_sum_grad_cross_inter_frame_diff_7x7, __ALIGNOF__(int));
unsigned short __pblock_vcop_sum_grad_cross_inter_frame_diff_7x7[44];

unsigned int vcop_sum_grad_cross_inter_frame_diff_7x7_param_count(void)
{
   return 44u;
}

unsigned int vcop_sum_grad_cross_inter_frame_diff_7x7_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_sum_grad_cross_inter_frame_diff_7x7_init(
   __vptr_int16 gradX_a,
   __vptr_int16 gradY_b,
   __vptr_uint8 im1_a,
   __vptr_uint8 im2_b,
   unsigned short gradStride,
   unsigned short imStride,
   unsigned short n,
   __vptr_int32 IxIt_a,
   __vptr_int32 IyIt_b,
   __vptr_int32 scartch_a,
   __vptr_int32 scartch_b,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), ((n + (8u)-1)/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((7))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)gradY_b);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)im1_a);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)im2_b);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)scartch_a);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)scartch_b);
   __vcop_pblock_init16(pblock, __offset+_PREG(16), (gradStride*2));
   __vcop_pblock_init16(pblock, __offset+_PREG(17), (gradStride*7*2) -(gradStride*2)*(((7))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(18), (8u*7*gradStride*2) -(gradStride*7*2)*(((8u))-1u) -(gradStride*2)*(((7))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(19), (imStride*1));
   __vcop_pblock_init16(pblock, __offset+_PREG(20), (imStride*7*1) -(imStride*1)*(((7))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(21), (8u*7*imStride*1) -(imStride*7*1)*(((8u))-1u) -(imStride*1)*(((7))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(22), 4);
   __vcop_pblock_init16(pblock, __offset+_PREG(23), 260);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)gradX_a);
   __offset += 26;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((n + (8u)-1)/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((7))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)scartch_b);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)IxIt_a);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)IyIt_b);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), 36);
   __vcop_pblock_init16(pblock, __offset+_PREG(13), 72);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)scartch_a);
   __offset += 18;

   return 44u;
}

void vcop_sum_grad_cross_inter_frame_diff_7x7_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VDiff", 16);
   #pragma VCC_VREG("VIxIt", 17);
   #pragma VCC_VREG("VIyIt", 18);
   #pragma VCC_VREG("VgradX", 19);
   #pragma VCC_VREG("VgradY", 20);
   #pragma VCC_VREG("VimC", 21);
   #pragma VCC_VREG("VimP", 22);
   #pragma VCC_VREG("VsumIxIt", 23);
   #pragma VCC_VREG("VsumIyIt", 24);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("inAddr1", "A0");
   #pragma EVE_REG("inAddr2", "A1");
   #pragma EVE_REG("outAddr", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I0", "I2");
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 15u, 13u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(24), _VREG(23));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(24), _VREG(24));
   __vcop_vagen(_AGEN(0), _PREG(16), _PREG(17), _PREG(18), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(19), _PREG(20), _PREG(21), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(0), _PREG(22), _PREG(23), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(26), _AGEN(0), _VREG(19), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(6), _AGEN(0), _VREG(20), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(8), _AGEN(1), _VREG(21), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(10), _AGEN(1), _VREG(22), __vcop_alws());
   __vcop_vsub(_VREG(21), _VREG(22), _VREG(16));
   __vcop_vmadd(_VREG(19), _VREG(16), _VREG(23), _PREG(0));
   __vcop_vmadd(_VREG(20), _VREG(16), _VREG(24), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_offst_np1(), __vcop_last_i4(), _VREG(23), _PREG(12), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_offst_np1(), __vcop_last_i4(), _VREG(24), _PREG(14), _AGEN(2), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("inAddr1", "A0");
   #pragma EVE_REG("inAddr2", "A1");
   #pragma EVE_REG("outAddr", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I0", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 12u, 9u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(16), _VREG(23));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(16), _VREG(24));
   __vcop_vagen(_AGEN(0), _PREG(12), _PREG(13), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(0), _PREG(14), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(18), _AGEN(0), _VREG(17), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(6), _AGEN(0), _VREG(18), __vcop_alws());
   __vcop_vadd(_VREG(23), _VREG(17), _VREG(23));
   __vcop_vadd(_VREG(24), _VREG(18), _VREG(24));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_last_i4(), _VREG(23), _PREG(8), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_last_i4(), _VREG(24), _PREG(10), _AGEN(2), _PREG(0));
   __vcop_vloop_end(2u);

}

void vcop_sum_grad_cross_inter_frame_diff_7x7(
   __vptr_int16 gradX_a,
   __vptr_int16 gradY_b,
   __vptr_uint8 im1_a,
   __vptr_uint8 im2_b,
   unsigned short gradStride,
   unsigned short imStride,
   unsigned short n,
   __vptr_int32 IxIt_a,
   __vptr_int32 IyIt_b,
   __vptr_int32 scartch_a,
   __vptr_int32 scartch_b)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_sum_grad_cross_inter_frame_diff_7x7_init(gradX_a, gradY_b, im1_a, im2_b, gradStride, imStride, n, IxIt_a, IyIt_b, scartch_a, scartch_b, __pblock_vcop_sum_grad_cross_inter_frame_diff_7x7);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_sum_grad_cross_inter_frame_diff_7x7_vloops(__pblock_vcop_sum_grad_cross_inter_frame_diff_7x7);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_sum_grad_cross_inter_frame_diff_7x7_custom(
   __vptr_int16 gradX_a,
   __vptr_int16 gradY_b,
   __vptr_uint8 im1_a,
   __vptr_uint8 im2_b,
   unsigned short gradStride,
   unsigned short imStride,
   unsigned short n,
   __vptr_int32 IxIt_a,
   __vptr_int32 IyIt_b,
   __vptr_int32 scartch_a,
   __vptr_int32 scartch_b,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_sum_grad_cross_inter_frame_diff_7x7_init(gradX_a, gradY_b, im1_a, im2_b, gradStride, imStride, n, IxIt_a, IyIt_b, scartch_a, scartch_b, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_sum_grad_cross_inter_frame_diff_7x7_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

