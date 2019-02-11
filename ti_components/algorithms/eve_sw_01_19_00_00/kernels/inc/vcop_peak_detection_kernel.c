#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_tx_decoding_kernel, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_tx_decoding_kernel, __ALIGNOF__(int));
unsigned short __pblock_vcop_tx_decoding_kernel[80];

unsigned short __ctrl_vcop_tx_decoding_kernel[1];

unsigned int vcop_tx_decoding_kernel_param_count(void)
{
   return 80u;
}

unsigned int vcop_tx_decoding_kernel_ctrl_count(void)
{
   return 1u;
}

unsigned int vcop_tx_decoding_kernel_init(
   __vptr_int16_arr inputData,
   __vptr_int16 txDecodingCoeff,
   __vptr_int16_arr outputData,
   unsigned short numTx,
   unsigned short numRx,
   unsigned short numRows,
   unsigned short numHorzPtPerAntenna,
   unsigned short offsetBwTx,
   unsigned short offsetBwRx,
   unsigned short pitch,
   unsigned short pblock[])
{
   int I0;
   int __offset = 0;
   /* Loop 1 PREGS */

   __ctrl_vcop_tx_decoding_kernel[0] = numHorzPtPerAntenna/ (8u) - 1;
   for (I0 = 0; I0 < numHorzPtPerAntenna/ (8u); I0++)
   {
   __vcop_pblock_init16(pblock, __offset+_PREG(2), (numRows)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (numRx)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (numTx)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (numTx)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)txDecodingCoeff);
   __vcop_pblock_init16(pblock, __offset+_PREG(8), __vcop_vop_round(1, 15));
   __vcop_pblock_init16(pblock, __offset+_PREG(9), (numTx*sizeof(*txDecodingCoeff)));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)outputData[I0]);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), (sizeof(*txDecodingCoeff)) -(numTx*sizeof(*txDecodingCoeff))*((numTx)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(13),  -(sizeof(*txDecodingCoeff))*((numTx)-1u) -(numTx*sizeof(*txDecodingCoeff))*((numTx)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(14), (offsetBwTx));
   __vcop_pblock_init16(pblock, __offset+_PREG(15),  -(offsetBwTx)*((numTx)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(16), (offsetBwRx) -(offsetBwTx)*((numTx)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(17), (pitch) -(offsetBwRx)*((numRx)-1u) -(offsetBwTx)*((numTx)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)inputData[I0]);
   __offset += 20;
   }


   return 80u;
}

void vcop_tx_decoding_kernel_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VDataI", 16);
   #pragma VCC_VREG("VDataR", 17);
   #pragma VCC_VREG("VOutI", 18);
   #pragma VCC_VREG("VOutR", 19);
   #pragma VCC_VREG("VTxCoeff", 20);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("coeffAddr", "A0");
   #pragma EVE_REG("inAddr", "A1");
   #pragma EVE_REG("outAddr", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I0", "I0");
   #pragma EVE_REG("rowIdx", "I1");
   #pragma EVE_REG("rxIdx", "I2");
   #pragma EVE_REG("txOutIdx", "I3");
   #pragma EVE_REG("txInIdx", "I4");
   

   __vcop_rpt(__ctrl_vcop_tx_decoding_kernel[0]);
   __vcop_vloop(__vcop_compute(), 11u, 10u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(18), _VREG(19));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(18), _VREG(18));
   __vcop_vagen(_AGEN(0), _PREG(9), _PREG(12), _PREG(13), _PREG(13));
   __vcop_vagen(_AGEN(1), _PREG(14), _PREG(15), _PREG(16), _PREG(17));
   __vcop_vagen(_AGEN(2), _PREG(0), _PREG(14), _PREG(16), _PREG(17));
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(20), _AGEN(1), _VPAIR(17,16), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_1pt(), _PREG(6), _AGEN(0), _VREG(20), __vcop_alws());
   __vcop_vmadd(_VREG(17), _VREG(20), _VREG(19), _PREG(8));
   __vcop_vmadd(_VREG(16), _VREG(20), _VREG(18), _PREG(8));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_last_i4(), _VPAIR(19,18), _PREG(10), _AGEN(2), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_tx_decoding_kernel(
   __vptr_int16_arr inputData,
   __vptr_int16 txDecodingCoeff,
   __vptr_int16_arr outputData,
   unsigned short numTx,
   unsigned short numRx,
   unsigned short numRows,
   unsigned short numHorzPtPerAntenna,
   unsigned short offsetBwTx,
   unsigned short offsetBwRx,
   unsigned short pitch)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_tx_decoding_kernel_init(inputData, txDecodingCoeff, outputData, numTx, numRx, numRows, numHorzPtPerAntenna, offsetBwTx, offsetBwRx, pitch, __pblock_vcop_tx_decoding_kernel);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_tx_decoding_kernel_vloops(__pblock_vcop_tx_decoding_kernel);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_tx_decoding_kernel_custom(
   __vptr_int16_arr inputData,
   __vptr_int16 txDecodingCoeff,
   __vptr_int16_arr outputData,
   unsigned short numTx,
   unsigned short numRx,
   unsigned short numRows,
   unsigned short numHorzPtPerAntenna,
   unsigned short offsetBwTx,
   unsigned short offsetBwRx,
   unsigned short pitch,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_tx_decoding_kernel_init(inputData, txDecodingCoeff, outputData, numTx, numRx, numRows, numHorzPtPerAntenna, offsetBwTx, offsetBwRx, pitch, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_tx_decoding_kernel_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_peak_detection_energy_across_antenna, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_peak_detection_energy_across_antenna, __ALIGNOF__(int));
unsigned short __pblock_vcop_peak_detection_energy_across_antenna[22];

unsigned int vcop_peak_detection_energy_across_antenna_param_count(void)
{
   return 22u;
}

unsigned int vcop_peak_detection_energy_across_antenna_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_peak_detection_energy_across_antenna_init(
   __vptr_int16 inputData,
   __vptr_uint32 outputData,
   unsigned short numRows,
   unsigned short numAntennas,
   unsigned short numHorzPtPerAntenna,
   unsigned short pitch,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   const int preg_ref1 = _PREG(12);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (numRows/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((numHorzPtPerAntenna/ (8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (numAntennas)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_SYMM32,preg_ref1,RM_NONE,0));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), (numHorzPtPerAntenna*sizeof(*inputData)*2));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)inputData+pitch);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)outputData);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), 4294967295);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)outputData+sizeof(*outputData)*numHorzPtPerAntenna);
   __vcop_pblock_init16(pblock, __offset+_PREG(16), (8u*sizeof(*inputData)*2) -(numHorzPtPerAntenna*sizeof(*inputData)*2)*((numAntennas)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(17), (pitch*2) -(8u*sizeof(*inputData)*2)*(((numHorzPtPerAntenna/ (8u)))-1u) -(numHorzPtPerAntenna*sizeof(*inputData)*2)*((numAntennas)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(18), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(19), (sizeof(*outputData)*numHorzPtPerAntenna*2) -(8u*sizeof(*outputData))*(((numHorzPtPerAntenna/ (8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)inputData);
   __offset += 22;

   return 22u;
}

void vcop_peak_detection_energy_across_antenna_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VInDataImg1", 16);
   #pragma VCC_VREG("VInDataImg2", 17);
   #pragma VCC_VREG("VInDataReal1", 18);
   #pragma VCC_VREG("VInDataReal2", 19);
   #pragma VCC_VREG("VOutEnergy1", 20);
   #pragma VCC_VREG("VOutEnergy2", 21);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   #pragma EVE_REG("inAddr", "A1");
   #pragma EVE_REG("outAddr", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("rowIdx", "I2");
   #pragma EVE_REG("idx", "I3");
   #pragma EVE_REG("antennaIdx", "I4");
   

   __vcop_vloop(__vcop_compute(), 14u, 11u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(20), _VREG(20));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(20), _VREG(21));
   __vcop_vagen(_AGEN(1), _PREG(7), _PREG(16), _PREG(17), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(0), _PREG(18), _PREG(19), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(22), _AGEN(1), _VPAIR(18,16), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(8), _AGEN(1), _VPAIR(19,17), __vcop_alws());
   __vcop_vmadd(_VREG(18), _VREG(18), _VREG(20), _PREG(0));
   __vcop_vmadd(_VREG(19), _VREG(19), _VREG(21), _PREG(0));
   __vcop_vmadd(_VREG(16), _VREG(16), _VREG(20), _PREG(0));
   __vcop_vmadd(_VREG(17), _VREG(17), _VREG(21), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_last_i4(), _VREG(20), _PREG(10), _AGEN(2), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_last_i4(), _VREG(21), _PREG(14), _AGEN(2), _PREG(6));
   __vcop_vloop_end(1u);

}

void vcop_peak_detection_energy_across_antenna(
   __vptr_int16 inputData,
   __vptr_uint32 outputData,
   unsigned short numRows,
   unsigned short numAntennas,
   unsigned short numHorzPtPerAntenna,
   unsigned short pitch)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_peak_detection_energy_across_antenna_init(inputData, outputData, numRows, numAntennas, numHorzPtPerAntenna, pitch, __pblock_vcop_peak_detection_energy_across_antenna);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_peak_detection_energy_across_antenna_vloops(__pblock_vcop_peak_detection_energy_across_antenna);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_peak_detection_energy_across_antenna_custom(
   __vptr_int16 inputData,
   __vptr_uint32 outputData,
   unsigned short numRows,
   unsigned short numAntennas,
   unsigned short numHorzPtPerAntenna,
   unsigned short pitch,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_peak_detection_energy_across_antenna_init(inputData, outputData, numRows, numAntennas, numHorzPtPerAntenna, pitch, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_peak_detection_energy_across_antenna_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_peak_detection_binlog_energy_scaling, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_peak_detection_binlog_energy_scaling, __ALIGNOF__(int));
unsigned short __pblock_vcop_peak_detection_binlog_energy_scaling[66];

unsigned int vcop_peak_detection_binlog_energy_scaling_param_count(void)
{
   return 66u;
}

unsigned int vcop_peak_detection_binlog_energy_scaling_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_peak_detection_binlog_energy_scaling_init(
   __vptr_uint32 inputEnergy,
   __vptr_uint16 indexBuf,
   __vptr_uint8 lmbdBuf,
   __vptr_uint16 lutTable,
   __vptr_uint16 lutValue,
   __vptr_uint16 scatterIndex,
   __vptr_uint16 outputEnergy,
   unsigned short outputPitch,
   unsigned char lutQFormat,
   unsigned char alphaQFormat,
   unsigned short numRows,
   unsigned short numHorzPtPerAntenna,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   const int preg_ref2 = _PREG(7);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (numRows/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((numHorzPtPerAntenna/ (8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_SYMM,preg_ref2,RM_NONE,0));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 255);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)inputEnergy);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)inputEnergy+sizeof(*inputEnergy)*numHorzPtPerAntenna);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)lmbdBuf);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)lmbdBuf+sizeof(*lmbdBuf)*numHorzPtPerAntenna);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)indexBuf);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)indexBuf+sizeof(*indexBuf)*numHorzPtPerAntenna);
   __vcop_pblock_init16(pblock, __offset+_PREG(20), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(21), (sizeof(*inputEnergy)*numHorzPtPerAntenna*2) -(8u*sizeof(*inputEnergy))*(((numHorzPtPerAntenna/ (8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(22), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(23), (sizeof(*indexBuf)*numHorzPtPerAntenna*2) -(8u*sizeof(*indexBuf))*(((numHorzPtPerAntenna/ (8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(24), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(25), (sizeof(*lmbdBuf)*numHorzPtPerAntenna*2) -(8u*sizeof(*lmbdBuf))*(((numHorzPtPerAntenna/ (8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(26), 1);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), alphaQFormat);
   __offset += 28;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (((numHorzPtPerAntenna *numRows ) / ((8u))))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)lutValue);
   __vcop_pblock_init16(pblock, __offset+_PREG(8), 16);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)indexBuf);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)lutTable);
   __offset += 12;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (numRows/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((numHorzPtPerAntenna/ (8u)))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)lmbdBuf);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)lmbdBuf+sizeof(*lmbdBuf)*numHorzPtPerAntenna);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)lutValue);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)lutValue+sizeof(*lutValue)*numHorzPtPerAntenna);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)outputEnergy);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)outputEnergy+sizeof(*outputEnergy));
   __vcop_pblock_init16(pblock, __offset+_PREG(18), 8);
   __vcop_pblock_init16(pblock, __offset+_PREG(19), (sizeof(*lmbdBuf)*numHorzPtPerAntenna*2) -(8u*sizeof(*lmbdBuf))*(((numHorzPtPerAntenna/ (8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(20), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(21), (sizeof(*indexBuf)*numHorzPtPerAntenna*2) -(8u*sizeof(*indexBuf))*(((numHorzPtPerAntenna/ (8u)))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(22), (outputPitch*8u));
   __vcop_pblock_init16(pblock, __offset+_PREG(23), (sizeof(*outputEnergy)*2) -(outputPitch*8u)*(((numHorzPtPerAntenna/ (8u)))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)scatterIndex);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), lutQFormat);
   __offset += 26;

   return 66u;
}

void vcop_peak_detection_binlog_energy_scaling_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VInEnergy1", 16);
   #pragma VCC_VREG("VInEnergy2", 17);
   #pragma VCC_VREG("VIndex1", 18);
   #pragma VCC_VREG("VIndex2", 19);
   #pragma VCC_VREG("VK1", 20);
   #pragma VCC_VREG("VM1", 21);
   #pragma VCC_VREG("VM2", 22);
   #pragma VCC_VREG("VN", 23);
   #pragma VCC_VREG("VScatterIndex", 24);
   #pragma VCC_VREG("VShift1", 25);
   #pragma VCC_VREG("VShift2", 26);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   #pragma EVE_REG("inAddr", "A1");
   #pragma EVE_REG("indexAddr", "A2");
   #pragma EVE_REG("lmbdAddr", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("rowIdx", "I3");
   #pragma EVE_REG("idx", "I4");
   

   __vcop_vloop(__vcop_compute(), 19u, 14u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(26), _VREG(20));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(28), _VREG(23));
   __vcop_vagen(_AGEN(1), _PREG(20), _PREG(21), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(22), _PREG(23), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(24), _PREG(25), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(8), _AGEN(1), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(10), _AGEN(1), _VREG(17), __vcop_alws());
   __vcop_vlmbd(_VREG(16), _VREG(20), _VREG(21));
   __vcop_vlmbd(_VREG(17), _VREG(20), _VREG(22));
   __vcop_vsub(_VREG(23), _VREG(21), _VREG(25));
   __vcop_vsub(_VREG(23), _VREG(22), _VREG(26));
   __vcop_vshf(_VREG(16), _VREG(25), _VREG(18));
   __vcop_vshf(_VREG(17), _VREG(26), _VREG(19));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(21), _PREG(12), _AGEN(3), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_npt(), __vcop_alws(), _VREG(22), _PREG(14), _AGEN(3), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(18), _PREG(16), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(19), _PREG(18), _AGEN(2), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VIndex", 27);
   #pragma VCC_VREG("VLUTvalue", 28);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("indexAddr", "A0");
   #pragma EVE_REG("outAddr", "A2");
   #pragma EVE_REG("tableAddr", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("idx", "I4");
   

   __vcop_vloop(__vcop_tablelkup(), 7u, 6u, 2u);
   __vcop_vagen(_AGEN(0), _PREG(8), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(8), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(10), _AGEN(0), _VREG(27), __vcop_alws());
   __vcop_vtbload(__vcop_sizeHU(), __vcop_tableinfo(8, 1), _PREG(12), _AGEN(1), _VREG(27), _VREG(28), _PREG(0), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(28), _PREG(6), _AGEN(2), _PREG(0));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VIndex", 29);
   #pragma VCC_VREG("VLutQFormat", 30);
   #pragma VCC_VREG("VLutValue1", 31);
   #pragma VCC_VREG("VLutValue2", 32);
   #pragma VCC_VREG("VOutEnergy1", 33);
   #pragma VCC_VREG("VOutEnergy2", 34);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   #pragma EVE_REG("lmbdAddr", "A1");
   #pragma EVE_REG("lutValAddr", "A2");
   #pragma EVE_REG("outAddr", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("rowIdx", "I3");
   #pragma EVE_REG("idx", "I4");
   

   __vcop_vloop(__vcop_compute(), 17u, 13u, 3u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(26), _VREG(30));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(18), _PREG(19), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(20), _PREG(21), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(22), _PREG(23), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(24), _AGEN(0), _VREG(24), __vcop_once());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(6), _AGEN(1), _VREG(21), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(8), _AGEN(1), _VREG(22), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(10), _AGEN(2), _VREG(31), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(12), _AGEN(2), _VREG(32), __vcop_alws());
   __vcop_vshf(_VREG(21), _VREG(30), _VREG(21));
   __vcop_vshf(_VREG(22), _VREG(30), _VREG(22));
   __vcop_vadd(_VREG(21), _VREG(31), _VREG(33));
   __vcop_vadd(_VREG(22), _VREG(32), _VREG(34));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_pdda(_VREG(24)), __vcop_alws(), _VREG(33), _PREG(14), _AGEN(3), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_pdda(_VREG(24)), __vcop_alws(), _VREG(34), _PREG(16), _AGEN(3), _PREG(0));
   __vcop_vloop_end(3u);

}

