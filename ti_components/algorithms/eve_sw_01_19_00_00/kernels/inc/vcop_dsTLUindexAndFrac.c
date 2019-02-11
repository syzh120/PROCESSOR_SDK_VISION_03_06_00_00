#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_dsTLUindexAndFracBilInterpolate, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_dsTLUindexAndFracBilInterpolate, __ALIGNOF__(int));
unsigned short __pblock_vcop_dsTLUindexAndFracBilInterpolate[74];

unsigned int vcop_dsTLUindexAndFracBilInterpolate_param_count(void)
{
   return 74u;
}

unsigned int vcop_dsTLUindexAndFracBilInterpolate_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_dsTLUindexAndFracBilInterpolate_init(
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 fracArray,
   unsigned short numEvenMappedPixels,
   unsigned short numOddMappedPixels,
   __vptr_uint8 xFracArrayU,
   __vptr_uint8 yFracArrayU,
   __vptr_uint16 tluIndexArrayU,
   __vptr_uint8 xFracArrayV,
   __vptr_uint8 yFracArrayV,
   __vptr_uint16 tluIndexArrayV,
   unsigned char QShift,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((numEvenMappedPixels) + 2U*(8u)-1U) & ~(2U*(8u)-1U))/(2*(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_TRUNC,1));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), -4);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), QShift);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)tluIndexArray);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)tluIndexArray+8u*sizeof(*tluIndexArray));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)fracArray);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)fracArray+8u*sizeof(*fracArray));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)tluIndexArrayU);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)tluIndexArrayU+8u*sizeof(*tluIndexArrayU));
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)xFracArrayU);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)xFracArrayU+8u*sizeof(*xFracArrayU));
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)yFracArrayU);
   __vcop_pblock_init32(pblock, __offset+_PREG(30), (uchar *)yFracArrayU+8u*sizeof(*yFracArrayU));
   __vcop_pblock_init16(pblock, __offset+_PREG(32), 16);
   __vcop_pblock_init32(pblock, __offset+_PREG(34), 0x0000000001);
   __vcop_pblock_init32(pblock, __offset+_PREG(36), 0x000000000F);
   __offset += 36;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((numOddMappedPixels) + 2U*(8u)-1U) & ~(2U*(8u)-1U))/(2*(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_TRUNC,1));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), -4);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), QShift);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), 1);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)tluIndexArray+2*numEvenMappedPixels);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)tluIndexArray+2*numEvenMappedPixels+8u*sizeof(*tluIndexArray));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)fracArray+numEvenMappedPixels);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)fracArray+numEvenMappedPixels+8u*sizeof(*fracArray));
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)tluIndexArrayV);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)tluIndexArrayV+8u*sizeof(*tluIndexArrayV));
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)xFracArrayV);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)xFracArrayV+8u*sizeof(*xFracArrayV));
   __vcop_pblock_init32(pblock, __offset+_PREG(30), (uchar *)yFracArrayV);
   __vcop_pblock_init32(pblock, __offset+_PREG(32), (uchar *)yFracArrayV+8u*sizeof(*yFracArrayV));
   __vcop_pblock_init16(pblock, __offset+_PREG(34), 16);
   __vcop_pblock_init32(pblock, __offset+_PREG(36), 0x0000000001);
   __vcop_pblock_init32(pblock, __offset+_PREG(38), 0x000000000F);
   __offset += 38;

   return 74u;
}

