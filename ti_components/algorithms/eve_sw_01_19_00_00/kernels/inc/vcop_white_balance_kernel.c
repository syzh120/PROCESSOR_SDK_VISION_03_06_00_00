#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_white_balance_BGGR, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_white_balance_BGGR, __ALIGNOF__(int));
unsigned short __pblock_vcop_white_balance_BGGR[24];

unsigned int vcop_white_balance_BGGR_param_count(void)
{
   return 24u;
}

unsigned int vcop_white_balance_BGGR_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_white_balance_BGGR_init(
   __vptr_uint16 CFA_short_in,
   __vptr_uint16 CFA_short_out,
   unsigned int blk_w,
   unsigned int blk_h,
   unsigned int gain_factor_R,
   unsigned int gain_factor_Gr,
   unsigned int gain_factor_Gb,
   unsigned int gain_factor_B,
   unsigned int shift_val,
   unsigned int input_stride,
   unsigned int output_stride,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (((blk_h/2) +1))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (((blk_w/((8u) * 2))+1))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_ROUND,shift_val));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), gain_factor_Gr);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), gain_factor_B);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)CFA_short_in);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)CFA_short_in+input_stride*sizeof(*CFA_short_in));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)CFA_short_out);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)CFA_short_out+output_stride*sizeof(*CFA_short_in));
   __vcop_pblock_init16(pblock, __offset+_PREG(20), (2*input_stride*sizeof(*CFA_short_in)) -((sizeof(*CFA_short_in)*(8u*2)))*((((blk_w/((8u) * 2))+1))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(21), (2*output_stride*sizeof(*CFA_short_in)) -((sizeof(*CFA_short_in)*(8u*2)))*((((blk_w/((8u) * 2))+1))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(22), gain_factor_R);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), gain_factor_Gb);
   __offset += 24;

   return 24u;
}

void vcop_white_balance_BGGR_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VB0", 16);
   #pragma VCC_VREG("VB0_copy", 17);
   #pragma VCC_VREG("VB0_wb", 18);
   #pragma VCC_VREG("VG0", 19);
   #pragma VCC_VREG("VG0_wb", 20);
   #pragma VCC_VREG("VG1", 21);
   #pragma VCC_VREG("VG1_wb", 22);
   #pragma VCC_VREG("VGAIN_FACT_B", 23);
   #pragma VCC_VREG("VGAIN_FACT_Gb", 24);
   #pragma VCC_VREG("VGAIN_FACT_Gr", 25);
   #pragma VCC_VREG("VGAIN_FACT_R", 26);
   #pragma VCC_VREG("VR0", 27);
   #pragma VCC_VREG("VR0_copy", 28);
   #pragma VCC_VREG("VR0_wb", 29);
   #pragma VCC_VREG("VR1", 30);
   #pragma VCC_VREG("VR1_wb", 31);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_in", "A0");
   #pragma EVE_REG("Addr_out", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I0", "I3");
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 15u, 12u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(22), _VREG(26));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(24), _VREG(24));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(8), _VREG(25));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(10), _VREG(23));
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(20), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(21), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(12), _AGEN(0), _VPAIR(16,19), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(14), _AGEN(0), _VPAIR(21,27), __vcop_alws());
   __vcop_vmpy(_VREG(16), _VREG(23), _VREG(18), _PREG(0));
   __vcop_vmpy(_VREG(19), _VREG(24), _VREG(20), _PREG(0));
   __vcop_vmpy(_VREG(21), _VREG(25), _VREG(22), _PREG(0));
   __vcop_vmpy(_VREG(27), _VREG(26), _VREG(29), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(18,20), _PREG(16), _AGEN(1), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(22,29), _PREG(18), _AGEN(1), _PREG(6));
   __vcop_vloop_end(1u);

}

