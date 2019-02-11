#ifndef _TI_vcop_beam_forming_kernel_h_
#define _TI_vcop_beam_forming_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_beam_forming_copy_steering_matrix_kernel[10];

/* Basic Runner Function */
void vcop_beam_forming_copy_steering_matrix_kernel(
   __vptr_uint32 inputData,
   __vptr_uint32 outputData,
   unsigned short numAngles,
   unsigned short numAntennas);
/* Custom Runner Function */
void vcop_beam_forming_copy_steering_matrix_kernel_custom(
   __vptr_uint32 inputData,
   __vptr_uint32 outputData,
   unsigned short numAngles,
   unsigned short numAntennas,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_beam_forming_copy_steering_matrix_kernel_init(
   __vptr_uint32 inputData,
   __vptr_uint32 outputData,
   unsigned short numAngles,
   unsigned short numAntennas,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_beam_forming_copy_steering_matrix_kernel_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_beam_forming_copy_steering_matrix_kernel ((unsigned int)10)
unsigned int vcop_beam_forming_copy_steering_matrix_kernel_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_beam_forming_copy_steering_matrix_kernel ((unsigned int)0)
unsigned int vcop_beam_forming_copy_steering_matrix_kernel_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_beam_forming_transpose_antenna_data_kernel[14];

/* Basic Runner Function */
void vcop_beam_forming_transpose_antenna_data_kernel(
   __vptr_uint32 inputData,
   __vptr_uint32 outputData,
   __vptr_uint16 pScatterIndex,
   unsigned short outputPitch,
   unsigned short numDetections,
   unsigned short numAntennas);
/* Custom Runner Function */
void vcop_beam_forming_transpose_antenna_data_kernel_custom(
   __vptr_uint32 inputData,
   __vptr_uint32 outputData,
   __vptr_uint16 pScatterIndex,
   unsigned short outputPitch,
   unsigned short numDetections,
   unsigned short numAntennas,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_beam_forming_transpose_antenna_data_kernel_init(
   __vptr_uint32 inputData,
   __vptr_uint32 outputData,
   __vptr_uint16 pScatterIndex,
   unsigned short outputPitch,
   unsigned short numDetections,
   unsigned short numAntennas,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_beam_forming_transpose_antenna_data_kernel_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_beam_forming_transpose_antenna_data_kernel ((unsigned int)14)
unsigned int vcop_beam_forming_transpose_antenna_data_kernel_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_beam_forming_transpose_antenna_data_kernel ((unsigned int)0)
unsigned int vcop_beam_forming_transpose_antenna_data_kernel_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_beam_forming_kernel[24];

/* Basic Runner Function */
void vcop_beam_forming_kernel(
   __vptr_int16 inputData,
   __vptr_int16 outputData,
   __vptr_int16 steeringMatrix,
   unsigned short pitch,
   unsigned short numDetections,
   unsigned short numAntennas,
   unsigned short numAngles,
   unsigned short scale);
/* Custom Runner Function */
void vcop_beam_forming_kernel_custom(
   __vptr_int16 inputData,
   __vptr_int16 outputData,
   __vptr_int16 steeringMatrix,
   unsigned short pitch,
   unsigned short numDetections,
   unsigned short numAntennas,
   unsigned short numAngles,
   unsigned short scale,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_beam_forming_kernel_init(
   __vptr_int16 inputData,
   __vptr_int16 outputData,
   __vptr_int16 steeringMatrix,
   unsigned short pitch,
   unsigned short numDetections,
   unsigned short numAntennas,
   unsigned short numAngles,
   unsigned short scale,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_beam_forming_kernel_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_beam_forming_kernel ((unsigned int)24)
unsigned int vcop_beam_forming_kernel_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_beam_forming_kernel ((unsigned int)0)
unsigned int vcop_beam_forming_kernel_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_beam_energy_calculation_kernel[16];

/* Basic Runner Function */
void vcop_beam_energy_calculation_kernel(
   __vptr_int16 inputData,
   __vptr_uint32 outputEnergy,
   unsigned short numDetections,
   unsigned short numAngles);
/* Custom Runner Function */
void vcop_beam_energy_calculation_kernel_custom(
   __vptr_int16 inputData,
   __vptr_uint32 outputEnergy,
   unsigned short numDetections,
   unsigned short numAngles,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_beam_energy_calculation_kernel_init(
   __vptr_int16 inputData,
   __vptr_uint32 outputEnergy,
   unsigned short numDetections,
   unsigned short numAngles,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_beam_energy_calculation_kernel_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_beam_energy_calculation_kernel ((unsigned int)16)
unsigned int vcop_beam_energy_calculation_kernel_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_beam_energy_calculation_kernel ((unsigned int)0)
unsigned int vcop_beam_energy_calculation_kernel_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_beam_angle_association_kernel[36];

/* Basic Runner Function */
void vcop_beam_angle_association_kernel(
   __vptr_uint32 inputEnergy,
   __vptr_uint16 angleBuf,
   __vptr_uint16 energyBuf,
   __vptr_uint16 ptrToInfoBuffer,
   __vptr_uint32 ptrToParamBlock,
   unsigned short baseAngleOffset,
   unsigned short numDetections,
   unsigned short numAngles,
   unsigned short energyScalingFactor);
/* Custom Runner Function */
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
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
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
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_beam_angle_association_kernel_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_beam_angle_association_kernel ((unsigned int)36)
unsigned int vcop_beam_angle_association_kernel_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_beam_angle_association_kernel ((unsigned int)0)
unsigned int vcop_beam_angle_association_kernel_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_range_doppler_energy_angle_mapping_kernel[16];

/* Basic Runner Function */
void vcop_range_doppler_energy_angle_mapping_kernel(
   __vptr_uint32 coordinateBufEnergy,
   __vptr_uint16 angleDetectionMapping,
   __vptr_uint16 angleBuf,
   __vptr_uint16 energyBuf,
   unsigned short coordinateBufPitch,
   unsigned short numDetections);
/* Custom Runner Function */
void vcop_range_doppler_energy_angle_mapping_kernel_custom(
   __vptr_uint32 coordinateBufEnergy,
   __vptr_uint16 angleDetectionMapping,
   __vptr_uint16 angleBuf,
   __vptr_uint16 energyBuf,
   unsigned short coordinateBufPitch,
   unsigned short numDetections,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_range_doppler_energy_angle_mapping_kernel_init(
   __vptr_uint32 coordinateBufEnergy,
   __vptr_uint16 angleDetectionMapping,
   __vptr_uint16 angleBuf,
   __vptr_uint16 energyBuf,
   unsigned short coordinateBufPitch,
   unsigned short numDetections,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_range_doppler_energy_angle_mapping_kernel_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_range_doppler_energy_angle_mapping_kernel ((unsigned int)16)
unsigned int vcop_range_doppler_energy_angle_mapping_kernel_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_range_doppler_energy_angle_mapping_kernel ((unsigned int)0)
unsigned int vcop_range_doppler_energy_angle_mapping_kernel_ctrl_count(void);

/***********************************************************/
#endif

