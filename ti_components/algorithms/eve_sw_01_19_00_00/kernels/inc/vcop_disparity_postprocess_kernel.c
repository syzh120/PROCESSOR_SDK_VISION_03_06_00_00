#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_disparity_genPrevAndNextMinCost, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_disparity_genPrevAndNextMinCost, __ALIGNOF__(int));
unsigned short __pblock_vcop_disparity_genPrevAndNextMinCost[42];

unsigned int vcop_disparity_genPrevAndNextMinCost_param_count(void)
{
   return 42u;
}

unsigned int vcop_disparity_genPrevAndNextMinCost_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_disparity_genPrevAndNextMinCost_init(
   __vptr_uint8 disparity,
   __vptr_uint16 allCost,
   __vptr_uint16 prevMinCostOutput,
   __vptr_uint16 nextMinCostOutput,
   __vptr_uint16 scratchIndex,
   unsigned short width,
   unsigned short allCostStride,
   unsigned char numDisparities,
   unsigned char disparityStep,
   unsigned char disparityStepShift,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((width) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)disparity);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)disparity+8u*sizeof(*disparity));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)scratchIndex);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)scratchIndex+8u*sizeof(*scratchIndex));
   __vcop_pblock_init16(pblock, __offset+_PREG(14), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(15), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (numDisparities/disparityStep - 1)*disparityStep);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), allCostStride/sizeof(*allCost));
   __offset += 18;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (width)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_TRUNC,disparityStepShift));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 2);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)prevMinCostOutput);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)scratchIndex);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)allCost+allCostStride);
   __offset += 12;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (width)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_TRUNC,disparityStepShift));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 2);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)nextMinCostOutput);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)scratchIndex);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)allCost-allCostStride);
   __offset += 12;

   return 42u;
}

void vcop_disparity_genPrevAndNextMinCost_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("vMaxDisp", 16);
   #pragma VCC_VREG("vStride", 17);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vDisparity0", 18);
   #pragma VCC_VREG("vDisparity1", 19);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("dispAddr", "A0");
   #pragma EVE_REG("indexAddr", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("w", "I4");
   

   __vcop_vloop(__vcop_compute(), 13u, 9u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(16), _VREG(16));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(18), _VREG(17));
   __vcop_vagen(_AGEN(0), _PREG(14), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(15), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(6), _AGEN(0), _VREG(18), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(8), _AGEN(0), _VREG(19), __vcop_alws());
   __vcop_vsub(_VREG(16), _VREG(18), _VREG(18));
   __vcop_vsub(_VREG(16), _VREG(19), _VREG(19));
   __vcop_vmpy(_VREG(18), _VREG(17), _VREG(18), _PREG(0));
   __vcop_vmpy(_VREG(19), _VREG(17), _VREG(19), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(18), _PREG(10), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(19), _PREG(12), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vCost", 20);
   #pragma VCC_VREG("vIndex", 21);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("allCostAddr", "A1");
   #pragma EVE_REG("indexAddr", "A0");
   #pragma EVE_REG("prevMinCostAddr", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("w", "I4");
   

   __vcop_vloop(__vcop_tablelkup(), 7u, 6u, 2u);
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(7), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(10), _AGEN(0), _VREG(21), __vcop_alws());
   __vcop_vtbload(__vcop_sizeHU(), __vcop_tableinfo(1, 1), _PREG(12), _AGEN(1), _VREG(21), _VREG(20), _PREG(6), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(20), _PREG(8), _AGEN(2), _PREG(0));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vCost", 22);
   #pragma VCC_VREG("vIndex", 23);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("allCostAddr", "A1");
   #pragma EVE_REG("indexAddr", "A0");
   #pragma EVE_REG("nextMinCostAddr", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("w", "I4");
   

   __vcop_vloop(__vcop_tablelkup(), 7u, 6u, 3u);
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(7), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(10), _AGEN(0), _VREG(23), __vcop_alws());
   __vcop_vtbload(__vcop_sizeHU(), __vcop_tableinfo(1, 1), _PREG(12), _AGEN(1), _VREG(23), _VREG(22), _PREG(6), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(22), _PREG(8), _AGEN(2), _PREG(0));
   __vcop_vloop_end(3u);

}

