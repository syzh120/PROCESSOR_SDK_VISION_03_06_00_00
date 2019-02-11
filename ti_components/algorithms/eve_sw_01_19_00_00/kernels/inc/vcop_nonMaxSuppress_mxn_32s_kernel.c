#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_nonMaxSuppress_mxn_32s, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_nonMaxSuppress_mxn_32s, __ALIGNOF__(int));
unsigned short __pblock_vcop_nonMaxSuppress_mxn_32s[76];

unsigned int vcop_nonMaxSuppress_mxn_32s_param_count(void)
{
   return 76u;
}

unsigned int vcop_nonMaxSuppress_mxn_32s_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_nonMaxSuppress_mxn_32s_init(
   __vptr_int32 im_A,
   __vptr_uint8 out_B,
   __vptr_int32 scratch_B,
   __vptr_int32 scratch_C,
   int width,
   int height,
   int input_stride,
   int output_stride,
   int m,
   int n,
   int thresh,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (height-m+1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((width + (8u)*2 - 1)/((8u)*2))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((m-1))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)im_A+8u*sizeof(*im_A));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)im_A+input_stride*sizeof(*im_A));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)im_A+input_stride*sizeof(*im_A)+8u*sizeof(*im_A));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)scratch_B);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)scratch_B+8u*sizeof(*im_A));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)out_B);
   __vcop_pblock_init16(pblock, __offset+_PREG(18), 64);
   __vcop_pblock_init16(pblock, __offset+_PREG(19), (width*sizeof(*im_A)) -((8u*sizeof(*im_A))*2)*(((width + (8u)*2 - 1)/((8u)*2))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(20), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(21), (output_stride*sizeof(*out_B)) -((8u*sizeof(*out_B))*2)*(((width + (8u)*2 - 1)/((8u)*2))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(22), (input_stride*sizeof(*im_A)) -((8u*sizeof(*im_A))*2)*(((width + (8u)*2 - 1)/((8u)*2))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(23), (input_stride*sizeof(*im_A)));
   __vcop_pblock_init16(pblock, __offset+_PREG(24), ((8u*sizeof(*im_A))*2) -(input_stride*sizeof(*im_A))*(((m-1))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(25), (input_stride*sizeof(*im_A)) -((8u*sizeof(*im_A))*2)*(((width + (8u)*2 - 1)/((8u)*2))-1u) -(input_stride*sizeof(*im_A))*(((m-1))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(26), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)im_A);
   __offset += 28;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), ((height-m+2)/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((width-n+(8u))/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((n-1))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)scratch_B+sizeof(*im_A));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)scratch_B+width*sizeof(*im_A)+sizeof(*im_A));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)scratch_C);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)scratch_C+(width-n+8u)/8u*8u*sizeof(*im_A));
   __vcop_pblock_init16(pblock, __offset+_PREG(14), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(15), (2*width*sizeof(*im_A)) -((8u*sizeof(*im_A)))*(((width-n+(8u))/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(16), (2*((width-n+8u)/8u*8u)*sizeof(*im_A)) -((8u*sizeof(*im_A)))*(((width-n+(8u))/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(17), 4);
   __vcop_pblock_init16(pblock, __offset+_PREG(18), ((8u*sizeof(*im_A))) -(sizeof(*im_A))*(((n-1))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(19), (2*width*sizeof(*im_A)) -((8u*sizeof(*im_A)))*(((width-n+(8u))/(8u))-1u) -(sizeof(*im_A))*(((n-1))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)scratch_B);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)scratch_B+width*sizeof(*im_A));
   __offset += 22;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((height-m+2)/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((width-n+(8u))/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)im_A+(m-1)/2*input_stride*sizeof(*im_A)+(n-1)/2*sizeof(*im_A));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)im_A+(m-1)/2*input_stride*sizeof(*im_A)+(n-1)/2*sizeof(*im_A)+input_stride*sizeof(*im_A));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)scratch_C);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)scratch_C+(width-n+8u)/8u*8u*sizeof(*im_A));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)out_B);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)out_B+output_stride*sizeof(*out_B));
   __vcop_pblock_init16(pblock, __offset+_PREG(18), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(19), (2*((width-n+8u)/8u*8u)*sizeof(*im_A)) -((8u*sizeof(*im_A)))*(((width-n+(8u))/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(20), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(21), (2*output_stride*sizeof(*out_B)) -((8u*sizeof(*out_B)))*(((width-n+(8u))/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(22), (2*input_stride*sizeof(*im_A)) -((8u*sizeof(*im_A)))*(((width-n+(8u))/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(24), thresh);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), 255);
   __offset += 26;

   return 76u;
}

void vcop_nonMaxSuppress_mxn_32s_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("C0", 16);
   #pragma VCC_VREG("C1", 17);
   #pragma VCC_VREG("I0", 18);
   #pragma VCC_VREG("I1", 19);
   #pragma VCC_VREG("Ieqmax0", 20);
   #pragma VCC_VREG("Ieqmax1", 21);
   #pragma VCC_VREG("Igtthr0", 22);
   #pragma VCC_VREG("Igtthr1", 23);
   #pragma VCC_VREG("K0", 24);
   #pragma VCC_VREG("K0p", 25);
   #pragma VCC_VREG("K255", 26);
   #pragma VCC_VREG("R0", 27);
   #pragma VCC_VREG("R1", 28);
   #pragma VCC_VREG("Rthr", 29);
   #pragma VCC_VREG("max0", 30);
   #pragma VCC_VREG("max1", 31);
   #pragma VCC_VREG("maxs", 32);
   #pragma VCC_VREG("maxsp", 33);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   #pragma EVE_REG("Addr2", "A1");
   #pragma EVE_REG("Addr3", "A2");
   #pragma EVE_REG("Addr0", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("i", "I2");
   #pragma EVE_REG("j", "I3");
   #pragma EVE_REG("k", "I4");
   

   __vcop_vloop(__vcop_compute(), 16u, 14u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(26), _VREG(24));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(26), _VREG(25));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(18), _PREG(19), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(20), _PREG(21), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(0), _PREG(18), _PREG(22), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(23), _PREG(24), _PREG(25), _PREG(0));
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(28), _AGEN(2), _VREG(32), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(6), _AGEN(2), _VREG(33), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(8), _AGEN(3), _VREG(27), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(10), _AGEN(3), _VREG(28), __vcop_alws());
   __vcop_vmax(_VREG(27), _VREG(32), _VREG(32));
   __vcop_vmax(_VREG(28), _VREG(33), _VREG(33));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_last_i4(), _VREG(32), _PREG(12), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_last_i4(), _VREG(33), _PREG(14), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_intrlv(), __vcop_last_i4(), _VPAIR(24,25), _PREG(16), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   #pragma EVE_REG("Addr2", "A1");
   #pragma EVE_REG("Addr0", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("i", "I2");
   #pragma EVE_REG("j", "I3");
   #pragma EVE_REG("k", "I4");
   

   __vcop_vloop(__vcop_compute(), 12u, 11u, 2u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(14), _PREG(15), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(14), _PREG(16), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(17), _PREG(18), _PREG(19), _PREG(0));
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(20), _AGEN(0), _VREG(30), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(22), _AGEN(0), _VREG(31), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(6), _AGEN(2), _VREG(18), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(8), _AGEN(2), _VREG(19), __vcop_alws());
   __vcop_vmax(_VREG(18), _VREG(30), _VREG(30));
   __vcop_vmax(_VREG(19), _VREG(31), _VREG(31));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_last_i4(), _VREG(30), _PREG(10), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_last_i4(), _VREG(31), _PREG(12), _AGEN(1), _PREG(0));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   #pragma EVE_REG("Addr2", "A1");
   #pragma EVE_REG("Addr3", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("i", "I3");
   #pragma EVE_REG("j", "I4");
   

   __vcop_vloop(__vcop_compute(), 18u, 13u, 3u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(24), _VREG(29));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(26), _VREG(26));
   __vcop_vagen(_AGEN(0), _PREG(18), _PREG(19), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(20), _PREG(21), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(18), _PREG(22), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(6), _AGEN(2), _VREG(18), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(8), _AGEN(2), _VREG(19), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(10), _AGEN(0), _VREG(30), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(12), _AGEN(0), _VREG(31), __vcop_alws());
   __vcop_vcmpeq(_VREG(18), _VREG(30), _VREG(20));
   __vcop_vcmpeq(_VREG(19), _VREG(31), _VREG(21));
   __vcop_vcmpgt(_VREG(18), _VREG(29), _VREG(22));
   __vcop_vcmpgt(_VREG(19), _VREG(29), _VREG(23));
   __vcop_vand(_VREG(20), _VREG(22), _VREG(16));
   __vcop_vand(_VREG(21), _VREG(23), _VREG(17));
   __vcop_vstore(__vcop_predicate(_VREG(16)), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(26), _PREG(14), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_predicate(_VREG(17)), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(26), _PREG(16), _AGEN(1), _PREG(0));
   __vcop_vloop_end(3u);

}

