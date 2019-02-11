#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_rgb_rgb555, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_rgb_rgb555, __ALIGNOF__(int));
unsigned short __pblock_vcop_rgb_rgb555[30];

unsigned int vcop_rgb_rgb555_param_count(void)
{
   return 30u;
}

unsigned int vcop_rgb_rgb555_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_rgb_rgb555_init(
   __vptr_uint32 rgb,
   __vptr_int8 rgbmask,
   unsigned int npixels,
   __vptr_uint16 rgb555,
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
   __vcop_pblock_init32(pblock, __offset+_PREG(6), 0x1F);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), _CUSTOM(cust_arr1));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)rgbmask+0);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)rgbmask+8);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)rgbmask+16);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), _CUSTOM(cust_arr2));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)rgb);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)rgb555);
   __vcop_pblock_init16(pblock, __offset+_PREG(22), 24);
   __vcop_pblock_init16(pblock, __offset+_PREG(23),  -(((8u-2)*sizeof(*rgb)))*(((npixels/(8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(24), _CUSTOM(cust_arr3));
   __vcop_pblock_init16(pblock, __offset+_PREG(26), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(27),  -((8u*sizeof(*rgb555)))*(((npixels/(8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(28), 5);
   __vcop_pblock_init32(pblock, __offset+_PREG(30), 10);
   __offset += 30;

   return 30u;
}

void vcop_rgb_rgb555_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("S10", 16);
   #pragma VCC_VREG("S5", 17);
   #pragma VCC_VREG("VBm", 18);
   #pragma VCC_VREG("VGm", 19);
   #pragma VCC_VREG("VRm", 20);
   #pragma VCC_VREG("Vb", 21);
   #pragma VCC_VREG("Vbs", 22);
   #pragma VCC_VREG("Vg", 23);
   #pragma VCC_VREG("Vgs", 24);
   #pragma VCC_VREG("Vr", 25);
   #pragma VCC_VREG("Vrgb", 26);
   #pragma VCC_VREG("Vrs", 27);
   #pragma VCC_VREG("Vtmp", 28);
   #pragma VCC_VREG("mask5", 29);

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
   

   __vcop_vloop(__vcop_compute(), 22u, 15u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(28), _VREG(17));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(30), _VREG(16));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(6), _VREG(29));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(1), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(22), _PREG(23), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(26), _PREG(27), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeB(), __vcop_npt(), _PREG(10), _AGEN(0), _VREG(20), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeB(), __vcop_npt(), _PREG(12), _AGEN(0), _VREG(19), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeB(), __vcop_npt(), _PREG(14), _AGEN(0), _VREG(18), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeWU(), __vcop_cust_p8(), _PREG(18), _AGEN(1), _VREG(25), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_cust_p16(), _PREG(18), _AGEN(1), _VREG(23), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_cust_p24(), _PREG(18), _AGEN(1), _VREG(21), __vcop_alws());
   __vcop_vshf(_VREG(25), _VREG(20), _VREG(27));
   __vcop_vshf(_VREG(23), _VREG(19), _VREG(24));
   __vcop_vshf(_VREG(21), _VREG(18), _VREG(22));
   __vcop_vand(_VREG(27), _VREG(29), _VREG(26));
   __vcop_vand(_VREG(24), _VREG(29), _VREG(24));
   __vcop_vshfor(_VREG(24), _VREG(17), _VREG(26));
   __vcop_vand(_VREG(22), _VREG(29), _VREG(22));
   __vcop_vshfor(_VREG(22), _VREG(16), _VREG(26));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(26), _PREG(20), _AGEN(2), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_rgb_rgb555(
   __vptr_uint32 rgb,
   __vptr_int8 rgbmask,
   unsigned int npixels,
   __vptr_uint16 rgb555)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_rgb_rgb555_init(rgb, rgbmask, npixels, rgb555, __pblock_vcop_rgb_rgb555);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_rgb_rgb555_vloops(__pblock_vcop_rgb_rgb555);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_rgb_rgb555_custom(
   __vptr_uint32 rgb,
   __vptr_int8 rgbmask,
   unsigned int npixels,
   __vptr_uint16 rgb555,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_rgb_rgb555_init(rgb, rgbmask, npixels, rgb555, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_rgb_rgb555_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_rgb_rgb565, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_rgb_rgb565, __ALIGNOF__(int));
unsigned short __pblock_vcop_rgb_rgb565[32];

unsigned int vcop_rgb_rgb565_param_count(void)
{
   return 32u;
}

unsigned int vcop_rgb_rgb565_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_rgb_rgb565_init(
   __vptr_uint32 rgb,
   __vptr_int8 rgbmask,
   unsigned int npixels,
   __vptr_uint16 rgb565,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   unsigned char cust_arr4[8] = {0, 0, 1, 2, 3, 3, 4, 5};
   unsigned char cust_arr5[8] = {0, 1, 1, 2, 3, 4, 4, 5};
   unsigned char cust_arr6[8] = {0, 1, 2, 2, 3, 4, 5, 5};

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((npixels/(8u)))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), 0x1F);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), _CUSTOM(cust_arr4));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), 0x3F);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)rgbmask+0);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)rgbmask+8);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), _CUSTOM(cust_arr5));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)rgbmask+16);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)rgb);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)rgb565);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), _CUSTOM(cust_arr6));
   __vcop_pblock_init16(pblock, __offset+_PREG(26), 24);
   __vcop_pblock_init16(pblock, __offset+_PREG(27),  -(((8u-2)*sizeof(*rgb)))*(((npixels/(8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(28), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(29),  -((8u*sizeof(*rgb565)))*(((npixels/(8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(30), 5);
   __vcop_pblock_init32(pblock, __offset+_PREG(32), 11);
   __offset += 32;

   return 32u;
}

void vcop_rgb_rgb565_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("S11", 16);
   #pragma VCC_VREG("S5", 17);
   #pragma VCC_VREG("VBm", 18);
   #pragma VCC_VREG("VGm", 19);
   #pragma VCC_VREG("VRm", 20);
   #pragma VCC_VREG("Vb", 21);
   #pragma VCC_VREG("Vbs", 22);
   #pragma VCC_VREG("Vg", 23);
   #pragma VCC_VREG("Vgs", 24);
   #pragma VCC_VREG("Vr", 25);
   #pragma VCC_VREG("Vrgb", 26);
   #pragma VCC_VREG("Vrs", 27);
   #pragma VCC_VREG("Vtmp", 28);
   #pragma VCC_VREG("mask5", 29);
   #pragma VCC_VREG("mask6", 30);

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
   

   __vcop_vloop(__vcop_compute(), 23u, 16u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(30), _VREG(17));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(32), _VREG(16));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(6), _VREG(29));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(10), _VREG(30));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(1), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(26), _PREG(27), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(28), _PREG(29), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeB(), __vcop_npt(), _PREG(12), _AGEN(0), _VREG(20), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeB(), __vcop_npt(), _PREG(14), _AGEN(0), _VREG(19), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeB(), __vcop_npt(), _PREG(18), _AGEN(0), _VREG(18), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeWU(), __vcop_cust_p8(), _PREG(20), _AGEN(1), _VREG(25), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_cust_p16(), _PREG(20), _AGEN(1), _VREG(23), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_cust_p24(), _PREG(20), _AGEN(1), _VREG(21), __vcop_alws());
   __vcop_vshf(_VREG(25), _VREG(20), _VREG(27));
   __vcop_vshf(_VREG(23), _VREG(19), _VREG(24));
   __vcop_vshf(_VREG(21), _VREG(18), _VREG(22));
   __vcop_vand(_VREG(27), _VREG(29), _VREG(26));
   __vcop_vand(_VREG(24), _VREG(30), _VREG(24));
   __vcop_vshfor(_VREG(24), _VREG(17), _VREG(26));
   __vcop_vand(_VREG(22), _VREG(29), _VREG(22));
   __vcop_vshfor(_VREG(22), _VREG(16), _VREG(26));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(26), _PREG(22), _AGEN(2), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_rgb_rgb565(
   __vptr_uint32 rgb,
   __vptr_int8 rgbmask,
   unsigned int npixels,
   __vptr_uint16 rgb565)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_rgb_rgb565_init(rgb, rgbmask, npixels, rgb565, __pblock_vcop_rgb_rgb565);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_rgb_rgb565_vloops(__pblock_vcop_rgb_rgb565);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_rgb_rgb565_custom(
   __vptr_uint32 rgb,
   __vptr_int8 rgbmask,
   unsigned int npixels,
   __vptr_uint16 rgb565,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_rgb_rgb565_init(rgb, rgbmask, npixels, rgb565, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_rgb_rgb565_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

