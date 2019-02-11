#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_hough_for_lines, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_hough_for_lines, __ALIGNOF__(int));
unsigned short __pblock_vcop_hough_for_lines[46];

unsigned int vcop_hough_for_lines_param_count(void)
{
   return 46u;
}

unsigned int vcop_hough_for_lines_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_hough_for_lines_init(
   __vptr_uint16 pEdgeMapList,
   __vptr_int16 pCosSinThetaMulNormQ15,
   __vptr_uint16 intermIndexArray,
   __vptr_uint16 votedRhoArray8Copy,
   unsigned short listSize,
   unsigned short rhoMaxLength,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((listSize) / (2 * (8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_ROUND,15));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 64);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pCosSinThetaMulNormQ15+2);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pEdgeMapList);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pEdgeMapList+32);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)intermIndexArray);
   __vcop_pblock_init16(pblock, __offset+_PREG(16), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), ((rhoMaxLength << 15) / 2));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pCosSinThetaMulNormQ15);
   __offset += 20;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((((rhoMaxLength) + 2*(8u)-1) & ~(2*(8u)-1)) * 8)/(2 * (8u)) ))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)votedRhoArray8Copy);
   __offset += 10;

   /* Loop 3 PREGS */
   const int preg_ref1 = _PREG(10);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (listSize / ((8)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_4PARAM,preg_ref1,RM_NONE,0));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 16);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)votedRhoArray8Copy);
   __vcop_pblock_4param_init(pblock, __offset+_PREG(10), (rhoMaxLength - 1), (rhoMaxLength - 1), 0, 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), 1);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)intermIndexArray);
   __offset += 16;

   return 46u;
}

void vcop_hough_for_lines_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("vCosLutQ8", 16);
   #pragma VCC_VREG("vCosMulNormQ15", 17);
   #pragma VCC_VREG("vEdge_x1", 18);
   #pragma VCC_VREG("vEdge_x2", 19);
   #pragma VCC_VREG("vEdge_y1", 20);
   #pragma VCC_VREG("vEdge_y2", 21);
   #pragma VCC_VREG("vNormMulDiamQ15", 22);
   #pragma VCC_VREG("vSinLutQ8", 23);
   #pragma VCC_VREG("vSinMulNormQ15", 24);
   #pragma VCC_VREG("vTempX_1", 25);
   #pragma VCC_VREG("vTempX_2", 26);
   #pragma VCC_VREG("vTempY_1", 27);
   #pragma VCC_VREG("vTempY_2", 28);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("thetaAddr", "A0");
   #pragma EVE_REG("edgeMapAddr", "A1");
   #pragma EVE_REG("outIndexAddr", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("listCount", "I4");
   

   __vcop_vloop(__vcop_compute(), 16u, 10u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(18), _VREG(22));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(16), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_1pt(), _PREG(20), _AGEN(0), _VREG(17), __vcop_once());
   __vcop_vload(__vcop_sizeH(), __vcop_1pt(), _PREG(8), _AGEN(0), _VREG(24), __vcop_once());
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(10), _AGEN(1), _VPAIR(18,20), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(12), _AGEN(1), _VPAIR(19,21), __vcop_alws());
   __vcop_vmpy(_VREG(17), _VREG(18), _VREG(25), _PREG(0));
   __vcop_vmpy(_VREG(17), _VREG(19), _VREG(26), _PREG(0));
   __vcop_vmpy(_VREG(24), _VREG(20), _VREG(27), _PREG(0));
   __vcop_vmpy(_VREG(24), _VREG(21), _VREG(28), _PREG(0));
   __vcop_vadd3(_VREG(22), _VREG(27), _VREG(25));
   __vcop_vadd3(_VREG(22), _VREG(28), _VREG(26));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(25,26), _PREG(14), _AGEN(2), _PREG(6));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vZero1", 29);
   #pragma VCC_VREG("vZero2", 30);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("thetaAddr", "A0");
   #pragma EVE_REG("addGen", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("rhoCount", "I4");
   

   __vcop_vloop(__vcop_compute(), 6u, 5u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(8), _VREG(29));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(8), _VREG(30));
   __vcop_vagen(_AGEN(1), _PREG(6), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(29,30), _PREG(10), _AGEN(1), _PREG(0));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vData", 31);
   #pragma VCC_VREG("vIndex", 32);
   #pragma VCC_VREG("vWeight", 33);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("histAgen", "A1");
   #pragma EVE_REG("indexAddr", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("listCount", "I4");
   

   __vcop_vloop(__vcop_histogram(), 8u, 8u, 3u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(14), _VREG(33));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(16), _AGEN(0), _VREG(32), __vcop_alws());
   __vcop_vhistload(__vcop_sizeHU(), 8, _PREG(8), _AGEN(1), _VREG(32), _VREG(31), _PREG(6), __vcop_alws());
   __vcop_hist_vadd(_VREG(31), _VREG(33), _VREG(31));
   __vcop_vhiststore(__vcop_sizeHU(), 8, __vcop_alws(), _VREG(31), _PREG(8), _AGEN(1), _VREG(32));
   __vcop_vloop_end(3u);

}

