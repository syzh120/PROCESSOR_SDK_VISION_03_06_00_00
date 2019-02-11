#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_generateList, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_generateList, __ALIGNOF__(int));
unsigned short __pblock_vcop_generateList[70];

unsigned int vcop_generateList_param_count(void)
{
   return 70u;
}

unsigned int vcop_generateList_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_generateList_init(
   __vptr_uint8 pIn,
   __vptr_uint8 pEndRowPadVal,
   __vptr_uint16 pXval,
   __vptr_uint16 pYval,
   __vptr_uint16 pBlockX,
   __vptr_uint16 pBlockY,
   unsigned short numHorzBlock,
   unsigned short numVertBlock,
   __vptr_uint16 pListX,
   __vptr_uint16 pListY,
   __vptr_uint16 pNumElmtsX,
   __vptr_uint16 pNumElmtsY,
   unsigned short maxNumElmts,
   unsigned short width,
   unsigned short height,
   unsigned short inStride,
   unsigned char qShift,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (height)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), (inStride*sizeof(*pIn)));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pEndRowPadVal);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pIn+sizeof(*pIn)*((width+8u-1&~(8u-1))-8u));
   __offset += 10;

   /* Loop 2 PREGS */
   const int preg_ref1 = _PREG(18);
   const int preg_ref2 = _PREG(22);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_4PARAM,preg_ref1,RM_NONE,0));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), __vcop_store_round_sat(SM_4PARAM,preg_ref2,RM_NONE,0));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), width);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), height);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pBlockX);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pBlockY);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), numHorzBlock*width);
   __vcop_pblock_4param_init(pblock, __offset+_PREG(18), numHorzBlock*width,0,0,0);
   __vcop_pblock_4param_init(pblock, __offset+_PREG(22), numVertBlock*height,0,0,0);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), 0xff);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), 1);
   __offset += 28;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (height)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((width) + (8u)-1) & ~((8u)-1))/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), -1);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), qShift);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), maxNumElmts);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pIn);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pXval);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pListX);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pListY);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)pNumElmtsY);
   __vcop_pblock_init16(pblock, __offset+_PREG(24), 2);
   __vcop_pblock_init16(pblock, __offset+_PREG(25), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(26), (sizeof(*pIn)*inStride) -(sizeof(*pIn)*8u)*(((((width) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(27), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(28),  -(sizeof(*pXval)*8u)*(((((width) + (8u)-1) & ~((8u)-1))/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(30), (uchar *)pNumElmtsX);
   __vcop_pblock_init32(pblock, __offset+_PREG(32), (uchar *)pYval);
   __offset += 32;

   return 70u;
}

void vcop_generateList_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("vBlockX", 16);
   #pragma VCC_VREG("vBlockY", 17);
   #pragma VCC_VREG("vEndRowPadVal", 18);
   #pragma VCC_VREG("vFF", 19);
   #pragma VCC_VREG("vHeight", 20);
   #pragma VCC_VREG("vNumElmts", 21);
   #pragma VCC_VREG("vOne", 22);
   #pragma VCC_VREG("vOneIn8Lanes", 23);
   #pragma VCC_VREG("vWidth", 24);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vIn", 25);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   #pragma EVE_REG("AddrIn", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("i", "I4");
   

   __vcop_vloop(__vcop_compute(), 7u, 5u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(6), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(8), _AGEN(0), _VREG(18), __vcop_once());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(10), _AGEN(1), _VREG(25), __vcop_alws());
   __vcop_vand(_VREG(25), _VREG(18), _VREG(25));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(25), _PREG(10), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vFlag", 26);
   #pragma VCC_VREG("vNumHorzBlock", 27);
   #pragma VCC_VREG("vUpdateBlockX", 28);
   #pragma VCC_VREG("vUpdateBlockY", 29);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("i", "I4");
   

   __vcop_vloop(__vcop_compute(), 15u, 14u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(26), _VREG(19));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(28), _VREG(22));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(8), _VREG(24));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(10), _VREG(20));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(16), _VREG(27));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(12), _AGEN(0), _VREG(16), __vcop_once());
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(14), _AGEN(0), _VREG(17), __vcop_once());
   __vcop_vadd(_VREG(16), _VREG(24), _VREG(28));
   __vcop_vadd(_VREG(17), _VREG(20), _VREG(29));
   __vcop_vcmpeq(_VREG(28), _VREG(27), _VREG(26));
   __vcop_vbittr(_VREG(19), _VREG(23));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_1pt(), __vcop_alws(), _VREG(28), _PREG(12), _AGEN(0), _PREG(6));
   __vcop_vstore(__vcop_predicate(_VREG(26)), __vcop_sizeHU(), __vcop_1pt(), __vcop_alws(), _VREG(29), _PREG(14), _AGEN(0), _PREG(7));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("vyVal", 30);
   #pragma VCC_VREG("vBitMask", 31);
   #pragma VCC_VREG("vFlag", 32);
   #pragma VCC_VREG("vIn", 33);
   #pragma VCC_VREG("vMask", 34);
   #pragma VCC_VREG("vMaxNumElmts", 35);
   #pragma VCC_VREG("vNeg1", 36);
   #pragma VCC_VREG("vNumNewElmts", 37);
   #pragma VCC_VREG("vQshift", 38);
   #pragma VCC_VREG("vZero", 39);
   #pragma VCC_VREG("vxVal", 40);
   #pragma VCC_VREG("vxValAbsolute", 41);
   #pragma VCC_VREG("vyValAbsolute", 42);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   #pragma EVE_REG("AddrYval", "A1");
   #pragma EVE_REG("AddrIn", "A2");
   #pragma EVE_REG("AddrXval", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("i", "I3");
   #pragma EVE_REG("j", "I4");
   

   __vcop_vloop(__vcop_compute(), 30u, 16u, 3u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(6), _VREG(39));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(8), _VREG(36));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(10), _VREG(38));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(12), _VREG(35));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(24), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(25), _PREG(26), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(27), _PREG(28), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(30), _AGEN(0), _VREG(21), __vcop_once());
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(32), _AGEN(1), _VREG(30), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(14), _AGEN(2), _VREG(33), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(16), _AGEN(3), _VREG(40), __vcop_alws());
   __vcop_vbitpk(_VREG(33), _VREG(22), _VREG(31));
   __vcop_vadd(_VREG(40), _VREG(16), _VREG(41));
   __vcop_vadd(_VREG(30), _VREG(17), _VREG(42));
   __vcop_vbitc(_VREG(31), _VREG(37));
   __vcop_vbitunpk(_VREG(31), _VREG(23), _VREG(34));
   __vcop_vadd(_VREG(21), _VREG(37), _VREG(21));
   __vcop_vcmpgt(_VREG(21), _VREG(35), _VREG(32));
   __vcop_vshf(_VREG(41), _VREG(38), _VREG(41));
   __vcop_vand(_VREG(32), _VREG(36), _VREG(32));
   __vcop_vshf(_VREG(42), _VREG(38), _VREG(42));
   __vcop_vsel(_VREG(32), _VREG(39), _VREG(36));
   __vcop_vmin(_VREG(21), _VREG(35), _VREG(21));
   __vcop_vexitnz(__vcop_level_vloop(), _VREG(32));
   __vcop_vstore(__vcop_predicate(_VREG(34)), __vcop_sizeHU(), __vcop_collat(), __vcop_alws(), _VREG(41), _PREG(18), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_predicate(_VREG(34)), __vcop_sizeHU(), __vcop_collat(), __vcop_alws(), _VREG(42), _PREG(20), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_1pt(), __vcop_alws(), _VREG(21), _PREG(30), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_1pt(), __vcop_alws(), _VREG(21), _PREG(22), _AGEN(0), _PREG(0));
   __vcop_vloop_end(3u);

}

