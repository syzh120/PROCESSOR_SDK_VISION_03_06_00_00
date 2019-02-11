#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_YCbCr444_Deinterleave444_char, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_YCbCr444_Deinterleave444_char, __ALIGNOF__(int));
unsigned short __pblock_vcop_YCbCr444_Deinterleave444_char[28];

unsigned int vcop_YCbCr444_Deinterleave444_char_param_count(void)
{
   return 28u;
}

unsigned int vcop_YCbCr444_Deinterleave444_char_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_YCbCr444_Deinterleave444_char_init(
   __vptr_uint32 YCbCr_char,
   __vptr_int8 YCbCrmask,
   unsigned int npixels,
   __vptr_uint8 Y_char,
   __vptr_uint8 Cb_char,
   __vptr_uint8 Cr_char,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   unsigned char cust_arr1[8] = {0, 0, 1, 2, 3, 3, 4, 5};
   unsigned char cust_arr2[8] = {0, 1, 1, 2, 3, 4, 4, 5};
   unsigned char cust_arr3[8] = {0, 1, 2, 2, 3, 4, 5, 5};

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((npixels/(8u)))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)YCbCrmask+16);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), _CUSTOM(cust_arr1));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)YCbCr_char);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)Y_char);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)Cb_char);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), _CUSTOM(cust_arr2));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)Cr_char);
   __vcop_pblock_init16(pblock, __offset+_PREG(20), 24);
   __vcop_pblock_init16(pblock, __offset+_PREG(21),  -(((8u-2)*sizeof(*YCbCr_char)))*(((npixels/(8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(22), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(23),  -((8u*sizeof(*Y_char)))*(((npixels/(8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(24), _CUSTOM(cust_arr3));
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)YCbCrmask+0);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)YCbCrmask+8);
   __offset += 28;

   return 28u;
}

void vcop_YCbCr444_Deinterleave444_char_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VCb", 16);
   #pragma VCC_VREG("VCbm", 17);
   #pragma VCC_VREG("VCbs", 18);
   #pragma VCC_VREG("VCr", 19);
   #pragma VCC_VREG("VCrm", 20);
   #pragma VCC_VREG("VCrs", 21);
   #pragma VCC_VREG("VY", 22);
   #pragma VCC_VREG("VYm", 23);
   #pragma VCC_VREG("VYs", 24);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_m", "A0");
   #pragma EVE_REG("Addr_in", "A1");
   #pragma EVE_REG("Addr_out", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I0", "I3");
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 16u, 14u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(1), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(20), _PREG(21), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(22), _PREG(23), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeB(), __vcop_npt(), _PREG(26), _AGEN(0), _VREG(23), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeB(), __vcop_npt(), _PREG(28), _AGEN(0), _VREG(17), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeB(), __vcop_npt(), _PREG(6), _AGEN(0), _VREG(20), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeWU(), __vcop_cust_p8(), _PREG(10), _AGEN(1), _VREG(22), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_cust_p16(), _PREG(10), _AGEN(1), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_cust_p24(), _PREG(10), _AGEN(1), _VREG(19), __vcop_alws());
   __vcop_vshf(_VREG(22), _VREG(23), _VREG(24));
   __vcop_vshf(_VREG(16), _VREG(17), _VREG(18));
   __vcop_vshf(_VREG(19), _VREG(20), _VREG(21));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(24), _PREG(12), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(18), _PREG(14), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(21), _PREG(18), _AGEN(2), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_YCbCr444_Deinterleave444_char(
   __vptr_uint32 YCbCr_char,
   __vptr_int8 YCbCrmask,
   unsigned int npixels,
   __vptr_uint8 Y_char,
   __vptr_uint8 Cb_char,
   __vptr_uint8 Cr_char)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_YCbCr444_Deinterleave444_char_init(YCbCr_char, YCbCrmask, npixels, Y_char, Cb_char, Cr_char, __pblock_vcop_YCbCr444_Deinterleave444_char);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_YCbCr444_Deinterleave444_char_vloops(__pblock_vcop_YCbCr444_Deinterleave444_char);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_YCbCr444_Deinterleave444_char_custom(
   __vptr_uint32 YCbCr_char,
   __vptr_int8 YCbCrmask,
   unsigned int npixels,
   __vptr_uint8 Y_char,
   __vptr_uint8 Cb_char,
   __vptr_uint8 Cr_char,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_YCbCr444_Deinterleave444_char_init(YCbCr_char, YCbCrmask, npixels, Y_char, Cb_char, Cr_char, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_YCbCr444_Deinterleave444_char_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_YCbCr444_Deinterleave444_short, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_YCbCr444_Deinterleave444_short, __ALIGNOF__(int));
unsigned short __pblock_vcop_YCbCr444_Deinterleave444_short[28];

unsigned int vcop_YCbCr444_Deinterleave444_short_param_count(void)
{
   return 28u;
}

unsigned int vcop_YCbCr444_Deinterleave444_short_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_YCbCr444_Deinterleave444_short_init(
   __vptr_uint32 YCbCr_short,
   __vptr_int8 YCbCrmask,
   unsigned int npixels,
   __vptr_uint16 Y_short,
   __vptr_uint16 Cb_short,
   __vptr_uint16 Cr_short,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   unsigned char cust_arr4[8] = {0, 1, 3, 4, 6, 7, 0, 0};
   unsigned char cust_arr5[8] = {0, 2, 3, 5, 6, 0, 0, 0};
   unsigned char cust_arr6[8] = {1, 2, 4, 5, 7, 0, 0, 0};

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((npixels/(8u)))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)YCbCrmask+16);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), _CUSTOM(cust_arr4));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)YCbCr_short);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)Y_short);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)Cb_short);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), _CUSTOM(cust_arr5));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)Cr_short);
   __vcop_pblock_init16(pblock, __offset+_PREG(20), 24);
   __vcop_pblock_init16(pblock, __offset+_PREG(21),  -(((8u-2)*sizeof(*YCbCr_short)))*(((npixels/(8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(22), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(23),  -((4*sizeof(*Y_short)))*(((npixels/(8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(24), _CUSTOM(cust_arr6));
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)YCbCrmask+0);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)YCbCrmask+8);
   __offset += 28;

   return 28u;
}

void vcop_YCbCr444_Deinterleave444_short_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VCb", 16);
   #pragma VCC_VREG("VCbm", 17);
   #pragma VCC_VREG("VCbs", 18);
   #pragma VCC_VREG("VCr", 19);
   #pragma VCC_VREG("VCrm", 20);
   #pragma VCC_VREG("VCrs", 21);
   #pragma VCC_VREG("VY", 22);
   #pragma VCC_VREG("VYm", 23);
   #pragma VCC_VREG("VYs", 24);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_m", "A0");
   #pragma EVE_REG("Addr_in", "A1");
   #pragma EVE_REG("Addr_out", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I0", "I3");
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 16u, 14u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(1), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(20), _PREG(21), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(22), _PREG(23), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeB(), __vcop_npt(), _PREG(26), _AGEN(0), _VREG(23), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeB(), __vcop_npt(), _PREG(28), _AGEN(0), _VREG(17), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeB(), __vcop_npt(), _PREG(6), _AGEN(0), _VREG(20), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeWU(), __vcop_cust_p8(), _PREG(10), _AGEN(1), _VREG(22), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_cust_p16(), _PREG(10), _AGEN(1), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_cust_p24(), _PREG(10), _AGEN(1), _VREG(19), __vcop_alws());
   __vcop_vshf(_VREG(22), _VREG(23), _VREG(24));
   __vcop_vshf(_VREG(16), _VREG(17), _VREG(18));
   __vcop_vshf(_VREG(19), _VREG(20), _VREG(21));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(24), _PREG(12), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(18), _PREG(14), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(21), _PREG(18), _AGEN(2), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_YCbCr444_Deinterleave444_short(
   __vptr_uint32 YCbCr_short,
   __vptr_int8 YCbCrmask,
   unsigned int npixels,
   __vptr_uint16 Y_short,
   __vptr_uint16 Cb_short,
   __vptr_uint16 Cr_short)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_YCbCr444_Deinterleave444_short_init(YCbCr_short, YCbCrmask, npixels, Y_short, Cb_short, Cr_short, __pblock_vcop_YCbCr444_Deinterleave444_short);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_YCbCr444_Deinterleave444_short_vloops(__pblock_vcop_YCbCr444_Deinterleave444_short);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_YCbCr444_Deinterleave444_short_custom(
   __vptr_uint32 YCbCr_short,
   __vptr_int8 YCbCrmask,
   unsigned int npixels,
   __vptr_uint16 Y_short,
   __vptr_uint16 Cb_short,
   __vptr_uint16 Cr_short,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_YCbCr444_Deinterleave444_short_init(YCbCr_short, YCbCrmask, npixels, Y_short, Cb_short, Cr_short, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_YCbCr444_Deinterleave444_short_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

