#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_extract_bit_field_u32, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_extract_bit_field_u32, __ALIGNOF__(int));
unsigned short __pblock_vcop_extract_bit_field_u32[14];

unsigned int vcop_extract_bit_field_u32_param_count(void)
{
   return 14u;
}

unsigned int vcop_extract_bit_field_u32_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_extract_bit_field_u32_init(
   __vptr_uint32 inArray_A,
   unsigned short length,
   unsigned int bit_mask,
   unsigned char shift,
   __vptr_uint8 outList_B,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((length + (8u) - 1)/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_TRUNC,shift));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)outList_B);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 8);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), bit_mask);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)inArray_A);
   __offset += 14;

   return 14u;
}

void vcop_extract_bit_field_u32_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vmask", 16);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vin", 17);
   #pragma VCC_VREG("Vout", 18);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_in", "A0");
   #pragma EVE_REG("Addr_out", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 7u, 7u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(12), _VREG(16));
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(10), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(14), _AGEN(0), _VREG(17), __vcop_alws());
   __vcop_vand(_VREG(17), _VREG(16), _VREG(18));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(18), _PREG(8), _AGEN(1), _PREG(6));
   __vcop_vloop_end(1u);

}

void vcop_extract_bit_field_u32(
   __vptr_uint32 inArray_A,
   unsigned short length,
   unsigned int bit_mask,
   unsigned char shift,
   __vptr_uint8 outList_B)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_extract_bit_field_u32_init(inArray_A, length, bit_mask, shift, outList_B, __pblock_vcop_extract_bit_field_u32);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_extract_bit_field_u32_vloops(__pblock_vcop_extract_bit_field_u32);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_extract_bit_field_u32_custom(
   __vptr_uint32 inArray_A,
   unsigned short length,
   unsigned int bit_mask,
   unsigned char shift,
   __vptr_uint8 outList_B,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_extract_bit_field_u32_init(inArray_A, length, bit_mask, shift, outList_B, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_extract_bit_field_u32_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

