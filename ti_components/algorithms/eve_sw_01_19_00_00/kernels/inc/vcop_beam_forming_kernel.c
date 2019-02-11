#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_beam_forming_copy_steering_matrix_kernel, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_beam_forming_copy_steering_matrix_kernel, __ALIGNOF__(int));
unsigned short __pblock_vcop_beam_forming_copy_steering_matrix_kernel[10];

unsigned int vcop_beam_forming_copy_steering_matrix_kernel_param_count(void)
{
   return 10u;
}

unsigned int vcop_beam_forming_copy_steering_matrix_kernel_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_beam_forming_copy_steering_matrix_kernel_init(
   __vptr_uint32 inputData,
   __vptr_uint32 outputData,
   unsigned short numAngles,
   unsigned short numAntennas,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((numAngles * numAntennas) + (8u)-1U) & ~((8u)-1U))/ (8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)inputData);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)outputData);
   __offset += 10;

   return 10u;
}

void vcop_beam_forming_copy_steering_matrix_kernel_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vin", 16);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("inOutAddr", "A0");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("i", "I4");
   

   __vcop_vloop(__vcop_compute(), 4u, 5u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(6), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(8), _AGEN(0), _VREG(16), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(16), _PREG(10), _AGEN(0), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_beam_forming_copy_steering_matrix_kernel(
   __vptr_uint32 inputData,
   __vptr_uint32 outputData,
   unsigned short numAngles,
   unsigned short numAntennas)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_beam_forming_copy_steering_matrix_kernel_init(inputData, outputData, numAngles, numAntennas, __pblock_vcop_beam_forming_copy_steering_matrix_kernel);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_beam_forming_copy_steering_matrix_kernel_vloops(__pblock_vcop_beam_forming_copy_steering_matrix_kernel);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_beam_forming_copy_steering_matrix_kernel_custom(
   __vptr_uint32 inputData,
   __vptr_uint32 outputData,
   unsigned short numAngles,
   unsigned short numAntennas,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_beam_forming_copy_steering_matrix_kernel_init(inputData, outputData, numAngles, numAntennas, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_beam_forming_copy_steering_matrix_kernel_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_beam_forming_transpose_antenna_data_kernel, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_beam_forming_transpose_antenna_data_kernel, __ALIGNOF__(int));
unsigned short __pblock_vcop_beam_forming_transpose_antenna_data_kernel[14];

unsigned int vcop_beam_forming_transpose_antenna_data_kernel_param_count(void)
{
   return 14u;
}

unsigned int vcop_beam_forming_transpose_antenna_data_kernel_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_beam_forming_transpose_antenna_data_kernel_init(
   __vptr_uint32 inputData,
   __vptr_uint32 outputData,
   __vptr_uint16 pScatterIndex,
   unsigned short outputPitch,
   unsigned short numDetections,
   unsigned short numAntennas,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (numDetections)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((numAntennas) + (8u)-1U) & ~((8u)-1U))/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)outputData);
   __vcop_pblock_init16(pblock, __offset+_PREG(8), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(9), (numAntennas*sizeof(*inputData)) -(8u*sizeof(*inputData))*(((((numAntennas) + (8u)-1U) & ~((8u)-1U))/(8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(10), (outputPitch*8u));
   __vcop_pblock_init16(pblock, __offset+_PREG(11), (sizeof(*outputData)) -(outputPitch*8u)*(((((numAntennas) + (8u)-1U) & ~((8u)-1U))/(8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pScatterIndex);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)inputData);
   __offset += 14;

   return 14u;
}

void vcop_beam_forming_transpose_antenna_data_kernel_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VIndex", 16);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Vin", 17);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   #pragma EVE_REG("inAddr", "A1");
   #pragma EVE_REG("outAddr", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("detectionIdx", "I3");
   #pragma EVE_REG("antennaIdx", "I4");
   

   __vcop_vloop(__vcop_compute(), 7u, 7u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(8), _PREG(9), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(10), _PREG(11), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(12), _AGEN(0), _VREG(16), __vcop_once());
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(14), _AGEN(1), _VREG(17), __vcop_alws());
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_pdda(_VREG(16)), __vcop_alws(), _VREG(17), _PREG(6), _AGEN(2), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_beam_forming_transpose_antenna_data_kernel(
   __vptr_uint32 inputData,
   __vptr_uint32 outputData,
   __vptr_uint16 pScatterIndex,
   unsigned short outputPitch,
   unsigned short numDetections,
   unsigned short numAntennas)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_beam_forming_transpose_antenna_data_kernel_init(inputData, outputData, pScatterIndex, outputPitch, numDetections, numAntennas, __pblock_vcop_beam_forming_transpose_antenna_data_kernel);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_beam_forming_transpose_antenna_data_kernel_vloops(__pblock_vcop_beam_forming_transpose_antenna_data_kernel);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_beam_forming_transpose_antenna_data_kernel_custom(
   __vptr_uint32 inputData,
   __vptr_uint32 outputData,
   __vptr_uint16 pScatterIndex,
   unsigned short outputPitch,
   unsigned short numDetections,
   unsigned short numAntennas,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_beam_forming_transpose_antenna_data_kernel_init(inputData, outputData, pScatterIndex, outputPitch, numDetections, numAntennas, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_beam_forming_transpose_antenna_data_kernel_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_beam_forming_kernel, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_beam_forming_kernel, __ALIGNOF__(int));
unsigned short __pblock_vcop_beam_forming_kernel[24];

unsigned int vcop_beam_forming_kernel_param_count(void)
{
   return 24u;
}

unsigned int vcop_beam_forming_kernel_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_beam_forming_kernel_init(
   __vptr_int16 inputData,
   __vptr_int16 outputData,
   __vptr_int16 steeringMatrix,
   unsigned short pitch,
   unsigned short numDetections,
   unsigned short numAntennas,
   unsigned short numAngles,
   unsigned short scale,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   const int preg_ref1 = _PREG(7);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), ((((numDetections) + (8u)-1U) & ~((8u)-1U))/ (8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (numAngles)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (numAntennas)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_ASYMM,preg_ref1,RM_ROUND,scale));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 32767);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)steeringMatrix);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)steeringMatrix+sizeof(*steeringMatrix));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)outputData);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), (pitch));
   __vcop_pblock_init16(pblock, __offset+_PREG(15),  -(pitch)*((numAntennas)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(16), (sizeof(*inputData)*2*8u) -(pitch)*((numAntennas)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(17), (sizeof(*outputData)*2*numDetections));
   __vcop_pblock_init16(pblock, __offset+_PREG(18), (sizeof(*outputData)*2*8u) -(sizeof(*outputData)*2*numDetections)*((numAngles)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(19), 4);
   __vcop_pblock_init16(pblock, __offset+_PREG(20), (sizeof(*steeringMatrix)*2*numAntennas) -(sizeof(*steeringMatrix)*2)*((numAntennas)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(21),  -(sizeof(*steeringMatrix)*2*numAntennas)*((numAngles)-1u) -(sizeof(*steeringMatrix)*2)*((numAntennas)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(22), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(24), (uchar *)inputData);
   __offset += 24;

   return 24u;
}

void vcop_beam_forming_kernel_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VInDataImg", 16);
   #pragma VCC_VREG("VInDataReal", 17);
   #pragma VCC_VREG("VOutDataImg", 18);
   #pragma VCC_VREG("VOutDataReal", 19);
   #pragma VCC_VREG("VSmDataImg", 20);
   #pragma VCC_VREG("VSmDataReal", 21);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("inAddr", "A0");
   #pragma EVE_REG("outAddr", "A1");
   #pragma EVE_REG("smAddr", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("detectionIdx", "I2");
   #pragma EVE_REG("angleIdx", "I3");
   #pragma EVE_REG("antennaIdx", "I4");
   

   __vcop_vloop(__vcop_compute(), 14u, 12u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(22), _VREG(19));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(22), _VREG(18));
   __vcop_vagen(_AGEN(0), _PREG(14), _PREG(15), _PREG(16), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(17), _PREG(18), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(19), _PREG(20), _PREG(21), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(24), _AGEN(0), _VPAIR(17,16), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_1pt(), _PREG(8), _AGEN(2), _VREG(21), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_1pt(), _PREG(10), _AGEN(2), _VREG(20), __vcop_alws());
   __vcop_vmadd(_VREG(17), _VREG(21), _VREG(19), _PREG(0));
   __vcop_vmadd(_VREG(17), _VREG(20), _VREG(18), _PREG(0));
   __vcop_vmsub(_VREG(16), _VREG(20), _VREG(19), _PREG(0));
   __vcop_vmadd(_VREG(16), _VREG(21), _VREG(18), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeH(), __vcop_intrlv(), __vcop_last_i4(), _VPAIR(19,18), _PREG(12), _AGEN(1), _PREG(6));
   __vcop_vloop_end(1u);

}

void vcop_beam_forming_kernel(
   __vptr_int16 inputData,
   __vptr_int16 outputData,
   __vptr_int16 steeringMatrix,
   unsigned short pitch,
   unsigned short numDetections,
   unsigned short numAntennas,
   unsigned short numAngles,
   unsigned short scale)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_beam_forming_kernel_init(inputData, outputData, steeringMatrix, pitch, numDetections, numAntennas, numAngles, scale, __pblock_vcop_beam_forming_kernel);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_beam_forming_kernel_vloops(__pblock_vcop_beam_forming_kernel);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_beam_forming_kernel_custom(
   __vptr_int16 inputData,
   __vptr_int16 outputData,
   __vptr_int16 steeringMatrix,
   unsigned short pitch,
   unsigned short numDetections,
   unsigned short numAntennas,
   unsigned short numAngles,
   unsigned short scale,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_beam_forming_kernel_init(inputData, outputData, steeringMatrix, pitch, numDetections, numAntennas, numAngles, scale, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_beam_forming_kernel_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_beam_energy_calculation_kernel, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_beam_energy_calculation_kernel, __ALIGNOF__(int));
unsigned short __pblock_vcop_beam_energy_calculation_kernel[16];

unsigned int vcop_beam_energy_calculation_kernel_param_count(void)
{
   return 16u;
}

unsigned int vcop_beam_energy_calculation_kernel_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_beam_energy_calculation_kernel_init(
   __vptr_int16 inputData,
   __vptr_uint32 outputEnergy,
   unsigned short numDetections,
   unsigned short numAngles,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), (numAngles / 2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((numDetections) + (8u)-1U) & ~((8u)-1U))/ (8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)outputEnergy);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)outputEnergy+numDetections*sizeof(*outputEnergy));
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(11), (sizeof(*inputData)*2*numDetections*2) -(sizeof(*inputData)*2*8u)*(((((numDetections) + (8u)-1U) & ~((8u)-1U))/ (8u))-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(12), (sizeof(*outputEnergy)*numDetections*2) -(sizeof(*outputEnergy)*8u)*(((((numDetections) + (8u)-1U) & ~((8u)-1U))/ (8u))-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)inputData);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)inputData+numDetections*2*sizeof(*inputData));
   __offset += 16;

   return 16u;
}