void vcop_nonMaxSuppress_mxn_32s(
   __vptr_int32 im_A,
   __vptr_uint8 out_B,
   __vptr_int32 scratch_B,
   __vptr_int32 scratch_C,
   int width,
   int height,
   int input_stride,
   int output_stride,
   int m,
   int n,
   int thresh)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_nonMaxSuppress_mxn_32s_init(im_A, out_B, scratch_B, scratch_C, width, height, input_stride, output_stride, m, n, thresh, __pblock_vcop_nonMaxSuppress_mxn_32s);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_nonMaxSuppress_mxn_32s_vloops(__pblock_vcop_nonMaxSuppress_mxn_32s);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_nonMaxSuppress_mxn_32s_custom(
   __vptr_int32 im_A,
   __vptr_uint8 out_B,
   __vptr_int32 scratch_B,
   __vptr_int32 scratch_C,
   int width,
   int height,
   int input_stride,
   int output_stride,
   int m,
   int n,
   int thresh,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_nonMaxSuppress_mxn_32s_init(im_A, out_B, scratch_B, scratch_C, width, height, input_stride, output_stride, m, n, thresh, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_nonMaxSuppress_mxn_32s_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_nonMaxSuppress_mxn_32s_bitPack, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_nonMaxSuppress_mxn_32s_bitPack, __ALIGNOF__(int));
unsigned short __pblock_vcop_nonMaxSuppress_mxn_32s_bitPack[68];

unsigned int vcop_nonMaxSuppress_mxn_32s_bitPack_param_count(void)
{
   return 68u;
}

unsigned int vcop_nonMaxSuppress_mxn_32s_bitPack_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_nonMaxSuppress_mxn_32s_bitPack_init(
   __vptr_int32 im_A,
   __vptr_uint8 out_B,
   __vptr_int32 scratch_B,
   __vptr_int32 scratch_C,
   int width,
   int height,
   int input_stride,
   int output_stride,
   int windowWidth,
   int windowHeight,
   int thresh,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (height - windowHeight + 1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (((width + 2*(8u)-1) & ~(2*(8u)-1))/ (2 * (8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((windowHeight - 1))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)im_A+input_stride*sizeof(*im_A));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)im_A+input_stride*sizeof(*im_A)+sizeof(*im_A)*8u);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)scratch_B);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)scratch_B+sizeof(*im_A)*8u);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), 64);
   __vcop_pblock_init16(pblock, __offset+_PREG(15), (input_stride*sizeof(*im_A)) -((sizeof(*im_A)*8u)*2)*((((width + 2*(8u)-1) & ~(2*(8u)-1))/ (2 * (8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(16), (width*sizeof(*im_A)) -((sizeof(*im_A)*8u)*2)*((((width + 2*(8u)-1) & ~(2*(8u)-1))/ (2 * (8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(17), (input_stride*sizeof(*im_A)));
   __vcop_pblock_init16(pblock, __offset+_PREG(18), ((sizeof(*im_A)*8u)*2) -(input_stride*sizeof(*im_A))*(((windowHeight - 1))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(19), (input_stride*sizeof(*im_A)) -((sizeof(*im_A)*8u)*2)*((((width + 2*(8u)-1) & ~(2*(8u)-1))/ (2 * (8u)))-1u) -(input_stride*sizeof(*im_A))*(((windowHeight - 1))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)im_A);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)im_A+sizeof(*im_A)*8u);
   __offset += 22;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), ((height - windowHeight + 2)/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((((width - windowWidth + 1) + (8u)-1) & ~((8u)-1))/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((windowWidth - 1))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)scratch_B+sizeof(*im_A));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)scratch_B+width*sizeof(*im_A)+sizeof(*im_A));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)scratch_C);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)scratch_C+sizeof(*im_A)*width);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(15), (sizeof(*im_A)*width*2) -((sizeof(*im_A)*8u))*(((((width - windowWidth + 1) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(16), 4);
   __vcop_pblock_init16(pblock, __offset+_PREG(17), ((sizeof(*im_A)*8u)) -(sizeof(*im_A))*(((windowWidth - 1))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(18), (2*width*sizeof(*im_A)) -((sizeof(*im_A)*8u))*(((((width - windowWidth + 1) + (8u)-1) & ~((8u)-1))/(8u))-1u) -(sizeof(*im_A))*(((windowWidth - 1))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)scratch_B);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)scratch_B+sizeof(*im_A)*width);
   __offset += 22;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((height-windowHeight+2)/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((width-windowWidth+(8u))/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)im_A+(windowHeight-1)/2*input_stride*sizeof(*im_A)+(windowWidth-1)/2*sizeof(*im_A));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)im_A+(windowHeight-1)/2*input_stride*sizeof(*im_A)+(windowWidth-1)/2*sizeof(*im_A)+input_stride*sizeof(*im_A));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)scratch_C);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)scratch_C+width*sizeof(*im_A));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)out_B);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)out_B+output_stride*sizeof(*out_B));
   __vcop_pblock_init16(pblock, __offset+_PREG(18), (2*output_stride*sizeof(*out_B)) -(sizeof(*out_B))*(((width-windowWidth+(8u))/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(19), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(20), (2*input_stride*sizeof(*im_A)) -((sizeof(*im_A)*8u))*(((width-windowWidth+(8u))/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(21), (2*width*sizeof(*im_A)) -((sizeof(*im_A)*8u))*(((width-windowWidth+(8u))/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(22), thresh);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), 1);
   __offset += 24;

   return 68u;
}

void vcop_nonMaxSuppress_mxn_32s_bitPack_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("C0", 16);
   #pragma VCC_VREG("C1", 17);
   #pragma VCC_VREG("I0", 18);
   #pragma VCC_VREG("I1", 19);
   #pragma VCC_VREG("Ieqmax0", 20);
   #pragma VCC_VREG("Ieqmax1", 21);
   #pragma VCC_VREG("Igtthr0", 22);
   #pragma VCC_VREG("Igtthr1", 23);
   #pragma VCC_VREG("K1", 24);
   #pragma VCC_VREG("R0", 25);
   #pragma VCC_VREG("R1", 26);
   #pragma VCC_VREG("Rthr", 27);
   #pragma VCC_VREG("max0", 28);
   #pragma VCC_VREG("max1", 29);
   #pragma VCC_VREG("maxs", 30);
   #pragma VCC_VREG("maxsp", 31);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addrIn", "A0");
   #pragma EVE_REG("addrOut", "A1");
   #pragma EVE_REG("Addr0", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("i", "I2");
   #pragma EVE_REG("j", "I3");
   #pragma EVE_REG("k", "I4");
   

   __vcop_vloop(__vcop_compute(), 12u, 11u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(14), _PREG(15), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(14), _PREG(16), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(17), _PREG(18), _PREG(19), _PREG(0));
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(20), _AGEN(0), _VREG(30), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(22), _AGEN(0), _VREG(31), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(6), _AGEN(2), _VREG(25), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(8), _AGEN(2), _VREG(26), __vcop_alws());
   __vcop_vmax(_VREG(25), _VREG(30), _VREG(30));
   __vcop_vmax(_VREG(26), _VREG(31), _VREG(31));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_last_i4(), _VREG(30), _PREG(10), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_last_i4(), _VREG(31), _PREG(12), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addrInOut", "A0");
   #pragma EVE_REG("Addr0", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("i", "I2");
   #pragma EVE_REG("j", "I3");
   #pragma EVE_REG("k", "I4");
   

   __vcop_vloop(__vcop_compute(), 11u, 11u, 2u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(14), _PREG(15), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(16), _PREG(17), _PREG(18), _PREG(0));
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(20), _AGEN(0), _VREG(28), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(22), _AGEN(0), _VREG(29), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(6), _AGEN(1), _VREG(18), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(8), _AGEN(1), _VREG(19), __vcop_alws());
   __vcop_vmax(_VREG(18), _VREG(28), _VREG(28));
   __vcop_vmax(_VREG(19), _VREG(29), _VREG(29));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_last_i4(), _VREG(28), _PREG(10), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_last_i4(), _VREG(29), _PREG(12), _AGEN(0), _PREG(0));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("binaryMask1", 32);
   #pragma VCC_VREG("binaryMask2", 33);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addrBinPack", "A0");
   #pragma EVE_REG("addrInData", "A1");
   #pragma EVE_REG("addrMaxVal", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("i", "I3");
   #pragma EVE_REG("j", "I4");
   

   __vcop_vloop(__vcop_compute(), 20u, 12u, 3u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(22), _VREG(27));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(24), _VREG(24));
   __vcop_vagen(_AGEN(0), _PREG(1), _PREG(18), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(19), _PREG(20), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(19), _PREG(21), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(6), _AGEN(1), _VREG(18), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(8), _AGEN(1), _VREG(19), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(10), _AGEN(2), _VREG(28), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(12), _AGEN(2), _VREG(29), __vcop_alws());
   __vcop_vcmpeq(_VREG(18), _VREG(28), _VREG(20));
   __vcop_vcmpeq(_VREG(19), _VREG(29), _VREG(21));
   __vcop_vcmpgt(_VREG(18), _VREG(27), _VREG(22));
   __vcop_vcmpgt(_VREG(19), _VREG(27), _VREG(23));
   __vcop_vand(_VREG(20), _VREG(22), _VREG(16));
   __vcop_vand(_VREG(21), _VREG(23), _VREG(17));
   __vcop_vbitpk(_VREG(16), _VREG(24), _VREG(32));
   __vcop_vbitpk(_VREG(17), _VREG(24), _VREG(33));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_1pt(), __vcop_alws(), _VREG(32), _PREG(14), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_1pt(), __vcop_alws(), _VREG(33), _PREG(16), _AGEN(0), _PREG(0));
   __vcop_vloop_end(3u);

}

