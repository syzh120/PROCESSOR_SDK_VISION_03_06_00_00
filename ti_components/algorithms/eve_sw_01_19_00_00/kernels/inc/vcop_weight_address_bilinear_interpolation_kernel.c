#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_weight_address_bilinear_interpolation, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_weight_address_bilinear_interpolation, __ALIGNOF__(int));
unsigned short __pblock_vcop_weight_address_bilinear_interpolation[52];

unsigned int vcop_weight_address_bilinear_interpolation_param_count(void)
{
   return 52u;
}

unsigned int vcop_weight_address_bilinear_interpolation_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_weight_address_bilinear_interpolation_init(
   __vptr_uint16 pXList_A,
   __vptr_uint16 pYList_A,
   __vptr_uint32 pBaseAddrList_B,
   __vptr_uint32 pOutAddrList_B,
   __vptr_uint16 pOutWts_C,
   __vptr_uint32 pOutBaseAddress_C,
   __vptr_uint16 pParamBlkOffsetVec_C,
   unsigned short numKeyPoints,
   unsigned short qFormatMaxFactor,
   unsigned short truncateBits,
   unsigned short qShift,
   unsigned short blkStride,
   unsigned short outputStride,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((numKeyPoints+(8u)-1)/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_NONE,0,RM_TRUNC,truncateBits));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 16);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pYList_A);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pBaseAddrList_B);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), qFormatMaxFactor);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), -qShift);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (7)/2);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), blkStride);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)pOutWts_C);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)pOutWts_C+outputStride*sizeof(*pOutWts_C));
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)pOutWts_C+2*outputStride*sizeof(*pOutWts_C));
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)pOutWts_C+3*outputStride*sizeof(*pOutWts_C));
   __vcop_pblock_init32(pblock, __offset+_PREG(30), (uchar *)pOutBaseAddress_C);
   __vcop_pblock_init32(pblock, __offset+_PREG(32), (uchar *)pOutBaseAddress_C+4);
   __vcop_pblock_init32(pblock, __offset+_PREG(34), (uchar *)pOutBaseAddress_C+8);
   __vcop_pblock_init32(pblock, __offset+_PREG(36), (uchar *)pOutBaseAddress_C+12);
   __vcop_pblock_init16(pblock, __offset+_PREG(38), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(39), 416);
   __vcop_pblock_init32(pblock, __offset+_PREG(40), (uchar *)pParamBlkOffsetVec_C);
   __vcop_pblock_init32(pblock, __offset+_PREG(42), (uchar *)pXList_A);
   __offset += 42;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((numKeyPoints+(8u)-1)/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 416);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pOutAddrList_B);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pOutBaseAddress_C+16);
   __offset += 10;

   return 52u;
}