void vcop_peak_detection_binlog_energy_scaling(
   __vptr_uint32 inputEnergy,
   __vptr_uint16 indexBuf,
   __vptr_uint8 lmbdBuf,
   __vptr_uint16 lutTable,
   __vptr_uint16 lutValue,
   __vptr_uint16 scatterIndex,
   __vptr_uint16 outputEnergy,
   unsigned short outputPitch,
   unsigned char lutQFormat,
   unsigned char alphaQFormat,
   unsigned short numRows,
   unsigned short numHorzPtPerAntenna)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_peak_detection_binlog_energy_scaling_init(inputEnergy, indexBuf, lmbdBuf, lutTable, lutValue, scatterIndex, outputEnergy, outputPitch, lutQFormat, alphaQFormat, numRows, numHorzPtPerAntenna, __pblock_vcop_peak_detection_binlog_energy_scaling);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_peak_detection_binlog_energy_scaling_vloops(__pblock_vcop_peak_detection_binlog_energy_scaling);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_peak_detection_binlog_energy_scaling_custom(
   __vptr_uint32 inputEnergy,
   __vptr_uint16 indexBuf,
   __vptr_uint8 lmbdBuf,
   __vptr_uint16 lutTable,
   __vptr_uint16 lutValue,
   __vptr_uint16 scatterIndex,
   __vptr_uint16 outputEnergy,
   unsigned short outputPitch,
   unsigned char lutQFormat,
   unsigned char alphaQFormat,
   unsigned short numRows,
   unsigned short numHorzPtPerAntenna,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_peak_detection_binlog_energy_scaling_init(inputEnergy, indexBuf, lmbdBuf, lutTable, lutValue, scatterIndex, outputEnergy, outputPitch, lutQFormat, alphaQFormat, numRows, numHorzPtPerAntenna, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_peak_detection_binlog_energy_scaling_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_peak_detection_cell_sum, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_peak_detection_cell_sum, __ALIGNOF__(int));
unsigned short __pblock_vcop_peak_detection_cell_sum[68];

unsigned int vcop_peak_detection_cell_sum_param_count(void)
{
   return 68u;
}

unsigned int vcop_peak_detection_cell_sum_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_peak_detection_cell_sum_init(
   __vptr_uint16 inputEnergy1,
   __vptr_uint16 inputEnergy2,
   __vptr_uint16 cellSum,
   __vptr_uint32 cellSumOneLine,
   unsigned short noiseLen,
   unsigned short gaurdLen,
   unsigned short numHorzPoint,
   unsigned short numVertPoint,
   unsigned short inputDataPitch,
   unsigned short cellSumPitch,
   unsigned short shift,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   const int preg_ref3 = _PREG(7);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (numHorzPoint/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (noiseLen)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_SYMM,preg_ref3,RM_TRUNC,shift));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32767);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)inputEnergy2);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)cellSum+(noiseLen+gaurdLen)*cellSumPitch);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)cellSum+(numVertPoint/2+(noiseLen+gaurdLen))*cellSumPitch);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)cellSumOneLine);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)cellSumOneLine+numHorzPoint*sizeof(*cellSumOneLine));
   __vcop_pblock_init16(pblock, __offset+_PREG(18), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(19), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(20), (inputDataPitch));
   __vcop_pblock_init16(pblock, __offset+_PREG(21), (sizeof(*inputEnergy1)*8u) -(inputDataPitch)*((noiseLen)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(22), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)inputEnergy1);
   __offset += 24;

   /* Loop 2 PREGS */
   const int preg_ref4 = _PREG(7);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (numHorzPoint/ (8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((numVertPoint/2) - 1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_SYMM,preg_ref4,RM_TRUNC,shift));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32767);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)inputEnergy1);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)inputEnergy2);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)inputEnergy1+noiseLen*inputDataPitch);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)inputEnergy2+noiseLen*inputDataPitch);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)cellSum+(noiseLen+gaurdLen+1)*cellSumPitch);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)cellSum+(numVertPoint/2+(noiseLen+gaurdLen)+1)*cellSumPitch);
   __vcop_pblock_init16(pblock, __offset+_PREG(20), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(21), (inputDataPitch));
   __vcop_pblock_init16(pblock, __offset+_PREG(22), (sizeof(*inputEnergy1)*8u) -(inputDataPitch)*(((numVertPoint/2) - 1)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(23), (cellSumPitch));
   __vcop_pblock_init16(pblock, __offset+_PREG(24), (sizeof(*cellSum)*8u) -(cellSumPitch)*(((numVertPoint/2) - 1)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)cellSumOneLine);
   __vcop_pblock_init32(pblock, __offset+_PREG(28), (uchar *)cellSumOneLine+numHorzPoint*sizeof(*cellSumOneLine));
   __offset += 28;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (numHorzPoint/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (noiseLen + gaurdLen)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)cellSum+(numVertPoint-1*(noiseLen+gaurdLen))*cellSumPitch);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)cellSum);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)cellSum+(numVertPoint+1+gaurdLen)*cellSumPitch);
   __vcop_pblock_init16(pblock, __offset+_PREG(12), (cellSumPitch));
   __vcop_pblock_init16(pblock, __offset+_PREG(13), (sizeof(*cellSum)*8u) -(cellSumPitch)*((noiseLen + gaurdLen)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)cellSum+(noiseLen+2*gaurdLen+1)*cellSumPitch);
   __offset += 16;

   return 68u;
}

