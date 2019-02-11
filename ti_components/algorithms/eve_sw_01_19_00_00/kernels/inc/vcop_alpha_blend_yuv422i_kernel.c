#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_alpha_blend_yuv422i, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_alpha_blend_yuv422i, __ALIGNOF__(int));
unsigned short __pblock_vcop_alpha_blend_yuv422i[22];

unsigned int vcop_alpha_blend_yuv422i_param_count(void)
{
   return 22u;
}

unsigned int vcop_alpha_blend_yuv422i_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_alpha_blend_yuv422i_init(
   __vptr_uint8 in_img1_X,
   __vptr_uint8 in_img2_X,
   __vptr_uint8 alphaFrame_X,
   __vptr_uint8 out_X,
   unsigned short width,
   unsigned short height,
   unsigned short in_img1_stride,
   unsigned short in_img2_stride,
   unsigned short out_stride,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (height)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((2*width + (2 * (8u)) - 1)/(2 * (8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_TRUNC,4));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 8);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)in_img2_X);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)alphaFrame_X);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)out_X);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), (width) -(8u)*(((2*width + (2 * (8u)) - 1)/(2 * (8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(15), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(16), (in_img1_stride) -((2*8u))*(((2*width + (2 * (8u)) - 1)/(2 * (8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(17), (in_img2_stride) -((2*8u))*(((2*width + (2 * (8u)) - 1)/(2 * (8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(18), (out_stride) -((2*8u))*(((2*width + (2 * (8u)) - 1)/(2 * (8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), 16);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)in_img1_X);
   __offset += 22;

   return 22u;
}

void vcop_alpha_blend_yuv422i_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("V16", 16);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Valpha", 17);
   #pragma VCC_VREG("Vuv", 18);
   #pragma VCC_VREG("Vuv1", 19);
   #pragma VCC_VREG("Vuv2", 20);
   #pragma VCC_VREG("Vy", 21);
   #pragma VCC_VREG("Vy1", 22);
   #pragma VCC_VREG("Vy2", 23);
   #pragma VCC_VREG("duv", 24);
   #pragma VCC_VREG("dy", 25);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_alpha", "A0");
   #pragma EVE_REG("Addr_in1", "A1");
   #pragma EVE_REG("Addr_in2", "A2");
   #pragma EVE_REG("Addr_out", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 16u, 11u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(20), _VREG(16));
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(14), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(15), _PREG(16), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(15), _PREG(17), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(15), _PREG(18), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(22), _AGEN(1), _VPAIR(19,22), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(8), _AGEN(2), _VPAIR(20,23), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(10), _AGEN(0), _VREG(17), __vcop_alws());
   __vcop_vsub(_VREG(22), _VREG(23), _VREG(25));
   __vcop_vsub(_VREG(19), _VREG(20), _VREG(24));
   __vcop_vmpy(_VREG(17), _VREG(24), _VREG(18), _PREG(0));
   __vcop_vmpy(_VREG(17), _VREG(25), _VREG(21), _PREG(0));
   __vcop_vmadd(_VREG(20), _VREG(16), _VREG(18), _PREG(0));
   __vcop_vmadd(_VREG(23), _VREG(16), _VREG(21), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(18,21), _PREG(12), _AGEN(3), _PREG(6));
   __vcop_vloop_end(1u);

}

void vcop_alpha_blend_yuv422i(
   __vptr_uint8 in_img1_X,
   __vptr_uint8 in_img2_X,
   __vptr_uint8 alphaFrame_X,
   __vptr_uint8 out_X,
   unsigned short width,
   unsigned short height,
   unsigned short in_img1_stride,
   unsigned short in_img2_stride,
   unsigned short out_stride)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_alpha_blend_yuv422i_init(in_img1_X, in_img2_X, alphaFrame_X, out_X, width, height, in_img1_stride, in_img2_stride, out_stride, __pblock_vcop_alpha_blend_yuv422i);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_alpha_blend_yuv422i_vloops(__pblock_vcop_alpha_blend_yuv422i);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_alpha_blend_yuv422i_custom(
   __vptr_uint8 in_img1_X,
   __vptr_uint8 in_img2_X,
   __vptr_uint8 alphaFrame_X,
   __vptr_uint8 out_X,
   unsigned short width,
   unsigned short height,
   unsigned short in_img1_stride,
   unsigned short in_img2_stride,
   unsigned short out_stride,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_alpha_blend_yuv422i_init(in_img1_X, in_img2_X, alphaFrame_X, out_X, width, height, in_img1_stride, in_img2_stride, out_stride, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_alpha_blend_yuv422i_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