void vcop_hough_for_lines(
   __vptr_uint16 pEdgeMapList,
   __vptr_int16 pCosSinThetaMulNormQ15,
   __vptr_uint16 intermIndexArray,
   __vptr_uint16 votedRhoArray8Copy,
   unsigned short listSize,
   unsigned short rhoMaxLength)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_hough_for_lines_init(pEdgeMapList, pCosSinThetaMulNormQ15, intermIndexArray, votedRhoArray8Copy, listSize, rhoMaxLength, __pblock_vcop_hough_for_lines);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_hough_for_lines_vloops(__pblock_vcop_hough_for_lines);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_hough_for_lines_custom(
   __vptr_uint16 pEdgeMapList,
   __vptr_int16 pCosSinThetaMulNormQ15,
   __vptr_uint16 intermIndexArray,
   __vptr_uint16 votedRhoArray8Copy,
   unsigned short listSize,
   unsigned short rhoMaxLength,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_hough_for_lines_init(pEdgeMapList, pCosSinThetaMulNormQ15, intermIndexArray, votedRhoArray8Copy, listSize, rhoMaxLength, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_hough_for_lines_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_merge_voted_rho_array, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_merge_voted_rho_array, __ALIGNOF__(int));
unsigned short __pblock_vcop_merge_voted_rho_array[28];

unsigned int vcop_merge_voted_rho_array_param_count(void)
{
   return 28u;
}

unsigned int vcop_merge_voted_rho_array_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_merge_voted_rho_array_init(
   __vptr_uint16 votedRhoArray8Copy,
   __vptr_uint16 votedRhoArray,
   __vptr_uint16 interimTransposeBuf1,
   __vptr_uint16 interimTransposeBuf2,
   __vptr_uint16 offsetArray,
   unsigned short rhoMaxLength,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (( (((rhoMaxLength) + 2*(8u)-1) & ~(2*(8u)-1))/ 2 ))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)interimTransposeBuf1);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)interimTransposeBuf2);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), 2);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)offsetArray);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)votedRhoArray8Copy);
   __offset += 14;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (( (((rhoMaxLength) + 2*(8u)-1) & ~(2*(8u)-1))/ (2 * (8u))))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)interimTransposeBuf2);
   __vcop_pblock_init16(pblock, __offset+_PREG(8), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(9), ((((rhoMaxLength+2*8u-1&~(2*8u-1))/4+1)*4)));
   __vcop_pblock_init16(pblock, __offset+_PREG(10), (2*8u) -((((rhoMaxLength+2*8u-1&~(2*8u-1))/4+1)*4))*(((8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)votedRhoArray);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)interimTransposeBuf1);
   __offset += 14;

   return 28u;
}

void vcop_merge_voted_rho_array_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("vData1", 16);
   #pragma VCC_VREG("vData2", 17);
   #pragma VCC_VREG("vOffset", 18);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("offsetAddr", "A0");
   #pragma EVE_REG("inAddr", "A1");
   #pragma EVE_REG("outAddr1", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("rhoCount", "I4");
   

   __vcop_vloop(__vcop_compute(), 8u, 7u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(10), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(11), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(12), _AGEN(0), _VREG(18), __vcop_once());
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(14), _AGEN(1), _VPAIR(16,17), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_pdda(_VREG(18)), __vcop_alws(), _VREG(16), _PREG(6), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_pdda(_VREG(18)), __vcop_alws(), _VREG(17), _PREG(8), _AGEN(2), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vSum1", 19);
   #pragma VCC_VREG("vSum2", 20);
   #pragma VCC_VREG("inData1", 21);
   #pragma VCC_VREG("inData2", 22);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("offsetAddr", "A0");
   #pragma EVE_REG("addrIn", "A1");
   #pragma EVE_REG("inAddr", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("rhoCount", "I3");
   #pragma EVE_REG("i", "I4");
   

   __vcop_vloop(__vcop_compute(), 10u, 7u, 2u);
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(8), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(9), _PREG(10), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(12), _AGEN(1), _VPAIR(19,20), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(14), _AGEN(2), _VREG(21), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(6), _AGEN(2), _VREG(22), __vcop_alws());
   __vcop_vadd(_VREG(19), _VREG(21), _VREG(19));
   __vcop_vadd(_VREG(20), _VREG(22), _VREG(20));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_intrlv(), __vcop_last_i4(), _VPAIR(19,20), _PREG(12), _AGEN(1), _PREG(0));
   __vcop_vloop_end(2u);

}

void vcop_merge_voted_rho_array(
   __vptr_uint16 votedRhoArray8Copy,
   __vptr_uint16 votedRhoArray,
   __vptr_uint16 interimTransposeBuf1,
   __vptr_uint16 interimTransposeBuf2,
   __vptr_uint16 offsetArray,
   unsigned short rhoMaxLength)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_merge_voted_rho_array_init(votedRhoArray8Copy, votedRhoArray, interimTransposeBuf1, interimTransposeBuf2, offsetArray, rhoMaxLength, __pblock_vcop_merge_voted_rho_array);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_merge_voted_rho_array_vloops(__pblock_vcop_merge_voted_rho_array);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_merge_voted_rho_array_custom(
   __vptr_uint16 votedRhoArray8Copy,
   __vptr_uint16 votedRhoArray,
   __vptr_uint16 interimTransposeBuf1,
   __vptr_uint16 interimTransposeBuf2,
   __vptr_uint16 offsetArray,
   unsigned short rhoMaxLength,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_merge_voted_rho_array_init(votedRhoArray8Copy, votedRhoArray, interimTransposeBuf1, interimTransposeBuf2, offsetArray, rhoMaxLength, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_merge_voted_rho_array_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