void vcop_white_balance_BGGR(
   __vptr_uint16 CFA_short_in,
   __vptr_uint16 CFA_short_out,
   unsigned int blk_w,
   unsigned int blk_h,
   unsigned int gain_factor_R,
   unsigned int gain_factor_Gr,
   unsigned int gain_factor_Gb,
   unsigned int gain_factor_B,
   unsigned int shift_val,
   unsigned int input_stride,
   unsigned int output_stride)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_white_balance_BGGR_init(CFA_short_in, CFA_short_out, blk_w, blk_h, gain_factor_R, gain_factor_Gr, gain_factor_Gb, gain_factor_B, shift_val, input_stride, output_stride, __pblock_vcop_white_balance_BGGR);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_white_balance_BGGR_vloops(__pblock_vcop_white_balance_BGGR);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_white_balance_BGGR_custom(
   __vptr_uint16 CFA_short_in,
   __vptr_uint16 CFA_short_out,
   unsigned int blk_w,
   unsigned int blk_h,
   unsigned int gain_factor_R,
   unsigned int gain_factor_Gr,
   unsigned int gain_factor_Gb,
   unsigned int gain_factor_B,
   unsigned int shift_val,
   unsigned int input_stride,
   unsigned int output_stride,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_white_balance_BGGR_init(CFA_short_in, CFA_short_out, blk_w, blk_h, gain_factor_R, gain_factor_Gr, gain_factor_Gb, gain_factor_B, shift_val, input_stride, output_stride, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_white_balance_BGGR_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_white_balance_GBRG, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_white_balance_GBRG, __ALIGNOF__(int));
unsigned short __pblock_vcop_white_balance_GBRG[24];

unsigned int vcop_white_balance_GBRG_param_count(void)
{
   return 24u;
}

unsigned int vcop_white_balance_GBRG_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_white_balance_GBRG_init(
   __vptr_uint16 CFA_short_in,
   __vptr_uint16 CFA_short_out,
   unsigned int blk_w,
   unsigned int blk_h,
   unsigned int gain_factor_R,
   unsigned int gain_factor_Gr,
   unsigned int gain_factor_Gb,
   unsigned int gain_factor_B,
   unsigned int shift_val,
   unsigned int input_stride,
   unsigned int output_stride,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (((blk_h/2) +1))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (((blk_w/((8u) * 2))+1))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_ROUND,shift_val));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), gain_factor_Gr);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), gain_factor_B);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)CFA_short_in);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)CFA_short_in+input_stride*sizeof(*CFA_short_in));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)CFA_short_out);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)CFA_short_out+output_stride*sizeof(*CFA_short_in));
   __vcop_pblock_init16(pblock, __offset+_PREG(20), (2*input_stride*sizeof(*CFA_short_in)) -((sizeof(*CFA_short_in)*(8u*2)))*((((blk_w/((8u) * 2))+1))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(21), (2*output_stride*sizeof(*CFA_short_in)) -((sizeof(*CFA_short_in)*(8u*2)))*((((blk_w/((8u) * 2))+1))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(22), gain_factor_R);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), gain_factor_Gb);
   __offset += 24;

   return 24u;
}

void vcop_white_balance_GBRG_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VB0", 16);
   #pragma VCC_VREG("VB0_copy", 17);
   #pragma VCC_VREG("VB0_wb", 18);
   #pragma VCC_VREG("VG0", 19);
   #pragma VCC_VREG("VG0_wb", 20);
   #pragma VCC_VREG("VG1", 21);
   #pragma VCC_VREG("VG1_wb", 22);
   #pragma VCC_VREG("VGAIN_FACT_B", 23);
   #pragma VCC_VREG("VGAIN_FACT_Gb", 24);
   #pragma VCC_VREG("VGAIN_FACT_Gr", 25);
   #pragma VCC_VREG("VGAIN_FACT_R", 26);
   #pragma VCC_VREG("VR0", 27);
   #pragma VCC_VREG("VR0_copy", 28);
   #pragma VCC_VREG("VR0_wb", 29);
   #pragma VCC_VREG("VR1", 30);
   #pragma VCC_VREG("VR1_wb", 31);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_in", "A0");
   #pragma EVE_REG("Addr_out", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I0", "I3");
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 15u, 12u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(22), _VREG(26));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(24), _VREG(24));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(8), _VREG(25));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(10), _VREG(23));
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(20), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(21), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(12), _AGEN(0), _VPAIR(19,16), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(14), _AGEN(0), _VPAIR(27,21), __vcop_alws());
   __vcop_vmpy(_VREG(19), _VREG(24), _VREG(20), _PREG(0));
   __vcop_vmpy(_VREG(16), _VREG(23), _VREG(18), _PREG(0));
   __vcop_vmpy(_VREG(27), _VREG(26), _VREG(29), _PREG(0));
   __vcop_vmpy(_VREG(21), _VREG(25), _VREG(22), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(20,18), _PREG(16), _AGEN(1), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(29,22), _PREG(18), _AGEN(1), _PREG(6));
   __vcop_vloop_end(1u);

}

