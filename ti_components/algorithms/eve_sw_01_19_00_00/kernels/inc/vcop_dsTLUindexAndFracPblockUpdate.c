#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_dsTLUindexAndFracBilInterpolatePblockUpdate, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_dsTLUindexAndFracBilInterpolatePblockUpdate, __ALIGNOF__(int));
unsigned short __pblock_vcop_dsTLUindexAndFracBilInterpolatePblockUpdate[36];

unsigned int vcop_dsTLUindexAndFracBilInterpolatePblockUpdate_param_count(void)
{
   return 36u;
}

unsigned int vcop_dsTLUindexAndFracBilInterpolatePblockUpdate_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_dsTLUindexAndFracBilInterpolatePblockUpdate_init(
   __vptr_uint16 numMappedPixels_ptr,
   __vptr_uint16 numEvenMappedPixels_ptr,
   __vptr_uint16 pBlock16,
   unsigned int tluIndexArray_ptr,
   unsigned int fracArray_ptr,
   __vptr_uint32 pBlock32,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (1)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), tluIndexArray_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), fracArray_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), 0x00000001);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), 0x0000000F);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), -4);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), 16);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), 1);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), 8);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)pBlock16+6);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)pBlock16+78);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)pBlock32+96);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)pBlock32+100);
   __vcop_pblock_init32(pblock, __offset+_PREG(30), (uchar *)pBlock32+104);
   __vcop_pblock_init32(pblock, __offset+_PREG(32), (uchar *)pBlock32+108);
   __vcop_pblock_init32(pblock, __offset+_PREG(34), (uchar *)numMappedPixels_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(36), (uchar *)numEvenMappedPixels_ptr);
   __offset += 36;

   return 36u;
}

