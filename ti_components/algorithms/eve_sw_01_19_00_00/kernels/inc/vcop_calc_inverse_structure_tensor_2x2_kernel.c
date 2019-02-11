#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_calc_inverse_structure_tensor_2x2, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_calc_inverse_structure_tensor_2x2, __ALIGNOF__(int));
unsigned short __pblock_vcop_calc_inverse_structure_tensor_2x2[54];

unsigned int vcop_calc_inverse_structure_tensor_2x2_param_count(void)
{
   return 54u;
}

unsigned int vcop_calc_inverse_structure_tensor_2x2_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_calc_inverse_structure_tensor_2x2_init(
   __vptr_int32 pTensorArrInp_A,
   __vptr_uint16 pD_nrsb_B,
   __vptr_uint32 pD_norm_C,
   __vptr_int16 pInverseArrOut_A,
   __vptr_int32 pScratchNorm_C,
   __vptr_uint32 pScratchDividend_C,
   unsigned short inputStride,
   unsigned short outputStride,
   unsigned short numFracBits,
   unsigned short numKeyPoints,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (3)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((numKeyPoints+(8u)-1)/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), 1);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), 32 + (9-1) - numFracBits);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), ~((1 << 9) -1));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pTensorArrInp_A);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)pD_norm_C);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pD_nrsb_B);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pInverseArrOut_A);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)pScratchNorm_C);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)pScratchDividend_C);
   __vcop_pblock_init16(pblock, __offset+_PREG(26), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(27), (inputStride*sizeof(*pTensorArrInp_A)) -((8u*sizeof(*pTensorArrInp_A)))*(((numKeyPoints+(8u)-1)/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(28),  -((8u*sizeof(*pTensorArrInp_A)))*(((numKeyPoints+(8u)-1)/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(29), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(30),  -((8u*sizeof(*pInverseArrOut_A)))*(((numKeyPoints+(8u)-1)/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(31), (outputStride*sizeof(*pInverseArrOut_A)) -(2*(8u*sizeof(*pInverseArrOut_A)))*(((numKeyPoints+(8u)-1)/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(32), -32);
   __vcop_pblock_init32(pblock, __offset+_PREG(34), 30);
   __offset += 34;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (3)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((numKeyPoints+(8u)-1)/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (9)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pScratchDividend_C);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pInverseArrOut_A);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), 1);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(15), (inputStride*sizeof(*pTensorArrInp_A)) -((8u*sizeof(*pTensorArrInp_A)))*(((numKeyPoints+(8u)-1)/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(16),  -((8u*sizeof(*pTensorArrInp_A)))*(((numKeyPoints+(8u)-1)/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(17), (outputStride*sizeof(*pInverseArrOut_A)) -(2*(8u*sizeof(*pInverseArrOut_A)))*(((numKeyPoints+(8u)-1)/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)pD_norm_C);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)pScratchNorm_C);
   __offset += 20;

   return 54u;
}

void vcop_calc_inverse_structure_tensor_2x2_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("V_dividend", 16);
   #pragma VCC_VREG("V_dividendA", 17);
   #pragma VCC_VREG("V_dividendB", 18);
   #pragma VCC_VREG("V_quotientA", 19);
   #pragma VCC_VREG("V_quotientB", 20);
   #pragma VCC_VREG("Vcst30", 21);
   #pragma VCC_VREG("Vcst31_M2_DIVIDE_BITS_M2_FRAC_BITS", 22);
   #pragma VCC_VREG("VcstOne", 23);
   #pragma VCC_VREG("VcstZero", 24);
   #pragma VCC_VREG("Vd_norm", 25);
   #pragma VCC_VREG("Vd_nrsb", 26);
   #pragma VCC_VREG("VdivbitsMask", 27);
   #pragma VCC_VREG("Vleadbit", 28);
   #pragma VCC_VREG("Vn", 29);
   #pragma VCC_VREG("Vn1", 30);
   #pragma VCC_VREG("Vn2", 31);
   #pragma VCC_VREG("Vn_nrsb", 32);
   #pragma VCC_VREG("Vout_exp", 33);
   #pragma VCC_VREG("Vshift32", 34);
   #pragma VCC_VREG("Vsign", 35);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_in", "A0");
   #pragma EVE_REG("Addr_norm", "A1");
   #pragma EVE_REG("Addr_nrsb", "A2");
   #pragma EVE_REG("Addr_out", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I2", "I3");
   #pragma EVE_REG("I1", "I4");
   

   __vcop_vloop(__vcop_compute(), 31u, 17u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(32), _VREG(34));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(34), _VREG(21));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(6), _VREG(24));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(8), _VREG(23));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(8), _VREG(28));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(10), _VREG(22));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(12), _VREG(27));
   __vcop_vagen(_AGEN(0), _PREG(26), _PREG(27), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(26), _PREG(28), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(29), _PREG(30), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(26), _PREG(31), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(14), _AGEN(0), _VREG(29), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(16), _AGEN(1), _VREG(25), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(18), _AGEN(2), _VREG(26), __vcop_alws());
   __vcop_vand(_VREG(25), _VREG(27), _VREG(25));
   __vcop_vshf(_VREG(29), _VREG(34), _VREG(35));
   __vcop_vadd(_VREG(23), _VREG(24), _VREG(28));
   __vcop_vsel(_VREG(35), _VREG(24), _VREG(28));
   __vcop_vlmbd(_VREG(29), _VREG(28), _VREG(32));
   __vcop_vsub(_VREG(21), _VREG(32), _VREG(32));
   __vcop_vshf(_VREG(29), _VREG(32), _VREG(29));
   __vcop_vabs(_VREG(29), _VREG(16));
   __vcop_vsub(_VREG(22), _VREG(26), _VREG(33));
   __vcop_vadd(_VREG(32), _VREG(33), _VREG(33));
   __vcop_vsub(_VREG(24), _VREG(33), _VREG(33));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(26), _PREG(18), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_npt(), __vcop_alws(), _VREG(33), _PREG(20), _AGEN(3), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(25), _PREG(16), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeW(), __vcop_npt(), __vcop_alws(), _VREG(29), _PREG(22), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(16), _PREG(24), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr_in", "A0");
   #pragma EVE_REG("Addr_norm", "A1");
   #pragma EVE_REG("Addr_out", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I2", "I2");
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("J1", "I4");
   

   __vcop_vloop(__vcop_compute(), 24u, 10u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(10), _VREG(24));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(12), _VREG(19));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(12), _VREG(20));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(14), _PREG(15), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(14), _PREG(16), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(0), _PREG(14), _PREG(17), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(18), _AGEN(1), _VREG(25), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeW(), __vcop_npt(), _PREG(20), _AGEN(0), _VREG(29), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(6), _AGEN(0), _VREG(16), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeH(), __vcop_npt(), _PREG(8), _AGEN(2), _VREG(33), __vcop_i4_zero());
   __vcop_vshfor(_VREG(24), _VREG(23), _VREG(19));
   __vcop_vsub(_VREG(16), _VREG(25), _VREG(17));
   __vcop_vshf(_VREG(17), _VREG(23), _VREG(17));
   __vcop_vshf(_VREG(24), _VREG(23), _VREG(20));
   __vcop_vshf(_VREG(16), _VREG(23), _VREG(18));
   __vcop_vcmpgt(_VREG(16), _VREG(25), _VREG(35));
   __vcop_vsel(_VREG(35), _VREG(19), _VREG(20));
   __vcop_vsel(_VREG(35), _VREG(17), _VREG(18));
   __vcop_vor(_VREG(20), _VREG(20), _VREG(24));
   __vcop_vor(_VREG(18), _VREG(18), _VREG(16));
   __vcop_vsign(_VREG(29), _VREG(24), _VREG(28));
   __vcop_vor(_VREG(23), _VREG(23), _VREG(19));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_last_i4(), _VPAIR(28,33), _PREG(8), _AGEN(2), _PREG(0));
   __vcop_vloop_end(2u);

}

