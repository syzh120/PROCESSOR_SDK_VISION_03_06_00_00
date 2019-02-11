#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_rgb_to_yuv_UYVY, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_rgb_to_yuv_UYVY, __ALIGNOF__(int));
unsigned short __pblock_rgb_to_yuv_UYVY[32];

unsigned int rgb_to_yuv_UYVY_param_count(void)
{
   return 32u;
}

unsigned int rgb_to_yuv_UYVY_ctrl_count(void)
{
   return 0u;
}

unsigned int rgb_to_yuv_UYVY_init(
   __vptr_uint16 iPtrR,
   __vptr_uint16 iPtrG,
   __vptr_uint16 iPtrB,
   unsigned short blk_w,
   unsigned short blk_h,
   unsigned short in_stride,
   short coefs_r,
   short coefs_g,
   short coefs_b,
   __vptr_int16 rgb2yuv_coefs,
   unsigned int roundingFactor,
   unsigned short shift_val,
   __vptr_uint8 iPtrOut,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   const int preg_ref1 = _PREG(26);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (blk_h)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((blk_w/(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_SYMM,preg_ref1,RM_TRUNC,shift_val));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 128);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), coefs_b);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)rgb2yuv_coefs+6);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)rgb2yuv_coefs+10);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)rgb2yuv_coefs+14);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), roundingFactor);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)iPtrR);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)iPtrG);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)iPtrB);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)iPtrOut);
   __vcop_pblock_init16(pblock, __offset+_PREG(26), 255);
   __vcop_pblock_init16(pblock, __offset+_PREG(27), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(28), (in_stride*sizeof(*iPtrR)) -((8u*sizeof(*iPtrR)))*(((blk_w/(8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(29), (blk_w*2*sizeof(*iPtrOut)) -((2*8u*sizeof(*iPtrOut)))*(((blk_w/(8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(30), coefs_r);
   __vcop_pblock_init32(pblock, __offset+_PREG(32), coefs_g);
   __offset += 32;

   return 32u;
}

void rgb_to_yuv_UYVY_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vblu", 16);
   #pragma VCC_VREG("Vbu_bv0", 17);
   #pragma VCC_VREG("Vby0", 18);
   #pragma VCC_VREG("Vgrn", 19);
   #pragma VCC_VREG("Vgu_gv0", 20);
   #pragma VCC_VREG("Vgy0", 21);
   #pragma VCC_VREG("Vred", 22);
   #pragma VCC_VREG("Vru_rv0", 23);
   #pragma VCC_VREG("Vry0", 24);
   #pragma VCC_VREG("Vuv0", 25);
   #pragma VCC_VREG("Vy0", 26);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_c", "A0");
   #pragma EVE_REG("Addr_in", "A1");
   #pragma EVE_REG("Addr_out", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I0", "I3");
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 22u, 16u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(30), _VREG(24));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(32), _VREG(21));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(8), _VREG(18));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(16), _VREG(25));
   __vcop_vinit(__vcop_sizeHU(), __vcop_alws(), _PREG(7), _VREG(26));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(27), _PREG(28), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(27), _PREG(29), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_circ2(), _PREG(10), _AGEN(0), _VREG(23), __vcop_once());
   __vcop_vload(__vcop_sizeH(), __vcop_circ2(), _PREG(12), _AGEN(0), _VREG(20), __vcop_once());
   __vcop_vload(__vcop_sizeH(), __vcop_circ2(), _PREG(14), _AGEN(0), _VREG(17), __vcop_once());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(18), _AGEN(1), _VREG(22), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(20), _AGEN(1), _VREG(19), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(22), _AGEN(1), _VREG(16), __vcop_alws());
   __vcop_vmadd(_VREG(24), _VREG(22), _VREG(26), _PREG(0));
   __vcop_vmadd(_VREG(23), _VREG(22), _VREG(25), _PREG(0));
   __vcop_vmadd(_VREG(21), _VREG(19), _VREG(26), _PREG(0));
   __vcop_vmadd(_VREG(20), _VREG(19), _VREG(25), _PREG(0));
   __vcop_vmadd(_VREG(18), _VREG(16), _VREG(26), _PREG(0));
   __vcop_vmadd(_VREG(17), _VREG(16), _VREG(25), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(25,26), _PREG(24), _AGEN(2), _PREG(6));
   __vcop_vloop_end(1u);

}