void vcop_dsTLUindexAndFracBilInterpolate_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VQShift", 16);
   #pragma VCC_VREG("VmaskEven", 17);
   #pragma VCC_VREG("Vmaskx", 18);
   #pragma VCC_VREG("Vshifty", 19);
   #pragma VCC_VREG("fracMapU_1", 20);
   #pragma VCC_VREG("fracMapU_2", 21);
   #pragma VCC_VREG("tluIndexUOffset_1", 22);
   #pragma VCC_VREG("tluIndexUOffset_2", 23);
   #pragma VCC_VREG("tluIndexU_1", 24);
   #pragma VCC_VREG("tluIndexU_2", 25);
   #pragma VCC_VREG("xFracU_1", 26);
   #pragma VCC_VREG("xFracU_2", 27);
   #pragma VCC_VREG("yFracU_1", 28);
   #pragma VCC_VREG("yFracU_2", 29);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   #pragma EVE_REG("Addr2", "A1");
   #pragma EVE_REG("Addr3", "A2");
   #pragma EVE_REG("Addr4", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 29u, 18u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(34), _VREG(17));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(36), _VREG(18));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(8), _VREG(19));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(10), _VREG(16));
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(32), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(32), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(12), _AGEN(0), _VREG(24), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(14), _AGEN(0), _VREG(25), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(16), _AGEN(3), _VREG(20), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(18), _AGEN(3), _VREG(21), __vcop_alws());
   __vcop_vand(_VREG(20), _VREG(18), _VREG(26));
   __vcop_vand(_VREG(21), _VREG(18), _VREG(27));
   __vcop_vshf(_VREG(20), _VREG(19), _VREG(28));
   __vcop_vshf(_VREG(21), _VREG(19), _VREG(29));
   __vcop_vand(_VREG(24), _VREG(17), _VREG(22));
   __vcop_vand(_VREG(25), _VREG(17), _VREG(23));
   __vcop_vshf(_VREG(22), _VREG(16), _VREG(22));
   __vcop_vshf(_VREG(23), _VREG(16), _VREG(23));
   __vcop_vadd(_VREG(22), _VREG(26), _VREG(26));
   __vcop_vadd(_VREG(23), _VREG(27), _VREG(27));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(24), _PREG(20), _AGEN(1), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(25), _PREG(22), _AGEN(1), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(26), _PREG(24), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(27), _PREG(26), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(28), _PREG(28), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(29), _PREG(30), _AGEN(2), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VQShift", 30);
   #pragma VCC_VREG("VmaskEven", 31);
   #pragma VCC_VREG("Vmaskx", 32);
   #pragma VCC_VREG("Vone", 33);
   #pragma VCC_VREG("Vshifty", 34);
   #pragma VCC_VREG("fracMapV_1", 35);
   #pragma VCC_VREG("fracMapV_2", 36);
   #pragma VCC_VREG("maxTluIndexV_1", 37);
   #pragma VCC_VREG("maxTluIndexV_2", 38);
   #pragma VCC_VREG("tluIndexVOffset_1", 39);
   #pragma VCC_VREG("tluIndexVOffset_2", 40);
   #pragma VCC_VREG("tluIndexV_1", 41);
   #pragma VCC_VREG("tluIndexV_2", 42);
   #pragma VCC_VREG("xFracV_1", 43);
   #pragma VCC_VREG("xFracV_2", 44);
   #pragma VCC_VREG("yFracV_1", 45);
   #pragma VCC_VREG("yFracV_2", 46);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   #pragma EVE_REG("Addr2", "A1");
   #pragma EVE_REG("Addr3", "A2");
   #pragma EVE_REG("Addr4", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 30u, 19u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(36), _VREG(31));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(38), _VREG(32));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(8), _VREG(34));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(10), _VREG(30));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(12), _VREG(33));
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(34), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(34), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(14), _AGEN(0), _VREG(41), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(16), _AGEN(0), _VREG(42), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(18), _AGEN(3), _VREG(35), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(20), _AGEN(3), _VREG(36), __vcop_alws());
   __vcop_vand(_VREG(35), _VREG(32), _VREG(43));
   __vcop_vand(_VREG(36), _VREG(32), _VREG(44));
   __vcop_vshf(_VREG(35), _VREG(34), _VREG(45));
   __vcop_vshf(_VREG(36), _VREG(34), _VREG(46));
   __vcop_vand(_VREG(41), _VREG(31), _VREG(39));
   __vcop_vand(_VREG(42), _VREG(31), _VREG(40));
   __vcop_vshf(_VREG(39), _VREG(30), _VREG(39));
   __vcop_vshf(_VREG(40), _VREG(30), _VREG(40));
   __vcop_vadd(_VREG(39), _VREG(43), _VREG(43));
   __vcop_vadd(_VREG(40), _VREG(44), _VREG(44));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(41), _PREG(22), _AGEN(1), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(42), _PREG(24), _AGEN(1), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(43), _PREG(26), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(44), _PREG(28), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(45), _PREG(30), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(46), _PREG(32), _AGEN(2), _PREG(0));
   __vcop_vloop_end(2u);

}

