#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_rgb_to_srgb, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_rgb_to_srgb, __ALIGNOF__(int));
unsigned short __pblock_rgb_to_srgb[42];

unsigned int rgb_to_srgb_param_count(void)
{
   return 42u;
}

unsigned int rgb_to_srgb_ctrl_count(void)
{
   return 0u;
}

unsigned int rgb_to_srgb_init(
   __vptr_uint16 iPtrR,
   __vptr_uint16 iPtrG,
   __vptr_uint16 iPtrB,
   __vptr_uint16 oPtrR,
   __vptr_uint16 oPtrG,
   __vptr_uint16 oPtrB,
   unsigned short blk_w,
   unsigned short blk_h,
   unsigned short input_stride,
   unsigned short output_stride,
   __vptr_int16 rgb2srgb_coefs,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   const int preg_ref1 = _PREG(7);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (blk_h)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((blk_w/(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_SYMM,preg_ref1,RM_TRUNC,8));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 4095);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), *(rgb2srgb_coefs+2));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), *(rgb2srgb_coefs+3));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), *(rgb2srgb_coefs+4));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), *(rgb2srgb_coefs+5));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), *(rgb2srgb_coefs+6));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), *(rgb2srgb_coefs+7));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), *(rgb2srgb_coefs+8));
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)iPtrR);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)iPtrG);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)iPtrB);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), 0x80);
   __vcop_pblock_init32(pblock, __offset+_PREG(30), (uchar *)oPtrR);
   __vcop_pblock_init32(pblock, __offset+_PREG(32), (uchar *)oPtrG);
   __vcop_pblock_init32(pblock, __offset+_PREG(34), (uchar *)oPtrB);
   __vcop_pblock_init16(pblock, __offset+_PREG(36), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(37), (input_stride*sizeof(*iPtrR)) -((8u*sizeof(*iPtrR)))*(((blk_w/(8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(38), (output_stride*sizeof(*iPtrR)) -((8u*sizeof(*iPtrR)))*(((blk_w/(8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(40), *(rgb2srgb_coefs));
   __vcop_pblock_init32(pblock, __offset+_PREG(42), *(rgb2srgb_coefs+1));
   __offset += 42;

   return 42u;
}

void rgb_to_srgb_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vblu", 16);
   #pragma VCC_VREG("Vcoef0", 17);
   #pragma VCC_VREG("Vcoef1", 18);
   #pragma VCC_VREG("Vcoef2", 19);
   #pragma VCC_VREG("Vcoef3", 20);
   #pragma VCC_VREG("Vcoef4", 21);
   #pragma VCC_VREG("Vcoef5", 22);
   #pragma VCC_VREG("Vcoef6", 23);
   #pragma VCC_VREG("Vcoef7", 24);
   #pragma VCC_VREG("Vcoef8", 25);
   #pragma VCC_VREG("Vgrn", 26);
   #pragma VCC_VREG("Vred", 27);
   #pragma VCC_VREG("VsBlue", 28);
   #pragma VCC_VREG("VsGreen", 29);
   #pragma VCC_VREG("VsRed", 30);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_in", "A0");
   #pragma EVE_REG("Addr_out", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I0", "I3");
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 30u, 21u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(40), _VREG(17));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(42), _VREG(18));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(8), _VREG(19));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(10), _VREG(20));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(12), _VREG(21));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(14), _VREG(22));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(16), _VREG(23));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(18), _VREG(24));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(20), _VREG(25));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(28), _VREG(30));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(28), _VREG(29));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(28), _VREG(28));
   __vcop_vagen(_AGEN(0), _PREG(36), _PREG(37), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(36), _PREG(38), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(22), _AGEN(0), _VREG(27), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(24), _AGEN(0), _VREG(26), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(26), _AGEN(0), _VREG(16), __vcop_alws());
   __vcop_vmadd(_VREG(17), _VREG(27), _VREG(30), _PREG(0));
   __vcop_vmadd(_VREG(18), _VREG(26), _VREG(30), _PREG(0));
   __vcop_vmadd(_VREG(19), _VREG(16), _VREG(30), _PREG(0));
   __vcop_vmadd(_VREG(20), _VREG(27), _VREG(29), _PREG(0));
   __vcop_vmadd(_VREG(21), _VREG(26), _VREG(29), _PREG(0));
   __vcop_vmadd(_VREG(22), _VREG(16), _VREG(29), _PREG(0));
   __vcop_vmadd(_VREG(23), _VREG(27), _VREG(28), _PREG(0));
   __vcop_vmadd(_VREG(24), _VREG(26), _VREG(28), _PREG(0));
   __vcop_vmadd(_VREG(25), _VREG(16), _VREG(28), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(30), _PREG(30), _AGEN(1), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(29), _PREG(32), _AGEN(1), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(28), _PREG(34), _AGEN(1), _PREG(6));
   __vcop_vloop_end(1u);

}

void rgb_to_srgb(
   __vptr_uint16 iPtrR,
   __vptr_uint16 iPtrG,
   __vptr_uint16 iPtrB,
   __vptr_uint16 oPtrR,
   __vptr_uint16 oPtrG,
   __vptr_uint16 oPtrB,
   unsigned short blk_w,
   unsigned short blk_h,
   unsigned short input_stride,
   unsigned short output_stride,
   __vptr_int16 rgb2srgb_coefs)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   rgb_to_srgb_init(iPtrR, iPtrG, iPtrB, oPtrR, oPtrG, oPtrB, blk_w, blk_h, input_stride, output_stride, rgb2srgb_coefs, __pblock_rgb_to_srgb);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   rgb_to_srgb_vloops(__pblock_rgb_to_srgb);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void rgb_to_srgb_custom(
   __vptr_uint16 iPtrR,
   __vptr_uint16 iPtrG,
   __vptr_uint16 iPtrB,
   __vptr_uint16 oPtrR,
   __vptr_uint16 oPtrG,
   __vptr_uint16 oPtrB,
   unsigned short blk_w,
   unsigned short blk_h,
   unsigned short input_stride,
   unsigned short output_stride,
   __vptr_int16 rgb2srgb_coefs,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   rgb_to_srgb_init(iPtrR, iPtrG, iPtrB, oPtrR, oPtrG, oPtrB, blk_w, blk_h, input_stride, output_stride, rgb2srgb_coefs, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   rgb_to_srgb_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

