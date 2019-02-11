#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_eve_UYVY_to_YUVpl, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_eve_UYVY_to_YUVpl, __ALIGNOF__(int));
unsigned short __pblock_eve_UYVY_to_YUVpl[20];

unsigned int eve_UYVY_to_YUVpl_param_count(void)
{
   return 20u;
}

unsigned int eve_UYVY_to_YUVpl_ctrl_count(void)
{
   return 0u;
}

unsigned int eve_UYVY_to_YUVpl_init(
   __vptr_uint16 in1_ptr,
   int width,
   int line_pitch,
   int height,
   __vptr_uint8 optr_Y,
   __vptr_uint8 optr_Cr,
   __vptr_uint8 optr_Cb,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (height)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (width/(2 * (8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_TRUNC,8));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)optr_Cb);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)optr_Cr);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), (line_pitch*sizeof(*in1_ptr)) -((2*8u*sizeof(*in1_ptr)))*((width/(2 * (8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(13), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), ((width/2)*sizeof(*optr_Y)) -((8u*sizeof(*optr_Y)))*((width/(2 * (8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(15), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(16), (width*sizeof(*optr_Y)) -((2*8u*sizeof(*optr_Y)))*((width/(2 * (8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)in1_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)optr_Y);
   __offset += 20;

   return 20u;
}

void eve_UYVY_to_YUVpl_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vin1", 16);
   #pragma VCC_VREG("Vin2", 17);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr", "A0");
   #pragma EVE_REG("AddrOut_CrCb", "A1");
   #pragma EVE_REG("AddrOut_Y", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 8u, 10u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(12), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(13), _PREG(14), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(15), _PREG(16), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(18), _AGEN(0), _VPAIR(16,17), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(16,17), _PREG(20), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(16), _PREG(8), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(17), _PREG(10), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

}

void eve_UYVY_to_YUVpl(
   __vptr_uint16 in1_ptr,
   int width,
   int line_pitch,
   int height,
   __vptr_uint8 optr_Y,
   __vptr_uint8 optr_Cr,
   __vptr_uint8 optr_Cb)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   eve_UYVY_to_YUVpl_init(in1_ptr, width, line_pitch, height, optr_Y, optr_Cr, optr_Cb, __pblock_eve_UYVY_to_YUVpl);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   eve_UYVY_to_YUVpl_vloops(__pblock_eve_UYVY_to_YUVpl);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void eve_UYVY_to_YUVpl_custom(
   __vptr_uint16 in1_ptr,
   int width,
   int line_pitch,
   int height,
   __vptr_uint8 optr_Y,
   __vptr_uint8 optr_Cr,
   __vptr_uint8 optr_Cb,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   eve_UYVY_to_YUVpl_init(in1_ptr, width, line_pitch, height, optr_Y, optr_Cr, optr_Cb, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   eve_UYVY_to_YUVpl_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