void vcop_dsTLUindexAndFracBilInterpolate(
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 fracArray,
   unsigned short numEvenMappedPixels,
   unsigned short numOddMappedPixels,
   __vptr_uint8 xFracArrayU,
   __vptr_uint8 yFracArrayU,
   __vptr_uint16 tluIndexArrayU,
   __vptr_uint8 xFracArrayV,
   __vptr_uint8 yFracArrayV,
   __vptr_uint16 tluIndexArrayV,
   unsigned char QShift)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_dsTLUindexAndFracBilInterpolate_init(tluIndexArray, fracArray, numEvenMappedPixels, numOddMappedPixels, xFracArrayU, yFracArrayU, tluIndexArrayU, xFracArrayV, yFracArrayV, tluIndexArrayV, QShift, __pblock_vcop_dsTLUindexAndFracBilInterpolate);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_dsTLUindexAndFracBilInterpolate_vloops(__pblock_vcop_dsTLUindexAndFracBilInterpolate);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_dsTLUindexAndFracBilInterpolate_custom(
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 fracArray,
   unsigned short numEvenMappedPixels,
   unsigned short numOddMappedPixels,
   __vptr_uint8 xFracArrayU,
   __vptr_uint8 yFracArrayU,
   __vptr_uint16 tluIndexArrayU,
   __vptr_uint8 xFracArrayV,
   __vptr_uint8 yFracArrayV,
   __vptr_uint16 tluIndexArrayV,
   unsigned char QShift,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_dsTLUindexAndFracBilInterpolate_init(tluIndexArray, fracArray, numEvenMappedPixels, numOddMappedPixels, xFracArrayU, yFracArrayU, tluIndexArrayU, xFracArrayV, yFracArrayV, tluIndexArrayV, QShift, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_dsTLUindexAndFracBilInterpolate_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_dsTLUindexAndFracNNInterpolate, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_dsTLUindexAndFracNNInterpolate, __ALIGNOF__(int));
unsigned short __pblock_vcop_dsTLUindexAndFracNNInterpolate[48];

unsigned int vcop_dsTLUindexAndFracNNInterpolate_param_count(void)
{
   return 48u;
}

unsigned int vcop_dsTLUindexAndFracNNInterpolate_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_dsTLUindexAndFracNNInterpolate_init(
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 fracArray,
   unsigned short numEvenMappedPixels,
   unsigned short numOddMappedPixels,
   __vptr_uint16 tluIndexArrayU,
   __vptr_uint16 tluIndexArrayV,
   unsigned char stride,
   unsigned char QShift,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((numEvenMappedPixels) + 2U*(8u)-1U) & ~(2U*(8u)-1U))/(2*(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_TRUNC,1));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), 0x0000000001);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), -4);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)tluIndexArray);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)tluIndexArray+8u*sizeof(*tluIndexArray));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)fracArray);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)fracArray+8u*sizeof(*fracArray));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)tluIndexArrayU);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)tluIndexArrayU+8u*sizeof(*tluIndexArrayU));
   __vcop_pblock_init16(pblock, __offset+_PREG(24), 16);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), stride);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), QShift);
   __offset += 28;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((numOddMappedPixels) + 2U*(8u)-1U) & ~(2U*(8u)-1U))/(2*(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_TRUNC,1));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)fracArray+numEvenMappedPixels);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)fracArray+numEvenMappedPixels+8u*sizeof(*fracArray));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)tluIndexArrayV);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)tluIndexArrayV+8u*sizeof(*tluIndexArrayV));
   __vcop_pblock_init16(pblock, __offset+_PREG(16), 16);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)tluIndexArray+2*numEvenMappedPixels);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)tluIndexArray+2*numEvenMappedPixels+8u*sizeof(*tluIndexArray));
   __offset += 20;

   return 48u;
}

