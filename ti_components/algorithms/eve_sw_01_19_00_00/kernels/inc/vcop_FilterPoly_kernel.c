#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_FilterPoly_ushort_short_ushort, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_FilterPoly_ushort_short_ushort, __ALIGNOF__(int));
unsigned short __pblock_vcop_FilterPoly_ushort_short_ushort[38];

unsigned int vcop_FilterPoly_ushort_short_ushort_param_count(void)
{
   return 38u;
}

unsigned int vcop_FilterPoly_ushort_short_ushort_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_FilterPoly_ushort_short_ushort_init(
   __vptr_uint16 in,
   __vptr_int16 f_coef,
   __vptr_uint8 smpl_flag,
   __vptr_uint16 inter_out,
   __vptr_uint8 out,
   int w_input,
   int ntaps,
   int w_compute,
   int h_compute,
   int w_out,
   int h_out,
   int D,
   int U,
   int loop_end,
   int rnd_shift,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   const int preg_ref1 = _PREG(7);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), (w_compute/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (h_compute)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (loop_end)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (ntaps)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_SYMM,preg_ref1,RM_ROUND,rnd_shift));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 255);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)f_coef);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)in);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)inter_out);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), (loop_end*sizeof(*smpl_flag)) -(sizeof(*smpl_flag))*((loop_end)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(15),  -(loop_end*sizeof(*smpl_flag))*((h_compute)-1u) -(sizeof(*smpl_flag))*((loop_end)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(16), (U*sizeof(*f_coef)));
   __vcop_pblock_init16(pblock, __offset+_PREG(17), (D*sizeof(*f_coef)) -(U*sizeof(*f_coef))*((ntaps)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(18),  -(D*sizeof(*f_coef))*((loop_end)-1u) -(U*sizeof(*f_coef))*((ntaps)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(19), (w_input*sizeof(*in)));
   __vcop_pblock_init16(pblock, __offset+_PREG(20),  -(w_input*sizeof(*in))*((ntaps)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(21), (w_input*sizeof(*in)) -(w_input*sizeof(*in))*((ntaps)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(22), (8u*sizeof(*in)) -(w_input*sizeof(*in))*((h_compute)-1u) -(w_input*sizeof(*in))*((ntaps)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)smpl_flag);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), 0);
   __offset += 26;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (h_out)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (w_compute/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), (h_out*8u*sizeof(*inter_out)));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), (8u*sizeof(*inter_out)) -(h_out*8u*sizeof(*inter_out))*((w_compute/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(8), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(9), (w_compute*sizeof(*out)) -(8u*sizeof(*out))*((w_compute/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)inter_out);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)out);
   __offset += 12;

   return 38u;
}

void vcop_FilterPoly_ushort_short_ushort_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vcoef", 16);
   #pragma VCC_VREG("Vflg", 17);
   #pragma VCC_VREG("Vin", 18);
   #pragma VCC_VREG("Vout", 19);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("FlagAddr", "A0");
   #pragma EVE_REG("CoefAddr", "A1");
   #pragma EVE_REG("InAddr", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I1");
   #pragma EVE_REG("I2", "I2");
   #pragma EVE_REG("I3", "I3");
   #pragma EVE_REG("I4", "I4");
   

   __vcop_vloop(__vcop_compute(), 10u, 13u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(26), _VREG(19));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(1), _PREG(14), _PREG(15));
   __vcop_vagen(_AGEN(1), _PREG(16), _PREG(17), _PREG(18), _PREG(18));
   __vcop_vagen(_AGEN(2), _PREG(19), _PREG(20), _PREG(21), _PREG(22));
   __vcop_vload(__vcop_sizeBU(), __vcop_1pt(), _PREG(24), _AGEN(0), _VREG(17), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeH(), __vcop_1pt(), _PREG(8), _AGEN(1), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(10), _AGEN(2), _VREG(18), __vcop_alws());
   __vcop_vmadd(_VREG(18), _VREG(16), _VREG(19), _PREG(0));
   __vcop_vstore(__vcop_predicate(_VREG(17)), __vcop_sizeHU(), __vcop_collat(), __vcop_last_i4(), _VREG(19), _PREG(12), _AGEN(0), _PREG(6));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("inAddr", "A0");
   #pragma EVE_REG("outAddr", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 5u, 6u, 2u);
   __vcop_vagen(_AGEN(0), _PREG(6), _PREG(7), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(8), _PREG(9), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(10), _AGEN(0), _VREG(18), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(18), _PREG(12), _AGEN(1), _PREG(0));
   __vcop_vloop_end(2u);

}

void vcop_FilterPoly_ushort_short_ushort(
   __vptr_uint16 in,
   __vptr_int16 f_coef,
   __vptr_uint8 smpl_flag,
   __vptr_uint16 inter_out,
   __vptr_uint8 out,
   int w_input,
   int ntaps,
   int w_compute,
   int h_compute,
   int w_out,
   int h_out,
   int D,
   int U,
   int loop_end,
   int rnd_shift)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_FilterPoly_ushort_short_ushort_init(in, f_coef, smpl_flag, inter_out, out, w_input, ntaps, w_compute, h_compute, w_out, h_out, D, U, loop_end, rnd_shift, __pblock_vcop_FilterPoly_ushort_short_ushort);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_FilterPoly_ushort_short_ushort_vloops(__pblock_vcop_FilterPoly_ushort_short_ushort);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_FilterPoly_ushort_short_ushort_custom(
   __vptr_uint16 in,
   __vptr_int16 f_coef,
   __vptr_uint8 smpl_flag,
   __vptr_uint16 inter_out,
   __vptr_uint8 out,
   int w_input,
   int ntaps,
   int w_compute,
   int h_compute,
   int w_out,
   int h_out,
   int D,
   int U,
   int loop_end,
   int rnd_shift,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_FilterPoly_ushort_short_ushort_init(in, f_coef, smpl_flag, inter_out, out, w_input, ntaps, w_compute, h_compute, w_out, h_out, D, U, loop_end, rnd_shift, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_FilterPoly_ushort_short_ushort_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

