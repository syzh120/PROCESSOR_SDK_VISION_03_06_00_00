#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_calc_new_lk_xy, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_calc_new_lk_xy, __ALIGNOF__(int));
unsigned short __pblock_vcop_calc_new_lk_xy[70];

unsigned int vcop_calc_new_lk_xy_param_count(void)
{
   return 70u;
}

unsigned int vcop_calc_new_lk_xy_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_calc_new_lk_xy_init(
   __vptr_uint16 IxItL_a,
   __vptr_uint16 IyItL_b,
   __vptr_int16 IxItH_a,
   __vptr_int16 IyItH_b,
   __vptr_int16 Ix2_a,
   __vptr_int16 Iy2_b,
   __vptr_int16 Ixy_c,
   __vptr_int16 X_c,
   __vptr_int16 Y_c,
   __vptr_int16 localXY_b,
   __vptr_int16 frameXY_b,
   __vptr_uint16 numValidPoints,
   __vptr_uint8 currValidPoints,
   __vptr_uint32 pBaseAddrList,
   __vptr_uint32 pValidAddrList,
   __vptr_uint32 pOutAddrList,
   __vptr_uint32 pValidOutAddrList,
   __vptr_int32 vx,
   __vptr_int32 vy,
   unsigned short qFormatePel,
   unsigned short minErrValue,
   unsigned char searchRange,
   unsigned short n,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (n/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)IxItL_a);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)IyItL_b);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)IxItH_a);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)IyItH_b);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)Iy2_b);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)Ixy_c);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)Ix2_a);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)vx);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)vy);
   __vcop_pblock_init16(pblock, __offset+_PREG(24), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(25), 16);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), 4294967295);
   __offset += 28;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (n/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), minErrValue >> ((10) - qFormatePel));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)vx);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)vy);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)localXY_b);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)frameXY_b);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)currValidPoints);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pBaseAddrList);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)pOutAddrList);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)X_c);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)Y_c);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)pValidAddrList);
   __vcop_pblock_init32(pblock, __offset+_PREG(30), (uchar *)pValidOutAddrList);
   __vcop_pblock_init32(pblock, __offset+_PREG(32), (uchar *)numValidPoints);
   __vcop_pblock_init16(pblock, __offset+_PREG(34), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(35),  -(4*8u)*((n/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(36), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(37),  -(2*8u)*((n/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(38), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(39),  -(8u)*((n/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(40), (((7)/2+1) << qFormatePel));
   __vcop_pblock_init32(pblock, __offset+_PREG(42), (((searchRange*2) + (7)- (7)/2 -2) << qFormatePel));
   __offset += 42;

   return 70u;
}

void vcop_calc_new_lk_xy_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vec0", 16);
   #pragma VCC_VREG("Vec1", 17);
   #pragma VCC_VREG("Vec10", 18);
   #pragma VCC_VREG("Vec11", 19);
   #pragma VCC_VREG("Vec12", 20);
   #pragma VCC_VREG("Vec13", 21);
   #pragma VCC_VREG("Vec14", 22);
   #pragma VCC_VREG("Vec15", 23);
   #pragma VCC_VREG("Vec2", 24);
   #pragma VCC_VREG("Vec3", 25);
   #pragma VCC_VREG("Vec4", 26);
   #pragma VCC_VREG("Vec5", 27);
   #pragma VCC_VREG("Vec6", 28);
   #pragma VCC_VREG("Vec7", 29);
   #pragma VCC_VREG("Vec8", 30);
   #pragma VCC_VREG("Vec9", 31);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr1", "A0");
   #pragma EVE_REG("Addr2", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 51u, 14u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(26), _VREG(21));
   __vcop_vinit(__vcop_sizeWU(), __vcop_once(), _PREG(28), _VREG(23));
   __vcop_vagen(_AGEN(0), _PREG(24), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(6), _AGEN(0), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(8), _AGEN(0), _VREG(24), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_ds2(), _PREG(10), _AGEN(0), _VREG(30), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_ds2(), _PREG(12), _AGEN(0), _VREG(22), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(14), _AGEN(0), _VPAIR(26,27), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(16), _AGEN(0), _VPAIR(28,29), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(18), _AGEN(0), _VPAIR(18,19), __vcop_alws());
   __vcop_vmpy(_VREG(30), _VREG(26), _VREG(17), _PREG(0));
   __vcop_vmpy(_VREG(16), _VREG(26), _VREG(25), _PREG(0));
   __vcop_vshf16(_VREG(17), _VREG(31), _VREG(26));
   __vcop_vadd(_VREG(25), _VREG(31), _VREG(25));
   __vcop_vaddh(_VREG(26), _VREG(25), _VREG(17));
   __vcop_vand(_VREG(25), _VREG(23), _VREG(25));
   __vcop_vshf(_VREG(25), _VREG(27), _VREG(25));
   __vcop_vadd(_VREG(27), _VREG(21), _VREG(27));
   __vcop_vshfor(_VREG(17), _VREG(27), _VREG(25));
   __vcop_vmpy(_VREG(22), _VREG(18), _VREG(17), _PREG(0));
   __vcop_vmpy(_VREG(24), _VREG(18), _VREG(27), _PREG(0));
   __vcop_vshf16(_VREG(17), _VREG(31), _VREG(18));
   __vcop_vadd(_VREG(27), _VREG(31), _VREG(27));
   __vcop_vaddh(_VREG(18), _VREG(27), _VREG(17));
   __vcop_vand(_VREG(27), _VREG(23), _VREG(27));
   __vcop_vshf(_VREG(27), _VREG(19), _VREG(27));
   __vcop_vadd(_VREG(19), _VREG(21), _VREG(19));
   __vcop_vshfor(_VREG(17), _VREG(19), _VREG(27));
   __vcop_vmpy(_VREG(22), _VREG(28), _VREG(17), _PREG(0));
   __vcop_vmpy(_VREG(24), _VREG(28), _VREG(18), _PREG(0));
   __vcop_vshf16(_VREG(17), _VREG(31), _VREG(26));
   __vcop_vadd(_VREG(18), _VREG(31), _VREG(18));
   __vcop_vaddh(_VREG(26), _VREG(18), _VREG(17));
   __vcop_vand(_VREG(18), _VREG(23), _VREG(18));
   __vcop_vshf(_VREG(18), _VREG(29), _VREG(18));
   __vcop_vadd(_VREG(29), _VREG(21), _VREG(24));
   __vcop_vshfor(_VREG(17), _VREG(24), _VREG(18));
   __vcop_vsub(_VREG(25), _VREG(18), _VREG(19));
   __vcop_vmpy(_VREG(30), _VREG(28), _VREG(17), _PREG(0));
   __vcop_vmpy(_VREG(16), _VREG(28), _VREG(25), _PREG(0));
   __vcop_vshf16(_VREG(17), _VREG(31), _VREG(26));
   __vcop_vadd(_VREG(25), _VREG(31), _VREG(25));
   __vcop_vaddh(_VREG(26), _VREG(25), _VREG(17));
   __vcop_vand(_VREG(25), _VREG(23), _VREG(25));
   __vcop_vshf(_VREG(25), _VREG(29), _VREG(25));
   __vcop_vshfor(_VREG(17), _VREG(24), _VREG(25));
   __vcop_vsub(_VREG(27), _VREG(25), _VREG(18));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(19), _PREG(20), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(18), _PREG(22), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   #pragma EVE_REG("Addr1", "A1");
   #pragma EVE_REG("Addr2", "A2");
   #pragma EVE_REG("Addr3", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 57u, 21u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(40), _VREG(17));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(42), _VREG(25));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(6), _VREG(31));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(6), _VREG(23));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(8), _VREG(21));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(34), _PREG(35), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(38), _PREG(39), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(10), _AGEN(1), _VREG(22), __vcop_alws());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(12), _AGEN(1), _VREG(24), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(14), _AGEN(1), _VPAIR(26,27), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(16), _AGEN(1), _VPAIR(28,29), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(18), _AGEN(3), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(20), _AGEN(1), _VREG(30), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(22), _AGEN(1), _VREG(18), __vcop_alws());
   __vcop_vmpy(_VREG(16), _VREG(24), _VREG(24), _PREG(0));
   __vcop_vmpy(_VREG(16), _VREG(22), _VREG(22), _PREG(0));
   __vcop_vcmplt(_VREG(26), _VREG(17), _VREG(19));
   __vcop_vcmplt(_VREG(27), _VREG(17), _VREG(20));
   __vcop_vor(_VREG(19), _VREG(20), _VREG(20));
   __vcop_vcmpge(_VREG(26), _VREG(25), _VREG(19));
   __vcop_vcmpge(_VREG(27), _VREG(25), _VREG(16));
   __vcop_vor(_VREG(19), _VREG(16), _VREG(19));
   __vcop_vor(_VREG(19), _VREG(20), _VREG(20));
   __vcop_vsel(_VREG(20), _VREG(31), _VREG(22));
   __vcop_vsel(_VREG(20), _VREG(31), _VREG(24));
   __vcop_vsub(_VREG(31), _VREG(17), _VREG(16));
   __vcop_vcmple(_VREG(24), _VREG(16), _VREG(19));
   __vcop_vsel(_VREG(19), _VREG(16), _VREG(24));
   __vcop_vcmpge(_VREG(24), _VREG(17), _VREG(19));
   __vcop_vsel(_VREG(19), _VREG(17), _VREG(24));
   __vcop_vcmple(_VREG(22), _VREG(16), _VREG(19));
   __vcop_vsel(_VREG(19), _VREG(16), _VREG(22));
   __vcop_vcmpge(_VREG(22), _VREG(17), _VREG(19));
   __vcop_vsel(_VREG(19), _VREG(17), _VREG(22));
   __vcop_vadd(_VREG(26), _VREG(22), _VREG(26));
   __vcop_vadd(_VREG(27), _VREG(24), _VREG(27));
   __vcop_vadd(_VREG(28), _VREG(22), _VREG(28));
   __vcop_vadd(_VREG(29), _VREG(24), _VREG(29));
   __vcop_vabs(_VREG(22), _VREG(22));
   __vcop_vabs(_VREG(24), _VREG(24));
   __vcop_vcmpgt(_VREG(22), _VREG(21), _VREG(20));
   __vcop_vcmpgt(_VREG(24), _VREG(21), _VREG(19));
   __vcop_vor(_VREG(20), _VREG(19), _VREG(16));
   __vcop_vbittr(_VREG(16), _VREG(20));
   __vcop_vbitc(_VREG(20), _VREG(20));
   __vcop_vadd(_VREG(23), _VREG(20), _VREG(23));
   __vcop_vstore(__vcop_predicate(_VREG(16)), __vcop_sizeH(), __vcop_collat(), __vcop_alws(), _VREG(26), _PREG(24), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_predicate(_VREG(16)), __vcop_sizeH(), __vcop_collat(), __vcop_alws(), _VREG(27), _PREG(26), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_predicate(_VREG(16)), __vcop_sizeWU(), __vcop_collat(), __vcop_alws(), _VREG(30), _PREG(28), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_predicate(_VREG(16)), __vcop_sizeWU(), __vcop_collat(), __vcop_alws(), _VREG(18), _PREG(30), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_alws(), _VPAIR(28,29), _PREG(16), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_alws(), _VPAIR(26,27), _PREG(14), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(16), _PREG(18), _AGEN(3), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_1pt(), __vcop_last_i4(), _VREG(23), _PREG(32), _AGEN(0), _PREG(0));
   __vcop_vloop_end(2u);

}

void vcop_calc_new_lk_xy(
   __vptr_uint16 IxItL_a,
   __vptr_uint16 IyItL_b,
   __vptr_int16 IxItH_a,
   __vptr_int16 IyItH_b,
   __vptr_int16 Ix2_a,
   __vptr_int16 Iy2_b,
   __vptr_int16 Ixy_c,
   __vptr_int16 X_c,
   __vptr_int16 Y_c,
   __vptr_int16 localXY_b,
   __vptr_int16 frameXY_b,
   __vptr_uint16 numValidPoints,
   __vptr_uint8 currValidPoints,
   __vptr_uint32 pBaseAddrList,
   __vptr_uint32 pValidAddrList,
   __vptr_uint32 pOutAddrList,
   __vptr_uint32 pValidOutAddrList,
   __vptr_int32 vx,
   __vptr_int32 vy,
   unsigned short qFormatePel,
   unsigned short minErrValue,
   unsigned char searchRange,
   unsigned short n)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_calc_new_lk_xy_init(IxItL_a, IyItL_b, IxItH_a, IyItH_b, Ix2_a, Iy2_b, Ixy_c, X_c, Y_c, localXY_b, frameXY_b, numValidPoints, currValidPoints, pBaseAddrList, pValidAddrList, pOutAddrList, pValidOutAddrList, vx, vy, qFormatePel, minErrValue, searchRange, n, __pblock_vcop_calc_new_lk_xy);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_calc_new_lk_xy_vloops(__pblock_vcop_calc_new_lk_xy);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_calc_new_lk_xy_custom(
   __vptr_uint16 IxItL_a,
   __vptr_uint16 IyItL_b,
   __vptr_int16 IxItH_a,
   __vptr_int16 IyItH_b,
   __vptr_int16 Ix2_a,
   __vptr_int16 Iy2_b,
   __vptr_int16 Ixy_c,
   __vptr_int16 X_c,
   __vptr_int16 Y_c,
   __vptr_int16 localXY_b,
   __vptr_int16 frameXY_b,
   __vptr_uint16 numValidPoints,
   __vptr_uint8 currValidPoints,
   __vptr_uint32 pBaseAddrList,
   __vptr_uint32 pValidAddrList,
   __vptr_uint32 pOutAddrList,
   __vptr_uint32 pValidOutAddrList,
   __vptr_int32 vx,
   __vptr_int32 vy,
   unsigned short qFormatePel,
   unsigned short minErrValue,
   unsigned char searchRange,
   unsigned short n,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_calc_new_lk_xy_init(IxItL_a, IyItL_b, IxItH_a, IyItH_b, Ix2_a, Iy2_b, Ixy_c, X_c, Y_c, localXY_b, frameXY_b, numValidPoints, currValidPoints, pBaseAddrList, pValidAddrList, pOutAddrList, pValidOutAddrList, vx, vy, qFormatePel, minErrValue, searchRange, n, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_calc_new_lk_xy_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