void vcop_beam_energy_calculation_kernel_vloops(
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
   #pragma EVE_REG("inAddr", "A0");
   #pragma EVE_REG("outAddr", "A1");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("angleIdx", "I3");
   #pragma EVE_REG("detectionIdx", "I4");
   

   __vcop_vloop(__vcop_compute(), 11u, 8u, 1u);
   __vcop_vagen(_AGEN(0), _PREG(10), _PREG(11), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(10), _PREG(12), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(14), _AGEN(0), _VPAIR(18,16), __vcop_alws());
   __vcop_vload(__vcop_sizeH(), __vcop_dintrlv(), _PREG(16), _AGEN(0), _VPAIR(19,17), __vcop_alws());
   __vcop_vmpy(_VREG(18), _VREG(18), _VREG(20), _PREG(0));
   __vcop_vmpy(_VREG(19), _VREG(19), _VREG(21), _PREG(0));
   __vcop_vmadd(_VREG(16), _VREG(16), _VREG(20), _PREG(0));
   __vcop_vmadd(_VREG(17), _VREG(17), _VREG(21), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(20), _PREG(6), _AGEN(1), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_npt(), __vcop_alws(), _VREG(21), _PREG(8), _AGEN(1), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_beam_energy_calculation_kernel(
   __vptr_int16 inputData,
   __vptr_uint32 outputEnergy,
   unsigned short numDetections,
   unsigned short numAngles)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_beam_energy_calculation_kernel_init(inputData, outputEnergy, numDetections, numAngles, __pblock_vcop_beam_energy_calculation_kernel);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_beam_energy_calculation_kernel_vloops(__pblock_vcop_beam_energy_calculation_kernel);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_beam_energy_calculation_kernel_custom(
   __vptr_int16 inputData,
   __vptr_uint32 outputEnergy,
   unsigned short numDetections,
   unsigned short numAngles,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_beam_energy_calculation_kernel_init(inputData, outputEnergy, numDetections, numAngles, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_beam_energy_calculation_kernel_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_beam_angle_association_kernel, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_beam_angle_association_kernel, __ALIGNOF__(int));
unsigned short __pblock_vcop_beam_angle_association_kernel[36];

unsigned int vcop_beam_angle_association_kernel_param_count(void)
{
   return 36u;
}

unsigned int vcop_beam_angle_association_kernel_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_beam_angle_association_kernel_init(
   __vptr_uint32 inputEnergy,
   __vptr_uint16 angleBuf,
   __vptr_uint16 energyBuf,
   __vptr_uint16 ptrToInfoBuffer,
   __vptr_uint32 ptrToParamBlock,
   unsigned short baseAngleOffset,
   unsigned short numDetections,
   unsigned short numAngles,
   unsigned short energyScalingFactor,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   const int preg_ref2 = _PREG(7);

   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((((numDetections) + (8u)-1U) & ~((8u)-1U))/ (8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (numAngles)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(6), __vcop_store_round_sat(SM_SYMM,preg_ref2,RM_ROUND,energyScalingFactor));
   __vcop_pblock_init16(pblock, __offset+_PREG(7), 65535);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)inputEnergy);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)angleBuf);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)energyBuf);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(15), (sizeof(*inputEnergy)*numDetections));
   __vcop_pblock_init16(pblock, __offset+_PREG(16), (sizeof(*inputEnergy)*8u) -(sizeof(*inputEnergy)*numDetections)*((numAngles)-1u));
   __vcop_pblock_init32(pblock, __offset+_PREG(18), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), baseAngleOffset);
   __offset += 20;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (1)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)ptrToParamBlock+20U);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)ptrToParamBlock+36U);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)ptrToInfoBuffer);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)ptrToInfoBuffer+sizeof(*ptrToInfoBuffer));
   __vcop_pblock_init32(pblock, __offset+_PREG(14), 2);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), (uchar *)ptrToParamBlock+16U);
   __offset += 16;

   return 36u;
}

