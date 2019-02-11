#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_disparity_hammingDistance64_first_row_firstCall, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_disparity_hammingDistance64_first_row_firstCall, __ALIGNOF__(int));
unsigned short __pblock_vcop_disparity_hammingDistance64_first_row_firstCall[106];

unsigned int vcop_disparity_hammingDistance64_first_row_firstCall_param_count(void)
{
   return 106u;
}

unsigned int vcop_disparity_hammingDistance64_first_row_firstCall_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_disparity_hammingDistance64_first_row_firstCall_init(
   __vptr_uint32 pLeft,
   __vptr_uint32 pRight,
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
   __vptr_int16 pCarryOverOut,
   unsigned short scratchStride,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), ((numDisparities/disparityStep))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (winHeight)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (winWidth)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pLeft);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pLeft+8u*4);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pRight+(disparityStep-1)*2*4);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pRight+(disparityStep-1)*2*4+8u*4);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pAllCostOutput);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pCarryOverOut);
   __vcop_pblock_init16(pblock, __offset+_PREG(20), (allCostOutputStride));
   __vcop_pblock_init16(pblock, __offset+_PREG(21), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(22), (leftStride) -(4*2)*((winWidth)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(23),  -(leftStride)*((winHeight)-1u) -(4*2)*((winWidth)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(24), (rightStride) -(4*2)*((winWidth)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(25), (disparityStep*4*2) -(rightStride)*((winHeight)-1u) -(4*2)*((winWidth)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)pOffset);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)pCollateMask);
   __offset += 28;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), ((numDisparities/disparityStep))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((((width-(8u)) + (8u)-1) & ~((8u)-1))/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (winHeight)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pLeft+2*(8u*4+(winWidth-1)*4)+8u*4);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pRight+(disparityStep-1)*2*4+2*(8u*4+(winWidth-1)*4));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pRight+(disparityStep-1)*2*4+2*(8u*4+(winWidth-1)*4)+8u*4);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pLeft+2*(8u*4-4));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pLeft+2*(8u*4-4)+8u*4);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pRight+(disparityStep-1)*2*4+2*(8u*4-4));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pRight+(disparityStep-1)*2*4+2*(8u*4-4)+8u*4);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pScratch0);
   __vcop_pblock_init16(pblock, __offset+_PREG(22), (8u*scratchStride));
   __vcop_pblock_init16(pblock, __offset+_PREG(23), (sizeof(*pAllCostOutput)) -(8u*scratchStride)*(((((width-(8u)) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(24), (leftStride));
   __vcop_pblock_init16(pblock, __offset+_PREG(25), (8u*2*4) -(leftStride)*((winHeight)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(26),  -(8u*2*4)*(((((width-(8u)) + (8u)-1) & ~((8u)-1))/(8u))-1u) -(leftStride)*((winHeight)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(27), (rightStride));
   __vcop_pblock_init16(pblock, __offset+_PREG(28), (8u*2*4) -(rightStride)*((winHeight)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(29), (disparityStep*2*4) -(8u*2*4)*(((((width-(8u)) + (8u)-1) & ~((8u)-1))/(8u))-1u) -(rightStride)*((winHeight)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(30), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(32), (uchar *)pLeft+2*(8u*4+(winWidth-1)*4));
   __offset += 32;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((((numDisparities/disparityStep) + (8u)-1) & ~((8u)-1))/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((width-(8u)))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pScratch0);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pAllCostOutput+8u*sizeof(*pAllCostOutput));
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), (scratchStride));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), (8u*sizeof(*pScratch0)) -(scratchStride)*(((width-(8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(13), 2);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), (8u*allCostOutputStride) -(sizeof(*pAllCostOutput))*(((width-(8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pOffset+16);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pCarryOverOut);
   __offset += 18;

   /* Loop 4 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((((width) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((numDisparities/disparityStep))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (numDisparities));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pAllCostOutput+0);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pAllCostOutput+0+8u*sizeof(*pAllCostOutput));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pMinCostOutput);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pMinCostOutput+8u*sizeof(*pMinCostOutput));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pDisparityOutput);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pDisparityOutput+8u*sizeof(*pDisparityOutput));
   __vcop_pblock_init16(pblock, __offset+_PREG(22), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(23), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(24), (allCostOutputStride));
   __vcop_pblock_init16(pblock, __offset+_PREG(25), ((2*8u)*sizeof(*pAllCostOutput)) -(allCostOutputStride)*(((numDisparities/disparityStep))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (-disparityStep));
   __vcop_pblock_init32(pblock, __offset+_PREG(28), 4294967295);
   __offset += 28;

   return 106u;
}

void vcop_disparity_hammingDistance64_first_row_firstCall_vloops(
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
   #pragma VCC_VREG("vLeft0", 20);
   #pragma VCC_VREG("vLeft1", 21);
   #pragma VCC_VREG("vRight0", 22);
   #pragma VCC_VREG("vRight1", 23);
   #pragma VCC_VREG("vXor0", 24);
   #pragma VCC_VREG("vXor1", 25);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("agen0", "A0");
   #pragma EVE_REG("agenOffset", "A1");
   #pragma EVE_REG("agenCost", "A2");
   #pragma EVE_REG("agenLeft", "A3");
   #pragma EVE_REG("agenRight", "A4");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("d", "I2");
   #pragma EVE_REG("h", "I3");
   #pragma EVE_REG("w", "I4");
   

   __vcop_vloop(__vcop_compute(), 22u, 14u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i34_zero(), _PREG(6), _VREG(19));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(0), _PREG(0), _PREG(20), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(21), _PREG(22), _PREG(23), _PREG(0));
   __vcop_vagen(_AGEN(4), _PREG(21), _PREG(24), _PREG(25), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(26), _AGEN(1), _VREG(0), __vcop_once());
   __vcop_vload(__vcop_sizeBU(), __vcop_nbits(), _PREG(28), _AGEN(0), _VREG(17), __vcop_once());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(8), _AGEN(3), _VREG(20), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(10), _AGEN(3), _VREG(21), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(12), _AGEN(4), _VREG(22), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(14), _AGEN(4), _VREG(23), __vcop_alws());
   __vcop_vxor(_VREG(20), _VREG(22), _VREG(24));
   __vcop_vxor(_VREG(21), _VREG(23), _VREG(25));
   __vcop_vbitc(_VREG(24), _VREG(24));
   __vcop_vbitc(_VREG(25), _VREG(25));
   __vcop_vdintrlv(_VREG(24), _VREG(25));
   __vcop_vadd3(_VREG(24), _VREG(25), _VREG(19));
   __vcop_vcmov(__vcop_last_i34(),_VREG(0),_VREG(18));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_last_i34(), _VREG(19), _PREG(16), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_predicate(_VREG(17)), __vcop_sizeH(), __vcop_collat(), __vcop_last_i34(), _VREG(19), _PREG(18), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   

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
   

   __vcop_vloop(__vcop_compute(), 30u, 16u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(30), _VREG(1));
   __vcop_vagen(_AGEN(2), _PREG(0), _PREG(22), _PREG(23), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(24), _PREG(25), _PREG(26), _PREG(0));
   __vcop_vagen(_AGEN(4), _PREG(27), _PREG(28), _PREG(29), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(32), _AGEN(3), _VREG(0), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(6), _AGEN(3), _VREG(2), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(8), _AGEN(4), _VREG(4), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(10), _AGEN(4), _VREG(6), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(12), _AGEN(3), _VREG(8), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(14), _AGEN(3), _VREG(10), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(16), _AGEN(4), _VREG(12), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(18), _AGEN(4), _VREG(14), __vcop_alws());
   __vcop_vxor(_VREG(0), _VREG(4), _VREG(0));
   __vcop_vxor(_VREG(2), _VREG(6), _VREG(2));
   __vcop_vbitc(_VREG(0), _VREG(0));
   __vcop_vbitc(_VREG(2), _VREG(2));
   __vcop_vxor(_VREG(8), _VREG(12), _VREG(8));
   __vcop_vxor(_VREG(10), _VREG(14), _VREG(10));
   __vcop_vbitc(_VREG(8), _VREG(8));
   __vcop_vbitc(_VREG(10), _VREG(10));
   __vcop_vdintrlv(_VREG(0), _VREG(2));
   __vcop_vdintrlv(_VREG(8), _VREG(10));
   __vcop_vadd3(_VREG(0), _VREG(2), _VREG(1));
   __vcop_vadd(_VREG(8), _VREG(10), _VREG(8));
   __vcop_vsub(_VREG(1), _VREG(8), _VREG(1));
   __vcop_vcmov(__vcop_last_i4(),_VREG(18),_VREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_pdda(_VREG(0)), __vcop_last_i4(), _VREG(1), _PREG(20), _AGEN(2), _PREG(0));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vAcc", 26);
   #pragma VCC_VREG("vPartial", 27);
   

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
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(16), _AGEN(1), _VREG(0), __vcop_once());
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(18), _AGEN(2), _VREG(26), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(6), _AGEN(3), _VREG(27), __vcop_alws());
   __vcop_vadd(_VREG(26), _VREG(27), _VREG(26));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_pdda(_VREG(0)), __vcop_alws(), _VREG(26), _PREG(8), _AGEN(4), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_npt(), __vcop_last_i4(), _VREG(26), _PREG(18), _AGEN(2), _PREG(0));
   __vcop_vloop_end(3u);

   /* VLOOP 4 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vDisp0", 28);
   #pragma VCC_VREG("vDisp1", 29);
   #pragma VCC_VREG("vIdx", 30);
   #pragma VCC_VREG("vMin0", 31);
   #pragma VCC_VREG("vMin1", 32);
   #pragma VCC_VREG("vCost0", 33);
   #pragma VCC_VREG("vCost1", 34);
   #pragma VCC_VREG("vMinFlag0", 35);
   #pragma VCC_VREG("vMinFlag1", 36);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("agen0", "A0");
   #pragma EVE_REG("agenOffset", "A1");
   #pragma EVE_REG("agenDisp", "A2");
   #pragma EVE_REG("agenMinCost", "A3");
   #pragma EVE_REG("agenCost", "A4");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("c", "I3");
   #pragma EVE_REG("d", "I4");
   

   __vcop_vloop(__vcop_compute(), 23u, 14u, 4u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(26), _VREG(16));
   __vcop_vinit(__vcop_sizeWU(), __vcop_i4_zero(), _PREG(28), _VREG(31));
   __vcop_vinit(__vcop_sizeWU(), __vcop_i4_zero(), _PREG(28), _VREG(32));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(6), _VREG(28));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(6), _VREG(29));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(8), _VREG(30));
   __vcop_vagen(_AGEN(2), _PREG(0), _PREG(22), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(0), _PREG(23), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(4), _PREG(24), _PREG(25), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(10), _AGEN(4), _VREG(33), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(12), _AGEN(4), _VREG(34), __vcop_alws());
   __vcop_vadd(_VREG(30), _VREG(16), _VREG(30));
   __vcop_vminsetf(_VREG(33), _VREG(31), _VREG(35));
   __vcop_vminsetf(_VREG(34), _VREG(32), _VREG(36));
   __vcop_vsel(_VREG(35), _VREG(30), _VREG(28));
   __vcop_vsel(_VREG(36), _VREG(30), _VREG(29));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_last_i4(), _VREG(31), _PREG(14), _AGEN(3), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_last_i4(), _VREG(32), _PREG(16), _AGEN(3), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_last_i4(), _VREG(28), _PREG(18), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_last_i4(), _VREG(29), _PREG(20), _AGEN(2), _PREG(0));
   __vcop_vloop_end(4u);

}

void vcop_disparity_hammingDistance64_first_row_firstCall(
   __vptr_uint32 pLeft,
   __vptr_uint32 pRight,
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
   __vptr_int16 pCarryOverOut,
   unsigned short scratchStride)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_disparity_hammingDistance64_first_row_firstCall_init(pLeft, pRight, leftStride, rightStride, winWidth, winHeight, pDisparityOutput, pMinCostOutput, pAllCostOutput, allCostOutputStride, width, numDisparities, disparityStep, pCollateMask, pOffset, pScratch0, pCarryOverOut, scratchStride, __pblock_vcop_disparity_hammingDistance64_first_row_firstCall);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_disparity_hammingDistance64_first_row_firstCall_vloops(__pblock_vcop_disparity_hammingDistance64_first_row_firstCall);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_disparity_hammingDistance64_first_row_firstCall_custom(
   __vptr_uint32 pLeft,
   __vptr_uint32 pRight,
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
   __vptr_int16 pCarryOverOut,
   unsigned short scratchStride,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_disparity_hammingDistance64_first_row_firstCall_init(pLeft, pRight, leftStride, rightStride, winWidth, winHeight, pDisparityOutput, pMinCostOutput, pAllCostOutput, allCostOutputStride, width, numDisparities, disparityStep, pCollateMask, pOffset, pScratch0, pCarryOverOut, scratchStride, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_disparity_hammingDistance64_first_row_firstCall_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_disparity_hammingDistance64_first_row, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_disparity_hammingDistance64_first_row, __ALIGNOF__(int));
unsigned short __pblock_vcop_disparity_hammingDistance64_first_row[88];

unsigned int vcop_disparity_hammingDistance64_first_row_param_count(void)
{
   return 88u;
}

unsigned int vcop_disparity_hammingDistance64_first_row_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_disparity_hammingDistance64_first_row_init(
   __vptr_uint32 pLeft,
   __vptr_uint32 pRight,
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
   __vptr_int16 pCarryOverIn,
   __vptr_int16 pCarryOverOut,
   unsigned short scratchStride,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (1)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pOffset);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pCollateMask);
   __offset += 8;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), ((numDisparities/disparityStep))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((((width) + (8u)-1) & ~((8u)-1))/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (winHeight)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pLeft+2*((winWidth-1)*4)+8u*4);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pRight+(disparityStep-1)*2*4+2*((winWidth-1)*4));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pRight+(disparityStep-1)*2*4+2*((winWidth-1)*4)+8u*4);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pLeft-4*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pLeft-4*2+8u*4);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pRight+(disparityStep-1)*2*4-4*2);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pRight+(disparityStep-1)*2*4-4*2+8u*4);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pScratch0);
   __vcop_pblock_init16(pblock, __offset+_PREG(22), (8u*scratchStride));
   __vcop_pblock_init16(pblock, __offset+_PREG(23), (sizeof(*pAllCostOutput)) -(8u*scratchStride)*(((((width) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(24), (leftStride));
   __vcop_pblock_init16(pblock, __offset+_PREG(25), (8u*2*4) -(leftStride)*((winHeight)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(26),  -(8u*2*4)*(((((width) + (8u)-1) & ~((8u)-1))/(8u))-1u) -(leftStride)*((winHeight)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(27), (rightStride));
   __vcop_pblock_init16(pblock, __offset+_PREG(28), (8u*2*4) -(rightStride)*((winHeight)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(29), (disparityStep*2*4) -(8u*2*4)*(((((width) + (8u)-1) & ~((8u)-1))/(8u))-1u) -(rightStride)*((winHeight)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(30), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(32), (uchar *)pLeft+2*((winWidth-1)*4));
   __offset += 32;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((((numDisparities/disparityStep) + (8u)-1) & ~((8u)-1))/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (width)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pScratch0);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pAllCostOutput);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pCarryOverOut);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(13), (scratchStride));
   __vcop_pblock_init16(pblock, __offset+_PREG(14), (8u*sizeof(*pScratch0)) -(scratchStride)*((width)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(15), 2);
   __vcop_pblock_init16(pblock, __offset+_PREG(16), (8u*allCostOutputStride) -(sizeof(*pAllCostOutput))*((width)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pOffset+16);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pCarryOverIn);
   __offset += 20;

   /* Loop 4 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((((width) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((numDisparities/disparityStep))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (numDisparities));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pAllCostOutput+0);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pAllCostOutput+0+8u*sizeof(*pAllCostOutput));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pMinCostOutput);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pMinCostOutput+8u*sizeof(*pMinCostOutput));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pDisparityOutput);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pDisparityOutput+8u*sizeof(*pDisparityOutput));
   __vcop_pblock_init16(pblock, __offset+_PREG(22), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(23), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(24), (allCostOutputStride));
   __vcop_pblock_init16(pblock, __offset+_PREG(25), ((2*8u)*sizeof(*pAllCostOutput)) -(allCostOutputStride)*(((numDisparities/disparityStep))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (-disparityStep));
   __vcop_pblock_init32(pblock, __offset+_PREG(28), 4294967295);
   __offset += 28;

   return 88u;
}

void vcop_disparity_hammingDistance64_first_row_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("vDisparityStep", 16);
   #pragma VCC_VREG("vMask", 17);
   #pragma VCC_VREG("vOfst", 18);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("agen0", "A0");
   #pragma EVE_REG("agenOffset", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("d", "I4");
   

   __vcop_vloop(__vcop_compute(), 6u, 4u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(6), _AGEN(1), _VREG(0), __vcop_once());
   __vcop_vload(__vcop_sizeBU(), __vcop_nbits(), _PREG(8), _AGEN(0), _VREG(17), __vcop_once());
   __vcop_vor(_VREG(0), _VREG(0), _VREG(18));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   

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
   

   __vcop_vloop(__vcop_compute(), 30u, 16u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(30), _VREG(1));
   __vcop_vagen(_AGEN(2), _PREG(0), _PREG(22), _PREG(23), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(24), _PREG(25), _PREG(26), _PREG(0));
   __vcop_vagen(_AGEN(4), _PREG(27), _PREG(28), _PREG(29), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(32), _AGEN(3), _VREG(0), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(6), _AGEN(3), _VREG(2), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(8), _AGEN(4), _VREG(4), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(10), _AGEN(4), _VREG(6), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(12), _AGEN(3), _VREG(8), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(14), _AGEN(3), _VREG(10), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(16), _AGEN(4), _VREG(12), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(18), _AGEN(4), _VREG(14), __vcop_alws());
   __vcop_vxor(_VREG(0), _VREG(4), _VREG(0));
   __vcop_vxor(_VREG(2), _VREG(6), _VREG(2));
   __vcop_vbitc(_VREG(0), _VREG(0));
   __vcop_vbitc(_VREG(2), _VREG(2));
   __vcop_vxor(_VREG(8), _VREG(12), _VREG(8));
   __vcop_vxor(_VREG(10), _VREG(14), _VREG(10));
   __vcop_vbitc(_VREG(8), _VREG(8));
   __vcop_vbitc(_VREG(10), _VREG(10));
   __vcop_vdintrlv(_VREG(0), _VREG(2));
   __vcop_vdintrlv(_VREG(8), _VREG(10));
   __vcop_vadd3(_VREG(0), _VREG(2), _VREG(1));
   __vcop_vadd(_VREG(8), _VREG(10), _VREG(8));
   __vcop_vsub(_VREG(1), _VREG(8), _VREG(1));
   __vcop_vcmov(__vcop_last_i4(),_VREG(18),_VREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_pdda(_VREG(0)), __vcop_last_i4(), _VREG(1), _PREG(20), _AGEN(2), _PREG(0));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vAcc", 19);
   #pragma VCC_VREG("vPartial", 20);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("agen0", "A0");
   #pragma EVE_REG("agenOffset", "A1");
   #pragma EVE_REG("agenScratch2", "A2");
   #pragma EVE_REG("agenIn", "A3");
   #pragma EVE_REG("agenOut", "A4");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("d", "I3");
   #pragma EVE_REG("c", "I4");
   

   __vcop_vloop(__vcop_compute(), 12u, 10u, 3u);
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(0), _PREG(12), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(13), _PREG(14), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(4), _PREG(15), _PREG(16), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(18), _AGEN(1), _VREG(0), __vcop_once());
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(20), _AGEN(2), _VREG(19), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(6), _AGEN(3), _VREG(20), __vcop_alws());
   __vcop_vadd(_VREG(19), _VREG(20), _VREG(19));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_pdda(_VREG(0)), __vcop_alws(), _VREG(19), _PREG(8), _AGEN(4), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_npt(), __vcop_last_i4(), _VREG(19), _PREG(10), _AGEN(2), _PREG(0));
   __vcop_vloop_end(3u);

   /* VLOOP 4 Start */

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
   #pragma EVE_REG("agen0", "A0");
   #pragma EVE_REG("agenOffset", "A1");
   #pragma EVE_REG("agenDisp", "A2");
   #pragma EVE_REG("agenMinCost", "A3");
   #pragma EVE_REG("agenCost", "A4");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("c", "I3");
   #pragma EVE_REG("d", "I4");
   

   __vcop_vloop(__vcop_compute(), 23u, 14u, 4u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(26), _VREG(16));
   __vcop_vinit(__vcop_sizeWU(), __vcop_i4_zero(), _PREG(28), _VREG(24));
   __vcop_vinit(__vcop_sizeWU(), __vcop_i4_zero(), _PREG(28), _VREG(25));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(6), _VREG(21));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(6), _VREG(22));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(8), _VREG(23));
   __vcop_vagen(_AGEN(2), _PREG(0), _PREG(22), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(0), _PREG(23), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(4), _PREG(24), _PREG(25), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(10), _AGEN(4), _VREG(26), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(12), _AGEN(4), _VREG(27), __vcop_alws());
   __vcop_vadd(_VREG(23), _VREG(16), _VREG(23));
   __vcop_vminsetf(_VREG(26), _VREG(24), _VREG(28));
   __vcop_vminsetf(_VREG(27), _VREG(25), _VREG(29));
   __vcop_vsel(_VREG(28), _VREG(23), _VREG(21));
   __vcop_vsel(_VREG(29), _VREG(23), _VREG(22));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_last_i4(), _VREG(24), _PREG(14), _AGEN(3), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_last_i4(), _VREG(25), _PREG(16), _AGEN(3), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_last_i4(), _VREG(21), _PREG(18), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_last_i4(), _VREG(22), _PREG(20), _AGEN(2), _PREG(0));
   __vcop_vloop_end(4u);

}

void vcop_disparity_hammingDistance64_first_row(
   __vptr_uint32 pLeft,
   __vptr_uint32 pRight,
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
   __vptr_int16 pCarryOverIn,
   __vptr_int16 pCarryOverOut,
   unsigned short scratchStride)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_disparity_hammingDistance64_first_row_init(pLeft, pRight, leftStride, rightStride, winWidth, winHeight, pDisparityOutput, pMinCostOutput, pAllCostOutput, allCostOutputStride, width, numDisparities, disparityStep, pCollateMask, pOffset, pScratch0, pCarryOverIn, pCarryOverOut, scratchStride, __pblock_vcop_disparity_hammingDistance64_first_row);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_disparity_hammingDistance64_first_row_vloops(__pblock_vcop_disparity_hammingDistance64_first_row);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_disparity_hammingDistance64_first_row_custom(
   __vptr_uint32 pLeft,
   __vptr_uint32 pRight,
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
   __vptr_int16 pCarryOverIn,
   __vptr_int16 pCarryOverOut,
   unsigned short scratchStride,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_disparity_hammingDistance64_first_row_init(pLeft, pRight, leftStride, rightStride, winWidth, winHeight, pDisparityOutput, pMinCostOutput, pAllCostOutput, allCostOutputStride, width, numDisparities, disparityStep, pCollateMask, pOffset, pScratch0, pCarryOverIn, pCarryOverOut, scratchStride, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_disparity_hammingDistance64_first_row_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_disparity_hammingDistance64_nth_row_firstCall, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_disparity_hammingDistance64_nth_row_firstCall, __ALIGNOF__(int));
unsigned short __pblock_vcop_disparity_hammingDistance64_nth_row_firstCall[154];

unsigned int vcop_disparity_hammingDistance64_nth_row_firstCall_param_count(void)
{
   return 154u;
}

unsigned int vcop_disparity_hammingDistance64_nth_row_firstCall_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_disparity_hammingDistance64_nth_row_firstCall_init(
   __vptr_uint32 pLeft_prevRow,
   __vptr_uint32 pLeft_lastRow,
   __vptr_uint32 pRight_prevRow,
   __vptr_uint32 pRight_lastRow,
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
   __vptr_int16 pCarryOverOut,
   unsigned short scratchStride,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((numDisparities/disparityStep))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((width-(8u)) + (8u)-1) & ~((8u)-1))/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pRight_prevRow+(disparityStep-1)*2*4+2*8u*4-2*4);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pRight_prevRow+(disparityStep-1)*2*4+2*8u*4-2*4+8u*4);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pLeft_lastRow+2*8u*4+2*4*(winWidth-1));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pLeft_lastRow+2*8u*4+2*4*(winWidth-1)+8u*4);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pRight_lastRow+(disparityStep-1)*2*4+2*8u*4+2*4*(winWidth-1));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pRight_lastRow+(disparityStep-1)*2*4+2*8u*4+2*4*(winWidth-1)+8u*4);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pScratch1);
   __vcop_pblock_init16(pblock, __offset+_PREG(20), 64);
   __vcop_pblock_init16(pblock, __offset+_PREG(21),  -(8u*4*2)*(((((width-(8u)) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(22), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(23), ((width-8u+8u-1&~(8u-1))*sizeof(*pAllCostOutput)) -(8u*sizeof(*pAllCostOutput))*(((((width-(8u)) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(24), (disparityStep*4*2) -(8u*4*2)*(((((width-(8u)) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)pLeft_prevRow+2*8u*4-2*4);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)pLeft_prevRow+2*8u*4-2*4+8u*4);
   __offset += 28;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((numDisparities/disparityStep))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((width-(8u)) + (8u)-1) & ~((8u)-1))/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pRight_prevRow+(disparityStep-1)*2*4+2*8u*4+2*4*(winWidth-1));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pRight_prevRow+(disparityStep-1)*2*4+2*8u*4+2*4*(winWidth-1)+8u*4);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pLeft_lastRow+2*8u*4-2*4);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pLeft_lastRow+2*8u*4-2*4+8u*4);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pRight_lastRow+(disparityStep-1)*2*4+2*8u*4-2*4);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pRight_lastRow+(disparityStep-1)*2*4+2*8u*4-2*4+8u*4);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pScratch2);
   __vcop_pblock_init16(pblock, __offset+_PREG(20), 64);
   __vcop_pblock_init16(pblock, __offset+_PREG(21),  -(8u*4*2)*(((((width-(8u)) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(22), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(23), ((width-8u+8u-1&~(8u-1))*sizeof(*pAllCostOutput)) -(8u*sizeof(*pAllCostOutput))*(((((width-(8u)) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(24), (disparityStep*4*2) -(8u*4*2)*(((((width-(8u)) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)pLeft_prevRow+2*8u*4+2*4*(winWidth-1));
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)pLeft_prevRow+2*8u*4+2*4*(winWidth-1)+8u*4);
   __offset += 28;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((numDisparities/disparityStep))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((width-(8u)) + (8u)-1) & ~((8u)-1))/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pScratch1);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pScratch2);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pScratch0);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(13), ((width-8u+8u-1&~(8u-1))*sizeof(*pAllCostOutput)) -(8u*sizeof(*pAllCostOutput))*(((((width-(8u)) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(14), (8u*scratchStride));
   __vcop_pblock_init16(pblock, __offset+_PREG(15), (sizeof(*pAllCostOutput)) -(8u*scratchStride)*(((((width-(8u)) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pCollateMask);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pOffset);
   __offset += 18;

   /* Loop 4 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((numDisparities/disparityStep))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (winWidth)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pLeft_lastRow+8u*4);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pRight_lastRow+(disparityStep-1)*2*4);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pRight_lastRow+(disparityStep-1)*2*4+8u*4);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pLeft_prevRow);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pLeft_prevRow+8u*4);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pRight_prevRow+(disparityStep-1)*2*4);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pRight_prevRow+(disparityStep-1)*2*4+8u*4);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pScratch2);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)pCarryOverOut);
   __vcop_pblock_init16(pblock, __offset+_PREG(24), (allCostOutputStride));
   __vcop_pblock_init16(pblock, __offset+_PREG(25), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(26), (0) -(4*2)*((winWidth)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(27), (disparityStep*4*2) -(4*2)*((winWidth)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(28), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(30), (uchar *)pLeft_lastRow);
   __offset += 30;

   /* Loop 5 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((((numDisparities/disparityStep) + (8u)-1) & ~((8u)-1))/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((width-(8u)))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pScratch0);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pScratch2+8u*sizeof(*pAllCostOutput));
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), (scratchStride));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), (8u*sizeof(*pScratch0)) -(scratchStride)*(((width-(8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(13), 2);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), (8u*allCostOutputStride) -(sizeof(*pAllCostOutput))*(((width-(8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pOffset+16);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pCarryOverOut);
   __offset += 18;

   /* Loop 6 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((((width) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((numDisparities/disparityStep))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (numDisparities));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pAllCostOutput+0);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pAllCostOutput+0+8u*sizeof(*pAllCostOutput));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pScratch2+0);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pScratch2+0+8u*sizeof(*pScratch2));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pMinCostOutput);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pMinCostOutput+8u*sizeof(*pMinCostOutput));
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)pDisparityOutput);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)pDisparityOutput+8u*sizeof(*pDisparityOutput));
   __vcop_pblock_init16(pblock, __offset+_PREG(26), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(27), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(28), (allCostOutputStride));
   __vcop_pblock_init16(pblock, __offset+_PREG(29), ((2*8u)*sizeof(*pAllCostOutput)) -(allCostOutputStride)*(((numDisparities/disparityStep))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(30), (-disparityStep));
   __vcop_pblock_init32(pblock, __offset+_PREG(32), 4294967295);
   __offset += 32;

   return 154u;
}

void vcop_disparity_hammingDistance64_nth_row_firstCall_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("vDisparityStep", 16);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vLeftBR0", 17);
   #pragma VCC_VREG("vLeftBR1", 18);
   #pragma VCC_VREG("vLeftUL0", 19);
   #pragma VCC_VREG("vLeftUL1", 20);
   #pragma VCC_VREG("vPtDiffPos", 21);
   #pragma VCC_VREG("vRightBR0", 22);
   #pragma VCC_VREG("vRightBR1", 23);
   #pragma VCC_VREG("vRightUL0", 24);
   #pragma VCC_VREG("vRightUL1", 25);
   #pragma VCC_VREG("vXorBR0", 26);
   #pragma VCC_VREG("vXorBR1", 27);
   #pragma VCC_VREG("vXorUL0", 28);
   #pragma VCC_VREG("vXorUL1", 29);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("agenLeft", "A0");
   #pragma EVE_REG("agenOut", "A1");
   #pragma EVE_REG("agenRight", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("d", "I3");
   #pragma EVE_REG("c", "I4");
   

   __vcop_vloop(__vcop_compute(), 25u, 14u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(20), _PREG(21), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(22), _PREG(23), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(20), _PREG(24), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(26), _AGEN(0), _VREG(19), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(28), _AGEN(0), _VREG(20), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(6), _AGEN(2), _VREG(24), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(8), _AGEN(2), _VREG(25), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(10), _AGEN(0), _VREG(17), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(12), _AGEN(0), _VREG(18), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(14), _AGEN(2), _VREG(22), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(16), _AGEN(2), _VREG(23), __vcop_alws());
   __vcop_vxor(_VREG(19), _VREG(24), _VREG(28));
   __vcop_vxor(_VREG(20), _VREG(25), _VREG(29));
   __vcop_vbitc(_VREG(28), _VREG(28));
   __vcop_vbitc(_VREG(29), _VREG(29));
   __vcop_vxor(_VREG(17), _VREG(22), _VREG(26));
   __vcop_vxor(_VREG(18), _VREG(23), _VREG(27));
   __vcop_vbitc(_VREG(26), _VREG(26));
   __vcop_vbitc(_VREG(27), _VREG(27));
   __vcop_vdintrlv(_VREG(28), _VREG(29));
   __vcop_vdintrlv(_VREG(26), _VREG(27));
   __vcop_vadd(_VREG(28), _VREG(29), _VREG(21));
   __vcop_vadd3(_VREG(26), _VREG(27), _VREG(21));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_npt(), __vcop_alws(), _VREG(21), _PREG(18), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vLeftBL0", 30);
   #pragma VCC_VREG("vLeftBL1", 31);
   #pragma VCC_VREG("vLeftUR0", 32);
   #pragma VCC_VREG("vLeftUR1", 33);
   #pragma VCC_VREG("vPtDiffNeg", 34);
   #pragma VCC_VREG("vRightBL0", 35);
   #pragma VCC_VREG("vRightBL1", 36);
   #pragma VCC_VREG("vRightUR0", 37);
   #pragma VCC_VREG("vRightUR1", 38);
   #pragma VCC_VREG("vXorBL0", 39);
   #pragma VCC_VREG("vXorBL1", 40);
   #pragma VCC_VREG("vXorUR0", 41);
   #pragma VCC_VREG("vXorUR1", 42);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("agenLeft", "A0");
   #pragma EVE_REG("agenOut", "A1");
   #pragma EVE_REG("agenRight", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("d", "I3");
   #pragma EVE_REG("c", "I4");
   

   __vcop_vloop(__vcop_compute(), 25u, 14u, 2u);
   __vcop_vagen(_AGEN(0), _PREG(20), _PREG(21), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(22), _PREG(23), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(20), _PREG(24), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(26), _AGEN(0), _VREG(32), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(28), _AGEN(0), _VREG(33), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(6), _AGEN(2), _VREG(37), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(8), _AGEN(2), _VREG(38), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(10), _AGEN(0), _VREG(30), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(12), _AGEN(0), _VREG(31), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(14), _AGEN(2), _VREG(35), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(16), _AGEN(2), _VREG(36), __vcop_alws());
   __vcop_vxor(_VREG(32), _VREG(37), _VREG(41));
   __vcop_vxor(_VREG(33), _VREG(38), _VREG(42));
   __vcop_vbitc(_VREG(41), _VREG(41));
   __vcop_vbitc(_VREG(42), _VREG(42));
   __vcop_vxor(_VREG(30), _VREG(35), _VREG(39));
   __vcop_vxor(_VREG(31), _VREG(36), _VREG(40));
   __vcop_vbitc(_VREG(39), _VREG(39));
   __vcop_vbitc(_VREG(40), _VREG(40));
   __vcop_vdintrlv(_VREG(41), _VREG(42));
   __vcop_vdintrlv(_VREG(39), _VREG(40));
   __vcop_vadd(_VREG(41), _VREG(42), _VREG(34));
   __vcop_vadd3(_VREG(39), _VREG(40), _VREG(34));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_npt(), __vcop_alws(), _VREG(34), _PREG(18), _AGEN(1), _PREG(0));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vPtDiff", 43);
   #pragma VCC_VREG("vPtDiffNeg", 44);
   #pragma VCC_VREG("vPtDiffPos", 45);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("agen0", "A0");
   #pragma EVE_REG("agenIn", "A1");
   #pragma EVE_REG("agenOut", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("d", "I3");
   #pragma EVE_REG("c", "I4");
   

   __vcop_vloop(__vcop_compute(), 11u, 9u, 3u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(12), _PREG(13), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(14), _PREG(15), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_nbits(), _PREG(16), _AGEN(0), _VREG(2), __vcop_once());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(18), _AGEN(0), _VREG(0), __vcop_once());
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(6), _AGEN(1), _VREG(45), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(8), _AGEN(1), _VREG(44), __vcop_alws());
   __vcop_vsub(_VREG(45), _VREG(44), _VREG(43));
   __vcop_vcmov(__vcop_last_i4(),_VREG(2),_VREG(1));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_pdda(_VREG(0)), __vcop_alws(), _VREG(43), _PREG(10), _AGEN(2), _PREG(0));
   __vcop_vloop_end(3u);

   /* VLOOP 4 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("agen0", "A0");
   #pragma EVE_REG("agenCost", "A1");
   #pragma EVE_REG("agenLeft", "A2");
   #pragma EVE_REG("agenRight", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("d", "I3");
   #pragma EVE_REG("w", "I4");
   

   __vcop_vloop(__vcop_compute(), 29u, 15u, 4u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(28), _VREG(3));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(24), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(25), _PREG(26), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(25), _PREG(27), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(30), _AGEN(2), _VREG(0), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(6), _AGEN(2), _VREG(2), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(8), _AGEN(3), _VREG(4), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(10), _AGEN(3), _VREG(6), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(12), _AGEN(2), _VREG(8), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(14), _AGEN(2), _VREG(10), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(16), _AGEN(3), _VREG(12), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(18), _AGEN(3), _VREG(14), __vcop_alws());
   __vcop_vxor(_VREG(0), _VREG(4), _VREG(0));
   __vcop_vxor(_VREG(2), _VREG(6), _VREG(2));
   __vcop_vbitc(_VREG(0), _VREG(0));
   __vcop_vbitc(_VREG(2), _VREG(2));
   __vcop_vxor(_VREG(8), _VREG(12), _VREG(8));
   __vcop_vxor(_VREG(10), _VREG(14), _VREG(10));
   __vcop_vbitc(_VREG(8), _VREG(8));
   __vcop_vbitc(_VREG(10), _VREG(10));
   __vcop_vdintrlv(_VREG(0), _VREG(2));
   __vcop_vdintrlv(_VREG(8), _VREG(10));
   __vcop_vadd3(_VREG(0), _VREG(2), _VREG(3));
   __vcop_vadd(_VREG(8), _VREG(10), _VREG(5));
   __vcop_vsub(_VREG(3), _VREG(5), _VREG(3));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_npt(), __vcop_last_i4(), _VREG(3), _PREG(20), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_predicate(_VREG(1)), __vcop_sizeH(), __vcop_collat(), __vcop_last_i4(), _VREG(3), _PREG(22), _AGEN(0), _PREG(0));
   __vcop_vloop_end(4u);

   /* VLOOP 5 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vAcc", 46);
   #pragma VCC_VREG("vPartial", 47);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("agen0", "A0");
   #pragma EVE_REG("agenScratch2", "A1");
   #pragma EVE_REG("agenIn", "A2");
   #pragma EVE_REG("agenOut", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("d", "I3");
   #pragma EVE_REG("c", "I4");
   

   __vcop_vloop(__vcop_compute(), 11u, 9u, 5u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(10), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(11), _PREG(12), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(13), _PREG(14), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(16), _AGEN(0), _VREG(0), __vcop_once());
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(18), _AGEN(1), _VREG(46), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(6), _AGEN(2), _VREG(47), __vcop_alws());
   __vcop_vadd(_VREG(46), _VREG(47), _VREG(46));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_pdda(_VREG(0)), __vcop_alws(), _VREG(46), _PREG(8), _AGEN(3), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_npt(), __vcop_last_i4(), _VREG(46), _PREG(18), _AGEN(1), _PREG(0));
   __vcop_vloop_end(5u);

   /* VLOOP 6 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vDisp0", 48);
   #pragma VCC_VREG("vDisp1", 49);
   #pragma VCC_VREG("vIdx", 50);
   #pragma VCC_VREG("vMin0", 51);
   #pragma VCC_VREG("vMin1", 52);
   #pragma VCC_VREG("vCost0", 53);
   #pragma VCC_VREG("vCost1", 54);
   #pragma VCC_VREG("vMinFlag0", 55);
   #pragma VCC_VREG("vMinFlag1", 56);
   #pragma VCC_VREG("vPartial0", 57);
   #pragma VCC_VREG("vPartial1", 58);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("agen0", "A0");
   #pragma EVE_REG("agenDisp", "A1");
   #pragma EVE_REG("agenMinCost", "A2");
   #pragma EVE_REG("agenCost", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("c", "I3");
   #pragma EVE_REG("d", "I4");
   

   __vcop_vloop(__vcop_compute(), 28u, 16u, 6u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(30), _VREG(16));
   __vcop_vinit(__vcop_sizeWU(), __vcop_i4_zero(), _PREG(32), _VREG(51));
   __vcop_vinit(__vcop_sizeWU(), __vcop_i4_zero(), _PREG(32), _VREG(52));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(6), _VREG(48));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(6), _VREG(49));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(8), _VREG(50));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(26), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(0), _PREG(27), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(28), _PREG(29), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(10), _AGEN(3), _VREG(53), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(12), _AGEN(3), _VREG(54), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(14), _AGEN(3), _VREG(57), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(16), _AGEN(3), _VREG(58), __vcop_alws());
   __vcop_vadd(_VREG(50), _VREG(16), _VREG(50));
   __vcop_vadd(_VREG(53), _VREG(57), _VREG(53));
   __vcop_vadd(_VREG(54), _VREG(58), _VREG(54));
   __vcop_vminsetf(_VREG(53), _VREG(51), _VREG(55));
   __vcop_vminsetf(_VREG(54), _VREG(52), _VREG(56));
   __vcop_vsel(_VREG(55), _VREG(50), _VREG(48));
   __vcop_vsel(_VREG(56), _VREG(50), _VREG(49));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(53), _PREG(10), _AGEN(3), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(54), _PREG(12), _AGEN(3), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_last_i4(), _VREG(51), _PREG(18), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_last_i4(), _VREG(52), _PREG(20), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_last_i4(), _VREG(48), _PREG(22), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_last_i4(), _VREG(49), _PREG(24), _AGEN(1), _PREG(0));
   __vcop_vloop_end(6u);

}

void vcop_disparity_hammingDistance64_nth_row_firstCall(
   __vptr_uint32 pLeft_prevRow,
   __vptr_uint32 pLeft_lastRow,
   __vptr_uint32 pRight_prevRow,
   __vptr_uint32 pRight_lastRow,
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
   __vptr_int16 pCarryOverOut,
   unsigned short scratchStride)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_disparity_hammingDistance64_nth_row_firstCall_init(pLeft_prevRow, pLeft_lastRow, pRight_prevRow, pRight_lastRow, leftStride, rightStride, winWidth, winHeight, pDisparityOutput, pMinCostOutput, pAllCostOutput, allCostOutputStride, width, numDisparities, disparityStep, pCollateMask, pOffset, pScratch0, pScratch1, pScratch2, pCarryOverOut, scratchStride, __pblock_vcop_disparity_hammingDistance64_nth_row_firstCall);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_disparity_hammingDistance64_nth_row_firstCall_vloops(__pblock_vcop_disparity_hammingDistance64_nth_row_firstCall);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_disparity_hammingDistance64_nth_row_firstCall_custom(
   __vptr_uint32 pLeft_prevRow,
   __vptr_uint32 pLeft_lastRow,
   __vptr_uint32 pRight_prevRow,
   __vptr_uint32 pRight_lastRow,
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
   __vptr_int16 pCarryOverOut,
   unsigned short scratchStride,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_disparity_hammingDistance64_nth_row_firstCall_init(pLeft_prevRow, pLeft_lastRow, pRight_prevRow, pRight_lastRow, leftStride, rightStride, winWidth, winHeight, pDisparityOutput, pMinCostOutput, pAllCostOutput, allCostOutputStride, width, numDisparities, disparityStep, pCollateMask, pOffset, pScratch0, pScratch1, pScratch2, pCarryOverOut, scratchStride, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_disparity_hammingDistance64_nth_row_firstCall_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_disparity_hammingDistance64_nth_row, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_disparity_hammingDistance64_nth_row, __ALIGNOF__(int));
unsigned short __pblock_vcop_disparity_hammingDistance64_nth_row[124];

unsigned int vcop_disparity_hammingDistance64_nth_row_param_count(void)
{
   return 124u;
}

unsigned int vcop_disparity_hammingDistance64_nth_row_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_disparity_hammingDistance64_nth_row_init(
   __vptr_uint32 pLeft_prevRow,
   __vptr_uint32 pLeft_lastRow,
   __vptr_uint32 pRight_prevRow,
   __vptr_uint32 pRight_lastRow,
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
   __vptr_int16 pCarryOverIn,
   __vptr_int16 pCarryOverOut,
   unsigned short scratchStride,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((numDisparities/disparityStep))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((width) + (8u)-1) & ~((8u)-1))/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pRight_prevRow+(disparityStep-1)*2*4-2*4);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pRight_prevRow+(disparityStep-1)*2*4-2*4+8u*4);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pLeft_lastRow+2*4*(winWidth-1));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pLeft_lastRow+2*4*(winWidth-1)+8u*4);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pRight_lastRow+(disparityStep-1)*2*4+2*4*(winWidth-1));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pRight_lastRow+(disparityStep-1)*2*4+2*4*(winWidth-1)+8u*4);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pScratch1);
   __vcop_pblock_init16(pblock, __offset+_PREG(20), 64);
   __vcop_pblock_init16(pblock, __offset+_PREG(21),  -(8u*4*2)*(((((width) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(22), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(23), ((width+8u-1&~(8u-1))*sizeof(*pAllCostOutput)) -(8u*sizeof(*pAllCostOutput))*(((((width) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(24), (disparityStep*4*2) -(8u*4*2)*(((((width) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)pLeft_prevRow-2*4);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)pLeft_prevRow-2*4+8u*4);
   __offset += 28;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((numDisparities/disparityStep))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((width) + (8u)-1) & ~((8u)-1))/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pRight_prevRow+(disparityStep-1)*2*4+2*4*(winWidth-1));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pRight_prevRow+(disparityStep-1)*2*4+2*4*(winWidth-1)+8u*4);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pLeft_lastRow-2*4);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pLeft_lastRow-2*4+8u*4);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pRight_lastRow+(disparityStep-1)*2*4-2*4);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pRight_lastRow+(disparityStep-1)*2*4-2*4+8u*4);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pScratch2);
   __vcop_pblock_init16(pblock, __offset+_PREG(20), 64);
   __vcop_pblock_init16(pblock, __offset+_PREG(21),  -(8u*4*2)*(((((width) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(22), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(23), ((width+8u-1&~(8u-1))*sizeof(*pAllCostOutput)) -(8u*sizeof(*pAllCostOutput))*(((((width) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(24), (disparityStep*4*2) -(8u*4*2)*(((((width) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)pLeft_prevRow+2*4*(winWidth-1));
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)pLeft_prevRow+2*4*(winWidth-1)+8u*4);
   __offset += 28;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((numDisparities/disparityStep))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((width) + (8u)-1) & ~((8u)-1))/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pScratch2);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pScratch0);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), ((width+8u-1&~(8u-1))*sizeof(*pAllCostOutput)) -(8u*sizeof(*pAllCostOutput))*(((((width) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), (8u*scratchStride));
   __vcop_pblock_init16(pblock, __offset+_PREG(13), (sizeof(*pAllCostOutput)) -(8u*scratchStride)*(((((width) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pOffset);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pScratch1);
   __offset += 16;

   /* Loop 4 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((((numDisparities/disparityStep) + (8u)-1) & ~((8u)-1))/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((width))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pScratch0);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pScratch2);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pCarryOverOut);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(13), (scratchStride));
   __vcop_pblock_init16(pblock, __offset+_PREG(14), (8u*sizeof(*pScratch0)) -(scratchStride)*(((width))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(15), 2);
   __vcop_pblock_init16(pblock, __offset+_PREG(16), (8u*allCostOutputStride) -(sizeof(*pAllCostOutput))*(((width))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pOffset+16);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pCarryOverIn);
   __offset += 20;

   /* Loop 5 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((((width) + (2*(8u))-1) & ~(2*(8u)-1))/(2*(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((numDisparities/disparityStep))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (numDisparities));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pAllCostOutput+0);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pAllCostOutput+0+8u*sizeof(*pAllCostOutput));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pScratch2+0);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pScratch2+0+8u*sizeof(*pScratch2));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pMinCostOutput);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pMinCostOutput+8u*sizeof(*pMinCostOutput));
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)pDisparityOutput);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)pDisparityOutput+8u*sizeof(*pDisparityOutput));
   __vcop_pblock_init16(pblock, __offset+_PREG(26), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(27), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(28), (allCostOutputStride));
   __vcop_pblock_init16(pblock, __offset+_PREG(29), ((2*8u)*sizeof(*pAllCostOutput)) -(allCostOutputStride)*(((numDisparities/disparityStep))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(30), (-disparityStep));
   __vcop_pblock_init32(pblock, __offset+_PREG(32), 4294967295);
   __offset += 32;

   return 124u;
}

void vcop_disparity_hammingDistance64_nth_row_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("vDisparityStep", 16);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vLeftBR0", 17);
   #pragma VCC_VREG("vLeftBR1", 18);
   #pragma VCC_VREG("vLeftUL0", 19);
   #pragma VCC_VREG("vLeftUL1", 20);
   #pragma VCC_VREG("vPtDiffPos", 21);
   #pragma VCC_VREG("vRightBR0", 22);
   #pragma VCC_VREG("vRightBR1", 23);
   #pragma VCC_VREG("vRightUL0", 24);
   #pragma VCC_VREG("vRightUL1", 25);
   #pragma VCC_VREG("vXorBR0", 26);
   #pragma VCC_VREG("vXorBR1", 27);
   #pragma VCC_VREG("vXorUL0", 28);
   #pragma VCC_VREG("vXorUL1", 29);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("agenLeft", "A0");
   #pragma EVE_REG("agenOut", "A1");
   #pragma EVE_REG("agenRight", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("d", "I3");
   #pragma EVE_REG("c", "I4");
   

   __vcop_vloop(__vcop_compute(), 25u, 14u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(20), _PREG(21), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(22), _PREG(23), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(20), _PREG(24), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(26), _AGEN(0), _VREG(19), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(28), _AGEN(0), _VREG(20), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(6), _AGEN(2), _VREG(24), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(8), _AGEN(2), _VREG(25), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(10), _AGEN(0), _VREG(17), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(12), _AGEN(0), _VREG(18), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(14), _AGEN(2), _VREG(22), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(16), _AGEN(2), _VREG(23), __vcop_alws());
   __vcop_vxor(_VREG(19), _VREG(24), _VREG(28));
   __vcop_vxor(_VREG(20), _VREG(25), _VREG(29));
   __vcop_vbitc(_VREG(28), _VREG(28));
   __vcop_vbitc(_VREG(29), _VREG(29));
   __vcop_vxor(_VREG(17), _VREG(22), _VREG(26));
   __vcop_vxor(_VREG(18), _VREG(23), _VREG(27));
   __vcop_vbitc(_VREG(26), _VREG(26));
   __vcop_vbitc(_VREG(27), _VREG(27));
   __vcop_vdintrlv(_VREG(28), _VREG(29));
   __vcop_vdintrlv(_VREG(26), _VREG(27));
   __vcop_vadd(_VREG(28), _VREG(29), _VREG(21));
   __vcop_vadd3(_VREG(26), _VREG(27), _VREG(21));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_npt(), __vcop_alws(), _VREG(21), _PREG(18), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vLeftBL0", 30);
   #pragma VCC_VREG("vLeftBL1", 31);
   #pragma VCC_VREG("vLeftUR0", 32);
   #pragma VCC_VREG("vLeftUR1", 33);
   #pragma VCC_VREG("vPtDiffNeg", 34);
   #pragma VCC_VREG("vRightBL0", 35);
   #pragma VCC_VREG("vRightBL1", 36);
   #pragma VCC_VREG("vRightUR0", 37);
   #pragma VCC_VREG("vRightUR1", 38);
   #pragma VCC_VREG("vXorBL0", 39);
   #pragma VCC_VREG("vXorBL1", 40);
   #pragma VCC_VREG("vXorUR0", 41);
   #pragma VCC_VREG("vXorUR1", 42);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("agenLeft", "A0");
   #pragma EVE_REG("agenOut", "A1");
   #pragma EVE_REG("agenRight", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("d", "I3");
   #pragma EVE_REG("c", "I4");
   

   __vcop_vloop(__vcop_compute(), 25u, 14u, 2u);
   __vcop_vagen(_AGEN(0), _PREG(20), _PREG(21), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(22), _PREG(23), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(20), _PREG(24), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(26), _AGEN(0), _VREG(32), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(28), _AGEN(0), _VREG(33), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(6), _AGEN(2), _VREG(37), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(8), _AGEN(2), _VREG(38), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(10), _AGEN(0), _VREG(30), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(12), _AGEN(0), _VREG(31), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(14), _AGEN(2), _VREG(35), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(16), _AGEN(2), _VREG(36), __vcop_alws());
   __vcop_vxor(_VREG(32), _VREG(37), _VREG(41));
   __vcop_vxor(_VREG(33), _VREG(38), _VREG(42));
   __vcop_vbitc(_VREG(41), _VREG(41));
   __vcop_vbitc(_VREG(42), _VREG(42));
   __vcop_vxor(_VREG(30), _VREG(35), _VREG(39));
   __vcop_vxor(_VREG(31), _VREG(36), _VREG(40));
   __vcop_vbitc(_VREG(39), _VREG(39));
   __vcop_vbitc(_VREG(40), _VREG(40));
   __vcop_vdintrlv(_VREG(41), _VREG(42));
   __vcop_vdintrlv(_VREG(39), _VREG(40));
   __vcop_vadd(_VREG(41), _VREG(42), _VREG(34));
   __vcop_vadd3(_VREG(39), _VREG(40), _VREG(34));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_npt(), __vcop_alws(), _VREG(34), _PREG(18), _AGEN(1), _PREG(0));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vPtDiff", 43);
   #pragma VCC_VREG("vPtDiffNeg", 44);
   #pragma VCC_VREG("vPtDiffPos", 45);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("agen0", "A0");
   #pragma EVE_REG("agenIn", "A1");
   #pragma EVE_REG("agenOut", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("d", "I3");
   #pragma EVE_REG("c", "I4");
   

   __vcop_vloop(__vcop_compute(), 9u, 8u, 3u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(10), _PREG(11), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(12), _PREG(13), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(14), _AGEN(0), _VREG(0), __vcop_once());
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(16), _AGEN(1), _VREG(45), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(6), _AGEN(1), _VREG(44), __vcop_alws());
   __vcop_vsub(_VREG(45), _VREG(44), _VREG(43));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_pdda(_VREG(0)), __vcop_alws(), _VREG(43), _PREG(8), _AGEN(2), _PREG(0));
   __vcop_vloop_end(3u);

   /* VLOOP 4 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vAcc", 46);
   #pragma VCC_VREG("vPartial", 47);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("agen0", "A0");
   #pragma EVE_REG("agenScratch2", "A1");
   #pragma EVE_REG("agenIn", "A2");
   #pragma EVE_REG("agenOut", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("d", "I3");
   #pragma EVE_REG("c", "I4");
   

   __vcop_vloop(__vcop_compute(), 11u, 10u, 4u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(12), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(13), _PREG(14), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(15), _PREG(16), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(18), _AGEN(0), _VREG(0), __vcop_once());
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(20), _AGEN(1), _VREG(46), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(6), _AGEN(2), _VREG(47), __vcop_alws());
   __vcop_vadd(_VREG(46), _VREG(47), _VREG(46));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_pdda(_VREG(0)), __vcop_alws(), _VREG(46), _PREG(8), _AGEN(3), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_npt(), __vcop_last_i4(), _VREG(46), _PREG(10), _AGEN(1), _PREG(0));
   __vcop_vloop_end(4u);

   /* VLOOP 5 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vDisp0", 48);
   #pragma VCC_VREG("vDisp1", 49);
   #pragma VCC_VREG("vIdx", 50);
   #pragma VCC_VREG("vMin0", 51);
   #pragma VCC_VREG("vMin1", 52);
   #pragma VCC_VREG("vCost0", 53);
   #pragma VCC_VREG("vCost1", 54);
   #pragma VCC_VREG("vMinFlag0", 55);
   #pragma VCC_VREG("vMinFlag1", 56);
   #pragma VCC_VREG("vPartial0", 57);
   #pragma VCC_VREG("vPartial1", 58);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("agen0", "A0");
   #pragma EVE_REG("agenDisp", "A1");
   #pragma EVE_REG("agenMinCost", "A2");
   #pragma EVE_REG("agenCost", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("c", "I3");
   #pragma EVE_REG("d", "I4");
   

   __vcop_vloop(__vcop_compute(), 28u, 16u, 5u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(30), _VREG(16));
   __vcop_vinit(__vcop_sizeWU(), __vcop_i4_zero(), _PREG(32), _VREG(51));
   __vcop_vinit(__vcop_sizeWU(), __vcop_i4_zero(), _PREG(32), _VREG(52));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(6), _VREG(48));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(6), _VREG(49));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(8), _VREG(50));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(26), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(0), _PREG(27), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(28), _PREG(29), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(10), _AGEN(3), _VREG(53), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(12), _AGEN(3), _VREG(54), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(14), _AGEN(3), _VREG(57), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(16), _AGEN(3), _VREG(58), __vcop_alws());
   __vcop_vadd(_VREG(50), _VREG(16), _VREG(50));
   __vcop_vadd(_VREG(53), _VREG(57), _VREG(53));
   __vcop_vadd(_VREG(54), _VREG(58), _VREG(54));
   __vcop_vminsetf(_VREG(53), _VREG(51), _VREG(55));
   __vcop_vminsetf(_VREG(54), _VREG(52), _VREG(56));
   __vcop_vsel(_VREG(55), _VREG(50), _VREG(48));
   __vcop_vsel(_VREG(56), _VREG(50), _VREG(49));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(53), _PREG(10), _AGEN(3), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(54), _PREG(12), _AGEN(3), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_last_i4(), _VREG(51), _PREG(18), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_last_i4(), _VREG(52), _PREG(20), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_last_i4(), _VREG(48), _PREG(22), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_last_i4(), _VREG(49), _PREG(24), _AGEN(1), _PREG(0));
   __vcop_vloop_end(5u);

}

void vcop_disparity_hammingDistance64_nth_row(
   __vptr_uint32 pLeft_prevRow,
   __vptr_uint32 pLeft_lastRow,
   __vptr_uint32 pRight_prevRow,
   __vptr_uint32 pRight_lastRow,
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
   __vptr_int16 pCarryOverIn,
   __vptr_int16 pCarryOverOut,
   unsigned short scratchStride)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_disparity_hammingDistance64_nth_row_init(pLeft_prevRow, pLeft_lastRow, pRight_prevRow, pRight_lastRow, leftStride, rightStride, winWidth, winHeight, pDisparityOutput, pMinCostOutput, pAllCostOutput, allCostOutputStride, width, numDisparities, disparityStep, pCollateMask, pOffset, pScratch0, pScratch1, pScratch2, pCarryOverIn, pCarryOverOut, scratchStride, __pblock_vcop_disparity_hammingDistance64_nth_row);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_disparity_hammingDistance64_nth_row_vloops(__pblock_vcop_disparity_hammingDistance64_nth_row);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_disparity_hammingDistance64_nth_row_custom(
   __vptr_uint32 pLeft_prevRow,
   __vptr_uint32 pLeft_lastRow,
   __vptr_uint32 pRight_prevRow,
   __vptr_uint32 pRight_lastRow,
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
   __vptr_int16 pCarryOverIn,
   __vptr_int16 pCarryOverOut,
   unsigned short scratchStride,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_disparity_hammingDistance64_nth_row_init(pLeft_prevRow, pLeft_lastRow, pRight_prevRow, pRight_lastRow, leftStride, rightStride, winWidth, winHeight, pDisparityOutput, pMinCostOutput, pAllCostOutput, allCostOutputStride, width, numDisparities, disparityStep, pCollateMask, pOffset, pScratch0, pScratch1, pScratch2, pCarryOverIn, pCarryOverOut, scratchStride, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_disparity_hammingDistance64_nth_row_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