void vcop_dsTLUindexAndFracNNInterpolate_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VQShift", 16);
   #pragma VCC_VREG("VmaskEven", 17);
   #pragma VCC_VREG("Vshifty", 18);
   #pragma VCC_VREG("Vstride", 19);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("fracMapU_1", 20);
   #pragma VCC_VREG("fracMapU_2", 21);
   #pragma VCC_VREG("roundedYFracU_1", 22);
   #pragma VCC_VREG("roundedYFracU_2", 23);
   #pragma VCC_VREG("tluIndexUOffset_1", 24);
   #pragma VCC_VREG("tluIndexUOffset_2", 25);
   #pragma VCC_VREG("tluIndexU_1", 26);
   #pragma VCC_VREG("tluIndexU_2", 27);
   #pragma VCC_VREG("yFracU_1", 28);
   #pragma VCC_VREG("yFracU_2", 29);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   #pragma EVE_REG("Addr2", "A1");
   #pragma EVE_REG("Addr3", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 24u, 14u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(26), _VREG(19));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(28), _VREG(16));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(8), _VREG(17));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(10), _VREG(18));
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(24), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(12), _AGEN(0), _VREG(26), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(14), _AGEN(0), _VREG(27), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(16), _AGEN(2), _VREG(20), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(18), _AGEN(2), _VREG(21), __vcop_alws());
   __vcop_vand(_VREG(26), _VREG(17), _VREG(24));
   __vcop_vand(_VREG(27), _VREG(17), _VREG(25));
   __vcop_vadd(_VREG(26), _VREG(24), _VREG(26));
   __vcop_vadd(_VREG(27), _VREG(25), _VREG(27));
   __vcop_vshf(_VREG(20), _VREG(18), _VREG(28));
   __vcop_vshf(_VREG(21), _VREG(18), _VREG(29));
   __vcop_vrnd(_VREG(28), _VREG(16), _VREG(22));
   __vcop_vrnd(_VREG(29), _VREG(16), _VREG(23));
   __vcop_vmadd(_VREG(22), _VREG(19), _VREG(26), _PREG(0));
   __vcop_vmadd(_VREG(23), _VREG(19), _VREG(27), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(26), _PREG(20), _AGEN(1), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(27), _PREG(22), _AGEN(1), _PREG(6));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("fracMapV_1", 30);
   #pragma VCC_VREG("fracMapV_2", 31);
   #pragma VCC_VREG("roundedYFracV_1", 32);
   #pragma VCC_VREG("roundedYFracV_2", 33);
   #pragma VCC_VREG("tluIndexVOffset_1", 34);
   #pragma VCC_VREG("tluIndexVOffset_2", 35);
   #pragma VCC_VREG("tluIndexV_1", 36);
   #pragma VCC_VREG("tluIndexV_2", 37);
   #pragma VCC_VREG("yFracV_1", 38);
   #pragma VCC_VREG("yFracV_2", 39);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   #pragma EVE_REG("Addr2", "A1");
   #pragma EVE_REG("Addr3", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 20u, 10u, 2u);
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(16), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(18), _AGEN(0), _VREG(36), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(20), _AGEN(0), _VREG(37), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(8), _AGEN(2), _VREG(30), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(10), _AGEN(2), _VREG(31), __vcop_alws());
   __vcop_vand(_VREG(36), _VREG(17), _VREG(34));
   __vcop_vand(_VREG(37), _VREG(17), _VREG(35));
   __vcop_vadd(_VREG(36), _VREG(34), _VREG(36));
   __vcop_vadd(_VREG(37), _VREG(35), _VREG(37));
   __vcop_vshf(_VREG(30), _VREG(18), _VREG(38));
   __vcop_vshf(_VREG(31), _VREG(18), _VREG(39));
   __vcop_vrnd(_VREG(38), _VREG(16), _VREG(32));
   __vcop_vrnd(_VREG(39), _VREG(16), _VREG(33));
   __vcop_vmadd(_VREG(32), _VREG(19), _VREG(36), _PREG(0));
   __vcop_vmadd(_VREG(33), _VREG(19), _VREG(37), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(36), _PREG(12), _AGEN(1), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(37), _PREG(14), _AGEN(1), _PREG(6));
   __vcop_vloop_end(2u);

}

