#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_bin_image_to_list, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_bin_image_to_list, __ALIGNOF__(int));
unsigned short __pblock_vcop_bin_image_to_list[38];

unsigned int vcop_bin_image_to_list_param_count(void)
{
   return 38u;
}

unsigned int vcop_bin_image_to_list_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_bin_image_to_list_init(
   __vptr_uint8 im_A,
   __vptr_uint32 upperLeftXY,
   __vptr_uint32 outXY_B,
   __vptr_uint32 listSize,
   unsigned short width,
   unsigned short height,
   unsigned short inputStride,
   unsigned char outputQformat,
   __vptr_uint32 xSequence_C,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (height)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((width+(8u)-1)/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), height);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), outputQformat);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), 1);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)xSequence_C);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)im_A);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)outXY_B);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)listSize);
   __vcop_pblock_init16(pblock, __offset+_PREG(20), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(21),  -((8u*sizeof(*xSequence_C)))*(((width+(8u)-1)/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(22), ((inputStride/8)*sizeof(*im_A)) -(1)*(((width+(8u)-1)/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(23),  -((inputStride/8)*sizeof(*im_A))*((height)-1u) -(1)*(((width+(8u)-1)/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(24), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)upperLeftXY);
   __offset += 26;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (7)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)upperLeftXY);
   __vcop_pblock_init16(pblock, __offset+_PREG(8), 4);
   __vcop_pblock_init16(pblock, __offset+_PREG(9), -24);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)listSize+sizeof(*listSize));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)listSize);
   __offset += 12;

   return 38u;
}

void vcop_bin_image_to_list_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VoutQformat", 16);
   #pragma VCC_VREG("XYIncr", 17);
   #pragma VCC_VREG("XYIncrQFormat", 18);
   #pragma VCC_VREG("numEntries", 19);
   #pragma VCC_VREG("upLeftXY", 20);
   #pragma VCC_VREG("xyOffset", 21);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("K0", 22);
   #pragma VCC_VREG("K1", 23);
   #pragma VCC_VREG("I", 24);
   #pragma VCC_VREG("mask", 25);
   #pragma VCC_VREG("xseq", 26);
   #pragma VCC_VREG("xy", 27);
   #pragma VCC_VREG("y", 28);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   #pragma EVE_REG("Addr1", "A1");
   #pragma EVE_REG("Addr2", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("k", "I2");
   #pragma EVE_REG("i", "I3");
   #pragma EVE_REG("j", "I4");
   

   __vcop_vloop(__vcop_compute(), 19u, 13u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(24), _VREG(19));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(6), _VREG(17));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(8), _VREG(16));
   __vcop_vinit(__vcop_sizeW(), __vcop_i34_zero(), _PREG(24), _VREG(22));
   __vcop_vinit(__vcop_sizeW(), __vcop_i34_zero(), _PREG(10), _VREG(23));
   __vcop_vinit(__vcop_sizeHU(), __vcop_alws(), _PREG(67), _VREG(28));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(20), _PREG(21), _PREG(21), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(1), _PREG(22), _PREG(23), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_1pt(), _PREG(26), _AGEN(0), _VREG(20), __vcop_once());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(12), _AGEN(1), _VREG(26), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_1pt(), _PREG(14), _AGEN(2), _VREG(24), __vcop_alws());
   __vcop_vbitunpk(_VREG(24), _VREG(23), _VREG(25));
   __vcop_vshf(_VREG(28), _VREG(16), _VREG(27));
   __vcop_vadd3(_VREG(26), _VREG(20), _VREG(27));
   __vcop_vadd(_VREG(19), _VREG(25), _VREG(19));
   __vcop_vstore(__vcop_predicate(_VREG(25)), __vcop_sizeWU(), __vcop_collat(), __vcop_alws(), _VREG(27), _PREG(16), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_last_i34(), _VREG(19), _PREG(18), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("updatedXY", 29);
   #pragma VCC_VREG("sz", 30);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   #pragma EVE_REG("Addr1", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("i", "I3");
   #pragma EVE_REG("j", "I4");
   

   __vcop_vloop(__vcop_compute(), 9u, 6u, 2u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(8), _PREG(9), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_1pt(), _PREG(10), _AGEN(1), _VREG(30), __vcop_alws());
   __vcop_vshf(_VREG(17), _VREG(16), _VREG(18));
   __vcop_vadd(_VREG(19), _VREG(30), _VREG(19));
   __vcop_vadd(_VREG(20), _VREG(18), _VREG(21));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_1pt(), __vcop_last_i4(), _VREG(19), _PREG(12), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_1pt(), __vcop_last_i4(), _VREG(21), _PREG(6), _AGEN(0), _PREG(0));
   __vcop_vloop_end(2u);

}

void vcop_bin_image_to_list(
   __vptr_uint8 im_A,
   __vptr_uint32 upperLeftXY,
   __vptr_uint32 outXY_B,
   __vptr_uint32 listSize,
   unsigned short width,
   unsigned short height,
   unsigned short inputStride,
   unsigned char outputQformat,
   __vptr_uint32 xSequence_C)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_bin_image_to_list_init(im_A, upperLeftXY, outXY_B, listSize, width, height, inputStride, outputQformat, xSequence_C, __pblock_vcop_bin_image_to_list);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_bin_image_to_list_vloops(__pblock_vcop_bin_image_to_list);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_bin_image_to_list_custom(
   __vptr_uint8 im_A,
   __vptr_uint32 upperLeftXY,
   __vptr_uint32 outXY_B,
   __vptr_uint32 listSize,
   unsigned short width,
   unsigned short height,
   unsigned short inputStride,
   unsigned char outputQformat,
   __vptr_uint32 xSequence_C,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_bin_image_to_list_init(im_A, upperLeftXY, outXY_B, listSize, width, height, inputStride, outputQformat, xSequence_C, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_bin_image_to_list_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