void vcop_beam_angle_association_kernel_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VAngleBufAddr", 16);
   #pragma VCC_VREG("VAngleIdx", 17);
   #pragma VCC_VREG("VAngleOffset", 18);
   #pragma VCC_VREG("VBaseAngleOffset", 19);
   #pragma VCC_VREG("VBaseAngleOffsetUpdate", 20);
   #pragma VCC_VREG("VBaseAngleOffsetValue", 21);
   #pragma VCC_VREG("VBaseDetectionOffset", 22);
   #pragma VCC_VREG("VBaseDetectionOffsetUpdate", 23);
   #pragma VCC_VREG("VDetectionBufAddr", 24);
   #pragma VCC_VREG("VDetectionIdx", 25);
   #pragma VCC_VREG("VEnergyBufAddr", 26);
   #pragma VCC_VREG("VEnergyOffset", 27);
   #pragma VCC_VREG("VFinalDetectionIdx", 28);
   #pragma VCC_VREG("VInputEnergy", 29);
   #pragma VCC_VREG("VK1", 30);
   #pragma VCC_VREG("VK2", 31);
   #pragma VCC_VREG("VK8", 32);
   #pragma VCC_VREG("VMaxAngleIdx", 33);
   #pragma VCC_VREG("VMaxEnergy", 34);
   #pragma VCC_VREG("VMaxEnergyFlag", 35);
   #pragma VCC_VREG("VNumValidDetections", 36);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("angleAddr", "A0");
   #pragma EVE_REG("energyAddr", "A1");
   #pragma EVE_REG("inAddr", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("detectionIdx", "I3");
   #pragma EVE_REG("angleIdx", "I4");
   

   __vcop_vloop(__vcop_compute(), 14u, 10u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(18), _VREG(34));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(20), _VREG(33));
   __vcop_vinit(__vcop_sizeHU(), __vcop_alws(), _PREG(68), _VREG(17));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(20), _VREG(19));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(14), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(0), _PREG(14), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(15), _PREG(16), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_npt(), _PREG(8), _AGEN(2), _VREG(29), __vcop_alws());
   __vcop_vmaxsetf(_VREG(29), _VREG(34), _VREG(35));
   __vcop_vadd(_VREG(17), _VREG(19), _VREG(17));
   __vcop_vsel(_VREG(35), _VREG(17), _VREG(33));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_last_i4(), _VREG(33), _PREG(10), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_last_i4(), _VREG(34), _PREG(12), _AGEN(1), _PREG(6));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("addr0", "A0");
   #pragma EVE_REG("angleAddr", "A1");
   #pragma EVE_REG("energyAddr", "A2");
   #pragma EVE_REG("inAddr", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("i", "I4");
   

   __vcop_vloop(__vcop_compute(), 20u, 8u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(14), _VREG(31));
   __vcop_vinit(__vcop_sizeHU(), __vcop_once(), _PREG(1), _VREG(30));
   __vcop_vagen(_AGEN(0), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeWU(), __vcop_1pt(), _PREG(16), _AGEN(0), _VREG(16), __vcop_once());
   __vcop_vload(__vcop_sizeWU(), __vcop_1pt(), _PREG(6), _AGEN(0), _VREG(26), __vcop_once());
   __vcop_vload(__vcop_sizeWU(), __vcop_1pt(), _PREG(8), _AGEN(0), _VREG(20), __vcop_once());
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(10), _AGEN(0), _VREG(36), __vcop_once());
   __vcop_vload(__vcop_sizeHU(), __vcop_1pt(), _PREG(12), _AGEN(0), _VREG(21), __vcop_once());
   __vcop_vshf(_VREG(36), _VREG(30), _VREG(18));
   __vcop_vshf(_VREG(36), _VREG(30), _VREG(27));
   __vcop_vadd(_VREG(16), _VREG(18), _VREG(16));
   __vcop_vadd(_VREG(26), _VREG(27), _VREG(26));
   __vcop_vor(_VREG(21), _VREG(21), _VREG(20));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_1pt(), __vcop_alws(), _VREG(16), _PREG(16), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_1pt(), __vcop_alws(), _VREG(26), _PREG(6), _AGEN(0), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_1pt(), __vcop_alws(), _VREG(20), _PREG(8), _AGEN(0), _PREG(0));
   __vcop_vloop_end(2u);

}