void vcop_peak_detection_cell_sum_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VOut1", 16);
   #pragma VCC_VREG("VOut2", 17);
   #pragma VCC_VREG("VSum1", 18);
   #pragma VCC_VREG("VSum2", 19);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VIn1", 20);
   #pragma VCC_VREG("VIn2", 21);
   #pragma VCC_VREG("VInPlusN1", 22);
   #pragma VCC_VREG("VInPlusN2", 23);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   #pragma EVE_REG("addrOut1", "A1");
   #pragma EVE_REG("addrOut2", "A2");
   #pragma EVE_REG("addrIn", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("horzIdx", "I3");
   #pragma EVE_REG("idx", "I4");
   

   __vcop_vloop(__vcop_compute(), 15u, 12u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(22), _VREG(18));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(22), _VREG(19));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(18), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(0), _PREG(19), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(20), _PREG(21), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(24), _AGEN(3), _VREG(20), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(8), _AGEN(3), _VREG(21), __vcop_alws());
   __vcop_vadd(_VREG(18), _VREG(20), _VREG(18));
   __vcop_vadd(_VREG(19), _VREG(21), _VREG(19));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_last_i4(), _VREG(18), _PREG(10), _AGEN(1), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_last_i4(), _VREG(19), _PREG(12), _AGEN(1), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_last_i4(), _VREG(18), _PREG(14), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_last_i4(), _VREG(19), _PREG(16), _AGEN(2), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VIn1", 24);
   #pragma VCC_VREG("VIn2", 25);
   #pragma VCC_VREG("VInPlusN1", 26);
   #pragma VCC_VREG("VInPlusN2", 27);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   #pragma EVE_REG("addrFirstRow", "A1");
   #pragma EVE_REG("addrIn", "A2");
   #pragma EVE_REG("addrOut", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("horzIdx", "I3");
   #pragma EVE_REG("vertIdx", "I4");
   

   __vcop_vloop(__vcop_compute(), 17u, 14u, 2u);
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(20), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(21), _PREG(22), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(23), _PREG(24), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(26), _AGEN(1), _VREG(18), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(28), _AGEN(1), _VREG(19), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(8), _AGEN(2), _VREG(24), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(10), _AGEN(2), _VREG(25), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(12), _AGEN(2), _VREG(26), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(14), _AGEN(2), _VREG(27), __vcop_alws());
   __vcop_vsub(_VREG(18), _VREG(24), _VREG(18));
   __vcop_vsub(_VREG(19), _VREG(25), _VREG(19));
   __vcop_vadd(_VREG(18), _VREG(26), _VREG(18));
   __vcop_vadd(_VREG(19), _VREG(27), _VREG(19));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(18), _PREG(16), _AGEN(3), _PREG(6));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(19), _PREG(18), _AGEN(3), _PREG(6));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VIn1", 28);
   #pragma VCC_VREG("VIn2", 29);
   #pragma VCC_VREG("VInPlusN1", 30);
   #pragma VCC_VREG("VInPlusN2", 31);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   #pragma EVE_REG("addrOut", "A1");
   #pragma EVE_REG("addrIn", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("horzIdx", "I3");
   #pragma EVE_REG("idx", "I4");
   

   __vcop_vloop(__vcop_compute(), 10u, 8u, 3u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(14), _VREG(18));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(14), _VREG(19));
   __vcop_vagen(_AGEN(1), _PREG(12), _PREG(13), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(12), _PREG(13), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(16), _AGEN(2), _VREG(28), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(6), _AGEN(2), _VREG(29), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(28), _PREG(8), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(29), _PREG(10), _AGEN(1), _PREG(0));
   __vcop_vloop_end(3u);

}

