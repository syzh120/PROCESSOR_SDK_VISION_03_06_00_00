#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_dct8x8_OddEven_col_int_int, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_dct8x8_OddEven_col_int_int, __ALIGNOF__(int));
unsigned short __pblock_vcop_dct8x8_OddEven_col_int_int[56];

unsigned int vcop_dct8x8_OddEven_col_int_int_param_count(void)
{
   return 56u;
}

unsigned int vcop_dct8x8_OddEven_col_int_int_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_dct8x8_OddEven_col_int_int_init(
   __vptr_int16 in,
   __vptr_int16 f_ignore,
   __vptr_int16 out,
   int w_input,
   int h_input,
   int w_out,
   int h_out,
   int HBLKS,
   int VBLKS,
   int type_input,
   int type_coeff,
   int type_output,
   int rnd_shift,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   const int preg_ref1 = _PREG(7);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (VBLKS)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (HBLKS)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_ASYMM,preg_ref1,RM_ROUND,rnd_shift));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32767);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)in+2*w_input*sizeof(*in));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)in+3*w_input*sizeof(*in));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)in+4*w_input*sizeof(*in));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)in+5*w_input*sizeof(*in));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)in+6*w_input*sizeof(*in));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)in+7*w_input*sizeof(*in));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), 23173);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), 30271);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), 12537);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), 32138);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), 27243);
   __vcop_pblock_init32(pblock, __offset+_PREG(30), 18205);
   __vcop_pblock_init32(pblock, __offset+_PREG(32), 6389);
   __vcop_pblock_init32(pblock, __offset+_PREG(34), (uchar *)out+0*sizeof(*out));
   __vcop_pblock_init32(pblock, __offset+_PREG(36), (uchar *)out+1*sizeof(*out));
   __vcop_pblock_init32(pblock, __offset+_PREG(38), (uchar *)out+2*sizeof(*out));
   __vcop_pblock_init32(pblock, __offset+_PREG(40), (uchar *)out+3*sizeof(*out));
   __vcop_pblock_init32(pblock, __offset+_PREG(42), (uchar *)out+4*sizeof(*out));
   __vcop_pblock_init32(pblock, __offset+_PREG(44), (uchar *)out+5*sizeof(*out));
   __vcop_pblock_init32(pblock, __offset+_PREG(46), (uchar *)out+6*sizeof(*out));
   __vcop_pblock_init32(pblock, __offset+_PREG(48), (uchar *)out+7*sizeof(*out));
   __vcop_pblock_init16(pblock, __offset+_PREG(50), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(51), (8*w_input*sizeof(*in)) -((8u*sizeof(*in)))*((HBLKS)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(52), 288);
   __vcop_pblock_init16(pblock, __offset+_PREG(53), (8*(w_out+HBLKS)*4) -(8*9*4)*((HBLKS)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(54), (uchar *)in+0*w_input*sizeof(*in));
   __vcop_pblock_init32(pblock, __offset+_PREG(56), (uchar *)in+1*w_input*sizeof(*in));
   __offset += 56;

   return 56u;
}

void vcop_dct8x8_OddEven_col_int_int_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("dataAddr0", "A0");
   #pragma EVE_REG("dataAddr1", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 55u, 28u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(20), _VREG(1));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(22), _VREG(3));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(24), _VREG(5));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(26), _VREG(7));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(28), _VREG(9));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(30), _VREG(11));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(32), _VREG(13));
   __vcop_vagen(_AGEN(0), _PREG(50), _PREG(51), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(52), _PREG(53), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(54), _AGEN(0), _VREG(0), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(56), _AGEN(0), _VREG(2), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(8), _AGEN(0), _VREG(4), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(10), _AGEN(0), _VREG(6), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(12), _AGEN(0), _VREG(8), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(14), _AGEN(0), _VREG(10), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(16), _AGEN(0), _VREG(12), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(18), _AGEN(0), _VREG(14), __vcop_alws());
   __vcop_vaddsub(_VREG(0), _VREG(14));
   __vcop_vaddsub(_VREG(2), _VREG(12));
   __vcop_vaddsub(_VREG(4), _VREG(10));
   __vcop_vaddsub(_VREG(6), _VREG(8));
   __vcop_vaddsub(_VREG(0), _VREG(6));
   __vcop_vaddsub(_VREG(2), _VREG(4));
   __vcop_vaddsub(_VREG(0), _VREG(2));
   __vcop_vmpy(_VREG(1), _VREG(0), _VREG(0), _PREG(0));
   __vcop_vmpy(_VREG(1), _VREG(2), _VREG(2), _PREG(0));
   __vcop_vmpy(_VREG(3), _VREG(6), _VREG(15), _PREG(0));
   __vcop_vmadd(_VREG(5), _VREG(4), _VREG(15), _PREG(0));
   __vcop_vmpy(_VREG(5), _VREG(6), _VREG(6), _PREG(0));
   __vcop_vmsub(_VREG(3), _VREG(4), _VREG(6), _PREG(0));
   __vcop_vmpy(_VREG(7), _VREG(14), _VREG(3), _PREG(0));
   __vcop_vmadd(_VREG(9), _VREG(12), _VREG(3), _PREG(0));
   __vcop_vmadd(_VREG(11), _VREG(10), _VREG(3), _PREG(0));
   __vcop_vmadd(_VREG(13), _VREG(8), _VREG(3), _PREG(0));
   __vcop_vmpy(_VREG(9), _VREG(14), _VREG(5), _PREG(0));
   __vcop_vmsub(_VREG(13), _VREG(12), _VREG(5), _PREG(0));
   __vcop_vmsub(_VREG(7), _VREG(10), _VREG(5), _PREG(0));
   __vcop_vmsub(_VREG(11), _VREG(8), _VREG(5), _PREG(0));
   __vcop_vmpy(_VREG(11), _VREG(14), _VREG(4), _PREG(0));
   __vcop_vmsub(_VREG(7), _VREG(12), _VREG(4), _PREG(0));
   __vcop_vmadd(_VREG(13), _VREG(10), _VREG(4), _PREG(0));
   __vcop_vmadd(_VREG(9), _VREG(8), _VREG(4), _PREG(0));
   __vcop_vmpy(_VREG(13), _VREG(14), _VREG(14), _PREG(0));
   __vcop_vmsub(_VREG(11), _VREG(12), _VREG(14), _PREG(0));
   __vcop_vmadd(_VREG(9), _VREG(10), _VREG(14), _PREG(0));
   __vcop_vmsub(_VREG(7), _VREG(8), _VREG(14), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_offst_np1(), __vcop_alws(), _VREG(0), _PREG(34), _AGEN(1), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_offst_np1(), __vcop_alws(), _VREG(3), _PREG(36), _AGEN(1), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_offst_np1(), __vcop_alws(), _VREG(15), _PREG(38), _AGEN(1), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_offst_np1(), __vcop_alws(), _VREG(5), _PREG(40), _AGEN(1), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_offst_np1(), __vcop_alws(), _VREG(2), _PREG(42), _AGEN(1), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_offst_np1(), __vcop_alws(), _VREG(4), _PREG(44), _AGEN(1), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_offst_np1(), __vcop_alws(), _VREG(6), _PREG(46), _AGEN(1), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_offst_np1(), __vcop_alws(), _VREG(14), _PREG(48), _AGEN(1), _PREG(6));
   __vcop_vloop_end(1u);

}

