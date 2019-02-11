#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_rotate_90, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_rotate_90, __ALIGNOF__(int));
unsigned short __pblock_vcop_rotate_90[28];

unsigned int vcop_rotate_90_param_count(void)
{
   return 28u;
}

unsigned int vcop_rotate_90_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_rotate_90_init(
   __vptr_uint8 in,
   __vptr_uint8 inter,
   __vptr_uint8 out,
   int img_w,
   int img_h,
   int out_w,
   int out_h,
   int blk_w,
   int blk_h,
   int in_type,
   int inter_type,
   int out_type,
   int angle,
   int round_shift,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (blk_h/( 8 * (4/sizeof(*in))))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (blk_w/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (( 8 * (4/sizeof(*in))))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), (img_w*sizeof(*in)));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), (8u*sizeof(*in)) -(img_w*sizeof(*in))*((( 8 * (4/sizeof(*in))))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(8), ((8*(4/sizeof(*in)))*img_w*sizeof(*in)) -(8u*sizeof(*in))*((blk_w/(8u))-1u) -(img_w*sizeof(*in))*((( 8 * (4/sizeof(*in))))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(9), 257);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), (9*(4/sizeof(*in))*blk_h*sizeof(*out)) -(9*(8*(4/sizeof(*in)))*sizeof(*out))*((blk_w/(8u))-1u) -(sizeof(*out))*((( 8 * (4/sizeof(*in))))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)in);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)inter);
   __offset += 14;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (blk_w/( 8 * (4/sizeof(*in))))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (blk_h)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((( 8 * (4/sizeof(*in)))/(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 12);
   __vcop_pblock_init16(pblock, __offset+_PREG(8), (blk_h*(9*(4/sizeof(*in)))*sizeof(*out)) -((9*(4/sizeof(*in)))*sizeof(*out))*((blk_h)-1u) -(8u*sizeof(*out))*(((( 8 * (4/sizeof(*in)))/(8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(9), -56);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), (blk_h*(8*(4/sizeof(*in)))*sizeof(*out)) -(-(8*(4/sizeof(*in)))*sizeof(*out))*((blk_h)-1u) -(8u*sizeof(*out))*(((( 8 * (4/sizeof(*in)))/(8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)inter);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)out+(blk_h-1)*(8*(4/sizeof(*in)))*sizeof(*out));
   __offset += 14;

   return 28u;
}

void vcop_rotate_90_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("dataAddr", "A0");
   #pragma EVE_REG("outAddr", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I2");
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 5u, 7u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(6), _PREG(7), _PREG(8), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(1), _PREG(9), _PREG(10), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(12), _AGEN(0), _VREG(0), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_offst_np1(), __vcop_alws(), _VREG(0), _PREG(14), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("dataAddr", "A0");
   #pragma EVE_REG("outAddr", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I2");
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 5u, 7u, 2u);
   __vcop_vagen(_AGEN(0), _PREG(6), _PREG(7), _PREG(8), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(6), _PREG(9), _PREG(10), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(12), _AGEN(0), _VREG(0), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(0), _PREG(14), _AGEN(1), _PREG(0));
   __vcop_vloop_end(2u);

}

void vcop_rotate_90(
   __vptr_uint8 in,
   __vptr_uint8 inter,
   __vptr_uint8 out,
   int img_w,
   int img_h,
   int out_w,
   int out_h,
   int blk_w,
   int blk_h,
   int in_type,
   int inter_type,
   int out_type,
   int angle,
   int round_shift)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_rotate_90_init(in, inter, out, img_w, img_h, out_w, out_h, blk_w, blk_h, in_type, inter_type, out_type, angle, round_shift, __pblock_vcop_rotate_90);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_rotate_90_vloops(__pblock_vcop_rotate_90);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_rotate_90_custom(
   __vptr_uint8 in,
   __vptr_uint8 inter,
   __vptr_uint8 out,
   int img_w,
   int img_h,
   int out_w,
   int out_h,
   int blk_w,
   int blk_h,
   int in_type,
   int inter_type,
   int out_type,
   int angle,
   int round_shift,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_rotate_90_init(in, inter, out, img_w, img_h, out_w, out_h, blk_w, blk_h, in_type, inter_type, out_type, angle, round_shift, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_rotate_90_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_rotate_180, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_rotate_180, __ALIGNOF__(int));
unsigned short __pblock_vcop_rotate_180[14];

unsigned int vcop_rotate_180_param_count(void)
{
   return 14u;
}

unsigned int vcop_rotate_180_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_rotate_180_init(
   __vptr_uint8 in,
   __vptr_uint8 inter,
   __vptr_uint8 out,
   int img_w,
   int img_h,
   int out_w,
   int out_h,
   int blk_w,
   int blk_h,
   int in_type,
   int inter_type,
   int out_type,
   int angle,
   int round_shift,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   unsigned char cust_arr1[8] = {7, 6, 5, 4, 3, 2, 1, 0};

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (blk_h)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (blk_w/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)out+blk_h*blk_w-8u);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), _CUSTOM(cust_arr1));
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), (img_w*sizeof(*in)) -(8u*sizeof(*in))*((blk_w/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), -8);
   __vcop_pblock_init16(pblock, __offset+_PREG(13), (-blk_w*sizeof(*out)) -(-8u*sizeof(*out))*((blk_w/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)in);
   __offset += 14;

   return 14u;
}

