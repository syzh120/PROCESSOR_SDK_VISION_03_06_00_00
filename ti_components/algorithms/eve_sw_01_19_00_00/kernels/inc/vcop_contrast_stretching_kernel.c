#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_memset, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_memset, __ALIGNOF__(int));
unsigned short __pblock_vcop_memset[10];

unsigned int vcop_memset_param_count(void)
{
   return 10u;
}

unsigned int vcop_memset_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_memset_init(
   __vptr_uint32 inPtr,
   unsigned char value,
   unsigned short size,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((size) + 2*(8u)-1) & ~(2*(8u)-1))/(4*(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), value);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)inPtr);
   __offset += 10;

   return 10u;
}

void vcop_memset_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("valPtr", 16);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr1", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("i", "I4");
   

   __vcop_vloop(__vcop_compute(), 4u, 5u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(8), _VREG(16));
   __vcop_vagen(_AGEN(0), _PREG(6), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(16), _PREG(10), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_memset(
   __vptr_uint32 inPtr,
   unsigned char value,
   unsigned short size)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_memset_init(inPtr, value, size, __pblock_vcop_memset);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_memset_vloops(__pblock_vcop_memset);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_memset_custom(
   __vptr_uint32 inPtr,
   unsigned char value,
   unsigned short size,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_memset_init(inPtr, value, size, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_memset_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_histogram_8c_word, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_histogram_8c_word, __ALIGNOF__(int));
unsigned short __pblock_vcop_histogram_8c_word[14];

unsigned int vcop_histogram_8c_word_param_count(void)
{
   return 14u;
}

unsigned int vcop_histogram_8c_word_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_histogram_8c_word_init(
   __vptr_uint8 inputImage,
   unsigned short blkWidth,
   unsigned short blkHeight,
   unsigned short inPitch,
   __vptr_uint32 histogram8Copy,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   const int preg_ref1 = _PREG(7);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (blkHeight)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (blkWidth/(8))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_SYMM,preg_ref1,RM_TRUNC,0));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 255);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)histogram8Copy);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), ((inPitch*sizeof(*inputImage))) -((sizeof(*inputImage)*8))*((blkWidth/(8))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), 1);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)inputImage);
   __offset += 14;

   return 14u;
}

void vcop_histogram_8c_word_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vdata", 16);
   #pragma VCC_VREG("Vindex", 17);
   #pragma VCC_VREG("Vout", 18);
   #pragma VCC_VREG("Vweight", 19);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("hist_agen", "A1");
   #pragma EVE_REG("ind_agen", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("i3", "I3");
   #pragma EVE_REG("i4", "I4");
   

   __vcop_vloop(__vcop_histogram(), 8u, 7u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(12), _VREG(19));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(0), _PREG(10), _PREG(11), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(14), _AGEN(0), _VREG(17), __vcop_alws());
   __vcop_vhistload(__vcop_sizeWU(), 8, _PREG(8), _AGEN(1), _VREG(17), _VREG(16), _PREG(6), __vcop_alws());
   __vcop_hist_vadd(_VREG(16), _VREG(19), _VREG(16));
   __vcop_vhiststore(__vcop_sizeWU(), 8, __vcop_alws(), _VREG(16), _PREG(8), _AGEN(1), _VREG(17));
   __vcop_vloop_end(1u);

}

void vcop_histogram_8c_word(
   __vptr_uint8 inputImage,
   unsigned short blkWidth,
   unsigned short blkHeight,
   unsigned short inPitch,
   __vptr_uint32 histogram8Copy)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_histogram_8c_word_init(inputImage, blkWidth, blkHeight, inPitch, histogram8Copy, __pblock_vcop_histogram_8c_word);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_histogram_8c_word_vloops(__pblock_vcop_histogram_8c_word);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_histogram_8c_word_custom(
   __vptr_uint8 inputImage,
   unsigned short blkWidth,
   unsigned short blkHeight,
   unsigned short inPitch,
   __vptr_uint32 histogram8Copy,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_histogram_8c_word_init(inputImage, blkWidth, blkHeight, inPitch, histogram8Copy, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_histogram_8c_word_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_contrast_stretching, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_contrast_stretching, __ALIGNOF__(int));
unsigned short __pblock_vcop_contrast_stretching[22];

unsigned int vcop_contrast_stretching_param_count(void)
{
   return 22u;
}

unsigned int vcop_contrast_stretching_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_contrast_stretching_init(
   __vptr_uint8 inputImage,
   __vptr_uint8 outputImage,
   unsigned short blkWidth,
   unsigned short blkHeight,
   unsigned short inPitch,
   unsigned short outPitch,
   unsigned char minVal,
   unsigned short scaleFactorQ16,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   const int preg_ref2 = _PREG(7);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (blkHeight)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((blkWidth) + 2*(8u)-1) & ~(2*(8u)-1)) / (2*(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_SYMM,preg_ref2,RM_ROUND,16));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 255);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (-8));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (255));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)inputImage);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)outputImage);
   __vcop_pblock_init16(pblock, __offset+_PREG(16), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(17), (inPitch*sizeof(*inputImage)) -((2*8u*sizeof(*inputImage)))*(((((blkWidth) + 2*(8u)-1) & ~(2*(8u)-1)) / (2*(8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(18), (outPitch*sizeof(*inputImage)) -((2*8u*sizeof(*inputImage)))*(((((blkWidth) + 2*(8u)-1) & ~(2*(8u)-1)) / (2*(8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), scaleFactorQ16);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), minVal);
   __offset += 22;

   return 22u;
}

void vcop_contrast_stretching_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VinterimVal1", 16);
   #pragma VCC_VREG("VinterimVal2", 17);
   #pragma VCC_VREG("VmaxPixVal", 18);
   #pragma VCC_VREG("VminVal", 19);
   #pragma VCC_VREG("VnegShift", 20);
   #pragma VCC_VREG("VpixVal1", 21);
   #pragma VCC_VREG("VpixVal2", 22);
   #pragma VCC_VREG("VremappedValueQ16_1", 23);
   #pragma VCC_VREG("VremappedValueQ16_2", 24);
   #pragma VCC_VREG("VrightShift8", 25);
   #pragma VCC_VREG("VscaleFactorQ16", 26);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("inAddr", "A0");
   #pragma EVE_REG("outAddr", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("i3", "I3");
   #pragma EVE_REG("i4", "I4");
   

   __vcop_vloop(__vcop_compute(), 15u, 11u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(20), _VREG(26));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(22), _VREG(19));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(8), _VREG(25));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(10), _VREG(18));
   __vcop_vagen(_AGEN(0), _PREG(16), _PREG(17), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(16), _PREG(18), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(12), _AGEN(0), _VPAIR(21,22), __vcop_alws());
   __vcop_vsub(_VREG(21), _VREG(19), _VREG(21));
   __vcop_vsub(_VREG(22), _VREG(19), _VREG(22));
   __vcop_vmpy(_VREG(21), _VREG(18), _VREG(16), _PREG(0));
   __vcop_vmpy(_VREG(22), _VREG(18), _VREG(17), _PREG(0));
   __vcop_vmpy(_VREG(16), _VREG(26), _VREG(23), _PREG(0));
   __vcop_vmpy(_VREG(17), _VREG(26), _VREG(24), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(23,24), _PREG(14), _AGEN(1), _PREG(6));
   __vcop_vloop_end(1u);

}

