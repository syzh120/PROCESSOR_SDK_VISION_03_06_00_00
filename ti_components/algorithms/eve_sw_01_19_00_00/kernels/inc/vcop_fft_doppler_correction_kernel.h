#ifndef _TI_vcop_fft_doppler_correction_kernel_h_
#define _TI_vcop_fft_doppler_correction_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_fft_doppler_correction_kernel[24];

/* Basic Runner Function */
void vcop_fft_doppler_correction_kernel(
   __vptr_int16 inputData,
   __vptr_int16 outputData,
   __vptr_int16 dopplerCorrectionBuf,
   __vptr_uint16 pScatterIndex,
   unsigned short transposePitch,
   unsigned short numPoints,
   unsigned short numOfLines,
   unsigned short scaleFactor,
   unsigned short saturationLimit);
/* Custom Runner Function */
void vcop_fft_doppler_correction_kernel_custom(
   __vptr_int16 inputData,
   __vptr_int16 outputData,
   __vptr_int16 dopplerCorrectionBuf,
   __vptr_uint16 pScatterIndex,
   unsigned short transposePitch,
   unsigned short numPoints,
   unsigned short numOfLines,
   unsigned short scaleFactor,
   unsigned short saturationLimit,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_fft_doppler_correction_kernel_init(
   __vptr_int16 inputData,
   __vptr_int16 outputData,
   __vptr_int16 dopplerCorrectionBuf,
   __vptr_uint16 pScatterIndex,
   unsigned short transposePitch,
   unsigned short numPoints,
   unsigned short numOfLines,
   unsigned short scaleFactor,
   unsigned short saturationLimit,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_fft_doppler_correction_kernel_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_fft_doppler_correction_kernel ((unsigned int)24)
unsigned int vcop_fft_doppler_correction_kernel_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_fft_doppler_correction_kernel ((unsigned int)0)
unsigned int vcop_fft_doppler_correction_kernel_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_fft_doppler_pitch_removal[12];

/* Basic Runner Function */
void vcop_fft_doppler_pitch_removal(
   __vptr_int16 inputData,
   __vptr_int16 outputData,
   unsigned short inputPitch,
   unsigned short outputPitch,
   unsigned short numPoints,
   unsigned short numOfLines);
/* Custom Runner Function */
void vcop_fft_doppler_pitch_removal_custom(
   __vptr_int16 inputData,
   __vptr_int16 outputData,
   unsigned short inputPitch,
   unsigned short outputPitch,
   unsigned short numPoints,
   unsigned short numOfLines,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_fft_doppler_pitch_removal_init(
   __vptr_int16 inputData,
   __vptr_int16 outputData,
   unsigned short inputPitch,
   unsigned short outputPitch,
   unsigned short numPoints,
   unsigned short numOfLines,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_fft_doppler_pitch_removal_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_fft_doppler_pitch_removal ((unsigned int)12)
unsigned int vcop_fft_doppler_pitch_removal_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_fft_doppler_pitch_removal ((unsigned int)0)
unsigned int vcop_fft_doppler_pitch_removal_ctrl_count(void);

/***********************************************************/
#endif

