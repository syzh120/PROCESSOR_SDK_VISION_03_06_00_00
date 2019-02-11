#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_weight_computation, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_weight_computation, __ALIGNOF__(int));
unsigned short __pblock_vcop_weight_computation[20];

unsigned int vcop_weight_computation_param_count(void)
{
   return 20u;
}

unsigned int vcop_weight_computation_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_weight_computation_init(
   __vptr_uint16 pXYList_A,
   __vptr_uint16 pOutWts_B,
   unsigned short numKeyPoints,
   unsigned short qFormatMaxFactor,
   unsigned short truncateBits,
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
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pOutWts_B);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pOutWts_B+outputStride*sizeof(*pOutWts_B));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pOutWts_B+2*outputStride*sizeof(*pOutWts_B));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pOutWts_B+3*outputStride*sizeof(*pOutWts_B));
   __vcop_pblock_init16(pblock, __offset+_PREG(16), 16);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), qFormatMaxFactor);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pXYList_A);
   __offset += 20;

   return 20u;
}

void vcop_weight_computation_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VQFt_xFrac", 16);
   #pragma VCC_VREG("VQFt_yFrac", 17);
   #pragma VCC_VREG("VqFormat", 18);
   #pragma VCC_VREG("Vwt0", 19);
   #pragma VCC_VREG("Vwt1", 20);
   #pragma VCC_VREG("Vwt2", 21);
   #pragma VCC_VREG("Vwt3", 22);
   #pragma VCC_VREG("Vx", 23);
   #pragma VCC_VREG("VxFrac", 24);
   #pragma VCC_VREG("Vy", 25);
   #pragma VCC_VREG("VyFrac", 26);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("AddrIn", "A0");
   #pragma EVE_REG("AddrOut", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 17u, 10u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(18), _VREG(18));
   __vcop_vagen(_AGEN(0), _PREG(7), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(16), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(20), _AGEN(0), _VPAIR(23,25), __vcop_alws());
   __vcop_vand(_VREG(23), _VREG(18), _VREG(24));
   __vcop_vand(_VREG(25), _VREG(18), _VREG(26));
   __vcop_vsub(_VREG(18), _VREG(24), _VREG(16));
   __vcop_vsub(_VREG(18), _VREG(26), _VREG(17));
   __vcop_vmpy(_VREG(24), _VREG(26), _VREG(19), _PREG(0));
   __vcop_vmpy(_VREG(16), _VREG(26), _VREG(20), _PREG(0));
   __vcop_vmpy(_VREG(24), _VREG(17), _VREG(21), _PREG(0));
   __vcop_vmpy(_VREG(16), _VREG(17), _VREG(22), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(19), _PREG(8), _AGEN(1), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(20), _PREG(10), _AGEN(1), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(21), _PREG(12), _AGEN(1), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(22), _PREG(14), _AGEN(1), _PREG(6));
   __vcop_vloop_end(1u);

}

void vcop_weight_computation(
   __vptr_uint16 pXYList_A,
   __vptr_uint16 pOutWts_B,
   unsigned short numKeyPoints,
   unsigned short qFormatMaxFactor,
   unsigned short truncateBits,
   unsigned short outputStride)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_weight_computation_init(pXYList_A, pOutWts_B, numKeyPoints, qFormatMaxFactor, truncateBits, outputStride, __pblock_vcop_weight_computation);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_weight_computation_vloops(__pblock_vcop_weight_computation);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_weight_computation_custom(
   __vptr_uint16 pXYList_A,
   __vptr_uint16 pOutWts_B,
   unsigned short numKeyPoints,
   unsigned short qFormatMaxFactor,
   unsigned short truncateBits,
   unsigned short outputStride,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_weight_computation_init(pXYList_A, pOutWts_B, numKeyPoints, qFormatMaxFactor, truncateBits, outputStride, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_weight_computation_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