void vcop_dsTLUindexAndFracBilInterpolatePblockUpdate_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VnumEvenMappedPixels", 16);
   #pragma VCC_VREG("VnumMappedPixels", 17);
   #pragma VCC_VREG("VnumOddMappedPixels", 18);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VOddfracArray", 19);
   #pragma VCC_VREG("VOddfracArrayNext", 20);
   #pragma VCC_VREG("VOddtluIndexArray", 21);
   #pragma VCC_VREG("VOddtluIndexArrayNext", 22);
   #pragma VCC_VREG("Veight", 23);
   #pragma VCC_VREG("Vfifteen", 24);
   #pragma VCC_VREG("VfracArray", 25);
   #pragma VCC_VREG("Vloop1", 26);
   #pragma VCC_VREG("Vloop2", 27);
   #pragma VCC_VREG("Vone", 28);
   #pragma VCC_VREG("Vshiftfour", 29);
   #pragma VCC_VREG("Vshiftone", 30);
   #pragma VCC_VREG("Vsixteen", 31);
   #pragma VCC_VREG("VtluIndexArray", 32);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 32u, 18u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(6), _VREG(32));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(8), _VREG(25));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(10), _VREG(28));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(12), _VREG(24));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(14), _VREG(29));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(16), _VREG(31));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(18), _VREG(30));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(20), _VREG(23));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(34), _AGEN(0), _VREG(17), __vcop_once());
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(36), _AGEN(0), _VREG(16), __vcop_once());
   __vcop_vsub(_VREG(17), _VREG(16), _VREG(18));
   __vcop_vadd(_VREG(16), _VREG(24), _VREG(26));
   __vcop_vshf(_VREG(26), _VREG(29), _VREG(26));
   __vcop_vmax(_VREG(26), _VREG(28), _VREG(26));
   __vcop_vsub(_VREG(26), _VREG(28), _VREG(26));
   __vcop_vadd(_VREG(18), _VREG(24), _VREG(27));
   __vcop_vshf(_VREG(27), _VREG(29), _VREG(27));
   __vcop_vmax(_VREG(27), _VREG(28), _VREG(27));
   __vcop_vsub(_VREG(27), _VREG(28), _VREG(27));
   __vcop_vshf(_VREG(16), _VREG(30), _VREG(21));
   __vcop_vadd(_VREG(21), _VREG(32), _VREG(21));
   __vcop_vadd(_VREG(21), _VREG(31), _VREG(22));
   __vcop_vadd(_VREG(16), _VREG(25), _VREG(19));
   __vcop_vadd(_VREG(19), _VREG(23), _VREG(20));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_1pt(), __vcop_alws(), _VREG(26), _PREG(22), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_1pt(), __vcop_alws(), _VREG(27), _PREG(24), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_1pt(), __vcop_alws(), _VREG(21), _PREG(26), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_1pt(), __vcop_alws(), _VREG(22), _PREG(28), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_1pt(), __vcop_alws(), _VREG(19), _PREG(30), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_1pt(), __vcop_alws(), _VREG(20), _PREG(32), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_dsTLUindexAndFracBilInterpolatePblockUpdate(
   __vptr_uint16 numMappedPixels_ptr,
   __vptr_uint16 numEvenMappedPixels_ptr,
   __vptr_uint16 pBlock16,
   unsigned int tluIndexArray_ptr,
   unsigned int fracArray_ptr,
   __vptr_uint32 pBlock32)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_dsTLUindexAndFracBilInterpolatePblockUpdate_init(numMappedPixels_ptr, numEvenMappedPixels_ptr, pBlock16, tluIndexArray_ptr, fracArray_ptr, pBlock32, __pblock_vcop_dsTLUindexAndFracBilInterpolatePblockUpdate);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_dsTLUindexAndFracBilInterpolatePblockUpdate_vloops(__pblock_vcop_dsTLUindexAndFracBilInterpolatePblockUpdate);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_dsTLUindexAndFracBilInterpolatePblockUpdate_custom(
   __vptr_uint16 numMappedPixels_ptr,
   __vptr_uint16 numEvenMappedPixels_ptr,
   __vptr_uint16 pBlock16,
   unsigned int tluIndexArray_ptr,
   unsigned int fracArray_ptr,
   __vptr_uint32 pBlock32,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_dsTLUindexAndFracBilInterpolatePblockUpdate_init(numMappedPixels_ptr, numEvenMappedPixels_ptr, pBlock16, tluIndexArray_ptr, fracArray_ptr, pBlock32, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_dsTLUindexAndFracBilInterpolatePblockUpdate_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_dsTLUindexAndFracNNInterpolatePblockUpdate, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_dsTLUindexAndFracNNInterpolatePblockUpdate, __ALIGNOF__(int));
unsigned short __pblock_vcop_dsTLUindexAndFracNNInterpolatePblockUpdate[36];

unsigned int vcop_dsTLUindexAndFracNNInterpolatePblockUpdate_param_count(void)
{
   return 36u;
}

unsigned int vcop_dsTLUindexAndFracNNInterpolatePblockUpdate_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_dsTLUindexAndFracNNInterpolatePblockUpdate_init(
   __vptr_uint16 numMappedPixels_ptr,
   __vptr_uint16 numEvenMappedPixels_ptr,
   __vptr_uint16 pBlock16,
   unsigned int tluIndexArray_ptr,
   unsigned int fracArray_ptr,
   __vptr_uint32 pBlock32,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (1)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), tluIndexArray_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), fracArray_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), 0x00000001);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), 0x0000000F);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), -4);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), 16);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), 1);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), 8);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)pBlock16+6);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)pBlock16+62);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)pBlock32+88);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)pBlock32+92);
   __vcop_pblock_init32(pblock, __offset+_PREG(30), (uchar *)pBlock32+68);
   __vcop_pblock_init32(pblock, __offset+_PREG(32), (uchar *)pBlock32+72);
   __vcop_pblock_init32(pblock, __offset+_PREG(34), (uchar *)numMappedPixels_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(36), (uchar *)numEvenMappedPixels_ptr);
   __offset += 36;

   return 36u;
}