void vcop_white_balance_GBRG(
   __vptr_uint16 CFA_short_in,
   __vptr_uint16 CFA_short_out,
   unsigned int blk_w,
   unsigned int blk_h,
   unsigned int gain_factor_R,
   unsigned int gain_factor_Gr,
   unsigned int gain_factor_Gb,
   unsigned int gain_factor_B,
   unsigned int shift_val,
   unsigned int input_stride,
   unsigned int output_stride)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_white_balance_GBRG_init(CFA_short_in, CFA_short_out, blk_w, blk_h, gain_factor_R, gain_factor_Gr, gain_factor_Gb, gain_factor_B, shift_val, input_stride, output_stride, __pblock_vcop_white_balance_GBRG);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_white_balance_GBRG_vloops(__pblock_vcop_white_balance_GBRG);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_white_balance_GBRG_custom(
   __vptr_uint16 CFA_short_in,
   __vptr_uint16 CFA_short_out,
   unsigned int blk_w,
   unsigned int blk_h,
   unsigned int gain_factor_R,
   unsigned int gain_factor_Gr,
   unsigned int gain_factor_Gb,
   unsigned int gain_factor_B,
   unsigned int shift_val,
   unsigned int input_stride,
   unsigned int output_stride,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_white_balance_GBRG_init(CFA_short_in, CFA_short_out, blk_w, blk_h, gain_factor_R, gain_factor_Gr, gain_factor_Gb, gain_factor_B, shift_val, input_stride, output_stride, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_white_balance_GBRG_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_white_balance_GRBG, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_white_balance_GRBG, __ALIGNOF__(int));
unsigned short __pblock_vcop_white_balance_GRBG[24];

unsigned int vcop_white_balance_GRBG_param_count(void)
{
   return 24u;
}

unsigned int vcop_white_balance_GRBG_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_white_balance_GRBG_init(
   __vptr_uint16 CFA_short_in,
   __vptr_uint16 CFA_short_out,
   unsigned int blk_w,
   unsigned int blk_h,
   unsigned int gain_factor_R,
   unsigned int gain_factor_Gr,
   unsigned int gain_factor_Gb,
   unsigned int gain_factor_B,
   unsigned int shift_val,
   unsigned int input_stride,
   unsigned int output_stride,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (((blk_h/2) +1))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (((blk_w/((8u) * 2))+1))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_ROUND,shift_val));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), gain_factor_Gr);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), gain_factor_B);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)CFA_short_in);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)CFA_short_in+input_stride*sizeof(*CFA_short_in));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)CFA_short_out);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)CFA_short_out+output_stride*sizeof(*CFA_short_in));
   __vcop_pblock_init16(pblock, __offset+_PREG(20), (2*input_stride*sizeof(*CFA_short_in)) -((sizeof(*CFA_short_in)*(8u*2)))*((((blk_w/((8u) * 2))+1))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(21), (2*output_stride*sizeof(*CFA_short_in)) -((sizeof(*CFA_short_in)*(8u*2)))*((((blk_w/((8u) * 2))+1))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(22), gain_factor_R);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), gain_factor_Gb);
   __offset += 24;

   return 24u;
}

