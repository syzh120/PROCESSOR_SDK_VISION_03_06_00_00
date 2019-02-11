#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_intensity_scaling, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_intensity_scaling, __ALIGNOF__(int));
unsigned short __pblock_vcop_intensity_scaling[14];

unsigned int vcop_intensity_scaling_param_count(void)
{
   return 14u;
}

unsigned int vcop_intensity_scaling_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_intensity_scaling_init(
   __vptr_uint8 inImg_A,
   __vptr_uint8 scalingLUT_C,
   __vptr_uint8 outImg_B,
   unsigned short blockWidth,
   unsigned short blockHeight,
   unsigned short blockStride,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (blockHeight)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((blockWidth + (8) - 1)/(8))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)outImg_B);
   __vcop_pblock_init16(pblock, __offset+_PREG(8), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(9), ((blockStride*sizeof(*inImg_A))) -((sizeof(*inImg_A)*8))*(((blockWidth + (8) - 1)/(8))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(10), ((blockWidth*sizeof(*outImg_B))) -((sizeof(*outImg_B)*8))*(((blockWidth + (8) - 1)/(8))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)inImg_A);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)scalingLUT_C);
   __offset += 14;

   return 14u;
}

void vcop_intensity_scaling_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vin", 16);
   #pragma VCC_VREG("Vscaledpix", 17);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("index_addr", "A0");
   #pragma EVE_REG("out_addr", "A2");
   #pragma EVE_REG("table_addr", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_tablelkup(), 7u, 7u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(8), _PREG(9), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(8), _PREG(10), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(12), _AGEN(0), _VREG(16), __vcop_alws());
   __vcop_vtbload(__vcop_sizeBU(), __vcop_tableinfo(8, 1), _PREG(14), _AGEN(1), _VREG(16), _VREG(17), _PREG(0), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(17), _PREG(6), _AGEN(2), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_intensity_scaling(
   __vptr_uint8 inImg_A,
   __vptr_uint8 scalingLUT_C,
   __vptr_uint8 outImg_B,
   unsigned short blockWidth,
   unsigned short blockHeight,
   unsigned short blockStride)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_intensity_scaling_init(inImg_A, scalingLUT_C, outImg_B, blockWidth, blockHeight, blockStride, __pblock_vcop_intensity_scaling);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_intensity_scaling_vloops(__pblock_vcop_intensity_scaling);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_intensity_scaling_custom(
   __vptr_uint8 inImg_A,
   __vptr_uint8 scalingLUT_C,
   __vptr_uint8 outImg_B,
   unsigned short blockWidth,
   unsigned short blockHeight,
   unsigned short blockStride,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_intensity_scaling_init(inImg_A, scalingLUT_C, outImg_B, blockWidth, blockHeight, blockStride, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_intensity_scaling_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

