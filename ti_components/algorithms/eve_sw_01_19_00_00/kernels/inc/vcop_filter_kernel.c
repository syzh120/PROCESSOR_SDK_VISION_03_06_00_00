#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_filter_uchar_char_uchar, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_filter_uchar_char_uchar, __ALIGNOF__(int));
unsigned short __pblock_vcop_filter_uchar_char_uchar[22];

unsigned int vcop_filter_uchar_char_uchar_param_count(void)
{
   return 22u;
}

unsigned int vcop_filter_uchar_char_uchar_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_filter_uchar_char_uchar_init(
   __vptr_uint8 in,
   __vptr_int8 coef,
   __vptr_uint8 res,
   int w_input,
   int w_coeff,
   int h_coeff,
   int w_compute,
   int h_compute,
   int dnsmpl_vert,
   int dnsmpl_horz,
   int rnd_shift,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   const int preg_ref1 = _PREG(7);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), (h_compute/dnsmpl_vert)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (w_compute/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (h_coeff)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (w_coeff)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_SYMM,preg_ref1,RM_ROUND,rnd_shift));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 255);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)in);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)res);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(13), ((w_compute*dnsmpl_horz)*sizeof(*res)) -((8u*sizeof(*res)))*((w_compute/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(14), (w_coeff*sizeof(*coef)) -(sizeof(*coef))*((w_coeff)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(15),  -(w_coeff*sizeof(*coef))*((h_coeff)-1u) -(sizeof(*coef))*((w_coeff)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(16), (w_input*sizeof(*in)) -(sizeof(*in))*((w_coeff)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(17), ((8u*sizeof(*in))) -(w_input*sizeof(*in))*((h_coeff)-1u) -(sizeof(*in))*((w_coeff)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(18), (dnsmpl_vert*w_input*sizeof(*in)) -((8u*sizeof(*in)))*((w_compute/(8u))-1u) -(w_input*sizeof(*in))*((h_coeff)-1u) -(sizeof(*in))*((w_coeff)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)coef);
   __offset += 22;

   return 22u;
}

void vcop_filter_uchar_char_uchar_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("v_coef", 16);
   #pragma VCC_VREG("v_out", 17);
   #pragma VCC_VREG("v_x", 18);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("outAddr", "A0");
   #pragma EVE_REG("coefAddr", "A1");
   #pragma EVE_REG("dataAddr", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I1");
   #pragma EVE_REG("I2", "I2");
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 9u, 11u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i34_zero(), _PREG(20), _VREG(17));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(12), _PREG(13));
   __vcop_vagen(_AGEN(1), _PREG(1), _PREG(14), _PREG(15), _PREG(15));
   __vcop_vagen(_AGEN(2), _PREG(1), _PREG(16), _PREG(17), _PREG(18));
   __vcop_vload(__vcop_sizeB(), __vcop_1pt(), _PREG(22), _AGEN(1), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(8), _AGEN(2), _VREG(18), __vcop_alws());
   __vcop_vmadd(_VREG(18), _VREG(16), _VREG(17), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_last_i34(), _VREG(17), _PREG(10), _AGEN(0), _PREG(6));
   __vcop_vloop_end(1u);

}

void vcop_filter_uchar_char_uchar(
   __vptr_uint8 in,
   __vptr_int8 coef,
   __vptr_uint8 res,
   int w_input,
   int w_coeff,
   int h_coeff,
   int w_compute,
   int h_compute,
   int dnsmpl_vert,
   int dnsmpl_horz,
   int rnd_shift)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_filter_uchar_char_uchar_init(in, coef, res, w_input, w_coeff, h_coeff, w_compute, h_compute, dnsmpl_vert, dnsmpl_horz, rnd_shift, __pblock_vcop_filter_uchar_char_uchar);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_filter_uchar_char_uchar_vloops(__pblock_vcop_filter_uchar_char_uchar);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_filter_uchar_char_uchar_custom(
   __vptr_uint8 in,
   __vptr_int8 coef,
   __vptr_uint8 res,
   int w_input,
   int w_coeff,
   int h_coeff,
   int w_compute,
   int h_compute,
   int dnsmpl_vert,
   int dnsmpl_horz,
   int rnd_shift,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_filter_uchar_char_uchar_init(in, coef, res, w_input, w_coeff, h_coeff, w_compute, h_compute, dnsmpl_vert, dnsmpl_horz, rnd_shift, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_filter_uchar_char_uchar_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_filter_uchar_char_char, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_filter_uchar_char_char, __ALIGNOF__(int));
unsigned short __pblock_vcop_filter_uchar_char_char[22];

unsigned int vcop_filter_uchar_char_char_param_count(void)
{
   return 22u;
}

unsigned int vcop_filter_uchar_char_char_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_filter_uchar_char_char_init(
   __vptr_uint8 in,
   __vptr_int8 coef,
   __vptr_int8 res,
   int w_input,
   int w_coeff,
   int h_coeff,
   int w_compute,
   int h_compute,
   int dnsmpl_vert,
   int dnsmpl_horz,
   int rnd_shift,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   const int preg_ref2 = _PREG(7);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), (h_compute/dnsmpl_vert)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (w_compute/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (h_coeff)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (w_coeff)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_ASYMM,preg_ref2,RM_ROUND,rnd_shift));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 127);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)in);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)res);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(13), (w_compute*sizeof(*res)) -((8u*sizeof(*res)))*((w_compute/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(14), (w_coeff*sizeof(*coef)) -(sizeof(*coef))*((w_coeff)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(15),  -(w_coeff*sizeof(*coef))*((h_coeff)-1u) -(sizeof(*coef))*((w_coeff)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(16), (w_input*sizeof(*in)) -(sizeof(*in))*((w_coeff)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(17), ((8u*sizeof(*in))) -(w_input*sizeof(*in))*((h_coeff)-1u) -(sizeof(*in))*((w_coeff)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(18), (dnsmpl_vert*w_input*sizeof(*in)) -((8u*sizeof(*in)))*((w_compute/(8u))-1u) -(w_input*sizeof(*in))*((h_coeff)-1u) -(sizeof(*in))*((w_coeff)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)coef);
   __offset += 22;

   return 22u;
}

void vcop_filter_uchar_char_char_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("v_coef", 16);
   #pragma VCC_VREG("v_out", 17);
   #pragma VCC_VREG("v_x", 18);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("outAddr", "A0");
   #pragma EVE_REG("coefAddr", "A1");
   #pragma EVE_REG("dataAddr", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I1");
   #pragma EVE_REG("I2", "I2");
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 9u, 11u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i34_zero(), _PREG(20), _VREG(17));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(12), _PREG(13));
   __vcop_vagen(_AGEN(1), _PREG(1), _PREG(14), _PREG(15), _PREG(15));
   __vcop_vagen(_AGEN(2), _PREG(1), _PREG(16), _PREG(17), _PREG(18));
   __vcop_vload(__vcop_sizeB(), __vcop_1pt(), _PREG(22), _AGEN(1), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(8), _AGEN(2), _VREG(18), __vcop_alws());
   __vcop_vmadd(_VREG(18), _VREG(16), _VREG(17), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeB(), __vcop_npt(), __vcop_last_i34(), _VREG(17), _PREG(10), _AGEN(0), _PREG(6));
   __vcop_vloop_end(1u);

}

void vcop_filter_uchar_char_char(
   __vptr_uint8 in,
   __vptr_int8 coef,
   __vptr_int8 res,
   int w_input,
   int w_coeff,
   int h_coeff,
   int w_compute,
   int h_compute,
   int dnsmpl_vert,
   int dnsmpl_horz,
   int rnd_shift)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_filter_uchar_char_char_init(in, coef, res, w_input, w_coeff, h_coeff, w_compute, h_compute, dnsmpl_vert, dnsmpl_horz, rnd_shift, __pblock_vcop_filter_uchar_char_char);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_filter_uchar_char_char_vloops(__pblock_vcop_filter_uchar_char_char);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_filter_uchar_char_char_custom(
   __vptr_uint8 in,
   __vptr_int8 coef,
   __vptr_int8 res,
   int w_input,
   int w_coeff,
   int h_coeff,
   int w_compute,
   int h_compute,
   int dnsmpl_vert,
   int dnsmpl_horz,
   int rnd_shift,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_filter_uchar_char_char_init(in, coef, res, w_input, w_coeff, h_coeff, w_compute, h_compute, dnsmpl_vert, dnsmpl_horz, rnd_shift, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_filter_uchar_char_char_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_filter_uchar_char_short, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_filter_uchar_char_short, __ALIGNOF__(int));
unsigned short __pblock_vcop_filter_uchar_char_short[22];

unsigned int vcop_filter_uchar_char_short_param_count(void)
{
   return 22u;
}

unsigned int vcop_filter_uchar_char_short_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_filter_uchar_char_short_init(
   __vptr_uint8 in,
   __vptr_int8 coef,
   __vptr_int16 res,
   int w_input,
   int w_coeff,
   int h_coeff,
   int w_compute,
   int h_compute,
   int dnsmpl_vert,
   int dnsmpl_horz,
   int rnd_shift,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   const int preg_ref3 = _PREG(7);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), (h_compute/dnsmpl_vert)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (w_compute/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (h_coeff)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (w_coeff)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_ASYMM,preg_ref3,RM_ROUND,rnd_shift));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32767);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)in);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)res);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(13), ((w_compute*dnsmpl_horz)*sizeof(*res)) -((8u*sizeof(*res)))*((w_compute/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(14), (w_coeff*sizeof(*coef)) -(sizeof(*coef))*((w_coeff)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(15),  -(w_coeff*sizeof(*coef))*((h_coeff)-1u) -(sizeof(*coef))*((w_coeff)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(16), (w_input*sizeof(*in)) -(sizeof(*in))*((w_coeff)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(17), ((8u*sizeof(*in))) -(w_input*sizeof(*in))*((h_coeff)-1u) -(sizeof(*in))*((w_coeff)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(18), (dnsmpl_vert*w_input*sizeof(*in)) -((8u*sizeof(*in)))*((w_compute/(8u))-1u) -(w_input*sizeof(*in))*((h_coeff)-1u) -(sizeof(*in))*((w_coeff)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)coef);
   __offset += 22;

   return 22u;
}

void vcop_filter_uchar_char_short_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("v_coef", 16);
   #pragma VCC_VREG("v_out", 17);
   #pragma VCC_VREG("v_x", 18);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("outAddr", "A0");
   #pragma EVE_REG("coefAddr", "A1");
   #pragma EVE_REG("dataAddr", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I1");
   #pragma EVE_REG("I2", "I2");
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 9u, 11u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i34_zero(), _PREG(20), _VREG(17));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(12), _PREG(13));
   __vcop_vagen(_AGEN(1), _PREG(1), _PREG(14), _PREG(15), _PREG(15));
   __vcop_vagen(_AGEN(2), _PREG(1), _PREG(16), _PREG(17), _PREG(18));
   __vcop_vload(__vcop_sizeB(), __vcop_1pt(), _PREG(22), _AGEN(1), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(8), _AGEN(2), _VREG(18), __vcop_alws());
   __vcop_vmadd(_VREG(18), _VREG(16), _VREG(17), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_npt(), __vcop_last_i34(), _VREG(17), _PREG(10), _AGEN(0), _PREG(6));
   __vcop_vloop_end(1u);

}

void vcop_filter_uchar_char_short(
   __vptr_uint8 in,
   __vptr_int8 coef,
   __vptr_int16 res,
   int w_input,
   int w_coeff,
   int h_coeff,
   int w_compute,
   int h_compute,
   int dnsmpl_vert,
   int dnsmpl_horz,
   int rnd_shift)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_filter_uchar_char_short_init(in, coef, res, w_input, w_coeff, h_coeff, w_compute, h_compute, dnsmpl_vert, dnsmpl_horz, rnd_shift, __pblock_vcop_filter_uchar_char_short);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_filter_uchar_char_short_vloops(__pblock_vcop_filter_uchar_char_short);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_filter_uchar_char_short_custom(
   __vptr_uint8 in,
   __vptr_int8 coef,
   __vptr_int16 res,
   int w_input,
   int w_coeff,
   int h_coeff,
   int w_compute,
   int h_compute,
   int dnsmpl_vert,
   int dnsmpl_horz,
   int rnd_shift,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_filter_uchar_char_short_init(in, coef, res, w_input, w_coeff, h_coeff, w_compute, h_compute, dnsmpl_vert, dnsmpl_horz, rnd_shift, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_filter_uchar_char_short_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_filter_ushort_short_short, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_filter_ushort_short_short, __ALIGNOF__(int));
unsigned short __pblock_vcop_filter_ushort_short_short[22];

unsigned int vcop_filter_ushort_short_short_param_count(void)
{
   return 22u;
}

unsigned int vcop_filter_ushort_short_short_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_filter_ushort_short_short_init(
   __vptr_uint16 in,
   __vptr_int16 coef,
   __vptr_int16 res,
   int w_input,
   int w_coeff,
   int h_coeff,
   int w_compute,
   int h_compute,
   int dnsmpl_vert,
   int dnsmpl_horz,
   int rnd_shift,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   const int preg_ref4 = _PREG(7);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), (h_compute/dnsmpl_vert)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (w_compute/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (h_coeff)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (w_coeff)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_ASYMM,preg_ref4,RM_ROUND,rnd_shift));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32767);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)in);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)res);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(13), ((w_compute*dnsmpl_horz)*sizeof(*res)) -((8u*sizeof(*res)))*((w_compute/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(14), 2);
   __vcop_pblock_init16(pblock, __offset+_PREG(15), (w_coeff*sizeof(*coef)) -(sizeof(*coef))*((w_coeff)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(16),  -(w_coeff*sizeof(*coef))*((h_coeff)-1u) -(sizeof(*coef))*((w_coeff)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(17), (w_input*sizeof(*in)) -(sizeof(*in))*((w_coeff)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(18), ((8u*sizeof(*in))) -(w_input*sizeof(*in))*((h_coeff)-1u) -(sizeof(*in))*((w_coeff)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(19), (dnsmpl_vert*w_input*sizeof(*in)) -((8u*sizeof(*in)))*((w_compute/(8u))-1u) -(w_input*sizeof(*in))*((h_coeff)-1u) -(sizeof(*in))*((w_coeff)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)coef);
   __offset += 22;

   return 22u;
}

void vcop_filter_ushort_short_short_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("v_coef", 16);
   #pragma VCC_VREG("v_out", 17);
   #pragma VCC_VREG("v_x", 18);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("outAddr", "A0");
   #pragma EVE_REG("coefAddr", "A1");
   #pragma EVE_REG("dataAddr", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I1");
   #pragma EVE_REG("I2", "I2");
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 9u, 11u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i34_zero(), _PREG(20), _VREG(17));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(12), _PREG(13));
   __vcop_vagen(_AGEN(1), _PREG(14), _PREG(15), _PREG(16), _PREG(16));
   __vcop_vagen(_AGEN(2), _PREG(14), _PREG(17), _PREG(18), _PREG(19));
   __vcop_vload(__vcop_sizeH(), __vcop_1pt(), _PREG(22), _AGEN(1), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(8), _AGEN(2), _VREG(18), __vcop_alws());
   __vcop_vmadd(_VREG(18), _VREG(16), _VREG(17), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_npt(), __vcop_last_i34(), _VREG(17), _PREG(10), _AGEN(0), _PREG(6));
   __vcop_vloop_end(1u);

}

void vcop_filter_ushort_short_short(
   __vptr_uint16 in,
   __vptr_int16 coef,
   __vptr_int16 res,
   int w_input,
   int w_coeff,
   int h_coeff,
   int w_compute,
   int h_compute,
   int dnsmpl_vert,
   int dnsmpl_horz,
   int rnd_shift)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_filter_ushort_short_short_init(in, coef, res, w_input, w_coeff, h_coeff, w_compute, h_compute, dnsmpl_vert, dnsmpl_horz, rnd_shift, __pblock_vcop_filter_ushort_short_short);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_filter_ushort_short_short_vloops(__pblock_vcop_filter_ushort_short_short);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_filter_ushort_short_short_custom(
   __vptr_uint16 in,
   __vptr_int16 coef,
   __vptr_int16 res,
   int w_input,
   int w_coeff,
   int h_coeff,
   int w_compute,
   int h_compute,
   int dnsmpl_vert,
   int dnsmpl_horz,
   int rnd_shift,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_filter_ushort_short_short_init(in, coef, res, w_input, w_coeff, h_coeff, w_compute, h_compute, dnsmpl_vert, dnsmpl_horz, rnd_shift, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_filter_ushort_short_short_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_filter_short_short_short, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_filter_short_short_short, __ALIGNOF__(int));
unsigned short __pblock_vcop_filter_short_short_short[22];

unsigned int vcop_filter_short_short_short_param_count(void)
{
   return 22u;
}

unsigned int vcop_filter_short_short_short_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_filter_short_short_short_init(
   __vptr_int16 in,
   __vptr_int16 coef,
   __vptr_int16 res,
   int w_input,
   int w_coeff,
   int h_coeff,
   int w_compute,
   int h_compute,
   int dnsmpl_vert,
   int dnsmpl_horz,
   int rnd_shift,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   const int preg_ref5 = _PREG(7);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), (h_compute/dnsmpl_vert)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (w_compute/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (h_coeff)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (w_coeff)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_ASYMM,preg_ref5,RM_ROUND,rnd_shift));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32767);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)in);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)res);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(13), ((w_compute*dnsmpl_horz)*sizeof(*res)) -((8u*sizeof(*res)))*((w_compute/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(14), 2);
   __vcop_pblock_init16(pblock, __offset+_PREG(15), (w_coeff*sizeof(*coef)) -(sizeof(*coef))*((w_coeff)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(16),  -(w_coeff*sizeof(*coef))*((h_coeff)-1u) -(sizeof(*coef))*((w_coeff)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(17), (w_input*sizeof(*in)) -(sizeof(*in))*((w_coeff)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(18), ((8u*sizeof(*in))) -(w_input*sizeof(*in))*((h_coeff)-1u) -(sizeof(*in))*((w_coeff)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(19), (dnsmpl_vert*w_input*sizeof(*in)) -((8u*sizeof(*in)))*((w_compute/(8u))-1u) -(w_input*sizeof(*in))*((h_coeff)-1u) -(sizeof(*in))*((w_coeff)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)coef);
   __offset += 22;

   return 22u;
}

void vcop_filter_short_short_short_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("v_coef", 16);
   #pragma VCC_VREG("v_out", 17);
   #pragma VCC_VREG("v_x", 18);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("outAddr", "A0");
   #pragma EVE_REG("coefAddr", "A1");
   #pragma EVE_REG("dataAddr", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I1");
   #pragma EVE_REG("I2", "I2");
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 9u, 11u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i34_zero(), _PREG(20), _VREG(17));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(12), _PREG(13));
   __vcop_vagen(_AGEN(1), _PREG(14), _PREG(15), _PREG(16), _PREG(16));
   __vcop_vagen(_AGEN(2), _PREG(14), _PREG(17), _PREG(18), _PREG(19));
   __vcop_vload(__vcop_sizeH(), __vcop_1pt(), _PREG(22), _AGEN(1), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(8), _AGEN(2), _VREG(18), __vcop_alws());
   __vcop_vmadd(_VREG(18), _VREG(16), _VREG(17), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_npt(), __vcop_last_i34(), _VREG(17), _PREG(10), _AGEN(0), _PREG(6));
   __vcop_vloop_end(1u);

}

void vcop_filter_short_short_short(
   __vptr_int16 in,
   __vptr_int16 coef,
   __vptr_int16 res,
   int w_input,
   int w_coeff,
   int h_coeff,
   int w_compute,
   int h_compute,
   int dnsmpl_vert,
   int dnsmpl_horz,
   int rnd_shift)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_filter_short_short_short_init(in, coef, res, w_input, w_coeff, h_coeff, w_compute, h_compute, dnsmpl_vert, dnsmpl_horz, rnd_shift, __pblock_vcop_filter_short_short_short);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_filter_short_short_short_vloops(__pblock_vcop_filter_short_short_short);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_filter_short_short_short_custom(
   __vptr_int16 in,
   __vptr_int16 coef,
   __vptr_int16 res,
   int w_input,
   int w_coeff,
   int h_coeff,
   int w_compute,
   int h_compute,
   int dnsmpl_vert,
   int dnsmpl_horz,
   int rnd_shift,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_filter_short_short_short_init(in, coef, res, w_input, w_coeff, h_coeff, w_compute, h_compute, dnsmpl_vert, dnsmpl_horz, rnd_shift, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_filter_short_short_short_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_filter_ushort_ushort_short, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_filter_ushort_ushort_short, __ALIGNOF__(int));
unsigned short __pblock_vcop_filter_ushort_ushort_short[22];

unsigned int vcop_filter_ushort_ushort_short_param_count(void)
{
   return 22u;
}

unsigned int vcop_filter_ushort_ushort_short_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_filter_ushort_ushort_short_init(
   __vptr_uint16 in,
   __vptr_uint16 coef,
   __vptr_int16 res,
   int w_input,
   int w_coeff,
   int h_coeff,
   int w_compute,
   int h_compute,
   int dnsmpl_vert,
   int dnsmpl_horz,
   int rnd_shift,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   const int preg_ref6 = _PREG(7);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), (h_compute/dnsmpl_vert)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (w_compute/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (h_coeff)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (w_coeff)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_ASYMM,preg_ref6,RM_ROUND,rnd_shift));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32767);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)in);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)res);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(13), ((w_compute*dnsmpl_horz)*sizeof(*res)) -((8u*sizeof(*res)))*((w_compute/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(14), 2);
   __vcop_pblock_init16(pblock, __offset+_PREG(15), (w_coeff*sizeof(*coef)) -(sizeof(*coef))*((w_coeff)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(16),  -(w_coeff*sizeof(*coef))*((h_coeff)-1u) -(sizeof(*coef))*((w_coeff)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(17), (w_input*sizeof(*in)) -(sizeof(*in))*((w_coeff)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(18), ((8u*sizeof(*in))) -(w_input*sizeof(*in))*((h_coeff)-1u) -(sizeof(*in))*((w_coeff)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(19), (dnsmpl_vert*w_input*sizeof(*in)) -((8u*sizeof(*in)))*((w_compute/(8u))-1u) -(w_input*sizeof(*in))*((h_coeff)-1u) -(sizeof(*in))*((w_coeff)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)coef);
   __offset += 22;

   return 22u;
}

void vcop_filter_ushort_ushort_short_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("v_coef", 16);
   #pragma VCC_VREG("v_out", 17);
   #pragma VCC_VREG("v_x", 18);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("outAddr", "A0");
   #pragma EVE_REG("coefAddr", "A1");
   #pragma EVE_REG("dataAddr", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I1");
   #pragma EVE_REG("I2", "I2");
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 9u, 11u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i34_zero(), _PREG(20), _VREG(17));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(12), _PREG(13));
   __vcop_vagen(_AGEN(1), _PREG(14), _PREG(15), _PREG(16), _PREG(16));
   __vcop_vagen(_AGEN(2), _PREG(14), _PREG(17), _PREG(18), _PREG(19));
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(22), _AGEN(1), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(8), _AGEN(2), _VREG(18), __vcop_alws());
   __vcop_vmadd(_VREG(18), _VREG(16), _VREG(17), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_npt(), __vcop_last_i34(), _VREG(17), _PREG(10), _AGEN(0), _PREG(6));
   __vcop_vloop_end(1u);

}

