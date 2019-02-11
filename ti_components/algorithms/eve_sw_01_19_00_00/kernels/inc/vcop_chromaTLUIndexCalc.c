#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_chromaTLUIndexCalcBilInterpolate, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_chromaTLUIndexCalcBilInterpolate, __ALIGNOF__(int));
unsigned short __pblock_vcop_chromaTLUIndexCalcBilInterpolate[40];

unsigned int vcop_chromaTLUIndexCalcBilInterpolate_param_count(void)
{
   return 40u;
}

unsigned int vcop_chromaTLUIndexCalcBilInterpolate_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_chromaTLUIndexCalcBilInterpolate_init(
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 fracArray,
   __vptr_uint16 scatterStoreArray,
   unsigned short numMappedPixels,
   unsigned short inputStride,
   unsigned short inputStrideInverseQ16,
   unsigned short outputStride,
   unsigned short outputStrideInverseQ16,
   __vptr_uint16 tluIndexArrayUV,
   __vptr_uint8 xfracArrayUV,
   __vptr_uint8 yfracArrayUV,
   __vptr_uint16 scatterStoreArrayUV,
   unsigned char QShift,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((numMappedPixels) + (8u)-1U) & ~((8u)-1U))/((8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_TRUNC,1));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), __vcop_vop_round(2, 16));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), outputStride);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), outputStrideInverseQ16);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), -1);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), 0x0000000001);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), 0x000000000F);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), -4);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), QShift);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)tluIndexArray);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)fracArray);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)scatterStoreArray);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)tluIndexArrayUV);
   __vcop_pblock_init32(pblock, __offset+_PREG(30), (uchar *)scatterStoreArrayUV);
   __vcop_pblock_init32(pblock, __offset+_PREG(32), (uchar *)xfracArrayUV);
   __vcop_pblock_init32(pblock, __offset+_PREG(34), (uchar *)yfracArrayUV);
   __vcop_pblock_init16(pblock, __offset+_PREG(36), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(37), 8);
   __vcop_pblock_init32(pblock, __offset+_PREG(38), inputStride);
   __vcop_pblock_init32(pblock, __offset+_PREG(40), inputStrideInverseQ16);
   __offset += 40;

   return 40u;
}

