#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_calc_determinant_tensor_matrix, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_calc_determinant_tensor_matrix, __ALIGNOF__(int));
unsigned short __pblock_vcop_calc_determinant_tensor_matrix[30];

unsigned int vcop_calc_determinant_tensor_matrix_param_count(void)
{
   return 30u;
}

unsigned int vcop_calc_determinant_tensor_matrix_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_calc_determinant_tensor_matrix_init(
   __vptr_uint16 Ix2L_a,
   __vptr_uint16 Iy2L_b,
   __vptr_uint16 IxyL_c,
   __vptr_int16 Ix2H_a,
   __vptr_int16 Iy2H_b,
   __vptr_int16 IxyH_c,
   __vptr_uint16 d_nrsb_a,
   __vptr_int32 d_norm_b,
   unsigned short n,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (n/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)Ix2L_a);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)Ix2H_a);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)Iy2L_b);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)Iy2H_b);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)IxyL_c);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)IxyH_c);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)d_nrsb_a);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)d_norm_b);
   __vcop_pblock_init16(pblock, __offset+_PREG(26), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(27), 16);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), 4294967295);
   __vcop_pblock_init32(pblock, __offset+_PREG(30), 31);
   __offset += 30;

   return 30u;
}

void vcop_calc_determinant_tensor_matrix_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vec0", 16);
   #pragma VCC_VREG("Vec1", 17);
   #pragma VCC_VREG("Vec10", 18);
   #pragma VCC_VREG("Vec11", 19);
   #pragma VCC_VREG("Vec12", 20);
   #pragma VCC_VREG("Vec13", 21);
   #pragma VCC_VREG("Vec14", 22);
   #pragma VCC_VREG("Vec15", 23);
   #pragma VCC_VREG("Vec2", 24);
   #pragma VCC_VREG("Vec3", 25);
   #pragma VCC_VREG("Vec4", 26);
   #pragma VCC_VREG("Vec5", 27);
   #pragma VCC_VREG("Vec6", 28);
   #pragma VCC_VREG("Vec7", 29);
   #pragma VCC_VREG("Vec8", 30);
   #pragma VCC_VREG("Vec9", 31);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   #pragma EVE_REG("Addr2", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 55u, 15u, 1u);
   __vcop_vinit(__vcop_sizeWU(), __vcop_once(), _PREG(28), _VREG(23));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(30), _VREG(21));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(6), _VREG(20));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(8), _VREG(22));
   __vcop_vagen(_AGEN(0), _PREG(26), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(27), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(10), _AGEN(0), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_ds2(), _PREG(12), _AGEN(0), _VREG(24), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(14), _AGEN(0), _VREG(26), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_ds2(), _PREG(16), _AGEN(0), _VREG(28), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(18), _AGEN(0), _VREG(30), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_ds2(), _PREG(20), _AGEN(0), _VREG(18), __vcop_alws());
   __vcop_vmpy(_VREG(16), _VREG(28), _VREG(17), _PREG(0));
   __vcop_vmpy(_VREG(24), _VREG(26), _VREG(25), _PREG(0));
   __vcop_vmpy(_VREG(24), _VREG(28), _VREG(29), _PREG(0));
   __vcop_vmpy(_VREG(16), _VREG(26), _VREG(27), _PREG(0));
   __vcop_vshf16(_VREG(17), _VREG(16), _VREG(24));
   __vcop_vshf16(_VREG(25), _VREG(26), _VREG(28));
   __vcop_vadd3(_VREG(16), _VREG(26), _VREG(27));
   __vcop_vadd3(_VREG(24), _VREG(28), _VREG(29));
   __vcop_vaddh(_VREG(29), _VREG(27), _VREG(29));
   __vcop_vmpy(_VREG(30), _VREG(30), _VREG(16), _PREG(0));
   __vcop_vmpy(_VREG(18), _VREG(18), _VREG(17), _PREG(0));
   __vcop_vmpy(_VREG(30), _VREG(18), _VREG(24), _PREG(0));
   __vcop_vshf16(_VREG(24), _VREG(25), _VREG(26));
   __vcop_vadd3(_VREG(25), _VREG(25), _VREG(16));
   __vcop_vadd3(_VREG(26), _VREG(26), _VREG(17));
   __vcop_vaddh(_VREG(17), _VREG(16), _VREG(17));
   __vcop_vand(_VREG(27), _VREG(23), _VREG(27));
   __vcop_vand(_VREG(16), _VREG(23), _VREG(16));
   __vcop_vsub(_VREG(27), _VREG(16), _VREG(16));
   __vcop_vsub(_VREG(29), _VREG(17), _VREG(17));
   __vcop_vaddh(_VREG(17), _VREG(16), _VREG(17));
   __vcop_vand(_VREG(16), _VREG(23), _VREG(16));
   __vcop_vcmpge(_VREG(17), _VREG(22), _VREG(24));
   __vcop_vlmbd(_VREG(16), _VREG(24), _VREG(25));
   __vcop_vsub(_VREG(21), _VREG(25), _VREG(26));
   __vcop_vlmbd(_VREG(17), _VREG(24), _VREG(25));
   __vcop_vsub(_VREG(21), _VREG(25), _VREG(25));
   __vcop_vcmpge(_VREG(16), _VREG(22), _VREG(30));
   __vcop_vxor(_VREG(24), _VREG(30), _VREG(24));
   __vcop_vadd(_VREG(26), _VREG(25), _VREG(26));
   __vcop_vsel(_VREG(24), _VREG(20), _VREG(26));
   __vcop_vcmpgt(_VREG(20), _VREG(25), _VREG(24));
   __vcop_vsel(_VREG(24), _VREG(25), _VREG(26));
   __vcop_vadif(_VREG(21), _VREG(20), _VREG(26));
   __vcop_vsub(_VREG(26), _VREG(20), _VREG(27));
   __vcop_vshf(_VREG(16), _VREG(27), _VREG(28));
   __vcop_vshf(_VREG(17), _VREG(26), _VREG(17));
   __vcop_vor(_VREG(17), _VREG(28), _VREG(17));
   __vcop_vcmpgt(_VREG(20), _VREG(26), _VREG(24));
   __vcop_vsel(_VREG(24), _VREG(17), _VREG(28));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(26), _PREG(22), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(28), _PREG(24), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_calc_determinant_tensor_matrix(
   __vptr_uint16 Ix2L_a,
   __vptr_uint16 Iy2L_b,
   __vptr_uint16 IxyL_c,
   __vptr_int16 Ix2H_a,
   __vptr_int16 Iy2H_b,
   __vptr_int16 IxyH_c,
   __vptr_uint16 d_nrsb_a,
   __vptr_int32 d_norm_b,
   unsigned short n)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_calc_determinant_tensor_matrix_init(Ix2L_a, Iy2L_b, IxyL_c, Ix2H_a, Iy2H_b, IxyH_c, d_nrsb_a, d_norm_b, n, __pblock_vcop_calc_determinant_tensor_matrix);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_calc_determinant_tensor_matrix_vloops(__pblock_vcop_calc_determinant_tensor_matrix);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_calc_determinant_tensor_matrix_custom(
   __vptr_uint16 Ix2L_a,
   __vptr_uint16 Iy2L_b,
   __vptr_uint16 IxyL_c,
   __vptr_int16 Ix2H_a,
   __vptr_int16 Iy2H_b,
   __vptr_int16 IxyH_c,
   __vptr_uint16 d_nrsb_a,
   __vptr_int32 d_norm_b,
   unsigned short n,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_calc_determinant_tensor_matrix_init(Ix2L_a, Iy2L_b, IxyL_c, Ix2H_a, Iy2H_b, IxyH_c, d_nrsb_a, d_norm_b, n, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_calc_determinant_tensor_matrix_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