void rgb_to_yuv_UYVY(
   __vptr_uint16 iPtrR,
   __vptr_uint16 iPtrG,
   __vptr_uint16 iPtrB,
   unsigned short blk_w,
   unsigned short blk_h,
   unsigned short in_stride,
   short coefs_r,
   short coefs_g,
   short coefs_b,
   __vptr_int16 rgb2yuv_coefs,
   unsigned int roundingFactor,
   unsigned short shift_val,
   __vptr_uint8 iPtrOut)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   rgb_to_yuv_UYVY_init(iPtrR, iPtrG, iPtrB, blk_w, blk_h, in_stride, coefs_r, coefs_g, coefs_b, rgb2yuv_coefs, roundingFactor, shift_val, iPtrOut, __pblock_rgb_to_yuv_UYVY);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   rgb_to_yuv_UYVY_vloops(__pblock_rgb_to_yuv_UYVY);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void rgb_to_yuv_UYVY_custom(
   __vptr_uint16 iPtrR,
   __vptr_uint16 iPtrG,
   __vptr_uint16 iPtrB,
   unsigned short blk_w,
   unsigned short blk_h,
   unsigned short in_stride,
   short coefs_r,
   short coefs_g,
   short coefs_b,
   __vptr_int16 rgb2yuv_coefs,
   unsigned int roundingFactor,
   unsigned short shift_val,
   __vptr_uint8 iPtrOut,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   rgb_to_yuv_UYVY_init(iPtrR, iPtrG, iPtrB, blk_w, blk_h, in_stride, coefs_r, coefs_g, coefs_b, rgb2yuv_coefs, roundingFactor, shift_val, iPtrOut, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   rgb_to_yuv_UYVY_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_rgb_to_yuv_YUYV, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_rgb_to_yuv_YUYV, __ALIGNOF__(int));
unsigned short __pblock_rgb_to_yuv_YUYV[32];

unsigned int rgb_to_yuv_YUYV_param_count(void)
{
   return 32u;
}

unsigned int rgb_to_yuv_YUYV_ctrl_count(void)
{
   return 0u;
}

unsigned int rgb_to_yuv_YUYV_init(
   __vptr_uint16 iPtrR,
   __vptr_uint16 iPtrG,
   __vptr_uint16 iPtrB,
   unsigned short blk_w,
   unsigned short blk_h,
   unsigned short in_stride,
   short coefs_r,
   short coefs_g,
   short coefs_b,
   __vptr_int16 coefs,
   unsigned int roundingFactor,
   unsigned short shift_val,
   __vptr_uint8 iPtrOut,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   const int preg_ref2 = _PREG(26);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (blk_h)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((blk_w/(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_SYMM,preg_ref2,RM_TRUNC,shift_val));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 128);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), coefs_b);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)coefs+6);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)coefs+10);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)coefs+14);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), roundingFactor);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)iPtrR);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)iPtrG);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)iPtrB);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)iPtrOut);
   __vcop_pblock_init16(pblock, __offset+_PREG(26), 255);
   __vcop_pblock_init16(pblock, __offset+_PREG(27), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(28), (in_stride*sizeof(*iPtrR)) -((8u*sizeof(*iPtrR)))*(((blk_w/(8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(29), (blk_w*2*sizeof(*iPtrOut)) -((2*8u*sizeof(*iPtrOut)))*(((blk_w/(8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(30), coefs_r);
   __vcop_pblock_init32(pblock, __offset+_PREG(32), coefs_g);
   __offset += 32;

   return 32u;
}

void rgb_to_yuv_YUYV_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vblu", 16);
   #pragma VCC_VREG("Vbu_bv0", 17);
   #pragma VCC_VREG("Vby0", 18);
   #pragma VCC_VREG("Vgrn", 19);
   #pragma VCC_VREG("Vgu_gv0", 20);
   #pragma VCC_VREG("Vgy0", 21);
   #pragma VCC_VREG("Vred", 22);
   #pragma VCC_VREG("Vru_rv0", 23);
   #pragma VCC_VREG("Vry0", 24);
   #pragma VCC_VREG("Vuv0", 25);
   #pragma VCC_VREG("Vy0", 26);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_c", "A0");
   #pragma EVE_REG("Addr_in", "A1");
   #pragma EVE_REG("Addr_out", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I0", "I3");
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 22u, 16u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(30), _VREG(24));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(32), _VREG(21));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(8), _VREG(18));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(16), _VREG(25));
   __vcop_vinit(__vcop_sizeHU(), __vcop_alws(), _PREG(7), _VREG(26));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(27), _PREG(28), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(27), _PREG(29), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_circ2(), _PREG(10), _AGEN(0), _VREG(23), __vcop_once());
   __vcop_vload(__vcop_sizeH(), __vcop_circ2(), _PREG(12), _AGEN(0), _VREG(20), __vcop_once());
   __vcop_vload(__vcop_sizeH(), __vcop_circ2(), _PREG(14), _AGEN(0), _VREG(17), __vcop_once());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(18), _AGEN(1), _VREG(22), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(20), _AGEN(1), _VREG(19), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(22), _AGEN(1), _VREG(16), __vcop_alws());
   __vcop_vmadd(_VREG(24), _VREG(22), _VREG(26), _PREG(0));
   __vcop_vmadd(_VREG(23), _VREG(22), _VREG(25), _PREG(0));
   __vcop_vmadd(_VREG(21), _VREG(19), _VREG(26), _PREG(0));
   __vcop_vmadd(_VREG(20), _VREG(19), _VREG(25), _PREG(0));
   __vcop_vmadd(_VREG(18), _VREG(16), _VREG(26), _PREG(0));
   __vcop_vmadd(_VREG(17), _VREG(16), _VREG(25), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(26,25), _PREG(24), _AGEN(2), _PREG(6));
   __vcop_vloop_end(1u);

}

