#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_yuv_422uyvy_to_420nv12, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_yuv_422uyvy_to_420nv12, __ALIGNOF__(int));
unsigned short __pblock_vcop_yuv_422uyvy_to_420nv12[20];

unsigned int vcop_yuv_422uyvy_to_420nv12_param_count(void)
{
   return 20u;
}

unsigned int vcop_yuv_422uyvy_to_420nv12_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_yuv_422uyvy_to_420nv12_init(
   __vptr_uint8 in_img_A,
   __vptr_uint8 out_B,
   unsigned short width,
   unsigned short height,
   unsigned short in_stride,
   unsigned short out_stride,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (height/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((2*width + (2 * (8u)) - 1)/(2 * (8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_ROUND,1));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 16);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)out_B);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)out_B+out_stride);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)out_B+height*out_stride);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), (2*in_stride) -((2*8u))*(((2*width + (2 * (8u)) - 1)/(2 * (8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(15), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(16), (out_stride) -(8u)*(((2*width + (2 * (8u)) - 1)/(2 * (8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(17), (2*out_stride) -(8u)*(((2*width + (2 * (8u)) - 1)/(2 * (8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)in_img_A);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)in_img_A+in_stride);
   __offset += 20;

   return 20u;
}

void vcop_yuv_422uyvy_to_420nv12_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vuv", 16);
   #pragma VCC_VREG("Vuv1", 17);
   #pragma VCC_VREG("Vuv2", 18);
   #pragma VCC_VREG("Vy1", 19);
   #pragma VCC_VREG("Vy2", 20);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_in", "A0");
   #pragma EVE_REG("Addr_out_uv", "A1");
   #pragma EVE_REG("Addr_out_y", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 10u, 10u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(14), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(15), _PREG(16), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(15), _PREG(17), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(18), _AGEN(0), _VPAIR(17,19), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(20), _AGEN(0), _VPAIR(18,20), __vcop_alws());
   __vcop_vadd(_VREG(17), _VREG(18), _VREG(16));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(19), _PREG(8), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(20), _PREG(10), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(16), _PREG(12), _AGEN(1), _PREG(6));
   __vcop_vloop_end(1u);

}

void vcop_yuv_422uyvy_to_420nv12(
   __vptr_uint8 in_img_A,
   __vptr_uint8 out_B,
   unsigned short width,
   unsigned short height,
   unsigned short in_stride,
   unsigned short out_stride)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_yuv_422uyvy_to_420nv12_init(in_img_A, out_B, width, height, in_stride, out_stride, __pblock_vcop_yuv_422uyvy_to_420nv12);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_yuv_422uyvy_to_420nv12_vloops(__pblock_vcop_yuv_422uyvy_to_420nv12);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_yuv_422uyvy_to_420nv12_custom(
   __vptr_uint8 in_img_A,
   __vptr_uint8 out_B,
   unsigned short width,
   unsigned short height,
   unsigned short in_stride,
   unsigned short out_stride,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_yuv_422uyvy_to_420nv12_init(in_img_A, out_B, width, height, in_stride, out_stride, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_yuv_422uyvy_to_420nv12_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

