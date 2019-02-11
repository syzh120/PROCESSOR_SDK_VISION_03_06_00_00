#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_nnInterpolate420SPchromaPblockUpdate, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_nnInterpolate420SPchromaPblockUpdate, __ALIGNOF__(int));
unsigned short __pblock_vcop_nnInterpolate420SPchromaPblockUpdate[22];

unsigned int vcop_nnInterpolate420SPchromaPblockUpdate_param_count(void)
{
   return 22u;
}

unsigned int vcop_nnInterpolate420SPchromaPblockUpdate_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_nnInterpolate420SPchromaPblockUpdate_init(
   __vptr_uint16 numMappedPixels_ptr,
   __vptr_uint16 pBlock16,
   unsigned int scatterStoreArray_ptr,
   __vptr_uint32 pBlock32,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (1)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), 0x00000001);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), 0x00000007);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), -3);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), 1);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pBlock16+6);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pBlock32+44);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pBlock16+54);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)numMappedPixels_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), scatterStoreArray_ptr);
   __offset += 22;

   return 22u;
}

void vcop_nnInterpolate420SPchromaPblockUpdate_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VnumMappedPixels", 16);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vloop1", 17);
   #pragma VCC_VREG("Vloop2", 18);
   #pragma VCC_VREG("VlutLoop", 19);
   #pragma VCC_VREG("VnumMappedPixels_1", 20);
   #pragma VCC_VREG("Vone", 21);
   #pragma VCC_VREG("VscatterStoreArray", 22);
   #pragma VCC_VREG("Vseven", 23);
   #pragma VCC_VREG("Vshiftone", 24);
   #pragma VCC_VREG("Vshiftthree", 25);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 18u, 11u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(22), _VREG(22));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(6), _VREG(21));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(8), _VREG(23));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(10), _VREG(25));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(12), _VREG(24));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(20), _AGEN(0), _VREG(16), __vcop_once());
   __vcop_vmax(_VREG(16), _VREG(21), _VREG(20));
   __vcop_vsub(_VREG(20), _VREG(21), _VREG(19));
   __vcop_vadd(_VREG(20), _VREG(23), _VREG(18));
   __vcop_vshf(_VREG(18), _VREG(25), _VREG(18));
   __vcop_vsub(_VREG(18), _VREG(21), _VREG(18));
   __vcop_vshf(_VREG(16), _VREG(24), _VREG(17));
   __vcop_vadd(_VREG(17), _VREG(22), _VREG(17));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_1pt(), __vcop_alws(), _VREG(19), _PREG(14), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_1pt(), __vcop_alws(), _VREG(17), _PREG(16), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_1pt(), __vcop_alws(), _VREG(18), _PREG(18), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_nnInterpolate420SPchromaPblockUpdate(
   __vptr_uint16 numMappedPixels_ptr,
   __vptr_uint16 pBlock16,
   unsigned int scatterStoreArray_ptr,
   __vptr_uint32 pBlock32)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_nnInterpolate420SPchromaPblockUpdate_init(numMappedPixels_ptr, pBlock16, scatterStoreArray_ptr, pBlock32, __pblock_vcop_nnInterpolate420SPchromaPblockUpdate);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_nnInterpolate420SPchromaPblockUpdate_vloops(__pblock_vcop_nnInterpolate420SPchromaPblockUpdate);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_nnInterpolate420SPchromaPblockUpdate_custom(
   __vptr_uint16 numMappedPixels_ptr,
   __vptr_uint16 pBlock16,
   unsigned int scatterStoreArray_ptr,
   __vptr_uint32 pBlock32,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_nnInterpolate420SPchromaPblockUpdate_init(numMappedPixels_ptr, pBlock16, scatterStoreArray_ptr, pBlock32, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_nnInterpolate420SPchromaPblockUpdate_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