void vcop_nonMaxSuppress_mxn_32s_bitPack(
   __vptr_int32 im_A,
   __vptr_uint8 out_B,
   __vptr_int32 scratch_B,
   __vptr_int32 scratch_C,
   int width,
   int height,
   int input_stride,
   int output_stride,
   int windowWidth,
   int windowHeight,
   int thresh)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_nonMaxSuppress_mxn_32s_bitPack_init(im_A, out_B, scratch_B, scratch_C, width, height, input_stride, output_stride, windowWidth, windowHeight, thresh, __pblock_vcop_nonMaxSuppress_mxn_32s_bitPack);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_nonMaxSuppress_mxn_32s_bitPack_vloops(__pblock_vcop_nonMaxSuppress_mxn_32s_bitPack);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_nonMaxSuppress_mxn_32s_bitPack_custom(
   __vptr_int32 im_A,
   __vptr_uint8 out_B,
   __vptr_int32 scratch_B,
   __vptr_int32 scratch_C,
   int width,
   int height,
   int input_stride,
   int output_stride,
   int windowWidth,
   int windowHeight,
   int thresh,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_nonMaxSuppress_mxn_32s_bitPack_init(im_A, out_B, scratch_B, scratch_C, width, height, input_stride, output_stride, windowWidth, windowHeight, thresh, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_nonMaxSuppress_mxn_32s_bitPack_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

