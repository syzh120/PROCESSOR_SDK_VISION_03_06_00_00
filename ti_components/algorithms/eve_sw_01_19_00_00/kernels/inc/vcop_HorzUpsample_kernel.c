#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_HorzUpsample_ushort_short_ushort, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_HorzUpsample_ushort_short_ushort, __ALIGNOF__(int));
unsigned short __pblock_vcop_HorzUpsample_ushort_short_ushort[22];

unsigned int vcop_HorzUpsample_ushort_short_ushort_param_count(void)
{
   return 22u;
}

unsigned int vcop_HorzUpsample_ushort_short_ushort_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_HorzUpsample_ushort_short_ushort_init(
   __vptr_uint16 in,
   __vptr_int16 f_coef,
   __vptr_uint16 out,
   int w_input,
   int ntaps,
   int w_compute,
   int h_compute,
   int w_out,
   int U,
   int type_output,
   int rnd_shift,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   const int preg_ref1 = _PREG(7);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (h_compute)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (w_compute)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (ntaps)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_SYMM,preg_ref1,RM_ROUND,rnd_shift));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 255);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)in);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)out);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), (U*sizeof(*out)));
   __vcop_pblock_init16(pblock, __offset+_PREG(13), (w_out*sizeof(*out)) -(U*sizeof(*out))*((w_compute)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(14), (U*sizeof(*f_coef)));
   __vcop_pblock_init16(pblock, __offset+_PREG(15),  -(U*sizeof(*f_coef))*((ntaps)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(16), 2);
   __vcop_pblock_init16(pblock, __offset+_PREG(17), (sizeof(*in)) -(sizeof(*in))*((ntaps)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(18), (w_input*sizeof(*in)) -(sizeof(*in))*((w_compute)-1u) -(sizeof(*in))*((ntaps)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)f_coef);
   __offset += 22;

   return 22u;
}

void vcop_HorzUpsample_ushort_short_ushort_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vcoef", 16);
   #pragma VCC_VREG("Vin", 17);
   #pragma VCC_VREG("Vout", 18);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("OutAddr", "A0");
   #pragma EVE_REG("CoefAddr", "A1");
   #pragma EVE_REG("InAddr", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I2");
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 9u, 11u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(20), _VREG(18));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(12), _PREG(13), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(14), _PREG(15), _PREG(15), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(16), _PREG(17), _PREG(18), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(22), _AGEN(1), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(8), _AGEN(2), _VREG(17), __vcop_alws());
   __vcop_vmadd(_VREG(17), _VREG(16), _VREG(18), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_last_i4(), _VREG(18), _PREG(10), _AGEN(0), _PREG(6));
   __vcop_vloop_end(1u);

}

void vcop_HorzUpsample_ushort_short_ushort(
   __vptr_uint16 in,
   __vptr_int16 f_coef,
   __vptr_uint16 out,
   int w_input,
   int ntaps,
   int w_compute,
   int h_compute,
   int w_out,
   int U,
   int type_output,
   int rnd_shift)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_HorzUpsample_ushort_short_ushort_init(in, f_coef, out, w_input, ntaps, w_compute, h_compute, w_out, U, type_output, rnd_shift, __pblock_vcop_HorzUpsample_ushort_short_ushort);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_HorzUpsample_ushort_short_ushort_vloops(__pblock_vcop_HorzUpsample_ushort_short_ushort);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_HorzUpsample_ushort_short_ushort_custom(
   __vptr_uint16 in,
   __vptr_int16 f_coef,
   __vptr_uint16 out,
   int w_input,
   int ntaps,
   int w_compute,
   int h_compute,
   int w_out,
   int U,
   int type_output,
   int rnd_shift,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_HorzUpsample_ushort_short_ushort_init(in, f_coef, out, w_input, ntaps, w_compute, h_compute, w_out, U, type_output, rnd_shift, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_HorzUpsample_ushort_short_ushort_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