void vcop_chromaTLUIndexCalcBilInterpolate_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("ChromaColIndex", 16);
   #pragma VCC_VREG("ChromaLineIndex", 17);
   #pragma VCC_VREG("LumaIndx", 18);
   #pragma VCC_VREG("LumaLineIndex", 19);
   #pragma VCC_VREG("LumaLineOffset", 20);
   #pragma VCC_VREG("LumaScatterStore", 21);
   #pragma VCC_VREG("Lumafrac", 22);
   #pragma VCC_VREG("Q16_outputStride", 23);
   #pragma VCC_VREG("Q16_stride", 24);
   #pragma VCC_VREG("U16_outputStride", 25);
   #pragma VCC_VREG("U16_stride", 26);
   #pragma VCC_VREG("VQShift", 27);
   #pragma VCC_VREG("VmaskFirstBit", 28);
   #pragma VCC_VREG("Vmaskx", 29);
   #pragma VCC_VREG("Vshift", 30);
   #pragma VCC_VREG("Vshifty", 31);
   #pragma VCC_VREG("xFrac", 32);
   #pragma VCC_VREG("yFrac", 33);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   #pragma EVE_REG("Addr2", "A1");
   #pragma EVE_REG("Addr3", "A2");
   #pragma EVE_REG("Addr4", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 40u, 20u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(38), _VREG(26));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(40), _VREG(24));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(8), _VREG(25));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(10), _VREG(23));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(12), _VREG(30));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(14), _VREG(28));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(16), _VREG(29));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(18), _VREG(31));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(20), _VREG(27));
   __vcop_vagen(_AGEN(0), _PREG(36), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(37), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(36), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(37), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(22), _AGEN(0), _VREG(18), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(24), _AGEN(1), _VREG(22), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(26), _AGEN(0), _VREG(21), __vcop_alws());
   __vcop_vand(_VREG(22), _VREG(29), _VREG(32));
   __vcop_vshf(_VREG(22), _VREG(31), _VREG(33));
   __vcop_vmpy(_VREG(24), _VREG(18), _VREG(19), _PREG(7));
   __vcop_vmpy(_VREG(26), _VREG(19), _VREG(20), _PREG(0));
   __vcop_vshf(_VREG(19), _VREG(30), _VREG(17));
   __vcop_vsub(_VREG(18), _VREG(20), _VREG(16));
   __vcop_vand(_VREG(16), _VREG(28), _VREG(22));
   __vcop_vshf(_VREG(22), _VREG(27), _VREG(22));
   __vcop_vadd(_VREG(22), _VREG(32), _VREG(32));
   __vcop_vmadd(_VREG(17), _VREG(26), _VREG(16), _PREG(0));
   __vcop_vandn(_VREG(16), _VREG(28), _VREG(16));
   __vcop_vand(_VREG(19), _VREG(28), _VREG(22));
   __vcop_vshf(_VREG(22), _VREG(27), _VREG(22));
   __vcop_vadd(_VREG(22), _VREG(33), _VREG(33));
   __vcop_vmpy(_VREG(23), _VREG(21), _VREG(19), _PREG(7));
   __vcop_vmpy(_VREG(25), _VREG(19), _VREG(20), _PREG(0));
   __vcop_vshf(_VREG(19), _VREG(30), _VREG(17));
   __vcop_vsub(_VREG(21), _VREG(20), _VREG(21));
   __vcop_vmadd(_VREG(17), _VREG(25), _VREG(21), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(16), _PREG(28), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(21), _PREG(30), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(32), _PREG(32), _AGEN(3), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(33), _PREG(34), _AGEN(3), _PREG(6));
   __vcop_vloop_end(1u);

}

void vcop_chromaTLUIndexCalcBilInterpolate(
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 fracArray,
   __vptr_uint16 scatterStoreArray,
   unsigned short numMappedPixels,
   unsigned short inputStride,
   unsigned short inputStrideInverseQ16,
   unsigned short outputStride,
   unsigned short outputStrideInverseQ16,
   __vptr_uint16 tluIndexArrayUV,
   __vptr_uint8 xfracArrayUV,
   __vptr_uint8 yfracArrayUV,
   __vptr_uint16 scatterStoreArrayUV,
   unsigned char QShift)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_chromaTLUIndexCalcBilInterpolate_init(tluIndexArray, fracArray, scatterStoreArray, numMappedPixels, inputStride, inputStrideInverseQ16, outputStride, outputStrideInverseQ16, tluIndexArrayUV, xfracArrayUV, yfracArrayUV, scatterStoreArrayUV, QShift, __pblock_vcop_chromaTLUIndexCalcBilInterpolate);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_chromaTLUIndexCalcBilInterpolate_vloops(__pblock_vcop_chromaTLUIndexCalcBilInterpolate);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_chromaTLUIndexCalcBilInterpolate_custom(
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 fracArray,
   __vptr_uint16 scatterStoreArray,
   unsigned short numMappedPixels,
   unsigned short inputStride,
   unsigned short inputStrideInverseQ16,
   unsigned short outputStride,
   unsigned short outputStrideInverseQ16,
   __vptr_uint16 tluIndexArrayUV,
   __vptr_uint8 xfracArrayUV,
   __vptr_uint8 yfracArrayUV,
   __vptr_uint16 scatterStoreArrayUV,
   unsigned char QShift,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_chromaTLUIndexCalcBilInterpolate_init(tluIndexArray, fracArray, scatterStoreArray, numMappedPixels, inputStride, inputStrideInverseQ16, outputStride, outputStrideInverseQ16, tluIndexArrayUV, xfracArrayUV, yfracArrayUV, scatterStoreArrayUV, QShift, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_chromaTLUIndexCalcBilInterpolate_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_chromaTLUIndexCalcNNInterpolate, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_chromaTLUIndexCalcNNInterpolate, __ALIGNOF__(int));
unsigned short __pblock_vcop_chromaTLUIndexCalcNNInterpolate[34];

unsigned int vcop_chromaTLUIndexCalcNNInterpolate_param_count(void)
{
   return 34u;
}

unsigned int vcop_chromaTLUIndexCalcNNInterpolate_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_chromaTLUIndexCalcNNInterpolate_init(
   __vptr_uint16 tluIndexArray,
   __vptr_uint16 scatterStoreArray,
   unsigned short numMappedPixels,
   unsigned short inputStride,
   unsigned short inputStrideInverseQ16,
   unsigned short outputStride,
   unsigned short outputStrideInverseQ16,
   __vptr_uint16 tluIndexArrayUV,
   __vptr_uint16 scatterStoreArrayUV,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((numMappedPixels) + 2U*(8u)-1U) & ~(2U*(8u)-1U))/(2*(8u)))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), outputStride);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), outputStrideInverseQ16);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), -1);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), 0x0000000001);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)tluIndexArray);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)tluIndexArray+8u*sizeof(*tluIndexArray));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)scatterStoreArray);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)scatterStoreArray+8u*sizeof(*scatterStoreArray));
   __vcop_pblock_init16(pblock, __offset+_PREG(22), __vcop_vop_round(2, 16));
   __vcop_pblock_init16(pblock, __offset+_PREG(23), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)tluIndexArrayUV);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)tluIndexArrayUV+8u*sizeof(*tluIndexArray));
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)scatterStoreArrayUV);
   __vcop_pblock_init32(pblock, __offset+_PREG(30), (uchar *)scatterStoreArrayUV+8u*sizeof(*scatterStoreArrayUV));
   __vcop_pblock_init32(pblock, __offset+_PREG(32), inputStride);
   __vcop_pblock_init32(pblock, __offset+_PREG(34), inputStrideInverseQ16);
   __offset += 34;

   return 34u;
}