void vcop_white_balance_GRBG_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VB0", 16);
   #pragma VCC_VREG("VB0_copy", 17);
   #pragma VCC_VREG("VB0_wb", 18);
   #pragma VCC_VREG("VG0", 19);
   #pragma VCC_VREG("VG0_wb", 20);
   #pragma VCC_VREG("VG1", 21);
   #pragma VCC_VREG("VG1_wb", 22);
   #pragma VCC_VREG("VGAIN_FACT_B", 23);
   #pragma VCC_VREG("VGAIN_FACT_Gb", 24);
   #pragma VCC_VREG("VGAIN_FACT_Gr", 25);
   #pragma VCC_VREG("VGAIN_FACT_R", 26);
   #pragma VCC_VREG("VR0", 27);
   #pragma VCC_VREG("VR0_copy", 28);
   #pragma VCC_VREG("VR0_wb", 29);
   #pragma VCC_VREG("VR1", 30);
   #pragma VCC_VREG("VR1_wb", 31);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_in", "A0");
   #pragma EVE_REG("Addr_out", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I0", "I3");
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 15u, 12u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(22), _VREG(26));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(24), _VREG(24));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(8), _VREG(25));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(10), _VREG(23));
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(20), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(21), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(12), _AGEN(0), _VPAIR(19,27), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(14), _AGEN(0), _VPAIR(16,21), __vcop_alws());
   __vcop_vmpy(_VREG(19), _VREG(24), _VREG(20), _PREG(0));
   __vcop_vmpy(_VREG(27), _VREG(26), _VREG(29), _PREG(0));
   __vcop_vmpy(_VREG(16), _VREG(23), _VREG(18), _PREG(0));
   __vcop_vmpy(_VREG(21), _VREG(25), _VREG(22), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(20,29), _PREG(16), _AGEN(1), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(18,22), _PREG(18), _AGEN(1), _PREG(6));
   __vcop_vloop_end(1u);

}

void vcop_white_balance_GRBG(
   __vptr_uint16 CFA_short_in,
   __vptr_uint16 CFA_short_out,
   unsigned int blk_w,
   unsigned int blk_h,
   unsigned int gain_factor_R,
   unsigned int gain_factor_Gr,
   unsigned int gain_factor_Gb,
   unsigned int gain_factor_B,
   unsigned int shift_val,
   unsigned int input_stride,
   unsigned int output_stride)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_white_balance_GRBG_init(CFA_short_in, CFA_short_out, blk_w, blk_h, gain_factor_R, gain_factor_Gr, gain_factor_Gb, gain_factor_B, shift_val, input_stride, output_stride, __pblock_vcop_white_balance_GRBG);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_white_balance_GRBG_vloops(__pblock_vcop_white_balance_GRBG);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_white_balance_GRBG_custom(
   __vptr_uint16 CFA_short_in,
   __vptr_uint16 CFA_short_out,
   unsigned int blk_w,
   unsigned int blk_h,
   unsigned int gain_factor_R,
   unsigned int gain_factor_Gr,
   unsigned int gain_factor_Gb,
   unsigned int gain_factor_B,
   unsigned int shift_val,
   unsigned int input_stride,
   unsigned int output_stride,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_white_balance_GRBG_init(CFA_short_in, CFA_short_out, blk_w, blk_h, gain_factor_R, gain_factor_Gr, gain_factor_Gb, gain_factor_B, shift_val, input_stride, output_stride, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_white_balance_GRBG_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_white_balance_RGGB, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_white_balance_RGGB, __ALIGNOF__(int));
unsigned short __pblock_vcop_white_balance_RGGB[24];

unsigned int vcop_white_balance_RGGB_param_count(void)
{
   return 24u;
}

unsigned int vcop_white_balance_RGGB_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_white_balance_RGGB_init(
   __vptr_uint16 CFA_short_in,
   __vptr_uint16 CFA_short_out,
   unsigned int blk_w,
   unsigned int blk_h,
   unsigned int gain_factor_R,
   unsigned int gain_factor_Gr,
   unsigned int gain_factor_Gb,
   unsigned int gain_factor_B,
   unsigned int shift_val,
   unsigned int input_stride,
   unsigned int output_stride,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (((blk_h/2) +1))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (((blk_w/((8u) * 2))+1))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_ROUND,shift_val));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), gain_factor_Gr);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), gain_factor_B);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)CFA_short_in);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)CFA_short_in+input_stride*sizeof(*CFA_short_in));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)CFA_short_out);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)CFA_short_out+output_stride*sizeof(*CFA_short_in));
   __vcop_pblock_init16(pblock, __offset+_PREG(20), (2*input_stride*sizeof(*CFA_short_in)) -((sizeof(*CFA_short_in)*(8u*2)))*((((blk_w/((8u) * 2))+1))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(21), (2*output_stride*sizeof(*CFA_short_in)) -((sizeof(*CFA_short_in)*(8u*2)))*((((blk_w/((8u) * 2))+1))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(22), gain_factor_R);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), gain_factor_Gb);
   __offset += 24;

   return 24u;
}