void vcop_beam_angle_association_kernel(
   __vptr_uint32 inputEnergy,
   __vptr_uint16 angleBuf,
   __vptr_uint16 energyBuf,
   __vptr_uint16 ptrToInfoBuffer,
   __vptr_uint32 ptrToParamBlock,
   unsigned short baseAngleOffset,
   unsigned short numDetections,
   unsigned short numAngles,
   unsigned short energyScalingFactor)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_beam_angle_association_kernel_init(inputEnergy, angleBuf, energyBuf, ptrToInfoBuffer, ptrToParamBlock, baseAngleOffset, numDetections, numAngles, energyScalingFactor, __pblock_vcop_beam_angle_association_kernel);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_beam_angle_association_kernel_vloops(__pblock_vcop_beam_angle_association_kernel);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_beam_angle_association_kernel_custom(
   __vptr_uint32 inputEnergy,
   __vptr_uint16 angleBuf,
   __vptr_uint16 energyBuf,
   __vptr_uint16 ptrToInfoBuffer,
   __vptr_uint32 ptrToParamBlock,
   unsigned short baseAngleOffset,
   unsigned short numDetections,
   unsigned short numAngles,
   unsigned short energyScalingFactor,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_beam_angle_association_kernel_init(inputEnergy, angleBuf, energyBuf, ptrToInfoBuffer, ptrToParamBlock, baseAngleOffset, numDetections, numAngles, energyScalingFactor, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_beam_angle_association_kernel_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

#pragma DATA_SECTION(__pblock_vcop_range_doppler_energy_angle_mapping_kernel, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_range_doppler_energy_angle_mapping_kernel, __ALIGNOF__(int));
unsigned short __pblock_vcop_range_doppler_energy_angle_mapping_kernel[16];

unsigned int vcop_range_doppler_energy_angle_mapping_kernel_param_count(void)
{
   return 16u;
}

unsigned int vcop_range_doppler_energy_angle_mapping_kernel_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_range_doppler_energy_angle_mapping_kernel_init(
   __vptr_uint32 coordinateBufEnergy,
   __vptr_uint16 angleDetectionMapping,
   __vptr_uint16 angleBuf,
   __vptr_uint16 energyBuf,
   unsigned short coordinateBufPitch,
   unsigned short numDetections,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((((numDetections) + (8u)-1U) & ~((8u)-1U))/ (8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)angleBuf);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)energyBuf);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)angleDetectionMapping);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)coordinateBufEnergy);
   __vcop_pblock_init16(pblock, __offset+_PREG(14), 32);
   __vcop_pblock_init16(pblock, __offset+_PREG(15), 16);
   __vcop_pblock_init32(pblock, __offset+_PREG(16), coordinateBufPitch);
   __offset += 16;

   return 16u;
}

