#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_median3x3_char, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_median3x3_char, __ALIGNOF__(int));
unsigned short __pblock_vcop_median3x3_char[62];

unsigned int vcop_median3x3_char_param_count(void)
{
   return 62u;
}

unsigned int vcop_median3x3_char_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_median3x3_char_init(
   __vptr_int8 in,
   __vptr_int8 out,
   __vptr_int8 scratch1,
   __vptr_int8 scratch2,
   unsigned short w_blk,
   unsigned short h_blk,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((w_blk)/((8u) * 2))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (h_blk - 2)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)in+1*w_blk*sizeof(*in));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)in+2*w_blk*sizeof(*in));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)scratch1+0*w_blk*sizeof(*in));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)scratch1+1*w_blk*sizeof(*in));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)scratch1+2*w_blk*sizeof(*in));
   __vcop_pblock_init16(pblock, __offset+_PREG(16), (w_blk*sizeof(*in)));
   __vcop_pblock_init16(pblock, __offset+_PREG(17), (2*(8u*sizeof(*in))) -(w_blk*sizeof(*in))*((h_blk - 2)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(18), (3*w_blk*sizeof(*in)));
   __vcop_pblock_init16(pblock, __offset+_PREG(19), (2*(8u*sizeof(*in))) -(3*w_blk*sizeof(*in))*((h_blk - 2)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)in+0*w_blk*sizeof(*in));
   __offset += 22;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (h_blk - 2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (w_blk/((8u) * 2))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (3)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)scratch1+0*w_blk*sizeof(*in));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)scratch1+1*w_blk*sizeof(*in));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)scratch1+2*w_blk*sizeof(*in));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)scratch2+0*w_blk*sizeof(*in));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)scratch2+1*w_blk*sizeof(*in));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)scratch2+2*w_blk*sizeof(*in));
   __vcop_pblock_init16(pblock, __offset+_PREG(18), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(19), (3*w_blk*sizeof(*in)) -(2*(8u*sizeof(*in)))*((w_blk/((8u) * 2))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(20), 14);
   __vcop_pblock_init16(pblock, __offset+_PREG(21), (3*w_blk*sizeof(*in)) -(2*(8u*sizeof(*in)))*((w_blk/((8u) * 2))-1u) -(sizeof(*in))*((3)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(22), -128);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), 127);
   __offset += 24;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (h_blk - 2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (w_blk/((8u) * 2))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)scratch2+2*w_blk*sizeof(*in));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)out);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), (3*w_blk*sizeof(*in)) -((8u*2)*sizeof(*in))*((w_blk/((8u) * 2))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), ((w_blk-2)*sizeof(*out)) -((8u*2)*sizeof(*out))*((w_blk/((8u) * 2))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)scratch2+0*w_blk*sizeof(*in));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)scratch2+1*w_blk*sizeof(*in));
   __offset += 16;

   return 62u;
}

