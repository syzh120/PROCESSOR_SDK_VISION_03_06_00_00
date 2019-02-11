#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_binary_masking, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_binary_masking, __ALIGNOF__(int));
unsigned short __pblock_vcop_binary_masking[16];

unsigned int vcop_binary_masking_param_count(void)
{
   return 16u;
}

unsigned int vcop_binary_masking_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_binary_masking_init(
   __vptr_uint8 inByteData,
   __vptr_uint8 inBitPackedData,
   __vptr_uint8 outBitPackedData,
   unsigned short computeWidth,
   unsigned short computeHeight,
   unsigned short inputByteDataPitch,
   unsigned short inputBitDataPitch,
   unsigned short outputPitch,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (computeHeight)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((computeWidth) + (8u)-1) & ~((8u)-1))/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)inBitPackedData);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)outBitPackedData);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), (inputBitDataPitch*sizeof(*inBitPackedData)) -(sizeof(*inBitPackedData))*(((((computeWidth) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(11), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), (inputByteDataPitch*sizeof(*inByteData)) -(8u*sizeof(*inByteData))*(((((computeWidth) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(13), (outputPitch*sizeof(*outBitPackedData)) -(sizeof(*outBitPackedData))*(((((computeWidth) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), 1);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)inByteData);
   __offset += 16;

   return 16u;
}

void vcop_binary_masking_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VBitData", 16);
   #pragma VCC_VREG("VByteData", 17);
   #pragma VCC_VREG("VOutData", 18);
   #pragma VCC_VREG("VPackedData", 19);
   #pragma VCC_VREG("Vk1", 20);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("bitDataAddr", "A0");
   #pragma EVE_REG("byteDataAddr", "A1");
   #pragma EVE_REG("outAddr", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 10u, 8u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(14), _VREG(20));
   __vcop_vagen(_AGEN(0), _PREG(1), _PREG(10), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(11), _PREG(12), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(1), _PREG(13), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(16), _AGEN(1), _VREG(17), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_1pt(), _PREG(6), _AGEN(0), _VREG(16), __vcop_alws());
   __vcop_vbitpk(_VREG(17), _VREG(20), _VREG(19));
   __vcop_vand(_VREG(19), _VREG(16), _VREG(18));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_1pt(), __vcop_alws(), _VREG(18), _PREG(8), _AGEN(2), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_binary_masking(
   __vptr_uint8 inByteData,
   __vptr_uint8 inBitPackedData,
   __vptr_uint8 outBitPackedData,
   unsigned short computeWidth,
   unsigned short computeHeight,
   unsigned short inputByteDataPitch,
   unsigned short inputBitDataPitch,
   unsigned short outputPitch)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_binary_masking_init(inByteData, inBitPackedData, outBitPackedData, computeWidth, computeHeight, inputByteDataPitch, inputBitDataPitch, outputPitch, __pblock_vcop_binary_masking);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_binary_masking_vloops(__pblock_vcop_binary_masking);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_binary_masking_custom(
   __vptr_uint8 inByteData,
   __vptr_uint8 inBitPackedData,
   __vptr_uint8 outBitPackedData,
   unsigned short computeWidth,
   unsigned short computeHeight,
   unsigned short inputByteDataPitch,
   unsigned short inputBitDataPitch,
   unsigned short outputPitch,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_binary_masking_init(inByteData, inBitPackedData, outBitPackedData, computeWidth, computeHeight, inputByteDataPitch, inputBitDataPitch, outputPitch, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_binary_masking_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

