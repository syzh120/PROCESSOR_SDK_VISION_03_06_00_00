#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_mat_mul_uchar_uchar_short, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_mat_mul_uchar_uchar_short, __ALIGNOF__(int));
unsigned short __pblock_vcop_mat_mul_uchar_uchar_short[22];

unsigned int vcop_mat_mul_uchar_uchar_short_param_count(void)
{
   return 22u;
}

unsigned int vcop_mat_mul_uchar_uchar_short_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_mat_mul_uchar_uchar_short_init(
   __vptr_uint8 in1_ary,
   __vptr_uint8 in2_ary,
   __vptr_int16 res,
   int w_in1,
   int h_in1,
   int w_in2,
   int rnd_shift,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   const int preg_ref1 = _PREG(7);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (h_in1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (w_in2/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (w_in1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_ASYMM,preg_ref1,RM_ROUND,rnd_shift));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32767);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)in2_ary);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)res);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(13), (sizeof(*res)*w_in1) -(sizeof(*res)*8u)*((w_in2/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(14),  -(sizeof(*in1_ary))*((w_in1)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(15), (sizeof(*in1_ary)*w_in1) -(sizeof(*in1_ary))*((w_in1)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(16), (sizeof(*in2_ary)*w_in2));
   __vcop_pblock_init16(pblock, __offset+_PREG(17), (sizeof(*in2_ary)*8u) -(sizeof(*in2_ary)*w_in2)*((w_in1)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(18),  -(sizeof(*in2_ary)*8u)*((w_in2/(8u))-1u) -(sizeof(*in2_ary)*w_in2)*((w_in1)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)in1_ary);
   __offset += 22;

   return 22u;
}

void vcop_mat_mul_uchar_uchar_short_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("v_in1", 16);
   #pragma VCC_VREG("v_in2", 17);
   #pragma VCC_VREG("v_sum", 18);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("outAddr", "A0");
   #pragma EVE_REG("in1_Addr", "A1");
   #pragma EVE_REG("in2_Addr", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I2");
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 9u, 11u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i34_zero(), _PREG(20), _VREG(18));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(12), _PREG(13), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(1), _PREG(14), _PREG(15), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(16), _PREG(17), _PREG(18), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_1pt(), _PREG(22), _AGEN(1), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(8), _AGEN(2), _VREG(17), __vcop_alws());
   __vcop_vmadd(_VREG(16), _VREG(17), _VREG(18), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_npt(), __vcop_last_i4(), _VREG(18), _PREG(10), _AGEN(0), _PREG(6));
   __vcop_vloop_end(1u);

}

void vcop_mat_mul_uchar_uchar_short(
   __vptr_uint8 in1_ary,
   __vptr_uint8 in2_ary,
   __vptr_int16 res,
   int w_in1,
   int h_in1,
   int w_in2,
   int rnd_shift)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_mat_mul_uchar_uchar_short_init(in1_ary, in2_ary, res, w_in1, h_in1, w_in2, rnd_shift, __pblock_vcop_mat_mul_uchar_uchar_short);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_mat_mul_uchar_uchar_short_vloops(__pblock_vcop_mat_mul_uchar_uchar_short);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_mat_mul_uchar_uchar_short_custom(
   __vptr_uint8 in1_ary,
   __vptr_uint8 in2_ary,
   __vptr_int16 res,
   int w_in1,
   int h_in1,
   int w_in2,
   int rnd_shift,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_mat_mul_uchar_uchar_short_init(in1_ary, in2_ary, res, w_in1, h_in1, w_in2, rnd_shift, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_mat_mul_uchar_uchar_short_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