void vcop_dsTLUindexAndFracNNInterpolatePblockUpdate_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VnumEvenMappedPixels", 16);
   #pragma VCC_VREG("VnumMappedPixels", 17);
   #pragma VCC_VREG("VnumOddMappedPixels", 18);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VOddfracArray", 19);
   #pragma VCC_VREG("VOddfracArrayNext", 20);
   #pragma VCC_VREG("VOddtluIndexArray", 21);
   #pragma VCC_VREG("VOddtluIndexArrayNext", 22);
   #pragma VCC_VREG("Veight", 23);
   #pragma VCC_VREG("Vfifteen", 24);
   #pragma VCC_VREG("VfracArray", 25);
   #pragma VCC_VREG("Vloop1", 26);
   #pragma VCC_VREG("Vloop2", 27);
   #pragma VCC_VREG("Vone", 28);
   #pragma VCC_VREG("Vshiftfour", 29);
   #pragma VCC_VREG("Vshiftone", 30);
   #pragma VCC_VREG("Vsixteen", 31);
   #pragma VCC_VREG("VtluIndexArray", 32);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 32u, 18u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(6), _VREG(32));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(8), _VREG(25));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(10), _VREG(28));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(12), _VREG(24));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(14), _VREG(29));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(16), _VREG(31));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(18), _VREG(30));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(20), _VREG(23));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(34), _AGEN(0), _VREG(17), __vcop_once());
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(36), _AGEN(0), _VREG(16), __vcop_once());
   __vcop_vsub(_VREG(17), _VREG(16), _VREG(18));
   __vcop_vadd(_VREG(16), _VREG(24), _VREG(26));
   __vcop_vshf(_VREG(26), _VREG(29), _VREG(26));
   __vcop_vmax(_VREG(26), _VREG(28), _VREG(26));
   __vcop_vsub(_VREG(26), _VREG(28), _VREG(26));
   __vcop_vadd(_VREG(18), _VREG(24), _VREG(27));
   __vcop_vshf(_VREG(27), _VREG(29), _VREG(27));
   __vcop_vmax(_VREG(27), _VREG(28), _VREG(27));
   __vcop_vsub(_VREG(27), _VREG(28), _VREG(27));
   __vcop_vshf(_VREG(16), _VREG(30), _VREG(21));
   __vcop_vadd(_VREG(21), _VREG(32), _VREG(21));
   __vcop_vadd(_VREG(21), _VREG(31), _VREG(22));
   __vcop_vadd(_VREG(16), _VREG(25), _VREG(19));
   __vcop_vadd(_VREG(19), _VREG(23), _VREG(20));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_1pt(), __vcop_alws(), _VREG(26), _PREG(22), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_1pt(), __vcop_alws(), _VREG(27), _PREG(24), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_1pt(), __vcop_alws(), _VREG(21), _PREG(26), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_1pt(), __vcop_alws(), _VREG(22), _PREG(28), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_1pt(), __vcop_alws(), _VREG(19), _PREG(30), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_1pt(), __vcop_alws(), _VREG(20), _PREG(32), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_dsTLUindexAndFracNNInterpolatePblockUpdate(
   __vptr_uint16 numMappedPixels_ptr,
   __vptr_uint16 numEvenMappedPixels_ptr,
   __vptr_uint16 pBlock16,
   unsigned int tluIndexArray_ptr,
   unsigned int fracArray_ptr,
   __vptr_uint32 pBlock32)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_dsTLUindexAndFracNNInterpolatePblockUpdate_init(numMappedPixels_ptr, numEvenMappedPixels_ptr, pBlock16, tluIndexArray_ptr, fracArray_ptr, pBlock32, __pblock_vcop_dsTLUindexAndFracNNInterpolatePblockUpdate);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_dsTLUindexAndFracNNInterpolatePblockUpdate_vloops(__pblock_vcop_dsTLUindexAndFracNNInterpolatePblockUpdate);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_dsTLUindexAndFracNNInterpolatePblockUpdate_custom(
   __vptr_uint16 numMappedPixels_ptr,
   __vptr_uint16 numEvenMappedPixels_ptr,
   __vptr_uint16 pBlock16,
   unsigned int tluIndexArray_ptr,
   unsigned int fracArray_ptr,
   __vptr_uint32 pBlock32,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_dsTLUindexAndFracNNInterpolatePblockUpdate_init(numMappedPixels_ptr, numEvenMappedPixels_ptr, pBlock16, tluIndexArray_ptr, fracArray_ptr, pBlock32, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_dsTLUindexAndFracNNInterpolatePblockUpdate_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

