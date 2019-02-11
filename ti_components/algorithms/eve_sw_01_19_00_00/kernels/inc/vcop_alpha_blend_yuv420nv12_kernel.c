#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_alpha_blend_yuv420nv12, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_alpha_blend_yuv420nv12, __ALIGNOF__(int));
unsigned short __pblock_vcop_alpha_blend_yuv420nv12[38];

unsigned int vcop_alpha_blend_yuv420nv12_param_count(void)
{
   return 38u;
}

unsigned int vcop_alpha_blend_yuv420nv12_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_alpha_blend_yuv420nv12_init(
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
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((width + (2 * (8u)) - 1)/(2 * (8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_TRUNC,4));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 16);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)in_img2_X);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)alphaFrame_X);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)out_X);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), (width) -((2*8u))*(((width + (2 * (8u)) - 1)/(2 * (8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(15), (in_img1_stride) -((2*8u))*(((width + (2 * (8u)) - 1)/(2 * (8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(16), (in_img2_stride) -((2*8u))*(((width + (2 * (8u)) - 1)/(2 * (8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(17), (out_stride) -((2*8u))*(((width + (2 * (8u)) - 1)/(2 * (8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), 16);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)in_img1_X);
   __offset += 20;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (height/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((width + (2 * (8u)) - 1)/(2 * (8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_TRUNC,4));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 16);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)alphaFrame_X);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)out_X+height*out_stride);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), (2*width) -((2*8u))*(((width + (2 * (8u)) - 1)/(2 * (8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(13), (in_img1_stride) -((2*8u))*(((width + (2 * (8u)) - 1)/(2 * (8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(14), (in_img2_stride) -((2*8u))*(((width + (2 * (8u)) - 1)/(2 * (8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(15), (out_stride) -((2*8u))*(((width + (2 * (8u)) - 1)/(2 * (8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)in_img1_X+height*in_img1_stride);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)in_img2_X+height*in_img2_stride);
   __offset += 18;

   return 38u;
}

void vcop_alpha_blend_yuv420nv12_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("V16", 16);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Valpha_e", 17);
   #pragma VCC_VREG("Valpha_o", 18);
   #pragma VCC_VREG("Vy1_e", 19);
   #pragma VCC_VREG("Vy1_o", 20);
   #pragma VCC_VREG("Vy2_e", 21);
   #pragma VCC_VREG("Vy2_o", 22);
   #pragma VCC_VREG("Vy_e", 23);
   #pragma VCC_VREG("Vy_o", 24);
   #pragma VCC_VREG("dy_e", 25);
   #pragma VCC_VREG("dy_o", 26);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_alpha", "A0");
   #pragma EVE_REG("Addr_in1", "A1");
   #pragma EVE_REG("Addr_in2", "A2");
   #pragma EVE_REG("Addr_out", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 16u, 10u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(18), _VREG(16));
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(14), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(15), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(7), _PREG(16), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(7), _PREG(17), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(20), _AGEN(1), _VPAIR(19,20), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(8), _AGEN(2), _VPAIR(21,22), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(10), _AGEN(0), _VPAIR(17,18), __vcop_alws());
   __vcop_vsub(_VREG(19), _VREG(21), _VREG(25));
   __vcop_vsub(_VREG(20), _VREG(22), _VREG(26));
   __vcop_vmpy(_VREG(17), _VREG(25), _VREG(23), _PREG(0));
   __vcop_vmpy(_VREG(18), _VREG(26), _VREG(24), _PREG(0));
   __vcop_vmadd(_VREG(21), _VREG(16), _VREG(23), _PREG(0));
   __vcop_vmadd(_VREG(22), _VREG(16), _VREG(24), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(23,24), _PREG(12), _AGEN(3), _PREG(6));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Valpha_e", 27);
   #pragma VCC_VREG("Valpha_o", 28);
   #pragma VCC_VREG("Vuv1_e", 29);
   #pragma VCC_VREG("Vuv1_o", 30);
   #pragma VCC_VREG("Vuv2_e", 31);
   #pragma VCC_VREG("Vuv2_o", 32);
   #pragma VCC_VREG("Vuv_e", 33);
   #pragma VCC_VREG("Vuv_o", 34);
   #pragma VCC_VREG("dy_e", 35);
   #pragma VCC_VREG("dy_o", 36);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_alpha", "A0");
   #pragma EVE_REG("Addr_in1", "A1");
   #pragma EVE_REG("Addr_in2", "A2");
   #pragma EVE_REG("Addr_out", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 15u, 9u, 2u);
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(12), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(13), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(7), _PREG(14), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(7), _PREG(15), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(16), _AGEN(1), _VPAIR(29,30), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(18), _AGEN(2), _VPAIR(31,32), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(8), _AGEN(0), _VPAIR(27,28), __vcop_alws());
   __vcop_vsub(_VREG(29), _VREG(31), _VREG(35));
   __vcop_vsub(_VREG(30), _VREG(32), _VREG(36));
   __vcop_vmpy(_VREG(27), _VREG(35), _VREG(33), _PREG(0));
   __vcop_vmpy(_VREG(28), _VREG(36), _VREG(34), _PREG(0));
   __vcop_vmadd(_VREG(31), _VREG(16), _VREG(33), _PREG(0));
   __vcop_vmadd(_VREG(32), _VREG(16), _VREG(34), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(33,34), _PREG(10), _AGEN(3), _PREG(6));
   __vcop_vloop_end(2u);

}

void vcop_alpha_blend_yuv420nv12(
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
   vcop_alpha_blend_yuv420nv12_init(in_img1_X, in_img2_X, alphaFrame_X, out_X, width, height, in_img1_stride, in_img2_stride, out_stride, __pblock_vcop_alpha_blend_yuv420nv12);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_alpha_blend_yuv420nv12_vloops(__pblock_vcop_alpha_blend_yuv420nv12);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_alpha_blend_yuv420nv12_custom(
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
   vcop_alpha_blend_yuv420nv12_init(in_img1_X, in_img2_X, alphaFrame_X, out_X, width, height, in_img1_stride, in_img2_stride, out_stride, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_alpha_blend_yuv420nv12_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