void vcop_rotate_180_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("dataAddr", "A0");
   #pragma EVE_REG("outAddr", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 5u, 7u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(10), _PREG(11), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(12), _PREG(13), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_cust_p8(), _PREG(14), _AGEN(0), _VREG(0), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(0), _PREG(6), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_rotate_180(
   __vptr_uint8 in,
   __vptr_uint8 inter,
   __vptr_uint8 out,
   int img_w,
   int img_h,
   int out_w,
   int out_h,
   int blk_w,
   int blk_h,
   int in_type,
   int inter_type,
   int out_type,
   int angle,
   int round_shift)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_rotate_180_init(in, inter, out, img_w, img_h, out_w, out_h, blk_w, blk_h, in_type, inter_type, out_type, angle, round_shift, __pblock_vcop_rotate_180);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_rotate_180_vloops(__pblock_vcop_rotate_180);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_rotate_180_custom(
   __vptr_uint8 in,
   __vptr_uint8 inter,
   __vptr_uint8 out,
   int img_w,
   int img_h,
   int out_w,
   int out_h,
   int blk_w,
   int blk_h,
   int in_type,
   int inter_type,
   int out_type,
   int angle,
   int round_shift,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_rotate_180_init(in, inter, out, img_w, img_h, out_w, out_h, blk_w, blk_h, in_type, inter_type, out_type, angle, round_shift, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_rotate_180_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_rotate_270, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_rotate_270, __ALIGNOF__(int));
unsigned short __pblock_vcop_rotate_270[24];

unsigned int vcop_rotate_270_param_count(void)
{
   return 24u;
}

unsigned int vcop_rotate_270_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_rotate_270_init(
   __vptr_uint8 in,
   __vptr_uint8 inter,
   __vptr_uint8 out,
   int img_w,
   int img_h,
   int out_w,
   int out_h,
   int blk_w,
   int blk_h,
   int in_type,
   int inter_type,
   int out_type,
   int angle,
   int round_shift,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (blk_h/( 8 * (4/sizeof(*in))))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (blk_w/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (( 8 * (4/sizeof(*in))))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), (img_w*sizeof(*in)));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), (8u*sizeof(*in)) -(img_w*sizeof(*in))*((( 8 * (4/sizeof(*in))))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(8), ((8*(4/sizeof(*in)))*img_w*sizeof(*in)) -(8u*sizeof(*in))*((blk_w/(8u))-1u) -(img_w*sizeof(*in))*((( 8 * (4/sizeof(*in))))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(9), -1);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 319);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), (-(9*(4/sizeof(*in)))*blk_w*sizeof(*out)) -(9*(8*(4/sizeof(*in)))*sizeof(*out))*((blk_w/(8u))-1u) -(-sizeof(*out))*((( 8 * (4/sizeof(*in))))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)in);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)inter+(9*(4/sizeof(*in))*blk_w+8*(4/sizeof(*in))-1));
   __offset += 14;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (blk_w * (blk_h/( 8 * (4/sizeof(*in)))))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((9 * (4/sizeof(*in)))/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 12);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)inter);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)out);
   __offset += 10;

   return 24u;
}

void vcop_rotate_270_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("dataAddr", "A0");
   #pragma EVE_REG("outAddr", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I2");
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 5u, 7u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(6), _PREG(7), _PREG(8), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(9), _PREG(10), _PREG(11), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(12), _AGEN(0), _VREG(0), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_offst_np1(), __vcop_alws(), _VREG(0), _PREG(14), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("dataAddr", "A0");
   #pragma EVE_REG("outAddr", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 5u, 5u, 2u);
   __vcop_vagen(_AGEN(0), _PREG(6), _PREG(7), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(6), _PREG(6), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(8), _AGEN(0), _VREG(0), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(0), _PREG(10), _AGEN(1), _PREG(0));
   __vcop_vloop_end(2u);

}

void vcop_rotate_270(
   __vptr_uint8 in,
   __vptr_uint8 inter,
   __vptr_uint8 out,
   int img_w,
   int img_h,
   int out_w,
   int out_h,
   int blk_w,
   int blk_h,
   int in_type,
   int inter_type,
   int out_type,
   int angle,
   int round_shift)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_rotate_270_init(in, inter, out, img_w, img_h, out_w, out_h, blk_w, blk_h, in_type, inter_type, out_type, angle, round_shift, __pblock_vcop_rotate_270);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_rotate_270_vloops(__pblock_vcop_rotate_270);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_rotate_270_custom(
   __vptr_uint8 in,
   __vptr_uint8 inter,
   __vptr_uint8 out,
   int img_w,
   int img_h,
   int out_w,
   int out_h,
   int blk_w,
   int blk_h,
   int in_type,
   int inter_type,
   int out_type,
   int angle,
   int round_shift,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_rotate_270_init(in, inter, out, img_w, img_h, out_w, out_h, blk_w, blk_h, in_type, inter_type, out_type, angle, round_shift, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_rotate_270_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