void vcop_range_doppler_energy_angle_mapping_kernel_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */
   #pragma VCC_VREG("VAngle", 16);
   #pragma VCC_VREG("VAngleEnergy", 17);
   #pragma VCC_VREG("VEnergy", 18);
   #pragma VCC_VREG("VK16", 19);
   #pragma VCC_VREG("VMapping", 20);
   #pragma VCC_VREG("VMappingOffset", 21);
   #pragma VCC_VREG("VPitch", 22);

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("angleAddr", "A0");
   #pragma EVE_REG("angleDetMapAddr", "A1");
   #pragma EVE_REG("energyAddr", "A2");
   #pragma EVE_REG("outAddr", "A3");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("detectionIdx", "I4");
   

   __vcop_vloop(__vcop_compute(), 14u, 8u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_once(), _PREG(16), _VREG(22));
   __vcop_vinit(__vcop_sizeHU(), __vcop_once(), _PREG(15), _VREG(19));
   __vcop_vagen(_AGEN(0), _PREG(15), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(14), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(15), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(3), _PREG(0), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(6), _AGEN(0), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(8), _AGEN(2), _VREG(18), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_ds2(), _PREG(10), _AGEN(1), _VREG(20), __vcop_alws());
   __vcop_vshf(_VREG(16), _VREG(19), _VREG(16));
   __vcop_vadd(_VREG(16), _VREG(18), _VREG(16));
   __vcop_vmpy(_VREG(20), _VREG(22), _VREG(21), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeWU(), __vcop_sdda(_VREG(21)), __vcop_alws(), _VREG(16), _PREG(12), _AGEN(3), _PREG(0));
   __vcop_vloop_end(1u);

}