void vcop_peak_detection_cell_sum(
   __vptr_uint16 inputEnergy1,
   __vptr_uint16 inputEnergy2,
   __vptr_uint16 cellSum,
   __vptr_uint32 cellSumOneLine,
   unsigned short noiseLen,
   unsigned short gaurdLen,
   unsigned short numHorzPoint,
   unsigned short numVertPoint,
   unsigned short inputDataPitch,
   unsigned short cellSumPitch,
   unsigned short shift)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_peak_detection_cell_sum_init(inputEnergy1, inputEnergy2, cellSum, cellSumOneLine, noiseLen, gaurdLen, numHorzPoint, numVertPoint, inputDataPitch, cellSumPitch, shift, __pblock_vcop_peak_detection_cell_sum);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_peak_detection_cell_sum_vloops(__pblock_vcop_peak_detection_cell_sum);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_peak_detection_cell_sum_custom(
   __vptr_uint16 inputEnergy1,
   __vptr_uint16 inputEnergy2,
   __vptr_uint16 cellSum,
   __vptr_uint32 cellSumOneLine,
   unsigned short noiseLen,
   unsigned short gaurdLen,
   unsigned short numHorzPoint,
   unsigned short numVertPoint,
   unsigned short inputDataPitch,
   unsigned short cellSumPitch,
   unsigned short shift,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_peak_detection_cell_sum_init(inputEnergy1, inputEnergy2, cellSum, cellSumOneLine, noiseLen, gaurdLen, numHorzPoint, numVertPoint, inputDataPitch, cellSumPitch, shift, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_peak_detection_cell_sum_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_peak_detection_CFARCA_thresholding, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_peak_detection_CFARCA_thresholding, __ALIGNOF__(int));
unsigned short __pblock_vcop_peak_detection_CFARCA_thresholding[76];

unsigned int vcop_peak_detection_CFARCA_thresholding_param_count(void)
{
   return 76u;
}

unsigned int vcop_peak_detection_CFARCA_thresholding_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_peak_detection_CFARCA_thresholding_init(
   __vptr_uint16 inputEnergy,
   __vptr_uint16 cellSum,
   __vptr_uint8 binaryMask,
   __vptr_uint32 outRangeDopplerBuf,
   __vptr_uint16 outEnergyBuf,
   __vptr_uint32 idxBuf,
   __vptr_uint32 horzIdxOffsetBuf,
   __vptr_uint16 numDetections,
   unsigned int offsetBwTwoInBuf,
   unsigned short noiseLen,
   unsigned short gaurdLen,
   unsigned short numHorzPointActual,
   unsigned short numHorzPoint,
   unsigned short numVertPointActual,
   unsigned short numVertPoint,
   unsigned short cellSumPitchActual,
   unsigned short cellSumPitch,
   unsigned short inputDataPitchActual,
   unsigned short inputDataPitch,
   unsigned short vertCoordinateShift,
   unsigned short horzIdxUpdateOffset,
   signed short threshold,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (numHorzPoint /(2*(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (numVertPoint/2)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)inputEnergy);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), threshold);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)binaryMask);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), (inputDataPitch));
   __vcop_pblock_init16(pblock, __offset+_PREG(15), ((2*8u)*sizeof(*inputEnergy)) -(inputDataPitch)*((numVertPoint/2)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(16), (offsetBwTwoInBuf) -((2*8u)*sizeof(*inputEnergy))*((numHorzPoint /(2*(8u)))-1u) -(inputDataPitch)*((numVertPoint/2)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(17), (numHorzPoint*sizeof(*binaryMask)));
   __vcop_pblock_init16(pblock, __offset+_PREG(18), ((2*8u)*sizeof(*binaryMask)) -(numHorzPoint*sizeof(*binaryMask))*((numVertPoint/2)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(19), ((numVertPoint/2)*numHorzPoint*sizeof(*binaryMask)) -((2*8u)*sizeof(*binaryMask))*((numHorzPoint /(2*(8u)))-1u) -(numHorzPoint*sizeof(*binaryMask))*((numVertPoint/2)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(20), (cellSumPitch));
   __vcop_pblock_init16(pblock, __offset+_PREG(21), ((2*8u)*sizeof(*cellSum)) -(cellSumPitch)*((numVertPoint/2)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(22), ((numVertPoint/2)*cellSumPitch) -((2*8u)*sizeof(*cellSum))*((numHorzPoint /(2*(8u)))-1u) -(cellSumPitch)*((numVertPoint/2)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)cellSum);
   __vcop_pblock_init32(pblock, __offset+_PREG(26), (uchar *)cellSum+(noiseLen+(2*gaurdLen+1))*cellSumPitchActual);
   __offset += 26;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), (2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (numHorzPointActual / (8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (numVertPointActual/2)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), vertCoordinateShift);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (2000 / (8u)));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)horzIdxOffsetBuf);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)idxBuf);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)binaryMask);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)inputEnergy);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (uchar *)outRangeDopplerBuf);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)outEnergyBuf);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)numDetections);
   __vcop_pblock_init16(pblock, __offset+_PREG(26), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(27), (numHorzPointActual*sizeof(*idxBuf)) -(8u*sizeof(*idxBuf))*((numHorzPointActual / (8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(28), (inputDataPitchActual));
   __vcop_pblock_init16(pblock, __offset+_PREG(29), (8u*sizeof(*inputEnergy)) -(inputDataPitchActual)*((numVertPointActual/2)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(30), (offsetBwTwoInBuf) -(8u*sizeof(*inputEnergy))*((numHorzPointActual / (8u))-1u) -(inputDataPitchActual)*((numVertPointActual/2)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(31), (numHorzPointActual*sizeof(*binaryMask)));
   __vcop_pblock_init16(pblock, __offset+_PREG(32), (8u*sizeof(*binaryMask)) -(numHorzPointActual*sizeof(*binaryMask))*((numVertPointActual/2)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(33), (numHorzPointActual*sizeof(*binaryMask)*(numVertPointActual/2)) -(8u*sizeof(*binaryMask))*((numHorzPointActual / (8u))-1u) -(numHorzPointActual*sizeof(*binaryMask))*((numVertPointActual/2)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(34), noiseLen);
   __vcop_pblock_init32(pblock, __offset+_PREG(36), gaurdLen);
   __offset += 36;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (1)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (8)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)numDetections);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 2);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), -14);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)horzIdxOffsetBuf);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), horzIdxUpdateOffset);
   __offset += 14;

   return 76u;
}