void vcop_white_balance_RGGB_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VB0", 16);
   #pragma VCC_VREG("VB0_copy", 17);
   #pragma VCC_VREG("VB0_wb", 18);
   #pragma VCC_VREG("VG0", 19);
   #pragma VCC_VREG("VG0_wb", 20);
   #pragma VCC_VREG("VG1", 21);
   #pragma VCC_VREG("VG1_wb", 22);
   #pragma VCC_VREG("VGAIN_FACT_B", 23);
   #pragma VCC_VREG("VGAIN_FACT_Gb", 24);
   #pragma VCC_VREG("VGAIN_FACT_Gr", 25);
   #pragma VCC_VREG("VGAIN_FACT_R", 26);
   #pragma VCC_VREG("VR0", 27);
   #pragma VCC_VREG("VR0_copy", 28);
   #pragma VCC_VREG("VR0_wb", 29);
   #pragma VCC_VREG("VR1", 30);
   #pragma VCC_VREG("VR1_wb", 31);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_in", "A0");
   #pragma EVE_REG("Addr_out", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I0", "I3");
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 15u, 12u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(22), _VREG(26));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(24), _VREG(24));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(8), _VREG(25));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(10), _VREG(23));
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(20), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(21), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(12), _AGEN(0), _VPAIR(27,19), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(14), _AGEN(0), _VPAIR(21,16), __vcop_alws());
   __vcop_vmpy(_VREG(27), _VREG(26), _VREG(29), _PREG(0));
   __vcop_vmpy(_VREG(19), _VREG(24), _VREG(20), _PREG(0));
   __vcop_vmpy(_VREG(21), _VREG(25), _VREG(22), _PREG(0));
   __vcop_vmpy(_VREG(16), _VREG(23), _VREG(18), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(29,20), _PREG(16), _AGEN(1), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(22,18), _PREG(18), _AGEN(1), _PREG(6));
   __vcop_vloop_end(1u);

}

void vcop_white_balance_RGGB(
   __vptr_uint16 CFA_short_in,
   __vptr_uint16 CFA_short_out,
   unsigned int blk_w,
   unsigned int blk_h,
   unsigned int gain_factor_R,
   unsigned int gain_factor_Gr,
   unsigned int gain_factor_Gb,
   unsigned int gain_factor_B,
   unsigned int shift_val,
   unsigned int input_stride,
   unsigned int output_stride)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_white_balance_RGGB_init(CFA_short_in, CFA_short_out, blk_w, blk_h, gain_factor_R, gain_factor_Gr, gain_factor_Gb, gain_factor_B, shift_val, input_stride, output_stride, __pblock_vcop_white_balance_RGGB);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_white_balance_RGGB_vloops(__pblock_vcop_white_balance_RGGB);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_white_balance_RGGB_custom(
   __vptr_uint16 CFA_short_in,
   __vptr_uint16 CFA_short_out,
   unsigned int blk_w,
   unsigned int blk_h,
   unsigned int gain_factor_R,
   unsigned int gain_factor_Gr,
   unsigned int gain_factor_Gb,
   unsigned int gain_factor_B,
   unsigned int shift_val,
   unsigned int input_stride,
   unsigned int output_stride,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_white_balance_RGGB_init(CFA_short_in, CFA_short_out, blk_w, blk_h, gain_factor_R, gain_factor_Gr, gain_factor_Gb, gain_factor_B, shift_val, input_stride, output_stride, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_white_balance_RGGB_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