void vcop_chromaTLUIndexCalcNNInterpolate_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("ChromaIndex_1", 16);
   #pragma VCC_VREG("ChromaIndex_2", 17);
   #pragma VCC_VREG("ChromaLineIndex_1", 18);
   #pragma VCC_VREG("ChromaLineIndex_2", 19);
   #pragma VCC_VREG("LumaIndx1", 20);
   #pragma VCC_VREG("LumaIndx2", 21);
   #pragma VCC_VREG("LumaLineIndex_1", 22);
   #pragma VCC_VREG("LumaLineIndex_2", 23);
   #pragma VCC_VREG("LumaLineOffset1", 24);
   #pragma VCC_VREG("LumaLineOffset2", 25);
   #pragma VCC_VREG("LumaScatterStore1", 26);
   #pragma VCC_VREG("LumaScatterStore2", 27);
   #pragma VCC_VREG("Q16_outputStride", 28);
   #pragma VCC_VREG("Q16_stride", 29);
   #pragma VCC_VREG("U16_outputStride", 30);
   #pragma VCC_VREG("U16_stride", 31);
   #pragma VCC_VREG("VmaskFirstBit", 32);
   #pragma VCC_VREG("Vshift", 33);
   #pragma VCC_VREG("opChromaColIndex1", 34);
   #pragma VCC_VREG("opChromaColIndex2", 35);
   #pragma VCC_VREG("opChromaLineIndex1", 36);
   #pragma VCC_VREG("opChromaLineIndex2", 37);
   #pragma VCC_VREG("opLumaLineIndex1", 38);
   #pragma VCC_VREG("opLumaLineIndex2", 39);
   #pragma VCC_VREG("opLumaLineOffset1", 40);
   #pragma VCC_VREG("opLumaLineOffset2", 41);
   #pragma VCC_VREG("xFracOffset1", 42);
   #pragma VCC_VREG("xFracOffset2", 43);
   #pragma VCC_VREG("yFracOffset1", 44);
   #pragma VCC_VREG("yFracOffset2", 45);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   #pragma EVE_REG("Addr2", "A1");
   #pragma EVE_REG("Addr3", "A2");
   #pragma EVE_REG("Addr4", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 47u, 17u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(32), _VREG(31));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(34), _VREG(29));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(6), _VREG(30));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(8), _VREG(28));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(10), _VREG(33));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(12), _VREG(32));
   __vcop_vagen(_AGEN(0), _PREG(23), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(23), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(23), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(23), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(14), _AGEN(0), _VREG(20), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(16), _AGEN(0), _VREG(21), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(18), _AGEN(1), _VREG(26), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(20), _AGEN(1), _VREG(27), __vcop_alws());
   __vcop_vmpy(_VREG(29), _VREG(20), _VREG(22), _PREG(22));
   __vcop_vmpy(_VREG(29), _VREG(21), _VREG(23), _PREG(22));
   __vcop_vmpy(_VREG(31), _VREG(22), _VREG(24), _PREG(0));
   __vcop_vmpy(_VREG(31), _VREG(23), _VREG(25), _PREG(0));
   __vcop_vand(_VREG(22), _VREG(32), _VREG(44));
   __vcop_vand(_VREG(23), _VREG(32), _VREG(45));
   __vcop_vshf(_VREG(22), _VREG(33), _VREG(18));
   __vcop_vshf(_VREG(23), _VREG(33), _VREG(19));
   __vcop_vadd(_VREG(18), _VREG(44), _VREG(18));
   __vcop_vadd(_VREG(19), _VREG(45), _VREG(19));
   __vcop_vsub(_VREG(20), _VREG(24), _VREG(16));
   __vcop_vsub(_VREG(21), _VREG(25), _VREG(17));
   __vcop_vand(_VREG(16), _VREG(32), _VREG(42));
   __vcop_vand(_VREG(17), _VREG(32), _VREG(43));
   __vcop_vadd(_VREG(16), _VREG(42), _VREG(16));
   __vcop_vadd(_VREG(17), _VREG(43), _VREG(17));
   __vcop_vmadd(_VREG(18), _VREG(31), _VREG(16), _PREG(0));
   __vcop_vmadd(_VREG(19), _VREG(31), _VREG(17), _PREG(0));
   __vcop_vmpy(_VREG(28), _VREG(26), _VREG(38), _PREG(22));
   __vcop_vmpy(_VREG(28), _VREG(27), _VREG(39), _PREG(22));
   __vcop_vmpy(_VREG(30), _VREG(38), _VREG(40), _PREG(0));
   __vcop_vmpy(_VREG(30), _VREG(39), _VREG(41), _PREG(0));
   __vcop_vshf(_VREG(38), _VREG(33), _VREG(36));
   __vcop_vshf(_VREG(39), _VREG(33), _VREG(37));
   __vcop_vsub(_VREG(26), _VREG(40), _VREG(34));
   __vcop_vsub(_VREG(27), _VREG(41), _VREG(35));
   __vcop_vmadd(_VREG(36), _VREG(30), _VREG(34), _PREG(0));
   __vcop_vmadd(_VREG(37), _VREG(30), _VREG(35), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(16), _PREG(24), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(17), _PREG(26), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(34), _PREG(28), _AGEN(3), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(35), _PREG(30), _AGEN(3), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_chromaTLUIndexCalcNNInterpolate(
   __vptr_uint16 tluIndexArray,
   __vptr_uint16 scatterStoreArray,
   unsigned short numMappedPixels,
   unsigned short inputStride,
   unsigned short inputStrideInverseQ16,
   unsigned short outputStride,
   unsigned short outputStrideInverseQ16,
   __vptr_uint16 tluIndexArrayUV,
   __vptr_uint16 scatterStoreArrayUV)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_chromaTLUIndexCalcNNInterpolate_init(tluIndexArray, scatterStoreArray, numMappedPixels, inputStride, inputStrideInverseQ16, outputStride, outputStrideInverseQ16, tluIndexArrayUV, scatterStoreArrayUV, __pblock_vcop_chromaTLUIndexCalcNNInterpolate);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_chromaTLUIndexCalcNNInterpolate_vloops(__pblock_vcop_chromaTLUIndexCalcNNInterpolate);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_chromaTLUIndexCalcNNInterpolate_custom(
   __vptr_uint16 tluIndexArray,
   __vptr_uint16 scatterStoreArray,
   unsigned short numMappedPixels,
   unsigned short inputStride,
   unsigned short inputStrideInverseQ16,
   unsigned short outputStride,
   unsigned short outputStrideInverseQ16,
   __vptr_uint16 tluIndexArrayUV,
   __vptr_uint16 scatterStoreArrayUV,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_chromaTLUIndexCalcNNInterpolate_init(tluIndexArray, scatterStoreArray, numMappedPixels, inputStride, inputStrideInverseQ16, outputStride, outputStrideInverseQ16, tluIndexArrayUV, scatterStoreArrayUV, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_chromaTLUIndexCalcNNInterpolate_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_chromaTLUIndexCalcBilInterpolateBB, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_chromaTLUIndexCalcBilInterpolateBB, __ALIGNOF__(int));
unsigned short __pblock_vcop_chromaTLUIndexCalcBilInterpolateBB[42];

unsigned int vcop_chromaTLUIndexCalcBilInterpolateBB_param_count(void)
{
   return 42u;
}

unsigned int vcop_chromaTLUIndexCalcBilInterpolateBB_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_chromaTLUIndexCalcBilInterpolateBB_init(
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 fracArray,
   __vptr_uint16 stride_ptr,
   __vptr_uint16 stride_inverse_q16_ptr,
   __vptr_uint16 tluIndexArrayUV,
   __vptr_uint8 xfracArrayUV,
   __vptr_uint8 yfracArrayUV,
   unsigned char QShift,
   unsigned short outputBlockWidth,
   unsigned short outputBlockHeight,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (outputBlockHeight)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((outputBlockWidth) + 2U*(8u)-1U) & ~(2U*(8u)-1U))/(2*(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_TRUNC,1));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), __vcop_vop_round(2, 16));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), 4294967294);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), -1);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), -16);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), 0x0000000001);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), 0x000000000F);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), -4);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), QShift);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)tluIndexArray);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)fracArray);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)tluIndexArrayUV);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)xfracArrayUV);
   __vcop_pblock_init32(pblock, __offset+_PREG(30), (uchar *)yfracArrayUV);
   __vcop_pblock_init16(pblock, __offset+_PREG(32), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(33), (2*outputBlockWidth*sizeof(*tluIndexArray)) -(2*8u*sizeof(*tluIndexArray))*(((((outputBlockWidth) + 2U*(8u)-1U) & ~(2U*(8u)-1U))/(2*(8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(34), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(35), (2*outputBlockWidth*sizeof(*fracArray)) -(2*8u*sizeof(*fracArray))*(((((outputBlockWidth) + 2U*(8u)-1U) & ~(2U*(8u)-1U))/(2*(8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(36), (((outputBlockWidth+1)/2)*sizeof(*tluIndexArrayUV)) -(8u*sizeof(*tluIndexArrayUV))*(((((outputBlockWidth) + 2U*(8u)-1U) & ~(2U*(8u)-1U))/(2*(8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(37), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(38), (((outputBlockWidth+1)/2)*sizeof(*xfracArrayUV)) -(8u*sizeof(*xfracArrayUV))*(((((outputBlockWidth) + 2U*(8u)-1U) & ~(2U*(8u)-1U))/(2*(8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(40), (uchar *)stride_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(42), (uchar *)stride_ptr+4);
   __offset += 42;

   return 42u;
}

void vcop_chromaTLUIndexCalcBilInterpolateBB_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("ChromaColIndex", 16);
   #pragma VCC_VREG("ChromaIndex", 17);
   #pragma VCC_VREG("ChromaLineIndex", 18);
   #pragma VCC_VREG("LumaIndx", 19);
   #pragma VCC_VREG("LumaLineIndex", 20);
   #pragma VCC_VREG("LumaLineOffset", 21);
   #pragma VCC_VREG("Lumafrac", 22);
   #pragma VCC_VREG("Q16_stride", 23);
   #pragma VCC_VREG("U16_stride", 24);
   #pragma VCC_VREG("VQShift", 25);
   #pragma VCC_VREG("VmaskEven", 26);
   #pragma VCC_VREG("VmaskFirstBit", 27);
   #pragma VCC_VREG("Vmaskx", 28);
   #pragma VCC_VREG("Vq16shift", 29);
   #pragma VCC_VREG("Vshift", 30);
   #pragma VCC_VREG("Vshifty", 31);
   #pragma VCC_VREG("xFrac", 32);
   #pragma VCC_VREG("xFracOffset", 33);
   #pragma VCC_VREG("yFrac", 34);
   #pragma VCC_VREG("yFracOffset", 35);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   #pragma EVE_REG("Addr3", "A1");
   #pragma EVE_REG("Addr4", "A2");
   #pragma EVE_REG("Addr5", "A3");
   #pragma EVE_REG("Addr6", "A4");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 34u, 21u, 1u);
   __vcop_vinit(__vcop_sizeWU(), __vcop_once(), _PREG(8), _VREG(26));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(10), _VREG(30));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(12), _VREG(29));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(14), _VREG(27));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(16), _VREG(28));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(18), _VREG(31));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(20), _VREG(25));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(32), _PREG(33), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(34), _PREG(35), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(34), _PREG(36), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(4), _PREG(37), _PREG(38), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(40), _AGEN(0), _VREG(24), __vcop_once());
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(42), _AGEN(0), _VREG(23), __vcop_once());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(22), _AGEN(1), _VREG(19), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_ds2(), _PREG(24), _AGEN(2), _VREG(22), __vcop_alws());
   __vcop_vand(_VREG(22), _VREG(28), _VREG(32));
   __vcop_vshf(_VREG(22), _VREG(31), _VREG(34));
   __vcop_vmpy(_VREG(23), _VREG(19), _VREG(20), _PREG(7));
   __vcop_vmpy(_VREG(24), _VREG(20), _VREG(21), _PREG(0));
   __vcop_vshf(_VREG(20), _VREG(30), _VREG(18));
   __vcop_vsub(_VREG(19), _VREG(21), _VREG(16));
   __vcop_vand(_VREG(16), _VREG(27), _VREG(33));
   __vcop_vshf(_VREG(33), _VREG(25), _VREG(33));
   __vcop_vadd(_VREG(33), _VREG(32), _VREG(32));
   __vcop_vmadd(_VREG(18), _VREG(24), _VREG(16), _PREG(0));
   __vcop_vand(_VREG(16), _VREG(26), _VREG(17));
   __vcop_vand(_VREG(20), _VREG(27), _VREG(35));
   __vcop_vshf(_VREG(35), _VREG(25), _VREG(35));
   __vcop_vadd(_VREG(35), _VREG(34), _VREG(34));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(17), _PREG(26), _AGEN(3), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(32), _PREG(28), _AGEN(4), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(34), _PREG(30), _AGEN(4), _PREG(6));
   __vcop_vloop_end(1u);

}

void vcop_chromaTLUIndexCalcBilInterpolateBB(
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 fracArray,
   __vptr_uint16 stride_ptr,
   __vptr_uint16 stride_inverse_q16_ptr,
   __vptr_uint16 tluIndexArrayUV,
   __vptr_uint8 xfracArrayUV,
   __vptr_uint8 yfracArrayUV,
   unsigned char QShift,
   unsigned short outputBlockWidth,
   unsigned short outputBlockHeight)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_chromaTLUIndexCalcBilInterpolateBB_init(tluIndexArray, fracArray, stride_ptr, stride_inverse_q16_ptr, tluIndexArrayUV, xfracArrayUV, yfracArrayUV, QShift, outputBlockWidth, outputBlockHeight, __pblock_vcop_chromaTLUIndexCalcBilInterpolateBB);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_chromaTLUIndexCalcBilInterpolateBB_vloops(__pblock_vcop_chromaTLUIndexCalcBilInterpolateBB);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_chromaTLUIndexCalcBilInterpolateBB_custom(
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 fracArray,
   __vptr_uint16 stride_ptr,
   __vptr_uint16 stride_inverse_q16_ptr,
   __vptr_uint16 tluIndexArrayUV,
   __vptr_uint8 xfracArrayUV,
   __vptr_uint8 yfracArrayUV,
   unsigned char QShift,
   unsigned short outputBlockWidth,
   unsigned short outputBlockHeight,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_chromaTLUIndexCalcBilInterpolateBB_init(tluIndexArray, fracArray, stride_ptr, stride_inverse_q16_ptr, tluIndexArrayUV, xfracArrayUV, yfracArrayUV, QShift, outputBlockWidth, outputBlockHeight, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_chromaTLUIndexCalcBilInterpolateBB_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_chromaTLUIndexCalcNNInterpolateBB, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_chromaTLUIndexCalcNNInterpolateBB, __ALIGNOF__(int));
unsigned short __pblock_vcop_chromaTLUIndexCalcNNInterpolateBB[26];

unsigned int vcop_chromaTLUIndexCalcNNInterpolateBB_param_count(void)
{
   return 26u;
}

unsigned int vcop_chromaTLUIndexCalcNNInterpolateBB_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_chromaTLUIndexCalcNNInterpolateBB_init(
   __vptr_uint16 tluIndexArray,
   __vptr_uint16 stride_ptr,
   __vptr_uint16 stride_inverse_q16_ptr,
   __vptr_uint16 tluIndexArrayUV,
   unsigned short outputBlockWidth,
   unsigned short outputBlockHeight,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (outputBlockHeight)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((outputBlockWidth) + 4U*(8u)-1U) & ~(4U*(8u)-1U))/(4*(8u)))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), -1);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), 0x0000000001);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)tluIndexArray);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)tluIndexArray+2*8u*sizeof(*tluIndexArray));
   __vcop_pblock_init16(pblock, __offset+_PREG(14), __vcop_vop_round(2, 16));
   __vcop_pblock_init16(pblock, __offset+_PREG(15), 64);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)tluIndexArrayUV);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)tluIndexArrayUV+8u*sizeof(*tluIndexArray));
   __vcop_pblock_init16(pblock, __offset+_PREG(20), (2*outputBlockWidth*sizeof(*tluIndexArray)) -(4*8u*sizeof(*tluIndexArray))*(((((outputBlockWidth) + 4U*(8u)-1U) & ~(4U*(8u)-1U))/(4*(8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(21), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(22), (((outputBlockWidth+1)/2)*sizeof(*tluIndexArray)) -(2*8u*sizeof(*tluIndexArray))*(((((outputBlockWidth) + 4U*(8u)-1U) & ~(4U*(8u)-1U))/(4*(8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)stride_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)stride_ptr+4);
   __offset += 26;

   return 26u;
}

void vcop_chromaTLUIndexCalcNNInterpolateBB_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("ChromaIndex_1", 16);
   #pragma VCC_VREG("ChromaIndex_2", 17);
   #pragma VCC_VREG("ChromaLineIndex_1", 18);
   #pragma VCC_VREG("ChromaLineIndex_2", 19);
   #pragma VCC_VREG("LumaIndx1", 20);
   #pragma VCC_VREG("LumaIndx2", 21);
   #pragma VCC_VREG("LumaLineIndex_1", 22);
   #pragma VCC_VREG("LumaLineIndex_2", 23);
   #pragma VCC_VREG("LumaLineOffset1", 24);
   #pragma VCC_VREG("LumaLineOffset2", 25);
   #pragma VCC_VREG("Q16_stride", 26);
   #pragma VCC_VREG("U16_stride", 27);
   #pragma VCC_VREG("VmaskFirstBit", 28);
   #pragma VCC_VREG("Vshift", 29);
   #pragma VCC_VREG("xFracOffset1", 30);
   #pragma VCC_VREG("xFracOffset2", 31);
   #pragma VCC_VREG("yFracOffset1", 32);
   #pragma VCC_VREG("yFracOffset2", 33);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   #pragma EVE_REG("Addr3", "A1");
   #pragma EVE_REG("Addr4", "A2");
   #pragma EVE_REG("Addr5", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 31u, 13u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(6), _VREG(29));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(8), _VREG(28));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(15), _PREG(20), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(21), _PREG(22), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(24), _AGEN(0), _VREG(27), __vcop_once());
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(26), _AGEN(0), _VREG(26), __vcop_once());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(10), _AGEN(1), _VREG(20), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(12), _AGEN(1), _VREG(21), __vcop_alws());
   __vcop_vmpy(_VREG(26), _VREG(20), _VREG(22), _PREG(14));
   __vcop_vmpy(_VREG(26), _VREG(21), _VREG(23), _PREG(14));
   __vcop_vmpy(_VREG(27), _VREG(22), _VREG(24), _PREG(0));
   __vcop_vmpy(_VREG(27), _VREG(23), _VREG(25), _PREG(0));
   __vcop_vand(_VREG(22), _VREG(28), _VREG(32));
   __vcop_vand(_VREG(23), _VREG(28), _VREG(33));
   __vcop_vshf(_VREG(22), _VREG(29), _VREG(18));
   __vcop_vshf(_VREG(23), _VREG(29), _VREG(19));
   __vcop_vadd(_VREG(18), _VREG(32), _VREG(18));
   __vcop_vadd(_VREG(19), _VREG(33), _VREG(19));
   __vcop_vsub(_VREG(20), _VREG(24), _VREG(16));
   __vcop_vsub(_VREG(21), _VREG(25), _VREG(17));
   __vcop_vand(_VREG(16), _VREG(28), _VREG(30));
   __vcop_vand(_VREG(17), _VREG(28), _VREG(31));
   __vcop_vadd(_VREG(16), _VREG(30), _VREG(16));
   __vcop_vadd(_VREG(17), _VREG(31), _VREG(17));
   __vcop_vmadd(_VREG(18), _VREG(27), _VREG(16), _PREG(0));
   __vcop_vmadd(_VREG(19), _VREG(27), _VREG(17), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(16), _PREG(16), _AGEN(3), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(17), _PREG(18), _AGEN(3), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_chromaTLUIndexCalcNNInterpolateBB(
   __vptr_uint16 tluIndexArray,
   __vptr_uint16 stride_ptr,
   __vptr_uint16 stride_inverse_q16_ptr,
   __vptr_uint16 tluIndexArrayUV,
   unsigned short outputBlockWidth,
   unsigned short outputBlockHeight)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_chromaTLUIndexCalcNNInterpolateBB_init(tluIndexArray, stride_ptr, stride_inverse_q16_ptr, tluIndexArrayUV, outputBlockWidth, outputBlockHeight, __pblock_vcop_chromaTLUIndexCalcNNInterpolateBB);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_chromaTLUIndexCalcNNInterpolateBB_vloops(__pblock_vcop_chromaTLUIndexCalcNNInterpolateBB);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_chromaTLUIndexCalcNNInterpolateBB_custom(
   __vptr_uint16 tluIndexArray,
   __vptr_uint16 stride_ptr,
   __vptr_uint16 stride_inverse_q16_ptr,
   __vptr_uint16 tluIndexArrayUV,
   unsigned short outputBlockWidth,
   unsigned short outputBlockHeight,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_chromaTLUIndexCalcNNInterpolateBB_init(tluIndexArray, stride_ptr, stride_inverse_q16_ptr, tluIndexArrayUV, outputBlockWidth, outputBlockHeight, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_chromaTLUIndexCalcNNInterpolateBB_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