void vcop_range_doppler_energy_angle_mapping_kernel(
   __vptr_uint32 coordinateBufEnergy,
   __vptr_uint16 angleDetectionMapping,
   __vptr_uint16 angleBuf,
   __vptr_uint16 energyBuf,
   unsigned short coordinateBufPitch,
   unsigned short numDetections)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_range_doppler_energy_angle_mapping_kernel_init(coordinateBufEnergy, angleDetectionMapping, angleBuf, energyBuf, coordinateBufPitch, numDetections, __pblock_vcop_range_doppler_energy_angle_mapping_kernel);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_range_doppler_energy_angle_mapping_kernel_vloops(__pblock_vcop_range_doppler_energy_angle_mapping_kernel);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_range_doppler_energy_angle_mapping_kernel_custom(
   __vptr_uint32 coordinateBufEnergy,
   __vptr_uint16 angleDetectionMapping,
   __vptr_uint16 angleBuf,
   __vptr_uint16 energyBuf,
   unsigned short coordinateBufPitch,
   unsigned short numDetections,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_range_doppler_energy_angle_mapping_kernel_init(coordinateBufEnergy, angleDetectionMapping, angleBuf, energyBuf, coordinateBufPitch, numDetections, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_range_doppler_energy_angle_mapping_kernel_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

