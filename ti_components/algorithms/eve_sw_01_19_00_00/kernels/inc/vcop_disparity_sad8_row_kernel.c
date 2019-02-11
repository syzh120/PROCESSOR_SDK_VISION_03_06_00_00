#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_disparity_sad8_first_row_firstCall, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_disparity_sad8_first_row_firstCall, __ALIGNOF__(int));
unsigned short __pblock_vcop_disparity_sad8_first_row_firstCall[92];

unsigned int vcop_disparity_sad8_first_row_firstCall_param_count(void)
{
   return 92u;
}

unsigned int vcop_disparity_sad8_first_row_firstCall_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_disparity_sad8_first_row_firstCall_init(
   __vptr_uint8 pLeft,
   __vptr_uint8 pRight,
   unsigned short leftStride,
   unsigned short rightStride,
   unsigned char winWidth,
   unsigned char winHeight,
   __vptr_uint8 pDisparityOutput,
   __vptr_uint16 pMinCostOutput,
   __vptr_uint16 pAllCostOutput,
   unsigned short allCostOutputStride,
   unsigned short width,
   unsigned char numDisparities,
   unsigned char disparityStep,
   __vptr_uint8 pCollateMask,
   __vptr_uint16 pOffset,
   __vptr_int16 pScratch0,
   __vptr_int16 pScratch1,
   __vptr_uint16 pCarryOver,
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
   __vcop_pblock_init16(pblock, __offset+_PREG(15), (leftStride*sizeof(*pLeft)) -(sizeof(*pLeft))*((winWidth)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(16),  -(leftStride*sizeof(*pLeft))*((winHeight)-1u) -(sizeof(*pLeft))*((winWidth)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(17), (rightStride*sizeof(*pLeft)) -(sizeof(*pLeft))*((winWidth)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(18), (disparityStep*sizeof(*pLeft)) -(rightStride*sizeof(*pLeft))*((winHeight)-1u) -(sizeof(*pLeft))*((winWidth)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pCollateMask);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), 0);
   __offset += 22;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), ((numDisparities/disparityStep))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((((width-(2*(8u))) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (winHeight)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pLeft+2*8u*sizeof(*pLeft)+(winWidth-1)*sizeof(*pLeft));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pRight+(disparityStep-1)*sizeof(*pLeft)+2*8u*sizeof(*pLeft)+(winWidth-1)*sizeof(*pLeft));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pLeft+2*8u*sizeof(*pLeft)-sizeof(*pLeft));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pRight+(disparityStep-1)*sizeof(*pLeft)+2*8u*sizeof(*pLeft)-sizeof(*pLeft));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pScratch0);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pScratch1);
   __vcop_pblock_init16(pblock, __offset+_PREG(18), (8u*scratchStride));
   __vcop_pblock_init16(pblock, __offset+_PREG(19), (sizeof(*pAllCostOutput)) -(8u*scratchStride)*(((((width-(2*(8u))) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(20), (leftStride*sizeof(*pLeft)));
   __vcop_pblock_init16(pblock, __offset+_PREG(21), ((2*8u)*sizeof(*pLeft)) -(leftStride*sizeof(*pLeft))*((winHeight)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(22),  -((2*8u)*sizeof(*pLeft))*(((((width-(2*(8u))) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u) -(leftStride*sizeof(*pLeft))*((winHeight)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(23), (rightStride*sizeof(*pLeft)));
   __vcop_pblock_init16(pblock, __offset+_PREG(24), ((2*8u)*sizeof(*pLeft)) -(rightStride*sizeof(*pLeft))*((winHeight)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(25), (disparityStep*sizeof(*pLeft)) -((2*8u)*sizeof(*pLeft))*(((((width-(2*(8u))) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u) -(rightStride*sizeof(*pLeft))*((winHeight)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)pOffset);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), 0);
   __offset += 28;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((((numDisparities/disparityStep) + (8u)-1) & ~((8u)-1))/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((width-(2*(8u)))/2)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pScratch0);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pScratch1);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pAllCostOutput+2*8u*sizeof(*pAllCostOutput));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pAllCostOutput+(2*8u+1)*sizeof(*pAllCostOutput));
   __vcop_pblock_init16(pblock, __offset+_PREG(14), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(15), (scratchStride));
   __vcop_pblock_init16(pblock, __offset+_PREG(16), (8u*sizeof(*pScratch0)) -(scratchStride)*(((width-(2*(8u)))/2)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(17), 4);
   __vcop_pblock_init16(pblock, __offset+_PREG(18), (8u*allCostOutputStride) -(2*sizeof(*pAllCostOutput))*(((width-(2*(8u)))/2)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pOffset+16);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)pCarryOver);
   __offset += 22;

   /* Loop 4 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((((width) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((numDisparities/disparityStep))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pAllCostOutput+(numDisparities/disparityStep-1)*allCostOutputStride);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pMinCostOutput);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pDisparityOutput);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(15), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(16), (-allCostOutputStride));
   __vcop_pblock_init16(pblock, __offset+_PREG(17), ((2*8u)*sizeof(*pAllCostOutput)) -(-allCostOutputStride)*(((numDisparities/disparityStep))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), disparityStep);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), 65535);
   __offset += 20;

   return 92u;
}

void vcop_disparity_sad8_first_row_firstCall_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("vDisparityStep", 16);
   #pragma VCC_VREG("vMask", 17);
   #pragma VCC_VREG("vOfst", 18);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vCost0", 19);
   #pragma VCC_VREG("vCost1", 20);
   #pragma VCC_VREG("vLeft0", 21);
   #pragma VCC_VREG("vLeft1", 22);
   #pragma VCC_VREG("vRight0", 23);
   #pragma VCC_VREG("vRight1", 24);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("agen0", "A0");
   #pragma EVE_REG("agenCost", "A1");
   #pragma EVE_REG("agenLeft", "A2");
   #pragma EVE_REG("agenRight", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("d", "I2");
   #pragma EVE_REG("h", "I3");
   #pragma EVE_REG("w", "I4");
   

   __vcop_vloop(__vcop_compute(), 14u, 11u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i34_zero(), _PREG(22), _VREG(19));
   __vcop_vinit(__vcop_sizeW(), __vcop_i34_zero(), _PREG(22), _VREG(20));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(0), _PREG(14), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(1), _PREG(15), _PREG(16), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(1), _PREG(17), _PREG(18), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_nbits(), _PREG(20), _AGEN(0), _VREG(17), __vcop_once());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(6), _AGEN(2), _VPAIR(21,22), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(8), _AGEN(3), _VPAIR(23,24), __vcop_alws());
   __vcop_vsad(_VREG(21), _VREG(23), _VREG(19));
   __vcop_vsad(_VREG(22), _VREG(24), _VREG(20));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_intrlv(), __vcop_last_i34(), _VPAIR(19,20), _PREG(10), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_predicate(_VREG(17)), __vcop_sizeHU(), __vcop_collat(), __vcop_last_i34(), _VREG(20), _PREG(12), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vColDiff0", 25);
   #pragma VCC_VREG("vColDiff1", 26);
   #pragma VCC_VREG("vLeftL0", 27);
   #pragma VCC_VREG("vLeftL1", 28);
   #pragma VCC_VREG("vLeftR0", 29);
   #pragma VCC_VREG("vLeftR1", 30);
   #pragma VCC_VREG("vRightL0", 31);
   #pragma VCC_VREG("vRightL1", 32);
   #pragma VCC_VREG("vRightR0", 33);
   #pragma VCC_VREG("vRightR1", 34);
   #pragma VCC_VREG("vSAD0", 35);
   #pragma VCC_VREG("vSAD1", 36);
   

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
   

   __vcop_vloop(__vcop_compute(), 21u, 14u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(28), _VREG(25));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(28), _VREG(26));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(0), _PREG(18), _PREG(19), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(20), _PREG(21), _PREG(22), _PREG(0));
   __vcop_vagen(_AGEN(4), _PREG(23), _PREG(24), _PREG(25), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(26), _AGEN(1), _VREG(18), __vcop_once());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(6), _AGEN(3), _VPAIR(29,30), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(8), _AGEN(4), _VPAIR(33,34), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(10), _AGEN(3), _VPAIR(27,28), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(12), _AGEN(4), _VPAIR(31,32), __vcop_alws());
   __vcop_vsad(_VREG(29), _VREG(33), _VREG(25));
   __vcop_vsad(_VREG(30), _VREG(34), _VREG(26));
   __vcop_vabsdif(_VREG(27), _VREG(31), _VREG(35));
   __vcop_vabsdif(_VREG(28), _VREG(32), _VREG(36));
   __vcop_vsub(_VREG(25), _VREG(35), _VREG(25));
   __vcop_vsub(_VREG(26), _VREG(36), _VREG(26));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_pdda(_VREG(18)), __vcop_last_i4(), _VREG(25), _PREG(14), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_pdda(_VREG(18)), __vcop_last_i4(), _VREG(26), _PREG(16), _AGEN(2), _PREG(0));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vAcc", 37);
   #pragma VCC_VREG("vEven", 38);
   #pragma VCC_VREG("vEvenAcc", 39);
   #pragma VCC_VREG("vOdd", 40);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("agen0", "A0");
   #pragma EVE_REG("agenOffset", "A1");
   #pragma EVE_REG("agenScratch2", "A2");
   #pragma EVE_REG("agenIn", "A3");
   #pragma EVE_REG("agenOut", "A4");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("d", "I3");
   #pragma EVE_REG("c", "I4");
   

   __vcop_vloop(__vcop_compute(), 15u, 11u, 3u);
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(0), _PREG(14), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(15), _PREG(16), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(4), _PREG(17), _PREG(18), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(20), _AGEN(1), _VREG(18), __vcop_once());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(22), _AGEN(2), _VREG(37), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(6), _AGEN(3), _VREG(38), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(8), _AGEN(3), _VREG(40), __vcop_alws());
   __vcop_vadd(_VREG(37), _VREG(38), _VREG(39));
   __vcop_vadd3(_VREG(38), _VREG(40), _VREG(37));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_pdda(_VREG(18)), __vcop_alws(), _VREG(39), _PREG(10), _AGEN(4), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_pdda(_VREG(18)), __vcop_alws(), _VREG(37), _PREG(12), _AGEN(4), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_last_i4(), _VREG(37), _PREG(22), _AGEN(2), _PREG(0));
   __vcop_vloop_end(3u);

   /* VLOOP 4 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vDisp0", 41);
   #pragma VCC_VREG("vDisp1", 42);
   #pragma VCC_VREG("vMin0", 43);
   #pragma VCC_VREG("vMin1", 44);
   #pragma VCC_VREG("vCost0", 45);
   #pragma VCC_VREG("vCost1", 46);
   #pragma VCC_VREG("vIdx", 47);
   #pragma VCC_VREG("vMinFlag0", 48);
   #pragma VCC_VREG("vMinFlag1", 49);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("agen0", "A0");
   #pragma EVE_REG("agenOffset", "A1");
   #pragma EVE_REG("agenDisp", "A2");
   #pragma EVE_REG("agenMinCost", "A3");
   #pragma EVE_REG("agenCost", "A4");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("c", "I3");
   #pragma EVE_REG("d", "I4");
   

   __vcop_vloop(__vcop_compute(), 20u, 10u, 4u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(18), _VREG(16));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(20), _VREG(43));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(20), _VREG(44));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(6), _VREG(41));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(6), _VREG(42));
   __vcop_vinit(__vcop_sizeHU(), __vcop_alws(), _PREG(68), _VREG(47));
   __vcop_vagen(_AGEN(2), _PREG(0), _PREG(14), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(0), _PREG(15), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(4), _PREG(16), _PREG(17), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(8), _AGEN(4), _VPAIR(45,46), __vcop_alws());
   __vcop_vmpy(_VREG(47), _VREG(16), _VREG(47), _PREG(0));
   __vcop_vminsetf(_VREG(45), _VREG(43), _VREG(48));
   __vcop_vminsetf(_VREG(46), _VREG(44), _VREG(49));
   __vcop_vsel(_VREG(48), _VREG(47), _VREG(41));
   __vcop_vsel(_VREG(49), _VREG(47), _VREG(42));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_intrlv(), __vcop_last_i4(), _VPAIR(43,44), _PREG(10), _AGEN(3), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_intrlv(), __vcop_last_i4(), _VPAIR(41,42), _PREG(12), _AGEN(2), _PREG(0));
   __vcop_vloop_end(4u);

}

void vcop_disparity_sad8_first_row_firstCall(
   __vptr_uint8 pLeft,
   __vptr_uint8 pRight,
   unsigned short leftStride,
   unsigned short rightStride,
   unsigned char winWidth,
   unsigned char winHeight,
   __vptr_uint8 pDisparityOutput,
   __vptr_uint16 pMinCostOutput,
   __vptr_uint16 pAllCostOutput,
   unsigned short allCostOutputStride,
   unsigned short width,
   unsigned char numDisparities,
   unsigned char disparityStep,
   __vptr_uint8 pCollateMask,
   __vptr_uint16 pOffset,
   __vptr_int16 pScratch0,
   __vptr_int16 pScratch1,
   __vptr_uint16 pCarryOver,
   unsigned short scratchStride)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_disparity_sad8_first_row_firstCall_init(pLeft, pRight, leftStride, rightStride, winWidth, winHeight, pDisparityOutput, pMinCostOutput, pAllCostOutput, allCostOutputStride, width, numDisparities, disparityStep, pCollateMask, pOffset, pScratch0, pScratch1, pCarryOver, scratchStride, __pblock_vcop_disparity_sad8_first_row_firstCall);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_disparity_sad8_first_row_firstCall_vloops(__pblock_vcop_disparity_sad8_first_row_firstCall);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_disparity_sad8_first_row_firstCall_custom(
   __vptr_uint8 pLeft,
   __vptr_uint8 pRight,
   unsigned short leftStride,
   unsigned short rightStride,
   unsigned char winWidth,
   unsigned char winHeight,
   __vptr_uint8 pDisparityOutput,
   __vptr_uint16 pMinCostOutput,
   __vptr_uint16 pAllCostOutput,
   unsigned short allCostOutputStride,
   unsigned short width,
   unsigned char numDisparities,
   unsigned char disparityStep,
   __vptr_uint8 pCollateMask,
   __vptr_uint16 pOffset,
   __vptr_int16 pScratch0,
   __vptr_int16 pScratch1,
   __vptr_uint16 pCarryOver,
   unsigned short scratchStride,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_disparity_sad8_first_row_firstCall_init(pLeft, pRight, leftStride, rightStride, winWidth, winHeight, pDisparityOutput, pMinCostOutput, pAllCostOutput, allCostOutputStride, width, numDisparities, disparityStep, pCollateMask, pOffset, pScratch0, pScratch1, pCarryOver, scratchStride, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_disparity_sad8_first_row_firstCall_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_disparity_sad8_first_row, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_disparity_sad8_first_row, __ALIGNOF__(int));
unsigned short __pblock_vcop_disparity_sad8_first_row[70];

unsigned int vcop_disparity_sad8_first_row_param_count(void)
{
   return 70u;
}

unsigned int vcop_disparity_sad8_first_row_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_disparity_sad8_first_row_init(
   __vptr_uint8 pLeft,
   __vptr_uint8 pRight,
   unsigned short leftStride,
   unsigned short rightStride,
   unsigned char winWidth,
   unsigned char winHeight,
   __vptr_uint8 pDisparityOutput,
   __vptr_uint16 pMinCostOutput,
   __vptr_uint16 pAllCostOutput,
   unsigned short allCostOutputStride,
   unsigned short width,
   unsigned char numDisparities,
   unsigned char disparityStep,
   __vptr_uint8 pCollateMask,
   __vptr_uint16 pOffset,
   __vptr_int16 pScratch0,
   __vptr_int16 pScratch1,
   __vptr_uint16 pCarryOver,
   unsigned short scratchStride,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), ((numDisparities/disparityStep))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((((width) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (winHeight)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pLeft+(winWidth-1)*sizeof(*pLeft));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pRight+(disparityStep-1)*sizeof(*pLeft)+(winWidth-1)*sizeof(*pLeft));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pLeft-sizeof(*pLeft));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pRight+(disparityStep-1)*sizeof(*pLeft)-sizeof(*pLeft));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pScratch0);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pScratch1);
   __vcop_pblock_init16(pblock, __offset+_PREG(18), (8u*scratchStride));
   __vcop_pblock_init16(pblock, __offset+_PREG(19), (sizeof(*pAllCostOutput)) -(8u*scratchStride)*(((((width) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(20), (leftStride*sizeof(*pLeft)));
   __vcop_pblock_init16(pblock, __offset+_PREG(21), ((2*8u)*sizeof(*pLeft)) -(leftStride*sizeof(*pLeft))*((winHeight)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(22),  -((2*8u)*sizeof(*pLeft))*(((((width) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u) -(leftStride*sizeof(*pLeft))*((winHeight)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(23), (rightStride*sizeof(*pLeft)));
   __vcop_pblock_init16(pblock, __offset+_PREG(24), ((2*8u)*sizeof(*pLeft)) -(rightStride*sizeof(*pLeft))*((winHeight)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(25), (disparityStep*sizeof(*pLeft)) -((2*8u)*sizeof(*pLeft))*(((((width) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u) -(rightStride*sizeof(*pLeft))*((winHeight)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)pOffset);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), 0);
   __offset += 28;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((((numDisparities/disparityStep) + (8u)-1) & ~((8u)-1))/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (width/2)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pScratch0);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pScratch1);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pAllCostOutput);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pAllCostOutput+sizeof(*pAllCostOutput));
   __vcop_pblock_init16(pblock, __offset+_PREG(14), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(15), (scratchStride));
   __vcop_pblock_init16(pblock, __offset+_PREG(16), (8u*sizeof(*pScratch0)) -(scratchStride)*((width/2)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(17), 4);
   __vcop_pblock_init16(pblock, __offset+_PREG(18), (8u*allCostOutputStride) -(2*sizeof(*pAllCostOutput))*((width/2)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pOffset+16);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)pCarryOver);
   __offset += 22;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((((width) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((numDisparities/disparityStep))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pAllCostOutput+(numDisparities/disparityStep-1)*allCostOutputStride);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pMinCostOutput);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pDisparityOutput);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(15), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(16), (-allCostOutputStride));
   __vcop_pblock_init16(pblock, __offset+_PREG(17), ((2*8u)*sizeof(*pAllCostOutput)) -(-allCostOutputStride)*(((numDisparities/disparityStep))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), disparityStep);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), 65535);
   __offset += 20;

   return 70u;
}

void vcop_disparity_sad8_first_row_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("vDisparityStep", 16);
   #pragma VCC_VREG("vOfst", 17);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vColDiff0", 18);
   #pragma VCC_VREG("vColDiff1", 19);
   #pragma VCC_VREG("vLeftL0", 20);
   #pragma VCC_VREG("vLeftL1", 21);
   #pragma VCC_VREG("vLeftR0", 22);
   #pragma VCC_VREG("vLeftR1", 23);
   #pragma VCC_VREG("vRightL0", 24);
   #pragma VCC_VREG("vRightL1", 25);
   #pragma VCC_VREG("vRightR0", 26);
   #pragma VCC_VREG("vRightR1", 27);
   #pragma VCC_VREG("vSAD0", 28);
   #pragma VCC_VREG("vSAD1", 29);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("agenOffset", "A0");
   #pragma EVE_REG("agenOut", "A1");
   #pragma EVE_REG("agenLeft", "A2");
   #pragma EVE_REG("agenRight", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("d", "I2");
   #pragma EVE_REG("c", "I3");
   #pragma EVE_REG("h", "I4");
   

   __vcop_vloop(__vcop_compute(), 20u, 14u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(28), _VREG(18));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(28), _VREG(19));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(18), _PREG(19), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(20), _PREG(21), _PREG(22), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(23), _PREG(24), _PREG(25), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(26), _AGEN(0), _VREG(17), __vcop_once());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(6), _AGEN(2), _VPAIR(22,23), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(8), _AGEN(3), _VPAIR(26,27), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(10), _AGEN(2), _VPAIR(20,21), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(12), _AGEN(3), _VPAIR(24,25), __vcop_alws());
   __vcop_vsad(_VREG(22), _VREG(26), _VREG(18));
   __vcop_vsad(_VREG(23), _VREG(27), _VREG(19));
   __vcop_vabsdif(_VREG(20), _VREG(24), _VREG(28));
   __vcop_vabsdif(_VREG(21), _VREG(25), _VREG(29));
   __vcop_vsub(_VREG(18), _VREG(28), _VREG(18));
   __vcop_vsub(_VREG(19), _VREG(29), _VREG(19));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_pdda(_VREG(17)), __vcop_last_i4(), _VREG(18), _PREG(14), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_pdda(_VREG(17)), __vcop_last_i4(), _VREG(19), _PREG(16), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vAcc", 30);
   #pragma VCC_VREG("vEven", 31);
   #pragma VCC_VREG("vEvenAcc", 32);
   #pragma VCC_VREG("vOdd", 33);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("agenOffset", "A0");
   #pragma EVE_REG("agenScratch2", "A1");
   #pragma EVE_REG("agenIn", "A2");
   #pragma EVE_REG("agenOut", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("d", "I3");
   #pragma EVE_REG("c", "I4");
   

   __vcop_vloop(__vcop_compute(), 14u, 11u, 2u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(14), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(15), _PREG(16), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(17), _PREG(18), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(20), _AGEN(0), _VREG(17), __vcop_once());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(22), _AGEN(1), _VREG(30), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(6), _AGEN(2), _VREG(31), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(8), _AGEN(2), _VREG(33), __vcop_alws());
   __vcop_vadd(_VREG(30), _VREG(31), _VREG(32));
   __vcop_vadd3(_VREG(31), _VREG(33), _VREG(30));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_pdda(_VREG(17)), __vcop_alws(), _VREG(32), _PREG(10), _AGEN(3), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_pdda(_VREG(17)), __vcop_alws(), _VREG(30), _PREG(12), _AGEN(3), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_last_i4(), _VREG(30), _PREG(22), _AGEN(1), _PREG(0));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vDisp0", 34);
   #pragma VCC_VREG("vDisp1", 35);
   #pragma VCC_VREG("vMin0", 36);
   #pragma VCC_VREG("vMin1", 37);
   #pragma VCC_VREG("vCost0", 38);
   #pragma VCC_VREG("vCost1", 39);
   #pragma VCC_VREG("vIdx", 40);
   #pragma VCC_VREG("vMinFlag0", 41);
   #pragma VCC_VREG("vMinFlag1", 42);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("agenOffset", "A0");
   #pragma EVE_REG("agenDisp", "A1");
   #pragma EVE_REG("agenMinCost", "A2");
   #pragma EVE_REG("agenCost", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("c", "I3");
   #pragma EVE_REG("d", "I4");
   

   __vcop_vloop(__vcop_compute(), 19u, 10u, 3u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(18), _VREG(16));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(20), _VREG(36));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(20), _VREG(37));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(6), _VREG(34));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(6), _VREG(35));
   __vcop_vinit(__vcop_sizeHU(), __vcop_alws(), _PREG(68), _VREG(40));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(14), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(0), _PREG(15), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(16), _PREG(17), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(8), _AGEN(3), _VPAIR(38,39), __vcop_alws());
   __vcop_vmpy(_VREG(40), _VREG(16), _VREG(40), _PREG(0));
   __vcop_vminsetf(_VREG(38), _VREG(36), _VREG(41));
   __vcop_vminsetf(_VREG(39), _VREG(37), _VREG(42));
   __vcop_vsel(_VREG(41), _VREG(40), _VREG(34));
   __vcop_vsel(_VREG(42), _VREG(40), _VREG(35));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_intrlv(), __vcop_last_i4(), _VPAIR(36,37), _PREG(10), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_intrlv(), __vcop_last_i4(), _VPAIR(34,35), _PREG(12), _AGEN(1), _PREG(0));
   __vcop_vloop_end(3u);

}

void vcop_disparity_sad8_first_row(
   __vptr_uint8 pLeft,
   __vptr_uint8 pRight,
   unsigned short leftStride,
   unsigned short rightStride,
   unsigned char winWidth,
   unsigned char winHeight,
   __vptr_uint8 pDisparityOutput,
   __vptr_uint16 pMinCostOutput,
   __vptr_uint16 pAllCostOutput,
   unsigned short allCostOutputStride,
   unsigned short width,
   unsigned char numDisparities,
   unsigned char disparityStep,
   __vptr_uint8 pCollateMask,
   __vptr_uint16 pOffset,
   __vptr_int16 pScratch0,
   __vptr_int16 pScratch1,
   __vptr_uint16 pCarryOver,
   unsigned short scratchStride)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_disparity_sad8_first_row_init(pLeft, pRight, leftStride, rightStride, winWidth, winHeight, pDisparityOutput, pMinCostOutput, pAllCostOutput, allCostOutputStride, width, numDisparities, disparityStep, pCollateMask, pOffset, pScratch0, pScratch1, pCarryOver, scratchStride, __pblock_vcop_disparity_sad8_first_row);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_disparity_sad8_first_row_vloops(__pblock_vcop_disparity_sad8_first_row);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_disparity_sad8_first_row_custom(
   __vptr_uint8 pLeft,
   __vptr_uint8 pRight,
   unsigned short leftStride,
   unsigned short rightStride,
   unsigned char winWidth,
   unsigned char winHeight,
   __vptr_uint8 pDisparityOutput,
   __vptr_uint16 pMinCostOutput,
   __vptr_uint16 pAllCostOutput,
   unsigned short allCostOutputStride,
   unsigned short width,
   unsigned char numDisparities,
   unsigned char disparityStep,
   __vptr_uint8 pCollateMask,
   __vptr_uint16 pOffset,
   __vptr_int16 pScratch0,
   __vptr_int16 pScratch1,
   __vptr_uint16 pCarryOver,
   unsigned short scratchStride,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_disparity_sad8_first_row_init(pLeft, pRight, leftStride, rightStride, winWidth, winHeight, pDisparityOutput, pMinCostOutput, pAllCostOutput, allCostOutputStride, width, numDisparities, disparityStep, pCollateMask, pOffset, pScratch0, pScratch1, pCarryOver, scratchStride, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_disparity_sad8_first_row_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_disparity_sad8_nth_row_firstCall, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_disparity_sad8_nth_row_firstCall, __ALIGNOF__(int));
unsigned short __pblock_vcop_disparity_sad8_nth_row_firstCall[112];

unsigned int vcop_disparity_sad8_nth_row_firstCall_param_count(void)
{
   return 112u;
}

unsigned int vcop_disparity_sad8_nth_row_firstCall_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_disparity_sad8_nth_row_firstCall_init(
   __vptr_uint8 pLeft,
   __vptr_uint8 pRight,
   unsigned short leftStride,
   unsigned short rightStride,
   unsigned char winWidth,
   unsigned char winHeight,
   __vptr_uint8 pDisparityOutput,
   __vptr_uint16 pMinCostOutput,
   __vptr_uint16 pAllCostOutput,
   unsigned short allCostOutputStride,
   unsigned short width,
   unsigned char numDisparities,
   unsigned char disparityStep,
   __vptr_uint8 pCollateMask,
   __vptr_uint16 pOffset,
   __vptr_int16 pScratch0,
   __vptr_int16 pScratch1,
   __vptr_int16 pScratch2,
   __vptr_uint16 pCarryOver,
   unsigned short scratchStride,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((numDisparities/disparityStep))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((width-(2*(8u))) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pLeft+2*8u*sizeof(*pLeft)+(leftStride*(winHeight-1)+(winWidth-1))*sizeof(*pLeft));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pRight+(disparityStep-1)*sizeof(*pLeft)+2*8u*sizeof(*pLeft)+(rightStride*(winHeight-1)+(winWidth-1))*sizeof(*pLeft));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pLeft+2*8u*sizeof(*pLeft)+(leftStride*-1+(winWidth-1))*sizeof(*pLeft));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pRight+(disparityStep-1)*sizeof(*pLeft)+2*8u*sizeof(*pLeft)+(rightStride*-1+(winWidth-1))*sizeof(*pLeft));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pLeft+2*8u*sizeof(*pLeft)+(leftStride*(winHeight-1)+-1)*sizeof(*pLeft));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pRight+(disparityStep-1)*sizeof(*pLeft)+2*8u*sizeof(*pLeft)+(rightStride*(winHeight-1)+-1)*sizeof(*pLeft));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pScratch2);
   __vcop_pblock_init16(pblock, __offset+_PREG(20), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(21),  -((2*8u)*sizeof(*pLeft))*(((((width-(2*(8u))) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(22), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(23), ((width-2*8u+2*8u-1&~(2*8u-1))*sizeof(*pAllCostOutput)) -((2*8u)*sizeof(*pAllCostOutput))*(((((width-(2*(8u))) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(24), (disparityStep*sizeof(*pLeft)) -((2*8u)*sizeof(*pLeft))*(((((width-(2*(8u))) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)pLeft+2*8u*sizeof(*pLeft)+(leftStride*-1+-1)*sizeof(*pLeft));
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)pRight+(disparityStep-1)*sizeof(*pLeft)+2*8u*sizeof(*pLeft)+(rightStride*-1+-1)*sizeof(*pLeft));
   __offset += 28;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((numDisparities/disparityStep))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((width-(2*(8u))) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pScratch0);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pScratch1);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), ((width-2*8u+2*8u-1&~(2*8u-1))*sizeof(*pAllCostOutput)) -((2*8u)*sizeof(*pAllCostOutput))*(((((width-(2*(8u))) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), (8u*scratchStride));
   __vcop_pblock_init16(pblock, __offset+_PREG(13), (sizeof(*pAllCostOutput)) -(8u*scratchStride)*(((((width-(2*(8u))) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pOffset);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pScratch2);
   __offset += 16;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((numDisparities/disparityStep))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (winWidth)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pLeft+leftStride*(winHeight-1)*sizeof(*pLeft));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pRight+(disparityStep-1)*sizeof(*pLeft)+rightStride*(winHeight-1)*sizeof(*pLeft));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pLeft-leftStride*sizeof(*pLeft));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pRight+(disparityStep-1)*sizeof(*pLeft)-rightStride*sizeof(*pLeft));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pScratch2);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pCarryOver);
   __vcop_pblock_init16(pblock, __offset+_PREG(18), (allCostOutputStride));
   __vcop_pblock_init16(pblock, __offset+_PREG(19),  -(sizeof(*pLeft))*((winWidth)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(20), (disparityStep*sizeof(*pLeft)) -(sizeof(*pLeft))*((winWidth)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)pCollateMask);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), 0);
   __offset += 24;

   /* Loop 4 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((((numDisparities/disparityStep) + (8u)-1) & ~((8u)-1))/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((width-(2*(8u)))/2)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pScratch0);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pScratch1);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pScratch2+2*8u*sizeof(*pAllCostOutput));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pScratch2+(2*8u+1)*sizeof(*pAllCostOutput));
   __vcop_pblock_init16(pblock, __offset+_PREG(14), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(15), (scratchStride));
   __vcop_pblock_init16(pblock, __offset+_PREG(16), (8u*sizeof(*pScratch0)) -(scratchStride)*(((width-(2*(8u)))/2)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(17), 4);
   __vcop_pblock_init16(pblock, __offset+_PREG(18), (8u*allCostOutputStride) -(2*sizeof(*pAllCostOutput))*(((width-(2*(8u)))/2)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pOffset+16);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)pCarryOver);
   __offset += 22;

   /* Loop 5 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((((width) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((numDisparities/disparityStep))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pAllCostOutput+(numDisparities/disparityStep-1)*allCostOutputStride);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pScratch2+(numDisparities/disparityStep-1)*allCostOutputStride);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pMinCostOutput);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pDisparityOutput);
   __vcop_pblock_init16(pblock, __offset+_PREG(16), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(17), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(18), (-allCostOutputStride));
   __vcop_pblock_init16(pblock, __offset+_PREG(19), ((2*8u)*sizeof(*pAllCostOutput)) -(-allCostOutputStride)*(((numDisparities/disparityStep))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), disparityStep);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), 65535);
   __offset += 22;

   return 112u;
}

void vcop_disparity_sad8_nth_row_firstCall_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("vDisparityStep", 16);
   #pragma VCC_VREG("vMask", 17);
   #pragma VCC_VREG("vOfst", 18);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vLeftBL0", 19);
   #pragma VCC_VREG("vLeftBL1", 20);
   #pragma VCC_VREG("vLeftBR0", 21);
   #pragma VCC_VREG("vLeftBR1", 22);
   #pragma VCC_VREG("vLeftUL0", 23);
   #pragma VCC_VREG("vLeftUL1", 24);
   #pragma VCC_VREG("vLeftUR0", 25);
   #pragma VCC_VREG("vLeftUR1", 26);
   #pragma VCC_VREG("vPtDiff0", 27);
   #pragma VCC_VREG("vPtDiff0Neg", 28);
   #pragma VCC_VREG("vPtDiff0Pos", 29);
   #pragma VCC_VREG("vPtDiff1", 30);
   #pragma VCC_VREG("vPtDiff1Neg", 31);
   #pragma VCC_VREG("vPtDiff1Pos", 32);
   #pragma VCC_VREG("vRightBL0", 33);
   #pragma VCC_VREG("vRightBL1", 34);
   #pragma VCC_VREG("vRightBR0", 35);
   #pragma VCC_VREG("vRightBR1", 36);
   #pragma VCC_VREG("vRightUL0", 37);
   #pragma VCC_VREG("vRightUL1", 38);
   #pragma VCC_VREG("vRightUR0", 39);
   #pragma VCC_VREG("vRightUR1", 40);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("agenLeft", "A0");
   #pragma EVE_REG("agenOut", "A1");
   #pragma EVE_REG("agenRight", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("d", "I3");
   #pragma EVE_REG("c", "I4");
   

   __vcop_vloop(__vcop_compute(), 23u, 14u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(20), _PREG(21), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(22), _PREG(23), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(20), _PREG(24), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(26), _AGEN(0), _VPAIR(23,24), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(28), _AGEN(2), _VPAIR(37,38), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(6), _AGEN(0), _VPAIR(21,22), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(8), _AGEN(2), _VPAIR(35,36), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(10), _AGEN(0), _VPAIR(25,26), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(12), _AGEN(2), _VPAIR(39,40), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(14), _AGEN(0), _VPAIR(19,20), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(16), _AGEN(2), _VPAIR(33,34), __vcop_alws());
   __vcop_vabsdif(_VREG(23), _VREG(37), _VREG(29));
   __vcop_vabsdif(_VREG(24), _VREG(38), _VREG(32));
   __vcop_vsad(_VREG(21), _VREG(35), _VREG(29));
   __vcop_vsad(_VREG(22), _VREG(36), _VREG(32));
   __vcop_vabsdif(_VREG(25), _VREG(39), _VREG(28));
   __vcop_vabsdif(_VREG(26), _VREG(40), _VREG(31));
   __vcop_vsad(_VREG(19), _VREG(33), _VREG(28));
   __vcop_vsad(_VREG(20), _VREG(34), _VREG(31));
   __vcop_vsub(_VREG(29), _VREG(28), _VREG(27));
   __vcop_vsub(_VREG(32), _VREG(31), _VREG(30));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_alws(), _VPAIR(27,30), _PREG(18), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vPtDiff0", 41);
   #pragma VCC_VREG("vPtDiff1", 42);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("agenOffset", "A0");
   #pragma EVE_REG("agenIn", "A1");
   #pragma EVE_REG("agenOut", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("d", "I3");
   #pragma EVE_REG("c", "I4");
   

   __vcop_vloop(__vcop_compute(), 8u, 8u, 2u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(10), _PREG(11), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(12), _PREG(13), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(14), _AGEN(0), _VREG(18), __vcop_once());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(16), _AGEN(1), _VPAIR(41,42), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_pdda(_VREG(18)), __vcop_alws(), _VREG(41), _PREG(6), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_pdda(_VREG(18)), __vcop_alws(), _VREG(42), _PREG(8), _AGEN(2), _PREG(0));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vRowDiff0", 43);
   #pragma VCC_VREG("vRowDiff1", 44);
   #pragma VCC_VREG("vLeftB0", 45);
   #pragma VCC_VREG("vLeftB1", 46);
   #pragma VCC_VREG("vLeftU0", 47);
   #pragma VCC_VREG("vLeftU1", 48);
   #pragma VCC_VREG("vRightB0", 49);
   #pragma VCC_VREG("vRightB1", 50);
   #pragma VCC_VREG("vRightU0", 51);
   #pragma VCC_VREG("vRightU1", 52);
   #pragma VCC_VREG("vSAD0", 53);
   #pragma VCC_VREG("vSAD1", 54);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("agen0", "A0");
   #pragma EVE_REG("agenOffset", "A1");
   #pragma EVE_REG("agenCost", "A2");
   #pragma EVE_REG("agenLeft", "A3");
   #pragma EVE_REG("agenRight", "A4");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("d", "I3");
   #pragma EVE_REG("w", "I4");
   

   __vcop_vloop(__vcop_compute(), 21u, 12u, 3u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(24), _VREG(43));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(24), _VREG(44));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(0), _PREG(18), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(1), _PREG(19), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(4), _PREG(1), _PREG(20), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_nbits(), _PREG(22), _AGEN(0), _VREG(17), __vcop_once());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(6), _AGEN(3), _VPAIR(45,46), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(8), _AGEN(4), _VPAIR(49,50), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(10), _AGEN(3), _VPAIR(47,48), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(12), _AGEN(4), _VPAIR(51,52), __vcop_alws());
   __vcop_vsad(_VREG(45), _VREG(49), _VREG(43));
   __vcop_vsad(_VREG(46), _VREG(50), _VREG(44));
   __vcop_vabsdif(_VREG(47), _VREG(51), _VREG(53));
   __vcop_vabsdif(_VREG(48), _VREG(52), _VREG(54));
   __vcop_vsub(_VREG(43), _VREG(53), _VREG(43));
   __vcop_vsub(_VREG(44), _VREG(54), _VREG(44));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_last_i4(), _VPAIR(43,44), _PREG(14), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_predicate(_VREG(17)), __vcop_sizeHU(), __vcop_collat(), __vcop_last_i4(), _VREG(44), _PREG(16), _AGEN(0), _PREG(0));
   __vcop_vloop_end(3u);

   /* VLOOP 4 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vAcc", 55);
   #pragma VCC_VREG("vEven", 56);
   #pragma VCC_VREG("vEvenAcc", 57);
   #pragma VCC_VREG("vOdd", 58);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("agen0", "A0");
   #pragma EVE_REG("agenOffset", "A1");
   #pragma EVE_REG("agenScratch2", "A2");
   #pragma EVE_REG("agenIn", "A3");
   #pragma EVE_REG("agenOut", "A4");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("d", "I3");
   #pragma EVE_REG("c", "I4");
   

   __vcop_vloop(__vcop_compute(), 15u, 11u, 4u);
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(0), _PREG(14), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(15), _PREG(16), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(4), _PREG(17), _PREG(18), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(20), _AGEN(1), _VREG(18), __vcop_once());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(22), _AGEN(2), _VREG(55), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(6), _AGEN(3), _VREG(56), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(8), _AGEN(3), _VREG(58), __vcop_alws());
   __vcop_vadd(_VREG(55), _VREG(56), _VREG(57));
   __vcop_vadd3(_VREG(56), _VREG(58), _VREG(55));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_pdda(_VREG(18)), __vcop_alws(), _VREG(57), _PREG(10), _AGEN(4), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_pdda(_VREG(18)), __vcop_alws(), _VREG(55), _PREG(12), _AGEN(4), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_last_i4(), _VREG(55), _PREG(22), _AGEN(2), _PREG(0));
   __vcop_vloop_end(4u);

   /* VLOOP 5 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vDisp0", 59);
   #pragma VCC_VREG("vDisp1", 60);
   #pragma VCC_VREG("vMin0", 61);
   #pragma VCC_VREG("vMin1", 62);
   #pragma VCC_VREG("vCost0", 63);
   #pragma VCC_VREG("vCost1", 64);
   #pragma VCC_VREG("vIdx", 65);
   #pragma VCC_VREG("vMinFlag0", 66);
   #pragma VCC_VREG("vMinFlag1", 67);
   #pragma VCC_VREG("vPartial0", 68);
   #pragma VCC_VREG("vPartial1", 69);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("agen0", "A0");
   #pragma EVE_REG("agenOffset", "A1");
   #pragma EVE_REG("agenDisp", "A2");
   #pragma EVE_REG("agenMinCost", "A3");
   #pragma EVE_REG("agenCost", "A4");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("c", "I3");
   #pragma EVE_REG("d", "I4");
   

   __vcop_vloop(__vcop_compute(), 24u, 11u, 5u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(20), _VREG(16));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(22), _VREG(61));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(22), _VREG(62));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(6), _VREG(59));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(6), _VREG(60));
   __vcop_vinit(__vcop_sizeHU(), __vcop_alws(), _PREG(68), _VREG(65));
   __vcop_vagen(_AGEN(2), _PREG(0), _PREG(16), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(0), _PREG(17), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(4), _PREG(18), _PREG(19), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(8), _AGEN(4), _VPAIR(63,64), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(10), _AGEN(4), _VPAIR(68,69), __vcop_alws());
   __vcop_vmpy(_VREG(65), _VREG(16), _VREG(65), _PREG(0));
   __vcop_vadd(_VREG(63), _VREG(68), _VREG(63));
   __vcop_vadd(_VREG(64), _VREG(69), _VREG(64));
   __vcop_vminsetf(_VREG(63), _VREG(61), _VREG(66));
   __vcop_vminsetf(_VREG(64), _VREG(62), _VREG(67));
   __vcop_vsel(_VREG(66), _VREG(65), _VREG(59));
   __vcop_vsel(_VREG(67), _VREG(65), _VREG(60));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(63,64), _PREG(8), _AGEN(4), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_intrlv(), __vcop_last_i4(), _VPAIR(61,62), _PREG(12), _AGEN(3), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_intrlv(), __vcop_last_i4(), _VPAIR(59,60), _PREG(14), _AGEN(2), _PREG(0));
   __vcop_vloop_end(5u);

}

void vcop_disparity_sad8_nth_row_firstCall(
   __vptr_uint8 pLeft,
   __vptr_uint8 pRight,
   unsigned short leftStride,
   unsigned short rightStride,
   unsigned char winWidth,
   unsigned char winHeight,
   __vptr_uint8 pDisparityOutput,
   __vptr_uint16 pMinCostOutput,
   __vptr_uint16 pAllCostOutput,
   unsigned short allCostOutputStride,
   unsigned short width,
   unsigned char numDisparities,
   unsigned char disparityStep,
   __vptr_uint8 pCollateMask,
   __vptr_uint16 pOffset,
   __vptr_int16 pScratch0,
   __vptr_int16 pScratch1,
   __vptr_int16 pScratch2,
   __vptr_uint16 pCarryOver,
   unsigned short scratchStride)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_disparity_sad8_nth_row_firstCall_init(pLeft, pRight, leftStride, rightStride, winWidth, winHeight, pDisparityOutput, pMinCostOutput, pAllCostOutput, allCostOutputStride, width, numDisparities, disparityStep, pCollateMask, pOffset, pScratch0, pScratch1, pScratch2, pCarryOver, scratchStride, __pblock_vcop_disparity_sad8_nth_row_firstCall);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_disparity_sad8_nth_row_firstCall_vloops(__pblock_vcop_disparity_sad8_nth_row_firstCall);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_disparity_sad8_nth_row_firstCall_custom(
   __vptr_uint8 pLeft,
   __vptr_uint8 pRight,
   unsigned short leftStride,
   unsigned short rightStride,
   unsigned char winWidth,
   unsigned char winHeight,
   __vptr_uint8 pDisparityOutput,
   __vptr_uint16 pMinCostOutput,
   __vptr_uint16 pAllCostOutput,
   unsigned short allCostOutputStride,
   unsigned short width,
   unsigned char numDisparities,
   unsigned char disparityStep,
   __vptr_uint8 pCollateMask,
   __vptr_uint16 pOffset,
   __vptr_int16 pScratch0,
   __vptr_int16 pScratch1,
   __vptr_int16 pScratch2,
   __vptr_uint16 pCarryOver,
   unsigned short scratchStride,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_disparity_sad8_nth_row_firstCall_init(pLeft, pRight, leftStride, rightStride, winWidth, winHeight, pDisparityOutput, pMinCostOutput, pAllCostOutput, allCostOutputStride, width, numDisparities, disparityStep, pCollateMask, pOffset, pScratch0, pScratch1, pScratch2, pCarryOver, scratchStride, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_disparity_sad8_nth_row_firstCall_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_disparity_sad8_nth_row, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_disparity_sad8_nth_row, __ALIGNOF__(int));
unsigned short __pblock_vcop_disparity_sad8_nth_row[88];

unsigned int vcop_disparity_sad8_nth_row_param_count(void)
{
   return 88u;
}

unsigned int vcop_disparity_sad8_nth_row_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_disparity_sad8_nth_row_init(
   __vptr_uint8 pLeft,
   __vptr_uint8 pRight,
   unsigned short leftStride,
   unsigned short rightStride,
   unsigned char winWidth,
   unsigned char winHeight,
   __vptr_uint8 pDisparityOutput,
   __vptr_uint16 pMinCostOutput,
   __vptr_uint16 pAllCostOutput,
   unsigned short allCostOutputStride,
   unsigned short width,
   unsigned char numDisparities,
   unsigned char disparityStep,
   __vptr_uint8 pCollateMask,
   __vptr_uint16 pOffset,
   __vptr_int16 pScratch0,
   __vptr_int16 pScratch1,
   __vptr_int16 pScratch2,
   __vptr_uint16 pCarryOver,
   unsigned short scratchStride,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((numDisparities/disparityStep))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((width) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pLeft+(leftStride*(winHeight-1)+(winWidth-1))*sizeof(*pLeft));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pRight+(disparityStep-1)*sizeof(*pLeft)+(rightStride*(winHeight-1)+(winWidth-1))*sizeof(*pLeft));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pLeft+(leftStride*-1+(winWidth-1))*sizeof(*pLeft));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pRight+(disparityStep-1)*sizeof(*pLeft)+(rightStride*-1+(winWidth-1))*sizeof(*pLeft));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pLeft+(leftStride*(winHeight-1)+-1)*sizeof(*pLeft));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pRight+(disparityStep-1)*sizeof(*pLeft)+(rightStride*(winHeight-1)+-1)*sizeof(*pLeft));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pScratch2);
   __vcop_pblock_init16(pblock, __offset+_PREG(20), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(21),  -((2*8u)*sizeof(*pLeft))*(((((width) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(22), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(23), ((width+2*8u-1&~(2*8u-1))*sizeof(*pAllCostOutput)) -((2*8u)*sizeof(*pAllCostOutput))*(((((width) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(24), (disparityStep*sizeof(*pLeft)) -((2*8u)*sizeof(*pLeft))*(((((width) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)pLeft+(leftStride*-1+-1)*sizeof(*pLeft));
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)pRight+(disparityStep-1)*sizeof(*pLeft)+(rightStride*-1+-1)*sizeof(*pLeft));
   __offset += 28;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((numDisparities/disparityStep))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((width) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pScratch0);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pScratch1);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), ((width+2*8u-1&~(2*8u-1))*sizeof(*pAllCostOutput)) -((2*8u)*sizeof(*pAllCostOutput))*(((((width) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), (8u*scratchStride));
   __vcop_pblock_init16(pblock, __offset+_PREG(13), (sizeof(*pAllCostOutput)) -(8u*scratchStride)*(((((width) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pOffset);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pScratch2);
   __offset += 16;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((((numDisparities/disparityStep) + (8u)-1) & ~((8u)-1))/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((width)/2)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pScratch0);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pScratch1);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pScratch2);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pScratch2+sizeof(*pAllCostOutput));
   __vcop_pblock_init16(pblock, __offset+_PREG(14), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(15), (scratchStride));
   __vcop_pblock_init16(pblock, __offset+_PREG(16), (8u*sizeof(*pScratch0)) -(scratchStride)*(((width)/2)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(17), 4);
   __vcop_pblock_init16(pblock, __offset+_PREG(18), (8u*allCostOutputStride) -(2*sizeof(*pAllCostOutput))*(((width)/2)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pOffset+16);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)pCarryOver);
   __offset += 22;

   /* Loop 4 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((((width) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((numDisparities/disparityStep))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pAllCostOutput+(numDisparities/disparityStep-1)*allCostOutputStride);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pScratch2+(numDisparities/disparityStep-1)*allCostOutputStride);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pMinCostOutput);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pDisparityOutput);
   __vcop_pblock_init16(pblock, __offset+_PREG(16), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(17), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(18), (-allCostOutputStride));
   __vcop_pblock_init16(pblock, __offset+_PREG(19), ((2*8u)*sizeof(*pAllCostOutput)) -(-allCostOutputStride)*(((numDisparities/disparityStep))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), disparityStep);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), 65535);
   __offset += 22;

   return 88u;
}

void vcop_disparity_sad8_nth_row_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("vDisparityStep", 16);
   #pragma VCC_VREG("vOfst", 17);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vLeftBL0", 18);
   #pragma VCC_VREG("vLeftBL1", 19);
   #pragma VCC_VREG("vLeftBR0", 20);
   #pragma VCC_VREG("vLeftBR1", 21);
   #pragma VCC_VREG("vLeftUL0", 22);
   #pragma VCC_VREG("vLeftUL1", 23);
   #pragma VCC_VREG("vLeftUR0", 24);
   #pragma VCC_VREG("vLeftUR1", 25);
   #pragma VCC_VREG("vPtDiff0", 26);
   #pragma VCC_VREG("vPtDiff0Neg", 27);
   #pragma VCC_VREG("vPtDiff0Pos", 28);
   #pragma VCC_VREG("vPtDiff1", 29);
   #pragma VCC_VREG("vPtDiff1Neg", 30);
   #pragma VCC_VREG("vPtDiff1Pos", 31);
   #pragma VCC_VREG("vRightBL0", 32);
   #pragma VCC_VREG("vRightBL1", 33);
   #pragma VCC_VREG("vRightBR0", 34);
   #pragma VCC_VREG("vRightBR1", 35);
   #pragma VCC_VREG("vRightUL0", 36);
   #pragma VCC_VREG("vRightUL1", 37);
   #pragma VCC_VREG("vRightUR0", 38);
   #pragma VCC_VREG("vRightUR1", 39);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("agenLeft", "A0");
   #pragma EVE_REG("agenOut", "A1");
   #pragma EVE_REG("agenRight", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("d", "I3");
   #pragma EVE_REG("c", "I4");
   

   __vcop_vloop(__vcop_compute(), 23u, 14u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(20), _PREG(21), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(22), _PREG(23), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(20), _PREG(24), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(26), _AGEN(0), _VPAIR(22,23), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(28), _AGEN(2), _VPAIR(36,37), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(6), _AGEN(0), _VPAIR(20,21), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(8), _AGEN(2), _VPAIR(34,35), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(10), _AGEN(0), _VPAIR(24,25), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(12), _AGEN(2), _VPAIR(38,39), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(14), _AGEN(0), _VPAIR(18,19), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(16), _AGEN(2), _VPAIR(32,33), __vcop_alws());
   __vcop_vabsdif(_VREG(22), _VREG(36), _VREG(28));
   __vcop_vabsdif(_VREG(23), _VREG(37), _VREG(31));
   __vcop_vsad(_VREG(20), _VREG(34), _VREG(28));
   __vcop_vsad(_VREG(21), _VREG(35), _VREG(31));
   __vcop_vabsdif(_VREG(24), _VREG(38), _VREG(27));
   __vcop_vabsdif(_VREG(25), _VREG(39), _VREG(30));
   __vcop_vsad(_VREG(18), _VREG(32), _VREG(27));
   __vcop_vsad(_VREG(19), _VREG(33), _VREG(30));
   __vcop_vsub(_VREG(28), _VREG(27), _VREG(26));
   __vcop_vsub(_VREG(31), _VREG(30), _VREG(29));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_alws(), _VPAIR(26,29), _PREG(18), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vPtDiff0", 40);
   #pragma VCC_VREG("vPtDiff1", 41);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("agenOffset", "A0");
   #pragma EVE_REG("agenIn", "A1");
   #pragma EVE_REG("agenOut", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("d", "I3");
   #pragma EVE_REG("c", "I4");
   

   __vcop_vloop(__vcop_compute(), 8u, 8u, 2u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(10), _PREG(11), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(12), _PREG(13), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(14), _AGEN(0), _VREG(17), __vcop_once());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(16), _AGEN(1), _VPAIR(40,41), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_pdda(_VREG(17)), __vcop_alws(), _VREG(40), _PREG(6), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_pdda(_VREG(17)), __vcop_alws(), _VREG(41), _PREG(8), _AGEN(2), _PREG(0));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vAcc", 42);
   #pragma VCC_VREG("vEven", 43);
   #pragma VCC_VREG("vEvenAcc", 44);
   #pragma VCC_VREG("vOdd", 45);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("agenOffset", "A0");
   #pragma EVE_REG("agenScratch2", "A1");
   #pragma EVE_REG("agenIn", "A2");
   #pragma EVE_REG("agenOut", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("d", "I3");
   #pragma EVE_REG("c", "I4");
   

   __vcop_vloop(__vcop_compute(), 14u, 11u, 3u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(14), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(15), _PREG(16), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(17), _PREG(18), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(20), _AGEN(0), _VREG(17), __vcop_once());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(22), _AGEN(1), _VREG(42), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(6), _AGEN(2), _VREG(43), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(8), _AGEN(2), _VREG(45), __vcop_alws());
   __vcop_vadd(_VREG(42), _VREG(43), _VREG(44));
   __vcop_vadd3(_VREG(43), _VREG(45), _VREG(42));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_pdda(_VREG(17)), __vcop_alws(), _VREG(44), _PREG(10), _AGEN(3), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_pdda(_VREG(17)), __vcop_alws(), _VREG(42), _PREG(12), _AGEN(3), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_last_i4(), _VREG(42), _PREG(22), _AGEN(1), _PREG(0));
   __vcop_vloop_end(3u);

   /* VLOOP 4 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vDisp0", 46);
   #pragma VCC_VREG("vDisp1", 47);
   #pragma VCC_VREG("vMin0", 48);
   #pragma VCC_VREG("vMin1", 49);
   #pragma VCC_VREG("vCost0", 50);
   #pragma VCC_VREG("vCost1", 51);
   #pragma VCC_VREG("vIdx", 52);
   #pragma VCC_VREG("vMinFlag0", 53);
   #pragma VCC_VREG("vMinFlag1", 54);
   #pragma VCC_VREG("vPartial0", 55);
   #pragma VCC_VREG("vPartial1", 56);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("agenOffset", "A0");
   #pragma EVE_REG("agenDisp", "A1");
   #pragma EVE_REG("agenMinCost", "A2");
   #pragma EVE_REG("agenCost", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("c", "I3");
   #pragma EVE_REG("d", "I4");
   

   __vcop_vloop(__vcop_compute(), 23u, 11u, 4u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(20), _VREG(16));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(22), _VREG(48));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(22), _VREG(49));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(6), _VREG(46));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(6), _VREG(47));
   __vcop_vinit(__vcop_sizeHU(), __vcop_alws(), _PREG(68), _VREG(52));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(16), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(0), _PREG(17), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(18), _PREG(19), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(8), _AGEN(3), _VPAIR(50,51), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(10), _AGEN(3), _VPAIR(55,56), __vcop_alws());
   __vcop_vmpy(_VREG(52), _VREG(16), _VREG(52), _PREG(0));
   __vcop_vadd(_VREG(50), _VREG(55), _VREG(50));
   __vcop_vadd(_VREG(51), _VREG(56), _VREG(51));
   __vcop_vminsetf(_VREG(50), _VREG(48), _VREG(53));
   __vcop_vminsetf(_VREG(51), _VREG(49), _VREG(54));
   __vcop_vsel(_VREG(53), _VREG(52), _VREG(46));
   __vcop_vsel(_VREG(54), _VREG(52), _VREG(47));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(50,51), _PREG(8), _AGEN(3), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_intrlv(), __vcop_last_i4(), _VPAIR(48,49), _PREG(12), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_intrlv(), __vcop_last_i4(), _VPAIR(46,47), _PREG(14), _AGEN(1), _PREG(0));
   __vcop_vloop_end(4u);

}

void vcop_disparity_sad8_nth_row(
   __vptr_uint8 pLeft,
   __vptr_uint8 pRight,
   unsigned short leftStride,
   unsigned short rightStride,
   unsigned char winWidth,
   unsigned char winHeight,
   __vptr_uint8 pDisparityOutput,
   __vptr_uint16 pMinCostOutput,
   __vptr_uint16 pAllCostOutput,
   unsigned short allCostOutputStride,
   unsigned short width,
   unsigned char numDisparities,
   unsigned char disparityStep,
   __vptr_uint8 pCollateMask,
   __vptr_uint16 pOffset,
   __vptr_int16 pScratch0,
   __vptr_int16 pScratch1,
   __vptr_int16 pScratch2,
   __vptr_uint16 pCarryOver,
   unsigned short scratchStride)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_disparity_sad8_nth_row_init(pLeft, pRight, leftStride, rightStride, winWidth, winHeight, pDisparityOutput, pMinCostOutput, pAllCostOutput, allCostOutputStride, width, numDisparities, disparityStep, pCollateMask, pOffset, pScratch0, pScratch1, pScratch2, pCarryOver, scratchStride, __pblock_vcop_disparity_sad8_nth_row);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_disparity_sad8_nth_row_vloops(__pblock_vcop_disparity_sad8_nth_row);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_disparity_sad8_nth_row_custom(
   __vptr_uint8 pLeft,
   __vptr_uint8 pRight,
   unsigned short leftStride,
   unsigned short rightStride,
   unsigned char winWidth,
   unsigned char winHeight,
   __vptr_uint8 pDisparityOutput,
   __vptr_uint16 pMinCostOutput,
   __vptr_uint16 pAllCostOutput,
   unsigned short allCostOutputStride,
   unsigned short width,
   unsigned char numDisparities,
   unsigned char disparityStep,
   __vptr_uint8 pCollateMask,
   __vptr_uint16 pOffset,
   __vptr_int16 pScratch0,
   __vptr_int16 pScratch1,
   __vptr_int16 pScratch2,
   __vptr_uint16 pCarryOver,
   unsigned short scratchStride,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_disparity_sad8_nth_row_init(pLeft, pRight, leftStride, rightStride, winWidth, winHeight, pDisparityOutput, pMinCostOutput, pAllCostOutput, allCostOutputStride, width, numDisparities, disparityStep, pCollateMask, pOffset, pScratch0, pScratch1, pScratch2, pCarryOver, scratchStride, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_disparity_sad8_nth_row_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