void vcop_generateList(
   __vptr_uint8 pIn,
   __vptr_uint8 pEndRowPadVal,
   __vptr_uint16 pXval,
   __vptr_uint16 pYval,
   __vptr_uint16 pBlockX,
   __vptr_uint16 pBlockY,
   unsigned short numHorzBlock,
   unsigned short numVertBlock,
   __vptr_uint16 pListX,
   __vptr_uint16 pListY,
   __vptr_uint16 pNumElmtsX,
   __vptr_uint16 pNumElmtsY,
   unsigned short maxNumElmts,
   unsigned short width,
   unsigned short height,
   unsigned short inStride,
   unsigned char qShift)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_generateList_init(pIn, pEndRowPadVal, pXval, pYval, pBlockX, pBlockY, numHorzBlock, numVertBlock, pListX, pListY, pNumElmtsX, pNumElmtsY, maxNumElmts, width, height, inStride, qShift, __pblock_vcop_generateList);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_generateList_vloops(__pblock_vcop_generateList);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_generateList_custom(
   __vptr_uint8 pIn,
   __vptr_uint8 pEndRowPadVal,
   __vptr_uint16 pXval,
   __vptr_uint16 pYval,
   __vptr_uint16 pBlockX,
   __vptr_uint16 pBlockY,
   unsigned short numHorzBlock,
   unsigned short numVertBlock,
   __vptr_uint16 pListX,
   __vptr_uint16 pListY,
   __vptr_uint16 pNumElmtsX,
   __vptr_uint16 pNumElmtsY,
   unsigned short maxNumElmts,
   unsigned short width,
   unsigned short height,
   unsigned short inStride,
   unsigned char qShift,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_generateList_init(pIn, pEndRowPadVal, pXval, pYval, pBlockX, pBlockY, numHorzBlock, numVertBlock, pListX, pListY, pNumElmtsX, pNumElmtsY, maxNumElmts, width, height, inStride, qShift, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_generateList_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_updateGenerateList, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_updateGenerateList, __ALIGNOF__(int));
unsigned short __pblock_vcop_updateGenerateList[16];

unsigned int vcop_updateGenerateList_param_count(void)
{
   return 16u;
}

unsigned int vcop_updateGenerateList_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_updateGenerateList_init(
   __vptr_uint32 preg,
   unsigned int pListX,
   unsigned int pListY,
   __vptr_uint16 pNumElmtsX,
   unsigned short listXOfst,
   unsigned short listYOfst,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (1)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), pListY);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pNumElmtsX);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)preg+listXOfst*sizeof(*preg));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)preg+listYOfst*sizeof(*preg));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), pListX);
   __offset += 16;

   return 16u;
}

