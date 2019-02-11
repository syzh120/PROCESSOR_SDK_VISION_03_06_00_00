#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_fft_zero_padding_kernel, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_fft_zero_padding_kernel, __ALIGNOF__(int));
unsigned short __pblock_vcop_fft_zero_padding_kernel[10];

unsigned int vcop_fft_zero_padding_kernel_param_count(void)
{
   return 10u;
}

unsigned int vcop_fft_zero_padding_kernel_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_fft_zero_padding_kernel_init(
   __vptr_uint32 inputData,
   unsigned short numActualPoints,
   unsigned short numOfLines,
   unsigned short numPointsZeroPadding,
   unsigned short pitch,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (numOfLines)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (numPointsZeroPadding / (8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(7), (pitch) -(8u*sizeof(*inputData))*((numPointsZeroPadding / (8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)inputData+numActualPoints*sizeof(*inputData));
   __offset += 10;

   return 10u;
}

void vcop_fft_zero_padding_kernel_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VK0", 16);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("outAddr", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 4u, 5u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(8), _VREG(16));
   __vcop_vagen(_AGEN(0), _PREG(6), _PREG(7), _PREG(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(16), _PREG(10), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_fft_zero_padding_kernel(
   __vptr_uint32 inputData,
   unsigned short numActualPoints,
   unsigned short numOfLines,
   unsigned short numPointsZeroPadding,
   unsigned short pitch)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_zero_padding_kernel_init(inputData, numActualPoints, numOfLines, numPointsZeroPadding, pitch, __pblock_vcop_fft_zero_padding_kernel);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_zero_padding_kernel_vloops(__pblock_vcop_fft_zero_padding_kernel);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_fft_zero_padding_kernel_custom(
   __vptr_uint32 inputData,
   unsigned short numActualPoints,
   unsigned short numOfLines,
   unsigned short numPointsZeroPadding,
   unsigned short pitch,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_fft_zero_padding_kernel_init(inputData, numActualPoints, numOfLines, numPointsZeroPadding, pitch, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_fft_zero_padding_kernel_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

