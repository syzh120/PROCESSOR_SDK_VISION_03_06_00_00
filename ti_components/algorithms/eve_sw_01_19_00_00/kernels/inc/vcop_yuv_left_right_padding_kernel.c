#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_yuv_left_right_padding_u8, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_yuv_left_right_padding_u8, __ALIGNOF__(int));
unsigned short __pblock_vcop_yuv_left_right_padding_u8[14];

unsigned int vcop_yuv_left_right_padding_u8_param_count(void)
{
   return 14u;
}

unsigned int vcop_yuv_left_right_padding_u8_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_yuv_left_right_padding_u8_init(
   __vptr_uint8 in_left_A,
   __vptr_uint8 in_right_B,
   __vptr_uint8 out_left_A,
   __vptr_uint8 out_right_B,
   unsigned short width,
   unsigned short height,
   unsigned short out_stride,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (height)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((width + (8u) - 1)/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)out_left_A);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)out_right_B);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), (out_stride) -(8u)*(((width + (8u) - 1)/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)in_left_A);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)in_right_B);
   __offset += 14;

   return 14u;
}

void vcop_yuv_left_right_padding_u8_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("vin_left", 16);
   #pragma VCC_VREG("vin_right", 17);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_in", "A0");
   #pragma EVE_REG("Addr_out", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 7u, 7u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(1), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(10), _PREG(11), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_1pt(), _PREG(12), _AGEN(0), _VREG(16), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeBU(), __vcop_1pt(), _PREG(14), _AGEN(0), _VREG(17), __vcop_i4_zero());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(16), _PREG(6), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(17), _PREG(8), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_yuv_left_right_padding_u8(
   __vptr_uint8 in_left_A,
   __vptr_uint8 in_right_B,
   __vptr_uint8 out_left_A,
   __vptr_uint8 out_right_B,
   unsigned short width,
   unsigned short height,
   unsigned short out_stride)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_yuv_left_right_padding_u8_init(in_left_A, in_right_B, out_left_A, out_right_B, width, height, out_stride, __pblock_vcop_yuv_left_right_padding_u8);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_yuv_left_right_padding_u8_vloops(__pblock_vcop_yuv_left_right_padding_u8);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_yuv_left_right_padding_u8_custom(
   __vptr_uint8 in_left_A,
   __vptr_uint8 in_right_B,
   __vptr_uint8 out_left_A,
   __vptr_uint8 out_right_B,
   unsigned short width,
   unsigned short height,
   unsigned short out_stride,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_yuv_left_right_padding_u8_init(in_left_A, in_right_B, out_left_A, out_right_B, width, height, out_stride, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_yuv_left_right_padding_u8_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_yuv_left_right_padding_u16, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_yuv_left_right_padding_u16, __ALIGNOF__(int));
unsigned short __pblock_vcop_yuv_left_right_padding_u16[16];

unsigned int vcop_yuv_left_right_padding_u16_param_count(void)
{
   return 16u;
}

unsigned int vcop_yuv_left_right_padding_u16_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_yuv_left_right_padding_u16_init(
   __vptr_uint16 in_left_A,
   __vptr_uint16 in_right_B,
   __vptr_uint16 out_left_A,
   __vptr_uint16 out_right_B,
   unsigned short width,
   unsigned short height,
   unsigned short out_stride,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (height)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((width + (8u) - 1)/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)out_left_A);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)out_right_B);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 2);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), (out_stride*2) -(8u*2)*(((width + (8u) - 1)/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)in_left_A);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)in_right_B);
   __offset += 16;

   return 16u;
}

void vcop_yuv_left_right_padding_u16_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("vin_left", 16);
   #pragma VCC_VREG("vin_right", 17);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_in", "A0");
   #pragma EVE_REG("Addr_out", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 7u, 8u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(10), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(11), _PREG(12), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(14), _AGEN(0), _VREG(16), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(16), _AGEN(0), _VREG(17), __vcop_i4_zero());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(16), _PREG(6), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(17), _PREG(8), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_yuv_left_right_padding_u16(
   __vptr_uint16 in_left_A,
   __vptr_uint16 in_right_B,
   __vptr_uint16 out_left_A,
   __vptr_uint16 out_right_B,
   unsigned short width,
   unsigned short height,
   unsigned short out_stride)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_yuv_left_right_padding_u16_init(in_left_A, in_right_B, out_left_A, out_right_B, width, height, out_stride, __pblock_vcop_yuv_left_right_padding_u16);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_yuv_left_right_padding_u16_vloops(__pblock_vcop_yuv_left_right_padding_u16);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_yuv_left_right_padding_u16_custom(
   __vptr_uint16 in_left_A,
   __vptr_uint16 in_right_B,
   __vptr_uint16 out_left_A,
   __vptr_uint16 out_right_B,
   unsigned short width,
   unsigned short height,
   unsigned short out_stride,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_yuv_left_right_padding_u16_init(in_left_A, in_right_B, out_left_A, out_right_B, width, height, out_stride, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_yuv_left_right_padding_u16_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