void vcop_dsTLUindexAndFracNNInterpolate(
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 fracArray,
   unsigned short numEvenMappedPixels,
   unsigned short numOddMappedPixels,
   __vptr_uint16 tluIndexArrayU,
   __vptr_uint16 tluIndexArrayV,
   unsigned char stride,
   unsigned char QShift)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_dsTLUindexAndFracNNInterpolate_init(tluIndexArray, fracArray, numEvenMappedPixels, numOddMappedPixels, tluIndexArrayU, tluIndexArrayV, stride, QShift, __pblock_vcop_dsTLUindexAndFracNNInterpolate);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_dsTLUindexAndFracNNInterpolate_vloops(__pblock_vcop_dsTLUindexAndFracNNInterpolate);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_dsTLUindexAndFracNNInterpolate_custom(
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 fracArray,
   unsigned short numEvenMappedPixels,
   unsigned short numOddMappedPixels,
   __vptr_uint16 tluIndexArrayU,
   __vptr_uint16 tluIndexArrayV,
   unsigned char stride,
   unsigned char QShift,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_dsTLUindexAndFracNNInterpolate_init(tluIndexArray, fracArray, numEvenMappedPixels, numOddMappedPixels, tluIndexArrayU, tluIndexArrayV, stride, QShift, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_dsTLUindexAndFracNNInterpolate_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_dsTLUindexAndFracBilInterpolateBB, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_dsTLUindexAndFracBilInterpolateBB, __ALIGNOF__(int));
unsigned short __pblock_vcop_dsTLUindexAndFracBilInterpolateBB[34];

unsigned int vcop_dsTLUindexAndFracBilInterpolateBB_param_count(void)
{
   return 34u;
}

unsigned int vcop_dsTLUindexAndFracBilInterpolateBB_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_dsTLUindexAndFracBilInterpolateBB_init(
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 fracArray,
   __vptr_uint8 xFracArrayU,
   __vptr_uint8 yFracArrayU,
   __vptr_uint16 tluIndexArrayU,
   __vptr_uint8 xFracArrayV,
   __vptr_uint8 yFracArrayV,
   __vptr_uint16 tluIndexArrayV,
   unsigned char QShift,
   unsigned short outputBlockSize,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((outputBlockSize) + 2U*(8u)-1U) & ~(2U*(8u)-1U))/(2*(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_TRUNC,1));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), -4);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), QShift);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), 1);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)tluIndexArray);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)fracArray);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)tluIndexArrayU);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)xFracArrayU);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)yFracArrayU);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)tluIndexArrayV);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)xFracArrayV);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)yFracArrayV);
   __vcop_pblock_init16(pblock, __offset+_PREG(30), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(31), 8);
   __vcop_pblock_init32(pblock, __offset+_PREG(32), 0x0000000001);
   __vcop_pblock_init32(pblock, __offset+_PREG(34), 0x000000000F);
   __offset += 34;

   return 34u;
}