void vcop_peak_detection_CFARCA_thresholding_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VCurrHorzIdx", 16);
   #pragma VCC_VREG("VCutVal1", 17);
   #pragma VCC_VREG("VCutVal2", 18);
   #pragma VCC_VREG("VEnergy", 19);
   #pragma VCC_VREG("VExitCondition", 20);
   #pragma VCC_VREG("VFinalHorzIdx", 21);
   #pragma VCC_VREG("VGaurdLen", 22);
   #pragma VCC_VREG("VHorzIdx", 23);
   #pragma VCC_VREG("VLeftNoiseFloor1", 24);
   #pragma VCC_VREG("VLeftNoiseFloor2", 25);
   #pragma VCC_VREG("VMask", 26);
   #pragma VCC_VREG("VMask1", 27);
   #pragma VCC_VREG("VMask2", 28);
   #pragma VCC_VREG("VMaxNumDetections", 29);
   #pragma VCC_VREG("VNoiseFloor1", 30);
   #pragma VCC_VREG("VNoiseFloor2", 31);
   #pragma VCC_VREG("VNoiseLen", 32);
   #pragma VCC_VREG("VNumDetections", 33);
   #pragma VCC_VREG("VNumHorzPt", 34);
   #pragma VCC_VREG("VRangeDoppler", 35);
   #pragma VCC_VREG("VRightNoiseFloor1", 36);
   #pragma VCC_VREG("VRightNoiseFloor2", 37);
   #pragma VCC_VREG("VThreshold", 38);
   #pragma VCC_VREG("VUpdateDopplerIdx", 39);
   #pragma VCC_VREG("VVertCoordinateShift", 40);
   #pragma VCC_VREG("VVertIdx", 41);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   #pragma EVE_REG("addrEnergy", "A1");
   #pragma EVE_REG("addrMask", "A2");
   #pragma EVE_REG("addrNoiseFloor", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("bufIdx", "I2");
   #pragma EVE_REG("dopplerIdx", "I3");
   #pragma EVE_REG("rangeIdx", "I4");
   

   __vcop_vloop(__vcop_compute(), 18u, 13u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(8), _VREG(38));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(10), _VREG(27));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(10), _VREG(28));
   __vcop_vagen(_AGEN(1), _PREG(14), _PREG(15), _PREG(16), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(17), _PREG(18), _PREG(19), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(20), _PREG(21), _PREG(22), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(24), _AGEN(3), _VPAIR(24,25), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(26), _AGEN(3), _VPAIR(36,37), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(6), _AGEN(1), _VPAIR(17,18), __vcop_alws());
   __vcop_vadd(_VREG(24), _VREG(36), _VREG(30));
   __vcop_vadd(_VREG(25), _VREG(37), _VREG(31));
   __vcop_vsub(_VREG(17), _VREG(30), _VREG(17));
   __vcop_vsub(_VREG(18), _VREG(31), _VREG(18));
   __vcop_vcmpgt(_VREG(17), _VREG(38), _VREG(27));
   __vcop_vcmpgt(_VREG(18), _VREG(38), _VREG(28));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeBU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(27,28), _PREG(12), _AGEN(2), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   #pragma EVE_REG("addrIdx", "A1");
   #pragma EVE_REG("addrEnergy", "A2");
   #pragma EVE_REG("addrMask", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("bufIdx", "I2");
   #pragma EVE_REG("horzIdx", "I3");
   #pragma EVE_REG("vertIdx", "I4");
   

   __vcop_vloop(__vcop_compute(), 25u, 18u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(34), _VREG(32));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(36), _VREG(22));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(6), _VREG(40));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(8), _VREG(20));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(8), _VREG(33));
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(10), _VREG(29));
   __vcop_vinit(__vcop_sizeHU(), __vcop_alws(), _PREG(68), _VREG(41));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(26), _PREG(27), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(28), _PREG(29), _PREG(30), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(31), _PREG(32), _PREG(33), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_1pt(), _PREG(12), _AGEN(0), _VREG(16), __vcop_once());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(14), _AGEN(1), _VREG(23), __vcop_i4_zero());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(16), _AGEN(3), _VREG(26), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(18), _AGEN(2), _VREG(19), __vcop_alws());
   __vcop_vshf(_VREG(41), _VREG(40), _VREG(41));
   __vcop_vadd(_VREG(23), _VREG(16), _VREG(21));
   __vcop_vadd(_VREG(41), _VREG(21), _VREG(35));
   __vcop_vadd(_VREG(33), _VREG(26), _VREG(33));
   __vcop_vbitpk(_VREG(33), _VREG(29), _VREG(20));
   __vcop_vexitnz(__vcop_level_vloop(), _VREG(20));
   __vcop_vstore(__vcop_predicate(_VREG(26)), __vcop_sizeWU(), __vcop_collat(), __vcop_alws(), _VREG(35), _PREG(20), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_predicate(_VREG(26)), __vcop_sizeHU(), __vcop_collat(), __vcop_alws(), _VREG(19), _PREG(22), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(33), _PREG(24), _AGEN(0), _PREG(0));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VTotalDetections", 42);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   #pragma EVE_REG("addrIn", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("i", "I3");
   #pragma EVE_REG("j", "I4");
   

   __vcop_vloop(__vcop_compute(), 11u, 7u, 3u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(14), _VREG(34));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(6), _VREG(42));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(10), _PREG(11), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_1pt(), _PREG(12), _AGEN(0), _VREG(16), __vcop_once());
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(8), _AGEN(1), _VREG(33), __vcop_alws());
   __vcop_vadd(_VREG(42), _VREG(33), _VREG(42));
   __vcop_vadd(_VREG(16), _VREG(34), _VREG(39));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_1pt(), __vcop_last_i4(), _VREG(42), _PREG(8), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_1pt(), __vcop_last_i4(), _VREG(39), _PREG(12), _AGEN(0), _PREG(0));
   __vcop_vloop_end(3u);

}