void vcop_updateGenerateList_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("vConst0", 16);
   #pragma VCC_VREG("vFlag", 17);
   #pragma VCC_VREG("vListX", 18);
   #pragma VCC_VREG("vListY", 19);
   #pragma VCC_VREG("vMaxNumElmts", 20);
   #pragma VCC_VREG("vNumElmts", 21);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("i", "I4");
   

   __vcop_vloop(__vcop_compute(), 12u, 8u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(14), _VREG(16));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(16), _VREG(18));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(6), _VREG(19));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(8), _AGEN(0), _VREG(21), __vcop_once());
   __vcop_vadd(_VREG(18), _VREG(21), _VREG(18));
   __vcop_vadd(_VREG(19), _VREG(21), _VREG(19));
   __vcop_vadd(_VREG(18), _VREG(21), _VREG(18));
   __vcop_vadd(_VREG(19), _VREG(21), _VREG(19));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_1pt(), __vcop_alws(), _VREG(18), _PREG(10), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_1pt(), __vcop_alws(), _VREG(19), _PREG(12), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_updateGenerateList(
   __vptr_uint32 preg,
   unsigned int pListX,
   unsigned int pListY,
   __vptr_uint16 pNumElmtsX,
   unsigned short listXOfst,
   unsigned short listYOfst)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_updateGenerateList_init(preg, pListX, pListY, pNumElmtsX, listXOfst, listYOfst, __pblock_vcop_updateGenerateList);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_updateGenerateList_vloops(__pblock_vcop_updateGenerateList);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_updateGenerateList_custom(
   __vptr_uint32 preg,
   unsigned int pListX,
   unsigned int pListY,
   __vptr_uint16 pNumElmtsX,
   unsigned short listXOfst,
   unsigned short listYOfst,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_updateGenerateList_init(preg, pListX, pListY, pNumElmtsX, listXOfst, listYOfst, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_updateGenerateList_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_copyListToOutBuff, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_copyListToOutBuff, __ALIGNOF__(int));
unsigned short __pblock_vcop_copyListToOutBuff[22];

unsigned int vcop_copyListToOutBuff_param_count(void)
{
   return 22u;
}

unsigned int vcop_copyListToOutBuff_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_copyListToOutBuff_init(
   __vptr_uint16 pListX,
   __vptr_uint16 pListY,
   __vptr_uint16 pListXY,
   __vptr_uint16 pNumElmts,
   __vptr_uint16 pNumElmtsOut,
   unsigned short NumElmts,
   unsigned short offsetX,
   unsigned short offsetY,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (NumElmts/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pNumElmts);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pListX);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pListY);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pListXY);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pNumElmtsOut);
   __vcop_pblock_init16(pblock, __offset+_PREG(16), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(17),  -(8u*sizeof(*pListX))*((NumElmts/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(18), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(19),  -(8u*sizeof(*pListX)*2)*((NumElmts/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), offsetX);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), offsetY);
   __offset += 22;

   return 22u;
}

