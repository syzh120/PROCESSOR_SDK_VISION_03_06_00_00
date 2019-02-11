#ifndef _TI_vcop_fft_doppler_correction_32ix32o_kernel_h_
#define _TI_vcop_fft_doppler_correction_32ix32o_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_copy_fft_32ix32o_kernel[10];

/* Basic Runner Function */
void vcop_copy_fft_32ix32o_kernel(
   __vptr_int32 inputData,
   __vptr_int32 outputData,
   unsigned short numPoints,
   unsigned short numOfLines);
/* Custom Runner Function */
void vcop_copy_fft_32ix32o_kernel_custom(
   __vptr_int32 inputData,
   __vptr_int32 outputData,
   unsigned short numPoints,
   unsigned short numOfLines,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_copy_fft_32ix32o_kernel_init(
   __vptr_int32 inputData,
   __vptr_int32 outputData,
   unsigned short numPoints,
   unsigned short numOfLines,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_copy_fft_32ix32o_kernel_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_copy_fft_32ix32o_kernel ((unsigned int)10)
unsigned int vcop_copy_fft_32ix32o_kernel_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_copy_fft_32ix32o_kernel ((unsigned int)0)
unsigned int vcop_copy_fft_32ix32o_kernel_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_fft_transpose_output_32ix32o_kernel[18];

/* Basic Runner Function */
void vcop_fft_transpose_output_32ix32o_kernel(
   __vptr_int32 inputData,
   __vptr_int32 outputData,
   __vptr_uint16 pScatterIndex,
   unsigned short transposePitch,
   unsigned short numPoints,
   unsigned short numOfLines);
/* Custom Runner Function */
void vcop_fft_transpose_output_32ix32o_kernel_custom(
   __vptr_int32 inputData,
   __vptr_int32 outputData,
   __vptr_uint16 pScatterIndex,
   unsigned short transposePitch,
   unsigned short numPoints,
   unsigned short numOfLines,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_fft_transpose_output_32ix32o_kernel_init(
   __vptr_int32 inputData,
   __vptr_int32 outputData,
   __vptr_uint16 pScatterIndex,
   unsigned short transposePitch,
   unsigned short numPoints,
   unsigned short numOfLines,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_fft_transpose_output_32ix32o_kernel_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_fft_transpose_output_32ix32o_kernel ((unsigned int)18)
unsigned int vcop_fft_transpose_output_32ix32o_kernel_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_fft_transpose_output_32ix32o_kernel ((unsigned int)0)
unsigned int vcop_fft_transpose_output_32ix32o_kernel_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_fft_doppler_correction_32ix32o_kernel[30];

/* Basic Runner Function */
void vcop_fft_doppler_correction_32ix32o_kernel(
   __vptr_int32 inputData,
   __vptr_int32 outputData,
   __vptr_int16 dopplerCorrectionBuf,
   __vptr_uint16 pScatterIndex,
   unsigned short transposePitch,
   unsigned short numPoints,
   unsigned short numOfLines,
   unsigned short scaleFactor,
   unsigned short saturationLimit);
/* Custom Runner Function */
void vcop_fft_doppler_correction_32ix32o_kernel_custom(
   __vptr_int32 inputData,
   __vptr_int32 outputData,
   __vptr_int16 dopplerCorrectionBuf,
   __vptr_uint16 pScatterIndex,
   unsigned short transposePitch,
   unsigned short numPoints,
   unsigned short numOfLines,
   unsigned short scaleFactor,
   unsigned short saturationLimit,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_fft_doppler_correction_32ix32o_kernel_init(
   __vptr_int32 inputData,
   __vptr_int32 outputData,
   __vptr_int16 dopplerCorrectionBuf,
   __vptr_uint16 pScatterIndex,
   unsigned short transposePitch,
   unsigned short numPoints,
   unsigned short numOfLines,
   unsigned short scaleFactor,
   unsigned short saturationLimit,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_fft_doppler_correction_32ix32o_kernel_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_fft_doppler_correction_32ix32o_kernel ((unsigned int)30)
unsigned int vcop_fft_doppler_correction_32ix32o_kernel_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_fft_doppler_correction_32ix32o_kernel ((unsigned int)0)
unsigned int vcop_fft_doppler_correction_32ix32o_kernel_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_fft_doppler_pitch_removal_32ix32o[12];

/* Basic Runner Function */
void vcop_fft_doppler_pitch_removal_32ix32o(
   __vptr_int32 inputData,
   __vptr_int32 outputData,
   unsigned short inputPitch,
   unsigned short outputPitch,
   unsigned short numPoints,
   unsigned short numOfLines);
/* Custom Runner Function */
void vcop_fft_doppler_pitch_removal_32ix32o_custom(
   __vptr_int32 inputData,
   __vptr_int32 outputData,
   unsigned short inputPitch,
   unsigned short outputPitch,
   unsigned short numPoints,
   unsigned short numOfLines,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_fft_doppler_pitch_removal_32ix32o_init(
   __vptr_int32 inputData,
   __vptr_int32 outputData,
   unsigned short inputPitch,
   unsigned short outputPitch,
   unsigned short numPoints,
   unsigned short numOfLines,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_fft_doppler_pitch_removal_32ix32o_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_fft_doppler_pitch_removal_32ix32o ((unsigned int)12)
unsigned int vcop_fft_doppler_pitch_removal_32ix32o_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_fft_doppler_pitch_removal_32ix32o ((unsigned int)0)
unsigned int vcop_fft_doppler_pitch_removal_32ix32o_ctrl_count(void);

/***********************************************************/
#endif