void vcop_peak_detection_CFARCA_thresholding(
   __vptr_uint16 inputEnergy,
   __vptr_uint16 cellSum,
   __vptr_uint8 binaryMask,
   __vptr_uint32 outRangeDopplerBuf,
   __vptr_uint16 outEnergyBuf,
   __vptr_uint32 idxBuf,
   __vptr_uint32 horzIdxOffsetBuf,
   __vptr_uint16 numDetections,
   unsigned int offsetBwTwoInBuf,
   unsigned short noiseLen,
   unsigned short gaurdLen,
   unsigned short numHorzPointActual,
   unsigned short numHorzPoint,
   unsigned short numVertPointActual,
   unsigned short numVertPoint,
   unsigned short cellSumPitchActual,
   unsigned short cellSumPitch,
   unsigned short inputDataPitchActual,
   unsigned short inputDataPitch,
   unsigned short vertCoordinateShift,
   unsigned short horzIdxUpdateOffset,
   signed short threshold)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_peak_detection_CFARCA_thresholding_init(inputEnergy, cellSum, binaryMask, outRangeDopplerBuf, outEnergyBuf, idxBuf, horzIdxOffsetBuf, numDetections, offsetBwTwoInBuf, noiseLen, gaurdLen, numHorzPointActual, numHorzPoint, numVertPointActual, numVertPoint, cellSumPitchActual, cellSumPitch, inputDataPitchActual, inputDataPitch, vertCoordinateShift, horzIdxUpdateOffset, threshold, __pblock_vcop_peak_detection_CFARCA_thresholding);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_peak_detection_CFARCA_thresholding_vloops(__pblock_vcop_peak_detection_CFARCA_thresholding);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_peak_detection_CFARCA_thresholding_custom(
   __vptr_uint16 inputEnergy,
   __vptr_uint16 cellSum,
   __vptr_uint8 binaryMask,
   __vptr_uint32 outRangeDopplerBuf,
   __vptr_uint16 outEnergyBuf,
   __vptr_uint32 idxBuf,
   __vptr_uint32 horzIdxOffsetBuf,
   __vptr_uint16 numDetections,
   unsigned int offsetBwTwoInBuf,
   unsigned short noiseLen,
   unsigned short gaurdLen,
   unsigned short numHorzPointActual,
   unsigned short numHorzPoint,
   unsigned short numVertPointActual,
   unsigned short numVertPoint,
   unsigned short cellSumPitchActual,
   unsigned short cellSumPitch,
   unsigned short inputDataPitchActual,
   unsigned short inputDataPitch,
   unsigned short vertCoordinateShift,
   unsigned short horzIdxUpdateOffset,
   signed short threshold,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_peak_detection_CFARCA_thresholding_init(inputEnergy, cellSum, binaryMask, outRangeDopplerBuf, outEnergyBuf, idxBuf, horzIdxOffsetBuf, numDetections, offsetBwTwoInBuf, noiseLen, gaurdLen, numHorzPointActual, numHorzPoint, numVertPointActual, numVertPoint, cellSumPitchActual, cellSumPitch, inputDataPitchActual, inputDataPitch, vertCoordinateShift, horzIdxUpdateOffset, threshold, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_peak_detection_CFARCA_thresholding_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_peak_detection_transpose, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_peak_detection_transpose, __ALIGNOF__(int));
unsigned short __pblock_vcop_peak_detection_transpose[46];

unsigned int vcop_peak_detection_transpose_param_count(void)
{
   return 46u;
}

unsigned int vcop_peak_detection_transpose_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_peak_detection_transpose_init(
   __vptr_uint16 inputEnergy1,
   __vptr_uint16 inputEnergy2,
   __vptr_uint16 outputEnergy,
   __vptr_uint16 scatterIndex,
   unsigned short numHorzPoint,
   unsigned short numVertPoint,
   unsigned short transposePitch,
   unsigned short numExtraLines,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (numHorzPoint/(2 * (8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((numVertPoint))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)inputEnergy2);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)outputEnergy);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)outputEnergy+transposePitch*(numHorzPoint/2));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), ((numHorzPoint/2)*sizeof(*inputEnergy1)));
   __vcop_pblock_init16(pblock, __offset+_PREG(13), (8u*sizeof(*inputEnergy1)) -((numHorzPoint/2)*sizeof(*inputEnergy1))*(((numVertPoint))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(14), 2);
   __vcop_pblock_init16(pblock, __offset+_PREG(15), (8u*transposePitch) -(sizeof(*outputEnergy))*(((numVertPoint))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)scatterIndex);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), (uchar *)inputEnergy1);
   __offset += 18;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (numVertPoint/ (2*(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((numHorzPoint/2))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)inputEnergy1);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)inputEnergy2);
   __vcop_pblock_init16(pblock, __offset+_PREG(10), (transposePitch));
   __vcop_pblock_init16(pblock, __offset+_PREG(11), ((2*8u)*sizeof(*outputEnergy)) -(transposePitch)*(((numHorzPoint/2))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), (numVertPoint*sizeof(*inputEnergy1)));
   __vcop_pblock_init16(pblock, __offset+_PREG(13), ((2*8u)*sizeof(*inputEnergy1)) -(numVertPoint*sizeof(*inputEnergy1))*(((numHorzPoint/2))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)outputEnergy);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)outputEnergy+transposePitch*(numHorzPoint/2));
   __offset += 16;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (numVertPoint/ (2*(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (numExtraLines)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), (transposePitch));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), ((2*8u)*sizeof(*outputEnergy)) -(transposePitch)*((numExtraLines)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(8), (numVertPoint*sizeof(*inputEnergy1)));
   __vcop_pblock_init16(pblock, __offset+_PREG(9), ((2*8u)*sizeof(*inputEnergy1)) -(numVertPoint*sizeof(*inputEnergy1))*((numExtraLines)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)outputEnergy+numHorzPoint/2*transposePitch);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)inputEnergy1+numHorzPoint/2*numVertPoint*sizeof(*inputEnergy1));
   __offset += 12;

   return 46u;
}