void vcop_dsTLUindexAndFracBilInterpolateBB_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VQShift", 16);
   #pragma VCC_VREG("VmaskEven", 17);
   #pragma VCC_VREG("Vmaskx", 18);
   #pragma VCC_VREG("Vone", 19);
   #pragma VCC_VREG("Vshifty", 20);
   #pragma VCC_VREG("fracMapU", 21);
   #pragma VCC_VREG("fracMapV", 22);
   #pragma VCC_VREG("maxTluIndexV", 23);
   #pragma VCC_VREG("tluIndexU", 24);
   #pragma VCC_VREG("tluIndexUOffset", 25);
   #pragma VCC_VREG("tluIndexV", 26);
   #pragma VCC_VREG("tluIndexVOffset", 27);
   #pragma VCC_VREG("xFracU", 28);
   #pragma VCC_VREG("xFracV", 29);
   #pragma VCC_VREG("yFracU", 30);
   #pragma VCC_VREG("yFracV", 31);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   #pragma EVE_REG("Addr2", "A1");
   #pragma EVE_REG("Addr3", "A2");
   #pragma EVE_REG("Addr4", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 28u, 17u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(32), _VREG(17));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(34), _VREG(18));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(8), _VREG(20));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(10), _VREG(16));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(12), _VREG(19));
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(30), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(31), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(30), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(14), _AGEN(0), _VPAIR(24,26), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(16), _AGEN(3), _VPAIR(21,22), __vcop_alws());
   __vcop_vand(_VREG(21), _VREG(18), _VREG(28));
   __vcop_vand(_VREG(22), _VREG(18), _VREG(29));
   __vcop_vshf(_VREG(21), _VREG(20), _VREG(30));
   __vcop_vshf(_VREG(22), _VREG(20), _VREG(31));
   __vcop_vand(_VREG(24), _VREG(17), _VREG(25));
   __vcop_vand(_VREG(26), _VREG(17), _VREG(27));
   __vcop_vshf(_VREG(25), _VREG(16), _VREG(25));
   __vcop_vshf(_VREG(27), _VREG(16), _VREG(27));
   __vcop_vadd(_VREG(25), _VREG(28), _VREG(28));
   __vcop_vadd(_VREG(27), _VREG(29), _VREG(29));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(24), _PREG(18), _AGEN(1), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(28), _PREG(20), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(30), _PREG(22), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(26), _PREG(24), _AGEN(1), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(29), _PREG(26), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(31), _PREG(28), _AGEN(2), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_dsTLUindexAndFracBilInterpolateBB(
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 fracArray,
   __vptr_uint8 xFracArrayU,
   __vptr_uint8 yFracArrayU,
   __vptr_uint16 tluIndexArrayU,
   __vptr_uint8 xFracArrayV,
   __vptr_uint8 yFracArrayV,
   __vptr_uint16 tluIndexArrayV,
   unsigned char QShift,
   unsigned short outputBlockSize)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_dsTLUindexAndFracBilInterpolateBB_init(tluIndexArray, fracArray, xFracArrayU, yFracArrayU, tluIndexArrayU, xFracArrayV, yFracArrayV, tluIndexArrayV, QShift, outputBlockSize, __pblock_vcop_dsTLUindexAndFracBilInterpolateBB);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_dsTLUindexAndFracBilInterpolateBB_vloops(__pblock_vcop_dsTLUindexAndFracBilInterpolateBB);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_dsTLUindexAndFracBilInterpolateBB_custom(
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 fracArray,
   __vptr_uint8 xFracArrayU,
   __vptr_uint8 yFracArrayU,
   __vptr_uint16 tluIndexArrayU,
   __vptr_uint8 xFracArrayV,
   __vptr_uint8 yFracArrayV,
   __vptr_uint16 tluIndexArrayV,
   unsigned char QShift,
   unsigned short outputBlockSize,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_dsTLUindexAndFracBilInterpolateBB_init(tluIndexArray, fracArray, xFracArrayU, yFracArrayU, tluIndexArrayU, xFracArrayV, yFracArrayV, tluIndexArrayV, QShift, outputBlockSize, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_dsTLUindexAndFracBilInterpolateBB_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_dsTLUindexAndFracNNInterpolateBB, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_dsTLUindexAndFracNNInterpolateBB, __ALIGNOF__(int));
unsigned short __pblock_vcop_dsTLUindexAndFracNNInterpolateBB[24];

unsigned int vcop_dsTLUindexAndFracNNInterpolateBB_param_count(void)
{
   return 24u;
}

unsigned int vcop_dsTLUindexAndFracNNInterpolateBB_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_dsTLUindexAndFracNNInterpolateBB_init(
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 fracArray,
   __vptr_uint16 tluIndexArrayU,
   __vptr_uint16 tluIndexArrayV,
   __vptr_uint16 stride_ptr,
   unsigned char QShift,
   unsigned short outputBlockSize,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((outputBlockSize) + 2U*(8u)-1U) & ~(2U*(8u)-1U))/(2*(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_TRUNC,1));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), 0x0000000001);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), -4);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)tluIndexArray);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)fracArray);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)tluIndexArrayU);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)tluIndexArrayV);
   __vcop_pblock_init16(pblock, __offset+_PREG(20), 16);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)stride_ptr);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), QShift);
   __offset += 24;

   return 24u;
}

