#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_disparity_sad16_first_row_firstCall, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_disparity_sad16_first_row_firstCall, __ALIGNOF__(int));
unsigned short __pblock_vcop_disparity_sad16_first_row_firstCall[92];

unsigned int vcop_disparity_sad16_first_row_firstCall_param_count(void)
{
   return 92u;
}

unsigned int vcop_disparity_sad16_first_row_firstCall_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_disparity_sad16_first_row_firstCall_init(
   __vptr_uint16 pLeft,
   __vptr_uint16 pRight,
   unsigned short leftStride,
   unsigned short rightStride,
   unsigned char winWidth,
   unsigned char winHeight,
   __vptr_uint8 pDisparityOutput,
   __vptr_uint32 pMinCostOutput,
   __vptr_uint32 pAllCostOutput,
   unsigned short allCostOutputStride,
   unsigned short width,
   unsigned char numDisparities,
   unsigned char disparityStep,
   __vptr_uint8 pCollateMask,
   __vptr_uint16 pOffset,
   __vptr_int32 pScratch0,
   __vptr_uint32 pCarryOver,
   unsigned short scratchStride,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), ((numDisparities/disparityStep))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (winHeight)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (winWidth)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pLeft);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pRight+(disparityStep-1)*sizeof(*pLeft));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pAllCostOutput);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pCarryOver);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), (allCostOutputStride));
   __vcop_pblock_init16(pblock, __offset+_PREG(15), 2);
   __vcop_pblock_init16(pblock, __offset+_PREG(16), (leftStride*sizeof(*pLeft)) -(sizeof(*pLeft))*((winWidth)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(17),  -(leftStride*sizeof(*pLeft))*((winHeight)-1u) -(sizeof(*pLeft))*((winWidth)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(18), (rightStride*sizeof(*pLeft)) -(sizeof(*pLeft))*((winWidth)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(19), (disparityStep*sizeof(*pLeft)) -(rightStride*sizeof(*pLeft))*((winHeight)-1u) -(sizeof(*pLeft))*((winWidth)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pCollateMask);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), 0);
   __offset += 22;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), ((numDisparities/disparityStep))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((((width-(8u)) + (8u)-1) & ~((8u)-1))/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (winHeight)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pLeft+8u*sizeof(*pLeft)+(winWidth-1)*sizeof(*pLeft));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pRight+(disparityStep-1)*sizeof(*pLeft)+8u*sizeof(*pLeft)+(winWidth-1)*sizeof(*pLeft));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pLeft+8u*sizeof(*pLeft)-sizeof(*pLeft));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pRight+(disparityStep-1)*sizeof(*pLeft)+8u*sizeof(*pLeft)-sizeof(*pLeft));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pScratch0);
   __vcop_pblock_init16(pblock, __offset+_PREG(16), (8u*scratchStride));
   __vcop_pblock_init16(pblock, __offset+_PREG(17), (sizeof(*pAllCostOutput)) -(8u*scratchStride)*(((((width-(8u)) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(18), (leftStride*sizeof(*pLeft)));
   __vcop_pblock_init16(pblock, __offset+_PREG(19), (8u*sizeof(*pLeft)) -(leftStride*sizeof(*pLeft))*((winHeight)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(20),  -(8u*sizeof(*pLeft))*(((((width-(8u)) + (8u)-1) & ~((8u)-1))/(8u))-1u) -(leftStride*sizeof(*pLeft))*((winHeight)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(21), (rightStride*sizeof(*pLeft)));
   __vcop_pblock_init16(pblock, __offset+_PREG(22), (8u*sizeof(*pLeft)) -(rightStride*sizeof(*pLeft))*((winHeight)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(23), (disparityStep*sizeof(*pLeft)) -(8u*sizeof(*pLeft))*(((((width-(8u)) + (8u)-1) & ~((8u)-1))/(8u))-1u) -(rightStride*sizeof(*pLeft))*((winHeight)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)pOffset);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), 0);
   __offset += 26;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((((numDisparities/disparityStep) + (8u)-1) & ~((8u)-1))/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((width-(8u)))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pScratch0);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pAllCostOutput+8u*sizeof(*pAllCostOutput));
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), (scratchStride));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), (8u*sizeof(*pScratch0)) -(scratchStride)*(((width-(8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(13), 4);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), (8u*allCostOutputStride) -(sizeof(*pAllCostOutput))*(((width-(8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pOffset+16);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pCarryOver);
   __offset += 18;

   /* Loop 4 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((((width) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((numDisparities/disparityStep))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pAllCostOutput+(numDisparities/disparityStep-1)*allCostOutputStride);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pAllCostOutput+(numDisparities/disparityStep-1)*allCostOutputStride+8u*sizeof(*pAllCostOutput));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pMinCostOutput);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pMinCostOutput+8u*sizeof(*pMinCostOutput));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pDisparityOutput);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pDisparityOutput+8u*sizeof(*pDisparityOutput));
   __vcop_pblock_init16(pblock, __offset+_PREG(20), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(21), 64);
   __vcop_pblock_init16(pblock, __offset+_PREG(22), (-allCostOutputStride));
   __vcop_pblock_init16(pblock, __offset+_PREG(23), ((2*8u)*sizeof(*pAllCostOutput)) -(-allCostOutputStride)*(((numDisparities/disparityStep))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(24), disparityStep);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), 4294967295);
   __offset += 26;

   return 92u;
}

void vcop_disparity_sad16_first_row_firstCall_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("vDisparityStep", 16);
   #pragma VCC_VREG("vMask", 17);
   #pragma VCC_VREG("vOfst", 18);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vCost", 19);
   #pragma VCC_VREG("vLeft", 20);
   #pragma VCC_VREG("vRight", 21);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("agen0", "A0");
   #pragma EVE_REG("agenCost", "A1");
   #pragma EVE_REG("agenLeft", "A2");
   #pragma EVE_REG("agenRight", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("d", "I2");
   #pragma EVE_REG("h", "I3");
   #pragma EVE_REG("w", "I4");
   

   __vcop_vloop(__vcop_compute(), 12u, 11u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i34_zero(), _PREG(22), _VREG(19));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(0), _PREG(14), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(15), _PREG(16), _PREG(17), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(15), _PREG(18), _PREG(19), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_nbits(), _PREG(20), _AGEN(0), _VREG(17), __vcop_once());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(6), _AGEN(2), _VREG(20), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(8), _AGEN(3), _VREG(21), __vcop_alws());
   __vcop_vsad(_VREG(20), _VREG(21), _VREG(19));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_last_i34(), _VREG(19), _PREG(10), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_predicate(_VREG(17)), __vcop_sizeWU(), __vcop_collat(), __vcop_last_i34(), _VREG(19), _PREG(12), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vColDiff", 22);
   #pragma VCC_VREG("vLeftL", 23);
   #pragma VCC_VREG("vLeftR", 24);
   #pragma VCC_VREG("vRightL", 25);
   #pragma VCC_VREG("vRightR", 26);
   #pragma VCC_VREG("vSAD", 27);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("agen0", "A0");
   #pragma EVE_REG("agenOffset", "A1");
   #pragma EVE_REG("agenOut", "A2");
   #pragma EVE_REG("agenLeft", "A3");
   #pragma EVE_REG("agenRight", "A4");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("d", "I2");
   #pragma EVE_REG("c", "I3");
   #pragma EVE_REG("h", "I4");
   

   __vcop_vloop(__vcop_compute(), 16u, 13u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(26), _VREG(22));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(0), _PREG(16), _PREG(17), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(18), _PREG(19), _PREG(20), _PREG(0));
   __vcop_vagen(_AGEN(4), _PREG(21), _PREG(22), _PREG(23), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(24), _AGEN(1), _VREG(18), __vcop_once());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(6), _AGEN(3), _VREG(24), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(8), _AGEN(4), _VREG(26), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(10), _AGEN(3), _VREG(23), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(12), _AGEN(4), _VREG(25), __vcop_alws());
   __vcop_vsad(_VREG(24), _VREG(26), _VREG(22));
   __vcop_vabsdif(_VREG(23), _VREG(25), _VREG(27));
   __vcop_vsub(_VREG(22), _VREG(27), _VREG(22));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_pdda(_VREG(18)), __vcop_last_i4(), _VREG(22), _PREG(14), _AGEN(2), _PREG(0));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vAcc", 28);
   #pragma VCC_VREG("vEven", 29);
   #pragma VCC_VREG("vEvenAcc", 30);
   #pragma VCC_VREG("vOdd", 31);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("agen0", "A0");
   #pragma EVE_REG("agenOffset", "A1");
   #pragma EVE_REG("agenScratch2", "A2");
   #pragma EVE_REG("agenIn", "A3");
   #pragma EVE_REG("agenOut", "A4");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("d", "I3");
   #pragma EVE_REG("c", "I4");
   

   __vcop_vloop(__vcop_compute(), 12u, 9u, 3u);
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(0), _PREG(10), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(11), _PREG(12), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(4), _PREG(13), _PREG(14), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(16), _AGEN(1), _VREG(18), __vcop_once());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(18), _AGEN(2), _VREG(28), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(6), _AGEN(3), _VREG(29), __vcop_alws());
   __vcop_vadd(_VREG(28), _VREG(29), _VREG(28));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_pdda(_VREG(18)), __vcop_alws(), _VREG(28), _PREG(8), _AGEN(4), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_last_i4(), _VREG(28), _PREG(18), _AGEN(2), _PREG(0));
   __vcop_vloop_end(3u);

   /* VLOOP 4 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vDisp0", 32);
   #pragma VCC_VREG("vDisp1", 33);
   #pragma VCC_VREG("vMin0", 34);
   #pragma VCC_VREG("vMin1", 35);
   #pragma VCC_VREG("vCost0", 36);
   #pragma VCC_VREG("vCost1", 37);
   #pragma VCC_VREG("vIdx", 38);
   #pragma VCC_VREG("vMinFlag0", 39);
   #pragma VCC_VREG("vMinFlag1", 40);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("agen0", "A0");
   #pragma EVE_REG("agenOffset", "A1");
   #pragma EVE_REG("agenDisp", "A2");
   #pragma EVE_REG("agenMinCost", "A3");
   #pragma EVE_REG("agenCost", "A4");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("c", "I3");
   #pragma EVE_REG("d", "I4");
   

   __vcop_vloop(__vcop_compute(), 23u, 13u, 4u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(24), _VREG(16));
   __vcop_vinit(__vcop_sizeWU(), __vcop_i4_zero(), _PREG(26), _VREG(34));
   __vcop_vinit(__vcop_sizeWU(), __vcop_i4_zero(), _PREG(26), _VREG(35));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(6), _VREG(32));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(6), _VREG(33));
   __vcop_vinit(__vcop_sizeHU(), __vcop_alws(), _PREG(68), _VREG(38));
   __vcop_vagen(_AGEN(2), _PREG(0), _PREG(20), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(0), _PREG(21), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(4), _PREG(22), _PREG(23), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(8), _AGEN(4), _VREG(36), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(10), _AGEN(4), _VREG(37), __vcop_alws());
   __vcop_vmpy(_VREG(38), _VREG(16), _VREG(38), _PREG(0));
   __vcop_vminsetf(_VREG(36), _VREG(34), _VREG(39));
   __vcop_vminsetf(_VREG(37), _VREG(35), _VREG(40));
   __vcop_vsel(_VREG(39), _VREG(38), _VREG(32));
   __vcop_vsel(_VREG(40), _VREG(38), _VREG(33));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_last_i4(), _VREG(34), _PREG(12), _AGEN(3), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_last_i4(), _VREG(35), _PREG(14), _AGEN(3), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_last_i4(), _VREG(32), _PREG(16), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_last_i4(), _VREG(33), _PREG(18), _AGEN(2), _PREG(0));
   __vcop_vloop_end(4u);

}

void vcop_disparity_sad16_first_row_firstCall(
   __vptr_uint16 pLeft,
   __vptr_uint16 pRight,
   unsigned short leftStride,
   unsigned short rightStride,
   unsigned char winWidth,
   unsigned char winHeight,
   __vptr_uint8 pDisparityOutput,
   __vptr_uint32 pMinCostOutput,
   __vptr_uint32 pAllCostOutput,
   unsigned short allCostOutputStride,
   unsigned short width,
   unsigned char numDisparities,
   unsigned char disparityStep,
   __vptr_uint8 pCollateMask,
   __vptr_uint16 pOffset,
   __vptr_int32 pScratch0,
   __vptr_uint32 pCarryOver,
   unsigned short scratchStride)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_disparity_sad16_first_row_firstCall_init(pLeft, pRight, leftStride, rightStride, winWidth, winHeight, pDisparityOutput, pMinCostOutput, pAllCostOutput, allCostOutputStride, width, numDisparities, disparityStep, pCollateMask, pOffset, pScratch0, pCarryOver, scratchStride, __pblock_vcop_disparity_sad16_first_row_firstCall);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_disparity_sad16_first_row_firstCall_vloops(__pblock_vcop_disparity_sad16_first_row_firstCall);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_disparity_sad16_first_row_firstCall_custom(
   __vptr_uint16 pLeft,
   __vptr_uint16 pRight,
   unsigned short leftStride,
   unsigned short rightStride,
   unsigned char winWidth,
   unsigned char winHeight,
   __vptr_uint8 pDisparityOutput,
   __vptr_uint32 pMinCostOutput,
   __vptr_uint32 pAllCostOutput,
   unsigned short allCostOutputStride,
   unsigned short width,
   unsigned char numDisparities,
   unsigned char disparityStep,
   __vptr_uint8 pCollateMask,
   __vptr_uint16 pOffset,
   __vptr_int32 pScratch0,
   __vptr_uint32 pCarryOver,
   unsigned short scratchStride,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_disparity_sad16_first_row_firstCall_init(pLeft, pRight, leftStride, rightStride, winWidth, winHeight, pDisparityOutput, pMinCostOutput, pAllCostOutput, allCostOutputStride, width, numDisparities, disparityStep, pCollateMask, pOffset, pScratch0, pCarryOver, scratchStride, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_disparity_sad16_first_row_firstCall_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_disparity_sad16_first_row, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_disparity_sad16_first_row, __ALIGNOF__(int));
unsigned short __pblock_vcop_disparity_sad16_first_row[70];

unsigned int vcop_disparity_sad16_first_row_param_count(void)
{
   return 70u;
}

unsigned int vcop_disparity_sad16_first_row_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_disparity_sad16_first_row_init(
   __vptr_uint16 pLeft,
   __vptr_uint16 pRight,
   unsigned short leftStride,
   unsigned short rightStride,
   unsigned char winWidth,
   unsigned char winHeight,
   __vptr_uint8 pDisparityOutput,
   __vptr_uint32 pMinCostOutput,
   __vptr_uint32 pAllCostOutput,
   unsigned short allCostOutputStride,
   unsigned short width,
   unsigned char numDisparities,
   unsigned char disparityStep,
   __vptr_uint8 pCollateMask,
   __vptr_uint16 pOffset,
   __vptr_int32 pScratch0,
   __vptr_uint32 pCarryOver,
   unsigned short scratchStride,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), ((numDisparities/disparityStep))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((((width) + (8u)-1) & ~((8u)-1))/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (winHeight)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pLeft+(winWidth-1)*sizeof(*pLeft));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pRight+(disparityStep-1)*sizeof(*pLeft)+(winWidth-1)*sizeof(*pLeft));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pLeft-sizeof(*pLeft));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pRight+(disparityStep-1)*sizeof(*pLeft)-sizeof(*pLeft));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pScratch0);
   __vcop_pblock_init16(pblock, __offset+_PREG(16), (8u*scratchStride));
   __vcop_pblock_init16(pblock, __offset+_PREG(17), (sizeof(*pAllCostOutput)) -(8u*scratchStride)*(((((width) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(18), (leftStride*sizeof(*pLeft)));
   __vcop_pblock_init16(pblock, __offset+_PREG(19), (8u*sizeof(*pLeft)) -(leftStride*sizeof(*pLeft))*((winHeight)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(20),  -(8u*sizeof(*pLeft))*(((((width) + (8u)-1) & ~((8u)-1))/(8u))-1u) -(leftStride*sizeof(*pLeft))*((winHeight)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(21), (rightStride*sizeof(*pLeft)));
   __vcop_pblock_init16(pblock, __offset+_PREG(22), (8u*sizeof(*pLeft)) -(rightStride*sizeof(*pLeft))*((winHeight)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(23), (disparityStep*sizeof(*pLeft)) -(8u*sizeof(*pLeft))*(((((width) + (8u)-1) & ~((8u)-1))/(8u))-1u) -(rightStride*sizeof(*pLeft))*((winHeight)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)pOffset);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), 0);
   __offset += 26;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((((numDisparities/disparityStep) + (8u)-1) & ~((8u)-1))/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (width)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pScratch0);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pAllCostOutput);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), (scratchStride));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), (8u*sizeof(*pScratch0)) -(scratchStride)*((width)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(13), 4);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), (8u*allCostOutputStride) -(sizeof(*pAllCostOutput))*((width)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pOffset+16);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pCarryOver);
   __offset += 18;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((((width) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((numDisparities/disparityStep))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pAllCostOutput+(numDisparities/disparityStep-1)*allCostOutputStride);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pAllCostOutput+(numDisparities/disparityStep-1)*allCostOutputStride+8u*sizeof(*pAllCostOutput));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pMinCostOutput);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pMinCostOutput+8u*sizeof(*pMinCostOutput));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pDisparityOutput);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pDisparityOutput+8u*sizeof(*pDisparityOutput));
   __vcop_pblock_init16(pblock, __offset+_PREG(20), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(21), 64);
   __vcop_pblock_init16(pblock, __offset+_PREG(22), (-allCostOutputStride));
   __vcop_pblock_init16(pblock, __offset+_PREG(23), ((2*8u)*sizeof(*pAllCostOutput)) -(-allCostOutputStride)*(((numDisparities/disparityStep))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(24), disparityStep);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), 4294967295);
   __offset += 26;

   return 70u;
}

void vcop_disparity_sad16_first_row_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("vDisparityStep", 16);
   #pragma VCC_VREG("vOfst", 17);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vColDiff", 18);
   #pragma VCC_VREG("vLeftL", 19);
   #pragma VCC_VREG("vLeftR", 20);
   #pragma VCC_VREG("vRightL", 21);
   #pragma VCC_VREG("vRightR", 22);
   #pragma VCC_VREG("vSAD", 23);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("agenOffset", "A0");
   #pragma EVE_REG("agenOut", "A1");
   #pragma EVE_REG("agenLeft", "A2");
   #pragma EVE_REG("agenRight", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("d", "I2");
   #pragma EVE_REG("c", "I3");
   #pragma EVE_REG("h", "I4");
   

   __vcop_vloop(__vcop_compute(), 15u, 13u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(26), _VREG(18));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(16), _PREG(17), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(18), _PREG(19), _PREG(20), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(21), _PREG(22), _PREG(23), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(24), _AGEN(0), _VREG(17), __vcop_once());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(6), _AGEN(2), _VREG(20), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(8), _AGEN(3), _VREG(22), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(10), _AGEN(2), _VREG(19), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(12), _AGEN(3), _VREG(21), __vcop_alws());
   __vcop_vsad(_VREG(20), _VREG(22), _VREG(18));
   __vcop_vabsdif(_VREG(19), _VREG(21), _VREG(23));
   __vcop_vsub(_VREG(18), _VREG(23), _VREG(18));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_pdda(_VREG(17)), __vcop_last_i4(), _VREG(18), _PREG(14), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vAcc", 24);
   #pragma VCC_VREG("vEven", 25);
   #pragma VCC_VREG("vEvenAcc", 26);
   #pragma VCC_VREG("vOdd", 27);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("agenOffset", "A0");
   #pragma EVE_REG("agenScratch2", "A1");
   #pragma EVE_REG("agenIn", "A2");
   #pragma EVE_REG("agenOut", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("d", "I3");
   #pragma EVE_REG("c", "I4");
   

   __vcop_vloop(__vcop_compute(), 11u, 9u, 2u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(10), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(11), _PREG(12), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(13), _PREG(14), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(16), _AGEN(0), _VREG(17), __vcop_once());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(18), _AGEN(1), _VREG(24), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(6), _AGEN(2), _VREG(25), __vcop_alws());
   __vcop_vadd(_VREG(24), _VREG(25), _VREG(24));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_pdda(_VREG(17)), __vcop_alws(), _VREG(24), _PREG(8), _AGEN(3), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_last_i4(), _VREG(24), _PREG(18), _AGEN(1), _PREG(0));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vDisp0", 28);
   #pragma VCC_VREG("vDisp1", 29);
   #pragma VCC_VREG("vMin0", 30);
   #pragma VCC_VREG("vMin1", 31);
   #pragma VCC_VREG("vCost0", 32);
   #pragma VCC_VREG("vCost1", 33);
   #pragma VCC_VREG("vIdx", 34);
   #pragma VCC_VREG("vMinFlag0", 35);
   #pragma VCC_VREG("vMinFlag1", 36);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("agenOffset", "A0");
   #pragma EVE_REG("agenDisp", "A1");
   #pragma EVE_REG("agenMinCost", "A2");
   #pragma EVE_REG("agenCost", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("c", "I3");
   #pragma EVE_REG("d", "I4");
   

   __vcop_vloop(__vcop_compute(), 22u, 13u, 3u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(24), _VREG(16));
   __vcop_vinit(__vcop_sizeWU(), __vcop_i4_zero(), _PREG(26), _VREG(30));
   __vcop_vinit(__vcop_sizeWU(), __vcop_i4_zero(), _PREG(26), _VREG(31));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(6), _VREG(28));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(6), _VREG(29));
   __vcop_vinit(__vcop_sizeHU(), __vcop_alws(), _PREG(68), _VREG(34));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(20), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(0), _PREG(21), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(22), _PREG(23), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(8), _AGEN(3), _VREG(32), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(10), _AGEN(3), _VREG(33), __vcop_alws());
   __vcop_vmpy(_VREG(34), _VREG(16), _VREG(34), _PREG(0));
   __vcop_vminsetf(_VREG(32), _VREG(30), _VREG(35));
   __vcop_vminsetf(_VREG(33), _VREG(31), _VREG(36));
   __vcop_vsel(_VREG(35), _VREG(34), _VREG(28));
   __vcop_vsel(_VREG(36), _VREG(34), _VREG(29));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_last_i4(), _VREG(30), _PREG(12), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_last_i4(), _VREG(31), _PREG(14), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_last_i4(), _VREG(28), _PREG(16), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_last_i4(), _VREG(29), _PREG(18), _AGEN(1), _PREG(0));
   __vcop_vloop_end(3u);

}

void vcop_disparity_sad16_first_row(
   __vptr_uint16 pLeft,
   __vptr_uint16 pRight,
   unsigned short leftStride,
   unsigned short rightStride,
   unsigned char winWidth,
   unsigned char winHeight,
   __vptr_uint8 pDisparityOutput,
   __vptr_uint32 pMinCostOutput,
   __vptr_uint32 pAllCostOutput,
   unsigned short allCostOutputStride,
   unsigned short width,
   unsigned char numDisparities,
   unsigned char disparityStep,
   __vptr_uint8 pCollateMask,
   __vptr_uint16 pOffset,
   __vptr_int32 pScratch0,
   __vptr_uint32 pCarryOver,
   unsigned short scratchStride)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_disparity_sad16_first_row_init(pLeft, pRight, leftStride, rightStride, winWidth, winHeight, pDisparityOutput, pMinCostOutput, pAllCostOutput, allCostOutputStride, width, numDisparities, disparityStep, pCollateMask, pOffset, pScratch0, pCarryOver, scratchStride, __pblock_vcop_disparity_sad16_first_row);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_disparity_sad16_first_row_vloops(__pblock_vcop_disparity_sad16_first_row);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_disparity_sad16_first_row_custom(
   __vptr_uint16 pLeft,
   __vptr_uint16 pRight,
   unsigned short leftStride,
   unsigned short rightStride,
   unsigned char winWidth,
   unsigned char winHeight,
   __vptr_uint8 pDisparityOutput,
   __vptr_uint32 pMinCostOutput,
   __vptr_uint32 pAllCostOutput,
   unsigned short allCostOutputStride,
   unsigned short width,
   unsigned char numDisparities,
   unsigned char disparityStep,
   __vptr_uint8 pCollateMask,
   __vptr_uint16 pOffset,
   __vptr_int32 pScratch0,
   __vptr_uint32 pCarryOver,
   unsigned short scratchStride,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_disparity_sad16_first_row_init(pLeft, pRight, leftStride, rightStride, winWidth, winHeight, pDisparityOutput, pMinCostOutput, pAllCostOutput, allCostOutputStride, width, numDisparities, disparityStep, pCollateMask, pOffset, pScratch0, pCarryOver, scratchStride, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_disparity_sad16_first_row_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_disparity_sad16_nth_row_firstCall, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_disparity_sad16_nth_row_firstCall, __ALIGNOF__(int));
unsigned short __pblock_vcop_disparity_sad16_nth_row_firstCall[114];

unsigned int vcop_disparity_sad16_nth_row_firstCall_param_count(void)
{
   return 114u;
}

unsigned int vcop_disparity_sad16_nth_row_firstCall_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_disparity_sad16_nth_row_firstCall_init(
   __vptr_uint16 pLeft,
   __vptr_uint16 pRight,
   unsigned short leftStride,
   unsigned short rightStride,
   unsigned char winWidth,
   unsigned char winHeight,
   __vptr_uint8 pDisparityOutput,
   __vptr_uint32 pMinCostOutput,
   __vptr_uint32 pAllCostOutput,
   unsigned short allCostOutputStride,
   unsigned short width,
   unsigned char numDisparities,
   unsigned char disparityStep,
   __vptr_uint8 pCollateMask,
   __vptr_uint16 pOffset,
   __vptr_int32 pScratch0,
   __vptr_int32 pScratch1,
   __vptr_uint32 pCarryOver,
   unsigned short scratchStride,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((numDisparities/disparityStep))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((width-(8u)) + (8u)-1) & ~((8u)-1))/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pLeft+8u*sizeof(*pLeft)+(leftStride*(winHeight-1)+(winWidth-1))*sizeof(*pLeft));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pRight+(disparityStep-1)*sizeof(*pLeft)+8u*sizeof(*pLeft)+(rightStride*(winHeight-1)+(winWidth-1))*sizeof(*pLeft));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pLeft+8u*sizeof(*pLeft)+(leftStride*-1+(winWidth-1))*sizeof(*pLeft));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pRight+(disparityStep-1)*sizeof(*pLeft)+8u*sizeof(*pLeft)+(rightStride*-1+(winWidth-1))*sizeof(*pLeft));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pLeft+8u*sizeof(*pLeft)+(leftStride*(winHeight-1)+-1)*sizeof(*pLeft));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pRight+(disparityStep-1)*sizeof(*pLeft)+8u*sizeof(*pLeft)+(rightStride*(winHeight-1)+-1)*sizeof(*pLeft));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pScratch1);
   __vcop_pblock_init16(pblock, __offset+_PREG(20), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(21),  -(8u*sizeof(*pLeft))*(((((width-(8u)) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(22), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(23), ((width-8u+8u-1&~(8u-1))*sizeof(*pAllCostOutput)) -(8u*sizeof(*pAllCostOutput))*(((((width-(8u)) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(24), (disparityStep*sizeof(*pLeft)) -(8u*sizeof(*pLeft))*(((((width-(8u)) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)pLeft+8u*sizeof(*pLeft)+(leftStride*-1+-1)*sizeof(*pLeft));
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)pRight+(disparityStep-1)*sizeof(*pLeft)+8u*sizeof(*pLeft)+(rightStride*-1+-1)*sizeof(*pLeft));
   __offset += 28;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((numDisparities/disparityStep))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((width-(8u)) + (8u)-1) & ~((8u)-1))/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pScratch0);
   __vcop_pblock_init16(pblock, __offset+_PREG(8), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(9), ((width-8u+8u-1&~(8u-1))*sizeof(*pAllCostOutput)) -(8u*sizeof(*pAllCostOutput))*(((((width-(8u)) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(10), (8u*scratchStride));
   __vcop_pblock_init16(pblock, __offset+_PREG(11), (sizeof(*pAllCostOutput)) -(8u*scratchStride)*(((((width-(8u)) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pOffset);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pScratch1);
   __offset += 14;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((numDisparities/disparityStep))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (winWidth)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pLeft+leftStride*(winHeight-1)*sizeof(*pLeft));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pRight+(disparityStep-1)*sizeof(*pLeft)+rightStride*(winHeight-1)*sizeof(*pLeft));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pLeft-leftStride*sizeof(*pLeft));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pRight+(disparityStep-1)*sizeof(*pLeft)-rightStride*sizeof(*pLeft));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pScratch1);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pCarryOver);
   __vcop_pblock_init16(pblock, __offset+_PREG(18), (allCostOutputStride));
   __vcop_pblock_init16(pblock, __offset+_PREG(19), 2);
   __vcop_pblock_init16(pblock, __offset+_PREG(20),  -(sizeof(*pLeft))*((winWidth)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(21), (disparityStep*sizeof(*pLeft)) -(sizeof(*pLeft))*((winWidth)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)pCollateMask);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), 0);
   __offset += 24;

   /* Loop 4 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((((numDisparities/disparityStep) + (8u)-1) & ~((8u)-1))/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((width-(8u)))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pScratch0);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pScratch1+8u*sizeof(*pAllCostOutput));
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), (scratchStride));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), (8u*sizeof(*pScratch0)) -(scratchStride)*(((width-(8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(13), 4);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), (8u*allCostOutputStride) -(sizeof(*pAllCostOutput))*(((width-(8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pOffset+16);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pCarryOver);
   __offset += 18;

   /* Loop 5 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((((width) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((numDisparities/disparityStep))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pAllCostOutput+(numDisparities/disparityStep-1)*allCostOutputStride);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pAllCostOutput+(numDisparities/disparityStep-1)*allCostOutputStride+8u*sizeof(*pAllCostOutput));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pScratch1+(numDisparities/disparityStep-1)*allCostOutputStride);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pScratch1+(numDisparities/disparityStep-1)*allCostOutputStride+8u*sizeof(*pScratch1));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pMinCostOutput);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pMinCostOutput+8u*sizeof(*pMinCostOutput));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pDisparityOutput);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)pDisparityOutput+8u*sizeof(*pDisparityOutput));
   __vcop_pblock_init16(pblock, __offset+_PREG(24), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(25), 64);
   __vcop_pblock_init16(pblock, __offset+_PREG(26), (-allCostOutputStride));
   __vcop_pblock_init16(pblock, __offset+_PREG(27), ((2*8u)*sizeof(*pAllCostOutput)) -(-allCostOutputStride)*(((numDisparities/disparityStep))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(28), disparityStep);
   __vcop_pblock_init32(pblock, __offset+_PREG(30), 4294967295);
   __offset += 30;

   return 114u;
}

void vcop_disparity_sad16_nth_row_firstCall_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("vDisparityStep", 16);
   #pragma VCC_VREG("vMask", 17);
   #pragma VCC_VREG("vOfst", 18);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vLeftBL", 19);
   #pragma VCC_VREG("vLeftBR", 20);
   #pragma VCC_VREG("vLeftUL", 21);
   #pragma VCC_VREG("vLeftUR", 22);
   #pragma VCC_VREG("vPtDiff", 23);
   #pragma VCC_VREG("vPtDiffNeg", 24);
   #pragma VCC_VREG("vPtDiffPos", 25);
   #pragma VCC_VREG("vRightBL", 26);
   #pragma VCC_VREG("vRightBR", 27);
   #pragma VCC_VREG("vRightUL", 28);
   #pragma VCC_VREG("vRightUR", 29);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("agenLeft", "A0");
   #pragma EVE_REG("agenOut", "A1");
   #pragma EVE_REG("agenRight", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("d", "I3");
   #pragma EVE_REG("c", "I4");
   

   __vcop_vloop(__vcop_compute(), 18u, 14u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(20), _PREG(21), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(22), _PREG(23), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(20), _PREG(24), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(26), _AGEN(0), _VREG(21), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(28), _AGEN(2), _VREG(28), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(6), _AGEN(0), _VREG(20), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(8), _AGEN(2), _VREG(27), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(10), _AGEN(0), _VREG(22), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(12), _AGEN(2), _VREG(29), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(14), _AGEN(0), _VREG(19), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(16), _AGEN(2), _VREG(26), __vcop_alws());
   __vcop_vabsdif(_VREG(21), _VREG(28), _VREG(25));
   __vcop_vabsdif(_VREG(22), _VREG(29), _VREG(24));
   __vcop_vsad(_VREG(20), _VREG(27), _VREG(25));
   __vcop_vsad(_VREG(19), _VREG(26), _VREG(24));
   __vcop_vsub(_VREG(25), _VREG(24), _VREG(23));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(23), _PREG(18), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vPtDiff0", 30);
   #pragma VCC_VREG("vPtDiff1", 31);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("agenOffset", "A0");
   #pragma EVE_REG("agenIn", "A1");
   #pragma EVE_REG("agenOut", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("d", "I3");
   #pragma EVE_REG("c", "I4");
   

   __vcop_vloop(__vcop_compute(), 7u, 7u, 2u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(8), _PREG(9), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(10), _PREG(11), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(12), _AGEN(0), _VREG(18), __vcop_once());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(14), _AGEN(1), _VREG(30), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_pdda(_VREG(18)), __vcop_alws(), _VREG(30), _PREG(6), _AGEN(2), _PREG(0));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vRowDiff", 32);
   #pragma VCC_VREG("vLeftB", 33);
   #pragma VCC_VREG("vLeftU", 34);
   #pragma VCC_VREG("vRightB", 35);
   #pragma VCC_VREG("vRightU", 36);
   #pragma VCC_VREG("vSAD", 37);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("agen0", "A0");
   #pragma EVE_REG("agenOffset", "A1");
   #pragma EVE_REG("agenCost", "A2");
   #pragma EVE_REG("agenLeft", "A3");
   #pragma EVE_REG("agenRight", "A4");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("d", "I3");
   #pragma EVE_REG("w", "I4");
   

   __vcop_vloop(__vcop_compute(), 17u, 12u, 3u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(24), _VREG(32));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(0), _PREG(18), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(19), _PREG(20), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(4), _PREG(19), _PREG(21), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_nbits(), _PREG(22), _AGEN(0), _VREG(17), __vcop_once());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(6), _AGEN(3), _VREG(33), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(8), _AGEN(4), _VREG(35), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(10), _AGEN(3), _VREG(34), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(12), _AGEN(4), _VREG(36), __vcop_alws());
   __vcop_vsad(_VREG(33), _VREG(35), _VREG(32));
   __vcop_vabsdif(_VREG(34), _VREG(36), _VREG(37));
   __vcop_vsub(_VREG(32), _VREG(37), _VREG(32));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_last_i4(), _VREG(32), _PREG(14), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_predicate(_VREG(17)), __vcop_sizeWU(), __vcop_collat(), __vcop_last_i4(), _VREG(32), _PREG(16), _AGEN(0), _PREG(0));
   __vcop_vloop_end(3u);

   /* VLOOP 4 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vAcc", 38);
   #pragma VCC_VREG("vEven", 39);
   #pragma VCC_VREG("vEvenAcc", 40);
   #pragma VCC_VREG("vOdd", 41);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("agen0", "A0");
   #pragma EVE_REG("agenOffset", "A1");
   #pragma EVE_REG("agenScratch2", "A2");
   #pragma EVE_REG("agenIn", "A3");
   #pragma EVE_REG("agenOut", "A4");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("d", "I3");
   #pragma EVE_REG("c", "I4");
   

   __vcop_vloop(__vcop_compute(), 12u, 9u, 4u);
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(0), _PREG(10), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(11), _PREG(12), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(4), _PREG(13), _PREG(14), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(16), _AGEN(1), _VREG(18), __vcop_once());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(18), _AGEN(2), _VREG(38), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(6), _AGEN(3), _VREG(39), __vcop_alws());
   __vcop_vadd(_VREG(38), _VREG(39), _VREG(38));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_pdda(_VREG(18)), __vcop_alws(), _VREG(38), _PREG(8), _AGEN(4), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_last_i4(), _VREG(38), _PREG(18), _AGEN(2), _PREG(0));
   __vcop_vloop_end(4u);

   /* VLOOP 5 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vDisp0", 42);
   #pragma VCC_VREG("vDisp1", 43);
   #pragma VCC_VREG("vMin0", 44);
   #pragma VCC_VREG("vMin1", 45);
   #pragma VCC_VREG("vCost0", 46);
   #pragma VCC_VREG("vCost1", 47);
   #pragma VCC_VREG("vIdx", 48);
   #pragma VCC_VREG("vMinFlag0", 49);
   #pragma VCC_VREG("vMinFlag1", 50);
   #pragma VCC_VREG("vPartial0", 51);
   #pragma VCC_VREG("vPartial1", 52);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("agen0", "A0");
   #pragma EVE_REG("agenOffset", "A1");
   #pragma EVE_REG("agenDisp", "A2");
   #pragma EVE_REG("agenMinCost", "A3");
   #pragma EVE_REG("agenCost", "A4");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("c", "I3");
   #pragma EVE_REG("d", "I4");
   

   __vcop_vloop(__vcop_compute(), 29u, 15u, 5u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(28), _VREG(16));
   __vcop_vinit(__vcop_sizeWU(), __vcop_i4_zero(), _PREG(30), _VREG(44));
   __vcop_vinit(__vcop_sizeWU(), __vcop_i4_zero(), _PREG(30), _VREG(45));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(6), _VREG(42));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(6), _VREG(43));
   __vcop_vinit(__vcop_sizeHU(), __vcop_alws(), _PREG(68), _VREG(48));
   __vcop_vagen(_AGEN(2), _PREG(0), _PREG(24), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(0), _PREG(25), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(4), _PREG(26), _PREG(27), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(8), _AGEN(4), _VREG(46), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(10), _AGEN(4), _VREG(47), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(12), _AGEN(4), _VREG(51), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(14), _AGEN(4), _VREG(52), __vcop_alws());
   __vcop_vmpy(_VREG(48), _VREG(16), _VREG(48), _PREG(0));
   __vcop_vadd(_VREG(46), _VREG(51), _VREG(46));
   __vcop_vadd(_VREG(47), _VREG(52), _VREG(47));
   __vcop_vminsetf(_VREG(46), _VREG(44), _VREG(49));
   __vcop_vminsetf(_VREG(47), _VREG(45), _VREG(50));
   __vcop_vsel(_VREG(49), _VREG(48), _VREG(42));
   __vcop_vsel(_VREG(50), _VREG(48), _VREG(43));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(46), _PREG(8), _AGEN(4), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(47), _PREG(10), _AGEN(4), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_last_i4(), _VREG(44), _PREG(16), _AGEN(3), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_last_i4(), _VREG(45), _PREG(18), _AGEN(3), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_last_i4(), _VREG(42), _PREG(20), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_last_i4(), _VREG(43), _PREG(22), _AGEN(2), _PREG(0));
   __vcop_vloop_end(5u);

}

void vcop_disparity_sad16_nth_row_firstCall(
   __vptr_uint16 pLeft,
   __vptr_uint16 pRight,
   unsigned short leftStride,
   unsigned short rightStride,
   unsigned char winWidth,
   unsigned char winHeight,
   __vptr_uint8 pDisparityOutput,
   __vptr_uint32 pMinCostOutput,
   __vptr_uint32 pAllCostOutput,
   unsigned short allCostOutputStride,
   unsigned short width,
   unsigned char numDisparities,
   unsigned char disparityStep,
   __vptr_uint8 pCollateMask,
   __vptr_uint16 pOffset,
   __vptr_int32 pScratch0,
   __vptr_int32 pScratch1,
   __vptr_uint32 pCarryOver,
   unsigned short scratchStride)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_disparity_sad16_nth_row_firstCall_init(pLeft, pRight, leftStride, rightStride, winWidth, winHeight, pDisparityOutput, pMinCostOutput, pAllCostOutput, allCostOutputStride, width, numDisparities, disparityStep, pCollateMask, pOffset, pScratch0, pScratch1, pCarryOver, scratchStride, __pblock_vcop_disparity_sad16_nth_row_firstCall);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_disparity_sad16_nth_row_firstCall_vloops(__pblock_vcop_disparity_sad16_nth_row_firstCall);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_disparity_sad16_nth_row_firstCall_custom(
   __vptr_uint16 pLeft,
   __vptr_uint16 pRight,
   unsigned short leftStride,
   unsigned short rightStride,
   unsigned char winWidth,
   unsigned char winHeight,
   __vptr_uint8 pDisparityOutput,
   __vptr_uint32 pMinCostOutput,
   __vptr_uint32 pAllCostOutput,
   unsigned short allCostOutputStride,
   unsigned short width,
   unsigned char numDisparities,
   unsigned char disparityStep,
   __vptr_uint8 pCollateMask,
   __vptr_uint16 pOffset,
   __vptr_int32 pScratch0,
   __vptr_int32 pScratch1,
   __vptr_uint32 pCarryOver,
   unsigned short scratchStride,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_disparity_sad16_nth_row_firstCall_init(pLeft, pRight, leftStride, rightStride, winWidth, winHeight, pDisparityOutput, pMinCostOutput, pAllCostOutput, allCostOutputStride, width, numDisparities, disparityStep, pCollateMask, pOffset, pScratch0, pScratch1, pCarryOver, scratchStride, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_disparity_sad16_nth_row_firstCall_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_disparity_sad16_nth_row, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_disparity_sad16_nth_row, __ALIGNOF__(int));
unsigned short __pblock_vcop_disparity_sad16_nth_row[90];

unsigned int vcop_disparity_sad16_nth_row_param_count(void)
{
   return 90u;
}

unsigned int vcop_disparity_sad16_nth_row_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_disparity_sad16_nth_row_init(
   __vptr_uint16 pLeft,
   __vptr_uint16 pRight,
   unsigned short leftStride,
   unsigned short rightStride,
   unsigned char winWidth,
   unsigned char winHeight,
   __vptr_uint8 pDisparityOutput,
   __vptr_uint32 pMinCostOutput,
   __vptr_uint32 pAllCostOutput,
   unsigned short allCostOutputStride,
   unsigned short width,
   unsigned char numDisparities,
   unsigned char disparityStep,
   __vptr_uint8 pCollateMask,
   __vptr_uint16 pOffset,
   __vptr_int32 pScratch0,
   __vptr_int32 pScratch1,
   __vptr_uint32 pCarryOver,
   unsigned short scratchStride,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((numDisparities/disparityStep))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((width) + (8u)-1) & ~((8u)-1))/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pLeft+(leftStride*(winHeight-1)+(winWidth-1))*sizeof(*pLeft));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pRight+(disparityStep-1)*sizeof(*pLeft)+(rightStride*(winHeight-1)+(winWidth-1))*sizeof(*pLeft));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pLeft+(leftStride*-1+(winWidth-1))*sizeof(*pLeft));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pRight+(disparityStep-1)*sizeof(*pLeft)+(rightStride*-1+(winWidth-1))*sizeof(*pLeft));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pLeft+(leftStride*(winHeight-1)+-1)*sizeof(*pLeft));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pRight+(disparityStep-1)*sizeof(*pLeft)+(rightStride*(winHeight-1)+-1)*sizeof(*pLeft));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pScratch1);
   __vcop_pblock_init16(pblock, __offset+_PREG(20), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(21),  -(8u*sizeof(*pLeft))*(((((width) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(22), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(23), ((width+8u-1&~(8u-1))*sizeof(*pAllCostOutput)) -(8u*sizeof(*pAllCostOutput))*(((((width) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(24), (disparityStep*sizeof(*pLeft)) -(8u*sizeof(*pLeft))*(((((width) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)pLeft+(leftStride*-1+-1)*sizeof(*pLeft));
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)pRight+(disparityStep-1)*sizeof(*pLeft)+(rightStride*-1+-1)*sizeof(*pLeft));
   __offset += 28;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((numDisparities/disparityStep))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((width) + (8u)-1) & ~((8u)-1))/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pScratch0);
   __vcop_pblock_init16(pblock, __offset+_PREG(8), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(9), ((width+8u-1&~(8u-1))*sizeof(*pAllCostOutput)) -(8u*sizeof(*pAllCostOutput))*(((((width) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(10), (8u*scratchStride));
   __vcop_pblock_init16(pblock, __offset+_PREG(11), (sizeof(*pAllCostOutput)) -(8u*scratchStride)*(((((width) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pOffset);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pScratch1);
   __offset += 14;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((((numDisparities/disparityStep) + (8u)-1) & ~((8u)-1))/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (width)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pScratch0);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pScratch1);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), (scratchStride));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), (8u*sizeof(*pScratch0)) -(scratchStride)*((width)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(13), 4);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), (8u*allCostOutputStride) -(sizeof(*pAllCostOutput))*((width)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pOffset+16);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pCarryOver);
   __offset += 18;

   /* Loop 4 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((((width) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((numDisparities/disparityStep))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pAllCostOutput+(numDisparities/disparityStep-1)*allCostOutputStride);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pAllCostOutput+(numDisparities/disparityStep-1)*allCostOutputStride+8u*sizeof(*pAllCostOutput));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pScratch1+(numDisparities/disparityStep-1)*allCostOutputStride);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pScratch1+(numDisparities/disparityStep-1)*allCostOutputStride+8u*sizeof(*pScratch1));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pMinCostOutput);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pMinCostOutput+8u*sizeof(*pMinCostOutput));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pDisparityOutput);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)pDisparityOutput+8u*sizeof(*pDisparityOutput));
   __vcop_pblock_init16(pblock, __offset+_PREG(24), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(25), 64);
   __vcop_pblock_init16(pblock, __offset+_PREG(26), (-allCostOutputStride));
   __vcop_pblock_init16(pblock, __offset+_PREG(27), ((2*8u)*sizeof(*pAllCostOutput)) -(-allCostOutputStride)*(((numDisparities/disparityStep))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(28), disparityStep);
   __vcop_pblock_init32(pblock, __offset+_PREG(30), 4294967295);
   __offset += 30;

   return 90u;
}

void vcop_disparity_sad16_nth_row_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("vDisparityStep", 16);
   #pragma VCC_VREG("vOfst", 17);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vLeftBL", 18);
   #pragma VCC_VREG("vLeftBR", 19);
   #pragma VCC_VREG("vLeftUL", 20);
   #pragma VCC_VREG("vLeftUR", 21);
   #pragma VCC_VREG("vPtDiff", 22);
   #pragma VCC_VREG("vPtDiffNeg", 23);
   #pragma VCC_VREG("vPtDiffPos", 24);
   #pragma VCC_VREG("vRightBL", 25);
   #pragma VCC_VREG("vRightBR", 26);
   #pragma VCC_VREG("vRightUL", 27);
   #pragma VCC_VREG("vRightUR", 28);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("agenLeft", "A0");
   #pragma EVE_REG("agenOut", "A1");
   #pragma EVE_REG("agenRight", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("d", "I3");
   #pragma EVE_REG("c", "I4");
   

   __vcop_vloop(__vcop_compute(), 18u, 14u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(20), _PREG(21), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(22), _PREG(23), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(20), _PREG(24), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(26), _AGEN(0), _VREG(20), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(28), _AGEN(2), _VREG(27), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(6), _AGEN(0), _VREG(19), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(8), _AGEN(2), _VREG(26), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(10), _AGEN(0), _VREG(21), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(12), _AGEN(2), _VREG(28), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(14), _AGEN(0), _VREG(18), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(16), _AGEN(2), _VREG(25), __vcop_alws());
   __vcop_vabsdif(_VREG(20), _VREG(27), _VREG(24));
   __vcop_vabsdif(_VREG(21), _VREG(28), _VREG(23));
   __vcop_vsad(_VREG(19), _VREG(26), _VREG(24));
   __vcop_vsad(_VREG(18), _VREG(25), _VREG(23));
   __vcop_vsub(_VREG(24), _VREG(23), _VREG(22));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(22), _PREG(18), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vPtDiff0", 29);
   #pragma VCC_VREG("vPtDiff1", 30);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("agenOffset", "A0");
   #pragma EVE_REG("agenIn", "A1");
   #pragma EVE_REG("agenOut", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("d", "I3");
   #pragma EVE_REG("c", "I4");
   

   __vcop_vloop(__vcop_compute(), 7u, 7u, 2u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(8), _PREG(9), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(10), _PREG(11), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(12), _AGEN(0), _VREG(17), __vcop_once());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(14), _AGEN(1), _VREG(29), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_pdda(_VREG(17)), __vcop_alws(), _VREG(29), _PREG(6), _AGEN(2), _PREG(0));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vAcc", 31);
   #pragma VCC_VREG("vEven", 32);
   #pragma VCC_VREG("vEvenAcc", 33);
   #pragma VCC_VREG("vOdd", 34);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("agenOffset", "A0");
   #pragma EVE_REG("agenScratch2", "A1");
   #pragma EVE_REG("agenIn", "A2");
   #pragma EVE_REG("agenOut", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("d", "I3");
   #pragma EVE_REG("c", "I4");
   

   __vcop_vloop(__vcop_compute(), 11u, 9u, 3u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(10), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(11), _PREG(12), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(13), _PREG(14), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(16), _AGEN(0), _VREG(17), __vcop_once());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(18), _AGEN(1), _VREG(31), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(6), _AGEN(2), _VREG(32), __vcop_alws());
   __vcop_vadd(_VREG(31), _VREG(32), _VREG(31));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_pdda(_VREG(17)), __vcop_alws(), _VREG(31), _PREG(8), _AGEN(3), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_last_i4(), _VREG(31), _PREG(18), _AGEN(1), _PREG(0));
   __vcop_vloop_end(3u);

   /* VLOOP 4 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vDisp0", 35);
   #pragma VCC_VREG("vDisp1", 36);
   #pragma VCC_VREG("vMin0", 37);
   #pragma VCC_VREG("vMin1", 38);
   #pragma VCC_VREG("vCost0", 39);
   #pragma VCC_VREG("vCost1", 40);
   #pragma VCC_VREG("vIdx", 41);
   #pragma VCC_VREG("vMinFlag0", 42);
   #pragma VCC_VREG("vMinFlag1", 43);
   #pragma VCC_VREG("vPartial0", 44);
   #pragma VCC_VREG("vPartial1", 45);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("agenOffset", "A0");
   #pragma EVE_REG("agenDisp", "A1");
   #pragma EVE_REG("agenMinCost", "A2");
   #pragma EVE_REG("agenCost", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("c", "I3");
   #pragma EVE_REG("d", "I4");
   

   __vcop_vloop(__vcop_compute(), 28u, 15u, 4u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(28), _VREG(16));
   __vcop_vinit(__vcop_sizeWU(), __vcop_i4_zero(), _PREG(30), _VREG(37));
   __vcop_vinit(__vcop_sizeWU(), __vcop_i4_zero(), _PREG(30), _VREG(38));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(6), _VREG(35));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(6), _VREG(36));
   __vcop_vinit(__vcop_sizeHU(), __vcop_alws(), _PREG(68), _VREG(41));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(24), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(0), _PREG(25), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(26), _PREG(27), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(8), _AGEN(3), _VREG(39), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(10), _AGEN(3), _VREG(40), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(12), _AGEN(3), _VREG(44), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(14), _AGEN(3), _VREG(45), __vcop_alws());
   __vcop_vmpy(_VREG(41), _VREG(16), _VREG(41), _PREG(0));
   __vcop_vadd(_VREG(39), _VREG(44), _VREG(39));
   __vcop_vadd(_VREG(40), _VREG(45), _VREG(40));
   __vcop_vminsetf(_VREG(39), _VREG(37), _VREG(42));
   __vcop_vminsetf(_VREG(40), _VREG(38), _VREG(43));
   __vcop_vsel(_VREG(42), _VREG(41), _VREG(35));
   __vcop_vsel(_VREG(43), _VREG(41), _VREG(36));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(39), _PREG(8), _AGEN(3), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(40), _PREG(10), _AGEN(3), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_last_i4(), _VREG(37), _PREG(16), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_last_i4(), _VREG(38), _PREG(18), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_last_i4(), _VREG(35), _PREG(20), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_last_i4(), _VREG(36), _PREG(22), _AGEN(1), _PREG(0));
   __vcop_vloop_end(4u);

}

void vcop_disparity_sad16_nth_row(
   __vptr_uint16 pLeft,
   __vptr_uint16 pRight,
   unsigned short leftStride,
   unsigned short rightStride,
   unsigned char winWidth,
   unsigned char winHeight,
   __vptr_uint8 pDisparityOutput,
   __vptr_uint32 pMinCostOutput,
   __vptr_uint32 pAllCostOutput,
   unsigned short allCostOutputStride,
   unsigned short width,
   unsigned char numDisparities,
   unsigned char disparityStep,
   __vptr_uint8 pCollateMask,
   __vptr_uint16 pOffset,
   __vptr_int32 pScratch0,
   __vptr_int32 pScratch1,
   __vptr_uint32 pCarryOver,
   unsigned short scratchStride)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_disparity_sad16_nth_row_init(pLeft, pRight, leftStride, rightStride, winWidth, winHeight, pDisparityOutput, pMinCostOutput, pAllCostOutput, allCostOutputStride, width, numDisparities, disparityStep, pCollateMask, pOffset, pScratch0, pScratch1, pCarryOver, scratchStride, __pblock_vcop_disparity_sad16_nth_row);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_disparity_sad16_nth_row_vloops(__pblock_vcop_disparity_sad16_nth_row);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_disparity_sad16_nth_row_custom(
   __vptr_uint16 pLeft,
   __vptr_uint16 pRight,
   unsigned short leftStride,
   unsigned short rightStride,
   unsigned char winWidth,
   unsigned char winHeight,
   __vptr_uint8 pDisparityOutput,
   __vptr_uint32 pMinCostOutput,
   __vptr_uint32 pAllCostOutput,
   unsigned short allCostOutputStride,
   unsigned short width,
   unsigned char numDisparities,
   unsigned char disparityStep,
   __vptr_uint8 pCollateMask,
   __vptr_uint16 pOffset,
   __vptr_int32 pScratch0,
   __vptr_int32 pScratch1,
   __vptr_uint32 pCarryOver,
   unsigned short scratchStride,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_disparity_sad16_nth_row_init(pLeft, pRight, leftStride, rightStride, winWidth, winHeight, pDisparityOutput, pMinCostOutput, pAllCostOutput, allCostOutputStride, width, numDisparities, disparityStep, pCollateMask, pOffset, pScratch0, pScratch1, pCarryOver, scratchStride, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_disparity_sad16_nth_row_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

