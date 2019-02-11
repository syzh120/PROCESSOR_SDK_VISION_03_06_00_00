#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_YCbCr422_Deinterleave422_char, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_YCbCr422_Deinterleave422_char, __ALIGNOF__(int));
unsigned short __pblock_vcop_YCbCr422_Deinterleave422_char[18];

unsigned int vcop_YCbCr422_Deinterleave422_char_param_count(void)
{
   return 18u;
}

unsigned int vcop_YCbCr422_Deinterleave422_char_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_YCbCr422_Deinterleave422_char_init(
   __vptr_uint8 YCbYCr_char,
   unsigned int npixels,
   __vptr_uint8 Y_char,
   __vptr_uint8 Cb_char,
   __vptr_uint8 Cr_char,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((npixels/(16)))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)Y_char);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)Cb_char);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)Cr_char);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), 4);
   __vcop_pblock_init16(pblock, __offset+_PREG(13), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), 16);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)YCbYCr_char);
   __offset += 18;

   return 18u;
}

void vcop_YCbCr422_Deinterleave422_char_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VCb", 16);
   #pragma VCC_VREG("VCbCr", 17);
   #pragma VCC_VREG("VCr", 18);
   #pragma VCC_VREG("VY", 19);
   #pragma VCC_VREG("Vdummy", 20);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_Cb_out", "A0");
   #pragma EVE_REG("Addr_Y_out", "A1");
   #pragma EVE_REG("Addr_in", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 12u, 9u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(16), _VREG(20));
   __vcop_vagen(_AGEN(0), _PREG(12), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(13), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(14), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(18), _AGEN(2), _VPAIR(19,17), __vcop_alws());
   __vcop_vmove(_VREG(17), _VREG(16));
   __vcop_vmove(_VREG(20), _VREG(18));
   __vcop_vdintrlv(_VREG(16), _VREG(18));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(19), _PREG(6), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(16), _PREG(8), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(18), _PREG(10), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_YCbCr422_Deinterleave422_char(
   __vptr_uint8 YCbYCr_char,
   unsigned int npixels,
   __vptr_uint8 Y_char,
   __vptr_uint8 Cb_char,
   __vptr_uint8 Cr_char)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_YCbCr422_Deinterleave422_char_init(YCbYCr_char, npixels, Y_char, Cb_char, Cr_char, __pblock_vcop_YCbCr422_Deinterleave422_char);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_YCbCr422_Deinterleave422_char_vloops(__pblock_vcop_YCbCr422_Deinterleave422_char);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_YCbCr422_Deinterleave422_char_custom(
   __vptr_uint8 YCbYCr_char,
   unsigned int npixels,
   __vptr_uint8 Y_char,
   __vptr_uint8 Cb_char,
   __vptr_uint8 Cr_char,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_YCbCr422_Deinterleave422_char_init(YCbYCr_char, npixels, Y_char, Cb_char, Cr_char, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_YCbCr422_Deinterleave422_char_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_YCbCr422_Deinterleave422_short, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_YCbCr422_Deinterleave422_short, __ALIGNOF__(int));
unsigned short __pblock_vcop_YCbCr422_Deinterleave422_short[18];

unsigned int vcop_YCbCr422_Deinterleave422_short_param_count(void)
{
   return 18u;
}

unsigned int vcop_YCbCr422_Deinterleave422_short_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_YCbCr422_Deinterleave422_short_init(
   __vptr_uint16 YCbYCr_short,
   unsigned int npixels,
   __vptr_uint16 Y_short,
   __vptr_uint16 Cb_short,
   __vptr_uint16 Cr_short,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((npixels/(16)))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)Y_short);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)Cb_short);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)Cr_short);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(13), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)YCbYCr_short);
   __offset += 18;

   return 18u;
}

void vcop_YCbCr422_Deinterleave422_short_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VCb", 16);
   #pragma VCC_VREG("VCbCr", 17);
   #pragma VCC_VREG("VCr", 18);
   #pragma VCC_VREG("VY", 19);
   #pragma VCC_VREG("Vdummy", 20);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_Cb_out", "A0");
   #pragma EVE_REG("Addr_Y_out", "A1");
   #pragma EVE_REG("Addr_in", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 12u, 9u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(16), _VREG(20));
   __vcop_vagen(_AGEN(0), _PREG(12), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(13), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(14), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(18), _AGEN(2), _VPAIR(19,17), __vcop_alws());
   __vcop_vmove(_VREG(17), _VREG(16));
   __vcop_vmove(_VREG(20), _VREG(18));
   __vcop_vdintrlv(_VREG(16), _VREG(18));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(19), _PREG(6), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(16), _PREG(8), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(18), _PREG(10), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_YCbCr422_Deinterleave422_short(
   __vptr_uint16 YCbYCr_short,
   unsigned int npixels,
   __vptr_uint16 Y_short,
   __vptr_uint16 Cb_short,
   __vptr_uint16 Cr_short)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_YCbCr422_Deinterleave422_short_init(YCbYCr_short, npixels, Y_short, Cb_short, Cr_short, __pblock_vcop_YCbCr422_Deinterleave422_short);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_YCbCr422_Deinterleave422_short_vloops(__pblock_vcop_YCbCr422_Deinterleave422_short);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_YCbCr422_Deinterleave422_short_custom(
   __vptr_uint16 YCbYCr_short,
   unsigned int npixels,
   __vptr_uint16 Y_short,
   __vptr_uint16 Cb_short,
   __vptr_uint16 Cr_short,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_YCbCr422_Deinterleave422_short_init(YCbYCr_short, npixels, Y_short, Cb_short, Cr_short, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_YCbCr422_Deinterleave422_short_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

