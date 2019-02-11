#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_chromaTLUIndexCalcBilInterpolatePblockUpdate, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_chromaTLUIndexCalcBilInterpolatePblockUpdate, __ALIGNOF__(int));
unsigned short __pblock_vcop_chromaTLUIndexCalcBilInterpolatePblockUpdate[14];

unsigned int vcop_chromaTLUIndexCalcBilInterpolatePblockUpdate_param_count(void)
{
   return 14u;
}

unsigned int vcop_chromaTLUIndexCalcBilInterpolatePblockUpdate_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_chromaTLUIndexCalcBilInterpolatePblockUpdate_init(
   __vptr_uint16 numMappedPixels_ptr,
   __vptr_uint16 pBlock16,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (1)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), 0x00000007);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), -3);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pBlock16+6);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)numMappedPixels_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), 0x00000001);
   __offset += 14;

   return 14u;
}

void vcop_chromaTLUIndexCalcBilInterpolatePblockUpdate_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VnumMappedPixels", 16);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vloop1", 17);
   #pragma VCC_VREG("Vone", 18);
   #pragma VCC_VREG("Vseven", 19);
   #pragma VCC_VREG("Vshiftthree", 20);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 11u, 7u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(14), _VREG(18));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(6), _VREG(19));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(8), _VREG(20));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(12), _AGEN(0), _VREG(16), __vcop_once());
   __vcop_vmax(_VREG(16), _VREG(18), _VREG(16));
   __vcop_vadd(_VREG(16), _VREG(19), _VREG(17));
   __vcop_vshf(_VREG(17), _VREG(20), _VREG(17));
   __vcop_vsub(_VREG(17), _VREG(18), _VREG(17));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_1pt(), __vcop_alws(), _VREG(17), _PREG(10), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_chromaTLUIndexCalcBilInterpolatePblockUpdate(
   __vptr_uint16 numMappedPixels_ptr,
   __vptr_uint16 pBlock16)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_chromaTLUIndexCalcBilInterpolatePblockUpdate_init(numMappedPixels_ptr, pBlock16, __pblock_vcop_chromaTLUIndexCalcBilInterpolatePblockUpdate);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_chromaTLUIndexCalcBilInterpolatePblockUpdate_vloops(__pblock_vcop_chromaTLUIndexCalcBilInterpolatePblockUpdate);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_chromaTLUIndexCalcBilInterpolatePblockUpdate_custom(
   __vptr_uint16 numMappedPixels_ptr,
   __vptr_uint16 pBlock16,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_chromaTLUIndexCalcBilInterpolatePblockUpdate_init(numMappedPixels_ptr, pBlock16, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_chromaTLUIndexCalcBilInterpolatePblockUpdate_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_chromaTLUIndexCalcNNInterpolatePblockUpdate, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_chromaTLUIndexCalcNNInterpolatePblockUpdate, __ALIGNOF__(int));
unsigned short __pblock_vcop_chromaTLUIndexCalcNNInterpolatePblockUpdate[14];

unsigned int vcop_chromaTLUIndexCalcNNInterpolatePblockUpdate_param_count(void)
{
   return 14u;
}

unsigned int vcop_chromaTLUIndexCalcNNInterpolatePblockUpdate_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_chromaTLUIndexCalcNNInterpolatePblockUpdate_init(
   __vptr_uint16 numMappedPixels_ptr,
   __vptr_uint16 pBlock16,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (1)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), 0x0000000F);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), -4);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pBlock16+6);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)numMappedPixels_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), 0x00000001);
   __offset += 14;

   return 14u;
}

void vcop_chromaTLUIndexCalcNNInterpolatePblockUpdate_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VnumMappedPixels", 16);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vfifteen", 17);
   #pragma VCC_VREG("Vloop1", 18);
   #pragma VCC_VREG("Vone", 19);
   #pragma VCC_VREG("Vshiftfour", 20);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 11u, 7u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(14), _VREG(19));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(6), _VREG(17));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(8), _VREG(20));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(12), _AGEN(0), _VREG(16), __vcop_once());
   __vcop_vmax(_VREG(16), _VREG(19), _VREG(16));
   __vcop_vadd(_VREG(16), _VREG(17), _VREG(18));
   __vcop_vshf(_VREG(18), _VREG(20), _VREG(18));
   __vcop_vsub(_VREG(18), _VREG(19), _VREG(18));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_1pt(), __vcop_alws(), _VREG(18), _PREG(10), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_chromaTLUIndexCalcNNInterpolatePblockUpdate(
   __vptr_uint16 numMappedPixels_ptr,
   __vptr_uint16 pBlock16)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_chromaTLUIndexCalcNNInterpolatePblockUpdate_init(numMappedPixels_ptr, pBlock16, __pblock_vcop_chromaTLUIndexCalcNNInterpolatePblockUpdate);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_chromaTLUIndexCalcNNInterpolatePblockUpdate_vloops(__pblock_vcop_chromaTLUIndexCalcNNInterpolatePblockUpdate);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_chromaTLUIndexCalcNNInterpolatePblockUpdate_custom(
   __vptr_uint16 numMappedPixels_ptr,
   __vptr_uint16 pBlock16,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_chromaTLUIndexCalcNNInterpolatePblockUpdate_init(numMappedPixels_ptr, pBlock16, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_chromaTLUIndexCalcNNInterpolatePblockUpdate_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

