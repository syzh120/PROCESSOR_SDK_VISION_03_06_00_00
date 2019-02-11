#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_bilinearInterpolateUV, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_bilinearInterpolateUV, __ALIGNOF__(int));
unsigned short __pblock_vcop_bilinearInterpolateUV[56];

unsigned int vcop_bilinearInterpolateUV_param_count(void)
{
   return 56u;
}

unsigned int vcop_bilinearInterpolateUV_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_bilinearInterpolateUV_init(
   __vptr_uint8 src,
   __vptr_uint8 dst,
   unsigned short outputBlockSize,
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 fracArray,
   __vptr_uint16 scratch,
   __vptr_uint8 scratchHbuf,
   unsigned short stride,
   unsigned int inSize,
   __vptr_uint8 inLUT,
   unsigned char mnQShift,
   unsigned char oQShift,
   unsigned short qScale,
   unsigned char mult,
   unsigned char rightShift,
   long sat_high,
   long sat_high_set,
   long sat_low,
   long sat_low_set,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((inSize) + 2U*(8u)-1U) & ~(2U*(8u)-1U))/(2*(8u)))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)inLUT);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)inLUT+16);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), 16);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)src);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)src+stride);
   __offset += 14;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (outputBlockSize)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)scratchHbuf);
   __vcop_pblock_init16(pblock, __offset+_PREG(8), 2);
   __vcop_pblock_init16(pblock, __offset+_PREG(9), 8);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)tluIndexArray);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)inLUT);
   __offset += 12;

   /* Loop 3 PREGS */
   const int preg_ref1 = _PREG(22);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((outputBlockSize) + (8u)-1U) & ~((8u)-1U))/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_4PARAM,preg_ref1,RM_ROUND,mnQShift+oQShift));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 8);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), -4);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)fracArray);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)scratchHbuf);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)scratchHbuf+16);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)scratchHbuf+32);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)scratchHbuf+48);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)dst);
   __vcop_pblock_4param_init(pblock, __offset+_PREG(22), sat_high,sat_high_set,sat_low,sat_low_set);
   __vcop_pblock_init16(pblock, __offset+_PREG(26), 64);
   __vcop_pblock_init16(pblock, __offset+_PREG(27), 16);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), qScale);
   __vcop_pblock_init32(pblock, __offset+_PREG(30), 0x000000000F);
   __offset += 30;

   return 56u;
}