void vcop_peak_detection_transpose_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VIn1", 16);
   #pragma VCC_VREG("VIn2", 17);
   #pragma VCC_VREG("VIn3", 18);
   #pragma VCC_VREG("VIn4", 19);
   #pragma VCC_VREG("VIn5", 20);
   #pragma VCC_VREG("VIn6", 21);
   #pragma VCC_VREG("VScatterIndex", 22);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   #pragma EVE_REG("addrIn", "A1");
   #pragma EVE_REG("addrOut", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("horzIdx", "I3");
   #pragma EVE_REG("vertIdx", "I4");
   

   __vcop_vloop(__vcop_compute(), 9u, 9u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(12), _PREG(13), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(14), _PREG(15), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(16), _AGEN(0), _VREG(22), __vcop_once());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(18), _AGEN(1), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(6), _AGEN(1), _VREG(17), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_pdda(_VREG(22)), __vcop_alws(), _VREG(16), _PREG(8), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_pdda(_VREG(22)), __vcop_alws(), _VREG(17), _PREG(10), _AGEN(2), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   #pragma EVE_REG("addrIn", "A1");
   #pragma EVE_REG("addrOut", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("horzIdx", "I3");
   #pragma EVE_REG("vertIdx", "I4");
   

   __vcop_vloop(__vcop_compute(), 8u, 8u, 2u);
   __vcop_vagen(_AGEN(1), _PREG(10), _PREG(11), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(12), _PREG(13), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(14), _AGEN(1), _VPAIR(18,19), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(16), _AGEN(1), _VPAIR(20,21), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(18,19), _PREG(6), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(20,21), _PREG(8), _AGEN(2), _PREG(0));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   #pragma EVE_REG("addrIn", "A1");
   #pragma EVE_REG("addrOut", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("horzIdx", "I3");
   #pragma EVE_REG("vertIdx", "I4");
   

   __vcop_vloop(__vcop_compute(), 6u, 6u, 3u);
   __vcop_vagen(_AGEN(1), _PREG(6), _PREG(7), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(8), _PREG(9), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(10), _AGEN(1), _VPAIR(18,19), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_intrlv(), __vcop_alws(), _VPAIR(18,19), _PREG(12), _AGEN(2), _PREG(0));
   __vcop_vloop_end(3u);

}

void vcop_peak_detection_transpose(
   __vptr_uint16 inputEnergy1,
   __vptr_uint16 inputEnergy2,
   __vptr_uint16 outputEnergy,
   __vptr_uint16 scatterIndex,
   unsigned short numHorzPoint,
   unsigned short numVertPoint,
   unsigned short transposePitch,
   unsigned short numExtraLines)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_peak_detection_transpose_init(inputEnergy1, inputEnergy2, outputEnergy, scatterIndex, numHorzPoint, numVertPoint, transposePitch, numExtraLines, __pblock_vcop_peak_detection_transpose);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_peak_detection_transpose_vloops(__pblock_vcop_peak_detection_transpose);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_peak_detection_transpose_custom(
   __vptr_uint16 inputEnergy1,
   __vptr_uint16 inputEnergy2,
   __vptr_uint16 outputEnergy,
   __vptr_uint16 scatterIndex,
   unsigned short numHorzPoint,
   unsigned short numVertPoint,
   unsigned short transposePitch,
   unsigned short numExtraLines,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_peak_detection_transpose_init(inputEnergy1, inputEnergy2, outputEnergy, scatterIndex, numHorzPoint, numVertPoint, transposePitch, numExtraLines, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_peak_detection_transpose_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

