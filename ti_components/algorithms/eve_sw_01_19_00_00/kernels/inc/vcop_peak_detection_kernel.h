#ifndef _TI_vcop_peak_detection_kernel_h_
#define _TI_vcop_peak_detection_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_tx_decoding_kernel[80];

/* Basic Runner Function */
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
   unsigned short pitch);
/* Custom Runner Function */
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
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
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
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_tx_decoding_kernel_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_tx_decoding_kernel ((unsigned int)80)
unsigned int vcop_tx_decoding_kernel_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_tx_decoding_kernel ((unsigned int)1)
unsigned int vcop_tx_decoding_kernel_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_peak_detection_energy_across_antenna[22];

/* Basic Runner Function */
void vcop_peak_detection_energy_across_antenna(
   __vptr_int16 inputData,
   __vptr_uint32 outputData,
   unsigned short numRows,
   unsigned short numAntennas,
   unsigned short numHorzPtPerAntenna,
   unsigned short pitch);
/* Custom Runner Function */
void vcop_peak_detection_energy_across_antenna_custom(
   __vptr_int16 inputData,
   __vptr_uint32 outputData,
   unsigned short numRows,
   unsigned short numAntennas,
   unsigned short numHorzPtPerAntenna,
   unsigned short pitch,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_peak_detection_energy_across_antenna_init(
   __vptr_int16 inputData,
   __vptr_uint32 outputData,
   unsigned short numRows,
   unsigned short numAntennas,
   unsigned short numHorzPtPerAntenna,
   unsigned short pitch,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_peak_detection_energy_across_antenna_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_peak_detection_energy_across_antenna ((unsigned int)22)
unsigned int vcop_peak_detection_energy_across_antenna_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_peak_detection_energy_across_antenna ((unsigned int)0)
unsigned int vcop_peak_detection_energy_across_antenna_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_peak_detection_binlog_energy_scaling[66];

/* Basic Runner Function */
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
   unsigned short numHorzPtPerAntenna);
/* Custom Runner Function */
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
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
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
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_peak_detection_binlog_energy_scaling_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_peak_detection_binlog_energy_scaling ((unsigned int)66)
unsigned int vcop_peak_detection_binlog_energy_scaling_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_peak_detection_binlog_energy_scaling ((unsigned int)0)
unsigned int vcop_peak_detection_binlog_energy_scaling_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_peak_detection_cell_sum[68];

/* Basic Runner Function */
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
   unsigned short shift);
/* Custom Runner Function */
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
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
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
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_peak_detection_cell_sum_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_peak_detection_cell_sum ((unsigned int)68)
unsigned int vcop_peak_detection_cell_sum_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_peak_detection_cell_sum ((unsigned int)0)
unsigned int vcop_peak_detection_cell_sum_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_peak_detection_CFARCA_thresholding[76];

/* Basic Runner Function */
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
   signed short threshold);
/* Custom Runner Function */
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
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
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
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_peak_detection_CFARCA_thresholding_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_peak_detection_CFARCA_thresholding ((unsigned int)76)
unsigned int vcop_peak_detection_CFARCA_thresholding_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_peak_detection_CFARCA_thresholding ((unsigned int)0)
unsigned int vcop_peak_detection_CFARCA_thresholding_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_peak_detection_transpose[46];

/* Basic Runner Function */
void vcop_peak_detection_transpose(
   __vptr_uint16 inputEnergy1,
   __vptr_uint16 inputEnergy2,
   __vptr_uint16 outputEnergy,
   __vptr_uint16 scatterIndex,
   unsigned short numHorzPoint,
   unsigned short numVertPoint,
   unsigned short transposePitch,
   unsigned short numExtraLines);
/* Custom Runner Function */
void vcop_peak_detection_transpose_custom(
   __vptr_uint16 inputEnergy1,
   __vptr_uint16 inputEnergy2,
   __vptr_uint16 outputEnergy,
   __vptr_uint16 scatterIndex,
   unsigned short numHorzPoint,
   unsigned short numVertPoint,
   unsigned short transposePitch,
   unsigned short numExtraLines,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_peak_detection_transpose_init(
   __vptr_uint16 inputEnergy1,
   __vptr_uint16 inputEnergy2,
   __vptr_uint16 outputEnergy,
   __vptr_uint16 scatterIndex,
   unsigned short numHorzPoint,
   unsigned short numVertPoint,
   unsigned short transposePitch,
   unsigned short numExtraLines,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_peak_detection_transpose_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_peak_detection_transpose ((unsigned int)46)
unsigned int vcop_peak_detection_transpose_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_peak_detection_transpose ((unsigned int)0)
unsigned int vcop_peak_detection_transpose_ctrl_count(void);

/***********************************************************/
#endif