void vcop_median3x3_char_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("c2h_0", 16);
   #pragma VCC_VREG("c2h_1", 17);
   #pragma VCC_VREG("c2l_0", 18);
   #pragma VCC_VREG("c2l_1", 19);
   #pragma VCC_VREG("c2m_0", 20);
   #pragma VCC_VREG("c2m_1", 21);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("dataAddr0", "A0");
   #pragma EVE_REG("dataAddr1", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 21u, 11u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(20), _VREG(18));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(20), _VREG(20));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(20), _VREG(16));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(20), _VREG(19));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(20), _VREG(21));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(20), _VREG(17));
   __vcop_vagen(_AGEN(0), _PREG(16), _PREG(17), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(18), _PREG(19), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeB(), __vcop_dintrlv(), _PREG(22), _AGEN(0), _VPAIR(18,19), __vcop_alws());
   __vcop_vload(__vcop_sizeB(), __vcop_dintrlv(), _PREG(6), _AGEN(0), _VPAIR(20,21), __vcop_alws());
   __vcop_vload(__vcop_sizeB(), __vcop_dintrlv(), _PREG(8), _AGEN(0), _VPAIR(16,17), __vcop_alws());
   __vcop_vsort2(_VREG(18), _VREG(16));
   __vcop_vsort2(_VREG(18), _VREG(20));
   __vcop_vsort2(_VREG(20), _VREG(16));
   __vcop_vsort2(_VREG(19), _VREG(17));
   __vcop_vsort2(_VREG(19), _VREG(21));
   __vcop_vsort2(_VREG(21), _VREG(17));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeB(), __vcop_intrlv(), __vcop_alws(), _VPAIR(18,19), _PREG(10), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeB(), __vcop_intrlv(), __vcop_alws(), _VPAIR(20,21), _PREG(12), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeB(), __vcop_intrlv(), __vcop_alws(), _VPAIR(16,17), _PREG(14), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("max_in0", 22);
   #pragma VCC_VREG("max_in1", 23);
   #pragma VCC_VREG("max_of_min0", 24);
   #pragma VCC_VREG("max_of_min1", 25);
   #pragma VCC_VREG("med_in0", 26);
   #pragma VCC_VREG("med_in1", 27);
   #pragma VCC_VREG("med_max0", 28);
   #pragma VCC_VREG("med_max1", 29);
   #pragma VCC_VREG("med_max_nxt0", 30);
   #pragma VCC_VREG("med_max_nxt1", 31);
   #pragma VCC_VREG("min_in0", 32);
   #pragma VCC_VREG("min_in1", 33);
   #pragma VCC_VREG("min_of_max0", 34);
   #pragma VCC_VREG("min_of_max1", 35);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("dataAddr1", "A0");
   #pragma EVE_REG("dataAddr0", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I2");
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 25u, 12u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(22), _VREG(28));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(22), _VREG(30));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(24), _VREG(34));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(22), _VREG(24));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(22), _VREG(29));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(22), _VREG(31));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(24), _VREG(35));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(22), _VREG(25));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(18), _PREG(19), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(1), _PREG(20), _PREG(21), _PREG(0));
   __vcop_vload(__vcop_sizeB(), __vcop_dintrlv(), _PREG(6), _AGEN(1), _VPAIR(32,33), __vcop_alws());
   __vcop_vload(__vcop_sizeB(), __vcop_dintrlv(), _PREG(8), _AGEN(1), _VPAIR(26,27), __vcop_alws());
   __vcop_vload(__vcop_sizeB(), __vcop_dintrlv(), _PREG(10), _AGEN(1), _VPAIR(22,23), __vcop_alws());
   __vcop_vmax(_VREG(24), _VREG(32), _VREG(24));
   __vcop_vmin(_VREG(34), _VREG(22), _VREG(34));
   __vcop_vmax(_VREG(25), _VREG(33), _VREG(25));
   __vcop_vmin(_VREG(35), _VREG(23), _VREG(35));
   __vcop_vsort2(_VREG(26), _VREG(28));
   __vcop_vsort2(_VREG(26), _VREG(30));
   __vcop_vsort2(_VREG(27), _VREG(29));
   __vcop_vsort2(_VREG(27), _VREG(31));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeB(), __vcop_intrlv(), __vcop_last_i4(), _VPAIR(24,25), _PREG(12), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeB(), __vcop_intrlv(), __vcop_last_i4(), _VPAIR(30,31), _PREG(14), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeB(), __vcop_intrlv(), __vcop_last_i4(), _VPAIR(34,35), _PREG(16), _AGEN(0), _PREG(0));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("max_out0", 36);
   #pragma VCC_VREG("max_out1", 37);
   #pragma VCC_VREG("med_out0", 38);
   #pragma VCC_VREG("med_out1", 39);
   #pragma VCC_VREG("min_out0", 40);
   #pragma VCC_VREG("min_out1", 41);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("dataAddr0", "A0");
   #pragma EVE_REG("dataAddr1", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 13u, 8u, 3u);
   __vcop_vagen(_AGEN(0), _PREG(10), _PREG(11), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(10), _PREG(12), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeB(), __vcop_dintrlv(), _PREG(14), _AGEN(0), _VPAIR(40,41), __vcop_alws());
   __vcop_vload(__vcop_sizeB(), __vcop_dintrlv(), _PREG(16), _AGEN(0), _VPAIR(38,39), __vcop_alws());
   __vcop_vload(__vcop_sizeB(), __vcop_dintrlv(), _PREG(6), _AGEN(0), _VPAIR(36,37), __vcop_alws());
   __vcop_vsort2(_VREG(40), _VREG(36));
   __vcop_vsort2(_VREG(40), _VREG(38));
   __vcop_vsort2(_VREG(38), _VREG(36));
   __vcop_vsort2(_VREG(41), _VREG(37));
   __vcop_vsort2(_VREG(41), _VREG(39));
   __vcop_vsort2(_VREG(39), _VREG(37));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeB(), __vcop_intrlv(), __vcop_alws(), _VPAIR(38,39), _PREG(8), _AGEN(1), _PREG(0));
   __vcop_vloop_end(3u);

}