void vcop_dsTLUindexAndFracNNInterpolateBB_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VQShift", 16);
   #pragma VCC_VREG("VmaskEven", 17);
   #pragma VCC_VREG("Vshifty", 18);
   #pragma VCC_VREG("Vstride", 19);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("fracMapU", 20);
   #pragma VCC_VREG("fracMapV", 21);
   #pragma VCC_VREG("roundedYFracU", 22);
   #pragma VCC_VREG("roundedYFracV", 23);
   #pragma VCC_VREG("tluIndexU", 24);
   #pragma VCC_VREG("tluIndexUOffset", 25);
   #pragma VCC_VREG("tluIndexV", 26);
   #pragma VCC_VREG("tluIndexVOffset", 27);
   #pragma VCC_VREG("yFracU", 28);
   #pragma VCC_VREG("yFracV", 29);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   #pragma EVE_REG("Addr1", "A1");
   #pragma EVE_REG("Addr2", "A2");
   #pragma EVE_REG("Addr3", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 23u, 12u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(24), _VREG(16));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(8), _VREG(17));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(10), _VREG(18));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(20), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(20), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(22), _AGEN(0), _VREG(19), __vcop_once());
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(12), _AGEN(1), _VPAIR(24,26), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(14), _AGEN(3), _VPAIR(20,21), __vcop_alws());
   __vcop_vand(_VREG(24), _VREG(17), _VREG(25));
   __vcop_vand(_VREG(26), _VREG(17), _VREG(27));
   __vcop_vadd(_VREG(24), _VREG(25), _VREG(24));
   __vcop_vadd(_VREG(26), _VREG(27), _VREG(26));
   __vcop_vshf(_VREG(20), _VREG(18), _VREG(28));
   __vcop_vshf(_VREG(21), _VREG(18), _VREG(29));
   __vcop_vrnd(_VREG(28), _VREG(16), _VREG(22));
   __vcop_vrnd(_VREG(29), _VREG(16), _VREG(23));
   __vcop_vmadd(_VREG(22), _VREG(19), _VREG(24), _PREG(0));
   __vcop_vmadd(_VREG(23), _VREG(19), _VREG(26), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(24), _PREG(16), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(26), _PREG(18), _AGEN(2), _PREG(6));
   __vcop_vloop_end(1u);

}

void vcop_dsTLUindexAndFracNNInterpolateBB(
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 fracArray,
   __vptr_uint16 tluIndexArrayU,
   __vptr_uint16 tluIndexArrayV,
   __vptr_uint16 stride_ptr,
   unsigned char QShift,
   unsigned short outputBlockSize)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_dsTLUindexAndFracNNInterpolateBB_init(tluIndexArray, fracArray, tluIndexArrayU, tluIndexArrayV, stride_ptr, QShift, outputBlockSize, __pblock_vcop_dsTLUindexAndFracNNInterpolateBB);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_dsTLUindexAndFracNNInterpolateBB_vloops(__pblock_vcop_dsTLUindexAndFracNNInterpolateBB);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_dsTLUindexAndFracNNInterpolateBB_custom(
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 fracArray,
   __vptr_uint16 tluIndexArrayU,
   __vptr_uint16 tluIndexArrayV,
   __vptr_uint16 stride_ptr,
   unsigned char QShift,
   unsigned short outputBlockSize,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_dsTLUindexAndFracNNInterpolateBB_init(tluIndexArray, fracArray, tluIndexArrayU, tluIndexArrayV, stride_ptr, QShift, outputBlockSize, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_dsTLUindexAndFracNNInterpolateBB_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