void vcop_weight_address_bilinear_interpolation_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VQFt_xFrac", 16);
   #pragma VCC_VREG("VQFt_yFrac", 17);
   #pragma VCC_VREG("VbaseAddr", 18);
   #pragma VCC_VREG("Vpwid", 19);
   #pragma VCC_VREG("VqFormat", 20);
   #pragma VCC_VREG("VqShift", 21);
   #pragma VCC_VREG("VscatterOffset", 22);
   #pragma VCC_VREG("Vstride", 23);
   #pragma VCC_VREG("Vwt0", 24);
   #pragma VCC_VREG("Vwt1", 25);
   #pragma VCC_VREG("Vwt2", 26);
   #pragma VCC_VREG("Vwt3", 27);
   #pragma VCC_VREG("Vx", 28);
   #pragma VCC_VREG("VxFrac", 29);
   #pragma VCC_VREG("Vy", 30);
   #pragma VCC_VREG("VyFrac", 31);
   #pragma VCC_VREG("Vzero", 32);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("AddrIn1", "A0");
   #pragma EVE_REG("AddrIn2", "A1");
   #pragma EVE_REG("AddrOut1", "A2");
   #pragma EVE_REG("AddrOut2", "A3");
   #pragma EVE_REG("offset", "A4");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 55u, 21u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(12), _VREG(20));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(14), _VREG(21));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(16), _VREG(19));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(18), _VREG(23));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(20), _VREG(32));
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(38), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(7), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(39), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(4), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(40), _AGEN(4), _VREG(22), __vcop_once());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(42), _AGEN(0), _VREG(28), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(8), _AGEN(0), _VREG(30), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(10), _AGEN(1), _VREG(18), __vcop_alws());
   __vcop_vand(_VREG(28), _VREG(20), _VREG(29));
   __vcop_vand(_VREG(30), _VREG(20), _VREG(31));
   __vcop_vsub(_VREG(20), _VREG(29), _VREG(16));
   __vcop_vsub(_VREG(20), _VREG(31), _VREG(17));
   __vcop_vmpy(_VREG(29), _VREG(31), _VREG(24), _PREG(0));
   __vcop_vmpy(_VREG(16), _VREG(31), _VREG(25), _PREG(0));
   __vcop_vmpy(_VREG(29), _VREG(17), _VREG(26), _PREG(0));
   __vcop_vmpy(_VREG(16), _VREG(17), _VREG(27), _PREG(0));
   __vcop_vshf(_VREG(28), _VREG(21), _VREG(28));
   __vcop_vshf(_VREG(30), _VREG(21), _VREG(30));
   __vcop_vsub(_VREG(28), _VREG(19), _VREG(28));
   __vcop_vsub(_VREG(30), _VREG(19), _VREG(30));
   __vcop_vcmplt(_VREG(28), _VREG(32), _VREG(29));
   __vcop_vcmplt(_VREG(30), _VREG(32), _VREG(31));
   __vcop_vsel(_VREG(29), _VREG(32), _VREG(28));
   __vcop_vsel(_VREG(31), _VREG(32), _VREG(30));
   __vcop_vadd(_VREG(28), _VREG(19), _VREG(16));
   __vcop_vadd(_VREG(30), _VREG(19), _VREG(17));
   __vcop_vadd(_VREG(16), _VREG(19), _VREG(16));
   __vcop_vadd(_VREG(17), _VREG(19), _VREG(17));
   __vcop_vadd(_VREG(16), _VREG(19), _VREG(16));
   __vcop_vadd(_VREG(17), _VREG(19), _VREG(17));
   __vcop_vcmpge(_VREG(16), _VREG(23), _VREG(29));
   __vcop_vcmpge(_VREG(17), _VREG(23), _VREG(31));
   __vcop_vsel(_VREG(29), _VREG(32), _VREG(28));
   __vcop_vsel(_VREG(31), _VREG(32), _VREG(30));
   __vcop_vmadd(_VREG(30), _VREG(23), _VREG(28), _PREG(0));
   __vcop_vcmpgt(_VREG(32), _VREG(21), _VREG(29));
   __vcop_vadd(_VREG(18), _VREG(28), _VREG(28));
   __vcop_vadd(_VREG(28), _VREG(29), _VREG(30));
   __vcop_vadd(_VREG(28), _VREG(23), _VREG(16));
   __vcop_vadd(_VREG(30), _VREG(23), _VREG(17));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(24), _PREG(22), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(25), _PREG(24), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(26), _PREG(26), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(27), _PREG(28), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_sdda(_VREG(22)), __vcop_alws(), _VREG(28), _PREG(30), _AGEN(3), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_sdda(_VREG(22)), __vcop_alws(), _VREG(30), _PREG(32), _AGEN(3), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_sdda(_VREG(22)), __vcop_alws(), _VREG(16), _PREG(34), _AGEN(3), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_sdda(_VREG(22)), __vcop_alws(), _VREG(17), _PREG(36), _AGEN(3), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("AddrIn1", "A0");
   #pragma EVE_REG("AddrIn2", "A1");
   #pragma EVE_REG("AddrOut1", "A2");
   #pragma EVE_REG("AddrOut2", "A3");
   #pragma EVE_REG("offset", "A4");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 8u, 5u, 2u);
   __vcop_vagen(_AGEN(1), _PREG(6), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(7), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(8), _AGEN(1), _VREG(28), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_sdda(_VREG(22)), __vcop_alws(), _VREG(28), _PREG(10), _AGEN(3), _PREG(0));
   __vcop_vloop_end(2u);

}

void vcop_weight_address_bilinear_interpolation(
   __vptr_uint16 pXList_A,
   __vptr_uint16 pYList_A,
   __vptr_uint32 pBaseAddrList_B,
   __vptr_uint32 pOutAddrList_B,
   __vptr_uint16 pOutWts_C,
   __vptr_uint32 pOutBaseAddress_C,
   __vptr_uint16 pParamBlkOffsetVec_C,
   unsigned short numKeyPoints,
   unsigned short qFormatMaxFactor,
   unsigned short truncateBits,
   unsigned short qShift,
   unsigned short blkStride,
   unsigned short outputStride)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_weight_address_bilinear_interpolation_init(pXList_A, pYList_A, pBaseAddrList_B, pOutAddrList_B, pOutWts_C, pOutBaseAddress_C, pParamBlkOffsetVec_C, numKeyPoints, qFormatMaxFactor, truncateBits, qShift, blkStride, outputStride, __pblock_vcop_weight_address_bilinear_interpolation);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_weight_address_bilinear_interpolation_vloops(__pblock_vcop_weight_address_bilinear_interpolation);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_weight_address_bilinear_interpolation_custom(
   __vptr_uint16 pXList_A,
   __vptr_uint16 pYList_A,
   __vptr_uint32 pBaseAddrList_B,
   __vptr_uint32 pOutAddrList_B,
   __vptr_uint16 pOutWts_C,
   __vptr_uint32 pOutBaseAddress_C,
   __vptr_uint16 pParamBlkOffsetVec_C,
   unsigned short numKeyPoints,
   unsigned short qFormatMaxFactor,
   unsigned short truncateBits,
   unsigned short qShift,
   unsigned short blkStride,
   unsigned short outputStride,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_weight_address_bilinear_interpolation_init(pXList_A, pYList_A, pBaseAddrList_B, pOutAddrList_B, pOutWts_C, pOutBaseAddress_C, pParamBlkOffsetVec_C, numKeyPoints, qFormatMaxFactor, truncateBits, qShift, blkStride, outputStride, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_weight_address_bilinear_interpolation_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

