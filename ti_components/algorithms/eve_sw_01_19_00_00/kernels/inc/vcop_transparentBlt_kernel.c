#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_transparentBlt_ushort_ushort, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_transparentBlt_ushort_ushort, __ALIGNOF__(int));
unsigned short __pblock_vcop_transparentBlt_ushort_ushort[16];

unsigned int vcop_transparentBlt_ushort_ushort_param_count(void)
{
   return 16u;
}

unsigned int vcop_transparentBlt_ushort_ushort_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_transparentBlt_ushort_ushort_init(
   __vptr_uint16 inrgb555_ptr,
   __vptr_uint16 backrgb555_ptr,
   unsigned short transparentClr,
   unsigned short in1_w,
   unsigned short in1_h,
   unsigned short in2_w,
   unsigned short in2_h,
   unsigned short comp_w,
   unsigned short comp_h,
   unsigned short out_w,
   unsigned short out_h,
   __vptr_uint16 outptr,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (comp_h)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (comp_w/(2 * (8u)))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)backrgb555_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)outptr);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), (in1_w*sizeof(*inrgb555_ptr)) -((2*8u*sizeof(*inrgb555_ptr)))*((comp_w/(2 * (8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), (in2_w*sizeof(*backrgb555_ptr)) -((2*8u*sizeof(*backrgb555_ptr)))*((comp_w/(2 * (8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(13), (out_w*sizeof(*outptr)) -((2*8u*sizeof(*outptr)))*((comp_w/(2 * (8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), transparentClr);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)inrgb555_ptr);
   __offset += 16;

   return 16u;
}

void vcop_transparentBlt_ushort_ushort_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vbk0", 16);
   #pragma VCC_VREG("Vbk1", 17);
   #pragma VCC_VREG("Vcomp0", 18);
   #pragma VCC_VREG("Vcomp1", 19);
   #pragma VCC_VREG("Vin0", 20);
   #pragma VCC_VREG("Vin1", 21);
   #pragma VCC_VREG("VtranspClr", 22);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_alpha", "A0");
   #pragma EVE_REG("Addr_in1", "A1");
   #pragma EVE_REG("Addr_in2", "A2");
   #pragma EVE_REG("Addr_out", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 13u, 8u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(14), _VREG(22));
   __vcop_vagen(_AGEN(1), _PREG(10), _PREG(11), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(10), _PREG(12), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(10), _PREG(13), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(16), _AGEN(1), _VPAIR(20,21), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(6), _AGEN(2), _VPAIR(16,17), __vcop_alws());
   __vcop_vcmpeq(_VREG(20), _VREG(22), _VREG(18));
   __vcop_vcmpeq(_VREG(21), _VREG(22), _VREG(19));
   __vcop_vsel(_VREG(18), _VREG(16), _VREG(20));
   __vcop_vsel(_VREG(19), _VREG(17), _VREG(21));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(20,21), _PREG(8), _AGEN(3), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_transparentBlt_ushort_ushort(
   __vptr_uint16 inrgb555_ptr,
   __vptr_uint16 backrgb555_ptr,
   unsigned short transparentClr,
   unsigned short in1_w,
   unsigned short in1_h,
   unsigned short in2_w,
   unsigned short in2_h,
   unsigned short comp_w,
   unsigned short comp_h,
   unsigned short out_w,
   unsigned short out_h,
   __vptr_uint16 outptr)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_transparentBlt_ushort_ushort_init(inrgb555_ptr, backrgb555_ptr, transparentClr, in1_w, in1_h, in2_w, in2_h, comp_w, comp_h, out_w, out_h, outptr, __pblock_vcop_transparentBlt_ushort_ushort);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_transparentBlt_ushort_ushort_vloops(__pblock_vcop_transparentBlt_ushort_ushort);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_transparentBlt_ushort_ushort_custom(
   __vptr_uint16 inrgb555_ptr,
   __vptr_uint16 backrgb555_ptr,
   unsigned short transparentClr,
   unsigned short in1_w,
   unsigned short in1_h,
   unsigned short in2_w,
   unsigned short in2_h,
   unsigned short comp_w,
   unsigned short comp_h,
   unsigned short out_w,
   unsigned short out_h,
   __vptr_uint16 outptr,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_transparentBlt_ushort_ushort_init(inrgb555_ptr, backrgb555_ptr, transparentClr, in1_w, in1_h, in2_w, in2_h, comp_w, comp_h, out_w, out_h, outptr, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_transparentBlt_ushort_ushort_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

