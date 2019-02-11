#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_rgb555_rgb, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_rgb555_rgb, __ALIGNOF__(int));
unsigned short __pblock_vcop_rgb555_rgb[22];

unsigned int vcop_rgb555_rgb_param_count(void)
{
   return 22u;
}

unsigned int vcop_rgb555_rgb_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_rgb555_rgb_init(
   __vptr_uint16 rgb16,
   unsigned int npixels,
   __vptr_uint8 r,
   __vptr_uint8 g,
   __vptr_uint8 b,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (npixels/(2 * (8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_ROUND,5));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), __vcop_store_round_sat(SM_NONE,0,RM_ROUND,10));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), 0x7C00);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)rgb16);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)r);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)g);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)b);
   __vcop_pblock_init16(pblock, __offset+_PREG(18), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(19), 16);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), 0x1F);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), 0x3E0);
   __offset += 22;

   return 22u;
}

void vcop_rgb555_rgb_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("V1F", 16);
   #pragma VCC_VREG("V3E0", 17);
   #pragma VCC_VREG("V7C00", 18);
   #pragma VCC_VREG("Vb1", 19);
   #pragma VCC_VREG("Vb2", 20);
   #pragma VCC_VREG("Vg1", 21);
   #pragma VCC_VREG("Vg2", 22);
   #pragma VCC_VREG("Vin1", 23);
   #pragma VCC_VREG("Vin2", 24);
   #pragma VCC_VREG("Vr1", 25);
   #pragma VCC_VREG("Vr2", 26);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("inAddr", "A0");
   #pragma EVE_REG("outAddr", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 16u, 11u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(20), _VREG(16));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(22), _VREG(17));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(8), _VREG(18));
   __vcop_vagen(_AGEN(0), _PREG(18), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(19), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(10), _AGEN(0), _VPAIR(23,24), __vcop_alws());
   __vcop_vand(_VREG(23), _VREG(16), _VREG(25));
   __vcop_vand(_VREG(23), _VREG(17), _VREG(21));
   __vcop_vand(_VREG(23), _VREG(18), _VREG(19));
   __vcop_vand(_VREG(24), _VREG(16), _VREG(26));
   __vcop_vand(_VREG(24), _VREG(17), _VREG(22));
   __vcop_vand(_VREG(24), _VREG(18), _VREG(20));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(25,26), _PREG(12), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(21,22), _PREG(14), _AGEN(1), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(19,20), _PREG(16), _AGEN(1), _PREG(7));
   __vcop_vloop_end(1u);

}

void vcop_rgb555_rgb(
   __vptr_uint16 rgb16,
   unsigned int npixels,
   __vptr_uint8 r,
   __vptr_uint8 g,
   __vptr_uint8 b)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_rgb555_rgb_init(rgb16, npixels, r, g, b, __pblock_vcop_rgb555_rgb);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_rgb555_rgb_vloops(__pblock_vcop_rgb555_rgb);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_rgb555_rgb_custom(
   __vptr_uint16 rgb16,
   unsigned int npixels,
   __vptr_uint8 r,
   __vptr_uint8 g,
   __vptr_uint8 b,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_rgb555_rgb_init(rgb16, npixels, r, g, b, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_rgb555_rgb_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_rgb565_rgb, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_rgb565_rgb, __ALIGNOF__(int));
unsigned short __pblock_vcop_rgb565_rgb[22];

unsigned int vcop_rgb565_rgb_param_count(void)
{
   return 22u;
}

unsigned int vcop_rgb565_rgb_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_rgb565_rgb_init(
   __vptr_uint16 rgb16,
   unsigned int npixels,
   __vptr_uint8 r,
   __vptr_uint8 g,
   __vptr_uint8 b,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (npixels/(2 * (8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_ROUND,5));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), __vcop_store_round_sat(SM_NONE,0,RM_ROUND,11));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), 0xF800);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)rgb16);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)r);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)g);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)b);
   __vcop_pblock_init16(pblock, __offset+_PREG(18), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(19), 16);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), 0x1F);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), 0x7E0);
   __offset += 22;

   return 22u;
}

void vcop_rgb565_rgb_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("V1F", 16);
   #pragma VCC_VREG("V7E0", 17);
   #pragma VCC_VREG("VF800", 18);
   #pragma VCC_VREG("Vb1", 19);
   #pragma VCC_VREG("Vb2", 20);
   #pragma VCC_VREG("Vg1", 21);
   #pragma VCC_VREG("Vg2", 22);
   #pragma VCC_VREG("Vin1", 23);
   #pragma VCC_VREG("Vin2", 24);
   #pragma VCC_VREG("Vr1", 25);
   #pragma VCC_VREG("Vr2", 26);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("inAddr", "A0");
   #pragma EVE_REG("outAddr", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 16u, 11u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(20), _VREG(16));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(22), _VREG(17));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(8), _VREG(18));
   __vcop_vagen(_AGEN(0), _PREG(18), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(19), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(10), _AGEN(0), _VPAIR(23,24), __vcop_alws());
   __vcop_vand(_VREG(23), _VREG(16), _VREG(25));
   __vcop_vand(_VREG(23), _VREG(17), _VREG(21));
   __vcop_vand(_VREG(23), _VREG(18), _VREG(19));
   __vcop_vand(_VREG(24), _VREG(16), _VREG(26));
   __vcop_vand(_VREG(24), _VREG(17), _VREG(22));
   __vcop_vand(_VREG(24), _VREG(18), _VREG(20));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(25,26), _PREG(12), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(21,22), _PREG(14), _AGEN(1), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(19,20), _PREG(16), _AGEN(1), _PREG(7));
   __vcop_vloop_end(1u);

}

void vcop_rgb565_rgb(
   __vptr_uint16 rgb16,
   unsigned int npixels,
   __vptr_uint8 r,
   __vptr_uint8 g,
   __vptr_uint8 b)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_rgb565_rgb_init(rgb16, npixels, r, g, b, __pblock_vcop_rgb565_rgb);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_rgb565_rgb_vloops(__pblock_vcop_rgb565_rgb);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_rgb565_rgb_custom(
   __vptr_uint16 rgb16,
   unsigned int npixels,
   __vptr_uint8 r,
   __vptr_uint8 g,
   __vptr_uint8 b,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_rgb565_rgb_init(rgb16, npixels, r, g, b, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_rgb565_rgb_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