void rgb_to_yuv_YUYV(
   __vptr_uint16 iPtrR,
   __vptr_uint16 iPtrG,
   __vptr_uint16 iPtrB,
   unsigned short blk_w,
   unsigned short blk_h,
   unsigned short in_stride,
   short coefs_r,
   short coefs_g,
   short coefs_b,
   __vptr_int16 coefs,
   unsigned int roundingFactor,
   unsigned short shift_val,
   __vptr_uint8 iPtrOut)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   rgb_to_yuv_YUYV_init(iPtrR, iPtrG, iPtrB, blk_w, blk_h, in_stride, coefs_r, coefs_g, coefs_b, coefs, roundingFactor, shift_val, iPtrOut, __pblock_rgb_to_yuv_YUYV);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   rgb_to_yuv_YUYV_vloops(__pblock_rgb_to_yuv_YUYV);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void rgb_to_yuv_YUYV_custom(
   __vptr_uint16 iPtrR,
   __vptr_uint16 iPtrG,
   __vptr_uint16 iPtrB,
   unsigned short blk_w,
   unsigned short blk_h,
   unsigned short in_stride,
   short coefs_r,
   short coefs_g,
   short coefs_b,
   __vptr_int16 coefs,
   unsigned int roundingFactor,
   unsigned short shift_val,
   __vptr_uint8 iPtrOut,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   rgb_to_yuv_YUYV_init(iPtrR, iPtrG, iPtrB, blk_w, blk_h, in_stride, coefs_r, coefs_g, coefs_b, coefs, roundingFactor, shift_val, iPtrOut, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   rgb_to_yuv_YUYV_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