void vcop_bilinearInterpolateUV_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("first_0", 16);
   #pragma VCC_VREG("first_1", 17);
   #pragma VCC_VREG("in_0", 18);
   #pragma VCC_VREG("in_1", 19);
   #pragma VCC_VREG("in_2", 20);
   #pragma VCC_VREG("in_3", 21);
   #pragma VCC_VREG("in_4", 22);
   #pragma VCC_VREG("in_5", 23);
   #pragma VCC_VREG("in_6", 24);
   #pragma VCC_VREG("in_7", 25);
   #pragma VCC_VREG("v_qScale", 26);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   #pragma EVE_REG("Addr1", "A1");
   #pragma EVE_REG("Addr2", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 8u, 7u, 1u);
   __vcop_vagen(_AGEN(1), _PREG(10), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(11), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(12), _AGEN(2), _VPAIR(18,19), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(14), _AGEN(2), _VPAIR(20,21), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(18,19), _PREG(6), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(20,21), _PREG(8), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vdata", 27);
   #pragma VCC_VREG("Vindex", 28);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("TLU_agen", "A1");
   #pragma EVE_REG("ind_agen", "A0");
   #pragma EVE_REG("out_agen", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_tablelkup(), 7u, 6u, 2u);
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(0), _PREG(8), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(9), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(10), _AGEN(0), _VREG(28), __vcop_alws());
   __vcop_vtbload(__vcop_sizeBU(), __vcop_tableinfo(2, 4), _PREG(12), _AGEN(1), _VREG(28), _VREG(27), _PREG(0), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(27), _PREG(6), _AGEN(2), _PREG(0));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vmaskx", 29);
   #pragma VCC_VREG("Vmasky", 30);
   #pragma VCC_VREG("Vshiftx", 31);
   #pragma VCC_VREG("Vshifty", 32);
   #pragma VCC_VREG("fracMap", 33);
   #pragma VCC_VREG("pix00", 34);
   #pragma VCC_VREG("pix01", 35);
   #pragma VCC_VREG("pix10", 36);
   #pragma VCC_VREG("pix11", 37);
   #pragma VCC_VREG("qScale_xFrac", 38);
   #pragma VCC_VREG("qScale_yFrac", 39);
   #pragma VCC_VREG("temp1", 40);
   #pragma VCC_VREG("temp2", 41);
   #pragma VCC_VREG("xFrac", 42);
   #pragma VCC_VREG("yFrac", 43);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   #pragma EVE_REG("Addr1", "A1");
   #pragma EVE_REG("Addr2", "A2");
   #pragma EVE_REG("Addr_out", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 56u, 15u, 3u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(28), _VREG(26));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(30), _VREG(29));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(8), _VREG(32));
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(26), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(27), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(10), _AGEN(1), _VREG(33), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(12), _AGEN(2), _VPAIR(18,19), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(14), _AGEN(2), _VPAIR(20,21), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(16), _AGEN(2), _VPAIR(22,23), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_dintrlv(), _PREG(18), _AGEN(2), _VPAIR(24,25), __vcop_alws());
   __vcop_vmove(_VREG(18), _VREG(18));
   __vcop_vmove(_VREG(20), _VREG(20));
   __vcop_vdintrlv(_VREG(18), _VREG(20));
   __vcop_vmove(_VREG(22), _VREG(22));
   __vcop_vmove(_VREG(24), _VREG(24));
   __vcop_vdintrlv(_VREG(22), _VREG(24));
   __vcop_vmove(_VREG(18), _VREG(18));
   __vcop_vmove(_VREG(22), _VREG(22));
   __vcop_vdintrlv(_VREG(18), _VREG(22));
   __vcop_vmove(_VREG(20), _VREG(20));
   __vcop_vmove(_VREG(24), _VREG(24));
   __vcop_vdintrlv(_VREG(20), _VREG(24));
   __vcop_vmove(_VREG(19), _VREG(19));
   __vcop_vmove(_VREG(21), _VREG(21));
   __vcop_vdintrlv(_VREG(19), _VREG(21));
   __vcop_vmove(_VREG(23), _VREG(23));
   __vcop_vmove(_VREG(25), _VREG(25));
   __vcop_vdintrlv(_VREG(23), _VREG(25));
   __vcop_vmove(_VREG(19), _VREG(19));
   __vcop_vmove(_VREG(23), _VREG(23));
   __vcop_vdintrlv(_VREG(19), _VREG(23));
   __vcop_vmove(_VREG(21), _VREG(21));
   __vcop_vmove(_VREG(25), _VREG(25));
   __vcop_vdintrlv(_VREG(21), _VREG(25));
   __vcop_vand(_VREG(33), _VREG(29), _VREG(42));
   __vcop_vshf(_VREG(33), _VREG(32), _VREG(43));
   __vcop_vmpy(_VREG(42), _VREG(20), _VREG(40), _PREG(0));
   __vcop_vmpy(_VREG(42), _VREG(24), _VREG(41), _PREG(0));
   __vcop_vsub(_VREG(26), _VREG(42), _VREG(38));
   __vcop_vsub(_VREG(26), _VREG(43), _VREG(39));
   __vcop_vmadd(_VREG(38), _VREG(18), _VREG(40), _PREG(0));
   __vcop_vmadd(_VREG(38), _VREG(22), _VREG(41), _PREG(0));
   __vcop_vmpy(_VREG(39), _VREG(40), _VREG(40), _PREG(0));
   __vcop_vmpy(_VREG(43), _VREG(41), _VREG(41), _PREG(0));
   __vcop_vadd(_VREG(40), _VREG(41), _VREG(18));
   __vcop_vmpy(_VREG(42), _VREG(21), _VREG(40), _PREG(0));
   __vcop_vmpy(_VREG(42), _VREG(25), _VREG(41), _PREG(0));
   __vcop_vmadd(_VREG(38), _VREG(19), _VREG(40), _PREG(0));
   __vcop_vmadd(_VREG(38), _VREG(23), _VREG(41), _PREG(0));
   __vcop_vmpy(_VREG(39), _VREG(40), _VREG(40), _PREG(0));
   __vcop_vmpy(_VREG(43), _VREG(41), _VREG(41), _PREG(0));
   __vcop_vadd(_VREG(40), _VREG(41), _VREG(19));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(18,19), _PREG(20), _AGEN(3), _PREG(6));
   __vcop_vloop_end(3u);

}

void vcop_bilinearInterpolateUV(
   __vptr_uint8 src,
   __vptr_uint8 dst,
   unsigned short outputBlockSize,
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 fracArray,
   __vptr_uint16 scratch,
   __vptr_uint8 scratchHbuf,
   unsigned short stride,
   unsigned int inSize,
   __vptr_uint8 inLUT,
   unsigned char mnQShift,
   unsigned char oQShift,
   unsigned short qScale,
   unsigned char mult,
   unsigned char rightShift,
   long sat_high,
   long sat_high_set,
   long sat_low,
   long sat_low_set)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_bilinearInterpolateUV_init(src, dst, outputBlockSize, tluIndexArray, fracArray, scratch, scratchHbuf, stride, inSize, inLUT, mnQShift, oQShift, qScale, mult, rightShift, sat_high, sat_high_set, sat_low, sat_low_set, __pblock_vcop_bilinearInterpolateUV);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_bilinearInterpolateUV_vloops(__pblock_vcop_bilinearInterpolateUV);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_bilinearInterpolateUV_custom(
   __vptr_uint8 src,
   __vptr_uint8 dst,
   unsigned short outputBlockSize,
   __vptr_uint16 tluIndexArray,
   __vptr_uint8 fracArray,
   __vptr_uint16 scratch,
   __vptr_uint8 scratchHbuf,
   unsigned short stride,
   unsigned int inSize,
   __vptr_uint8 inLUT,
   unsigned char mnQShift,
   unsigned char oQShift,
   unsigned short qScale,
   unsigned char mult,
   unsigned char rightShift,
   long sat_high,
   long sat_high_set,
   long sat_low,
   long sat_low_set,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_bilinearInterpolateUV_init(src, dst, outputBlockSize, tluIndexArray, fracArray, scratch, scratchHbuf, stride, inSize, inLUT, mnQShift, oQShift, qScale, mult, rightShift, sat_high, sat_high_set, sat_low, sat_low_set, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_bilinearInterpolateUV_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