void vcop_calc_inverse_structure_tensor_2x2(
   __vptr_int32 pTensorArrInp_A,
   __vptr_uint16 pD_nrsb_B,
   __vptr_uint32 pD_norm_C,
   __vptr_int16 pInverseArrOut_A,
   __vptr_int32 pScratchNorm_C,
   __vptr_uint32 pScratchDividend_C,
   unsigned short inputStride,
   unsigned short outputStride,
   unsigned short numFracBits,
   unsigned short numKeyPoints)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_calc_inverse_structure_tensor_2x2_init(pTensorArrInp_A, pD_nrsb_B, pD_norm_C, pInverseArrOut_A, pScratchNorm_C, pScratchDividend_C, inputStride, outputStride, numFracBits, numKeyPoints, __pblock_vcop_calc_inverse_structure_tensor_2x2);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_calc_inverse_structure_tensor_2x2_vloops(__pblock_vcop_calc_inverse_structure_tensor_2x2);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_calc_inverse_structure_tensor_2x2_custom(
   __vptr_int32 pTensorArrInp_A,
   __vptr_uint16 pD_nrsb_B,
   __vptr_uint32 pD_norm_C,
   __vptr_int16 pInverseArrOut_A,
   __vptr_int32 pScratchNorm_C,
   __vptr_uint32 pScratchDividend_C,
   unsigned short inputStride,
   unsigned short outputStride,
   unsigned short numFracBits,
   unsigned short numKeyPoints,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_calc_inverse_structure_tensor_2x2_init(pTensorArrInp_A, pD_nrsb_B, pD_norm_C, pInverseArrOut_A, pScratchNorm_C, pScratchDividend_C, inputStride, outputStride, numFracBits, numKeyPoints, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_calc_inverse_structure_tensor_2x2_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