void vcop_median3x3_char(
   __vptr_int8 in,
   __vptr_int8 out,
   __vptr_int8 scratch1,
   __vptr_int8 scratch2,
   unsigned short w_blk,
   unsigned short h_blk)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_median3x3_char_init(in, out, scratch1, scratch2, w_blk, h_blk, __pblock_vcop_median3x3_char);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_median3x3_char_vloops(__pblock_vcop_median3x3_char);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_median3x3_char_custom(
   __vptr_int8 in,
   __vptr_int8 out,
   __vptr_int8 scratch1,
   __vptr_int8 scratch2,
   unsigned short w_blk,
   unsigned short h_blk,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_median3x3_char_init(in, out, scratch1, scratch2, w_blk, h_blk, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_median3x3_char_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_median3x3_uchar, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_median3x3_uchar, __ALIGNOF__(int));
unsigned short __pblock_vcop_median3x3_uchar[62];

unsigned int vcop_median3x3_uchar_param_count(void)
{
   return 62u;
}

unsigned int vcop_median3x3_uchar_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_median3x3_uchar_init(
   __vptr_uint8 in,
   __vptr_uint8 out,
   __vptr_uint8 scratch1,
   __vptr_uint8 scratch2,
   unsigned short w_blk,
   unsigned short h_blk,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (w_blk/((8u) * 2))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (h_blk - 2)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)in+1*w_blk*sizeof(*in));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)in+2*w_blk*sizeof(*in));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)scratch1+0*w_blk*sizeof(*in));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)scratch1+1*w_blk*sizeof(*in));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)scratch1+2*w_blk*sizeof(*in));
   __vcop_pblock_init16(pblock, __offset+_PREG(16), (w_blk*sizeof(*in)));
   __vcop_pblock_init16(pblock, __offset+_PREG(17), (2*(8u*sizeof(*in))) -(w_blk*sizeof(*in))*((h_blk - 2)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(18), (3*w_blk*sizeof(*in)));
   __vcop_pblock_init16(pblock, __offset+_PREG(19), (2*(8u*sizeof(*in))) -(3*w_blk*sizeof(*in))*((h_blk - 2)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)in+0*w_blk*sizeof(*in));
   __offset += 22;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (h_blk - 2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (w_blk/((8u) * 2))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (3)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)scratch1+0*w_blk*sizeof(*in));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)scratch1+1*w_blk*sizeof(*in));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)scratch1+2*w_blk*sizeof(*in));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)scratch2+0*w_blk*sizeof(*in));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)scratch2+1*w_blk*sizeof(*in));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)scratch2+2*w_blk*sizeof(*in));
   __vcop_pblock_init16(pblock, __offset+_PREG(18), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(19), (3*w_blk*sizeof(*in)) -(2*(8u*sizeof(*in)))*((w_blk/((8u) * 2))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(20), 14);
   __vcop_pblock_init16(pblock, __offset+_PREG(21), (3*w_blk*sizeof(*in)) -(2*(8u*sizeof(*in)))*((w_blk/((8u) * 2))-1u) -(sizeof(*in))*((3)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(22), 0x0);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), 255);
   __offset += 24;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (h_blk - 2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (w_blk/((8u) * 2))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)scratch2+2*w_blk*sizeof(*in));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)out);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), (3*w_blk*sizeof(*in)) -((8u*2)*sizeof(*in))*((w_blk/((8u) * 2))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), ((w_blk-2)*sizeof(*out)) -((8u*2)*sizeof(*out))*((w_blk/((8u) * 2))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)scratch2+0*w_blk*sizeof(*in));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)scratch2+1*w_blk*sizeof(*in));
   __offset += 16;

   return 62u;
}

