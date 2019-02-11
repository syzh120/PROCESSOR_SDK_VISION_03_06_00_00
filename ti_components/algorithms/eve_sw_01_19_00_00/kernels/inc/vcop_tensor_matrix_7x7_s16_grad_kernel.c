#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_tensor_matrix_7x7_s16_grad, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_tensor_matrix_7x7_s16_grad, __ALIGNOF__(int));
unsigned short __pblock_vcop_tensor_matrix_7x7_s16_grad[54];

unsigned int vcop_tensor_matrix_7x7_s16_grad_param_count(void)
{
   return 54u;
}

unsigned int vcop_tensor_matrix_7x7_s16_grad_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_tensor_matrix_7x7_s16_grad_init(
   __vptr_int16 gradX_a,
   __vptr_int16 gradY_b,
   unsigned short stride,
   unsigned short n,
   __vptr_int32 Ix2_a,
   __vptr_int32 Iy2_b,
   __vptr_int32 Ixy_c,
   __vptr_int32 scartch_a,
   __vptr_int32 scartch_b,
   __vptr_int32 scartch_c,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (n/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((8u)/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((7))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)gradY_b);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)gradX_a+stride*7*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)gradY_b+stride*7*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)scartch_a);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)scartch_a+4);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)scartch_b);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)scartch_b+4);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)scartch_c);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)scartch_c+4);
   __vcop_pblock_init16(pblock, __offset+_PREG(24), (stride*2));
   __vcop_pblock_init16(pblock, __offset+_PREG(25), (2*stride*7*2) -(stride*2)*(((7))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(26), (8u*7*stride*2) -(2*stride*7*2)*(((8u)/2)-1u) -(stride*2)*(((7))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(27), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(28), 264);
   __vcop_pblock_init32(pblock, __offset+_PREG(30), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(32), (uchar *)gradX_a);
   __offset += 32;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (n/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((7))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)scartch_b);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)scartch_c);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)Ix2_a);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)Iy2_b);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)Ixy_c);
   __vcop_pblock_init16(pblock, __offset+_PREG(16), 36);
   __vcop_pblock_init16(pblock, __offset+_PREG(17), 72);
   __vcop_pblock_init16(pblock, __offset+_PREG(18), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)scartch_a);
   __offset += 22;

   return 54u;
}

void vcop_tensor_matrix_7x7_s16_grad_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VgradX1", 16);
   #pragma VCC_VREG("VgradX2", 17);
   #pragma VCC_VREG("VgradY1", 18);
   #pragma VCC_VREG("VgradY2", 19);
   #pragma VCC_VREG("VsumIx21", 20);
   #pragma VCC_VREG("VsumIx22", 21);
   #pragma VCC_VREG("VsumIxy1", 22);
   #pragma VCC_VREG("VsumIxy2", 23);
   #pragma VCC_VREG("VsumIy21", 24);
   #pragma VCC_VREG("VsumIy22", 25);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("inAddr", "A0");
   #pragma EVE_REG("outAddr", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I0", "I2");
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 25u, 16u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(30), _VREG(20));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(30), _VREG(24));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(30), _VREG(22));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(30), _VREG(21));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(30), _VREG(25));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(30), _VREG(23));
   __vcop_vagen(_AGEN(0), _PREG(24), _PREG(25), _PREG(26), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(27), _PREG(28), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(32), _AGEN(0), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(6), _AGEN(0), _VREG(18), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(8), _AGEN(0), _VREG(17), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(10), _AGEN(0), _VREG(19), __vcop_alws());
   __vcop_vmadd(_VREG(16), _VREG(16), _VREG(20), _PREG(0));
   __vcop_vmadd(_VREG(17), _VREG(17), _VREG(21), _PREG(0));
   __vcop_vmadd(_VREG(18), _VREG(18), _VREG(24), _PREG(0));
   __vcop_vmadd(_VREG(19), _VREG(19), _VREG(25), _PREG(0));
   __vcop_vmadd(_VREG(16), _VREG(18), _VREG(22), _PREG(0));
   __vcop_vmadd(_VREG(17), _VREG(19), _VREG(23), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_offst_np1(), __vcop_last_i4(), _VREG(20), _PREG(12), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_offst_np1(), __vcop_last_i4(), _VREG(21), _PREG(14), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_offst_np1(), __vcop_last_i4(), _VREG(24), _PREG(16), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_offst_np1(), __vcop_last_i4(), _VREG(25), _PREG(18), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_offst_np1(), __vcop_last_i4(), _VREG(22), _PREG(20), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_offst_np1(), __vcop_last_i4(), _VREG(23), _PREG(22), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("inAddr", "A0");
   #pragma EVE_REG("outAddr", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I0", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 15u, 11u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(20), _VREG(20));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(20), _VREG(24));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(20), _VREG(22));
   __vcop_vagen(_AGEN(0), _PREG(16), _PREG(17), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(18), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(22), _AGEN(0), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(6), _AGEN(0), _VREG(17), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(8), _AGEN(0), _VREG(18), __vcop_alws());
   __vcop_vadd(_VREG(20), _VREG(16), _VREG(20));
   __vcop_vadd(_VREG(24), _VREG(17), _VREG(24));
   __vcop_vadd(_VREG(22), _VREG(18), _VREG(22));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_last_i4(), _VREG(20), _PREG(10), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_last_i4(), _VREG(24), _PREG(12), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_last_i4(), _VREG(22), _PREG(14), _AGEN(1), _PREG(0));
   __vcop_vloop_end(2u);

}

void vcop_tensor_matrix_7x7_s16_grad(
   __vptr_int16 gradX_a,
   __vptr_int16 gradY_b,
   unsigned short stride,
   unsigned short n,
   __vptr_int32 Ix2_a,
   __vptr_int32 Iy2_b,
   __vptr_int32 Ixy_c,
   __vptr_int32 scartch_a,
   __vptr_int32 scartch_b,
   __vptr_int32 scartch_c)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_tensor_matrix_7x7_s16_grad_init(gradX_a, gradY_b, stride, n, Ix2_a, Iy2_b, Ixy_c, scartch_a, scartch_b, scartch_c, __pblock_vcop_tensor_matrix_7x7_s16_grad);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_tensor_matrix_7x7_s16_grad_vloops(__pblock_vcop_tensor_matrix_7x7_s16_grad);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_tensor_matrix_7x7_s16_grad_custom(
   __vptr_int16 gradX_a,
   __vptr_int16 gradY_b,
   unsigned short stride,
   unsigned short n,
   __vptr_int32 Ix2_a,
   __vptr_int32 Iy2_b,
   __vptr_int32 Ixy_c,
   __vptr_int32 scartch_a,
   __vptr_int32 scartch_b,
   __vptr_int32 scartch_c,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_tensor_matrix_7x7_s16_grad_init(gradX_a, gradY_b, stride, n, Ix2_a, Iy2_b, Ixy_c, scartch_a, scartch_b, scartch_c, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_tensor_matrix_7x7_s16_grad_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