void vcop_contrast_stretching(
   __vptr_uint8 inputImage,
   __vptr_uint8 outputImage,
   unsigned short blkWidth,
   unsigned short blkHeight,
   unsigned short inPitch,
   unsigned short outPitch,
   unsigned char minVal,
   unsigned short scaleFactorQ16)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_contrast_stretching_init(inputImage, outputImage, blkWidth, blkHeight, inPitch, outPitch, minVal, scaleFactorQ16, __pblock_vcop_contrast_stretching);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_contrast_stretching_vloops(__pblock_vcop_contrast_stretching);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_contrast_stretching_custom(
   __vptr_uint8 inputImage,
   __vptr_uint8 outputImage,
   unsigned short blkWidth,
   unsigned short blkHeight,
   unsigned short inPitch,
   unsigned short outPitch,
   unsigned char minVal,
   unsigned short scaleFactorQ16,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_contrast_stretching_init(inputImage, outputImage, blkWidth, blkHeight, inPitch, outPitch, minVal, scaleFactorQ16, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_contrast_stretching_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_histogram_8c_word_sum, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_histogram_8c_word_sum, __ALIGNOF__(int));
unsigned short __pblock_vcop_histogram_8c_word_sum[24];

unsigned int vcop_histogram_8c_word_sum_param_count(void)
{
   return 24u;
}

unsigned int vcop_histogram_8c_word_sum_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_histogram_8c_word_sum_init(
   __vptr_uint32 histogram8Copy,
   __vptr_uint32 transposeBuff,
   __vptr_uint32 histogram,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (32)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 4);
   __vcop_pblock_init16(pblock, __offset+_PREG(8), 260);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)histogram8Copy);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)transposeBuff);
   __offset += 12;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (32)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)histogram);
   __vcop_pblock_init16(pblock, __offset+_PREG(8), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(9), 36);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)transposeBuff);
   __offset += 12;

   return 24u;
}

void vcop_histogram_8c_word_sum_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("bankData", 16);
   #pragma VCC_VREG("inData", 17);
   #pragma VCC_VREG("sum", 18);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("inAddr", "A0");
   #pragma EVE_REG("outAddr", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("i3", "I3");
   #pragma EVE_REG("i4", "I4");
   

   __vcop_vloop(__vcop_compute(), 5u, 6u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(6), _PREG(6), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(8), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(10), _AGEN(0), _VREG(16), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_offst_np1(), __vcop_alws(), _VREG(16), _PREG(12), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("outAddr", "A0");
   #pragma EVE_REG("inAddr", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("i3", "I3");
   #pragma EVE_REG("i4", "I4");
   

   __vcop_vloop(__vcop_compute(), 7u, 6u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(10), _VREG(18));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(8), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(9), _PREG(9), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(12), _AGEN(1), _VREG(17), __vcop_alws());
   __vcop_vadd(_VREG(18), _VREG(17), _VREG(18));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_last_i4(), _VREG(18), _PREG(6), _AGEN(0), _PREG(0));
   __vcop_vloop_end(2u);

}

void vcop_histogram_8c_word_sum(
   __vptr_uint32 histogram8Copy,
   __vptr_uint32 transposeBuff,
   __vptr_uint32 histogram)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_histogram_8c_word_sum_init(histogram8Copy, transposeBuff, histogram, __pblock_vcop_histogram_8c_word_sum);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_histogram_8c_word_sum_vloops(__pblock_vcop_histogram_8c_word_sum);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_histogram_8c_word_sum_custom(
   __vptr_uint32 histogram8Copy,
   __vptr_uint32 transposeBuff,
   __vptr_uint32 histogram,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_histogram_8c_word_sum_init(histogram8Copy, transposeBuff, histogram, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_histogram_8c_word_sum_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