void vcop_disparity_genPrevAndNextMinCost(
   __vptr_uint8 disparity,
   __vptr_uint16 allCost,
   __vptr_uint16 prevMinCostOutput,
   __vptr_uint16 nextMinCostOutput,
   __vptr_uint16 scratchIndex,
   unsigned short width,
   unsigned short allCostStride,
   unsigned char numDisparities,
   unsigned char disparityStep,
   unsigned char disparityStepShift)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_disparity_genPrevAndNextMinCost_init(disparity, allCost, prevMinCostOutput, nextMinCostOutput, scratchIndex, width, allCostStride, numDisparities, disparityStep, disparityStepShift, __pblock_vcop_disparity_genPrevAndNextMinCost);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_disparity_genPrevAndNextMinCost_vloops(__pblock_vcop_disparity_genPrevAndNextMinCost);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_disparity_genPrevAndNextMinCost_custom(
   __vptr_uint8 disparity,
   __vptr_uint16 allCost,
   __vptr_uint16 prevMinCostOutput,
   __vptr_uint16 nextMinCostOutput,
   __vptr_uint16 scratchIndex,
   unsigned short width,
   unsigned short allCostStride,
   unsigned char numDisparities,
   unsigned char disparityStep,
   unsigned char disparityStepShift,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_disparity_genPrevAndNextMinCost_init(disparity, allCost, prevMinCostOutput, nextMinCostOutput, scratchIndex, width, allCostStride, numDisparities, disparityStep, disparityStepShift, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_disparity_genPrevAndNextMinCost_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_disparity_hammingDistance_row_right_left_firstCall, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_disparity_hammingDistance_row_right_left_firstCall, __ALIGNOF__(int));
unsigned short __pblock_vcop_disparity_hammingDistance_row_right_left_firstCall[44];

unsigned int vcop_disparity_hammingDistance_row_right_left_firstCall_param_count(void)
{
   return 44u;
}

unsigned int vcop_disparity_hammingDistance_row_right_left_firstCall_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_disparity_hammingDistance_row_right_left_firstCall_init(
   __vptr_uint16 allCostOutput,
   __vptr_uint8 rlDisparityOutput,
   __vptr_uint16 rlMinCostOutput,
   __vptr_uint8 prevRlDisparityOutput,
   __vptr_uint16 prevRlMinCostOutput,
   __vptr_uint16 rlAllCostOutput,
   __vptr_uint8 rlDisparityScratch,
   __vptr_uint16 rlMinCostScratch,
   unsigned short allCostStride,
   unsigned short rlAllCostStride,
   unsigned short width,
   unsigned char numDisparities,
   unsigned char disparityStep,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((numDisparities/disparityStep)/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((width) + (8u)-1) & ~((8u)-1))/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)rlAllCostOutput+(numDisparities-1)*sizeof(*rlAllCostOutput));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)rlAllCostOutput+(numDisparities-1)*sizeof(*rlAllCostOutput)+(rlAllCostStride-disparityStep*sizeof(*rlAllCostOutput)));
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), (2*-allCostStride) -(8u*sizeof(*allCostOutput))*(((((width) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(12),  -(8u*sizeof(*rlMinCostOutput))*(((((width) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(13), (2*(rlAllCostStride-disparityStep*sizeof(*rlAllCostOutput))) -(8u*sizeof(*allCostOutput))*(((((width) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)allCostOutput+(numDisparities/disparityStep-1)*allCostStride);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)allCostOutput+(numDisparities/disparityStep-2)*allCostStride);
   __offset += 16;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((((width + numDisparities - 1) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((numDisparities/disparityStep))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (numDisparities));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)rlAllCostOutput+(numDisparities/disparityStep-1)*rlAllCostStride);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)rlAllCostOutput+(numDisparities/disparityStep-1)*rlAllCostStride+8u*sizeof(*rlAllCostOutput));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)rlMinCostOutput);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)rlMinCostOutput+8u*sizeof(*rlMinCostOutput));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)rlDisparityOutput);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)rlDisparityOutput+8u*sizeof(*rlDisparityOutput));
   __vcop_pblock_init16(pblock, __offset+_PREG(22), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(23), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(24), (-rlAllCostStride));
   __vcop_pblock_init16(pblock, __offset+_PREG(25), ((2*8u)*sizeof(*rlAllCostOutput)) -(-rlAllCostStride)*(((numDisparities/disparityStep))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (-disparityStep));
   __vcop_pblock_init32(pblock, __offset+_PREG(28), 4294967295);
   __offset += 28;

   return 44u;
}