void vcop_filter_ushort_ushort_short(
   __vptr_uint16 in,
   __vptr_uint16 coef,
   __vptr_int16 res,
   int w_input,
   int w_coeff,
   int h_coeff,
   int w_compute,
   int h_compute,
   int dnsmpl_vert,
   int dnsmpl_horz,
   int rnd_shift)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_filter_ushort_ushort_short_init(in, coef, res, w_input, w_coeff, h_coeff, w_compute, h_compute, dnsmpl_vert, dnsmpl_horz, rnd_shift, __pblock_vcop_filter_ushort_ushort_short);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_filter_ushort_ushort_short_vloops(__pblock_vcop_filter_ushort_ushort_short);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_filter_ushort_ushort_short_custom(
   __vptr_uint16 in,
   __vptr_uint16 coef,
   __vptr_int16 res,
   int w_input,
   int w_coeff,
   int h_coeff,
   int w_compute,
   int h_compute,
   int dnsmpl_vert,
   int dnsmpl_horz,
   int rnd_shift,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_filter_ushort_ushort_short_init(in, coef, res, w_input, w_coeff, h_coeff, w_compute, h_compute, dnsmpl_vert, dnsmpl_horz, rnd_shift, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_filter_ushort_ushort_short_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_filter_ushort_short_int, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_filter_ushort_short_int, __ALIGNOF__(int));
unsigned short __pblock_vcop_filter_ushort_short_int[22];

unsigned int vcop_filter_ushort_short_int_param_count(void)
{
   return 22u;
}

unsigned int vcop_filter_ushort_short_int_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_filter_ushort_short_int_init(
   __vptr_uint16 in,
   __vptr_int16 coef,
   __vptr_int32 res,
   int w_input,
   int w_coeff,
   int h_coeff,
   int w_compute,
   int h_compute,
   int dnsmpl_vert,
   int dnsmpl_horz,
   int rnd_shift,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), (h_compute/dnsmpl_vert)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (w_compute/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (h_coeff)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (w_coeff)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_ROUND,rnd_shift));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)in);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)res);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), ((w_compute*dnsmpl_horz)*sizeof(*res)) -((8u*sizeof(*res)))*((w_compute/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(13), 2);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), (w_coeff*sizeof(*coef)) -(sizeof(*coef))*((w_coeff)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(15),  -(w_coeff*sizeof(*coef))*((h_coeff)-1u) -(sizeof(*coef))*((w_coeff)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(16), (w_input*sizeof(*in)) -(sizeof(*in))*((w_coeff)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(17), ((8u*sizeof(*in))) -(w_input*sizeof(*in))*((h_coeff)-1u) -(sizeof(*in))*((w_coeff)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(18), (dnsmpl_vert*w_input*sizeof(*in)) -((8u*sizeof(*in)))*((w_compute/(8u))-1u) -(w_input*sizeof(*in))*((h_coeff)-1u) -(sizeof(*in))*((w_coeff)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)coef);
   __offset += 22;

   return 22u;
}

void vcop_filter_ushort_short_int_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("v_coef", 16);
   #pragma VCC_VREG("v_out", 17);
   #pragma VCC_VREG("v_x", 18);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("outAddr", "A0");
   #pragma EVE_REG("coefAddr", "A1");
   #pragma EVE_REG("dataAddr", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I1");
   #pragma EVE_REG("I2", "I2");
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 9u, 11u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i34_zero(), _PREG(20), _VREG(17));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(7), _PREG(12));
   __vcop_vagen(_AGEN(1), _PREG(13), _PREG(14), _PREG(15), _PREG(15));
   __vcop_vagen(_AGEN(2), _PREG(13), _PREG(16), _PREG(17), _PREG(18));
   __vcop_vload(__vcop_sizeH(), __vcop_1pt(), _PREG(22), _AGEN(1), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(8), _AGEN(2), _VREG(18), __vcop_alws());
   __vcop_vmadd(_VREG(18), _VREG(16), _VREG(17), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_last_i34(), _VREG(17), _PREG(10), _AGEN(0), _PREG(6));
   __vcop_vloop_end(1u);

}

void vcop_filter_ushort_short_int(
   __vptr_uint16 in,
   __vptr_int16 coef,
   __vptr_int32 res,
   int w_input,
   int w_coeff,
   int h_coeff,
   int w_compute,
   int h_compute,
   int dnsmpl_vert,
   int dnsmpl_horz,
   int rnd_shift)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_filter_ushort_short_int_init(in, coef, res, w_input, w_coeff, h_coeff, w_compute, h_compute, dnsmpl_vert, dnsmpl_horz, rnd_shift, __pblock_vcop_filter_ushort_short_int);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_filter_ushort_short_int_vloops(__pblock_vcop_filter_ushort_short_int);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_filter_ushort_short_int_custom(
   __vptr_uint16 in,
   __vptr_int16 coef,
   __vptr_int32 res,
   int w_input,
   int w_coeff,
   int h_coeff,
   int w_compute,
   int h_compute,
   int dnsmpl_vert,
   int dnsmpl_horz,
   int rnd_shift,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_filter_ushort_short_int_init(in, coef, res, w_input, w_coeff, h_coeff, w_compute, h_compute, dnsmpl_vert, dnsmpl_horz, rnd_shift, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_filter_ushort_short_int_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

