#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_vec_L_matrix_u8_Mag, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_vec_L_matrix_u8_Mag, __ALIGNOF__(int));
unsigned short __pblock_vcop_vec_L_matrix_u8_Mag[34];

unsigned int vcop_vec_L_matrix_u8_Mag_param_count(void)
{
   return 34u;
}

unsigned int vcop_vec_L_matrix_u8_Mag_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_vec_L_matrix_u8_Mag_init(
   __vptr_uint8 pIn,
   __vptr_uint8 pMag,
   __vptr_uint8 pOut1,
   __vptr_uint8 pOut2,
   __vptr_uint32 pOutClear1,
   __vptr_uint32 pOutClear2,
   unsigned short width,
   unsigned short height,
   unsigned short numBins,
   __vptr_uint8 binIdx,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (((numBins+1)/2)*height)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (((width + ((4*(8u))-1)) & (~((4*(8u))-1)))/(4*(8u)))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pOutClear2);
   __vcop_pblock_init16(pblock, __offset+_PREG(8), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(9), (width) -(sizeof(*pOutClear1)*8u)*((((width + ((4*(8u))-1)) & (~((4*(8u))-1)))/(4*(8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pOutClear1);
   __offset += 12;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), ((numBins+1)/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (height)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (((width + ((8u)-1)) & (~((8u)-1)))/((8u)))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pIn);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pMag);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pOut1);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pOut2);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), 2);
   __vcop_pblock_init16(pblock, __offset+_PREG(15), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(16), (width) -(8u)*((((width + ((8u)-1)) & (~((8u)-1)))/((8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(17), (0) -(width)*((height)-1u) -(8u)*((((width + ((8u)-1)) & (~((8u)-1)))/((8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(18), (width*height) -(width)*((height)-1u) -(8u)*((((width + ((8u)-1)) & (~((8u)-1)))/((8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)binIdx);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)binIdx+1);
   __offset += 22;

   return 34u;
}

void vcop_vec_L_matrix_u8_Mag_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vbin0", 16);
   #pragma VCC_VREG("Vbin1", 17);
   #pragma VCC_VREG("Vzero", 18);
   #pragma VCC_VREG("vbin", 19);
   #pragma VCC_VREG("vmag", 20);
   #pragma VCC_VREG("vpred0", 21);
   #pragma VCC_VREG("vpred1", 22);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   #pragma EVE_REG("Addr1", "A1");
   #pragma EVE_REG("Addr2", "A2");
   #pragma EVE_REG("Addr_Out", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 8u, 6u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(10), _VREG(18));
   __vcop_vagen(_AGEN(3), _PREG(8), _PREG(9), _PREG(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(18), _PREG(12), _AGEN(3), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(18), _PREG(6), _AGEN(3), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   #pragma EVE_REG("Addr1", "A1");
   #pragma EVE_REG("Addr2", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I0", "I2");
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 12u, 11u, 2u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(14), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(15), _PREG(16), _PREG(17), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(15), _PREG(16), _PREG(18), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_1pt(), _PREG(20), _AGEN(0), _VREG(16), __vcop_i34_zero());
   __vcop_vload(__vcop_sizeBU(), __vcop_1pt(), _PREG(22), _AGEN(0), _VREG(17), __vcop_i34_zero());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(6), _AGEN(1), _VREG(19), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(8), _AGEN(1), _VREG(20), __vcop_alws());
   __vcop_vcmpeq(_VREG(16), _VREG(19), _VREG(21));
   __vcop_vcmpeq(_VREG(17), _VREG(19), _VREG(22));
   __vcop_vstore(__vcop_predicate(_VREG(21)), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(20), _PREG(10), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_predicate(_VREG(22)), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(20), _PREG(12), _AGEN(2), _PREG(0));
   __vcop_vloop_end(2u);

}

void vcop_vec_L_matrix_u8_Mag(
   __vptr_uint8 pIn,
   __vptr_uint8 pMag,
   __vptr_uint8 pOut1,
   __vptr_uint8 pOut2,
   __vptr_uint32 pOutClear1,
   __vptr_uint32 pOutClear2,
   unsigned short width,
   unsigned short height,
   unsigned short numBins,
   __vptr_uint8 binIdx)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_vec_L_matrix_u8_Mag_init(pIn, pMag, pOut1, pOut2, pOutClear1, pOutClear2, width, height, numBins, binIdx, __pblock_vcop_vec_L_matrix_u8_Mag);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_vec_L_matrix_u8_Mag_vloops(__pblock_vcop_vec_L_matrix_u8_Mag);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_vec_L_matrix_u8_Mag_custom(
   __vptr_uint8 pIn,
   __vptr_uint8 pMag,
   __vptr_uint8 pOut1,
   __vptr_uint8 pOut2,
   __vptr_uint32 pOutClear1,
   __vptr_uint32 pOutClear2,
   unsigned short width,
   unsigned short height,
   unsigned short numBins,
   __vptr_uint8 binIdx,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_vec_L_matrix_u8_Mag_init(pIn, pMag, pOut1, pOut2, pOutClear1, pOutClear2, width, height, numBins, binIdx, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_vec_L_matrix_u8_Mag_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_vec_L_matrix_u16_Mag, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_vec_L_matrix_u16_Mag, __ALIGNOF__(int));
unsigned short __pblock_vcop_vec_L_matrix_u16_Mag[36];

unsigned int vcop_vec_L_matrix_u16_Mag_param_count(void)
{
   return 36u;
}

unsigned int vcop_vec_L_matrix_u16_Mag_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_vec_L_matrix_u16_Mag_init(
   __vptr_uint8 pIn,
   __vptr_uint16 pMag,
   __vptr_uint16 pOut1,
   __vptr_uint16 pOut2,
   __vptr_uint32 pOutClear1,
   __vptr_uint32 pOutClear2,
   unsigned short width,
   unsigned short height,
   unsigned short numBins,
   __vptr_uint8 binIdx,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (((numBins+1)/2)*height)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (((width + ((2*(8u))-1)) & (~((2*(8u))-1)))/(2*(8u)))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pOutClear2);
   __vcop_pblock_init16(pblock, __offset+_PREG(8), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(9), (width*2) -(sizeof(*pOutClear1)*8u)*((((width + ((2*(8u))-1)) & (~((2*(8u))-1)))/(2*(8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pOutClear1);
   __offset += 12;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), ((numBins+1)/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (height)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (((width + ((8u)-1)) & (~((8u)-1)))/((8u)))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pIn);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pMag);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pOut1);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pOut2);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), 2);
   __vcop_pblock_init16(pblock, __offset+_PREG(15), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(16), (width) -(8u)*((((width + ((8u)-1)) & (~((8u)-1)))/((8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(17), (0) -(width)*((height)-1u) -(8u)*((((width + ((8u)-1)) & (~((8u)-1)))/((8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(18), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(19), (width*2) -(2*8u)*((((width + ((8u)-1)) & (~((8u)-1)))/((8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(20), (width*height*2) -(width*2)*((height)-1u) -(2*8u)*((((width + ((8u)-1)) & (~((8u)-1)))/((8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(21), (0) -(width*2)*((height)-1u) -(2*8u)*((((width + ((8u)-1)) & (~((8u)-1)))/((8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)binIdx);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)binIdx+1);
   __offset += 24;

   return 36u;
}

void vcop_vec_L_matrix_u16_Mag_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("Vbin0", 16);
   #pragma VCC_VREG("Vbin1", 17);
   #pragma VCC_VREG("Vzero", 18);
   #pragma VCC_VREG("vbin", 19);
   #pragma VCC_VREG("vmag", 20);
   #pragma VCC_VREG("vpred0", 21);
   #pragma VCC_VREG("vpred1", 22);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   #pragma EVE_REG("Addr1", "A1");
   #pragma EVE_REG("Addr2", "A2");
   #pragma EVE_REG("Addr3", "A3");
   #pragma EVE_REG("Addr_Out", "A4");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 9u, 6u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(10), _VREG(18));
   __vcop_vagen(_AGEN(4), _PREG(8), _PREG(9), _PREG(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(18), _PREG(12), _AGEN(4), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(18), _PREG(6), _AGEN(4), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("Addr0", "A0");
   #pragma EVE_REG("Addr1", "A1");
   #pragma EVE_REG("Addr2", "A2");
   #pragma EVE_REG("Addr3", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I0", "I2");
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 13u, 12u, 2u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(14), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(15), _PREG(16), _PREG(17), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(18), _PREG(19), _PREG(20), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(18), _PREG(19), _PREG(21), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_1pt(), _PREG(22), _AGEN(0), _VREG(16), __vcop_i34_zero());
   __vcop_vload(__vcop_sizeBU(), __vcop_1pt(), _PREG(24), _AGEN(0), _VREG(17), __vcop_i34_zero());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(6), _AGEN(1), _VREG(19), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(8), _AGEN(3), _VREG(20), __vcop_alws());
   __vcop_vcmpeq(_VREG(16), _VREG(19), _VREG(21));
   __vcop_vcmpeq(_VREG(17), _VREG(19), _VREG(22));
   __vcop_vstore(__vcop_predicate(_VREG(21)), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(20), _PREG(10), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_predicate(_VREG(22)), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(20), _PREG(12), _AGEN(2), _PREG(0));
   __vcop_vloop_end(2u);

}

void vcop_vec_L_matrix_u16_Mag(
   __vptr_uint8 pIn,
   __vptr_uint16 pMag,
   __vptr_uint16 pOut1,
   __vptr_uint16 pOut2,
   __vptr_uint32 pOutClear1,
   __vptr_uint32 pOutClear2,
   unsigned short width,
   unsigned short height,
   unsigned short numBins,
   __vptr_uint8 binIdx)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_vec_L_matrix_u16_Mag_init(pIn, pMag, pOut1, pOut2, pOutClear1, pOutClear2, width, height, numBins, binIdx, __pblock_vcop_vec_L_matrix_u16_Mag);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_vec_L_matrix_u16_Mag_vloops(__pblock_vcop_vec_L_matrix_u16_Mag);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_vec_L_matrix_u16_Mag_custom(
   __vptr_uint8 pIn,
   __vptr_uint16 pMag,
   __vptr_uint16 pOut1,
   __vptr_uint16 pOut2,
   __vptr_uint32 pOutClear1,
   __vptr_uint32 pOutClear2,
   unsigned short width,
   unsigned short height,
   unsigned short numBins,
   __vptr_uint8 binIdx,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_vec_L_matrix_u16_Mag_init(pIn, pMag, pOut1, pOut2, pOutClear1, pOutClear2, width, height, numBins, binIdx, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_vec_L_matrix_u16_Mag_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