void vcop_copyListToOutBuff_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("vIn", 16);
   #pragma VCC_VREG("vListX", 17);
   #pragma VCC_VREG("vListY", 18);
   #pragma VCC_VREG("vListYout", 19);
   #pragma VCC_VREG("voffsetX", 20);
   #pragma VCC_VREG("voffsetY", 21);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   #pragma EVE_REG("Addr1", "A1");
   #pragma EVE_REG("Addr2", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("j", "I3");
   #pragma EVE_REG("i", "I4");
   

   __vcop_vloop(__vcop_compute(), 13u, 11u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(20), _VREG(20));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(22), _VREG(21));
   __vcop_vagen(_AGEN(0), _PREG(16), _PREG(17), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(18), _PREG(19), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(6), _AGEN(2), _VREG(16), __vcop_once());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(8), _AGEN(0), _VREG(17), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(10), _AGEN(0), _VREG(18), __vcop_alws());
   __vcop_vadd(_VREG(17), _VREG(20), _VREG(17));
   __vcop_vadd(_VREG(18), _VREG(21), _VREG(19));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(17,19), _PREG(12), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_1pt(), __vcop_last_i4(), _VREG(16), _PREG(14), _AGEN(2), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_copyListToOutBuff(
   __vptr_uint16 pListX,
   __vptr_uint16 pListY,
   __vptr_uint16 pListXY,
   __vptr_uint16 pNumElmts,
   __vptr_uint16 pNumElmtsOut,
   unsigned short NumElmts,
   unsigned short offsetX,
   unsigned short offsetY)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_copyListToOutBuff_init(pListX, pListY, pListXY, pNumElmts, pNumElmtsOut, NumElmts, offsetX, offsetY, __pblock_vcop_copyListToOutBuff);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_copyListToOutBuff_vloops(__pblock_vcop_copyListToOutBuff);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_copyListToOutBuff_custom(
   __vptr_uint16 pListX,
   __vptr_uint16 pListY,
   __vptr_uint16 pListXY,
   __vptr_uint16 pNumElmts,
   __vptr_uint16 pNumElmtsOut,
   unsigned short NumElmts,
   unsigned short offsetX,
   unsigned short offsetY,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_copyListToOutBuff_init(pListX, pListY, pListXY, pNumElmts, pNumElmtsOut, NumElmts, offsetX, offsetY, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_copyListToOutBuff_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_copyNumElementsToOutBuff_init, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_copyNumElementsToOutBuff_init, __ALIGNOF__(int));
unsigned short __pblock_vcop_copyNumElementsToOutBuff_init[8];

unsigned int vcop_copyNumElementsToOutBuff_init_param_count(void)
{
   return 8u;
}

unsigned int vcop_copyNumElementsToOutBuff_init_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_copyNumElementsToOutBuff_init_init(
   __vptr_uint16 src,
   __vptr_uint16 dst,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (1)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)src);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)dst);
   __offset += 8;

   return 8u;
}

void vcop_copyNumElementsToOutBuff_init_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("vIn", 16);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("i", "I4");
   

   __vcop_vloop(__vcop_compute(), 4u, 4u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(6), _AGEN(0), _VREG(16), __vcop_once());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_1pt(), __vcop_alws(), _VREG(16), _PREG(8), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_copyNumElementsToOutBuff_init(
   __vptr_uint16 src,
   __vptr_uint16 dst)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_copyNumElementsToOutBuff_init_init(src, dst, __pblock_vcop_copyNumElementsToOutBuff_init);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_copyNumElementsToOutBuff_init_vloops(__pblock_vcop_copyNumElementsToOutBuff_init);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_copyNumElementsToOutBuff_init_custom(
   __vptr_uint16 src,
   __vptr_uint16 dst,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_copyNumElementsToOutBuff_init_init(src, dst, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_copyNumElementsToOutBuff_init_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