void vcop_disparity_hammingDistance_row_right_left_firstCall_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("vDisparityStep", 16);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vCost0", 17);
   #pragma VCC_VREG("vCost1", 18);
   #pragma VCC_VREG("vFlag", 19);
   #pragma VCC_VREG("vIdx", 20);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("allCostAddr", "A0");
   #pragma EVE_REG("minCostAddr", "A1");
   #pragma EVE_REG("rlAllCostAddr", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("d", "I3");
   #pragma EVE_REG("i", "I4");
   

   __vcop_vloop(__vcop_compute(), 8u, 8u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(10), _PREG(11), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(10), _PREG(13), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(14), _AGEN(0), _VREG(17), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(16), _AGEN(0), _VREG(18), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(17), _PREG(6), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(18), _PREG(8), _AGEN(2), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vDisp0", 21);
   #pragma VCC_VREG("vDisp1", 22);
   #pragma VCC_VREG("vIdx", 23);
   #pragma VCC_VREG("vMin0", 24);
   #pragma VCC_VREG("vMin1", 25);
   #pragma VCC_VREG("vCost0", 26);
   #pragma VCC_VREG("vCost1", 27);
   #pragma VCC_VREG("vMinFlag0", 28);
   #pragma VCC_VREG("vMinFlag1", 29);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("agenDisp", "A0");
   #pragma EVE_REG("agenMinCost", "A1");
   #pragma EVE_REG("agenCost", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("c", "I3");
   #pragma EVE_REG("d", "I4");
   

   __vcop_vloop(__vcop_compute(), 21u, 14u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(26), _VREG(16));
   __vcop_vinit(__vcop_sizeWU(), __vcop_i4_zero(), _PREG(28), _VREG(24));
   __vcop_vinit(__vcop_sizeWU(), __vcop_i4_zero(), _PREG(28), _VREG(25));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(6), _VREG(21));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(6), _VREG(22));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(8), _VREG(23));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(22), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(23), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(24), _PREG(25), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(10), _AGEN(2), _VREG(26), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(12), _AGEN(2), _VREG(27), __vcop_alws());
   __vcop_vadd(_VREG(23), _VREG(16), _VREG(23));
   __vcop_vminsetf(_VREG(26), _VREG(24), _VREG(28));
   __vcop_vminsetf(_VREG(27), _VREG(25), _VREG(29));
   __vcop_vsel(_VREG(28), _VREG(23), _VREG(21));
   __vcop_vsel(_VREG(29), _VREG(23), _VREG(22));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_last_i4(), _VREG(24), _PREG(14), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_last_i4(), _VREG(25), _PREG(16), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_last_i4(), _VREG(21), _PREG(18), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_last_i4(), _VREG(22), _PREG(20), _AGEN(0), _PREG(0));
   __vcop_vloop_end(2u);

}