void vcop_dct8x8_OddEven_col_int_int(
   __vptr_int16 in,
   __vptr_int16 f_ignore,
   __vptr_int16 out,
   int w_input,
   int h_input,
   int w_out,
   int h_out,
   int HBLKS,
   int VBLKS,
   int type_input,
   int type_coeff,
   int type_output,
   int rnd_shift)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_dct8x8_OddEven_col_int_int_init(in, f_ignore, out, w_input, h_input, w_out, h_out, HBLKS, VBLKS, type_input, type_coeff, type_output, rnd_shift, __pblock_vcop_dct8x8_OddEven_col_int_int);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_dct8x8_OddEven_col_int_int_vloops(__pblock_vcop_dct8x8_OddEven_col_int_int);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_dct8x8_OddEven_col_int_int_custom(
   __vptr_int16 in,
   __vptr_int16 f_ignore,
   __vptr_int16 out,
   int w_input,
   int h_input,
   int w_out,
   int h_out,
   int HBLKS,
   int VBLKS,
   int type_input,
   int type_coeff,
   int type_output,
   int rnd_shift,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_dct8x8_OddEven_col_int_int_init(in, f_ignore, out, w_input, h_input, w_out, h_out, HBLKS, VBLKS, type_input, type_coeff, type_output, rnd_shift, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_dct8x8_OddEven_col_int_int_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