void vcop_median3x3_uchar_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("c2h_0", 16);
   #pragma VCC_VREG("c2h_1", 17);
   #pragma VCC_VREG("c2l_0", 18);
   #pragma VCC_VREG("c2l_1", 19);
   #pragma VCC_VREG("c2m_0", 20);
   #pragma VCC_VREG("c2m_1", 21);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("dataAddr0", "A0");
   #pragma EVE_REG("dataAddr1", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 21u, 11u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(20), _VREG(18));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(20), _VREG(20));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(20), _VREG(16));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(20), _VREG(19));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(20), _VREG(21));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(20), _VREG(17));
   __vcop_vagen(_AGEN(0), _PREG(16), _PREG(17), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(18), _PREG(19), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(22), _AGEN(0), _VPAIR(18,19), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(6), _AGEN(0), _VPAIR(20,21), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(8), _AGEN(0), _VPAIR(16,17), __vcop_alws());
   __vcop_vsort2(_VREG(18), _VREG(16));
   __vcop_vsort2(_VREG(18), _VREG(20));
   __vcop_vsort2(_VREG(20), _VREG(16));
   __vcop_vsort2(_VREG(19), _VREG(17));
   __vcop_vsort2(_VREG(19), _VREG(21));
   __vcop_vsort2(_VREG(21), _VREG(17));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(18,19), _PREG(10), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(20,21), _PREG(12), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(16,17), _PREG(14), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("max_in0", 22);
   #pragma VCC_VREG("max_in1", 23);
   #pragma VCC_VREG("max_of_min0", 24);
   #pragma VCC_VREG("max_of_min1", 25);
   #pragma VCC_VREG("med_in0", 26);
   #pragma VCC_VREG("med_in1", 27);
   #pragma VCC_VREG("med_max0", 28);
   #pragma VCC_VREG("med_max1", 29);
   #pragma VCC_VREG("med_max_nxt0", 30);
   #pragma VCC_VREG("med_max_nxt1", 31);
   #pragma VCC_VREG("min_in0", 32);
   #pragma VCC_VREG("min_in1", 33);
   #pragma VCC_VREG("min_of_max0", 34);
   #pragma VCC_VREG("min_of_max1", 35);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("dataAddr1", "A0");
   #pragma EVE_REG("dataAddr0", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I2");
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I3", "I4");
   

   __vcop_vloop(__vcop_compute(), 25u, 12u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(22), _VREG(28));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(22), _VREG(30));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(24), _VREG(34));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(22), _VREG(24));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(22), _VREG(29));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(22), _VREG(31));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(24), _VREG(35));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(22), _VREG(25));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(18), _PREG(19), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(1), _PREG(20), _PREG(21), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(6), _AGEN(1), _VPAIR(32,33), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(8), _AGEN(1), _VPAIR(26,27), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(10), _AGEN(1), _VPAIR(22,23), __vcop_alws());
   __vcop_vmax(_VREG(24), _VREG(32), _VREG(24));
   __vcop_vmin(_VREG(34), _VREG(22), _VREG(34));
   __vcop_vmax(_VREG(25), _VREG(33), _VREG(25));
   __vcop_vmin(_VREG(35), _VREG(23), _VREG(35));
   __vcop_vsort2(_VREG(26), _VREG(28));
   __vcop_vsort2(_VREG(26), _VREG(30));
   __vcop_vsort2(_VREG(27), _VREG(29));
   __vcop_vsort2(_VREG(27), _VREG(31));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_intrlv(), __vcop_last_i4(), _VPAIR(24,25), _PREG(12), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_intrlv(), __vcop_last_i4(), _VPAIR(30,31), _PREG(14), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_intrlv(), __vcop_last_i4(), _VPAIR(34,35), _PREG(16), _AGEN(0), _PREG(0));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("max_out0", 36);
   #pragma VCC_VREG("max_out1", 37);
   #pragma VCC_VREG("med_out0", 38);
   #pragma VCC_VREG("med_out1", 39);
   #pragma VCC_VREG("min_out0", 40);
   #pragma VCC_VREG("min_out1", 41);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("dataAddr0", "A0");
   #pragma EVE_REG("dataAddr1", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 13u, 8u, 3u);
   __vcop_vagen(_AGEN(0), _PREG(10), _PREG(11), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(10), _PREG(12), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(14), _AGEN(0), _VPAIR(40,41), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(16), _AGEN(0), _VPAIR(38,39), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(6), _AGEN(0), _VPAIR(36,37), __vcop_alws());
   __vcop_vsort2(_VREG(40), _VREG(36));
   __vcop_vsort2(_VREG(40), _VREG(38));
   __vcop_vsort2(_VREG(38), _VREG(36));
   __vcop_vsort2(_VREG(41), _VREG(37));
   __vcop_vsort2(_VREG(41), _VREG(39));
   __vcop_vsort2(_VREG(39), _VREG(37));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(38,39), _PREG(8), _AGEN(1), _PREG(0));
   __vcop_vloop_end(3u);

}

void vcop_median3x3_uchar(
   __vptr_uint8 in,
   __vptr_uint8 out,
   __vptr_uint8 scratch1,
   __vptr_uint8 scratch2,
   unsigned short w_blk,
   unsigned short h_blk)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_median3x3_uchar_init(in, out, scratch1, scratch2, w_blk, h_blk, __pblock_vcop_median3x3_uchar);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_median3x3_uchar_vloops(__pblock_vcop_median3x3_uchar);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_median3x3_uchar_custom(
   __vptr_uint8 in,
   __vptr_uint8 out,
   __vptr_uint8 scratch1,
   __vptr_uint8 scratch2,
   unsigned short w_blk,
   unsigned short h_blk,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_median3x3_uchar_init(in, out, scratch1, scratch2, w_blk, h_blk, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_median3x3_uchar_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