void vcop_disparity_hammingDistance_row_right_left_firstCall(
   __vptr_uint16 allCostOutput,
   __vptr_uint8 rlDisparityOutput,
   __vptr_uint16 rlMinCostOutput,
   __vptr_uint8 prevRlDisparityOutput,
   __vptr_uint16 prevRlMinCostOutput,
   __vptr_uint16 rlAllCostOutput,
   __vptr_uint8 rlDisparityScratch,
   __vptr_uint16 rlMinCostScratch,
   unsigned short allCostStride,
   unsigned short rlAllCostStride,
   unsigned short width,
   unsigned char numDisparities,
   unsigned char disparityStep)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_disparity_hammingDistance_row_right_left_firstCall_init(allCostOutput, rlDisparityOutput, rlMinCostOutput, prevRlDisparityOutput, prevRlMinCostOutput, rlAllCostOutput, rlDisparityScratch, rlMinCostScratch, allCostStride, rlAllCostStride, width, numDisparities, disparityStep, __pblock_vcop_disparity_hammingDistance_row_right_left_firstCall);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_disparity_hammingDistance_row_right_left_firstCall_vloops(__pblock_vcop_disparity_hammingDistance_row_right_left_firstCall);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_disparity_hammingDistance_row_right_left_firstCall_custom(
   __vptr_uint16 allCostOutput,
   __vptr_uint8 rlDisparityOutput,
   __vptr_uint16 rlMinCostOutput,
   __vptr_uint8 prevRlDisparityOutput,
   __vptr_uint16 prevRlMinCostOutput,
   __vptr_uint16 rlAllCostOutput,
   __vptr_uint8 rlDisparityScratch,
   __vptr_uint16 rlMinCostScratch,
   unsigned short allCostStride,
   unsigned short rlAllCostStride,
   unsigned short width,
   unsigned char numDisparities,
   unsigned char disparityStep,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_disparity_hammingDistance_row_right_left_firstCall_init(allCostOutput, rlDisparityOutput, rlMinCostOutput, prevRlDisparityOutput, prevRlMinCostOutput, rlAllCostOutput, rlDisparityScratch, rlMinCostScratch, allCostStride, rlAllCostStride, width, numDisparities, disparityStep, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_disparity_hammingDistance_row_right_left_firstCall_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_disparity_hammingDistance_row_right_left, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_disparity_hammingDistance_row_right_left, __ALIGNOF__(int));
unsigned short __pblock_vcop_disparity_hammingDistance_row_right_left[86];

unsigned int vcop_disparity_hammingDistance_row_right_left_param_count(void)
{
   return 86u;
}

unsigned int vcop_disparity_hammingDistance_row_right_left_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_disparity_hammingDistance_row_right_left_init(
   __vptr_uint16 allCostOutput,
   __vptr_uint8 rlDisparityOutput,
   __vptr_uint16 rlMinCostOutput,
   __vptr_uint8 prevRlDisparityOutput,
   __vptr_uint16 prevRlMinCostOutput,
   __vptr_uint16 rlAllCostOutput,
   __vptr_uint8 rlDisparityScratch,
   __vptr_uint16 rlMinCostScratch,
   unsigned short allCostStride,
   unsigned short rlAllCostStride,
   unsigned short width,
   unsigned char numDisparities,
   unsigned char disparityStep,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((numDisparities - 1) + (8u)-1) & ~((8u)-1))/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)rlMinCostOutput);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)rlDisparityOutput);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), 16);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)prevRlMinCostOutput+width*sizeof(*prevRlMinCostOutput));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)prevRlDisparityOutput+width*sizeof(*prevRlDisparityOutput));
   __offset += 14;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((numDisparities/disparityStep)/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((width) + (8u)-1) & ~((8u)-1))/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)allCostOutput+(numDisparities/disparityStep-1)*allCostStride);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)allCostOutput+(numDisparities/disparityStep-2)*allCostStride);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)rlAllCostOutput+(numDisparities-1)*sizeof(*rlAllCostOutput));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)rlAllCostOutput+(numDisparities-1)*sizeof(*rlAllCostOutput)+(rlAllCostStride-disparityStep*sizeof(*rlAllCostOutput)));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)rlMinCostOutput+(numDisparities-1)*sizeof(*rlMinCostOutput));
   __vcop_pblock_init16(pblock, __offset+_PREG(16), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(17), (2*-allCostStride) -(8u*sizeof(*allCostOutput))*(((((width) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(18),  -(8u*sizeof(*rlMinCostOutput))*(((((width) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(19), (2*(rlAllCostStride-disparityStep*sizeof(*rlAllCostOutput))) -(8u*sizeof(*allCostOutput))*(((((width) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), 65535);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), 0);
   __offset += 22;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((((width + numDisparities - 1) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((numDisparities/disparityStep))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (numDisparities));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)rlAllCostOutput+(numDisparities/disparityStep-1)*rlAllCostStride);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)rlAllCostOutput+(numDisparities/disparityStep-1)*rlAllCostStride+8u*sizeof(*rlAllCostOutput));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)rlMinCostScratch);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)rlMinCostScratch+8u*sizeof(*rlMinCostScratch));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)rlDisparityScratch);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)rlDisparityScratch+8u*sizeof(*rlDisparityScratch));
   __vcop_pblock_init16(pblock, __offset+_PREG(22), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(23), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(24), (-rlAllCostStride));
   __vcop_pblock_init16(pblock, __offset+_PREG(25), ((2*8u)*sizeof(*rlAllCostOutput)) -(-rlAllCostStride)*(((numDisparities/disparityStep))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (-disparityStep));
   __vcop_pblock_init32(pblock, __offset+_PREG(28), 4294967295);
   __offset += 28;

   /* Loop 4 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((width + numDisparities - 1) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)rlDisparityScratch);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)rlDisparityScratch+8u*sizeof(*rlDisparityScratch));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)rlMinCostOutput);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)rlMinCostOutput+8u*sizeof(*rlMinCostOutput));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)rlMinCostScratch);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)rlMinCostScratch+8u*sizeof(*rlMinCostScratch));
   __vcop_pblock_init16(pblock, __offset+_PREG(18), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(19), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)rlDisparityOutput);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)rlDisparityOutput+8u*sizeof(*rlDisparityOutput));
   __offset += 22;

   return 86u;
}

void vcop_disparity_hammingDistance_row_right_left_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("vDisparityStep", 16);
   #pragma VCC_VREG("vMinCost", 17);
   #pragma VCC_VREG("vZero", 18);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vDisp", 19);
   #pragma VCC_VREG("vMinCost", 20);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("dispAddr", "A0");
   #pragma EVE_REG("minCostAddr", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("c", "I4");
   

   __vcop_vloop(__vcop_compute(), 7u, 7u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(10), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(11), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(12), _AGEN(1), _VREG(20), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(14), _AGEN(0), _VREG(19), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(20), _PREG(6), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(19), _PREG(8), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vCost0", 21);
   #pragma VCC_VREG("vCost1", 22);
   #pragma VCC_VREG("vFlag", 23);
   #pragma VCC_VREG("vIdx", 24);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("allCostAddr", "A0");
   #pragma EVE_REG("minCostAddr", "A1");
   #pragma EVE_REG("rlAllCostAddr", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("d", "I3");
   #pragma EVE_REG("i", "I4");
   

   __vcop_vloop(__vcop_compute(), 13u, 11u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(20), _VREG(17));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(22), _VREG(18));
   __vcop_vinit(__vcop_sizeHU(), __vcop_alws(), _PREG(67), _VREG(24));
   __vcop_vagen(_AGEN(0), _PREG(16), _PREG(17), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(16), _PREG(18), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(16), _PREG(19), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(6), _AGEN(0), _VREG(21), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(8), _AGEN(0), _VREG(22), __vcop_alws());
   __vcop_vcmpeq(_VREG(24), _VREG(18), _VREG(23));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(21), _PREG(10), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(22), _PREG(12), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_predicate(_VREG(23)), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(17), _PREG(14), _AGEN(1), _PREG(0));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vDisp0", 25);
   #pragma VCC_VREG("vDisp1", 26);
   #pragma VCC_VREG("vIdx", 27);
   #pragma VCC_VREG("vMin0", 28);
   #pragma VCC_VREG("vMin1", 29);
   #pragma VCC_VREG("vCost0", 30);
   #pragma VCC_VREG("vCost1", 31);
   #pragma VCC_VREG("vMinFlag0", 32);
   #pragma VCC_VREG("vMinFlag1", 33);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("agenDisp", "A0");
   #pragma EVE_REG("agenMinCost", "A1");
   #pragma EVE_REG("agenCost", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("c", "I3");
   #pragma EVE_REG("d", "I4");
   

   __vcop_vloop(__vcop_compute(), 21u, 14u, 3u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(26), _VREG(16));
   __vcop_vinit(__vcop_sizeWU(), __vcop_i4_zero(), _PREG(28), _VREG(28));
   __vcop_vinit(__vcop_sizeWU(), __vcop_i4_zero(), _PREG(28), _VREG(29));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(6), _VREG(25));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(6), _VREG(26));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(8), _VREG(27));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(22), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(23), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(24), _PREG(25), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(10), _AGEN(2), _VREG(30), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(12), _AGEN(2), _VREG(31), __vcop_alws());
   __vcop_vadd(_VREG(27), _VREG(16), _VREG(27));
   __vcop_vminsetf(_VREG(30), _VREG(28), _VREG(32));
   __vcop_vminsetf(_VREG(31), _VREG(29), _VREG(33));
   __vcop_vsel(_VREG(32), _VREG(27), _VREG(25));
   __vcop_vsel(_VREG(33), _VREG(27), _VREG(26));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_last_i4(), _VREG(28), _PREG(14), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_last_i4(), _VREG(29), _PREG(16), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_last_i4(), _VREG(25), _PREG(18), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_last_i4(), _VREG(26), _PREG(20), _AGEN(0), _PREG(0));
   __vcop_vloop_end(3u);

   /* VLOOP 4 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vDisp0", 34);
   #pragma VCC_VREG("vDisp0Prev", 35);
   #pragma VCC_VREG("vDisp1", 36);
   #pragma VCC_VREG("vDisp1Prev", 37);
   #pragma VCC_VREG("vMin0", 38);
   #pragma VCC_VREG("vMin0Prev", 39);
   #pragma VCC_VREG("vMin1", 40);
   #pragma VCC_VREG("vMin1Prev", 41);
   #pragma VCC_VREG("vMinFlag0", 42);
   #pragma VCC_VREG("vMinFlag1", 43);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("agenDisp", "A0");
   #pragma EVE_REG("agenMinCost", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("c", "I4");
   

   __vcop_vloop(__vcop_compute(), 19u, 11u, 4u);
   __vcop_vagen(_AGEN(0), _PREG(18), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(19), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(20), _AGEN(0), _VREG(35), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(22), _AGEN(0), _VREG(37), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(6), _AGEN(0), _VREG(34), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(8), _AGEN(0), _VREG(36), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(10), _AGEN(1), _VREG(39), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(12), _AGEN(1), _VREG(41), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(14), _AGEN(1), _VREG(38), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(16), _AGEN(1), _VREG(40), __vcop_alws());
   __vcop_vminsetf(_VREG(39), _VREG(38), _VREG(42));
   __vcop_vminsetf(_VREG(41), _VREG(40), _VREG(43));
   __vcop_vsel(_VREG(42), _VREG(35), _VREG(34));
   __vcop_vsel(_VREG(43), _VREG(37), _VREG(36));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(38), _PREG(10), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(40), _PREG(12), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(34), _PREG(20), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(36), _PREG(22), _AGEN(0), _PREG(0));
   __vcop_vloop_end(4u);

}

void vcop_disparity_hammingDistance_row_right_left(
   __vptr_uint16 allCostOutput,
   __vptr_uint8 rlDisparityOutput,
   __vptr_uint16 rlMinCostOutput,
   __vptr_uint8 prevRlDisparityOutput,
   __vptr_uint16 prevRlMinCostOutput,
   __vptr_uint16 rlAllCostOutput,
   __vptr_uint8 rlDisparityScratch,
   __vptr_uint16 rlMinCostScratch,
   unsigned short allCostStride,
   unsigned short rlAllCostStride,
   unsigned short width,
   unsigned char numDisparities,
   unsigned char disparityStep)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_disparity_hammingDistance_row_right_left_init(allCostOutput, rlDisparityOutput, rlMinCostOutput, prevRlDisparityOutput, prevRlMinCostOutput, rlAllCostOutput, rlDisparityScratch, rlMinCostScratch, allCostStride, rlAllCostStride, width, numDisparities, disparityStep, __pblock_vcop_disparity_hammingDistance_row_right_left);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_disparity_hammingDistance_row_right_left_vloops(__pblock_vcop_disparity_hammingDistance_row_right_left);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_disparity_hammingDistance_row_right_left_custom(
   __vptr_uint16 allCostOutput,
   __vptr_uint8 rlDisparityOutput,
   __vptr_uint16 rlMinCostOutput,
   __vptr_uint8 prevRlDisparityOutput,
   __vptr_uint16 prevRlMinCostOutput,
   __vptr_uint16 rlAllCostOutput,
   __vptr_uint8 rlDisparityScratch,
   __vptr_uint16 rlMinCostScratch,
   unsigned short allCostStride,
   unsigned short rlAllCostStride,
   unsigned short width,
   unsigned char numDisparities,
   unsigned char disparityStep,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_disparity_hammingDistance_row_right_left_init(allCostOutput, rlDisparityOutput, rlMinCostOutput, prevRlDisparityOutput, prevRlMinCostOutput, rlAllCostOutput, rlDisparityScratch, rlMinCostScratch, allCostStride, rlAllCostStride, width, numDisparities, disparityStep, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_disparity_hammingDistance_row_right_left_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

