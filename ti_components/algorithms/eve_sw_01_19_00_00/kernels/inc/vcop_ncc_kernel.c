#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_slidingSum, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_slidingSum, __ALIGNOF__(int));
unsigned short __pblock_vcop_slidingSum[100];

unsigned int vcop_slidingSum_param_count(void)
{
   return 100u;
}

unsigned int vcop_slidingSum_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_slidingSum_init(
   __vptr_uint8 pInput,
   unsigned short inputStride,
   unsigned short windowWidth,
   unsigned short windowHeight,
   unsigned short computeWidth,
   unsigned short computeHeight,
   __vptr_int32 pScratch,
   unsigned short scratchStride,
   __vptr_uint32 pSum,
   unsigned short sumStride,
   __vptr_uint16 pOffset,
   __vptr_int32 pScratchLine,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (((((computeWidth + windowWidth - 1)) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (windowHeight)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pInput);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pInput+8u*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pScratch);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pScratch+8u*scratchStride);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pScratchLine);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pScratchLine+8u*sizeof(*pScratch));
   __vcop_pblock_init16(pblock, __offset+_PREG(18), ((2*8u)*scratchStride));
   __vcop_pblock_init16(pblock, __offset+_PREG(19), 64);
   __vcop_pblock_init16(pblock, __offset+_PREG(20), (inputStride));
   __vcop_pblock_init16(pblock, __offset+_PREG(21), ((2*8u)) -(inputStride)*((windowHeight)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)pOffset);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), 0);
   __offset += 24;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (((((computeWidth + windowWidth - 1)) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((computeHeight-1))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pInput+1*windowHeight*inputStride);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pInput+8u*1+1*windowHeight*inputStride);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pInput);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pInput+8u*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pScratch+sizeof(*pScratch));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pScratch+sizeof(*pScratch)+8u*scratchStride);
   __vcop_pblock_init16(pblock, __offset+_PREG(18), 64);
   __vcop_pblock_init16(pblock, __offset+_PREG(19), (inputStride));
   __vcop_pblock_init16(pblock, __offset+_PREG(20), ((2*8u)) -(inputStride)*(((computeHeight-1))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(21), 4);
   __vcop_pblock_init16(pblock, __offset+_PREG(22), ((2*8u)*scratchStride) -(sizeof(*pScratch))*(((computeHeight-1))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)pScratchLine);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)pScratchLine+8u*sizeof(*pScratch));
   __offset += 26;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((((computeHeight) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (windowWidth)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pScratch);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pScratch+8u*sizeof(*pScratch));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pSum);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pSum+8u*sumStride);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pScratchLine);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pScratchLine+8u*sizeof(*pScratch));
   __vcop_pblock_init16(pblock, __offset+_PREG(18), 64);
   __vcop_pblock_init16(pblock, __offset+_PREG(19), ((2*8u)*sumStride));
   __vcop_pblock_init16(pblock, __offset+_PREG(20), (scratchStride));
   __vcop_pblock_init16(pblock, __offset+_PREG(21), (sizeof(*pScratch)*(2*8u)) -(scratchStride)*((windowWidth)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)pOffset+16);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), 0);
   __offset += 24;

   /* Loop 4 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((((computeHeight) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((computeWidth-1))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pScratch+scratchStride*windowWidth);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pScratch+8u*sizeof(*pScratch)+scratchStride*windowWidth);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pScratch);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pScratch+8u*sizeof(*pScratch));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pSum+sizeof(*pSum));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pSum+sizeof(*pSum)+8u*sumStride);
   __vcop_pblock_init16(pblock, __offset+_PREG(18), 64);
   __vcop_pblock_init16(pblock, __offset+_PREG(19), (scratchStride));
   __vcop_pblock_init16(pblock, __offset+_PREG(20), (sizeof(*pScratch)*(2*8u)) -(scratchStride)*(((computeWidth-1))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(21), 4);
   __vcop_pblock_init16(pblock, __offset+_PREG(22), ((2*8u)*sumStride) -(sizeof(*pSum))*(((computeWidth-1))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)pScratchLine);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)pScratchLine+8u*sizeof(*pScratch));
   __offset += 26;

   return 100u;
}

void vcop_slidingSum_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("vOfst", 16);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vInput0", 17);
   #pragma VCC_VREG("vInput1", 18);
   #pragma VCC_VREG("vScratch0", 19);
   #pragma VCC_VREG("vScratch1", 20);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("AddrOffset", "A0");
   #pragma EVE_REG("scratchAddr", "A1");
   #pragma EVE_REG("scratchLineAddr", "A2");
   #pragma EVE_REG("orgImgAddr", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("u", "I3");
   #pragma EVE_REG("v", "I4");
   

   __vcop_vloop(__vcop_compute(), 16u, 12u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(24), _VREG(19));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(24), _VREG(20));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(18), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(0), _PREG(19), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(20), _PREG(21), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(22), _AGEN(0), _VREG(16), __vcop_once());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(6), _AGEN(3), _VREG(17), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(8), _AGEN(3), _VREG(18), __vcop_alws());
   __vcop_vadd(_VREG(19), _VREG(17), _VREG(19));
   __vcop_vadd(_VREG(20), _VREG(18), _VREG(20));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_pdda(_VREG(16)), __vcop_last_i4(), _VREG(19), _PREG(10), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_pdda(_VREG(16)), __vcop_last_i4(), _VREG(20), _PREG(12), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_last_i4(), _VREG(19), _PREG(14), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_last_i4(), _VREG(20), _PREG(16), _AGEN(2), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vScratch0", 21);
   #pragma VCC_VREG("vScratch1", 22);
   #pragma VCC_VREG("vNewInput0", 23);
   #pragma VCC_VREG("vNewInput1", 24);
   #pragma VCC_VREG("vOldInput0", 25);
   #pragma VCC_VREG("vOldInput1", 26);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("AddrOffset", "A0");
   #pragma EVE_REG("scratchLineAddr", "A1");
   #pragma EVE_REG("orgImgAddr", "A2");
   #pragma EVE_REG("scratchWrAddr", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("u", "I3");
   #pragma EVE_REG("v", "I4");
   

   __vcop_vloop(__vcop_compute(), 15u, 13u, 2u);
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(18), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(19), _PREG(20), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(21), _PREG(22), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(24), _AGEN(1), _VREG(21), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(26), _AGEN(1), _VREG(22), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(6), _AGEN(2), _VREG(23), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(8), _AGEN(2), _VREG(24), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(10), _AGEN(2), _VREG(25), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(12), _AGEN(2), _VREG(26), __vcop_alws());
   __vcop_vadif(_VREG(23), _VREG(25), _VREG(21));
   __vcop_vadif(_VREG(24), _VREG(26), _VREG(22));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_pdda(_VREG(16)), __vcop_alws(), _VREG(21), _PREG(14), _AGEN(3), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_pdda(_VREG(16)), __vcop_alws(), _VREG(22), _PREG(16), _AGEN(3), _PREG(0));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vScratch0", 27);
   #pragma VCC_VREG("vScratch1", 28);
   #pragma VCC_VREG("vSum0", 29);
   #pragma VCC_VREG("vSum1", 30);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("AddrOffset", "A0");
   #pragma EVE_REG("scratchLineAddr", "A1");
   #pragma EVE_REG("sumAddr", "A2");
   #pragma EVE_REG("scratchAddr", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("v", "I3");
   #pragma EVE_REG("u", "I4");
   

   __vcop_vloop(__vcop_compute(), 16u, 12u, 3u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(24), _VREG(29));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(24), _VREG(30));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(18), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(0), _PREG(19), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(20), _PREG(21), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(22), _AGEN(0), _VREG(16), __vcop_once());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(6), _AGEN(3), _VREG(27), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(8), _AGEN(3), _VREG(28), __vcop_alws());
   __vcop_vadd(_VREG(29), _VREG(27), _VREG(29));
   __vcop_vadd(_VREG(30), _VREG(28), _VREG(30));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_pdda(_VREG(16)), __vcop_last_i4(), _VREG(29), _PREG(10), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_pdda(_VREG(16)), __vcop_last_i4(), _VREG(30), _PREG(12), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_last_i4(), _VREG(29), _PREG(14), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_last_i4(), _VREG(30), _PREG(16), _AGEN(1), _PREG(0));
   __vcop_vloop_end(3u);

   /* VLOOP 4 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vSum0", 31);
   #pragma VCC_VREG("vSum1", 32);
   #pragma VCC_VREG("vNewInput0", 33);
   #pragma VCC_VREG("vNewInput1", 34);
   #pragma VCC_VREG("vOldInput0", 35);
   #pragma VCC_VREG("vOldInput1", 36);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("AddrOffset", "A0");
   #pragma EVE_REG("scratchLineAddr", "A1");
   #pragma EVE_REG("scratchAddr", "A2");
   #pragma EVE_REG("sumWrAddr", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("v", "I3");
   #pragma EVE_REG("u", "I4");
   

   __vcop_vloop(__vcop_compute(), 15u, 13u, 4u);
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(18), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(19), _PREG(20), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(21), _PREG(22), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(24), _AGEN(1), _VREG(31), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(26), _AGEN(1), _VREG(32), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(6), _AGEN(2), _VREG(33), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(8), _AGEN(2), _VREG(34), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(10), _AGEN(2), _VREG(35), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(12), _AGEN(2), _VREG(36), __vcop_alws());
   __vcop_vadif(_VREG(33), _VREG(35), _VREG(31));
   __vcop_vadif(_VREG(34), _VREG(36), _VREG(32));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_pdda(_VREG(16)), __vcop_alws(), _VREG(31), _PREG(14), _AGEN(3), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_pdda(_VREG(16)), __vcop_alws(), _VREG(32), _PREG(16), _AGEN(3), _PREG(0));
   __vcop_vloop_end(4u);

}

void vcop_slidingSum(
   __vptr_uint8 pInput,
   unsigned short inputStride,
   unsigned short windowWidth,
   unsigned short windowHeight,
   unsigned short computeWidth,
   unsigned short computeHeight,
   __vptr_int32 pScratch,
   unsigned short scratchStride,
   __vptr_uint32 pSum,
   unsigned short sumStride,
   __vptr_uint16 pOffset,
   __vptr_int32 pScratchLine)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_slidingSum_init(pInput, inputStride, windowWidth, windowHeight, computeWidth, computeHeight, pScratch, scratchStride, pSum, sumStride, pOffset, pScratchLine, __pblock_vcop_slidingSum);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_slidingSum_vloops(__pblock_vcop_slidingSum);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_slidingSum_custom(
   __vptr_uint8 pInput,
   unsigned short inputStride,
   unsigned short windowWidth,
   unsigned short windowHeight,
   unsigned short computeWidth,
   unsigned short computeHeight,
   __vptr_int32 pScratch,
   unsigned short scratchStride,
   __vptr_uint32 pSum,
   unsigned short sumStride,
   __vptr_uint16 pOffset,
   __vptr_int32 pScratchLine,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_slidingSum_init(pInput, inputStride, windowWidth, windowHeight, computeWidth, computeHeight, pScratch, scratchStride, pSum, sumStride, pOffset, pScratchLine, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_slidingSum_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_ncc, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_ncc, __ALIGNOF__(int));
unsigned short __pblock_vcop_ncc[60];

unsigned int vcop_ncc_param_count(void)
{
   return 60u;
}

unsigned int vcop_ncc_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_ncc_init(
   __vptr_uint8 pOrgImg,
   unsigned short orgImgWidth,
   unsigned short orgImgHeight,
   unsigned short orgImgPitch,
   __vptr_int16 pTempImg,
   unsigned short tempImgWidth,
   unsigned short tempImgHeight,
   unsigned short tempImgPitch,
   __vptr_uint32 pSum,
   __vptr_uint16 pSumL,
   __vptr_uint16 pSumH,
   unsigned short sumStride,
   unsigned char sizeQshift,
   unsigned char qShift,
   __vptr_int32 pOutNumCC,
   __vptr_uint32 pOutDenomVar,
   unsigned short outPitch,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((orgImgHeight - tempImgHeight + 1))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (((((orgImgWidth - tempImgWidth + 1)) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_ROUND,(sizeQshift - qShift)));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 64);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pSumH);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pSumL);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pSumH+8u*sizeof(*pSum));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pSumL+8u*sizeof(*pSum));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pSum);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pSum+8u*sizeof(*pSum));
   __vcop_pblock_init16(pblock, __offset+_PREG(20), (sumStride) -((2*8u)*sizeof(*pSum))*((((((orgImgWidth - tempImgWidth + 1)) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(22), ((1<<sizeQshift) + ((tempImgWidth*tempImgHeight)/2)) / (tempImgWidth*tempImgHeight));
   __vcop_pblock_init32(pblock, __offset+_PREG(24), 16);
   __offset += 24;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), ((orgImgHeight - tempImgHeight + 1))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (((((orgImgWidth - tempImgWidth + 1)) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (tempImgHeight)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (tempImgWidth)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pSum);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pSum+8u*sizeof(*pSum));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pOrgImg);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pOrgImg+8u*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pTempImg);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pOutNumCC);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pOutNumCC+8u*sizeof(*pOutNumCC));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pOutDenomVar);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)pOutDenomVar+8u*sizeof(*pOutNumCC));
   __vcop_pblock_init16(pblock, __offset+_PREG(24), 64);
   __vcop_pblock_init16(pblock, __offset+_PREG(25), (outPitch*sizeof(*pOutNumCC)) -((2*8u)*sizeof(*pOutNumCC))*((((((orgImgWidth - tempImgWidth + 1)) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(26), (sumStride) -((2*8u)*sizeof(*pSum))*((((((orgImgWidth - tempImgWidth + 1)) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(27), (orgImgPitch) -(1)*((tempImgWidth)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(28), ((2*8u)*1) -(orgImgPitch)*((tempImgHeight)-1u) -(1)*((tempImgWidth)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(29), (orgImgPitch) -((2*8u)*1)*((((((orgImgWidth - tempImgWidth + 1)) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u) -(orgImgPitch)*((tempImgHeight)-1u) -(1)*((tempImgWidth)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(30), 2);
   __vcop_pblock_init16(pblock, __offset+_PREG(31), (sizeof(*pTempImg)*tempImgPitch) -(sizeof(*pTempImg))*((tempImgWidth)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(32),  -(sizeof(*pTempImg)*tempImgPitch)*((tempImgHeight)-1u) -(sizeof(*pTempImg))*((tempImgWidth)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(34), qShift);
   __vcop_pblock_init32(pblock, __offset+_PREG(36), 0);
   __offset += 36;

   return 60u;
}

void vcop_ncc_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("vInvTemplateSize", 16);
   #pragma VCC_VREG("v_16", 17);
   #pragma VCC_VREG("vqShift", 18);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vInput0", 19);
   #pragma VCC_VREG("vInput0_h", 20);
   #pragma VCC_VREG("vInput0_l", 21);
   #pragma VCC_VREG("vInput1", 22);
   #pragma VCC_VREG("vInput1_h", 23);
   #pragma VCC_VREG("vInput1_l", 24);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("sumWrAddr", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("v", "I3");
   #pragma EVE_REG("u", "I4");
   

   __vcop_vloop(__vcop_compute(), 18u, 12u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(22), _VREG(16));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(24), _VREG(17));
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(20), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(8), _AGEN(0), _VREG(20), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(10), _AGEN(0), _VREG(21), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(12), _AGEN(0), _VREG(23), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(14), _AGEN(0), _VREG(24), __vcop_alws());
   __vcop_vmpy(_VREG(20), _VREG(16), _VREG(20), _PREG(0));
   __vcop_vmpy(_VREG(23), _VREG(16), _VREG(23), _PREG(0));
   __vcop_vmpy(_VREG(21), _VREG(16), _VREG(21), _PREG(0));
   __vcop_vmpy(_VREG(24), _VREG(16), _VREG(24), _PREG(0));
   __vcop_vshf(_VREG(20), _VREG(17), _VREG(20));
   __vcop_vshf(_VREG(23), _VREG(17), _VREG(23));
   __vcop_vadd(_VREG(20), _VREG(21), _VREG(19));
   __vcop_vadd(_VREG(23), _VREG(24), _VREG(22));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(19), _PREG(16), _AGEN(0), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(22), _PREG(18), _AGEN(0), _PREG(6));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vDenomVar0", 25);
   #pragma VCC_VREG("vDenomVar1", 26);
   #pragma VCC_VREG("vFavg0", 27);
   #pragma VCC_VREG("vFavg1", 28);
   #pragma VCC_VREG("vNumCC0", 29);
   #pragma VCC_VREG("vNumCC1", 30);
   #pragma VCC_VREG("vInput0", 31);
   #pragma VCC_VREG("vInput1", 32);
   #pragma VCC_VREG("vTemp10", 33);
   #pragma VCC_VREG("vTemp11", 34);
   #pragma VCC_VREG("vTemp20", 35);
   #pragma VCC_VREG("vTemp21", 36);
   #pragma VCC_VREG("vTemplate", 37);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("outAddr", "A0");
   #pragma EVE_REG("sumAddr", "A1");
   #pragma EVE_REG("orgImgAddr", "A2");
   #pragma EVE_REG("tempImgAddr", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("v", "I1");
   #pragma EVE_REG("u", "I2");
   #pragma EVE_REG("y", "I3");
   #pragma EVE_REG("x", "I4");
   

   __vcop_vloop(__vcop_compute(), 35u, 18u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(34), _VREG(18));
   __vcop_vinit(__vcop_sizeW(), __vcop_i34_zero(), _PREG(36), _VREG(29));
   __vcop_vinit(__vcop_sizeW(), __vcop_i34_zero(), _PREG(36), _VREG(30));
   __vcop_vinit(__vcop_sizeW(), __vcop_i34_zero(), _PREG(36), _VREG(25));
   __vcop_vinit(__vcop_sizeW(), __vcop_i34_zero(), _PREG(36), _VREG(26));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(24), _PREG(25));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(0), _PREG(24), _PREG(26));
   __vcop_vagen(_AGEN(2), _PREG(1), _PREG(27), _PREG(28), _PREG(29));
   __vcop_vagen(_AGEN(3), _PREG(30), _PREG(31), _PREG(32), _PREG(32));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(6), _AGEN(1), _VREG(27), __vcop_i34_zero());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(8), _AGEN(1), _VREG(28), __vcop_i34_zero());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(10), _AGEN(2), _VREG(31), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(12), _AGEN(2), _VREG(32), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_1pt(), _PREG(14), _AGEN(3), _VREG(37), __vcop_alws());
   __vcop_vshf(_VREG(31), _VREG(18), _VREG(31));
   __vcop_vshf(_VREG(32), _VREG(18), _VREG(32));
   __vcop_vsub(_VREG(31), _VREG(27), _VREG(31));
   __vcop_vsub(_VREG(32), _VREG(28), _VREG(32));
   __vcop_vmpy(_VREG(31), _VREG(37), _VREG(33), _PREG(0));
   __vcop_vmpy(_VREG(32), _VREG(37), _VREG(34), _PREG(0));
   __vcop_vmpy(_VREG(31), _VREG(31), _VREG(35), _PREG(0));
   __vcop_vmpy(_VREG(32), _VREG(32), _VREG(36), _PREG(0));
   __vcop_vrnd(_VREG(33), _VREG(18), _VREG(33));
   __vcop_vrnd(_VREG(34), _VREG(18), _VREG(34));
   __vcop_vrnd(_VREG(35), _VREG(18), _VREG(35));
   __vcop_vrnd(_VREG(36), _VREG(18), _VREG(36));
   __vcop_vadd(_VREG(29), _VREG(33), _VREG(29));
   __vcop_vadd(_VREG(30), _VREG(34), _VREG(30));
   __vcop_vadd(_VREG(25), _VREG(35), _VREG(25));
   __vcop_vadd(_VREG(26), _VREG(36), _VREG(26));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_last_i34(), _VREG(29), _PREG(16), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_last_i34(), _VREG(30), _PREG(18), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_last_i34(), _VREG(25), _PREG(20), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_last_i34(), _VREG(26), _PREG(22), _AGEN(0), _PREG(0));
   __vcop_vloop_end(2u);

}

void vcop_ncc(
   __vptr_uint8 pOrgImg,
   unsigned short orgImgWidth,
   unsigned short orgImgHeight,
   unsigned short orgImgPitch,
   __vptr_int16 pTempImg,
   unsigned short tempImgWidth,
   unsigned short tempImgHeight,
   unsigned short tempImgPitch,
   __vptr_uint32 pSum,
   __vptr_uint16 pSumL,
   __vptr_uint16 pSumH,
   unsigned short sumStride,
   unsigned char sizeQshift,
   unsigned char qShift,
   __vptr_int32 pOutNumCC,
   __vptr_uint32 pOutDenomVar,
   unsigned short outPitch)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_ncc_init(pOrgImg, orgImgWidth, orgImgHeight, orgImgPitch, pTempImg, tempImgWidth, tempImgHeight, tempImgPitch, pSum, pSumL, pSumH, sumStride, sizeQshift, qShift, pOutNumCC, pOutDenomVar, outPitch, __pblock_vcop_ncc);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_ncc_vloops(__pblock_vcop_ncc);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_ncc_custom(
   __vptr_uint8 pOrgImg,
   unsigned short orgImgWidth,
   unsigned short orgImgHeight,
   unsigned short orgImgPitch,
   __vptr_int16 pTempImg,
   unsigned short tempImgWidth,
   unsigned short tempImgHeight,
   unsigned short tempImgPitch,
   __vptr_uint32 pSum,
   __vptr_uint16 pSumL,
   __vptr_uint16 pSumH,
   unsigned short sumStride,
   unsigned char sizeQshift,
   unsigned char qShift,
   __vptr_int32 pOutNumCC,
   __vptr_uint32 pOutDenomVar,
   unsigned short outPitch,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_ncc_init(pOrgImg, orgImgWidth, orgImgHeight, orgImgPitch, pTempImg, tempImgWidth, tempImgHeight, tempImgPitch, pSum, pSumL, pSumH, sumStride, sizeQshift, qShift, pOutNumCC, pOutDenomVar, outPitch, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_ncc_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_ncc_qShift8, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_ncc_qShift8, __ALIGNOF__(int));
unsigned short __pblock_vcop_ncc_qShift8[60];

unsigned int vcop_ncc_qShift8_param_count(void)
{
   return 60u;
}

unsigned int vcop_ncc_qShift8_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_ncc_qShift8_init(
   __vptr_uint8 pOrgImg,
   unsigned short orgImgWidth,
   unsigned short orgImgHeight,
   unsigned short orgImgPitch,
   __vptr_int16 pTempImg,
   unsigned short tempImgWidth,
   unsigned short tempImgHeight,
   unsigned short tempImgPitch,
   __vptr_uint32 pSum,
   __vptr_uint16 pSumL,
   __vptr_uint16 pSumH,
   unsigned short sumStride,
   unsigned char sizeQshift,
   unsigned char qShift,
   __vptr_int32 pOutNumCC,
   __vptr_uint32 pOutDenomVar,
   unsigned short outPitch,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((orgImgHeight - tempImgHeight + 1))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (((((orgImgWidth - tempImgWidth + 1)) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_ROUND,(sizeQshift - qShift)));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 64);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pSumH);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pSumL);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pSumH+8u*sizeof(*pSum));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pSumL+8u*sizeof(*pSum));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pSum);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pSum+8u*sizeof(*pSum));
   __vcop_pblock_init16(pblock, __offset+_PREG(20), (sumStride) -((2*8u)*sizeof(*pSum))*((((((orgImgWidth - tempImgWidth + 1)) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(22), ((1<<sizeQshift) + ((tempImgWidth*tempImgHeight)/2)) / (tempImgWidth*tempImgHeight));
   __vcop_pblock_init32(pblock, __offset+_PREG(24), 16);
   __offset += 24;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), ((orgImgHeight - tempImgHeight + 1))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (((((orgImgWidth - tempImgWidth + 1)) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (tempImgHeight)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (tempImgWidth)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pSum);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pSum+8u*sizeof(*pSum));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pOrgImg);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pOrgImg+8u*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pTempImg);
   __vcop_pblock_init16(pblock, __offset+_PREG(16), __vcop_vop_round(1, 8));
   __vcop_pblock_init16(pblock, __offset+_PREG(17), 64);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pOutNumCC);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pOutNumCC+8u*sizeof(*pOutNumCC));
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)pOutDenomVar);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)pOutDenomVar+8u*sizeof(*pOutNumCC));
   __vcop_pblock_init16(pblock, __offset+_PREG(26), (outPitch*sizeof(*pOutNumCC)) -((2*8u)*sizeof(*pOutNumCC))*((((((orgImgWidth - tempImgWidth + 1)) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(27), (sumStride) -((2*8u)*sizeof(*pSum))*((((((orgImgWidth - tempImgWidth + 1)) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(28), (orgImgPitch) -(1)*((tempImgWidth)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(29), ((2*8u)*1) -(orgImgPitch)*((tempImgHeight)-1u) -(1)*((tempImgWidth)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(30), (orgImgPitch) -((2*8u)*1)*((((((orgImgWidth - tempImgWidth + 1)) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u) -(orgImgPitch)*((tempImgHeight)-1u) -(1)*((tempImgWidth)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(31), 2);
   __vcop_pblock_init16(pblock, __offset+_PREG(32), (sizeof(*pTempImg)*tempImgPitch) -(sizeof(*pTempImg))*((tempImgWidth)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(33),  -(sizeof(*pTempImg)*tempImgPitch)*((tempImgHeight)-1u) -(sizeof(*pTempImg))*((tempImgWidth)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(34), qShift);
   __vcop_pblock_init32(pblock, __offset+_PREG(36), 0);
   __offset += 36;

   return 60u;
}

void vcop_ncc_qShift8_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("vInvTemplateSize", 16);
   #pragma VCC_VREG("v_16", 17);
   #pragma VCC_VREG("vqShift", 18);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vInput0", 19);
   #pragma VCC_VREG("vInput0_h", 20);
   #pragma VCC_VREG("vInput0_l", 21);
   #pragma VCC_VREG("vInput1", 22);
   #pragma VCC_VREG("vInput1_h", 23);
   #pragma VCC_VREG("vInput1_l", 24);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("sumWrAddr", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("v", "I3");
   #pragma EVE_REG("u", "I4");
   

   __vcop_vloop(__vcop_compute(), 18u, 12u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(22), _VREG(16));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(24), _VREG(17));
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(20), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(8), _AGEN(0), _VREG(20), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(10), _AGEN(0), _VREG(21), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(12), _AGEN(0), _VREG(23), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(14), _AGEN(0), _VREG(24), __vcop_alws());
   __vcop_vmpy(_VREG(20), _VREG(16), _VREG(20), _PREG(0));
   __vcop_vmpy(_VREG(23), _VREG(16), _VREG(23), _PREG(0));
   __vcop_vmpy(_VREG(21), _VREG(16), _VREG(21), _PREG(0));
   __vcop_vmpy(_VREG(24), _VREG(16), _VREG(24), _PREG(0));
   __vcop_vshf(_VREG(20), _VREG(17), _VREG(20));
   __vcop_vshf(_VREG(23), _VREG(17), _VREG(23));
   __vcop_vadd(_VREG(20), _VREG(21), _VREG(19));
   __vcop_vadd(_VREG(23), _VREG(24), _VREG(22));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(19), _PREG(16), _AGEN(0), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(22), _PREG(18), _AGEN(0), _PREG(6));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vDenomVar0", 25);
   #pragma VCC_VREG("vDenomVar1", 26);
   #pragma VCC_VREG("vFavg0", 27);
   #pragma VCC_VREG("vFavg1", 28);
   #pragma VCC_VREG("vNumCC0", 29);
   #pragma VCC_VREG("vNumCC1", 30);
   #pragma VCC_VREG("vInput0", 31);
   #pragma VCC_VREG("vInput1", 32);
   #pragma VCC_VREG("vTemp10", 33);
   #pragma VCC_VREG("vTemp11", 34);
   #pragma VCC_VREG("vTemp20", 35);
   #pragma VCC_VREG("vTemp21", 36);
   #pragma VCC_VREG("vTemplate", 37);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("outAddr", "A0");
   #pragma EVE_REG("sumAddr", "A1");
   #pragma EVE_REG("orgImgAddr", "A2");
   #pragma EVE_REG("tempImgAddr", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("v", "I1");
   #pragma EVE_REG("u", "I2");
   #pragma EVE_REG("y", "I3");
   #pragma EVE_REG("x", "I4");
   

   __vcop_vloop(__vcop_compute(), 27u, 18u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(34), _VREG(18));
   __vcop_vinit(__vcop_sizeW(), __vcop_i34_zero(), _PREG(36), _VREG(29));
   __vcop_vinit(__vcop_sizeW(), __vcop_i34_zero(), _PREG(36), _VREG(30));
   __vcop_vinit(__vcop_sizeW(), __vcop_i34_zero(), _PREG(36), _VREG(25));
   __vcop_vinit(__vcop_sizeW(), __vcop_i34_zero(), _PREG(36), _VREG(26));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(17), _PREG(26));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(0), _PREG(17), _PREG(27));
   __vcop_vagen(_AGEN(2), _PREG(1), _PREG(28), _PREG(29), _PREG(30));
   __vcop_vagen(_AGEN(3), _PREG(31), _PREG(32), _PREG(33), _PREG(33));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(6), _AGEN(1), _VREG(27), __vcop_i34_zero());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(8), _AGEN(1), _VREG(28), __vcop_i34_zero());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(10), _AGEN(2), _VREG(31), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(12), _AGEN(2), _VREG(32), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_1pt(), _PREG(14), _AGEN(3), _VREG(37), __vcop_alws());
   __vcop_vshf(_VREG(31), _VREG(18), _VREG(31));
   __vcop_vshf(_VREG(32), _VREG(18), _VREG(32));
   __vcop_vsub(_VREG(31), _VREG(27), _VREG(31));
   __vcop_vsub(_VREG(32), _VREG(28), _VREG(32));
   __vcop_vmadd(_VREG(31), _VREG(37), _VREG(29), _PREG(16));
   __vcop_vmadd(_VREG(32), _VREG(37), _VREG(30), _PREG(16));
   __vcop_vmadd(_VREG(31), _VREG(31), _VREG(25), _PREG(16));
   __vcop_vmadd(_VREG(32), _VREG(32), _VREG(26), _PREG(16));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_last_i34(), _VREG(29), _PREG(18), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_last_i34(), _VREG(30), _PREG(20), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_last_i34(), _VREG(25), _PREG(22), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_last_i34(), _VREG(26), _PREG(24), _AGEN(0), _PREG(0));
   __vcop_vloop_end(2u);

}

void vcop_ncc_qShift8(
   __vptr_uint8 pOrgImg,
   unsigned short orgImgWidth,
   unsigned short orgImgHeight,
   unsigned short orgImgPitch,
   __vptr_int16 pTempImg,
   unsigned short tempImgWidth,
   unsigned short tempImgHeight,
   unsigned short tempImgPitch,
   __vptr_uint32 pSum,
   __vptr_uint16 pSumL,
   __vptr_uint16 pSumH,
   unsigned short sumStride,
   unsigned char sizeQshift,
   unsigned char qShift,
   __vptr_int32 pOutNumCC,
   __vptr_uint32 pOutDenomVar,
   unsigned short outPitch)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_ncc_qShift8_init(pOrgImg, orgImgWidth, orgImgHeight, orgImgPitch, pTempImg, tempImgWidth, tempImgHeight, tempImgPitch, pSum, pSumL, pSumH, sumStride, sizeQshift, qShift, pOutNumCC, pOutDenomVar, outPitch, __pblock_vcop_ncc_qShift8);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_ncc_qShift8_vloops(__pblock_vcop_ncc_qShift8);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_ncc_qShift8_custom(
   __vptr_uint8 pOrgImg,
   unsigned short orgImgWidth,
   unsigned short orgImgHeight,
   unsigned short orgImgPitch,
   __vptr_int16 pTempImg,
   unsigned short tempImgWidth,
   unsigned short tempImgHeight,
   unsigned short tempImgPitch,
   __vptr_uint32 pSum,
   __vptr_uint16 pSumL,
   __vptr_uint16 pSumH,
   unsigned short sumStride,
   unsigned char sizeQshift,
   unsigned char qShift,
   __vptr_int32 pOutNumCC,
   __vptr_uint32 pOutDenomVar,
   unsigned short outPitch,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_ncc_qShift8_init(pOrgImg, orgImgWidth, orgImgHeight, orgImgPitch, pTempImg, tempImgWidth, tempImgHeight, tempImgPitch, pSum, pSumL, pSumH, sumStride, sizeQshift, qShift, pOutNumCC, pOutDenomVar, outPitch, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_ncc_qShift8_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_ncc_qShift0, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_ncc_qShift0, __ALIGNOF__(int));
unsigned short __pblock_vcop_ncc_qShift0[60];

unsigned int vcop_ncc_qShift0_param_count(void)
{
   return 60u;
}

unsigned int vcop_ncc_qShift0_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_ncc_qShift0_init(
   __vptr_uint8 pOrgImg,
   unsigned short orgImgWidth,
   unsigned short orgImgHeight,
   unsigned short orgImgPitch,
   __vptr_int16 pTempImg,
   unsigned short tempImgWidth,
   unsigned short tempImgHeight,
   unsigned short tempImgPitch,
   __vptr_uint32 pSum,
   __vptr_uint16 pSumL,
   __vptr_uint16 pSumH,
   unsigned short sumStride,
   unsigned char sizeQshift,
   unsigned char qShift,
   __vptr_int32 pOutNumCC,
   __vptr_uint32 pOutDenomVar,
   unsigned short outPitch,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((orgImgHeight - tempImgHeight + 1))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (((((orgImgWidth - tempImgWidth + 1)) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_ROUND,(sizeQshift - qShift)));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 64);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pSumH);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pSumL);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pSumH+8u*sizeof(*pSum));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pSumL+8u*sizeof(*pSum));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pSum);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pSum+8u*sizeof(*pSum));
   __vcop_pblock_init16(pblock, __offset+_PREG(20), (sumStride) -((2*8u)*sizeof(*pSum))*((((((orgImgWidth - tempImgWidth + 1)) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(22), ((1<<sizeQshift) + ((tempImgWidth*tempImgHeight)/2)) / (tempImgWidth*tempImgHeight));
   __vcop_pblock_init32(pblock, __offset+_PREG(24), 16);
   __offset += 24;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), ((orgImgHeight - tempImgHeight + 1))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (((((orgImgWidth - tempImgWidth + 1)) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (tempImgHeight)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (tempImgWidth)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pSum);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pSum+8u*sizeof(*pSum));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pOrgImg);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pOrgImg+8u*1);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pTempImg);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pOutNumCC);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pOutNumCC+8u*sizeof(*pOutNumCC));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pOutDenomVar);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)pOutDenomVar+8u*sizeof(*pOutNumCC));
   __vcop_pblock_init16(pblock, __offset+_PREG(24), 64);
   __vcop_pblock_init16(pblock, __offset+_PREG(25), (outPitch*sizeof(*pOutNumCC)) -((2*8u)*sizeof(*pOutNumCC))*((((((orgImgWidth - tempImgWidth + 1)) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(26), (sumStride) -((2*8u)*sizeof(*pSum))*((((((orgImgWidth - tempImgWidth + 1)) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(27), (orgImgPitch) -(1)*((tempImgWidth)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(28), ((2*8u)*1) -(orgImgPitch)*((tempImgHeight)-1u) -(1)*((tempImgWidth)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(29), (orgImgPitch) -((2*8u)*1)*((((((orgImgWidth - tempImgWidth + 1)) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u) -(orgImgPitch)*((tempImgHeight)-1u) -(1)*((tempImgWidth)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(30), 2);
   __vcop_pblock_init16(pblock, __offset+_PREG(31), (sizeof(*pTempImg)*tempImgPitch) -(sizeof(*pTempImg))*((tempImgWidth)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(32),  -(sizeof(*pTempImg)*tempImgPitch)*((tempImgHeight)-1u) -(sizeof(*pTempImg))*((tempImgWidth)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(34), qShift);
   __vcop_pblock_init32(pblock, __offset+_PREG(36), 0);
   __offset += 36;

   return 60u;
}

void vcop_ncc_qShift0_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("vInvTemplateSize", 16);
   #pragma VCC_VREG("v_16", 17);
   #pragma VCC_VREG("vqShift", 18);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vInput0", 19);
   #pragma VCC_VREG("vInput0_h", 20);
   #pragma VCC_VREG("vInput0_l", 21);
   #pragma VCC_VREG("vInput1", 22);
   #pragma VCC_VREG("vInput1_h", 23);
   #pragma VCC_VREG("vInput1_l", 24);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("sumWrAddr", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("v", "I3");
   #pragma EVE_REG("u", "I4");
   

   __vcop_vloop(__vcop_compute(), 18u, 12u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(22), _VREG(16));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(24), _VREG(17));
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(20), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(8), _AGEN(0), _VREG(20), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(10), _AGEN(0), _VREG(21), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(12), _AGEN(0), _VREG(23), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(14), _AGEN(0), _VREG(24), __vcop_alws());
   __vcop_vmpy(_VREG(20), _VREG(16), _VREG(20), _PREG(0));
   __vcop_vmpy(_VREG(23), _VREG(16), _VREG(23), _PREG(0));
   __vcop_vmpy(_VREG(21), _VREG(16), _VREG(21), _PREG(0));
   __vcop_vmpy(_VREG(24), _VREG(16), _VREG(24), _PREG(0));
   __vcop_vshf(_VREG(20), _VREG(17), _VREG(20));
   __vcop_vshf(_VREG(23), _VREG(17), _VREG(23));
   __vcop_vadd(_VREG(20), _VREG(21), _VREG(19));
   __vcop_vadd(_VREG(23), _VREG(24), _VREG(22));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(19), _PREG(16), _AGEN(0), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(22), _PREG(18), _AGEN(0), _PREG(6));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vDenomVar0", 25);
   #pragma VCC_VREG("vDenomVar1", 26);
   #pragma VCC_VREG("vFavg0", 27);
   #pragma VCC_VREG("vFavg1", 28);
   #pragma VCC_VREG("vNumCC0", 29);
   #pragma VCC_VREG("vNumCC1", 30);
   #pragma VCC_VREG("vInput0", 31);
   #pragma VCC_VREG("vInput1", 32);
   #pragma VCC_VREG("vTemp10", 33);
   #pragma VCC_VREG("vTemp11", 34);
   #pragma VCC_VREG("vTemp20", 35);
   #pragma VCC_VREG("vTemp21", 36);
   #pragma VCC_VREG("vTemplate", 37);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("outAddr", "A0");
   #pragma EVE_REG("sumAddr", "A1");
   #pragma EVE_REG("orgImgAddr", "A2");
   #pragma EVE_REG("tempImgAddr", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("v", "I1");
   #pragma EVE_REG("u", "I2");
   #pragma EVE_REG("y", "I3");
   #pragma EVE_REG("x", "I4");
   

   __vcop_vloop(__vcop_compute(), 27u, 18u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(34), _VREG(18));
   __vcop_vinit(__vcop_sizeW(), __vcop_i34_zero(), _PREG(36), _VREG(29));
   __vcop_vinit(__vcop_sizeW(), __vcop_i34_zero(), _PREG(36), _VREG(30));
   __vcop_vinit(__vcop_sizeW(), __vcop_i34_zero(), _PREG(36), _VREG(25));
   __vcop_vinit(__vcop_sizeW(), __vcop_i34_zero(), _PREG(36), _VREG(26));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(24), _PREG(25));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(0), _PREG(24), _PREG(26));
   __vcop_vagen(_AGEN(2), _PREG(1), _PREG(27), _PREG(28), _PREG(29));
   __vcop_vagen(_AGEN(3), _PREG(30), _PREG(31), _PREG(32), _PREG(32));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(6), _AGEN(1), _VREG(27), __vcop_i34_zero());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(8), _AGEN(1), _VREG(28), __vcop_i34_zero());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(10), _AGEN(2), _VREG(31), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(12), _AGEN(2), _VREG(32), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_1pt(), _PREG(14), _AGEN(3), _VREG(37), __vcop_alws());
   __vcop_vshf(_VREG(31), _VREG(18), _VREG(31));
   __vcop_vshf(_VREG(32), _VREG(18), _VREG(32));
   __vcop_vsub(_VREG(31), _VREG(27), _VREG(31));
   __vcop_vsub(_VREG(32), _VREG(28), _VREG(32));
   __vcop_vmadd(_VREG(31), _VREG(37), _VREG(29), _PREG(0));
   __vcop_vmadd(_VREG(32), _VREG(37), _VREG(30), _PREG(0));
   __vcop_vmadd(_VREG(31), _VREG(31), _VREG(25), _PREG(0));
   __vcop_vmadd(_VREG(32), _VREG(32), _VREG(26), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_last_i34(), _VREG(29), _PREG(16), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_last_i34(), _VREG(30), _PREG(18), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_last_i34(), _VREG(25), _PREG(20), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_last_i34(), _VREG(26), _PREG(22), _AGEN(0), _PREG(0));
   __vcop_vloop_end(2u);

}

void vcop_ncc_qShift0(
   __vptr_uint8 pOrgImg,
   unsigned short orgImgWidth,
   unsigned short orgImgHeight,
   unsigned short orgImgPitch,
   __vptr_int16 pTempImg,
   unsigned short tempImgWidth,
   unsigned short tempImgHeight,
   unsigned short tempImgPitch,
   __vptr_uint32 pSum,
   __vptr_uint16 pSumL,
   __vptr_uint16 pSumH,
   unsigned short sumStride,
   unsigned char sizeQshift,
   unsigned char qShift,
   __vptr_int32 pOutNumCC,
   __vptr_uint32 pOutDenomVar,
   unsigned short outPitch)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_ncc_qShift0_init(pOrgImg, orgImgWidth, orgImgHeight, orgImgPitch, pTempImg, tempImgWidth, tempImgHeight, tempImgPitch, pSum, pSumL, pSumH, sumStride, sizeQshift, qShift, pOutNumCC, pOutDenomVar, outPitch, __pblock_vcop_ncc_qShift0);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_ncc_qShift0_vloops(__pblock_vcop_ncc_qShift0);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_ncc_qShift0_custom(
   __vptr_uint8 pOrgImg,
   unsigned short orgImgWidth,
   unsigned short orgImgHeight,
   unsigned short orgImgPitch,
   __vptr_int16 pTempImg,
   unsigned short tempImgWidth,
   unsigned short tempImgHeight,
   unsigned short tempImgPitch,
   __vptr_uint32 pSum,
   __vptr_uint16 pSumL,
   __vptr_uint16 pSumH,
   unsigned short sumStride,
   unsigned char sizeQshift,
   unsigned char qShift,
   __vptr_int32 pOutNumCC,
   __vptr_uint32 pOutDenomVar,
   unsigned short outPitch,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_ncc_qShift0_init(pOrgImg, orgImgWidth, orgImgHeight, orgImgPitch, pTempImg, tempImgWidth, tempImgHeight, tempImgPitch, pSum, pSumL, pSumH, sumStride, sizeQshift, qShift, pOutNumCC, pOutDenomVar, outPitch, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_ncc_qShift0_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

