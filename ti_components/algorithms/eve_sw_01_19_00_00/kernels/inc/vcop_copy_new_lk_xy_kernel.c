#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_copy_new_lk_xy, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_copy_new_lk_xy, __ALIGNOF__(int));
unsigned short __pblock_vcop_copy_new_lk_xy[30];

unsigned int vcop_copy_new_lk_xy_param_count(void)
{
   return 30u;
}

unsigned int vcop_copy_new_lk_xy_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_copy_new_lk_xy_init(
   __vptr_int16 pInput_A,
   __vptr_int16 pOutput_B,
   __vptr_uint8 currValidPoints,
   __vptr_uint32 pBaseAddrList,
   __vptr_uint32 pValidAddrList,
   __vptr_uint32 pOutAddrList,
   __vptr_uint32 pValidOutAddrList,
   __vptr_int16 pLocalX,
   __vptr_int16 pLocalY,
   __vptr_int16 pLocalXY,
   unsigned short numKeyPoints,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((numKeyPoints+(8u)-1)/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pBaseAddrList);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pOutAddrList);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pLocalXY);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pValidAddrList);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pValidOutAddrList);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)currValidPoints);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pLocalX);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pLocalY);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)pOutput_B);
   __vcop_pblock_init16(pblock, __offset+_PREG(24), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(25), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(26), 16);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), 1);
   __vcop_pblock_init32(pblock, __offset+_PREG(30), (uchar *)pInput_A);
   __offset += 30;

   return 30u;
}

void vcop_copy_new_lk_xy_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vconst1", 16);
   #pragma VCC_VREG("Veven", 17);
   #pragma VCC_VREG("Vevenlocalxy", 18);
   #pragma VCC_VREG("Vodd", 19);
   #pragma VCC_VREG("Voddlocalxy", 20);
   #pragma VCC_VREG("Vsrc1", 21);
   #pragma VCC_VREG("Vsrc2", 22);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("AddrIn", "A0");
   #pragma EVE_REG("AddrOut", "A1");
   #pragma EVE_REG("AddrValidAdrs", "A2");
   #pragma EVE_REG("AddrValidPts", "A3");
   #pragma EVE_REG("AddrXYLocal", "A4");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 17u, 15u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(28), _VREG(16));
   __vcop_vagen(_AGEN(0), _PREG(24), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(24), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(24), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(25), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(4), _PREG(26), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(30), _AGEN(0), _VPAIR(17,19), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(6), _AGEN(2), _VREG(21), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(8), _AGEN(2), _VREG(22), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(10), _AGEN(0), _VPAIR(18,20), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(21), _PREG(12), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(22), _PREG(14), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(16), _PREG(16), _AGEN(3), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_npt(), __vcop_alws(), _VREG(18), _PREG(18), _AGEN(4), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_npt(), __vcop_alws(), _VREG(20), _PREG(20), _AGEN(4), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_alws(), _VPAIR(17,19), _PREG(22), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_copy_new_lk_xy(
   __vptr_int16 pInput_A,
   __vptr_int16 pOutput_B,
   __vptr_uint8 currValidPoints,
   __vptr_uint32 pBaseAddrList,
   __vptr_uint32 pValidAddrList,
   __vptr_uint32 pOutAddrList,
   __vptr_uint32 pValidOutAddrList,
   __vptr_int16 pLocalX,
   __vptr_int16 pLocalY,
   __vptr_int16 pLocalXY,
   unsigned short numKeyPoints)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_copy_new_lk_xy_init(pInput_A, pOutput_B, currValidPoints, pBaseAddrList, pValidAddrList, pOutAddrList, pValidOutAddrList, pLocalX, pLocalY, pLocalXY, numKeyPoints, __pblock_vcop_copy_new_lk_xy);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_copy_new_lk_xy_vloops(__pblock_vcop_copy_new_lk_xy);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_copy_new_lk_xy_custom(
   __vptr_int16 pInput_A,
   __vptr_int16 pOutput_B,
   __vptr_uint8 currValidPoints,
   __vptr_uint32 pBaseAddrList,
   __vptr_uint32 pValidAddrList,
   __vptr_uint32 pOutAddrList,
   __vptr_uint32 pValidOutAddrList,
   __vptr_int16 pLocalX,
   __vptr_int16 pLocalY,
   __vptr_int16 pLocalXY,
   unsigned short numKeyPoints,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_copy_new_lk_xy_init(pInput_A, pOutput_B, currValidPoints, pBaseAddrList, pValidAddrList, pOutAddrList, pValidOutAddrList, pLocalX, pLocalY, pLocalXY, numKeyPoints, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_copy_new_lk_xy_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

